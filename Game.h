//
// Created by Janice He on 3/6/18.
//

#ifndef WORD_SCRAMBLEPROJECT1CSC235_GAME_H
#define WORD_SCRAMBLEPROJECT1CSC235_GAME_H


using namespace std;

class Game {
public:
    void start(); //To start a game.
//    void printHello(); //Testing References
//    string getWord(); //Random word from text file.



private:
//    int score = 0; //should I create another header file for score?
//    int playersNumGuess = 0;
//    string word = ""; //Word user will enter....should this be private?
//    bool lifeLine = true;
    bool gameRunning = false;
//    vector <vector <string> > wordStore;
//    string filePath();
//    int livesRemaining = 3;
    bool getLibrary(string filePath);
//    void useLifeLine(); //extra life if player wish to use, using bool because if lifeline is activated (so thinking t it will activates)





};


#endif //WORD_SCRAMBLEPROJECT1CSC235_GAME_H
