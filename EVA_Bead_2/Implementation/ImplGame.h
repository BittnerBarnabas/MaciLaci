#pragma once

#include <memory>
#include <QObject>
#include <QTimer>
#include <QTime>

#include "ImpTypes.h"
#include "ImplUtility.h"

namespace Implementation
{
	class MagicGameImpl : public QObject
	{
	private:
		Q_OBJECT;
		QTimer hunterRefreshTimer; //!< Interval between refreshing the pos of hunters
		QTimer secondsTimer; //!< Time after elapsedT is incremented
		int elapsedT; //!< Elapsed time
		bool isInPausedState; //!< Whether the game is paused
		std::unique_ptr<BoardRepresentation> game; //!< The actual game's properties
        
	public:
		MagicGameImpl(QObject *parent = nullptr);
		~MagicGameImpl();
		inline const BoardRepresentation& getBoardRepr() const { return *game.get();}

	public slots:
		void newGame(QString path); //!< Sets up the game, initiates all other variables
		void updateHunters(); //!< Updates the position of hunters, according to the rules of the game
		void sendElapsedTime(); //!< Sends the elapsed time
		void pauseGame(); //!< Pauses the game, if it's not paused, continues if it's 
		void movePlayer(Implementation::direction_t dir); //!< Moves player in the direction specified

	signals:
		void updatedHunters();
		void updatedPlayer();
		void elapsedTime(int sec);
		void newGameStarted();
		void endGame(int result);
		void sendFoodToEat(int);
	};

}
