#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct statistic{
		char item[200];
		int cnt;
		struct statistic *next;
};
int main(){
		int flag=0,i=0,tmp;
		char line[1024];
		struct statistic *first,*cur,*new,*pre,*ptr;
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
		flag=0;
		i=0;
		pre=first;
		cur=first;
		while(cur!=NULL && cur->next!=NULL){
				new=cur->next;
				//pre=cur;//當cur==NULL時pre記錄到最後一筆
				if(flag==0 && cur->cnt < new->cnt){
						cur->next=new->next;
						new->next=cur;
						pre=new;
						flag=1;
				}
				else if(flag==1 && cur->cnt < new->cnt){
						cur->next=new->next;
						new->next=cur;
						pre->next=new;
				}
				else
						pre=cur;
				printf("%d \n",i);//測試結果:沒有跑到最後一個cur
				i++;
				printf("%d %s",cur->cnt,cur->item);
				
				cur=cur->next;

		}
		printf("%d %s",cur->cnt,cur->item);
		return 0;
}
