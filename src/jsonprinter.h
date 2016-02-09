/*
 * JSON printer class can be used to print objects to a standardized JSON output format
 * 
 * In the constructor you can define to which output stream the JSON Printer should print its JSON output.
 * Further, the JSON printer supports printing of numerical-valued properties, string-valued properties and
 * if you implement the corresponding method in the DomainExpert class then the JSON Printer can also print
 * custom-valued properties.
 *
 * Printing of a single line can be done using:
 *     *) printLinePlain<float>("pi", 3.1415);
 *     *) printLineQuoted<string>("key", "string-value");
 *     *) printLineObject<MyClass>("class", myObject);
 *
 * A general list can be printed using:
 *     *) printList<int>("numbers", listOfIntegers);
 *
 * A general object can be printed using:
 *     *) print<MyClass>(myObject);
 *
 *
 *
 * Author: J. Snoeijer, February 2016
 */

#pragma once

#include <ostream>
#include <sstream>
#include <string>
#include <list>
#include <algorithm>

#include "domainexpert.h"

 /*
  * number of spaces that is used for the indentation
  */
#define INDENTATION_WIDTH 2

using std::string;
using std::stringstream;
using std::list;


class JSONPrinter
{
public:
	/*
	 * Constructor that takes an output stream to write the output
	 */
	JSONPrinter(std::ostream& output)
		: output_(output), indentationLevel_(0)
	{ }


	/*
	* Prints the content of a string stream to the output
	*/
	void printStringStream(const string& key, stringstream& stringStream, bool printEndingComma = true);

	/*
	* prints a key and the corresponding value to the output, templated for the value type
	*/
	template<typename ValueType>
	inline void printLine(string key, ValueType val, bool printEndingComma = true);

	/*
	* prints a key and the corresponding value to the output, templated for the value type
	* which is printed without quotes (")
	*/
	template<typename ValueType>
	inline void printLinePlain(string key, ValueType val, bool printEndingComma = true);

	/*
	* prints a key and the corresponding value to the output, templated for the value type
	* which is printed with quotes (")
	*/
	template<typename ValueType>
	inline void printLineQuoted(string key, ValueType val, bool printEndingComma = true);

	/*
	* prints a key and the corresponding value to the output, templated for the value type
	*/
	template<typename ValueType>
	inline void printLineObject(string key, ValueType val, bool printEndingComma = true);

	/*
	* prints an object to the output using the DomainExpert
	*/
	template<typename DomainSpecificType>
	inline void print(DomainSpecificType& object, bool printEndingComma = false);

	/*
	* prints a key and the list of all elements to the output, templated for the value type
	*/
	template<typename ValueType>
	void printList(string key, list<ValueType> vals, bool printEndingComma = true);

	/*
	 * Gets the underlying output stream
	 */
	inline std::ostream& outputStream()
	{
		return output_;
	}

protected:
	/*
	 * Output stream to write the generated JSON to
	 */
	std::ostream& output_;

private:
	/*
	 * Number of steps that the printer is indented
	 */
	unsigned int indentationLevel_;

	/*
	* Used to skip the printing of the next indentation if we print an object-valued property
	*/
	bool neglectIndentation_ = false;

	/*
	* prints the indentation for a new line
	*/
	void printIndentation();

	/*
	* Prints the header of an object (i.e. the bracket open and the increment of indentation)
	*/
	void printObjectHeader();

	/*
	* Prints the footer of an object (i.e. the bracket closed and the decrement of indentation)
	*/
	void printObjectFooter(bool printEndingComma);

	/************************************************
	 * Helper functions for printing single lines   *
	 ************************************************/
	void printEndLine(bool printEndingComma);

	/*
	* prints a key and the corresponding value to the output, templated for the value type
	* which is printed without quotes (") and without new line
	*/
	template<typename ValueType>
	inline void printLineSegment(string key, ValueType val);
};





/************************************************
* Implementation of templated functions         *
************************************************/
template<typename ValueType>
void JSONPrinter::printLine(string key, ValueType val, bool printEndingComma)
{
	printLinePlain(key, val, printEndingComma);
}

template<typename ValueType>
void JSONPrinter::printLinePlain(string key, ValueType val, bool printEndingComma)
{
	printLineSegment(key, val);
	printEndLine(printEndingComma);
}

template<typename ValueType>
void JSONPrinter::printLineQuoted(string key, ValueType val, bool printEndingComma)
{
	stringstream quotedValue;
	quotedValue << "\"" << val << "\"";
	string strValue = quotedValue.str();
	printLinePlain<string&>(key, strValue, printEndingComma);
}

template<typename ValueType>
void JSONPrinter::printLineObject(string key, ValueType val, bool printEndingComma)
{
	printIndentation();

	// print the line to the output file
	output_ << "\"" << key << "\": ";

	// neglect indentation because we want to have the opening bracket of an object-property
	// on the same line as the name of the object-valued property
	neglectIndentation_ = true;
	print(val, printEndingComma);
}

template<typename DomainSpecificType>
void JSONPrinter::print(DomainSpecificType& object, bool printEndingComma)
{
	// Print begin bracket of object
	printObjectHeader();

	// Sends the object to the DomainExpert such that he prints this domain specific object
	DomainExpert::print(*this, object);

	// Print end bracket of object
	printObjectFooter(printEndingComma);
}

template<typename ValueType>
void JSONPrinter::printList(string key, list<ValueType> vals, bool printEndingComma)
{
	if (vals.size() > 0)
	{
		// Print the opening bracket of the list
		printLine<char>(key, '[', false);
		++indentationLevel_;

		// Print first to one before last element ending with a comma
		typename std::list<ValueType>::iterator lastElement = prev(vals.end());
		for_each(vals.begin(), lastElement, [this](ValueType val) { print(val, true); });

		// Print the last element without an ending comma
		print(*lastElement, false);

		// Print the closing bracket of the list
		--indentationLevel_;
		printIndentation();
		output_ << "]";
		printEndLine(printEndingComma);
	}
	else
		// Print empty list
		printLine<string>(key, "[]", printEndingComma);
}

template<typename ValueType>
void JSONPrinter::printLineSegment(string key, ValueType val)
{
	printIndentation();

	// print the line to the output file
	output_ << "\"" << key << "\": " << val;
}