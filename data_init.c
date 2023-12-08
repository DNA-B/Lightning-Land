#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct data {
	char name[20];
	int price;
	int min_price;
	int is_selled;
	int is_trade;
}selling_data;

void data_init() {
	selling_data data[10];
	FILE *fp = fopen("LL_data.txt", "r");
	if (fp == NULL) {
		printf("거래 정보가 없습니다.");
		return 0;
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
				strcpy(data[idx].name, token);
			}
			else if (i == 1) {
				data[idx].price = atoi(token);
			}
			else if (i == 2) {
				data[idx].min_price = atoi(token);
			}
			else if (i == 3) {
				data[idx].is_selled = atoi(token);
			}
			else if (i == 4) {
				data[idx].is_trade = atoi(token);
			}
			i++;
			token = strtok(NULL, " ");
		}
		idx++;
	}

	for (int i = 0; i < idx-1; i++) {
		printf("%s %d %d %d %d\n", data[i].name, data[i].price, data[i].min_price, data[i].is_selled, data[i].is_trade);
	}

	fclose(fp);
}



