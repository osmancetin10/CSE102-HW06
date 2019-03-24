						/***************************/
						/*                         */
						/*      Osman Çetin        */
						/*       161044069         */
						/*          HW-06          */
						/*                         */
						/***************************/


#include <stdio.h>

void menu();
void encrypt_open_msg();
void decrypt_secret_msg();/*these are prototypes*/
int find_size_of_line(char line[]);
void reverse_line(char line[], int line_lenght);

/*This program implements a program which encrypts, or decrypts a given message. The message contains only English letters and they are all in lowercase.*/



int main(){

	menu();	
	
	return 0;
}


void menu(){/*Because of this function you can choose encrypt, decrypt or exit by using menu*/
	
	int selection;
	
	do{
		printf("1. Encrypt\n");
		printf("2. Decrypt\n");
		printf("0. Exit\n");
		printf("Choice:");
		scanf("%d",&selection);
		
		switch(selection){
			case 1: encrypt_open_msg();
					break;
			case 2: decrypt_secret_msg();
					break;
		
		}
	}while(selection!=0);
}

void encrypt_open_msg(){/*this function encrypt message where in file with using reverse function and key. and then writes encrypted message to secret file */ 
	int i=0,j=0,k,m,line_lenght,key;
	FILE *fl;
	char str[50][1024],line[1024];
	char a;
	
	do{/*this gets key from user*/
		printf("Key:");
		scanf("%d",&key);
	}while(key<=1 || key>=26);
	
	
	fl=fopen("open_msg.txt","r");
	
	do{ /*the purpose of this function is get line from text*/
		a=fscanf(fl,"%c",&(str[i][j]));
		
		if(str[i][j]=='\n'){
			i++;/*this is size line*/
			j=0;
		}
		else ++j;
			
	}while(a!=EOF);/*loop will finish when comes and of file*/
	
	j=0;
	fclose(fl);
	
	fl=fopen("secret_msg.txt","a");
	for(m=0;m<i;m++){
		for(j=0;j<1024;j++){
			line[j]=str[m][j];
		}

		line_lenght=find_size_of_line(line);/*this finds lenght of line*/

		reverse_line(line,line_lenght);	/*this reverses line*/
		
		for(k=0;k<line_lenght;k++){/*this loop returns the words back to given key value*/
			if(line[k]!=' ' && line[k]!='.' ){
				line[k]-=key;
				if(line[k]<'a') line[k]+=26;
			}
			else if(line[k]==' ') line[k]='_';/*this condition changes void to underscore*/
			else if(line[k]=='.') line[k]='*';/*this condition changes dot to star*/
		}	
		fprintf(fl,"%s",line);/*this writes decrypted message to file*/

	}


	fclose(fl);
}

int find_size_of_line(char line[]){/*this function can find line lenght by using '\n'*/
	int i;
	for(i=0;line[i]!='\n';i++); return i-1;
}	


void reverse_line(char line[], int line_lenght){/*this function can reverse given line*/ 
	int i,j,temp=0;
	
	for(i=line_lenght-1,j=0;i>line_lenght/2;i--,j++){
		temp=line[i];
		line[i]=line[j];
		line[j]=temp;
	}
}

void decrypt_secret_msg(){/*this function decrypts message where in secret file with using reverse function and key. and then writes decrypted message to open file */ 	
	int i=0,j=0,k,m,line_lenght,key,ascii;
	FILE *fl;
	char a,str[50][1024],line[1024];
	
	do{/*this gets key value from user*/
		printf("Key:");
		scanf("%d",&key);
	}while(key<=1 || key>=26);
	
	
	fl=fopen("secret_msg.txt","r");
	
	do{/*this loop gets lines from secret text when comes end of file*/ 
		a=fscanf(fl,"%c",&(str[i][j]));
		
		if(str[i][j]=='\n'){
			i++;
			j=0;
		}
		else ++j;
			
	}while(a!=EOF);
	
	j=0;
	fclose(fl);
	
	fl=fopen("open_msg.txt","a");
	for(m=0;m<i;m++){
		for(j=0;j<1024;j++){
			line[j]=str[m][j];
		}

		line_lenght=find_size_of_line(line);/*this finds lenght of line */

		for(k=0;k<line_lenght;k++){/*this loop decrypts given line*/
			if(line[k]=='_') line[k]=' ';/*this changes underscore to void*/
			else if(line[k]=='*') line[k]='.';/*this changes star to dot*/
			else if(line[k]!=' ' && line[k]!='.' ){/*this loop returns the words forward to given key value*/
				ascii=(int)(line[k])+key;
				if(ascii>'z') ascii-=26;
				line[k]=(char)ascii;
			}

		}	
		reverse_line(line,line_lenght);/*this function reverses given line*/
		fprintf(fl,"%s",line);/*this writes line to open line*/
	}


	fclose(fl);
}	
