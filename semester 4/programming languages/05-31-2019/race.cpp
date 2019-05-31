#include <stdexcept>
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
	if (max_velocity <= 0) {
		throw std::invalid_argument(
			"Maximum velocity should be positive");
	}
	if (acceleration <= 0) {
		throw std::invalid_argument(
			"Acceleration should be positive");
	}
	if (deceleration <= 0) {
		throw std::invalid_argument(
			"Deceleration should be positive");
	}
	if (mass <= 0) {
		throw std::invalid_argument(
			"Mass should be positive");
	}
	if (downforce <= 0) {
		throw std::invalid_argument(
			"Downforce should be positive");
	}

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
	if (track_length <= 0) {
		throw std::invalid_argument(
			"Track length should be positive");
	}
	if (!(friction_coefficient >= 0) && (friction_coefficient <= 1)) {
		throw std::invalid_argument("Friction coefficient should be in rage [0; 1]");
	}

	this->track_length = track_length;
	this->num_of_turns = num_of_turns;
	this->friction_coefficient = friction_coefficient;
}

void Race::add_bolide(Bolide bolide) {
	this->bolides.push_back(std::make_pair(bolide, 0));
}
