#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>

// Convert to uppercase
void upper(char s[]) 
{
    for(int i=0;s[i];i++)
        if(s[i]>='a' && s[i]<='z')
            s[i]-=32;
}

// Convert to lowercase
void lower(char s[])
{
    for(int i=0; s[i]; i++)
        if(s[i]>='A' && s[i]<='Z')
            s[i]+=32;
}

void help() 
{
    printf
    (
        "\n----- COMMAND MENU -----\n"
        "01. Show directory\n"
        "02. Show username\n"
        "03. Show computer name\n"
        "04. Show date & time\n"
        "05. Print text\n"
        "06. Count characters\n"
        "07. Compare strings\n"
        "08. Copy text\n"
        "09. Join texts\n"
        "10. Uppercase text\n"
        "11. Lowercase text\n"
        "12. Reverse text\n"
        "13. Add numbers\n"
        "14. Show menu\n"
        "15. Quit program\n"
        "------------------------\n"
    );
}


int main() {
    int choice;
    char text1[50], text2[50], cwd[1024];
    int num1, num2;

    printf("Mini Shell Program (Integer Choice)\n");
    help();

    while(1) 
    {
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        if(choice==1) 
        {
            getcwd(cwd, sizeof(cwd));
            printf("%s\n", cwd);
        }
        else if(choice==2) 
        {
            char *user=getenv("USER");
            printf("%s\n", user);
        }
        else if(choice==3) 
        {
            gethostname(text1, sizeof(text1));
            printf("%s\n", text1);
        }
        else if(choice==4) 
        {
            time_t t =time(NULL);
            printf("%s", ctime(&t));
        }
        else if(choice==5) 
        {
            printf("Enter text: ");
            scanf(" %[^\n]", text1);
            printf("%s\n", text1);
        }
        else if(choice==6) 
        {
            printf("Enter text: ");
            scanf("%s", text1);
            printf("Length: %lu\n", strlen(text1));
        }
        else if(choice==7) 
        {
            printf("Enter two strings: ");
            scanf("%s %s", text1, text2);
            if(strcmp(text1, text2)==0)
                printf("Same\n");
            else
                printf("Different\n");
        }
        else if(choice==8) 
        {
            printf("Enter text: ");
            scanf("%s", text1);
            strcpy(text2, text1);
            printf("Copied: %s\n", text2);
        }
        else if(choice==9) 
        {
            printf("Enter two texts: ");
            scanf("%s %s", text1, text2);
            strcat(text1, text2);
            printf("Result: %s\n", text1);
        }
        else if(choice==10) 
        {
            printf("Enter text: ");
            scanf("%s", text1);
            upper(text1);
            printf("%s\n", text1);
        }
        else if(choice==11) 
        {
            printf("Enter text: ");
            scanf("%s", text1);
            lower(text1);
            printf("%s\n", text1);
        }
        else if(choice==12) 
        {
            printf("Enter text: ");
            scanf("%s", text1);
            int len=strlen(text1);
            for(int i=0; i<len/2; i++) {
                char temp=text1[i];
                text1[i]=text1[len-i-1];
                text1[len-i-1]=temp;
            }
            printf("%s\n", text1);
        }
        else if(choice==13) 
        {
            printf("Enter two numbers: ");
            scanf("%d %d", &num1, &num2);
            printf("Sum: %d\n",num1+num2);
        }
        else if(choice==14) 
        {
            help();
        }
        else if(choice==15) 
        {
            printf("Bye!\n");
            break;
        }
        else 
        {
            printf("Invalid choice\n");
        }
    }
    return 0;
}
