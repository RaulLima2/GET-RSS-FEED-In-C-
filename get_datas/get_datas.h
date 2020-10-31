#ifndef GET_DATAS_H
#define GET_DATAS_H

#include <stdbool.h>

#define MAX_LINE_SIZE 500000

char *columns_search(const char *tag_search, const char *_linefile);

char *cdata_change(char *line_file, char* tag_in_line);

#endif
