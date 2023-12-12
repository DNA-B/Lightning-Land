 #ifndef _DATA_INIT_H
 #define _DATA_INIT_H

typedef struct Data {
	char name[32];
	char price[32];
	char min_price[32];
	int is_selled;
	int is_trading;
	int idx;
} Data;

void data_init(Data* item);

 #endif
