/**
 *******************************************************************************
 * @file parameter.h
 * @brief Parameters area (header)
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

#ifndef __PARAMETER_H__
#define __PARAMETER_H__

#include "generalDefine.h"

void setOfsetFile(int32_t offset);
void upDownOfsetFile(int32_t offset);
uint32_t getOfsetFile(void);

bool getParamModification();
void needRedraw(void);
void nextType(void);
showType_te getType(void);
void setType(showType_te newType);

void nextTypeSize(void);
showTypeSize_te getTypeSize(void);
void setTypeSize(showTypeSize_te newType);

void displayPaddingOffset(int32_t size);
void displayPaddingOffsetClear(void);
int32_t getPaddingOffsetFile(void);


#define NB_HEARDER_RAW             (8)

void UpdateNumberOfRawAndColomn(void);
int32_t GetNumberOfRaw(void);
int32_t GetNumberOfColomn(void);

void CleanDisplay(void);

#endif

