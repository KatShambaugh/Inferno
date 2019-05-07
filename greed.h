
//{{BLOCK(greed)

//======================================================================
//
//	greed, 256x256@8, 
//	+ palette 256 entries, not compressed
//	+ 65 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 4160 + 2048 = 6720
//
//	Time-stamp: 2019-04-17, 17:02:30
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_GREED_H
#define GRIT_GREED_H

#define greedTilesLen 4160
extern const unsigned short greedTiles[2080];

#define greedMapLen 2048
extern const unsigned short greedMap[1024];

#define greedPalLen 512
extern const unsigned short greedPal[256];

#endif // GRIT_GREED_H

//}}BLOCK(greed)
