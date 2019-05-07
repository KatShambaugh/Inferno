
//{{BLOCK(limbo)

//======================================================================
//
//	limbo, 256x256@8, 
//	+ palette 256 entries, not compressed
//	+ 214 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 13696 + 2048 = 16256
//
//	Time-stamp: 2019-04-17, 17:26:45
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_LIMBO_H
#define GRIT_LIMBO_H

#define limboTilesLen 13696
extern const unsigned short limboTiles[6848];

#define limboMapLen 2048
extern const unsigned short limboMap[1024];

#define limboPalLen 512
extern const unsigned short limboPal[256];

#endif // GRIT_LIMBO_H

//}}BLOCK(limbo)
