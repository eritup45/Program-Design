#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define maxnum 100
struct score{
		int ID;
		char stuname[maxnum];
		char phone[maxnum];
		char email[maxnum];
		struct score *next;
};
void usage(){
		printf("Please input command(i/d/u/f/l/q) and data:\n");
		printf("Insert the record:i studentID\\tname\\tphone\\temail\n");
		printf("Delete the record:d studentID\n");
		printf("Update the record:u studentID\\tname\\tphone\\temail\n");
		printf("Find the record:f [string]\n");
		printf("List the record:l\n");
		printf("Quit:q\n");
}
//**first==struct *first==struct�O���骺��m first==(�s�O�����m������)�ܼƪ��O�����m
struct score *insert(struct score *first,struct score *new){//return cur as first//
		struct score *cur=first,*tmp=cur,*pre;
		int flag=1,i=0;
		int len;
		if(first==NULL){
				first=malloc(sizeof(struct score));
				first->ID=new->ID;
				strcpy(first->stuname,new->stuname);
				strcpy(first->phone,new->phone);
				strcpy(first->email,new->email);
				first->next=NULL;
				printf("Insert successful!\n");
				return first;
		}
		while(cur!=NULL){//�P�_���S������ �٥i����cur
				if(cur->ID==new->ID){
						printf("Insert error! studentID is exists!\n");
						flag=0;
						break;
				}
				pre=cur;
				cur=cur->next;
		}
		if(flag==0){//ID ���� => ����fgets
				len=strlen(new->stuname);
				for(i=0;i<len;i++)
						new->stuname[i]='\0';
				len=strlen(new->phone);
				for(i=0;i<len;i++)
						new->phone[i]='\0';
				len=strlen(new->email);
				for(i=0;i<len;i++)
						new->email[i]='\0';
				//student[*stucnt].email[i]='\0';
				return first;
		}
		else{
				cur=first;
				pre=cur;
				while(cur!=NULL){//sort_������ ���s��cur���X�h	//�ثe���D:�u�C�X�Ĥ@�� ��L�F�賣�����F
						if(new->ID < first->ID){//���̫e��
								new->next=first;
								printf("Insert successful!\n");
								return new;
						}
						else if(new->ID > cur->ID){//�~��
								pre=cur;
								cur=cur->next;
								if(cur==NULL){//74�Y����cur->next�ONULL�h���]�ӳo��return
										pre->next=new;
										new->next=NULL;
										printf("Insert successful!\n");
										return tmp;
								}

						}
						else{
								pre->next=new;//������
								new->next=cur;
								printf("Insert successful!\n");
								return tmp;
						}
				}
				/*pre->next=new;//�i�A��X�i�Q�θ귽
				  cur=pre->next;
				  cur->ID=new->ID;//cur�w�O�̫�@��
				  strcpy(cur->stuname,new->stuname);
				  strcpy(cur->phone,new->phone);
				  strcpy(cur->email,new->email);
				  cur->next=NULL;*/
				//printf("Insert successful!\n");
				//return tmp;
		}
		return 0;
}
void list(struct score *first){
		struct score *cur=first;
		if(first==NULL){//the first data
				printf("error! (first==NULL)\n");
		}
		while(cur!=NULL){
				printf("studentID:%d\t",cur->ID);
				printf("name:%s\t",cur->stuname);	
				printf("phone:%s\t",cur->phone);
				printf("email:%s\n",cur->email);
				cur=cur->next;
		}
}
struct score *update(struct score *first,struct score *new){
		int flag=1,i=0,len=0;
		struct score *cur=first,*tmp=cur;
		while(cur!=NULL){
				if(new->ID==cur->ID){
						strcpy(cur->stuname,new->stuname);
						strcpy(cur->phone,new->phone);
						strcpy(cur->email,new->email);
						printf("Update successful!\n");
						flag=0;
						return tmp;
				}
				cur=cur->next;
		}
		if(flag==1){
				len=strlen(new->stuname);//new
				for(i=0;i<len;i++)
						new->stuname[i]='\0';
				len=strlen(new->phone);//new
				for(i=0;i<len;i++)
						new->phone[i]='\0';
				len=strlen(new->email);//new
				for(i=0;i<len;i++)
						new->email[i]='\0';
				printf("Update error! studentID not exists!\n");
		}
		flag=1;
		return first;
}
void find(struct score *first,char *line){
		int k=0,flag=0;
		char *ptr;
		char tmp[10000];
		struct score *cur=first;
		for(k=k;k>=0;k--)
				tmp[k]='\0';
		k=0;
		ptr=line+2;//��l��J"f ",�ҥH+2
		while(*(ptr+k)!='\n'){
				tmp[k]=*(ptr+k);//tmp�O�n�䪺string								
				k++;
		}
		tmp[k]='\0';
		while(cur!=NULL){
				if(strstr(cur->stuname,tmp)!=NULL||\
								strstr(cur->phone,tmp)!=NULL||\
								strstr(cur->email,tmp)!=NULL){
						printf("studentID:%d\tname:%s\tphone:%s\temail:%s\n"\
										,cur->ID,cur->stuname,cur->phone,cur->email);
						flag=1;
				}
				cur=cur->next;
		}
		if(flag==0)
				printf("Find error! Not exists!\n");
}
struct score *delete(struct score *first,struct score *new){
		int flag=1;
		struct score *cur=first,*tmp=cur,*pre;
		//latter=malloc(sizeof(struct score));
		while(cur!=NULL){//���ID�N�F��
				if(new->ID==cur->ID && cur->ID==first->ID){
						first=first->next;
						printf("delete successful!\n");
						return first;
				}
				else if(new->ID==cur->ID){
						/*while(cur->next!=NULL){//�q�᭱�л\���QDelete��
						//pre=cur;
						latter=cur->next;
						cur->ID=latter->ID;
						strcpy(cur->stuname,latter->stuname);
						strcpy(cur->phone,latter->phone);
						strcpy(cur->email,latter->email);
						cur=cur-i studentID:111	name:eri	phone:0911	email:eri@gmail>next;
						}*/
						pre->next=cur->next;
						free(cur);
						printf("delete successful!\n");
						flag=0;
						return tmp;
				}
				pre=cur;
				cur=cur->next;
		}
		if(flag==1){
				printf("Delete error! studentID not exists!\n");
		}
		return first;
}
int main(){
		int i=0;
		char line[1024];
		struct score *first=NULL,*new;
		char *ptr,*qtr;
		usage();
		while(fgets(line,1024,stdin)){
				new=malloc(sizeof(struct score));
				if((ptr=strstr(line,"studentID:"))){
						ptr=ptr+10;
						new->ID=atoi(ptr);
						new->next=NULL;
				}			
				if((qtr=strstr(line,"name:"))){
						qtr=qtr+5;
						i=0;
						while(*(qtr+i)!='\t'){
								if(i>=maxnum)	break;
								new->stuname[i]=*(qtr+i);
								i++;
						}
						new->stuname[i]='\0';
						new->next=NULL;
				}
				if((qtr=strstr(line,"phone:"))){
						qtr=qtr+6;
						i=0;
						while(*(qtr+i)!='\t'){
								if(i>=maxnum)	break;
								new->phone[i]=*(qtr+i);
								i++;
						}
						new->phone[i]='\0';
						new->next=NULL;
				}
				if((qtr=strstr(line,"email:"))){
						qtr=qtr+6;
						i=0;
						while(*(qtr+i)!='\n'){
								if(i>=maxnum)	break;
								new->email[i]=*(qtr+i);
								i++;
						}
						new->email[i]='\0';
						new->next=NULL;
				} 
				if(line[0]=='i'){//�P�_ID�O�_����
						first=insert(first,new);
				}
				if(line[0]=='d'){
						first=delete(first,new);
				}
				if(line[0]=='f'){
						find(first,line);
				}
				if(line[0]=='u'){
						first=update(first,new);
				}
				if(line[0]=='l'){
						list(first);
				}
				if(line[0]=='q'){
						printf("Thanks for your using!\n");
						break;
				}
		}
		return 0;
}

