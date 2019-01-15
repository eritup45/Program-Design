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
struct statistic *sort(struct statistic *first,int all){
		int i,j;
		struct statistic *current=first, *future=first->next, *previous=NULL, *last=NULL, *tmp;
		for (i = 0; i < all - 1; i++){
				current=first, future=first->next, previous=NULL, last=NULL;
				for (j = 0; j < all - i -1; j++)
				{
						if (current->cnt < future->cnt||
										(current->cnt == future->cnt&&strcmp(current->item,future->item)>0))
						{
								if(j==0){
										current->next=future->next;
										future->next=current;
										first=future;
								}
								else if(j==all-2){
										last=future;
										previous->next=last;
										current->next=last->next;
										last->next=current;

								}
								else{
										tmp=future->next;
										previous->next=future;
										future->next=current;
										current->next=tmp;
								}
						}
						if(j==0){
								previous=first;
						}
						else{
								previous=previous->next;
						}
						current=previous->next;
						future=current->next;
						if(previous==NULL||current==NULL||future==NULL){
								break;
						}

				}
		}
		return first;
}
int main(){
		int flag=0,size=0;
		char line[1024];
		struct statistic *first,*cur,*new;
		first=malloc(sizeof(struct statistic));
		//fgets(line,1024,stdin);
		if(scanf("%s",line))
				flag=0;
		strcpy(first->item,line);
		first->cnt=1;
		first->next=NULL;
		//while(fgets(line,1024,stdin)!=NULL){//將資料存入
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
		while(cur!=NULL){
				size++;
				if(cur->next==NULL)
						break;
				cur=cur->next;
		}
		first=sort(first,size);
		list(first);
		return 0;
}
