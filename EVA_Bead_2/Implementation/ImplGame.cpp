#include "ImplGame.h"

namespace Implementation
{
	MagicGameImpl::MagicGameImpl(QObject *parent)
		: QObject(parent), hunterRefreshTimer(), secondsTimer(), elapsedT(0), isInPausedState(false) ,game(nullptr)
	{
		connect(&hunterRefreshTimer, SIGNAL(timeout()), this, SLOT(updateHunters()));
		connect(&secondsTimer, SIGNAL(timeout()), this, SLOT(sendElapsedTime()));
	}

	MagicGameImpl::~MagicGameImpl()
	{}

	void MagicGameImpl::newGame(QString path)
	{
		game = readBoardFromFile(path.toStdString());
		secondsTimer.setInterval(1000);
		hunterRefreshTimer.setInterval(1000);
		hunterRefreshTimer.start();
		secondsTimer.start();
		elapsedT = 0;

		emit(newGameStarted());
		emit(sendFoodToEat(game->foodToEat));
	}

	void MagicGameImpl::updateHunters()
	{
		for (auto& hunters : game->hunterPos)
		{
			//get new coordinates
			auto updatedCoord = directionDispatch(hunters.second);


			auto freeToColor = [](int r, int c, BoardRepresentation& board)
			{
				return (inRange(r, c, board) && !isObstruction(r, c, board));
			};

			//removes color
			applyToRange(hunters.first.first, hunters.first.second, *game.get(), freeToColor, player_t::NoPlayer);


			//if it's out of range or would collide with an obstacle
			if (!freeToColor(hunters.first.first+updatedCoord.first,hunters.first.second+ updatedCoord.second,*game.get()))
			{
				switch (hunters.second)
				{
				case Implementation::direction_t::UP:
					hunters.second = direction_t::DOWN;
					break;
				case Implementation::direction_t::DOWN:
					hunters.second = direction_t::UP;
					break;
				case Implementation::direction_t::LEFT:
					hunters.second = direction_t::RIGHT;
					break;
				case Implementation::direction_t::RIGHT:
					hunters.second = direction_t::LEFT;
					break;
				default:
					break;
				}
				applyToRange(hunters.first.first, hunters.first.second, *game.get(), freeToColor, player_t::InHunterRange);
				continue;
			}

			//updates the hunters position
			game->gameBoard[hunters.first.first][hunters.first.second] = player_t::NoPlayer;
			game->gameBoard[hunters.first.first+ updatedCoord.first][hunters.first.second+ updatedCoord.second] = player_t::Hunter;
			//updates the coordinates of the hunter
			hunters.first.first += updatedCoord.first;
			hunters.first.second += updatedCoord.second;
			//sets the hunters range 
			applyToRange(hunters.first.first, hunters.first.second, *game.get(), freeToColor,player_t::InHunterRange);

			//checks if player is in the range
			if (isPlayerInRange(hunters.first.first, hunters.first.second, *game.get()))
			{
				emit(endGame(0));
				return;
			}

		}
		emit updatedHunters();
	}

	void MagicGameImpl::sendElapsedTime()
	{
		++elapsedT;
		emit(elapsedTime(elapsedT));
	}

	void MagicGameImpl::pauseGame()
	{
		if (isInPausedState)
		{
			hunterRefreshTimer.start();
			secondsTimer.start();
		}
		else
		{
			hunterRefreshTimer.stop();
			secondsTimer.stop();
		}
		isInPausedState = !isInPausedState;
	}

	void MagicGameImpl::movePlayer(Implementation::direction_t dir)
	{
		if (isInPausedState) return;
		//sets the new coordinates of the player
		auto newPlayerCoord = directionDispatch(dir);
		int X = game->playerPos.first + newPlayerCoord.first;
		int Y = game->playerPos.second + newPlayerCoord.second;
		if (!inRange(X, Y, *game.get())) return;
		//checks whether the player is stepping on a food or hunter range
		if (game->gameBoard[X][Y] == player_t::Food)
		{
			game->gameBoard[X][Y] = player_t::NoPlayer;
			--game->foodToEat;
			emit(sendFoodToEat(game->foodToEat));
			if (game->foodToEat == 0)
			{
				emit(endGame(1));
				return;
			}
		}
		else if (game->gameBoard[X][Y] == player_t::InHunterRange)
		{
			emit(endGame(0));
			return;
		}
		else if (isObstruction(X, Y, *game.get()))
		{
			return;
		}
			
		//updating the players position
		game->gameBoard[game->playerPos.first][game->playerPos.second] = player_t::NoPlayer;
		game->playerPos.first = X;
		game->playerPos.second = Y;
		game->gameBoard[game->playerPos.first][game->playerPos.second] = player_t::MaciLaci;

		emit(updatedPlayer());
	}

}
