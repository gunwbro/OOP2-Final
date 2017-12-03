#include <Windows.h> // gotoxy Ŀ�� �̵�
#include "header.h"

void gotoxy(int x, int y)
{
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int main()
{
	int insstu = 0; // 0�̸� �α��� ����, 1 �̸� instructor ����, 2 �� student ����
	Instructor sys1(1, "jo", "Instructor", "1234"); // �� ���α׷��� ���� �ϱ� ���� ������ ��ü ����
	ofstream outfile("admin.dat", ios::out | ios::in | ios::binary); // �����ڵ��� ������ ���� admin.dat ���� ����

	if (!outfile)
	{
		ofstream outfile("admin.dat", ios::out | ios::binary);
		outfile.seekp((sys1.getInstructno() - 1) * sizeof(Instructor)); // �ռ� ���� �ߴ� ������ ��ü�� instrutno - 1 �κ����� �̵�
		outfile.write(reinterpret_cast<const char*>(&sys1), sizeof(Instructor)); // �ռ� ���� �ߴ� ������ ������ admin.dat�� ����
	}
	outfile.seekp(0); // 0���� ������ �̵�

	while (true) // �α��� ������ ��ġ�� �� ���� �ݺ�
	{
		ifstream AdminFile("admin.dat", ios::in | ios::binary); // admin.dat �� �б������ ���
		ifstream StudentFile("Student.dat", ios::in | ios::binary);
		Instructor test; // �α��� ������ ���� ��ü ����
		Student test1;
		char username[IDPW_MAX];
		char password[IDPW_MAX];
		gotoxy(20, 5);                                              // �α��� â
		cout << "----------------- Login ----------------";
		gotoxy(20, 6);
		cout << "|                                      |";
		gotoxy(20, 7);
		cout << "|     Enter username :                 |";
		gotoxy(20, 8);
		cout << "|                                      |";
		gotoxy(20, 9);
		cout << "|     Enter password :                 |";
		gotoxy(20, 10);
		cout << "|                                      |";
		gotoxy(20, 11);
		cout << "|--------------------------------------|" << endl;
		gotoxy(43, 7);
		for (int i = 0;;)                     
		{                                     
			username[i] = _getch();
			if ((int)username[i] == 13) 
			{
				username[i] = NULL;
				break;
			}
			if ((int)username[i] == 8)
			{
				if (i > 0)
				{
					gotoxy(43 + i - 1, 7);
					cout << " ";
					gotoxy(43 + i - 1, 7);
					i--;
				}
				continue;
			}
			if (i < 15)
			{
				cout << username[i];
				i++;
			}
		}
		gotoxy(43, 9);

		for (int i = 0;;)                     // ��й�ȣ * �� ��Ÿ����
		{                                     //
			password[i] = _getch();
			if ((int)password[i] == 13) // Enter �� ���� �� i��° �ε����� NULL�� �ʱ�ȭ �� �ݺ��� Ż��
			{
				password[i] = NULL;
				break;
			}
			if ((int)password[i] == 8) // Backspace�� ���� ��
			{
				if (i > 0)
				{
					gotoxy(43 + i - 1, 9);
					cout << " ";
					gotoxy(43 + i - 1, 9);
					i--;
				}
				continue;
			}
			if (i < 15)
			{
				cout << "*";
				i++;
			}
		}
		AdminFile.seekg(0); // 0���� ����
		StudentFile.seekg(0);
		while (AdminFile || StudentFile) // �α��� ������ ��ġ�ϴ� �����͸� ������ ���� �� ������ ã��
		{
			if (AdminFile && !AdminFile.eof())
			{
				AdminFile.read(reinterpret_cast<char*>(&test), sizeof(Instructor));
				if (username == test.getName() && password == test.getPassword())
				{
					insstu = 1;
					break;
				}
			}
			if (StudentFile && !StudentFile.eof())
			{
				StudentFile.read(reinterpret_cast<char*>(&test1), sizeof(Instructor));
				if (username == test1.getName() && password == test1.getPassword())
				{
					insstu = 2;
					break;
				}
			}
		}
		if (insstu == 0)
		{
			gotoxy(27, 15);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // �۾� ���� �������� ����
			cout << "Oops, that's not a match." << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // ����
		}
		else break;
	}
	switch (insstu)
	{
	case 1: InstructorMenu(); break;
	case 2: StudentMenu(); break;
	}
	return 0;
}
