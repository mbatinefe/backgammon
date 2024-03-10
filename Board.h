// Mustafa Batin Efe - 29272
#include "CharStack.h"
#ifndef UNTITLED2_BOARD_H
#define UNTITLED2_BOARD_H

struct slot
{
    slot * next;
    slot * prev;
    CharStack slotStack;
    slot ()
    {}
};

class Board
{
private:
    slot * head;
    slot * tail;

    int xCnt;
    int oCnt;
public:
    Board();
    bool noMove(char player, int steps);
    int validMove(char player, int startIndex, int steps, int direction);
    void movePiece(int source, int target);
    void printBoard();
    int evaluateGame();
    bool targetSlotFull(int slotIndex);
    void destroySlot(int slotIndex);
    void createSlotBegin(char ch, int num);
    void createSlotEnd(char ch, int num);
    void createEmptySlotEnd();
    void clearBoard();
};



#endif //UNTITLED2_BOARD_H
