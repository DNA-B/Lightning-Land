 #ifndef _DATA_INIT_H
 #define _DATA_INIT_H

struct Data {
	char name[20];
	int idx;
	int price;
	int min_price;
	int is_selled;
	int is_trading;
	pid_t cur_ppid;
};

struct Data* data_init();

 #endif
