/**
 * Eric Slutz
 * CS-210
 * Project 3
 *
 * Main Method
 */

#include <fstream>
#include <iostream>
#include <Python.h>
#include <sstream>
#include <vector>

#include "InventoryItem.h"
#include "Utilities.h"

using namespace std;

/**
 * Pass the name of the Python function you wish to call and the two string parameters you want to send.
 *
 * @param proc Python function name.
 * @param param1 First string parameter for the Python function.
 * @param param2 Second string parameter for the Python function.
 */
void callFunc(const string& proc, const string& param1, const string& param2)
{
	char *procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char *paramval1 = new char[param1.length() + 1];
	std::strcpy(paramval1, param1.c_str());

	char *paramval2 = new char[param2.length() + 1];
	std::strcpy(paramval2, param2.c_str());


	PyObject *pName, *pModule, *pDict, *pFunc, *pValue = nullptr, *presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(s, s)", paramval1, paramval2);
		PyErr_Print();
		PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}

	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean
	delete[] procname;
	delete[] paramval1;
	delete[] paramval2;
}


/**
 * Pass the name of the Python function you wish to call and the string parameter you want to send.
 *
 * @param proc Python function name.
 * @param param1 String parameter for the Python function.
 */
void callFunc(const string& proc, const string& param)
{
	char *procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char *paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject *pName, *pModule, *pDict, *pFunc, *pValue = nullptr, *presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}

	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean
	delete[] procname;
	delete[] paramval;
}

/**
 * Pass the name of the Python function you wish to call and the two string parameters you want to send.
 *
 * @param proc Python function name.
 * @param param1 First string parameter for the Python function.
 * @param param2 Second string parameter for the Python function.
 * @return Integer value from the Python function.
 */
int callIntFunc(const string& proc, const string& param1, const string& param2)
{
	char *procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char *paramval1 = new char[param1.length() + 1];
	std::strcpy(paramval1, param1.c_str());

	char *paramval2 = new char[param2.length() + 1];
	std::strcpy(paramval2, param2.c_str());


	PyObject *pName, *pModule, *pDict, *pFunc, *pValue = nullptr, *presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(s, s)", paramval1, paramval2);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	// printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean
	delete[] procname;
	delete[] paramval1;
	delete[] paramval2;

	return _PyLong_AsInt(presult);
}

/**
 * Reads in file and creates a histogram to display.
 *
 * @param input_file name and location of file with the data to display.
 * @return string of the histogram to display.
 */
string displayFrequencyHistogram(const string& input_file) {
	// Declare file stream variable and open the file.
	ifstream inputFileStream;
	inputFileStream.open(input_file);

	if (!inputFileStream.is_open()) {
		return "Unable to open " + input_file + "\n";
	}

	// Declare list to store inventory items read in from file.
	vector<InventoryItem> inventoryList;
	// Declare variables to temporarily store item values before adding to list.
	string item_name;
	int item_qty;
	// Loop until the end of the file is reached.
	while (!inputFileStream.eof()) {
		// Read in the items name.
		inputFileStream >> item_name;
		// Read in the quantity sold for the item.
		inputFileStream >> item_qty;
		if (!inputFileStream.fail()) {
			// Create new inventory item from the read in values.
			InventoryItem item = InventoryItem(item_name, item_qty);
			// Add the new item to the inventory list.
			inventoryList.push_back(item);
		}
	}
	// Close the file.
	inputFileStream.close();

	// Get max width for item name and max value for item quantity.
	// Loop through the inventory list.
	int maxNameWidth = 0, maxQty = 0;
	for(InventoryItem item : inventoryList) {
		// If name width greater than current max, set max to current name width.
		if(size(item.getName()) > maxNameWidth) {
			maxNameWidth = static_cast<int>(size(item.getName()));
		}
		// If quantity greater than current max, set max to current quantity.
		if(item.getQty() > maxQty) {
			maxQty = item.getQty();
		}
	}
	// Add a little spacing to the max value.
	maxQty += 2;

	// Constants storing the desired histogram width and header.
	const string HISTOGRAM_HEADER = "items purchased";
	const int HISTOGRAM_CHART_WIDTH = (maxNameWidth + maxQty + 6) > size(HISTOGRAM_HEADER) ?
			maxNameWidth + maxQty + 6 :
			static_cast<int>(size(HISTOGRAM_HEADER));

	// Variable for storing the frequency histogram.
	stringstream histogramStream;
	// Add header for the frequency histogram.
	histogramStream << Utilities::generateHeader(HISTOGRAM_HEADER, HISTOGRAM_CHART_WIDTH);
	// Loop through the inventory list.
	for(InventoryItem item : inventoryList) {
		histogramStream << item.getName();
		histogramStream << Utilities::repeatingChar(' ',
													maxNameWidth - static_cast<int>(size(item.getName())));
		histogramStream << " || ";
		histogramStream << Utilities::repeatingChar('*', item.getQty());
		histogramStream << endl;
	}
	// Determines width of histogram end line.
	// If the width is less that the header value, then set new header width.
	int endLineWidth = HISTOGRAM_CHART_WIDTH < size(HISTOGRAM_HEADER) + 2 ?
			HISTOGRAM_CHART_WIDTH + 4 :
			HISTOGRAM_CHART_WIDTH;
	histogramStream << Utilities::repeatingChar('=', endLineWidth) << endl;

	// Return the string of the histogram.
	return histogramStream.str();
}

 /**
  * Gets the menu as a string to display.
  *
  * @param menuInputError input error message to display, if there is one.
  * @return string of the menu content.
  */
string displayMenu(const string& menuInputError) {
	// Constants storing the desired menu width and header.
	const int MENU_WIDTH = 56;
	const string MENU_HEADER = "welcome to corner grocer inventory tracker";
	// Variable for storing the menu.
	stringstream menuStream;

	// Add the menu options to the stream.
	menuStream << Utilities::generateHeader(MENU_HEADER, MENU_WIDTH, menuInputError);
	menuStream << "1: Display Items Purchased w/ Quantity" << endl;
	menuStream << "2: Display Number of Times Item Purchased" << endl;
	menuStream << "3: Display Histogram Listing of Items Purchased" << endl;
	menuStream << "4: Exit" << endl;
	menuStream << Utilities::repeatingChar('=', MENU_WIDTH) << endl;

	// Return the menu string.
	return menuStream.str();
}

/**
 * Displays menu and gets the user's selection.
 *
 * @return integer value representing the users menu selection.
 */
unsigned int getMenuSelection() {
	// Declares variables for storing the users input and the users validated selection.
	string userInput;
	int menuSelection = 0;
	bool validMenuSelection = true;
	ostringstream invalidInputString;

	// Loops until the user makes a valid menu selection.
	do {
		Utilities::clearScreen();
		if (!validMenuSelection) {
			invalidInputString << "Not a valid menu option, please try again ";
		}
		// Display the bank menu.
		cout << displayMenu(invalidInputString.str());
		// Gets the users input.
		cout << "=> ";
		cin >> userInput;

		// Validates the user's selection is of the valid type and within the menu option range.
		validMenuSelection = Utilities::validateIntegerInput(userInput, menuSelection)
							 && (menuSelection > 0 && menuSelection < 5);
		// Resets the invalid input string.
		invalidInputString.str("");
	} while (!validMenuSelection);

	// Return the users validated menu selection.
	return menuSelection;
}

int main() {
	// Constants for needed file names and locations.
	const string INPUT_FILE = "../CS210_Project_Three_Input_File.txt";
	const string FREQUENCY_FILE = "../frequency.dat";
	// Variable for current run state of the program.
	bool quitProgram = false;

	// Loop until the user quits the program.
	while (!quitProgram) {
		// Call the Python function to create list of quantity of each item sold.
		callFunc("get_inventory",INPUT_FILE, FREQUENCY_FILE);

		// Display the menu and get the user's menu selection.
		unsigned int menuSelection = getMenuSelection();

		// Declare variables needed for setting values in switch statement.
		string itemName;
		int itemQty;
		// Based on user's selection, execute the correct case.
		switch (menuSelection) {
			// Call the Python function to display item list and quantities.
			case 1:
				Utilities::clearScreen();
				cout << Utilities::generateHeader("item and quantities sold today", 40);
				// Uses the Python function to display the list of items sold and the quantity sold for each.
				callFunc("display_inventory", FREQUENCY_FILE);
				cout << Utilities::repeatingChar('=', 40) << endl;
				break;
			// Pass item to search to Python function and return quantity for that item.
			case 2:
				Utilities::clearScreen();
				// Gets the item the user wants to search for.
				cout << "Enter the item you would like to get the quantity for." << endl;
				cout << "=> ";
				cin >> itemName;
				// Calls the Python function to get quantity sold of the requested item.
				itemQty = callIntFunc("get_item_qty", FREQUENCY_FILE, itemName);
				// Displays the item and the quantity sold.
				cout << "Item: " << itemName << endl;
				cout << "Quantity: "<< itemQty << endl;
				break;
			// Read from inventory list file and display histogram.
			case 3:
				Utilities::clearScreen();
				// Display the frequency histogram.
				cout << displayFrequencyHistogram(FREQUENCY_FILE);
				break;
			// Exit
			case 4:
				quitProgram = Utilities::confirmation("Are you sure you want to quit?");
				continue;
			// Unexpected input, start over.
			default:
				cout << "Invalid selection, try again." << endl;
				continue;
		}
		// Pause until the user chooses to continue.
		Utilities::pauseUntilEnter();
	}
	// Display goodbye message.
	cout << endl << "Goodbye!" << endl;

	return 0;
}
