//Binary Search Tree:
//	funtion:
//		1.insert
//		2.delete
//		3.query
//		4.traverse (inorder)
//		5.count
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//char *textbuf;//一次分配一堆記憶體
//struct data *kvdb;//轉BST為陣列
//struct data parseline;
typedef struct data{
		int cnt;
		int flag;//delete時使用
		char key[1024];
		struct data *lchild;
		struct data *rchild;
}Data;
/*void list(struct data *tptr){
  struct data *tmp=tptr;
  if(tmp==NULL)
  return;
  else if(tmp=tmp->lchild){//左邊尚有東西
  list(tmp);
  printf("%s\t",tmp->key);
//printf("%d\n",tmp->cnt);
return;
}
else if(tmp=tmp->rchild){//左邊尚有東西
list(tmp);
printf("%s\t",tmp->key);
//printf("%d\n",tmp->cnt);
return;				printf("error! repeat!\n");
}
}*/
void bst_traverse(struct data *tptr){
		if(tptr==NULL)
				return;
		else{
				bst_traverse(tptr->lchild);
				if(tptr->flag==1){
						printf("%s\t",tptr->key);
						printf("%d\n",tptr->cnt);
				}
				bst_traverse(tptr->rchild);
		}
}
Data *insert(Data *tptr,char *key){
		Data *tmp=tptr;
		if(tptr==NULL){
				tmp=malloc(sizeof(Data));				
				strcpy(tmp->key,key);
				tmp->cnt=1;
				tmp->flag=1;
				tmp->lchild=NULL; 
				tmp->rchild=NULL;
				return tmp;
		}
		else if(strcmp(key,tmp->key)<0){//key在左
				tmp->lchild=insert(tmp->lchild,key);
		}
		else if(strcmp(key,tmp->key)>0){//key在右
				tmp->rchild=insert(tmp->rchild,key);
		}
		else if(strcmp(tmp->key,key)==0){
				tmp->cnt++;
				tmp->flag=1;
		}
		return tptr;
}
Data *delete(Data *tptr,char *key){
		Data *tmp=tptr;
		if(tptr==NULL)
				return tptr;
		if(strcmp(tmp->key,key)==0){
				tmp->cnt--;
				if(tmp->cnt<=0){
						tmp->flag=0;//標記為刪除
						tmp->cnt=0;
				}
		}
		else if(strcmp(key,tmp->key)<0){
				tmp->lchild=delete(tmp->lchild,key);
		}
		else if(strcmp(key,tmp->key)>0){
				tmp->rchild=delete(tmp->rchild,key);
		}
		return tptr;
}
Data *query(Data *tptr,char *key){
		Data *tmp=tptr;
		if(tptr==NULL)
				return tptr;
		else if(strcmp(key,tmp->key)==0 && tmp->flag==1){
				printf("%s\t",tmp->key);
				printf("%d\n",tmp->cnt);
		}
		else if(strcmp(key,tmp->key)<0)
				tmp->lchild=query(tmp->lchild,key);
		else if(strcmp(key,tmp->key)>0)
				tmp->rchild=query(tmp->rchild,key);
		return tptr;
}
void bst2arr(Data *tptr,Data **bst_arr,int *i){
		Data *tmp=tptr;
		if(tptr==NULL)
				return;
		else{
				bst2arr(tmp->lchild,bst_arr,i);
				if(tmp->flag==1){
						bst_arr[*i]=tmp;
						(*i)++;
				}
				bst2arr(tmp->rchild,bst_arr,i);
		}
		return;
}
void Datasort(Data **bst_arr){
		Data *tmp;
		int i=0,j=0,size;
		while(*(bst_arr+i)!=NULL)	
				i++;
		size=i;
		for(i=0;i<size;i++){
				for(j=0;j<size-1;j++){
						if((bst_arr[j]->cnt) < (bst_arr[j+1]->cnt)){
								tmp=bst_arr[j];
								bst_arr[j]=bst_arr[j+1];
								bst_arr[j+1]=tmp;
						}
						else if((bst_arr[j]->cnt) == (bst_arr[j+1]->cnt)){
								if(strcmp(bst_arr[j]->key,bst_arr[j+1]->key)>0){
										tmp=bst_arr[j];
										bst_arr[j]=bst_arr[j+1];
										bst_arr[j+1]=tmp;
								}
						}
				}
		}
		return;
}
int main(){
		Data *tptr=NULL;
		Data *bst_arr[1024];
		int i=0,j=0,size;
		char key[100];
		while(scanf("%s",key)!=EOF){
				if(strcmp(key,"insert")==0){
						if(scanf("%s",key)!=EOF){
								tptr=insert(tptr,key);
						}
				}
				else if(strcmp(key,"delete")==0){
						if(scanf("%s",key)!=EOF){
								tptr=delete(tptr,key);
						}
				}
				else if(strcmp(key,"query")==0){
						if(scanf("%s",key)!=EOF){
								printf("----------\n");
								query(tptr,key);
								printf("----------\n");
						}
				}
				else if(strcmp(key,"inorder")==0){
						printf("----------\n");
						bst_traverse(tptr);
						printf("----------\n");
				}
				else if(strcmp(key,"count")==0){
						printf("----------\n");
						i=0;
						bst2arr(tptr,bst_arr,&i);
						Datasort(bst_arr);
						while(*(bst_arr+j)!=NULL){
								j++;
						}
						size=j;
						for(j=0;j<size;j++){
								printf("%d\t",bst_arr[j]->cnt);
								printf("%s\n",bst_arr[j]->key);
						}
						printf("----------\n");
				}
		}
		return 0;
}
