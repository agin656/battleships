/**
 * @author Stefan Brandle, Jonathan Geisler
 * @date September, 2004 Updated 2015 for multi-round play.
 *
 * Please type in your name[s] here:
 */

#include <iostream>
#include <cstdio>
#include <string.h>

#include "conio.h"
#include "amwplayer.h"

using namespace conio;

/**
 * @brief Constructor that initializes any inter-round data structures.
 * @param boardSize Indication of the size of the board that is in use.
 */
 amwplayer::amwplayer( int boardSize ):
    PlayerV2(boardSize)
{
  this->initializeBoard1();
}

/**
 * @brief Destructor placeholder.
 */
 amwplayer::~amwplayer( ) {}

/*
 * Private internal function that initializes a MAX_BOARD_SIZE 2D array of char to water.
 */
void amwplayer::initializeBoard() {
    for(int row=0; row<boardSize; row++) {
      for(int col=0; col<boardSize; col++) {
        board[row][col] = WATER;
      }
    }
}

void amwplayer::initializeBoard1() {
    for(int row=0; row<boardSize; row++) {
      for(int col=0; col<boardSize; col++) {
        boardpre[row][col] = 0;
      }
    }
}

void amwplayer::initializeBoard2() {
    for(int row=0; row<boardSize; row++) {
      for(int col=0; col<boardSize; col++) {
        boardprob[row][col] = 0;
      }
    }
}


/**
 * Gets the computer's shot choice. This is then returned to the caller.
 * @return Message The most important parts of the returned message are
 * the row and column values.
 * Position 0 of the int array should hold the row, position 1 the column.
 */
Message amwplayer::getMove() {
  if( board[lastRow][lastCol] == HIT) {
    sinkShip(lastRow, lastCol, shot);
    Message result(SHOT,shot[0],shot[1],"Bang");
    return result;
  }
  if(seeifthereisahit( shot )){
	cout << "it is hear"<< endl<<flush;
	sinkShip(shot[0], shot[1], shot);
	Message result(SHOT,shot[0],shot[1],"Bang");
	return result;
  }
  cout << arrayfinalshot[0] << "part one"<< endl<<flush;
  cout << arrayfinalshot[1] << "part one"<< endl<<flush;
  spotProb();
  greatestProb();
  cout << arrayfinalshot[0] << "part two"<< endl<<flush;
  cout << arrayfinalshot[1] << "part two"<< endl<<flush;
  lastRow = arrayfinalshot[0];
  lastCol = arrayfinalshot[1];
  Message result( SHOT, lastRow, lastCol, "Bang", None, 1 );
  return result;
}

bool amwplayer::seeifthereisahit( int shot[] ) {
	for(int row=0; row<boardSize; row++) {
		for(int col=0; col<boardSize; col++) {
			if(board[row][col] == HIT){
				shot[0] = row;
				shot[1] = col;
				return true;
			}
		}
	}
	return false;
}

/**
 * @brief Tells the AI that a new round is beginning.
 * The AI show reinitialize any intra-round data structures.
 */
void amwplayer::newRound() {
    /* DumbPlayer is too simple to do any inter-round learning. Smarter players reinitialize any
     * round-specific data structures here.
     */
    this->lastRow = 0;
    this->lastCol = -1;
    this->numShipsPlaced = 0;

    this->initializeBoard();
    this->initializeBoard2();
}

/**
 * Gets the AI's ship placement choice. This is then returned to the caller.
 * @param length The length of the ship to be placed.
 * @return Message The most important parts of the returned message are
 * the direction, row, and column values.
 * Position 0 of the int array should hold the row, position 1 the column.
 */
Message amwplayer::placeShip(int length) {
    char shipName[10];
    // Create ship names each time called: Ship0, Ship1, Ship2, ...
    snprintf(shipName, sizeof shipName, "Ship%d", numShipsPlaced);

    // parameters = mesg type (PLACE_SHIP), row, col, a string, direction (Horizontal/Vertical)
    Message response( PLACE_SHIP, numShipsPlaced+4, 5, shipName, Horizontal, length );
    numShipsPlaced++;

    return response;
}

void amwplayer::greatestProb(){
  int highest = 0;
  int highestarray[200];
  int count = 0;
  for(int row=0; row<boardSize - 2; row++) {
    for(int col=0; col<boardSize - 2; col++) {
      if( boardprob[row][col] > highest){
        memset(highestarray, '\0', 200*(sizeof count)); //check if this works
        count = 0;
        highest = boardprob[row][col];
        highestarray[count + 0] = row;
        highestarray[count + 1] = col;
        count += 1;
      }
      else if (boardprob[row][col] == highest){
        highestarray[count + 1] = row;
        highestarray[count + 2] = col;
        count += 2;
      }
    }
  }
  pickthebestspot(highestarray, count);
}

void amwplayer::copyarray1(int array2[], int array3[]){
	for (int i=0; i< 2 ; i++) {
		array3[i] = array2[i];
	}
}

void amwplayer::pickthebestspot(int array1[], int count){
   int row1;
   int col1;
   //int RCfinal[2];
   int highest = 0;
   int temp1;

   for(int move1=0; move1 < count; move1 = move1 + 2) {
     row1 = array1[move1];
     col1 = array1[move1 + 1];
     if(boardpre[row1][col1] > highest){
       highest = boardpre[row1][col1];
       arrayfinalshot[0] = array1[move1];
       arrayfinalshot[1] = array1[move1 + 1];
     }
   }
   if(highest == 0){
	    temp1 = array1[0];
      arrayfinalshot[0] = temp1;
	    temp1 = array1[1];
      arrayfinalshot[1] = temp1;
   }
   
   cout << arrayfinalshot[0] << endl<<flush;
   cout << arrayfinalshot[1] << endl<<flush;
 }

void amwplayer::spotProb(){
initializeBoard2();
  for(int row=0; row<boardSize - 2; row++) {
    for(int col=0; col<boardSize - 2; col++) {
      if( board[row][col] == WATER) {
        if( board[row + 1][col] == WATER) {
          if( board[row + 2][col] == WATER) {
            boardprob[row][col] += 1;
            boardprob[row + 1][col] += 1;
            boardprob[row + 2][col] += 1;
          }
        }
      }
	  if( board[row][col] == WATER) {
        if( board[row][col + 1] == WATER) {
          if( board[row][col + 2] == WATER) {
            boardprob[row][col] += 1;
            boardprob[row][col + 1] += 1;
            boardprob[row][col + 2] += 1;
          }
        }
      }
    }
  }
  for(int row=boardSize; row>0; row--) {
    for(int col=boardSize; col>0; col--) {
      if( board[row][col] == WATER) {
        if( board[row - 1][col] == WATER) {
          if( board[row - 2][col] == WATER) {
            boardprob[row][col] += 1;
            boardprob[row - 1][col] += 1;
            boardprob[row - 2][col] += 1;
          }
        }
      }
	  if( board[row][col] == WATER) {
        if( board[row][col - 1] == WATER) {
          if( board[row][col - 2] == WATER) {
            boardprob[row][col] += 1;
            boardprob[row][col - 1] += 1;
            boardprob[row][col - 2] += 1;
          }
        }
      }
    }
  }
}



void amwplayer::sinkShip( int lastRow, int lastCol, int shot[] ) {
  if ( validFollow( lastRow, lastCol, 0, 1, shot)) return;
  else if (validFollow( lastRow, lastCol, 0, -1, shot)) return;
  else if (validFollow( lastRow, lastCol, 1, 0, shot)) return;
  else if (validFollow( lastRow, lastCol, -1, 0, shot)) return;
  else return;
}

bool amwplayer::validFollow( int row, int col, int irow, int icol, int shot[] ) {
  for(int r=row,c=col;r>=0 && c >= 0 && r<boardSize && c<boardSize;r+=irow,c+=icol)
  {
    switch(board[r][c])
    {
      case MISS:
      case KILL:
        return false;
      case WATER:
        shot[0]=r;
        shot[1]=c;
        return true;
    }
  }
  return false;
}

/**
 * @brief Updates the AI with the results of its shots and where the opponent is shooting.
 * @param msg Message specifying what happened + row/col as appropriate.
 */
void amwplayer::update(Message msg) {
    switch(msg.getMessageType()) {
    case HIT:
    case KILL:
    case MISS:
        board[msg.getRow()][msg.getCol()] = msg.getMessageType();
        break;
    case OPPONENT_SHOT:
        // TODO: get rid of the cout, but replace in your AI with code that does something
        // useful with the information about where the opponent is shooting.
        cout << gotoRowCol(20, 30) << "DumbPl: opponent shot at "<< msg.getRow() << ", " << msg.getCol() << flush;
        break;
      }
}
