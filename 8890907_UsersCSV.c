#define  _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <locale.h>
#include <Windows.h> 

typedef struct TBook {
	char isbn[256];
	char author[256];
	char name[256];
	int count;
	int available;
} Book;

typedef struct TStudent {
	char number[256];
	char firstname[256];
	char lastname[256];
	char middlename[256];
	char faculty[256];
	char specialty[256];
} Student;

typedef struct TAccount {
	char login[256];
	char password[256];
	int stRights;
	int bRights;
} Account;

typedef struct Node {
	void* value;
	struct Node *next;
} Node;

Node* add(Node *head, void* data) {
	Node *tmp = (Node*)malloc(sizeof(Node));
	tmp->value = data;
	tmp->next = head;
	head = tmp;
	return head;
}

Node* readBooks()
{
	Node* books = NULL;
	FILE* booksCSV = fopen("books.csv", "r");
	if (booksCSV==NULL)
		printf("Файл 'books.csv' не найден!");
	else
	{
		char buf[2048];
		while (!feof(booksCSV))
		{
			fgets(buf, 2048, booksCSV);
			int j = 0, i=0;
			Book *book = malloc(sizeof(Book));
			for (i=0;j<strlen(buf)&&buf[j]!=';';i++,j++)
				book->isbn[i] = buf[j];
			book->isbn[i] = '\0';
			for (i = 0,j++; j < strlen(buf) && buf[j] != ';'; i++, j++)
				book->author[i] = buf[j];
			book->author[i] = '\0';
			for (i = 0,j++; j < strlen(buf) && buf[j] != ';'; i++, j++)
				book->name[i] = buf[j];
			book->name[i] = '\0';
			char tmp[16];
			for (i = 0,j++; j < strlen(buf) && buf[j] != ';'; i++, j++)
				tmp[i] = buf[j];
			tmp[i] = '\0';
			book->count = atoi(tmp);
			for (i = 0, j++; j < strlen(buf) && buf[j] != ';'; i++, j++)
				tmp[i] = buf[j];
			tmp[i] = '\0';
			book->available = atoi(tmp);
			books = add(books, book);
		}
		fclose(booksCSV);
	}
	return books;
}

Node* readStudents()
{
	Node* students = NULL;
	FILE* studentsCSV = fopen("students.csv", "r");
	if (studentsCSV == NULL)
		printf("Файл 'students.csv' не найден!");
	else
	{
		char buf[2048];
		while (!feof(studentsCSV))
		{
			fgets(buf, 2048, studentsCSV);
			int j = 0, i = 0;
			Student *stud = malloc(sizeof(Student));
			for (i = 0; j < strlen(buf) && buf[j] != ';'; i++, j++)
				stud->number[i] = buf[j];
			stud->number[i] = '\0';
			for (i = 0, j++; j < strlen(buf) && buf[j] != ';'; i++, j++)
				stud->lastname[i] = buf[j];
			stud->lastname[i] = '\0';
			for (i = 0, j++; j < strlen(buf) && buf[j] != ';'; i++, j++)
				stud->firstname[i] = buf[j];
			stud->firstname[i] = '\0';
			for (i = 0, j++; j < strlen(buf) && buf[j] != ';'; i++, j++)
				stud->middlename[i] = buf[j];
			stud->middlename[i] = '\0';
			for (i = 0, j++; j < strlen(buf) && buf[j] != ';'; i++, j++)
				stud->faculty[i] = buf[j];
			stud->faculty[i] = '\0';
			for (i = 0, j++; j < strlen(buf) && buf[j] != ';'&&buf[j] != '\n'; i++, j++)
				stud->specialty[i] = buf[j];
			stud->specialty[i] = '\0';
			students = add(students, stud);
		}
		fclose(studentsCSV);
	}
	return students;
}

Node* readAccounts()
{
	Node* users = NULL;
	FILE* usersCSV = fopen("users.csv", "r");
	if (usersCSV == NULL)
		printf("Файл 'students.csv' не найден!");
	else
	{
		char buf[2048];
		while (!feof(usersCSV))
		{
			fgets(buf, 2048, usersCSV);
			int j = 0, i = 0;
			Account *acc = malloc(sizeof(Account));
			for (i = 0; j < strlen(buf) && buf[j] != ';'; i++, j++)
				acc->login[i] = buf[j];
			acc->login[i] = '\0';
			for (i = 0, j++; j < strlen(buf) && buf[j] != ';'; i++, j++)
				acc->password[i] = buf[j];
			acc->password[i] = '\0';
			char tmp[16];
			for (i = 0, j++; j < strlen(buf) && buf[j] != ';'; i++, j++)
				tmp[i] = buf[j];
			tmp[i] = '\0';
			acc->stRights = atoi(tmp);
			tmp[16];
			for (i = 0, j++; j < strlen(buf) && buf[j] != ';'; i++, j++)
				tmp[i] = buf[j];
			tmp[i] = '\0';
			acc->bRights = atoi(tmp);
			users = add(users, acc);
		}
		fclose(usersCSV);
	}
	return users;
}

char* readLine(char* title)
{
	char *buf=malloc(256);
	printf("%s: ", title);
	gets(buf);
	buf[strlen(buf)] = '\0';
	return buf;
}

void editStud(Student* tmpStud)
{
	char *lastname = readLine("Фамилия");
	char *firstname = readLine("Имя");
	char *middlename = readLine("Отчество");
	char *faculty = readLine("Факультет");
	char *specialty = readLine("Специальность");
	strcpy(tmpStud->firstname, firstname);
	strcpy(tmpStud->lastname, lastname);
	strcpy(tmpStud->middlename, middlename);
	strcpy(tmpStud->faculty, faculty);
	strcpy(tmpStud->specialty, specialty);
}

void menuBook()
{
	Node* books = readBooks();
	int cmd = -1;
	while (cmd != 0)
	{
		cmd = atoi(readLine("1 - Добавить книгу\n2 - Удалить книгу\n3 - Выдать книгу\n4 - Принять книгу\n5 - Печать инфо\n0 - Выход\nКоманда"));
		if (cmd == 1)
		{
			char *isbn=readLine("isbn");
			Node* booksTmp = books;
			while (booksTmp != NULL)
			{
				Book *tmpBook = booksTmp->value;
				if (strcmp(tmpBook->isbn, isbn) == 0)
					break;
				else booksTmp = booksTmp->next;
			}
			if (booksTmp != NULL)
				printf("Книга с таким isbn уже существует!\n");
			else
			{
				char *author = readLine("Автор");
				char *name = readLine("Название");
				int count = atoi(readLine("Всего книг"));
				int available = atoi(readLine("Доступно книг"));
				if (count>=available)
				{
					Book* book = malloc(sizeof(Book));
					strcpy(book->name, name);
					strcpy(book->author, author);
					strcpy(book->isbn, isbn);
					book->count = count;
					book->available = available;
					books = add(books, book);
				}
				else printf("Общее количество книг не может быть меньше остатка!\n");
			}
		}
		if (cmd == 2)
		{
			char *isbn = readLine("isbn");
			Book *tmpBook = books->value;
			if (strcmp(tmpBook->isbn, isbn) == 0)
			{
				Node *del = books;
				books = books->next;
				free(del);
			}
			else
			{
				Node* booksTmp = books;
				while (booksTmp != NULL&&booksTmp->next!=NULL)
				{
					tmpBook = booksTmp->next->value;
					if (strcmp(tmpBook->isbn, isbn) == 0)
						break;
					else booksTmp = booksTmp->next;
				}
				if (booksTmp==NULL||booksTmp->next == NULL)
					printf("Книга с таким isbn не найдена!\n");
				else
				{
					Node *elm = booksTmp->next;
					booksTmp->next = elm->next;
					free(elm);
				}
			}
		}
		if (cmd == 3)
		{
			char *isbn = readLine("isbn");
			Node* booksTmp = books;
			while (booksTmp != NULL)
			{
				Book *tmpBook = booksTmp->value;
				if (strcmp(tmpBook->isbn, isbn) == 0)
				{
					if (tmpBook->available==0)
						printf("Нет доступных книг!\n");
					else tmpBook->available--;
					break;
				}
				else booksTmp = booksTmp->next;
			}
			if (booksTmp == NULL)
				printf("Книга с таким isbn не найдена!\n");
		}
		if (cmd == 4)
		{
			char *isbn = readLine("isbn");
			Node* booksTmp = books;
			while (booksTmp != NULL)
			{
				Book *tmpBook = booksTmp->value;
				if (strcmp(tmpBook->isbn, isbn) == 0)
				{
					if (tmpBook->count == tmpBook->available)
						printf("Количество доступных книг полное!\n");
					else tmpBook->available++;
					break;
				}
				else booksTmp = booksTmp->next;
			}
			if (booksTmp == NULL)
				printf("Книга с таким isbn не найдена!\n");
		}
		if (cmd == 5)
		{
			Node* booksTmp = books;
			while (booksTmp != NULL)
			{
				Book *tmpBook = booksTmp->value;
				printf("isbn: %s, автор: %s, название: %s, всего: %d, доступно: %d\n", tmpBook->isbn, 
					tmpBook->author, tmpBook->name, tmpBook->count, tmpBook->available);
				booksTmp = booksTmp->next;
			}
		}
	}
	Node* booksTmp = books;
	FILE* booksCSV = fopen("books.csv", "w");
	while (booksTmp != NULL)
	{
		Book *tmpBook = booksTmp->value;
		fprintf(booksCSV, "%s;%s;%s;%d;%d", tmpBook->isbn,
			tmpBook->author, tmpBook->name, tmpBook->count, tmpBook->available);
		booksTmp = booksTmp->next;
		if (booksTmp != NULL)
			fprintf(booksCSV, "\n");
	}
	fclose(booksCSV);
}

void menuStudent()
{
	Node* studs = readStudents();
	int cmd = -1;
	while (cmd != 0)
	{
		cmd = atoi(readLine("1 - Добавить студента\n2 - Удалить студента\n3 - Редактировать инфо о студенте\n4 - Инфо о студенте\n5 - Печать инфо\n0 - Выход\nКоманда"));
		if (cmd == 1)
		{
			char *number = readLine("Номер зачетки");
			Node* studsTmp = studs;
			while (studsTmp != NULL)
			{
				Student *tmpStud = studsTmp->value;
				if (strcmp(tmpStud->number, number) == 0)
					break;
				else studsTmp = studsTmp->next;
			}
			if (studsTmp != NULL)
				printf("Студент с такой зачеткой уже существует!\n");
			else
			{
				Student* stud = malloc(sizeof(Student));
				strcpy(stud->number, number);
				editStud(stud);
				studs = add(studs, stud);
			}
		}
		if (cmd == 2)
		{
			char *number = readLine("Номер зачетки");
			Student *tmpStud = studs->value;
			if (strcmp(tmpStud->number, number) == 0)
			{
				Node *del = studs;
				studs = studs->next;
				free(del);
			}
			else
			{
				Node* studsTmp = studs;
				while (studsTmp != NULL && studsTmp->next != NULL)
				{
					tmpStud = studsTmp->next->value;
					if (strcmp(tmpStud->number, number) == 0)
						break;
					else studsTmp = studsTmp->next;
				}
				if (studsTmp == NULL || studsTmp->next == NULL)
					printf("Студент с таким номер зачетки не найден!\n");
				else
				{
					Node *elm = studsTmp->next;
					studsTmp->next = elm->next;
					free(elm);
				}
			}
		}
		if (cmd == 3)
		{
			char *number = readLine("Номер зачетки");
			Node* studsTmp = studs;
			while (studsTmp != NULL)
			{
				Student *tmpStud = studsTmp->value;
				if (strcmp(tmpStud->number, number) == 0)
				{
					editStud(tmpStud);
					break;
				}
				else studsTmp = studsTmp->next;
			}
			if (studsTmp == NULL)
				printf("Студент с таким номер зачетки не найден!\n");
		}
		if (cmd == 4)
		{
			char *number = readLine("Номер зачетки");
			Node* studsTmp = studs;
			while (studsTmp != NULL)
			{
				Student *tmpStud = studsTmp->value;
				if (strcmp(tmpStud->number, number) == 0)
				{
					printf("Найден студент:\nНомер зачетной книжки: %s, ФИО: %s %s %s, факультет: %s, специальность: %s\n", 
						tmpStud->number, tmpStud->lastname, tmpStud->firstname, tmpStud->middlename, tmpStud->faculty, tmpStud->specialty);
					break;
				}
				else studsTmp = studsTmp->next;
			}
			if (studsTmp == NULL)
				printf("Студент с таким номер зачетки не найден!\n");
		}
		if (cmd == 5)
		{
			Node* studsTmp = studs;
			while (studsTmp != NULL)
			{
				Student *tmpStud = studsTmp->value;
				printf("Номер зачетной книжки: %s, ФИО: %s %s %s, факультет: %s, специальность: %s\n", 
					tmpStud->number, tmpStud->lastname, tmpStud->firstname, tmpStud->middlename, tmpStud->faculty, tmpStud->specialty);
				studsTmp = studsTmp->next;
			}
		}
	}
	Node* studsTmp = studs;
	FILE* studsCSV = fopen("students.csv", "w");
	while (studsTmp != NULL)
	{
		Student *tmpStud = studsTmp->value;
		fprintf(studsCSV, "%s;%s;%s;%s;%s;%s", tmpStud->number, tmpStud->lastname, 
			tmpStud->firstname, tmpStud->middlename, tmpStud->faculty, tmpStud->specialty);
		studsTmp = studsTmp->next;
		if (studsTmp != NULL)
			fprintf(studsCSV, "\n");
	}
	fclose(studsCSV);
}

void menuBookStudent()
{
	int cmd = -1;
	while (cmd != 0)
	{
		cmd = atoi(readLine("1 - Книги\n2 - Студенты\n0 - Выход\nКоманда"));
		if (cmd == 1)
			menuBook();
		if (cmd == 2)
			menuStudent();
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Rus");
	Node* accounts=readAccounts();
	char *login = readLine("Логин");
	char *password = readLine("Пароль");
	Account *acc = NULL;
	int found = 0;
	while (accounts!=NULL)
	{
		Account *tmpAcc = accounts->value;
		if (strcmp(tmpAcc->login, login) == 0)
		{
			found = 1;
			if (strcmp(tmpAcc->password, password) == 0)
			{
				acc = tmpAcc;
				break;
			}
			else
			{
				printf("Неверный пароль!\n");
				break;
			}
		}
		else accounts = accounts->next;
	}
	if (!found)
		printf("Пользователь не найден!\n");
	else
	{
		if (acc!=NULL)
		{
			if (acc->bRights&&acc->stRights)
				menuBookStudent();
			else if (acc->bRights)
				menuBook();
			else if (acc->stRights)
				menuStudent();
		}
	}
}