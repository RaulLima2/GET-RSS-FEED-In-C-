#ifndef GET_TAG_H
#define GET_TAG_H

#define MAX_LINE_SIZE 50000


void get_tag(const char* __restrict__ _filename);

void change_file(const char* __restrict__ _filename);

char* columns_search(const char* tag_search, const char* _linefile);

#endif