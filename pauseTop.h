
//{{BLOCK(pauseTop)

//======================================================================
//
//	pauseTop, 256x256@8, 
//	+ palette 256 entries, not compressed
//	+ 76 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 4864 + 2048 = 7424
//
//	Time-stamp: 2019-04-24, 17:52:59
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_PAUSETOP_H
#define GRIT_PAUSETOP_H

#define pauseTopTilesLen 4864
extern const unsigned short pauseTopTiles[2432];

#define pauseTopMapLen 2048
extern const unsigned short pauseTopMap[1024];

#define pauseTopPalLen 512
extern const unsigned short pauseTopPal[256];

#endif // GRIT_PAUSETOP_H

//}}BLOCK(pauseTop)
