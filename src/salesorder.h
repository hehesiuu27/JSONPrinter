/*
 * Sales order is a dataholder for a demo sales order
 */

#pragma once

#include <list>
#include "customer.h"
#include "salesorderline.h"

 // Forward declaration of DomainExpert such that it has access to private properties that need to be printed
class DomainExpert;

class SalesOrder
{
	friend DomainExpert;
public:
	SalesOrder(Customer customer)
		: customer_(customer), paid_(true)
	{ }

	void addLine(SalesOrderLine line)
	{
		lines_.push_back(line);
	}

private:
	Customer customer_;
	std::list<SalesOrderLine> lines_;
	bool paid_;
};

