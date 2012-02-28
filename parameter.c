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


extern uint32_t filesize[2];

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
	if(    offset > (int32_t)filesize[0]
	    && offset > (int32_t)filesize[1]) {
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

