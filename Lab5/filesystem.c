#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include<string.h>
#include "filesystem.h"
#include "iosystem.h"
#include <string.h>
int init()
{
	printf("\nFILE INFO,file system will init.\n");
	init_ldisk();
	bitMap=(unsigned char*)calloc(512,sizeof(unsigned char));
	for(int i=0;i<512;i++)
	{bitMap[i]=0;} 
	bitMap[0]=0xff; 
	write_block(0,bitMap);
	for(int i=0;i<7;i++)
	{
		fileDescriptor[i]=(fileDescriptorItem*)calloc(sizeof(unsigned char)*512/sizeof(fileDescriptorItem),sizeof(fileDescriptorItem));
		write_block(i+1,(unsigned char*)fileDescriptor[i]);
	}
	printf("FILE INFO,file system init finished.\n");
	return 0;
}
int bitMapUpdate(int flag,int index)
{
	printf("\nFILE INFO,bitmap is updating.\n");
	read_block(0,bitMap);
	int temp=index%8;
	if(flag==1){
	switch(temp)
	{
		case 0:bitMap[index/8]=bitMap[index/8]|0x80;break;
		case 1:bitMap[index/8]=bitMap[index/8]|0x40;break;
		case 2:bitMap[index/8]=bitMap[index/8]|0x20;break; 
		case 3:bitMap[index/8]=bitMap[index/8]|0x10;break;
		case 4:bitMap[index/8]=bitMap[index/8]|0x08;break;
		case 5:bitMap[index/8]=bitMap[index/8]|0x04;break;
		case 6:bitMap[index/8]=bitMap[index/8]|0x02;break;
		case 7:bitMap[index/8]=bitMap[index/8]|0x01;break;
	}}
	else if(flag==0)
	{	
		
		switch(temp)
	{
		case 0:bitMap[index/8]=bitMap[index/8]&0x7f;break;
		case 1:bitMap[index/8]=bitMap[index/8]&0xbf;break;
		case 2:bitMap[index/8]=bitMap[index/8]&0xdf;break; 
		case 3:bitMap[index/8]=bitMap[index/8]&0xef;break;
		case 4:bitMap[index/8]=bitMap[index/8]&0xf7;break;
		case 5:bitMap[index/8]=bitMap[index/8]&0xfb;break;
		case 6:bitMap[index/8]=bitMap[index/8]&0xfd;break;
		case 7:bitMap[index/8]=bitMap[index/8]&0xfe;break;
	}
		
	}
	write_block(0,bitMap);
	printf("FILE INFO,bitmap updated.\n");
}

int findFreeBitMap()
{
	printf("\nFILE INFO,is finding free bitmap.\n");
	read_block(0,bitMap);
	for(int i=0;i<512;i++)
	{
		printf("%d",bitMap[i]);
		if(bitMap[i]!=0xff)
		{
			
			for(int j=0;j<8;j++)
			{
				int a=bitMap[i];
				if(a==0)
				{ 
					printf("\nFILE INFO,found free bitmap:%d.\n",i*8+j);
					return i*8+j;
				} 
			}
		}
	}
	printf("\nFILE ERROR,can't find free bitmap.\n");
	return -1;
}

int bitMapOutput()
{
	printf("\nFILE INFO,bitmap output:\n");
	for(int i=0;i<512;i++)
	{
		if(bitMap[i]==0)
		printf("00000000"); 
		else
		{
			for(int j=7;j>=0;j--)
			{
				int a=bitMap[i];
				printf("%d",(a>>j)&0x01);
			}
		}
		if((i+1)%16==0 && i!=0)
			printf("\n");
	}
	printf("\nFILE INFO,bitmap output finished.\n");
}

int fileDescriptorInsert(int fileSize,int blockList[3])
{
	printf("\nFILE INFO,file descriptor is inserting.\n");
	for(int i=0;i<7;i++)
	{
		read_block(i+1,(unsigned char*)fileDescriptor[i]);
	}
	for(int i=0;i<7;i++)
	{
		for(int j=0;j<sizeof(unsigned char)*512/sizeof(fileDescriptorItem);j++)
		{
			if (fileDescriptor[i][j].fileSize==0 && fileDescriptor[i][j].blockList[0]==0 && fileDescriptor[i][j].blockList[1]==0 && fileDescriptor[i][j].blockList[2]==0)
			{
				fileDescriptor[i][j].fileSize=fileSize;
				fileDescriptor[i][j].blockList[0]= blockList[0];
				fileDescriptor[i][j].blockList[1]= blockList[1];
				fileDescriptor[i][j].blockList[2]= blockList[2];
				for(int l=0;l<7;l++)
				{
					write_block(l+1,(unsigned char*)fileDescriptor[l]);
				}
				printf("FILE INFO,file descriptor inserted.\n");
				return i*sizeof(unsigned char)*512/sizeof(fileDescriptorItem)+j;
			}
		}
	}
	printf("FILE ERROR,can't insertfile descriptor.\n");
	return -1; 
}

int fileDescriptorUpdate(int index,int fileSize,int blockList[3])
{
	printf("\nFILE INFO,file descriptor is updating.\n");
	for(int i=0;i<7;i++)
	{
		read_block(i+1,(unsigned char*)fileDescriptor[i]);
	}
	fileDescriptor[index/(sizeof(unsigned char)*512/sizeof(fileDescriptorItem))][index%(sizeof(unsigned char)*512/sizeof(fileDescriptorItem))].fileSize=fileSize;
	fileDescriptor[index/(sizeof(unsigned char)*512/sizeof(fileDescriptorItem))][index%(sizeof(unsigned char)*512/sizeof(fileDescriptorItem))].blockList[0]= blockList[0];
	fileDescriptor[index/(sizeof(unsigned char)*512/sizeof(fileDescriptorItem))][index%(sizeof(unsigned char)*512/sizeof(fileDescriptorItem))].blockList[1]= blockList[1];
	fileDescriptor[index/(sizeof(unsigned char)*512/sizeof(fileDescriptorItem))][index%(sizeof(unsigned char)*512/sizeof(fileDescriptorItem))].blockList[2]= blockList[2];
	for(int l=0;l<7;l++)
	{
		write_block(l+1,(unsigned char*)fileDescriptor[l]);
	}
	printf("FILE INFO,file descriptor updated.\n");
	return 0;
}

int fileDescriptorDelete(int index)
{
	printf("\nFILE INFO,file descriptor is deleting.\n");
	for(int i=0;i<7;i++)
	{
		read_block(i+1,(unsigned char*)fileDescriptor[i]);
	}
	fileDescriptor[index/(sizeof(unsigned char)*512/sizeof(fileDescriptorItem))][index%(sizeof(unsigned char)*512/sizeof(fileDescriptorItem))].fileSize=0;
	fileDescriptor[index/(sizeof(unsigned char)*512/sizeof(fileDescriptorItem))][index%(sizeof(unsigned char)*512/sizeof(fileDescriptorItem))].blockList[0]= 0;
	fileDescriptor[index/(sizeof(unsigned char)*512/sizeof(fileDescriptorItem))][index%(sizeof(unsigned char)*512/sizeof(fileDescriptorItem))].blockList[1]= 0;
	fileDescriptor[index/(sizeof(unsigned char)*512/sizeof(fileDescriptorItem))][index%(sizeof(unsigned char)*512/sizeof(fileDescriptorItem))].blockList[2]= 0;
	for(int l=0;l<7;l++)
	{
		write_block(l+1,(unsigned char*)fileDescriptor[l]);
	}
	printf("FILE INFO,file descriptor deleted.\n");
	return 0;
}

int initDic()
{
	printf("FILE INFO,is initing dic.\n");
	dictionary=(dictionaryItem*)calloc(sizeof(unsigned char)*512/sizeof(dictionaryItem),sizeof(dictionaryItem)) ;		
	int index=findFreeBitMap();
	write_block(index,(unsigned char*)dictionary);
	bitMapUpdate(1,index);
	int blockList[3]={index};
	int descriptorIndex=fileDescriptorInsert(1,blockList);
	strncpy(dictionary[0].fileName,"Dictionary",strlen("Dictionary"));
	dictionary[0].fileDescriptorIndex=descriptorIndex;
	write_block(index,(unsigned char*)dictionary);
	printf("FILE INFO,inited dic.\n");
	return 0;
}

int readDic()
{
	for(int i=0;i<7;i++)
	{
		read_block(i+1,(unsigned char*)fileDescriptor[i]);
	}
	int i0=fileDescriptor[0][0].blockList[0];
	int i1=fileDescriptor[0][0].blockList[1];
	int i2=fileDescriptor[0][0].blockList[2];
	if(i0!=0)
	{
		read_block(i0,(unsigned char*)dictionary);
	}
	if(i1!=0)
	{
		read_block(i0,(unsigned char*)dictionary+512);
	}
	if(i2!=0)
	{
		read_block(i0,(unsigned char*)dictionary+512);
	}
	return 0;	
}

int create(unsigned char *filename)
{
	printf("\nFILE INFO,is creating file,filename is %s\n",filename);
	int flag=0;
	read_block(0,bitMap);
	for(int i=1;i<512;i++)
	{
		if(bitMap[i]!=0)
		{
			flag=1;
			break;
		}
	} 
	if(flag==0)
	{
		initDic();
	}
	/*Check dic is full or not*/
	readDic();
	CheckDic();
	 int FileDescriptorNum,MenuItemNum,DiskNum;
    MenuItemNum = SearchMenuItem();
    strcpy(menuitem[MenuItemNum].FileName,filename);
    FileDescriptorNum = SearchFileDescriptor();
    menuitem[MenuItemNum].FileDescriptorNum = FileDescriptorNum;
    DiskNum = SearchBitMap();
    filedescriptor[FileDescriptorNum].DiskNum[0] = DiskNum;
    filedescriptor[FileDescriptorNum].IsFree = 'N';
    ChangeBitMap(DiskNum,'Y');
	return 0;
}
int destroy(char* filename)
{
	int temp = 1;
	int pos = 0;
	for (int i = 0; i < B_MAX; i++)
	{
		if (ldisk[0][0][i].flag == '1')
		{
			if (strcmp(ldisk[0][0][i].data, filename)== 0)
			{
				pos = i;
				break;
			}
		}
	}
	if (pos == 0)
	{
		cout << "FILE ERROR,can't delete.\n" << endl;
	}
	else {
		ldisk[0][0][pos].flag = '0';
		ldisk[0][0][pos].data[0] = '\0';
		ldisk[0][0][pos].next = NULL;
		cout << "FILE INFO,deleted." << endl;
	}
	return 0;
}
int open(char* filename)
{
	int pos = 0;
	for (int i = 0; i < B_MAX; i++)
	{
		if (ldisk[0][0][i].flag == '1')
		{
			if (strcmp(ldisk[0][0][i].data, filename)==0)
			{
				pos = i;
				break;
			}
		}
	}
	if (pos == 0)
	{
		cout << "FILE ERROR,can't open.\n" << endl;
	}
	else {
		cout << "FILE INFO,opened." << endl;

		for (int j = 0; j < C_MAX; j++)
		{
			if (item[j].index == 0)
			{
				item[j].index = 19706500 + j;
				item[j].pos = 0;
				item[j].data = ldisk[0][0][pos].next;
				cout << "index: " << item[j].index << endl;
				return item[j].index;
			}

		}
	}
	return 0;
}
int close(int index)
{
	for (int j = 0; j < C_MAX; j++)
	{
		if (item[j].index == index)
		{
			item[j].index == 0;
			item[j].pos = 0;
			item[j].data = NULL;
		}

	}
	cout << "FILE INFO,closed." << endl;
	return 0;
}
int read(int index, string mem_area, int count)
{
	for (int j = 0; j < C_MAX; j++)
	{
		if (item[j].index == index)
		{
			for (int i = 0; i < count; i++)
			{
			    mem_area[i] = item[j].data->data[i + item[j].pos];
				cout << mem_area[i];
			}
			cout << "FILE INFO,read." << endl;
			return 0;
		}
	}
	cout << "FILE ERROR,can't read.'" << endl;
	return 0;
}
int write(int index, string mem_area, int count)
{
	for (int j = 0; j < C_MAX; j++)
	{
		if (item[j].index == index)
		{
			myblock* p = item[j].data;
			for (int i = 0; i < count; i++)
			{
				if (i+1 % 512 == 0)
				{
					p->next = NULL;
					p = p->next;
				}
				p->data[item[j].pos] = mem_area[i];
				item[j].pos++;
			}
			cout << "FILE INFO,wirtten." << endl;
			return 0;
		}
	}
	cout << "FILE ERROR,can't write." << endl;
	return 0;
}
//列表显示所有文件及其长度 
void directory()
{
	printf("以下是所有文件的相关信息(文件目录):\n");
	int number = 1;
	for(int i = 0;i < L;i++)
	{
		if(dir[i].des != -1)
		{
			printf("%d 文件名: %s 文件长度: %d\n",number,dir[i].filename,loc[dir[i].des].fileLength);
			number++;
		}
	}
}

//输入文件名
void input_filename()
{
	printf("请输入文件名：\n");
	scanf("%s",file_name);
}

//测试文件菜单
void menu()
{
	int choose;
	printf("*************************************\n");
	printf("请输入相应的数字来选择对应的功能:\n");
	printf("1.创建文件\n");
	printf("2.读取文件\n");
	printf("3.写入文件\n");
	printf("4.删除文件\n");
	printf("5.查看文件目录\n");
	printf("0.退出\n");
	printf("*************************************\n");
	scanf("%d",&choose);
	while(choose)
	{
		switch(choose)
		{
			case 1: input_filename(); create(file_name); break;
			case 2: input_filename(); read_file(file_name); break;
			case 3: input_filename(); write_file(file_name) ; break;
			case 4: input_filename(); destroy(file_name); break;
			case 5: directory(); break;
			case 0: exit(0);
		}
		printf("*************************************\n");
		printf("请输入相应的数字来选择对应的功能:\n");
		printf("1.创建文件\n");
		printf("2.读取文件\n");
		printf("3.写入文件\n");
		printf("4.删除文件\n");
		printf("5.查看文件目录\n");
		printf("0.退出\n");
		printf("*************************************\n");
		scanf("%d",&choose);
	} 
} 
//int main()
//{
//	init();
//	bitMapOutput();
//	create("5555"); 
//	bitMapOutput();
//}

