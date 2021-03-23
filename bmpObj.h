#ifndef bmpObj_h
#define bmpObj_h

#include <drawObj.h>
#include <bmpImage.h>


// Years later after so much messing about.
//
// This is to be the BASE CLASS for bitmap file drawing objects. Its a rect location on
// the screen that can spat a bitmap to itself. It just a draw object mixed with a bmpPipe.
// Want to do a picture, a button or an icon? Start with this. (Or just draw a bitmap)
//
// Basically this is the glue that hooks a bmpPipe to a drawObj.

class bmpObj :	public drawObj {

	public:
				bmpObj(int inX,int inY,int inwidth,int inHeight,char* bmpPath=NULL);
	virtual	~bmpObj(void);
	
	virtual	bool	begin(void);		// Some stuff must wait 'till our hardware is up and running. like SD cards.
				void	setSourceRect(int sX,int sY,int sWidth,int sHeight);
				bool	setImage(char* bmpPath);
	virtual	void	drawSelf(void);
	
				rect			mSourceRect;
				RGBpack*		mRowArray;
				char*			mPath;
				bmpImage*	mBMPObj;
};

#endif