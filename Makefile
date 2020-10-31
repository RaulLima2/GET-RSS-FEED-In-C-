OBJS	= get_datas.o get_tag.o main.o
SOURCE	= get_datas/get_datas.c get_tags/get_tag.c main.c
HEADER	= 
OUT	= conversor_xml_for_html
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

conversor_xml_for_html: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT)
get_datas.o: get_datas/get_datas.c
	$(CC) $(FLAGS) get_datas/get_datas.c -std=c99
get_tag.o: get_tags/get_tag.c
	$(CC) $(FLAGS) get_tags/get_tag.c -std=c99

main.o: main.c
	$(CC) $(FLAGS) main.c -std=c99

cls:
	rm -rf $(OBJS) *.html $(OUT)

run: $(OUT)
	./$(OUT)
