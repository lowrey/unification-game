/* Title:Unification Card Game
 * Author: Bret Lowrey
 * Date: 07/08/2010
 *
 * some code based on the open source card engine Drac
 * found at http://drac-cardlib.sourceforge.net/
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "includes/CGame.h"
#include "font.h"

#define 	CARD_COMMON_PILE			0
#define 	CARD_PLAYER_DECK			1
#define 	CARD_PLAYER_DISCARD 	    2
#define		CARD_TRASH			   		3
#define 	CARD_PLAYER_HAND			4

SDL_Surface *screen;
//SDLFont *font1; // 2 fonts
//SDLFont *font2;
CGame Unification;

const unsigned int SCREEN_WIDTH		=	1024;
const unsigned int SCREEN_HEIGHT	=	768;

void Initialize() // must be called only once
{
	//do some initialization and create the regions in here

	SDL_WM_SetCaption("Unification", NULL); // Set the window title
	//font1 = initFont("font/data/font1");
	//font2 = initFont("font/data/font2");

	InitDeck(screen);
	Unification.Initialize(screen);

	//index 0, Player's Deck
	Unification.CreateRegion(CARD_PLAYER_DECK, CRD_VISIBLE | CRD_3D, 0, 0, CRD_ATTACK_SYMBOL,
			SCREEN_WIDTH - CARD_WIDTH - 35, SCREEN_HEIGHT - CARD_HEIGHT - 20, 2, 2);

	//index 1, Player's Discard
	Unification.CreateRegion(CARD_PLAYER_DISCARD, CRD_VISIBLE|CRD_FACEUP|CRD_DODRAG|CRD_DODROP
			|CRD_3D,CRD_DOALL,CRD_DRAGTOP, CRD_ATTACK_SYMBOL, SCREEN_WIDTH - CARD_WIDTH - 35,
			SCREEN_HEIGHT - CARD_HEIGHT * 2 - 20 * 2, 0, 0);

	//index 2-6. Player's hand
	for (int i =0 ; i <= 4; i++)
		Unification.CreateRegion(CARD_PLAYER_HAND, CRD_VISIBLE|CRD_FACEUP|CRD_DODRAG|CRD_3D,
					CRD_DOALL,CRD_DRAGTOP, CRD_ATTACK_SYMBOL, ((CARD_WIDTH + 20) * i + 35),
					(SCREEN_HEIGHT - CARD_HEIGHT - (20) ) , 0, 0);

	//index 7-11, Common piles, row 1
	for (int i =0 ; i <= 4; i++)
			Unification.CreateRegion(CARD_COMMON_PILE, CRD_VISIBLE|CRD_FACEUP|CRD_DODRAG|CRD_DODROP|CRD_3D,
					CRD_DOALL,CRD_DRAGTOP, CRD_ATTACK_SYMBOL, ((CARD_WIDTH + 20) * i + 35),
					(SCREEN_HEIGHT - CARD_HEIGHT * 2 - (60 * 2) ) , 0, 0);

	//index 12-16, Common piles, row 2
	for (int i =0 ; i <= 4; i++)
			Unification.CreateRegion(CARD_COMMON_PILE, CRD_VISIBLE|CRD_FACEUP|CRD_DODRAG|CRD_DODROP|CRD_3D,
					CRD_DOALL,CRD_DRAGTOP, CRD_ATTACK_SYMBOL, ((CARD_WIDTH + 20) * i + 35),
					(SCREEN_HEIGHT - CARD_HEIGHT * 3 - (140) ) , 0, 0);


	/*
	//index 1-7
	for (int i = 1; i <= 7; i++)
		Unification.CreateRegion(CARD_COMMON_PILE, CRD_VISIBLE | CRD_DODRAG
				| CRD_DODROP, CRD_DOALL, CRD_DRAGFACEUP, CRD_ATTACK_SYMBOL,
				(CARDWIDTH * (i - 1)) + (i * 35), CARDHEIGHT + 40, 0, 16);
	//index 8
	Unification.CreateRegion(CARD_PLAYER_DISCARD, CRD_VISIBLE | CRD_FACEUP | CRD_DODRAG
			| CRD_3D, CRD_DOALL, CRD_DRAGTOP, CRD_ATTACK_SYMBOL, CARDWIDTH + 65, 10,
			0, 0);
	Unification.CreateRegion(CARD_TRASH, CRD_VISIBLE | CRD_FACEUP | CRD_DODRAG
				| CRD_3D, CRD_DOALL, CRD_DRAGTOP, CRD_ATTACK_SYMBOL, CARDWIDTH + 65, 10,
				0, 0);
	//index 9-12
	for (int i = 4; i <= 7; i++)
		Unification.CreateRegion(CARD_PLAYER_HAND, CRD_VISIBLE | CRD_3D | CRD_DODRAG
				| CRD_DODROP, CRD_DOSINGLE , CRD_DRAGTOP, CRD_ATTACK_SYMBOL, (CARDWIDTH
				* (i - 1)) + (i * 35), 10, 0, 0);
	Unification.CreateRegion(CARD_PLAYER_DISCARD, CRD_VISIBLE | CRD_FACEUP | CRD_DODRAG
					| CRD_3D, CRD_DOALL, CRD_DRAGTOP, CRD_ATTACK_SYMBOL, CARDWIDTH + 65, 10,
					0, 0);
	*/
}

void NewGame() {
	//Reset pile symbol
	Unification[0].SetSymbol(CRD_ATTACK_SYMBOL);

	//Empty the card regions from the previous game
	Unification.EmptyStacks();

	//create then shuffle the deck
	Unification[0].NewSetOfCards();
	Unification[0].NewDeck();
	//Unification[0].Shuffle();

	//add one of each card to the common piles
	for (unsigned int i =7 ; i <= 16; i++)
		Unification[i].NewPile(i-7);
	//for (int i = 2; i <= 6; i++)
		//Unification[i].Push(Unification[0].Pop(1));

	//deal
	/*for (int i = 1; i <= 7; i++)
		Unification[i].Push(Unification[0].Pop(i));

	//initialize all card coordinates
	Unification.InitAllCoords();

	//set initial faced up cards in foundations
	for (int i = 1; i <= 7; i++)
		Unification[i].SetCardFaceUp(true, Unification[i].Size() - 1);*/

	Unification.InitAllCoords();
}

void HandleKeyDownEvent(SDL_Event &event) {
	if (event.key.keysym.sym == SDLK_n) {
		NewGame();
		Unification.DrawStaticScene();
	}
	if (event.key.keysym.sym == SDLK_a) {
		AnimateCards();
	}; // Test animation
	if (event.key.keysym.sym == SDLK_r) {
		Unification.DrawStaticScene();
	}; // Refresh
}

bool startdrag = false;
void ShuffleDiscardIntoDeck(CCardStack *& cs)
{
    *cs = Unification[1].Pop(Unification[1].Size());
    cs->SetCardsFaceUp(false);
    Unification.InitDrag(cs, -1, -1);
    Unification.DoDrop(&Unification[0]);
    Unification[0].Shuffle();
    Unification[0].InitCardCoords();
}

void HandleMouseDownEvent(SDL_Event &event) {
	CCardRegion *srcReg;
	if (event.button.button == SDL_BUTTON_LEFT) {
		srcReg = Unification.OnMouseDown(event.button.x, event.button.y);
		if (srcReg == NULL)
			return;
		if(srcReg->Id == CARD_PLAYER_DECK)
		{
			CCardStack *cs = new CCardStack;

			//discard player's hand
			for (int i = 2; i <= 6; i++)
			{
				if(!Unification[i].IsEmpty())
				{
					*cs = Unification[i].Pop(1);
					Unification.InitDrag(cs, -1, -1);
					Unification.DoDrop(&Unification[1]);
				}

			}

			if(srcReg->IsEmpty() && !Unification[1].IsEmpty()) //Bring back the cards
			{
			    ShuffleDiscardIntoDeck(cs);
			}
			else if(!srcReg->IsEmpty())
			{
				//draw new cards for the hand
				for (int i = 2; i <= 6; i++)
				{
					//if there are not enough left, shuffle discard back into deck
					if(Unification[0].IsEmpty())
					{
						ShuffleDiscardIntoDeck(cs);
					}
					*cs = Unification[0].Pop(1);
					cs->SetCardsFaceUp(true);
					Unification.InitDrag(cs, -1, -1);
					Unification.DoDrop(&Unification[i]);
				}
			}
		}
		else if ( Unification.InitDrag(event.button.x, event.button.y))
		{
			startdrag = true;
			SDL_WM_GrabInput(SDL_GRAB_ON);
		}
		//std::cout << "Here" << '\n';
	}

	//substitute right-click for double-click event
	/*if (event.button.button == SDL_BUTTON_RIGHT) {
		srcReg = Unification.OnMouseDown(event.button.x, event.button.y);
		if (srcReg == NULL)
			return;
		CCardRegion *cr;
		CCard card = srcReg->GetCard(srcReg->Size() - 1);

		//clicked on the top of the foundations
		if (((srcReg->Id == CARD_PLAYER_HAND) || (srcReg->Id == CARD_COMMON_PILE))
				&& card.FaceUp() && srcReg->PtOnTop(event.button.x,
				event.button.y)) {
			if ((cr = Unification.FindDropRegion(CARD_PLAYER_HAND, card))) {
				CCardStack *cs = new CCardStack;
				*cs = srcReg->Pop(1);
				Unification.InitDrag(cs, -1, -1);
				Unification.DoDrop(cr);
			}
		}
	}*/
}

void HandleMouseMoveEvent(SDL_Event &event) {
	if (event.motion.state == SDL_BUTTON(1) && startdrag)
		Unification.DoDrag(event.motion.x, event.motion.y);
}

void HandleMouseUpEvent(SDL_Event &event) {
	if (startdrag) {
		startdrag = false;
		Unification.DoDrop();
		SDL_WM_GrabInput(SDL_GRAB_OFF);
	}
	if (Unification[0].IsEmpty() && Unification[1].IsEmpty()) {
		Unification[0].SetSymbol(1);
		Unification.DrawStaticScene();
	}
	//victory
	/*
	if ((Unification[9].Size() == 13) && (Unification[10].Size() == 13)
			&& (Unification[11].Size() == 13) && (Unification[12].Size() == 13)) {
		AnimateCards();
		NewGame();
		Unification.DrawStaticScene();
	}*/
}

int main(int argc, char *argv[]) {
	if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0) {
		printf("Unable to initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}
	atexit(SDL_Quit);

	//screen = SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE | SDL_HWPALETTE
	//		| SDL_RESIZABLE);
	//screen = SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE | SDL_HWPALETTE
		//		| SDL_FULLSCREEN);
	screen=SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32,
			SDL_SWSURFACE|SDL_HWPALETTE);


	if (screen == NULL) {
		printf("Unable to set 0x0 video: %s\n", SDL_GetError());
		exit(1);
	}

	Initialize();
	NewGame();
	Unification.DrawStaticScene();

	SDL_Event event;
	int done = 0;

	while (done == 0) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				return 0;

			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					done = 1;
				}
				HandleKeyDownEvent(event);
				break;

			case SDL_MOUSEBUTTONDOWN:
				HandleMouseDownEvent(event);
				break;

			case SDL_MOUSEMOTION:
				HandleMouseMoveEvent(event);
				break;

			case SDL_MOUSEBUTTONUP:
				HandleMouseUpEvent(event);
				break;
			}
		}
	}

	// perform cleaning up in here

	//freeFont(font1);
	//freeFont(font2);
	return 0;
}
