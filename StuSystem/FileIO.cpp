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
	// �жϵ�¼��ݣ���ѡ���Ӧ�������ļ�
	if (status == 1)
	{// ����ѧ����ݵ�¼
		ifstream ifs(_S_LOGIN);		// �����ļ���ȡ����

		char buf[1024] = {0};

		while (!ifs.eof())		// ֱ���ļ���β
		{
			student tmp;
			ifs.getline(buf, sizeof(buf));		// ��ȡһ��

			//AfxMessageBox(CString(buf));
			char *info = strtok(buf, "|");		// ��"|"����
			if (info != NULL)
			{
				tmp.stuname = info;		// ѧ������
			}
			else
			{
				break;
			}

			info = strtok(NULL, "|");
			tmp.stunum = info;		// ѧ��ѧ��

			info = strtok(NULL, "|");
			tmp.password = info;	// ѧ������

			// һ��ѧ����¼ȡ���������е�¼��Ϣ�ıȶ�
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
		// ����������û�з��سɹ���˵����¼ʧ��
		return FALSE;
	}
	else if (status == 2)
	{// ���ý�ʦ��ݵ�¼
		ifstream ifs(_T_LOGIN);		// �����ļ���ȡ����

		char buf[1024] = { 0 };

		while (!ifs.eof())		// ֱ���ļ���β
		{
			teacher tmp;
			ifs.getline(buf, sizeof(buf));		// ��ȡһ��

			//AfxMessageBox(CString(buf));
			char *info = strtok(buf, "|");		// ��"|"����
			if (info != NULL)
			{
				tmp.teaname = info;		// ��ʦ����
			}
			else
			{
				break;
			}

			info = strtok(NULL, "|");
			tmp.teanum = info;		// ��ʦ���

			info = strtok(NULL, "|");
			tmp.password = info;	// ��ʦ����

			// һ��ѧ����¼ȡ���������е�¼��Ϣ�ıȶ�
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
		// ����������û�з��سɹ���˵����¼ʧ��
		return FALSE;
	}
	else
	{// ���ù���Ա��ݵ�¼
		ifstream ifs(_A_LOGIN);		// �����ļ���ȡ����

		char buf[1024] = { 0 };

		while (!ifs.eof())		// ֱ���ļ���β
		{
			admin tmp;
			ifs.getline(buf, sizeof(buf));		// ��ȡһ��

			//AfxMessageBox(CString(buf));
			char *info = strtok(buf, "|");		// ��"|"����
			if (info != NULL)
			{
				tmp.name = info;		// ����Ա����
			}
			else
			{
				break;
			}

			info = strtok(NULL, "|");
			tmp.password = info;	// ����Ա����

									// һ��ѧ����¼ȡ���������е�¼��Ϣ�ıȶ�
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
		// ����������û�з��سɹ���˵����¼ʧ��
		return FALSE;
	}
}

CString FileIO::ReadLogin()
{
	ifstream ifs(_LOGIN);
	char buf[100];
	ifs.getline(buf, sizeof(buf));	// ��ȡ�ѵ�¼�û���Ϣ

	char *info = strtok(buf, "|");
	string name = info;
	ifs.close();
	CString num;
	num = name.c_str();
	return num;
}

student FileIO::FindstudentById(CString stunum)
{
	student tmp;		// ����������ҵ�ѧ����Ϣ

	ifstream ifs(_S_LOGIN);
	char buf[1024] = { 0 };
	while (!ifs.eof())
	{
		ifs.getline(buf, sizeof(buf));		// ��ȡһ��
		char *info = strtok(buf, "|");		// ��"|"����
		if (info != NULL)
		{
			tmp.stuname = info;		// ѧ������
		}
		else
		{
			break;
		}
		info = strtok(NULL, "|");
		tmp.stunum = info;		// ѧ��ѧ��
		if (stunum == tmp.stunum.c_str())
		{
			info = strtok(NULL, "|");
			tmp.password = info;	// ѧ������
			ifs.close();
			return tmp;
		}
	}
	ifs.close();
	return tmp;
}

stucourse FileIO::FindstucourseById(CString stunum, int * coursenum)	// ��������coursenum
{
	stucourse tmp;	// ��������ѧ���ɼ���
	ifstream ifs(_S_COURSE);

	char buf[1024] = { 0 };
	while (!ifs.eof())
	{
		ifs.getline(buf, sizeof(buf));		// ��ȡһ��
		char *info = strtok(buf, "|");		// ��"|"����
		if (info != NULL)
		{
			tmp.stunum = info;		// ѧ�����
		}
		else
		{
			break;
		}
		if (stunum == tmp.stunum.c_str())	// �ҵ���Ӧѧ���ĳɼ���
		{
			lesson tmp1;
			info = strtok(NULL, "|");
			while (info != NULL)		// �����ɳɼ�����ӵ�list��
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
		stucourse tmp;	// ��������ѧ���ɼ���
		ifs.getline(buf, sizeof(buf));		// ��ȡһ��
		char *info = strtok(buf, "|");		// ��"|"����
		if (info != NULL)
		{
			tmp.stunum = info;		// ѧ�����
		}
		else
		{
			break;
		}
		
		lesson tmp1;
		info = strtok(NULL, "|");
		while (info != NULL)		// �����ɳɼ�����ӵ�list��
		{
			tmp1.courseid = atoi(info);
			info = strtok(NULL, "|");
			tmp1.score = atoi(info);
			info = strtok(NULL, "|");
			tmp.courses.push_back(tmp1);
		}
		ls.push_back(tmp);		// һ��ѧ���ɼ�����ȡ�꣬���浽ls
	}
	ifs.close();
}

vector<CString> FileIO::ReadCourseList()
{
	vector<CString> tmp;

	ifstream ifs(_COURSE_LIST);
	char buf[1024] = { 0 };
	string str;	// ����ת��char*ΪCString
	while (!ifs.eof())
	{
		ifs.getline(buf, sizeof(buf));
		char *info = strtok(buf, "|");
		if (info != NULL)
		{
			info = strtok(NULL, "|");
			str = info;
			tmp.push_back(CString(str.c_str()));	// �ѿγ��������Ӧ��list�±�
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
	//string str;	// ����ת��char*ΪCString
	while (!ifs.eof())
	{
		lcourse course;		// ��ʱ��������������γ̺ż��γ���
		ifs.getline(buf, sizeof(buf));
		char *info = strtok(buf, "|");
		if (info != NULL)
		{
			course.courseid = stoi(info);		// ����γ̺�
			info = strtok(NULL, "|");
			course.coursename = info;
			tmp.push_back(course);	// �ѿγ̴����Ӧ��list�±�
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
{	// ���γ��б�д�������ļ�
	ofstream ofs(_COURSE_LIST);
	if (courselist.size() > 0)
	{
		int courseid = 0;
		//ͨ��������ȡ���������ݣ�д���ļ�����"|"�ָ��β�ӻ���
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
	teacher tmp;		// ����������ҵ���ʦ��Ϣ

	ifstream ifs;
	ifs.open(_T_LOGIN);
	char buf[1024] = { 0 };
	while (!ifs.eof())
	{
		ifs.getline(buf, sizeof(buf));		// ��ȡһ��
		char *info = strtok(buf, "|");		// ��"|"����
		if (info != NULL)
		{
			tmp.teaname = info;		// ��ʦ����
		}
		else
		{
			break;
		}
		info = strtok(NULL, "|");
		tmp.teanum = info;		// ��ʦ���
		if (stunum == tmp.teanum.c_str())
		{
			info = strtok(NULL, "|");
			tmp.password = info;	// ��ʦ����
			ifs.close();
			// ��ȡ��ʦ�ڿ��б���䵽��ʦ�ṹ�嵱��
			ifstream ifs(_T_COURSE);	// ��ȡ��ʦ�α��ļ�
			while (!ifs.eof())
			{
				ifs.getline(buf, sizeof(buf));	// ��ȡһ������
				info = strtok(buf, "|");		// ��ȡ��ʦ���
				string tmpnum = info;
				if (tmpnum != tmp.teanum)
				{	// ������Ƕ�Ӧ��ŵĽ�ʦ���ݣ��������ѭ��
					continue;
				}
				if (info != NULL)
				{
					info = strtok(NULL, "|");	// ��һ���γ̺�
					while (info != NULL)		// �����ɳɼ�����ӵ�vector��
					{
						tmp.courseList.push_back(atoi(info));
						info = strtok(NULL, "|");
					}
					break;	// ������ֱ���˳�
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
		//ͨ��������ȡ���������ݣ�д���ļ�����"|"�ָ��β�ӻ���
		for (vector<stucourse>::iterator it = ls.begin(); it != ls.end(); it++)
		{
			ofs << it->stunum << "|";	// д��ѧ��
			for (vector<lesson>::iterator it1 = it->courses.begin(); it1 != it->courses.end(); it1++)	// ����д��γ̺źͳɼ�
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
	// ���ҵ�ѧ����������
	CString fstunum;
	ifstream ifs;
	int flag = 0;		// �ж��Ƿ��޸ĳɹ�
	ifs.open(_S_COURSE);
	char buf[1024] = { 0 };

	while (!ifs.eof())
	{
		stucourse tmp;
		ifs.getline(buf, sizeof(buf));		// ��ȡһ��
		char *info = strtok(buf, "|");		// ��"|"����
		if (info != NULL)
		{
			fstunum = info;		// ѧ�����
			tmp.stunum = info;	// ���浽��ʱ�ṹ����
		}
		else
		{
			break;
		}
		if (stunum == fstunum)	// �ҵ���Ӧѧ���ĳɼ������ȶ�ȡ���ݺ���tmp�в����³ɼ�
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
			tmp.courses.push_back(tmplesson);		// ����¿γ�
			flag = 1;		// �޸ĳɹ�
		}
		else
		{//		����Ҫ�޸ĵ�ѧ�������У�ֱ�ӱ���
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
		ls.push_back(tmp);		// ���������ݱ��浽��ʱ����
	}
	ifs.close();
	// ���ݶ�ȡ���޸���ϣ� ��ʼд��
	WriteStuCourse();
	return flag;
}

admin FileIO::FindAdminById(CString name)
{
	admin tmp;		// ����������ҵ�����Ա��Ϣ

	ifstream ifs(_A_LOGIN);
	char buf[1024] = { 0 };
	while (!ifs.eof())
	{
		ifs.getline(buf, sizeof(buf));		// ��ȡһ��
		char *info = strtok(buf, "|");		// ��"|"����
		if (info != NULL)
		{
			tmp.name = info;		// ����Ա����
		}
		else
		{
			break;
		}
		if (name == tmp.name.c_str())
		{
			info = strtok(NULL, "|");
			tmp.password = info;	// ����Ա����
			// TODO����ȡ����Ա��Ϣ�б�
			ifs.close();
			return tmp;
		}
	}
	ifs.close();
	return tmp;
}

void FileIO::ReadUserInfo(int status)
{	// ��ȡ�û���Ϣ�������浽��Ӧ��vector������
	ifstream ifs;
	if (status == 1)
	{	// ѧ��
		ifs.open(_S_LOGIN);
		char buf[1024] = { 0 };
		while (!ifs.eof())
		{
			student tmp;
			ifs.getline(buf, sizeof(buf));		// ��ȡһ��
			char *info = strtok(buf, "|");		// ��"|"����
			if (info != NULL)
			{
				tmp.stuname = info;	// ѧ������
			}
			else
			{
				break;
			}
			
			info = strtok(NULL, "|");
			tmp.stunum = info;	// ѧ�����
			info = strtok(NULL, "|");
			tmp.password = info;	// ѧ������
			info = strtok(NULL, "|");
			stuls.push_back(tmp);		// ���������ݱ��浽��ʱ����
		}
		ifs.close();
	}
	else if (status == 2)
	{	// ��ʦ
		ifs.open(_T_LOGIN);
		char buf[1024] = { 0 };
		while (!ifs.eof())
		{
			CString teanum;
			ifs.getline(buf, sizeof(buf));		// ��ȡһ��
			char *info = strtok(buf, "|");		// ��"|"����
			if (info != NULL)
			{
				info;	// ��ʦ����
			}
			else
			{
				break;
			}

			info = strtok(NULL, "|");
			string str = info;
			teanum = str.c_str();	// ��ʦ���
			// ��ʦ�Ŀ����б��ȡ������
			teacher tmp = FindteacherById(teanum);		// ��ȡ��ʦ�����Ϣ
			teals.push_back(tmp);		// ���������ݱ��浽��ʱ����
		}
		ifs.close();
	}
	else
	{	// ����Ա
		ifs.open(_A_LOGIN);
		char buf[1024] = { 0 };
		while (!ifs.eof())
		{
			admin tmp;
			ifs.getline(buf, sizeof(buf));		// ��ȡһ��
			char *info = strtok(buf, "|");		// ��"|"����
			if (info != NULL)
			{
				tmp.name = info;	// ����Ա����
			}
			else
			{
				break;
			}

			info = strtok(NULL, "|");
			tmp.password = info;	// ����Ա����
			info = strtok(NULL, "|");
			adminls.push_back(tmp);		// ���������ݱ��浽��ʱ����
		}
		ifs.close();
	}
}

void FileIO::WriteUserInfo(int status)
{	// д���û���Ϣ
	if (status == 1)
	{	// ѧ��
		ofstream ofs(_S_LOGIN);
		if (stuls.size() > 0)
		{
			//ͨ��������ȡ���������ݣ�д���ļ�����"|"�ָ��β�ӻ���
			for (vector<student>::iterator it = stuls.begin(); it != stuls.end(); it++)
			{
				ofs << it->stuname << "|";	// д������
				ofs << it->stunum << "|";	// д��ѧ��
				ofs << it->password << endl;	// д������
			}
		}
		ofs.close();
	}
	else if (status == 2)
	{	// ��ʦ
		ofstream ofs(_T_LOGIN);
		if (teals.size() > 0)
		{
			//ͨ��������ȡ���������ݣ�д���ļ�����"|"�ָ��β�ӻ���
			for (vector<teacher>::iterator it = teals.begin(); it != teals.end(); it++)
			{
				ofs << it->teaname << "|";	// д������
				ofs << it->teanum << "|";	// д���ʦ���
				ofs << it->password << endl;	// д������
			}
		}
		ofs.close();
	}
	else
	{	// ����Ա
		ofstream ofs(_A_LOGIN);
		if (adminls.size() > 0)
		{
			//ͨ��������ȡ���������ݣ�д���ļ�����"|"�ָ��β�ӻ���
			for (vector<admin>::iterator it = adminls.begin(); it != adminls.end(); it++)
			{
				ofs << it->name << "|";	// д������
				ofs << it->password << endl;	// д������
			}
		}
		ofs.close();
	}
}

BOOL FileIO::UpdatePwd(int status, CString usernum, CString newPwd)
{	// �޸�����
	int flag = 0;
	if (status == 1)
	{	// �޸�ѧ������
		// ��ȡѧ����Ϣ����
		ReadUserInfo(1);
		// �ҵ�ָ��ѧ�������޸�����
		for (vector<student>::iterator it = stuls.begin(); it != stuls.end(); it++)
		{
			if (usernum == it->stunum.c_str())
			{	// �ҵ���Ӧѧ���������У��޸�����
				CStringA str;
				str = newPwd;
				it->password = str.GetBuffer();
				break;	// �޸ĳɹ�������ѭ��
			}
		}
		// ���޸ĺ����������ȥ
		WriteUserInfo(1);
		flag = 1;
	}
	else if (status == 2)
	{	// �޸Ľ�ʦ����
		ReadUserInfo(2);
		// �ҵ�ָ����ʦ�����޸�����
		for (vector<teacher>::iterator it = teals.begin(); it != teals.end(); it++)
		{
			if (usernum == it->teanum.c_str())
			{	// �ҵ���Ӧ��ʦ�������У��޸�����
				CStringA str;
				str = newPwd;
				it->password = str.GetBuffer();
				break;	// �޸ĳɹ�������ѭ��
			}
		}
		// ���޸ĺ����������ȥ
		WriteUserInfo(2);
		flag = 1;
	}
	else
	{	// �޸Ĺ���Ա����
		ReadUserInfo(3);
		// �ҵ�ָ����ʦ�����޸�����
		for (vector<admin>::iterator it = adminls.begin(); it != adminls.end(); it++)
		{
			if (usernum == it->name.c_str())
			{	// �ҵ���Ӧ��ʦ�������У��޸�����
				CStringA str;
				str = newPwd;
				it->password = str.GetBuffer();
				break;	// �޸ĳɹ�������ѭ��
			}
		}
		// ���޸ĺ����������ȥ
		WriteUserInfo(3);
		flag = 1;
	}
	return flag;
}

void FileIO::ReadMessage()
{	// ��ȡ�����б��ļ���messagev��
	ifstream ifs(_A_MESSAGE);
	char buf[1024] = { 0 };
	while (!ifs.eof())
	{
		message tmp;
		ifs.getline(buf, sizeof(buf));		// ��ȡһ�У���һ����Ϣ
		char *info = strtok(buf, "|");		// ��"|"����
		if (info != NULL)
		{
			tmp.teaname = info;		// ��ʦ����
		}
		else
		{
			break;
		}
		info = strtok(NULL, "|");
		tmp.teanum = info;		// ��ʦ���
		info = strtok(NULL, "|");
		tmp.coursename = info;	// �¿γ���
		info = strtok(NULL, "|");
		tmp.courseplan = info;	// �ڿμƻ�
		messagev.push_back(tmp);
	}
	ifs.close();
}

void FileIO::WriteMessage()
{	// �������messagev��д���ļ�
	ofstream ofs(_A_MESSAGE);
	if (messagev.size() > 0)
	{
		//ͨ��������ȡ���������ݣ�д���ļ�����"|"�ָ��β�ӻ���
		for (vector<message>::iterator it = messagev.begin(); it != messagev.end(); it++)
		{
			ofs << it->teaname << "|";	// д���ʦ����
			ofs << it->teanum << "|";	// д���ʦ���
			ofs << it->coursename << "|";	// д���¿γ���
			ofs << it->courseplan << endl;	// �ڿμƻ�
		}
	}

	ofs.close();
}

void FileIO::WriteTeaCourse()
{	// ���½�ʦ�γ̱�
	ofstream ofs(_T_COURSE);
	if (teals.size() > 0)
	{
		//ͨ��������ȡ���������ݣ�д���ļ�����"|"�ָ��β�ӻ���
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
