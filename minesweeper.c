// Santosh Pingali
// minesweeper.c 

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct {
	int display;
	char cells;
} newgrid;

newgrid grid[11][11];
newgrid mines[11][11];

int clearZero(int i, int j){
		if(i >= 0 && i <= 9 && j >= 0 && j <= 9){
			if(mines[i][j].display == 0){
				grid[i][j].display = 0;
				mines[i][j].display = 1;
				if(mines[i][j].cells == 0){
					clearZero(i+1,j);
					clearZero(i-1,j);
					clearZero(i,j-1);
					clearZero(i,j+1);
					clearZero(i+1,j-1);
					clearZero(i-1,j-1);
					clearZero(i+1,j+1);
					clearZero(i-1,j+1);
				}
			}
		}
	}

int main(int argc, char *argv[]){
	
	// declare program variables
	srand(time(NULL));
	int i;
	int j;
	int x;
	int coord1;
	int coord2;
	int play = 1;

	
	// mines of 12 on the playing field
	x = 12;
	while(x > 0){
		i = rand() % 10;
		j = rand() % 10;
		if(mines[i][j].cells != '*'){
			mines[i][j].cells = '*';
			x--;
		}
	}
	
	// create array
	for(i = 0; i < 11; i++){
		for(j = 0; j < 11; j++){
			grid[i][j].cells = '-';
			grid[i][j].display = 1;
		}
	}
	
	
	// check for mines 
	x = 0;
	for(i = 0; i < 11; i++){
		for(j = 0; j < 11; j++){
			if(i == 0 && j == 0 && mines[i][j].cells != '*'){
				if(mines[i][j+1].cells == '*'){
					x++;
				}
				if(mines[i+1][j].cells == '*'){
					x++;
				}
				if(mines[i+1][j+1].cells == '*'){
					x++;
				}
				mines[i][j].cells = x;
				mines[i][j].display = 0;
			}
			else if(i == 0 && mines[i][j].cells != '*'){
				if(mines[i][j-1].cells == '*'){
					x++;
				}
				if(mines[i+1][j-1].cells == '*'){
					x++;
				}
				if(mines[i+1][j+1].cells == '*' ){
					x++;
				}
				if(mines[i+1][j].cells == '*'){
					x++;
				}
				if(mines[i][j+1].cells == '*'){
					x++;
				}
				mines[i][j].cells = x;
				mines[i][j].display = 0;
			}
			else if(j == 0 && mines[i][j].cells != '*'){
				if(mines[i-1][j].cells == '*'){
					x++;
				}
				if(mines[i-1][j+1].cells == '*'){
					x++;
				}
				if(mines[i+1][j+1].cells == '*'){
					x++;
				}
				if(mines[i][j+1].cells == '*'){
					x++;
				}
				if(mines[i+1][j].cells == '*'){
					x++;
				}
				mines[i][j].cells = x;
				mines[i][j].display = 0;
			}
			else if(mines[i][j].cells != '*'){
				if(mines[i-1][j-1].cells == '*'){
					x++;
				}
				if(mines[i][j-1].cells == '*'){
					x++;
				}
				if(mines[i-1][j].cells == '*') {
					x++;
				}
				if(mines[i][j+1].cells == '*'){
					x++;
				}
				if(mines[i+1][j].cells == '*'){
					x++;
				}
				if(mines[i+1][j+1].cells == '*'){
					x++;
				}
				if(mines[i-1][j+1].cells == '*'){
					x++;
				}
				if(mines[i+1][j-1].cells == '*'){
					x++;
				}
				mines[i][j].cells = x;
				mines[i][j].display = 0;
			}
			x = 0;
		}
	}
	
	// display the 10x10 grid
	printf("  0 1 2 3 4 5 6 7 8 9\n");
	for(i = 0; i < 10; i++){
		for(j = 0; j < 10; j++){
			if(j == 0){
				printf("%d ",i);
			}
			printf("%c ",grid[i][j].cells);
		}
		printf("\n");
	}
	// get coordinates from the user. If they hit a mine end the game. 
	int counter;
	while(play == 1){
		printf("Enter Coordinate 1(x axis)");
		scanf("%d",&coord1);
		printf("Enter Coordinate 2(y axis)");
		scanf("%d",&coord2);
		if(coord1 || coord2 > 10){
			printf("Out of bounds. Try Again\n ");
			Enter Coordinate 1(x axis) ");
			scanf("%d",&coord1);
			printf("Enter Coordinate 2(y axis)");
			scanf("%d",&coord2);
		}
		if(mines[coord2][coord1].cells == 0){
			i = 0;
			if(coord2 == 0 && coord1 == 0){
				while(i == 0){
					mines[coord2+1][coord1].display = 1;
					grid[coord2+1][coord1].display = 0;
					mines[coord2][coord1+1].display = 1;
					grid[coord2][coord1+1].display = 0;
					mines[coord2+1][coord1+1].display = 1;
					grid[coord2+1][coord1+1].display = 0;
					i = mines[coord2][coord1+1].cells;
					if(i == 0){
						coord1++;
					}
					if(!play && (x == 12)){
						printf("You Survived, You Win!");
						play = 0;
					}
				}
			}
		}
		// call function
		clearZero(coord2,coord1);
		
		grid[coord2][coord1].display = 0;
		mines[coord2][coord1].display = 1;
		// show the grid after player move 
		printf("  0 1 2 3 4 5 6 7 8 9\n");
		for(i = 0; i < 10; i++){
			for(j = 0; j < 10; j++){
				if(j == 0){
					printf("%d ",i);
				}
				if(grid[i][j].display == 1){
					printf("%c ",grid[i][j].cells);
				}
				if(mines[i][j].display == 1){
					if(mines[i][j].cells == '*'){
						printf("%c ",mines[i][j].cells);
					}
					else{
						printf("%d ",mines[i][j].cells);
					}
				}
			}
			printf("\n");
		}
		if(mines[coord2][coord1].cells == '*'){
			play = 0;
			printf("Clicked a mine. You lost.\n");
			break;
		}
		else {
			int count = 0;
			for(i = 0; i < 10; i++){
				for(j = 0; j < 10; j++){
					if(mines[i][j].cells != '*'){
						count += mines[i][j].display;
					}
				}
			}
			if(count == 88){
				play = 0;
				printf("Hooray!!! You Won!!!!!");
			}
		}
	}
	return 0;
}