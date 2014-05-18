/**
 @filename particle.h
  
*/
#pragma once

#include "math/Math.h"
#include <vector>
using std::vector;

class cParticle
{
public:
	cParticle(const POINT &pos);
	virtual ~cParticle();
	void Render(HDC hdc);
	bool Move(int elapseTime);


protected:


private:
	vector<Vector3> m_vertices;
	vector<int> m_indices;
	Matrix44 m_tm;
	Matrix44 m_localTm;
	Vector3 m_Velocity;
	Vector3 m_Pos;
	float m_Torq;
};



// cParticleManager
class cParticleManager
{
public:
	cParticleManager();
	virtual ~cParticleManager();
	void AddParticle(cParticle *partcle);
	void Render(HDC hdc);
	bool Move(int elapseTime);

private:
	vector<cParticle*> m_particles;
};
