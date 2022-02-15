/**
 * C++ Foundations - SAXION 2022
 *
 * Project: Assignment 1
 * Datum: 14-02-2022
 * Door: Elmar Blume
 */

#include <iostream>
#include <string>
#include <fstream>

using std::cout, std::cin, std::endl, std::getline, std::ifstream, std::ofstream, std::string, std::isalpha, std::islower;

/**
 * Prompt the user for a file name which will be used
 * as the name for the input stream
 *
 * @return the name of the input file
 */
string promptInputFileName() {
    string fileName{};
    cout << "Please enter a file name. Empty file name quits the program." << endl << "File name:";
    getline(cin, fileName);

    // Check if the input failed
    if (cin.fail()) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        cout << "You did not specify the right data type!" << endl;
        return promptInputFileName();
    }

    return fileName;
}

/**
 * Convert an input file name to an output file name
 *
 * Example:
 * alice.txt -> alice.out
 */
string convertInputFileNameToOutputFileName(const string &fileName) {
    auto position = fileName.find('.');
    if (position == string::npos) return fileName + ".out";

    return fileName.substr(0, position) + ".out";
}

/**
 * Read every line from a file, and put the frequency results in an array
 *
 * @param fileName the name of the file to open
 * @param letterFrequencyArray the integer array to store the values in
 */
void readLetterFrequency(const string &fileName, int letterFrequencyArray[26]) {
    ifstream inputStream{fileName};

    for (string fileLine{}; getline(inputStream, fileLine);) {
        for (const char character: fileLine) {
            if (!isalpha(character)) continue;

            int index = tolower(character) - 'a';
            letterFrequencyArray[index]++;
        }
    }
}

/**
 * Write the letter frequency array to the specified output file
 *
 * @param fileName the name of the file to write to
 * @param letterFrequencyArray the integer array to read it's values from
 */
void writeLetterFrequencyToOutputFile(const string &fileName, const int letterFrequencyArray[26]) {
    ofstream outputStream{fileName};

    for (int i = 0; i < 26; ++i) {
        int letterFrequency = letterFrequencyArray[i];
        outputStream << static_cast<char>(i + 'a') << ": " << letterFrequency << "x" << endl;
    }
}

/**
 * Sort the letter frequency array using BubbleSort, swapping values
 *
 * @param letterFrequencyArray the integer array to sort
 */
void sortLetterFrequencyArray(int letterFrequencyArray[26]) {
    for (int floor = 0; floor < 26; ++floor) {
        for (int ceiling = floor + 1; ceiling < 26; ++ceiling) {
            int temporaryFloor = letterFrequencyArray[floor];
            if (letterFrequencyArray[floor] < letterFrequencyArray[ceiling]) {
                letterFrequencyArray[floor] = letterFrequencyArray[ceiling];
                letterFrequencyArray[ceiling] = temporaryFloor;
            }
        }
    }
}

/**
 * Print the whole letter frequency array with it's character to the console
 *
 * @param letterFrequencyArray the integer array to prints it's value from
 */
void printLetterFrequencyArray(const int letterFrequencyArray[26]) {
    for (int i = 0; i < 26; i++) {
        int letterFrequency = letterFrequencyArray[i];
        cout << static_cast<char>(i + 'a') << ": " << letterFrequency << endl;
    }
}

int main() {
    // Declare a new integer array to store all the frequency data in
    int letterFrequencyArray[26]{};

    // Prompt the user for an input file name
    string inputFileName = promptInputFileName();

    // Read the text file, and count every single character from the Alphabet
    readLetterFrequency(inputFileName, letterFrequencyArray);

    // Sort the letter frequency array using Bubblesort
    sortLetterFrequencyArray(letterFrequencyArray);

    // Convert the input file name to a fitting output file name, and write the
    // sorted letter frequency array to the output stream
    string outputFileName = convertInputFileNameToOutputFileName(inputFileName);
    writeLetterFrequencyToOutputFile(outputFileName, letterFrequencyArray);

    // Print the whole letter frequency array to the console
    printLetterFrequencyArray(letterFrequencyArray);
    return 0;
}
