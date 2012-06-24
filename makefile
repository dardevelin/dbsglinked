CC=gcc
CFLAGS=-Wall -Werror -std=c99 -pedantic
#LDFLAGS=
EXECUTABLE=dbsglinked
SOURCES=main.c glinked_list.c
OBJECTS=$(SOURCES:.c=.o) 
#CLEAN: $(EXECUTABLE)
	#rm $(OBJECTS)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(EXECUTABLE)
	
$(OBJECTS): $(SOURCES)
	$(CC) $(CFLAGS) -c $(SOURCES) 
