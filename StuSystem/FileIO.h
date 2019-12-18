#pragma once

#include <list>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define _S_LOGIN "./data/studentinfo.txt"	// ѧ����¼��Ϣ
#define _S_COURSE "./data/studentscore.txt"	// ѧ���ɼ���
#define _A_LOGIN "./data/admininfo.txt"		// ����Ա��¼��Ϣ
#define _A_MESSAGE "./data/adminmessage.txt"	// ����Ա��Ϣ�б�
#define _T_LOGIN "./data/teacherinfo.txt"	// ��ʦ��¼��Ϣ
#define _T_COURSE "./data/teachercourses.txt"	// ��ʦ�γ��б�
#define _LOGIN "./data/logininfo.txt"		// �ѵ�¼�û���Ż��û�����Ϣ
#define _COURSE_LIST "./data/courselist.txt"	// �γ����б�

using namespace std;

// ���ÿγ��б�ר�ÿγ̽ṹ��
struct lcourse
{
	int courseid;	// �γ̺�
	string coursename;	// �γ���
};

// �γ̽ṹ��
struct lesson
{
	int courseid;		// �γ̺ţ���Ӧȫ�ֱ����Ŀγ��±�
	int score;
};

// ��ʦ������Ϣ�ṹ��
struct message
{
	string teaname;		// �����ʦ����
	string teanum;		// �����ʦ���
	string coursename;	// �����¿γ�����
	string courseplan;	// �¿γ̽�ѧ�ƻ�
};

// ѧ���ṹ��
struct student
{
	string stunum;		// ѧ�ţ���Ϊ����
	string stuname;		// ѧ������
	string password;	// ����
};

// ѧ���ɼ����ṹ��
struct stucourse
{
	string stunum;		// ѧ�ţ���Ϊ����
	vector<lesson> courses;		// �ɼ��б�ÿ��Ԫ�ذ����γ̺źͷ���
};

// ��ʦ�ṹ��
struct teacher
{
	string teanum;		// ��ʦ���
	string teaname;		// ��ʦ����
	string password;	// ����
	vector<int> courseList;	// ��ʦ�ѿ�ͨ�γ��б�
};

// ����Ա�ṹ��
struct admin
{
	string name;		// ����Ա����
	string password;	// ����
	vector<message> newMessage;	// �յ��Ľ�ʦ����������Ϣ
};



class FileIO
{
public:
	FileIO();
	virtual ~FileIO();

	// ��֤��¼��Ϣ
	BOOL Login(int status, CString name, CString pwd);
	// ��ȡ�ѵ�½�û���Ϣ
	CString ReadLogin();

	// ͨ����Ų���ѧ����Ϣ
	student FindstudentById(CString stunum);
	// ͨ��ѧ�Ų���ѧ���ɼ���
	stucourse FindstucourseById(CString stunum, int *coursenum);
	// ��ȡ����ѧ���ĳɼ�
	void FindAllStuCourse();

	// ��ʦ��ȡ�γ��б�
	vector<CString> ReadCourseList();
	vector<lcourse> ReadCourses();
	void WriteCourseList(vector<CString> courselist);
	// ͨ����ʦ����ҽ�ʦ��Ϣ
	teacher FindteacherById(CString stunum);
	// ��ʦд����º��ѧ���ɼ�
	void WriteStuCourse();
	// ��ʦ¼��ѧ���ɼ�
	BOOL Insertscore(CString stunum, int courseid, int score);

	// ͨ������Ա���ֲ��ҹ���Ա��Ϣ
	admin FindAdminById(CString name);

	// ��ȡ�û���Ϣ
	void ReadUserInfo(int status);
	// д���û���Ϣ
	void WriteUserInfo(int status);
	// �޸�����
	BOOL UpdatePwd(int status, CString usernum, CString newPwd);
	// ��ȡ�����б��ļ���messagev��
	void ReadMessage();
	// �������messagev��д���ļ�
	void WriteMessage();
	// ���½�ʦ�γ̱�
	void WriteTeaCourse();

	// ��ʱ������������ѧ���ɼ�����
	vector<stucourse> ls;
	// �����޸�����
	vector<student> stuls;
	vector<teacher> teals;
	vector<admin> adminls;
	// ������Ϣ�ļ�ʱʹ��
	vector<message> messagev;
};

