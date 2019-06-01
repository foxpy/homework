#include <iostream>
#include "race.hpp"

int main(void)
{
	Race race(3200.0f,	// track_length (m)
		  4,    	// num_of_turns
		  0.8); 	// friction_coefficient

	race.add_bolide(Bolide("Aston Martin DB9", // name
				299.0f, // max_velocity (kmph)
				21.7f, // acceleration (ms-2)
				17.2f, // deceleration (ms-2)
				6, // num_of_gears
				true, // abs
				true, // traction_control
				1760.0f, // mass (kg)
				0.9f)); // downforce (g)

	race.add_bolide(Bolide("Audi S4", // name
				249.0f, // max_velocity (kmph)
				20.8f, // acceleration (ms-2)
				18.9f, // deceleration (ms-2)
				6, // num_of_gears
				false, // abs
				true, // traction_control
				1660.0f, // mass (kg)
				1.1f)); // downforce (g)

	race.add_bolide(Bolide("BMW M3", // name
				249.0f, // max_velocity (kmph)
				25.6f, // acceleration (ms-2)
				14.2f, // deceleration (ms-2)
				6, // num_of_gears
				false, // abs
				false, // traction_control
				1655.0f, // mass (kg)
				0.7f)); // downforce (g)

	race.add_bolide(Bolide("Dodge Challenger Concept", // name
				280.0f, // max_velocity (kmph)
				22.2f, // acceleration (ms-2)
				12.3f, // deceleration (ms-2)
				6, // num_of_gears
				false, // abs
				false, // traction_control
				1750.0f, // mass (kg)
				0.6f)); // downforce (g)

	race.add_bolide(Bolide("Ferrari F50 GT", // name
				377.0f, // max_velocity (kmph)
				34.5f, // acceleration (ms-2)
				27.3f, // deceleration (ms-2)
				6, // num_of_gears
				true, // abs
				true, // traction_control
				908.0f, // mass (kg)
				1.7f)); // downforce (g)

	race.add_bolide(Bolide("Mazda RX-7 (FD)", // name
				249.0f, // max_velocity (kmph)
				18.2f, // acceleration (ms-2)
				22.3f, // deceleration (ms-2)
				5, // num_of_gears
				true, // abs
				true, // traction_control
				1310.0f, // mass (kg)
				0.9f)); // downforce (g)

	race.add_bolide(Bolide("Mitsubishi Lancer Evolution X", // name
				266.0f, // max_velocity (kmph)
				18.5f, // acceleration (ms-2)
				23.1f, // deceleration (ms-2)
				6, // num_of_gears
				true, // abs
				false, // traction_control
				1370.0f, // mass (kg)
				0.7f)); // downforce (g)

	race.add_bolide(Bolide("Subaru Impreza WRX STI (2006)", // name
				249.0f, // max_velocity (kmph)
				19.6f, // acceleration (ms-2)
				21.2f, // deceleration (ms-2)
				6, // num_of_gears
				true, // abs
				true, // traction_control
				1520.0f, // mass (kg)
				0.8f)); // downforce (g)

	race.add_bolide(Bolide("Porsche 911 GT3 RS", // name
				311.0f, // max_velocity (kmph)
				25.0f, // acceleration (ms-2)
				21.6f, // deceleration (ms-2)
				6, // num_of_gears
				true, // abs
				true, // traction_control
				1325.0f, // mass (kg)
				1.5f)); // downforce (g)

	race.print_stats();

	return EXIT_SUCCESS;
}
