/*
	description:	Card stack data structure subs.
*/
#include "../includes/CCardStack.h"

const unsigned int STARTING_DECK = 10;
const unsigned int PILE_SIZE = 10;

void CCardStack::NewSetOfCards()
{
	int Id = 0;

	this->clear();
	this->resize(NUMBER_OF_CARDS);

    for(std::vector<CCard>::iterator vi = this->begin(); vi != this->end(); ++vi, ++Id)
        vi->SetIdx(Id);
}

void CCardStack::NewDeck()
{
	this->clear();
	CCard card(0);
	//start the deck with ten power - 1 cards
	for (unsigned int i = 0; i < STARTING_DECK; ++i)
	{
		this->Push(card);
	}

	//debugging for random cards in deck
	/*
	srand(time(0));
	int r = rand() % 10;
	for (unsigned int i = 0; i < 50; ++i)
	{
		CCard card(r);
		this->Push(card);
		r = rand() % 10;
	}*/
}

void CCardStack::NewPile(unsigned int i)
{
	this->clear();
	CCard card(i);
	for (unsigned int i = 0; i < PILE_SIZE; ++i)
	{
		this->Push(card);
	}
}

void CCardStack::Shuffle()
{
	srand((unsigned)time(0));
	std::random_shuffle(this->begin(), this->end());
}

void CCardStack::Clear()
{
	this->clear();
}

void CCardStack::Reverse()
{
	std::reverse(this->begin(), this->end());
}
// predicate for sorting
bool SortRank(const CCard& l, const CCard& r)
{
	return l.Rank() < r.Rank();
}

void CCardStack::Sort()
{
	std::sort(this->begin(), this->end(), SortRank);
}

void CCardStack::Push(const CCard card)
{
	this->push_back(card);
}

void CCardStack::Push(CCardStack cardstack)
{
	for(std::vector<CCard>::iterator vi = cardstack.begin(); vi != cardstack.end(); ++vi)
		this->push_back(*vi);
}

CCard CCardStack::Pop()
{
	if(Empty())
		return 0;

	CCard card = this->back();
	this->pop_back();

	return card;
}

CCardStack CCardStack::Pop(int items)
{
	if(items > Size())
		items = Size();

	CCardStack cardstack;

	while(items > 0)
	{
		cardstack.Push(this->Pop());
		items--;
	}
	cardstack.Reverse();
	return cardstack;
}

CCard CCardStack::RemoveCard(int index)
{
	if(this->Empty())
		return 0;

	std::vector<CCard>::iterator vi = this->begin() + index;
	CCard card = *vi;
	this->erase(vi);

	return card;
}

void CCardStack::InsertCard(int index, CCard card)
{
	std::vector<CCard>::iterator vi = this->begin() + index;
 	this->insert(vi, card);
}

int CCardStack::GetClickedCard(int x, int y)
{
	int i = this->Size() - 1;

	for(std::vector<CCard>::iterator vi = this->end() - 1; vi >= this->begin(); --vi)
    {
    	if( vi->PtInCard(x, y) )
    		return i;
		i--;
	}

	return -1;
}

CCard CCardStack::GetCard(int index)
{
	if(this->Empty())
		return 0;

	std::vector<CCard>::iterator vi = this->begin() + index;
	CCard card = *vi;

	return card;
}

void CCardStack::SetCardsFaceUp(bool fTrue)
{
	for(std::vector<CCard>::iterator vi = this->begin(); vi != this->end(); ++vi)
		vi->SetFaceUp(fTrue);
}

/*void CCardStack::AddJokers(int jokers)
{
	if(jokers < 0) jokers = 1;

	std::vector<CCard>::iterator vi = this->end() - 1;

	this->resize(this->size() + jokers);

    for(;vi != this->end(); ++vi)
        vi->SetIdx(52);
}*/
