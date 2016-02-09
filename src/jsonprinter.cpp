/*
 * Implementation of JSON printer class
 */

#include "jsonprinter.h"

using std::endl;

 /************************************************
 * Public methods for JSON printer               *
 ************************************************/

void JSONPrinter::printStringStream(const string& key, stringstream& stringStream, bool printEndingComma)
{
	// Print opening bracket for an object
	printIndentation();
	output_ << "\"" << key << "\": {" << endl;
	++indentationLevel_;

	string line;

	while (std::getline(stringStream, line))
	{
		printIndentation();
		output_ << line << endl;
	}

	// Print end bracket of object
	printObjectFooter(printEndingComma);
}





/************************************************
 * Helper functions for printing single lines   *
 ************************************************/
void JSONPrinter::printIndentation()
{
	if (neglectIndentation_)
		neglectIndentation_ = false;
	else
	{
		// set correct indentation level
		output_ << string(indentationLevel_ * INDENTATION_WIDTH, ' ');
	}
}

void JSONPrinter::printEndLine(bool printEndingComma)
{
	if (printEndingComma)
		output_ << ",";
	output_ << endl;
}

void JSONPrinter::printObjectHeader()
{
	printIndentation();
	output_ << "{" << endl;
	++indentationLevel_;
}

void JSONPrinter::printObjectFooter(bool printEndingComma)
{
	--indentationLevel_;
	printIndentation();
	output_ << "}";
	printEndLine(printEndingComma);
}
