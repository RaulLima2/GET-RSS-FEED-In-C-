#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "get_datas.h"

char *columns_search(const char *tag_search, const char *_linefile)
{
	bool check_input_ = false;
	check_input_ = strstr(_linefile, tag_search) != NULL;
	if (check_input_ == true)
	{
		return strstr(_linefile, tag_search);
	}

	return "\0";
}

char *cdata_change(char *line_file, char* tag_in_line)
{
	int i = 0;
	char* change_line = (char*)calloc(MAX_LINE_SIZE, sizeof(char));

	if (strstr(line_file, "<![CDATA[") != NULL)
	{
		sprintf(change_line,"%s ",tag_in_line);
		strncat(change_line, strstr(line_file, "<![CDATA[") + strlen("<![CDATA["), strlen(strstr(line_file, "<![CDATA[")));
		strcpy(line_file, change_line);

		for (i = 0; i < MAX_LINE_SIZE; i++)
		{
			if (line_file[i] == ']' && line_file[i + 1] == ']')
			{
				line_file[i] = ' ';
				line_file[i + 1] = ' ';
			}
		}
	}

	return line_file;
}