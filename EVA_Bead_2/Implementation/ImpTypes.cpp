#include "ImpTypes.h"

namespace Implementation
{
	std::istream & operator>>(std::istream & is, direction_t & dir)
	{
		{
			std::string temp;
			is >> temp;
			if (temp == "UP")
			{
				dir = direction_t::UP;
			}
			else if (temp == "DOWN")
			{
				dir = direction_t::DOWN;
			}
			else if (temp == "LEFT")
			{
				dir = direction_t::LEFT;
			}
			else
			{
				dir = direction_t::RIGHT;
			}
			return is;
		}
	}
}