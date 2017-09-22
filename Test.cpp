#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>

#define BOARD_WIDTH  36
#define BOARD_HEIGHT 30

#define BOARD_START_X 5
#define BOARD_START_Y 5

#define BLOCK_START_X 10
#define BLOCK_START_Y 5

static int currentBlockIndex;
//static int curPosX, curPosY;
static int blockPosX, blockPosY;
static int rotation=0;

void set_cur(int x, int y);
int display_firstpage(void);
void Draw_GameBoard(void);
void InitfirstBlockpos(int x, int y);
void ChooseBlock(void);
int GetCurrentBlockNum(void);
void showBlock(char blockInfo[][4]);
void deleteBlock(char blockInfo[][4]);
int blockDown(void);	
void AddCurrentBlockInfoToBoard(void);
void DrawSolidBlocks(void);
int DetectCollision(int posInfoX, int posInfoY, char block[][4]);

static int board[BOARD_HEIGHT+1][(BOARD_WIDTH+4)/2]={0,};
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

void set_cur(int x, int y)
{

	printf("\033[%dd\033[%dG", y, x);
	fflush(stdout);
}

int display_firstpage(void)
{
	
	system("clear");

	set_cur(18,5);
	printf("Hong's Tetris Game"); 
	set_cur(9,7);
        printf("    =============================    "); 
	set_cur(11,10);
        printf("Please Enter '1' Key to Start!"); 
	set_cur(9,15);
      	printf("=====================================");
	set_cur(22,17); 
       	printf("J : Left"); 
	set_cur(22,18);
       	printf("L : Right");
	set_cur(22,19); 
	printf("I : Up"); 
	set_cur(22,20);
	printf("K : Soft Down"); 
	set_cur(22,21);
	printf("A : Hard Down"); 
	set_cur(9,24); 
        printf("=====================================\n"); 
	
	
	return 0;
	
}

void Draw_GameBoard(void)
{
	int x,y;
	
	system("clear");

	for(y=0; y<=BOARD_HEIGHT; y++)
	{	
		set_cur(BOARD_START_X ,BOARD_START_Y+y);
		printf("■");
		
	}
	for(y=0; y<=BOARD_HEIGHT; y++)
	{
		set_cur(BOARD_START_X + (BOARD_WIDTH+2) ,BOARD_START_Y+y);	
		
			printf("■");
		
	}
	for (x = 1; x <= BOARD_WIDTH/2; x++)
	{
		set_cur(BOARD_START_X+x*2, BOARD_START_Y+BOARD_HEIGHT); 
		printf("■");
	}
	printf("\n\n\n");


	for(y=0; y<BOARD_HEIGHT; y++)
	{
		board[y][BOARD_START_X] =1;
		board[y][(BOARD_WIDTH+2)/2] =1;
	}
	for(x=0; x<(BOARD_WIDTH+4)/2; x++)
	{
		board[BOARD_HEIGHT][x] =1;
		
	}	
	
}

void InitfirstBlockpos(int x, int y)
{
	blockPosX = x;
	blockPosY = y;

	set_cur(x,y);
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

void showBlock(char blockInfo[][4])
{
	int x,y;
	for(y=0; y<4; y++)
	{
		for(x=0; x<4;x++)
		{
			set_cur(blockPosX+x*2,blockPosY+y);
			if(blockInfo[y][x] ==1)
				printf(" ■ ");
		}
		
	}

	
}
void deleteBlock(char blockInfo[][4])
{
	int x,y;
	for(y=0; y<4; y++)
	{
		for(x=0; x<4;x++)
		{
			set_cur(blockPosX+x*2,blockPosY+y);
			if(blockInfo[y][x] ==1)
				printf("   ");
		}
		
	}
}
int blockDown(void)	
{
	
	if(!DetectCollision(blockPosX, blockPosY+1, block[GetCurrentBlockNum()]))
	{
		AddCurrentBlockInfoToBoard();
		return 0;
	}
	else
	{	
		deleteBlock(block[GetCurrentBlockNum()]);
		blockPosY+=1;
		set_cur(blockPosX,blockPosY);
		showBlock(block[GetCurrentBlockNum()]);
		return 1;
	}
}
void AddCurrentBlockInfoToBoard(void)
{
	int x,y;
	int arrcurX;
	int arrcurY;

	for(y=0; y<4; y++)
	{
		for(x=0; x<4; x++)
		{
			arrcurX = blockPosX/2;
			arrcurY = blockPosY;
			if(block[GetCurrentBlockNum()][y][x] ==1){
				board[arrcurY+y][arrcurX+x]=1;
			}
		}
	}
}
void DrawSolidBlocks(void)
{	
	int x,y;
	int curpos_x;
	int curpos_y;

	for(y=0; y<BOARD_HEIGHT; y++)
	{
		for(x=0; x<BOARD_WIDTH/2;x++)
		{
			curpos_x = x*2 + BOARD_START_X; 
			curpos_y = y +BOARD_START_Y;
			set_cur(curpos_x, curpos_y);
			
			if(board[y][x]==1)
				printf("■");
			else
				printf("  ");
		}
	}

}

int DetectCollision(int posInfoX, int posInfoY, char block[][4])
{
	int x,y;
	int arrX = (blockPosX)/2;
	int arrY = blockPosY;
	
	for(x=0; x<4; x++)
	{
		for(y=0; y<4; y++)
		{
			if(block[y][x] ==1 && board[arrY+y][arrX+x] ==1)
				return 0;
		}
	}
	return 1;

}

int main(void)
{
	//int x, y;

	
	initscr();
	
	display_firstpage();
	sleep(2);
	
	Draw_GameBoard();
	
	while(1)
	{
		InitfirstBlockpos(BLOCK_START_X, BLOCK_START_Y);

		ChooseBlock();

		while(1)
		{
			if(blockDown()==1)
			{
				blockDown();
				sleep(1);
	 		}
			else
				break;
		}
		refresh();
		DrawSolidBlocks();
				       
	   	
		
	//for(x=0; x<100; x++)
	//{
		//for(y=0; y<100; y++)
			//set_cur(x,y);
	
	}
	endwin();
	
	return 0;
}
