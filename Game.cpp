//
//
#include <iostream>

#include "Game.h"


using namespace std;

//This function will run the game by taking in a text file and see if it is valid or not.
//Precondition: User must enter a correct file path as well file cannot be empty and have the right amount of word.
void Game::run(string filePath) { //
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

//Postcondition:



//Explains the game/rules to player.
    cout << "\n\n";
    cout << "You must unscramble the jumbled word given to pass on the next level." << endl;
    cout << "You will have three tries for each level." << endl;
    cout << "You may have an option to use a Life Line once if you are stuck on a word." << endl;
    cout << "Good luck!" << endl;
    cout << "\n\n";


//UI ish of the program:
    int level = 1;
    int score = 0;
    int lifeLineRem = 5;
    int numGuessRem = 3;
    int currentLength = 3;
    string currentWord;
    string jumbledWord;
    string guessedWord; //a word user will enter
    int stage = 1;
// This variables will help us with saving game:
    int maxLevel;
    int numWordCorrect = 0;
    string longestWord;
    //check if there is a saved game.
    if (loadGameValues.size() == 10) {
        level = stoi(loadGameValues[0]);
        score = stoi(loadGameValues[1]);
        lifeLineRem = stoi(loadGameValues[2]);
        currentLength = stoi(loadGameValues[3]);
        currentWord = loadGameValues[4];
        jumbledWord = loadGameValues[5];
        stage = stoi(loadGameValues[6]);
        numWordCorrect = stoi(loadGameValues[7]);
        longestWord = loadGameValues[8];
        filePath = loadGameValues[9];
        fileExist = createLibrary(filePath);
        if (!fileExist) {
            cout << "\nSaved library failed to load.\n";
            return;
        }
        while (getWord(currentLength) != currentWord);
    } else {
        currentWord = getWord(currentLength);
        jumbledWord = jumble(currentWord);
    }

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

        cin >> guessedWord;

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
                    score = score +15;
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
            saveGame(level, score, lifeLineRem, currentLength, currentWord, jumbledWord, stage, numWordCorrect, longestWord, filePath);

        } else {
            cout << "Incorrect!" << endl;

            numGuessRem--;

            //Fix this case into like filepath. (Dont let them enter something other wise)
            if (numGuessRem == 0) {
                if (lifeLineRem > 0) {
                    string response;
                    cout << "You ran out of chances to guess for this word. If you do not use a lifeline you will lose."
                         << endl; //Would you like to use lifeline?
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
                        //Game is over*******************************
                    }
                } else {
                    cout << "Sorry you do not have any life line left. You lost."
                         << endl; //maybe put this in the first statement
                    gameRunning = false;
                    //Game is over*******************************
                }
            }
            saveGame(level, score, lifeLineRem, currentLength, currentWord, jumbledWord, stage, numWordCorrect, longestWord, filePath);
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


//This function will read file. Using a while loop just print out what is being read.
bool Game::createLibrary(string filePath) {
    ifstream file;
    try {
        file.open(filePath);
        if (file.good()) {
            while (!file.eof()) {//while its running till the end for every word in the file it pulls it in give it to the string
//then conform it and store it into a storeWord
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


//This function takes all upper cases,punctuation and forces all characters into lower case.
string Game::wordConformance(string word) {
    string result;
    remove_copy_if(word.begin(), word.end(),
                   back_inserter(result), //Store output
                   ptr_fun<int, int>(ispunct)
    );
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

//This Function will store the word from file into a map of length and word. Also, check to see if word is existing.
void Game::storeWord(string word) { //worry about length unique .use library
    auto length = (int) word.length(); //this will give length of the word by calling a function called length on <string>
    if (length > maxLength) {
        maxLength = length;
    }
    if (library.count(length) == 1) { //If key exist
        if (find(library[length].begin(), library[length].end(), word) ==
            library[length].end()) { //Look through the element of vector
            library[length].push_back(word); //then add word
        }
    } else { //If length and word does not exist, create a new vector.
        vector<string> tempVect;
        tempVect.push_back(word);
        library[length] = tempVect;
    }
}


//This Function will take the word from the text file -getWord();
string Game::getWord(int length) {
//    return library[length][rand()%library[length].size()]; //Generate random number from the size of the vector
    //rotating vector's value
    if (library.count(length) == 1) {
        string tempVect = library[length][0];
        library[length].erase(library[length].begin());
        library[length].push_back(tempVect);
        return tempVect;
    }
    return "";
}


string Game::jumble(string word) {
    for (int i = 0; i < 1000; i++) {
        int storeNum = rand() % word.size();
        int storeNum1 = rand() % word.size();
        char letter = word[storeNum];
        char letter1 = word[storeNum1];
        word[storeNum] = letter1;
        word[storeNum1] = letter;
    } //need a while saying if jumble word is same rejumble
    return word;
}

void Game::saveGame(int level, int score, int lifelineRem, int currentLength, string currentWord, string jumbledWord,
                    int stage, int numWordCorrect, string longestWord, string filePath) {
    ofstream gamefile;
    gamefile.open("Save.txt");
    gamefile << level << " "
             << score << " "
             << lifelineRem << " "
             << currentLength << " "
             << currentWord << " "
             << jumbledWord << " "
             << stage << " "
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
            for (int i = 0; i < 10; i++) {
                string tempVal;
                load >> tempVal;
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

