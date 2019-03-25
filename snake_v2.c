#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>



// Sercan BAYRAMBEY  https://github.com/sercanbayrambey/C-Snake-Game

void gameLoop();
void draw();
void FoodGenerator();
void Start();
int random();
void Movement();
char GetKey();
void Reset();
void IsGameOver();
void hidecursor();

enum Direction
{
	UP,DOWN,LEFT,RIGHT,NONE
};


struct Food
{
	int x,y;
}food;

struct Snake
{
	int tailX[150],tailY[150],headX,headY;
	int lenght;
	char head[1];
}snake;

int isPrinted=0,isGameOver=0;
int direction;
const int FPS=30;

int main()
{
	Start();
}

void Start()
{
	hidecursor();
	system("color 70");
	isGameOver = 0;
	srand(time(NULL));
	FoodGenerator();
	snake.lenght = 10;
	snake.headX = 10;
	snake.headY = 10;
	isPrinted = 0;
	draw();
	direction = UP;
	
		while(1)
	{
		gameLoop();
	}
}


void draw()
{
	int i,j,k,m;
	system("cls");
	
	for(i=0;i<20;i++){
		for(j=0;j<50;j++)
		{
			isPrinted = 0;
		 	for(k=0;k<=snake.lenght;k++){
		
				if( ( (i==0 && j!=0 && j!=49) || (i==19 && j!=0 && j!= 49) ) && isPrinted == 0  )
					printf("-");
				else if( (j==49 || j==0) && isPrinted == 0)
					printf("|");
				else if(j==food.x && i==food.y && isPrinted == 0)
					printf("O");
				else if(j==snake.headX && i == snake.headY && isPrinted == 0)	
					printf("%c",snake.head[1]);
				
				else if(j==snake.tailX[k] && i==snake.tailY[k] && k!=0)
				{
					printf("\b");
					printf("*");					
				}
				
				else if (isPrinted==0){
						printf(" ");
				}
					
					
				isPrinted = 1;
			}
		}	
		
		printf("\n");	
	}
		
		printf("\n");
		printf("Snake: y= %d x= %d",snake.headY,snake.headX);
		printf("\nScore: %d",snake.lenght-5);
	
}


void gameLoop()
{
	IsGameOver();
	int i,j,tempy[150],tempx[150];
	tempy[0] = snake.headY;
	tempx[0] = snake.headX;
	Movement();
	
		 
	if(direction == UP){
		snake.head[1] = '^';
		if(snake.headY != 1)
				snake.headY--;
		else
				snake.headY = 18;
	}
			
	else if(direction == DOWN){
		snake.head[1] = 'v';
			if(snake.headY != 18)
				snake.headY += 1;
			else 
				snake.headY = 1;
	}		
			
	else if (direction == LEFT){
		snake.head[1] = '<';
			if(snake.headX != 1)
				snake.headX -= 1;
			else 
				snake.headX = 48;
	}		//LEFT
			
			
			//RIGHT
			
	else if(direction == RIGHT){
		snake.head[1] = '>';
		if(snake.headX != 48)
				snake.headX += 1;
			else 
				snake.headX = 1;
	}

			
			
	  //Follow Snake's Head
		for(i=1;i<=snake.lenght;i++){
				tempy[i] = snake.tailY[i]; 
				tempx[i] = snake.tailX[i];
				snake.tailY[i] = tempy[i-1];
				snake.tailX[i] = tempx[i-1];
								
				}	

		
	//Is Take Food?
	if(food.x == snake.headX && food.y == snake.headY)
	{
		snake.lenght++;
		FoodGenerator();
	}
	
	
	draw();
	Sleep(1000/FPS);
	
}


void FoodGenerator()
{
	food.x = random(1,48);	
	food.y = random(1,18);
}

char getKey()
{
	int ch;
	 if ( _kbhit() ) // If something pressed in keyboard
	 {
       ch = _getch();
	if(ch==100 || ch == 68)
	return 'D';
	else if(ch==97 || ch==65)
	return 'A';
	else if(ch==87 || ch==119)
	return 'W';
	else if(ch==115 ||ch==83)
	return 'S';
	else
	return '-';	
	 }
	
}

void Movement()
{
	int i,tempy,tempx;
	char key = getKey();
	if(key == 'W')
			direction = UP;
	else if(key == 'S')
			direction = DOWN;
	else if(key == 'A')	
			direction = LEFT;	
	else if(key == 'D')
			direction = RIGHT;			
	
}


void IsGameOver()
{
	int i;
	for(i=1;i<=snake.lenght;i++)
	{
		if(snake.headX == snake.tailX[i] && snake.headY==snake.tailY[i])
		{
			isGameOver = 1;
		}
	}
	
	if(isGameOver==1)
	{
	Reset();
	isGameOver = 0;
	Start();
	}
	
}

void Reset()
{
	int i;
	for(i=0;i<=snake.lenght;i++)
	{
		snake.tailX[i] = 0;
		snake.tailY[i] = 0;
	}
	direction = NONE;
	system("color 74");
	Sleep(1000);
	system("cls");
	printf("\t \t \t \n\n\n GAME OVER , RESTARTING");
	Sleep(3000);
}

void hidecursor() // THIS FOR HIDE CONSOLE CURSOR
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}


int random(int min, int max){

   return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}
