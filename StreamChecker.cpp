#include "StreamChecker.h"

bool StreamChecker::isStreamFail(std::istream& in) {
	if (in.fail()) // ���� ���������� ���������� ��������� ���������,
	{
		in.clear(); // �� ���������� cin � '�������' ����� ������
		in.ignore(32767, '\n'); // � ������� �������� ����������� ����� �� �������� ������
		std::cout << std::endl << "����������� ������� ������.\n";
		return true;
	}
	else {
		in.ignore(32767, '\n'); // ������� ������ ��������, �� ������, ���� ��� ����
		return false;
	} 
}