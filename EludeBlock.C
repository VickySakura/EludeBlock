#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>

//  Screen character area.
static char screen[16][16]={
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32
};
// Initial player position.
static int addr=7;

// Standard input and output handle (just written)
HANDLE hOut,hIn;

// Its current purpose is to clear the screen.
COORD M={0,0}; 

// The game score, which is the number of lines the player passes.
int score=-16;

// A button pressed by the player
char hit;

// The player health
int health=1;

const char ico_1[4][4]={
32,32,32,32,
32,32,32,32,
32,35,35,32,
42,42,42,42
};
int tip;

int counter=0;

// Main Function
int main(){
	// Gets the standard input and output handle
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	hIn = GetStdHandle(STD_INPUT_HANDLE);
	
	// Game initialization (symbolic)
	// Give the player a second to get ready
	puts("Ready");
	_getch();
	Sleep(1000);
	system("CLS");
	
	while(1){
		// Detect button
		if(_kbhit()!=0){
			hit=_getch();
			//Move left
			if(hit=='a'){
				if(addr>0)addr--;
			}
			//Move right
			if(hit=='d'){
				if(addr<15)addr++;
			}
		}
		// Get the first random number.
		srand(clock());
		//The screen moves down 1 byte
		for(int i=15;i>0;i--){
			counter=0;
			for(int j=0;j<16;j++){
				counter++;
				srand(clock()|counter|score);
				screen[j][i]=screen[j][i-1];
				if(i<=2&&rand()%2==0){
					screen[j][i]=' ';
				}
			}
			if(rand()%8==0&&i<12){
				screen[0][i]=screen[2][i];
				screen[2][i]=screen[4][i];
				screen[4][i]=screen[6][i];
				screen[6][i]=screen[8][i];
				screen[8][i]=screen[10][i];
				screen[10][i]=screen[12][i];
				screen[12][i]=screen[14][i];
				screen[14][i]=screen[0][i];
			}
		}
		// (Player goes through a line)
		score++;
		// Initialize the first row.
		for(int j=0;j<16;j++){
			screen[j][0]='|';
		}
		// Generate the '#' character.
		{screen[rand()%16][0]='#';}
		if(rand()%20==0)  {
			tip=rand()%12;
			for(int i=0;i<4;i++){
				for(int j=0;j<4;j++){
					screen[j+tip][i]=ico_1[i][j];
				}
			}
		}
		// Screen character drawing.
		Sleep(50);
		srand(clock());
		if(rand()%8!=0) {screen[rand()%16][0]='#';}
		printf("--Score:%d--20fps Elude#  <Karyna>\n",score);
		for(int i=0;i<16;i++){
			for(int j=0;j<16;j++){
				if(j==addr&&i==15&&screen[j][i]=='$'){
					health++;
				}
				if(j==addr&&i==15&&!(screen[j][i]==' '||screen[j][i]=='|')){
					health--;
				}
				
				
				// Draw the player.
				if(j==addr&&i==15)
					screen[j][i]='A';
				putchar(screen[j][i]);
				
			}
			// Next line.
			putchar('\n');
		}
		srand(clock());
		if(rand()%8==0) {screen[rand()%16][0]='#';}
		// // Detect button
		if(_kbhit()!=0){
			hit=_getch();
			
			if(hit=='a'){
				if(addr>0)addr--;
			}
			if(hit=='d'){
				if(addr<15)addr++;
			}
		}
		printf("~~~~~~~~~~~~~~~~  HP:%d\n",health);
		puts("---Elude \'#\'---Press \'a\' to move left,\'d\' to move right");
		SetConsoleCursorPosition(hOut,M);// Repaint.
		// When the player death.
		if(health<=0){
			printf("Game Over,Score:%d   Thanks for playing.   \n",score);
			Sleep(2000);
			break;
		}
	}
	CloseHandle(hOut);
	CloseHandle(hIn);
	return 0;
}
