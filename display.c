/**
 *******************************************************************************
 * @file display.c
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
#include "display.h"

extern FILE *filePointer[2];
extern char fileName[2][2096];
void showConfiguration(void)
{
	showType_te myType = getType();
	showTypeSize_te mySize = getTypeSize();
	
	printf(GO_TOP);
	printf(COLOR_BOLD_GREEN"----------------------------------------------------------------------------------------------------------------------------\n"COLOR_NORMAL);
	printf(COLOR_GREEN);
	printf("| hewViewer    |  ofset : %7d octets  | ", (int)getOfsetFile());
	printf("  Type (t) : ");
	switch(myType)
	{
		case SHOW_TYPE_HEX:
			printf("Hexadecimal     ");
			break;
		case SHOW_TYPE_DECIMAL_SIGNED:
			printf("Decimal Signed  ");
			break;
		case SHOW_TYPE_DECIMAL_UNSIGNED:
			printf("Decimal Unsigned");
			break;
		default :
			printf("?               ");
			break;
	}
	printf(" | ");
	printf("  Size (s) : ");
	switch(mySize)
	{
		case SHOW_TYPE_SIZE_8:
			printf("  8 bits   ");
			break;
		case SHOW_TYPE_SIZE_16:
			printf(" 16 bits   ");
			break;
		case SHOW_TYPE_SIZE_32:
			printf(" 32 bits   ");
			break;
		case SHOW_TYPE_SIZE_64:
			printf(" 64 bits   ");
			break;
		case SHOW_TYPE_SIZE_128:
			printf("128 bits   ");
			break;
		default :
			printf("  ? bits   ");
			break;
	}
	printf(COLOR_NORMAL"\n");
	printf(COLOR_GREEN"| File Left  << | " COLOR_BOLD_GREEN "%s\n" COLOR_NORMAL, fileName[0]);
	printf(COLOR_GREEN"| File Right >> | " COLOR_BOLD_GREEN "%s\n"COLOR_NORMAL,   fileName[1]);

	printf(COLOR_BOLD_GREEN"----------------------------------------------------------------------------------------------------------------------------\n"COLOR_NORMAL);
}

void printNoElement(showType_te localType, showTypeSize_te localSize)
{
	switch(localType)
	{
		case SHOW_TYPE_HEX:
			switch(localSize)
			{
				case SHOW_TYPE_SIZE_8:
					printf("   ");
					break;
				case SHOW_TYPE_SIZE_16:
					printf("     ");
					break;
				case SHOW_TYPE_SIZE_32:
					printf("         ");
					break;
				case SHOW_TYPE_SIZE_64:
					printf("                 ");
					break;
				default:
					break;
			}
			break;
		case SHOW_TYPE_DECIMAL_UNSIGNED:
		case SHOW_TYPE_DECIMAL_SIGNED:
			switch(localSize)
			{
				case SHOW_TYPE_SIZE_8:
					printf("     ");
					break;
				case SHOW_TYPE_SIZE_16:
					printf("        ");
					break;
				case SHOW_TYPE_SIZE_32:
					printf("               ");
					break;
				case SHOW_TYPE_SIZE_64:
					printf("                      ");
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
	
}

void printElement(uint64_t data, showType_te localType, showTypeSize_te localSize, bool error, bool outOfRange)
{
	if (false == outOfRange) {
		printf(COLOR_CYAN);
	} else if (true == error) {
		printf(COLOR_BOLD_RED);
	}
	switch(localType)
	{
		case SHOW_TYPE_HEX:
			switch(localSize)
			{
				case SHOW_TYPE_SIZE_8:
					printf("%02x"COLOR_NORMAL" ", (unsigned int)((uint8_t)data));
					break;
				case SHOW_TYPE_SIZE_16:
					printf("%04x"COLOR_NORMAL" ", (unsigned int)((uint16_t)data));
					break;
				case SHOW_TYPE_SIZE_32:
					printf("%08x"COLOR_NORMAL" ", (unsigned int)((uint32_t)data));
					break;
				case SHOW_TYPE_SIZE_64:
					printf("%08x%08x"COLOR_NORMAL" ", (unsigned int)((uint32_t)(data>>32)), (unsigned int)((uint32_t)data));
					break;
				default:
					break;
			}
			break;
		case SHOW_TYPE_DECIMAL_SIGNED:
			switch(localSize)
			{
				case SHOW_TYPE_SIZE_8:
					printf("%4d"COLOR_NORMAL" ", ((int8_t)data));
					break;
				case SHOW_TYPE_SIZE_16:
					printf("%7d"COLOR_NORMAL" ", ((int16_t)data));
					break;
				case SHOW_TYPE_SIZE_32:
					printf("%14d"COLOR_NORMAL" ", (int)((int32_t)data));
					break;
				case SHOW_TYPE_SIZE_64:
					printf("%21lld"COLOR_NORMAL" ", (int64_t)data);
					break;
				default:
					break;
			}

			break;
		case SHOW_TYPE_DECIMAL_UNSIGNED:
			switch(localSize)
			{
				case SHOW_TYPE_SIZE_8:
					printf("%4u"COLOR_NORMAL" ", ((uint8_t)data));
					break;
				case SHOW_TYPE_SIZE_16:
					printf("%7u"COLOR_NORMAL" ", ((uint16_t)data));
					break;
				case SHOW_TYPE_SIZE_32:
					printf("%14u"COLOR_NORMAL" ", (unsigned int)((uint32_t)data));
					break;
				case SHOW_TYPE_SIZE_64:
					printf("%21llu"COLOR_NORMAL" ", (uint64_t)data);
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
	
}
typedef union {
	uint8_t   data_8  [16];
	uint16_t  data_16 [8];
	uint32_t  data_32 [4];
	uint64_t  data_64 [2];
}inputData_tu;

void compareFile(FILE *filePointer1, FILE *filePointer2 ,int32_t CurentFilePosition)
{
	inputData_tu data1;
	inputData_tu data2;
	uint32_t i;
	uint32_t j;
	
	showConfiguration();
	
	showTypeSize_te mySize = getTypeSize();
	showType_te myType = getType();
	
	// Display the main show
	printf(COLOR_BOLD_YELLOW"Ofset :    |         | ");
	switch(myType)
	{
		case SHOW_TYPE_DECIMAL_SIGNED:
		case SHOW_TYPE_DECIMAL_UNSIGNED:
			for (i = 0 ; i<2 ; i++ )
			{
				switch(mySize)
				{
					case SHOW_TYPE_SIZE_8:
						for (j=0; j<2 ; j++ ) {
							printf("  +0   +1   +2   +3   +4   +5   +6   +7   +8   +9   +A   +B   +C   +D   +E   +F  | ");
						}
						break;
					case SHOW_TYPE_SIZE_16:
						for (j=0; j<2 ; j++ ) {
							printf("     +0      +2      +4      +6      +8      +A      +C      +E  | ");
						}
						break;
					case SHOW_TYPE_SIZE_32:
						for (j=0; j<2 ; j++ ) {
							printf("            +0             +4             +8             +C  | ");
						}
						break;
					case SHOW_TYPE_SIZE_64:
						for (j=0; j<2 ; j++ ) {
							printf("                   +0                    +8  | ");
						}
						break;
					default:
						break;
				}
				if (i == 0)
				{
					printf(COLOR_NORMAL"\n");
					printf(COLOR_BOLD_MAGENTA"           |  ofset  | ");
				}
			}
			break;
		case SHOW_TYPE_HEX:
		default : 
			for (i = 0 ; i<2 ; i++ ) {
				switch(mySize)
				{
					case SHOW_TYPE_SIZE_8:
						for (j=0; j<2 ; j++ ) {
							printf("+0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F  | ");
						}
						break;
					case SHOW_TYPE_SIZE_16:
						for (j=0; j<2 ; j++ ) {
							printf("  +0   +2   +4   +6   +8   +A   +C   +E  | ");
						}
						break;
					case SHOW_TYPE_SIZE_32:
						for (j=0; j<2 ; j++ ) {
							printf("      +0       +4       +8       +C  | ");
						}
						break;
					case SHOW_TYPE_SIZE_64:
						for (j=0; j<2 ; j++ ) {
							printf("              +0               +8  | ");
						}
						break;
					default:
						break;
				}
				if (i == 0)
				{
					printf(COLOR_NORMAL"\n");
					printf(COLOR_BOLD_MAGENTA"           |  ofset  | ");
				}
			}
			break;
	}
	printf(COLOR_NORMAL"\n");
	
	
	// Display the main show
	printf(COLOR_BOLD_YELLOW"----------------------------------------------------------------------------------------------------------------------------");
	printf(COLOR_NORMAL"\n");
	for (j=0; j < NB_MAX_LINE; j++) {
		uint32_t readFile1 = 0;
		uint32_t readFile2 = 0;
		uint32_t lineNumber = 0;
		uint32_t numberOfCycle;
		// read data in files : 
		memset(data1.data_8, 0, 16 * sizeof(uint8_t));
		memset(data2.data_8, 0, 16 * sizeof(uint8_t));
		if (filePointer1 != NULL) {
			readFile1 = fread(data1.data_8, sizeof(uint8_t), 16, filePointer1);
		}
		if (filePointer2 != NULL) {
			readFile2 = fread(data2.data_8, sizeof(uint8_t), 16, filePointer2);
		}
		// display the line number
		lineNumber = j * (NB_DATA_PER_LINE*4) + CurentFilePosition;
		printf(COLOR_BOLD_YELLOW"0x%08x | "COLOR_NORMAL, (unsigned int)lineNumber);
		switch(mySize)
		{
			case SHOW_TYPE_SIZE_8:
				printf(COLOR_BOLD_MAGENTA"%7d | "COLOR_NORMAL, (int)(lineNumber));
				break;
			case SHOW_TYPE_SIZE_16:
				printf(COLOR_BOLD_MAGENTA"%7d | "COLOR_NORMAL, (int)(lineNumber/2));
				break;
			case SHOW_TYPE_SIZE_32:
				printf(COLOR_BOLD_MAGENTA"%7d | "COLOR_NORMAL, (int)(lineNumber/4));
				break;
			case SHOW_TYPE_SIZE_64:
				printf(COLOR_BOLD_MAGENTA"%7d | "COLOR_NORMAL, (int)(lineNumber/8));
				break;
			default:
				break;
		}
		if (readFile1 == 0) {
			switch(mySize)
			{
				case SHOW_TYPE_SIZE_8:
					numberOfCycle = 16;
					break;
				case SHOW_TYPE_SIZE_16:
					numberOfCycle = 8;
					break;
				case SHOW_TYPE_SIZE_32:
					numberOfCycle = 4;
					break;
				case SHOW_TYPE_SIZE_64:
					numberOfCycle = 2;
					break;
				default :
					numberOfCycle = 0;
					break;
			}
			//printf("no more data");
			for (i = 0; i< numberOfCycle; i++) {
				printNoElement(myType, mySize);
			}
		} else {
			// TODO : mettre les octet qui reste a la fin si ce n'est pas complet
			i = 0;
			numberOfCycle = 16;
			while (i< numberOfCycle)
			{
				switch(mySize)
				{
					case SHOW_TYPE_SIZE_8:
						numberOfCycle = 16;
						for (i = 0; i< numberOfCycle; i++) {
							if (readFile1 >= (i+1)) {
								bool OutOfRange = (readFile2 >= (i+1));
								bool identic    = (data1.data_8[i] != data2.data_8[i]);
								printElement((uint64_t)data1.data_8[i], myType, mySize, identic, OutOfRange);
							} else {
								printNoElement(myType, mySize);
							}
						}
						break;
					case SHOW_TYPE_SIZE_16:
						numberOfCycle = 8;
						for (i = 0; i< numberOfCycle; i++) {
							if ((readFile1/2) >= (i+1)) {
								bool OutOfRange = ((readFile2/2) >= (i+1));
								bool identic    = (data1.data_16[i] != data2.data_16[i]);
								printElement((uint64_t)data1.data_16[i], myType, mySize, identic, OutOfRange);
							} else {
								printNoElement(myType, mySize);
							}
						}
						break;
					case SHOW_TYPE_SIZE_32:
						numberOfCycle = 4;
						for (i = 0; i< numberOfCycle; i++) {
							if ((readFile1/4) >= (i+1)) {
								bool OutOfRange = ((readFile2/4) >= (i+1));
								bool identic    = (data1.data_32[i] != data2.data_32[i]);
								printElement((uint64_t)data1.data_32[i], myType, mySize, identic, OutOfRange);
							} else {
								printNoElement(myType, mySize);
							}
						}
						break;
					case SHOW_TYPE_SIZE_64:
						numberOfCycle = 2;
						for (i = 0; i< numberOfCycle; i++) {
							if ((readFile1/8) >= (i+1)) {
								bool OutOfRange = ((readFile2/8) >= (i+1));
								bool identic    = (data1.data_64[i] != data2.data_64[i]);
								printElement((uint64_t)data1.data_64[i], myType, mySize, identic, OutOfRange);
							} else {
								printNoElement(myType, mySize);
							}
						}
						break;
					default :
						numberOfCycle = 0;
						break;
				}
				i++;
			}
		}
		printf(" | ");
		if (readFile2 == 0) {
			switch(mySize)
			{
				case SHOW_TYPE_SIZE_8:
					numberOfCycle = 16;
					break;
				case SHOW_TYPE_SIZE_16:
					numberOfCycle = 8;
					break;
				case SHOW_TYPE_SIZE_32:
					numberOfCycle = 4;
					break;
				case SHOW_TYPE_SIZE_64:
					numberOfCycle = 2;
					break;
				default :
					numberOfCycle = 0;
					break;
			}
			//printf("no more data");
			for (i = 0; i< numberOfCycle; i++) {
				printNoElement(myType, mySize);
			}
		} else {
			i = 0;
			numberOfCycle = 16;
			while (i< numberOfCycle)
			{
				switch(mySize)
				{
					case SHOW_TYPE_SIZE_8:
						numberOfCycle = 16;
						for (i = 0; i< numberOfCycle; i++) {
							if (readFile2 >= (i+1)) {
								bool OutOfRange = (readFile1 >= (i+1));
								bool identic    = (data1.data_8[i] != data2.data_8[i]);
								printElement((uint64_t)data2.data_8[i], myType, mySize, identic, OutOfRange);
							} else {
								printNoElement(myType, mySize);
							}
						}
						break;
					case SHOW_TYPE_SIZE_16:
						numberOfCycle = 8;
						for (i = 0; i< numberOfCycle; i++) {
							if ((readFile2/2) >= (i+1)) {
								bool OutOfRange = ((readFile1/2) >= (i+1));
								bool identic    = (data1.data_16[i] != data2.data_16[i]);
								printElement((uint64_t)data2.data_16[i], myType, mySize, identic, OutOfRange);
							} else {
								printNoElement(myType, mySize);
							}
						}
						break;
					case SHOW_TYPE_SIZE_32:
						numberOfCycle = 4;
						for (i = 0; i< numberOfCycle; i++) {
							if ((readFile2/4) >= (i+1)) {
								bool OutOfRange = ((readFile1/4) >= (i+1));
								bool identic    = (data1.data_32[i] != data2.data_32[i]);
								printElement((uint64_t)data2.data_32[i], myType, mySize, identic, OutOfRange);
							} else {
								printNoElement(myType, mySize);
							}
						}
						break;
					case SHOW_TYPE_SIZE_64:
						numberOfCycle = 2;
						for (i = 0; i< numberOfCycle; i++) {
							if ((readFile2/8) >= (i+1)) {
								bool OutOfRange = ((readFile1/8) >= (i+1));
								bool identic    = (data1.data_64[i] != data2.data_64[i]);
								printElement((uint64_t)data2.data_64[i], myType, mySize, identic, OutOfRange);
							} else {
								printNoElement(myType, mySize);
							}
						}
						break;
					default :
						numberOfCycle = 0;
						break;
				}
				i++;
			}
		}
		printf(COLOR_NORMAL" |\n");
	}
}








/* Fonction pour le thread du magasin. */
void * threadDisplay (void * p_data)
{
	while (1)
	{
		if (getParamModification()) {
			uint32_t CurentFilePosition = getOfsetFile();
			if (filePointer[0] != NULL) {
				fseek ( filePointer[0] , CurentFilePosition , SEEK_SET );
			}
			if (NULL != filePointer[1]) {
				fseek ( filePointer[1] , CurentFilePosition , SEEK_SET );
			}
			compareFile(filePointer[0],filePointer[1], CurentFilePosition);
		} else {
			usleep(10000);
		}
	}
	return NULL;
}



