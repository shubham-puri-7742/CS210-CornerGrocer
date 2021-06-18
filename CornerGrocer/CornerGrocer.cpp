/*
* CornerGrocer.cpp : Driver program for the corner grocer program (Python + C++)
* Shubham Puri
* 13th June, 2021
*/

#include <Python.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <cmath>
#include <cctype>
#include <string>

#define PYFILENAME "CornerGrocerPython"
#define HISTOGRAMDATAFILE "frequency.dat"

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule(PYFILENAME);
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)PYFILENAME);
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
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)PYFILENAME);
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

void PrintHistogram() {
	// Borrowed snippet from an old friend in an old script - 'bool FileExists'
	ifstream f(HISTOGRAMDATAFILE); // Open in ifstream
	if (!f) { // If the file doesn't exist
		cout << "ERROR: HISTOGRAM INPUT DATA FILE MISSING. Expected " << HISTOGRAMDATAFILE << endl; // Error message
		return; // Terminate, basically (see main)
	}

	string name; // IMPORTANT: Currently works for one-word names of items.
	int quantity;

	while (f >> name >> quantity) {
		cout << setw(15) << std::left << name << " : ";
		for (int i = 0; i < quantity; ++i) {
			cout << '*'; // Currently, the histogram scales to * = 1
		}
		cout << endl;
	}

	cout << "\n(Scale: * = 1 item)" << endl;
}

/*
MENU:
1. List of purchases in a given day with the number of times each item was purchased
2. How many times a specific item was purchased in a given day
3. Text-based histogram of all items in a given day
4. Exit
*/

int main() {
	// CallProcedure("printsomething");
	// cout << callIntFunc("PrintMe", "House") << endl;
	// cout << callIntFunc("SquareValue", 2);

	char cont = 'n'; short choice;

	do {
		do {
			system("CLS");
			// Menu
			cout << "CORNER GROCER\n1. List purchases with quantities\n2. Query the quantity of a given item\n3. Print a histogram of items and quantities\n4. Exit\nENTER YOUR CHOICE: ";
			
			// Borrowed from AirgeadBanking
			cin.exceptions(ios_base::failbit); // We need the failbit exception to check if the user accidentally (maliciously?) enters non-numeric data
			try {
				cin >> choice;
			}
			catch (const ios_base::failure& e) { // Invalid (non-numeric) type error
				cout << "\nERROR: INVALID INPUT TYPE!\n";
				break;
			}

		} while (choice < 1 || choice > 4); // Input validation

		cout << endl;

		switch (choice) {
			case 1: {
				// The corresponding procedure displays a table of all items with the quantities purchased
				CallProcedure("FrequenciesOfItems");
				break;
			}
			case 2: {
				// Get the item name from the user
				string itemName;
				cout << "Enter the item to query (one-word name, case-sensitive): "; // Match from the label maybe. Case-sensitivity is a reasonable assumption as the input data doesn't mix upper and lower case entries.
				cin >> itemName;

				// Get the number of times that item was bought
				int result = callIntFunc("FrequencyOf", itemName);
				cout << itemName << " was/were purchased " << result << " times\n";
				break;
			}
			case 3: {
				CallProcedure("ExportFrequencyData"); // Export the data to a .dat
				PrintHistogram(); // Print a histogram based on the data
				break;
			}
			case 4: {
				break;
			}
		}

		if (choice != 4) {
			cout << "\nRun again? (Y/N): ";
			cin >> cont; // Lazy program alert: Technically, it's anything EXCEPT y (or Y) to quit :3
		}
	} while (tolower(cont) == 'y'); // tolower to accept both y and Y

	cout << "\nThank you for choosing CornerGrocer :)\n"; // Customer retention 101

	return 0;
}