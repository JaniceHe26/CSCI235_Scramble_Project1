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
#include <algorithm>
using namespace std;


class Game {
public:
    void run(string filePath); //To start a game. User interaction will happen here
    void storeWord(string word);

private:
    bool gameRunning = false;
    int maxLength = 0;
    map <int, vector<string> > library;
    bool createLibrary(string filePath);
    string getWord(int length);
    string jumble(string word);
    string wordConformance(string word);
    void saveFile(string Game);


};


#endif //WORD_SCRAMBLEPROJECT1CSC235_GAME_H
