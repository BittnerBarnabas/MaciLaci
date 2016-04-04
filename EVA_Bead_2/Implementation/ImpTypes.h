#pragma once


#include <QVector>
#include <QPair>
#include <istream>

namespace Implementation
{
    /// Type of possible objects on the map
	enum class player_t
	{
		NoPlayer,MaciLaci, Tree, Hunter, InHunterRange, Food
	}; 
    /// Type of possible moving directions
	enum class direction_t 
	{
		UP, DOWN, LEFT, RIGHT
	}; 
	using gameBoard_t = QVector<QVector<player_t>>; //!< Type of the gameboard
	using hunterIndex_t = QPair<QPair<int, int>, direction_t>; //!< Type of hunter indexing 
	using playerIndex_t = QPair<int, int>; //!< Type of player indexing

	struct BoardRepresentation
	{
		gameBoard_t gameBoard; //!< Actual gameBoard object which holds the players on it
		QVector<hunterIndex_t> hunterPos; //!< Position of the hunters in the game
		playerIndex_t playerPos; //!< Position of player
		int boardSize; //!< Size of the gameBoard
		int hunterNumber; //!< Size of hunterPos
		int foodToEat; //!< Actual food left to be eaten
	};
	
	std::istream& operator>> (std::istream& is, direction_t& dir);
}