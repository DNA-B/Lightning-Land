#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_init.h"
#include <unistd.h>

int main() {

	FILE *fp = fopen("LL_data.txt", "w");

	if (fp == NULL) {
		perror("open error");
		exit(1)
	}

	for (i = 0; i < 7; ++i) {
		fprintf(fp, "%s %d %d %d %d\n",
				item[i].name,
				item[i].idx,
				item[i].price,
				item[i].min_price,
				item[i].is_trading);
	}

	fclose(fp);

	return 0;
}

