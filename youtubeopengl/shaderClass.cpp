#include "shaderClass.h"

//�ļ���ȡת��Ϊstd::string����
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

//������ɫ��
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	//������ɫ������
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//��vertex��ɫ��Դ����ص�vertex����
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	//����vertex��ɫ��Ϊ������
	glCompileShader(vertexShader);


	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//��fragment��ɫ��Դ����ص�vertex����
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	//����fragment��ɫ��Ϊ������
	glCompileShader(fragmentShader);

	//����Shader Program Object
	ID = glCreateProgram();
	//��vertex��ɫ����fragment��ɫ�����ؽ�Shader Program Object
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	//��������ɫ�����ӽ�Shader Program
	glLinkProgram(ID);

	//ɾ���Ѿ����õ�
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glUseProgram(ID);
}