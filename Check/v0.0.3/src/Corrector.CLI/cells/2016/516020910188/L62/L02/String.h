#pragma once
class String
{
private:
	char* content;
	int capacity;
public:
	int count;
	String(char*str);
	String(const String& str);
	~String();
	char*GetCString();

};//声明类所包含的项目

