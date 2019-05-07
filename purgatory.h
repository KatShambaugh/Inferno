
//{{BLOCK(purgatory)

//======================================================================
//
//	purgatory, 256x256@8, 
//	+ palette 256 entries, not compressed
//	+ 404 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 25856 + 2048 = 28416
//
//	Time-stamp: 2019-04-23, 11:10:05
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_PURGATORY_H
#define GRIT_PURGATORY_H

#define purgatoryTilesLen 25856
extern const unsigned short purgatoryTiles[12928];

#define purgatoryMapLen 2048
extern const unsigned short purgatoryMap[1024];

#define purgatoryPalLen 512
extern const unsigned short purgatoryPal[256];

#endif // GRIT_PURGATORY_H

//}}BLOCK(purgatory)
