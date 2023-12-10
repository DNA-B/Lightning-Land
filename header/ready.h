 #ifndef _READY_H
 #define _READY_H
 
int item_idx;
char buf[BUFSIZ];

void send_msg(int nsd, char* msg);
char* receive_msg(int nsd);
void select_item(int nsd);
int re_trade(int nsd);
void trade_or_exit(int nsd);

#endif
