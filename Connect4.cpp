#include <iostream>
#include <string>

#define HEIGHT 6
#define WIDTH 7

char token[3][2] = {"-","X","O"};
char winCondition[3][13]={"Horizontaily", "Verticaly","Diagonaly"};

int BOARD[HEIGHT][WIDTH];
int playerOn = 1;

void initilize();
void print();
void placePiece(int colum);
void nextPlayer();
int scoreBoard();

int main(){
	initilize();
	while(scoreBoard()==0){
		int x;
		std::cin >> x;
		placePiece(x);}
	return 0;
}

void initilize(){
	for (int x = 0; x < HEIGHT; x++){
		for (int y = 0; y < WIDTH; y++){
			BOARD [x][y] = 0;
		}
	}
}
void print(){
	for (int x = 0; x < HEIGHT; x++){
		for (int y = 0; y < WIDTH; y++)
			std::cout << token[BOARD[HEIGHT-x-1][y]] << " ";
		std::cout<<std::endl;
	}
	std::cout<<std::endl;
}

void placePiece(int col){
	if(col<WIDTH){
		//only accept from 0 to WIDTH-1
		for(int x = 0; x < HEIGHT; x++){
			if(BOARD[x][col] == 0){ 		//if it is empty
				BOARD[x][col] = playerOn;	//put you checker their
				if(scoreBoard()!=false)		//check if they won
					std::cout<<"Player "<<playerOn <<" wins " <<winCondition[scoreBoard()-1]<<std::endl;
				nextPlayer();				//go to next player 
				break;						//End the loop
			}
			if(x==HEIGHT-1)
				std::cout<<"COLUMN FILLED, SAME PLAYER"<<std::endl;
		}
		print();							//print the board
	}
	else
		std::cout<<"COLUM MUST BE AN INTEGER LESS THAN " << WIDTH<<std::endl;
}

void nextPlayer(){ //Just alternates between 1 and 2
	if(playerOn==2)				
		playerOn=0;
	playerOn++;
}

int scoreBoard(){
	//Horizontail
	for(int x = 0; x<HEIGHT; x++)
		for(int y = 0; y<WIDTH-3; y++)
			if(BOARD[0+x][0+y]==BOARD[0+x][1+y] && BOARD[0+x][1+y]==BOARD[0+x][2+y] && BOARD[0+x][2+y]==BOARD[0+x][3+y] && BOARD[0+x][0+y]!=0)
				return 1;
	//Vertical
	for(int x = 0; x<HEIGHT-3; x++)
		for(int y = 0; y<WIDTH; y++)
			if(BOARD[0+x][0+y]==BOARD[1+x][0+y] && BOARD[1+x][0+y]==BOARD[2+x][0+y] && BOARD[2+x][0+y]==BOARD[3+x][0+y]&& BOARD[0+x][0+y]!=0)
				return 2;
	//Diagonal
	for(int x = 0; x<HEIGHT-3; x++)
		for(int y = 0; y<WIDTH-3; y++)
			if(BOARD[0+x][0+y]==BOARD[1+x][1+y] && BOARD[1+x][1+y]==BOARD[2+x][2+y] && BOARD[2+x][2+y]==BOARD[3+x][3+y]&& BOARD[0+x][0+y]!=0)
				return 3;
	//Diagonal inverted
	for(int x = 0; x<HEIGHT-3; x++)
		for(int y = 0; y<WIDTH-3; y++)
			if(BOARD[3+x][0+y]==BOARD[2+x][1+y] && BOARD[2+x][1+y]==BOARD[1+x][2+y] && BOARD[1+x][2+y]==BOARD[0+x][3+y]&& BOARD[3+x][0+y]!=0)
				return 3;
	return 0;
}
