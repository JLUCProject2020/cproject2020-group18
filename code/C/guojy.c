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
    float time;//����ʱ��
    int clicks;//�������
	int level;
	Date date;  //��¼����
}User;
void sort_clicks(User U[],int n) ;// ������������򣬵�������ٵ�����ǰ��
void sort_time(User U[],int n) ;  //�����ʱ������ʱ��̵�����ǰ��
void output_rank(FILE *filename,User temp[],int n,char name[]);  //�������ļ�¼��д���ļ�
void get_user_score(User U[],int n);  //����ǰ�û��ĳɼ�д���ļ�
int search(User R[],int n, char name[]);
int main()
 {
    User temp[N],R[N];  //tempΪ��ʱ���飻RΪ��ǰ�û�����ʷ���ݣ�����Ϸ�����ţ����ڻ����û��ĳɼ�����ͼ
    int i,j,k,rec_num,level;//user_numΪ�û�����rec_numΪ�ļ��еļ�¼����
	char name[10];
	FILE *read,*write1,*write2,*last;  //������������ļ�����ʱ��������ļ�

///////	gcvt(t,4,name);
	


//���ļ��ж�ȡ��ǰ�û�����Ϣ
	last = fopen("last_user.txt", "r+");
	if (last == NULL)
		{
			printf("file not found!\n");
			return 0;
		}

//�ȴ��ļ�last_uuser.txt�ж����û���ǰ��������Ϸ������û����ƣ�Ȼ��Ըü�������ݽ�������������а�
	fscanf(last, "%s\t%f\t%d\t%d\n", temp[0].name, &temp[0].time, &temp[0].clicks,&temp[0].level);
    printf("%s\t%.2f\t%d\t%d\n", temp[0].name, temp[0].time, temp[0].clicks,temp[0].level);
    level=temp[0].level;    //ȡ����ǰ��Ϸ�ߵ���Ϸ���𣬸���level
    strcpy(name,temp[0].name);  //ȡ����ǰ�û������֣����ڶԸ��û�����ʷ�ɼ���������
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
    	if(strcmp(temp[i].name,name)==0&&temp[i].level==level) R[j++]=temp[i];    //����ǰ�û�����ǰ�������ʷ���ݴ���R
		if(temp[i].level==level)     //temp��ֻ������Ϸ�������level������
			i++;
	
    }
    fclose(read);
	rec_num=i;  //�ļ��й���rec_num����¼
	get_user_score(R,j);   //����ǰ�û��ü���ĳɼ�д���ļ�user_score.txt
	write1 = fopen("rank_clicks.txt", "w");   //write1���ڴ������������������ļ�ranking_clicks
	if(write1==NULL)
	{
		printf("cannot create file!\n");
        return 0;
	}
	write2 = fopen("rank_time.txt", "w");  //write2���ڴ�����ʱ��������ļ�ranking_time
	if(write2==NULL)
	{
		printf("cannot create file!\n");
        return 0;
	}

//��ȡ�ļ����� 
    sort_clicks(temp,rec_num);  //�������û������������������
//��ӡ����������
	printf("after sort by clicks:\n");
	for(k=0;k<rec_num;k++)
       printf("%s\t%.2f\t%d\t%d\n", temp[k].name, temp[k].time, temp[k].clicks,temp[k].level );

//������������д���ļ�ranking_clicks.txt��һ���û�ֻ����һ��
	output_rank(write1,temp,rec_num,name);

    sort_time(temp,rec_num);  //�������û������������������
//��ӡ����������
	printf("after sort by time:\n");
	for(k=0;k<rec_num;k++)
       printf("%s\t%.2f\t%d\t%d\n", temp[k].name, temp[k].time, temp[k].clicks,temp[k].level ); 
//������������д���ļ�ranking_time.txt��һ���û�ֻ����һ��
    output_rank(write2,temp,rec_num,name);
	fclose(write1);
	fclose(write2);
    return 0;
}
void sort_clicks(User U[],int n)    //�����������С�������򣬵��������ͬ�ģ���ʱ���С��������
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
void sort_time(User U[],int n)   //����Ϸ����ʱ���С��������ʱ����ͬ�ģ������������С��������
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
void output_rank(FILE *filename,User temp[],int n,char name[])   //��������д���ļ�filename
{
	User R[N];
	int i,j,k,m,user_num,flag,no;//user_numΪ�û�����rec_numΪ�ļ��еļ�¼����
	int index;//�±� 
	char res[31];
    char buff[4],Le[3],time[10]; // //buff����������Le����Ϸ����
	R[0] = temp[0];
    user_num = 1;
	index=0;  
	flag=0;   //���ڱ굱ǰ�û��Ƿ������ǰ������������֣����а�ֻ��ʾǰ����������ʾǰ���ӵ�ǰ�û�����4����¼
	for (k = 0; k < n; k++) 
	{
		if(strcmp(temp[k].name,name)==0) flag=1;
		for(j=0;j<k;j++)
			if (strcmp(temp[k].name, temp[j].name)==0)
				break;
		if(j>=k)
		{  //�����ǰ������Ԫ�غ�ǰһ��Ԫ��������ͬ����д��R[index++]�У���ͬһ���û�ֻд��һ��
            R[index++] = temp[k];//�浽R��   
            user_num++;
        }
		if(index>2) break;
	}
	if(flag==0)
	{
		no=search(temp,n,name);    //�����ǰ�û�û����ǰ��������������ļ��е�����������������ŷ��أ����¼��Ϣ����R[index]
		R[index++]=temp[no];
	}


    //printf("Number of users:=%d\n",user_num);
    
    for ( k = 0; k < index; ++k) 
	{
        itoa(R[k].clicks, buff, 10);   //������ת��Ϊ10���Ƶ�ASCII�룬4λ������buff
		itoa(R[k].level,Le,10);    //����Ϸ�ȼ�ת��Ϊʮ�����ַ���������Le
        //gcvt(R[k].time,10,time);    //char *gcvt(double v,int n,char *b)������һ������b�Ǵ��ת����du���ַ���zhi�Ŀռ��׵�ַ(ָ��)��n��ת������ַ����ĳ��ȣ�
		sprintf(time,"%.2f", R[k].time);   //��ʵ��ʱ��ת��Ϊ������λС�����ַ���
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