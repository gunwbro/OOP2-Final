#include "header.h"

/////////////////////////////////////
// Instructor
/////////////////////////////////////

void Instructor::setPassword(const string& password_)
{
	int length = password_.size();
	password_.copy(password, length);
	password[length] = NULL;
}
void Instructor::setInstructno(int instructno_)
{
	instructno = instructno_;
}
void Instructor::setName(const string& name_)
{
	int length = name_.size();
	name_.copy(name, length);
	name[length] = NULL;
}
void Instructor::setRank(const string& rank_)
{
	int length = rank_.size();
	rank_.copy(rank, length);
	rank[length] = NULL;
}
int Instructor::getInstructno() const
{
	return instructno;
}
string Instructor::getName() const
{
	return name;
}
string Instructor::getRank() const
{
	return rank;
}
string Instructor::getPassword() const
{
	return password;
}
Instructor::Instructor(int instructno_, const string& name_, const string& rank_, const string& password_)
{
	instructno = instructno_;
	setName(name_);
	setRank(rank_);
	setPassword(password_);
}
void InstructorMenu()
{
	char choice;
	while ((choice = InstructorChoice()) != 'x')
	{
		system("cls");
		switch (choice)
		{
		case 's': StudentSubMenu(); break;
		case 'i': InstructorSubMenu(); break;
		case 'b': BuildFiles(); break;
		}
	}
}
char InstructorChoice()
{
	system("cls");
	char a;
	cout << endl;
	cout << "        ----<Admin>Instructor Main Menu-----" << endl;
	cout << "        |                                  |" << endl;
	cout << "        |     <S>TUDENT INFORMATION        |" << endl;
	cout << "        |     <I>NSTRUCTOR INFORMATION     |" << endl;
	cout << "        |     <Q>UESTION INFORMATION       |" << endl;
	cout << "        |     <J>SUBJECT INFORMATION       |" << endl;
	cout << "        |     <G>GRADE INFORMATION         |" << endl;
	cout << "        |     <U>Update password           |" << endl;
	cout << "        |     <B>BUILD FILES               |" << endl;
	cout << "        |     <X>EXIT                      |" << endl;
	cout << "        |                                  |" << endl;
	cout << "        |----------------------------------|" << endl;
	cout << "        ";
	cin >> a;
	if (a <= 'Z' && a >= 'A')
		return a - ('Z' - 'z');
	return a;
}
void BuildFiles()
{
	char back;
	system("cls");
	ofstream OutStudent("Student.dat", ios::out | ios::in | ios::binary);
	ofstream OutQuestion("Question.dat", ios::out | ios::in | ios::binary);
	ofstream OutSubject("Subject.dat", ios::out | ios::in | ios::binary);
	ofstream OutGrade("Grade.dat", ios::out | ios::in | ios::binary);

	if (OutStudent && OutQuestion && OutSubject && OutGrade)
	{
		cout << "File is already exist" << endl;
		back = _getch();
	}
	else
	{
		if (!OutStudent) ofstream OutStudent("Student.dat", ios::out | ios::binary);
		if (!OutQuestion) ofstream OutQuestion("Question.dat", ios::out | ios::binary);
		if (!OutSubject) ofstream OutSubject("Subject.dat", ios::out | ios::binary);
		if (!OutGrade) ofstream OutGrade("Grade.dat", ios::out | ios::binary);

		cout << "Success..!" << endl;
		back = _getch();
	}
}
