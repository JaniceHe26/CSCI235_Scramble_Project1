//
// Created by Janice He on 3/6/18.
//

#ifndef WORD_SCRAMBLEPROJECT1CSC235_GAME_H
#define WORD_SCRAMBLEPROJECT1CSC235_GAME_H

#include <iostream>
#include <map>
#include "Game.h"
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;


class Game {
public:
    void run(string filePath); //To start a game. User interaction will happen here
//    string getWord(); //Random word from text file.



private:
//    int score = 0; //should I create another header file for score?
//    int playersNumGuess = 0;
//    string word = ""; //Word user will enter....should this be private?
//    bool lifeLine = true;
    void level(int playerLvl);
    bool gameRunning = false;
    int maxLength = 0;
    map <int, vector<string> > library;
    bool createLibrary(string filePath);
    void storeWord(string word);
    string getWord(int length);
    string jumble(string word);
    string correctWord(int score); // keeps the correct word saved.
    void saveGame();


//    void useLifeLine(); //extra life if player wish to use, using bool because if lifeline is activated (so thinking t it will activates)





};


#endif //WORD_SCRAMBLEPROJECT1CSC235_GAME_H
