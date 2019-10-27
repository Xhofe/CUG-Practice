#include "MatrixStack.h"

MatrixStack::MatrixStack()
{
	// Initialize the matrix stack with the identity matrix.
	//�õ�λ�����ʼ�������ջ
	Matrix4f matrix = Matrix4f::identity();
	this->m_matrices.push_back(matrix);
}

void MatrixStack::clear()
{
	// Revert to just containing the identity matrix.
	this->m_matrices.clear();
	this->m_matrices.push_back(Matrix4f::identity());
}

Matrix4f MatrixStack::top()
{
	// Return the top of the stack
	return this->m_matrices.back();
}

void MatrixStack::push( const Matrix4f& m )
{
	// Push m onto the stack.
	// Your stack should have OpenGL semantics:
	// the new top should be the old top multiplied by m
	//��m�����ջ��
	//���Ķ�ջӦ����OpenGL���壺
	//�µĶ���Ӧ���ǾɵĶ�������m
	Matrix4f newM = this->top()*m;
	this->m_matrices.push_back(newM);
}

void MatrixStack::pop()
{
	// Remove the top element from the stack
	this->m_matrices.pop_back();
}
