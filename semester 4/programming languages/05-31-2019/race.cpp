#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "race.hpp"
#include "scores.hpp"

bool operator < (std::pair<Bolide, unsigned> l, std::pair<Bolide, unsigned> r)
{ return l.second < r.second; }

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

	this->name = name;
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
		throw std::invalid_argument("Friction coefficient should be in range [0; 1]");
	}

	this->track_length = track_length;
	this->num_of_turns = num_of_turns;
	this->friction_coefficient = friction_coefficient;
}

unsigned Race::calculate_vehicle_score(Bolide bolide) {
	// All the fun
	double score = crude_score(bolide.max_velocity,
			           bolide.acceleration,
				   bolide.deceleration,
				   bolide.num_of_gears,
				   this->track_length);
	double stability = stability_index(bolide.num_of_gears,
			                   bolide.abs,
					   bolide.traction_control,
					   bolide.mass,
					   bolide.downforce,
					   this->track_length,
					   this->num_of_turns,
					   this->friction_coefficient);
	double correction = score - score*random(0.1, 10.0);
	return (unsigned) (score + correction*stability)/10000;
}

void Race::calculate_scores() {
	if (this->scores_calculated) return;
	for(std::vector<std::pair<Bolide, unsigned>>::iterator it =
			this->bolides.begin(); it != this->bolides.end(); ++it) {
		it->second = calculate_vehicle_score(it->first);
	}
	std::sort(this->bolides.begin(), this->bolides.end());
	this->scores_calculated = true;
}

void Race::add_bolide(Bolide bolide) {
	this->bolides.push_back(std::make_pair(bolide, 0));
}

void Race::print_stats() {
	calculate_scores();

	unsigned i = 1;
	for (std::vector<std::pair<Bolide, unsigned>>::reverse_iterator it =
			this->bolides.rbegin(); it != this->bolides.rend(); ++it) {
		std::cout << "[" << i++ << "] " << it->first.name << ": " << it->second << std::endl;
	}
}
