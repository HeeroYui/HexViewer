/**
 *******************************************************************************
 * @file generalDefine.h
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

#ifndef __GENERAL_DEFINE_H__
#define __GENERAL_DEFINE_H__

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

typedef unsigned char                   uint8_t;
typedef   signed char                   int8_t;
typedef unsigned short int              uint16_t;
typedef   signed short int              int16_t;
typedef unsigned long int               uint32_t;
//typedef   signed long int               int32_t;
typedef unsigned long long int          uint64_t;
typedef   signed long long int          int64_t;
//typedef unsigned long long long int     uint128_t;
//typedef   signed long long long int     int128_t;

//regular colors
#define COLOR_BLACK         "\e[0;30m"
#define COLOR_RED           "\e[0;31m"
#define COLOR_GREEN         "\e[0;32m"
#define COLOR_YELLOW        "\e[0;33m"
#define COLOR_BLUE          "\e[0;34m"
#define COLOR_MAGENTA       "\e[0;35m"
#define COLOR_CYAN          "\e[0;36m"
#define COLOR_WHITE         "\e[0;37m"
    
//emphasized (bolded) colors
#define COLOR_BOLD_BLACK         "\e[1;30m"
#define COLOR_BOLD_RED           "\e[1;31m"
#define COLOR_BOLD_GREEN         "\e[1;32m"
#define COLOR_BOLD_YELLOW        "\e[1;33m"
#define COLOR_BOLD_BLUE          "\e[1;34m"
#define COLOR_BOLD_MAGENTA       "\e[1;35m"
#define COLOR_BOLD_CYAN          "\e[1;36m"
#define COLOR_BOLD_WHITE         "\e[1;37m"
    
//background colors
#define COLOR_BG_BLACK         "\e[40m"
#define COLOR_BG_RED           "\e[41m"
#define COLOR_BG_GREEN         "\e[42m"
#define COLOR_BG_YELLOW        "\e[43m"
#define COLOR_BG_BLUE          "\e[44m"
#define COLOR_BG_MAGENTA       "\e[45m"
#define COLOR_BG_CYAN          "\e[46m"
#define COLOR_BG_WHITE         "\e[47m"
// Return to the normal color setings
#define COLOR_NORMAL         "\e[0m"

#define MOUSE_REPORTING_ENABLE    "\e[?9h"
#define MOUSE_REPORTING_DISABLE   "\e[?9l"

#define CURSOR_DISPLAY_DISABLE    "\e[?25l"
#define CURSOR_DISPLAY_ENABLE     "\e[?12l\e[?25h"

//go to the Top of bash
#define GO_TOP         "\e[0;0f"


#define NB_DATA_PER_LINE    (4)



typedef enum {
    SHOW_TYPE_HEX,
    SHOW_TYPE_DECIMAL_SIGNED,
    SHOW_TYPE_DECIMAL_UNSIGNED
} showType_te;


typedef enum {
    SHOW_TYPE_SIZE_8,
    SHOW_TYPE_SIZE_16,
    SHOW_TYPE_SIZE_32,
    SHOW_TYPE_SIZE_64,
    SHOW_TYPE_SIZE_128
} showTypeSize_te;


#endif
