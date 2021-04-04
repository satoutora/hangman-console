#include <iostream>
#include <cstdlib>
#include <vector>
#include <thread>

using namespace std;

string getHangPicture(int badGuessCount)
{
    string picture[] = {"",
"   ------------\n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        ",
"   ------------\n"
"   |          |\n"
"   |          O\n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        ",
"   ------------\n"
"   |          |\n"
"   |          O\n"
"   |          |\n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        ",
"   ------------\n"
"   |          |\n"
"   |          O\n"
"   |         /|\n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        ",
"   ------------\n"
"   |          |\n"
"   |          O\n"
"   |         /|\\\n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        ",
"   ------------\n"
"   |          |\n"
"   |          O\n"
"   |         /|\\\n"
"   |         / \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        ",
"   ------------\n"
"   |          |\n"
"   |          O\n"
"   |         /|\\\n"
"   |         / \\\n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        ",

};
    return picture[badGuessCount];
}

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#elif __linux__
    system("clear");
#endif // _WIN32
}

void Inforgame (int tag, int level)
{
    cout <<"\t\t\t"<< "WELLCOME TO HANGMAN" << endl;
    cout <<"*RULES:*"<<endl;
    cout <<"*1 turn, you guess 1 character of the Guessword*" << endl;
    cout << "*Type '$' to take 1 suggestion*" << endl;
    cout <<"\t\t_____________________________________"<<endl<<endl;

    cout <<"Your select Level: ";
    if(level == 1) cout <<"EASY"; else cout<<"HARD"; cout<<endl;

    cout <<"Your select Tag: ";
    if(tag == 1) cout<<"ANIMALS \n";
    else if(tag == 2) cout<<"ACTIONS \n";
    else if(tag == 3) cout<<"THINGS \n";
    else if(tag == 4) cout<<"MYSTIC \n";
}

void renderGame(string guessedWord, int badGuessCount, int Suggestion, int tag, int level, string badGuess = "")
{
    clearScreen();
    Inforgame(tag, level);
    cout<<endl;
    cout << "Current guess = " << guessedWord << endl << endl;
    cout << "You have " << Suggestion << " suggestion(s)" << endl;
    cout << "You have made bad " << badGuessCount << " guess(es)"
         << (badGuess.empty() ? "" : ": ") << badGuess << endl
         << getHangPicture(badGuessCount) << endl;
}

const vector<string> HANGED = {
"   ------------\n"
"   |         /\n"
"   |        O\n"
"   |       /|\\\n"
"   |       / \\\n"
"   |         \n"
"   |         \n"
"   |         \n"
"   |         \n"
"-------        ",
"   ------------\n"
"   |          |\n"
"   |          O\n"
"   |         /|\\\n"
"   |         / \\\n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        ",
"   ------------\n"
"   |           \\\n"
"   |            O\n"
"   |           /|\\\n"
"   |           / \\\n"
"   |             \n"
"   |             \n"
"   |             \n"
"   |             \n"
"-------        ",
"   ------------\n"
"   |          |\n"
"   |          O\n"
"   |         /|\\\n"
"   |         / \\\n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        "
};

const vector<string> FREE = {
"   ------------\n"
"   |         \n"
"   |         \n"
"   |         \n"
"   |         \n"
"   |         \n"
"   |         O\n"
"   |        /|/\n"
"   |        / \\\n"
"-------        ",
"   ------------\n"
"   |         \n"
"   |         \n"
"   |         \n"
"   |         \n"
"   |         \n"
"   |        \\O\\\n"
"   |         | \n"
"   |        / \\\n"
"-------        ",
"   ------------\n"
"   |         \n"
"   |         \n"
"   |         \n"
"   |         \n"
"   |         \n"
"   |             O \n"
"   |            \\|\\\n"
"   |            / \\\n"
"-------        ",
"   ------------\n"
"   |         \n"
"   |         \n"
"   |         \n"
"   |         \n"
"   |         \n"
"   |            /O/\n"
"   |             |\n"
"   |            / \\\n"
"-------        "
};


void printGameOverInfo(string guessedWord, string word, int badGuessCount, int Suggestion, int tag, int level, int& cwin, int& cloose)
{
    renderGame(guessedWord, badGuessCount, Suggestion, tag, level);
    //word = guessedWord;
    if (guessedWord != word) {
        int n = 0;
        for(int i=1; i<=16; ++i) {
            clearScreen();
            cout <<endl;
            cout << "Game Over!!! You are hanged" << endl << endl
                 << "The correct word is: " << word << endl;
            cout << HANGED[n];
            n = (n+1) % HANGED.size();
            std::this_thread::sleep_for (std::chrono::milliseconds(100));
        }
    ++cloose;
    }
    else{
        int n=0;
        for(int i=1; i<=16; ++i) {
                clearScreen();
                cout << endl;
                cout << "Congrats!!! You are free" << endl << endl
                     << "The correct word is: " << word << endl;
                cout << FREE[n];
                n = (n+1) % FREE.size();
                std::this_thread::sleep_for (std::chrono::milliseconds(80));
        }
    ++cwin;
    }
}
