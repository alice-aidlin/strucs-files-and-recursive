/* Assignment: 4  Campus: Ashdod Author: Alice Aidlin, ID: 206448326 */
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define N 20


typedef struct Date { int day, month, year; }Date;
typedef struct Person { char* name; Date birthday; }Person;
typedef struct Unit { char* name; Person manager; int NumOfWorkers; Person* workers; }Unit;
typedef struct Company { Person CEO; int NumOfUnits; Unit* units; }Company;


int getDate(Date* d);
int getPerson(Person* p);
int getUnit(Unit* u);
int getCompany(Company* c);

void printDate(const Date* d);
void printPerson(const Person* p);
void printUnit(const Unit* u);
void printCompany(const Company* c);

int writeToFileDate(FILE* fd, Date* d);
int writeToFilePerson(FILE* fp, Person* p);
int writeToFileUnit(FILE* fu, Unit* u);
int writeToFileCompany(FILE* fc, Company* c);

int readFromFileDate(FILE* fd, Date* d);
int readFromFilePerson(FILE* fp, Person* p);
int readFromFileUnit(FILE* fu, Unit* u);
int readFromFileCompany(FILE* fc, Company* c);

void freeUnit(Unit* u);
void freeCompany(Company* c);

int sumof(int num);
void dectobin(int num);
int bintodec(char* bin);
void bigletter(char *str, char* ostr, int iPos, int iCurrPos);

void Recursivemenu();

int main()
{ 
	int choice ,ifcompany=0;//choise for cases,ifcompany-to check if company exist
	FILE* f; 
	Company company;
	Company* p;
	Unit* unix = NULL;//for free
	p = &company;
	do {
		puts("Please enter your choice:\n1 Read a company from keyboard\n2 Read a company from file \n3 Add a department to the company \n4 Write the company to file \n5 Recursive menu \n6 Exit ");
		scanf("%d", &choice);

		switch (choice)
		{

		case 1://to create company
			if (ifcompany == 1)
			{
				freeCompany(p);
			}
			puts("enter only first name of person");
			getCompany(&company);
			ifcompany = 1;
			break;

		case 2://to create company from file
			puts("enter only first name of person");
			f = fopen("company.txt", "r");
			if (!f)
			{
				puts("can not open file");//if file faild
				exit(1);
			}
			readFromFileCompany(f, &company);
			fclose(f);
			ifcompany = 1;
			break;

		case 3://to add unit
			if (ifcompany == 1)
			{
				if (company.NumOfUnits == 0)//if there no units in company
				{
					company.units = (Unit*)malloc(sizeof(Unit));
					if (company.units == NULL)//check if there company
					{
						printf("company not exist\n");
						break;
					}
				}
				else
				{
					unix = (Unit*)realloc(company.units, sizeof(Unit) + (company.NumOfUnits * sizeof(Unit)));
					if (unix == NULL)//check if company exist
					{
						printf("company not exist\n");
						break;

					}
					else
						company.units = unix;
				}
				++company.NumOfUnits;//for add


				getUnit(&company.units[company.NumOfUnits - 1]);
			}
			else
			{
				puts("company not exist");//if companu not exixst
			}
		     break;
			 
		case 4://write to file
		 f = fopen("company.txt", "w");
			if (!f)
				exit(1);
			if (ifcompany == 1)//if company exist
			{
				writeToFileCompany(f, p);
				fclose(f);
			}
			else//not exist
			{
				puts("ERROR! company not exist");
			}


			break;

		case 5://recursia menu
			Recursivemenu();
			break;

		case 6://to finish
			puts("good bey");
			break;



		default://if case not exist
			puts("bad input, please try again");
				break;
		}
	} 
	while (choice != 6);

	
	freeCompany(p);
	return 0;
}

int getDate(Date* d)//for info date
{
	puts("enter day month and year");
	scanf("%d%d%d", &(d->day), &(d->month), &(d->year));
	

	return 0;//if 0 mistakes return 0 (true)
}
int getPerson(Person* p)//for info persom
{
	char name[N];
	puts("enter name of person");
	scanf("%s", &name);
	p->name = (char*)malloc((strlen(name) + 1) * sizeof(char));
	if (p->name)
	{
		strcpy(p->name, name);
		puts("enter birthday");
		getDate(&(p->birthday));
	}
	else return -1;//if mistake in malloc

	return 0;//0 mistake 

}
int getUnit(Unit* u)//for info unit
{
	char name[N];//for save the name
	int i;
	puts("enter name of unit");
	scanf("%s", name);
	u->name = (char*)malloc((strlen(name) + 1) * sizeof(char));
	if (!(u->name))
	{
		return -1;//if mistake in malloc
	}

	strcpy(u->name, name);
	puts("enter manager");
	if (getPerson(&(u->manager)))
		return -1;// if mistake
	puts("enter num of workers");
	scanf("%d", &(u->NumOfWorkers));
	u->workers = (Person*)malloc((u->NumOfWorkers) * sizeof(Person));
	if (!(u->workers))//if mistake
		return -1;
	for (i = 0; i < u->NumOfWorkers; ++i)
		if (getPerson(&(u->workers[i])))
			return -1;

	return 0;
}
int getCompany(Company* c)//for info company
{
	int i;
	puts("enter CEO");
	if (getPerson(&(c->CEO)))
		return -1;
	puts("enter num of units");
	scanf("%d", &c->NumOfUnits);

	if (!(c->units = (Unit*)malloc((c->NumOfUnits)*(sizeof(Unit)))))
		return -1;

	for (i = 0; i < c->NumOfUnits; ++i)
		if (getUnit(&(c->units[i])))
			return -1;

	return 0;
}
void printDate(const Date* d) //for print date
{
	printf("%d/%d/%d\n", d->day, d->month, d->year);
	
}
void printPerson(const Person* p)//for print person
{
	printf("name: %s\nBirthday: ", p->name);
	printDate(&(p->birthday));
	printf("\n");
}
void printUnit(const Unit* u)//for peint unit
{
	int i;
	printf("name of unit: %s\nmanrger:", u->name);
	printPerson(&(u->manager));
	printf("num of workers: %d\n", u->NumOfWorkers);
	for (i = 1; i <= u->NumOfWorkers; ++i)
	{
		printf("worker %d:", i);
		printPerson(&(u->workers[i]));
	}
	printf("\n");
}
void printCompany(const Company* c)//for print company
{
	int i;
	printf("CEO;");
	printPerson(&(c->CEO));
	printf("\n");
	printf("number of units:%d\nunits:", c->NumOfUnits);
	for (i = 1; i <= c->NumOfUnits; ++i)
	{
		printf("unit %d:", i);
		printUnit(c->units + i);

	}
	printf(":\n");
}
int writeToFileDate(FILE* fd, Date* d)//print to file date
{
	fprintf(fd, "%d/%d/%d\n", d->day, d->month, d->year);
	return 0;
}
int writeToFilePerson(FILE* fp, Person* p)//print to file person
{
	fprintf(fp,"name: %s\nBirthday: ", p->name);
	writeToFileDate(fp,&(p->birthday));
	fprintf(fp,"\n");
	return 0;
}
int writeToFileUnit(FILE* fu, Unit* u)//print to file unit
{
	int i;
	fprintf(fu,"name of unit: %s\nmaneger: ", u->name);
	writeToFilePerson(fu,&(u->manager));
	fprintf(fu,"num of workers: %d\n", u->NumOfWorkers);
	for (i = 0; i < u->NumOfWorkers; ++i)
	{
		fprintf(fu,"worker %d: ", i+1);
		writeToFilePerson(fu,&(u->workers[i]));
	}
	fprintf(fu,"\n");
	return 0;

}
int writeToFileCompany(FILE* fc, Company* c)//print to file
{
	int i;
	fprintf(fc,"CEO: ");
	writeToFilePerson(fc,&(c->CEO));
	fprintf(fc,"\n");
	fprintf(fc,"number of units: %d\nunits: ", c->NumOfUnits);
	for (i = 0; i < c->NumOfUnits; ++i)
	{
		fprintf(fc,"unit %d: ", i+1);
		writeToFileUnit(fc,c->units + i);

	}
	fprintf(fc,":\n");
	return 0;
}
int readFromFileDate(FILE* fd, Date* d)//for info date from file
{
	char slesh;//for save slesh
	fscanf(fd,"%d%c%d%c%d", &(d->day),&slesh, &(d->month),&slesh, &(d->year));
	return 0;
}
int readFromFilePerson(FILE* fp, Person* p)//for info person from file
{
	char name[N], temp[N];//name for save the name, temp for save what we dont need
	fscanf(fp,"%s", name);//scan "name:"
	fscanf(fp, "%s", name);//to scan the actual name

	p->name = (char*)malloc((strlen(name) + 1) * sizeof(char));
	if (p->name)
	{
		strcpy(p->name, name);
		fscanf(fp, "%s", temp);//scan birthday
		readFromFileDate(fp,&(p->birthday));
	}
	else return -1;//if mistake in malloc

	return 0;
}
int readFromFileUnit(FILE* fu, Unit* u)
{
	char name[N],temp[N];//name for save the name, temp for save what we dont need
	int i;

	fscanf(fu,"%s", name);//scan name
	fscanf(fu,"%s", name);//scan of
	fscanf(fu,"%s", name);//scan units
	fscanf(fu,"%s", name);//scan name finally!!!!
	u->name = (char*)malloc((strlen(name) + 1) * sizeof(char));
	if (!(u->name))
	{
		return -1;//if mistake in malloc
	}
	strcpy(u->name, name);
	fscanf(fu, "%s", temp);//scan manager
	if (readFromFilePerson(fu, &(u->manager)))
		return -1;// mistake
	
	fscanf(fu, "%s", temp);//scan num
	fscanf(fu, "%s", temp);//scan of
	fscanf(fu, "%s", temp);//scan workers


	fscanf(fu, "%d", &(u->NumOfWorkers));
	if (u->NumOfWorkers == 0)
		u->workers = NULL;
	else
	{
		u->workers = (Person*)malloc((u->NumOfWorkers) * sizeof(Person));
		if (!(u->workers))//if mistake
			return -1;

		for (i = 0; i < u->NumOfWorkers; ++i)
		{
			fscanf(fu, "%s", temp);//scan worker
			fscanf(fu, "%s", temp);//scan i:
			if (readFromFilePerson(fu, &(u->workers[i])))
				return -1;
		}
	}
	
	return 0;
}
int readFromFileCompany(FILE* fc, Company* c)
{
	int i;
	char temp[N];//for save what wo dont need

	fscanf(fc, "%s", temp);//scan CEO
	if (readFromFilePerson(fc, &(c->CEO)))
		return -1;
	fscanf(fc, "%s", temp);//scan num
	fscanf(fc, "%s", temp);//scan of
	fscanf(fc, "%s", temp);//scan units

	fscanf(fc, "%d", &c->NumOfUnits);
	if (c->NumOfUnits==0)
	{
		c->units = NULL;
	}
	else
	{
		if (!(c->units = (Unit*)malloc((c->NumOfUnits)*(sizeof(Unit)))))
			return -1;
		fscanf(fc, "%s", temp);//scan units
		for (i = 0; i < c->NumOfUnits; ++i)
		{
			fscanf(fc, "%s", temp);//scan unit
			fscanf(fc, "%s", temp);//scan i:
			if (readFromFileUnit(fc, &(c->units[i])))
				return -1;
		}
	}
	if (!(c->units = (Unit*)malloc((c->NumOfUnits)*(sizeof(Unit)))))
		return -1;
	fscanf(fc, "%s", temp);//scan units
	for (i = 0; i < c->NumOfUnits; ++i)
	{
		fscanf(fc, "%s", temp);//scan unit
		fscanf(fc, "%s", temp);//scan i:
		if (readFromFileUnit(fc, &(c->units[i])))
			return -1;
	}
	return 0;
}
int sumof(int num)//recursia 1
{
	int sum=0;//for result
	if (num==0)
		return num;
	else
	{

		if ((num % 10) % 2 == 0)//if even
		{
			sum = sumof(num / 10) + (num % 10);
				
		}
		else//if odd
		{
			sum = sumof(num / 10) - (num % 10);
		}
		return sum;
			
	}
	
}
void dectobin(int num)//function rekursia 2 from dec to bin
{
	if (num < 1)
		return;
	
	dectobin(num / 2);
	printf("%d", num % 2);	
}
int bintodec(char* bin)//function rekursia 3 from bun to dec
{
	int digit,sum;//digid for save every digit, sum for save the result
	if (*bin == '\0')
		return 0;
	if (*bin != '1' && *bin != '0')
		return -1;//if mistake!!!!
	digit = (int)*bin - '0';
	sum = bintodec(bin + 1);
	if (sum != -1)
		return digit * pow(2, (strlen(bin) - 1)) + sum;
	else return sum;

}
void bigletter(char *str, char* Nstr, int i, int n)//function recursia 4.i for index of the string, n for index of new string of big letters
{
	if (str[i]!='\0')//if the sentens exist
	{
		if ((str[i] >= 'A' && str[i] <='Z')) //if the letter at this index is capital (ASCII codes for A and Z)
		{
			Nstr[n] = str[i];
			bigletter(str, Nstr, i + 1, n + 1);//for move on on the new and old string
		}
		else
			bigletter(str, Nstr, i + 1, n);//move on only old string

	}
}

void Recursivemenu()//menu for recursia
{
	int choiceRec, num, temp;//choicerec for ceses, num for save num input, temp for save
	char bin[N] = { 0 };//for recursaia 3 
	char string[N] = { 0 };//for recursia 4 save the user input
	char nstr[N] = { 0 };//FOR NEW STRING OF BIG LETTERS recursia 4
	do {
		printf("\n1.Amount of odd and even numbers\n2.To make dec number to a binary number\n3.To make a dec number to binary number\n4.Find the big letters\n5.BACK\n");
		scanf("%d", &choiceRec);

		switch (choiceRec)
		{
		case 1:
			puts("please enter a int number");
			scanf("%d", &num);
			temp = sumof(num);
			printf("%d", temp);
			break;

		case 2:
			puts("please enter a int number");
			scanf("%d", &num);
			dectobin(num);
			

			break;

		case 3:
			puts("enter binari num");
			scanf("%s",bin);
			printf("dec num :%d", bintodec(bin));
			break;

		case 4:
			puts("enter a sentence");
			scanf("%s", &string);
			bigletter(string, nstr, 0, 0);

			printf("%s", nstr);
			break;


		case 5:
			puts("returns to main menu");
			break;

		default:puts("bad input, please try again");
			break;

			
		}
	} while (choiceRec != 5);

}

void freeUnit(Unit* u)//for free malloc in unit
{
	int i;
	free(u->name);
	free(u->manager.name);
	for (i = 0; i < u->NumOfWorkers; ++i)
	{
		if (u->workers[i].name)
		{
			free(u->workers[i].name);
		}
	}

}
void freeCompany(Company* c)//free maloc in company
{
	int i;
	free(c->CEO.name);
	free(c->NumOfUnits);
	for (i = 0; i < c->NumOfUnits; ++i)
	{
		freeUnit(&c->units[i]);
	}
}