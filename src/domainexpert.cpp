/*
 * Implementation of DomainExpert helper class
 */

#include "domainexpert.h"
#include "jsonprinter.h"


void DomainExpert::print(JSONPrinter& printer, const SalesOrder& salesOrder)
{
	printer.printLineObject<Customer>("customer", salesOrder.customer_);
	printer.printLine<bool>("paid", salesOrder.paid_);

	// We are at the end of an object and don't want an ending comma at the last line, 
	// so set the parameter printEndingComma = false (default = true)
	printer.printList<SalesOrderLine>("lines", salesOrder.lines_, false);
}

void DomainExpert::print(JSONPrinter& printer, const Customer& customer)
{
	printer.printLineQuoted<string>("companyname", customer.companyName_);
	printer.printLineQuoted<string>("address", customer.address_);

	// We are at the end of an object and don't want an ending comma at the last line, 
	// so set the parameter printEndingComma = false (default = true)
	printer.printLineQuoted<string>("city", customer.city_, false);
}

void DomainExpert::print(JSONPrinter& printer, const SalesOrderLine& salesOrderLine)
{
	printer.printLineQuoted<string>("product", salesOrderLine.product_);
	printer.printLine<int>("amount", salesOrderLine.amount_);

	// We are at the end of an object and don't want an ending comma at the last line, 
	// so set the parameter printEndingComma = false (default = true)
	printer.printLine<float>("price", salesOrderLine.unitPrice_, false);
}
