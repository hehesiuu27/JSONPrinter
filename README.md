# JSONPrinter for C++
Just a Simple Object-oriented Natural (JSON) Printer for C++

##Introduction
JSONPrinter provides a basic infrastructure to easily generate JSON output in your C++ projects. It is intended to be a *Simple*, *Object oriented* and *Natural* library for generating JSON output.
The JSONPrinter is capable to print *text valued*, *numerical valued* and custom defined *object-valued* properties. Along this basic structures the JSONPrinter provides also functionality to print *complex structures* like *lists of a generic type*.


Here is an example showing how to use the `JSONPrinter` with your own C++ classes (e.g. a `SalesOrder`):

```C++
/*
 * Example writing JSON standard output
 */
void writeJSONtoStdOut()
{
	// Construct the JSON cout printer.
	JSONPrinter printer(cout);

	// Get an object representing a Sales order
	SalesOrder order = createSalesOrder();

	// Send the data to the JSON Printer.
	printer.print(order);
}

```

In the constructor you can define to which output stream the JSONPrinter should print its JSON output. All objects implementing the C++ `std::ostream` are supported, so for example standard output and writing data to a textfile.

##Setting up the DomainExpert
Of course, someone need to define how the objects of your domain are mapped to properties that are printed in the JSON output. Therefore, we have a `DomainExpert` who knows how to generate a sequence of instructions for the JSONPrinter based on an object.

Here is an example showing how the DomainExpert controls the JSONPrinter and declares which properties are printed with which values:

```C++
/*
 * Print function to print a SalesOrder as JSON output
 */
void DomainExpert::print(JSONPrinter& printer, const SalesOrder& salesOrder)
{
	printer.printLineObject<Customer>("customer", salesOrder.customer_);
	printer.printLine<bool>("paid", salesOrder.paid_);

	// We are at the end of an object and don't want an ending comma at the last line, 
	// so set the parameter printEndingComma = false (default = true)
	printer.printList<SalesOrderLine>("lines", salesOrder.lines_, false);
}

```

###JSONPrinter out-of-the-box support
The JSONPrinter has out of the box support for
* Printing lines with *plain numbers*:
```C++
printLinePlain<float>("pi", 3.1415);
```

* Printing lines with *string with quotes*:
```C++
printLineQuoted<string>("key", "string-value");
```

* Printing lines with *own defined objects*:
```C++
MyClass myObject;
printLineObject<MyClass>("class", myObject);
```

* Printing *general lists*:
```C++
std::list<int> listOfIntegers { 1, 2, 3, 4 };
printList<int>("numbers", listOfIntegers);
```

* Printing *general object*:
```C++
MyClass myObject;
print<MyClass>(myObject);
```

### Printing your own objects
To be able to print objects of a cumstom class `MyClass` the DomainExpert need to be extended with the following function:
```C++
static void print(JSONPrinter& printer, const MyClass& myObject);
```
where `myObject` is the instance of `MyClass` that need to be printed to JSONPrinter `printer`.


##Final remarks
JSON is a common format to exchange data between programs and projects. So, a good and easy JSON printing library makes life a lot easier. Therefore, JSONPrinter aims to be Just a Simple Object-oriented Natural JSON Printer for C++.

In this repository you will find an worked out example for a `SalesOrder` scenario, but the `JSONPrinter` files and your customized `DomainExpert` should be sufficient in all other projects.

If you found a bug, have feature requests, pull requests, or other feedback, feel free to [create an issue](https://github.com/jsnoeijer/JSONPrinter/issues/new).
