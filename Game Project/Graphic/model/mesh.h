#pragma once

#include "node.h"

namespace graphic
{

	class cMesh : public cNode
	{
	public:
		cMesh(const int id, const sRawMesh &raw);
		virtual ~cMesh();

		void LoadAnimation( const sRawAni &rawAni );
		virtual bool Move(const float elapseTime) override;
		virtual void Render(const Matrix44 &parentTm) override;
		void RenderBBox();


	private:
		bool m_isSkinned;
		cMaterial m_mtrl;
		cVertexBuffer m_vtxBuff;
		cIndexBuffer m_idxBuff;

		// animation
		cTrack *m_track;
		int m_aniStart;
		int m_aniEnd;
		int m_aniFrame;
		float m_aniTime;
		//Matrix44 m_matAniTM;
	};

}
