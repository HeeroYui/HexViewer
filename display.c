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
    printf(COLOR_BOLD_GREEN"----------------------------------------------------------------------------------------------------------------------------\n"COLOR_NORMAL);

    printf(COLOR_BOLD_GREEN"                                                                                                                            \r                     ");
    switch(myType)
    {
        case SHOW_TYPE_DECIMAL_SIGNED:
            switch(mySize)
            {
                case SHOW_TYPE_SIZE_8:
                    printf("                                                                 | ");

                    break;
                case SHOW_TYPE_SIZE_16:
                    printf("                                                         | ");
                    break;
                case SHOW_TYPE_SIZE_32:
                        printf("                                         | ");
                    break;
                default:
                    break;
            }
            break;
        case SHOW_TYPE_DECIMAL_UNSIGNED:
            switch(mySize)
            {
                case SHOW_TYPE_SIZE_8:
                    printf("                                                                 | ");
                    break;
                case SHOW_TYPE_SIZE_16:
                    printf("                                                 | ");
                    break;
                case SHOW_TYPE_SIZE_32:
                    printf("                                         | ");
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
                        printf("                                                 | ");
                    break;
                case SHOW_TYPE_SIZE_16:
                        printf("                                         | ");
                    break;
                case SHOW_TYPE_SIZE_32:
                        printf("                                     | ");
                    break;
                default:
                    break;
            }
            break;
    }
    printf("file : %s\r", fileName[1]);
    printf("                   | file : %s", fileName[0]);
    printf(COLOR_NORMAL"\n");
    printf(COLOR_BOLD_GREEN"----------------------------------------------------------------------------------------------------------------------------\n"COLOR_NORMAL);
}



void showFile(FILE *filePointer ,I32 CurentFilePosition)
{
    /*
    U16 data[NB_DATA_PER_LINE];
    U32 i;
    U32 j;
    
    showConfiguration();
    
    // Display the main show
    printf(COLOR_BOLD_YELLOW"Ofset :    |");
    for (i = 0; i< NB_DATA_PER_LINE; i++)
    {
        printf("    +%x",(unsigned int)i);
    }
    printf(COLOR_NORMAL"\n");
    // Display the main show
    printf(COLOR_BOLD_YELLOW"------------");
    for (i = 0; i< NB_DATA_PER_LINE; i++)
    {
        printf("------");
    }
    printf(COLOR_NORMAL"\n");
    for (j=0; j < NB_MAX_LINE; j++)
    {
    
        if (fread(data, sizeof(I8), NB_DATA_PER_LINE, filePointer)  != NB_DATA_PER_LINE)
        {
            printf("No More Data in the file");
            j = NB_MAX_LINE;
        }
        else
        {
            U32 lineNumber = 0;
            lineNumber = (j ) * NB_DATA_PER_LINE + CurentFilePosition;
            printf(COLOR_BOLD_YELLOW"0x%08x | "COLOR_NORMAL, (unsigned int)lineNumber);
            for (i = 0; i< NB_DATA_PER_LINE; i++)
            {
                //printf("%04x ", data[i]);
                printf("%5d ", data[i]);
            }
        }
        printf(COLOR_NORMAL"\n");
    }
    */
}

void print_U32(U32 data)
{
    
}


void print_I32(I32 data)
{
    
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
                    //printf("%08x%08x"COLOR_NORMAL" ", (unsigned int)((U32)(data>>32)), (unsigned int)((U32)data));
                    break;
                default:
                    break;
            }
            break;
        case SHOW_TYPE_DECIMAL_SIGNED:
            switch(localSize)
            {
                case SHOW_TYPE_SIZE_8:
                    printf("    ");
                    break;
                case SHOW_TYPE_SIZE_16:
                    printf("       ");
                    break;
                case SHOW_TYPE_SIZE_32:
                    printf("          ");
                    break;
                case SHOW_TYPE_SIZE_64:
                    //printf("%08x%08x"COLOR_NORMAL" ", (unsigned int)((U32)(data>>32)), (unsigned int)((U32)data));
                    break;
                default:
                    break;
            }

            break;
        case SHOW_TYPE_DECIMAL_UNSIGNED:
            switch(localSize)
            {
                case SHOW_TYPE_SIZE_8:
                    printf("    ");
                    break;
                case SHOW_TYPE_SIZE_16:
                    printf("       ");
                    break;
                case SHOW_TYPE_SIZE_32:
                    printf("           ");
                    break;
                case SHOW_TYPE_SIZE_64:
                    //printf("%08x%08x"COLOR_NORMAL" ", (unsigned int)((U32)(data>>32)), (unsigned int)((U32)data));
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    
}

void printElement(U64 data, showType_te localType, showTypeSize_te localSize, bool error)
{
    if (true == error)
    {
        printf(COLOR_BOLD_RED);
    }
    switch(localType)
    {
        case SHOW_TYPE_HEX:
            switch(localSize)
            {
                case SHOW_TYPE_SIZE_8:
                    printf("%02x"COLOR_NORMAL" ", (unsigned int)((U8)data));
                    break;
                case SHOW_TYPE_SIZE_16:
                    printf("%04x"COLOR_NORMAL" ", (unsigned int)((U16)data));
                    break;
                case SHOW_TYPE_SIZE_32:
                    printf("%08x"COLOR_NORMAL" ", (unsigned int)((U32)data));
                    break;
                case SHOW_TYPE_SIZE_64:
                    //printf("%08x%08x"COLOR_NORMAL" ", (unsigned int)((U32)(data>>32)), (unsigned int)((U32)data));
                    break;
                default:
                    break;
            }
            break;
        case SHOW_TYPE_DECIMAL_SIGNED:
            switch(localSize)
            {
                case SHOW_TYPE_SIZE_8:
                    printf("%4d"COLOR_NORMAL"", ((I8)data));
                    break;
                case SHOW_TYPE_SIZE_16:
                    printf("%6d"COLOR_NORMAL" ", ((I16)data));
                    break;
                case SHOW_TYPE_SIZE_32:
                    printf("%9d"COLOR_NORMAL" ", (int)((I32)data));
                    break;
                case SHOW_TYPE_SIZE_64:
                    //printf("%08x%08x"COLOR_NORMAL" ", (unsigned int)((U32)(data>>32)), (unsigned int)((U32)data));
                    break;
                default:
                    break;
            }

            break;
        case SHOW_TYPE_DECIMAL_UNSIGNED:
            switch(localSize)
            {
                case SHOW_TYPE_SIZE_8:
                    printf("%3d"COLOR_NORMAL" ", ((U8)data));
                    break;
                case SHOW_TYPE_SIZE_16:
                    printf("%5d"COLOR_NORMAL" ", ((U16)data));
                    break;
                case SHOW_TYPE_SIZE_32:
                    printf("%9d"COLOR_NORMAL" ", (unsigned int)((U32)data));
                    break;
                case SHOW_TYPE_SIZE_64:
                    //printf("%08x%08x"COLOR_NORMAL" ", (unsigned int)((U32)(data>>32)), (unsigned int)((U32)data));
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
    U8   data_8  [16];
    U16  data_16 [8];
    U32  data_32 [4];
    U64  data_64 [2];
}inputData_tu;

void compareFile(FILE *filePointer1, FILE *filePointer2 ,I32 CurentFilePosition)
{
    inputData_tu data1;
    inputData_tu data2;
    U32 i;
    U32 j;
    
    
    showConfiguration();
    
    showTypeSize_te mySize = getTypeSize();
    showType_te myType = getType();
    
    // Display the main show
    printf(COLOR_BOLD_YELLOW"Ofset :    |       | ");
    switch(myType)
    {
        case SHOW_TYPE_DECIMAL_SIGNED:
            for (i = 0 ; i<2 ; i++ )
            {
                switch(mySize)
                {
                    case SHOW_TYPE_SIZE_8:
                        for (j=0; j<2 ; j++ ) {
                            printf("  +0  +1  +2  +3  +4  +5  +6  +7  +8  +9  +A  +B  +C  +D  +E  +F | ");
                        }
                        break;
                    case SHOW_TYPE_SIZE_16:
                        for (j=0; j<2 ; j++ ) {
                            printf("    +0     +2     +4     +6     +8     +A     +C     +E  | ");
                        }
                        break;
                    case SHOW_TYPE_SIZE_32:
                        for (j=0; j<2 ; j++ ) {
                            printf("       +0        +4        +8        +C  | ");
                        }
                        break;
                    default:
                        break;
                }
                if (i == 0)
                {
                    printf(COLOR_NORMAL"\n");
                    printf(COLOR_BOLD_MAGENTA"           | ofset | ");
                }
            }
            break;
        case SHOW_TYPE_DECIMAL_UNSIGNED:
            for (i = 0 ; i<2 ; i++ )
            {
                switch(mySize)
                {
                    case SHOW_TYPE_SIZE_8:
                        for (j=0; j<2 ; j++ ) {
                            printf(" +0  +1  +2  +3  +4  +5  +6  +7  +8  +9  +A  +B  +C  +D  +E  +F  | ");
                        }
                        break;
                    case SHOW_TYPE_SIZE_16:
                        for (j=0; j<2 ; j++ ) {
                            printf("   +0    +2    +4    +6    +8    +A    +C    +E  | ");
                        }
                        break;
                    case SHOW_TYPE_SIZE_32:
                        for (j=0; j<2 ; j++ ) {
                            printf("       +0        +4        +8        +C  | ");
                        }
                        break;
                    default:
                        break;
                }
                if (i == 0)
                {
                    printf(COLOR_NORMAL"\n");
                    printf(COLOR_BOLD_MAGENTA"           | ofset | ");
                }
            }
            break;
        case SHOW_TYPE_HEX:
        default : 
            for (i = 0 ; i<2 ; i++ )
            {
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
                    default:
                        break;
                }
                if (i == 0)
                {
                    printf(COLOR_NORMAL"\n");
                    printf(COLOR_BOLD_MAGENTA"           | ofset | ");
                }
            }
            break;
    }
    printf(COLOR_NORMAL"\n");
    
    
    // Display the main show
    printf(COLOR_BOLD_YELLOW"------------");
    for (i = 0; i< 16; i++)
    {
        printf("---");
    }
    printf("---");
    for (i = 0; i< 16; i++)
    {
        printf("---");
    }
    printf(COLOR_NORMAL"\n");
    for (j=0; j < NB_MAX_LINE; j++)
    {
        U32 readFile1 = 0;
        U32 readFile2 = 0;
        U32 lineNumber = 0;
        U32 numberOfCycle;
        // read data in files : 
        readFile1 = fread(data1.data_8, sizeof(U8), 16, filePointer1);
        readFile2 = fread(data2.data_8, sizeof(U8), 16, filePointer2);
        // display the line number
        lineNumber = j * (NB_DATA_PER_LINE*4) + CurentFilePosition;
        printf(COLOR_BOLD_YELLOW"0x%08x | "COLOR_NORMAL, (unsigned int)lineNumber);
        switch(mySize)
        {
            case SHOW_TYPE_SIZE_8:
                printf(COLOR_BOLD_MAGENTA"%5d | "COLOR_NORMAL, (int)(lineNumber));
                break;
            case SHOW_TYPE_SIZE_16:
                printf(COLOR_BOLD_MAGENTA"%5d | "COLOR_NORMAL, (int)(lineNumber/2));
                break;
            case SHOW_TYPE_SIZE_32:
                printf(COLOR_BOLD_MAGENTA"%5d | "COLOR_NORMAL, (int)(lineNumber/4));
                break;
            default:
                break;
        }
        if (readFile1 == 0)
        {
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
            for (i = 0; i< numberOfCycle; i++)
            {
                    printNoElement(myType, mySize);
            }
        }
        else // TODO : mettre les octet qui reste a la fin si ce n'est pas complet
        {
            i = 0;
            numberOfCycle = 16;
            while (i< numberOfCycle)
            {
                switch(mySize)
                {
                    case SHOW_TYPE_SIZE_8:
                        numberOfCycle = 16;
                        for (i = 0; i< numberOfCycle; i++)
                        {
                            if (readFile1 >= (i+1))
                            {
                                printElement((U64)data1.data_8[i], myType, mySize, (data1.data_8[i] != data2.data_8[i]));
                            }
                            else
                            {
                                printNoElement(myType, mySize);
                            }
                        }
                        break;
                    case SHOW_TYPE_SIZE_16:
                        numberOfCycle = 8;
                        for (i = 0; i< numberOfCycle; i++)
                        {
                            if ((readFile1/2) >= (i+1))
                            {
                                printElement((U64)data1.data_16[i], myType, mySize, (data1.data_16[i] != data2.data_16[i]));
                            }
                            else
                            {
                                printNoElement(myType, mySize);
                            }
                        }
                        break;
                    case SHOW_TYPE_SIZE_32:
                        numberOfCycle = 4;
                        for (i = 0; i< numberOfCycle; i++)
                        {
                            if ((readFile1/4) >= (i+1))
                            {
                                printElement((U64)data1.data_32[i], myType, mySize, (data1.data_32[i] != data2.data_32[i]));
                            }
                            else
                            {
                                printNoElement(myType, mySize);
                            }
                        }
                        break;
                    case SHOW_TYPE_SIZE_64:
                        numberOfCycle = 2;
                        for (i = 0; i< numberOfCycle; i++)
                        {
                            if ((readFile1/8) >= (i+1))
                            {
                                printElement((U64)data1.data_64[i], myType, mySize, (data1.data_8[i] != data2.data_64[i]));
                            }
                            else
                            {
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
        if (readFile2 == 0)
        {
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
            for (i = 0; i< numberOfCycle; i++)
            {
                    printNoElement(myType, mySize);
            }
        }
        else
        {
            i = 0;
            numberOfCycle = 16;
            while (i< numberOfCycle)
            {
                switch(mySize)
                {
                    case SHOW_TYPE_SIZE_8:
                        numberOfCycle = 16;
                        for (i = 0; i< numberOfCycle; i++)
                        {
                            if (readFile2 >= (i+1))
                            {
                                printElement((U64)data2.data_8[i], myType, mySize, (data1.data_8[i] != data2.data_8[i]));
                            }
                            else
                            {
                                printNoElement(myType, mySize);
                            }
                        }
                        break;
                    case SHOW_TYPE_SIZE_16:
                        numberOfCycle = 8;
                        for (i = 0; i< numberOfCycle; i++)
                        {
                            if ((readFile2/2) >= (i+1))
                            {
                                printElement((U64)data2.data_16[i], myType, mySize, (data1.data_16[i] != data2.data_16[i]));
                            }
                            else
                            {
                                printNoElement(myType, mySize);
                            }
                        }
                        break;
                    case SHOW_TYPE_SIZE_32:
                        numberOfCycle = 4;
                        for (i = 0; i< numberOfCycle; i++)
                        {
                            if ((readFile2/4) >= (i+1))
                            {
                                printElement((U64)data2.data_32[i], myType, mySize, (data1.data_32[i] != data2.data_32[i]));
                            }
                            else
                            {
                                printNoElement(myType, mySize);
                            }
                        }
                        break;
                    case SHOW_TYPE_SIZE_64:
                        numberOfCycle = 2;
                        for (i = 0; i< numberOfCycle; i++)
                        {
                            if ((readFile2/8) >= (i+1))
                            {
                                printElement((U64)data2.data_64[i], myType, mySize, (data1.data_8[i] != data2.data_64[i]));
                            }
                            else
                            {
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
        printf(COLOR_NORMAL"\n");
        
        /*
        if (    fread(data1.data_8, sizeof(U8), 16, filePointer1)  != 16
             || fread(data2.data_8, sizeof(U8), 16, filePointer2)  != 16)
        {
            printf("No More Data in the file                                                                                                       \n");
            for (;j < NB_MAX_LINE; j++)
            {
                printf("                                                                                                                           \n");
            }
        }
        else
        {
            U32 lineNumber = 0;
            U32 numberOfCycle;
            lineNumber = j * (NB_DATA_PER_LINE*4) + CurentFilePosition;
            printf(COLOR_BOLD_YELLOW"0x%08x | "COLOR_NORMAL, (unsigned int)lineNumber);
            switch(mySize)
            {
                case SHOW_TYPE_SIZE_8:
                    printf(COLOR_BOLD_MAGENTA"%5d | "COLOR_NORMAL, (int)(lineNumber));
                    break;
                case SHOW_TYPE_SIZE_16:
                    printf(COLOR_BOLD_MAGENTA"%5d | "COLOR_NORMAL, (int)(lineNumber/2));
                    break;
                case SHOW_TYPE_SIZE_32:
                    printf(COLOR_BOLD_MAGENTA"%5d | "COLOR_NORMAL, (int)(lineNumber/4));
                    break;
                default:
                    break;
            }
            i = 0;
            numberOfCycle = 16;
            while (i< numberOfCycle)
            {
                switch(mySize)
                {
                    case SHOW_TYPE_SIZE_8:
                        numberOfCycle = 16;
                        for (i = 0; i< numberOfCycle; i++)
                        {
                            printElement((U64)data1.data_8[i], myType, mySize, (data1.data_8[i] != data2.data_8[i]));
                        }
                        break;
                    case SHOW_TYPE_SIZE_16:
                        numberOfCycle = 8;
                        for (i = 0; i< numberOfCycle; i++)
                        {
                            printElement((U64)data1.data_16[i], myType, mySize, (data1.data_16[i] != data2.data_16[i]));
                        }
                        break;
                    case SHOW_TYPE_SIZE_32:
                        numberOfCycle = 4;
                        for (i = 0; i< numberOfCycle; i++)
                        {
                            printElement((U64)data1.data_32[i], myType, mySize, (data1.data_32[i] != data2.data_32[i]));
                        }
                        break;
                    case SHOW_TYPE_SIZE_64:
                        numberOfCycle = 2;
                        for (i = 0; i< numberOfCycle; i++)
                        {
                            printElement((U64)data1.data_64[i], myType, mySize, (data1.data_8[i] != data2.data_64[i]));
                        }
                        break;
                    default :
                        numberOfCycle = 0;
                        break;
                }
                i++;
            }
            printf(" | ");
            i = 0;
            numberOfCycle = 16;
            while (i< numberOfCycle)
            {
                switch(mySize)
                {
                    case SHOW_TYPE_SIZE_8:
                        numberOfCycle = 16;
                        for (i = 0; i< numberOfCycle; i++)
                        {
                            printElement((U64)data2.data_8[i], myType, mySize, (data1.data_8[i] != data2.data_8[i]));
                        }
                        break;
                    case SHOW_TYPE_SIZE_16:
                        numberOfCycle = 8;
                        for (i = 0; i< numberOfCycle; i++)
                        {
                            printElement((U64)data2.data_16[i], myType, mySize, (data1.data_16[i] != data2.data_16[i]));
                        }
                        break;
                    case SHOW_TYPE_SIZE_32:
                        numberOfCycle = 4;
                        for (i = 0; i< numberOfCycle; i++)
                        {
                            printElement((U64)data2.data_32[i], myType, mySize, (data1.data_32[i] != data2.data_32[i]));
                        }
                        break;
                    case SHOW_TYPE_SIZE_64:
                        numberOfCycle = 2;
                        for (i = 0; i< numberOfCycle; i++)
                        {
                            printElement((U64)data2.data_64[i], myType, mySize, (data1.data_8[i] != data2.data_64[i]));
                        }
                        break;
                    default :
                        numberOfCycle = 0;
                        break;
                }
                i++;
            }
        }
        */
    }
}








/* Fonction pour le thread du magasin. */
void * threadDisplay (void * p_data)
{
   while (1)
   {
        if (getParamModification())
        {
            U32 CurentFilePosition = getOfsetFile();
            fseek ( filePointer[0] , CurentFilePosition , SEEK_SET );
            if (NULL != filePointer[1])
            {
                fseek ( filePointer[1] , CurentFilePosition , SEEK_SET );
            }
            
            
            if (    NULL != filePointer[0]
                 && NULL == filePointer[1] )
            {
                showFile(filePointer[0],CurentFilePosition);
            }
            else if (    NULL != filePointer[0]
                      && NULL != filePointer[1] )
            {
                compareFile(filePointer[0],filePointer[1], CurentFilePosition);
            }
        }
        else
        {
            usleep(10000);
        }
   }

   return NULL;
}



