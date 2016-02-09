/*
 * Domain expert class is an helper for the JSON Printer to print domain-specific objects to a standarized JSON output format
 *
 * The idea of this separation between JSON Printer and a DomainExpert is that you as programmer for your domain only
 * need to maintain the functions that describe how you want to print your objects. The printing of the JSON format
 * is done in a separate class that `hides' some of the JSON details.
 */

#pragma once

#include "customer.h"
#include "salesorderline.h"
#include "salesorder.h"

 /*
 * Forward declaration of a JSON Printer such that the DomainExpert knows which printer should be used
 */
class JSONPrinter;


class DomainExpert
{
public:
	/*
	* Print function to print a SalesOrder as JSON output
	*/
	static void print(JSONPrinter& printer, const SalesOrder& salesOrder);

	/*
	* Print function to print a SalesOrderLine as JSON output
	*/
	static void print(JSONPrinter& printer, const SalesOrderLine& salesOrderLine);

	/*
	* Print function to print a Customer as JSON output
	*/
	static void print(JSONPrinter& printer, const Customer& customer);
};
