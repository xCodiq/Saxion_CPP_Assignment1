/**
 * C++ Foundations - SAXION 2022
 *
 * Project: Assignment 1
 * Datum: 16-02-2022
 * Door: Elmar Blume
 */

#include <iostream>
#include <string>
#include <fstream>

using std::cout, std::cin, std::endl, std::getline, std::ifstream, std::ofstream, std::string, std::isalpha, std::islower;

/**
 * The Letter structure represents one letter of the alphabet. It contains a character,
 * and frequency which will be swapped in sortLetterFrequency
 */
struct Letter {
    // The character of the alphabet
    char character;

    // The frequency of the character in the text file
    int frequency = 0;
};

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
 * Read every line from a file, and put the frequency
 * results in an letter structure in the letter array
 *
 * @param fileName the name of the file to open
 * @param letters the letter array to store the letter structures in
 */
void readLetters(const string &fileName, Letter letters[26]) {
    ifstream inputStream{fileName};

    for (string fileLine{}; getline(inputStream, fileLine);) {
        for (const char character: fileLine) {
            if (!isalpha(character)) continue;

            int index = tolower(character) - 'a';
            letters[index].character = tolower(character);
            letters[index].frequency++;
        }
    }
}

/**
 * Write the letter array to the specified output file
 *
 * @param fileName the name of the file to write to
 * @param letters the letter array to read it's frequencies from
 */
void writeLettersToOutputFile(const string &fileName, const Letter letters[26]) {
    ofstream outputStream{fileName};

    for (int i = 0; i < 26; ++i) {
        const Letter letter = letters[i];
        outputStream << letter.character << ": " << letter.frequency << endl;
    }
}

/**
 * Sort the letter array using BubbleSort, swapping values
 *
 * @param letters the letter array to sort
 */
void sortLetters(Letter letters[26]) {
    for (int floor = 0; floor < 26; ++floor) {
        for (int ceiling = floor + 1; ceiling < 26; ++ceiling) {
            // Store temporary values of floor to use later
            int temporaryFloorFrequency = letters[floor].frequency;
            char temporaryFloorCharacter = letters[floor].character;

            // Check if the ceiling frequency is greater than the floor frequency
            if (letters[floor].frequency < letters[ceiling].frequency) {
                letters[floor].frequency = letters[ceiling].frequency;
                letters[ceiling].frequency = temporaryFloorFrequency;

                letters[floor].character = letters[ceiling].character;
                letters[ceiling].character = temporaryFloorCharacter;
            }
        }
    }
}

/**
 * Print the whole letter array with it's character and frequency to the console
 *
 * @param letters the letter array to print it's values from
 */
void printLetters(const Letter letters[26]) {
    for (int i = 0; i < 26; i++) {
        Letter letter = letters[i];
        if (letter.frequency == 0) continue;

        cout << letter.character << ": " << letter.frequency << endl;
    }
}

int main() {
    // Declare a new integer array to store all the frequency data in
//    int letterFrequencyArray[26]{};
    Letter letters[26]{};

    // Prompt the user for an input file name
    string inputFileName = promptInputFileName();

    // Read the text file, and count every single character from the Alphabet
    readLetters(inputFileName, letters);

    // Sort the letter frequency array using Bubblesort
    sortLetters(letters);

    // Convert the input file name to a fitting output file name, and write the
    // sorted letter frequency array to the output stream
    string outputFileName = convertInputFileNameToOutputFileName(inputFileName);
    writeLettersToOutputFile(outputFileName, letters);

    // Print the whole letter frequency array to the console
    printLetters(letters);
    return 0;
}
