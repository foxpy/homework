#pragma once
#include <vector>
#include <string>
#include "human.hpp"
#include "disease.hpp"
#include "wallet.hpp"

class Patient: public Human, public Wallet {
public:
	Patient(const std::string &name,
	        unsigned age,
	        const std::vector<Disease> &diseases);
	bool is_ill() const;
	Disease needs_cure_of() const;
	void cure_from(Disease disease);
	void pay(unsigned amount) override;
	void charge(unsigned amount) override;
	int money() const override;
	void print_info() const override;
private:
	std::vector<Disease> diseases;
	int _money;
};
