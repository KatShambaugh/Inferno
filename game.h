
//{{BLOCK(game)

//======================================================================
//
//	game, 256x256@8, 
//	+ palette 256 entries, not compressed
//	+ 325 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 20800 + 2048 = 23360
//
//	Time-stamp: 2019-04-23, 13:01:55
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_GAME_H
#define GRIT_GAME_H

#define gameTilesLen 20800
extern const unsigned short gameTiles[10400];

#define gameMapLen 2048
extern const unsigned short gameMap[1024];

#define gamePalLen 512
extern const unsigned short gamePal[256];

#endif // GRIT_GAME_H

//}}BLOCK(game)
