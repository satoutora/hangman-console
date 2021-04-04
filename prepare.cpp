#include <iostream>
#include <cstdlib>
#include <vector>
#include <thread>
#include <string>
#include <windows.h>
#include <conio.h>


using namespace std;

void clearScreen_1()
{
#ifdef _WIN32
    system("cls");
#elif __linux__
    system("clear");
#endif // _WIN32
}

int SelectMode()
{
    clearScreen_1();
    cout <<"\t\t\t"<< "WELLCOME TO HANGMAN" << endl <<endl;
    cout <<"\t Select play mode:" <<endl;
    cout <<"(1). Bot thinks, you guess" <<endl;
    cout <<"(2). You think, bot suesses" <<endl<<endl;
    cout <<"Your select: ";
        int modeplay;
        cin>>modeplay;
        return modeplay;
}

int ConfirmLevel()
{
    cout <<"\t\t 1.(EASY) \t\t\t 2.(HARD)" <<endl;
    cout <<"Level selection:" ;
    int level;
    cin >> level;
    return level;
}
int ConfirmTag()
{
    cout <<"\t 1.(ANIMALS) \t\t 2.(ACTIONS) " <<endl;
    cout <<"\t 3.(THINGS) \t\t 4.(MYSTIC) " <<endl;
    cout <<"Tag selection:" ;
    int tag;
    cin >> tag;
    return tag;
}

void Start1()
{
    clearScreen_1();
    cout <<"\t\t\t"<< "WELLCOME TO HANGMAN" << endl;
    cout <<"*RULES:*"<<endl;
    cout <<"*1 turn, you guess 1 character of the Guessword*" << endl;
    cout << "*Type 'suggest' to take 1 suggestion*" << endl;
    cout <<"\t\t_____________________________________"<<endl;
    cout <<endl;
}

void Start2()
{
    clearScreen_1();
    cout <<"\t\t\t"<< "WELLCOME TO HANGMAN" << endl;
    cout <<"*RULES:*"<<endl;
    cout <<"*You think one word and I will guess it*"<<endl;
    cout <<"\t\t_____________________________________"<<endl;

}

char Clock()
{
    int counter = 20; //amount of seconds
    //Sleep(1000);
    char a;

    cout << "\rTime remaining: xx";
    while (counter >= 1)
    {
        if(counter >9)cout<<"\b\b"<< counter;
        else cout<<"\b\b"<<"0"<< counter;
        //cout<<"\b\b"<< counter;
        if(kbhit())
        {
            cout<<endl;
            cout<<"Your next guess is: ";
            a=getch();
            //cin>>a;
            //cout<<a<<endl;
            break;
        }
        Sleep(1000);
        counter--;
    }
    if(counter < 1) a = '*';
    //else cin>>a;
    return a;
}
