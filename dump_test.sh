#! /bin/bash

DUMP_DIR_EXP=.
DUMP_DIR_MATLAB=..

MATLAB_PREFIX=m__
MATLAB_SUFFIX=.raw
TANGO_PREFIX=exp
TANGO_SUFFIX=.raw

DUMP_FILES=(
    'WTX_')

#echo "Dump directory: $DUMP_DIR"
#echo "Dump files: ${DUMP_FILES[@]}"

COLOR_RESET=$(tput sgr0)
COLOR_FILENAME=$(tput bold)$(tput setaf 3)
COLOR_BIT_EXACT=$(tput bold)$(tput setaf 4)
COLOR_DIFFERENT=$(tput bold)$(tput setaf 1)
COLOR_ERROR=$(tput bold)$(tput setaf 5)

for i in "${DUMP_FILES[@]}" ; do
	for (( FileID=0; FileID<=1000; FileID++ )) ; do
		VALUE="010"
		if [ $FileID -lt 10 ] ; then
			VALUE="00$FileID"
		elif [ $FileID -lt 100 ] ; then
			VALUE="0$FileID"
		else
			VALUE="$FileID"
		fi
		
		MATLAB_DUMP="$DUMP_DIR_MATLAB/$MATLAB_PREFIX$i$VALUE*$MATLAB_SUFFIX"
		TANGO_DUMP="$DUMP_DIR_EXP/$TANGO_PREFIX$i$VALUE*$TANGO_SUFFIX"
		
		# TODO : afficher quend un des deux fichier existe
		
		if [ ! -e "$MATLAB_DUMP" ] ; then
			finanameLS=`ls $MATLAB_DUMP 2> /dev/null`
			if [ ! -e "$finanameLS" ] ; then
				#echo -e -n "$COLOR_ERROR [ ??? ] "
				#echo -e -n "\t\t\t\t\t$MATLAB_DUMP$COLOR_RESET\n"
				#echo -e -n "\t\t\t\t\t\t\t\t\t\t\t$COLOR_FILENAME$TANGO_DUMP$COLOR_RESET\n"
				continue
			else
				MATLAB_DUMP=$finanameLS
			fi
		fi
	
		if [ ! -e "$TANGO_DUMP" ] ; then
			finanameLS=`ls $TANGO_DUMP 2> /dev/null`
			if [ ! -e "$finanameLS" ] ; then
				#echo -e -n "$COLOR_ERROR [ ??? ]"
				#echo -e -n "\t\t\t\t\t$COLOR_FILENAME$MATLAB_DUMP$COLOR_RESET"
				#echo -e -n "\t\t\t\t\t\t\t\t\t\t\t$COLOR_ERROR$TANGO_DUMP$COLOR_RESET\n"
				continue
			else
				TANGO_DUMP=$finanameLS
			fi
		fi
		
		hexViewer -d $MATLAB_DUMP $TANGO_DUMP > .tmpResultHexViewer.txt
		VALUE_ERROR=$?
		RESULT=`cat .tmpResultHexViewer.txt`
		if [ $VALUE_ERROR -eq '0' ] ; then
			echo -e -n "$COLOR_ERROR [  OK  ] $COLOR_RESET"
			echo -e -n "\t\t\t\t\t$COLOR_FILENAME$MATLAB_DUMP$COLOR_RESET"
			echo -e -n "\t\t\t\t\t\t\t\t\t\t\t$COLOR_FILENAME$TANGO_DUMP$COLOR_RESET"
			echo -e -n "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t$RESULT\n"
		else
			echo -e -n "$COLOR_DIFFERENT [ERROR] $COLOR_RESET"
			echo -e -n "\t\toctet=$VALUE_ERROR"
			echo -e -n "\t\t\t\t\t$COLOR_FILENAME$MATLAB_DUMP$COLOR_RESET"
			echo -e -n "\t\t\t\t\t\t\t\t\t\t\t$COLOR_FILENAME$TANGO_DUMP$COLOR_RESET"
			echo -e -n "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t$RESULT\n"
		fi
	done
done

