#
# Makefile for a CS420 lab or programming assignment.
# Do not modify this file!!!
#

SUBMIT_URL = https://cs.ycp.edu/marmoset/bluej/SubmitProjectViaBlueJSubmitter
COURSE_NAME = CS 420
SEMESTER = Fall $(shell date +%Y)
PROJECT_NUMBER = lab03

CC = gcc
CFLAGS=-std=c99 -Wall
LIBS=-pthread



all: main


utils.o: utils.h utils.c
	$(CC) $(CFLAGS) -c utils.c

main: utils.o fileWriter main.c
	$(CC) $(CFLAGS) main.c -o main utils.o $(LIBS)
    
fileWriter: utils.o fileWriter.c
	$(CC) $(CFLAGS) fileWriter.c -o fileWriter utils.o $(LIBS)


runTest: all
	./main -p 25 -t 25 -f testOutput.txt


clean:
	rm -f *.o *~ solution.zip submit.properties
	rm -rf *.dSYM
	rm -f main fileWriter testOutput.txt


###############################################
# The following is for submission to Marmoset
###############################################

submit : clean submit.properties solution.zip
	perl submitToMarmoset.pl solution.zip submit.properties

solution.zip : collected-files.txt
	@echo "Creating a solution zip file"
	@zip -9 $@ `cat collected-files.txt`
	@rm -f collected-files.txt

# Create the submit.properties file that describes how
# the project should be uploaded to the Marmoset server.
submit.properties : nonexistent
	@echo "Creating submit.properties file"
	@rm -f $@
	@echo "submitURL = $(SUBMIT_URL)" >> $@
	@echo "courseName = $(COURSE_NAME)" >> $@
	@echo "semester = $(SEMESTER)" >> $@
	@echo "projectNumber = $(PROJECT_NUMBER)" >> $@

# Collect the names of all files that don't appear
# to be generated files.
collected-files.txt :
	@echo "Collecting the names of files to be submitted"
	@rm -f $@
	@find . -not \( \
				-name '*\.o' \
				-or -name '*\.exe' \
				-or -name '*~' \
				-or -name 'collected-files.txt' \
				-or -name 'submit.properties' \
				-or -type d \
				-or -name '.*' \
			\) -print \
		| perl -ne 's,\./,,; print' \
		> $@

# This is just a dummy target to force other targets
# to always be out of date.
nonexistent :


