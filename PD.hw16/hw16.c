//hash
//	funtion:
//		1.insert
//		2.delete
//		3.query
//		4.count
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define max 26
typedef struct hashdata{
	int cnt;
	char key[1000];
	struct hashdata *next;
}data;
typedef struct hashtable{
	struct hashdata *start;//放data的第一筆位置
}table;
int hashfunction(char key[]){
	int a=key[0];
	return a%max;
}
void insert(table t[],char *key){
	int value,search=-1;
	value=hashfunction(key);
	data *new,*cur=t[value].start;
	while(cur!=NULL){
		if(strcmp(key,cur->key)==0){
			search=1;//找到了
			break;
		}
		else if(cur->next==NULL){//等等插後面
			break;
		}
		else 
			search=-1;//沒找到
		cur=cur->next;
	}
	if(cur==NULL){
		new=malloc(sizeof(data));
		new->cnt=1;
		strcpy(new->key,key);
		new->next=NULL;
		t[value].start=new;
	}
	else if(search==-1){
		new=malloc(sizeof(data));
		new->cnt=1;
		strcpy(new->key,key);
		new->next=NULL;
		cur->next=new;
	}
	else if(search==1){
		cur->cnt++;
	}
	return;
}
void delete(table *t,char *key){//cur->cnt=0等於刪除
	data *cur;
	int value;
	value=hashfunction(key);
	cur=t[value].start;
	while(cur!=NULL){
		if(strcmp(key,cur->key)==0){
			if(cur->cnt>=1)
				cur->cnt--;
				break;
		}
		cur=cur->next;
	}
}
void query(table *t,char *key){
	data *cur;
	int value;
	value=hashfunction(key);
	cur=t[value].start;
	while(cur!=NULL){
		if(strcmp(key,cur->key)==0 && cur->cnt>=1){
			printf("%s	%d\n",cur->key,cur->cnt);
			return;
		}
		cur=cur->next;
	}
	printf("Not found!\n");
}
void hash2arr(table *t,data **hash_arr,int *total){
	data *cur;
	int i=0;
	for(i=0;i<max;i++){
		cur=t[i].start;
		if(cur==NULL){
			continue;
		}
		while(cur!=NULL && cur->cnt>=1){
			hash_arr[*total]=cur;
			cur=cur->next;
			(*total)++;
		}
	}
	if((*total)!=0){;}//no use
}
void datasort(data **hash_arr,int total){
	data *tmp;
	int i=0,j=0;
	for(i=0;i<total;i++){
		for(j=0;j<total-1;j++){
			if((hash_arr[j]->cnt) < (hash_arr[j+1]->cnt)){
				tmp=hash_arr[j];
				hash_arr[j]=hash_arr[j+1];
				hash_arr[j+1]=tmp;			
			}
			else if((hash_arr[j]->cnt) == (hash_arr[j+1]->cnt)){
				if(strcmp(hash_arr[j]->key,hash_arr[j+1]->key)>0){
					tmp=hash_arr[j];
					hash_arr[j]=hash_arr[j+1];
					hash_arr[j+1]=tmp;
				}
			}
		}
	}
return;
}
int main(){
	data *hash_arr[1000];
	table t[max];
	char key[1000];
	int total=0,i=0;
	for(i=max-1;i>=0;i--){
		t[i].start=NULL;
	}
	while(scanf("%s",key)!=EOF){
		if(strcmp(key,"insert")==0 && scanf("%s",key)!=EOF){
			insert(t,key);
		}
		else if (strcmp(key,"delete")==0 && scanf("%s",key)!=EOF){
			delete(t,key);
		}
		else if (strcmp(key,"query")==0 && scanf("%s",key)!=EOF){
			printf("----------\n");
			query(t,key);
			printf("----------\n");
		}
		else if(strcmp(key,"count")==0){
			printf("----------\n");
			hash2arr(t,hash_arr,&total);
			datasort(hash_arr,total);
			for(i=0;i<total;i++){
				printf("%d	%s\n",hash_arr[i]->cnt,hash_arr[i]->key);
			}
			printf("----------\n");
		}
	}
	return 0;
}
