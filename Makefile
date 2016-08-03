CC=gcc
CFLAGS= -Wall -std=c99
LIBS = -lncurses


all: Quoridor Affichage
#------------------------------------------------------------------------------
# Folders where the makefile will look for the sources of the rules.
#------------------------------------------------------------------------------

VPATH = tests:src:obj:src/affichage

INCLUDES = -I src/headers

#------------------------------------------------------------------------------
# List of files to generate the executables
#------------------------------------------------------------------------------
FILES_Quoridor = serveur.c \
				 fct_annexes.c \
				 is_blockable.c \
				 main.c \
				 random.c

FILES_Display = affichage.c

#------------------------------------------------------------------------------
# List of objects used to generate the executables
#------------------------------------------------------------------------------
OBJS_Quoridor = $(FILES_Quoridor:.c=.o)
OBJS_Display = $(FILES_Display:.c=.o)
#------------------------------------------------------------------------------
# Line to compile the executable file
#------------------------------------------------------------------------------
COMPILE_EXECUTABLE = $(CC) $(CFLAGS) $(LIBS) -o $@ $^ 





Quoridor: $(patsubst %, obj/%,$(OBJS_Quoridor))
	$(COMPILE_EXECUTABLE)
	@echo Success!

Affichage: $(patsubst %, obj/%,$(OBJS_Display))
	$(COMPILE_EXECUTABLE)
	@echo Success!


obj/%.o: %.c
	$(CC)  $(CFLAGS)  -c $< -o $@ 


clean : 
	rm -f obj/*.o *.aux *.log

mrproper : 
	rm -f obj/*.o *.aux *.log Quoridor Affichage
