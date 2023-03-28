#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

//��ȡ��ɫ������Ƭ��
std::string get_file_contents(const char* filename);

class Shader
{
public:
	GLuint ID;
	//���ļ��ж�ȡ����Ƭ�β�������ɫ��
	Shader(const char* vertexFile, const char* fragmentFile);

	//����shade Program
	void Activate();
	//ɾ��shade Program
	void Delete();
};


#endif