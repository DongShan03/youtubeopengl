#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "shaderClass.h"
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
		//    坐标											颜色
		-0.5f, -0.5f * float(sqrt(3)) / 3,      0.0f,	 0.8f, 0.3f, 0.02f,
		0.5f, -0.5f * float(sqrt(3)) / 3,       0.0f,	 0.8f, 0.3f, 0.02f,
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3,    0.0f,	 1.0f, 0.6f, 0.32f,
		- 0.5f / 2, 0.5f * float(sqrt(3)) / 6,  0.0f,	 0.9f, 0.45f, 0.17f,
		0.5f / 2, 0.5f * float(sqrt(3)) / 6,    0.0f,	 0.9f, 0.15f, 0.17f,
		0.0f, -0.5f * float(sqrt(3)) / 3,       0.0f,	 0.8f, 0.3f, 0.02f,
	};

	GLuint indices[] =
	{
		0, 3, 5, //左下角
		3, 2, 4, //右下角
		5, 4, 1, //上方
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
	VAO1.LinkVBO(VBO1, 0);
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	//主循环
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//告诉OpenGL用哪个着色器Program
		shaderProgram.Activate();
		//绑定VAO以使用
		VAO1.Bind();
		//绘制三角形
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	//删除无用的数据
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	//程序结束时摧毁窗口
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}