/*
	description:	Interface for card stack data structure and subs.
*/

#ifndef CCARDSTACK_H
#define CCARDSTACK_H

#include "CCard.h"

#include <vector>
#include <algorithm>

#include <time.h>
#include <stdlib.h>
//#include <iostream>
//#include <stdio.h>

const unsigned int NUMBER_OF_CARDS = 10;

//typedef std::vector<CCard>::iterator VI;

class CCardStack : public std::vector<CCard>
{

public:

    void		NewSetOfCards();
    void		NewDeck();
    void		NewPile(unsigned int i);
    void		Shuffle();
    void		Clear();
    void		Sort();
    void		Reverse();
    bool		Empty() { return this->empty(); }
    int			Size() { return this->size(); }

    void		Push(const CCard card);
    void		Push(CCardStack cardstack);

    CCard		Pop();
    CCardStack	Pop(int items);

    CCard		RemoveCard(int index);
    void		InsertCard(int index, CCard card);
    
    int			GetClickedCard(int x, int y);
	CCard		GetCard(int index);
//	CCardStack	GetStack(int index);

	void		SetCardsFaceUp(bool fTrue);
	
	//void		AddJokers(int jokers);
};

#endif //CCARDSTACK_H
