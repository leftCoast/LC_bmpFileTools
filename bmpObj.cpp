#include "bmpObj.h"
#include "resizeBuff.h"

bmpObj::bmpObj(int inX,int inY,int inWidth,int inHeight,char* bmpPath)
	: drawObj(inX,inY,inWidth,inHeight) {
		
	mRowArray = NULL;
	setSourceRect(0,0,inWidth,inHeight);			// Default source is top left of bitmap, our size.
	mBMPObj = new bmpImage();
	mPath = NULL;
	if (bmpPath) {
		resizeBuff(strlen(bmpPath)+1,&mPath);
		strcpy(mPath,bmpPath);
	}
}

		
bmpObj::~bmpObj(void) {

	if (mBMPObj) delete(mBMPObj);
	resizeBuff(0,(void**)&mRowArray);
}

	
// Some stuff must wait 'till our hardware is up and running. like SD cards.	
bool bmpObj::begin(void) {

	if (setImage(mPath)) {					// If we can set it up as this image..
		resizeBuff(0,&mPath);				// Then we can dump the copy of our path. Its in the bmpImage thing now.
		return true;							// And we return success.
	}
	return false;									// If we land here? Something went wrong.
}



// Setup the source rect for reading from the .bmp file.
void bmpObj::setSourceRect(int sX,int sY,int sWidth,int sHeight) {
	mSourceRect.setRect(sX,sY,sWidth,sHeight);
	resizeBuff(sizeof(RGBpack)*sWidth,(void**)&mRowArray);
}


bool bmpObj::setImage(char* bmpPath) {
	
	if (bmpPath && mBMPObj) {					// If we have a file path..
		if (mBMPObj->openDocFile(mPath)) {	// If we can open the pipe with our file path..
			return true;							// And we return success.
		}
	}
	return false;
}


void	bmpObj::drawSelf(void) {

	File		bmpFile;
	int		localY;
	int		syMax;
	colorObj	aColor;
	char*		filePath;
	
	filePath = mBMPObj->getDocFilePath();
	bmpFile = SD.open(filePath,FILE_READ);
	if (bmpFile) {
		mBMPObj->setGFile(&bmpFile);
		syMax = mSourceRect.y+mSourceRect.height;
		localY = y;
		for (int sourceY=mSourceRect.y;sourceY<syMax;sourceY++) {
			mBMPObj->getRow(sourceY,mRowArray,mSourceRect.width,mSourceRect.x);
			for (int i=0;i<mSourceRect.width;i++) {
				aColor.setColor(&(mRowArray[i]));
				screen->drawPixel(x+i,localY,&aColor);
			}
			localY++;
		}
		bmpFile.close();
		mBMPObj->setGFile(NULL);
	}
}