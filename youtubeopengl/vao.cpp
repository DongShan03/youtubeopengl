#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}
//链接VBO到VAO上
void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
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