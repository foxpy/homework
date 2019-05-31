#include "race.hpp"

Race::Race(double track_length,
	   unsigned number_of_turns,
	   double friction_coefficient)
{
	this->track_length = track_length;
	this->number_of_turns = number_of_turns;
	this->friction_coefficient = friction_coefficient;
}

void Race::add_bolide(Bolide bolide)
{
	this->bolides.push_back(std::make_pair(bolide, 0));
}
