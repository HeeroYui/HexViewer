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

void setOfsetFile(I32 offset);
void upDownOfsetFile(I32 offset);
U32 getOfsetFile(void);

bool getParamModification();

void nextType(void);
showType_te getType(void);

void nextTypeSize(void);
showTypeSize_te getTypeSize(void);

#endif

