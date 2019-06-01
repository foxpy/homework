double random(double low, double high);
double crude_score(double max_velocity,
		   double acceleration,
		   double deceleration,
		   unsigned num_of_gears,
		   double track_length);
double stability_index(unsigned num_of_gears,
		       bool abs,
		       bool traction_control,
		       double mass,
		       double downforce,
		       double track_length,
		       unsigned num_of_turns,
		       double friction_coefficient);
