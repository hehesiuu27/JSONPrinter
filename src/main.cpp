/*
 *	Demo program for JSON Printer
*/

#include <iostream>
#include <fstream>
#include <string>

#include "jsonprinter.h"

#include "customer.h"
#include "salesorder.h"
#include "salesorderline.h"

using std::string;
using std::cout;



SalesOrder createSalesOrder()
{
	Customer customer("My Company", "Mainstreet 123", "Acity");
	SalesOrder order(customer);
	order.addLine(SalesOrderLine("Apples", 10, 0.49f));
	order.addLine(SalesOrderLine("Butter", 1, 0.99f));
	order.addLine(SalesOrderLine("Cheese", 1, 5.39f));
	order.addLine(SalesOrderLine("Eggs", 10, 1.69f));
	return order;
}

/*
* Example writing JSON output to file
*/
void writeJSONtoFile(const char* filename)
{
	// Open a file to write the output to it
	std::ofstream outputFile;
	outputFile.open(filename, std::ios::out);

	// Construct the JSON file printer.
	JSONPrinter printer(outputFile);

	// Create some 'meaning full' data
	SalesOrder order = createSalesOrder();
	
	// Send the data to the JSON Printer.
	printer.print(order);

	// Close the file after printing
	outputFile.close();

}

/*
* Example writing JSON standard output
*/
void writeJSONtoStdOut()
{
	// Construct the JSON cout printer.
	JSONPrinter printer(cout);

	// Create some 'meaning full' data
	SalesOrder order = createSalesOrder();

	// Send the data to the JSON Printer.
	printer.print(order);
}


int main(int argc, char **argv)
{
	// Example to write output to file (first command line argument or 'output.json')
	if (argc > 1)
		writeJSONtoFile(argv[1]);
	else
		writeJSONtoFile("output.json");


	// Example to write output to stdout
	writeJSONtoStdOut();

	return 0;
}
