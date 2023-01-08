#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<dos.h>
#include<dir.h>
void librarian(void);
void student(void);
void studentfile(void);
void issuebook(void);
void issuebookscience(void);
void issuebookliterature(void);

void bookshelf(void);
void bookshelfscience(void);
void bookshelfliterature(void);

void viewbook(void);
void viewbookscience(void);
void viewbookliterature(void);
void youissued(void);
void returnbook(void);
void returnbookscience(void);
void returnbookliterature(void);

void SetColor(int ForgC);
int main()
{
	char choice;
	while(1)
	{		
		system("cls");
		printf("\n--------------------------------------------------------Welcome---------------------------------------------------------\n\n");
		printf("1.Login as a librarian\n");
		printf("2.Login as a student\n");
		printf("0.Exit\n");
		printf("Enter choice:");
		fflush(stdin);
		choice=getche();
		switch(choice)
		{
			case '1':
				librarian();
			break;
			case '2':
			    student();
			break;	
			case '0':
				exit(1);
			break;
		}
	}
}
void librarian(void)
{
	char yes='Y',choice;
	while(1)
	{
		system("cls");
		printf("1.View students and the books issued to them\n");
    	printf("2.Issue book to a student\n");
		printf("0.exit\n");
    	printf("Enter choice:");
    	fflush(stdin);
    	choice=getche();
		switch(choice)
    	{
    		case '1':
    			studentfile();
    		    break;
			case '2':
			    issuebook();
				break;
			case '0':
			    return;	 	
		}
	}
}
void student(void)
{
	while(1)
	{
		char yes='Y',choice;
		system("cls");
		printf("1.View bookshelfs\n");
    	printf("2.View the books available\n");
    	printf("3.View the books issued to you\n");
    	printf("4.Return book\n");
		printf("0.exit\n");
    	printf("Enter choice:");
    	fflush(stdin);
    	choice=getche();
    	switch(choice)
    	{
    		case '1':
    			bookshelf();
    		break;
    		case '2':
			    viewbook();
			break;
			case '3':
			    youissued();
			break;
			case '4':
				returnbook();
			break;
			case '0':
			    return;		
		}
	}
}
void studentfile(void)
{
    system("cls");
	char yes='Y',empty[50]="                                 ";
	FILE *fs;
	long int size;
	fs=fopen("studentfile.dat","rb");
    if(fs==NULL)
    {
    	printf("file doesnot exist");
    	exit(0);
    }
    struct student
    {
    	char name[50];
    	char id[50];
    	char date[50];
    	char kitab[50];
    };
    struct student s;
    size=sizeof(s);
    rewind(fs);
	printf("Name    Student ID    Date issued    Book name\n\n");
	while(fread(&s,size,1,fs)==1)
    {
		printf("%s %s %s %s\n",s.name,s.id,s.date,s.kitab);
    }
    printf("\nReturn to the menu(Y/N)");
	yes=getche();
    if(yes!='Y')
    exit(1);
}
void issuebook(void)
{
	char choice;
	while(1)
	{
		system("cls");
    	printf("1.Issue science book\n");
    	printf("2.Issue literature book\n");
    	
    	printf("0.Exit\n");
		printf("Enter choice:");
		fflush(stdin);
    	choice=getche();
    	switch(choice)
    	{
    		case '1':
    			issuebookscience();
    		break;
			case '2':
			    issuebookliterature();
			break;    
			
			case'0':
			    return;			
		}
	}
}
void issuebookscience(void)
{
	char *save,empty[50]=" ";
	FILE *fs,*fb,*ft;
	long int position;
	char yes='Y',n[50],*p[50];
	int x,i,z,len,j;
	fs=fopen("studentfile.dat","rb+");
    if(fs==NULL)
	{
        printf("File not available");
        exit(1);
	}
	struct student
	{
		char name[50];
		char id[50];
		char date[50];
		char kitab[50];
	};
    struct student s;
	fb=fopen("bookfilescience.dat","rb+");
	if(fb==NULL)
	{
		printf("File doesnot exist");
		exit(1);
	}
	struct book
	{
		char name[50];
		char author[50];
	};
	struct book b;
	struct book *ptr;
	ptr=&b;
	int choice;
	long int recsize=sizeof(s);
	while(yes=='Y')
	{
		fs=fopen("studentfile.dat","rb+");
		system("cls");
		fseek(fs,0,SEEK_END);
		printf("Tell the name\n");
	    scanf("%s",&s.name);
	    printf("Tell the student ID\n");
	    scanf("%s",&s.id);
	    printf("Enter the date\n");
	    scanf("%s",&s.date);
	    printf("Enter name of book student want to issue\n");
		fflush(stdin);
		gets(s.kitab);
		save=s.kitab;
		rewind(fb);
		z=0;
		while(fread(&b,sizeof(b),1,fb)==1)
	    {
	    	z=z+1;
			x=0;
			if(strcmp(b.name,save)==0)
	    	{   
			    x=x+1;
				fwrite(&s,recsize,1,fs);
				fclose(fs);
				printf("Successfully issued");
				break;
	        }
		}
		if(x==0||z==0)
		{
			printf("Book is already issued OR Invalid input\n");
			printf("\nAnother student approaches(Y/N)");
    		fflush(stdin);
    		yes=getche();
			break;
		} 
		
    	ft=fopen("temp.dat","wb");
    	rewind(fb);
    	while(fread(&b,sizeof(b),1,fb)==1)
		{
		    if(strcmp(b.name,save)!=0)
    		{				 
				fwrite(&b,sizeof(b),1,ft);
    		}
    	}
    	fclose(fb);
    	fclose(ft);    		
		position=ftell(fb);
		printf("%d",position);
		position=ftell(ft);
		printf("%d",position);
		remove("bookfilescience.dat");
        rename("temp.dat","bookfilescience.dat");    
		fb=fopen("bookfilescience.dat","rb+");
    	printf("\nAnother student approaches(Y/N)");
    	fflush(stdin);
    	yes=getche();			
    }
}
void issuebookliterature(void)
{
	char *save,empty[50]=" ";
	FILE *fs,*fb,*ft;
	long int position;
	char yes='Y',n[50],*p[50];
	int x,i,z,len,j;
	fs=fopen("studentfile.dat","rb+");
    if(fs==NULL)
	{
        printf("File not available");
        exit(1);
	}
	struct student
	{
		char name[50];
		char id[50];
		char date[50];
		char kitab[50];
	};
    struct student s;
	fb=fopen("bookfileliterature.dat","rb+");
	if(fb==NULL)
	{
		printf("File does not exist");
		exit(1);
	}
	struct book
	{
		char name[50];
		char author[50];
	};
	struct book b;
	struct book *ptr;
	ptr=&b;
	int choice;
	long int recsize=sizeof(s);
	while(yes=='Y')
	{
		fs=fopen("studentfile.dat","rb+");
		system("cls");
		fseek(fs,0,SEEK_END);
		printf("Tell the name\n");
	    scanf("%s",&s.name);
	    printf("Tell the student ID\n");
	    scanf("%s",&s.id);
	    printf("Enter the date\n");
	    scanf("%s",&s.date);
	    printf("Enter name of book student want to issue\n");
		fflush(stdin);
		gets(s.kitab);
		save=s.kitab;
		rewind(fb);
		z=0;
		while(fread(&b,sizeof(b),1,fb)==1)
	    {
	    	z=z+1;
			x=0;
			if(strcmp(b.name,save)==0)
	    	{   
			    x=x+1;
				fwrite(&s,recsize,1,fs);
				fclose(fs);
				printf("Successfully issued");
				break;
	        }
		}
		if(x==0||z==0)
		{
			printf("Book is already issued OR Invalid input\n");
			printf("\nAnother student approaches(Y/N)");
    		fflush(stdin);
    		yes=getche();
			break;
		} 
		
    	ft=fopen("temp1.dat","wb");
    	rewind(fb);
    	while(fread(&b,sizeof(b),1,fb)==1)
		{
		    if(strcmp(b.name,save)!=0)
    		{				 
				fwrite(&b,sizeof(b),1,ft);
    		}
    	}
    	fclose(fb);
    	fclose(ft);    		
		position=ftell(fb);
		printf("%d",position);
		position=ftell(ft);
		printf("%d",position);
		remove("bookfileliterature.dat");
        rename("temp1.dat","bookfileliterature.dat");    
		fb=fopen("bookfileliterature.dat","rb+");
    	printf("\nAnother student approaches(Y/N)");
    	fflush(stdin);
    	yes=getche();			
    }

}

void bookshelf(void)
{
	char choice;
	while(1)
	{
		system("cls");
    	printf("1.View science bookshelf\n");
    	printf("2.View literature bookshelf\n");
    
    	printf("0.Exit\n");
		printf("Enter choice:");
		fflush(stdin);
    	choice=getche();
    	switch(choice)
    	{
    		case '1':
    			bookshelfscience();
    		break;
			case '2':
			    bookshelfliterature();
			break;    
			
			case'0':
			    return;			
		}
	}
}
void bookshelfscience(void)
{
	FILE *fp,*ft;
	fp=fopen("bookfilescience.dat","rb+");
	char *book1="The brief history of time",*book2="Philosophiae Naturalis Principia Mathematica",*book3="Feynman lectures on physics",*book4="Cosmos";
	char *book5="Calculus",*book6="On the origin of species",*book7="lost in math",*book8="Quantum Mechanics";
	char *book9="Classical Mechanics",*book10="Electromagnetism",*book11="Fermat's Last Theorem",*book12="Flatland";
	char *book13="A Mathematician's Apology",*book14="Humble Pi",*book15="Journey through Genius",*book16="How to Solve It";
	char *book17="How to Lie with Statistics",*book18="The Number Devil",*book19="Infinite Powers",*book20="The Music of the Primes";
	char *book21="Zero",*book22="The history of pi",*book23="The math book",*book24="Principles of mathematical analysis";
	char *book25="The road to reality",*book26="Algebra Essentials",*book27="The man who knew infinity",*book28="Proofs and refutations";
	char *book29="Math without numbers",*book30="In Search of Schrodinger's Cat",*book31="Inorganic chemistry",*book32="Organic chemistry";	
	int x;
	long int size;
	if(fp==NULL)
	{
		printf("File doesnot exist");
		exit(1);
	}
	struct book
	{
		char name[50];
		char author[50];
	};
	struct book b;	
	int i,j;
	char card=21;
	char a=186;
	char kitab=177;
	char code1[5]="S-01",code2[5]="S-02",code3[5]="S-03",code4[5]="S-04";
	char code5[5]="S-05",code6[5]="S-06",code7[5]="S-07",code8[5]="S-08";
    char code9[5]="S-09",code10[5]="S-10",code11[5]="S-11",code12[5]="S-12";
    char code13[5]="S-13",code14[5]="S-14",code15[5]="S-15",code16[5]="S-16";
    char code17[5]="S-17",code18[5]="S-18",code19[5]="S-19",code20[5]="S-20";    
    char code21[5]="S-21",code22[5]="S-22",code23[5]="S-23",code24[5]="S-24";
	char code25[5]="S-25",code26[5]="S-26",code27[5]="S-27",code28[5]="S-28";
	char code29[5]="S-29",code30[5]="S-30",code31[5]="S-31",code32[5]="S-32";
	printf("\n");
	printf("\t\t\t\t%c Science",card);
	printf("\n\n");
	for(i=1;i<=8;i++)
	{
		SetColor(15);
		printf("       \t%c",a);
		for(j=1;j<=35;j++)
		{
			SetColor(15);
			if(j<35)
			printf("_");
			else
			{
				printf("%c",a);
		    }
			if(i==1&&j==4)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book1,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
    	    	printf("_");
		    }
			if(i==1&&j==5)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book1,b.name)==0)
	            	{
	            		SetColor(6);
						printf("%s",code1);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
    	    	printf("____");
		    }
			if(i==1&&j==12)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book2,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("_");
		    }
			if(i==1&&j==13)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book2,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%s",code2);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("____");
		    }
		    if(i==1&&j==20)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book3,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("_");
		    }
			if(i==1&&j==21)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book3,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%s",code3);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("____");
		    }
			if(i==1&&j==28)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book4,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("_");
		    }
			if(i==1&&j==29)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book4,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%s",code4);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("____");
		    }
			if(i==2&&j==4)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book5,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
    	    	printf("_");
		    }
			if(i==2&&j==5)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book5,b.name)==0)
	            	{
	            		SetColor(6);
						printf("%s",code5);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
    	    	printf("____");
		    }
			if(i==2&&j==12)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book6,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("_");
		    }
			if(i==2&&j==13)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book6,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%s",code6);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("____");
		    }
		    if(i==2&&j==20)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book7,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("_");
		    }
			if(i==2&&j==21)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book7,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%s",code7);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("____");
		    }
			if(i==2&&j==28)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book8,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("_");
		    }
			if(i==2&&j==29)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book8,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%s",code8);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("____");
		    }
			if(i==3&&j==4)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book9,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
    	    	printf("_");
		    }
			if(i==3&&j==5)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book9,b.name)==0)
	            	{
	            		SetColor(6);
						printf("%s",code9);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
    	    	printf("____");
		    }
			if(i==3&&j==12)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book10,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("_");
		    }
			if(i==3&&j==13)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book10,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%s",code10);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("____");
		    }
		    if(i==3&&j==20)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book11,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("_");
		    }
			if(i==3&&j==21)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book11,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%s",code11);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("____");
		    }
			if(i==3&&j==28)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book12,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("_");
		    }
			if(i==3&&j==29)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book12,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%s",code12);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("____");
		    }
			if(i==4&&j==4)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book13,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
    	    	printf("_");
		    }
			if(i==4&&j==5)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book13,b.name)==0)
	            	{
	            		SetColor(6);
						printf("%s",code13);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
    	    	printf("____");
		    }
			if(i==4&&j==12)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book14,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("_");
		    }
			if(i==4&&j==13)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book14,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%s",code14);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("____");
		    }
		    if(i==4&&j==20)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book15,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("_");
		    }
			if(i==4&&j==21)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book15,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%s",code15);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("____");
		    }
			if(i==4&&j==28)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book16,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("_");
		    }
			if(i==4&&j==29)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book16,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%s",code16);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("____");
		    }
			if(i==5&&j==4)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book17,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
    	    	printf("_");
		    }
			if(i==5&&j==5)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book17,b.name)==0)
	            	{
	            		SetColor(6);
						printf("%s",code17);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
    	    	printf("____");
		    }
			if(i==5&&j==12)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book18,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("_");
		    }
			if(i==5&&j==13)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book18,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%s",code18);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("____");
		    }
		    if(i==5&&j==20)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book19,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("_");
		    }
			if(i==5&&j==21)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book19,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%s",code19);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("____");
		    }
			if(i==5&&j==28)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book20,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("_");
		    }
			if(i==5&&j==29)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book20,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%s",code20);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("____");
		    }
			if(i==6&&j==4)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book21,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
    	    	printf("_");
		    }
			if(i==6&&j==5)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book21,b.name)==0)
	            	{
	            		SetColor(6);
						printf("%s",code21);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
    	    	printf("____");
		    }
			if(i==6&&j==12)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book22,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("_");
		    }
			if(i==6&&j==13)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book22,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%s",code22);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("____");
		    }
		    if(i==6&&j==20)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book23,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("_");
		    }
			if(i==6&&j==21)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book23,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%s",code23);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("____");
		    }
			if(i==6&&j==28)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book24,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("_");
		    }
			if(i==6&&j==29)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book24,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%s",code24);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("____");
		    }
			if(i==7&&j==4)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book25,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
    	    	printf("_");
		    }
			if(i==7&&j==5)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book25,b.name)==0)
	            	{
	            		SetColor(6);
						printf("%s",code25);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
    	    	printf("____");
		    }
			if(i==7&&j==12)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book26,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("_");
		    }
			if(i==7&&j==13)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book26,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%s",code26);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("____");
		    }
		    if(i==7&&j==20)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book27,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("_");
		    }
			if(i==7&&j==21)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book27,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%s",code27);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("____");
		    }
			if(i==7&&j==28)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book28,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("_");
		    }
			if(i==7&&j==29)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book28,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%s",code28);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("____");
		    }
			if(i==8&&j==4)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book29,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
    	    	printf("_");
		    }
			if(i==8&&j==5)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book29,b.name)==0)
	            	{
	            		SetColor(6);
						printf("%s",code29);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
    	    	printf("____");
		    }
			if(i==8&&j==12)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book30,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("_");
		    }
			if(i==8&&j==13)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book30,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%s",code26);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("____");
		    }
		    if(i==8&&j==20)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book31,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("_");
		    }
			if(i==8&&j==21)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book31,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%s",code31);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("____");
		    }
			if(i==8&&j==28)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book32,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("_");
		    }
			if(i==8&&j==29)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book32,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%s",code32);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("____");
		    }																										    								    
		}		
	SetColor(15);
	printf("\n\t%c\t\t\t\t\t\t       %c\n",a,a);
	}
	char yes='Y';
	printf("\nReturn to the menu(Y/N)");
	fflush(stdin);
	yes=getche();
	if(yes!='Y')
	exit(1);
}
void bookshelfliterature(void)
{
	FILE *fp,*ft;
	fp=fopen("bookfileliterature.dat","rb+");
	char *book1="Medea",*book2="The Odyssey",*book3="Antigone",*book4="Tom Jones";
	char *book5="As You Like It",*book6="Julius Caesar",*book7="King Lear",*book8="A Midsummer Night's Dream";
	char *book9="The Merchant of Venice",*book10="Othello",*book11="The Tempest",*book12="Candide";
	char *book13="Emma",*book14="Mansfield Park",*book15="Pride and Prejudice",*book16="Jane Eyre";
	char *book17="Wuthering Heights",*book18="The Awakening",*book19="he Red Badge of Courage",*book20="Bleak House";
	char *book21="David Copperfield",*book22="Great Expectations",*book23="Oliver Twist",*book24="A Tale of Two Cities";
	char *book25="Crime and Punishment",*book26="Madame Bovary",*book27="Jude the Obscure",*book28="The Mayor of Casterbridge";
	char *book29="The Little Foxes",*book30="Tess of the d'Urbervilles",*book31="The Scarlet Letter",*book32="A Doll's House";
	int x;
	long int size;
	if(fp==NULL)
	{
		printf("File does not exist");
		exit(1);
	}
	struct book
	{
		char name[50];
		char author[50];
	};
	struct book b;	
	int i,j;
	char card=21;
	char a=186;
	char kitab=177;
	char code1[5]="L-01",code2[5]="L-02",code3[5]="L-03",code4[5]="L-04";
	char code5[5]="L-05",code6[5]="L-06",code7[5]="L-07",code8[5]="L-08";
    char code9[5]="L-09",code10[5]="L-10",code11[5]="L-11",code12[5]="L-12";
    char code13[5]="L-13",code14[5]="L-14",code15[5]="L-15",code16[5]="L-16";
    char code17[5]="L-17",code18[5]="L-18",code19[5]="L-19",code20[5]="L-20";    
    char code21[5]="L-21",code22[5]="L-22",code23[5]="L-23",code24[5]="L-24";
	char code25[5]="L-25",code26[5]="L-26",code27[5]="L-27",code28[5]="L-28";
	char code29[5]="L-29",code30[5]="L-30",code31[5]="L-31",code32[5]="L-32";
	printf("\n");
	printf("\t\t\t\t%c Literature",card);
	printf("\n\n");
	for(i=1;i<=8;i++)
	{
		SetColor(15);
		printf("       \t%c",a);
		for(j=1;j<=35;j++)
		{
			SetColor(15);
			if(j<35)
			printf("_");
			else
			{
				printf("%c",a);
		    }
			if(i==1&&j==4)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book1,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
    	    	printf("_");
		    }
			if(i==1&&j==5)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book1,b.name)==0)
	            	{
	            		SetColor(6);
						printf("%s",code1);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
    	    	printf("____");
		    }
			if(i==1&&j==12)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book2,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("_");
		    }
			if(i==1&&j==13)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book2,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%s",code2);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("____");
		    }
		    if(i==1&&j==20)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book3,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("_");
		    }
			if(i==1&&j==21)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book3,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%s",code3);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("____");
		    }
			if(i==1&&j==28)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book4,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("_");
		    }
			if(i==1&&j==29)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book4,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%s",code4);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("____");
		    }
			if(i==2&&j==4)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book5,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
    	    	printf("_");
		    }
			if(i==2&&j==5)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book5,b.name)==0)
	            	{
	            		SetColor(6);
						printf("%s",code5);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
    	    	printf("____");
		    }
			if(i==2&&j==12)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book6,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("_");
		    }
			if(i==2&&j==13)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book6,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%s",code6);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("____");
		    }
		    if(i==2&&j==20)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book7,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("_");
		    }
			if(i==2&&j==21)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book7,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%s",code7);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("____");
		    }
			if(i==2&&j==28)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book8,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("_");
		    }
			if(i==2&&j==29)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book8,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%s",code8);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("____");
		    }
			if(i==3&&j==4)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book9,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
    	    	printf("_");
		    }
			if(i==3&&j==5)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book9,b.name)==0)
	            	{
	            		SetColor(6);
						printf("%s",code9);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
    	    	printf("____");
		    }
			if(i==3&&j==12)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book10,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("_");
		    }
			if(i==3&&j==13)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book10,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%s",code10);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("____");
		    }
		    if(i==3&&j==20)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book11,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("_");
		    }
			if(i==3&&j==21)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book11,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%s",code11);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("____");
		    }
			if(i==3&&j==28)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book12,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("_");
		    }
			if(i==3&&j==29)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book12,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%s",code12);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("____");
		    }
			if(i==4&&j==4)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book13,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
    	    	printf("_");
		    }
			if(i==4&&j==5)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book13,b.name)==0)
	            	{
	            		SetColor(6);
						printf("%s",code13);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
    	    	printf("____");
		    }
			if(i==4&&j==12)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book14,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("_");
		    }
			if(i==4&&j==13)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book14,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%s",code14);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("____");
		    }
		    if(i==4&&j==20)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book15,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("_");
		    }
			if(i==4&&j==21)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book15,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%s",code15);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("____");
		    }
			if(i==4&&j==28)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book16,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("_");
		    }
			if(i==4&&j==29)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book16,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%s",code16);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("____");
		    }
			if(i==5&&j==4)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book17,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
    	    	printf("_");
		    }
			if(i==5&&j==5)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book17,b.name)==0)
	            	{
	            		SetColor(6);
						printf("%s",code17);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
    	    	printf("____");
		    }
			if(i==5&&j==12)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book18,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("_");
		    }
			if(i==5&&j==13)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book18,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%s",code18);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("____");
		    }
		    if(i==5&&j==20)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book19,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("_");
		    }
			if(i==5&&j==21)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book19,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%s",code19);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("____");
		    }
			if(i==5&&j==28)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book20,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("_");
		    }
			if(i==5&&j==29)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book20,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%s",code20);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("____");
		    }
			if(i==6&&j==4)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book21,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
    	    	printf("_");
		    }
			if(i==6&&j==5)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book21,b.name)==0)
	            	{
	            		SetColor(6);
						printf("%s",code21);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
    	    	printf("____");
		    }
			if(i==6&&j==12)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book22,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("_");
		    }
			if(i==6&&j==13)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book22,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%s",code22);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("____");
		    }
		    if(i==6&&j==20)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book23,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("_");
		    }
			if(i==6&&j==21)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book23,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%s",code23);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("____");
		    }
			if(i==6&&j==28)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book24,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("_");
		    }
			if(i==6&&j==29)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book24,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%s",code24);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("____");
		    }
			if(i==7&&j==4)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book25,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
    	    	printf("_");
		    }
			if(i==7&&j==5)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book25,b.name)==0)
	            	{
	            		SetColor(6);
						printf("%s",code25);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
    	    	printf("____");
		    }
			if(i==7&&j==12)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book26,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("_");
		    }
			if(i==7&&j==13)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book26,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%s",code26);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("____");
		    }
		    if(i==7&&j==20)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book27,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("_");
		    }
			if(i==7&&j==21)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book27,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%s",code27);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("____");
		    }
			if(i==7&&j==28)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book28,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("_");
		    }
			if(i==7&&j==29)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book28,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%s",code28);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("____");
		    }
			if(i==8&&j==4)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book29,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
    	    	printf("_");
		    }
			if(i==8&&j==5)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book29,b.name)==0)
	            	{
	            		SetColor(6);
						printf("%s",code29);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
    	    	printf("____");
		    }
			if(i==8&&j==12)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book30,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("_");
		    }
			if(i==8&&j==13)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book30,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%s",code26);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("____");
		    }
		    if(i==8&&j==20)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book31,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("_");
		    }
			if(i==8&&j==21)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book31,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%s",code31);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("____");
		    }
			if(i==8&&j==28)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book32,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%c",kitab);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("_");
		    }
			if(i==8&&j==29)
			{
                rewind(fp);
    	    	while(fread(&b,sizeof(b),1,fp)==1)
            	{
            		x=0;
					if(strcmp(book32,b.name)==0)
	            	{
	            		SetColor(6);
	        			printf("%s",code32);
                		x=x+1;
						break;
	        		}				
		    	}
		    	if(x==0)
		    	printf("____");
		    }																										    								    
		}		
	SetColor(15);
	printf("\n\t%c\t\t\t\t\t\t       %c\n",a,a);
	}
	char yes='Y';
	printf("\nReturn to the menu(Y/N)");
	fflush(stdin);
	yes=getche();
	if(yes!='Y')
	exit(1);

}

void viewbook(void)
{
	char choice;
	while(1)
	{
		system("cls");
    	printf("1.View science book\n");
    	printf("2.View literature book\n");	
    	printf("0.Exit\n");
		printf("Enter choice:");
		fflush(stdin);
    	choice=getche();
    	switch(choice)
    	{
    		case '1':
    			viewbookscience();
    		break;
			case '2':
			    viewbookliterature();
			break;    
			
			case'0':
			    return;			
		}
	}	
}
void viewbookscience()
{
	system("cls");
	FILE *fp,*ft;
	fp=fopen("bookfilescience.dat","rb+");
	long int size;
	if(fp==NULL)
	{
		printf("File doesnot exist");
		exit(1);
	}
	struct book
	{
		char name[50];
		char author[50];
	};
	struct book b;
	size=sizeof(b);
	rewind(fp);
	printf("Bookname-Author\n\n");
	while(fread(&b,size,1,fp)==1)
	{
		printf("%s-%s\n",b.name,b.author);
	}
	fclose(fp);
	char yes='Y';
	printf("\nReturn to the menu(Y/N)");
	fflush(stdin);
	yes=getche();
	if(yes!='Y')
	exit(1);	
}
void viewbookliterature()
{
	system("cls");
	FILE *fl;
	fl=fopen("bookfileliterature.dat","rb");
	long int size;
	if(fl==NULL)
	{
		printf("File doesnot exist");
		exit(1);
	}
	struct book
	{
		char name[50];
		char author[50];
	};
	struct book b;
	size=sizeof(b);
	rewind(fl);
	printf("Bookname-Author\n\n");
	while(fread(&b,size,1,fl)==1)
	{
		printf("%s-%s\n",b.name,b.author);
	}
	fclose(fl);
	char yes='Y';
	printf("\nReturn to the menu(Y/N)");
	fflush(stdin);
	yes=getche();
	if(yes!='Y')
	exit(1);	
}
void youissued(void)
{
    system("cls");
	char string[50],yes='Y';
    int x,i;
	printf("Enter your name: ");
    scanf("%s",&string);
    FILE *fs;
    fs=fopen("studentfile.dat","rb+");
    if(fs==NULL)
    {
    	printf("File doesnot exist");
    	exit(1);
	}
	struct student
	{
    	char name[50];
    	char id[50];
    	char date[50];
    	char kitab[50];
	};
	struct student s;
	x=0;
	i=0;
	printf("\nName    Student ID    Date issued    Book name\n\n");
	rewind(fs);
	while(fread(&s,sizeof(s),1,fs)==1)
	{
		if(strcmp(string,s.name)==0)
		{
			x=x+1;
			printf("%s %s %s %s\n",s.name,s.id,s.date,s.kitab);
		}		
	}
	if(x==0)
	{
		printf("\nInvalid name entered");
	}
	printf("\n\nReturn to the menu(Y/N)");
	fflush(stdin);
	yes=getche();
	if(yes!='Y')
	exit(0);
}
void returnbook(void)
{
	char choice;
	while(1)
	{
		system("cls");
    	printf("1.Return science book\n");
    	printf("2.Return literature book\n");
    	
    	printf("0.Exit\n");
		printf("Enter choice:");
		fflush(stdin);
    	choice=getche();
    	switch(choice)
    	{
    		case '1':
    			returnbookscience();
    		break;
			case '2':
			    returnbookliterature();
			break;    
			
			case'0':
			    return;			
		}
	}
}
void returnbookscience(void)
{
	FILE *fp,*ft;
	long int position; 
	int i;
	int choice;
	char *book1="The brief history of time",*book2="Philosophiae Naturalis Principia Mathematica",*book3="Feynman lectures on physics",*book4="Cosmos";
	char *book5="Calculus",*book6="On the origin of species",*book7="lost in math",*book8="Quantum Mechanics";
	char *book9="Classical Mechanics",*book10="Electromagnetism",*book11="Fermat's Last Theorem",*book12="Flatland";
	char *book13="A Mathematician's Apology",*book14="Humble Pi",*book15="Journey through Genius",*book16="How to Solve It";
	char *book17="How to Lie with Statistics",*book18="The Number Devil",*book19="Infinite Powers",*book20="The Music of the Primes";
	char *book21="Zero",*book22="The history of pi",*book23="The math book",*book24="Principles of mathematical analysis";
	char *book25="The road to reality",*book26="Algebra Essentials",*book27="The man who knew infinity",*book28="Proofs and refutations";
	char *book29="Math without numbers",*book30="In Search of Schrodinger's Cat",*book31="Inorganic chemistry",*book32="Organic chemistry";
	char yes='Y';
	fp=fopen("bookfilescience.dat","rb+");
	if(fp==NULL)
	{
		printf("file does not exist");
		exit(1);
	}
	struct book
	{
		char name[50];
		char author[50];
	};
	struct book b;
	struct book b1={"The brief history of time","Stephan Hawking"};
	struct book b2={"Philosophiae Naturalis Principia Mathematica","Issac Newton"};
	struct book b3={"Feynman lectures on physics","Ricchard Feynman"};
	struct book b4={"Cosmos","Carl Sagan"};
	struct book b5={"Calculus","Gilbert Strang"};
	struct book b6={"On the origin of species","Charles Darwin"	};
	struct book b7={"lost in math","Sabine Hossenfelder"};
	struct book b8={"Quantum Mechanics","Paul Dirac"};
	struct book b9={"Classical Mechanics","Tom Kibble"};
	struct book b10={"Electromagnetism","Tom Kibble"};
	struct book b11={"Fermat's Last Theorem","Simon Singh"};
	struct book b12={"Flatland","Edwin Abbott"};
	struct book b13={"A Mathematician's Apology","GH Hardy"};
	struct book b14={"Humble Pi","Matt Parker"};
	struct book b15={"Journey through Genius","William Dunham"};
	struct book b16={"How to Solve It","George Polya"};
	struct book b17={"How to Lie with Statistics","Darrell Huff"};
	struct book b18={"The Number Devil","Hans Magnus"};
	struct book b19={"Infinite Powers","Steven"};
	struct book b20={"The Music of the Primes","Marcus"};
	struct book b21={"Zero","CS"};
	struct book b22={"The history of pi","PB"};
	struct book b23={"The math book","AN"};
	struct book b24={"Principles of mathematical analysis","WR"};
	struct book b25={"The road to reality","RP"};
	struct book b26={"Algebra Essentials","CM"};
	struct book b27={"The man who knew infinity","RK"};
	struct book b28={"Proofs and refutations","IL"};
	struct book b29={"Math without numbers","MB"};
	struct book b30={"In Search of Schrodinger's Cat","John Gribbin"};
	struct book b31={"Inorganic chemistry","TW"};
	struct book b32={"Organic chemistry","TW"};
	system("cls");
	printf("1.Return The brief history of time-Stephan Hawking\n\n");
	printf("2.Return Philosophiae Naturalis Principia Mathematica-Issac Newton\n\n");
	printf("3.Return Feynman lectures on physics-Richard Feynman\n\n");
	printf("4.Return Cosmos-Carl Sagan\n\n");
	printf("5.Return Calculus-Gilberd Strang\n\n");
	printf("6.Return On the origin of species-Charles Darwin\n\n");
	printf("7.Return lost in math-SH\n\n");
	printf("8.Return Quantum Mechanics-Paul Dirac\n\n");
    printf("9.Return Classical Mechanics-Tom Kibble\n\n");
    printf("10.Return Electromagnetism-Tom Kibble\n\n");
	printf("11.Return Fermat's Last Theorem-Simon Singh\n\n");
	printf("12.Return Flatland-Edwin Abbott\n\n");
	printf("13.Return A Mathematician's Apology-GH Hardy\n\n");
	printf("14.Return Humble Pi-Matt Parker\n\n");
	printf("15.Return Journey through Genius-William Dunham\n\n");
	printf("16.Return How to Solve It-George Polya\n\n");
	printf("17.Return How to Lie with Statistics-Darrell Huff\n\n");
	printf("18.Return The Number Devil-Hans Magnus\n\n");
	printf("19.Return Infinite Powers: Steven\n\n");
	printf("20.Return The Music of the Primes-Marcus\n\n");
	printf("21.Return Zero-CS\n\n");
	printf("22.Return The history of pi-PB\n\n");
	printf("23.Return The math book-AN\n\n");
	printf("24.Return Principles of mathematical analysis-WR\n\n");
	printf("25.Return The road to reality-RP\n\n");
	printf("26.Return Algebra Essentials-CM\n\n");
	printf("27.Return The man who knew infinity-RK\n\n");
	printf("28.Return Proofs and refutations-IL\n\n");
	printf("29.Return Math without numbers-MB\n\n");
	printf("30.Return In Search of Schrodinger's Cat-John Gribbin\n\n");
	printf("31.Return Inorganic chemistry-TW\n\n");
	printf("32.Return Organic chemistry-TW\n\n");
	printf("0.Exit\n\n"); 
	while(yes=='Y')
	{
	printf("Enter choice:");
	scanf("%d",&choice);
	switch(choice)
    {
    case 1:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book1,b.name)==0)
	    	{
	    		printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		i=i+1;
        		break;
			}
		}
		if(i>0)
		break;
		if(strcmp(b1.name,book1)==0)
    	{
    		fseek(fp,0,SEEK_END);
			fwrite(&b1,sizeof(b1),1,fp);
			printf("Process Completed");
    	}
    	else
    	{
    		printf("\nInvalid Input");
    	}
        break;
    case 2:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book2,b.name)==0)
	    	{
	    		printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		i=i+1;
        		break;
			}
		}
		if(i>0)
		break;
		if(strcmp(b2.name,book2)==0)
    	{
    		fseek(fp,0,SEEK_END);
			fwrite(&b2,sizeof(b2),1,fp);
			printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 3:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book3,b.name)==0)
	    	{
	    		printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		i=i+1;
        		break;
			}
		}
		if(i>0)
		break;
		if(strcmp(b3.name,book3)==0)
    	{
			fseek(fp,0,SEEK_END);
			fwrite(&b3,sizeof(b3),1,fp);
			printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;        
	case 4:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book4,b.name)==0)
	    	{
	    		printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		i=i+1;
        		break;
			}
		}
		if(i>0)
		break;
		if(strcmp(b4.name,book4)==0)
        {
	        fseek(fp,0,SEEK_END);
	    	fwrite(&b4,sizeof(b4),1,fp);
			printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
    	break;
    case 5:
    	rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book5,b.name)==0)
	    	{
	    		printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		i=i+1;
        		break;
			}
		}
		if(i>0)
		break;	    
		if(strcmp(b5.name,book5)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b5,sizeof(b5),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;																																																																																				
    case 6:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book6,b.name)==0)
	    	{
	    		printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		i=i+1;
			}
		}
		if(i>0)
		break;	    
		if(strcmp(b6.name,book6)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b6,sizeof(b6),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 7:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book7,b.name)==0)
	    	{
	    		printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		i=i+1;
        		break;
			}
		}
		if(i>0)
		break;
		if(strcmp(b7.name,book7)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b7,sizeof(b7),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 8:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book8,b.name)==0)
	    	{
	    		printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		i=i+1;
        		break;
			}
		}
		if(i>0)
		break;	    
		if(strcmp(b8.name,book8)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b8,sizeof(b8),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 9:
 	    rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book9,b.name)==0)
	    	{
	    		printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		i=i+1;
        		break;
			}
		}
		if(i>0)
		break;
		if(strcmp(b9.name,book9)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b9,sizeof(b9),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 10:
	    rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book10,b.name)==0)
	    	{
	    		printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		i=i+1;
        		break;
			}
		}
		if(i>0)
		break;
		if(strcmp(b10.name,book10)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b10,sizeof(b10),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 11:
	    rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book11,b.name)==0)
	    	{
	    		printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		i=i+1;
        		break;
			}
		}
		if(i>0)
		break;
		if(strcmp(b11.name,book11)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b11,sizeof(b11),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 12:
	    rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book12,b.name)==0)
	    	{
	    		printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		i=i+1;
        		break;
			}
		}
		if(i>0)
		break;
		if(strcmp(b12.name,book12)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b12,sizeof(b12),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 13:
    	rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book13,b.name)==0)
	    	{
	    		printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		i=i+1;
				break;
			}
		}
		if(i>0)
		break;
		if(strcmp(b13.name,book13)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b13,sizeof(b13),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 14:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book14,b.name)==0)
	    	{
	    		printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		i=i+1;
        		break;
			}
		}
		if(i>0)
		break;		
		if(strcmp(b14.name,book14)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b14,sizeof(b14),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 15:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book15,b.name)==0)
	    	{
	    		printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		i=i+1;
        		break;
			}
		}
		if(i>0)
		break;	    
		if(strcmp(b15.name,book15)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b15,sizeof(b15),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 16:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book16,b.name)==0)
	    	{
	    		printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		i=i+1;
        		break;
			}
		}
		if(i>0)
		break;	    
		if(strcmp(b16.name,book16)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b16,sizeof(b16),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 17:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book17,b.name)==0)
	    	{
	    		printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		i=i+1;
        		break;
			}
		}
		if(i>0)
		break;	    
		if(strcmp(b17.name,book17)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b17,sizeof(b17),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 18:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book18,b.name)==0)
	    	{
	    		printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		i=i+1;
        		break;
			}
		}
		if(i>0)
		break;	    
		if(strcmp(b18.name,book18)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b18,sizeof(b18),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 19:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book19,b.name)==0)
	    	{
	    		printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		i=i+1;
        		break;
			}
		}
		if(i>0)
		break;	    
		if(strcmp(b19.name,book19)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b19,sizeof(b19),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 20:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book20,b.name)==0)
	    	{
	    		printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		i=i+1;
        		break;
			}
		}
		if(i>0)
		break;	    
		if(strcmp(b20.name,book20)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b20,sizeof(b20),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 21:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book21,b.name)==0)
	    	{
	    		printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		i=i+1;
        		break;
			}
		}
		if(i>0)
		break;	    
		if(strcmp(b21.name,book21)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b21,sizeof(b21),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 22:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book22,b.name)==0)
	    	{
	    		printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		i=i+1;
        		break;
			}
		}
		if(i>0)
		break;	    
		if(strcmp(b22.name,book22)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b22,sizeof(b22),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 23:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book23,b.name)==0)
	    	{
	    		printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		i=i+1;
        		break;
			}
		}
		if(i>0)
		break;	    
		if(strcmp(b23.name,book23)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b23,sizeof(b23),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 24:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book24,b.name)==0)
	    	{
	    		i=i+1;
				printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		break;
			}
		}
		if(i>0)
		break;	    
		if(strcmp(b24.name,book24)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b24,sizeof(b24),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 25:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book25,b.name)==0)
	    	{
	    		printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		i=i+1;
        		break;
			}
		}
		if(i>0)
		break;	    
		if(strcmp(b25.name,book25)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b25,sizeof(b25),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 26:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
			if(strcmp(book26,b.name)==0)
	    	{
	    		i=i+1;
				printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		break;
			}
		}
		if(i>0)
		break;	    
		if(strcmp(b26.name,book26)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b26,sizeof(b26),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 27:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book27,b.name)==0)
	    	{
	    		i=i+1;
				printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		break;
			}
		}
		if(i>0)
		break;	    
		if(strcmp(b27.name,book27)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b27,sizeof(b27),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 28:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book28,b.name)==0)
	    	{
	    		i=i+1;
				printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		break;
			}
		}
		if(i>0)
		break;	    
		if(strcmp(b28.name,book28)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b28,sizeof(b28),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 29:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book29,b.name)==0)
	    	{
	    		i=i+1;
				printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		break;
			}
		}	    
		if(i>0)
		break;
		if(strcmp(b29.name,book29)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b29,sizeof(b29),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 30:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book30,b.name)==0)
	    	{
	    		i=i+1;
				printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		break;
			}
		}
		if(i>0)
		break;
		if(strcmp(b30.name,book30)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b30,sizeof(b30),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 31:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book31,b.name)==0)
	    	{
	    		i=i+1;
				printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		break;
			}
		}
		if(i>0)
		break;	    
		if(strcmp(b31.name,book31)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b31,sizeof(b31),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 32:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book32,b.name)==0)
	    	{
	    		i=i+1;
				printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
	    		break;
			}
		}
		if(i>0)
		break; 
		if(strcmp(b32.name,book32)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b32,sizeof(b32),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
	case 0:
	    return;																																																																																																																																																																																																																						
	}	
	printf("\nDo you want to return another book(Y/N):");
	fflush(stdin);
	yes=getche();
	printf("\n");
    }    	
    fclose(fp);
}
void returnbookliterature(void)
{
	FILE *fp,*ft;
	long int position; 
	int i;
	int choice;
	char *book1="Medea",*book2="The Odyssey",*book3="Antigone",*book4="Tom Jones";
	char *book5="As You Like It",*book6="Julius Caesar",*book7="King Lear",*book8="A Midsummer Night's Dream";
	char *book9="The Merchant of Venice",*book10="Othello",*book11="The Tempest",*book12="Candide";
	char *book13="Emma",*book14="Mansfield Park",*book15="Pride and Prejudice",*book16="Jane Eyre";
	char *book17="Wuthering Heights",*book18="The Awakening",*book19="he Red Badge of Courage",*book20="Bleak House";
	char *book21="David Copperfield",*book22="Great Expectations",*book23="Oliver Twist",*book24="A Tale of Two Cities";
	char *book25="Crime and Punishment",*book26="Madame Bovary",*book27="Jude the Obscure",*book28="The Mayor of Casterbridge";
	char *book29="The Little Foxes",*book30="Tess of the d'Urbervilles",*book31="The Scarlet Letter",*book32="A Doll's House";
	char yes='Y';
	fp=fopen("bookfileliterature.dat","rb+");
	if(fp==NULL)
	{
		printf("file does not exist");
		exit(1);
	}
	struct book
	{
		char name[50];
		char author[50];
	};
	struct book b;
	struct book b1={"Medea","Euripides"};
	struct book b2={"The Odyssey","Homer"};
	struct book b3={"Antigone","Sophocles"};
	struct book b4={"Tom Jones","Henry Fielding"};
	struct book b5={"As You Like It","Shakespeare"};
	struct book b6={"Julius Caesar","Shakespeare"};
	struct book b7={"King Lear","Shakespeare"};
	struct book b8={"A Midsummer Night's Dream","Shakespeare"};
	struct book b9={"The Merchant of Venice","Shakespeare"};
	struct book b10={"Othello","Shakespeare"};
	struct book b11={"The Tempest","Shakespeare"};
	struct book b12={"Candide","Voltaire"};
	struct book b13={"Emma","Jane Austen"};
	struct book b14={"Mansfield Park","Jane Austen"};
	struct book b15={"Pride and Prejudice","Jane Austen"};
	struct book b16={"Jane Eyre","Charlotte Bronte"};
	struct book b17={"Wuthering Heights","Emily Bronte"};
	struct book b18={"The Awakening","Kate Chopin"};
	struct book b19={"The Red Badge of Courage","Stephen Crane"};
	struct book b20={"Bleak House","Charles Dickens"};
	struct book b21={"David Copperfield","Charles Dickens"};
	struct book b22={"Great Expectations","Charles Dickens"};
	struct book b23={"Oliver Twist","Charles Dickens"};
	struct book b24={"A Tale of Two Cities","Charles Dickens"};
	struct book b25={"Crime and Punishment","Fyodor Dostoyevsky"};
	struct book b26={"Madame Bovary","Gustave Flaubert"};
	struct book b27={"Jude the Obscure","Thomas Hardy"};
	struct book b28={"The Mayor of Casterbridge","Thomas Hardy"};
	struct book b29={"The Little Foxes","Lillian Hellman"};
	struct book b30={"Tess of the d'Urbervilles","Thomas Hardy"};
	struct book b31={"The Scarlet Letter","Nathaniel Hawthorne"};
	struct book b32={"A Doll's House","Henrik Ibsen"};
	system("cls");
	printf("1.Return Medea-Euripides\n\n");
	printf("2.Return The Odyssey-Homer\n\n");
	printf("3.Return Antigone-Sophocles\n\n");
	printf("4.Return Tom Jones-Henry Fielding\n\n");
	printf("5.Return As You Like It-Shakespeare\n\n");
	printf("6.Return Julius Caesar-Shakespeare\n\n");
	printf("7.Return King Lear-Shakespeare\n\n");
	printf("8.Return A Midsummer Night's Dream-Shakespeare\n\n");
    printf("9.Return The Merchant of Venice-Shakespeare\n\n");
    printf("10.Return Othello-Shakespeare\n\n");
	printf("11.Return The Tempest-Shakespeare\n\n");
	printf("12.Return Candide-Voltaire\n\n");
	printf("13.Return Emma-Jane Austen\n\n");
	printf("14.Return Mansfield Park-Jane Austen \n\n");
	printf("15.Return Pride and Prejudice-Jane Austen \n\n");
	printf("16.Return Jane Eyre-Charlotte Bronte\n\n");
	printf("17.Return Wuthering Heights-Emily Bronte  \n\n");
	printf("18.Return The Awakening-Kate Chopin \n\n");
	printf("19.Return The Red Badge of Courage-Stephen Crane  \n\n");
	printf("20.Return Bleak House-Charles Dickens  \n\n");
	printf("21.Return David Copperfield-Charles Dickens  \n\n");
	printf("22.Return Great Expectations-Charles Dickens  \n\n");
	printf("23.Return Oliver Twist-Charles Dickens  \n\n");
	printf("24.Return A Tale of Two Cities-Charles Dickens \n\n");
	printf("25.Return  Crime and Punishment-Fyodor Dostoyevsky\n\n");
	printf("26.Return Madame Bovary-Gustave Flaubert\n\n");
	printf("27.Return Jude the Obscure-Thomas Hardy\n\n");
	printf("28.Return The Mayor of Casterbridge-Thomas Hardy\n\n");
	printf("29.Return The Little Foxes-Lillian Hellman\n\n");
	printf("30.Return Tess of the d'Urbervilles-Thomas Hardy\n\n");
	printf("31.Return The Scarlet Letter-Nathaniel Hawthorne\n\n");
	printf("32.Return A Doll's House-Henrik Ibsen\n\n");
	printf("0.Exit\n\n"); 
	while(yes=='Y')
	{
	printf("Enter choice:");
	scanf("%d",&choice);
	switch(choice)
    {
    case 1:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book1,b.name)==0)
	    	{
	    		printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		i=i+1;
        		break;
			}
		}
		if(i>0)
		break;
		if(strcmp(b1.name,book1)==0)
    	{
    		fseek(fp,0,SEEK_END);
			fwrite(&b1,sizeof(b1),1,fp);
			printf("Process Completed");
    	}
    	else
    	{
    		printf("\nInvalid Input");
    	}
        break;
    case 2:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book2,b.name)==0)
	    	{
	    		printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		i=i+1;
        		break;
			}
		}
		if(i>0)
		break;
		if(strcmp(b2.name,book2)==0)
    	{
    		fseek(fp,0,SEEK_END);
			fwrite(&b2,sizeof(b2),1,fp);
			printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 3:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book3,b.name)==0)
	    	{
	    		printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		i=i+1;
        		break;
			}
		}
		if(i>0)
		break;
		if(strcmp(b3.name,book3)==0)
    	{
			fseek(fp,0,SEEK_END);
			fwrite(&b3,sizeof(b3),1,fp);
			printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;        
	case 4:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book4,b.name)==0)
	    	{
	    		printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		i=i+1;
        		break;
			}
		}
		if(i>0)
		break;
		if(strcmp(b4.name,book4)==0)
        {
	        fseek(fp,0,SEEK_END);
	    	fwrite(&b4,sizeof(b4),1,fp);
			printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
    	break;
    case 5:
    	rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book5,b.name)==0)
	    	{
	    		printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		i=i+1;
        		break;
			}
		}
		if(i>0)
		break;	    
		if(strcmp(b5.name,book5)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b5,sizeof(b5),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;																																																																																				
    case 6:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book6,b.name)==0)
	    	{
	    		printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		i=i+1;
			}
		}
		if(i>0)
		break;	    
		if(strcmp(b6.name,book6)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b6,sizeof(b6),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 7:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book7,b.name)==0)
	    	{
	    		printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		i=i+1;
        		break;
			}
		}
		if(i>0)
		break;
		if(strcmp(b7.name,book7)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b7,sizeof(b7),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 8:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book8,b.name)==0)
	    	{
	    		printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		i=i+1;
        		break;
			}
		}
		if(i>0)
		break;	    
		if(strcmp(b8.name,book8)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b8,sizeof(b8),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 9:
 	    rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book9,b.name)==0)
	    	{
	    		printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		i=i+1;
        		break;
			}
		}
		if(i>0)
		break;
		if(strcmp(b9.name,book9)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b9,sizeof(b9),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 10:
	    rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book10,b.name)==0)
	    	{
	    		printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		i=i+1;
        		break;
			}
		}
		if(i>0)
		break;
		if(strcmp(b10.name,book10)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b10,sizeof(b10),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 11:
	    rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book11,b.name)==0)
	    	{
	    		printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		i=i+1;
        		break;
			}
		}
		if(i>0)
		break;
		if(strcmp(b11.name,book11)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b11,sizeof(b11),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 12:
	    rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book12,b.name)==0)
	    	{
	    		printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		i=i+1;
        		break;
			}
		}
		if(i>0)
		break;
		if(strcmp(b12.name,book12)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b12,sizeof(b12),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 13:
    	rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book13,b.name)==0)
	    	{
	    		printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		i=i+1;
				break;
			}
		}
		if(i>0)
		break;
		if(strcmp(b13.name,book13)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b13,sizeof(b13),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 14:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book14,b.name)==0)
	    	{
	    		printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		i=i+1;
        		break;
			}
		}
		if(i>0)
		break;		
		if(strcmp(b14.name,book14)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b14,sizeof(b14),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 15:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book15,b.name)==0)
	    	{
	    		printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		i=i+1;
        		break;
			}
		}
		if(i>0)
		break;	    
		if(strcmp(b15.name,book15)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b15,sizeof(b15),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 16:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book16,b.name)==0)
	    	{
	    		printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		i=i+1;
        		break;
			}
		}
		if(i>0)
		break;	    
		if(strcmp(b16.name,book16)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b16,sizeof(b16),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 17:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book17,b.name)==0)
	    	{
	    		printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		i=i+1;
        		break;
			}
		}
		if(i>0)
		break;	    
		if(strcmp(b17.name,book17)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b17,sizeof(b17),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 18:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book18,b.name)==0)
	    	{
	    		printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		i=i+1;
        		break;
			}
		}
		if(i>0)
		break;	    
		if(strcmp(b18.name,book18)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b18,sizeof(b18),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 19:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book19,b.name)==0)
	    	{
	    		printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		i=i+1;
        		break;
			}
		}
		if(i>0)
		break;	    
		if(strcmp(b19.name,book19)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b19,sizeof(b19),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 20:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book20,b.name)==0)
	    	{
	    		printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		i=i+1;
        		break;
			}
		}
		if(i>0)
		break;	    
		if(strcmp(b20.name,book20)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b20,sizeof(b20),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 21:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book21,b.name)==0)
	    	{
	    		printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		i=i+1;
        		break;
			}
		}
		if(i>0)
		break;	    
		if(strcmp(b21.name,book21)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b21,sizeof(b21),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 22:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book22,b.name)==0)
	    	{
	    		printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		i=i+1;
        		break;
			}
		}
		if(i>0)
		break;	    
		if(strcmp(b22.name,book22)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b22,sizeof(b22),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 23:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book23,b.name)==0)
	    	{
	    		printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		i=i+1;
        		break;
			}
		}
		if(i>0)
		break;	    
		if(strcmp(b23.name,book23)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b23,sizeof(b23),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 24:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book24,b.name)==0)
	    	{
	    		i=i+1;
				printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		break;
			}
		}
		if(i>0)
		break;	    
		if(strcmp(b24.name,book24)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b24,sizeof(b24),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 25:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book25,b.name)==0)
	    	{
	    		printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		i=i+1;
        		break;
			}
		}
		if(i>0)
		break;	    
		if(strcmp(b25.name,book25)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b25,sizeof(b25),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 26:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
			if(strcmp(book26,b.name)==0)
	    	{
	    		i=i+1;
				printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		break;
			}
		}
		if(i>0)
		break;	    
		if(strcmp(b26.name,book26)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b26,sizeof(b26),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 27:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book27,b.name)==0)
	    	{
	    		i=i+1;
				printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		break;
			}
		}
		if(i>0)
		break;	    
		if(strcmp(b27.name,book27)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b27,sizeof(b27),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 28:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book28,b.name)==0)
	    	{
	    		i=i+1;
				printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		break;
			}
		}
		if(i>0)
		break;	    
		if(strcmp(b28.name,book28)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b28,sizeof(b28),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 29:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book29,b.name)==0)
	    	{
	    		i=i+1;
				printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		break;
			}
		}	    
		if(i>0)
		break;
		if(strcmp(b29.name,book29)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b29,sizeof(b29),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 30:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book30,b.name)==0)
	    	{
	    		i=i+1;
				printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		break;
			}
		}
		if(i>0)
		break;
		if(strcmp(b30.name,book30)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b30,sizeof(b30),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 31:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book31,b.name)==0)
	    	{
	    		i=i+1;
				printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
        		break;
			}
		}
		if(i>0)
		break;	    
		if(strcmp(b31.name,book31)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b31,sizeof(b31),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
    case 32:
		rewind(fp);
		i=0;
		while(fread(&b,sizeof(b),1,fp)==1)
    	{
    		if(strcmp(book32,b.name)==0)
	    	{
	    		i=i+1;
				printf("%s-%s\n",b.name,b.author);
	    		printf("Already exists");
	    		break;
			}
		}
		if(i>0)
		break; 
		if(strcmp(b32.name,book32)==0)
    	{
    		fseek(fp,0,SEEK_END);
    		fwrite(&b32,sizeof(b32),1,fp);
    		printf("Process completed");
    	}
    	else
    	{
    		printf("Invalid Input");
    	}
		break;
	case 0:
	    return;																																																																																																																																																																																																																						
	}	
	printf("\nDo you want to return another book(Y/N):");
	fflush(stdin);
	yes=getche();
	printf("\n");
    }    	
    fclose(fp);
}



void SetColor(int ForgC)
 {
 WORD wColor;

  HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbi;
 if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
 {
      wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
      SetConsoleTextAttribute(hStdOut, wColor);
 }
 return;
}
