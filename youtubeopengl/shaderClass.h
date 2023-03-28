#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

//读取着色器代码片段
std::string get_file_contents(const char* filename);

class Shader
{
public:
	GLuint ID;
	//从文件中读取代码片段并构建着色器
	Shader(const char* vertexFile, const char* fragmentFile);

	//激活shade Program
	void Activate();
	//删除shade Program
	void Delete();
};


#endif