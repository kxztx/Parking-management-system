#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>

typedef struct Port//��λ��Ϣ�ṹ��
{
	int status;//״̬��1���г���0���޳� 
	char no[20];//���ƺ�
    clock_t start;//ͣ��ʱ��
	int price;//�շѵ���
}port;

typedef struct Charge//�շѽṹ��
{
	char no[20];//���ƺ�
    clock_t start;//ͣ��ʱ��
	clock_t ed;//ȡ��ʱ��
	int price;//�շѵ���
	double sum;//�շ��ܶ�
}charge;

port pt[20];//��λ���飬Ĭ��20����λ
charge cg[100];//�շѼ�¼���飬Ĭ������100��ͣȡ��
int m = 0;//�շѼ�¼��Ŀ
int smallPrice = 5;//С������
int bigPrice = 7;//�󳵵���


void readfile();//���ļ�����
void runmain();//�˵�
void manage();//����λ
void putcar();//ͣ��
void takecar();//ȡ��
void search();//��ѯ
void search_no();//��ѯ������Ϣ
void search_pt();//��ѯ��λ��Ϣ
void savefile();//��������
void quit();//�˳�ϵͳ
void check();//��֤���� 


int main() 
{ 
	    printf("*******************************************************************************\n");
		printf("**                                                                           **\n");
		printf("**                   ---��ӭʹ���Ͼ��ʵ��ѧ����ϵͳ---                      **\n");
		printf("**                                                        V 5.0              **\n");
		printf("*******************************************************************************\n");

        printf("\t                   ������ָ�"); 
        check();
        return 0;
}

//��֤����
void check() 
{  
	char pass[]="admin"; //���� 
	char str[10]={0},ch;  
	int i=0,n=strlen(pass); 
	while(n--)  
	{   
		ch=getch();  
		if(ch!='\n')   
		{    
			putchar('*');    
			str[i++]=ch;    
		}
	}
   getchar();   
   str[strlen(pass)]='\0';  
   if(strcmp(str,pass)==0)  
   {    
	runmain();   
   }  
   else  
   {   
	printf("\n                 ����������������룺");   
	check();   
   }  
}

//���ļ�����
void readfile()
{
	int i=0;
	FILE *fp;//�ļ�ָ��
	//����λ��Ϣ
	if((fp=fopen("port.txt","r"))==NULL)//���ļ���������û�������ļ����½�һ�������ļ�
	{
	    fp=fopen("port.txt","w");
		fclose(fp);
		//��ʼ��ȫ����λΪ��
		for( i = 0; i < 20; i++ )
		{
			pt[i].status = 0;
		}
	}
	else
	{
		for( i = 0; i < 20; i++ )//�������
		{
			fscanf(fp,"%d%s%d%d", &pt[i].status, pt[i].no, &pt[i].start, &pt[i].price);
		}
		fclose(fp);//�ر��ļ�
	}
	//���շ���Ϣ
	if((fp=fopen("charge.txt","r"))==NULL)//���ļ���������û�������ļ����½�һ�������ļ�
	{
		fp=fopen("charge.txt","w");
		fclose(fp);
		m = 0;
	}
	else
	{
		fscanf(fp,"%d",&m);//�ȶ���Ŀ
		for( i = 0; i < m; i++ )//�������
		{
			fscanf(fp,"%s%d%d%d%lf", cg[i].no, &cg[i].start, &cg[i].ed, &cg[i].price, &cg[i].sum);
		}
		fclose(fp);//�ر��ļ�
	}
}

//�˵�
void runmain()
{
	int i;

	while(1)
	{
		printf("*******************************************************************************\n");
		printf("**                                                                           **\n");
		printf("**                   ---��ӭʹ���Ͼ��ʵ��ѧ����ϵͳ---                      **\n");
		printf("**                                                        V 5.0              **\n");
		printf("*******************************************************************************\n");

		printf("                        1.����λ��Ϣ\n\n");
		printf("                        2.ͣ��\n\n");
		printf("                        3.ȡ��\n\n");
		printf("                        4.��ѯ\n\n");
		printf("                        0.�������ݲ��˳�ϵͳ\n\n");

		printf("��ѡ�������Ӧ�ò˵��");
		scanf("%d",&i);
		while(i<0||i>4)	//��֤����		
		{
			printf("������ĺ���������������ȷ��ѡ����루0-4֮�䣩��");
			scanf("%d",&i);
		}
		switch(i)
		{
		case 1:
			manage();
			break;
		case 2:
			putcar();
			break;
		case 3:
			takecar();
			break;
		case 4:
			search();
			break;
		case 0:
			savefile();
			quit();
			break;
		}

	}

}

//����λ
void manage()
{
	int i, c;
	struct tm *local;//����ʱ��ṹ��
	char str[80];//����ʱ���ַ���

	while(1)
	{
		printf("\n                    **************************************\n");
		printf("                    *                                    *\n");
		printf("                    *              ����λ              *\n");
		printf("                    *                                    *\n");
		printf("                    **************************************\n\n");

		printf("1.�鿴���г�λ״̬\n");
		printf("0.����\n");
		printf("��ѡ��");

		scanf("%d",&c);
		while(c<0||c>1)	//��֤����		
		{
			printf("������ĺ���������������ȷ��ѡ����루0-1֮�䣩��");
			scanf("%d",&c);
		}
		switch(c)
		{
		case 1:
			for( i = 0; i < 20; i++ )
			{
				if( pt[i].status == 1 )//�г�
				{
					local = localtime(&pt[i].start);//��ͣ��ʱ��ת��Ϊ����ʱ��
					strftime(str, 80, "%Y��%m��%d��%Hʱ%M��%S��", local);//������ʱ��ת��Ϊ�ַ���
					printf("��λ %2d �� ��ͣ�� ���ƺţ�%10s; ͣ��ʱ�䣺%s���շѵ��ۣ�%dԪ/Сʱ��\n", i+1, pt[i].no, str, pt[i].price);
				}
				else//����
				{
					printf("��λ %2d �� ���С�\n", i+1);
				}
			}
			break;
		case 0:
			return;
			break;
		}
	}
}


//ͣ��
void putcar()
{
	int i;
	char no[20];//���ƺ�
	clock_t start;//ͣ��ʱ��
	int price;//�շѵ���
	struct tm *local;//����ʱ��ṹ��
	char str[80];//����ʱ���ַ���

	printf("\n                    **************************************\n");
	printf("                    *                                    *\n");
	printf("                    *                ͣ��                *\n");
	printf("                    *                                    *\n");
	printf("                    **************************************\n\n");

	printf("�����복�ƺţ�");
	scanf("%s", no);
	while(1)
	{
		printf("��ѡ���ͺţ�\n1.С��\n2.��\n");
		scanf("%d", &i);
		if( i == 1 )
		{
			price = smallPrice;
			break;
		}
		else if( i == 2 )
		{
			price = bigPrice;
			break;
		}
		else
		{
			printf("�������\n");
		}
	}
	start = time(NULL);//��ȡ��ǰʱ��
	
    //�����ճ�λ
	for( i = 0; i < 20; i++ )
	{
		if( pt[i].status == 0 )
		{
			break;
		}
	}
	if( i == 20 )//ѭ����β����ʾû�пճ�λ
	{
		printf("��Ǹ����λ������\n");
	}
	else
	{
		//ͣ���i����λ
		pt[i].status = 1;
		strcpy( pt[i].no, no );
		pt[i].start = start;
		pt[i].price = price;

		local = localtime(&pt[i].start);//��ͣ��ʱ��ת��Ϊ����ʱ��
		strftime(str, 80, "%Y��%m��%d��%Hʱ%M��%S��", local);//������ʱ��ת��Ϊ�ַ���
		printf("ͣ���ɹ���\n");
		printf("���ĳ�λ�ǵ� %d �ţ�ͣ��ʱ��Ϊ��%s���շ�Ϊ%dԪ/Сʱ��\n", i+1, str, price);
	}
}

//ȡ��
void takecar()
{
	int i;
	char no[20];//���ƺ�
	clock_t ed;//ȡ��ʱ��
	struct tm *local;//����ʱ��ṹ��
	char strS[80], strE[80];//����ʱ���ַ���
	double t;//ͣ��ʱ��

	printf("\n                    **************************************\n");
	printf("                    *                                    *\n");
	printf("                    *                ȡ��                *\n");
	printf("                    *                                    *\n");
	printf("                    **************************************\n\n");

	printf("�����복�ƺţ�");
	scanf("%s", no);
	ed = time(NULL);//��ȡ��ǰʱ��

	
	for( i = 0; i < 20; i++ )
	{
		if( strcmp(no, pt[i].no) == 0 )
		{
			break;
		}
	}
	if( i == 20 )//ѭ����β����ʾû�пճ�λ
	{
		printf("��Ǹ���ó��ƺŲ����ڣ�\n");
	}
	else
	{
		//ȡ��,����Ϣ�����շ�����
		pt[i].status = 0;
		strcpy( cg[m].no, pt[i].no );
		cg[m].start = pt[i].start;
		cg[m].ed = ed;
		cg[m].price = pt[i].price;
	    //�����շ��ܶ�
		t = (double)(ed - pt[i].start) / 3600;//ͣ��ʱ������λСʱ
		if( t - (int)t == 0 )//�պ���Сʱ
		{
			cg[m].sum = (double)((int)t * cg[m].price);
		}
		else if( t - (int)t < 0.5 )//����������Сʱ
		{
			cg[m].sum = (int)t * cg[m].price + 0.5 * cg[m].price;
		}
		else//����������Сʱ
		{
			cg[m].sum = (double)(((int)t + 1) * cg[m].price);
		}

		local = localtime(&pt[i].start);//��ʱ��ת��Ϊ����ʱ��
		strftime(strS, 80, "%Y��%m��%d��%Hʱ%M��%S��", local);
		local = localtime(&ed);
		strftime(strE, 80, "%Y��%m��%d��%Hʱ%M��%S��", local);
		printf("ȡ���ɹ������ĳ�λ�ǵ� %d �ţ�ͣ��ʱ��Ϊ��%s��ȡ��ʱ��Ϊ��%s��ͣ��%.1lfСʱ���շѹ�%.1lfԪ��\n", i+1, strS, strE, t, cg[m].sum);
	    m++;//��¼��һ
	}
}

//��ѯ
void search()
{
	int i;

	while(1)
	{
		printf("\n                    **************************************\n");
		printf("                    *                                    *\n");
		printf("                    *              ����λ              *\n");
		printf("                    *                                    *\n");
		printf("                    **************************************\n\n");

		printf("1.���ݳ��ƺŲ�ѯ\n");
		printf("2.��ѯ��λ���\n");
		printf("0.����\n");
		printf("��ѡ��");

		scanf("%d",&i);
		while(i<0||i>2)		//��֤����	
		{
			printf("������ĺ���������������ȷ��ѡ����루0-2֮�䣩��");
			scanf("%d",&i);
		}
		switch(i)
		{
		case 1:
			search_no();
			break;
		case 2:
			search_pt();
			break;
		case 0:
			return;
			break;
		}
	}
}

//��ѯ������Ϣ
void search_no()
{
	char no[20];
	int i;
	struct tm *local;//����ʱ��ṹ��
	char str[80];//����ʱ���ַ���

	printf("�����복�ƺţ�");
	scanf("%s", no);

	//�����ó���
	for( i = 0; i < 20; i++ )
	{
		if( strcmp(no, pt[i].no) == 0 )
		{
			break;
		}
	}
	if( i == 20 )
	{
		printf("��Ǹ���ó��ƺŲ����ڣ�\n");
	}
	else
	{
		local = localtime(&pt[i].start);//��ʱ��ת��Ϊ����ʱ��
		strftime(str, 80, "%Y��%m��%d��%Hʱ%M��%S��", local);//������ʱ��ת��Ϊ�ַ���

		printf("�ó�ͣ���ڵ� %d �ų�λ��ͣ��ʱ��Ϊ%s���շѱ�׼Ϊ%dԪ/Сʱ.\n", i+1, str, pt[i].price);
	}
}

//��ѯ��λ��Ϣ
void search_pt()
{
	int id;
	struct tm *local;//����ʱ��ṹ��
	char str[80];//����ʱ���ַ���

	while(1)
	{
		printf("�����복λ�ţ�1-20����");
		scanf("%d", &id);
		if( id >=1 && id <= 20 )
		{
			break;
		}
		else
		{
			printf("��������\n");
		}
	}

	id--;//�����д�0��ʼ
	if( pt[id].status == 1 )//�г�
	{
		local = localtime(&pt[id].start);//��ͣ��ʱ��ת��Ϊ����ʱ��
		strftime(str, 80, "%Y��%m��%d��%Hʱ%M��%S��", local);//������ʱ��ת��Ϊ�ַ���
		printf("��λ %2d �� ��ͣ�� ���ƺţ�%10s; ͣ��ʱ�䣺%s���շѵ��ۣ�%dԪ/Сʱ��\n", id+1, pt[id].no, str, pt[id].price);
	}
	else//����
	{
		printf("��λ %2d �� ���С�\n", id+1);
	}
}

//��������
void savefile()
{
	int i;
	FILE *fp;//�ļ�ָ��

    //�泵λ��Ϣ
	fp=fopen("port.txt","w");
	for( i = 0; i < 20; i++ )//�������
	{
		fprintf(fp,"%d %s %d %d\n", pt[i].status, pt[i].no, pt[i].start, pt[i].price);
	}
	fclose(fp);//�ر��ļ�

    //���շ���Ϣ
	fp=fopen("charge.txt","w");
	fprintf(fp,"%d\n",m);//�ȶ���Ŀ
	for( i = 0; i < m; i++ )//�������
	{
		fprintf(fp,"%s %d %d %d %lf\n", cg[i].no, cg[i].start, cg[i].ed, cg[i].price, cg[i].sum);
	}
	fclose(fp);//�ر��ļ�
}


//�˳�ϵͳ
void quit()
{
	printf("\n                    **************************************\n");
	printf("                    *       �����ѱ��棡ϵͳ�˳���       *\n");
	printf("                    **************************************\n\n");
	exit(0); 
}
