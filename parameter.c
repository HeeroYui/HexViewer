/**
 *******************************************************************************
 * @file parameter.c
 * @brief Parameters area (Sources)
 * @author Edouard DUPIN
 * @date 05/02/2011
 * @par Project
 * hexViewer
 *
 * @par Copyright
 * Copyright 2010 Edouard DUPIN, all right reserved
 *
 * This software is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY.
 *
 * Licence : GNU Lesser General Public License (LGPL) v3.0
 *
 *******************************************************************************
 */

#include "parameter.h"
#include <sys/ioctl.h>
#include <stdio.h>
// Parameter  Local Value : 

static uint32_t fileOfset = 0;
static uint32_t paddingOffset = 0;
static bool parmamModifier = true;


static showType_te curentType = SHOW_TYPE_HEX;
static showTypeSize_te curentTypeSize = SHOW_TYPE_SIZE_8;


extern fileProperties_ts fileProp[2];

void CleanDisplay(void)
{
	//system("clear");
	UpdateNumberOfRawAndColomn();
	printf(GO_TOP);
	for (int32_t iii=0; iii< GetNumberOfRaw(); iii++) {
		for (int32_t jjj=0; jjj < GetNumberOfColomn()-1; jjj++) {
			printf(" ");
		}
		if (iii< GetNumberOfRaw()-1) {
			printf("\n");
		}
	}
	printf(GO_TOP);
}




void setOfsetFile(int32_t offset)
{
	if (0 > offset) {
		offset = 0;
	}
	if(    offset > (int32_t)fileProp[0].size
	    && offset > (int32_t)fileProp[1].size) {
		// nothing to do
		return;
	}
	if (offset != (int32_t)fileOfset) {
		fileOfset = (uint32_t)offset;
		parmamModifier = true;
	}
}

void upDownOfsetFile(int32_t offset)
{
	int32_t tmp;
	tmp = fileOfset + (16 * offset);
	if (0 > tmp) {
		setOfsetFile(0);
	} else {
		setOfsetFile(tmp);
	}
}

uint32_t getOfsetFile(void)
{
	return fileOfset;
}

void displayPaddingOffset(int32_t size)
{
	paddingOffset += size;
	parmamModifier = true;
}

void displayPaddingOffsetClear(void)
{
	paddingOffset = 0;
	parmamModifier = true;
}

int32_t getPaddingOffsetFile(void)
{
	return paddingOffset;
}


bool getParamModification()
{
	if (parmamModifier == true) {
		parmamModifier = false;
		return true;
	} else {
		return false;
	}
}

void needRedraw(void) {
	parmamModifier = true;
}

void nextType(void)
{
	switch(curentType)
	{
		case SHOW_TYPE_HEX:
			curentType = SHOW_TYPE_DECIMAL_SIGNED;
			break;
		case SHOW_TYPE_DECIMAL_SIGNED:
			curentType = SHOW_TYPE_DECIMAL_UNSIGNED;
			break;
		case SHOW_TYPE_DECIMAL_UNSIGNED:
			curentType = SHOW_TYPE_HEX;
			break;
		default :
			curentType = SHOW_TYPE_HEX;
			break;
	}
	CleanDisplay();
	parmamModifier = true;
}

showType_te getType(void)
{
	return curentType;
}

void setType(showType_te newType)
{
	curentType = newType;
	parmamModifier = true;
}

void nextTypeSize(void)
{
	switch(curentTypeSize)
	{
		case SHOW_TYPE_SIZE_8:
			curentTypeSize = SHOW_TYPE_SIZE_16;
			break;
		case SHOW_TYPE_SIZE_16:
			curentTypeSize = SHOW_TYPE_SIZE_32;
			break;
		case SHOW_TYPE_SIZE_32:
			curentTypeSize = SHOW_TYPE_SIZE_64;
			break;
		case SHOW_TYPE_SIZE_64:
			curentTypeSize = SHOW_TYPE_SIZE_8;
			break;
		case SHOW_TYPE_SIZE_128:
			curentTypeSize = SHOW_TYPE_SIZE_8;
			break;
		default :
			curentTypeSize = SHOW_TYPE_SIZE_8;
			break;
	}
	CleanDisplay();
	parmamModifier = true;
}

showTypeSize_te getTypeSize(void)
{
	return curentTypeSize;
}
void setTypeSize(showTypeSize_te newType)
{
	curentTypeSize = newType;
	parmamModifier = true;
}


int32_t nbRaw = 20;
int32_t nbColomn = 70;

void UpdateNumberOfRawAndColomn(void)
{
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);
	nbRaw = w.ws_row;
	nbColomn = w.ws_col;
}


int32_t GetNumberOfRaw(void)
{
	return nbRaw;
}

int32_t GetNumberOfColomn(void)
{
	return nbColomn;
}


int32_t slotSize = -1;
bool slotEnable = false;
int32_t getSlotSize(void)
{
	if (true == slotEnable) {
		return slotSize;
	}
	return 0;
}
void setSlotSize(int32_t newSize)
{
	if (newSize<0) {
		newSize = 0;
	}
	slotSize = newSize;
}

void setSlotDisplayMode(bool enable)
{
	slotEnable = enable;
}
bool getSlotDisplayMode(void)
{
	return slotEnable;
}

bool displayHelp = false;
void setHelpDisplay(bool enable)
{
	displayHelp = enable;
}
bool getHelpDisplay(void)
{
	return displayHelp;
}

void cleanLine(void)
{
	printf(" |                                                                                                                                   | \r");
}
void endLine(void)
{
	printf(" |-----------------------------------------------------------------------------------------------------------------------------------| \n");
}
void usage(void)
{
	cleanLine();	printf(" | usage : hexViwer [option] [file_1] [file_2]\n");
	cleanLine();	printf("\t[option] : options:\n");
	cleanLine();	printf("\t\t[-d] : direct check of the error ...\n");
	cleanLine();	printf("\t[file_1] : Show the first file  only\n");
	cleanLine();	printf("\t[file_2] : if it was precise : Show the comparaison with the first file\n");
	cleanLine();	printf("\t\n");
	cleanLine();	printf("\tInside Usage : \n");
	cleanLine();	printf("\t\t[h]     diplay/Hide Help\n");
	cleanLine();	printf("\t\t[a]     Go to the start of the files\n");
	cleanLine();	printf("\t\t[z]     Go to the end of the files (the first push is the File 1, the second push is the file 2) \n");
	cleanLine();	printf("\t\t[q]     Quit the curent program\n");
	cleanLine();	printf("\t\t[s]     Change the view of the propram of the size of interpretation (8/16/32/64 bits)\n");
	cleanLine();	printf("\t\t[t]     Change the interpretation of Data (hexedecimal, Signed Decimal, Unigned Decimal)\n");
	cleanLine();	printf("\t\t[f]     Find the first Error when comparing the two files\n");
	cleanLine();	printf("\t\t[c]     Calibrate the delta between the 2 file (fist element !=0)\n");
	cleanLine();	printf("\t\t[UP]    Go up (5 lines)\n");
	cleanLine();	printf("\t\t[DOWN]  Go down (5 lines)\n");
	cleanLine();	printf("\t\t[LEFT]  Go up (one screen)\n");
	cleanLine();	printf("\t\t[RIGHT] Go down (one screen)\n");
	cleanLine();	printf("\t\tAdd padding : \n");
	cleanLine();	printf("\t\t\t[o]   Add  1 Byte  padding at the left file\n");
	cleanLine();	printf("\t\t\t[O]   Add 16 Bytes padding at the left file\n");
	cleanLine();	printf("\t\t\t[p]   Add  1 Byte  padding at the right file\n");
	cleanLine();	printf("\t\t\t[P]   Add 16 Bytes padding at the right file\n");
	cleanLine();	printf("\t\t\t[m]   reset padding\n");
	cleanLine();	printf("\t\tdiplay slot element\n");
	cleanLine();	printf("\t\t\t[j]   enable/disabe slot display\n");
	cleanLine();	printf("\t\t\t[u]   Decrement slot size  -1 \n");
	cleanLine();	printf("\t\t\t[U]   Decrement slot size -10 \n");
	cleanLine();	printf("\t\t\t[i]   Increment slot size  +1 \n");
	cleanLine();	printf("\t\t\t[I]   Increment slot size +10\n");
	cleanLine();	printf("\t\t\t[k]   Reset slot display\n");
	cleanLine();	printf("\t\n");
	cleanLine();	printf("\tCopyright: 2010 Edouard DUPIN, all right reserved\n");
	cleanLine();	printf("\tLicense: GNU Lesser General Public License (LGPL) v3.0\n");
	endLine();
}


