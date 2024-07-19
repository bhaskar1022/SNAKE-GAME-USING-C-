#include<iostream>
#include<windows.h>
#include<conio.h>
using namespace std;
#define width 50
#define height 20
int snakeTailX [100],snakeTailY [100];
int x, y, fruitcordX, fruitcordY,score,snakeTailLen;

enum snakeDirection{
	STOP = 0, LEFT, RIGHT, UP, DOWN 
};

snakeDirection sDir;
bool isGameOver;

void Gameinit()
{
	isGameOver = false;
	sDir = STOP;
	x = width / 2;
	y= height / 2;
	fruitcordX = rand() % width;
	fruitcordY = rand() % height;
	score = 0;	
}

void GameRender(string playerName)//create board game or game rendering
{
	system("cls");
	for(int i = 0; i < width+2; i++)
		cout<<"*";
	cout<<"\n";
		for(int i = 0; i < height; i++)
		{
			for(int j = 0;j <= width; j++)
			{
				if(j == 0 || j == width)//creating slide wallls
				cout<<"*";
				if(i == y && j == x)//creating snake head with 'O'
				cout<<"O";
				else if(i == fruitcordY && j== fruitcordX)//create snakes food
				cout<<"#";
				else //create snake head with 'O'
				{
					bool prTail = false;
					for(int k = 0; k < snakeTailLen; k++)
					
					{
						if(snakeTailX[k] == j && snakeTailY[k] == i)
						{
							cout<<"o";
							prTail = true;
						}
					}
					if(!prTail)
					cout<<" ";
				}
			}
			cout<<"\n";
		}
	for(int i=0;i < width +2; i++)//create bottom walls
		cout<<"*";
	cout<<"\n";
	cout<<playerName<<"s Score: "<<score<<"\n";
}

void UpdateGame()//updating game state
{
	int prevX = snakeTailX[0];
	int prevY = snakeTailX[0];	
	int prev2X,prev2Y;
	snakeTailX[0] = x;
	snakeTailY[0] = y;
	
	for(int i=1; i < snakeTailLen; i++)
	{
		prev2X = snakeTailX[i];
		prev2Y = snakeTailY[i];
		
		snakeTailX[i] = prevX;
		snakeTailY[i] = prevY;
		
		prevX = prev2X;
		prevY = prev2Y;
	}
	
	switch(sDir)
	{
	 case LEFT: x--; 
        break; 
    case RIGHT: x++; 
        break; 
    case UP:  y--; 
        break; 
    case DOWN: y++; 
        break;
	}
	if( x >= width || x < 0 || y >=height || y < 0)//check collison with walls
	isGameOver =true;
	for(int i = 0; i < snakeTailLen; i++)//checks collision with walls
	{
		if(snakeTailX[i] == x && snakeTailY[i] == y)
		isGameOver =true;
	}
	if(x == fruitcordX && y == fruitcordY)//snake collision checking with food
	{
		score +=5;
		fruitcordX =rand() % width;
		fruitcordX =rand() % height;
		snakeTailLen++;
	}
}
int setDifficult()//set game difficult level
{
	int dfc,choice;
	cout<<"\nSET DIFFICULTY\n1: Easy\n2: Medium\n3: hard "
            "\nNOTE: if not chosen or pressed any other "
            "key, the difficulty will be automatically set "
            "to Easy\nChoose difficulty level: "; 
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
            	default :
            		dfc = 50;
			}
			return dfc;
}
void UserInput()//handling user input
{
	if(_kbhit())//ckecks key pressed or not
	{
		switch(_getch())
		{
		case '4':
			sDir = LEFT; 
            break; 
        case '6': 
            sDir = RIGHT; 
            break; 
        case '8': 
            sDir = UP; 
            break; 
        case '2': 
            sDir = DOWN; 
            break; 
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
	cout<<"Enter Player Name: ";
	cin>>playerName;
	int dfc = setDifficult();
	Gameinit();
	while(!isGameOver)
	{
		GameRender(playerName);
		UserInput();
		UpdateGame();
		Sleep(dfc);//create some delay choose difficulty
	}
	return 0;
}
