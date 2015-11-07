#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>

using namespace std;

const float minBet=5;
const float maxBet=50000;
const int iterations=50;

//return true with odds oddsNum/oddsDen
bool spin(float oddsNum, float oddsDen)
{
    bool won;
    int guess=rand()%static_cast<int>(oddsNum)+1;
    if(guess>static_cast<int>(oddsDen))
        won=false;
    else
        won=true;
    return won;
}

//display stats for current iteration
void display_status(int currentIteration, bool won, bool up, float currentTotal, float currentBet)
{
    int set_w_constant=7;
    
    cout<<setiosflags(ios::left);
    
    if(won)
        cout<<setw(set_w_constant)<<"Win";
    else
        cout<<setw(set_w_constant)<<"Loss";
    
    
    if(up)
        cout<<setw(set_w_constant)<<"Up";
    else
        cout<<setw(set_w_constant)<<"Down";
    
    cout<<setw(set_w_constant)<<(int)currentTotal
        <<setw(set_w_constant)<<(int)currentBet
        <<setw(set_w_constant)<<currentIteration
        <<endl;
}

//check if the current game still allows betting with our strategy
bool can_keep_betting_with_strategy(float currentTotal, float currentBet, float maxBet)
{
    
    //if your current bet would take more than you have
    if((currentTotal-currentBet)<0)
    {
        cout<<"You lost! No money left."<<endl;
        return false;
    }
    
    //if your current bet would be larger than the max allowed bet
    if(currentBet>maxBet)
    {
        cout<<"You lost! Max bet reached."<<endl;
        return false;
    }
    
    //if we still have money and haven't reached max bet, can continue
    return true;
}

//use strategy to determine current bet
float get_current_bet_using_strategy(bool wonLast, float currentBet, float Ratio, float minBet)
{
    if(wonLast)
        currentBet=minBet;
    else
        currentBet*=Ratio;
    
    return currentBet;
}

//display when we transition from up to down or vice-versa
void display_if_up_down_transition(bool up, float currentTotal, float startingTotal)
{
    if(currentTotal>=startingTotal && !up)
        cout<<"----------Transitioned from down to up-------------"<<endl;
    
    if(currentTotal<startingTotal && up)
        cout<<"----------Transitioned from up to down-------------"<<endl;
}

int main()
{
    //initialize variables
    float oddsNum,oddsDen,odds,startingTotal,currentBet,currentTotal,finalBet,winnings,Ratio;
    bool wonLast=true,won,up;
    char throw_away;
    
    cout<<"Please enter an amount to buy in for. ex: 5000"<<endl;
    cin>>startingTotal;
    currentTotal=startingTotal;
    
    //enter odds to bet on
    cout<<"Please enter odds. ex: 2:1"<<endl;
    cin>>oddsNum;
    cin>>throw_away;
    cin>>oddsDen;
    
    cout<<"You entered odds of "<<oddsNum<<":"<<oddsDen<<endl;
    odds=oddsNum/oddsDen;
    
    //calculate the ideal betting ratio (based on recurrance relation)
    Ratio=1.0+(1.0/(odds-1.0));
    cout<<"Your ideal betting ratio is "<<Ratio<<endl;
    
    //seed random
    srand(time(0));
    
    //simulate "iterations" number of spins
    for(int i=1;i<=iterations;i++)
    {
        //here's our strategy
        currentBet = get_current_bet_using_strategy(wonLast,currentBet,Ratio,minBet);
        
        //cover loss situations
        if(!can_keep_betting_with_strategy(currentTotal,currentBet,maxBet))
            return 0;
        
        //spin! determine if we won
        won=spin(oddsNum,oddsDen);
        
        //update wonLast and currentTotal according to whether we won or not
        if(won)
        {
            currentTotal+=currentBet*odds-currentBet;
            wonLast=true;
        }
        else
        {
            currentTotal-=currentBet;
            wonLast=false;
        }
        

        //make a line for a clear marker when transitions from down to up
        display_if_up_down_transition(up, currentTotal, startingTotal);
        
        //update whether we're up or down
        currentTotal>=startingTotal ? up=true : up=false;
        
        //display
        display_status(i,won,up,currentTotal,currentBet);
        

    }
    
    cout<<endl;
    cout<<"Your final total after "<<iterations<<" iterations is "<<currentTotal<<endl;
    
    return 0;
}
