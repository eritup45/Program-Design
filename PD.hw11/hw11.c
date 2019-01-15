#include<stdio.h>
#include<string.h>
#include<ctype.h>
void removespace(char *line);
int main(int argc,char *argv[]){
		int i=0,j=0,k=0;
		int len2,len3,lenth;
		char sline[1024],line[1024],*ptr;
		while(fgets(line,1024,stdin)!=NULL){
				for(k=1;k<argc;k++){
						if(argv[k][0]=='-'){
								if(strcmp(argv[k],"-s")==0){
										len2=strlen(argv[k+1]);
										len3=strlen(argv[k+2]);
										for(i=j;i>=0;i--)
												sline[i]='\0';
										j=0;
										i=0;
										while((ptr=strstr(line,argv[k+1]))!=NULL){
												for(i=0;i<ptr-line;i++,j++){
														sline[j]=line[i];
												}		
												strcat(sline,argv[k+2]);
												j=j+len3;
												strcpy(line,ptr+len2);
										}
										strcat(sline,line);
										strcpy(line,sline);
										k+=2;//因為-s後有2個參數
								}
								else if(strcmp(argv[k],"-l")==0){
										for(i=0;i<(lenth=strlen(line));i++){
												line[i]=tolower(line[i]);
										}
								}
								else if(strcmp(argv[k],"-r")==0){
										removespace(line);
								}

						}
						else {
								printf("error!\n");
								break;
						}
				}
				if(k==argc && k!=1)
						printf("%s",line);
		}
		return 0;
}
void removespace(char *line){
		int len=0,i=0;		//了解strtok運作原理
		char *test;
		char s[10000];
		for(i=0;i<10000;i++)//清空空s[]
				s[i]='\0';
		test=strtok(line," ");
		while(test!=NULL){
				strcat(s,test);
				strcat(s," ");
				test=strtok(NULL," ");
				i++;
		}
		len=strlen(s);
		s[len-1]='\0';
		strcpy(line,s);
}
