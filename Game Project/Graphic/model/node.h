#pragma once

namespace graphic
{

	class cNode
	{
	public:
		enum NODE_TYPE { NONE, BONE, MESH };

		cNode( const int id);
		virtual ~cNode();

		int GetId() const;
		cNode* GetParent();
		int GetMaterialId() const;

		const Matrix44& GetTM() const;
		const Matrix44& GetLocalTM() const;
		void SetTM(const Matrix44 &tm);
		void SetLocalTM(const Matrix44 &tm);

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
		Matrix44 m_localTM;
		Matrix44 m_aniTM;
		Matrix44 m_tm;
	};


	inline int cNode::GetId() const { return m_id; }
	inline cNode* cNode::GetParent() { return m_parent; }
	inline int cNode::GetMaterialId() const { return m_materialId; }
	inline const Matrix44& cNode::GetTM() const { return m_tm; }
	inline void cNode::SetTM(const Matrix44 &tm) { m_tm = tm; }
	inline const Matrix44& cNode::GetLocalTM() const { return m_localTM; }
	inline void cNode::SetLocalTM(const Matrix44 &tm) { m_localTM = tm; }

}
