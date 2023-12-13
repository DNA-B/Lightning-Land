#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "data_init.h"

void data_save(Data* item) {
	FILE *fp = fopen("LL_after_data.txt", "w");

	if (fp == NULL) {
		perror("open error");
		exit(1);
	}

	for (int i = 0; i < 7; ++i) {
		fprintf(fp, "%s %s %s %d %d\n",
				item[i].name,
				item[i].price,
				item[i].min_price,
				item[i].is_selled,
				item[i].is_trading);
	}

	fclose(fp);
}
