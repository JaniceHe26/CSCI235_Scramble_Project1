//
// Created by Janice He on 3/6/18.
//

#include <iostream>
#include "Game.h"
#include <fstream>
using namespace std;

//Game will start running
void Game::start() {
    gameRunning = true;

//Ask user to give a text file. If user input a wrong file then ask user to input file again.
    string filePath; //filepath will be all string.
    cout << "Input text file path: "; //Ask user to input file path.
    cin>> filePath; //User enter file here.
    bool fileExist = getLibrary(filePath);
    while (!fileExist) {  //While loop will keep going until user enter a correct file.
        cout << "File does not exist. Please enter a new file path: ";
        cin >> filePath;
        fileExist = getLibrary(filePath);
    }


//Explains the game/rules to player.
//    cout<<"You must unscramble the jumbled word given to pass on the next level."<<endl;
//    cout<<"You will have three tries for each level."<<endl;
//    cout<<"You may have an option to use a Life Line once if you are stuck on a word."<<endl;
//    cout<<"Good luck!" <<endl;




//    printHello();
//    getWord();
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
bool Game::getLibrary(string filePath){
    ifstream file;
    file.open(filePath);
    string x;
    while (file >> x) {
        cout << x << endl;
    }
    file.close();
    return true;
}


//void Game::printHello() {
//    std::cout<< "hello\n";
//}
//
//string Game::getWord(int length) {
//    return vector[index].get(randomNumber);
//    //should access from text file.
//}
//
//void Game::useLifeLine(){
//    //
//
//}
