/*

ITC Lab Assignment/Project: Pacman Game

Memebers:
Nakash		17k-3641
Rohit		17k-3624
Adnan		17k-3615
Ali Ahmed	17k-3612

*/


#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include "./modules.h" // this contains map grid and enemey coordinates

//map[24][34];
//enemy_coords[4][50][2];


/*
Global Variables
*/
//user
int score = 0;

//enemy
int enemies;
int enemy_pos[4] = {0};
int enemy_max_pos[4] = {21, 20, 16, 23};
int touched = 0;
//for coloring
HANDLE hConsole;

//Pacman Structure
typedef struct
{
	int xpos;
	int ypos;
}
pacman;

/*
Prototypes
*/


void draw(pacman user, pacman *enemy);
void update(pacman *user, pacman *enemy);
void initialize(pacman *user, pacman *enemy, char m[][L]); 
int indexOf(int arr[2], int (*p)[2], int length);
void inputLevel(void);


/*
Main Code
*/

int main(){
	
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	pacman user;

	char try;
	do{
		inputLevel();	

		pacman enemy[enemies];
		initialize(&user, enemy, map);
		while(1){
			draw(user, enemy);
			Sleep(85);
			update(&user, enemy);
			
			if(score == 173 || touched == 1){
				break;
			}
			
		}
		
		if(touched == 1){
			SetConsoleTextAttribute(hConsole, 12);
			printf("\nSorry! Your lost the game.");
		}
		else if(score == 173){
			SetConsoleTextAttribute(hConsole, 14);
			printf("\nHurray!! You won the game.");
		}
		printf("\n\nPress any key to restart or Press N to exit.");
		try = getch();
		system("cls");
		SetConsoleTextAttribute(hConsole, 15);
	}while(try != 'n');
}



/*
Functions...
*/



void inputLevel(){
	int level;
	
	printf("%c Pacman.c - Pacman Game %c", 2, 2);
	printf("\n\n1. Beginner\n2. Moderate\n3. Expert\n\n");
	printf("\nEnter Level: ");
	scanf("%d", &level);
	
	switch(level){
		case 1:
			enemies = 1;
			break;
		case 2:
			enemies = 2;
			break;
		case 3:
			enemies = 4;
			break;
		default:
			enemies = 1;
			break;
	}
}

void draw(pacman user, pacman *enemy){
	system("cls");
	
	int i, j;
	int on_enemy = 0;
	for(i = 0; i < H; i ++){
		for(j = 0; j < L; j++){
			on_enemy = 0;
			int k;
			for(k = 0; k < enemies; k ++){
				if(i == enemy[k].ypos && j == enemy[k].xpos){
					SetConsoleTextAttribute(hConsole, 7);
					on_enemy = 1;
					printf("%c", 2);
				}
			}
			
			if(on_enemy == 1)
				continue;
			
			if(i == user.ypos && j == user.xpos){
				SetConsoleTextAttribute(hConsole, 14);
				if((user.xpos + user.ypos )%2 == 0)
					printf("O"); 
				else
					printf("C");
				if(map[i][j] == '.'){
					map[i][j] = ' ';
					score ++;
				}
			}
			else{
				if(map[i][j] == '.')
					SetConsoleTextAttribute(hConsole, 6);
				else
					SetConsoleTextAttribute(hConsole, 9);
				printf("%c", map[i][j]);
			}
		}
		printf("\n");
	}
	//printf("\n[Score: %d]", score);
}

int returnOne(int x){
	if(x > 0)
		return 1;
	else if(x < 0)
		return -1;
	else
		return 0;
}

void update(pacman *user, pacman *enemy){
	// If keyboard key press, then getch command will be executed..
	static char arrow;
	if(kbhit()){
		arrow = getch();
	}
	if(arrow != 32){
		switch(arrow){
			case 'w':
			case 72:
				user->ypos -= 1;
				if(map[user->ypos][user->xpos] !=  ' ' && map[user->ypos][user->xpos] !=  '.' ){
					user->ypos += 1;
				}
				break;
			case 's':
			case 80:
				user->ypos += 1;
				if(map[user->ypos][user->xpos] !=  ' ' && map[user->ypos][user->xpos] !=  '.' ){
					user->ypos -= 1;
				}
				break;
			case 'a':
			case 75:
				user->xpos -= 1;
				if(map[user->ypos][user->xpos] !=  ' ' && map[user->ypos][user->xpos] !=  '.' ){
					user->xpos += 1;
				}
				break;
			case 'd':
			case 77:
				user->xpos += 1;
				if(map[user->ypos][user->xpos] !=  ' ' && map[user->ypos][user->xpos] !=  '.' ){
					user->xpos -= 1;
				}
				break;
		}
	}
	
	int i;
	//Checking if new position of user interferes with enemy.
	for(i = 0; i < enemies; i ++){
		if(user->ypos == enemy[i].ypos && user->xpos == enemy[i].xpos){
			touched = 1;
		}
	}
	
	int xpos, ypos;
	int subset[2];
	
	//Moving Enemies
	for(i = 0; i < enemies; i++){
		xpos = enemy_coords[i][(enemy_pos[i])%enemy_max_pos[i]][0];
		ypos = enemy_coords[i][(enemy_pos[i])%enemy_max_pos[i]][1];
		enemy[i].xpos = enemy[i].xpos + returnOne(xpos-enemy [i].xpos);
		enemy[i].ypos = enemy[i].ypos + returnOne(ypos-enemy[i].ypos);
		if(enemy[i].xpos == xpos && enemy[i].ypos == ypos)
			enemy_pos[i] ++;
		// checks if new position of enemy interferes with user.
		if(enemy[i].xpos == user->xpos && enemy[i].ypos == user->ypos){
			touched = 1;
			break;
		}
	}
	
}

void initialize(pacman *user, pacman *enemy, char m[][L]){
	
	score = 0;
	
	//Index of enemy position inside enemy coordinates array.
	enemy_pos[0] = 0;
	enemy_pos[1] = 0;
	enemy_pos[2] = 0;
	enemy_pos[3] = 0;
	
	touched = 0;
	
	//initialzing user pos
	user->xpos = 15;
	user->ypos = 17;
	
	// initializing enemy x and y pos
	
	enemy[0].xpos = 14;
	enemy[0].ypos = 10;
	
	if(enemies > 1)
		enemy[1].xpos = 14;
		enemy[1].ypos = 10;
	
	if(enemies > 2){
		enemy[2].xpos = 10;
		enemy[2].ypos = 10;
		
		enemy[3].xpos = 12;
		enemy[3].ypos = 10;
	}
		
	
	// Food placement in map or grid
	int i,j;
	for(i = 0; i < H; i ++){
		for(j = 0; j < L; j ++){
			if(m[i][j] == ' '){
				if((i+j)%2 == 0){
					m[i][j] = '.';
				}
			}
		}
	}
}

