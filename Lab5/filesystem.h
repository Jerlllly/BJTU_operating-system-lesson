#define k 8
typedef struct
{
	int fileSize;
	int blockList[3];
}fileDescriptorItem;

typedef struct
{
	unsigned char fileName[28];
	int fileDescriptorIndex;
}dictionaryItem;

fileDescriptorItem *fileDescriptor[7];
unsigned char *bitMap;
dictionaryItem *dictionary;
int init();
int bitMapUpdate(int flag,int index); 
int findFreeBitMap(); 
int bitMapOutput();
int fileDescriptorInsert(int fileSize,int blockList[3]);
int fileDescriptorUpdate(int index,int fileSize,int blockList[3]);
int fileDescriptorDelete(int index);
int create(unsigned char* filename); 
int initDic();
//int destroy(filename);
//int open(filename);
//int close(index);
//int read(index, mem_area, count);
//int write(index, mem_area, count);
//int lseek(index, pos);
//int directory;
