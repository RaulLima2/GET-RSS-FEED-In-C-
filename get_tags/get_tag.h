#ifndef GET_TAG_H
#define GET_TAG_H


void get_tag(const char* __restrict__ _filename);

char *title_get(char *_input_, char *_tag_open_, char *_tag_close_);

char *description_get(char *_input_);

char *link_get(char *_input_, char *_tag_open_, char *_tag_close_);

char *pubDate_get(char *_input_, char *_tag_open_, char *_tag_close_);

void change_file(const char* __restrict__ _filename);

#endif