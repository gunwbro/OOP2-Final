#include <Windows.h> // gotoxy 커서 이동
#include "header.h"

void gotoxy(int x, int y)
{
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int main()
{
	int insstu = 0; // 0이면 로그인 실패, 1 이면 instructor 계정, 2 면 student 계정
	Instructor sys1(1, "jo", "Instructor", "1234"); // 이 프로그램을 관리 하기 위한 관리자 객체 생성
	ofstream outfile("admin.dat", ios::out | ios::in | ios::binary); // 관리자들의 정보를 담은 admin.dat 파일 생성

	if (!outfile)
	{
		ofstream outfile("admin.dat", ios::out | ios::binary);
		outfile.seekp((sys1.getInstructno() - 1) * sizeof(Instructor)); // 앞서 생성 했던 관리자 객체의 instrutno - 1 부분으로 이동
		outfile.write(reinterpret_cast<const char*>(&sys1), sizeof(Instructor)); // 앞서 생성 했던 관리자 정보를 admin.dat에 저장
	}
	outfile.seekp(0); // 0으로 포인터 이동

	while (true) // 로그인 정보가 일치할 때 까지 반복
	{
		ifstream AdminFile("admin.dat", ios::in | ios::binary); // admin.dat 을 읽기용으로 사용
		ifstream StudentFile("Student.dat", ios::in | ios::binary);
		Instructor test; // 로그인 정보를 담을 객체 생성
		Student test1;
		char username[IDPW_MAX];
		char password[IDPW_MAX];
		gotoxy(20, 5);                                              // 로그인 창
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

		for (int i = 0;;)                     // 비밀번호 * 로 나타내기
		{                                     //
			password[i] = _getch();
			if ((int)password[i] == 13) // Enter 를 누를 시 i번째 인덱스를 NULL로 초기화 후 반복문 탈출
			{
				password[i] = NULL;
				break;
			}
			if ((int)password[i] == 8) // Backspace를 누를 시
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
		AdminFile.seekg(0); // 0부터 읽음
		StudentFile.seekg(0);
		while (AdminFile || StudentFile) // 로그인 정보와 일치하는 데이터를 파일의 끝이 될 때까지 찾음
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
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // 글씨 색을 빨강으로 변경
			cout << "Oops, that's not a match." << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // 복구
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
