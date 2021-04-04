#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>
#include <windows.h>

#include "draw.h"
#include "utility.h"
#include "prepare.h"

int kt[500] = {0};
vector<string> vocabulary;
int d; int dd[500];

using namespace std;

char readAGuess(int counttrue)
{
    char guess;
    if(counttrue == 0){
        cout<<"\t\t __\n";
        cout<<"\t\t \\ \\________________\n";
        cout<<"\t\t |     Incorect!    \\\n";
        cout<<"\t\t |________-_________/\n";
    }
    else if(counttrue >= 1 ){
        cout<<"\t\t __\n";
        cout<<"\t\t \\ \\_______________________\n";
        cout<<"\t\t |          corect!        \\\n";
        //cout<<"\t\t |  You have 2 letter(s)   /\n";
        cout<<"\t\t |  You have "<<counttrue<<" letter(s)   /\n";
    }
    cout<<endl;
    cout << "Please enter your next guess: " <<endl;
    //cin >> guess;
    guess = Clock();
    return guess;
}

void MakeSuggest(string& guessedWord, const string& word)
{
    int n = guessedWord.length();
    for (int i = 0; i < n; i++) {
        if (guessedWord[i] == '-') {
            guessedWord[i] = word[i];
            break;
        }
    }
}

void update(string& guessedWord, const string& word, int& counttrue, char guess)
{
    int n = guessedWord.length();
    for (int i = 0; i < n; i++) {
        if (word[i] == guess)
            {
                guessedWord[i] = guess;
                ++counttrue;
            }
    }
}

char alp[]={'u','e','o','a','i'};
char randAlpha(string z)
{
    srand(time(0));
    int temp = z.size();
    int dem=0; char aa;
    for(int i=0; i<z.length(); ++i)
    {
         aa=z[i];
        if(kt[int(aa)]==1) ++dem;
    }
    if(dem==z.length()) aa = alp[rand()%5];
    else
    {
        aa = z[rand() % temp];
        while( kt[int(aa)] == 1)
        {
            aa = z[rand() % temp];
        }
        kt[int(aa)]=1;
    }
    return aa;
}

void makelistword(const string& fileName, int length)
{
    ifstream file(fileName);

    d=-1;
    while (!file.eof()) {
        string line;
        getline(file, line);
        if (file && !line.empty() && line.length() == length)
            {
                vocabulary.push_back(normalize(line));
                ++d; dd[d]=1;
            }
    }
}

string randfixword()
{
    srand(time(0));
    int n = vocabulary.size();
    if(n>0)
    {
        int temp = rand() % n;
        while(dd[temp] != 1)
        {
            temp = rand() % n;
        }
        return vocabulary[temp];
    }
}


int main(int argc, char* argv[])
{
    //srand(time(0));
    //string fileName = argc > 1 ? argv[1] : "ogden_picturable_200.txt";
    int cwin =0; int cloose =0;
    while (true) {

        int modeplay = SelectMode();

    if(modeplay == 1)  // may doan nguoi nghi
    {
        Start1();
        int level = ConfirmLevel();
        int tag = ConfirmTag();

        srand(time(0));
        string fileName;
        switch(tag)
        {
            case 1 : fileName = argc > 1 ? argv[1] : "animals.txt"; break;
            case 2 : fileName = argc > 1 ? argv[1] : "actions.txt"; break;
            case 3 : fileName = argc > 1 ? argv[1] : "things.txt"; break;
            case 4 : fileName = argc > 1 ? argv[1] : "mystic.txt"; break;
        }

        string word = chooseWord(fileName,level);
        if (word.empty()) {
            cout << "No word available in " << fileName << endl;
            return 0;
        }

        string guessedWord = string(word.length(), '-');
        int badGuessCount = 0;
        int Suggestion = (word.length()-1)/2;
        const int MAX_BAD_GUESS = 7;
        int counttrue = -1;
        string badGuess;

        do {
            renderGame(guessedWord, badGuessCount, Suggestion, tag, level, badGuess);
            char order = readAGuess(counttrue);
            counttrue = 0;

            if(order == '$' && Suggestion>0){
                MakeSuggest(guessedWord, word);
                --Suggestion;
                counttrue = 1;
            }
            else{
                    char guess = order;
                    if (contains(word, guess)) {
                        update(guessedWord, word, counttrue, guess);
                    } else {
                        badGuessCount++;
                        badGuess += guess;
                    }
            }
        } while (badGuessCount < MAX_BAD_GUESS && guessedWord != word);

        printGameOverInfo(guessedWord, word, badGuessCount, Suggestion, tag, level, cwin, cloose);
    }

    else  //nguoi nghi may doan
    {
        string ans ;
        int round = 10;
        string fileName = argc > 1 ? argv[1] : "ogden_picturable_200.txt";
        int length;
        int TF;
        clearScreen();
        Start2();

        cout << endl << "How many letters does word has?";
        cin >> length;
        makelistword(fileName, length);
        int check = vocabulary.size();
        while(round >= 1)
        {
            system("cls");
            Start2();
            cout << "roundleft: " << round ;
            string bb = randfixword();
            char aa = randAlpha(bb);
            //cout << endl << bb <<" "<< aa;
            cout << endl <<"Does word has letter: "<< aa << endl << "True(1) or False(2)?:";
            //cout << endl << kt[int(aa)] << endl;
            --round;
            cout << endl;
            //for(int i=0; i<=d; ++i) cout<<dd[i]<<" ";
            cin >> TF;
            if(TF==1)
            {
                for(int i=0; i<=d; ++i){
                    string ss = vocabulary[i];
                    if(contains(ss,aa)==false && dd[i]==1){
                        dd[i]=0; --check;
                    }
                }
            }
            else
            {
                for(int i=0; i<=d; ++i){
                    string ss = vocabulary[i];
                    if(contains(ss,aa)==true && dd[i]==1){
                        dd[i]=0; --check;
                    }
                }
            }
            //cout << endl << "check = " << check;
            if(check == 1)
            {
                for(int i=0; i<=d; ++i){
                    if(dd[i] == 1) cout << "Is your word is:" << vocabulary[i] <<endl;
                    }
                     cout << "True(1) or False(2)?: "; cin >> TF;
                    if(TF == 1) {
                     cout << "Yay, I win :) "; ++ cloose; }
                    else {
                     cout << "Hic, I loose"; ++cwin; }
                break;
            }
        }
         if(check > 1) {
                cout << "Is your word is:" << randfixword();
                cout<<endl;
                cout << "True(1) or False(2)?: "; cin >> TF;
                if(TF == 1) {
                    cout << "Yay, I win :) "; ++ cloose; }
                else {
                    cout << "Hic, I loose"; ++cwin; }
                break;
            }

            else if(check < 1) {
                cout << "Sorry, I can't find it :( " << endl;
                ++cwin;
                break;
            }

    }

        //cout << endl << check << " " << d;
        //ket thuc game
        cout << endl;
        cout << "You win: " << cwin << endl
             << "You loose: " << cloose << endl;
        cout << "Do you want more (Y/N) ?";
        string answer;
        cin.ignore(1);
        getline(cin, answer);
        if (answer != "Y" && answer != "y")
            break;
    }

    return 0;
}
