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
//        cout << "File does not exist. Please enter a new file path: ";
//        cin >> filePath;
        fileExist = createLibrary(filePath);
    }
//Postcondition:

//    cout << jumble(getWord(5)); for testing

//Explains the game/rules to player.
//    cout<< "\n\n";
//    cout<<"You must unscramble the jumbled word given to pass on the next level."<<endl;
//    cout<<"You will have three tries for each level."<<endl;
//    cout<<"You may have an option to use a Life Line once if you are stuck on a word."<<endl;
//    cout<<"Good luck!" <<endl;
//    cout<< "\n\n";

//UI ish of the program:

    int level = 1;
    int score = 0;
    int lifeLineRem = 5;
    int numGuess = 3;
//    int currentLevel = 0;
//    int maxLevel = currentLevel;
    int currentLength = 3;
    string currentWord = getWord(currentLength);
    string jumbledWord = jumble(currentWord);
    string guessedWord; //a word user will enter
    int stage = 1;



    while (gameRunning = true){


        cout<< "\n\n";
        cout<< "WORD JUMBLE BEGIN:"<<endl;
        cout<<"---------------------------------------------------------------------------------------------------------"<<endl;
        cout<<"Level:\t"<< level <<endl;//(put in keeping track of level function here)
        cout<<"Stage:\t(" << stage << "/3)" << endl;
        cout<<"Score:\t"<< score <<endl;//(put in keeping track of score function here)
        cout<<"LifeLine Remaining:\t"<< lifeLineRem <<endl;//(Lifeline remaining function inside here)
        cout<<"---------------------------------------------------------------------------------------------------------"<<endl;
        cout<<"\n\n";
        cout<<"Number of guesses remaining:\t"<< numGuess <<endl; //NumberofTries in here
        cout<<"Your word to unscramble:\t" << jumbledWord <<endl;//put in the displayWord function here //cin>>
        cout<<"Please enter the word:\t";

        cin>> guessedWord;

        if (currentWord == guessedWord) {
            cout << "Correct!" << endl;
            stage++;
            if(stage > 3){
                stage = 1;
                level++;
                score = score + 10;
                currentLength++;
                if(currentLength > maxLength){
                    //game is over******************************
                }
                while(library.count(currentLength) == 0 && currentLength <= maxLength){
                    currentLength++;
                }
           }
            score = score + 5;
            currentWord = getWord(currentLength);
            jumbledWord = jumble(currentWord);
            numGuess = 3;



        } else {
            cout << "Incorrect!" << endl;
            cout << "Stage:\t" << stage;
            numGuess = numGuess - 1;
            cout << "Number of Guess remaining for this stage:\t" << numGuess;
        }

        cout<<"\n\n";


    }
        cout<<"Game is over."<<endl;










//    useLifeLine();

//    while (gameRunning && livesRemaining > 0) {
//        // talk to user
//        //switch case 1. guess word 2. use life line 3. quit
//        switch(userInput) {
//            1: do something
//                break;
//            2: do something
//                break;
//            3. gameRunning = false;
//                break;
//        }
//    }
//    if(livesRemaining == 0) {
//        // give failure message
//    } else {
//        // give you won message.
//    }
}

//This function will read file. Using a while loop just print out what is being read.
bool Game::createLibrary(string filePath){
    ifstream file;
//    file.exceptions ( ifstream::failbit | ifstream::badbit );
    try{
        file.open(filePath);
        while(!file.eof()){
            string word;
            file >> word;
            storeWord(word);
        }
    } catch (const ifstream::failure& e) {
        return false;
    }
//    cout<< library[5][2];
    return true;
}

//This Function will store the word from file into a map of length and word. Also, check to see if word is existing.
void Game::storeWord(string word) { //worry about length unique .use library
    auto length = (int) word.length(); //this will give length of the word by calling a function called length on <string>
    if(length > maxLength){
        maxLength = length;
    }
    if(library.count(length) == 1){ //If key exist
        if (find(library[length].begin(), library[length].end(), word) == library[length].end()) { //Look through the element of vector
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
    if(library.count(length) == 1){
        string tempVect = library[length][0];
        library[length].erase(library[length].begin());
        library[length].push_back(tempVect);
        return tempVect;
    }
    return "";
}


string Game::jumble(string word) {
    for(int i = 0; i < 1000; i++) {
        int storeNum = rand()%word.size();
        int storeNum1 = rand()%word.size();
        char letter = word[storeNum];
        char letter1= word[storeNum1];
        word[storeNum] = letter1;
        word[storeNum1] = letter;
    }
    return word;
}



//
//void Game::useLifeLine(){
//    //
//
//}
