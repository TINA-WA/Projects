#pragma once
class String
{
private:
	char* content;//�ַ���
	int capacity;//����
public:
	int count;//������
	String(char* str);//����ԭ��
	String(const String&str);//�����ַ���
	~String();//����
	char* GetCString();//�õ�C�ַ���
};
