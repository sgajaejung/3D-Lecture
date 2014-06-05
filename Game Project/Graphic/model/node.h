#pragma once

namespace graphic
{

	class cNode
	{
	public:
		cNode( const int id);
		virtual ~cNode();

		int GetId();
		bool InsertChild(cNode *node);
		cNode* FindNode(const int id);
		bool RemoveNode(const int id);
		void Clear();

		virtual bool Move(const float elapseTime);
		virtual void Render();

	protected:


	private:
		int m_id;
		cNode *m_parent;
		vector<cNode*> m_children;
	};


	inline int cNode::GetId() { return m_id; }
}
