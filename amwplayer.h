/**
 * @author Stefan Brandle, Jonathan Geisler
 * @date September, 2004
 *
 * Please type in your name[s] here:
 *
 */

#ifndef AMWPLAYER_H		// Double inclusion protection
#define AMWPLAYER_H

using namespace std;

#include "PlayerV2.h"
#include "Message.h"
#include "defines.h"

// DumbPlayer inherits from/extends PlayerV2

class amwplayer: public PlayerV2 {
    public:
      amwplayer( int boardSize );
      ~amwplayer();
      void newRound();
      Message placeShip(int length);
      Message getMove();
      void update(Message msg);
      void sinkShip( int lastRow, int lastCol, int shot[] );
      bool validFollow( int row, int col, int irow, int icol, int shot[] );
      void greatestProb();
      void pickthebestspot(int array1[], int count);
      void spotProb();
	    void copyarray1(int array2[], int array3[]);
	bool seeifthereisahit( int shot[] ); 
      private:
          void initializeBoard();
		      void initializeBoard1();
          void initializeBoard2();
		      int board1[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
		      int shot[2];
		      int icol;
		      int irow;
          int lastRow;
          int lastCol;
          int numShipsPlaced;
		      int arrayfinalshot[2];
          char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
          int boardprob[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
          int boardpre[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
};

#endif
