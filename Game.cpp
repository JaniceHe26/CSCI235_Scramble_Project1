//
//
/* THIS PROGRAM WILL CREATE A WORD JUMBLE GAME THAT SCRAMBLE WORD FOR USER TO GUESS IN ORDER TO PASS ON TO THE
    NEXT LEVEL.
*/


#include <iostream>

#include "Game.h"
//ALL INCLUDE HEADERS NEEDED TO RUN THIS PROGRAM IS IN OUR Game.h FILE.

using namespace std;

//This function will run the game by taking in a text file and see if it is valid or not
//Precondition: User must enter a correct file path as well file cannot be empty and have the right amount of word.
void Game::run(string filePath) {
    gameRunning = true;
    vector<string> loadGameValues;
    bool fileExist = false;
    if (filePath.empty()) {
        loadGameValues = loadGame();
    } else {
        fileExist = createLibrary(filePath);
        while (!fileExist) {  //While loop will keep going until user enter a correct file.
            cout << "File does not exist. Please enter a new file path: ";
            cin >> filePath;
            fileExist = createLibrary(filePath);
        }
    }
/*Postcondition: Returns nothing. The function takes in file path if invalid, then ask user to give the correct file path
 * until the right file path is given*/




//Explains the game/rules to player.
    cout << "\n\n";
    cout << "You must unscramble the jumbled word given to pass on the next level." << endl;
    cout << "You will have three tries for each level." << endl;
    cout << "You may have an option to use a Life Line once if you are stuck on a word." << endl;
    cout << "Good luck!" << endl;
    cout << "\n\n";
//End of explaining the rules of the game.


//Global var of the of the program to keep score/status etc.
    int level = 1;
    int score = 0;
    int lifeLineRem = 5;
    int numGuessRem = 3;
    int currentLength = 3;
    string currentWord;
    string jumbledWord;
    string guessedWord; //This will be a word entered by user to use and compared to current word.
    int stage = 1;
//These variables will help us with saving game:

    int maxLevel;
    int numWordCorrect = 0;
    string longestWord;

    //check if there is a saved game.
    if (loadGameValues.size() == 11) {
        level = stoi(loadGameValues[0]);
        score = stoi(loadGameValues[1]);
        lifeLineRem = stoi(loadGameValues[2]);
        currentLength = stoi(loadGameValues[3]);
        currentWord = loadGameValues[4];
        jumbledWord = loadGameValues[5];
        stage = stoi(loadGameValues[6]);
        numGuessRem = stoi(loadGameValues[7]);
        numWordCorrect = stoi(loadGameValues[8]);
        longestWord = loadGameValues[9];
        filePath = loadGameValues[10];
        fileExist = createLibrary(filePath);
        if (!fileExist) {
            cout << "\nSaved library failed to load.\n";
            return;
        }
        //In case file deleted by user or corrupted/lost.

        while (getWord(currentLength) != currentWord);
    } else {
        currentWord = getWord(currentLength);
        cout << currentWord << endl;
        jumbledWord = jumble(currentWord);
    }

    //While the game is running each time this will be displayed to the user.
    while (gameRunning) {
        cout << "\n\n";
        cout << "WORD JUMBLE BEGIN:" << endl;
        cout << "------------------------------------------------------------------------------------------------------"
             << endl;
        cout << "Current Level:\t" << level << endl;//(put in keeping track of level function here)
        cout << "Stage:\t(" << stage << "/3)" << endl;
        cout << "Score:\t" << score << endl;//(put in keeping track of score function here)
        cout << "LifeLine Remaining:\t" << lifeLineRem << endl;//(Lifeline remaining function inside here)
        cout << "------------------------------------------------------------------------------------------------------"
             << endl;
        cout << "\n\n";
        cout << "Number of guesses remaining:\t" << numGuessRem << endl; //NumberofTries in here
        cout << "Your word to unscramble:\t" << jumbledWord << endl;//put in the displayWord function here //cin>>
        cout << "Please enter the word:\t";

        //User will enter their guess word here:
        cin >> guessedWord;

        //If user gets the word correct every var will updated keeping score.
        if (currentWord == guessedWord) {
            cout << "Correct!" << endl;
            cout << "\n\n";
            numWordCorrect++;
            longestWord = currentWord;
            stage++;

            if (stage > 3) { //Go on to next stage
                stage = 1;
                if(currentLength == maxLength){ //last update to final print of status.
                    maxLevel = level;
                    score = score +15; //+10 for each level, +5 for each word right therefore +15
                    break;

                }
                level++;
                score = score + 10;
                currentLength++;
                while (library.count(currentLength) == 0 && currentLength <= maxLength) {
                    currentLength++; //Keep going on until it reach to the max key
                }
            }
            score = score + 5;
            currentWord = getWord(currentLength);
            jumbledWord = jumble(currentWord);
            numGuessRem = 3;
            saveGame(level, score, lifeLineRem, currentLength, currentWord, jumbledWord, stage, numGuessRem, numWordCorrect, longestWord, filePath);

        } else {
            cout << "Incorrect!" << endl;
            numGuessRem--;

            if (numGuessRem == 0) {
                if (lifeLineRem > 0) {
                    string response;
                    cout << "You ran out of chances to guess for this word. If you do not use a lifeline you will lose."
                         << endl;
                    cout << "Would you like to use a life line?\t" "'Y' or 'y' for Yes and 'N' or 'n' for No" << endl;
                    cin >> response;
                    while (!(response == "y" || response == "Y" ||
                             response == "n" || response == "N")) {
                        cout << "Invalid Entry! Please enter either Y or y "
                             << "for using a lifeline or N or n for not using a life line."
                             << endl;
                        cin >> response;
                    }

                    if (response == "Y" || response == "y") {
                        lifeLineRem--;
                        numGuessRem = 3;
                        currentWord = getWord(currentLength);
                        jumbledWord = jumble(currentWord);
                    } else if (response == "N" || response == "n") {
                        cout << "You chose to not use a life line. You lost." << endl;
                        gameRunning = false;
                        //Game is over
                    }
                } else {
                    cout << "Sorry you do not have any life line left. You lost."
                         << endl; //maybe put this in the first statement
                    gameRunning = false;
                    //Game is over
                }
            }
            saveGame(level, score, lifeLineRem, currentLength, currentWord, jumbledWord,
                     stage, numGuessRem, numWordCorrect, longestWord, filePath);
        }

        cout << "\n\n";
    }

    cout << "STATUS:\t" << endl;
    cout << "------------------------------------------------------------------------------------------------------"
         << endl;
    cout << "Max Level Reached:\t" << maxLevel << endl;
    cout << "Number of Word Guessed:\t" << numWordCorrect <<endl;
    cout << "Highest Level:\t" << level <<endl;
    cout << "Longest Word Guessed:\t" << longestWord <<endl;
    cout << "------------------------------------------------------------------------------------------------------"
         << endl;
    cout<<"Game is over."<<endl;
}


//Precondition: Must have have a valid file path.
// This function creates a library to store in the word. Takes in good file path reads in and store word into var word.
bool Game::createLibrary(string filePath) {
    ifstream file;
    try {
        file.open(filePath);
        if (file.good()) {
            while (!file.eof()) {
                string word;
                file >> word;
                word = wordConformance(word);
                storeWord(word);
            }
            file.close();
        } else {
            return false;
        }
    } catch (const ifstream::failure &e) {
        return false;
    }

    return true;
}
//Postcondition: This function will store all the conformed word into library.



//Precondition: Need Words
//This function takes all upper cases and transform all characters into lower case. Using the #include <algorithm>
//This function goes through word from beginning till ends removes punctuation.
string Game::wordConformance(string word) {
    string result;
    remove_copy_if(word.begin(), word.end(),
                   back_inserter(result), //Store output
                   ptr_fun<int, int>(ispunct)
    );
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}
//Postcondition: Function removes all punctuations and change upper to lower case and store it.


//Precondition: Words from file.
//This Function will store the word from file into a map of length and word. Also, check to see if word is existing.
//Check words exist by the key(if length is unique). If key exist, look through the element of vector to see if word exist.
//If exist push word onto vector
//Creates a new  vector if key does not exist.
void Game::storeWord(string word) {
    auto length = (int) word.length();
    if (length > maxLength) {
        maxLength = length;
    }
    if (library.count(length) == 1) {
        if (find(library[length].begin(), library[length].end(), word) ==
            library[length].end()) {
            library[length].push_back(word);
        }
    } else {
        vector<string> tempVect;
        tempVect.push_back(word);
        library[length] = tempVect;
    }
}
//Postcondtion: A map is created to store word.



//Precondition: A map
//This Function will get word from. 
string Game::getWord(int length) {
    if (library[length].size() > 0) {
        string tempVect = library[length][0];
        library[length].erase(library[length].begin());
        library[length].push_back(tempVect);
        return tempVect;
    }
    return "";
}


string Game::jumble(string word) {
    for (int i = 0; i < 1000; i++) {
        unsigned long storeNum = rand() % word.size();
        unsigned long storeNum1 = rand() % word.size();
        char letter = word[storeNum];
        char letter1 = word[storeNum1];
        word[storeNum] = letter1;
        word[storeNum1] = letter;
    }
    return word;
}

void Game::saveGame(int level, int score, int lifelineRem, int currentLength, string currentWord, string jumbledWord,
                    int stage, int guessRem, int numWordCorrect, string longestWord, string filePath) {
    ofstream gamefile;
    gamefile.open("Save.txt");
    gamefile << level << " "
             << score << " "
             << lifelineRem << " "
             << currentLength << " "
             << currentWord << " "
             << jumbledWord << " "
             << stage << " "
             << guessRem << " "
             << numWordCorrect << " "
             << longestWord << " "
             << filePath;

    gamefile.close();

}

vector<string> Game::loadGame() {
    ifstream load;
    vector<string> temp;

    try { //opening a file might break and catches it.
        load.open("Save.txt"); //if file exist then some sort of game is saved in it.
        if (load.good()) {
            for (int i = 0; i < 11; i++) {
                string tempVal;
                load >> tempVal;
                cout << tempVal;
                temp.push_back(tempVal);
            }
            return temp;
        } else {
            return vector<string>();
        }
    } catch(const ifstream::failure &e) {
        return vector<string>();
    }
}

