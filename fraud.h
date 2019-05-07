
//{{BLOCK(fraud)

//======================================================================
//
//	fraud, 256x256@8, 
//	+ palette 256 entries, not compressed
//	+ 64 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 4096 + 2048 = 6656
//
//	Time-stamp: 2019-04-17, 17:18:10
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_FRAUD_H
#define GRIT_FRAUD_H

#define fraudTilesLen 4096
extern const unsigned short fraudTiles[2048];

#define fraudMapLen 2048
extern const unsigned short fraudMap[1024];

#define fraudPalLen 512
extern const unsigned short fraudPal[256];

#endif // GRIT_FRAUD_H

//}}BLOCK(fraud)
