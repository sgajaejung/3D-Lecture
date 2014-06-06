#pragma once

namespace graphic
{

	class cNode
	{
	public:
		enum NODE_TYPE { NONE, BONE, MESH };

		cNode( const int id);
		virtual ~cNode();

		int GetId();
		cNode* GetParent();
		int GetMaterialId();
		const Matrix44& GetTM();
		bool InsertChild(cNode *node);
		cNode* FindNode(const int id);
		bool RemoveNode(const int id);
		void Clear();

		virtual bool Move(const float elapseTime) {return true;}
		virtual void Render(const Matrix44 &parentTm) {}


	protected:
		int m_id;
		cNode *m_parent;
		vector<cNode*> m_children;
		NODE_TYPE m_nodeType;
		int m_materialId;
		Matrix44 m_matLocal;
		Matrix44 m_matAni;
		Matrix44 m_matTM;
	};


	inline int cNode::GetId() { return m_id; }
	inline cNode* cNode::GetParent() { return m_parent; }
	inline int cNode::GetMaterialId() { return m_materialId; }
	inline const Matrix44& cNode::GetTM() { return m_matTM; }
}
