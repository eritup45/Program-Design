//FINISHED VISION
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/time.h>
#include<ctype.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#define maxline 10000000
struct nstr{
	char key[1024];
	int value;
};

/*void swap(char **x,char **y){
  char *tmp;
  tmp=*x;
 *x=*y;
 *y=tmp;
 }*/
int compare(const void *a,const void *b){//qsort�̫�Ѽ�
	return (strcmp(*(char **)a,*(char **)b));
}
void bubblesort(struct nstr *nline,int n){
	int i=0,j=0;
	struct nstr tmp;
	for(i=0;i<n;i++){
		for(j=0;j<n-1;j++){
			if(nline[j].value > nline[j+1].value){
				tmp=nline[j];
				nline[j]=nline[j+1];
				nline[j+1]=tmp;
			}
		}
	}
}
void sort_no_num(struct nstr *nline){
	int i=0,j=0,idx=0;
	struct nstr tmp;
	while(nline[idx].value==0)
		idx++;
	for(i=0;i<idx;i++){
		for(j=0;j<idx-1;j++){
			if(strcmp(nline[j].key,nline[j+1].key)>0){
				tmp=nline[j];
				nline[j]=nline[j+1];
				nline[j+1]=tmp;
			}
		}
	}

}
char *randstr(){
	int i=0,j,select;
	char *str;
	j=rand()%6+1;//�r�Ƥp��
	str=malloc(sizeof(char)*j+1);
	for(i=0;i<j;i++){
		select=rand()%2;
		if(select==0)	str[i]=rand()%(122-97+1)+97;//��ASCII a-z���϶�
		else	str[i]=rand()%(90-65+1)+65;//A-Z�϶�
	}
	str[i]='\0';
	return str;
}
void help(){
	printf("-n:Numeral comparison\n");
	printf("-a:Random number/string generator\n");
	printf("-h:Help usage\n");
}
/*void heapify(char **arr,int n,int i){//�j��p
  int largest=i;
  int l=2*i+1;//���l��
  int r=2*i+2;//�k�l��
  if(i<n && strcmp(arr[l],arr[largest])>0){
  largest=l;
  }
  if(i<n && strcmp(arr[r],arr[largest])>=0){
  largest=r;
  }
  if(largest!=i){
  swap(&arr[i],&arr[largest]);
  heapify(arr,n,largest);
  }
  }
  void myheapsort(char **arr,int n){
  int i;
  for(i=n-1;i>=0;i--){//build heap (rearrange array)
  heapify(arr,an,i);
  }
  for(i=n-1;i>=0;i--){
  swap(&arr[i],&arr[0]);
  heapify(arr,i,0);//���ʳ̫�@�Ӧr(�̤j)
  }
  }*/
void merge(char **arr,char **reg,int start,int end){
	if(start >= end)	return;
	int len=end-start,mid=(len>>1)+start;
	int start1=start,end1=mid;
	int start2=mid+1,end2=end;
	merge(arr,reg,start1,end1);
	merge(arr,reg,start2,end2);
	int k=start;
	while(start1 <= end1 && start2 <= end2)
		if(strcmp(arr[start1],arr[start2])<0){
			reg[k++]=arr[start1++];
		}
		else{
			reg[k++]=arr[start2++];
		}
	while(start1 <= end1)
		reg[k++]=arr[start1++];
	while(start2 <= end2)
		reg[k++]=arr[start2++];
	for(k=start;k <= end;k++)
		arr[k]=reg[k];
}
void mymergesort(char **arr,const int len){
	char **reg;
	reg=malloc(len*sizeof(char*));
	merge(arr,reg,0,len-1);
}

int  main(int argc,char *argv[]){
	struct nstr *nline;
	char **line1,**line2;
	line1=malloc(maxline*sizeof(char*));
	line2=malloc(maxline*sizeof(char*));
	int i=0,j=0,len=0,idx=0;
	FILE *fp;
	struct stat buf;
	int f;
	if(argc==1 || strcmp(argv[1],"-n")==0){
		if(argc==3){
			fp=fopen(argv[2],"r");
			f=open(argv[2],O_RDONLY);
			fstat(f,&buf);
			nline=malloc(buf.st_size*sizeof(struct nstr));
			
			//printf("size==%ld\n",buf.st_size);
			//printf("sizeof==%ld\n",sizeof(struct nstr));
		}
		else{
			nline=malloc(1024*sizeof(struct nstr));
			fp=stdin;
		}
		while(fgets(nline[idx++].key,1024,fp)!=NULL){;}
		while(i<idx){
			j=0;
			while(isdigit(nline[i].key[j])==0 && j<(len=strlen(nline[i].key))){;//nline[i].key[j]!='\n'){
				j++;
			}
			if(isdigit(nline[i].key[j])!=0){
				nline[i].value=atoi(nline[i].key+j);
			}
			else 
				nline[i].value=0;
			i++;
			fclose(fp);
		}
		bubblesort(nline,idx);
		sort_no_num(nline);
		for(i=0;i<idx;i++){
			printf("%s",nline[i].key);
		}
	}
	else if(strcmp(argv[1],"-a")==0){
		srand((unsigned)time(NULL));
		int time_use1=0,time_use2=0;
		struct timeval start1,start2;
		struct timeval end1,end2;
		for(i=0;i<maxline;i++){
			line1[i]=randstr();
			line2[i]=line1[i];
			//line++;���Ѫ����~
		}
		gettimeofday(&start1,NULL);
		qsort(line1,maxline,sizeof(line1[0]),compare);
		gettimeofday(&end1,NULL);
		time_use1=(end1.tv_sec-start1.tv_sec)*1000000+(end1.tv_usec-start1.tv_usec);//�L��
		printf("Q Sort:%d�@��\n",time_use1/1000);//�@��

		gettimeofday(&start2,NULL);
		mymergesort(line2,maxline);
		gettimeofday(&end2,NULL);
		time_use2=((end2.tv_sec-start2.tv_sec)*1000000+(end2.tv_usec-start2.tv_usec));//�L��
		printf("Merge Sort:%d�@��\n",time_use2/1000);//�@��

		if((time_use2-time_use1)<0)
			printf("�ɶ��t:%d�@��\n",(time_use1-time_use2)/1000);
		else
			printf("�ɶ��t:%d�@��\n",(time_use2-time_use1)/1000);
		for(i=0;i<maxline;i++)
			printf("%s\n",line2[i]);
	}
	else if(strcmp(argv[1],"-h")==0){
		help();
	}
	return 0;
}
/*struct BST *bstinsert(struct BST *rstr,char *new){
  int k;
  if(rstr==NULL){
  rstr=malloc(sizeof(struct BST));
  rstr->key=malloc(8);
  strcpy(rstr->key,new);
  rstr->l=NULL;
  rstr->r=NULL;
  return rstr;
  }
  else{
  k=strcmp(new,rstr->key);
  if(k<0){
  rstr->l=bstinsert(rstr->l,new);
  }	
  else if(k>=0){
  rstr->r=bstinsert(rstr->r,new);
  }
  }
  }
  void bsttraverse(struct BST *rstr){
  if(rstr==NULL)	return;
  bsttraverse(rstr->l);
  printf("%s\n",rstr->key);
  bsttraverse(rstr->r);
  }*/
