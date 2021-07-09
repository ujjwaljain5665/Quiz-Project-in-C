#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<windows.h>

COORD c={0,0};
void gotoxy(int x,int y){
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

int startquiz();
void student();
void teacher();

int main()
{
    system("cls");
    char r1,l;
    gotoxy(7,4);
    printf("QUIZ (MULTIPLE CHOICE QUESTIONS)");
    gotoxy(4,3);
    printf("=========================================");
    gotoxy(7,5);
    printf("created By:Ujjwal Jain");
    gotoxy(4,6);
    printf("=========================================");
    gotoxy(7,8);
    printf("Press any key to continue:");
    l=getch();
    label:
    system("cls");
    gotoxy(10,4);
    printf("WELCOME!!!\n");
    printf("1.Student Login\n2.Teacher Login\n3.Exit");
    r1=getch();
    switch(r1){
        case '1':
        student();
        break;
        case '2':
        teacher();
        break;
        case '3':
        exit(0);
        default:
        system("cls");
        printf("Invalid choice...Press any key.");
        getch();
        goto label;
    }
}

void student(){
    //student interface//
    system("cls");
    char name[10],sr1;
    int rollno,marks;
    printf("\nEnter your name\t:");
    scanf("%s",&name);
    printf("Enter roll no.\t:");
    scanf("%d",&rollno);
    system("cls");
    printf("\n\nLogged in as:    %s \n",strupr(name));//name displays in upper case//
    printf("!! Enter option number as answers !!\n");
    marks=startquiz();//this attempts quiz and evaluates marks.//
    FILE* fp;
    fp=fopen("report.txt","a");
    fprintf(fp,"%d\t%s\t\t\t\t%d\n",rollno,strupr(name),marks);//stores marks in report//
    fclose(fp);
    printf("You have successfullt attempted the quiz.\nPress any key to continue.");
    getch();
}
void teacher(){
    //teacher interface//
    int h,tres;
    char b;
    char pass[20];
    label2:
    system("cls");
    fflush(stdin);
    printf("TEACHER LOGIN:\n======= =====\nEnter Passcode:\t:");
    scanf("%[^\n]",&pass);
    if(strcmp(pass,"jain")==0){
        label1:
        system("cls");
        printf("Logged in as: Ujjwal Jain \n\n");
        printf("Enter 1 to add questions.\nEnter 2 to view report.\n");
        printf("Enter your choice:");
        scanf("%d",&tres);
        if(tres==1){
            system("cls");
            //adding questions to quiz//
            FILE *fp,*fp1;
            fp = fopen("ques.txt", "w");
            printf("ADD QUESTIONS TO QUIZ:\n"); 
            printf("=== ========= == =====\n\n\n"); 
            printf(">>Enter the number of question:");
            scanf("%d",&h);
            fp1 = fopen("tques.txt", "w");
            putw(h,fp1);
            fclose(fp1);
            int i;
            int len;
            fprintf(fp,"QUIZ CREATED BY: Ujjwal Jain\n");
            fclose(fp);
            int a=1;
            while(a<=h){
                fp = fopen("ques.txt", "a");
                // fprintf(fp,"\n\n");
                char question[50];
                fflush(stdin);
                printf("Enter question %d:",a);
                gets(question);
                len = strlen(question);
                fprintf(fp,"Question %d:\t",a);
                for (i = 0; i < len; i++) {
                    fputc (question[i], fp);
                }
                fprintf(fp,"\n");
                fclose(fp);
                char option[4][50];
                for(int j=1;j<=4;j++){
                    fp = fopen("ques.txt", "a");
                    printf("Enter the option %d:\t",j);
                    gets(option[j]);
                    i=0;
                    int len = strlen(option[j]);
                    fprintf(fp,"%d)\t",j);
                    for (i = 0; i < len; i++) {
                        fputc (option[j][i], fp);
                    }
                    fprintf(fp,"\n");
                    fclose(fp);
                }
                printf("\nWe have written the question %d successfully\n\n",a);
                a++;
            }  
            printf("ADDING KEY\n====== ===\n");//adding answer key of the quiz//
            int ss;
            fp=fopen("answer.txt","w");
            for(int k=1;k<=h;k++){
                printf("enter the correct option for question %d:\t",k);
                scanf("%d",&ss);
                putw(ss,fp);
            }
            fclose(fp);
            printf("done!!\nclick enter\n\n\n");
            // goto label;
        }
        else if(tres==2){
            system("cls");
            FILE* fp;
            fp=fopen("report.txt","r");
            //views report//
            fseek (fp, 0, SEEK_END);
            int size = ftell(fp);
            if (0 == size) {
                printf("No one attempted the test yet...Press any key.");
                fclose(fp);
                getch();
                goto label1;
            }
            else{
                fp=fopen("report.txt","r");
                printf("\n\nSHOWING STUDENT REPORT\n");
                printf("======= ======= ======\n\n");
                printf("ROLLNO\tNAME\t\t\t\tMARKS\n");
                printf("======\t====\t\t\t\t=====\n");

                char c = fgetc(fp);
                while (c != EOF) { 
                    printf ("%c", c); 
                    c = fgetc(fp); 
                } 
                fclose(fp);
                // printf("\n\nMISSION ACCOMPLISHED\nA CHANDU OLLALA PRESENTATION\n\n");
                char ch;
                printf("\n\nPress 1 to exit app and clear the report...>>>>\t\t\n");
                printf("Press 2 to exit app without clearing the report...>>>>\t\t");
                printf("\nPress 3 to go back to main menu...>>>>\t\t\n");
                printf("Enter your choice:");
                ch=getch();
                if(ch=='1'){
                    fp=fopen("report.txt","w");//clears everything in text file//
                    fclose(fp);
                    exit(0);
                }
                else if(ch=='2'){
                    exit(0);//exits program//
                }
                else if(ch=='3'){
                    goto label1;
                }
            }
        }
        else{
            system("cls");
            printf("Invalid Choice...Press any key.");
            getch();
            goto label1;
        }
    }
    else{
        printf("Wrong Password...Press any key to continue.");
        getch();
        goto label2;
    }
}
int startquiz()
{
    //quiz started//
    char c;
    int tq,marks=0;
    
    FILE *fp,*fp1,*fp2;
    fp1=fopen("tques.txt","r");
    tq=getw(fp1);
    fclose(fp1);
    fp=fopen("ques.txt","r");

    c = fgetc(fp); 
    while (c!=EOF) 
    { 
        printf ("%c", c); 
        c = fgetc(fp); 
    } 
    fclose(fp);
    int a[tq],d[tq],i=0;
    for(i=0;i<tq;i++){
        printf("\nEnter Question-%d answer:",i+1);
        scanf("%d",&a[i]);
    }
    fp2=fopen("answer.txt","r");
    i=0;
    d[i]=getw(fp2);
    while (d[i]!=EOF){
        i++;  
        d[i] = getw(fp2); 
    }
    for(i=0;i<tq;i++){
        if(a[i]==d[i]){
            marks++;
        }
    }
    printf("answers are evaluated.\n\n");
    printf(">>YOUR SCORE=\t%d\n",marks);
    return marks;
}