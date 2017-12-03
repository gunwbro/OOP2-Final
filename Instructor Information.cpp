#include "header.h"

char InstructorInformation()
{
	char b;
	cout << endl;
	cout << "        ----Admin Sub-Menu for Instructor----" << endl;
	cout << "        |                                   |" << endl;
	cout << "        |     <S>how Instructor list        |" << endl;
	cout << "        |     <U>pdate Instructor           |" << endl;
	cout << "        |     <A>dd new Instructor          |" << endl;
	cout << "        |     <D>elete Instructor record    |" << endl;
	cout << "        |     <X>EXIT return main menu      |" << endl;
	cout << "        -------------------------------------" << endl;
	cout << "        ";
	cin >> b;
	if (b <= 'Z' && b >= 'A') return b - ('Z' - 'z');
	return b;
}
void InstructorSubMenu()
{
	char choice1;
	while ((choice1 = InstructorInformation()) != 'x')
	{
		system("cls");
		switch (choice1)
		{
		case 's':ShowInstructorList(); break;
		case 'u':UpdateInstructor(); break;
		case 'a':AddNewInstructor(); break;
		case 'd':DeleteInstructor(); break;
		}
	}
}
void ShowInstructorList()
{
	ifstream infile("admin.dat", ios::in | ios::binary);
	if (infile)
	{
		cout << endl;
		cout << "--------------------INSTRUCTOR'S LIST-------------------" << endl;
		cout << left << setw(15) << "INSTRUCTNO" << setw(18) << "NAME" << "RANK" << endl;
		cout << "--------------------------------------------------------" << endl;
		infile.seekg(0);
		while (!infile.eof())
		{
			Instructor ins;
			infile.read(reinterpret_cast<char*>(&ins), sizeof(Instructor));
			if (ins.getInstructno() > 0) cout << left << setw(15) << ins.getInstructno() 
				<< setw(18) << ins.getName() << ins.getRank() << endl;
		}
	}
	else cout << "file is not exist" << endl;
}
void AddNewInstructor()
{
	int Instructno;
	char name[IDPW_MAX], rank[20], password[IDPW_MAX];
	fstream outfile("admin.dat", ios::out | ios::in | ios::binary);

	if (!outfile) cout << "file is not exist" << endl;
	else
	{
		cout << "Enter Instructno" << endl;
		cin >> Instructno;
		if (Instructno > 0 && Instructno < 1000)
		{
			cin.ignore();
			cout << "Enter name" << endl;
			cin.getline(name, IDPW_MAX);
			cout << "Enter rank" << endl;
			cin.getline(rank, 20);
			cout << "Enter password" << endl;
			cin.getline(password, IDPW_MAX);
			Instructor ins(Instructno, name, rank, password);
			outfile.seekp((ins.getInstructno() - 1) * sizeof(Instructor));
			outfile.write(reinterpret_cast<const char*>(&ins), sizeof(Instructor));
		}
		else
		{
			cout << "Instructno must > 0 and < 1000" << endl;
		}
	}
}
void DeleteInstructor()
{
	int Instructno;
	Instructor ins;
	Instructor blankins;
	ifstream infile("admin.dat", ios::in | ios::binary);
	ofstream outfile("admin.dat", ios::out | ios::in | ios::binary);
	if (infile && outfile)
	{
		cout << "Enter Instructno to delete" << endl;
		cin >> Instructno;

		infile.seekg((Instructno - 1) * sizeof(Instructor));
		infile.read(reinterpret_cast<char*>(&ins), sizeof(Instructor));
		if (Instructno != ins.getInstructno()) cout << "Oops, that's not a match" << endl;
		else
		{
			outfile.seekp((Instructno - 1) * sizeof(Instructor));
			outfile.write(reinterpret_cast<const char*>(&blankins), sizeof(Instructor));
			cout << "Delete Complete!" << endl;
		}
	}
	else cout << "file is not exist" << endl;
}
void UpdateInstructor()
{
	int Instructno;
	int choice;
	int Insn;
	Instructor ins;
	char password[IDPW_MAX];
	char name[IDPW_MAX];
	char rank[20];
	ifstream infile("admin.dat", ios::in | ios::binary);
	if (infile)
	{
		cout << "Enter Instructno to update" << endl;
		cin >> Instructno;
		infile.seekg((Instructno - 1) * sizeof(Instructor));
		infile.read(reinterpret_cast<char*>(&ins), sizeof(Instructor));
		if (Instructno != ins.getInstructno()) cout << "Oops, that's not a match" << endl;
		else
		{
			cout << "1. Instructno" << endl;
			cout << "2. Name" << endl;
			cout << "3. Rank" << endl;
			cout << "4. Password" << endl;
			cout << "5. Exit" << endl;
			cin >> choice;

			switch (choice)
			{
			case 1:

				cout << "Enter Instructnoo to change" << endl;
				cin >> Insn;
				ins.setInstructno(Insn);
				break;
			case 2:

				cout << "Enter name to change" << endl;
				cin.ignore();
				cin.getline(name, IDPW_MAX);
				ins.setName(name);
				break;
			case 3:

				cout << "Enter rank to change" << endl;
				cin.ignore();
				cin.getline(rank, 20);
				ins.setRank(rank);
				break;
			case 4:

				cout << "Enter password to change" << endl;
				cin.ignore();
				cin.getline(password, IDPW_MAX);
				ins.setPassword(password);
				break;
			case 5:
				return;
			}
			ofstream outfile("admin.dat", ios::out | ios::in | ios::binary);
			outfile.seekp((Instructno - 1) * sizeof(Instructor));
			outfile.write(reinterpret_cast<const char*>(&ins), sizeof(Instructor));
			cout << "Complete" << endl;
		}
	}
	else cout << "file is not exist" << endl;
}