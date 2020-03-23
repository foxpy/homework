#pragma once

#include <string>
#include <vector>

#include "human.hpp"
#include "wallet.hpp"
#include "disease.hpp"

class Patient: public Human, public Wallet {
public:
	Patient(const std::string &name = "Alex",
	        unsigned age = 42);
	Patient(const std::string &name,
	        unsigned age,
	        const std::vector<Disease> &diseases);
	bool is_ill() const;
	void pay(unsigned amount) override;
	void charge(unsigned amount) override;
private:
	std::vector<Disease> diseases;
	int money;
};
