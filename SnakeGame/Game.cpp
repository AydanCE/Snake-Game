#include<iostream>
#include<conio.h>
#include<Windows.h>
using namespace std;
/*
iostream: Standard Input and Output Library of C++..
windows.h: Windows API Library.
conio.h: Non-Standard Library that contains console commands.
*/

//height and width of the boundary
const int width = 80;
const int height = 20;

//Head coordinates of snake (x and y axis)
int x, y;

//Coordinates of food
int fruitCordX, fruitCordY;

//variable to store the score of player
int playerScore;

//Array to store the coordinates of snake tail
int snakeTailX[100], snakeTailY[100];

//variable to store the length of snake
int snakeTailLen;

//for storing snake's moving snake's direction
enum snakesDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};

//snake direction variable
snakesDirection sDir;

//boolen variable for checking game is over or not
bool isGameOver;

//Initializing Game
void GameInit()
{
    isGameOver = false;
    sDir = STOP;
    x = width / 2;
    y = height / 2;
    fruitCordX = rand() % width; //range between [0, width-1]
    fruitCordY = rand() % height; //range between[0, height-1]
    playerScore = 0;
}

//Creating game board and rendering game
void GameRender(string playerName)
{
    system("cls"); //Clearing the console
    //Creating top walls with '-'
    for(int i = 0; i < width + 2; i++)
    {
        cout<<"-";
    }
    cout<<endl;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j <= width; j++)
        {
            //Creating side walls with "|"
            if(j == 0 || j == width) cout<<"|";
            //Creating snakes head with "O"
            if(i == y && j == x) cout<<"O";
            //Creating snakes food with "#"
            else if(i == fruitCordY && j == fruitCordX) cout<<"#";
            //Creating snakes body
            else{
                bool prTail = false;
                for(int k = 0; k < snakeTailLen; k++)
                {
                    if(snakeTailX[k] == j && snakeTailY[k] == i)
                    {
                        cout<<"o";
                        prTail = true;
                    }
                }
                if(!prTail) cout<<" ";
            }
        }
        cout<<endl;
    }
    //Creating bottom walls with "-"
    for(int i = 0; i < width + 2; i++) cout<<"-";
    cout<<endl;
    //Display player's score
    cout<<playerName<<"'s Score: "<<playerScore<<endl;
}

//Updating the Game state after each move
void UpdateGame()
{
    int prevX = snakeTailX[0];
    int prevY = snakeTailY[0];
    int prev2X, prev2Y;
    snakeTailX[0] = x;
    snakeTailY[0] = y;
    for(int i = 1; i < snakeTailLen; i++)
    {
        prev2X = snakeTailX[i];
        prev2Y = snakeTailY[i];
        snakeTailX[i] = prevX;
        snakeTailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (sDir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    }
    //Do snake touch wall 
    if(x >= width || x < 0 || y >= height || y < 0) 
        isGameOver = true;
    //Do snake touch tail
    for(int i = 0; i < snakeTailLen; i++)
    {
        if(snakeTailX[i] == x && snakeTailY[i] == y)
            isGameOver = true;
    }
    //Do snake touch food
    if(x == fruitCordX && y == fruitCordY)
    {
        playerScore += 10;
        fruitCordX = rand() % width;
        fruitCordY = rand() % height;
        snakeTailLen++;
    }
}

//Setting game difficulty
int Difficulty()
{
    int dfc, choice;
    cout<<"\nSET DIFFICULTY\n1: Easy\n2: Medium\n3: hard "
            "\nNOTE: if not chosen or pressed any other "
            "key, the difficulty will be automatically set "
            "to medium\nChoose difficulty level: "; 
    cin>>choice;
    switch(choice)
    {
        case '1':
            dfc = 50;
            break;
        case '2':
            dfc = 100;
            break;
        case '3':
            dfc = 150;
            break;
        default:
            dfc = 100;
            break;
    }
    return dfc;
}

//Getting user's input
void UserInput()
{
    //check if a key is pressed or not return non-zero value
    if(_kbhit())
    {
        //Pressed key
        switch(_getch())
        {
            case 'a':
                sDir = LEFT;
                break;
            case 'd':
                sDir = RIGHT;
                break;
            case 'w':
                sDir = UP;
                break;
            case 's':
                sDir = DOWN;
                break;
            case 'x':
                isGameOver = true;
                break;
        }
    }
}

int main()
{
    string playerName;
    cout<<"Enter your name: ";
    cin>>playerName;
    int dfc = Difficulty();
    GameInit();
    while(!isGameOver)
    {
        GameRender(playerName);
        UserInput();
        UpdateGame();
        //creating a delay for difficulty
        Sleep(dfc);
    }
    return 0;
}
