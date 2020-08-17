/*
成绩管理系统
避免信息的过度耦合
*/
#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;
/*
版本1：
批量录入学生的基本信息；
批量录入考试成绩；
以学号为次序，输出考试成绩
*/

/*
版本2：
①新增(+)主菜单功能：
录入学生基本信息
按学号查找学生
按姓名查找学生
录入学生考试成绩
清空学生考试成绩
按学号显示成绩
按排名显示成绩
帮助
关于
退出
②保留(.)学生基本信息的录入
③(+)输入单个学生的学号，然后输出其学号、姓名和成绩
④(+)输入单个学生的姓名，然后输出其学号、姓名和成绩。如果有
学生同名，则全部输出
⑤(*)学生成绩录入功能。在用户输入学号后，增加立即输出学生姓名的功能，
再提示用户输入成绩，如果对应的学号找不到学生则提示出错；、
⑥（.）一句学号从小到大输出学号、姓名、分数，需要考虑找不到成绩的情况
⑦（+）在完全录入成绩后立即按成绩从告到底排序，输出


*/

#include "manager.h"

int display() {
	cout << "学生成绩管理系统1" << endl;
	cout << "1--录入学生的姓名、学号" << endl;
	cout << "2--录入考试成绩" << endl;
	cout << "3--清空成绩" << endl;
	cout << "4--按学号次序显示成绩" << endl;
	cout << "5--按分数名次显示成绩" << endl;
	cout << "6--按学号查找学生" << endl;
	cout << "7--按姓名查找学生" << endl;
	cout << "8--保存学生信息" << endl;
	cout << "9--读取学生信息" << endl;
	cout << "10--退出" << endl;
	cout << "11--关于" << endl;
	int sel;
	cout << "请选择： " << endl;
	cin >> sel;
	return sel;
}
int main()
{
	Manager m;
	while (true) {
		int sel = display();
		if (sel == 1)
		{
			m.inputStudents();
		}
		else if (sel == 2)
		{
			m.inputScores();
		}
		else if (sel == 3)
		{
			m.clearScores();
		}
		else if (sel == 4)
		{
			m.outputScoresByNumber();
		}
		else if (sel == 5)
		{
			m.outputScoresByMark();
		}
		else if (sel == 6)
		{
			m.findStudentByNumber();
		}
		else if (sel == 7)
		{
			m.findStudentByName();
		}
		else if (sel == 8)
		{
			m.saveStudents();
		}
		else if (sel == 9)
		{
			m.loadStudents();
		}
		else if (sel == 10)
		{
			break;
		}
		else if (sel == 11)
		{
			cout << "学生成绩管理系统 Ver 3.0" << endl;
			cout << "copyright 2020 ~ ?" << endl;
			cout << "作者：Protostar" << endl;
		}
	}
	return 0;
}