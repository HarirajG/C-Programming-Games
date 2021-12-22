#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int shuffle = 100;
typedef struct LIFODS{
	int stack[500];
	int top,curr_top,moves_count;
	int capacity;
}lifoArr;

typedef struct PUZZLE{
	int board[4][4];
	int x_pos,y_pos;
}puzzle;

const int N = 4;
void drawBoard(int arr[N][N]){
	int i,j;
	system("cls");
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			if(arr[i][j] == 16){
				printf("   ");
			}
			else{
				printf("%2d ",arr[i][j]);
			}
		}
		printf("\n");
	}
	Sleep(100);
}

void push(lifoArr* stack,int move){
	if(stack->moves_count < stack->capacity){
		stack->top++;
		stack->stack[stack->top] = move;
		stack->curr_top++;
		stack->moves_count++;
	}
}

int pop(lifoArr* stack){
	int index = -1;
	if(stack->curr_top != -1){
		index = stack->curr_top;
		stack->curr_top--;
		return stack->stack[index];
	}
	return -1;
}

int peek(lifoArr* stack){
	return stack->top == -1? -1: stack->stack[stack->top];
}

int pos_check(int next){
	return 0<= next && next <= N-1;
}

void swap(int* a,int* b){
	
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void makeRandom(puzzle* pz,lifoArr* stack){
	int i,getMove,move = stack->moves_count,total_move;
	int x,y,flag;
	srand(time(0));
	while(shuffle>=total_move){
		flag  = 0;
		x = pz->x_pos;
		y = pz->y_pos;
		getMove = rand()%4;
		if(peek(stack) != getMove){
			if(getMove == 0 && pos_check(x-1)){//up
				push(stack,1);
				flag = 1;
				x = x -1;
			}
			else if(getMove == 1 && pos_check(x+1)){//down
				push(stack,0);
				flag = 1;
				x = x +1;
			}
			else if(getMove == 2 && pos_check(y-1)){//left
				push(stack,3);
				flag = 1;
				y = y -1;
			}
			else if(getMove == 3 && pos_check(y+1) ){//right
				push(stack,2);
				flag = 1;
				y = y +1;
			}
			if(flag){
				int* a = &pz->board[pz->x_pos][pz->y_pos];
				int* b = &pz->board[x][y];
				swap(a,b);
				pz->x_pos = x;
				pz->y_pos = y;
				total_move++;
			}
		}

	}
}

void reset(puzzle* pz,lifoArr* s){
	int x,y,move;
	while(s->curr_top > -1){
		x = pz->x_pos;
		y = pz->y_pos;
		move = pop(s);
		if(move == 0){
			x = x -1;
		}
		else if(move == 1){
			x = x +1;
		}
		else if(move == 2){
			y = y -1;
			
		}
		else if(move == 3){
			y = y +1;
		}
		int* a = &pz->board[x][y];
		int* b = &pz->board[pz->x_pos][pz->y_pos];
		swap(a,b);
		pz->x_pos = x;
		pz->y_pos = y;
		drawBoard(pz->board);
	}
}

void getTargetBoard(int arr[N][N]){
	int i,j,count=1;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			arr[i][j] = count++;
		}
	}
}

void construct_lifoArr(lifoArr* stack){
	stack->top = -1;
	stack->curr_top = -1;
	stack->moves_count = 0;
	stack->capacity = 500;
}

void construct_table(puzzle* pz,lifoArr* stack){
	getTargetBoard(pz->board);
	pz->x_pos = 3;
	pz->y_pos = 3;
	makeRandom(pz,stack);
}

void play(puzzle* pz,lifoArr* stack){
	int run = 1, x, y;
	char key;
	
	while(run){
		x = pz->x_pos;
		y = pz->y_pos;
		drawBoard(pz->board);
		printf("\nTo Exit press 'q'\nTo Restart press 'r'\nTo Solve auto press 'h'\nTo Move press (a,w,d,s):");
		key = getch();
		printf("%c",key);
		Sleep(500);
		switch(key){
			case 'w':
				x = x -1; 
				break;
			case 's': 
				x = x +1; 
				break;
			case 'a': 
				y = y -1; 
				break;
			case 'd': 
				y = y +1; 
				break;
			default:
				run = 0;
		}
		if(run){
			if(pos_check(x) && pos_check(y)){
				int* a = &pz->board[x][y];
				int* b = &pz->board[pz->x_pos][pz->y_pos];
				swap(a, b);
				pz->x_pos = x;
				pz->y_pos = y;
				switch(key){
					case 'w': push(stack,1); break;
					case 's': push(stack,0); break;
					case 'a': push(stack,3); break;
					case 'd': push(stack,2); break;
				}
			}
			else{
				printf("\nDo Valid Move!!!");
				Sleep(500);
			}
		}
	}
	drawBoard(pz->board);
	if(run == 0){
		if(key == 'q'){
			printf("\nYou are quitted the game!!!");
		}
		else if(key == 'h'){
			printf("You are switched to auto solve mode!!!");
			Sleep(400);
			reset(pz,stack);
			printf("Here is the Solution!!!");
		}
		else{
			printf("You are the Game!!!");
			Sleep(400);
			main();
		}
	}

}

void main(){
	
	lifoArr stack;
	puzzle pz;
	construct_lifoArr(&stack);
	construct_table(&pz,&stack);
	play(&pz,&stack);
}

