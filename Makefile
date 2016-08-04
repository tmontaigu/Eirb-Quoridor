CC=gcc
CFLAGS= -Wall -std=c99 -g -O0
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
				 random.c \
				 prompt_play.c

FILES_Display = affichage.c

FILES_Test_is_reachable = serveur.c \
						  test_is_reachable.c \
						  fct_annexes.c

FILES_Test_is_move_valid = serveur.c \
						  test_is_move_valid.c \
						  fct_annexes.c

FILES_Test_determine_direction = serveur.c \
								 test_determine_direction.c \
								 fct_annexes.c
#------------------------------------------------------------------------------
# List of objects used to generate the executables
#------------------------------------------------------------------------------
OBJS_Quoridor = $(FILES_Quoridor:.c=.o)
OBJS_Display = $(FILES_Display:.c=.o)
OBJS_Test_is_reachable = $(FILES_Test_is_reachable:.c=.o)
OBJS_Test_is_move_valid = $(FILES_Test_is_move_valid:.c=.o)
OBJS_Test_determine_direction = $(FILES_Test_determine_direction:.c=.o)
#------------------------------------------------------------------------------
# Line to compile the executable file
#------------------------------------------------------------------------------
COMPILE_EXECUTABLE = $(CC) $(CFLAGS)  -o $@ $^ $(LIBS)





Quoridor: $(patsubst %, obj/%,$(OBJS_Quoridor))
	$(COMPILE_EXECUTABLE)
	@echo Success!

Affichage: $(patsubst %, obj/%,$(OBJS_Display))
	$(COMPILE_EXECUTABLE)
	@echo Success!

Test_is_reachable: $(patsubst %, obj/%,$(OBJS_Test_is_reachable))
	$(COMPILE_EXECUTABLE)
	@echo Success!


Test_is_move_valid: $(patsubst %, obj/%,$(OBJS_Test_is_move_valid))
	$(COMPILE_EXECUTABLE)
	@echo Success!
	
Test_determine_direction: $(patsubst %, obj/%,$(OBJS_Test_determine_direction))
	$(COMPILE_EXECUTABLE)
	@echo Success!

obj/%.o: %.c
	$(CC)  $(CFLAGS)  -c $< -o $@ 


clean : 
	rm -f obj/*.o *.aux *.log

mrproper : 
	rm -f obj/*.o *.aux *.log Quoridor Affichage
