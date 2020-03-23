#pragma once

#include <string>
#include <vector>

#include "human.hpp"
#include "wallet.hpp"
#include "disease.hpp"

class Doctor: public Human, public Wallet {
public:
	Doctor(const std::string &name = "Carl",
	       unsigned age = 42);
	Doctor(const std::string &name,
	       unsigned age,
	       const std::vector<Disease> &cures);
	bool can_cure(Disease disease) const;
	void pay(unsigned amount) override;
	void charge(unsigned amount) override;
private:
	std::vector<Disease> cures;
	int money;
};
