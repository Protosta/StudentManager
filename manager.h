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

		cout << "�������������´���" << endl;

		return true;
	}
	return false;
}

//���ڲ��ҵıȽ���
//������students�в���ָ��������ѧ��
struct CompareByName4Find {
	string name;
	bool operator()(Student stu) const {
		return(stu.name == name);
	}
};

//������scores�в���ָ��ѧ�ŵĳɼ�
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
		cout << "���ļ�ʧ�ܣ�" << endl;
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
	cout << "������ϣ������أ�" << count << "λѧ���Ļ�����Ϣ!" << endl;
}

void Manager::saveStudents() const {
	ofstream ofs;
	ofs.open("./students_base_info.txt");
	if (!ofs) {
		cout << "���ļ�ʧ�ܣ�" << endl;
		return;
	}
	unsigned int count = students.size();
	ofs << count << endl;
	for (unsigned int i = 0; i < count; ++i) {
		ofs << students[i].number << ' ' << students[i].name << endl;
	}
	ofs.close();
	cout << "������ϣ�������" << count << "λѧ������Ϣ" << endl;
}
struct CompareByMarkBigger {
	bool operator()(Score s1, Score s2) {
		return (s1.mark > s2.mark);
	}
};

void Manager::inputStudents() {
	if (students.empty() == false) {
		cout << "ȷ��Ҫ����¼��ѧ���Ļ�����Ϣ��(y/n)" << endl;
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
		cout << "������" << number << "��ѧ������������x��ʾ����" << endl;
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
		cout << "������ѧ��(����0��ʾ����): ";
		cin >> number;

		if (checkInputFail()) {
			continue;
		}

		if (number == 0) {
			break;
		}
		if (number > students.size()) {
			cout << "����ѧ�ű���λ�ڣ�1~"
				<< students.size() << "֮��" << endl;
			continue;
		}
		float mark;
		cout << "�������ѧ���ĳɼ�(" << students[number - 1].name << ")";
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
	cout << "ȷ��Ҫ���ȫ���ĳɼ�������(y/n)";
	char c;
	cin >> c;
	if (c == 'y') {
		scores.clear();
		cout << "�ɼ�ȫ�������ϣ�" << endl;
	}
	cin.sync();
}
//����
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
		cout << ",�ɼ������޳ɼ�";
	}
	else {
		cout << ",�ɼ���" << itScore->mark;
	}
}

void Manager::findStudentByNumber() const {
	cout << "������ѧ�ţ�";
	unsigned int number;
	cin >> number;
	if (checkInputFail()) {
		return;
	}
	unsigned int maxNumber = students.size();
	if (number > maxNumber) {
		cout << "ѧ��ֻ������1~" << maxNumber << "֮�䣡" << endl;
		return;
	}
	cout << "ѧ�ţ�" << number;
	cout << "������" << students[number - 1].name;
	findScoreByNumber(number);
	cout << endl;
}

void Manager::findStudentByName() const {
	cout << "������������";
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
		cout << "������" << name;
		cout << "ѧ�ţ�" << beg->number;

		findScoreByNumber(beg->number);
		cout << endl;
		beg++;
	}

	cout << "���鵽" << foundCount << "λѧ������Ϊ��" << name << endl;
}

void Manager::outputScoresByNumber() const {
	int size = students.size();
	for (unsigned int i = 0; i < size; i++)
	{
		unsigned int number = students[i].number;
		cout << "ѧ�ţ�" << number;
		cout << ",������" << students[i].name;
		findScoreByNumber(number);
	}
}

void Manager::outputScoresByMark() const {
	int index = 1;
	if (scores.empty()) {
		cout << "�ɼ�����Ϊ�գ�" << endl;
		return;
	}
	for (list<Score>::const_iterator it = scores.begin()
		; it != scores.end()
		; ++it) {
		cout << "���Σ�" << index;
		cout << ",������" << students[it->number - 1].name;
		cout << ",ѧ�ţ�" << it->number;
		cout << ",�ɼ���" << it->mark;
		++index;
	}
	cout << "\n";
}

#endif //  !MANAGER_H_