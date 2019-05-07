
//{{BLOCK(gluttony)

//======================================================================
//
//	gluttony, 256x256@8, 
//	+ palette 256 entries, not compressed
//	+ 64 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 4096 + 2048 = 6656
//
//	Time-stamp: 2019-04-17, 16:58:06
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_GLUTTONY_H
#define GRIT_GLUTTONY_H

#define gluttonyTilesLen 4096
extern const unsigned short gluttonyTiles[2048];

#define gluttonyMapLen 2048
extern const unsigned short gluttonyMap[1024];

#define gluttonyPalLen 512
extern const unsigned short gluttonyPal[256];

#endif // GRIT_GLUTTONY_H

//}}BLOCK(gluttony)
