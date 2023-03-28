#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "shaderClass.h"
#include "Texture.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"


int main() {
	//初始化GLFW
	glfwInit();

	//告知系统所使用的GLFW版本号为 3.3 core
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//点集
	GLfloat vertices[] =
	{
		//    坐标					颜色
		-0.5f, -0.5f,0.0f,	 1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f,	 0.0f, 1.0f, 0.0f,	0.0f, 1.0f,
		0.5f,  0.5f,  0.0f,	 0.0f, 0.0f, 1.0f,	1.0f, 1.0f,
		0.5f, -0.5f,  0.0f,	 1.0f, 1.0f, 1.0f,	1.0f, 0.0f,
	};

	GLuint indices[] =
	{
		0, 2, 1, //上三角
		0, 3, 2, //下三角
	};

	//创建GLFW窗口（800*800）并命名为YoutubeOpenGL
	GLFWwindow* window = glfwCreateWindow(800, 800, "YoutubeOpenGL", NULL, NULL);
	//检查window初始化是否成功
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << "\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	//加载GLAD
	gladLoadGL();

	//指定OpenGl窗口
	//在这里是x=0, y=0, to x=800, y=800
	glViewport(0, 0, 800, 800);

	//从文件中读取代码并生成默认着色器
	Shader shaderProgram("default.vert", "default.frag");
	
	//生成Vertex Buffer物体并绑定
	VAO VAO1;
	VAO1.Bind();

	//生成Vertex Buffer物体并链接到点
	VBO VBO1(vertices, sizeof(vertices));
	//生成Element Buffer物体并链接到索引
	EBO EBO1(indices, sizeof(indices));

	//链接VBO到VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	//用于接收统一缩放参数
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	Texture dog("dog.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	dog.texUnit(shaderProgram, "tex0", 0);

	//主循环
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//告诉OpenGL用哪个着色器Program
		shaderProgram.Activate();
		//统一缩放参数的赋值
		glUniform1f(uniID, 0.5f);
		dog.Bind();
		//绑定VAO以使用
		VAO1.Bind();
		//绘制三角形
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	//删除无用的数据
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	dog.Delete();
	shaderProgram.Delete();

	//程序结束时摧毁窗口
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}