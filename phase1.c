#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <dirent.h>

/*-------------------------------------------------------------------------------\
| Title: EPTE (Easy professional text editor)                                    |
+--------------------------------------------------------------------------------+
| Repository link in Github:                                                     |                                                                       
| https://github.com/FundamentalOfProgramming-SUT-2022/project-hashemian1382     |
+--------------------------------------------------------------------------------+
|  AUTHOR :   Ali Hashemian                                                      |
+--------------------------------------------------------------------------------|
| Version: 0.5.0     Date of last revision: 2023-1-23                            |
+--------------------------------------------------------------------------------+
| DESCRIPTION:                                                                   |
|        This program is designed as the final project                           | 
|        of the Fundamental of Programming course of SUT.                        |
|        This program is actually a simulation of Vim.                           |
|        I named it EPTE, which stands for Easy professional text editor :)      | 
|        For more information, read the project's readme,                        |
|        which is accessible on the project's GitHub page.                       |                                                        |
|                                                                                |
\-------------------------------------------------------------------------------*/


struct texts
{
    int line;
    char name[50];
    char address[100];
    char content[1000][200];
};
char commands[14][100]={"createfile --file","insertstr --file","cat",
                        "removestr","copystr","cutstr","paststr","find","replace",
                        "grep","undo","auto-indent","compare","tree"};
char address_taghti_shode[100][100];
char clipboard[200000];



struct texts * struct_saz(){
    struct texts * text = (struct texts *) malloc(sizeof(struct texts));
    return (text); 
}
int payan_yab(char string[], char cs[]){
    int l1=strlen(string);
    int l2=strlen(cs);
    int i,j,t=-1;
    for (i = 0; i < l1; i++)
    {
        if (string[i]==cs[0])
        {
            for (j = 0; j < l2; j++)
            {
                if (string[i+j]!=cs[j]){
                    t=-1;
                    break;
                }
                t=i+j;
            }
            if (t!=-1)
            {
                return(t);
            }            
        }        
    }
    return(t);    
}
int start_yab(char string[], char cs[]){
    int l1=strlen(string);
    int l2=strlen(cs);
    int i,j,t=-1;
    for (i = 0; i < l1; i++)
    {
        if (string[i]==cs[0])
        {
            t=i;
            for (j = 0; j < l2; j++)
            {
                if (string[i+j]!=cs[j]){
                    t=-1;
                    break;
                }
            }
            if (t!=-1)
            {
                return(t);
            }            
        }        
    }
    return(t);    
}
void str_to_str(char a[],char b[],int x, int y){
    int t=0;
    for (int i = x; i <= y; i++)
    {
        a[t]=b[i];
        t=t+1;
    } 
    a[t]='\0';   
}
int first_ch(char string[],char ch){
    int t=-1; //not exist
    int l=strlen(string);
    for (int i = 0; i < l; i++)
    {
        if (string[i]==ch)
        {
            t=i;
            return(t);
        }        
    }
    return(t);    
}
int last_ch(char string[], char ch){
    int t=-1; //not exist
    int l=strlen(string);
    for (int i = l-1; i > -1; i--)
    {
        if (string[i]==ch)
        {
            t=i;
            return(t);
        }        
    }
    return(t);    
}
int nom_ch(char string[], char ch, int n){
    int t=-1; //not exist
    int l=strlen(string);
    int tedad=0;
    for (int i = 0; i < l; i++)
    {
        if (string[i]==ch)
        {
            tedad++;                
        }
        if (tedad>=n)
        {
            t=i;
            break;
        }                
    }
    return(t);       
}
int check_e2s(char s1[],char s2[]){  
    int l,i;
    int l1=strlen(s1);
    int l2=strlen(s2);
    if (l2>l1){
        return(0);
    }
    for ( i = 0; i < l2; i++)
    {
        if (s1[i]!=s2[i])
        {
            return(0);
        }
    }
    return(1); 
}
int tashkis_dorost_baz_shodan_file(char path[]) {
    FILE * file;
    file = fopen(path, "r");
    if (file == NULL)
    {
        printf("\nUnable to open file.\n");
        printf("Please check if file exists and you have read privilege.\n");
        return(-1);
    }
    else
        return(1);
}
void jodasaz_address(char string[],int n,int x,int y){
    for (int i = x; i <= y; i++)
    {
    address_taghti_shode[n][i-x]=string[i];
    }           
}
int tafkik_address(char address[]){
    int l=strlen(address);
    int t=0;
    int slash[l];
    for (int i = 0; i < l ; i++)
    {
        if (address[i]=='/')
        {
            slash[t]=i;
            t=t+1;
        }
    }
    jodasaz_address(address,0,0,slash[0]-1);
    for (int i = 1; i <= t-1; i++)
    {
        jodasaz_address(address,i,slash[i-1]+1,slash[i]-1);
    }
    jodasaz_address(address,t,slash[t-1]+1,l-1);
    return(t);      
}
int convet_to_num(char string[]){
    int l=strlen(string);
    int t=1;
    int num=0;
    if (string[0]!="-")
    {
        for (int i = l-1; i >= 0; i--)
        {
            num=num+(((int)string[i]-48)*t);
            t=t*10;
        }
    }
    else{
        for (int i = l-1; i > 0; i--)
        {
            num=num+(((int)string[i]-48)*t);
            t=t*10;
        }
        t=t*-1;
    }
    
    return(num);
    
}
int tedad_char_line(struct texts* text,int line){
    FILE * file;
    char path[100];
    strcpy(path,text->address);
    file = fopen(path, "r");
    char ch;
    int characters=0, lines=1;

    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == '\n' || ch == '\0'){
            if (lines==line)
            {
                return(characters-1);
            }
            else{
                lines++;
                characters=0;
            }
        }
        characters++;
    }
    fclose(file);
}
int get_file_content(char filename[],struct texts* text){
    int MAX_LEN=1000;
    FILE *file;
    file = fopen(filename, "r"); 
    int characters=0,lines = 1;
    char ch;     
    while((ch = fgetc(file))!=EOF) {
        if (ch=='\0' || ch=='\n')
        {
            text->content[lines][characters]='\n';
            lines++;
            characters=0;
        }
        else{
            text->content[lines][characters]=ch;
            characters++;
        }
        
    }
    text->line=lines; 
    strcpy(text->address,filename);
    fclose(file);
}
void change_one_char(struct texts* text, int line, int char_num, char ch){
    int i;
    if ((text->line)<line)
    {
        text->line=line;
    }    
    if (char_num>=tedad_char_line(text,line))
    {
        for ( i = tedad_char_line(text,line); i < char_num; i++)
        {
            if (text->content[line][i]=='\n' || text->content[line][i]==NULL || text->content[line][i]=='\0')
            {
                text->content[line][i]=' ';
            }
        }    
        text->content[line][char_num]=ch;
    }
    text->content[line][char_num]=ch;
}
void overwriting(char filename[],struct texts* text){
    int MAX_LEN=1000;
    FILE *file;
    file = fopen(filename, "w"); 
    int line = 1;
    int i,j;
    for (i = 1; i <= text->line; i++)
    {
        for (j = 0; j < 200 && text->content[i][j]!='\n' && text->content[i][j]!='\0'; j++)
        {
            putc(text->content[i][j], file);
        }
        putc('\n', file);        
    }    
    fclose(file);      
}
void file_backup(char file_name[]){
    char filename[strlen(file_name)];
    if (file_name[0]=='/')
    {
        str_to_str(filename,file_name,1,strlen(file_name)-1);
    }
    else{
        str_to_str(filename,file_name,0,strlen(file_name)-1);
    }
    
    FILE *fptr1, *fptr2;
    int l=strlen(filename);
    char name[l];
    char folder[l];
    char address[l];
    str_to_str(name,filename,last_ch(filename,'/')+1,l-1);
    str_to_str(folder,filename,0,last_ch(filename,'/'));
    char c,b_file_name[100]="b_";
    str_to_str(address,folder,0,strlen(folder));
    strcat(b_file_name,name);
    strcat(address,b_file_name);
    fptr1 = fopen(filename, "r");
    fptr2 = fopen(address, "w");
    c = fgetc(fptr1);
    while (c!= EOF){
        putc(c,fptr2);
        c = fgetc(fptr1);
    } 
}
int pr_create_file(char string[]){
    int l=strlen(string);
    char file1[l],file[l],folder[l],name[l];
    int f=payan_yab(string,"createfile --file");
    str_to_str(file1,string,f+1,l-1);
    if (first_ch(file1,'"')!=-1 && last_ch(file1,'"')!=-1)
    {
        str_to_str(file,file1,first_ch(file1,'"')+1,last_ch(file1,'"')-1);
    }
    else if (first_ch(file1,' ')!=-1 && last_ch(file1,' ')!=-1){
        str_to_str(file,file1,first_ch(file1,' ')+1,l-1);
    }
    str_to_str(folder,file,0,last_ch(file,'/')-1);
    str_to_str(name,file,last_ch(file,'/')+1,l-1);
    createfile(folder,name);
}
void createfile(char folder_names[],char file_name[]){
    printf("folder_names=%s\n",folder_names);
    printf("file_name=%s\n",file_name);
    int t= tafkik_address(folder_names);
    char address[150]="root";
    mkdir(address);
    for (int i = 2; i <= t; i++)
    {
    strcat(address,"/");
    strcat(address,address_taghti_shode[i]);
    printf("address=%s\n",address);
    mkdir(address);
    }
    strcat(address,"/");
    strcat(address,file_name);
    FILE *fp;
    fp = fopen (address, "r");
    if (fp==NULL){
        fp = fopen (address, "w");
        fclose (fp);
    }
    else{
        printf("This file named: %s ,has already been created.\n",address);
        fclose (fp);
    }
}
int pr_insert(char string[]){
    int l=strlen(string),i;
    printf("l=%d\n",l);
    char file[l],file1[l];
    char str[l],str1[l];
    char pos[l],pos1[l];
    char num1[l],num2[l];
    int f1,s1,p1,f2,s2,p2;
    f1=start_yab(string,"--file");
    f2=payan_yab(string,"--file");
    s1=start_yab(string,"--str");
    s2=payan_yab(string,"--str");
    p1=start_yab(string,"--pos");
    p2=payan_yab(string,"--pos");  

    str_to_str(file1,string,f2+1,s1-1);
    str_to_str(str1,string,s2+1,p1-1);
    str_to_str(pos1,string,p2+1,l-1);

    if (first_ch(file1,'"')!=-1 && last_ch(file1,'"')!=-1)
    {
        str_to_str(file,file1,first_ch(file1,'"')+1,last_ch(file1,'"')-1);
    }
    else if (first_ch(file1,' ')!=-1 && last_ch(file1,' ')!=-1){
        str_to_str(file,file1,first_ch(file1,' ')+1,last_ch(file1,' ')-1);
    }

    if (first_ch(str1,'"')!=-1 && last_ch(str1,'"')!=-1)
    {
        str_to_str(str,str1,first_ch(str1,'"')+1,last_ch(str1,'"')-1);
    }
    else if (first_ch(str1,' ')!=-1 && last_ch(str1,' ')!=-1){
        str_to_str(str,str1,first_ch(str1,' ')+1,last_ch(str1,' ')-1);
    }
    
    if (first_ch(pos1,'"')!=-1 && last_ch(pos1,'"')!=-1)
    {
        str_to_str(pos,pos1,first_ch(pos1,'"')+1,l-1);
    }
    else if (first_ch(pos1,' ')!=-1 && last_ch(pos1,' ')!=-1){
        str_to_str(pos,pos1,first_ch(pos1,' ')+1,l-1);
    }

    str_to_str(num1,pos,0,first_ch(pos,':')-1);
    str_to_str(num2,pos,first_ch(pos,':')+1,l-1);
    char filename[strlen(file)];
    str_to_str(filename,file,1,strlen(file));
    printf("%s\n%s\n%s\n%s\n",file,str,num1,num2);
    insert(filename,convet_to_num(num1),convet_to_num(num2),str);
}
void insert(char filename[], int line, int char_num, char string[]){
    printf("%s %d %d %s\n",filename,line,char_num, string);
    struct texts * text= struct_saz();
    get_file_content(filename,text);
    file_backup(filename);
    int l=strlen(string);
    char_num-=1;
    for (int i = 0; i < l; i++)
    {
        char_num++;        
        line=line+((char_num)/200);
        if (string[i]=='\n' || string[i]=='\0')
        {
            line=line+1;
            char_num=0;
            if (i<l-1)
            {
                change_one_char(text,line,(char_num)%200,string[i+1]);
                i++;
            }
            else{
                change_one_char(text,line,(char_num)%200,string[i]);
            }        
        }
    }
    overwriting(filename,text); 
}
void cat(char filename[]){
    FILE *fptr;
    fptr = fopen(filename, "r");
    char c = fgetc(fptr);
    while (c != EOF)
    {
        printf ("%c", c);
        c = fgetc(fptr);
    }
    fclose(fptr);
}
void line_swap(struct texts* text, int line1, int line2){ //line1 to line2
    int i;
    int l=strlen(text->content[line1]);
    for ( i = 0; i < l; i++)
    {
        text->content[line2][i]=text->content[line1][i];
        text->content[line1][i]=NULL;
    }    
}
void del_b(struct texts* text, int line, int ch){
    int i;
    for ( i = ch; i < 200; i++)
    {
        text->content[line][i-1]=text->content[line][i];
    }        
}
void del_bl(struct texts* text, int line){
    int i;
    int n=tedad_char_line(text,line-1)-1;
    for ( i = 0; i < 200; i++)
    {
        text->content[line-1][n+i]=text->content[line][i];
        text->content[line][i]=NULL;
    }    
}
void del_f(struct texts* text, int line, int ch){
    int i;
    for ( i = ch+2; i < 200; i++)
    {
        text->content[line][i-1]=text->content[line][i];
    }        
}
void del_fl(struct texts* text, int line){
    int i;
    int n=tedad_char_line(text,line-1)-1;
    for ( i = 0; i < 200; i++)
    {
        text->content[line-1][n+i]=text->content[line][i];
        text->content[line][i]=NULL;
    }    
}
void remove_text(char filename[],int line_n, int char_n, int size, int mode){
    struct texts * text=struct_saz();
    int i;
    get_file_content(filename,text);
    file_backup(filename);
    if (mode==1){
        for ( i = 0; i < size; i++)
        {
            del_b(text,line_n,char_n);
            char_n--;
            if (char_n==0)
            {
                line_n--;
                char_n=tedad_char_line(text,line_n)-1;
                i++;
                del_bl(text,line_n+1);
                line_swap(text,line_n+2,line_n+1);
                text->line--;
            }            
        }        
    }
    else if (mode==2){
        for ( i = 0; i < size; i++)
        {
            del_f(text,line_n,char_n);
            if (char_n+i==(tedad_char_line(text,line_n)))
            {
                i++;
                del_fl(text,line_n+1);
                line_swap(text,line_n+2,line_n+1);
                text->line--;
            }            
        }        
    }
    overwriting(filename,text);
}
void copy(char filename[],int line_n, int char_n, int size, int mode){
    struct texts * text=struct_saz();
    int i;
    get_file_content("ali.txt",text);
    file_backup("ali.txt");
    if (mode==2)
    {
        for ( i = 0; i < size; i++)
        {
            if (char_n+i+1<=tedad_char_line(text,line_n))
            {
                clipboard[i]=text->content[line_n][char_n+i+1];
            }
            else{
                line_n++;
                char_n=-i-1;
                clipboard[i]=text->content[line_n][char_n+i+1];
            }
            
        }
        
    }
    if (mode==1)
    {
        for ( i = 0; i < size; i++)
        {
            if (char_n-i-1>=0)
            {
                clipboard[i]=text->content[line_n][char_n-i-1];
            }
            else{
                line_n--;
                char_n=(tedad_char_line(text,line_n))+i;
                clipboard[i]=text->content[line_n][char_n-i-1];
            }            
        }        
    }
    clipboard[size]='\0';       
    overwriting("ali.txt",text);
}
void cut(char filename[],int line_n, int char_n, int size, int mode){
    copy(filename, line_n, char_n, size, mode);
    remove_text(filename, line_n, char_n, size, mode);
}
void past(char filename[],int line_n, int char_n){
    insert(filename,line_n,char_n,clipboard);
}
void undo (char filename[]){
    FILE *fptr1, *fptr2;
    char c,b_file_name[100]="b_";
    strcat(b_file_name,filename);
    fptr1 = fopen(b_file_name, "r");
    fptr2 = fopen(filename, "w");
    c = fgetc(fptr1);
    while (c!= EOF){
        putc(c,fptr2);
        c = fgetc(fptr1);
    } 
    
}
void compare(char filename1[],char filename2[]){
    int i;
    struct texts* text1=struct_saz();
    struct texts* text2=struct_saz();
    get_file_content(filename1,text1);
    get_file_content(filename2,text2);
    int l1=text1->line;
    int l2=text2->line;
    int min=(l1>l2)*l2+(l2>=l1)*l1;
    for ( i = 0; i < min; i++)
    {
        if (check_e2s(text1->content[i],text2->content[i])==0){
            printf("============ #<%d> ============\n",i);
            printf("%s",text1->content[i]);
            printf("%s",text2->content[i]);
        }
    }
    if (l1>l2)
    {
        printf("<<<<<<<<<<<< #%d - #%d <<<<<<<<<<<<\n",min,l1-1);
        for ( i = min; i < l1; i++)
        {
            printf("%s",text1->content[i]);
        }
    }
    if (l2>l1)
    {
        printf(">>>>>>>>>>>> #%d - #%d >>>>>>>>>>>>\n",min,l2-1);
        for ( i = min; i < l2; i++)
        {
            printf("%s",text2->content[i]);
        }
    }    
}
int check_wild(char *str1, char *str2) 
{ 
    if (*str1 != ' ' && *str2 == ' ')
    {
        return 0;
    }
    
    if (*str1 == '\0' && *str2 == '\0') 
        return 1; 
  
    if (*str1 == '*' && *(str1+1) != '\0' && *str2 == '\0') 
        return 0;

    if (*str1 == *str2) 
        return check_wild(str1+1, str2+1); 

    if (*str1 == '*') 
        return (check_wild(str1+1, str2) || check_wild(str1, str2+1)); 
    return 0; 
} 
int tafkik_spaces(char string[],int l,char jodashode[][l],int space[],int start[], int payan[]){
    int t=0,i;
    for ( i = 0; i < l; i++)
    {
        if (string[i]==' ')
        {
            space[t]=i;
            t++;
        }        
    }
    if (t!=0)
    {
        str_to_str(jodashode[0],string,0,space[0]-1);
        start[0]=0;
        payan[0]=space[0]-1;
        for ( i = 0; i < t-1; i++)
        {
            str_to_str(jodashode[i+1],string,space[i]+1,space[i+1]-1);
            start[i+1]=space[i]+1;
            payan[i+1]=space[i+1]-1;
            //printf("s=%d p=%d *** ",start[0],payan[0]);
        }
        str_to_str(jodashode[t],string,space[t-1]+1,l-1); 
        start[t]=space[t-1]+1;
        payan[t]=l-1;
        //printf("s=%d p=%d *** ",start[t],payan[t]);
    }
    else{
        str_to_str(jodashode[0],string,0,l-1);
        start[0]=0;
        payan[0]=l-1;
        //printf("s=%d p=%d *** ",start[0],payan[0]);
    }
    //printf("\n");

    return(t);       
}
int find_help(int A[],int B[],char string1[], char string2[],int space1[],int space2[],int start1[],int payan1[],int start2[],int payan2[]){
    int i,k,a=0,t=0;
    int l1=strlen(string1);
    int l2=strlen(string2);
    char joda1[l1][l1];
    char joda2[l2][l2];
    int t1= tafkik_spaces(string1,l1,joda1,space1,start1,payan1);
    int t2= tafkik_spaces(string2,l2,joda2,space2,start2,payan2);
    for ( i = 0; i <= t1; i++)
    {
        if (check_wild(joda2[0],joda1[i])==1)
        {
            a=1;
            for ( k = i; k < i+t2+1; k++)
            {
                if (check_wild(joda2[k-i],joda1[k])==0){
                    a=0;
                    break;
                }
            }
            if (a==1)
            {
                t++;
                A[t]=i;
            }
        }            
    }
    return (t);  
}
int find_ch(int n, int A[],int B[],char string1[], char string2[] ){
    int l1=strlen(string1);
    int l2=strlen(string2);
    int space1[l1];    
    int space2[l2];
    int start1[l1];
    int payan1[l1];
    int start2[l2];
    int payan2[l2];

    int t=find_help(A,B,string1,string2,space1,space2,start1,payan1,start2,payan2);
    if (t>=n){
        return(start1[A[n]]);
    }
    else{
        return(-1);
    }

}
int count_words(char string[],int f){
    int i,t=0;
    if (string[0]==' ')
    {
        for ( i = 0; i < f; i++)
        {
            if (string[i]==' ' && string[i+1]!=' ')
            {
                t++;
            }            
        }        
    }
    else{
        t++;
        for ( i = 1; i < f; i++)
        {
            if (string[i]==' ' && string[i-1]!=' ')
            {
                t++;
            }            
        }        
    }
    return(t);    
}
int count_c_line(char filename[],int line){
    int i;
    int l=0;
    struct texts * text= struct_saz();
    get_file_content(filename,text);
    for ( i = 1; i < line; i++)
    {
        l+=strlen(text->content[i]);
    }
    return(l);

}
int count_w_line(char filename[],int line){
    int i;
    int l=0;
    struct texts * text= struct_saz();
    get_file_content(filename,text);
    for ( i = 1; i < line; i++)
    {
        l+=count_words(text->content[i],200);
    }
    return(l);

}
int find_w(int n, int A[],int B[],char string1[], char string2[]){
    int x;
    int l1=strlen(string1);
    int l2=strlen(string2);
    int space1[l1];    
    int space2[l2];
    int start1[l1];
    int payan1[l1];
    int start2[l1];
    int payan2[l1];

    int t=find_help(A,B,string1,string2,space1,space2,start1,payan1,start2,payan2);

    if (t>=n){
        x=count_words(string1,start1[A[n]]);
        return(x);
    }
    else{
        return(-1);
    }

}
int find(char filename[],char string[], int mode, int n){
    int i,j,t,tt,k;
    struct texts * text= struct_saz();
    int l1=200;
    int l2=strlen(string);
    int space1[l1];    
    int space2[l2];
    int start1[l1];
    int payan1[l1];
    int start2[l2];
    int payan2[l2];
    int A[100],B[100];
    get_file_content(filename,text);
    if (mode==1)
    {
        t=0;
        for ( i = 1; i < 1000 && t<n; i++)
        {
            l1=strlen(text->content[i]);
            t+=find_help(A,B,text->content[i],string,space1,space2,start1,payan1,start2,payan2);
        }
        if (t<n)
        {
            printf("\nnot found!\n",t);
        }
        else{
            t=0;
            for ( j = 1; j < i-1 ; j++)
            {
                l1=strlen(text->content[j]);
                t+=find_help(A,B,text->content[j],string,space1,space2,start1,payan1,start2,payan2);
            }
            n=n-t;
            printf("start from the char=%d\n",find_ch(n,A,B,text->content[j],string)+count_c_line(filename,j));            
        }
        
        
    }
    if (mode==2)
    {
        t=0;
        for ( i = 1; i < 1000 && t<n; i++)
        {
            l1=strlen(text->content[i]);
            t+=find_help(A,B,text->content[i],string,space1,space2,start1,payan1,start2,payan2);
        }
        if (t<n)
        {
            printf("\nnot found!\n",t);
            return(-1);
        }
        else{
            t=0;
            for ( j = 1; j < i-1 ; j++)
            {
                l1=strlen(text->content[j]);
                t+=find_help(A,B,text->content[j],string,space1,space2,start1,payan1,start2,payan2);
            }
            n=n-t;
            printf("start from the word=%d\n",find_w(n,A,B,text->content[j],string)+count_w_line(filename,j));
            
        }
        
        
    }
    if (mode==3)
    {
        t=0;
        for ( i = 1; i < 1000; i++)
        {
            l1=strlen(text->content[i]);
            t+=find_help(A,B,text->content[i],string,space1,space2,start1,payan1,start2,payan2);
        }
        if (t==0)
        {
            printf("\nnot found!\n");
        }
        else{
            for ( k = 1; k <= t; k++)
            {
                n=k;
                tt=0;
                for ( i = 1; i < 1000 && tt<n; i++)
                {
                    l1=strlen(text->content[i]);
                    tt+=find_help(A,B,text->content[i],string,space1,space2,start1,payan1,start2,payan2);
                }
                tt=0;
                for ( j = 1; j < i-1 ; j++)
                {
                    l1=strlen(text->content[j]);
                    tt+=find_help(A,B,text->content[j],string,space1,space2,start1,payan1,start2,payan2);
                }
                n=n-tt;
                printf("%d",find_ch(n,A,B,text->content[j],string)+count_c_line(filename,j));
                if (k!=t)
                {
                    printf(",");
                }                
            }
            printf("\n");                
        }    
}
    if (mode==4)
    {
        t=0;
        for ( i = 1; i < 1000; i++)
        {
            l1=strlen(text->content[i]);
            t+=find_help(A,B,text->content[i],string,space1,space2,start1,payan1,start2,payan2);
        }
        if (t==0)
        {
            printf("\nnot found!\n");
        }
        else{
            for ( k = 1; k <= t; k++)
            {
                n=k;
                tt=0;
                for ( i = 1; i < 1000 && tt<n; i++)
                {
                    l1=strlen(text->content[i]);
                    tt+=find_help(A,B,text->content[i],string,space1,space2,start1,payan1,start2,payan2);
                }
                tt=0;
                for ( j = 1; j < i-1 ; j++)
                {
                    l1=strlen(text->content[j]);
                    tt+=find_help(A,B,text->content[j],string,space1,space2,start1,payan1,start2,payan2);
                }
                n=n-tt;
                printf("%d",find_w(n,A,B,text->content[j],string)+count_w_line(filename,j));
                if (k!=t)
                {
                    printf(",");
                }                
            }
            printf("\n");                
        }    
}
    if (mode==5){
    t=0;
    for ( i = 1; i < 1000; i++)
    {
        l1=strlen(text->content[i]);
        t+=find_help(A,B,text->content[i],string,space1,space2,start1,payan1,start2,payan2);
    }
    }
    else{
        printf("%d\n",t);
    }

}

int grep(char listnames[][30],char string[] ,int num, int mode){
    int i,j,t,k;
    struct texts * text[num];
    int l1=200;
    int l2=strlen(string);
    int space1[l1],space2[l2],start1[l1],payan1[l1],start2[l2],payan2[l2],A[100],B[100];

    for ( i = 0; i < num; i++)
    {
        text[i]= struct_saz();
        get_file_content(listnames[i],text[i]);
    }
    
    if (mode==1)
    {
        for ( i = 0; i < num; i++)
        {
            for ( j = 1; j <= text[i]->line; j++)
            {
                t=find_help(A,B,text[i]->content[j],string,space1,space2,start1,payan1,start2,payan2);
                if (t>0)
                {
                    printf("%s: %s",listnames[i],text[i]->content[j]);
                }        
            }
        }        
    }        
}

int raplace(char filename[], char str1[], char str2[], int mode, int num){

}

int replace_at(char filename[], char str1[], char str2[], int num){
    int i,j,t,k,n=num,x,y;
    struct texts * text=struct_saz();
    get_file_content(filename,text);
    int l1=strlen(str1);
    int l=200;
    int space1[l1],space2[l],start1[l1],payan1[l1],start2[l],payan2[l],A[100],B[100];
    t=0;
    for ( i = 0; i < 1000 && t<num; i++)
    {
        l=strlen(text->content[i+1]);
        t+=find_help(A,B,text->content[i+1],str1,space1,space2,start1,payan1,start2,payan2);
    }
    if (t<num)
    {
        return(-1);
    }    
    else{
        t=0;
        for ( j = 1; j < i ; j++)
        {
            l=strlen(text->content[j]);
            t+=find_help(A,B,text->content[j],str1,space1,space2,start1,payan1,start2,payan2);
        }
        find_help(A,B,text->content[i],str1,space1,space2,start1,payan1,start2,payan2);
        num=num-t;
        start1[A[num]]=find_ch(num,A,B,text->content[i],str1);
        x=start1[A[num]];
        y=payan1[A[num]];
        l=strlen(text->content[i]);
        char part1[l],part2[l],full[l];
        str_to_str(part1,text->content[i],0,x-1);
        str_to_str(part2,text->content[i],y+1,l-1);
        strcpy(text->content[i],part1);
        strcat(text->content[i],str2);
        strcat(text->content[i],part2);
        overwriting(filename,text);
    }


}

int replace_all(char filename[], char str1[], char str2[]){
    int i,j,t=0,k,x,y;
    struct texts * text= struct_saz();
    get_file_content(filename,text);
    int l1=strlen(str1);
    int l=200;
    int space1[l1],space2[l],start1[l1],payan1[l1],start2[l],payan2[l],A[100],B[100];
    for ( i = 1; i < 1000; i++)
    {
        t+=find_help(A,B,text->content[i],str1,space1,space2,start1,payan1,start2,payan2);
    }
    if (t==0)
    {
        return(-1);
    }
    int total=t;
    k=0;
    while (t!=0 && k<total)
    {
        replace_at(filename,str1,str2,1);
        k++;
        t=0;
        for ( i = 1; i < text->line; i++)
        {
        t+=find_help(A,B,text->content[i],str1,space1,space2,start1,payan1,start2,payan2);
        }
    }

}

int closing_pairs(char filename[]){
    int i;
    struct texts * text= struct_saz();
    get_file_content(filename,text);
    file_backup(filename);
    struct texts * temp= struct_saz();
    int l=strlen(text->content[1]);
    int tedad=1;
    while (tedad!=0)
    {
        tedad=0;
        for ( i = 1; i < l; i++)
        {
            if (text->content[1][i]=='{' || text->content[1][i]=='}')
            {
                if (text->content[1][i-1]==' ' || text->content[1][i+1]==' ')
                {
                    tedad++;
                }
                if(text->content[1][i-1]==' '){
                    del_b(text,1,i);
                }
                if(text->content[1][i+1]==' '){
                    del_f(text,1,i);
                }            
            }
        }
    }
    int first= first_ch(text->content[1],'{');
    int last= last_ch(text->content[1],'}');
    char parts[l][l];
    str_to_str(parts[1],text->content[1],0,first-1);
    str_to_str(parts[2],text->content[1],first+1,last-1);
    strcpy(text->content[1],parts[1]);
    if (parts[1][strlen(parts[1])]!=NULL)
    {
        strcat(text->content[1]," ");
    }    
    strcat(text->content[1],"{");
    strcpy(text->content[2],"   ");
    strcat(text->content[2],parts[2]);
    strcpy(text->content[3],"}");
    overwriting(filename,text);


}

int directory_tree(int depth){
    if (depth<-1){
        printf("invalid depth\n");
    }
    else{

    }
}

int command_detection(char s[]){  
    int t=0;
    while (t<14)
    {
        if (check_e2s(s,commands[t])==1)
        {
            printf("%d\n",t);
            break;
        }
        t=t+1;
    }
    (t==0) ? pr_create_file(s) : printf("no 0\n");
    (t==1) ? pr_insert(s) : printf("no 1\n");
    
    //return(-1);       
    }

int main(){
    //example

    //scanf("%[^\n]s",user_input);
    //printf("%d",command_detection(user_input));
    




}












































































































































































































































