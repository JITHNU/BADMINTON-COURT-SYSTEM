/****************************************
Student_Number: PS/2021/114
Student_Name: W.J.E.S.V.WEERASINGHE
Group_Number: Group 08
Assignment 02
Purpose: Manage the Reservation system  for Badminton Court and Court availability.
*****************************************/


#include <stdio.h> //include the libraries here
#include <stdlib.h>
#include <string.h>

int login(); //declared the variables
int registration();
void main_menu();
void display(int count);



struct details  //call structure for logging system
{
    char fname[30];
    char lname[30];
    char stname[30];
    char mail[50];
    char id[11];
};



int main()
{
    while (1)
    {
        int count = 0;
        main_menu(count);
    }

}


void main_menu(int count) //function call
{
    int option,reg_status = 1,login_status = 1;

    printf("\n\n---------------------------------------------------------------------------------------------------\n");
    printf("=================================== WELCOME TO UOK BADMINTON COURT ================================\n");
    printf("---------------------------------------------------------------------------------------------------\n");
    printf("\n\n1) Continue Playing \n"); //Login option for already members of court
    printf("2) New PLayer \n");  //Registration optin for new Players
    printf("\n");
    printf("Enter Option:");
    scanf("%d",&option);
    switch (option)
    {
    case 1:
        while (login_status)
        {
            login_status = login();
            if(login_status == 0)
            {
                printf("\n************* Login Successfully ************* \n");
                printf("\n");
                display(count);
                break;
            }
            else
            {
                printf("Incorrect Login Details! \n Please enter the correct credentials\n");
            }
        }
        break;
    case 2:
        while (reg_status)
        {
            reg_status = registration();
            if(!reg_status)
            {
                display(count);
                break;
            }
            else
            {
                system("cls");
            }

        }
        break;
    default:
        break;
    }
}


int login()
{
    char stu_unimail[30],stu_id[11];
    int login_status;

    struct details login_details;

    FILE *log;
    log = fopen("login.txt","r"); //saving users login details in the login.txt file

    printf("\n\n\n---------------------------------------------------------------------------------------------------\n");
    printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Welcome Back  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    printf("---------------------------------------------------------------------------------------------------\n");
    printf("\n\nStudent_ID must be contained as YY/2021/xxx. YY is your Cource type and xxx is your last 3 number digits of your university Student_ID\n");
    printf("Enter your Student ID:"); //ask user's student_ID to logging to system
    scanf("%s",stu_id);

    if(log)
    {
         while (fscanf(log, "%s %s",login_details.id,login_details.mail) != EOF)
        {
            if (strcmp(stu_id, login_details.id) == 0)
            {
                login_status = 0;
                break;
            }
            else
            {
                login_status = 1;
            }
        }

    fclose(log);

    }
    else
    {
        printf("Error 404.. File Not Found....\n\n");
        //system("CLS");
    }
    return login_status;
}

void displayStudentDetails(struct details reg_details) {
    printf("\nStudent Email: %s \n", reg_details.mail);
    printf("Student ID: %s \n", reg_details.id);
}

int registration()
{
    char firstname[15];
    int reg_status;
    FILE *log;
    log=fopen("login.txt","a"); //open the login.txt file

    struct details reg_details;

    printf("\n\nPlease provide the below details for registration.\n"); //Getting user's details for registration
    printf("\nEnter Your First Name: \n");
    scanf("%s",reg_details.fname);
    printf("\nEnter Your Surname: \n");
    scanf("%s",reg_details.lname);
    printf("\n\nStudent_ID must be contained as YY/2021/xxx. YY is your Cource type and xxx is your last 3 number digits of your university Student_ID\n");
    printf("Enter Your Student_ID :\n");
    scanf("%s",reg_details.id);
    printf("\nEnter Your University Mail address :\n");
    scanf("%s",reg_details.mail);

    printf("\n\nRegistering details.....\n");
    printf("\n");

    displayStudentDetails(reg_details);

    system("cls");
    if(log)
    {
        if(fprintf(log,"\n%s %s",reg_details.id,reg_details.mail)>0)
        {
            printf("\n************************************ Registration Successful! ***********************************\n");
            reg_status = 0;
            fclose(log);
        }
        else
        {
            printf("\n------------------------------------ Registration Unsuccessful! ---------------------------------\n");

            reg_status = 1;
            fclose(log);
        }
        return reg_status;

    }
    else
    {
        printf("Error when Opening File in");
        //system("CLS");
    }
}

void incrementCount(int *count, FILE *cfp, int MAX_COUNT) {
    if(*count<MAX_COUNT){
        (*count)++;
        fprintf(cfp, "%d", *count);
    } else {
        printf("\n***Oops! The court is already full. Please come again later.***\n");
    }
}

void decrementCount(int *count, FILE *cfp) {
    if(*count>0) {
        (*count)--;
        fprintf(cfp, "%d", *count);
        printf("\nThanks for using Badminton Court for your Physical activities....\n");
        printf("Come again Soon.....\n");
    } else {
        printf("\n***The court is empty.***\n");
    }
}

void display(int count)
{
    const int MAX_COUNT = 12;
	int student;

	struct details display_details;

	FILE *cfp;
    cfp = fopen("count.txt", "a"); //append the count of playing students

    printf("\n\n---------------------------------------------------------------------------------------------------\n");
    printf("=========================== Gear up your physical fitness with badminton. =========================\n");
    printf("---------------------------------------------------------------------------------------------------\n");
    while (1) {
        printf("\n\n\n****Current number of people in the court: %d ****\n\n", count);
        printf("If you want enter the court, press ---> 1. \n");
        printf("If you want exit  the court, press ---> 2. \n");
        printf("\n");
        printf("Enter Option:");
        scanf("%d", &student);

        switch (student) //switch for counting no students playing badminton on time
        {
            case 1:
                incrementCount(&count, cfp, MAX_COUNT);
                break;

            case 2:
                decrementCount(&count, cfp);
                break;

            default:
                printf("\nInvalid option. Please enter 1 or 2.\n");
        }

    fprintf(cfp, "%d\n", count); // Append the updated count to the file
    fflush(cfp); // Flush the buffer to ensure data is written immediately

    fclose(cfp);
    main_menu(count);

   }


}

