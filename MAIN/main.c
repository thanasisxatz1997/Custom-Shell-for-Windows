#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int GetKeyword(char Matrix[500], char KM[4]);
int Find(char FileNameMatrix[50],char AlphanumericMatrix[100],char DestinationFileMatrix[50]);
int main(int argc, char *argv[]) {
	int KeywordCase,SpaceCount,i,j,exit=0,MatrixLength;
	char Matrix[500],KM[4],AlphanumericValue2[100];
	char FileNameMatrix[50],AlphanumericMatrix[100],AlphanumericMatrix2[100],DestinationFileMatrix[50];
	char DelAlphanumeric[50];
	while(exit!=1){
	printf("Type help to see the available commands\n");
	gets(Matrix);
	SpaceCount=GetKeyword(Matrix,KM);
	while (Matrix[3+SpaceCount]!=' '&&Matrix[4+SpaceCount]!=' '&&Matrix[3+SpaceCount]!='\0'&&Matrix[4+SpaceCount]!='\0'){
		printf("Error\n");
		for(i=0;i<4;i++){
			KM[i]='\0';
		}
	    gets(Matrix);
	    SpaceCount=GetKeyword(Matrix,KM);
	}
	KeywordCase=CaseComparison(KM);
	if(KeywordCase==1){
	    printf("You have chosen the First Option(dir):\n");
		dir();
	}
	else if(KeywordCase==2){
		j=0;
		printf("You have chosen the second Option(echo):\n");
		for(i=0+SpaceCount+5;i<500;i++){
			AlphanumericValue2[j]=Matrix[i];
			j++;
		}
		printf("%s\n",AlphanumericValue2);
	}
	else if(KeywordCase==3){
		printf("You have chosen the third Option(find):\n");
		int position=4+SpaceCount;
		position=position+SpacesCountFun(Matrix,position);
		position=position+FileName(Matrix,FileNameMatrix,position);
		if(Matrix[position]==' '){
		    position=position+SpacesCountFun(Matrix,position);
		    position=position+AlphanumericFun(Matrix,AlphanumericMatrix,position)+2;
		    if  (Matrix[position]==' '){
		    	for(i=0;i<100;i++){
		    		if(AlphanumericMatrix[i]!='\0'){
		    		    AlphanumericMatrix2[i]=AlphanumericMatrix[i];
		    		}
		    		else{
		    			AlphanumericMatrix2[i]='\0';
		    			break;
					}
				}
		    	DestinationFile(Matrix,DestinationFileMatrix,position+1);
		    	Find(FileNameMatrix,AlphanumericMatrix,DestinationFileMatrix);
			}
			else{
				printf("\nError!\n");
			}
	    }
	    else{
	    	printf("Error!");
		}
	}
	else if(KeywordCase==4){
		printf("You have chosen the fourth Option(del)\n");
		int position=3+SpaceCount;
		int i=0,fail=0;
		int DelAlphCount=0;
		char DelFileName[500];
		position=position+SpacesCountFun(Matrix,position);
		if(Matrix[position]=='*'&&Matrix[position+1]=='.'&&Matrix[position+2]=='*'){
			position=position+3;
			position=position+SpacesCountFun(Matrix,position);
			while(Matrix[position+i]!=' '&&Matrix[position+i]!='\0'){
				DelAlphanumeric[i]=Matrix[position+i];
				DelAlphCount=DelAlphCount+1;
				i++;
			}
			position=position+i;
			i=0;
			for(i=position+i;i<500;i++){
				if(Matrix[i]=='\0'){
					break;
				}
				if(Matrix[i]!=' '&&Matrix[i]!='\0'){
				    fail=1;
				    puts(Matrix);
				    break;
				}
			}
			if(fail==1){
				printf("Please insert a valid command.The correct syntax of the dell command is 'del *.* alphanumeric'\n");
			}
			else{
				char c;
				int success=0;
				FILE *fptr;
				DIR *p;
                struct dirent *pp;
                p = opendir ("./");
                if (p != NULL)
                {
                while ((pp = readdir (p))!=NULL) {
                    int length = strlen(pp->d_name);
                    if (strncmp(pp->d_name + length - 4, ".txt", 4) == 0) {
                        puts (pp->d_name);
                        sprintf(DelFileName, "%s", pp->d_name);
                        fptr=fopen(DelFileName,"r");
                        while(1){
                        	c=fgetc(fptr);
                        	if(feof(fptr)){
                        		break;
							}
							//printf("%c",c);
							if(c==DelAlphanumeric[success]){
								success=success+1;
								if(success==DelAlphCount){
									printf("DELETING\n");
									fclose(fptr);
									if(remove(DelFileName)==0){
										printf("Deleted successfully\n");
										break;
									}
									else{
										printf("Unable to delete file\n");
									}
								}
							}
							else{
								success=0;
								if(c==DelAlphanumeric[0]){
									success=1;
								}
							}
						}
						fclose(fptr);
                    }
                }
                (void) closedir (p);
                }
			    }
		}
		else{
			printf("Please insert a valid command.The correct syntax of the dell command is 'del *.* alphanumeric'\n");
		}
		}
	else if(KeywordCase==5){
		printf("You have chosen the fifth Option(tree):\n");
		system("tree");
	}
	else if(KeywordCase==6){
		exit=1;
		printf("Exiting");
	}
	else if(KeywordCase==7){
		printf("This program supports the 5 following commands:\n1) dir\n2) echo alphanumeric_value\n3) find source_text_file alphanumeric > destination_text_file\n4) del *.* alphanumeric\n5) tree\n6) exit\n");
	}
	else if(KeywordCase==0){
		printf("Please choose a valid command!\n");
	}
	KM[0]='\0';
	KM[1]='\0';
	KM[2]='\0';
	KM[3]='\0';
	KM[4]='\0';
}
	return 0;
}
//sugkrinei thn proth lexh tou string
int CaseComparison(char KM[4]){
	int i=0,case1=1,case2=2,case3=3,case4=4,case5=5,case6=6,case7=7,KeywordCase;
	char Keyword2[4]="echo";
	char Keyword3[4]="find";
	char Keyword4[3]="del";
	char Keyword5[4]="tree";
	char Keyword1[3]="dir";
	if((KM[0]=='e'||KM[0]=='E')&&(KM[1]=='c'||KM[1]=='C')&&(KM[2]=='h'||KM[2]=='H')&&(KM[3]=='o'||KM[3]=='O')){
		KeywordCase=case2;
	}
	else if((KM[0]=='d'||KM[0]=='D')&&(KM[1]=='i'||KM[1]=='I')&&(KM[2]=='r'||KM[2]=='R')&&(KM[3]=='\0')){
		KeywordCase=case1;
	}
	else if(KM[0]=='t'||KM[0]=='T'&&KM[1]=='r'||KM[1]=='R'&&KM[2]=='e'||KM[2]=='E'&&KM[3]=='e'||KM[3]=='E'){
		KeywordCase=case5;
	}
	else if((KM[0]=='f'||KM[0]=='F')&&(KM[1]=='i'||KM[1]=='I')&&(KM[2]=='n'||KM[2]=='N')&&(KM[3]=='d'||KM[3]=='D')){
		KeywordCase=case3;
	}
	else if((KM[0]=='d'||KM[0]=='D')&&(KM[1]=='e'||KM[1]=='E')&&(KM[2]=='l'||KM[2]=='L')&&(KM[3]=='\0')){
		KeywordCase=case4;
	}
	else if((KM[0]=='e'||KM[0]=='E')&&(KM[1]=='x'||KM[1]=='X')&&(KM[2]=='i'||KM[2]=='I')&&(KM[3]=='t'||KM[3]=='T')){
		KeywordCase=case6;
	}
	else if((KM[0]=='h'||KM[0]=='H')&&(KM[1]=='e'||KM[1]=='E')&&(KM[2]=='l'||KM[2]=='L')&&(KM[3]=='p'||KM[3]=='P'))
	return KeywordCase=case7;
}
//Jaxnei na vrei thn proth lexh tou string gia na thn sugkrinei
int GetKeyword(char Matrix[500], char KM[4]){
		int count=0,i,repeats=0;
		for(i=0;i<500;i++){
		if(Matrix[i]!=' '){
			while(Matrix[i] != ' ' && Matrix[i]!='\0' && repeats<4){
				KM[i-count]=Matrix[i];
				repeats=repeats+1;
				i=i+1;
			}
		    break;
		}
		else{
			count=count+1;
		}
		if(repeats==3){
			KM[3]='\0';
		}
	}
	return count;
}

int dir(void){
	     DIR *folder;
    struct dirent *entry;
    int files = 0;

    folder = opendir(".");
    if(folder == NULL)
    {
        perror("Unable to read directory");
        return(1);
    }

    while( (entry=readdir(folder)) )
    {
        files++;
        printf("File %3d: %s\n",
                files,
                entry->d_name
              );
    }

    closedir(folder);
}

int Find(char FileNameMatrix[50],char AlphanumericMatrix[100],char DestinationFileMatrix[50]){
   int i=0,j=0,success=0,SuccessFactor=0,AlphanumericMatrixCount=0,NumOfLines=0,NumOfColumns,search=0,CountOfLinesFound=0,temp=0,DestFileOpen=0;
   char TempChar,line[500],TextOfFile[500][500];
   while(AlphanumericMatrix[i]!='\0'){
   	//Vriskei to plhthos ton xarakthron sto string AlphanumericMatrix
   	AlphanumericMatrixCount=AlphanumericMatrixCount+1;
   	i++;
   }
   FILE *fptr;
   FILE *fptrd;
   int c;
   fptr =fopen(FileNameMatrix,"r");
   if(fptr==NULL){
   	perror("Error in opening file");
   	return(-1);
   }
   i=0;
   j=0;
   while(1){
   	c=fgetc(fptr);
   	if(feof(fptr)){
   		TextOfFile[i][j]='\0';
   		break;
	   }
	TextOfFile[i][j]=c;
	if(TextOfFile[i][j]=='\n'){
		j=0;
		i++;
		NumOfLines=NumOfLines+1;
	}
	else{
		j++;
		
	}
   }
   j=0;
   i=0;
   for(i=0;i<=NumOfLines;i++){
   	for(j=0;j<500;j++){
   		if((TextOfFile[i][j]==AlphanumericMatrix[search])||(TextOfFile[i][j-1]==AlphanumericMatrix[search])){
		success=success+1;
		if(success==AlphanumericMatrixCount){
			CountOfLinesFound=CountOfLinesFound+1;
			for(temp=0;temp<500;temp=temp+1){
				line[temp]=TextOfFile[i][temp];
			}
			if(DestFileOpen==0){
				fptrd=fopen(DestinationFileMatrix,"a");
				DestFileOpen=1;
			}
			fputc('\n',fptrd);
			fputs(line,fptrd);
			search=0;
			success=0;
		}
		else{
			search=search+1;
		}
	    }
	    else{
		    search=0;
		    success=0;
	    }
   		if(TextOfFile[i][j]=='\n'){
   			break;
		   }
	   }
   }
   fclose(fptr);
   printf("\n");
   if(DestFileOpen==1){
   	fclose(fptrd);
   }
   else{
   	printf("Alphanumeric Not Found!\n");
   }
   FileNameMatrix[0]='\0';
   TextOfFile[0][0]='\0';
   return 0;
}
//Metraei to plhthos ton kainon kai epistrefei to position sto matrix meta apo ta kaina
int SpacesCountFun(char Matrix[500], int position){
	int SpacesCount=0,i=0;
	while(Matrix[position+i]==' '){
		i++;
	}
	position=position+i;
	return i;
}
//pairnei to onoma tou arxeiou gia thn entolh find
int FileName(char Matrix[500],char FileNameMatrix[50], int position){
	int i=0;
	while(Matrix[position+i]!=' '){
	    FileNameMatrix[i]=Matrix[position+i];
	    i++;
	}
	FileNameMatrix[i]='\0';
	return i;
}
//briskei to alphanumeric gia thn entolh find kai epistrefei to position
int AlphanumericFun(char Matrix[500],char AlphanumericMatrix[100],int position){
	int i=0,point,LastCharPos;
		while(i<501){
			if(Matrix[position+i]=='>'&&Matrix[position+i-1]==' '){
				break;
			}
			i++;
			if(i==500){
				if((Matrix[position+i-1]!='>')&&(Matrix[position+i-2]!=' ')){
					printf("Error! Please follow the instructions. the format of the command find should be: find source_text_file alphanumeric > destination_text_file\n");
					return 0;
					break;
				}
			}
		}
		point=i;
		i=0;
		for(i=0;i<point-1;i++){
			LastCharPos=i;
			AlphanumericMatrix[i]=Matrix[position+i];
		}
		AlphanumericMatrix[LastCharPos+1]='\0';
		return i;
}
//Pairnei to destination File gia thn entolh del
int DestinationFile(char Matrix[500],char DestinationFileMatrix[50],int position){
	int i=0;
	while(Matrix[position+i]!=' '){
		DestinationFileMatrix[i]=Matrix[position+i];
		i++;
	}
	return i;
}
