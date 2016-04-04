#include "ImplUtility.h"

namespace Implementation
{
	
	std::unique_ptr<BoardRepresentation> readBoardFromFile(std::string Path)
	{
		//File: First line - GameSize, Second - PlayerPos, Third Number Of Food and Food pos, Fourth Number of hunters and rowNum and Direction

		std::ifstream file(Path);
		if (!file.is_open()) throw std::ios_base::failure("Couldn't open file");

		auto repr = std::make_unique<BoardRepresentation>();
		std::string line;
		
		try
		{
			file >> repr->boardSize >> repr->playerPos.first >> repr->playerPos.second;

			repr->gameBoard.resize(repr->boardSize);
			for (auto& row : repr->gameBoard)
			{
				row.resize(repr->boardSize);
			}
		}
		catch (const std::exception&)
		{
			throw std::ios_base::failure("Wrong map size or player pos.");
		}


		repr->gameBoard[repr->playerPos.first][repr->playerPos.second] = player_t::MaciLaci;

		int FoodNum;

		file >> FoodNum;
		repr->foodToEat = FoodNum;
		for (int i = 0; i < FoodNum; ++i)
		{
			int row, col;
			file >> row >> col;
			repr->gameBoard[row][col] = player_t::Food;
		}

		int HunterNum;
		file >> HunterNum;
		for (int i = 0; i < HunterNum; ++i)
		{
			direction_t dir;
			int row, col;
			file >> row >> col >> dir;


			repr->gameBoard[row][col] = player_t::Hunter;
			applyToRange(row, col, *repr.get(),inRange,player_t::InHunterRange);
			QPair<QPair<int,int>,direction_t> ind = { {row,col},dir };
			repr->hunterPos.push_back(ind);
			++(repr->hunterNumber);
		}

		try
		{
			int TreeNum;
			file >> TreeNum;
			for (int i = 0; i < TreeNum; ++i)
			{
				int row, col;
				file >> row >> col;
				repr->gameBoard[row][col] = player_t::Tree;
			}
		}
		catch (const std::exception&)
		{
			throw std::ios_base::failure("Missing or badly formatted tree numbers.");
		}


		return repr;
		
	}

	bool inRange(int r, int c, const BoardRepresentation & board)
	{
		return (r >= board.boardSize || r < 0 || c >= board.boardSize || c < 0) ? false : true;
	}

	bool isObstruction(int r, int c, const BoardRepresentation & board)
	{
		if (board.gameBoard[r][c] == player_t::NoPlayer || board.gameBoard[r][c] == player_t::InHunterRange)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	bool isPlayerInRange(int r, int c, const BoardRepresentation& board)
	{
		const int deltas[16] = { 1,0,1,1,0,1,-1,1,-1,0,-1,-1,0,-1,1,-1 };

		for (int i = 0; i < 15; i += 2)
		{
			if (inRange(r + deltas[i], c + deltas[i + 1], board) && board.gameBoard[r + deltas[i]][c + deltas[i + 1]] == player_t::MaciLaci)
			{
				return true;
			}
		}
		return false;
	}

	std::pair<int, int> directionDispatch(direction_t dir)
	{
		int i = 0, j = 0;
		switch (dir)
		{
		case Implementation::direction_t::UP:
			--i;
			break;
		case Implementation::direction_t::DOWN:
			++i;
			break;
		case Implementation::direction_t::LEFT:
			--j;
			break;
		case Implementation::direction_t::RIGHT:
			++j;
			break;
		default:
			break;
		}
		return std::make_pair(i, j);
	}

}
