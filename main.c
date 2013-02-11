/**
 *******************************************************************************
 * @file main.c
 * @brief Main function (sources)
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
#include "generalDefine.h"
#include "parameter.h"
#include "display.h"


fileProperties_ts fileProp[2];

void usage(void)
{
	printf("usage : hexViwer [option] [file_1] [file_2]\n");
	printf("\t[option] : options:\n");
	printf("\t\t[-d] : direct check of the error ...\n");
	printf("\t[file_1] : Show the first file  only\n");
	printf("\t[file_2] : if it was precise : Show the comparaison with the first file\n");
	printf("\t\n");
	printf("\tInside Usage : \n");
	printf("\t\t[a]     Go to the start of the files\n");
	printf("\t\t[z]     Go to the end of the files (the first push is the File 1, the second push is the file 2) \n");
	printf("\t\t[q]     Quit the curent program\n");
	printf("\t\t[s]     Change the view of the propram of the size of interpretation (8/16/32/64 bits)\n");
	printf("\t\t[t]     Change the interpretation of Data (hexedecimal, Signed Decimal, Unigned Decimal)\n");
	printf("\t\t[f]     Find the first Error when comparing the two files\n");
	printf("\t\t[c]     Calibrate the delta between the 2 file (fist element !=0)\n");
	printf("\t\t[UP]    Go up (5 lines)\n");
	printf("\t\t[DOWN]  Go down (5 lines)\n");
	printf("\t\t[LEFT]  Go up (one screen)\n");
	printf("\t\t[RIGHT] Go down (one screen)\n");
	printf("\t\tAdd padding : \n");
	printf("\t\t\t[o]   Add  1 Byte  padding at the left file\n");
	printf("\t\t\t[O]   Add 16 Bytes padding at the left file\n");
	printf("\t\t\t[p]   Add  1 Byte  padding at the right file\n");
	printf("\t\t\t[P]   Add 16 Bytes padding at the right file\n");
	printf("\t\t\t[m]   reset padding\n");
	printf("\t\n");
	printf("\tCopyright: 2010 Edouard DUPIN, all right reserved\n");
	printf("\tLicense: GNU Lesser General Public License (LGPL) v3.0\n");
}




int32_t findFirstDiff(void)
{
	uint8_t data1, data2;
	int32_t offset = 0;
	if(    NULL == fileProp[0].pointer
	    || NULL == fileProp[1].pointer ) {
		return 0;
	}
	int32_t paddingFile = getPaddingOffsetFile();
	int32_t pad1 = 0;
	int32_t pad2 = 0;
	if (paddingFile>0) {
		pad1 = paddingFile;
		pad2 = 0;
	} else {
		pad1 = 0;
		pad2 = -1*paddingFile;
	}
	if(NULL != fileProp[0].pointer) {
		fseek ( fileProp[0].pointer , pad1+fileProp[0].fileBasicOffset , SEEK_SET );
	}
	if(NULL != fileProp[1].pointer) {
		fseek ( fileProp[1].pointer , pad2+fileProp[1].fileBasicOffset , SEEK_SET );
	}
	while (  fread(&data1, sizeof(uint8_t), 1, fileProp[0].pointer)  == 1
	         && fread(&data2, sizeof(uint8_t), 1, fileProp[1].pointer)  == 1)
	{
		offset ++;
		if (data1 != data2) {
			return offset;
		}
	}
	return offset;
}

void AutoSetPadding(void)
{
	displayPaddingOffset(0);
	if(    NULL == fileProp[0].pointer
	    || NULL == fileProp[1].pointer ) {
		return;
	}
	
	if(NULL != fileProp[0].pointer) {
		fseek ( fileProp[0].pointer , fileProp[0].fileBasicOffset , SEEK_SET );
	}
	int32_t offset1 = 0;
	char data;
	while(fread(&data, sizeof(uint8_t), 1, fileProp[0].pointer) == 1) {
		if (data != 0) {
			break;
		}
		offset1 ++;
	}
	if(NULL != fileProp[1].pointer) {
		fseek ( fileProp[1].pointer , fileProp[1].fileBasicOffset , SEEK_SET );
	}
	int32_t offset2 = 0;
	while(fread(&data, sizeof(uint8_t), 1, fileProp[1].pointer) == 1)
	{
		if (data != 0) {
			break;
		}
		offset2 ++;
	}
	if (offset1 == offset2) {
		return;
	}
	if (0 == offset1) {
		return;
	}
	if (0 == offset2) {
		return;
	}
	
	displayPaddingOffset(offset1 - offset2);
}



void UpdateFilesSize(void)
{
	// get size for 2 files
	int32_t iii=0;
	for (iii=0; iii<2; iii++) {
		if ( NULL != fileProp[iii].pointer) {
			fseek ( fileProp[iii].pointer , 0 , SEEK_END );
			fileProp[iii].size = ftell (fileProp[iii].pointer) - fileProp[iii].fileBasicOffset;
			fseek ( fileProp[iii].pointer , 0 , SEEK_SET );
		}
	}
}


void ResetProperties(void)
{
	int32_t iii=0;
	for (iii=0; iii<2; iii++) {
		fileProp[iii].availlable = false;
		fileProp[iii].pointer = NULL;
		fileProp[iii].size = 0;
		strcpy(fileProp[iii].name, "No-File");
		fileProp[iii].fileBasicOffset = 0;
		fileProp[iii].type = SHOW_TYPE_UNKNOW;
		fileProp[iii].typeSize = SHOW_TYPE_SIZE_UNKNOW;
		fileProp[iii].slotSize = 0;
		fileProp[iii].delta = 0;
	}
}


void OpenFiles(void)
{
	int32_t iii=0;
	for (iii=0; iii<2; iii++) {
		if (true == fileProp[iii].availlable) {
			// Open file 1
			fileProp[iii].pointer = fopen(fileProp[iii].name, "rb");
			if ( NULL == fileProp[iii].pointer) {
				//printf("Can not Open [File_1] = %s\n", fileName[0]);
			}
		}
		if (fileProp[iii].pointer==NULL) {
			continue;
		}
		// check if file has specifi header : 
		char dataheader[128];
		if(16 == fread(&dataheader, sizeof(uint8_t), 16, fileProp[iii].pointer)) {
			// parse header
			if(    dataheader[0]=='#'
			    && dataheader[1]=='M'
			    && dataheader[2]=='E'
			    && dataheader[3]=='T') {
				
				//    ==> "#MET %c %s %04d "
				// type unused ...
				if(    dataheader[5] == 'I'
				    || dataheader[5] == 'F'
				    || dataheader[5] == 'D') {
					fileProp[iii].type = SHOW_TYPE_DECIMAL_SIGNED;
				} else if (dataheader[5] == 'U') {
					fileProp[iii].type = SHOW_TYPE_DECIMAL_UNSIGNED;
				} else if (dataheader[5] == 'U') {
					fileProp[iii].type = SHOW_TYPE_HEX;
				} else {
					printf("Error while parsing the header ... \n");
					fileProp[iii].type = SHOW_TYPE_UNKNOW;
				}
				if (strncmp(&dataheader[6], "08", 2)==0) {
					fileProp[iii].typeSize = SHOW_TYPE_SIZE_8;
				} else if (strncmp(&dataheader[6], "16", 2)==0) {
					fileProp[iii].typeSize = SHOW_TYPE_SIZE_16;
				} else if (strncmp(&dataheader[6], "32", 2)==0) {
					fileProp[iii].typeSize = SHOW_TYPE_SIZE_32;
				} else if (strncmp(&dataheader[6], "64", 2)==0) {
					fileProp[iii].typeSize = SHOW_TYPE_SIZE_64;
				} else if (strncmp(&dataheader[6], "28", 2)==0) {
					fileProp[iii].typeSize = SHOW_TYPE_SIZE_128;
				} else if (strncmp(&dataheader[6], "LO", 2)==0) {
					fileProp[iii].typeSize = SHOW_TYPE_SIZE_FLOAT;
				} else if (strncmp(&dataheader[6], "OU", 2)==0) {
					fileProp[iii].typeSize = SHOW_TYPE_SIZE_DOUBLE;
				} else {
					printf("Error while parsing the header ... \n");
					fileProp[iii].typeSize = SHOW_TYPE_SIZE_UNKNOW;
				}
				char tmpVal[5];
				tmpVal[0] = dataheader[8];
				tmpVal[1] = dataheader[9];
				tmpVal[2] = dataheader[10];
				tmpVal[3] = dataheader[11];
				tmpVal[4] = '\0';
				sscanf(tmpVal, "%04d", &fileProp[iii].slotSize);
				
				sscanf(&dataheader[12], "%04d", &fileProp[iii].delta);
				//printf("slot size [%d]=%d\n", iii, fileProp[iii].slotSize);
				// ofset of the header : 
				fileProp[iii].fileBasicOffset = 16;
			}
		} // else : no header present ==> raw file
		fseek ( fileProp[iii].pointer , fileProp[iii].fileBasicOffset , SEEK_SET );
	}
	// check internal properties : 
	if (fileProp[0].fileBasicOffset!=0 && fileProp[1].fileBasicOffset!=0) {
		if (fileProp[0].typeSize == fileProp[1].typeSize) {
			setTypeSize(fileProp[0].typeSize);
		} else {
			printf("Error The 2 files has not the same header properties header ... \n");
		}
		if (fileProp[0].type == fileProp[1].type) {
			setType(fileProp[0].type);
		} else {
			printf("Error The 2 files has not the same header properties header ... \n");
		}
	} else if (fileProp[0].fileBasicOffset!=0) {
		setTypeSize(fileProp[0].typeSize);
		setType(fileProp[0].type);
	} else if (fileProp[1].fileBasicOffset!=0) {
		setTypeSize(fileProp[1].typeSize);
		setType(fileProp[1].type);
	}
	int32_t sizeElement=1;
	showTypeSize_te tmpType = getTypeSize();
	switch(tmpType)
	{
		default:
		case SHOW_TYPE_SIZE_8:
			sizeElement = 1;
			break;
		case SHOW_TYPE_SIZE_16:
			sizeElement = 2;
			break;
		case SHOW_TYPE_SIZE_FLOAT:
		case SHOW_TYPE_SIZE_32:
			sizeElement = 4;
			break;
		case SHOW_TYPE_SIZE_DOUBLE:
		case SHOW_TYPE_SIZE_64:
			sizeElement = 8;
			break;
	}
	int32_t tmpDela = (fileProp[1].delta - fileProp[0].delta) * sizeElement;
	displayPaddingOffset(tmpDela);
	
	
	UpdateFilesSize();
}


void CloseFiles(void)
{
	int32_t iii=0;
	for (iii=0; iii<2; iii++) {
		if (NULL != fileProp[iii].pointer) {
			fclose(fileProp[iii].pointer);
		}
		fileProp[iii].pointer = NULL;
		fileProp[iii].fileBasicOffset = 0;
		fileProp[iii].type = SHOW_TYPE_UNKNOW;
		fileProp[iii].typeSize = SHOW_TYPE_SIZE_UNKNOW;
		fileProp[iii].slotSize = 0;
		fileProp[iii].delta = 0;
	}
}


int main (int argc, char**argv)
{
	int32_t first_Error = 0;
	ResetProperties();
	UpdateNumberOfRawAndColomn();
	// check error
	if (argc < 2) {
		printf("You set more than 3 argument at the commande line\n");
		usage();
		return -1;
	}
	bool directCheckFiles = false;
	int basicIDParsing = 1;
	if (0==strcmp("-d",argv[1])) {
		basicIDParsing++;
		directCheckFiles = true;
	}
	// one file
	if (basicIDParsing+1 <= argc) {
		strcpy(fileProp[0].name, argv[basicIDParsing]);
		fileProp[0].availlable = true;
	}
	// a second file
	if (basicIDParsing+2 <= argc) {
		strcpy(fileProp[1].name, argv[basicIDParsing+1]);
		fileProp[1].availlable = true;
	}
	// open the files
	OpenFiles();
	
	// user requested to have the direct error ID of the file...
	if (directCheckFiles==true) {
		
		float dividor = 1;
		int32_t maxSlot = (fileProp[0].slotSize>fileProp[1].slotSize)?fileProp[0].slotSize:fileProp[1].slotSize;
		if (0!=maxSlot) {
			dividor = maxSlot;
		}
		
		int32_t idError = findFirstDiff();
		int minSizeFile = (fileProp[0].size<fileProp[1].size)?fileProp[0].size:fileProp[1].size;
		if (minSizeFile<=idError) {
			printf(" No error ... file size=%d Bytes slot=%3d", idError, (int32_t)dividor);
			CloseFiles();
			// 0 : no error
			return 0;
		} else {
			int32_t sizeElement = 1;
			showTypeSize_te tmpType = getTypeSize();
			switch(tmpType)
			{
				default:
				case SHOW_TYPE_SIZE_8:
					sizeElement = 1;
					break;
				case SHOW_TYPE_SIZE_16:
					sizeElement = 2;
					break;
				case SHOW_TYPE_SIZE_FLOAT:
				case SHOW_TYPE_SIZE_32:
					sizeElement = 4;
					break;
				case SHOW_TYPE_SIZE_DOUBLE:
				case SHOW_TYPE_SIZE_64:
					sizeElement = 8;
					break;
			}
			int32_t elementIDError = idError/sizeElement;
			float frameRatio = (float)elementIDError/dividor;
			int32_t idFrame = frameRatio;
			int32_t idFrameElement = (frameRatio-idFrame)*dividor;
			printf("%9d / frame=%9.2f ==> frame=%5d element=%5d slot=%3d", elementIDError, frameRatio, idFrame, idFrameElement, (int32_t)dividor);
			CloseFiles();
			return idError;
		}
	}
	// rendre la lecture des données non canonique
	system("stty -icanon");
	// supression de l'écho des caractères
	system("stty -echo");
	// enable mouse event ...
	printf(MOUSE_REPORTING_ENABLE);
	// hide cursor ...
	printf(CURSOR_DISPLAY_DISABLE);
	system("clear");
	CleanDisplay();


	int ret = 0;
	pthread_t HangleThreadDisplay;

	ret = pthread_create ( & HangleThreadDisplay, NULL, threadDisplay, NULL );
	if (! ret)
	{
		while (1)
		{
			int32_t inputValue;
			inputValue = getc(stdin);
			switch(inputValue)
			{
				case 'q':
				case 'Q':
					goto exit_programme;
					break;
				//case 0x1B:
				case '\e':
					inputValue = getc (stdin);
					//printf("\n get data : 0x%08x ..... : \n", (unsigned int)inputValue);
					// [ == 0x5B
					if (inputValue == '[')
					{
						inputValue = getc (stdin);
						char charValue = inputValue;
						// printf("\n get data : 0x%08x ..... : \\e[%c\n", (unsigned int)inputValue, charValue);
						if (    charValue == 'A' //0x41 ==> UP
						     || charValue == 'B' //0x42 ==> DOWN
						     || charValue == 'C' //0x43 ==> RIGHT
						     || charValue == 'D' //0x44 ==> LEFT
						   )
						{
							//printf("\n get data :\\e[%c ==> MoveKey \n", charValue);
							if (charValue == 'A') {
								upDownOfsetFile(-5);
							} else if ( charValue == 'B') {
								upDownOfsetFile(5);
							} else if ( charValue == 'C') {
								upDownOfsetFile((GetNumberOfRaw()-NB_HEARDER_RAW));
							} else if ( charValue == 'D') {
								upDownOfsetFile(-(GetNumberOfRaw()-NB_HEARDER_RAW));
							}
						} else if (charValue == 'M' ) { //0x4d ==> mouse
							//printf("\n get data :\\e[%c ==> Mouse \n", charValue);
							int32_t button = getc(stdin);
							int32_t xPos = getc(stdin);
							xPos -= 0x20;
							int32_t yPos = getc(stdin);
							yPos -= 0x20;
							
							int32_t bt=0;
							switch (button) {
								case 97:
									bt = 4;
									break;
								case 96:
									bt = 5;
									break;
								case 32:
									bt = 1;
									break;
								case 33:
									bt = 3;
									break;
							}
							//printf("     bt=%#x=%d \n", button, bt);
							//printf("     x=%d y=%d\n", xPos, yPos);
							if (bt == 4) {
								upDownOfsetFile(5);
							} else if (bt == 5) {
								upDownOfsetFile(-5);
							}
						}
					}
					
					break;
				// change the type of interpretation the file
				case 't':
				case 'T':
					nextType();
					break;
				// change the size of showing the file
				case 's':
				case 'S':
					nextTypeSize();
					break;
				// find the first ERROR
				case 'f':
				case 'F':
					// try to find the first error...
					first_Error = findFirstDiff();
					setOfsetFile((first_Error/16)*16 - 128);
					needRedraw();
					break;
				// find the first ERROR
				case 'a':
				case 'A':
					setOfsetFile(0);
					break;
				// go to the end of the file (File 1 and next File 2)
				case 'z':
				case 'Z':
					{
						UpdateFilesSize();
						static bool whichElement = false;
						if (whichElement == false) {
							whichElement = true;
							setOfsetFile((fileProp[0].size/16)*16 - 256);
						} else {
							whichElement = false;
							setOfsetFile((fileProp[1].size/16)*16 - 256);
						}
					}
					break;
				// Reload the 2 files
				case 'r':
				case 'R':
					CloseFiles();
					UpdateNumberOfRawAndColomn();
					CleanDisplay();
					OpenFiles();
					needRedraw();
					break;
				// Add padding offset between left an right file
				case 'o':
					displayPaddingOffset(-1);
					break;
				case 'O':
					displayPaddingOffset(-16);
					break;
				case 'p':
					displayPaddingOffset(1);
					break;
				case 'P':
					displayPaddingOffset(16);
					break;
				// Clear the padding
				case 'm':
				case 'M':
					displayPaddingOffsetClear();
					break;
				case 'c':
				case 'C':
					AutoSetPadding();
					break;
			}
		}
	} else {
		fprintf (stderr, "%s", strerror (ret));
	}
	
exit_programme : 
	CloseFiles();
	
	// disable mouse event ...
	printf(MOUSE_REPORTING_DISABLE);
	// Back cursor ON ...
	printf(CURSOR_DISPLAY_ENABLE);
	// remettre la lecture des données canonique
	system("stty icanon");
	// repositionnement de l'écho des caractères
	system("stty echo");
	return 0;
}







void displayCouleurBash(void)
{
	/* Initialise the main variables
	* colour: for the 256 colours (0-255)
	* space: to insert space or newline
	*/

	int colour = 0;
	int espace = 0;

	/* Print the 16 first colours, known as colours system */

	printf("System colours:\n");
	for( ; colour < 16; colour++) {
		printf("\e[48;5;%dm  ", colour);
	}
	printf("\e[0m\n\n");

	/* The 216 colours */

	printf("Color cube: 6x6x6\n");
	for ( ; colour < 232; colour++, espace++) {
		if ((espace%6) == 0) {
			printf("\e[0m ");
		}
		if ((espace%36 == 0)) {
			printf("\e[0m\n");
		}
		printf("\e[48;5;%dm  ", colour);
	}
	printf("\e[0m\n\n");

	/* And the grey colours */

	printf("Greyscale ramp\n");
	for ( ; colour < 256; colour++) {
		printf("\e[48;5;%dm  ", colour);
	}
	printf("\e[0m\n\n");

	/* Initialise the main variables
	* colour: for the 256 colours (0-255)
	* space: to insert space or newline
	*/


	/* Print the 16 first colours, known as colours system */

	printf("System colours:\n");
	for( ; colour < 16; colour++) {
		printf("\e[48;5;%dm  ", colour);
	}
	printf("\e[0m\n\n");

	/* The 216 colours */

	printf("Color cube: 6x6x6\n");
	for ( ; colour < 232; colour++, espace++) {
		if ((espace%6) == 0) {
			printf("\e[0m ");
		}
		if ((espace%36 == 0)) {
			printf("\e[0m\n");
		}
		printf("\e[48;5;%dm  ", colour);
	}
	printf("\e[0m\n\n");

	/* And the grey colours */

	printf("Greyscale ramp\n");
	for ( ; colour < 256; colour++) {
		printf("\e[48;5;%dm  ", colour);
	}
	printf("\e[0m\n\n");


}



