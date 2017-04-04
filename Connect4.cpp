#include <iostream>
#include <string>


#define HEIGHT 6
#define WIDTH 7

char playerName[2][5] = {"AI", "USER"};
char pieceName[3][2] = {"X","O","-"};
char winCondition[4][13]={"Tie","Horizontaily", "Verticaly","Diagonaly"};

int BOARD[HEIGHT][WIDTH];
int turns = 0;

void initilizeBoard();
void print();
void placePiece(int colum);
void nextPlayer();
int scoreBoard();
int getPlayer();
void checkForAWinner();
int MIDDLE = WIDTH/2;




//METHODS FOR AI
//int (*placePiece(int col, int board[HEIGHT][WIDTH], bool maximizingPlayer))[WIDTH]; //this returns a double array
int minMax(int tempBoard[][WIDTH], int depth, bool maximizingPlayer);
int scoreBoard(int (*tempBoard)[WIDTH]);
void placePiece(int col, int board[][WIDTH],bool maximizingPlayer);

void modify_array1(int (&a)[HEIGHT][WIDTH]);
void modify_array2(int (*a)[WIDTH]);
void modify_array3(int (*a)[WIDTH]);
void print(int board[][WIDTH]);

int main(){
	initilizeBoard();
	while(scoreBoard()==0){
		placePiece(minMax(BOARD,8,true));
  		int x;
  		std::cin >> x;
 		placePiece(x);
 	}
	return 0;
}

int scoreBoard(int tempBoard[][WIDTH]){
	for(int x = 0; x<HEIGHT; x++) 	//Horizontail
		for(int y = 0; y<WIDTH-3; y++)
			if(tempBoard[0+x][0+y]==tempBoard[0+x][1+y] && tempBoard[0+x][1+y]==tempBoard[0+x][2+y] && tempBoard[0+x][2+y]==tempBoard[0+x][3+y] && tempBoard[0+x][0+y]!=2)
				return 100;
	for(int x = 0; x<HEIGHT-3; x++)	//Vertical
		for(int y = 0; y<WIDTH; y++)
			if(tempBoard[0+x][0+y]==tempBoard[1+x][0+y] && tempBoard[1+x][0+y]==tempBoard[2+x][0+y] && tempBoard[2+x][0+y]==tempBoard[3+x][0+y]&& tempBoard[0+x][0+y]!=2)
				return 100;
	for(int x = 0; x<HEIGHT-3; x++)	//Diagonal
		for(int y = 0; y<WIDTH-3; y++)
			if(tempBoard[0+x][0+y]==tempBoard[1+x][1+y] && tempBoard[1+x][1+y]==tempBoard[2+x][2+y] && tempBoard[2+x][2+y]==tempBoard[3+x][3+y]&& tempBoard[0+x][0+y]!=2)
				return 100;
	for(int x = 0; x<HEIGHT-3; x++)	//Diagonal inverted
		for(int y = 0; y<WIDTH-3; y++)
			if(tempBoard[3+x][0+y]==tempBoard[2+x][1+y] && tempBoard[2+x][1+y]==tempBoard[1+x][2+y] && tempBoard[1+x][2+y]==tempBoard[0+x][3+y]&& tempBoard[3+x][0+y]!=2)
				return 100;
	return 0; 						//Nobody Wins
}


int minMax(int board[][WIDTH], int depth, bool maximizingPlayer){
	if (depth <= 0)
		return scoreBoard(board);
	int maxScore;
	int chosenCol;
	int score;

	if (maximizingPlayer){		//so this is for the AI
		maxScore = -100;
		for (int col = 0; col<WIDTH; col++){
			if(board[HEIGHT-1][col]==2){
				int tempBoard[HEIGHT][WIDTH];
				for(int x = 0; x < HEIGHT; x++){
					for(int y = 0; y < WIDTH; y++){
						tempBoard[x][y] = board[x][y];
					}
				}
				placePiece(col,tempBoard,true);	//I need this to be by refrence instead of by value
				score = minMax(tempBoard,depth-1,false);
				if (score>maxScore){
					maxScore = score;
					chosenCol = col;
				}
			}
		} 
		return chosenCol;	
	}
	else{						//so this is for the player
		maxScore = 100;
		for (int col = 0; col<WIDTH; col++){
			int tempBoard[HEIGHT][WIDTH];
			if(board[HEIGHT-1][col]==2){
				for(int x = 0; x < HEIGHT; x++){
					for(int y = 0; y < WIDTH; y++){
						tempBoard[x][y] = board[x][y];
					}
				}
				placePiece(col,tempBoard,false);
				score = -minMax(tempBoard,depth-1,true);
				if (score<maxScore){
					maxScore = score;
					chosenCol = col;
				}
			}
		}
		return chosenCol;	 	
	}
}

void placePiece(int col, int board[][WIDTH],bool maximizingPlayer){
	if(col < 0 || col>=WIDTH) 		//checks if a player has gone over bounds
		return;// board;
	if (turns == WIDTH*HEIGHT)		//checks if a the players have tied
		return;// board;
	if(board[HEIGHT-1][col] != 2)	//checks if the column chosen is filled
		return;// board;
	if(scoreBoard()>=2)				//checks if someone has won
		return;// board;
	
	for(int x = 0; x < HEIGHT; x++){
		if(board[x][col] == 2){ 			//if spot is empty
			board[x][col] = !maximizingPlayer;	//put checker there
			break;							//End the loop
		}
	}
	return;// board;
}

int getPlayer(){
	return turns%2;
}

void nextPlayer(){ 
	turns++;
}

void checkForAWinner(){
	if(scoreBoard()==1)
		std::cout<<"PLayers Tied"<<std::endl;
	if(scoreBoard()>=2)	
		std::cout<<"Player "<< playerName[getPlayer()] <<" wins " <<winCondition[scoreBoard()-1]<<std::endl;
}

void print(){
	for (int x = 0; x < HEIGHT; x++){
		for (int y = 0; y < WIDTH; y++)
			std::cout << pieceName[BOARD[HEIGHT-x-1][y]] << " ";
		std::cout<<std::endl;
	}
	std::cout<<std::endl;
}

void placePiece(int col){
	if(col < 0 || col>=WIDTH) 		//checks if a player has gone over bounds
		return;
	if (turns == WIDTH*HEIGHT)		//checks if a the players have tied
		return;
	if(BOARD[HEIGHT-1][col] != 2)	//checks if the column chosen is filled
		return;
	if(scoreBoard()>=2)				//checks if someone has won
		return;
	for(int x = 0; x < HEIGHT; x++){
		if(BOARD[x][col] == 2){ 			//if spot is empty
			BOARD[x][col] = getPlayer();	//put checker there
			print();						//print the board
			checkForAWinner();				//check if they won
			nextPlayer();					//go to next player 
			break;							//End the loop
		}
	}
}

void initilizeBoard(){
	for (int x = 0; x < HEIGHT; x++){
		for (int y = 0; y < WIDTH; y++){
			BOARD [x][y] = 2;
		}
	}
}

int scoreBoard(){
	for(int x = 0; x<HEIGHT; x++) 	//Horizontail
		for(int y = 0; y<WIDTH-3; y++)
			if(BOARD[0+x][0+y]==BOARD[0+x][1+y] && BOARD[0+x][1+y]==BOARD[0+x][2+y] && BOARD[0+x][2+y]==BOARD[0+x][3+y] && BOARD[0+x][0+y]!=2)
				return 2;
	for(int x = 0; x<HEIGHT-3; x++)	//Vertical
		for(int y = 0; y<WIDTH; y++)
			if(BOARD[0+x][0+y]==BOARD[1+x][0+y] && BOARD[1+x][0+y]==BOARD[2+x][0+y] && BOARD[2+x][0+y]==BOARD[3+x][0+y]&& BOARD[0+x][0+y]!=2)
				return 3;
	for(int x = 0; x<HEIGHT-3; x++)	//Diagonal
		for(int y = 0; y<WIDTH-3; y++)
			if(BOARD[0+x][0+y]==BOARD[1+x][1+y] && BOARD[1+x][1+y]==BOARD[2+x][2+y] && BOARD[2+x][2+y]==BOARD[3+x][3+y]&& BOARD[0+x][0+y]!=2)
				return 4;
	for(int x = 0; x<HEIGHT-3; x++)	//Diagonal inverted
		for(int y = 0; y<WIDTH-3; y++)
			if(BOARD[3+x][0+y]==BOARD[2+x][1+y] && BOARD[2+x][1+y]==BOARD[1+x][2+y] && BOARD[1+x][2+y]==BOARD[0+x][3+y]&& BOARD[3+x][0+y]!=2)
				return 4;
	if (turns == WIDTH*HEIGHT-1)
		return 1;					//Tie
	return 0; 						//Nobody Wins
}
