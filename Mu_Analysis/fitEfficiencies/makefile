#edit : main.o kbd.o command.o display.o \
       #insert.o search.o files.o utils.o
        #cc -o edit main.o kbd.o command.o display.o \
                   #insert.o search.o files.o utils.o

#main.o : main.c defs.h
        #cc -c main.c
#kbd.o : kbd.c defs.h command.h
        #cc -c kbd.c
#command.o : command.c defs.h command.h
        #cc -c command.c
#display.o : display.c defs.h buffer.h
        #cc -c display.c
#insert.o : insert.c defs.h buffer.h
        #cc -c insert.c
#search.o : search.c defs.h buffer.h
        #cc -c search.c
#files.o : files.c defs.h buffer.h command.h
        #cc -c files.c
#utils.o : utils.c defs.h
        #cc -c utils.c
#clean :
        #rm edit main.o kbd.o command.o display.o \
           #insert.o search.o files.o utils.o

CC=g++
ROOTFLG=`root-config --cflags --libs`

fitting_routine.exe : fitting_routine.o fit_efficiencies.o
	$(CC) -o fitting_routine.exe fittingRoutine.o fit_efficiencies.o ${ROOTFLG}

fitting_routine.o : fittingRoutine.C fittingRoutine.h
	$(CC) -c fittingRoutine.C fittingRoutine.h ${ROOTFLG}

fit_efficiencies.o : fit_efficiencies.C
	$(CC) -c fit_efficiencies.C ${ROOTFLG} 

clean :
	rm *.pcm *.d *.so .*.swp *.o *.gch
