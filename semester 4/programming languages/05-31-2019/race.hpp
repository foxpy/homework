#include <string>
#include <vector>
#include <utility>

struct Bolide {
	std::string name;
	double max_velocity; // kmph
	double acceleration; // ms-2
	double deceleration; // ms-2
	unsigned num_of_gears;
	bool abs;
	bool traction_control;
	double mass; // kg
	double downforce; // g

	Bolide(std::string name,
	       double max_velocity,
	       double acceleration,
	       double deceleration,
	       unsigned num_of_gears,
	       bool abs,
	       bool traction_control,
	       double mass,
	       double downforce);
};

class Race {
	private:
		// pair<vehicle, score>
		std::vector<std::pair<Bolide, unsigned>> bolides;

		double track_length; // m
		unsigned num_of_turns;
		double friction_coefficient;
		bool scores_calculated = false;

		unsigned calculate_vehicle_score(Bolide);
		void calculate_scores();

	public:
		void add_bolide(Bolide bolide);
		void print_stats();

	Race(double track_length,
	     unsigned num_of_turns,
	     double friction_coefficient);
};
