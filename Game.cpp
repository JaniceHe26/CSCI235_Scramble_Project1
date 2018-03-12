//
//
#include <iostream>

#include "Game.h"


using namespace std;

//This function will run the game by taking in a text file and see if it is valid or not.
//Precondition: User must enter a correct file path as well file cannot be empty and have the right amount of word.
void Game::run(string filePath) { //
    gameRunning = true;

    bool fileExist = createLibrary(filePath);
    while (!fileExist) {  //While loop will keep going until user enter a correct file.
        cout << "File does not exist. Please enter a new file path: ";
        cin >> filePath;
        fileExist = createLibrary(filePath);
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

//    int currentLevel = 0;
//    int maxLevel = currentLevel;
    int level = 1;
    int score = 0;
    int lifeLineRem = 5;
    int numGuessRem = 3;
    int currentLength = 3;
    string currentWord = getWord(currentLength);
    string jumbledWord = jumble(currentWord);
    string guessedWord; //a word user will enter
    int stage = 1;

    //check if there is a saved game.

    while (gameRunning) {

        cout << "\n\n";
        cout << "WORD JUMBLE BEGIN:" << endl;
        cout << "------------------------------------------------------------------------------------------------------"
             << endl;
        cout << "Level:\t" << level << endl;//(put in keeping track of level function here)
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
            stage++;
            if (stage > 3) {
                stage = 1;
                level++;
                score = score + 10;
                currentLength++;
//                if(currentLength > maxLength){
//                    //game is over******************************
//                    //******************************************
//                    //******************************************
//                    //******************************************
//                }
                while (library.count(currentLength) == 0 && currentLength <= maxLength) {
                    currentLength++;
                }
            }
            score = score + 5;
            currentWord = getWord(currentLength);
            jumbledWord = jumble(currentWord);
            numGuessRem = 3;

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
        }

        cout << "\n\n";


    }
//        cout<<"Game is over."<<endl;
}


//This function will read file. Using a while loop just print out what is being read.
bool Game::createLibrary(string filePath) {
    ifstream file;
    try {
        file.open(filePath);
        while (!file.eof()) {
            string word;
            file >> word;
            word = wordConformance(word);
            storeWord(word);
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
    }
    return word;
}

void Game::saveFile(string Game) {
    string saveGame;
    cout << "Would you like to save the fucking game? (y/n)" << endl;
    cin >> saveGame;
    while (!(saveGame == "y" || saveGame == "Y" ||
             saveGame == "n" || saveGame == "N")) {
        cout << "Invalid Entry" << endl;
        cin >> saveGame;
    }
    if (saveGame == "save") {//add in something that will save automatically if user quit.
        getline(cin, saveGame);
        ofstream filePath("Save.txt");
        filePath << saveGame;
        filePath.close();
    }
}


