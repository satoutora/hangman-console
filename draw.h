#ifndef __DRAW_H__
#define __DRAW_H__

#include <string>

std::string getHangPicture(int badGuessCount);
void clearScreen();
int Start();
void renderGame(std::string guessedWord, int badGuessCount, int Suggestion, int tag, int level, std::string badGuess = "");
void printGameOverInfo(std::string guessedWord, std::string word, int badGuessCount, int Suggestion, int tag, int level, int& cwin, int& cloose);

#endif // __DRAW_H__
