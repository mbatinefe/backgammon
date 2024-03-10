
// Mustafa Batin Efe - 29272
#include "Board.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

Board::Board() {
    head = nullptr;
    tail = nullptr;
    xCnt = 0;
    oCnt = 0;
}

bool Board::noMove(char player, int steps){
    // Function will check every possibility of player with given steps
    slot * startTemp = head;
    slot * attackTemp = head;
    // return true if no possible move
    // return false if there are possible move

    /*
     * attackTemp: the place where we will move
     * startTemp; the place where we start
     */
    bool outOfBound = false; // To check if expected move is out of boundary,
    // outOfBound will help to block segmentation fault
    /* Algorithm will be like following
     * First, assume it will go right, steps will be 2
     * [ a , b , c , d , e , f]
     * Algorithm will check respectively like;
     * { startTemp:A attackTemp:C, startTemp:B attackTemp:D, startTemp:C attackTemp:E, startTemp:D attackTemp:F }
     *
     * Second, assume it will go left, steps will be 2
     * { startTemp:F attackTemp:D, startTemp:E attackTemp:C, startTemp:D attackTemp:B, startTemp:C attackTemp:A }
     * */
    if (outOfBound == false){
        while(attackTemp != nullptr) {
                if (attackTemp->next != nullptr) { // If next is null it means we are done checking going right
                    for (int m = 0; m < steps; m++) {
                        if (attackTemp->next != nullptr) {
                            attackTemp = attackTemp->next;
                        } else {
                            // If next is null and for loop is not done;
                            // It means, we are out of boundary
                            outOfBound = true;
                            attackTemp = nullptr; // set to nullPtr
                        }
                    }
                    // Control attackTemp, if outOfBound is false
                    if (outOfBound == false) {
                        if (startTemp->slotStack.isEmpty() == false) {
                            // If not empty
                            char chStart, chAttack;
                            startTemp->slotStack.pop(chStart); // get chStart
                            if (attackTemp->slotStack.isEmpty() == true && player == chStart) {
                                // If attack is empty and player in start is same with the player
                                startTemp->slotStack.push(chStart);
                                // push back
                                return false;
                            } else if (attackTemp->slotStack.isEmpty() == false) {
                                // If it is not empty, we should check both player in start and player in attack
                                attackTemp->slotStack.pop(chAttack); // get attack
                                if (player == chStart && player == chAttack) {
                                    // push all back
                                    attackTemp->slotStack.push(chAttack);
                                    startTemp->slotStack.push(chStart);
                                    return false;
                                }
                                // If player does not match, push it back all and continue
                                attackTemp->slotStack.push(chAttack);
                                startTemp->slotStack.push(chStart);
                            } else{
                                // If none apply, push start back and continue
                                startTemp->slotStack.push(chStart);
                            }
                        }
                        // we need to move attackTemp one to its right, to access all possibilities
                        if (attackTemp != nullptr) {
                            if (attackTemp->next != nullptr) {
                                startTemp = startTemp->next; // move start
                                attackTemp = startTemp; // move attack to start
                            }
                        }
                    }
                } else {
                    // If attack's next is null we are done
                    attackTemp = nullptr;
                }
        }
    }
        // Going left side
        attackTemp = tail;
        startTemp = tail;
        outOfBound = false;

        // Same logic with rights side; however it will go left this time. So, we will use prev
        while (attackTemp != nullptr) {
            if (outOfBound == false){
                if (attackTemp->prev != nullptr) {   // If prev is null it means we are done checking going right
                    for (int y = 0; y < steps; y++) {
                        if (attackTemp->prev != nullptr) {
                            attackTemp = attackTemp->prev;
                        } else {
                            // If prev is null and for loop is not done;
                            // It means, we are out of boundary
                            outOfBound = true;
                            attackTemp = nullptr;
                        }
                    }
                    // control attackTemp, if outOfBound is false
                    if (outOfBound == false) {
                        if (startTemp->slotStack.isEmpty() == false) {
                            // If not empty
                            char chStart, chAttack;
                            startTemp->slotStack.pop(chStart);
                            if (attackTemp->slotStack.isEmpty() == true && player == chStart) {
                                // If attack is empty and player in start is same with the player
                                startTemp->slotStack.push(chStart);
                                // push back
                                return false;
                            } else if (attackTemp->slotStack.isEmpty() == false) {
                                // If it is not empty, we should check both player in start and player in attack
                                attackTemp->slotStack.pop(chAttack);
                                if (player == chStart && player == chAttack) {
                                    // push all back
                                    attackTemp->slotStack.push(chAttack);
                                    startTemp->slotStack.push(chStart);
                                    return false;
                                }
                                // If player does not match, push it back all and continue
                                attackTemp->slotStack.push(chAttack);
                                startTemp->slotStack.push(chStart);
                            } else {
                                // If none apply, push start back and continue
                                startTemp->slotStack.push(chStart);
                            }
                        }
                        // we need to move attackTemp one to its right, to access all possibilities
                        if (attackTemp != nullptr) {
                            if (attackTemp->prev != nullptr) {
                                startTemp = startTemp->prev;  // move start one step
                                attackTemp = startTemp; // move attack to start
                            }
                        }
                    }
                } else {
                    // If attack's prev is null we are done
                    attackTemp = nullptr;
                }
        }
    }
    // None apply, so return true
    return true;
}

int Board::validMove(char player, int startIndex, int steps, int direction) {
    // Function will check if the asked move is valid or not
    slot * tempHead = head;
    slot * tempStart = head;
    slot * tempAttack = head;

    //Let find sizeOf slot
    int sizeOf = 0;
    while(tempHead != nullptr){
        tempHead = tempHead->next;
        sizeOf++;
    }
    // set head back
    tempHead = head;

    // Let find if entered slot index is within bounds
    if(0 <= startIndex && startIndex < sizeOf){
        for(int m = 0; m < startIndex; m++){
            // It will find wanted start slot
            tempStart = tempStart->next;
        }
        char start;
        // get the start player
        tempStart->slotStack.pop(start);
        if(start != player){
            // If they do not match, we cannot play
            tempStart->slotStack.push(start);
            return 4;
        }
        tempStart->slotStack.push(start); // push back
    } else{
        // entered slot not in boundary
        return 1;
    }

    // Now let focus on the target
    // Two option: 1( for right) 0 (for left)
    int index = 0;
    if(direction == 1){
        index = startIndex + steps;
    } else {
        index = startIndex - steps;
    }

    if(0 <= (index) && (index) < sizeOf){
        for(int q = 0; q < (index); q++){
            // Lets find wanted slot
            tempAttack = tempAttack->next;
        }
        char attack;
        if(tempAttack->slotStack.isEmpty() != true) {
            // If it is not empty; otherwise we can put
            tempAttack->slotStack.pop(attack); // get the char
            if(attack != player){
                // If it does not match with player
                tempAttack->slotStack.push(attack); // push back
                return 3;
            }
            // if they match with player
            tempAttack->slotStack.push(attack);
        } // else; continue we are good

    } else{
        // Asked target is not in the boundary
        return 2;
    }
    // none apply, so good to go
    return 0;
}

void Board::movePiece(int source, int target) {
    /* Following function will move the player char from given source to target point*/
    slot * sourceTemp = head;
    slot * targetTemp = head;
    char ch;

    for (int m = 0; m < source; m++) {
        // find asked start point
        sourceTemp = sourceTemp->next;
    }
    for (int y = 0; y < target; y++){
        // find asked target point
        targetTemp = targetTemp->next;
    }

    sourceTemp->slotStack.pop(ch); // pop from start point
    targetTemp->slotStack.push(ch); // push it back to target point
}

void Board::printBoard() {
    /* Function will print every member of slot in asked order*/
    char catchPop;
    slot * temp = head;
    slot * temp2 = head;
    string lines; // to store slot members
    vector<string>line; //to store each slot
    cout << endl;
    while(temp != nullptr) {
        int countPop = 0; // How many we will pop
        while (temp->slotStack.isEmpty() != true) {
            // while slot is not empty, we will keep popping
            temp->slotStack.pop(catchPop);
            // if its player is o,x -> add to lines
            if (catchPop == 'o') { lines += "o"; countPop++;}
            else if (catchPop == 'x') { lines += "x"; countPop++;}

        }
        temp = temp->next; // set temp to other slot

        // push all the members back
        for (int z = 0; z < countPop; z++) {
            temp2->slotStack.push(catchPop);
        }
        // if the slot member is empty -> push _ _ _ (3 space)
        if(temp2->slotStack.isEmpty() == true || countPop == 0){
            lines += "   ";
        }
        temp2 = temp;
        lines += "^"; // and add their base
        // Logic for following:
        // It will help to have same order as slot in the vector we are going to store

        /* Let say we have _xx^, this will add one space to beginning of the string */
        if(countPop == 2){
            lines.insert(lines.length()-3, " ");
        }
        /* Let say we have __x^, this will add two space to beginning of the string */
        if(countPop == 1){
            lines.insert(lines.length()-2, "  ");
        }
        // push back to vector
        line.push_back(lines);
        lines = "";
    }

    for(int t = 0; t < 4; t++){
        // Logic comes to this, we will have same size in each lines
        // So, exactly 4 times printing will be easy and fast
        for(int m = 0; m < line.size(); m++){
            cout << line[m][t];
        }
        cout << endl;
    }

}

int Board::evaluateGame() {
    /* Following function will evaluate the game situation by looking at their x-o count*/
    if(xCnt < oCnt){
        // If x is less than o
        return 1;
    } else if(oCnt < xCnt){
        // If o less than o
        return 2;
    } else{
        // If game is draw
        return 3;
    }
}

bool Board::targetSlotFull(int slotIndex) {
    // Function will check if the target slot is full and ready to exploit
    slot * temp = head;
    for (int i = 0; i < slotIndex; ++i) {
        // move to target slot
        temp = temp->next;
    }
    // Check if its full or not
    if(temp->slotStack.isFull() == true){
        return true;
    } else {
        return false;
    }
}

void Board::destroySlot(int slotIndex) {
    // Function will delete asked slot

    slot * ptrHead = head;
    slot * ptrTail = tail;
    slot * destroy = head;
    // 3 options: Begin - Middle - End
    for (int a = 0; a < slotIndex; a++) {
        // destroy: will be asked slot to be deleted
        destroy = destroy->next;
    }
    // To learn size of slot
    int sizeSlot = 0;
    while(ptrHead != nullptr){
        ptrHead = ptrHead->next;
        sizeSlot++;
    }
    ptrHead = head; // assign back to head

    char ch;
    int countPar = 0;
    if(destroy->prev == nullptr && destroy == ptrHead){
        // If the deleted slot is in beginning
        while(destroy->slotStack.isEmpty() != true){
            // If it is not empty, pop all the elements and decrease their counts
            destroy->slotStack.pop(ch);
            if(ch == 'x'){
                xCnt--;
            } else{
                oCnt--;
            }
            countPar++;
        }

        ptrHead = ptrHead->next; // assign head to next one
        delete destroy; // delete the slot
        ptrHead->prev = nullptr; // assign new heads prev to nullptr
        // Update the tail as well
        ptrTail = ptrHead;
        while(ptrTail->next != nullptr){
            ptrTail = ptrTail->next;
            // move it to right
        }
    } else if(destroy != head && destroy != tail){
        // If the deleted slot is in the middle
        while(destroy->slotStack.isEmpty() != true){
            // same logic: if not empty pop all elements
            destroy->slotStack.pop(ch);
            if(ch == 'x'){
                xCnt--;
            } else{
                oCnt--;
            }
            countPar++;
        }
        slot * ptrPre = destroy->prev; // take previos slot
        slot * ptrPost = destroy->next; // take next slot
        delete destroy; // delete wanted slot

        // combine pre and post
        ptrPre->next = ptrPost;
        ptrPost->prev = ptrPre;
        // set pre to slot's head
        while(ptrPre->prev != nullptr){
            ptrPre = ptrPre->prev;
        }
        // set post to slot's tail
        while(ptrPost->next != nullptr){
            ptrPost = ptrPost->next;
        }
        ptrHead = ptrPre; // update head
        ptrTail = ptrPost; // update tail
    } else{
        // In the end, just to double check; lets see if it is in the end
        if(destroy == tail){
            // Double check completed
            while(destroy->slotStack.isEmpty() != true){
                // pop out if it is not empty
                destroy->slotStack.pop(ch);
                if(ch == 'x'){
                    xCnt--;
                } else{
                    oCnt--;
                }
                countPar++;
            }
            ptrTail = ptrTail->prev; // set new tail as prev
            delete destroy; // delete the slot
            ptrTail->next = nullptr; // set tail's next to null
        }
    }
    // UPDATE head and tail
    head = ptrHead;
    tail = ptrTail;

}

void Board::createSlotBegin(char ch, int num) {
    /* This function will create a slot in the beginning with given number of char*/
    CharStack chrBeg; // create stack
    slot * headPtr = head;
    slot * tailPtr = tail;
    // push number of char wanted to stack
    for (int m = 0; m < num; m++) {
        chrBeg.push(ch);
        if (ch == 'x') {
            xCnt++;
        } else {
            oCnt++;
        }
    }
    slot *ptr;
    ptr = new slot(); // create new slot
    ptr->slotStack = chrBeg; // assign stack

    if(headPtr == nullptr && tailPtr == nullptr &&
       headPtr->next == nullptr && headPtr->prev == nullptr
       && tailPtr->next == nullptr && tailPtr->prev == nullptr){
        // Situation that linked list is empty
        headPtr = ptr; // set head as ptr (there is only one)
        tailPtr = ptr; // set tail as ptr (there is only one)
        headPtr->prev = nullptr;
        headPtr->next = nullptr;
    } else{
        // If there are multiple
        ptr->prev = nullptr; // set prev as null
        ptr->next = headPtr; // connect its next to old head
        headPtr->prev = ptr; // connect its prev as well
        headPtr = ptr; // set ptr as new head
        }
    // update head and tail
    head = headPtr;
    tail = tailPtr;
}

void Board::createSlotEnd(char ch, int num) {
    /* This function will create a slot in the end with given number of char*/
    CharStack chrEnd; // create stack
    slot * headPtr = head;
    slot * tailPtr = tail;
    // push number of char wanted to stack
    for (int m = 0; m < num; m++) {
        chrEnd.push(ch);
        if (ch == 'x') {
            xCnt ++;
        } else {
            oCnt ++;
        }
    }

    slot *ptr;
    ptr = new slot(); // create new slot
    ptr->slotStack = chrEnd; // assign stack

    if(headPtr == nullptr && tailPtr == nullptr){
        // Situation that linked list is empty
        headPtr = ptr; // set tail as ptr (there is only one)
        tailPtr = ptr; // set tail as ptr (there is only one)
        headPtr->prev = nullptr;
        headPtr->next = nullptr;
    } else{
        ptr->next= nullptr; // set next to null
        tailPtr->next = ptr; // connect ex-tail with ptr(new tail)
        ptr->prev = tailPtr; // connect its prev as well
        tailPtr = ptr; // set new tail
    }
    // update head and tail
    head = headPtr;
    tail = tailPtr;
}

void Board::createEmptySlotEnd() {
    /* This function will create empty slot in the end*/
    CharStack chrEnd; // Create stack
    slot *ptr;
    slot * headPtr = head;
    slot * tailPtr = tail;
    ptr = new slot(); // show new slot
    ptr->slotStack = chrEnd; // show its slotStack object to stack

    if(headPtr == nullptr && tailPtr == nullptr){
        // Situation that linked list is empty
        headPtr = ptr; // there will be only 1 so headPtr = tailPtr
        tailPtr = ptr;
        headPtr->prev = nullptr;
        headPtr->next = nullptr;
    } else{
        // For all other possibilities
        ptr->next= nullptr; // set its next to null
        tailPtr->next = ptr; // connect with ex-tail
        ptr->prev = tailPtr; // connect with ex-tail
        tailPtr = ptr; // the set tail with updated tail
    }
    // Set tail and head to finalized situations
    tail = tailPtr;
    head = headPtr;
}

void Board::clearBoard() {
    /* Time to clear all slot nodes*/
    slot * temp = head;
    char ch;
    // First I will pop every member
    // I know it will be deleted, however; I wanted to make sure.
    while(temp != nullptr) {
        while (temp->slotStack.isEmpty() != true) {
            temp->slotStack.pop(ch);
        }
        temp = temp->next;
    }
    // Then; delete all the slot nodes (except last one)
    while(head != tail){
        temp = head->next;
        delete head;
        head = temp;
    }
    // Now, I will delete the last one and set head, tail, xCnt, oCnt to its inital values
    delete head;
    head = nullptr;
    tail = nullptr;
    xCnt = 0;
    oCnt = 0;
}

