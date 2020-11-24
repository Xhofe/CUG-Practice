
#include "pendulumSystem.h"

PendulumSystem::PendulumSystem(int numParticles):ParticleSystem(numParticles)
{
	m_numParticles = numParticles;
	
	// fill in code for initializing the state based on the number of particles
	// ��д���ڻ�������������ʼ��״̬�Ĵ���
	float r = 0.25f;
	if (m_numParticles == 1) {
		r = 1.0f;
	}
	for (int i = 0; i < m_numParticles; i++) {
		
		// for this system, we care about the position and the velocity
		m_vVecState.push_back(Vector3f(r + i * r, 0, 0));
		m_vVecState.push_back(Vector3f(0, 0, 0));//��ʼ�ٶ�Ϊ0
	}
}


// TODO: implement evalF
// for a given state, evaluate f(X,t)
vector<Vector3f> PendulumSystem::evalF(vector<Vector3f> state)
{
	vector<Vector3f> f;

	// YOUR CODE HERE
	//for (size_t i = 0; i < state.size(); i++)
	//{
	//	f.push_back(Vector3f::ZERO);
	//}
	float mass = 0.05f;//����
	float k_resistance = 0.015f;//����ϵ��
	float k_elasticity = 2.0f;//���ɵ���ϵ��
	float r = 0.25f;//��ʼ����
	if (m_numParticles == 1) {
		r = 1.0f;
	}
	//��������
	if (state.size() <= 2) {
		for (size_t i = 0; i < state.size(); i += 2)
		{
			f.push_back(state.at(i + 1));//X��fΪv
			Vector3f gravity(0, -9.8, 0);//����
			Vector3f resistance = -k_resistance / mass * state.at(i + 1);//ճ��������
			//���ɵ���
			float x = state.at(i).x();
			float y = state.at(i).y();
			float len = sqrt(x*x + y * y);
			float composition = -k_elasticity * (len - r);
			float elasticity_x = x / len * composition;
			float elasticity_y = y / len * composition;
			Vector3f elasticity(elasticity_x / mass, elasticity_y / mass, 0);
			f.push_back(gravity + resistance + elasticity);
		}
	}
	else//�������
	{
		Vector3f elasticity_next;
		for (size_t i = 0; i < state.size(); i+=2) {
			f.push_back(state.at(i + 1));//X��fΪv
			Vector3f gravity(0, -9.8, 0);//����
			Vector3f resistance = -k_resistance / mass * state.at(i + 1);//ճ��������
			//���ɵ���
			//��һ������
			if (i == 0) {
				float x = state.at(i).x();
				float y = state.at(i).y();
				float len = sqrt(x*x + y * y);
				float composition = -k_elasticity * (len - r);
				float elasticity_x = x / len * composition;
				float elasticity_y = y / len * composition;
				Vector3f elasticity(elasticity_x / mass, elasticity_y / mass, 0);
				float x_next = state.at(i + 2).x() - x;
				float y_next = state.at(i + 2).y() - y;
				float len_next = sqrt(x_next*x_next + y_next * y_next);
				float composition_next = -k_elasticity * (len_next - r);
				float elasticity_next_x = x_next / len_next * composition_next;
				float elasticity_next_y = y_next / len_next * composition_next;
				elasticity_next = Vector3f(elasticity_next_x / mass, elasticity_next_y / mass, 0);
				f.push_back(gravity + resistance + elasticity - elasticity_next);
			}
			//���һ��
			else if (i == state.size() - 2) {
				f.push_back(gravity + resistance + elasticity_next);
			}
			else {
				Vector3f elasticity = elasticity_next;
				float x = state.at(i).x();
				float y = state.at(i).y();
				float x_next = state.at(i + 2).x() - x;
				float y_next = state.at(i + 2).y() - y;
				float len_next = sqrt(x_next*x_next + y_next * y_next);
				float composition_next = -k_elasticity * (len_next - r);
				float elasticity_next_x = x_next / len_next * composition_next;
				float elasticity_next_y = y_next / len_next * composition_next;
				elasticity_next = Vector3f(elasticity_next_x / mass, elasticity_next_y / mass, 0);
				f.push_back(gravity + resistance + elasticity - elasticity_next);
			}
		}
	}

	return f;
}

// render the system (ie draw the particles)
void PendulumSystem::draw()
{
	for (int i = 0; i < m_numParticles; i++) {
		Vector3f pos =m_vVecState.at(i*2);//  position of particle i. YOUR CODE HERE
		glPushMatrix();
		glTranslatef(pos[0], pos[1], pos[2] );
		glutSolidSphere(0.075f,10.0f,10.0f);
		glPopMatrix();
	}
}
