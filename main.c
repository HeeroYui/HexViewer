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




bool  filePresent[2] = {false, false};
FILE *filePointer[2] = {NULL, NULL};
uint32_t filesize[2] = {0, 0};
char fileName[2][2096] = {"",""};

void usage(void)
{
	printf("usage : hexViwer [file_1] [file_2]\n");
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
	if(    NULL == filePointer[0]
	    || NULL == filePointer[1] ) {
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
	if(NULL != filePointer[0]) {
		fseek ( filePointer[0] , pad1 , SEEK_SET );
	}
	if(NULL != filePointer[1]) {
		fseek ( filePointer[1] , pad2 , SEEK_SET );
	}
	while (  fread(&data1, sizeof(uint8_t), 1, filePointer[0])  == 1
	         && fread(&data2, sizeof(uint8_t), 1, filePointer[1])  == 1)
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
	if(    NULL == filePointer[0]
	    || NULL == filePointer[1] ) {
		return;
	}
	
	if(NULL != filePointer[0]) {
		fseek ( filePointer[0] , 0 , SEEK_SET );
	}
	int32_t offset1 = 0;
	char data;
	while(fread(&data, sizeof(uint8_t), 1, filePointer[0]) == 1)
	{
		if (data != 0) {
			break;
		}
		offset1 ++;
	}
	if(NULL != filePointer[1]) {
		fseek ( filePointer[1] , 0 , SEEK_SET );
	}
	int32_t offset2 = 0;
	while(fread(&data, sizeof(uint8_t), 1, filePointer[1]) == 1)
	{
		if (data != 0) {
			break;
		}
		offset2 ++;
	}
	if (offset1 == offset2) {
		return;
	}
	if (offset1 == 0) {
		return;
	}
	if (0 == offset2) {
		return;
	}
	displayPaddingOffset(offset1 - offset2);
}



void UpdateFilesSize(void)
{
	// get size file 1
	if ( NULL != filePointer[0]) {
		fseek ( filePointer[0] , 0 , SEEK_END );
		filesize[0] = ftell (filePointer[0]);
		fseek ( filePointer[0] , 0 , SEEK_SET );
	}
	// get size file 2
	if ( NULL != filePointer[1]) {
		fseek ( filePointer[1] , 0 , SEEK_END );
		filesize[1] = ftell (filePointer[1]);
		fseek ( filePointer[1] , 0 , SEEK_SET );
	}
}

void OpenFiles(void) {
	filePointer[0] = NULL;
	filePointer[1] = NULL;
	filesize[0] = 0;
	filesize[1] = 0;
	if (true == filePresent[0]) {
		// Open file 1
		filePointer[0] = fopen(fileName[0], "rb");
		if ( NULL == filePointer[0]) {
			//printf("Can not Open [File_1] = %s\n", fileName[0]);
		}
	}
	if (true == filePresent[1]) {
		// open File 2
		filePointer[1] = fopen(fileName[1], "rb");
		if ( NULL == filePointer[1]) {
			//printf("Can not Open [File_2] = %s\n", fileName[1]);
		}
	}
	UpdateFilesSize();
}


void CloseFiles(void) {
	if (NULL != filePointer[0]) {
		fclose(filePointer[0]);
		filePointer[0] = NULL;
	} if (NULL != filePointer[1]) {
		fclose(filePointer[1]);
		filePointer[1] = NULL;
	}
}


int main (int argc, char**argv)
{
	int32_t first_Error = 0;
	filePointer[0] = NULL;
	filePointer[1] = NULL;
	strcpy(fileName[0], "No-File");
	strcpy(fileName[1], "No-File");
	
	UpdateNumberOfRawAndColomn();
	
	// check error
	if (3 < argc || argc < 2) {
		printf("You set more than 3 argument at the commande line\n");
		usage();
		return -1;
	}
	// one file
	if (2 <= argc) {
		strcpy(fileName[0], argv[1]);
		filePresent[0] = true;
	}
	// a second file
	if (3 <= argc) {
		strcpy(fileName[1], argv[2]);
		filePresent[1] = true;
	}
	// open the files
	OpenFiles();
	
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
							setOfsetFile((filesize[0]/16)*16 - 256);
						} else {
							whichElement = false;
							setOfsetFile((filesize[1]/16)*16 - 256);
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



