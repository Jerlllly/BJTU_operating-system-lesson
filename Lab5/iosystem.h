#define C 80
#define H 2
#define B 18
unsigned char *ldisk[C][H][B];
int init_ldisk();
int read_block(int i,unsigned char *p);
int write_block(int i,unsigned char *p);
int backup_disk(FILE *filepath);
int restore_disk(FILE *filepath);
