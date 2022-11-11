// ClassUI.cpp
//   Encapsulates the methods to read & write to the UI (for now, the console)

#include <iostream>
#include <stdlib.h>
#include "ClassUI.h"

using namespace std;

/* Class UI Class
 * Scope:
 *   Handles all reads & writes to console (or in the future, a graphical window)
 *   Singleton class (for now) - uses console
 * 
 * Methods:
 *      getUserInput() writes prompt to console, blocks on user input (terminated by new line), returns input
 *      writeOutput()  writes output to console & returns 0 indicating no error, 
 *        in future write errors may contain an error code
 * 
 * Instance Variables:
 *   None
 */


// using default constructor - nothing to initialize


// getUserInput()
//   prompts user with string included in call
//   waits for user input, echoes the input & returns it to caller

string ClassUI::getUserInput(string const &prompt) {
    string userInput;

    writeOutput(prompt);
    getline(cin, userInput);
    return userInput;
}

// writeOutput()
//   writes passed string to console
int ClassUI::writeOutput(string const &output) {
    cout << output;
    return 0;
}