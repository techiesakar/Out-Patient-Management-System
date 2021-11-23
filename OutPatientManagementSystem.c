#include<stdio.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#define true 1
#define false 0
#define ENTER 13
#define BKSP 8
#define TAB 9
#define SPACE 32

int get_size();
void adminRegistration();
void encrypt();
void forgetPassword();
void adminPanel();
void mainMenu();
void welcomeScreen();
void credit();
void changePassword();
void thankyou();
void fullScreen();

void fullScreen() {
	// This makes the application open in fullscreen
	keybd_event(VK_MENU,0x38,0,0);
	keybd_event(VK_RETURN,0x1c,0,0);
	keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
	keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
}

// For AdminPanel Function
void addRecord();
void addRecordItem();
void viewRecord();
int listLoopRow(int row);
void tableHead();
void searchRecord();
void editRecord();
void deleteRecord();


void gotoxy(short x, short y) {
	// For placing (x,y) co-ordinate
	COORD pos = {x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}


struct patient {
	// defining structure for patient
	char firstName[20], lastName[20];
	char add[100],sex[10], problem[20],depart[20], consultant[10], registeredDate[10];
	int patientno,age;
	char phone[12];
	float ticketFees,misc;
};
struct patient p;


int main () {
	fullScreen();
	mainMenu();
}

//Functions
int get_size(const char* file_name) {
	FILE *file = fopen(file_name, "r");
	if(file == NULL)
		return 0;
	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	fclose(file);
	return size;
}

//Password Encryption
void encrypt(char password[], int key) {
	unsigned int i;
	for(i=0; i<strlen(password); ++i) {
		password[i] = password[i] - key;
	}
}

void welcomeScreen() {
	system("cls");
	printf("\n\n\n\n\n\n\t\t___________________________________________________________________________________________________________________________________________________________________________________");
	printf("\n\n\t\t\t\t\t\t\t\t\t\t\t       Welcome To       \t");
	printf("\n\t\t\t\t\t\t\t\t\t\t\tOutPatient Management System\t");
	printf("\n\t\t\t\t\t\t\t\t\t\t\t       ABC Hospital    \t\t");
	printf("\n\t\t___________________________________________________________________________________________________________________________________________________________________________________");
}

void credit() {
	welcomeScreen();
	gotoxy(59,14);
	printf("SPECIAL THANKS TO PROJECT'S CONTRIBUTORS");
	gotoxy(66,16);
	printf("Sakar Aryal - Team Leader");
	gotoxy(69,18);
	printf("Pawan Chaudhary");
	gotoxy(69,20);
	printf("Sandhya Khadka");
	gotoxy(70,22);
	printf("Himal Aryal");
	printf("\n\t\t\t\t_____________________________________________________________________________________________");
	printf("\n\n\t\t\t\t\t\t\tFor Source Code: Visit github.com/techiesakar");
	printf("\n\n\t\t\t\t\t\t\t\tPress any key to continue...");
	getch();
	mainMenu();
}

void thankyou() {
	system("cls");
	printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t...THANK YOU FOR VISITING...");
	printf("\n\n\t\t\t\t\t\tFor Source Code: Visit github.com/techiesakar");
	printf("\n\n\t\t\t\t________________________________________________________________________________");
	printf("\n\n\t\t\t\t\t\t   ...Press any key to close the program...");
	printf("\n\n\n");
	getch();
}

void adminRegistration() {
	// If user exist, then login if not then register user
	char username[20], password[20], petName[20];
	FILE *pass;
	if ((pass = fopen("password.txt", "r")) == NULL || get_size("password.txt")==0 ) {
		pass = fopen("password.txt", "w");
		welcomeScreen();
		printf("\n\n\t\t\t\t\t\t\tUpdating New Details");
		printf("\n\n\t\t\t\t\t\t\tUsername       : ");
		scanf("%s", username);
		//	For Password
		int i = 0;
		char ch;
		printf("\n\t\t\t\t\t\t\tPassword       : ");
		while(1) {
			ch = getch();
			if(ch==ENTER) {
				password[i]='\0';
				break;
			} else if (ch==BKSP) {
				if(i>0) {
					i--;
					printf("\b \b");
				}
			} else if (ch==TAB || ch==SPACE) {
				continue;
			} else {
				password[i]=ch;
				i++;
				printf("*");
			}
		}
		encrypt(password,0xFACA);
		printf("\n\n\t\t\t\t\t\t\tEnter Security Questions Answer");
		printf("\n\n\t\t\t\t\t\t\tPet's Name     : ");
		scanf("%s", petName);
		fprintf(pass, "%s\t%s\t%s",username,password,petName);
		fclose(pass);
		printf("\n\n\t\t\t\t\t\t\tACCOUNT CREATED SUCCESSFULLY");
		printf("\n\n\t\t\t\t\t\t\t....Enter any key to continue... ");
		getch();
		mainMenu();
	}

	else {
		int count = 4;
		do {
			int i = 0;
			char ch;
			char temp_username[30];
			char temp_password[30];
			welcomeScreen();
			if(count<4) {
				printf("\n\n\t\t\t\t\t\t\tYou've %d more attempts left : ", count);
			}
			printf("\n\n\t\t\t\t\t\t\tLogin To Your Account");
			printf("\n\n\t\t\t\t\t\t\tEnter Username : ");
			scanf("%s", temp_username);
			printf("\n\t\t\t\t\t\t\tEnter Password: ");
			while(1) {
				ch = getch();
				if(ch==ENTER) {
					temp_password[i]='\0';
					break;
				} else if (ch==BKSP) {
					if(i>0) {
						i--;
						printf("\b \b");
					}
				} else if (ch==TAB || ch==SPACE) {
					continue;
				} else {
					temp_password[i]=ch;
					i++;
					printf("*");
				}
			}
			encrypt(temp_password,0xFACA);
			pass=fopen("password.txt","r");
			fscanf(pass,"%s\t%s%s",username, password, petName);
			if(strcmp(password, temp_password)==0 && strcmp(username,temp_username)==0) {
				adminPanel();
				break;
			} else {
				printf("\n\n\t\t\t\t\t\tOops...Either username or password may incorrect");
				printf("\n\n\t\t\t\t\t\tEnter any key to continue... ");
				getch();
			}
			count--;
			if(count<=0) {
				mainMenu();
			}
		} while(count>0);
	}
	fclose(pass);

} // Registration ends

void forgetPassword() {
	// Ask username and pet's name to rest password
	int count = 4;
	do {
		char username[20], password[20], petName[20], temp_username[20], temp_petName[20];
		FILE *pass;
		pass=fopen("password.txt","r");
		welcomeScreen();
		fscanf(pass,"%s\t%s\t%s",username, password, petName);
		if(count<4) {
			printf("\n\n\t\t\t\t\t\t\tYou've %d more attempt left", count);
		}
		printf("\n\n\t\t\t\t\t\t\tForget Password");
		printf("\n\n\t\t\t\t\t\t\tConfirm Username : ");
		scanf("%s", temp_username);
		printf("\n\t\t\t\t\t\t\tConfirm your pet's name : ");
		scanf("%s", temp_petName);
		if(strcmp(temp_petName, petName)==0&&strcmp(temp_username,username)==0) {
			fclose(pass);
			pass=fopen("password.txt","w");
			fclose(pass);
			adminRegistration();
			break;
		} else {
			printf("\n\n\t\t\t\t\t\t\tSorry !! Detailed not matched");
			printf("\n\n\t\t\t\t\t\t\t...Enter any key to continue...");
			getch();
		}
		count--;
		if(count<=0) {
			fclose(pass);
			mainMenu();
			break;
		}
	} while(count>0);
}
void changePassword() {
	// Erase existing record and register account again
	FILE *pass;
	pass=fopen("password.txt","w");
	fclose(pass);
	adminRegistration();
}
void adminPanel() {
	// Display all the available options for admin
	welcomeScreen();
	int choice;
	printf("\n\n\n\t\t\t\t1. Add Record");
	printf("\n\n\t\t\t\t2. Display Record");
	printf("\n\n\t\t\t\t3. Update Record");
	printf("\n\n\t\t\t\t4. Search Record");
	printf("\n\n\t\t\t\t5. Delete Record");
	printf("\n\n\t\t\t\t6. Update Admin's Details");
	printf("\n\n\t\t\t\t7. Terminate Program");
	printf("\n\n\t\t\t\t0. Logout");
	printf("\n\n\t\t\t\tEnter your choice... ");
	int ch;
	scanf("%d", &ch);
	switch(ch) {
		case 1:
			addRecord();
			break;
		case 2:
			viewRecord();
			break;
		case 3:
			editRecord();
			break;
		case 4:
			searchRecord();
			break;
		case 5:
			deleteRecord();
			break;
		case 6:
			changePassword();
			break;
		case 0:
			mainMenu();
			break;
		default:
			thankyou();
			break;
	}
}

void mainMenu() {
	// This will show before getting logged in
	welcomeScreen();
	int choice;
	printf("\n\n\n\t\t\t\t1. Register/Login");
	printf("\n\n\t\t\t\t2. Forget Password");
	printf("\n\n\t\t\t\t3. Credit");
	printf("\n\n\t\t\t\t4. Exit Program");
	printf("\n\n\t\t\t\tEnter your choice... ");
	int ch;
	scanf("%d", &ch);
	switch(ch) {
		case 1:
			adminRegistration(); // Register or Login
			break;
		case 2:
			if(get_size("password.txt")==0) {
				welcomeScreen();
				printf("\n\n\n\t\t\t\t\t\t\tYou've not registered yet");
				printf("\n\n\t\t\t\t\t\t   ...Enter any key to continue... ");
				getch();
				mainMenu();
			} else
				forgetPassword();
			break;
		case 3:
			credit();
			break;
		case 4:
			thankyou();
			break;
		default:
			fflush(stdin);
			mainMenu();
			break;
	}
}

void addRecord() {
	// Add patient - only available for logged in user
	system("cls");
	welcomeScreen();
	char ans;
	FILE *fp;
	fp = fopen("patient.txt","a+"); // open file in append mode
	if (!fp) {
		printf("\n\t Can not open file\n");
		exit(0);
	}

// Auto assign unique patient ID for new patient
	int patientID;
	int count = 0;
	while(fscanf(fp,"%s%s%s%s%d%d%s%s%s%s%f%f%s",p.firstName, p.lastName,p.add,p.sex,&p.age,&p.patientno,&p.phone,p.problem,p.depart,p.consultant,&p.ticketFees,&p.misc,p.registeredDate)!=EOF) {
		count++;
		if (count!=0) {
			patientID = p.patientno+1;
		} else {
			patientID = 0;
		}
	}
	p.patientno = patientID;


	// Auto assign date to new user
	char currentDate[10];
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	sprintf(currentDate, "%d-%d-%d", tm.tm_year+1900,tm.tm_mon + 1,tm.tm_mday);
	strcpy(p.registeredDate, currentDate );
	// Date Ends

	addRecordItem(); // Add patient's all data
	fprintf(fp,"%s\t%s\t%s\t%s\t%d\t%d\t%s\t%s\t%s\t%s\t%f\t%f\t%s\n",p.firstName, p.lastName,p.add, p.sex, p.age, p.patientno, p.phone,p.problem,p.depart,p.consultant, p.ticketFees, p.misc,p.registeredDate);
	printf("\n\n\t\t\t.....Information Record Successful ...");
	fclose(fp); // closing file pointer after successfull record entry
	getch(); // hold screen
	printf("\n\n\t\t\tDo you want to add more [Y/N]?? "); // Asking user, if they want to add more record
	fflush(stdin);
	scanf("%c", &ans);
	if (toupper(ans)=='Y')
		addRecord(); // If user wants, again calling addRecord();
	else if (toupper(ans)=='N') {
		adminPanel(); // If user don't want, then go back to home
	}
}
void addRecordItem(void) {
	// Read all details from patient
	int i, departID;

	char doctor[10][10] = {
		// Readymade doctor
		"Siddharth","Dipson","Simpal","Madhav","Sima","Sia","Poonam","Anuj","Yadav","Bhuwan"
	};
	char department[20][20]= {
		// Readymade department
		"Ortho","ENT","Radiology","Dental","Dermatalogy","Physiology","Neurology","Therapy","Urology","Cardiology"
	};
	fflush(stdin);
	gotoxy(85,15);
	printf("Available Department List\n");
	for(i=0; i<10; i++) {
		gotoxy(85,17+i);
		printf("%d   %s", i, department[i]);
	}
	gotoxy(20,15);
	printf("\t\t\t******** Add Patients Record ********");
	fflush(stdin);
	printf("\n\n\t\t\t\tFirst Name: ");
	scanf("%s",p.firstName);
	p.firstName[0]=toupper(p.firstName[0]);
	fflush(stdin);
	printf("\n\t\t\t\tLast Name: ");
	scanf("%s",p.lastName);
	p.lastName[0]=toupper(p.lastName[0]);
	fflush(stdin);
	printf("\n\t\t\t\tAddress: ");
	scanf("%s",p.add);
	p.add[0]=toupper(p.add[0]);
	fflush(stdin);
	printf("\n\t\t\t\tGender[M|F]:");
	scanf("%s",p.sex);
	fflush(stdin);
//	gets(p.sex);
	p.sex[0]=toupper(p.sex[0]);

	printf("\n\t\t\t\tAge: ");
	scanf("%d",&p.age);
	printf("\n\t\t\t\tPhone Number: ");
	scanf("%s",p.phone);
	fflush(stdin);
	printf("\n\t\t\t\tProblem: ");
	scanf("%s",p.problem);
	fflush(stdin);
	p.problem[0]=toupper(p.problem[0]);
	printf("\n\t\t\t\tDepart ID: ");
	scanf("%d",&departID);

	for(i=0; i<10; i++) {
		// Auto assign department and doctor using departID
		if(departID==i) {
			strcpy(p.depart, department[i]);
			strcpy(p.consultant, doctor[i]);
			break;
		} else {
			strcpy(p.depart, "Invalid");
			strcpy(p.consultant, "Invalid");
		}
	}
	printf("\n\t\t\t\tTicket Charge:");
	scanf("%f",&p.ticketFees);
	printf("\n\t\t\t\tMiscellaneous Charge:");
	scanf("%f",&p.misc);

} // addRecordItem ends

void tableHead() {
	gotoxy(11,15);
	printf(" _____________________________________________________________________________________________________________________________________________________________________________________");
	gotoxy(11,16);
	printf("|");
	gotoxy(15,17);
	printf("ID");
	gotoxy(20,17);
	printf("FULL NAME");
	gotoxy(40,17);
	printf("ADDRESS");
	gotoxy(55,17);
	printf("GENDER");
	gotoxy(65,17);
	printf("AGE");
	gotoxy(70,17);
	printf("PHONE NUMBER");
	gotoxy(85,17);
	printf("PROBLEM");
	gotoxy(100,17);
	printf("DEPART");
	gotoxy(115,17);
	printf("CONSULTANT");
	gotoxy(130,17);
	printf("TICKET FEES");
	gotoxy(145,17);
	printf("OTHER FEES");
	gotoxy(160,17);
	printf("TOTAL FEES");
	gotoxy(175, 17);
	printf("Registered Date");
	gotoxy(193,16);
	printf("|");
	gotoxy(193,17);
	printf("|");
	gotoxy(193,18);
	printf("|");
	gotoxy(11,17);
	printf("|");
	gotoxy(11,18);
	printf("|");
	gotoxy(12,18);
	printf("_____________________________________________________________________________________________________________________________________________________________________________________");
} // Heading of records
int listLoopRow(int row) {
	// Used inside while loop, to print the user's record in each line
	gotoxy(15,row);
	printf("%i", p.patientno);
	gotoxy(20,row);
	printf("%s %s", p.firstName, p.lastName);
	gotoxy(40,row);
	printf("%s", p.add);
	gotoxy(55,row);
	printf("%s", p.sex);
	gotoxy(65,row);
	printf("%d", p.age);
	gotoxy(70,row);
	printf("%s", p.phone);
	gotoxy(85,row);
	printf(" %s", p.problem);
	gotoxy(100,row);
	printf("%s", p.depart);
	gotoxy(115,row);
	printf("Dr. %s", p.consultant);
	gotoxy(130,row);
	printf("%.2f", p.ticketFees);
	gotoxy(145,row);
	printf("%.2f", p.misc);
	gotoxy(160,row);
	printf("%.2f", p.misc+p.ticketFees);
	gotoxy(175,row);
	printf("%s", p.registeredDate);
} // listLoopRow Ends

void viewRecord() {
	int totalMember;
	int row = 20;
	system("cls");
	FILE *fp;
	if((fp=fopen("patient.txt","r"))==NULL) {
		welcomeScreen();
		printf("\n\n\t\t\t\t    Enter any key to continue...");
		getch();
		welcomeScreen();
	}
	welcomeScreen();
	tableHead();
	while(fscanf(fp,"%s%s%s%s%d%d%s%s%s%s%f%f%s",p.firstName, p.lastName,p.add,p.sex,&p.age,&p.patientno,&p.phone,p.problem,p.depart,p.consultant,&p.ticketFees,&p.misc,p.registeredDate)!=EOF) {
		listLoopRow(row);
		row++;
	}
	printf("\n\n\t    ______________________________________________________________________________________________________________________________________________________________________________________");
	fclose(fp); // Closing file ponter after displaying record
	printf("\n\n\t\t\t\t    Enter any key to continue..."); // Asking user to press any key
	getch(); // Hold screen until user press any key
	welcomeScreen();
	adminPanel();// Takes back to main screen
} // ViewRecord Ends

void searchRecord(void) {
	welcomeScreen();
	int searchID;
	FILE *fp;
	int row = 20;
	char ans;
	int count = 0; // It is used to show total available records
	fp = fopen("patient.txt","r"); // open file in read mode
	printf("\n\n\n\t\t\t\t************************** ABC Hospital - Search Patient *************************\n");
	gotoxy(12,16);
	fflush(stdin);
	printf("\n\t\t\t\t\t Enter Patient's ID : ");
	scanf("%i",&searchID); // Takes user ID for search
	welcomeScreen(); // Once data read, clearing screen again
	printf("\n\n\n\t\t\t\t\t\t\t\tPatient Searched For : %i", searchID );
	tableHead();

	while(fscanf(fp,"%s%s%s%s%d%d%s%s%s%s%f%f%s",p.firstName, p.lastName,p.add,p.sex,&p.age,&p.patientno,&p.phone,p.problem,p.depart,p.consultant,&p.ticketFees,&p.misc,p.registeredDate)!=EOF) {
		if(p.patientno == searchID) {
			listLoopRow(row); // It takes row = 12 at first and row++ later
			row++; // Display the available results in row of each patient
			count++; // increasing count value after each successfull finding of ID
		}
	}
	printf("\n\n\t    ______________________________________________________________________________________________________________________________________________________________________________________");

	printf("\n\n\t\t\t\t\t\tTotal Patients found : %d", count);
	fclose(fp); // closing file pointer

searchAgain:
	printf("\n\n\t\t\t\t\t   Enter any key to continue...");
	getch();
	printf("\n\n\t\t\t\t\t   Do you want to view more [Y/N]?? ");
	scanf(" %c", &ans);
	if (toupper(ans)=='Y')
		searchRecord(); // If user want to search more, then again call searchRecord()
	else if (toupper(ans)=='N') {
		adminPanel(); // If not, Go back to main memu
	} else {
		printf("\n\tInvalid Input. \n");
		goto searchAgain;
	}
} // searchRecord ends

void editRecord() {
	welcomeScreen();
	int searchID;
	int valid = 0;
	FILE *fp, *tf;
	int row = 20;
	char ans;
	printf("\n\n\n\t\t\t\t************************** ABC Hospital - Edit Patient's Record *************************\n");

	if((fp=fopen("patient.txt","r"))==NULL) {
		welcomeScreen();
		printf("\n\n\t\t\t\t File is empty...");
		printf("\n\n\t\t\t\tEnter any key to continue...");
		getch();
		fclose(fp);
		welcomeScreen();
		adminPanel();
	} else {
		tf=fopen("temp_patient.txt","w+");
		gotoxy(12,16);
		fflush(stdin);
		printf("\n\t\t\t\t\t Enter Patient's ID : ");
		scanf("%i",&searchID);
		welcomeScreen();
		if (tf==NULL) {
			printf("\n\n\t\t\t\t\t Cannot Open File !!");
			adminPanel();
		}

		while(fscanf(fp,"%s%s%s%s%d%d%s%s%s%s%f%f%s",p.firstName, p.lastName,p.add,p.sex,&p.age,&p.patientno,&p.phone,p.problem,p.depart,p.consultant,&p.ticketFees,&p.misc,p.registeredDate)!=EOF) {
			if(p.patientno == searchID) {
				valid = 1;
				welcomeScreen();
				printf("\n\n\n\t\t\t\t\t\t\t\tPatient Searched For : %i", searchID );
				tableHead();
				listLoopRow(row);
				row++;
				printf("\n\n\t\t\t\tEnter any key to continue...");
				getch();
				welcomeScreen();
				addRecordItem();
				fprintf(tf,"%s\t%s\t%s\t%s\t%d\t%d\t%s\t%s\t%s\t%s\t%f\t%f\t%s\n",p.firstName, p.lastName,p.add, p.sex, p.age, p.patientno, p.phone,p.problem,p.depart,p.consultant, p.ticketFees, p.misc,p.registeredDate);
				printf("\n\n\t\t\t\tUpdated Successfully");
			} else {
				fprintf(tf,"%s\t%s\t%s\t%s\t%d\t%d\t%s\t%s\t%s\t%s\t%f\t%f\t%s\n",p.firstName, p.lastName,p.add, p.sex, p.age, p.patientno, p.phone,p.problem,p.depart,p.consultant, p.ticketFees, p.misc,p.registeredDate);
			}
		}
		if(!valid) {
			printf("\n\n\t\t\t\tNo record found");
		}
		fclose(tf);
		fclose(fp);
		remove("patient.txt"); // remove existing file
		rename("temp_patient.txt","patient.txt"); // Renaming temporaty file to original name
		getch();
		adminPanel(); // Go back to main memu
	}
} // edit record ends
void deleteRecord() {
	welcomeScreen();
	int searchID;
	int confirmID, found = false;
	int confirm;
	int valid = 0;
	FILE *fp, *tf;
	int row = 20;
	char ans;
	printf("\n\n\n\t\t\t\t************************** ABC Hospital - Delete Patient's Record *************************\n");
	if((fp=fopen("patient.txt","r"))==NULL) {
		welcomeScreen();
		printf("\n\n\t\t\t\t File is empty...");
		printf("\n\n\t\t\t\tEnter any key to continue...");
		getch();
		welcomeScreen();
		adminPanel();
	}
	tf=fopen("temp_patient.txt","w+");
	gotoxy(12,16);
	fflush(stdin);
	printf("\n\t\t\t\t\t Enter Patient's ID : ");
	scanf("%i",&searchID);
	printf("\n\n\t\t\t\t\t Enter ID again to confirm : ");
	scanf("%i", &confirmID); // To confirm with search ID entered before
	if(searchID==confirmID) {
		confirm = true;
		while(fscanf(fp,"%s%s%s%s%d%d%s%s%s%s%f%f%s",p.firstName, p.lastName,p.add,p.sex,&p.age,&p.patientno,&p.phone,p.problem,p.depart,p.consultant,&p.ticketFees,&p.misc,p.registeredDate)!=EOF) {
			if(confirmID!=p.patientno) {
				fprintf(tf,"%s\t%s\t%s\t%s\t%d\t%d\t%s\t%s\t%s\t%s\t%f\t%f\t%s\n",p.firstName, p.lastName,p.add, p.sex, p.age, p.patientno, p.phone,p.problem,p.depart,p.consultant, p.ticketFees, p.misc,p.registeredDate);
			} else {
				found=true; // record found
			}
		}

	} else {
		confirm = false;
	}
	if(!confirm || !found) {
		fclose(fp);
		fclose(tf);
		remove("temp_patient.txt");
		if(!confirm) {
			printf("\n\n\t\t\t\t\t You couldn't confirm ID ");
		} else if (!found) {
			printf("\n\n\t\t\t\t\t Record not found ");
		}
		printf("\n\n\t\t\t\tEnter any key to continue...");
		getch();
		welcomeScreen();
		adminPanel();
	}
	if(found) {
		printf("\n\n\t\t\t\t\t Record Deleted Successfully !!");
		// close all file pointer
		fclose(fp);
		fclose(tf);
		remove("patient.txt"); // remove existing file
		// change temporary file to original name
		rename("temp_patient.txt","patient.txt");
		printf("\n\n\t\t\t\t\t Enter any key to continue : ");
		getch();
		welcomeScreen();
		viewRecord();
	}
} // Delete record ends