#include "header.h"

char StudentInformation()
{
	char b;
	cout << endl;
	cout << "        ----Admin sub-menu for Student Information----" << endl;
	cout << "        |                                           |" << endl;
	cout << "        |       <S>how student list                 |" << endl;
	cout << "        |       <U>Update Student                   |" << endl;
	cout << "        |       <A>dd new Student                   |" << endl;
	cout << "        |       <D>elete Student                    |" << endl;
	cout << "        |       <X>EXIT menu                        |" << endl;
	cout << "        |-------------------------------------------|" << endl;
	cout << "        ";
	cin >> b;
	if (b <= 'Z' && b >= 'A') return b - ('Z' - 'z');
	return b;
}
void StudentSubMenu()
{
	char choice1;
	while ((choice1 = StudentInformation()) != 'x')
	{
		system("cls");
		switch (choice1)
		{
		case 's':ShowStudentList(); break;
		case 'u':UpdateStudent(); break;
		case 'a':AddNewStudent(); break;
		case 'd':DeleteStudent(); break;
		}
	}
}
void ShowStudentList()
{
	ifstream infile("Student.dat", ios::in | ios::binary);
	if (infile)
	{
		cout << endl;
		cout << "--------------------STUDENT LIST-------------------" << endl;
		cout << left << setw(9) << "STUDNO" << setw(18) << "NAME" << "COURSE" << endl;
		infile.seekg(0);
		while (!infile.eof())
		{
			Student stu;
			infile.read(reinterpret_cast<char*>(&stu), sizeof(Student));
			if (stu.getStudno() > 0) cout << left << setw(9) << stu.getStudno() << setw(18) << stu.getName() << stu.getCourse() << endl;
		}
	}
	else cout << "file is not exist" << endl;
}
void AddNewStudent()
{
	int Studno;
	char name[IDPW_MAX], course[20], password[IDPW_MAX];
	fstream outfile("Student.dat", ios::out | ios::in | ios::binary);

	if (!outfile) cout << "file is not exist" << endl;
	else
	{
		cout << "Enter Studno" << endl;
		cin >> Studno;
		if (Studno > 0 && Studno < 1000)
		{
			cin.ignore();
			cout << "Enter name" << endl;
			cin.getline(name, IDPW_MAX);
			cout << "Enter course" << endl;
			cin.getline(course, 20);
			cout << "Enter password" << endl;
			cin.getline(password, IDPW_MAX);
			Student stu1(Studno, name, course, password);
			outfile.seekp((stu1.getStudno() - 1) * sizeof(Student));
			outfile.write(reinterpret_cast<const char*>(&stu1), sizeof(Student));
		}
		else
		{
			cout << "Studno must > 0 and < 1000" << endl;
		}
	}
}
void DeleteStudent()
{
	int studno;
	Student stu;
	Student blankstu;
	ifstream infile("Student.dat", ios::in | ios::binary);
	ofstream outfile("Student.dat", ios::out | ios::in | ios::binary);
	if (infile && outfile)
	{
		cout << "Enter Studno to delete" << endl;
		cin >> studno;

		infile.seekg((studno - 1) * sizeof(Student));
		infile.read(reinterpret_cast<char*>(&stu), sizeof(Student));
		if (studno != stu.getStudno()) cout << "Oops, that's not a match" << endl;
		else
		{
			outfile.seekp((studno - 1) * sizeof(Student));
			outfile.write(reinterpret_cast<const char*>(&blankstu), sizeof(Student));
			cout << "Delete Complete!" << endl;
		}
	}
	else cout << "file is not exist" << endl;
}
void UpdateStudent()
{
	int studno;
	int choice;
	int stun;
	Student stu;
	char password[16];
	char name[IDPW_MAX];
	char course[20];
	ifstream infile("Student.dat", ios::in | ios::binary);
	if (infile)
	{
		cout << "Enter Studno to update" << endl;
		cin >> studno;
		infile.seekg((studno - 1) * sizeof(Student));
		infile.read(reinterpret_cast<char*>(&stu), sizeof(Student));
		if (studno != stu.getStudno()) cout << "Oops, that's not a match" << endl;
		else
		{
			cout << "1. Studno" << endl;
			cout << "2. Name" << endl;
			cout << "3. Course" << endl;
			cout << "4. Password" << endl;
			cout << "5. Exit" << endl;
			cin >> choice;

			switch (choice)
			{
			case 1:

				cout << "Enter Studno to change" << endl;
				cin >> stun;
				stu.setStudno(stun);
				break;
			case 2:

				cout << "Enter name to change" << endl;
				cin.ignore();
				cin.getline(name, IDPW_MAX);
				stu.setName(name);
				break;
			case 3:

				cout << "Enter course to change" << endl;
				cin.ignore();
				cin.getline(course, 20);
				stu.setCourse(course);
				break;
			case 4:

				cout << "Enter password to change" << endl;
				cin.ignore();
				cin.getline(password, IDPW_MAX);
				stu.setPassword(password);
				break;
			case 5:
				return;
			}
			ofstream outfile("Student.dat", ios::out | ios::in | ios::binary);
			outfile.seekp((studno - 1) * sizeof(Student));
			outfile.write(reinterpret_cast<const char*>(&stu), sizeof(Student));
			cout << "Complete" << endl;
		}
	}
	else cout << "file is not exist" << endl;
}