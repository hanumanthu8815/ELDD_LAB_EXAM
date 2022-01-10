#define MAGIC_NUMBER 'O'


#define WR_FUN _IOW(MAGIC_NUMBER, 8, int)
#define RD_FUN _IOR(MAGIC_NUMBER, 9, int)


#define GETSTATS _IOW(MAGIC_NUMBER, 11, int)