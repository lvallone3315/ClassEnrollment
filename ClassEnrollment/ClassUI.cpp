// PlayerUI.cpp
//   Encapsulates the methods to read & write to the UI (for now, the console)

#include <iostream>
#include <stdlib.h>
#include "ClassUI.h"

// Player UI Class
//   Singleton class (for now) - uses console


// empty constructor
ClassUI::ClassUI() {

}

string ClassUI::getUserInput(string prompt) {
    string userInput;
    writeOutput(prompt);
    cin >> userInput;
    writeOutput(userInput);
    return userInput;
}

int ClassUI::writeOutput(string output) {
    cout << output;
    return(0);
}