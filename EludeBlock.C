#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>

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
static int addr=3;

HANDLE hOut,hIn;

COORD M={0,0}; 

int score=-16;

char hit;



int main(){
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	hIn = GetStdHandle(STD_INPUT_HANDLE);
	
	puts("Ready");
	Sleep(1000);
	system("CLS");
	
	while(1){
		if(_kbhit()!=0){
			hit=_getch();
			
			if(hit=='a'){
				if(addr>0)addr--;
			}
			if(hit=='d'){
				if(addr<15)addr++;
			}
		}
		srand(clock());
		for(int i=15;i>0;i--){
			for(int j=0;j<16;j++){
				screen[j][i]=screen[j][i-1];
			}
		}
		score++;
		for(int j=0;j<16;j++){
			screen[j][0]=' ';
		}
		if(rand()%5!=0) {screen[rand()%16][0]='#';}
		Sleep(2);
		if(rand()%3!=0) {screen[rand()%16][0]='#';}
		Sleep(75);
		printf("--Score:%d--     Elude#  <Karyna>\n",score);
		for(int i=0;i<16;i++){
			for(int j=0;j<16;j++){
				if(j==addr&&i==15&&screen[j][i]=='#'){
					puts("Game Over.");
					Sleep(1000);
					exit(0);
				}
				if(j==addr&&i==15)
					screen[j][i]='A';
				putchar(screen[j][i]);
				if(j==addr&&i==15)
					screen[j][i]=32;
			}
			putchar('\n');
		}
		if(_kbhit()!=0){
			hit=_getch();
			
			if(hit=='a'){
				if(addr>0)addr--;
			}
			if(hit=='d'){
				if(addr<15)addr++;
			}
		}
		Sleep(75);
		puts("~~~~~~~~~~~~~~~~");
		puts("---Elude \'#\'---");
		SetConsoleCursorPosition(hOut,M);
	}
	CloseHandle(hOut);
	CloseHandle(hIn);
	return 0;
}
