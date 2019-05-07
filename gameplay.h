//Constants
#define ENEMYCOUNT 18
#define GRACECOUNT 22
#define FIREBALLCOUNT 1

OBJ_ATTR shadowOAM[128];

enum {LIMBO, LUST, GLUTTONY, GREED, ANGER, HERESY, VIOLENCE, FRAUD, TREACHERY};
int circle;

int graceCollected;
int livesLeft;
int updateE;
int enemyID;
int enemiesLeft;
int bossNumber;

//Enemy Struct
typedef struct {
    int row;
    int col;
    int rdel;
    int cdel;
    int active;
    int height;
    int width;
    int special;
    int boss;
} ENEMY;

//Player struct
typedef struct {
    int row;
    int col;
    int rdel;
    int cdel;
    int width;
    int height;
    int armed;
} PLAYER;

//Grace struct
typedef struct {
    int row;
    int col;
    int active;
    int height;
    int width;
    int collected;
} GRACE;

//Key struct
typedef struct {
    int row;
    int col;
    int active;
    int height;
    int width;
} KEY;

//Fireball struct
typedef struct {
    int row;
    int col;
    int speed;
    int active;
    int height;
    int width;
} FIREBALL;

PLAYER player;
ENEMY enemies[ENEMYCOUNT];
GRACE grace[GRACECOUNT];
KEY key;
FIREBALL fireballs[FIREBALLCOUNT];

//Prototypes
void initializeGame();
void updateGame();
void updatePlayer();
void updateEnemy(ENEMY* e, int spriteID);
void updateGrace(GRACE* g, int spriteID);
void updateKey();
void updateFireballs();
void initializeLevel();
void initializeLust();
void initializeGluttony();
void initializeGreed();
void initializeAnger();
void initializeHeresy();
void initializeViolence();
void initializeFraud();
void initializeTreachery();
void cheat();