
//{{BLOCK(lust)

//======================================================================
//
//	lust, 256x256@8, 
//	+ palette 256 entries, not compressed
//	+ 64 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 4096 + 2048 = 6656
//
//	Time-stamp: 2019-04-17, 16:51:00
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_LUST_H
#define GRIT_LUST_H

#define lustTilesLen 4096
extern const unsigned short lustTiles[2048];

#define lustMapLen 2048
extern const unsigned short lustMap[1024];

#define lustPalLen 512
extern const unsigned short lustPal[256];

#endif // GRIT_LUST_H

//}}BLOCK(lust)
