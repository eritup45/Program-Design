#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct statistic{
		char item[200];
		int cnt;
		struct statistic *next;
};
void list(struct statistic *first){
		struct statistic *cur;
		cur=first;
		while(cur!=NULL){
				printf("%d %s\n",cur->cnt,cur->item);
				cur=cur->next;
		}
}
void bubblesort(int size,struct statistic **first){
		int i=0,j=0;
		struct statistic *cur=*first,*pre=NULL,*new=NULL;
		if((*first)->next==NULL){//first在main判斷好了
				return;
		}
		for(i=0;i<size;i++){
				cur=*first;
				for(j=0;j<size-1;j++){
						new=cur->next;
						if((cur->cnt<new->cnt || (cur->cnt==new->cnt&&strcmp(cur->item,new->item)>0)) && j==0){
								cur->next=new->next;
								new->next=cur;
								*first=new;//wen
								pre=new;
						}
						else if(cur->next!=NULL && (cur->cnt<new->cnt||(cur->cnt==new->cnt&&strcmp(cur->item,new->item)>0))){
								cur->next=new->next;
								new->next=cur;
								pre->next=new;
								pre=new;
						}						
						else{
								pre=cur;
								cur=cur->next;
						}
						if(cur==NULL || cur->next==NULL){
								break;
						}
				}
		}
}
int main(){
		int flag=0,size=0;
		char line[1024];
		struct statistic *first,*cur,*new;
		first=malloc(sizeof(struct statistic));
		if(scanf("%s",line)){;}
		strcpy(first->item,line);
		first->cnt=1;
		first->next=NULL;
		while(scanf("%s",line)!=EOF){
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
						cur->cnt=1;
				}		
		}
		cur=first;
		while(cur!=NULL){//計算size=?
				size++;
				if(cur->next==NULL)
						break;
				cur=cur->next;
		}
		bubblesort(size,&first);
		list(first);
		return 0;
}

