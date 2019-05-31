#include "race.hpp"

Bolide::Bolide(std::string name,
		double max_velocity,
		double acceleration,
		double deceleration,
		unsigned num_of_gears,
		bool abs,
		bool traction_control,
		double mass,
		double downforce) {
	this->max_velocity = max_velocity;
	this->acceleration = acceleration;
	this->deceleration = deceleration;
	this->num_of_gears = num_of_gears;
	this->abs = abs;
	this->traction_control = traction_control;
	this->mass = mass;
	this->downforce = downforce;
}

Race::Race(double track_length,
	   unsigned num_of_turns,
	   double friction_coefficient) {
	this->track_length = track_length;
	this->num_of_turns = num_of_turns;
	this->friction_coefficient = friction_coefficient;
}

void Race::add_bolide(Bolide bolide) {
	this->bolides.push_back(std::make_pair(bolide, 0));
}
