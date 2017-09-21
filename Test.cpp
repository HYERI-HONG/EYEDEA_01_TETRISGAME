#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>

#define BOARD_WIDTH  40
#define BOARD_HEIGHT 30

#define BOARD_START_X 10
#define BOARD_START_Y 5

#define BLOCK_START_X 30
#define BLOCK_START_Y 6
int currentBlockIndex;
int rotation=0;

void move_cur(int x, int y);

static int  Board[BOARD_HEIGHT+1][BOARD_WIDTH+2]={0,};
char block[28][4][4]= 
	{
		{
			{ 0,0,0,0 },
			{ 1,0,0,0 },
			{ 1,1,1,0 },
			{ 0,0,0,0 } },
		{
			{ 0,0,1,0 },
			{ 0,0,1,0 },
			{ 0,1,1,0 },
			{ 0,0,0,0 } },
		{
			{ 1,1,1,0 },
			{ 0,0,1,0 },
			{ 0,0,0,0 },
			{ 0,0,0,0 } },
		{
			{ 1,1,0,0 },
			{ 1,0,0,0 },
			{ 1,0,0,0 },
			{ 0,0,0,0 } },
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 1, 0 },
			{ 1, 1, 1, 0 },
			{ 0, 0, 0, 0 } },
		{
			{ 0, 1, 1, 0 },
			{ 0, 0, 1, 0 },
			{ 0, 0, 1, 0 },
			{ 0, 0, 0, 0 } },
		{
			{ 1, 1, 1, 0 },
			{ 1, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 } },
		{
			{ 1, 0, 0, 0 },
			{ 1, 0, 0, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 0, 0, 0 } },
		{
			{ 0, 0, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 1, 1, 1, 0 },
			{ 0, 0, 0, 0 } },
		{
			{ 0, 0, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 1, 0, 0 } },
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 1, 1, 1, 0 },
			{ 0, 1, 0, 0 } },
		{
			{ 0, 0, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 1, 1, 0 },
			{ 0, 1, 0, 0 } },
		{
			{ 0, 1, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 1, 0, 0 } },
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 1, 1, 1, 1 },
			{ 0, 0, 0, 0 } },
		{
			{ 0, 1, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 1, 0, 0 } },
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 1, 1, 1, 1 },
			{ 0, 0, 0, 0 } },
		{
			{ 1, 1, 0, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 } },
		{
			{ 1, 1, 0, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 } },
		{
			{ 1, 1, 0, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 } },
		{
			{ 1, 1, 0, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 } },
		{
			{ 0, 0, 0, 0 },
			{ 0, 1, 1, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 0, 0, 0 } },
		{
			{ 0, 1, 0, 0 },
			{ 0, 1, 1, 0 },
			{ 0, 0, 1, 0 },
			{ 0, 0, 0, 0 } },
		{
			{ 0, 0, 0, 0 },
			{ 0, 1, 1, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 0, 0, 0 } },
		{
			{ 0, 1, 0, 0 },
			{ 0, 1, 1, 0 },
			{ 0, 0, 1, 0 },
			{ 0, 0, 0, 0 } },
		{
			{ 0, 0, 0, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 1, 1, 0 },
			{ 0, 0, 0, 0 } },
		{
			{ 0, 0, 1, 0 },
			{ 0, 1, 1, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 0, 0, 0 } },
		{
			{ 0, 0, 0, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 1, 1, 0 },
			{ 0, 0, 0, 0 } },
		{
			{ 0, 0, 1, 0 },
			{ 0, 1, 1, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 0, 0, 0 } },
	
	};

void move_cur(int x, int y)
{
	printf("\033[%dd\033[%dG", y, x);
	fflush(stdout);
}

int display_firstpage(void)
{
	
	system("clear");

	move_cur(18,5);
	printf("Hong's Tetris Game"); 
	move_cur(9,7);
        printf("    =============================    "); 
	move_cur(11,10);
        printf("Please Enter '1' Key to Start!"); 
	move_cur(9,15);
      	printf("=====================================");
	move_cur(22,17); 
       	printf("J : Left"); 
	move_cur(22,18);
       	printf("L : Right");
	move_cur(22,19); 
	printf("I : Up"); 
	move_cur(22,20);
	printf("K : Soft Down"); 
	move_cur(22,21);
	printf("A : Hard Down"); 
	move_cur(9,24); 
        printf("=====================================\n"); 
	
	
	return 0;
	
}

void Draw_GameBoard(void)
{
	int x,y;
	
	system("clear");
	
	move_cur(20, 2);
	printf("Let's Play the Game!!");

	for(y=0; y<=BOARD_HEIGHT; y++)
	{	
		move_cur(BOARD_START_X ,BOARD_START_Y+y);
		if(y==BOARD_HEIGHT)
			printf("┗");
		else
			printf("┃");	
	}
	for(y=0; y<=BOARD_HEIGHT; y++)
	{
		move_cur(BOARD_START_X + (BOARD_WIDTH+1) ,BOARD_START_Y+y);	
		if(y==BOARD_HEIGHT)
			printf("┛");
		else
			printf("┃");	
	}
	for (x = 1; x <= BOARD_WIDTH; x++)
	{
		move_cur(BOARD_START_X+x, BOARD_START_Y+BOARD_HEIGHT); 
		printf("━");
	}
	printf("\n\n\n");


	for(y=0; y<BOARD_HEIGHT; y++)
	{
		Board[y][BOARD_START_X] =1;
		Board[y][BOARD_WIDTH+1] =1;
	}
	for(x=0; x<BOARD_WIDTH+2; x++)
	{
		Board[BOARD_HEIGHT][x] =1;
		
	}	
	
}

void ChooseBlock(void)
{
	srand((unsigned int)time(NULL));
	currentBlockIndex = (rand() % 7)* 4;
	
}
int GetCurrentBlockNum(void)
{
	return currentBlockIndex + rotation;
}
void showFirstBlock(int Index, int a, int b)
{
	int x,y;
	for(y=0; y<4; y++)
	{
		for(x=0; x<4;x++)
		{
			move_cur(a+x *2, b+y);
			if(block[Index][y][x] ==1)
				printf("■");
			else
				printf(" ");
		}
		
	}
	printf("\n");

	
}

int main(void)
{
	initscr();
	
	display_firstpage();
	sleep(3);
	Draw_GameBoard();

	ChooseBlock();


	showFirstBlock(currentBlockIndex,BLOCK_START_X,BLOCK_START_Y);
	showFirstBlock(currentBlockIndex,30,15);
	
	
	endwin();
	
	return 0;
}
