
#include "particle.h"
#include "Renderer.h"
#include <set>


float randFloat()
{
	int x = rand() % 1000;
	x -= 500;
	float xx = (float)x / 500.f; 
	return xx;
}

cParticle::cParticle(const POINT &pos)
{
	//       (-30,-30)  ----------------- (+30, -30)
	//       |                                                       |
	//       |                         +                           |
	//       |                                                       |
	//       (-30,+30)  ----------------- (+30, +30)
	const float w = 10.f;
	m_vertices.push_back( Vector3(-w,-w,1) );
	m_vertices.push_back( Vector3(w,-w,1) );
	m_vertices.push_back( Vector3(w,w,1) );
	m_vertices.push_back( Vector3(-w,w,1) );
	m_vertices.push_back( Vector3(-w,-w,1) );

	m_indices.push_back(0);
	m_indices.push_back(3);
	m_indices.push_back(2);

	m_indices.push_back(0);
	m_indices.push_back(2);
	m_indices.push_back(1);

	m_tm.SetTranslate(Vector3((float)pos.x, (float)pos.y, 0));

	const float x = randFloat() * 1000.f;
	const float y = randFloat() * 1000.f;
	m_Velocity = Vector3(x,y,0);
	m_Pos = Vector3((float)pos.x, (float)pos.y, 0);

	m_Torq = randFloat() * 30.f;
}

cParticle::~cParticle()
{

}


/**
 @brief 
 @date 2014-04-17
*/
void cParticle::Render(HDC hdc)
{
	//RenderVertices(hdc, m_vertices, m_localTm*m_tm);
	RenderIndices(hdc, m_vertices, m_indices, m_localTm*m_tm);
}


/**
 @brief 
 @date 2014-04-17
*/
bool cParticle::Move(int elapseTime)
{
	const float dt = (float)elapseTime * 0.001f;
	m_Velocity += Vector3(0, 1000.f * dt, 0);
	m_Pos += m_Velocity * dt;
	m_tm.SetTranslate(m_Pos);

	Matrix44 mat;
	mat.SetRotationZ(m_Torq * dt);
	m_localTm *= mat;

	if (m_Pos.y > 1000.f)
		return false;

	return true;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////
// cParticleManager

cParticleManager::cParticleManager()
{

}

cParticleManager::~cParticleManager()
{
	for (int i=0; i < (int)m_particles.size(); ++i)
		delete m_particles[ i];
	m_particles.clear();
}


void cParticleManager::AddParticle(cParticle *partcle)
{
	m_particles.push_back(partcle);
}


void cParticleManager::Render(HDC hdc)
{
	if (m_particles.empty())
		return;

	for (int i=0; i < (int)m_particles.size(); ++i)
		m_particles[ i]->Render(hdc);
}


bool cParticleManager::Move(int elapseTime)
{
	if (m_particles.empty())
		return false;

	vector<int> rm;
	for (int i=0; i < (int)m_particles.size(); ++i)
	{
		if (!m_particles[ i]->Move(elapseTime))
			rm.push_back(i);
	}

	for (int i=rm.size()-1; i >= 0; --i)
	{
		delete m_particles[ rm[ i]];
		m_particles.erase( m_particles.begin()+rm[ i] );
	}

	return true;
}
