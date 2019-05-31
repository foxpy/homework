#include "race.hpp"

int main(void)
{
	Race race(12.0f,	// track_length (m)
		  4,    	// number_of_turns
		  0.8); 	// friction_coefficient
	return EXIT_SUCCESS;
}
