#include "stdafx.h"
#include "FileIO.h"


FileIO::FileIO()
{
}


FileIO::~FileIO()
{
}

BOOL FileIO::Login(int status, CString name, CString pwd)
{
	// 判断登录身份，来选择对应的数据文件
	if (status == 1)
	{// 采用学生身份登录
		ifstream ifs(_S_LOGIN);		// 创建文件读取对象

		char buf[1024] = {0};

		while (!ifs.eof())		// 直到文件结尾
		{
			student tmp;
			ifs.getline(buf, sizeof(buf));		// 读取一行

			//AfxMessageBox(CString(buf));
			char *info = strtok(buf, "|");		// 以"|"隔开
			if (info != NULL)
			{
				tmp.stuname = info;		// 学生姓名
			}
			else
			{
				break;
			}

			info = strtok(NULL, "|");
			tmp.stunum = info;		// 学生学号

			info = strtok(NULL, "|");
			tmp.password = info;	// 学生密码

			// 一条学生记录取出来，进行登录信息的比对
			CString stuname;
			stuname = tmp.stunum.c_str();
			CString stupwd;
			stupwd = tmp.password.c_str();
			if (name == stuname && stupwd == pwd)
			{
				ifs.close();
				return TRUE;
			}
		}
		ifs.close();
		// 遍历结束还没有返回成功，说明登录失败
		return FALSE;
	}
	else if (status == 2)
	{// 采用教师身份登录
		ifstream ifs(_T_LOGIN);		// 创建文件读取对象

		char buf[1024] = { 0 };

		while (!ifs.eof())		// 直到文件结尾
		{
			teacher tmp;
			ifs.getline(buf, sizeof(buf));		// 读取一行

			//AfxMessageBox(CString(buf));
			char *info = strtok(buf, "|");		// 以"|"隔开
			if (info != NULL)
			{
				tmp.teaname = info;		// 教师姓名
			}
			else
			{
				break;
			}

			info = strtok(NULL, "|");
			tmp.teanum = info;		// 教师编号

			info = strtok(NULL, "|");
			tmp.password = info;	// 教师密码

			// 一条学生记录取出来，进行登录信息的比对
			CString stuname;
			stuname = tmp.teanum.c_str();
			CString stupwd;
			stupwd = tmp.password.c_str();
			if (name == stuname && stupwd == pwd)
			{
				ifs.close();
				return TRUE;
			}
		}
		ifs.close();
		// 遍历结束还没有返回成功，说明登录失败
		return FALSE;
	}
	else
	{// 采用管理员身份登录
		ifstream ifs(_A_LOGIN);		// 创建文件读取对象

		char buf[1024] = { 0 };

		while (!ifs.eof())		// 直到文件结尾
		{
			admin tmp;
			ifs.getline(buf, sizeof(buf));		// 读取一行

			//AfxMessageBox(CString(buf));
			char *info = strtok(buf, "|");		// 以"|"隔开
			if (info != NULL)
			{
				tmp.name = info;		// 管理员姓名
			}
			else
			{
				break;
			}

			info = strtok(NULL, "|");
			tmp.password = info;	// 管理员密码

									// 一条学生记录取出来，进行登录信息的比对
			CString stuname;
			stuname = tmp.name.c_str();
			CString stupwd;
			stupwd = tmp.password.c_str();
			if (name == stuname && stupwd == pwd)
			{
				ifs.close();
				return TRUE;
			}
		}
		ifs.close();
		// 遍历结束还没有返回成功，说明登录失败
		return FALSE;
	}
}

CString FileIO::ReadLogin()
{
	ifstream ifs(_LOGIN);
	char buf[100];
	ifs.getline(buf, sizeof(buf));	// 读取已登录用户信息

	char *info = strtok(buf, "|");
	string name = info;
	ifs.close();
	CString num;
	num = name.c_str();
	return num;
}

student FileIO::FindstudentById(CString stunum)
{
	student tmp;		// 用来保存查找到学生信息

	ifstream ifs(_S_LOGIN);
	char buf[1024] = { 0 };
	while (!ifs.eof())
	{
		ifs.getline(buf, sizeof(buf));		// 读取一行
		char *info = strtok(buf, "|");		// 以"|"隔开
		if (info != NULL)
		{
			tmp.stuname = info;		// 学生姓名
		}
		else
		{
			break;
		}
		info = strtok(NULL, "|");
		tmp.stunum = info;		// 学生学号
		if (stunum == tmp.stunum.c_str())
		{
			info = strtok(NULL, "|");
			tmp.password = info;	// 学生密码
			ifs.close();
			return tmp;
		}
	}
	ifs.close();
	return tmp;
}

stucourse FileIO::FindstucourseById(CString stunum, int * coursenum)	// 传出参数coursenum
{
	stucourse tmp;	// 用来保存学生成绩单
	ifstream ifs(_S_COURSE);

	char buf[1024] = { 0 };
	while (!ifs.eof())
	{
		ifs.getline(buf, sizeof(buf));		// 读取一行
		char *info = strtok(buf, "|");		// 以"|"隔开
		if (info != NULL)
		{
			tmp.stunum = info;		// 学生编号
		}
		else
		{
			break;
		}
		if (stunum == tmp.stunum.c_str())	// 找到对应学生的成绩单
		{
			lesson tmp1;
			info = strtok(NULL, "|");
			while (info != NULL)		// 遍历吧成绩单添加到list中
			{
				tmp1.courseid = atoi(info);
				info = strtok(NULL, "|");
				tmp1.score = atoi(info);
				info = strtok(NULL, "|");
				tmp.courses.push_back(tmp1);
				(*coursenum)++;
			}
			ifs.close();
			return tmp;
		}
	}
	ifs.close();

	return tmp;
}

void FileIO::FindAllStuCourse()
{
	ifstream ifs(_S_COURSE);

	char buf[1024] = { 0 };
	while (!ifs.eof())
	{
		stucourse tmp;	// 用来保存学生成绩单
		ifs.getline(buf, sizeof(buf));		// 读取一行
		char *info = strtok(buf, "|");		// 以"|"隔开
		if (info != NULL)
		{
			tmp.stunum = info;		// 学生编号
		}
		else
		{
			break;
		}
		
		lesson tmp1;
		info = strtok(NULL, "|");
		while (info != NULL)		// 遍历吧成绩单添加到list中
		{
			tmp1.courseid = atoi(info);
			info = strtok(NULL, "|");
			tmp1.score = atoi(info);
			info = strtok(NULL, "|");
			tmp.courses.push_back(tmp1);
		}
		ls.push_back(tmp);		// 一个学生成绩单读取完，保存到ls
	}
	ifs.close();
}

vector<CString> FileIO::ReadCourseList()
{
	vector<CString> tmp;

	ifstream ifs(_COURSE_LIST);
	char buf[1024] = { 0 };
	string str;	// 用来转换char*为CString
	while (!ifs.eof())
	{
		ifs.getline(buf, sizeof(buf));
		char *info = strtok(buf, "|");
		if (info != NULL)
		{
			info = strtok(NULL, "|");
			str = info;
			tmp.push_back(CString(str.c_str()));	// 把课程名存入对应的list下标
		}
		else
		{
			break;
		}
	}
	ifs.close();

	return tmp;
}

vector<lcourse> FileIO::ReadCourses()
{
	vector<lcourse> tmp;

	ifstream ifs(_COURSE_LIST);
	char buf[1024] = { 0 };
	//string str;	// 用来转换char*为CString
	while (!ifs.eof())
	{
		lcourse course;		// 临时变量，用来保存课程号及课程名
		ifs.getline(buf, sizeof(buf));
		char *info = strtok(buf, "|");
		if (info != NULL)
		{
			course.courseid = stoi(info);		// 保存课程号
			info = strtok(NULL, "|");
			course.coursename = info;
			tmp.push_back(course);	// 把课程存入对应的list下标
		}
		else
		{
			break;
		}
	}
	ifs.close();

	return tmp;
}

void FileIO::WriteCourseList(vector<CString> courselist)
{	// 将课程列表写入数据文件
	ofstream ofs(_COURSE_LIST);
	if (courselist.size() > 0)
	{
		int courseid = 0;
		//通过迭代器取出链表内容，写入文件，以"|"分割，结尾加换行
		for (vector<CString>::iterator it = courselist.begin(); it != courselist.end(); it++)
		{
			CStringA str;
			str= *it;
			ofs << courseid++ << "|" << str.GetBuffer() << endl;
		}
	}

	ofs.close();
}

teacher FileIO::FindteacherById(CString stunum)
{
	teacher tmp;		// 用来保存查找到教师信息

	ifstream ifs;
	ifs.open(_T_LOGIN);
	char buf[1024] = { 0 };
	while (!ifs.eof())
	{
		ifs.getline(buf, sizeof(buf));		// 读取一行
		char *info = strtok(buf, "|");		// 以"|"隔开
		if (info != NULL)
		{
			tmp.teaname = info;		// 教师姓名
		}
		else
		{
			break;
		}
		info = strtok(NULL, "|");
		tmp.teanum = info;		// 教师编号
		if (stunum == tmp.teanum.c_str())
		{
			info = strtok(NULL, "|");
			tmp.password = info;	// 教师密码
			ifs.close();
			// 读取教师授课列表，填充到教师结构体当中
			ifstream ifs(_T_COURSE);	// 读取教师课表文件
			while (!ifs.eof())
			{
				ifs.getline(buf, sizeof(buf));	// 读取一行数据
				info = strtok(buf, "|");		// 获取教师编号
				string tmpnum = info;
				if (tmpnum != tmp.teanum)
				{	// 如果不是对应编号的教师数据，跳过这次循环
					continue;
				}
				if (info != NULL)
				{
					info = strtok(NULL, "|");	// 第一个课程号
					while (info != NULL)		// 遍历吧成绩单添加到vector中
					{
						tmp.courseList.push_back(atoi(info));
						info = strtok(NULL, "|");
					}
					break;	// 添加完成直接退出
				}
				else
				{
					break;
				}
			}
			ifs.close();
			return tmp;
		}
	}
	ifs.close();
	return tmp;
}

void FileIO::WriteStuCourse()
{
	ofstream ofs(_S_COURSE);
	if (ls.size() > 0)
	{
		//通过迭代器取出链表内容，写入文件，以"|"分割，结尾加换行
		for (vector<stucourse>::iterator it = ls.begin(); it != ls.end(); it++)
		{
			ofs << it->stunum << "|";	// 写入学号
			for (vector<lesson>::iterator it1 = it->courses.begin(); it1 != it->courses.end(); it1++)	// 遍历写入课程号和成绩
			{
				ofs << it1->courseid << "|";
				ofs << it1->score << "|";
			}
			ofs << endl;
		}
	}
	ofs.close();
}

BOOL FileIO::Insertscore(CString stunum, int courseid, int score)
{
	// 先找到学生的数据行
	CString fstunum;
	ifstream ifs;
	int flag = 0;		// 判断是否修改成功
	ifs.open(_S_COURSE);
	char buf[1024] = { 0 };

	while (!ifs.eof())
	{
		stucourse tmp;
		ifs.getline(buf, sizeof(buf));		// 读取一行
		char *info = strtok(buf, "|");		// 以"|"隔开
		if (info != NULL)
		{
			fstunum = info;		// 学生编号
			tmp.stunum = info;	// 保存到临时结构体中
		}
		else
		{
			break;
		}
		if (stunum == fstunum)	// 找到对应学生的成绩单，先读取数据后，在tmp中插入新成绩
		{
			lesson tmplesson;
			info = strtok(NULL, "|");
			while (info != NULL) {
				tmplesson.courseid = atoi(info);
				info = strtok(NULL, "|");
				tmplesson.score = atoi(info);
				tmp.courses.push_back(tmplesson);
				info = strtok(NULL, "|");
			}
			tmplesson.courseid = courseid;		
			tmplesson.score = score;
			tmp.courses.push_back(tmplesson);		// 添加新课程
			flag = 1;		// 修改成功
		}
		else
		{//		不是要修改的学生数据行，直接保存
			lesson tmplesson;
			info = strtok(NULL, "|");
			while (info != NULL) {
				tmplesson.courseid = atoi(info);
				info = strtok(NULL, "|");
				tmplesson.score = atoi(info);
				tmp.courses.push_back(tmplesson);
				info = strtok(NULL, "|");
			} 
		}
		ls.push_back(tmp);		// 将这行数据保存到临时变量
	}
	ifs.close();
	// 数据读取并修改完毕， 开始写入
	WriteStuCourse();
	return flag;
}

admin FileIO::FindAdminById(CString name)
{
	admin tmp;		// 用来保存查找到管理员信息

	ifstream ifs(_A_LOGIN);
	char buf[1024] = { 0 };
	while (!ifs.eof())
	{
		ifs.getline(buf, sizeof(buf));		// 读取一行
		char *info = strtok(buf, "|");		// 以"|"隔开
		if (info != NULL)
		{
			tmp.name = info;		// 管理员姓名
		}
		else
		{
			break;
		}
		if (name == tmp.name.c_str())
		{
			info = strtok(NULL, "|");
			tmp.password = info;	// 管理员密码
			// TODO：读取管理员消息列表
			ifs.close();
			return tmp;
		}
	}
	ifs.close();
	return tmp;
}

void FileIO::ReadUserInfo(int status)
{	// 读取用户信息，并保存到对应的vector容器中
	ifstream ifs;
	if (status == 1)
	{	// 学生
		ifs.open(_S_LOGIN);
		char buf[1024] = { 0 };
		while (!ifs.eof())
		{
			student tmp;
			ifs.getline(buf, sizeof(buf));		// 读取一行
			char *info = strtok(buf, "|");		// 以"|"隔开
			if (info != NULL)
			{
				tmp.stuname = info;	// 学生姓名
			}
			else
			{
				break;
			}
			
			info = strtok(NULL, "|");
			tmp.stunum = info;	// 学生序号
			info = strtok(NULL, "|");
			tmp.password = info;	// 学生密码
			info = strtok(NULL, "|");
			stuls.push_back(tmp);		// 将这行数据保存到临时变量
		}
		ifs.close();
	}
	else if (status == 2)
	{	// 教师
		ifs.open(_T_LOGIN);
		char buf[1024] = { 0 };
		while (!ifs.eof())
		{
			CString teanum;
			ifs.getline(buf, sizeof(buf));		// 读取一行
			char *info = strtok(buf, "|");		// 以"|"隔开
			if (info != NULL)
			{
				info;	// 教师姓名
			}
			else
			{
				break;
			}

			info = strtok(NULL, "|");
			string str = info;
			teanum = str.c_str();	// 教师序号
			// 教师的开课列表读取并存入
			teacher tmp = FindteacherById(teanum);		// 获取教师相关信息
			teals.push_back(tmp);		// 将这行数据保存到临时变量
		}
		ifs.close();
	}
	else
	{	// 管理员
		ifs.open(_A_LOGIN);
		char buf[1024] = { 0 };
		while (!ifs.eof())
		{
			admin tmp;
			ifs.getline(buf, sizeof(buf));		// 读取一行
			char *info = strtok(buf, "|");		// 以"|"隔开
			if (info != NULL)
			{
				tmp.name = info;	// 管理员姓名
			}
			else
			{
				break;
			}

			info = strtok(NULL, "|");
			tmp.password = info;	// 管理员密码
			info = strtok(NULL, "|");
			adminls.push_back(tmp);		// 将这行数据保存到临时变量
		}
		ifs.close();
	}
}

void FileIO::WriteUserInfo(int status)
{	// 写入用户信息
	if (status == 1)
	{	// 学生
		ofstream ofs(_S_LOGIN);
		if (stuls.size() > 0)
		{
			//通过迭代器取出链表内容，写入文件，以"|"分割，结尾加换行
			for (vector<student>::iterator it = stuls.begin(); it != stuls.end(); it++)
			{
				ofs << it->stuname << "|";	// 写入姓名
				ofs << it->stunum << "|";	// 写入学号
				ofs << it->password << endl;	// 写入密码
			}
		}
		ofs.close();
	}
	else if (status == 2)
	{	// 教师
		ofstream ofs(_T_LOGIN);
		if (teals.size() > 0)
		{
			//通过迭代器取出链表内容，写入文件，以"|"分割，结尾加换行
			for (vector<teacher>::iterator it = teals.begin(); it != teals.end(); it++)
			{
				ofs << it->teaname << "|";	// 写入姓名
				ofs << it->teanum << "|";	// 写入教师编号
				ofs << it->password << endl;	// 写入密码
			}
		}
		ofs.close();
	}
	else
	{	// 管理员
		ofstream ofs(_A_LOGIN);
		if (adminls.size() > 0)
		{
			//通过迭代器取出链表内容，写入文件，以"|"分割，结尾加换行
			for (vector<admin>::iterator it = adminls.begin(); it != adminls.end(); it++)
			{
				ofs << it->name << "|";	// 写入姓名
				ofs << it->password << endl;	// 写入密码
			}
		}
		ofs.close();
	}
}

BOOL FileIO::UpdatePwd(int status, CString usernum, CString newPwd)
{	// 修改密码
	int flag = 0;
	if (status == 1)
	{	// 修改学生密码
		// 读取学生信息数据
		ReadUserInfo(1);
		// 找到指定学生，并修改密码
		for (vector<student>::iterator it = stuls.begin(); it != stuls.end(); it++)
		{
			if (usernum == it->stunum.c_str())
			{	// 找到对应学生的数据行，修改密码
				CStringA str;
				str = newPwd;
				it->password = str.GetBuffer();
				break;	// 修改成功，跳出循环
			}
		}
		// 把修改后的数据填充回去
		WriteUserInfo(1);
		flag = 1;
	}
	else if (status == 2)
	{	// 修改教师密码
		ReadUserInfo(2);
		// 找到指定教师，并修改密码
		for (vector<teacher>::iterator it = teals.begin(); it != teals.end(); it++)
		{
			if (usernum == it->teanum.c_str())
			{	// 找到对应教师的数据行，修改密码
				CStringA str;
				str = newPwd;
				it->password = str.GetBuffer();
				break;	// 修改成功，跳出循环
			}
		}
		// 把修改后的数据填充回去
		WriteUserInfo(2);
		flag = 1;
	}
	else
	{	// 修改管理员密码
		ReadUserInfo(3);
		// 找到指定教师，并修改密码
		for (vector<admin>::iterator it = adminls.begin(); it != adminls.end(); it++)
		{
			if (usernum == it->name.c_str())
			{	// 找到对应教师的数据行，修改密码
				CStringA str;
				str = newPwd;
				it->password = str.GetBuffer();
				break;	// 修改成功，跳出循环
			}
		}
		// 把修改后的数据填充回去
		WriteUserInfo(3);
		flag = 1;
	}
	return flag;
}

void FileIO::ReadMessage()
{	// 读取申请列表文件到messagev中
	ifstream ifs(_A_MESSAGE);
	char buf[1024] = { 0 };
	while (!ifs.eof())
	{
		message tmp;
		ifs.getline(buf, sizeof(buf));		// 读取一行，即一条消息
		char *info = strtok(buf, "|");		// 以"|"隔开
		if (info != NULL)
		{
			tmp.teaname = info;		// 教师姓名
		}
		else
		{
			break;
		}
		info = strtok(NULL, "|");
		tmp.teanum = info;		// 教师编号
		info = strtok(NULL, "|");
		tmp.coursename = info;	// 新课程名
		info = strtok(NULL, "|");
		tmp.courseplan = info;	// 授课计划
		messagev.push_back(tmp);
	}
	ifs.close();
}

void FileIO::WriteMessage()
{	// 将申请从messagev中写入文件
	ofstream ofs(_A_MESSAGE);
	if (messagev.size() > 0)
	{
		//通过迭代器取出链表内容，写入文件，以"|"分割，结尾加换行
		for (vector<message>::iterator it = messagev.begin(); it != messagev.end(); it++)
		{
			ofs << it->teaname << "|";	// 写入教师姓名
			ofs << it->teanum << "|";	// 写入教师编号
			ofs << it->coursename << "|";	// 写入新课程名
			ofs << it->courseplan << endl;	// 授课计划
		}
	}

	ofs.close();
}

void FileIO::WriteTeaCourse()
{	// 更新教师课程表
	ofstream ofs(_T_COURSE);
	if (teals.size() > 0)
	{
		//通过迭代器取出链表内容，写入文件，以"|"分割，结尾加换行
		for (vector<teacher>::iterator it = teals.begin(); it != teals.end(); it++)
		{
			ofs << it->teanum << "|";
			for (vector<int>::iterator it1 = it->courseList.begin(); it1 != it->courseList.end(); it1++)
			{
				ofs << *it1 << "|";
			}
			ofs << endl;
		}
	}

	ofs.close();
}
