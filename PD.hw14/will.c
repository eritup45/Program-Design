#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct statistic{
		char item[200];
		int cnt;
		struct statistic *previous;
		struct statistic *mylocation;
		struct statistic *next;
};
void list(struct statistic *first){
		struct statistic *cur;
		cur=first;
		while(cur!=NULL){
				printf("%d %s",cur->cnt,cur->item);
				cur=cur->next;
		}
}
void initialize(struct statistic **tmp){
		int len,i=0;
		(*tmp)->cnt=0;//tmp初始化
		len=strlen((*tmp)->item);
		for(i=len;i>=0;i--){
				(*tmp)->item[i]='\0';
		}
}
struct statistic *delete(struct statistic *first,struct statistic *new){//new是要刪掉的東西
		int flag=1;
		struct statistic *cur=first,*tmp=cur,*pre;
		while(cur!=NULL){//找到ID就幹掉
				if(strcmp(new->item,cur->item)==0 && strcmp(cur->item,first->item)==0){
						first=first->next;
						return first;
				}
				else if(strcmp(new->item,cur->item)==0){
						pre->next=cur->next;
						free(cur);
						flag=0;
						return tmp;
				}
				pre=cur;
				cur=cur->next;
		}
		if(flag==1){
		  printf("Delete error! Not exists!\n");
		  }
		return first;
}
deletetest(struct statistic **first){
		struct statistic *c;
		c=malloc(sizeof(struct statistic));
		strcpy(c->item,"c");
		printf("%s\n",c->item);
		delete(*first,c);
		list(*first);
}
void sortandlist(struct statistic *first){
		struct statistic *tmp,*cur=first;
		int len,i=0;
		while(first!=NULL){//first停止條件??//first沒印出
				while(cur!=NULL){
						initialize(&tmp);
						tmp->cnt=cur->cnt;
						strcpy(tmp->item,cur->item);
						if(cur->next==NULL){
								printf("cur>next==NULL so set cur=cur->next and break!\n");
								cur=cur->next;
								break;
						}
						else if(cur->cnt > cur->next->cnt){
								initialize(&tmp);
								tmp->cnt=cur->cnt;
								strcpy(tmp->item,cur->item);
						}
						cur=cur->next;
				}
				printf("first==%p\n",first);//first!=NULL forever
				printf("cur==%p\n",cur);
				//printf("cur->next==%p\n",cur->next);//cur->next=NULL forever//cur!=NULL forever			
				printf("the result:\n");
				printf("%d %s",tmp->cnt,tmp->item);
				first=delete(first,tmp);
				printf("after delete剩:\n");//刪成first了
				//initialize(&tmp);
				list(first);
				//break;
		}
}
int main(){
		int flag=0,size=0;
		char line[1024];
		struct statistic *first,*cur,*new;
		struct statistic *c;
		first=malloc(sizeof(struct statistic));
		fgets(line,1024,stdin);
		strcpy(first->item,line);
		first->cnt=1;
		first->next=NULL;
		first->mylocation=first;
		first->previous=NULL;
		while(fgets(line,1024,stdin)!=NULL){//將資料存入
				//while(scanf("%s",&line)!=EOF){
				cur=first;
				new=malloc(sizeof(struct statistic));
				new->mylocation=new;
				while(cur!=NULL){
						if(strcmp(cur->item,line)==0){
								cur->cnt++;
								flag=2;
								break;
						}
						else if(cur->next==NULL){
								flag=1;
								break;
						}
						cur=cur->next;
				}
				if(flag==1){
						cur->next=new;	
						new->previous=cur;
						cur=cur->next;
						strcpy(cur->item,line);
						cur->cnt=1;
				}		
		}
		list(first);
		//sortandlist(first);
		deletetest(&first);
		return 0;
		}
		//printf("first==%s",(*first)->item);
		//printf("cur==%s",cur->item);
		//printf("cur->next==%s",cur->next->item);							
		//printf("new==%s",new->item);
		//printf("new->next==%s",new->next->item);							
