/**
 *******************************************************************************
 * @file parameter.c
 * @brief Editeur De N'ours :
 * @author Edouard DUPIN
 * @date 05/02/2011
 * @par Project
 * Edn tool : hexViewer
 *
 * @par Copyright
 * Copyright 2010 Edouard DUPIN, all right reserved
 *
 * This software is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY.
 *
 * Licence summary : 
 *    You can modify and redistribute the sources code and binaries.
 *    You can send me the bug-fix
 *    You can not earn money with this Software (if the source extract from Edn
 *        represent less than 50% of original Sources)
 * Term of the licence in in the file licence.txt.
 *
 *******************************************************************************
 */

#include "parameter.h"
// Parameter  Local Value : 

static U32 fileOfset = 0;
static bool parmamModifier = true;


static showType_te curentType = SHOW_TYPE_HEX;
static showTypeSize_te curentTypeSize = SHOW_TYPE_SIZE_8;


extern U32 filesize[2];

void setOfsetFile(I32 offset)
{
    if (0 > offset)
    {
        offset = 0;
    }
    if (    offset > (I32)filesize[0]
         && offset > (I32)filesize[1])
    {
        // nothing to do
        return;
    }
    if (offset != (I32)fileOfset)
    {
        fileOfset = (U32)offset;
        parmamModifier = true;
    }
}

void upDownOfsetFile(I32 offset)
{
    I32 tmp;
    tmp = fileOfset + (16 * offset);
    if (0 > tmp)
    {
        setOfsetFile(0);
    }
    else
    {
        setOfsetFile(tmp);
    }
}

U32 getOfsetFile(void)
{
    return fileOfset;
}

bool getParamModification()
{
    if (parmamModifier == true)
    {
        parmamModifier = false;
        return true;
    }
    else
    {
        return false;
    }
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
    system("clear");
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
            curentTypeSize = SHOW_TYPE_SIZE_8;
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
    system("clear");
    parmamModifier = true;
}

showTypeSize_te getTypeSize(void)
{
    return curentTypeSize;
}
