#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#define randomInt(x,y) (rand()%(y-x+1)+x)

typedef struct Lnode
{
    int data;
    int flag;//访问位
    int modify;//修改位
} LNode;
int block = 3;
int access[32]; //访问序列
int lost = 0,index=0;//没找到的页面数
LNode* nodes;//改进型Clock置换算法用到的数据结构

void generate()
{
	int maxLength, e, m, p;
	double t;
	printf("请输入要随机生成访问序列的长度\n");
	scanf("%d", &maxLength);
	printf("请输入页面数\n");
	scanf("%d", &e);
	printf("请输入工作集起始位置\n");
	scanf("%d", &p);
	printf("请输入工作集移动效率\n");
	scanf("%d", &m);
	printf("请输入0-1之间的t\n");
	scanf("%lf", &t);
	srand((unsigned)time(NULL));
	int iterNum = 0; 
	int index=0;
	for (int i = 0; i < maxLength;)
	{
		if (i + m >= maxLength)
			iterNum = maxLength - i;
		else
			iterNum = m;
		for (int j =0;j<iterNum;j++)
		{
			int temp=randomInt(p%32,(p+e)%32);
			access[index]=temp;
			printf("%d ",access[index]);
			index++;
		}
		
		double r=randomInt(0,100)/100.0;
		if(r<t)
			p=randomInt(0,32);
		else
			p++;
		i=i+iterNum;

	}
	printf("\n");
}
int isInNodes (int n)
{
    int i;
    
    for (i = 0; i < block; i++)
    {
        if (nodes[i].data == access[n])
        {
            return 1;
        }
    }
    
    return 0;
}


void updated_Clock (int n)
{
    if (isInNodes (n))
    {
        printf ("----------------------以下页面已被调入,无置换----------------------\n");
    }
    
    else
        if (index == block)
        {
            lost++;
            int i = 0, tag = -1;
            
            while (1)
            {
                if ( (i / block) % 2 == 0)
                {
                    if (nodes[i % block].flag == 0 && nodes[i % block].modify == 0)
                    {
                        tag = i % block;
                        break;
                    }
                }
                
                if ( (i / block) % 2 == 1)
                {
                    if (nodes[i % block].flag == 0 && nodes[i % block].modify == 1)
                    {
                        tag = i % block;
                        break;
                    }
                    
                    else
                    {
                        nodes[i % block].flag = 0;
                    }
                }
                
                i++;
            }
            
            nodes[tag].data = access[n];
            nodes[tag].flag = 1;
            
            if (rand() % 10 < 4)
            {
                nodes[tag].modify = 1;
            }
            
            else
            {
                nodes[tag].modify = 0;
            }
        }
        
        else
        {
            nodes[index].data = access[n];
            nodes[index].flag = 1;
            
            if (rand() % 10 < 4)
            {
                nodes[index].modify = 1;
            }
            
            else
            {
                nodes[index].modify = 0;
            }
            
            index++;
        }
}
void test_Clock()
{
    int i = 0, j = 0;
    printf ("改进型Clock置换算法\n");
    nodes = (LNode*) malloc (block * sizeof (LNode));
    
    for (i = 0; i < block; i++)
    {
        nodes[i].data = -1;
        nodes[i].flag = -1;
        nodes[i].modify = -1;
    }
    
    for (i = 0; i < 32; i++)
    {
        updated_Clock (i);
        
        for (j = 0; j < block; j++)
        {
            printf ("%d ", nodes[j].data);
        }
        
        printf ("\n");
    }
    
    printf ("改进型Clock置换算法缺页率： %2f \n缺页数为： %d\n", lost / 32.0, lost);
    lost = 0;
    index = 0;
}
int main()
{
	generate();
    test_Clock();

}
