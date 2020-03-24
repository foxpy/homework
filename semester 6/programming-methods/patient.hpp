#pragma once

#include <string>
#include <vector>
#include <utility>

#include "human.hpp"
#include "wallet.hpp"
#include "disease.hpp"

class Patient: public Human, public Wallet {
public:
	Patient(const std::string &name,
	        unsigned age);
	Patient(const std::string &name,
	        unsigned age,
	        const std::vector<Disease> &diseases);
	bool is_ill() const;
	std::pair<std::vector<Disease>::const_iterator, std::vector<Disease>::const_iterator> get_diseases() const;
	void pay(unsigned amount) override;
	void charge(unsigned amount) override;
	int money() const override;
private:
	std::vector<Disease> diseases;
	int _money;
};
