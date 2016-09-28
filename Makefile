CC=gcc
LD=ld

EXEC=iti

all: $(EXEC)

$(EXEC): iti.c language.h
	$(CC) $< -o $@ 

clean:
	rm $(EXEC)

install:
	cp $(EXEC) /usr/local/bin/$(EXEC)

.PHONY: all clean
