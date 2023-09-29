# Makefile supermercat ncash
# Execution in cygwin: 
# Enter cygwin and change to the directory where you have the code. 
# Put the mymakefile in the same directory
# Run the makefile with the instruction: make -f mymakefile
# The makefile generates a supermercat.exe
# Run the supermercat with the instruction: ./supermercat.exe


supermercat: agenda.o cua.o sev.o stochastic.o
	gcc -o supermercat -lm agenda.o cua.o sev.o stochastic.o

agenda.o: agenda.c agenda.h sev.h
	gcc -c agenda.c

cua.o: cua.c cua.h sev.h
	gcc -c cua.c

sev.o: sev.c sev.h cua.h agenda.h 
	gcc -c sev.c

# To makesure everything is recompiled eliminate the objective and executable
# files
# in the cygwin terminal do: make -f makefile clean
clean: 
	rm *.o supermercat

