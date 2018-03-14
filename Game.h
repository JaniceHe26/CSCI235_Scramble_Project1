//
// Created on 3/6/18.
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
#include <algorithm>
using namespace std;


class Game {
public:
    void run(string filePath);
    void storeWord(string word);


private:
    bool gameRunning = false;
    int maxLength = 0;
    map <int, vector<string> > library;
    bool createLibrary(string filePath);
    string getWord(int length);
    string jumble(string word);
    string wordConformance(string word);
    void saveGame(int level, int score, int lifelineRem, int currentLength, string currentWord, string jumbledWord,
                  int stage, int guessRem, int numWordCorrect, string longestWord, string filePath);
    vector<string> loadGame();
};


#endif //WORD_SCRAMBLEPROJECT1CSC235_GAME_H
