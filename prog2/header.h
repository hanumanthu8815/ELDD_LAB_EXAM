#define MAGIC_NUMBER 'z'

#define set_periodicity _IOW(MAGIC_NUMBER,1,int)
#define get_periodicity _IOR(MAGIC_NUMBER,2,int)