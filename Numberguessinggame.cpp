#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int main()
{
    int num,guess=0,tries=0;
    srand(time(0));//this will generate a random number
    num=rand() %100+1; //random number between 1 to 100
    cout<<"Welcome to random number guessing game....................."<<endl;
    do
    {
        cout<<"Enter the guess number between 1 to 100 :"<<endl;
        cin>>guess;
        tries++;
         if(guess > num)
         {
            cout<<"Too high,guess a lower number:"<<endl;
         }
         else if(guess < num)
         {
            cout<<"Too low,guess the higher number :"<<endl;
         }
         else
         {
            cout<<"Yes you got it correctly in "<<tries<<"guesses !"<<endl;
         }

    }while(guess != num);
    return 0;
}