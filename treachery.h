
//{{BLOCK(treachery)

//======================================================================
//
//	treachery, 256x256@8, 
//	+ palette 256 entries, not compressed
//	+ 64 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 4096 + 2048 = 6656
//
//	Time-stamp: 2019-04-17, 17:22:50
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_TREACHERY_H
#define GRIT_TREACHERY_H

#define treacheryTilesLen 4096
extern const unsigned short treacheryTiles[2048];

#define treacheryMapLen 2048
extern const unsigned short treacheryMap[1024];

#define treacheryPalLen 512
extern const unsigned short treacheryPal[256];

#endif // GRIT_TREACHERY_H

//}}BLOCK(treachery)
