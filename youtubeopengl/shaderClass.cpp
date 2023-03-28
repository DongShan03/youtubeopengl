#include "shaderClass.h"

//文件读取转化为std::string对象
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

//构建着色器
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	//创建着色器对象
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//将vertex着色器源码加载到vertex物体
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	//编译vertex着色器为机器码
	glCompileShader(vertexShader);


	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//将fragment着色器源码加载到vertex物体
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	//编译fragment着色器为机器码
	glCompileShader(fragmentShader);
	//判断着色器生成是否有问题
	compileErrors(fragmentShader, "FRAGMENT");

	//创建Shader Program Object
	ID = glCreateProgram();
	//将vertex着色器和fragment着色器加载进Shader Program Object
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	//将所有着色器链接进Shader Program
	glLinkProgram(ID);
	//判断着色器生成是否有问题
	compileErrors(vertexShader, "PROGRAM");

	//删除已经无用的
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

//判断着色器的生成是否有问题
void Shader::compileErrors(unsigned int shader, const char* type)
{
	GLint hasCompiled;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << std::endl;

		}

	}
	else
	{
		glGetProgramiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << std::endl;
		}
	}
}