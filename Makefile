OBJS	= get_tag.o main.o
SOURCE	= get/get_tag.c main.c
HEADER	= 
OUT	= conversor_xml_for_html
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

conversor_xml_for_html: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT)
get_tag.o: get/get_tag.c
	$(CC) $(FLAGS) get/get_tag.c -std=c99

main.o: main.c
	$(CC) $(FLAGS) main.c -std=c99

cls:
	rm -f $(OBJS) $(OUT)

run: $(OUT)
	./$(OUT)
