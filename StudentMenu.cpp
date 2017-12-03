#include "header.h"

/////////////////////////////////////
// Student
/////////////////////////////////////

int Student::getStudno()
{
	return studno;
}
string Student::getName() const
{
	return name;
}
string Student::getCourse() const
{
	return course;
}
string Student::getPassword() const
{
	return password;
}
void Student::setStudno(int studno_)
{
	studno = studno_;
}
void Student::setName(const string& name_)
{
	int length = name_.size();
	name_.copy(name, length);
	name[length] = NULL;
}
void Student::setCourse(const string& course_)
{
	int length = course_.size();
	course_.copy(course, length);
	course[length] = NULL;
}
void Student::setPassword(const string& password_)
{
	int length = password_.size();
	password_.copy(password, length);
	password[length] = NULL;
}
Student::Student(int studno_, const string& name_, const string& course_, const string& password_)
{
	studno = studno_;
	setName(name_);
	setCourse(course_);
	setPassword(password_);
}

void StudentMenu()
{

}
//char StudentChoice()
//{
//	
//}