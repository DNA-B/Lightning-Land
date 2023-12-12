#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data_init.h"

void data_init(Data* item) {
	FILE *fp = fopen("LL_data.txt", "r");	
	
	if (fp == NULL) {
		printf("거래 정보가 없습니다.");
		exit(1);
	}
	
	char buffer[1001], *token;
	int i = 0;
	int idx = 0;
	
	while (!feof(fp)) {
		i = 0;
		fgets(buffer, 1001, fp);
		token = strtok(buffer, " ");
		
		while (token != NULL) {
			if (i == 0)
				strcpy(item[idx].name, token);
			else if (i == 1)
				strcpy(item[idx].price, token);
			else if (i == 2)
				strcpy(item[idx].min_price, token);
			else if (i == 3)
				item[idx].is_selled = atoi(token);
			else if (i == 4)
				item[idx].is_trading = atoi(token);	
		
			i++;
			token = strtok(NULL, " ");
		}
		
		item[idx].idx = idx++;
	}

	fclose(fp);
	printf("***** Data Init Complete *****\n");
}
