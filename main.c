#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "get_datas/get_datas.h"
#include "get_tags/get_tag.h"

int main(void)
{
	char* nome_file = (char*)calloc(MAX_LINE_SIZE, sizeof(char));

	printf("Insira o local do arquivo: \n");
	fgets(nome_file, 100, stdin);

	nome_file[strlen(nome_file) - 1] = '\0';

	get_tag(nome_file);

  return 0;
}