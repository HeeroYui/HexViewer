/**
 *******************************************************************************
 * @file display.c
 * @brief main display system of the hexViewer (Sources)
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
#include "display.h"

extern fileProperties_ts fileProp[2];


void drawLine(bool returnLine)
{
	showTypeSize_te mySize = getTypeSize();
	showType_te myType = getType();
	switch(myType)
	{
		case SHOW_TYPE_DECIMAL_SIGNED:
		case SHOW_TYPE_DECIMAL_UNSIGNED:
			switch(mySize)
			{
				case SHOW_TYPE_SIZE_8:
					printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
					break;
				case SHOW_TYPE_SIZE_16:
					printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
					break;
				case SHOW_TYPE_SIZE_32:
					printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
					break;
				case SHOW_TYPE_SIZE_64:
					printf("-------------------------------------------------------------------------------------------------------------------------------------------");
					break;
				default:
					break;
			}
			break;
		case SHOW_TYPE_HEX:
		default : 
			switch(mySize)
			{
				case SHOW_TYPE_SIZE_8:
					printf("---------------------------------------------------------------------------------------------------------------------------------------------------");
					break;
				case SHOW_TYPE_SIZE_16:
					printf("-----------------------------------------------------------------------------------------------------------------------------------");
					break;
				case SHOW_TYPE_SIZE_32:
					printf("---------------------------------------------------------------------------------------------------------------------------");
					break;
				case SHOW_TYPE_SIZE_64:
					printf("-----------------------------------------------------------------------------------------------------------------------");
					break;
				default:
					break;
			}
			break;
	}
	if (returnLine==true) {
		printf("\n"COLOR_NORMAL);
	} else {
		printf("\r"COLOR_NORMAL);
	}
}

const char* getTypeChar(showType_te myType)
{
	switch(myType)
	{
		case SHOW_TYPE_HEX:
			return "Hexadecimal ";
			break;
		case SHOW_TYPE_DECIMAL_SIGNED:
			return "Dec Signed  ";
			break;
		case SHOW_TYPE_DECIMAL_UNSIGNED:
			return "Dec Unsigned";
			break;
		default :
			return "?           ";
			break;
	}
}
const char* getTypeSizeChar(showTypeSize_te mySize)
{
	switch(mySize)
	{
		case SHOW_TYPE_SIZE_8:
			return "  8 bits ";
			break;
		case SHOW_TYPE_SIZE_16:
			return " 16 bits ";
			break;
		case SHOW_TYPE_SIZE_32:
			return " 32 bits ";
			break;
		case SHOW_TYPE_SIZE_64:
			return " 64 bits ";
			break;
		case SHOW_TYPE_SIZE_128:
			return "128 bits ";
			break;
		default :
			return "  ? bits ";
			break;
	}
}

void showConfiguration(void)
{
	showType_te myType = getType();
	showTypeSize_te mySize = getTypeSize();
	
	// TODO : Redraw periodicly
	//CleanDisplay();
	printf(GO_TOP);
	
	printf(COLOR_BOLD_GREEN);
	drawLine(true);
	printf(COLOR_GREEN);
	printf("| hexViewer          |  offset : %7d octets ", (int)getOfsetFile());
	printf(" | Type (t) : %s", getTypeChar(myType));
	printf(" | ");
	printf(" | Size (s) : %s", getTypeSizeChar(mySize));
	printf(" | Slot (u+/i-/j/k) : %d (%s)", getSlotSize(), (getSlotDisplayMode()?"enable ":"disable"));
	printf(" | Padding (o+/p-/m) : %d ", getPaddingOffsetFile());
	printf(" | ");
	
	printf(COLOR_NORMAL"\n");
	printf(COLOR_GREEN"| File Left  <<      | [%s%s slot=%4d delta=%4d] " COLOR_BOLD_GREEN "%s\n" COLOR_NORMAL,
	       getTypeChar(fileProp[0].type),
	       getTypeSizeChar(fileProp[0].typeSize),
	       fileProp[0].slotSize,
	       fileProp[0].delta,
	       fileProp[0].name);
	printf(COLOR_GREEN"| File Right      >> | [%s%s slot=%4d delta=%4d] " COLOR_BOLD_GREEN "%s\n"COLOR_NORMAL,
	       getTypeChar(fileProp[1].type),
	       getTypeSizeChar(fileProp[1].typeSize),
	       fileProp[1].slotSize,
	       fileProp[1].delta,
	       fileProp[1].name);

	printf(COLOR_BOLD_GREEN);
	drawLine(true);
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
			break;printf(GO_TOP);
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


void compareFile(FILE *filePointer1, FILE *filePointer2 ,int32_t curentFilePosition, int32_t currentPadding)
{
	if (filePointer1==NULL && filePointer2==NULL) {
		return;
	}
	inputData_tu data1;
	inputData_tu data2;
	uint32_t i;
	uint32_t jjj;
	
	showConfiguration();
	
	showTypeSize_te mySize = getTypeSize();
	showType_te myType = getType();
	
	// Display the main show
	printf(COLOR_BOLD_YELLOW"   File offset       | ");
	switch(myType)
	{
		case SHOW_TYPE_DECIMAL_SIGNED:
		case SHOW_TYPE_DECIMAL_UNSIGNED:
			for (i = 0 ; i<2 ; i++ ) {
				switch(mySize)
				{
					case SHOW_TYPE_SIZE_8:
						printf("  +0   +1   +2   +3   +4   +5   +6   +7   +8   +9   +A   +B   +C   +D   +E   +F  | ");
						break;
					case SHOW_TYPE_SIZE_16:
						printf("     +0      +2      +4      +6      +8      +A      +C      +E  | ");
						break;
					case SHOW_TYPE_SIZE_32:
						printf("            +0             +4             +8             +C  | ");
						break;
					case SHOW_TYPE_SIZE_64:
						printf("                   +0                    +8  | ");
						break;
					default:
						break;
				}
			}
			break;
		case SHOW_TYPE_HEX:
		default : 
			for (i = 0 ; i<2 ; i++ ) {
				switch(mySize)
				{
					case SHOW_TYPE_SIZE_8:
						printf("+0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F  | ");
						break;
					case SHOW_TYPE_SIZE_16:
						printf("  +0   +2   +4   +6   +8   +A   +C   +E  | ");
						break;
					case SHOW_TYPE_SIZE_32:
						printf("      +0       +4       +8       +C  | ");
						break;
					case SHOW_TYPE_SIZE_64:
						printf("              +0               +8  | ");
						break;
					default:
						break;
				}
			}
			break;
	}
	printf(COLOR_BOLD_YELLOW"   File offset       | ");
	printf(COLOR_NORMAL"\n");
	
	
	// Display the main show
	printf(COLOR_BOLD_YELLOW);
	drawLine(true);
	int32_t counterLineID;
	int32_t offsetDisplaySlot=0;
	int32_t sizeSlotByte;
	switch(getTypeSize())
	{
		default:
		case SHOW_TYPE_SIZE_8:
			sizeSlotByte = 1*getSlotSize();
			break;
		case SHOW_TYPE_SIZE_16:
			sizeSlotByte = 2*getSlotSize();
			break;
		case SHOW_TYPE_SIZE_FLOAT:
		case SHOW_TYPE_SIZE_32:
			sizeSlotByte = 4*getSlotSize();
			break;
		case SHOW_TYPE_SIZE_DOUBLE:
		case SHOW_TYPE_SIZE_64:
			sizeSlotByte = 8*getSlotSize();
			break;
	}
	if (true == getSlotDisplayMode() && 0<getSlotSize()) {
		int32_t nbElementToRead = NB_DATA_PER_LINE*4;
		int32_t positionInSlot = curentFilePosition%sizeSlotByte;
		offsetDisplaySlot = positionInSlot%nbElementToRead;
	}
	for (jjj=0, counterLineID=0; jjj < (uint32_t)(GetNumberOfRaw()-NB_HEARDER_RAW); jjj++, counterLineID++) {
		uint32_t readFile1 = 0;
		uint32_t readFile2 = 0;
		int32_t lineNumber = 0;
		uint32_t numberOfCycle;
		// read data in files : 
		memset(data1.data_8, 0, 16 * sizeof(uint8_t));
		memset(data2.data_8, 0, 16 * sizeof(uint8_t));
		
		// Generate the ofset in the file
		int32_t positionStartDisplayFile1 = curentFilePosition + offsetDisplaySlot;
		int32_t positionStartDisplayFile2 = curentFilePosition + offsetDisplaySlot;
		if (currentPadding < 0) {
			positionStartDisplayFile1 += currentPadding;
		} else {
			positionStartDisplayFile2 -= currentPadding;
		}
		if (true == getSlotDisplayMode() && 0<getSlotSize()) {
			if (positionStartDisplayFile1%sizeSlotByte==0) {
				drawLine(false);
				printf(" Frame | %9d |\n", positionStartDisplayFile1/sizeSlotByte);
				jjj++;
			}
			if (jjj >= (uint32_t)(GetNumberOfRaw()-NB_HEARDER_RAW)) {
				return;
			}
		}
		
		
		
		int32_t nbElementToRead = NB_DATA_PER_LINE*4;
		if (true == getSlotDisplayMode() && 0<getSlotSize()) {
			int32_t posituionInSlot = positionStartDisplayFile1%sizeSlotByte;
			if (posituionInSlot+nbElementToRead>sizeSlotByte) {
				nbElementToRead = sizeSlotByte - posituionInSlot;
			}
		}
		/*
		if (nbElementToRead != NB_DATA_PER_LINE*4) {
			printf("                                                                                              \r");
			printf("nbElementToRead=%d\n",nbElementToRead);
			jjj++;
		}
		*/
		readFile1 = 0;
		int32_t readStartFile1 = 16;
		if (filePointer1 != NULL) {
			if (positionStartDisplayFile1 >= 0) {
				fseek(filePointer1 , positionStartDisplayFile1+fileProp[0].fileBasicOffset , SEEK_SET );
				readFile1 = fread(data1.data_8, sizeof(uint8_t), nbElementToRead, filePointer1);
				readStartFile1 = 0;
			} else if (positionStartDisplayFile1 > -NB_DATA_PER_LINE*4) {
				fseek(filePointer1 , fileProp[0].fileBasicOffset , SEEK_SET );
				// Special case of the partial display ...
				readFile1 = fread(data1.data_8 - positionStartDisplayFile1, sizeof(uint8_t), NB_DATA_PER_LINE*4 + positionStartDisplayFile1, filePointer1);
				readStartFile1 = NB_DATA_PER_LINE*4 - readFile1;
				readFile1 = 16;
			}
		}
		readFile2 = 0;
		int32_t readStartFile2 = 16;
		if (filePointer2 != NULL) {
			if (positionStartDisplayFile2 >= 0) {
				fseek(filePointer2 , positionStartDisplayFile2+fileProp[1].fileBasicOffset , SEEK_SET );
				readFile2 = fread(data2.data_8, sizeof(uint8_t), nbElementToRead, filePointer2);
				readStartFile2 = 0;
			} else if (positionStartDisplayFile2 > -NB_DATA_PER_LINE*4) {
				fseek(filePointer2 , fileProp[1].fileBasicOffset , SEEK_SET );
				// Special case of the partial display ...
				readFile2 = fread(data2.data_8 - positionStartDisplayFile2, sizeof(uint8_t), NB_DATA_PER_LINE*4 + positionStartDisplayFile2, filePointer2);
				readStartFile2 = NB_DATA_PER_LINE*4 - readFile2;
				readFile2 = 16;
			}
		}
		
		// display the line number
		lineNumber = positionStartDisplayFile1;
		if (lineNumber+NB_DATA_PER_LINE*4-1 >= 0) {
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
		} else {
			printf(COLOR_BOLD_YELLOW"           | "COLOR_BOLD_MAGENTA"        | "COLOR_NORMAL);
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
							if (readFile1 >= (i+1) && readStartFile1 <= (int32_t)i ) {
								bool OutOfRange = (readFile2 >= (i+1) && readStartFile2 <= (int32_t)i);
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
							if ((readFile1/2) >= (i+1) && readStartFile1/2 <= (int32_t)i) {
								bool OutOfRange = ((readFile2/2) >= (i+1) && readStartFile2/2 <= (int32_t)i);
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
							if ((readFile1/4) >= (i+1) && readStartFile1/4 <= (int32_t)i) {
								bool OutOfRange = ((readFile2/4) >= (i+1) && readStartFile2/4 <= (int32_t)i);
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
							if ((readFile1/8) >= (i+1) && readStartFile1/8 <= (int32_t)i) {
								bool OutOfRange = ((readFile2/8) >= (i+1) && readStartFile2/8 <= (int32_t)i);
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
							if (readFile2 >= (i+1) && readStartFile2 <= (int32_t)i ) {
								bool OutOfRange = (readFile1 >= (i+1) && readStartFile1 <= (int32_t)i);
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
							if ((readFile2/2) >= (i+1) && readStartFile2/2 <= (int32_t)i ) {
								bool OutOfRange = ((readFile1/2) >= (i+1) && readStartFile1/2 <= (int32_t)i);
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
							if ((readFile2/4) >= (i+1) && readStartFile2/4 <= (int32_t)i ) {
								bool OutOfRange = ((readFile1/4) >= (i+1) && readStartFile1/4 <= (int32_t)i);
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
							if ((readFile2/8) >= (i+1) && readStartFile2/8 <= (int32_t)i ) {
								bool OutOfRange = ((readFile1/8) >= (i+1) && readStartFile1/8 <= (int32_t)i);
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
		
		
		lineNumber = positionStartDisplayFile2;
		if (lineNumber+NB_DATA_PER_LINE*4-1 >= 0) {
			switch(mySize)
			{
				case SHOW_TYPE_SIZE_8:
					printf(COLOR_BOLD_MAGENTA" | %7d ", (int)(lineNumber));
					break;
				case SHOW_TYPE_SIZE_16:
					printf(COLOR_BOLD_MAGENTA" | %7d ", (int)(lineNumber/2));
					break;
				case SHOW_TYPE_SIZE_32:
					printf(COLOR_BOLD_MAGENTA" | %7d ", (int)(lineNumber/4));
					break;
				case SHOW_TYPE_SIZE_64:
					printf(COLOR_BOLD_MAGENTA" | %7d ", (int)(lineNumber/8));
					break;
				default:
					break;
			}
			printf(COLOR_BOLD_YELLOW"| 0x%08x"COLOR_NORMAL " |\n", (unsigned int)lineNumber);
		} else {
			printf(COLOR_BOLD_MAGENTA" |         "COLOR_BOLD_YELLOW"|           "COLOR_NORMAL " |\n");
		}
		// update file positions :
		offsetDisplaySlot += nbElementToRead;
	}
}








/* Fonction pour le thread du magasin. */
void * threadDisplay (void * p_data)
{
	while (1)
	{
		if (getParamModification()) {
			uint32_t curentFilePosition = getOfsetFile();
			uint32_t curentFilePadding  = getPaddingOffsetFile();
			compareFile(fileProp[0].pointer,fileProp[1].pointer, curentFilePosition, curentFilePadding);
			if (true==getHelpDisplay()) {
				showConfiguration();
				usage();
			}
		} else {
			usleep(10000);
		}
	}
	return NULL;
}



