#ifndef _SEM_H
#define _SEM_H

int initsem(key_t semkey);
int semlock(int semid);
int semunlock(int semid);

#endif
