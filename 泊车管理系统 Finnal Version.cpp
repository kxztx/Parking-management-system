#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>

typedef struct Port//车位信息结构体
{
	int status;//状态，1是有车，0是无车 
	char no[20];//车牌号
    clock_t start;//停车时间
	int price;//收费单价
}port;

typedef struct Charge//收费结构体
{
	char no[20];//车牌号
    clock_t start;//停车时间
	clock_t ed;//取车时间
	int price;//收费单价
	double sum;//收费总额
}charge;

port pt[20];//车位数组，默认20个车位
charge cg[100];//收费记录数组，默认上限100次停取车
int m = 0;//收费记录数目
int smallPrice = 5;//小车单价
int bigPrice = 7;//大车单价


void readfile();//读文件数据
void runmain();//菜单
void manage();//管理车位
void putcar();//停车
void takecar();//取车
void search();//查询
void search_no();//查询车牌信息
void search_pt();//查询车位信息
void savefile();//保存数据
void quit();//退出系统
void check();//验证密码 


int main() 
{ 
	    printf("*******************************************************************************\n");
		printf("**                                                                           **\n");
		printf("**                   ---欢迎使用南京邮电大学泊车系统---                      **\n");
		printf("**                                                        V 5.0              **\n");
		printf("*******************************************************************************\n");

        printf("\t                   请输入指令："); 
        check();
        return 0;
}

//验证密码
void check() 
{  
	char pass[]="admin"; //密码 
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
	printf("\n                 密码错误，请重新输入：");   
	check();   
   }  
}

//读文件数据
void readfile()
{
	int i=0;
	FILE *fp;//文件指针
	//读车位信息
	if((fp=fopen("port.txt","r"))==NULL)//打开文件，读，若没有数据文件，新建一个数据文件
	{
	    fp=fopen("port.txt","w");
		fclose(fp);
		//初始化全部车位为空
		for( i = 0; i < 20; i++ )
		{
			pt[i].status = 0;
		}
	}
	else
	{
		for( i = 0; i < 20; i++ )//逐个读出
		{
			fscanf(fp,"%d%s%d%d", &pt[i].status, pt[i].no, &pt[i].start, &pt[i].price);
		}
		fclose(fp);//关闭文件
	}
	//读收费信息
	if((fp=fopen("charge.txt","r"))==NULL)//打开文件，读，若没有数据文件，新建一个数据文件
	{
		fp=fopen("charge.txt","w");
		fclose(fp);
		m = 0;
	}
	else
	{
		fscanf(fp,"%d",&m);//先读数目
		for( i = 0; i < m; i++ )//逐个读出
		{
			fscanf(fp,"%s%d%d%d%lf", cg[i].no, &cg[i].start, &cg[i].ed, &cg[i].price, &cg[i].sum);
		}
		fclose(fp);//关闭文件
	}
}

//菜单
void runmain()
{
	int i;

	while(1)
	{
		printf("*******************************************************************************\n");
		printf("**                                                                           **\n");
		printf("**                   ---欢迎使用南京邮电大学泊车系统---                      **\n");
		printf("**                                                        V 5.0              **\n");
		printf("*******************************************************************************\n");

		printf("                        1.管理车位信息\n\n");
		printf("                        2.停车\n\n");
		printf("                        3.取车\n\n");
		printf("                        4.查询\n\n");
		printf("                        0.保存数据并退出系统\n\n");

		printf("请选择并输入对应得菜单项：");
		scanf("%d",&i);
		while(i<0||i>4)	//验证输入		
		{
			printf("您输入的号码有误，请输入正确的选项号码（0-4之间）：");
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

//管理车位
void manage()
{
	int i, c;
	struct tm *local;//日历时间结构体
	char str[80];//储存时间字符串

	while(1)
	{
		printf("\n                    **************************************\n");
		printf("                    *                                    *\n");
		printf("                    *              管理车位              *\n");
		printf("                    *                                    *\n");
		printf("                    **************************************\n\n");

		printf("1.查看所有车位状态\n");
		printf("0.返回\n");
		printf("请选择：");

		scanf("%d",&c);
		while(c<0||c>1)	//验证输入		
		{
			printf("您输入的号码有误，请输入正确的选项号码（0-1之间）：");
			scanf("%d",&c);
		}
		switch(c)
		{
		case 1:
			for( i = 0; i < 20; i++ )
			{
				if( pt[i].status == 1 )//有车
				{
					local = localtime(&pt[i].start);//将停车时间转化为日历时间
					strftime(str, 80, "%Y年%m月%d日%H时%M分%S秒", local);//将日历时间转化为字符串
					printf("车位 %2d ： 已停； 车牌号：%10s; 停车时间：%s；收费单价：%d元/小时。\n", i+1, pt[i].no, str, pt[i].price);
				}
				else//空闲
				{
					printf("车位 %2d ： 空闲。\n", i+1);
				}
			}
			break;
		case 0:
			return;
			break;
		}
	}
}


//停车
void putcar()
{
	int i;
	char no[20];//车牌号
	clock_t start;//停车时间
	int price;//收费单价
	struct tm *local;//日历时间结构体
	char str[80];//储存时间字符串

	printf("\n                    **************************************\n");
	printf("                    *                                    *\n");
	printf("                    *                停车                *\n");
	printf("                    *                                    *\n");
	printf("                    **************************************\n\n");

	printf("请输入车牌号：");
	scanf("%s", no);
	while(1)
	{
		printf("请选择车型号：\n1.小车\n2.大车\n");
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
			printf("输入错误！\n");
		}
	}
	start = time(NULL);//获取当前时间
	
    //搜索空车位
	for( i = 0; i < 20; i++ )
	{
		if( pt[i].status == 0 )
		{
			break;
		}
	}
	if( i == 20 )//循环到尾，表示没有空车位
	{
		printf("抱歉！车位已满！\n");
	}
	else
	{
		//停入第i个车位
		pt[i].status = 1;
		strcpy( pt[i].no, no );
		pt[i].start = start;
		pt[i].price = price;

		local = localtime(&pt[i].start);//将停车时间转化为日历时间
		strftime(str, 80, "%Y年%m月%d日%H时%M分%S秒", local);//将日历时间转化为字符串
		printf("停车成功！\n");
		printf("您的车位是第 %d 号，停车时间为：%s，收费为%d元/小时。\n", i+1, str, price);
	}
}

//取车
void takecar()
{
	int i;
	char no[20];//车牌号
	clock_t ed;//取车时间
	struct tm *local;//日历时间结构体
	char strS[80], strE[80];//储存时间字符串
	double t;//停车时长

	printf("\n                    **************************************\n");
	printf("                    *                                    *\n");
	printf("                    *                取车                *\n");
	printf("                    *                                    *\n");
	printf("                    **************************************\n\n");

	printf("请输入车牌号：");
	scanf("%s", no);
	ed = time(NULL);//获取当前时间

	
	for( i = 0; i < 20; i++ )
	{
		if( strcmp(no, pt[i].no) == 0 )
		{
			break;
		}
	}
	if( i == 20 )//循环到尾，表示没有空车位
	{
		printf("抱歉！该车牌号不存在！\n");
	}
	else
	{
		//取车,将信息填入收费数组
		pt[i].status = 0;
		strcpy( cg[m].no, pt[i].no );
		cg[m].start = pt[i].start;
		cg[m].ed = ed;
		cg[m].price = pt[i].price;
	    //计算收费总额
		t = (double)(ed - pt[i].start) / 3600;//停车时长，单位小时
		if( t - (int)t == 0 )//刚好满小时
		{
			cg[m].sum = (double)((int)t * cg[m].price);
		}
		else if( t - (int)t < 0.5 )//超出不满半小时
		{
			cg[m].sum = (int)t * cg[m].price + 0.5 * cg[m].price;
		}
		else//超出不满半小时
		{
			cg[m].sum = (double)(((int)t + 1) * cg[m].price);
		}

		local = localtime(&pt[i].start);//将时间转化为日历时间
		strftime(strS, 80, "%Y年%m月%d日%H时%M分%S秒", local);
		local = localtime(&ed);
		strftime(strE, 80, "%Y年%m月%d日%H时%M分%S秒", local);
		printf("取车成功！您的车位是第 %d 号，停车时间为：%s，取车时间为：%s，停车%.1lf小时，收费共%.1lf元。\n", i+1, strS, strE, t, cg[m].sum);
	    m++;//记录加一
	}
}

//查询
void search()
{
	int i;

	while(1)
	{
		printf("\n                    **************************************\n");
		printf("                    *                                    *\n");
		printf("                    *              管理车位              *\n");
		printf("                    *                                    *\n");
		printf("                    **************************************\n\n");

		printf("1.根据车牌号查询\n");
		printf("2.查询车位情况\n");
		printf("0.返回\n");
		printf("请选择：");

		scanf("%d",&i);
		while(i<0||i>2)		//验证输入	
		{
			printf("您输入的号码有误，请输入正确的选项号码（0-2之间）：");
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

//查询车牌信息
void search_no()
{
	char no[20];
	int i;
	struct tm *local;//日历时间结构体
	char str[80];//储存时间字符串

	printf("请输入车牌号：");
	scanf("%s", no);

	//搜索该车牌
	for( i = 0; i < 20; i++ )
	{
		if( strcmp(no, pt[i].no) == 0 )
		{
			break;
		}
	}
	if( i == 20 )
	{
		printf("抱歉！该车牌号不存在！\n");
	}
	else
	{
		local = localtime(&pt[i].start);//将时间转化为日历时间
		strftime(str, 80, "%Y年%m月%d日%H时%M分%S秒", local);//将日历时间转化为字符串

		printf("该车停放在第 %d 号车位，停车时间为%s，收费标准为%d元/小时.\n", i+1, str, pt[i].price);
	}
}

//查询车位信息
void search_pt()
{
	int id;
	struct tm *local;//日历时间结构体
	char str[80];//储存时间字符串

	while(1)
	{
		printf("请输入车位号（1-20）：");
		scanf("%d", &id);
		if( id >=1 && id <= 20 )
		{
			break;
		}
		else
		{
			printf("输入有误！\n");
		}
	}

	id--;//数组中从0开始
	if( pt[id].status == 1 )//有车
	{
		local = localtime(&pt[id].start);//将停车时间转化为日历时间
		strftime(str, 80, "%Y年%m月%d日%H时%M分%S秒", local);//将日历时间转化为字符串
		printf("车位 %2d ： 已停； 车牌号：%10s; 停车时间：%s；收费单价：%d元/小时。\n", id+1, pt[id].no, str, pt[id].price);
	}
	else//空闲
	{
		printf("车位 %2d ： 空闲。\n", id+1);
	}
}

//保存数据
void savefile()
{
	int i;
	FILE *fp;//文件指针

    //存车位信息
	fp=fopen("port.txt","w");
	for( i = 0; i < 20; i++ )//逐个保存
	{
		fprintf(fp,"%d %s %d %d\n", pt[i].status, pt[i].no, pt[i].start, pt[i].price);
	}
	fclose(fp);//关闭文件

    //存收费信息
	fp=fopen("charge.txt","w");
	fprintf(fp,"%d\n",m);//先读数目
	for( i = 0; i < m; i++ )//逐个保存
	{
		fprintf(fp,"%s %d %d %d %lf\n", cg[i].no, cg[i].start, cg[i].ed, cg[i].price, cg[i].sum);
	}
	fclose(fp);//关闭文件
}


//退出系统
void quit()
{
	printf("\n                    **************************************\n");
	printf("                    *       数据已保存！系统退出！       *\n");
	printf("                    **************************************\n\n");
	exit(0); 
}
