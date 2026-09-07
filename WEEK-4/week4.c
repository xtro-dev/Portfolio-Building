#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100
#define LEN 200

char doc[MAX][LEN], old[MAX][LEN];
int lines=0, oldLines=0, canUndo=0;

void backup()
{
    oldLines=lines;
    for(int i=0;i<lines;i++) strcpy(old[i],doc[i]);
    canUndo=1;
}

void undo()
{
    if(!canUndo){printf("Nothing to undo.\n");return;}
    lines=oldLines;
    for(int i=0;i<lines;i++) strcpy(doc[i],old[i]);
    canUndo=0;
    printf("Undo successful.\n");
}

void display()
{
    printf("\n========== DOCUMENT ==========\n");
    if(!lines) printf("Document is empty.\n");
    for(int i=0;i<lines;i++) printf("%d | %s\n",i+1,doc[i]);
    printf("===============================\n");
}

void insertLine(int p)
{
    char s[LEN];
    if(p<1||p>lines+1||lines==MAX){printf("Invalid position.\n");return;}
    printf("Enter text: ");
    fgets(s,LEN,stdin);
    s[strcspn(s,"\n")]=0;
    backup();
    for(int i=lines;i>=p;i--) strcpy(doc[i],doc[i-1]);
    strcpy(doc[p-1],s);
    lines++;
    printf("Line inserted.\n");
}

void deleteLine(int p)
{
    if(p<1||p>lines){printf("Invalid line.\n");return;}
    backup();
    for(int i=p-1;i<lines-1;i++) strcpy(doc[i],doc[i+1]);
    lines--;
    printf("Line deleted.\n");
}

void saveFile(char *name)
{
    FILE *f=fopen(name,"w");
    if(!f){printf("Cannot open file.\n");return;}
    for(int i=0;i<lines;i++) fprintf(f,"%s\n",doc[i]);
    fclose(f);
    printf("File saved.\n");
}

void loadFile(char *name)
{
    FILE *f=fopen(name,"r");
    if(!f){printf("Cannot open file.\n");return;}
    lines=0;
    while(lines<MAX&&fgets(doc[lines],LEN,f)){
        doc[lines][strcspn(doc[lines],"\n")]=0;
        lines++;
    }
    fclose(f);
    canUndo=0;
    printf("File loaded.\n");
}

void search(char *word)
{
    int found=0;
    for(int i=0;i<lines;i++)
        if(strstr(doc[i],word)){
            printf("Line %d: %s\n",i+1,doc[i]);
            found=1;
        }
    if(!found) printf("Not found.\n");
}

void replaceAll(char *a,char *b)
{
    char temp[LEN];
    int found=0;

    for(int i=0;i<lines;i++){
        char *p=doc[i];

        while((p=strstr(p,a))){
            found=1;
            p+=strlen(a);
        }
    }

    if(!found){printf("Text not found.\n");return;}

    backup();

    for(int i=0;i<lines;i++){
        while(strstr(doc[i],a)){
            char *p=strstr(doc[i],a);
            int pos=p-doc[i];

            strcpy(temp,p+strlen(a));
            doc[i][pos]=0;
            strcat(doc[i],b);
            strcat(doc[i],temp);
        }
    }

    printf("Text replaced.\n");
}

void countWords()
{
    int words=0,in=0;

    for(int i=0;i<lines;i++)
        for(int j=0;doc[i][j];j++)
            if(isspace((unsigned char)doc[i][j]))
                in=0;
            else if(!in){
                words++;
                in=1;
            }

    printf("Lines: %d\nWords: %d\n",lines,words);
}

int main(int argc,char *argv[])
{
    char cmd[300],name[200],a[100],b[100];
    int p;

    printf("\n===== SIMPLE LINE EDITOR =====\n");

    if(argc>1) loadFile(argv[1]);

    printf("Type help for commands.\n");

    while(1){
        printf("\n> ");

        if(!fgets(cmd,sizeof(cmd),stdin)) break;

        cmd[strcspn(cmd,"\n")]=0;

        if(!strcmp(cmd,"quit"))
            break;

        else if(!strcmp(cmd,"display"))
            display();

        else if(!strcmp(cmd,"undo"))
            undo();

        else if(!strcmp(cmd,"count"))
            countWords();

        else if(!strcmp(cmd,"help"))
            printf("\ninsert <n>\ndelete <n>\ndisplay\nsave <file>\nload <file>\nsearch <word>\nreplace <old> <new>\nundo\ncount\nquit\n");

        else if(sscanf(cmd,"insert %d",&p)==1)
            insertLine(p);

        else if(sscanf(cmd,"delete %d",&p)==1)
            deleteLine(p);

        else if(sscanf(cmd,"save %199s",name)==1)
            saveFile(name);

        else if(sscanf(cmd,"load %199s",name)==1)
            loadFile(name);

        else if(sscanf(cmd,"search %99s",a)==1)
            search(a);

        else if(sscanf(cmd,"replace %99s %99s",a,b)==2)
            replaceAll(a,b);

        else
            printf("Unknown command. Type help.\n");
    }

    return 0;
}