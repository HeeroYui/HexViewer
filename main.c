/**
 *******************************************************************************
 * @file main.c
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
#include "generalDefine.h"
#include "parameter.h"
#include "display.h"



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
	printf("\t\t[s]     Change the view of the propram of the size of interpretation (8 bits, 16 bits, 32 bits)\n");
	printf("\t\t[t]     Change the interpretation of Data (hexedecimal, Signed Decimal, Unigned Decimal)\n");
	printf("\t\t[f]     Find the first Error when comparing the two files\n");
	printf("\t\t[UP]    Go up 5 line in the view\n");
	printf("\t\t[DOWN]  Go down 5 line in the view\n");
	printf("\t\t[LEFT]  Go up 50 line in the view (one screen)\n");
	printf("\t\t[RIGHT] Go down 50 line in the view (one screen)\n");
	printf("\t\n");
	printf("\tTODO : \n");
	printf("\t\t- The print of 128 bytes\n");
	printf("\t\t- The print in Octal\n");
	printf("\t\t- The print in Binary\n");
	printf("\t\t- The Modification of the file\n");
	printf("\t\t- The Saving of the file\n");
	printf("\t\t- The information that one of the files has been update\n");
	printf("\t\t- To reload the two files                                     ==> [U]\n");
	printf("\t\t- The windows scroling with the mouse\n");
	printf("\t\t- The selection with the mouse\n");
	printf("\t\t- The display on char view\n");
	printf("\t\t- The scroling Bar on the right\n");
	printf("\t\t- Add to the croling bar the differences in the two files\n");
	printf("\t\t- The research of a sequency in the two files                 ==> [R]\n");
	printf("\t\t- The jump to an offset directly                              ==> [J] \n");
	/*printf("\t\t- \n");*/
}










int32_t findFirstDiff(void)
{
	uint8_t data1, data2;
	int32_t offset = 0;
	if(    NULL == filePointer[0]
	    || NULL == filePointer[1] ) {
		return 0;
	}
	while (  fread(&data1, sizeof(uint8_t), 1, filePointer[0])  == 1
	         && fread(&data2, sizeof(uint8_t), 1, filePointer[1])  == 1)
	{
		offset ++;
		if (data1 != data2)
		{
			return offset;
		}
	}
	return offset;
}


int main (int argc, char**argv)
{
	int32_t first_Error = 0;
	filePointer[0] = NULL;
	filePointer[1] = NULL;
	filesize[0] = 0;
	filesize[1] = 0;
	strcpy(fileName[0], "No-File");
	strcpy(fileName[1], "No-File");
	
	if (3 < argc || argc < 2) {
		printf("You set more than 3 argument at the commande line\n");
		usage();
		return -1;
	}
	
	if (2 <= argc) {
		// Open file 1
		filePointer[0] = fopen(argv[1], "rb");
		strcpy(fileName[0], argv[1]);
		if ( NULL == filePointer[0]) {
			printf("Can not Open [File_1] = %s\n", fileName[0]);
		}
		// get size file 1
		if ( NULL != filePointer[0]) {
			fseek ( filePointer[0] , 0 , SEEK_END );
			filesize[0] = ftell (filePointer[0]);
			fseek ( filePointer[0] , 0 , SEEK_SET );
		} else {
			filesize[0] = 0;
		}
	}
	if (3 <= argc) {
		// open File 2
		filePointer[1] = fopen(argv[2], "rb");
		strcpy(fileName[1], argv[2]);
		if ( NULL == filePointer[1]) {
			printf("Can not Open [File_2] = %s\n", fileName[1]);
		}
		// get size file 2
		if ( NULL != filePointer[1]) {
			fseek ( filePointer[1] , 0 , SEEK_END );
			filesize[1] = ftell (filePointer[1]);
			fseek ( filePointer[1] , 0 , SEEK_SET );
		} else {
			filesize[1] = 0;
		}
	}
	// try to find the first error...
	first_Error = findFirstDiff();
	
	// rendre la lecture des donn�es non canonique
	system("stty -icanon");
	// supression de l'�cho des caract�res
	system("stty -echo");
	
	system("clear");
	
	
	int ret = 0;
	pthread_t HangleThreadDisplay;

	ret = pthread_create ( & HangleThreadDisplay, NULL, threadDisplay, NULL );
	if (! ret)
	{
		while (1)
		{
			uint32_t inputValue;
			inputValue = getc (stdin);
			//printf("\n get data : 0x%08x ..... : \n", (unsigned int)inputValue);
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
					if (inputValue == 0x5B)
					{
						inputValue = getc (stdin);
						//printf("\n get data : 0x%08x ..... : \n", (unsigned int)inputValue);
						if (    inputValue == 0x41
						     || inputValue == 0x42
						     || inputValue == 0x43
						     || inputValue == 0x44)
						{
							if (inputValue == 0x41) {
								upDownOfsetFile(-5);
							} else if ( inputValue == 0x42) {
								upDownOfsetFile(5);
							} else if ( inputValue == 0x43) {
								upDownOfsetFile(NB_MAX_LINE);
							} else if ( inputValue == 0x44) {
								upDownOfsetFile(-NB_MAX_LINE);
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
					setOfsetFile((first_Error/16)*16 - 256);
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
			}
		}
	} else {
		fprintf (stderr, "%s", strerror (ret));
	}
	
exit_programme : 
	if (NULL != filePointer[0]) {
		fclose(filePointer[0]);
	} if (NULL != filePointer[1]) {
		fclose(filePointer[1]);
	}
	
	// remettre la lecture des donn�es canonique
	system("stty icanon");
	// repositionnement de l'�cho des caract�res
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


