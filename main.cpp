/*
�ɼ�����ϵͳ
������Ϣ�Ĺ������
*/
#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;
/*
�汾1��
����¼��ѧ���Ļ�����Ϣ��
����¼�뿼�Գɼ���
��ѧ��Ϊ����������Գɼ�
*/

/*
�汾2��
������(+)���˵����ܣ�
¼��ѧ��������Ϣ
��ѧ�Ų���ѧ��
����������ѧ��
¼��ѧ�����Գɼ�
���ѧ�����Գɼ�
��ѧ����ʾ�ɼ�
��������ʾ�ɼ�
����
����
�˳�
�ڱ���(.)ѧ��������Ϣ��¼��
��(+)���뵥��ѧ����ѧ�ţ�Ȼ�������ѧ�š������ͳɼ�
��(+)���뵥��ѧ����������Ȼ�������ѧ�š������ͳɼ��������
ѧ��ͬ������ȫ�����
��(*)ѧ���ɼ�¼�빦�ܡ����û�����ѧ�ź������������ѧ�������Ĺ��ܣ�
����ʾ�û�����ɼ��������Ӧ��ѧ���Ҳ���ѧ������ʾ������
�ޣ�.��һ��ѧ�Ŵ�С�������ѧ�š���������������Ҫ�����Ҳ����ɼ������
�ߣ�+������ȫ¼��ɼ����������ɼ��Ӹ浽���������


*/

#include "manager.h"

int display() {
	cout << "ѧ���ɼ�����ϵͳ1" << endl;
	cout << "1--¼��ѧ����������ѧ��" << endl;
	cout << "2--¼�뿼�Գɼ�" << endl;
	cout << "3--��ճɼ�" << endl;
	cout << "4--��ѧ�Ŵ�����ʾ�ɼ�" << endl;
	cout << "5--������������ʾ�ɼ�" << endl;
	cout << "6--��ѧ�Ų���ѧ��" << endl;
	cout << "7--����������ѧ��" << endl;
	cout << "8--����ѧ����Ϣ" << endl;
	cout << "9--��ȡѧ����Ϣ" << endl;
	cout << "10--�˳�" << endl;
	cout << "11--����" << endl;
	int sel;
	cout << "��ѡ�� " << endl;
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
			cout << "ѧ���ɼ�����ϵͳ Ver 3.0" << endl;
			cout << "copyright 2020 ~ ?" << endl;
			cout << "���ߣ�Protostar" << endl;
		}
	}
	return 0;
}