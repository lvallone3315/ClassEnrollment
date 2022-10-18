// ClassUI.cpp
//   Encapsulates the methods to read & write to the UI (for now, the console)

#include <iostream>
#include <stdlib.h>
#include "ClassUI.h"

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


// empty constructor
ClassUI::ClassUI() {

}


// getUserInput()
//   prompts user with string included in call
//   waits for user input, echoes the input & returns it to caller

string ClassUI::getUserInput(string prompt) {
    string userInput;

    writeOutput(prompt);
    cin >> userInput;
    writeOutput(userInput+"\n");
    return userInput;
}

// writeOutput()
//   writes passed string to console
int ClassUI::writeOutput(string output) {
    cout << output;
    return(0);
}