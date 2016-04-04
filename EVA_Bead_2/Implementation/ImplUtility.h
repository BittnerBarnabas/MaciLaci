#pragma once

#include <fstream>
#include <string>
#include "ImpTypes.h"
#include <sstream>
#include <memory>

namespace Implementation
{

	std::unique_ptr<BoardRepresentation> readBoardFromFile(std::string Path); //!< Reads a file specified by Path and creates a BoardRepresentation
	bool inRange(int r, int c, const BoardRepresentation& board); //!< Check whether a point on a BoardRepresentation.gameBoard is in range
	bool isObstruction(int r, int c, const BoardRepresentation& board); //!< Check whether a point on a BoardRepresentation.gameBoard is free to step on
	bool isPlayerInRange(int r, int c, const BoardRepresentation& board); //!< Check whether a point on a BoardRepresentation.gameBoard is free to step on by player
	std::pair<int, int> directionDispatch(direction_t dir); //!< Returns an int pair, each in {-1,0,1}, achieves the movement according to the direction

    /*!  Sets the ownership of a circle (3x3) around the given coordinates, if it satisfies the given function 
    \param r The first coordinate of the center of the circle
    \param c The second coordinate of the center of the circle
    \param board The gameBoard on which you want to set the ownership
    \param func The object which has operator() and does range cheching also, has 3 params (r,c,board), returns bool
    \param pl The desired player to own the field if func returns true 
    */ 
	template<class Functor_t>
	void applyToRange(int r, int c, BoardRepresentation& board, Functor_t func, player_t pl)
	{
		const int deltas[16] = { 1,0,1,1,0,1,-1,1,-1,0,-1,-1,0,-1,1,-1 };

		for (int i = 0; i < 15; i += 2)
		{
			if (func(r + deltas[i], c + deltas[i + 1], board))
			{
				board.gameBoard[r + deltas[i]][c + deltas[i + 1]] = pl;
			}
		}
	}

}