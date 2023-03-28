#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}
//����VBO��VAO��
void VAO::LinkVBO(VBO VBO, GLuint layout)
{
	VBO.Bind();
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}
//��VAO
void VAO::Bind()
{
	glBindVertexArray(ID);
}
//���VAO
void VAO::Unbind()
{
	glBindVertexArray(0);
}
//ɾ��VAO
void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}