#include <utility>
#include <random>

double random(double low, double high) {
	if (low < high) {
		std::swap(low, high);
	}
	static std::random_device rdrand;
	std::uniform_real_distribution<double> distr(low, high);
	return distr(rdrand);
}

double crude_score(double max_velocity,
		   double acceleration,
		   double deceleration,
		   unsigned num_of_gears,
		   double track_length) {
	double score = max_velocity*acceleration*deceleration;
	score /= num_of_gears; // more gears -> less max speed
	score *= track_length;
	return score;
}

double stability_index(unsigned num_of_gears,
		       bool abs,
		       bool traction_control,
		       double mass,
		       double downforce,
		       double track_length,
		       unsigned num_of_turns,
		       double friction_coefficient) {
	double turns_frequency = (num_of_turns) ? (track_length/num_of_turns) : 1;
	double stability = num_of_gears * downforce * friction_coefficient / (mass / 1000);
	if (!abs) turns_frequency *= 3; // no abs -> harder to turn
	if (!traction_control) turns_frequency *= 2; // the same as above
	return stability / turns_frequency;
}
