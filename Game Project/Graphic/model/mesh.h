#pragma once

#include "node.h"

namespace graphic
{

	class cMesh : public cNode
	{
	public:
		cMesh(const int id);
		virtual ~cMesh();

		virtual bool Move(const float elapseTime) override;
		virtual void Render() override;
		void RenderBBox();


	private:
		bool m_isSkinned;
		cVertexBuffer m_vtxBuff;
		cIndexBuffer m_idxBuff;
	};

}
