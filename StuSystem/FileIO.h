#pragma once

#include <list>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define _S_LOGIN "./data/studentinfo.txt"	// 学生登录信息
#define _S_COURSE "./data/studentscore.txt"	// 学生成绩单
#define _A_LOGIN "./data/admininfo.txt"		// 管理员登录信息
#define _A_MESSAGE "./data/adminmessage.txt"	// 管理员消息列表
#define _T_LOGIN "./data/teacherinfo.txt"	// 教师登录信息
#define _T_COURSE "./data/teachercourses.txt"	// 教师课程列表
#define _LOGIN "./data/logininfo.txt"		// 已登录用户编号或用户名信息
#define _COURSE_LIST "./data/courselist.txt"	// 课程名列表

using namespace std;

// 公用课程列表专用课程结构体
struct lcourse
{
	int courseid;	// 课程号
	string coursename;	// 课程名
};

// 课程结构体
struct lesson
{
	int courseid;		// 课程号，对应全局变量的课程下表
	int score;
};

// 教师申请信息结构体
struct message
{
	string teaname;		// 申请教师姓名
	string teanum;		// 申请教师编号
	string coursename;	// 申请新课程名字
	string courseplan;	// 新课程教学计划
};

// 学生结构体
struct student
{
	string stunum;		// 学号，作为主键
	string stuname;		// 学生姓名
	string password;	// 密码
};

// 学生成绩单结构体
struct stucourse
{
	string stunum;		// 学号，作为主键
	vector<lesson> courses;		// 成绩列表，每个元素包括课程号和分数
};

// 教师结构体
struct teacher
{
	string teanum;		// 教师编号
	string teaname;		// 教师姓名
	string password;	// 密码
	vector<int> courseList;	// 教师已开通课程列表
};

// 管理员结构体
struct admin
{
	string name;		// 管理员姓名
	string password;	// 密码
	vector<message> newMessage;	// 收到的教师开课申请消息
};



class FileIO
{
public:
	FileIO();
	virtual ~FileIO();

	// 验证登录信息
	BOOL Login(int status, CString name, CString pwd);
	// 读取已登陆用户信息
	CString ReadLogin();

	// 通过编号查找学生信息
	student FindstudentById(CString stunum);
	// 通过学号查找学生成绩单
	stucourse FindstucourseById(CString stunum, int *coursenum);
	// 读取所有学生的成绩
	void FindAllStuCourse();

	// 教师读取课程列表
	vector<CString> ReadCourseList();
	vector<lcourse> ReadCourses();
	void WriteCourseList(vector<CString> courselist);
	// 通过教师编号找教师信息
	teacher FindteacherById(CString stunum);
	// 教师写入更新后的学生成绩
	void WriteStuCourse();
	// 教师录入学生成绩
	BOOL Insertscore(CString stunum, int courseid, int score);

	// 通过管理员名字查找管理员信息
	admin FindAdminById(CString name);

	// 读取用户信息
	void ReadUserInfo(int status);
	// 写入用户信息
	void WriteUserInfo(int status);
	// 修改密码
	BOOL UpdatePwd(int status, CString usernum, CString newPwd);
	// 读取申请列表文件到messagev中
	void ReadMessage();
	// 将申请从messagev中写入文件
	void WriteMessage();
	// 更新教师课程表
	void WriteTeaCourse();

	// 临时变量用来更新学生成绩数据
	vector<stucourse> ls;
	// 用来修改密码
	vector<student> stuls;
	vector<teacher> teals;
	vector<admin> adminls;
	// 更新消息文件时使用
	vector<message> messagev;
};

