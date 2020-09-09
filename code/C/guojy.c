#define N 100
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct
{
	int year;
	int month;
	int day;
}Date;
typedef struct user_info{
    char name[10];
    float time;//所用时间
    int clicks;//点击次数
	int level;
	Date date;  //登录日期
}User;
void sort_clicks(User U[],int n) ;// 按点击次数排序，点击次数少的排在前面
void sort_time(User U[],int n) ;  //按完成时间排序，时间短的排在前面
void output_rank(FILE *filename,User temp[],int n,char name[]);  //将排序后的记录绩写入文件
void get_user_score(User U[],int n);  //将当前用户的成绩写入文件
int search(User R[],int n, char name[]);
int main()
 {
    User temp[N],R[N];  //temp为临时数组；R为当前用户的历史数据，按游戏级别存放，用于画出用户的成绩折线图
    int i,j,k,rec_num,level;//user_num为用户数，rec_num为文件中的记录条数
	char name[10];
	FILE *read,*write1,*write2,*last;  //按分数排序的文件，按时间排序的文件

///////	gcvt(t,4,name);
	


//从文件中读取当前用户的信息
	last = fopen("last_user.txt", "r+");
	if (last == NULL)
		{
			printf("file not found!\n");
			return 0;
		}

//先从文件last_uuser.txt中读出用户当前所处的游戏级别和用户名称，然后对该级别的数据进行排序，完成排行榜
	fscanf(last, "%s\t%f\t%d\t%d\n", temp[0].name, &temp[0].time, &temp[0].clicks,&temp[0].level);
    printf("%s\t%.2f\t%d\t%d\n", temp[0].name, temp[0].time, temp[0].clicks,temp[0].level);
    level=temp[0].level;    //取出当前游戏者的游戏级别，赋给level
    strcpy(name,temp[0].name);  //取出当前用户的名字，便于对该用户的历史成绩进行评价
	printf("level=%d\n",level);
    read = fopen("rank.txt", "r+");
    if (read == NULL)
	{
		printf("file not found!\n");
        return 0;
    }


	i=0;
	j=0;
	while (!feof(read))
	{
		fscanf(read, "%s\t%f\t%d\t%d\n", temp[i].name, &temp[i].time, &temp[i].clicks,&temp[i].level); 
		printf("%s\t%.2f\t%d\t%d\n", temp[i].name, temp[i].time, temp[i].clicks,temp[i].level);
    	if(strcmp(temp[i].name,name)==0&&temp[i].level==level) R[j++]=temp[i];    //将当前用户、当前级别的历史数据存入R
		if(temp[i].level==level)     //temp中只存贮游戏级别等于level的数据
			i++;
	
    }
    fclose(read);
	rec_num=i;  //文件中共用rec_num条记录
	get_user_score(R,j);   //将当前用户该级别的成绩写入文件user_score.txt
	write1 = fopen("rank_clicks.txt", "w");   //write1用于存贮按点击次数排序的文件ranking_clicks
	if(write1==NULL)
	{
		printf("cannot create file!\n");
        return 0;
	}
	write2 = fopen("rank_time.txt", "w");  //write2用于存贮按时间排序的文件ranking_time
	if(write2==NULL)
	{
		printf("cannot create file!\n");
        return 0;
	}

//读取文件结束 
    sort_clicks(temp,rec_num);  //对所有用户按点击次数进行排序
//打印排序后的数据
	printf("after sort by clicks:\n");
	for(k=0;k<rec_num;k++)
       printf("%s\t%.2f\t%d\t%d\n", temp[k].name, temp[k].time, temp[k].clicks,temp[k].level );

//将排序后的数据写入文件ranking_clicks.txt，一个用户只存贮一次
	output_rank(write1,temp,rec_num,name);

    sort_time(temp,rec_num);  //对所有用户按点击次数进行排序
//打印排序后的数据
	printf("after sort by time:\n");
	for(k=0;k<rec_num;k++)
       printf("%s\t%.2f\t%d\t%d\n", temp[k].name, temp[k].time, temp[k].clicks,temp[k].level ); 
//将排序后的数据写入文件ranking_time.txt，一个用户只存贮一次
    output_rank(write2,temp,rec_num,name);
	fclose(write1);
	fclose(write2);
    return 0;
}
void sort_clicks(User U[],int n)    //按点击次数从小到大排序，点击次数相同的，按时间从小到大排序
{
	int i,j;
	User temp;
	for(i=0;i<n-1;i++)
		for(j=0;j<n-1-i;j++)
			if(U[j].clicks>U[j+1].clicks||U[j].clicks==U[j+1].clicks&&U[j].time>U[j+1].time)
			{
			   temp=U[j];
			   U[j]=U[j+1];
			   U[j+1]=temp;
			}
}
void sort_time(User U[],int n)   //按游戏所用时间从小到大排序，时间相同的，按点击次数从小到大排序
{
	int i,j;
	User temp;
	for(i=0;i<n-1;i++)
		for(j=0;j<n-1-i;j++)
			if(U[j].time>U[j+1].time||U[j].time==U[j+1].time&&U[j].clicks>U[j+1].clicks)
			{
			   temp=U[j];
			   U[j]=U[j+1];
			   U[j+1]=temp;
			}
}
void output_rank(FILE *filename,User temp[],int n,char name[])   //将排序结果写入文件filename
{
	User R[N];
	int i,j,k,m,user_num,flag,no;//user_num为用户数，rec_num为文件中的记录条数
	int index;//下标 
	char res[31];
    char buff[4],Le[3],time[10]; // //buff存点击次数，Le存游戏级别
	R[0] = temp[0];
    user_num = 1;
	index=0;  
	flag=0;   //用于标当前用户是否出现在前三名，如果出现，排行榜只显示前三，否则，显示前三加当前用户，共4条记录
	for (k = 0; k < n; k++) 
	{
		if(strcmp(temp[k].name,name)==0) flag=1;
		for(j=0;j<k;j++)
			if (strcmp(temp[k].name, temp[j].name)==0)
				break;
		if(j>=k)
		{  //如果当前遍历的元素和前一个元素姓名不同，则写入R[index++]中，即同一个用户只写入一次
            R[index++] = temp[k];//存到R中   
            user_num++;
        }
		if(index>2) break;
	}
	if(flag==0)
	{
		no=search(temp,n,name);    //如果当前用户没进入前三，则查找其在文件中的排名，并将名次序号返回，其记录信息存入R[index]
		R[index++]=temp[no];
	}


    //printf("Number of users:=%d\n",user_num);
    
    for ( k = 0; k < index; ++k) 
	{
        itoa(R[k].clicks, buff, 10);   //将分数转化为10进制的ASCII码，4位，存入buff
		itoa(R[k].level,Le,10);    //将游戏等级转化为十进制字符串，存入Le
        //gcvt(R[k].time,10,time);    //char *gcvt(double v,int n,char *b)就是其一。其中b是存放转换后du的字符串zhi的空间首地址(指针)，n是转换后的字符串的长度，
		sprintf(time,"%.2f", R[k].time);   //将实数时间转化为保留两位小数的字符串
        //itoa(R[k].time,time,10);

		//if(k<3) itoa(k+1,Seq,10);
		//else itoa(i+1,Seq,10);
		//printf("len of time:%d\n",strlen(time));
	
        for (i = 0, j = 0, m = 0; i < 31; ++i)
		{
            if (i < strlen(R[k].name) && R[k].name[i] != '\0')
                res[i] = R[k].name[i];
            else if (i < 12)
                res[i] = '-';
            else if (i < strlen(time)+12 && time[i-12] != '\0')
                res[i] =time[i-12];
            else if (i < 20)
                res[i] = '-';
            else  if (i < strlen(buff)+20 && buff[i-20] != '\0')
                res[i] = buff[j++];
			else if(i<26)
                res[i] = '-';
			else if (i < strlen(Le)+26 && Le[i-26] != '\0') res[i]=Le[m++];
			else res[i]=0;
        }
		//printf("res: %s\n",res);
		if(k<3)
			fprintf(filename, "%d: %s\n",k+1,res);
		else 
			fprintf(filename, "%d: %s\n",no+1,res);
		//fprintf(write, "%s\t%s\t%d\n", R[k].name,R[k].time,R[k].clicks);
    }
    fclose(filename);
}
void get_user_score(User U[],int n)
{
	FILE *user_time,*user_clicks;	
	int i,j;
    user_time = fopen("time_score.txt", "w");
    if (user_time == NULL)
	{
		printf("file not found!\n");
        exit(0);
    }
    user_clicks = fopen("clicks_score.txt", "w");
    if (user_clicks == NULL)
	{
		printf("file not found!\n");
        exit(0);
    }
	
/*	for(i=0;i<n-1;i++)
		for(j=0;j<n-1-i;j++)
			if(U[j].level>U[j+1].level)
			{
			   temp=U[j];
			   U[j]=U[j+1];
			   U[j+1]=temp;
			}*/
	for(i=0;i<n;i++)
	{
        printf("%s\t%d\t%.2f\t%d\n", U[i].name, U[i].time, U[i].clicks,U[i].level);
        fprintf(user_time,"%.2f\n", U[i].time);
		fprintf(user_clicks,"%d\n", U[i].clicks);
	}
    fclose(user_time);
	fclose(user_clicks);
}
int search(User R[],int n, char name[])
{
	int i;
	for(i=0;i<n;i++)
		if(strcmp(R[i].name,name)==0) break;
	return i;
}