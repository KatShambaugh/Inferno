/*
Completed for M02:
	[x] Set up state machine
	[x] Set up basic player controls and movement
	[x] Set up enemies and their movement
	[x] Collision between enemies and the player
	[x] Set up display of lives
	[x] Set up basic grace controls and grace-player collision
	[x] Set up basic key controls, key is revealed by random enemy, set up key-player collision
	[x] Set up basic navigation between levels 1 and 2 when player collects the key

Completed for M03:
	[x] Add in navigation between all layers
	[x] Add grace to display on screen
	[x] Add in navigation to win, lose, and purgatory screens
	[x] Set up circle 0 as a cut screen
	[x] Fix grace display bug
	[x] Add in bonus enemy
	[x] Get bonus enemies moving / collision
	[x] When bonus enemy is killed, reveal a hidden piece of grace
	[x] Set up cheat room
	[x] Fix grace display to wrap all of them
	[x] Draw grace to be 8x8
	[x] Draw sword and create in game / link to player
	[x] Add in sword-enemy collision

To Complete for M04:
	[x] Create all sprite art
	[x] Add in all sprites
	[x] Create all level backgrounds
	[x] Create game “sky” background
	[x] Create all other state backgrounds
	[x] Find sounds as written in M01
	[x] Add in background sounds
	[x] Add in shooting fireballs
	[x] Design fireball sprite
	[x] Add in sword animation
	[x] Fix instructions screen
	[x] Animate Satan
	[x] Grace showing up as a fireball bug
	[x] Fireballs shoot too quickly bug
	[x] Fireballs show up too small bug
	[x] Fix cheat bug

To Complete for Final Submission:
	[x] Add in special effects sounds
	[x] Tweak colors of backgrounds to clash less
	[x] Make sure to squash all bugs
	[x] Pause music for pause screen - make it look nicer too???
	[x] Make pause screen look nicer


Current Bugs:
	[x] Some messups with the boss enemies and the grace display (there's an error in array indexing somewhere I think)
	[x] Hell song not working? Decrease length of songs maybe?
	[x] Purgatory song not working either
	[x] some bosses only moving diagonally???
	[x] You have to hit multiple times sometimes??? that's because of the update clasue I guess?
	[x] Cerberus placed too high
	[x] When fallen angels release grace it takes one from the top
	[x] Only active enemies need to shoot fireballs
	[x] Grace display on yellow screen
	[x] Angels stuck????
	[x] When you start over it needs to fully start over!
	[x] My key didn't come back when I restarted
	[x] Lost both last lives at the same time

Gameplay:
	- Use arrow keys to move the player around
	- Collect the key and grace with the B button 
		- Collect at least 5 grace before the end of the game to win
		- Collect keys to move to the next level
	- Collide your sword with enemies while pressing A to kill them
	- Block fireballs with your sword with L button
	While in level 4 (pink enemies), go to bottom left corner for cheat
*/

#include "myLib.h"
#include "start.h"
#include "game.h"
#include "pause.h"
#include "win.h"
#include "lose.h"
#include "gameplay.h"
#include "spritesheet.h"
#include "instruct.h"
#include "purgatory.h"
#include "limbo.h"
#include "titleSong.h"
#include "sound.h"
#include "gameSong.h"
#include "heavenSong.h"
#include "purgatorySong.h"
#include "hellSong.h"
#include "pauseTop.h"
#include "lust.h"
#include "gluttony.h"
#include "greed.h"
#include "anger.h"
#include "heresy.h"
#include "violence.h"
#include "fraud.h"
#include "treachery.h"

//Prototypes
void initialize();
void goToStart();
void start();
void goToInstruct();
void instruct();
void goToGame();
void game();
void goToPause();
void pause();
void goToWin();
void win();
void goToLose();
void lose();
void goToPurgatory();
void purgatory();

enum {START, INSTRUCT, GAME, PAUSE, WIN, LOSE, PURGATORY};
int state;

unsigned short buttons;
unsigned short oldButtons;

SOUND soundA;
SOUND soundB;

int main() {
	initialize();

	setupSounds();
	setupInterrupts();

	while(1) {
		//State machine
		switch(state) {
            case START:
                start();
                break;
            case INSTRUCT:
            	instruct();
            	break;
            case GAME:
                game();
                break;
            case PAUSE:
                pause();
                break;
            case WIN:
                win();
                break;
            case LOSE:
                lose();
                break;
            case PURGATORY:
                purgatory();
                break;
        }  

		oldButtons = buttons;
		buttons = BUTTONS;
	}
}

//Initializes states
void initialize() {
	hideSprites();
	//Load start background
	DMANow(3, startPal, PALETTE, 256);
	DMANow(3, startTiles, &CHARBLOCK[0], 8576);
	DMANow(3, startMap, &SCREENBLOCK[31], 1024);

	buttons = BUTTONS;

	//Load spritesheet
    DMANow(3, spritesheetPal, SPRITEPALETTE, 256);
    DMANow(3, spritesheetTiles, &CHARBLOCK[4], 32768/2);

    playSoundA(titleSong,TITLESONGLEN,TITLESONGFREQ, 1);

    //Set up control register and background control
    REG_DISPCTL = MODE0 | BG1_ENABLE | SPRITE_ENABLE | SPRITE_MODE_1D;
    REG_BG1CNT = BG_SIZE_SMALL | BG_8BPP | BG_CHARBLOCK(0) | BG_SCREENBLOCK(31);
}

//Navigates to start state
void goToStart() {
    state = START;
}

//Sets up start screen
void start() {
	hideSprites();

	waitForVBlank();

	DMANow(3, shadowOAM, OAM, 512);

    if (BUTTON_PRESSED(BUTTON_START)) {
        initializeGame();
		goToGame();
    }
    if (BUTTON_PRESSED(BUTTON_SELECT)) {
		goToInstruct();
    }
}

//Navigates to instructions
void goToInstruct() {
    state = INSTRUCT;
}

//Sets up instructions screen
void instruct() {
	//Load game background
	DMANow(3, instructPal, PALETTE, 256);
	DMANow(3, instructTiles, &CHARBLOCK[0], 6560);
	DMANow(3, instructMap, &SCREENBLOCK[31], 1024);

	waitForVBlank();

	DMANow(3, shadowOAM, OAM, 512);

    if (BUTTON_PRESSED(BUTTON_START)) {
        initializeGame();
        goToGame();
    }
    if (BUTTON_PRESSED(BUTTON_SELECT)) {
        initialize();
		goToStart();
    }
}

//Navigates to game state
void goToGame() {
	playSoundA(gameSong,GAMESONGLEN,GAMESONGFREQ, 1);
	if (circle == LIMBO){
		DMANow(3, limboPal, PALETTE, 256);
		DMANow(3, limboTiles, &CHARBLOCK[0], 6848);
		DMANow(3, limboMap, &SCREENBLOCK[31], 1024);
	} else {
		DMANow(3, gamePal, PALETTE, 256);
		DMANow(3, gameTiles, &CHARBLOCK[0], 10400);
		DMANow(3, gameMap, &SCREENBLOCK[31], 1024);
	}
	switch(circle) {
        case LUST:
            DMANow(3, lustTiles, &CHARBLOCK[2], 2048);
			DMANow(3, lustMap, &SCREENBLOCK[28], 1024);
            break; 
        case GLUTTONY:
            DMANow(3, gluttonyTiles, &CHARBLOCK[2], 2048);
			DMANow(3, gluttonyMap, &SCREENBLOCK[28], 1024);
            break;
        case GREED:
            DMANow(3, greedTiles, &CHARBLOCK[2], 2048);
			DMANow(3, greedMap, &SCREENBLOCK[28], 1024);
            break;
        case ANGER:
            DMANow(3, angerTiles, &CHARBLOCK[2], 2048);
			DMANow(3, angerMap, &SCREENBLOCK[28], 1024);
            break;
        case HERESY:
            DMANow(3, heresyTiles, &CHARBLOCK[2], 2048);
			DMANow(3, heresyMap, &SCREENBLOCK[28], 1024);
            break;
        case VIOLENCE:
            DMANow(3, violenceTiles, &CHARBLOCK[2], 2048);
			DMANow(3, violenceMap, &SCREENBLOCK[28], 1024);
            break;
        case FRAUD:
            DMANow(3, fraudTiles, &CHARBLOCK[2], 2048);
			DMANow(3, fraudMap, &SCREENBLOCK[28], 1024);
            break;
        case TREACHERY:
            DMANow(3, treacheryTiles, &CHARBLOCK[2], 2048);
			DMANow(3, treacheryMap, &SCREENBLOCK[28], 1024);
            break;        
    }     
    state = GAME;
}

//Run game state
void game() {
    updateGame();

    if (BUTTON_PRESSED(BUTTON_START)) {
        goToPause();
    } else if (circle == 9) {
    	if (graceCollected >= 10) {
    		goToWin();
    	} else {
    		goToPurgatory();
    	}
    } else if (livesLeft == 0) {
        goToLose();
    }
}

//Navigates to pause state
void goToPause() {
	pauseSound();
    state = PAUSE;
}

//Runs pause state
void pause() {
	//Load pause background
	DMANow(3, pauseTiles, &CHARBLOCK[0], 640);
	DMANow(3, pauseMap, &SCREENBLOCK[31], 1024);
	DMANow(3, pauseTopPal, PALETTE, 256);
	DMANow(3, pauseTopTiles, &CHARBLOCK[2], 2432);
	DMANow(3, pauseTopMap, &SCREENBLOCK[28], 1024);
    waitForVBlank();

    if (BUTTON_PRESSED(BUTTON_START)) {
        goToGame();
        unpauseSound();
    } else if (BUTTON_PRESSED(BUTTON_SELECT)) {
    	initialize();
        goToStart();
    }
}

//Navigates to win state
void goToWin() {
	playSoundA(heavenSong,HEAVENSONGLEN,HEAVENSONGFREQ, 1);

	//Load win background
	DMANow(3, winPal, PALETTE, 256);
	DMANow(3, winTiles, &CHARBLOCK[0], 9312);
	DMANow(3, winMap, &SCREENBLOCK[31], 1024);
    state = WIN;
}

//Runs win state
void win() {
	hideSprites();

    waitForVBlank();

    DMANow(3, shadowOAM, OAM, 512);

    if (BUTTON_PRESSED(BUTTON_START)) {
    	initialize();
        goToStart();
    }
}

//Navigates to lose state
void goToLose() {
	playSoundA(hellSong,HELLSONGLEN,HELLSONGFREQ, 1);

	//Load lose background
	DMANow(3, losePal, PALETTE, 256);
	DMANow(3, loseTiles, &CHARBLOCK[0], 7904);
	DMANow(3, loseMap, &SCREENBLOCK[31], 1024);
    state = LOSE;
}

//Runs lose state
void lose() {
	hideSprites();

    waitForVBlank();

    DMANow(3, shadowOAM, OAM, 512);

    if (BUTTON_PRESSED(BUTTON_START)) {
    	initialize();
        goToStart();
    }
}

//Navigates to purgatory state
void goToPurgatory() {
	playSoundA(purgatorySong, PURGATORYSONGLEN, PURGATORYSONGFREQ, 1);

	//Load purgatory background
	DMANow(3, purgatoryPal, PALETTE, 256);
	DMANow(3, purgatoryTiles, &CHARBLOCK[0], 12928);
	DMANow(3, purgatoryMap, &SCREENBLOCK[31], 1024);
	state = PURGATORY;	
}

//Runs purgatory state
void purgatory() {
	hideSprites();

    waitForVBlank();

    DMANow(3, shadowOAM, OAM, 512);

    if (BUTTON_PRESSED(BUTTON_START)) {
    	initialize();
        goToStart();
    }
}
