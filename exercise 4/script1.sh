#!/bin/bash

EXECUTABLE=./galaxyring.exec
TESTCASES_FOLDER=galaxyring
for i in `seq 1 30`;
do
	echo =========================================
	echo Running testcase $TESTCASES_FOLDER/input$i.txt
	INPUT_NAME=$TESTCASES_FOLDER/input$i.txt
	OUTPUT_NAME=$TESTCASES_FOLDER/output$i.txt
	echo Program output
	prog_result="`$EXECUTABLE < $INPUT_NAME`"
	echo $prog_result
	correct_result="`cat $OUTPUT_NAME`"
	echo output$i.txt
	echo $correct_result
done
