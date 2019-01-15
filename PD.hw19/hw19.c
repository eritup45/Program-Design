#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define max 701//table size
struct hash{
	char key[200];
	struct hash *next;
};

int hashfunction(char *);
void hashInsert(struct hash**, char*);
int hashQuery(struct hash**, char*);
void cut(char*, struct hash**);
void getWord(struct hash**, int, char**);
void makeHashDict(struct hash**, char**);

int main(int argc,char *argv[]){
	struct hash *table[max];//for dictionary
	makeHashDict(table,argv);
	getWord(table,argc,argv);
	return 0;
}
void makeHashDict(struct hash *table[],char **argv){
	char word[200];
	int len=0,i=0;
	FILE *dictFp=fopen(argv[1],"r");
	for(i=0;i<max;i++){
		table[i]=NULL;
	}
	while(fgets(word,max,dictFp)){
		len=strlen(word);
		word[len-1]='\0';
		hashInsert(table,word);
	}
	fclose(dictFp);
}
void getWord(struct hash *table[],int argc,char **argv){
	FILE *fp;
	char line[1024];
	int len;
	if(argc==3)
		fp=fopen(argv[2],"r");
	else
		fp=stdin;
	while(fgets(line,max,fp)){
		len=strlen(line);
		line[len-1]='\0';
		cut(line,table);
	}
	fclose(fp);
	return;
}
void cut(char *line,struct hash *table[]){
	int i=0,j=0,len=20,flag;
	char key[200];
	while(line[0]!='\0'){
		len=5;
		while(len>0){
			for(j=0;j<len;j++){
				key[j]=line[j];
			}
			key[j]='\0';
			flag=hashQuery(table,key);
			if(flag==-1 && len==2){//中文字: 兩符號=一中文字
				printf("%s\n",key);
				line+=strlen(key);
				break;
			}
			else if(flag==1){
				printf("%s\n",key);
				line+=strlen(key);
				break;
			}
			else
				len--;	
		}
	}
}
int hashfunction(char key[]){
	unsigned long long sum=0;
	while(*key!='\0'){
		sum=sum*33+abs(*key);
		key++;
	}
	return sum%max;
}
void hashInsert(struct hash *table[],char *key){
	int value,search=-1;
	value=hashfunction(key);
	struct hash *new,*cur=table[value];
	while(cur!=NULL){
		if(strcmp(cur->key,key)==0){
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
		new=malloc(sizeof(struct hash));
		strcpy(new->key,key);
		new->next=NULL;
		table[value]=new;
	}
	else if(search==-1){
		new=malloc(sizeof(struct hash));
		strcpy(new->key,key);
		new->next=NULL;
		cur->next=new;
	}
	return;
}
int hashQuery(struct hash *table[],char *key){
	struct hash *cur;
	int value;
	value=hashfunction(key);
	cur=table[value];
	while(cur!=NULL){
		if(strcmp(key,cur->key)==0){
			return 1;//found
		}
		cur=cur->next;
	}
	return -1;//Not found
}
