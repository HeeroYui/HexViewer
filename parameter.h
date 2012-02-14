/**
 *******************************************************************************
 * @file parameter.h
 * @brief Editeur De N'ours :
 * @author Edouard DUPIN
 * @date 05/02/2011
 * @par Project
 * Edn tool : hexViewer
 *
 * @version $Id$
 * 
 * @par Copyright
 * Copyright 2010 Edouard DUPIN, all right reserved
 *
 * This is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 3 of the License, or (at your option) any later
 * version.
 * 
 * This software is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
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

void nextTypeSize(void);
showTypeSize_te getTypeSize(void);

void displayPaddingOffset(int32_t size);
void displayPaddingOffsetClear(void);
int32_t getPaddingOffsetFile(void);


#define NB_HEARDER_RAW             (8)

void UpdateNumberOfRawAndColomn(void);
int32_t GetNumberOfRaw(void);
int32_t GetNumberOfColomn(void);

void CleanDisplay(void);

#endif

