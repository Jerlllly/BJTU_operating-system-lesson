#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#define randomInt(x,y) (rand()%(y-x+1)+x)

typedef struct Lnode
{
    int data;
    int flag;//����λ
    int modify;//�޸�λ
} LNode;
int block = 3;
int access[32]; //��������
int lost = 0,index=0;//û�ҵ���ҳ����
LNode* nodes;//�Ľ���Clock�û��㷨�õ������ݽṹ

void generate()
{
	int maxLength, e, m, p;
	double t;
	printf("������Ҫ������ɷ������еĳ���\n");
	scanf("%d", &maxLength);
	printf("������ҳ����\n");
	scanf("%d", &e);
	printf("�����빤������ʼλ��\n");
	scanf("%d", &p);
	printf("�����빤�����ƶ�Ч��\n");
	scanf("%d", &m);
	printf("������0-1֮���t\n");
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
        printf ("----------------------����ҳ���ѱ�����,���û�----------------------\n");
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
    printf ("�Ľ���Clock�û��㷨\n");
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
    
    printf ("�Ľ���Clock�û��㷨ȱҳ�ʣ� %2f \nȱҳ��Ϊ�� %d\n", lost / 32.0, lost);
    lost = 0;
    index = 0;
}
int main()
{
	generate();
    test_Clock();

}
