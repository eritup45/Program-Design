#include<stdio.h>
#include<string.h>
static char *mystrstr(char *line,char *word){
		int i=0,j=0,len1,len2,tmp;
		static char final[1024];
		len1=strlen(line);
		len2=strlen(word);
		for(i=0;i<len1;i++){
				tmp=i;
				for(j=0;j<len2;j++){
						if(line[tmp]==word[j]){
								tmp++;
						}
						else{
								break;
						}
				}
				if(j==len2){	
						for(i=i,j=0;i<len1;i++,j++){
								final[j]=line[i];
						}
						final[j]='\0';
						return final;
				}
		}
		return NULL;
}
void usage(){
		printf("please input a correct option\n");
		printf("-c:print pattern counts\n");
		printf("-m:find lines containing a pattern\n");
		printf("-v:find lines not containing a pattern\n");
}
int main(int argc,char *argv[]){
		char line[1024];
		int cnt=0,patternlen;
		if(argc!=3){
				usage();
				return 0;
		}
		patternlen=strlen(argv[2]);
		while(fgets(line,1024,stdin)!=NULL){
				if(strcmp(argv[1],"-c")==0){
						while(mystrstr(line,argv[2])!=NULL){//strstr沒有好好運作
								cnt++;
						printf("%s-------------\n",line);							
								strcpy(line,(line+patternlen));
						printf("%s+++++++++++++\n",line);
						}
				}
				else if(strcmp(argv[1],"-m")==0){
						if(mystrstr(line,argv[2])!=NULL)
								printf("%s",line);
				}
				else if(strcmp(argv[1],"-v")==0){
						if(mystrstr(line,argv[2])==NULL)
								printf("%s",line);
				}
		}
		if(strcmp(argv[1],"-c")==0){
				printf("%s:%d\n",argv[2],cnt);
		}
		return 0;
}
