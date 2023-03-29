#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaderClass.h"
#include "Texture.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Camera.h"


const int width = 800;
const int height = 800;

//点集
GLfloat vertices[] =
{
	//    坐标					   颜色                     UV           normal      
	-1.0f, 0.0f, 1.0f,   0.0f, 0.0f, 0.0f,   0.0f, 0.0f,    0.0f, 1.0f, 0.0f,
	-1.0f, 0.0f, -1.0f,  0.0f, 0.0f, 0.0f,   0.0f, 1.0f,    0.0f, 1.0f, 0.0f,
	1.0f, 0.0f, -1.0f,   0.0f, 0.0f, 0.0f,   1.0f, 1.0f,    0.0f, 1.0f, 0.0f,
	1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,   1.0f, 0.0f,    0.0f, 1.0f, 0.0f,
};

GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
};

GLfloat lightVertices[] =
{
	-0.1f, -0.1f, 0.1f,
	-0.1f, -0.1f, -0.1f,
	0.1f, -0.1f, -0.1f,
	0.1f, -0.1f, 0.1f,
	-0.1f, 0.1f, 0.1f,
	-0.1f, 0.1f, -0.1f,
	0.1f, 0.1f, -0.1f,
	0.1f, 0.1f, 0.1f,
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7,
};

int main() {
	//初始化GLFW
	glfwInit();

	//告知系统所使用的GLFW版本号为 3.3 core
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	//创建GLFW窗口（800*800）并命名为YoutubeOpenGL
	GLFWwindow* window = glfwCreateWindow(width, height, "YoutubeOpenGL", NULL, NULL);
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
	glViewport(0, 0, width, height);

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
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	Shader lightShader("light.vert", "light.frag");

	VAO lightVAO;
	lightVAO.Bind();

	VBO lightVBO(lightVertices, sizeof(lightVertices));
	EBO lightEBO(lightIndices, sizeof(lightIndices));

	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();


	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);


	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos);

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);



	Texture baseTexture("Albedo.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
	baseTexture.texUnit(shaderProgram, "tex0", 0);

	Texture SpecTexture("Spec.png", GL_TEXTURE_2D, 1, GL_RED, GL_UNSIGNED_BYTE);
	SpecTexture.texUnit(shaderProgram, "tex1", 1);

	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	//主循环
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Inputs(window);
		camera.updateMatrix(45.0f, 0.1f, 100.0f);


		shaderProgram.Activate();
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(shaderProgram, "camMatrix");

		baseTexture.Bind();
		SpecTexture.Bind();
		//绑定VAO以使用
		VAO1.Bind();
		//绘制三角形
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		
		lightShader.Activate();
		camera.Matrix(lightShader, "camMatrix");
		lightVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
		
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	//删除无用的数据
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	lightVAO.Delete();
	lightVBO.Delete();
	lightEBO.Delete();
	baseTexture.Delete();
	shaderProgram.Delete();

	//程序结束时摧毁窗口
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}