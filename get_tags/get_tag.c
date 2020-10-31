#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../get_datas/get_datas.h"
#include "get_tag.h"

int count_insert = 0;
char *cdata_change(char *line_file, char* tag_in_line);

/*Functions get:
	->change tags in xml for tags html, 
	if  haven't tags xml in line, is going print some line in file.html*/
char *description_get(char *_input_);
char *link_get(char *_input_, char *_tag_open_, char *_tag_close_);
char *pubDate_get(char *_input_, char *_tag_open_, char *_tag_close_);
char *title_get(char *_input_, char *_tag_open_, char *_tag_close_);

const char *type_tags_html[] = {
	"<html>\t\n<head>\t\t\n<title>%s</title>\n</head>\n<body>\n",
	"<h1>%s</h1>\n<br>\n",
	"<h2>%s</h2>\n",
	"<a href=\"%s\">%s</a>\n",
	"<p>Data de publicação: %s</p>\n",
	"<p>%s ",
	"%s</p><hr>\n",
	"<br>\n",
	"<hr>\n",
	"</body>\n</html>\n"};

char *_type_tags_xml[] = {
	"<title>",
	"</title>",
	"<link>",
	"</link>",
	"<pubDate>",
	"</pubDate>"};

void get_tag(const char *__restrict__ _filename)
{
	int count_description = 0;
	char *_line_input_ = (char *)calloc(MAX_LINE_SIZE, sizeof(char));
	FILE *file_xml = fopen(_filename, "r+");
	FILE *file_html = fopen("output.html", "aw+");

	while (fgets(_line_input_, MAX_LINE_SIZE, file_xml) != NULL)
	{

		_line_input_[strlen(_line_input_) - 1] = '\0';

		if (strstr(_line_input_, "<title>") != NULL)
		{
			_line_input_ = cdata_change(_line_input_, _type_tags_xml[0]);
			fprintf(file_html, "%s", title_get(_line_input_, _type_tags_xml[0], _type_tags_xml[1]));

			count_insert++;

			if (count_insert == 1)
			{
				fprintf(file_html, "%s", title_get(_line_input_, _type_tags_xml[0], _type_tags_xml[1]));
				count_insert += 1;
			}
		}
		else if (strstr(_line_input_, "<link>") != NULL)
		{
			_line_input_ = cdata_change(_line_input_, _type_tags_xml[2]);
			fprintf(file_html, "%s", link_get(_line_input_, _type_tags_xml[2], _type_tags_xml[3]));
		}
		else if (strstr(_line_input_, "<pubDate>") != NULL)
		{
			_line_input_ = cdata_change(_line_input_, _type_tags_xml[4]);
			fprintf(file_html, "%s", pubDate_get(_line_input_, _type_tags_xml[4], _type_tags_xml[5]));
		}
		else
		{

			_line_input_ = cdata_change(_line_input_,"<description>");

			if(strstr(_line_input_,"<description>") != NULL)
			{
				fprintf(file_html, "%s", description_get(columns_search("<description>", _line_input_)));

				if(count_description != 1)
				{
					count_description++;
				}
			}
			else if(strstr(_line_input_,"</description>") != NULL)
			{
				fprintf(file_html, "%s", description_get(columns_search("</description>", _line_input_)));

				count_description++;

				if(count_description == 2)
				{
					count_description = 0;
				}
			}
			
			if((strstr(_line_input_,"<description>") != NULL) && (strstr(_line_input_,"</description>") != NULL))
			{
				count_description = 0;
			}
			
			if(count_description == 1)
			{
				fprintf(file_html,"%s\n", _line_input_);
			}

		}
		
	}
	fprintf(file_html, "%s", type_tags_html[9]);
}


char *title_get(char *_input_, char *_tag_open_, char *_tag_close_)
{
	char *temp = (char *)calloc(MAX_LINE_SIZE, sizeof(char));
	char *temp1 = (char *)calloc(MAX_LINE_SIZE, sizeof(char));
	char *between = (char *)calloc(MAX_LINE_SIZE, sizeof(char));

	strncpy(temp, strstr(_input_, _tag_open_) + strlen(_tag_open_), strlen(strstr(_input_, _tag_open_)));
	strncpy(temp1, temp, strlen(temp) - strlen(_tag_close_));

	if (count_insert == 0)
	{
		sprintf(between, type_tags_html[0], temp1);
	}
	else if (count_insert == 1)
	{
		sprintf(between, type_tags_html[1], temp1);
	}
	else
	{
		sprintf(between, type_tags_html[2], temp1);
	}

	return between;
}

char *pubDate_get(char *_input_, char *_tag_open_, char *_tag_close_)
{
	char *temp = (char *)calloc(MAX_LINE_SIZE, sizeof(char));
	char *temp1 = (char *)calloc(MAX_LINE_SIZE, sizeof(char));
	char *between = (char *)calloc(MAX_LINE_SIZE, sizeof(char));

	strncpy(temp, strstr(_input_, _tag_open_) + strlen(_tag_open_), strlen(strstr(_input_, _tag_open_)));
	strncpy(temp1, temp, strlen(temp) - strlen(_tag_close_));
	sprintf(between, type_tags_html[4], temp1);

	return between;
}

char *link_get(char *_input_, char *_tag_open_, char *_tag_close_)
{
	char *temp = (char *)calloc(MAX_LINE_SIZE, sizeof(char));
	char *temp1 = (char *)calloc(MAX_LINE_SIZE, sizeof(char));
	char *between = (char *)calloc(MAX_LINE_SIZE, sizeof(char));

	strncpy(temp, strstr(_input_, _tag_open_) + strlen(_tag_open_), strlen(strstr(_input_, _tag_open_)));
	strncpy(temp1, temp, strlen(temp) - strlen(_tag_close_));
	sprintf(between, type_tags_html[3], temp1, temp1);

	return between;
}

char *description_get(char *_input_)
{
	char *temp = (char *)calloc(MAX_LINE_SIZE, sizeof(char));
	char *between = (char *)calloc(MAX_LINE_SIZE, sizeof(char));

	if (strstr(_input_, "<description>") != NULL)
	{
		strncpy(temp, _input_ + strlen("<description>"), strlen(strstr(_input_, "<description>")));
		sprintf(between, type_tags_html[5], temp);
	}
	else if (strstr(_input_, "</description>") != NULL)
	{
		if (strcmp(_input_, "</description>") != 0)
		{
			strncpy(temp, _input_ + strlen(_input_), strlen(_input_));
			sprintf(between, type_tags_html[6], temp);
		}
		else
		{
			sprintf(between, "%s", "</p>\n<hr>\n");
		}
	}
	else
	{
		sprintf(between, "%s", _input_);
	}

	return between;
}
