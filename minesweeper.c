#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

typedef struct Player{
	char name[30];
	int level;
} player;

typedef struct MineSweeper{
	char showGround[50][50];
	char hideGround[50][50];
	player *p;
	int mine_count,unvisited;
	int mark_pos[50][2],mar_ind; 
	int x_dim, y_dim;
} minesweeper;

void play(minesweeper*);
void createMineGround(minesweeper*);
void getNeighborCount(minesweeper*,int,int);
int checkBoundary(int,int);
int isWinner(minesweeper*);
int markTheBlock(char[][50],int,int);
void drawHideGround(minesweeper*);
void drawTheGround(minesweeper*);
void checkTheMark(minesweeper*);
void constructor(minesweeper*);
void clearGround(minesweeper*);
void clearHideGround(minesweeper*);
int checkBomb(char[][50],int,int);
void updateNeighborCount(char[][50],int,int);
void hitTheBlock(minesweeper*,int,int);
void del(int[][2],int,int,int);
void ins(int[][2],int,int,int);
void finalDraw(minesweeper*);
int breakTheBlock(minesweeper*,int,int);

void updateNeighborCount(char hideMap[][50],int x,int y){
	int count;
	
	if(checkBomb(hideMap,x,y)){
		count = hideMap[x][y] - '0';
		count++;
		hideMap[x][y] = count+'0';
	}
}

int checkBomb(char hideMap[][50], int x, int y){
	if(hideMap[x][y] == '@'){
		return 0;
	}
	else{
		return 1;
	}
}

int checkBoundary(int pos,int dim){
	return 0<=pos && pos<=dim-1;
}

void getNeighborCount(minesweeper *ms,int x,int y){
	int new_x, new_y;
	
	if(checkBoundary(x-1,ms->x_dim)){
		new_x = x-1;
		
		if(checkBoundary(y-1,ms->y_dim)){
			updateNeighborCount(ms->hideGround,new_x,y-1);			
		}
		
		if(checkBoundary(y+1,ms->y_dim)){
			updateNeighborCount(ms->hideGround,new_x,y+1);	
		}
		
		updateNeighborCount(ms->hideGround,new_x,y);
	}
	
	if(checkBoundary(x+1,ms->x_dim)){
		new_x = x+1;
		
		if(checkBoundary(y-1,ms->y_dim)){
			updateNeighborCount(ms->hideGround,new_x,y-1);	
		}
		
		if(checkBoundary(y+1,ms->y_dim)){
			updateNeighborCount(ms->hideGround,new_x,y+1);	
		}
		
		updateNeighborCount(ms->hideGround,new_x,y);
	}
	
	if(checkBoundary(y-1,ms->y_dim)){
		updateNeighborCount(ms->hideGround,x,y-1);	
	}
	
	if(checkBoundary(y+1,ms->y_dim)){
		updateNeighborCount(ms->hideGround,x,y+1);	
	}
}

void createMineGround(minesweeper *ms){
	int count = 0, x, y;
	
	while(count<ms->mine_count){
		srand(time(0));
		x = rand()%ms->x_dim;
		y = rand()%ms->y_dim;
		
		if(ms->hideGround[x][y] == '0'){
			ms->hideGround[x][y] = '@';
			getNeighborCount(ms,x,y);
			count++;
		}
	}
}

void clearHideGround(minesweeper *ms){
	int i,j;
	
	for(i=0;i<ms->x_dim;i++){
		for(j=0;j<ms->y_dim;j++){
			ms->hideGround[i][j] = '0';
		}
	}
}

void clearGround(minesweeper *ms){
	int i,j;
	
	for(i=0;i<ms->x_dim;i++){
		for(j=0;j<ms->y_dim;j++){
			ms->showGround[i][j] = '.';
		}
	}
}

void drawHideGround(minesweeper *ms){
	int i,j;
	system("cls");
	printf("    ");
	for(i=1;i<=ms->y_dim;i++){
		printf("%2d ",i);
	}
	printf("\n    ");
	for(i=1;i<=ms->y_dim;i++){
		printf("---",i);
	}
	printf("\n");
	
	for(i=0;i<ms->x_dim;i++){
		printf("%2d |",i+1);
		for(j=0;j<ms->y_dim;j++){
			if(ms->hideGround[i][j] == '0'){
				printf("   ");
			}
			else{
				printf(" %c ",ms->hideGround[i][j]);
			}
		}
		printf("\n");
	}
}

void drawTheGround(minesweeper *ms){
	int i,j;
	system("cls");
	printf("Flag: %d",ms->mine_count-ms->mar_ind);
	printf("\n\n    ");
	for(i=1;i<=ms->y_dim;i++){
		printf("%2d ",i);
	}
	printf("\n    ");
	for(i=1;i<=ms->y_dim;i++){
		printf("---",i);
	}
	printf("\n");
	
	for(i=0;i<ms->x_dim;i++){
		printf("%2d |",i+1);
		for(j=0;j<ms->y_dim;j++){
			printf(" %c ",ms->showGround[i][j]);
		}
		printf("\n");
	}
}

int markTheBlock(char showGround[][50],int x,int y){
	if(showGround[x][y] == '.'){
		showGround[x][y] = 'F';
		return 1;
	}
	else if(showGround[x][y] == 'F') {
		showGround[x][y] = '.';
		return -1;
	}
	return 0;
}

void hitTheBlock(minesweeper *ms,int x,int y){
	if(checkBoundary(x,ms->x_dim) && checkBoundary(y,ms->y_dim)){
		 if(ms->showGround[x][y] == '.' || ms->showGround[x][y] == 'F') {
	 		if(ms->hideGround[x][y] == '0'){
				ms->showGround[x][y] = ' ';

				
				hitTheBlock(ms,x-1,y-1);
				hitTheBlock(ms,x-1,y+1);
				hitTheBlock(ms,x-1,y);
				
				hitTheBlock(ms,x,y-1);
				hitTheBlock(ms,x,y+1);
				
				hitTheBlock(ms,x+1,y-1);
				hitTheBlock(ms,x+1,y+1);
				hitTheBlock(ms,x+1,y);
				
			}
			else if(ms->hideGround[x][y] >= '1' && ms->hideGround[x][y] <= '8'){
				ms->showGround[x][y] = ms->hideGround[x][y];
			}
			ms->unvisited--;
		 }
		
	}
}

int breakTheBlock(minesweeper *ms,int x,int y){
	if(ms->showGround[x][y] == 'F'){
		return -1;
	}
	else if(ms->hideGround[x][y] == '@'){
		return 0;
	}
	else if(ms->showGround[x][y] == '.'){
		hitTheBlock(ms,x,y);
		return 1;		
	}
	else{
		return -1;
	}
	
}

int isWinner(minesweeper *ms){
	int x,y,i;
	if(ms->unvisited == ms->mine_count){
		for(i=0;i<ms->mar_ind;i++){
			x = ms->mark_pos[i][0];
			y = ms->mark_pos[i][1];
			if(ms->hideGround[x][y] != '@'){
				return 0;
			}
		}
	}
	else{
		return 0;
	}
	return 1;
}

void ins(int mark_pos[][2],int index,int x,int y){
	mark_pos[index][0] = x;
	mark_pos[index][1] = y;
}

void del(int mark_pos[][2],int index,int x,int y){
	int i,found = -1;
	for(i=0;i<index;i++){
		if(mark_pos[i][0] == x && mark_pos[i][1] == y){
			found = i;
			break;
		}
	}
	
	for(i=found+1;i<index;i++){
		mark_pos[i-1][0] = mark_pos[i][0];
		mark_pos[i-1][1] = mark_pos[i][1];
	}
}

void finalDraw(minesweeper *ms){
	int i,j;
	char temp;
	system("cls");
	printf("Flag: %d",ms->mine_count-ms->mar_ind);
	printf("\n\n    ");
	for(i=1;i<=ms->y_dim;i++){
		printf("%2d ",i);
	}
	printf("\n    ");
	for(i=1;i<=ms->y_dim;i++){
		printf("---",i);
	}
	printf("\n");
	
	for(i=0;i<ms->x_dim;i++){
		printf("%2d |",i+1);
		for(j=0;j<ms->y_dim;j++){
			temp = ms->showGround[i][j];
			if(temp == 'F'){
				if(ms->hideGround[i][j] == '@'){
					printf(" F ");
				}
				else{
					printf(" X ");
				}
			}
			else if(ms->hideGround[i][j] == '0'){
				printf("   ");
			}
			else{
				printf(" %c ",ms->hideGround[i][j]);
			}	
		}
		printf("\n");
	}
}

void play(minesweeper *ms){
	char key;
	int row, col, status;
	
	while(1){
		//drawHideGround(ms);
		drawTheGround(ms);
		printf("\nPress Anyone of the key\nm - mark\\unmark\nh - hit\nq - quit: ");
		key = getch();
		printf("%c",key);
		
		if(key != 'm' && key != 'h' && key != 'q'){
			printf("\nPress Valid Options!!!");
		}
		else{
			if(key == 'q'){
				printf("\nYou quitted the Game!!!");
				break;
			}
			else{
				printf("\nEnter row and col to ");
				printf(key=='m'?"mark and unmark the block: ":"hit the block: ");
				scanf("%d %d",&row,&col);
				row--;
				col--;
				if(checkBoundary(row,ms->x_dim) && checkBoundary(col,ms->y_dim)){
					if(key == 'm'){
						status = markTheBlock(ms->showGround,row,col);
						if(status == 1){
							printf("\nThe Block marked successfully!!!");
							ins(ms->mark_pos,ms->mar_ind,row,col);
							ms->mar_ind++;
						}
						else if(status == -1){
							printf("\nThe Block unmarked successfully!!!");
							del(ms->mark_pos,ms->mar_ind,row,col);
							ms->mar_ind--;
						}
						else{
							printf("\nThe Block shouldn't be Hitted!!!");
						}
					}
					else{
						status = breakTheBlock(ms,row,col);
						if(status == 1){
							printf("\nThe Block Hitted Successfully!!!");
							if(isWinner(ms)){
								finalDraw(ms);
								printf("\nYou Won the Game!!!");
								break;
							}
						}
						else if(status == -1){
							printf("\nThe Block is already Hitted!!!");
						}
						else{
							finalDraw(ms);
							printf("\nYou lost the Game!!!");
							break;
						}
					}
				}
				else{
					printf("\nEnter the Valid row and column!!!");
				}
			}
		}
		Sleep(300);
	}
}


void constructor(minesweeper *ms){
	ms->p = (player*)malloc(sizeof(player));
	
	printf("\nEnter your name: ");
	scanf("%s",ms->p->name);
	printf("\nEnter the Level of Difficulty\n1 - Easy\n2 - Medium\n3 - Hard: ");
	scanf("%d",&ms->p->level);

	//ms->p->level = 1;
	if(ms->p->level == 1){
		ms->x_dim = 10;
		ms->y_dim = 8;
		ms->mine_count = 6;
	}
	else if(ms->p->level == 2){
		ms->x_dim = 18;
		ms->y_dim = 14;
		ms->mine_count = 12;
	}
	else{
		ms->x_dim = 24;
		ms->y_dim = 20;
		ms->mine_count = 40;
	}
	printf("\nLoading.......");
	ms->unvisited = ms->x_dim * ms->y_dim;
	ms->mar_ind = 0;
	clearGround(ms);
	clearHideGround(ms);
	createMineGround(ms);
	play(ms);
}

void main(){
	minesweeper ms;
	constructor(&ms);
}
