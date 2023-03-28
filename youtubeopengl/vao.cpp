#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}
//链接VBO到VAO上
void VAO::LinkVBO(VBO VBO, GLuint layout)
{
	VBO.Bind();
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}
//绑定VAO
void VAO::Bind()
{
	glBindVertexArray(ID);
}
//解绑VAO
void VAO::Unbind()
{
	glBindVertexArray(0);
}
//删除VAO
void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}