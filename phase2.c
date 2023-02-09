#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>
#include <ncurses.h>

/*-------------------------------------------------------------------------------\
| Title: EPTE (Easy professional text editor)                                    |
+--------------------------------------------------------------------------------+
| Repository link in Github:                                                     |                                                                       
| https://github.com/FundamentalOfProgramming-SUT-2022/project-hashemian1382     |
+--------------------------------------------------------------------------------+
|  AUTHOR :   Ali Hashemian       EMAIL: aho.hashemian@gmail.com                 |
+--------------------------------------------------------------------------------|
| Version: 2.0.0     Date of last revision: 2023-02-04 *** 1401-11-15            |
+--------------------------------------------------------------------------------+
| DESCRIPTION:                                                                   |
|        This program is designed as the final project                           | 
|        of the Fundamental of Programming course of SUT.                        |
|        This program is actually a simulation of Vim.                           |
|        I named it EPTE, which stands for Easy professional text editor.        | 
|        For more information, read the project's readme,                        |
|        which is accessible on the project's GitHub page.                       |                                                        |
|                                                                                |
\-------------------------------------------------------------------------------*/



enum modes { VISUAL , NORMAL , INSERT };
enum modes my_vim_mode;

struct texts
{
    int line;
    char name[50];
    char address[100];
    char content[1000][200];
};
char commands[14][100]={"createfile --file","insertstr --file","cat",
                        "removetstr --file","copystr","cutstr","pastestr --file","undo --file","compare","find","replace",
                        "grep","auto-indent","tree"};
char address_taghti_shode[100][100];
char clipboard[200000];

WINDOW *win;
WINDOW *win_text;
WINDOW *win_mode;
WINDOW *win_name;
WINDOW *win_command;

struct texts * struct_saz(){
    struct texts * text = (struct texts *) malloc(sizeof(struct texts));
    return (text); 
}
void command_phase1(){
    char user_input[1000],byn[1000];
    fgets (user_input, 1000, stdin);
    str_to_str(byn,user_input,0,strlen(user_input)-2);
    strcpy(user_input,byn);
    matlob_saz(user_input);
    while (strcmp(user_input,"END")) {
        matlob_saz(user_input);
        command_detection(user_input);
        printf("~~~ ");
        fgets (user_input, 1000, stdin);
        str_to_str(byn,user_input,0,strlen(user_input)-2);
        strcpy(user_input,byn);
    } 
}
void firs_dis(WINDOW *win,WINDOW *win_text,WINDOW *win_mode,WINDOW *win_name,WINDOW *win_command){ 
    initscr();
    char filename[1000];
    win = newwin (500, 500, 0, 0);
    win_text = newwin (500, 460, 0, 0);
    win_mode = newwin (20, 50, 0, 460);
    win_name = newwin (20, 100, 50, 460);
    win_command = newwin (20, 500, 0, 480);
    refresh();
}
void get_command(){
    char command[1000];
    int t=getch();
    int w=0;
    while (t!=(int)'\n')
    {
        command[w]==(char)t;
        w++;
    }
    command_detection(command);    
}
void printfwin(WINDOW *win,int x, int y, char string[] ){
    mvwprintw(win, x, y, string);
}
void normal(){
    int n=getch();
    if (n==(int)':')
    {
        get_command();
    }
    else{
        if (n==(int)'i')
        {
            my_vim_mode=INSERT;
            insertf();
        }
        if (n==(int)'v')
        {
            my_vim_mode=VISUAL;
            visual();
        }        
    }
    
}
void insertf(){
    int n= getch();
    int x=posx();
    int y=pozy();
    while (n!=(int)'Esc')
    {
        printfwin(win,x,y,(char)n);
        x++;
        y++;
    }
    
}
void visual(){
    int start=position();
    int pre=start;
    while (getch()!=(int)'Esc')
    {
        pre=position();
    }
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
bool file_exists(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    bool being = false;
    if (fp != NULL)
    {
        being = true;
        fclose(fp); 
    }
    return being;
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
            text->content[lines][characters]='\0';
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
    struct texts * text = struct_saz();
    get_file_content(file_name,text);
    char filename[strlen(file_name)];
    if (file_name[0]=='/')
    {
        str_to_str(filename,file_name,1,strlen(file_name)-1);
    }
    else{
        str_to_str(filename,file_name,0,strlen(file_name)-1);
    }    
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
    overwriting(address,text);

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
    int t= tafkik_address(folder_names);
    char address[150]="root";
    mkdir(address);
    for (int i = 2; i <= t; i++)
    {
    strcat(address,"/");
    strcat(address,address_taghti_shode[i]);
    mkdir(address);
    }
    strcat(address,"/");
    strcat(address,file_name);
    FILE *fp;
    fp = fopen (address, "r");
    if (fp==NULL){
        fp = fopen (address, "w");
        fclose (fp);
        printf("The operation was successful.\n");
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
    insert(filename,convet_to_num(num1),convet_to_num(num2),str);
}
void insert(char filename[], int line, int char_num, char string[]){
    int t=file_exists(filename);
    if (!t){
        printf("No such file found.\n");
        return 0;
    }
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
        }
        else{
                change_one_char(text,line,(char_num)%200,string[i]);
        }        
    }
    overwriting(filename,text); 
}
int pr_cat(char string[]){
    int l=strlen(string);
    char file1[l],file[l],folder[l],name[l];
    int f=payan_yab(string,"cat --file");
    str_to_str(file1,string,f+1,l-1);
    if (first_ch(file1,'"')!=-1 && last_ch(file1,'"')!=-1)
    {
        str_to_str(file,file1,first_ch(file1,'"')+1,last_ch(file1,'"')-1);
    }
    else if (first_ch(file1,' ')!=-1 && last_ch(file1,' ')!=-1){
        str_to_str(file,file1,first_ch(file1,' ')+1,l-1);
    }
    str_to_str(folder,file,first_ch(file,'/')+1,last_ch(file,'/')-1);
    str_to_str(name,file,last_ch(file,'/'),l-1);
    strcpy(file,folder);
    strcat(file,name);
    cat(file);
}
int cat(char filename[]){
    int t=file_exists(filename);
    if (!t){
        printf("No such file found.\n");
        return 0;
    }
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
int pr_remove(char string[]){
    int l=strlen(string),num,line_n,char_n,md;
    char part1[l],part2[l],part3[l],pos[l],buf1[l],buf2[l],buf3[l];
    char mode,file[l];
    str_to_str(part1,string,payan_yab(string,"--file")+1,start_yab(string,"--pos")-1);
    if (first_ch(part1,'"')!=-1 && last_ch(part1,'"')!=-1)
    {
        str_to_str(file,part1,first_ch(part1,'"')+1,last_ch(part1,'"')-1);
    }
    else if (first_ch(part1,' ')!=-1 && last_ch(part1,' ')!=-1){
        str_to_str(file,part1,first_ch(part1,' ')+1,l-1);
    }
    str_to_str(part1,file,first_ch(part1,'/'),strlen(part1)-1);
    strcpy(file,part1);
    str_to_str(part2,string,payan_yab(string,"--pos")+1,start_yab(string,"-size")-1);
    if (first_ch(part2,'"')!=-1 && last_ch(part2,'"')!=-1)
    {
        str_to_str(pos,part2,first_ch(part2,'"')+1,l-1);
    }
    else if (first_ch(part2,' ')!=-1 && last_ch(part2,' ')!=-1){
        str_to_str(pos,part2,first_ch(part2,' ')+1,l-1);
    }
    str_to_str(buf1,pos,0,first_ch(pos,':')-1);
    str_to_str(buf2,pos,first_ch(pos,':')+1,strlen(pos)-2);
    line_n=convet_to_num(buf1);
    char_n=convet_to_num(buf2);
    str_to_str(part3,string,payan_yab(string,"-size")+1,l-1);
    str_to_str(buf1,part3,first_ch(part3,' ')+1,last_ch(part3,' ')-1);
    num=convet_to_num(buf1);
    mode=string[l-1];
    if (mode=='b'){
        md=1;
    }
    else if(mode=='f'){
        md=2;
    }
    remove_text(file,line_n,char_n,num,md);
}
int remove_text(char filename[],int line_n, int char_n, int size, int mode){
    int t=file_exists(filename);
    if (!t){
        printf("No such file found.\n");
        return 0;
    }
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
                for ( i = 0; i < (text->line-1-line_n); i++)
                {
                    line_swap(text,i+line_n+2,i+line_n+1);
                }                
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
int pr_copy(char string[]){
    int l=strlen(string),num,line_n,char_n,md;
    char part1[l],part2[l],part3[l],pos[l],buf1[l],buf2[l],buf3[l];
    char mode,file[l];
    str_to_str(part1,string,payan_yab(string,"--file")+1,start_yab(string,"--pos")-1);
    if (first_ch(part1,'"')!=-1 && last_ch(part1,'"')!=-1)
    {
        str_to_str(file,part1,first_ch(part1,'"')+1,last_ch(part1,'"')-1);
    }
    else if (first_ch(part1,' ')!=-1 && last_ch(part1,' ')!=-1){
        str_to_str(file,part1,first_ch(part1,' ')+1,l-1);
    }
    str_to_str(part1,file,first_ch(part1,'/'),strlen(part1)-1);
    strcpy(file,part1);
    str_to_str(part2,string,payan_yab(string,"--pos")+1,start_yab(string,"-size")-1);
    if (first_ch(part2,'"')!=-1 && last_ch(part2,'"')!=-1)
    {
        str_to_str(pos,part2,first_ch(part2,'"')+1,l-1);
    }
    else if (first_ch(part2,' ')!=-1 && last_ch(part2,' ')!=-1){
        str_to_str(pos,part2,first_ch(part2,' ')+1,l-1);
    }
    str_to_str(buf1,pos,0,first_ch(pos,':')-1);
    str_to_str(buf2,pos,first_ch(pos,':')+1,strlen(pos)-2);
    line_n=convet_to_num(buf1);
    char_n=convet_to_num(buf2);
    str_to_str(part3,string,payan_yab(string,"-size")+1,l-1);
    str_to_str(buf1,part3,first_ch(part3,' ')+1,last_ch(part3,' ')-1);
    num=convet_to_num(buf1);
    mode=string[l-1];
    if (mode=='b'){
        md=1;
    }
    else if(mode=='f'){
        md=2;
    }
    copy(file,line_n,char_n,num,md);
}
int copy(char filename[],int line_n, int char_n, int size, int mode){
    int t=file_exists(filename);
    if (!t){
        printf("No such file found.\n");
        return 0;
    }
    struct texts * text=struct_saz();
    int i;
    get_file_content(filename,text);
    file_backup(filename);
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
    clip();       
    overwriting("ali.txt",text);
}
int pr_cut(char string[]){
    int l=strlen(string),num,line_n,char_n,md;
    char part1[l],part2[l],part3[l],pos[l],buf1[l],buf2[l],buf3[l];
    char mode,file[l];
    str_to_str(part1,string,payan_yab(string,"--file")+1,start_yab(string,"--pos")-1);
    if (first_ch(part1,'"')!=-1 && last_ch(part1,'"')!=-1)
    {
        str_to_str(file,part1,first_ch(part1,'"')+1,last_ch(part1,'"')-1);
    }
    else if (first_ch(part1,' ')!=-1 && last_ch(part1,' ')!=-1){
        str_to_str(file,part1,first_ch(part1,' ')+1,l-1);
    }
    str_to_str(part1,file,first_ch(part1,'/'),strlen(part1)-1);
    strcpy(file,part1);
    str_to_str(part2,string,payan_yab(string,"--pos")+1,start_yab(string,"-size")-1);
    if (first_ch(part2,'"')!=-1 && last_ch(part2,'"')!=-1)
    {
        str_to_str(pos,part2,first_ch(part2,'"')+1,l-1);
    }
    else if (first_ch(part2,' ')!=-1 && last_ch(part2,' ')!=-1){
        str_to_str(pos,part2,first_ch(part2,' ')+1,l-1);
    }
    str_to_str(buf1,pos,0,first_ch(pos,':')-1);
    str_to_str(buf2,pos,first_ch(pos,':')+1,strlen(pos)-2);
    line_n=convet_to_num(buf1);
    char_n=convet_to_num(buf2);
    str_to_str(part3,string,payan_yab(string,"-size")+1,l-1);
    str_to_str(buf1,part3,first_ch(part3,' ')+1,last_ch(part3,' ')-1);
    num=convet_to_num(buf1);
    mode=string[l-1];
    if (mode=='b'){
        md=1;
    }
    else if(mode=='f'){
        md=2;
    }
    cut(file,line_n,char_n,num,md);
}
int cut(char filename[],int line_n, int char_n, int size, int mode){
    int t=file_exists(filename);
    if (!t){
        printf("No such file found.\n");
        return 0;
    }
    copy(filename, line_n, char_n, size, mode);
    remove_text(filename, line_n, char_n, size, mode);
    clip();
}
int pr_paste(char string[]){
    int l=strlen(string),i;
    char file[l],file1[l];
    char pos[l],pos1[l];
    char num1[l],num2[l];
    int f1,p1,f2,p2;
    f1=start_yab(string,"--file");
    f2=payan_yab(string,"--file");
    p1=start_yab(string,"--pos");
    p2=payan_yab(string,"--pos");  

    str_to_str(file1,string,f2+1,p1-1);
    str_to_str(pos1,string,p2+1,l-1);

    if (first_ch(file1,'"')!=-1 && last_ch(file1,'"')!=-1)
    {
        str_to_str(file,file1,first_ch(file1,'"')+1,last_ch(file1,'"')-1);
    }
    else if (first_ch(file1,' ')!=-1 && last_ch(file1,' ')!=-1){
        str_to_str(file,file1,first_ch(file1,' ')+1,last_ch(file1,' ')-1);
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
    int n1=convet_to_num(num1);
    int n2=convet_to_num(num2);
    str_to_str(file1,file,first_ch(file1,'/')+1,last_ch(file1,' ')-1);
    paste(file1,n1,n2);

}
int paste(char filename[],int line_n, int char_n){
    int t=file_exists(filename);
    if (!t){
        printf("No such file found.\n");
        return 0;
    }
    insert(filename,line_n,char_n,clipboard);
    printf("The operation was successful.\n");
}
int pr_undo(char string[]){
    int l= strlen(string);
    char part1[l],file[l];
    str_to_str(part1,string,payan_yab(string,"--file")+1,l-1);
    if (first_ch(part1,'"')!=-1 && last_ch(part1,'"')!=-1)
    {
        str_to_str(file,part1,first_ch(part1,'"')+1,last_ch(part1,'"')-1);
    }
    else if (first_ch(part1,' ')!=-1 && last_ch(part1,' ')!=-1){
        str_to_str(file,part1,first_ch(part1,' ')+1,strlen(part1)-1);
    }
    str_to_str(part1,file,first_ch(file,'/')+1,strlen(file)-1);
    strcpy(file,part1);
    undo(file);
}
int undo (char filename[]){
    int t=file_exists(filename);
    if (!t){
        printf("No such file found.\n");
        return 0;
    }
    FILE *fptr1, *fptr2;
    char c,b_file_name[1000],cd1[1000],cd2[1000]="b_";
    str_to_str(b_file_name,filename,0,last_ch(filename,'/'));
    str_to_str(cd1,filename,last_ch(filename,'/')+1,strlen(filename)-1);
    strcat(cd2,cd1);
    strcat(b_file_name,cd2);
    struct texts * text= struct_saz();
    get_file_content(b_file_name,text);
    overwriting(filename,text);
    printf("The operation was successful.\n");
    
}
int pr_compare(char string[]){
    int l= strlen(string);
    char part1[l],part2[l],name1[l],name2[l];
    int t,p1,p2,p3,p4;
    str_to_str(part1,string,payan_yab(string,"compare")+1,l-1);
    if (nom_ch(part1,'"',1)!=-1)
    {
        p1=nom_ch(part1,'"',1);
        t=t+1;
    }
    if (nom_ch(part1,'"',2)!=-1)
    {
        p2=nom_ch(part1,'"',2);
        t=t+1;
    }
    if (nom_ch(part1,'"',3)!=-1)
    {
        p3=nom_ch(part1,'"',3);
        t=t+1;
    }
    if (nom_ch(part1,'"',4)!=-1)
    {
        p4=nom_ch(part1,'"',4);
        t=t+1;
    }
    
    str_to_str(name1,part1,nom_ch(part1,' ',1)+1,nom_ch(part1,' ',2)-1);
    str_to_str(name2,part1,nom_ch(part1,' ',2)+1,strlen(part1)-1);
    str_to_str(part1,name1,first_ch(name1,'/')+1,strlen(name1)-1);
    str_to_str(part2,name2,first_ch(name2,'/')+1,strlen(name2)-1);

    compare(part1,part2);
}
int compare(char filename1[],char filename2[]){
    int t1=file_exists(filename1);
    if (!t1){
        printf("No such file found.\n");
        return 0;
    }
    int t2=file_exists(filename2);
    if (!t2){
        printf("No such file found.\n");
        return 0;
    }
    int i;
    struct texts* text1=struct_saz();
    struct texts* text2=struct_saz();
    get_file_content(filename1,text1);
    get_file_content(filename2,text2);
    int l1=text1->line;
    int l2=text2->line;
    printf("%d %d\n",l1,l2);
    int min=(l1>l2)*l2+(l2>=l1)*l1;
    printf("%d\n",min);
    for ( i = 1; i <= min; i++)
    {
        if (check_e2s(text1->content[i],text2->content[i])==0){
            printf("============ #<%d> ============\n",i);
            printf("%s\n",text1->content[i]);
            printf("%s\n",text2->content[i]);            
        }
    }
    if (l1>l2)
    {
        printf("<<<<<<<<<<<< #%d - #%d <<<<<<<<<<<<\n",min+1,l1);
        for ( i = min; i < l1; i++)
        {
            printf("%s\n",text1->content[i]);
        }
    }
    if (l2>l1)
    {
        printf(">>>>>>>>>>>> #%d - #%d >>>>>>>>>>>>\n",min+1,l2);
        for ( i = min; i < l2; i++)
        {
            printf("%s\n",text2->content[i]);
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
    }
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
int min(int p1, int p2, int p3, int p4){
    int min=10000;
    if (p1!=-1 && p1<min)
    {
        min=p1;
    }
    if (p2!=-1 && p2<min){
        min=p2;
    }
    if (p3!=-1 && p3<min){
        min=p3;
    }
    if (p4!=-1 && p4<min){
        min=p4;
    }
    return (min);    
}
int pr_find(char string[]){
    int l=strlen(string),num=1;
    char name[l],str[l],file[l],file2[l],jost[l];
    str_to_str(str,string,payan_yab(string,"--str")+1,start_yab(string,"--file")-1);
    str_to_str(file,string,payan_yab(string,"--file")+1,l-1);

    int mode=1;
    if (start_yab(file,"-count")!=-1)
    {
        mode*=2;
    }
    if (start_yab(file,"-at")!=-1)
    {
        mode*=3;
        char number[l];
        str_to_str(number,file,payan_yab(file,"at")+1,strlen(file)-1);
        num=convet_to_num(number);
    }
    if (start_yab(file,"-byword")!=-1)
    {
        mode*=5;
    }
    if (start_yab(file,"-all")!=-1)
    {
        mode*=7;
    }
    if (mode!=1){
        int p1=start_yab(file,"-all");
        int p2=start_yab(file,"-byword");
        int p3=start_yab(file,"-at");
        int p4=start_yab(file,"-count");
        int minim= min(p1,p2,p3,p4);
        str_to_str(file2,file,0,minim-1);
    }
    else{
        str_to_str(file2,file,0,strlen(file)-1);
    }
    if (first_ch(file2,'"')!=-1 && last_ch(file2,'"')!=-1)
    {
        str_to_str(name,file2,first_ch(file2,'"')+1,last_ch(file2,'"')-1);
    }
    else if (nom_ch(file2,' ',1)!=-1 && nom_ch(file2,' ',2)==-1){
        str_to_str(name,file2,first_ch(file2,'/')+1,strlen(file2)-1);
    }
    else if ((nom_ch(file2,' ',1)!=-1 && nom_ch(file2,' ',2)!=-1)){
        str_to_str(name,file2,first_ch(file2,'/')+1,nom_ch(file2,' ',2)-1);
    }
    if (first_ch(str,'"')!=-1 && last_ch(str,'"')!=-1)
    {
        str_to_str(jost,str,first_ch(str,'"')+1,last_ch(str,'"')-1);
    }
    else if (first_ch(str,' ')!=-1 && last_ch(str,' ')!=-1){
        str_to_str(jost,str,first_ch(str,' ')+1,last_ch(str,' ')-1);
    }
    int md=1;
    int n=1;
    if (mode==1)
    {
        md=1;        
    }
    if (mode==2)
    {
        md=5;
    }
    if (mode==3)
    {
        md=1;
        n=num;
    }
    if (mode==5)
    {
        md=2;
    }
    if (mode==7)
    {
        md=3;
    }
    if (mode==35)
    {
        md=4;
    }
    if (mode==15)
    {
        md=2;
        n=num;
    }
    if (mode==21)
    {
        printf("Sorry,at and all cannot come together.\n");
        return(-1);
    }
    find(name,jost,md,n);
}
int find(char filename[],char string[], int mode, int n){
    int ttt=file_exists(filename);
    if (!ttt){
        printf("No such file found.\n");
        return 0;
    }
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
            printf("not found!\n",t);
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
            printf("not found!\n",t);
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
            printf("not found!\n");
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
        printf("%d\n",t);
    }

}
int pr_replace(char string[]){
    int l = strlen(string),num,n,md;
    char str1[l],str2[l],file[l],part1[l],part2[l],part3[l],part4[l];
    str_to_str(part1,string,payan_yab(string,"--str1")+1,start_yab(string,"--str2")-1);
    str_to_str(part2,string,payan_yab(string,"--str2")+1,start_yab(string,"--file")-1);
    str_to_str(part3,string,payan_yab(string,"--file")+1,l-1);
    if (first_ch(part1,'"')!=-1 && last_ch(part1,'"')!=-1)
    {
        str_to_str(str1,part1,first_ch(part1,'"')+1,last_ch(part1,'"')-1);
    }
    else if (first_ch(part1,' ')!=-1 && last_ch(part1,' ')!=-1){
        str_to_str(str1,part1,first_ch(part1,' ')+1,last_ch(part1,' ')-1);
    }

    if (first_ch(part2,'"')!=-1 && last_ch(part2,'"')!=-1)
    {
        str_to_str(str2,part2,first_ch(part2,'"')+1,last_ch(part2,'"')-1);
    }
    else if (first_ch(part2,' ')!=-1 && last_ch(part2,' ')!=-1){
        str_to_str(str2,part2,first_ch(part2,' ')+1,last_ch(part2,' ')-1);
    }

    int mode=1;
    if (start_yab(part3,"-at")!=-1)
    {
        mode*=3;
        char number[l];
        str_to_str(number,part3,payan_yab(part3,"-at")+2,strlen(part3)-1);
        num=convet_to_num(number);
    }
    if (start_yab(part3,"-all")!=-1)
    {
        mode*=7;
    }
    if (mode==21){
        printf("Sorry,at and all cannot come together.\n");
        return(-1);
    }

    else if (mode==3){
        int p=start_yab(part3,"-at");
        str_to_str(part4,part3,0,p-1);
    }
    else if (mode==7){
        int p=start_yab(part3,"-all");
        str_to_str(part4,part3,0,p-1);
    }
    else{
        str_to_str(part4,part3,0,strlen(part3)-1);
    }

    if (nom_ch(part4,'"',1)!=-1 && nom_ch(part4,'"',2)!=-1)
    {
        str_to_str(file,part4,first_ch(part4,'/')+1,last_ch(part4,'"')-1);
    }
    else if (nom_ch(part4,' ',1)!=-1 && nom_ch(part4,' ',2)!=-1){
        str_to_str(file,part4,first_ch(part4,'/')+1,last_ch(part4,' ')-1);
    }
    else if (nom_ch(part4,' ',1)!=-1 && nom_ch(part4,' ',2)==-1){
        str_to_str(file,part4,first_ch(part4,'/')+1,strlen(part4)-1);
    }
    if (mode==1){
        md=1;
        n=1;
    }
    if (mode==3)
    {
        md=1;
        n=num;
    }
    if (mode==7)
    {
        md=2;
        n=1;
    }
    replace(file,str1,str2,md,n);
}
int replace(char filename[], char str1[], char str2[], int mode, int num){
    int t=file_exists(filename);
    if (!t){
        printf("No such file found.\n");
        return 0;
    }
    file_backup(filename);
    if (mode==1)
    {
        replace_at(filename,str1,str2,num);
    }
    else if (mode==2)
    {
        replace_all(filename,str1,str2);
    }
    printf("The operation was successful.\n");
    
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
int pr_grep(char string[]){
    int aption=1,mode=1;
    int l= strlen(string);
    char part0[l],part1[l],str[l],part2[l],file_name[l][1000],file[l];
    int space[l];
    str_to_str(part0,string,payan_yab(string,"grep")+1,start_yab(string,"--str")-1);
    str_to_str(part1,string,payan_yab(string,"--str")+1,start_yab(string,"--files")-1);
    str_to_str(part2,string,payan_yab(string,"--files")+1,l-1);
    if (start_yab(part0,"-c")!=-1){
        aption*=2;
    }
    else if (start_yab(part0,"-l")!=-1){
        aption*=3;
    }
    if (first_ch(part1,'"')!=-1 && last_ch(part1,'"')!=-1)
    {
        str_to_str(str,part1,first_ch(part1,'"')+1,last_ch(part1,'"')-1);
    }
    else if (first_ch(part1,' ')!=-1 && last_ch(part1,' ')!=-1){
        str_to_str(str,part1,first_ch(part1,' ')+1,last_ch(part1,' ')-1);
    }
    int t=0;
    for (int i = 0; i < strlen(part2)-1; i++)
    {
        if (part2[i]==' ')
        {
            space[t]=i;
            t=t+1;
        }
    }
    space[t]=strlen(part2)-1;
    for (int i = 0; i < t-1; i++)
    {
        str_to_str(file,part2,space[i]+1,space[i+1]-1);
        str_to_str(file_name[i],file,first_ch(file,'/')+1,strlen(file)-1);
    }
    str_to_str(file,part2,space[t-1]+1,strlen(part2)-1);
    str_to_str(file_name[t-1],file,first_ch(file,'/')+1,strlen(file)-1);
    if (aption==2)
    {
        mode=2;
    }
    else if (aption==3)
    {
        mode=3;
    }
    else if (aption==6){
        printf("Sorry,aption l and c cannot come together.\n");
        return (0);
    }        
    grep(file_name,str,t,mode); 
}
int grep(char listnames[][1000],char string[] ,int num, int mode){
    int i,j,t,k,tt;
    struct texts * text[num];
    int l1=200;
    int l2=strlen(string);
    int space1[l1],space2[l2],start1[l1],payan1[l1],start2[l2],payan2[l2],A[100],B[100];
    for ( i = 0; i < num; i++)
    {
        int tt=file_exists(listnames[i]);
        if (!tt){
            printf("No such file found.\n");
            return 0;
        }
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
                    printf("%s: %s\n",listnames[i],text[i]->content[j]);
                }        
            }
        }        
    }        
    if (mode==2)
    {
        int count=0;
        for ( i = 0; i < num; i++)
        {
            for ( j = 1; j <= text[i]->line; j++)
            {
                t=find_help(A,B,text[i]->content[j],string,space1,space2,start1,payan1,start2,payan2);
                if (t>0)
                {
                    count++;
                }        
            }
        } 
    printf("%d\n",count);       
    }
    if (mode==3)
    {
        char files[(num*100)];
        strcpy(files,"");
        int count=0;
        for ( i = 0; i < num; i++)
        {
            count=0;
            for ( j = 1; j <= text[i]->line; j++)
            {
                t=find_help(A,B,text[i]->content[j],string,space1,space2,start1,payan1,start2,payan2);
                if (t>0)
                {
                    count++;
                }        
            }
            if (count>0)
            {
                strcat(files,listnames[i]);
                strcat(files,"\n");
            }            
        }
    printf("%s",files);        
    }                
}
int pr_yab(char string[],int baz[], int baste[]){
    int i, l=strlen(string),tedad=0;
    for ( i = 0; i < l; i++)
    {
        if (string[i]=='{')
        {
            tedad++;
            baz[tedad]=i;
        }        
    }
    int t=tedad;
    for ( i = 0; i < l; i++)
    {
        if (string[i]=='}')
        {
            baste[tedad]=i;
            tedad--;
        }        
    }
    return(t);    
}
int tedad_bein(int tedad_pr, int bein[], int baz[], int baste[]){
    int i;
    if (baz[tedad_pr]-baste[tedad_pr]==1)
    {
        bein[tedad_pr]=0;
    }
    else {
        bein[tedad_pr]=1;
    }
    for ( i = tedad_pr-1; i > 0; i--)
    {
        bein[i]=bein[i+1]+2;
    }
    int kol=bein[1]+2;
    return(kol);    
}
int start_end(int kol, int bein[], int start[], int end[], int tedad_pr){
    int i;
    start[1]=1;
    end[1]=kol;
    for ( i = 2; i <= tedad_pr; i++)
    {
        start[i]=start[i-1]+1;
        end[i]=end[i-1]-1;
    }
}
int help_auto_indent(char string[],struct texts* text, int shomare, int tedad_pr, int baz[], int baste[], int start[],int end[], int bein[]) {
    int i;
    text->line=bein[1]+3;
    if (shomare==1)
    {
        if (string[0]!='{')
        {
            str_to_str(text->content[1],string,0,baz[1]-1);
            strcat(text->content[1]," ");
            strcat(text->content[1],"{");
            strcat(text->content[1],"\0");
            strcpy(text->content[end[1]],"}");
            strcat(text->content[end[1]],"\0");
        }
        else{
            strcpy(text->content[1],"{");
            strcat(text->content[1],"\0");
            strcpy(text->content[end[1]],"}");
            strcat(text->content[end[1]],"\0");
        }
    }
    if (shomare!=1 && string[baz[shomare-1]+1]!='{')
    {
        char temp[1000];
        int len = strlen(text->content[start[shomare]]);
        str_to_str(temp,string,baz[shomare-1]+1,baz[shomare]-1);
        memset(text->content[start[shomare]]+len, '\t', shomare-1 );   
        text->content[start[shomare]][len + shomare-1] = '\0';
        strcat(text->content[start[shomare]],temp);
        strcat(text->content[start[shomare]]," ");
        strcat(text->content[start[shomare]],"{");
        strcat(text->content[start[shomare]],"\0");
        memset(text->content[end[shomare]]+len, '\t', shomare-1 );   
        text->content[end[shomare]][len + shomare-1] = '\0';
        strcat(text->content[end[shomare]],"}");
        strcat(text->content[end[shomare]],"\0");
    }
    else if (shomare!=1 && string[baz[shomare-1]+1]=='{'){
        int len = strlen(text->content[start[shomare]]);
        memset(text->content[start[shomare]]+len, '\t', shomare-1 );   
        text->content[start[shomare]][len + shomare-1] = '\0';
        strcat(text->content[start[shomare]],"{");
        strcat(text->content[start[shomare]],"\0");
        memset(text->content[end[shomare]]+len, '\t', shomare-1 );   
        text->content[end[shomare]][len + shomare-1] = '\0';
        strcat(text->content[end[shomare]],"}");
        strcat(text->content[end[shomare]],"\0");
    }    
    if (shomare==tedad_pr && (baste[shomare]-baz[shomare])>1){
        int len = strlen(text->content[start[shomare]+1]);
        char temp[1000];
        str_to_str(temp,string,baz[shomare]+1,baste[shomare]-2);
        memset(text->content[start[shomare]+1]+len, '\t', shomare);
        text->content[start[shomare]+1][len + shomare+1] = '\0';
        strcat(text->content[start[shomare]+1],temp);
        strcat(text->content[start[shomare]+1],"\0");
    }

}
int pr_auto_indent(char string[]){
    int l= strlen(string);
    char part1[l],file[l];
    str_to_str(part1,string,payan_yab(string,"auto-indent")+1,l-1);
    if (first_ch(part1,'"')!=-1 && last_ch(part1,'"')!=-1)
    {
        str_to_str(file,part1,first_ch(part1,'"')+1,last_ch(part1,'"')-1);
    }
    else if (first_ch(part1,' ')!=-1 && last_ch(part1,' ')!=-1){
        str_to_str(file,part1,first_ch(part1,' ')+1,strlen(part1)-1);
    }
    str_to_str(part1,file,first_ch(file,'/')+1,strlen(file)-1);
    strcpy(file,part1);
    auto_indent(file);
}
int auto_indent(char filename[]){
    int t=file_exists(filename);
    if (!t){
        printf("No such file found.\n");
        return 0;
    }
    struct texts * text= struct_saz();
    get_file_content(filename,text);
    int l=strlen(text->content[1]);
    file_backup(filename);
    int tedad=1,i;
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
    l=strlen(text->content[1]);
    char string[l];
    int bein[l],baz[l],baste[l],start[l],end[l];
    strcpy(string,text->content[1]);    
    int tedad_pr=pr_yab(string,baz,baste);
    int kol=tedad_bein(tedad_pr,bein,baz,baste);
    start_end(kol,bein,start,end,tedad_pr);
    for (i = 1; i <= tedad_pr; i++)
    {
        help_auto_indent(string,text,i,tedad_pr,baz,baste,start,end,bein);
    }
    overwriting(filename,text);
    printf("The operation was successful.\n");
}
int pr_tree(char string[]){
    int depth;
    char part[strlen(string)];
    str_to_str(part,string,nom_ch(string,' ',1)+1,strlen(string)-1);
    depth=convet_to_num(part);
    directory_tree(depth);
}
int tree_help(char name[], int indent, int depth)
{
    DIR *dir;
    struct dirent *entry;

    if (indent>depth && depth!=-1)
    {
        return -1;
    }
    
    if (!(dir = opendir(name)))
        return -1;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            char path[1024];
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0){
                strcpy(path,name);
                strcat(path,"/");
                strcat(path,entry->d_name);
                printf("%*sD|--%s\n", 4*indent, "", entry->d_name);
                tree_help(path, indent + 1, depth);
            }
        } 
        else {
            printf("%*sF|--%s\n", 4*indent, "", entry->d_name);
        }
    }
    closedir(dir);
}
int directory_tree(int depth){
    if (depth<-1){
        printf("invalid depth\n");
    }
    else{
        printf("D: directory(or folder)\nF: file\n");
        printf("<<<<<<<<<<<<tree-%dD>>>>>>>>>>>>\n",depth);
        printf("root:\n");
        tree_help("./root",0,depth);
        printf("<<<<<<<<<<<<tree-%dD>>>>>>>>>>>>\n",depth);
    }
}
void matlob_saz(char string[]){
    int l= strlen(string);
    char temp1[l],temp2[l],temp3[l];
    int i, t;
    for (int i = 0; i < l; i++)
    {
        if (string[i]=='\\' && string[i+1]=='n' && string[i-1]!='\\'){
            str_to_str(temp1,string,0,i-1);
            str_to_str(temp2,"\n",0,1);
            str_to_str(temp3,string,i+2,l-1);
            strcpy(string,temp1);
            strcat(string,temp2);
            strcat(string,temp3);
            l=l-1;
        }
        else if (string[i]=='\\' && string[i+1]=='n' && string[i-1]=='\\'){
            str_to_str(temp1,string,0,i-2);
            str_to_str(temp2,"\\n",0,2);
            str_to_str(temp3,string,i+2,l-1);
            strcpy(string,temp1);
            strcat(string,temp2);
            strcat(string,temp3);
            l=l-2;
            i=i+1;
        }
        else if (string[i]=='\\' && string[i+1]=='\"' && string[i-1]!='\\'){
            str_to_str(temp1,string,0,i-1);
            str_to_str(temp2,"\"",0,1);
            str_to_str(temp3,string,i+2,l-1);
            strcpy(string,temp1);
            strcat(string,temp2);
            strcat(string,temp3);
            l=l-1;
        }        
    }    
}
int command_detection(char s[]){  
    int t=0,r=0;
    while (t<14)
    {
        if (check_e2s(s,commands[t])==1)
        {
            r=1;
            break;
        }
        t=t+1;
    }
    (t==0) ? pr_create_file(s) : printf("");
    (t==1) ? pr_insert(s) : printf("");
    (t==2) ? pr_cat(s): printf("");
    (t==3) ? pr_remove(s) : printf("");
    (t==4) ? pr_copy(s) : printf("");
    (t==5) ? pr_cut(s) : printf("");
    (t==6) ? pr_paste(s) : printf("");
    (t==7) ? pr_undo(s) : printf("");
    (t==8) ? pr_compare(s) : printf("");
    (t==9) ? pr_find(s) : printf("");
    (t==10) ? pr_replace(s) : printf("");
    (t==11) ? pr_grep(s) : printf("");
    (t==12) ? pr_auto_indent(s) : printf("");
    (t==13) ? pr_tree(s) : printf("");
    if (r==0)
    {
        printf("invalid command\n");
        return(-1);       
    }    
}
int clip(){
    int t=file_exists("Clipboard.txt");
    if (t){
        FILE *fp = fopen("Clipboard.txt", "w");
        char s[strlen(clipboard)];
        strcpy(s,clipboard);
        insert("Clipboard.txt",1,0,s);
    }
    else{
        FILE *fp = fopen("Clipboard.txt", "w");
        char s[strlen(clipboard)];
        strcpy(s,clipboard);
        insert("Clipboard.txt",1,0,s);
    }
}
int clip_ex(){
    int t=file_exists("Clipboard.txt");
    if (t){
        struct texts * text= struct_saz();
        get_file_content("Clipboard.txt",text);
        strcpy(clipboard,text->content[1]);
        for (int i = 2; i <= (text->line); i++)
        {
            strcat(clipboard,text->content[i]);
        }        
    }
}
int main(){
    clip_ex();
    mkdir("root");
    my_vim_mode = NORMAL;
    initscr();
    firs_dis();
    while (1)
    {
        if (my_vim_mode==NORMAL)
        {
            normal();
        }
        else if (my_vim_mode==INSERT)
        {
            insertf();
        }
        else if (my_vim_mode==VISUAL){
            visual();
        }                
    }
    
    endwin();
    return 0;
}













































































































































































































































