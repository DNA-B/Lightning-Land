#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data_init.h"
	
struct Data* data_init() {
	FILE *fp = fopen("LL_data.txt", "r");	
	struct Data* item = (struct Data*)malloc(10 * sizeof(struct Data));
	
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
			if (i == 0) {
				strcpy(item[idx].name, token);
			}
			else if (i == 1) {
				item[idx].price = atoi(token);
			}
			else if (i == 2) {
				item[idx].min_price = atoi(token);
			}
			else if (i == 3) {
				item[idx].is_selled = atoi(token);
			}
			else if (i == 4) {
				item[idx].is_trade = atoi(token);
			}
			i++;
			token = strtok(NULL, " ");
		}
		idx++;
	}

	fclose(fp);
	return item;
}
