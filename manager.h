#pragma once
#ifndef MANAGER_H_
#define MANAGER_H_

#include "score.h"
#include "student.h"

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <fstream>

struct CompareByNumber_Equal {
	unsigned int number;
	bool operator()(Score current_score) {
		return (current_score.number == number);
	}
};


bool checkInputFail() {
	if (cin.fail()) {
		cin.clear();
		cin.sync();

		cout << "输入有误，请重新处理" << endl;

		return true;
	}
	return false;
}

//用于查找的比较器
//用于在students中查找指定姓名的学生
struct CompareByName4Find {
	string name;
	bool operator()(Student stu) const {
		return(stu.name == name);
	}
};

//用于在scores中查找指定学号的成绩
struct CompareByNumber4Find {
	unsigned int number;
	bool operator()(Score sco) const {
		return (sco.number == number);
	}
};


class Manager {
private:
	vector<Student> students;
	list<Score> scores;

	void findScoreByNumber(unsigned int number) const;

public:
	void inputStudents();
	void inputScores();
	void clearScores();

	void outputScoresByNumber() const;
	void outputScoresByMark() const;

	void findStudentByNumber() const;
	void findStudentByName() const;

	void saveStudents() const;
	void loadStudents();

};
void Manager::loadStudents() {
	ifstream ifs;
	ifs.open("./students_base_info.txt");
	if (!ifs) {
		cout << "打开文件失败！" << endl;
		return;
	}
	students.clear();
	unsigned int count = 0;
	ifs >> count;
	for (unsigned int i = 0; i < count; ++i) {
		Student stu;
		ifs >> stu.number >> stu.name;
		students.push_back(stu);
	}
	ifs.close();
	cout << "加载完毕！共加载：" << count << "位学生的基本信息!" << endl;
}

void Manager::saveStudents() const {
	ofstream ofs;
	ofs.open("./students_base_info.txt");
	if (!ofs) {
		cout << "打开文件失败！" << endl;
		return;
	}
	unsigned int count = students.size();
	ofs << count << endl;
	for (unsigned int i = 0; i < count; ++i) {
		ofs << students[i].number << ' ' << students[i].name << endl;
	}
	ofs.close();
	cout << "保存完毕！共保存" << count << "位学生的信息" << endl;
}
struct CompareByMarkBigger {
	bool operator()(Score s1, Score s2) {
		return (s1.mark > s2.mark);
	}
};

void Manager::inputStudents() {
	if (students.empty() == false) {
		cout << "确定要重新录入学生的基本信息吗？(y/n)" << endl;
		char c;
		cin >> c;
		if (c != 'y') {
			return;
		}
		cin.sync();
	}

	students.clear();
	unsigned int number = 1;

	while (true) {
		cout << "请输入" << number << "号学生姓名，输入x表示结束" << endl;
		string name;
		cin >> name;
		if (name == "x") {
			break;
		}
		Student stu;
		stu.name = name;
		stu.number = number;
		students.push_back(stu);
		++number;
	}
}

struct CompareMarkBigger {
	bool operator()(Score s1, Score s2) {
		return (s1.mark > s2.mark);
	}
};

void Manager::inputScores() {
	while (true) {
		unsigned int number;
		cout << "请输入学号(输入0表示结束): ";
		cin >> number;

		if (checkInputFail()) {
			continue;
		}

		if (number == 0) {
			break;
		}
		if (number > students.size()) {
			cout << "错误：学号必须位于：1~"
				<< students.size() << "之间" << endl;
			continue;
		}
		float mark;
		cout << "请输入该学生的成绩(" << students[number - 1].name << ")";
		cin >> mark;
		if (checkInputFail()) {
			continue;
		}

		Score sco;
		sco.number = number;
		sco.mark = mark;
		scores.push_back(sco);
	}

	auto cmp = [](Score s1, Score s2)->bool {
		return (s1.mark > s2.mark);
	};
	scores.sort(cmp);
}

void Manager::clearScores() {
	cout << "确定要清空全部的成绩数据吗？(y/n)";
	char c;
	cin >> c;
	if (c == 'y') {
		scores.clear();
		cout << "成绩全部清除完毕！" << endl;
	}
	cin.sync();
}
//泛型
//list<Score>::iterator begin
//list<Score>::iterator it;
//(*it) == Score s;
template <typename InputIterator, typename Predicate>
InputIterator myFind(InputIterator begin
	, InputIterator end
	, Predicate cmp) {
	for (InputIterator it = begin
		; it != end
		; ++it) {
		if (cmp(*it)) {
			return it;
		}
	}
	return end;
}



void Manager::findScoreByNumber(unsigned int number) const {
	CompareByNumber4Find cbne;
	cbne.number = number;
	list<Score>::const_iterator itScore = find_if(scores.begin(), scores.end(), cbne);
	if (itScore == scores.end()) {
		cout << ",成绩：查无成绩";
	}
	else {
		cout << ",成绩：" << itScore->mark;
	}
}

void Manager::findStudentByNumber() const {
	cout << "请输入学号：";
	unsigned int number;
	cin >> number;
	if (checkInputFail()) {
		return;
	}
	unsigned int maxNumber = students.size();
	if (number > maxNumber) {
		cout << "学号只允许在1~" << maxNumber << "之间！" << endl;
		return;
	}
	cout << "学号：" << number;
	cout << "姓名：" << students[number - 1].name;
	findScoreByNumber(number);
	cout << endl;
}

void Manager::findStudentByName() const {
	cout << "请输入姓名：";
	string name;
	cin >> name;
	CompareByName4Find cmp;
	cmp.name = name;
	vector<Student>::const_iterator beg = students.begin();
	int foundCount = 0;
	while (true) {
		beg = find_if(beg, students.end(), cmp);
		if (beg == students.end()) {
			break;
		}
		++foundCount;
		cout << "姓名：" << name;
		cout << "学号：" << beg->number;

		findScoreByNumber(beg->number);
		cout << endl;
		beg++;
	}

	cout << "共查到" << foundCount << "位学生，名为：" << name << endl;
}

void Manager::outputScoresByNumber() const {
	int size = students.size();
	for (unsigned int i = 0; i < size; i++)
	{
		unsigned int number = students[i].number;
		cout << "学号：" << number;
		cout << ",姓名：" << students[i].name;
		findScoreByNumber(number);
	}
}

void Manager::outputScoresByMark() const {
	int index = 1;
	if (scores.empty()) {
		cout << "成绩数据为空！" << endl;
		return;
	}
	for (list<Score>::const_iterator it = scores.begin()
		; it != scores.end()
		; ++it) {
		cout << "名次：" << index;
		cout << ",姓名：" << students[it->number - 1].name;
		cout << ",学号：" << it->number;
		cout << ",成绩：" << it->mark;
		++index;
	}
	cout << "\n";
}

#endif //  !MANAGER_H_