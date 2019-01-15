#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct statistic{
		char item[200];
		int cnt;
		struct statistic *next;
};
int main(){
		int amount=2,flag=0,i=0;
		char line[1024];
		struct statistic *first,*cur,*new,*pre,*ptr,*tmp;
		first=malloc(sizeof(struct statistic));
		fgets(line,1024,stdin);
		strcpy(first->item,line);
		first->cnt=1;
		first->next=NULL;
		while(fgets(line,1024,stdin)!=NULL){//將資料存入
				cur=first;
				new=malloc(sizeof(struct statistic));
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
						cur=cur->next;
						strcpy(cur->item,line);
						cur->cnt++;
				}		
		}
		cur=first;
		cur->next=first->next;
		if(cur->next==NULL){	
				printf("first->next==NULL\n");
				printf("%d %s\n",cur->cnt,cur->item);
				return 0;
		}
		while(cur!=NULL){
				if(cur->next!=NULL){
						tmp=cur->next;
						cur=tmp;
				}
				else if(cur->next==NULL){
						printf("error!\n");
						break;
				}
				while(cur->cnt<new->cnt && cur!=NULL){
						new=cur->next;
						cur->next=new->next;
						new->next=cur;
						pre->next=new;
						cur=cur->next;
				}
		}
		return 0;
}
