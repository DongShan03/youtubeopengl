#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"


int main() {
	//��ʼ��GLFW
	glfwInit();

	//��֪ϵͳ��ʹ�õ�GLFW�汾��Ϊ 3.3 core
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//�㼯
	GLfloat vertices[] =
	{
		//    ����											��ɫ
		-0.5f, -0.5f * float(sqrt(3)) / 3,      0.0f,	 0.8f, 0.3f, 0.02f,
		0.5f, -0.5f * float(sqrt(3)) / 3,       0.0f,	 0.8f, 0.3f, 0.02f,
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3,    0.0f,	 1.0f, 0.6f, 0.32f,
		- 0.5f / 2, 0.5f * float(sqrt(3)) / 6,  0.0f,	 0.9f, 0.45f, 0.17f,
		0.5f / 2, 0.5f * float(sqrt(3)) / 6,    0.0f,	 0.9f, 0.15f, 0.17f,
		0.0f, -0.5f * float(sqrt(3)) / 3,       0.0f,	 0.8f, 0.3f, 0.02f,
	};

	GLuint indices[] =
	{
		0, 3, 5, //���½�
		3, 2, 4, //���½�
		5, 4, 1, //�Ϸ�
	};

	//����GLFW���ڣ�800*800��������ΪYoutubeOpenGL
	GLFWwindow* window = glfwCreateWindow(800, 800, "YoutubeOpenGL", NULL, NULL);
	//���window��ʼ���Ƿ�ɹ�
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << "\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	//����GLAD
	gladLoadGL();

	//ָ��OpenGl����
	//��������x=0, y=0, to x=800, y=800
	glViewport(0, 0, 800, 800);

	//���ļ��ж�ȡ���벢����Ĭ����ɫ��
	Shader shaderProgram("default.vert", "default.frag");
	
	//����Vertex Buffer���岢��
	VAO VAO1;
	VAO1.Bind();

	//����Vertex Buffer���岢���ӵ���
	VBO VBO1(vertices, sizeof(vertices));
	//����Element Buffer���岢���ӵ�����
	EBO EBO1(indices, sizeof(indices));

	//����VBO��VAO
	VAO1.LinkVBO(VBO1, 0);
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	//��ѭ��
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//����OpenGL���ĸ���ɫ��Program
		shaderProgram.Activate();
		//��VAO��ʹ��
		VAO1.Bind();
		//����������
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	//ɾ�����õ�����
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	//�������ʱ�ݻٴ���
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}