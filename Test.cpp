#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>

#define BOARD_WIDTH  40
#define BOARD_HEIGHT 30

#define BOARD_START_X 10
#define BOARD_START_Y 5

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

void DrawGameBoard(void)
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
	refresh();
}




int main(void)
{
	initscr();
	
	display_firstpage();
	sleep(5);
	DrawGameBoard();
	
	
	endwin();
	
	return 0;
}
