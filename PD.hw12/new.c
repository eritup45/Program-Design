#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define maxnum 100
struct score{
		int ID;
		char stuname[maxnum];
		char phone[maxnum];
		char email[maxnum];
};
void usage(){
		printf("Please input command(i/d/u/f/l/q) and data :\n");
		printf("Insert the record : i studentID\\tname\\tphone\\temail\n");
		printf("Delete the record : d studentID\n");
		printf("Update the record : u studentID\\tname\\tphone\\temail\n");
		printf("Find the record : f [string]\n");
		printf("List the record : l\n");
		printf("Quit : q\n");
}
void insert(struct score *student,int *stucnt){
		int flag=1,j=0,i=0;
		int len;
		for(j=0;j<*stucnt;j++){
				if(student[*stucnt].ID==student[j].ID){
						printf("Insert error! studentID is exists!\n");
						flag=0;
						break;
				}
		}
		if(flag==0){//ID 重複 => 重做fgets
				len=strlen(student[*stucnt].stuname);//new
				for(i=0;i<len;i++)
						student[*stucnt].stuname[i]='\0';
				len=strlen(student[*stucnt].phone);//new
				for(i=0;i<len;i++)
						student[*stucnt].phone[i]='\0';
				len=strlen(student[*stucnt].email);//new
				for(i=0;i<len;i++)
						student[*stucnt].email[i]='\0';
				flag=1;
		}
		else{
				printf("Insert successful!\n");
				(*stucnt)++;
		}
}
void list(struct score student[],int stucnt){
		int j=0;
		for(j=0;j<stucnt;j++){
				printf("studentID:%d",student[j].ID);
				printf("\tname:%s",student[j].stuname);	
				printf("\tphone:%s",student[j].phone);
				printf("\temail:%s\n",student[j].email);
		}
}
void update(struct score *student,int *stucnt){
		int flag=1,i=0,len=0;
		for(i=0;i<*stucnt;i++){
				if(student[*stucnt].ID==student[i].ID){
						strcpy(student[i].stuname,student[*stucnt].stuname);
						strcpy(student[i].phone,student[*stucnt].phone);
						strcpy(student[i].email,student[*stucnt].email);
						printf("Update successful!\n");
						flag=0;
						break;
				}
		}
		if(flag==1){
				len=strlen(student[*stucnt].stuname);//new
				for(i=0;i<len;i++)
						student[*stucnt].stuname[i]='\0';
				len=strlen(student[*stucnt].phone);//new
				for(i=0;i<len;i++)
						student[*stucnt].phone[i]='\0';
				len=strlen(student[*stucnt].email);//new
				for(i=0;i<len;i++)
						student[*stucnt].email[i]='\0';
				printf("Update error! studentID not exists!\n");
		}
		flag=1;
}
void find(struct score student[],char *line,int *stucnt){
		int i=0,k=0,flag=0;
		char *ptr;
		char tmp[10000];
		for(k=k;k>=0;k--){
				tmp[k]='\0';
		}
		k=0;
		ptr=line+2;//原始輸入"f ",所以+2
		while(*(ptr+k)!='\n'){
				tmp[k]=*(ptr+k);//tmp是要找的string								
				k++;
		}
		tmp[k]='\0';
		//printf("k=%d\n",k);
		//printf("%s\n",tmp);
		for(i=0;i<*stucnt;i++){
				if(strstr(student[i].stuname,tmp)!=NULL||\
								strstr(student[i].phone,tmp)!=NULL||\
								strstr(student[i].email,tmp)!=NULL){
						printf("studentID:%d\tname:%s\tphone:%s\temail:%s\n"\
										,student[i].ID,student[i].stuname,student[i].phone,student[i].email);
						flag=1;
				}				
		}
		//if(flag==0)
		//flag=2;
		if(flag==0)
				printf("Find error! Not exists!\n");
}
void delete(struct score *student,int *stucnt){
		int j=0,flag=1;
		for(j=0;j<*stucnt;j++){//找到ID就幹掉
				if(student[*stucnt].ID==student[j].ID){
						for(j=j;j<*stucnt-1;j++){//從後面覆蓋掉被Delete的
								student[j]=student[j+1];
						}
						printf("delete successful!\n");
						flag=0;
						break;
				}
		}
		if(flag==0){
				(*stucnt)--;
				flag=1;
		}
		else if(flag==1){
				printf("Delete error! studentID not exists!\n");
		}
}
int main(){
		int i=0,stucnt=0;
		char line[1024];
		char *ptr,*qtr;
		struct score student[10000];
		usage();
		while(fgets(line,1024,stdin)){
				if((ptr=strstr(line,"studentID:"))){
						ptr=ptr+10;
						student[stucnt].ID=atoi(ptr);
				}			
				if((qtr=strstr(line,"name:"))){
						qtr=qtr+5;
						i=0;
						while(*(qtr+i)!='\t'){
								if(i>=maxnum)	break;
								student[stucnt].stuname[i]=*(qtr+i);
								i++;
						}
				}
				if((qtr=strstr(line,"phone:"))){
						qtr=qtr+6;
						i=0;
						while(*(qtr+i)!='\t'){
								if(i>=maxnum)	break;
								student[stucnt].phone[i]=*(qtr+i);
								i++;
						}
				}
				if((qtr=strstr(line,"email:"))){
						qtr=qtr+6;
						i=0;
						while(*(qtr+i)!='\n'){
								if(i>=maxnum)	break;
								student[stucnt].email[i]=*(qtr+i);
								i++;
						}
				} 
				if(line[0]=='i'){//判斷ID是否重複
						insert(student,&stucnt);
				}
				if(line[0]=='d'){
						delete(student,&stucnt);
				}
				if(line[0]=='f'){
						find(student,line,&stucnt);
				}
				if(line[0]=='u'){
						update(student,&stucnt);
				}
				if(line[0]=='l'){
						list(student,stucnt);
				}
				if(line[0]=='q'){
						printf("Thanks for your using!\n");
						break;
				}
		}
		return 0;
}

