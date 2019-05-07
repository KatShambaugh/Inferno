#include "spritesheet.h"
#include "myLib.h"
#include "gameplay.h"
#include <stdlib.h>
#include "lust.h"
#include "game.h"
#include "gluttony.h"
#include "greed.h"
#include "anger.h"
#include "heresy.h"
#include "violence.h"
#include "fraud.h"
#include "treachery.h"
#include "collect.h"
#include "sound.h"
#include "sword.h"

//Initializes the game in the limbo level
void initializeGame() {
	circle = LIMBO;
	graceCollected = 0;
    livesLeft = 3;
    bossNumber = 0;

    //Make sure all enemies are inactive
    for (int i = 1; i < ENEMYCOUNT; i++) {
        enemies[i].active = 0;
    }

    //Sets attributes for life sprites
    for (int i = 0; i < livesLeft; i++) {
        shadowOAM[ENEMYCOUNT + 1 + i].attr0 = ATTR0_REGULAR | ATTR0_8BPP | ATTR0_SQUARE | 0;
        shadowOAM[ENEMYCOUNT + 1 + i].attr1 = ATTR1_SMALL | 17 * i;
        shadowOAM[ENEMYCOUNT + 1 + i].attr2 = ATTR2_TILEID(2, 20);
    }
    
    //Initializes all of the grace
    for(int i = 0; i < GRACECOUNT; i++) {
        grace[i].row = rand() % 80 + 50;
        grace[i].col = rand() % 220 + 10;
        grace[i].active = 0;
        grace[i].width = 8;
        grace[i].height = 8;
        grace[i].collected = 0;
    }

    //Initializes the player
    player.row = 140;
    player.col = 130;
    player.rdel = 10;
    player.cdel = 10;
    player.width = 16;
    player.height = 16;
    player.armed = 0;

    //Sets attributes for player sprite 
    shadowOAM[0].attr0 = ATTR0_REGULAR | ATTR0_8BPP | ATTR0_SQUARE | player.row;
    shadowOAM[0].attr1 = ATTR1_SMALL | player.col;
    shadowOAM[0].attr2 = ATTR2_TILEID(2, 0);
    
    //Sets attributes for sword sprite
    shadowOAM[126].attr0 = ATTR0_REGULAR | ATTR0_8BPP | ATTR0_SQUARE | (player.row - 5);
    shadowOAM[126].attr1 = ATTR1_TINY | (player.col + 10);
    shadowOAM[126].attr2 = ATTR2_TILEID(2, 10);

    //Initializes the key to enter hell
    key.row = rand() % 80 + 80;
    key.col = rand() % 220 + 10;
    key.width = 16;
    key.height = 16;
    key.active = 1;

    //Sets attributes for key sprite
    shadowOAM[127].attr0 = ATTR0_REGULAR | ATTR0_8BPP | ATTR0_SQUARE | key.row;
    shadowOAM[127].attr1 = ATTR1_SMALL | key.col;
    shadowOAM[127].attr2 = ATTR2_TILEID(2, 12);

    //Initializes the fireballs
    for(int i = 0; i < FIREBALLCOUNT; i++) {
        fireballs[i].row = 150;
        fireballs[i].col = 70;
        fireballs[i].speed = 1;
        fireballs[i].active = 0;
        fireballs[i].width = 8;
        fireballs[i].height = 8;
    }
}

//Initializes each successive level
void initializeLevel() {
    enemiesLeft = circle;

    //Initializes regular enemies
    int randNum = (rand() % (enemiesLeft)) + 1;	//Picks random enemy to be the keyholder
    for(int i = 1; i <= enemiesLeft; i++) {
        enemies[i].row = rand() % 80 + 45;
        enemies[i].col = rand() % 210 + 10;
        enemies[i].rdel = 1;
        enemies[i].cdel = 1;
        enemies[i].active = 1;
        enemies[i].width = 16;
        enemies[i].height = 16;
        if ((randNum == i) || (enemiesLeft == 1)) {
            enemies[i].special = 1;
        } else {
            enemies[i].special = 0;
        }
        enemies[i].boss = 0;
    }

    //Initializes boss enemies
    for (int i = 9; i < 18; i++) {
        enemies[i].row = rand() % 80 + 45;
        enemies[i].col = rand() % 210 + 10;
        enemies[i].rdel = 1;
        enemies[i].cdel = 1;
        enemies[i].active = 0;
        enemies[i].width = 16;
        enemies[i].height = 16;
        enemies[i].boss = 1;
    }

    //Sets attributes for all enemy sprites
    for (int i = 1; i < ENEMYCOUNT; i++) {
    	if (enemies[i].active) {
        	shadowOAM[i].attr0 = ATTR0_REGULAR | ATTR0_8BPP | ATTR0_SQUARE | enemies[i].row;
        	shadowOAM[i].attr1 = ATTR1_SMALL | enemies[i].col;
        	shadowOAM[i].attr2 = ATTR2_TILEID(0, enemyID);
        } else {
        	shadowOAM[i].attr0 = ATTR0_HIDE;
        }
    }

    updateE = 0;

    //Reinitializes key for each level
    key.row = rand() % 80 + 50;
    key.col = rand() % 220 + 10;
    key.active = 0;

    //Sets attributes for key sprite (again)
    shadowOAM[127].attr0 = ATTR0_HIDE;
    shadowOAM[127].attr2 = ATTR2_TILEID(2, 12);

    //Makes all uncollected grace inactive
    for(int i = 0; i < GRACECOUNT; i++) {
        grace[i].active = 0;
    }

    //Sets the next grace to be active for the level
    grace[circle].active = 1;

    //Sets attributes for grace sprites
    for (int i = 0; i < GRACECOUNT; i++) {
        if (grace[i].active) {
    	    shadowOAM[22 + i].attr0 = ATTR0_REGULAR | ATTR0_8BPP | ATTR0_SQUARE | grace[i].row;
            shadowOAM[22 + i].attr1 = ATTR1_TINY | grace[i].col;
            shadowOAM[22 + i].attr2 = ATTR2_TILEID(2, 8);
        } else if (!grace[i].collected) {
        	shadowOAM[22 + i].attr0 = ATTR0_HIDE;
        }
    }
}

//Updates the game every cycle
void updateGame() {
    updatePlayer();

    //Update all of the grace
    for (int i = 0; i < GRACECOUNT; i++) {
        updateGrace(&grace[i], 22 + i);
    }

    updateKey();

    updateFireballs();

    //Update the enemies only every (11 - circle) cycles so they get progressively faster
    updateE++;
    if (updateE == (11 - circle)) {
        for (int i = 1; i < ENEMYCOUNT; i++) {
            updateEnemy(&enemies[i], i);
        }
        updateE = 0;
    }

    //Activate boss enemies
    if (enemiesLeft == 0) {
        if (circle == 2) {
            shadowOAM[9].attr0 = ATTR0_REGULAR | ATTR0_8BPP | ATTR0_SQUARE | enemies[9].row;
            shadowOAM[9].attr1 = ATTR1_SMALL | enemies[9].col;
            shadowOAM[9].attr2 = ATTR2_TILEID(4, 0); 
            enemies[9].active = 1;   
        }
        if (circle == 4) {
            shadowOAM[10].attr0 = ATTR0_REGULAR | ATTR0_8BPP | ATTR0_SQUARE | enemies[10].row;
            shadowOAM[10].attr1 = ATTR1_SMALL | enemies[10].col;
            shadowOAM[10].attr2 = ATTR2_TILEID(4, 8);
            shadowOAM[11].attr0 = ATTR0_REGULAR | ATTR0_8BPP | ATTR0_SQUARE | enemies[11].row;
            shadowOAM[11].attr1 = ATTR1_SMALL | enemies[11].col;
            shadowOAM[11].attr2 = ATTR2_TILEID(4, 8);    
            enemies[10].active = 1;  
            enemies[11].active = 1; 
        }
        if (circle == 6) {
            shadowOAM[12].attr0 = ATTR0_REGULAR | ATTR0_8BPP | ATTR0_SQUARE | enemies[12].row;
            shadowOAM[12].attr1 = ATTR1_SMALL | enemies[12].col;
            shadowOAM[12].attr2 = ATTR2_TILEID(4, 16); 
            enemies[12].active = 1;   
        }
        if (circle == 7) {
            shadowOAM[13].attr0 = ATTR0_REGULAR | ATTR0_8BPP | ATTR0_SQUARE | enemies[13].row;
            shadowOAM[13].attr1 = ATTR1_SMALL | enemies[13].col;
            shadowOAM[13].attr2 = ATTR2_TILEID(4, 24);
            shadowOAM[14].attr0 = ATTR0_REGULAR | ATTR0_8BPP | ATTR0_SQUARE | enemies[14].row;
            shadowOAM[14].attr1 = ATTR1_SMALL | enemies[14].col;
            shadowOAM[14].attr2 = ATTR2_TILEID(4, 24);
            shadowOAM[15].attr0 = ATTR0_REGULAR | ATTR0_8BPP | ATTR0_SQUARE | enemies[15].row;
            shadowOAM[15].attr1 = ATTR1_SMALL | enemies[15].col;
            shadowOAM[15].attr2 = ATTR2_TILEID(4, 24);
            shadowOAM[16].attr0 = ATTR0_REGULAR | ATTR0_8BPP | ATTR0_SQUARE | enemies[16].row;
            shadowOAM[16].attr1 = ATTR1_SMALL | enemies[16].col;
            shadowOAM[16].attr2 = ATTR2_TILEID(4, 24);
            enemies[13].active = 1;  
            enemies[14].active = 1;  
            enemies[15].active = 1;  
            enemies[16].active = 1;       
        }
        if (circle == 8) {
            shadowOAM[17].attr0 = ATTR0_REGULAR | ATTR0_8BPP | ATTR0_SQUARE | enemies[17].row;
            shadowOAM[17].attr1 = ATTR1_SMALL | enemies[17].col;
            enemies[17].active = 1;   
            int randTime = rand() % 100;
            if (randTime % 10 == 0) {
                shadowOAM[17].attr2 = ATTR2_TILEID(4, 40);
            } else {
                shadowOAM[17].attr2 = ATTR2_TILEID(4, 32);
            } 
        }
    }

	waitForVBlank();
    DMANow(3, shadowOAM, OAM, 512);
}

//Handles player controls
void updatePlayer() {
	if ((BUTTON_HELD(BUTTON_LEFT)) && (player.col >= player.cdel)) {
        player.col--;
        shadowOAM[0].attr1 = ATTR1_SMALL | player.col;
        shadowOAM[126].attr1 = ATTR1_TINY | (player.col + 10);
    } else if ((BUTTON_HELD(BUTTON_RIGHT)) && (player.col + player.width - 1 < SCREENWIDTH - player.cdel)) {
        player.col++;
        shadowOAM[0].attr1 = ATTR1_SMALL | player.col;
        shadowOAM[126].attr1 = ATTR1_TINY | (player.col + 10);
    } 
    if ((BUTTON_HELD(BUTTON_UP)) && (player.row >= player.rdel + 40)) {
        player.row--;
        shadowOAM[0].attr0 = ATTR0_REGULAR | ATTR0_8BPP | ATTR0_SQUARE | player.row;
        shadowOAM[126].attr0 = ATTR0_REGULAR | ATTR0_8BPP | ATTR0_SQUARE | (player.row - 5);
    } else if ((BUTTON_HELD(BUTTON_DOWN)) && (player.row + player.height - 1 < SCREENHEIGHT - player.rdel)) {
        player.row++;
        shadowOAM[0].attr0 = ATTR0_REGULAR | ATTR0_8BPP | ATTR0_SQUARE | player.row;
        shadowOAM[126].attr0 = ATTR0_REGULAR | ATTR0_8BPP | ATTR0_SQUARE | (player.row - 5);
    }

    //Cue sword animation for blocking
    if (BUTTON_HELD(BUTTON_L)) {
    	shadowOAM[126].attr2 = ATTR2_TILEID(2, 28);
    } else {
    	shadowOAM[126].attr2 = ATTR2_TILEID(2, 10);
    }

    //Controls cheat
    if (circle == 4) {
    	if ((player.col == player.cdel) && (player.row + player.height - 1 == SCREENHEIGHT - player.rdel)) {
    		cheat();
    	}
    }
}

//Handles enemy movement and collision
void updateEnemy(ENEMY* e, int spriteID) {
    if (e->active) {
        if (e->row <= 50 || e->row + e->height-1 >= 130) {
            e->rdel *= -1;
        }
        if (e->col <= 1 || e->col + e->width-1 >= SCREENWIDTH-2) {
            e->cdel *= -1;
        }

        e->row += e->rdel;
        e->col += e->cdel;

        shadowOAM[spriteID].attr0 = ATTR0_REGULAR | ATTR0_8BPP | ATTR0_SQUARE | e->row;
        shadowOAM[spriteID].attr1 = ATTR1_SMALL | e->col;

        //Handle enemy-sword collisions
        if (collision(e->row, e->col, e->height, e->width, (player.row - 10), (player.col + 10), 8, 8)) {
        	if (BUTTON_PRESSED(BUTTON_A)) {
        		e->active = 0;
                playSoundB(sword,SWORDLEN,SWORDFREQ, 0);
                enemiesLeft--;
            	shadowOAM[spriteID].attr0 = ATTR0_HIDE;
            	//if keyholder, reveal key
            	if (e->special == 1) {
                	key.active = 1;
                	shadowOAM[127].attr0 = ATTR0_REGULAR | ATTR0_8BPP | ATTR0_SQUARE | key.row;
                	shadowOAM[127].attr1 = ATTR1_SMALL | key.col;
            	}
            	//If boss, reveal bonus grace
            	if (e->boss == 1) {
                    bossNumber++;
                	grace[bossNumber + 8].active = 1;
                	shadowOAM[30 + bossNumber].attr0 = ATTR0_REGULAR | ATTR0_8BPP | ATTR0_SQUARE | grace[bossNumber + 8].row;
                	shadowOAM[30 + bossNumber].attr1 = ATTR1_TINY | grace[bossNumber + 8].col;
                	shadowOAM[30 + bossNumber].attr2 = ATTR2_TILEID(2, 8);
            	}
        	}
        }
        //Handle enemy fireballs
        int randTiming = rand() % 150;
    	if ((randTiming == 0) && (enemiesLeft > 1)) {
        	//Initializes enemy fireball
        	int randEnemy = rand() % enemiesLeft + 1;
        	if (randEnemy > enemiesLeft) {
        		randEnemy = enemiesLeft;
        	}
            if (enemies[randEnemy].active == 1) {
                fireballs[0].active = 1;
                fireballs[0].row = enemies[randEnemy].row;
                fireballs[0].col = enemies[randEnemy].col;
    
                shadowOAM[125].attr0 = ATTR0_REGULAR | ATTR0_8BPP | ATTR0_SQUARE | fireballs[0].row;
                shadowOAM[125].attr1 = ATTR1_SMALL | fireballs[0].col;
                shadowOAM[125].attr2 = ATTR2_TILEID(2, 30);
            }
    	}
    }
}

//Handles fireball movement and collision
void updateFireballs() {
    if (fireballs[0].active == 1) {
        //Move the enemy fireball down
        fireballs[0].row += fireballs[0].speed;
        shadowOAM[125].attr0 = ATTR0_REGULAR | ATTR0_8BPP | ATTR0_SQUARE | fireballs[0].row;
    	shadowOAM[125].attr1 = ATTR1_SMALL | fireballs[0].col;
    	shadowOAM[125].attr2 = ATTR2_TILEID(2, 30);

        //Check for fireball-player collisions
        if (collision(fireballs[0].row, fireballs[0].col, 8, 8, player.row, player.col, player.height, player.width)) {
            if (BUTTON_HELD(BUTTON_L)) {
            	fireballs[0].active = 0;
            	shadowOAM[125].attr0 = ATTR0_HIDE | 0;
            } else {
            	fireballs[0].active = 0;
            	livesLeft--;
            	shadowOAM[125].attr0 = ATTR0_HIDE | 0;
            	shadowOAM[ENEMYCOUNT + 1 + livesLeft].attr0 = ATTR0_HIDE;
        	}
        }

        //Hide fireballs that go off the screen
        if(fireballs[0].row > 150) {
            fireballs[0].row = 160;
            fireballs[0].active = 0;
            shadowOAM[125].attr0 = ATTR0_HIDE;
        }
    }
    DMANow(3, shadowOAM, OAM, 512);
}

// Handle grace-player collisions
void updateGrace(GRACE* g, int spriteID) {
    if (g->active) {
        if ((BUTTON_HELD(BUTTON_B)) && (collision(g->row, g->col, g->height, g->width, player.row, player.col, player.height, player.width))) {
            g->active = 0;
            g->collected = 1;
            playSoundB(collect,COLLECTLEN,COLLECTFREQ, 0);
            shadowOAM[spriteID].attr0 = ATTR0_REGULAR | ATTR0_8BPP | ATTR0_SQUARE | 3;
        	shadowOAM[spriteID].attr1 = ATTR1_TINY | ((9 * graceCollected) + 65);
            graceCollected++;
        }
    }
}

//Handles key-player collisions and level jumping
void updateKey() {
    if (key.active == 1) {
        // Handle key-player collisions
        if ((BUTTON_HELD(BUTTON_B)) && (collision(key.row, key.col, key.height, key.width, player.row, player.col, player.height, player.width))) {
            key.active = 0;
            playSoundB(collect,COLLECTLEN,COLLECTFREQ, 0);
            shadowOAM[127].attr0 = ATTR0_HIDE;
            //Go to next state level here
            if (circle < 9) {
            	circle++;
            }
            //Handles jumping between levels
            switch(circle) {
                case LUST:
                    initializeLust();
                    break; 
                case GLUTTONY:
                    initializeGluttony();
                    break;
                case GREED:
                    initializeGreed();
                    break;
                case ANGER:
                    initializeAnger();
                    break;
                case HERESY:
                    initializeHeresy();
                    break;
                case VIOLENCE:
                    initializeViolence();
                    break;
                case FRAUD:
                    initializeFraud();
                    break;
                case TREACHERY:
                    initializeTreachery();
                    break;
            }        
        }
    }
}

//Reveals 5 extra pieces of grace
void cheat() {
	for (int i = 0; i < 5; i++) {
		grace[i + 17].active = 1;
    	shadowOAM[39 + i].attr0 = ATTR0_REGULAR | ATTR0_8BPP | ATTR0_SQUARE | grace[i + 17].row;
        shadowOAM[39 + i].attr1 = ATTR1_TINY | grace[i + 17].col;
        shadowOAM[39 + i].attr2 = ATTR2_TILEID(2, 8);
    }
}


//Initialize the "lust" layer
void initializeLust() {
    enemyID = 0;
    //Enable second background
    REG_DISPCTL = MODE0 | BG1_ENABLE | BG2_ENABLE | SPRITE_ENABLE | SPRITE_MODE_1D;
    REG_BG2CNT = BG_SIZE_SMALL | BG_8BPP | BG_CHARBLOCK(2) | BG_SCREENBLOCK(28);
	
	DMANow(3, gamePal, PALETTE, 256);
	DMANow(3, gameTiles, &CHARBLOCK[0], 10400);
	DMANow(3, gameMap, &SCREENBLOCK[31], 1024);
	DMANow(3, lustTiles, &CHARBLOCK[2], 2048);
	DMANow(3, lustMap, &SCREENBLOCK[28], 1024);
    
    //Call initialize game again to "restart" level
    initializeLevel();
}

//Initialize the "gluttony" layer
void initializeGluttony() {
    enemyID = 8;
    DMANow(3, gluttonyTiles, &CHARBLOCK[2], 2048);
	DMANow(3, gluttonyMap, &SCREENBLOCK[28], 1024);
    
    //Call initialize game again to "restart" level
    initializeLevel();
}

//Initialize the "greed" layer
void initializeGreed() {
    enemyID = 16;
    DMANow(3, greedTiles, &CHARBLOCK[2], 2048);
	DMANow(3, greedMap, &SCREENBLOCK[28], 1024);

    //Call initialize game again to "restart" level
    initializeLevel();
}

//Initialize the "Anger" layer
void initializeAnger() {
    enemyID = 24;
    DMANow(3, angerTiles, &CHARBLOCK[2], 2048);
	DMANow(3, angerMap, &SCREENBLOCK[28], 1024);

    //Call initialize game again to "restart" level
    initializeLevel();
}

//Initialize the "heresy" layer
void initializeHeresy() {
    enemyID = 32;
    DMANow(3, heresyTiles, &CHARBLOCK[2], 2048);
	DMANow(3, heresyMap, &SCREENBLOCK[28], 1024);

    //Call initialize game again to "restart" level
    initializeLevel();
}

//Initialize the "violence" layer
void initializeViolence() {
    enemyID = 40;
    DMANow(3, violenceTiles, &CHARBLOCK[2], 2048);
	DMANow(3, violenceMap, &SCREENBLOCK[28], 1024);

    //Call initialize game again to "restart" level
    initializeLevel();
}

//Initialize the "fraud" layer
void initializeFraud() {
    enemyID = 48;
    DMANow(3, fraudTiles, &CHARBLOCK[2], 2048);
	DMANow(3, fraudMap, &SCREENBLOCK[28], 1024);

    //Call initialize game again to "restart" level
    initializeLevel();
}

//Initialize the "treachery" layer
void initializeTreachery() {
    enemyID = 56;
    DMANow(3, treacheryTiles, &CHARBLOCK[2], 2048);
	DMANow(3, treacheryMap, &SCREENBLOCK[28], 1024);

    //Call initialize game again to "restart" level
    initializeLevel();
}