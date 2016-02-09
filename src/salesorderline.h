/*
 * Sales order line is a dataholder for a single line of a sales order
 */

#pragma once

#include <string>

 // Forward declaration of DomainExpert such that it has access to private properties that need to be printed
class DomainExpert;


class SalesOrderLine
{
	friend DomainExpert;
public:
	SalesOrderLine(std::string product, int amount, float unitPrice)
		: product_(product), amount_(amount), unitPrice_(unitPrice)
	{	}

private:
	std::string product_;
	int amount_;
	float unitPrice_;
};

