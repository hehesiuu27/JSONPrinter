/*
 * Customer is a dataholder for some dummy data for a company
 */

#pragma once

#include <string>

// Forward declaration of DomainExpert such that it has access to private properties that need to be printed
class DomainExpert;

class Customer
{
	friend DomainExpert;
public:
	Customer(std::string companyName, std::string address, std::string city)
		: companyName_(companyName), address_(address), city_(city)
	{	}

private:
	std::string companyName_;
	std::string address_;
	std::string city_;
};

