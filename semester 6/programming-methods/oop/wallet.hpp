#pragma once
class Wallet {
public:
	virtual void pay(unsigned amount) = 0;
	virtual void charge(unsigned money) = 0;
	virtual int money() const = 0;
};
