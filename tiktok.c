#include<stdio.h>
#include<stdlib.h>
#include<string.h>
const int N = 3;
typedef struct Player{
	char name[30];
	char symbol;
}player;

typedef struct TickTok{
	player p[2];
	char chart[3][3];
	int filled;
}ticktok;

ticktok tk;

void clearTable(){
	int i,j;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			tk.chart[i][j] = '?';
		}
	}
	tk.filled = 0;
}

void drawTable(){
	int i,j;
	system("cls");
	printf("\n ");
	for(j=1;j<=N;j++){
			printf("   %d   ",j);
	}
	printf("\n");
	for(i=0;i<N;i++){
		printf("\n");
		printf("%d",i+1);
		for(j=0;j<N;j++){
			printf("   %c   ",tk.chart[i][j]);
		}
		printf("\n");
	}
}

int checkRowAndCol(char symbol){
	int count1,count2,i,j;
	//row and column wise check
	for(i=0;i<N;i++){
		count1 = 0;
		count2 = 0;
		for(j=0;j<N;j++){
			if(symbol == tk.chart[i][j]){
				count1++;
			}
			if(symbol == tk.chart[j][i]){
				count2++;
			}
			if(count1 == N || count2 == N){
				return 1;
			}
		}
	}
	return 0;	
}

int checkDiagonal(char symbol){
	int count1,count2,i,j;
	
	count1 = count2 = 0;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			if(i==j && symbol==tk.chart[i][j]){
				count1++;
			}
			if(i==N-j-1 && symbol==tk.chart[i][j]){
				count2++;
			}
			if(count1 == N || count2 == N){
				return 1;
			}
		}
	}
	return 0;
}

int decideWinner(char symbol){
	if(checkRowAndCol(symbol)){
		return 1;
	}
	else if(checkDiagonal(symbol)){
		return 1;
	}
	else{
		return 0;
	}
}

int checkBoundary(int row,int col){
	return (row>=1 && row<=N) && (col>=1 && col<=N);
}

int markMyPlace(char symbol,int row,int col){
	if(!checkBoundary(row,col)){
		printf("\nYou Entered in Unknown Position");
		sleep(1);
	}
	else if(tk.chart[row-1][col-1] == '?'){
		tk.chart[row-1][col-1] = symbol;
		return 1;
	}
	else{
		printf("\nYou Entered Marked Position");
		sleep(1);
	}
	return 0;
}

void play(){
	int player_toggle = 0,row,col;
	char sys;
	while(1){
		drawTable();
		printf("\n%s Turn: ",tk.p[player_toggle].name);
		scanf("%d %d",&row,&col);
		sys = tk.p[player_toggle].symbol;
		if(markMyPlace(sys,row,col)){
			tk.filled++;
			if(decideWinner(sys)){
				drawTable();
				printf("\n%s is Winner!!!",tk.p[player_toggle].name);
				return;
			}
			if(tk.filled == N*N){
				drawTable();
				printf("\nMatch is Tie!!!");
				return;
			}
			player_toggle^=1;
		}
	}
}

void fillPlayer(){
	strcpy(tk.p[0].name,"hariraj");
	tk.p[0].symbol= 'X';
	
	strcpy(tk.p[1].name,"vimalraj");
	tk.p[1].symbol= 'O';
	
}

void main(){
	clearTable();
	fillPlayer();//Hardcoded Input
	play();
}
