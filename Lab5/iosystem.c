#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include<string.h>
#include "iosystem.h"
int init_ldisk()
{
	for(int i=0;i<C;i++)
	{
		for(int j=0;j<H;j++)
		{
			for(int k=0;k<B;k++)
			{
				ldisk[i][j][k]=(unsigned char *)malloc(sizeof(unsigned char)*512);
			}
		}
	}
	printf("IO INFO,logic disk init successfuly.\n");
	return 0;
}
int read_block(int i,unsigned char *p)
{
	if (i >= C*H*B)
	{
		printf("IO ERROR,index out of range!\n");
		return -1;
	}
	int CylinderIndex=i/(H*B);
	int SectorIndex=i%B+1; 
	int HeadsIndex=(i/18)%2;
	memcpy(p,ldisk[CylinderIndex][HeadsIndex][SectorIndex-1],512);
	printf("IO INFO,read logic index is %d,physic index is %d,%d,%d,the content is %s.\n",i,CylinderIndex,HeadsIndex,SectorIndex,ldisk[CylinderIndex][HeadsIndex][SectorIndex-1]);
	return 0;
}
int write_block(int i,unsigned char *p)
{
	if (i >= C*H*B)
	{
		printf("IO ERROR,index out of range!\n");
		return -1;
	}
	int CylinderIndex=i/(H*B);
	int SectorIndex=i%B+1; 
	int HeadsIndex=(i/18)%2;
	memcpy(ldisk[CylinderIndex][HeadsIndex][SectorIndex-1],p,512);
	printf("IO INFO,write logic index is %d,physic index is %d,%d,%d,the content is %s.\n",i,CylinderIndex,HeadsIndex,SectorIndex,p);
	return 0;
}

int backup_disk(FILE *filepath)
{
	if(filepath==NULL)
	{
		printf("IO ERROR,filepath open fail");
		return -1;
	}
	for(int i=0;i<C;i++)
	{
		for(int j=0;j<H;j++)
		{
			for(int k=0;k<B;k++)
			{
				fwrite(ldisk[i][j][k],sizeof(unsigned char),512,filepath); 
			}
		}
	}
	fclose(filepath);
	printf("IO INFO,backup successfuly.\n");
	return 0;
}
int restore_disk(FILE *filepath)
{
		if(filepath==NULL)
	{
		printf("IO ERROR,filepath open fail");
		return -1;
	}
	for(int i=0;i<C;i++)
	{
		for(int j=0;j<H;j++)
		{
			for(int k=0;k<B;k++)
			{
				fread(ldisk[i][j][k],sizeof(unsigned char),512,filepath);
			}
		}
	}
	fclose(filepath);
	printf("IO INFO,restore backup successfuly.\n");
	return 0;
}
//int main()
//{
////	init_ldisk();
////	write_block(2581,"55555555555555555");
////	FILE *fp=fopen("backupFile.bin","wb");
////	backup_disk(fp);
//	init_ldisk();
//	FILE *fp=fopen("backupFile.bin","rb");
//	restore_disk(fp);
//	char *p=(char*)malloc(sizeof(unsigned char)*512);
//	read_block(2581,p);
//	printf("%s\n",p);
//	printf("\n");
//	system("pause");
//	return 0;
//	
//}
