#pragma once
#include <vector>
#include <string>
#include "human.hpp"
#include "disease.hpp"
#include "wallet.hpp"

class Doctor: public Human, public Wallet {
public:
	Doctor(const std::string &name,
	       unsigned age,
	       const std::vector<Disease> &cures);
	bool can_cure(Disease disease) const;
	void pay(unsigned amount) override;
	void charge(unsigned amount) override;
	int money() const override;
	void print_info() const override;
private:
	std::vector<Disease> cures;
	int _money;
};
