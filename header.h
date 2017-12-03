#pragma once
#include <iostream>
#include <fstream>
#include <conio.h>
#include <iomanip>
#include <string>
#include <cstdlib>
#pragma warning(disable:4996)
#define IDPW_MAX 16

using namespace std;

void InstructorMenu(); // instructor 계정으로 로그인 시, 기능 하는 모든 것들을 담은 함수
char InstructorChoice(); // 메뉴 선택
void StudentMenu();
char StudentChoice();

void BuildFiles();
char StudentInformation();
void ShowStudentList();
void StudentSubMenu();
void AddNewStudent();
void DeleteStudent();
void UpdateStudent();

char InstructorInformation();
void InstructorSubMenu();
void ShowInstructorList();
void AddNewInstructor();
void DeleteInstructor();
void UpdateInstructor();

class Student
{
private:
	int studno;
	char name[IDPW_MAX];
	char course[20];
	char password[IDPW_MAX];
public:
	Student(int = 0, const string& = "", const string& = "", const string& = "");
	
	int getStudno();
	string getName() const;
	string getCourse() const;
	string getPassword() const;

	void setStudno(int);
	void setName(const string&);
	void setCourse(const string&);
	void setPassword(const string&);
};

class Instructor
{
private:
	int instructno;
	char name[IDPW_MAX];
	char rank[20];
	char password[IDPW_MAX];
public:
	Instructor(int = 0, const string& = "", const string& = "", const string& = "");

	void setPassword(const string&);
	void setName(const string&);
	void setRank(const string&);
	void setInstructno(int);

	int getInstructno() const;
	string getName() const;
	string getRank() const;
	string getPassword() const;
};
class Question
{
private:
	int qno;
	string question;
	string choice1;
	string choice2;
	string choice3;
	string anskey;
	string subject;
	string period;
	string post;
public:
	Question(int = 0, string = "", string = "", string = "", string = "", string = "",
		string = "", string = "", string = "");
	static void qrandom();
};
class subject
{
private:
	int subjectno;
	string description;
	int unit;
public:
	subject(int = 0, string = "", int = 0);
	static void addsubject();
};

class Grade
{
private:

public:
};
