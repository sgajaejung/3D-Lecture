
#include "stdafx.h"
#include "node.h"

using namespace graphic;


cNode::cNode( const int id)
{

}

cNode::~cNode()
{

}


bool cNode::Move(const float elapseTime)
{

	return true;
}

void cNode::Render()
{
	
}


// 노드를 자식으로 추가한다.
bool cNode::InsertChild(cNode *node)
{
	RETV(!node, false);
	RETV(FindNode(node->GetId()), false); // Already Exist
	
	m_children.push_back(node);
	return true;
}


// 자식 노드 중에 id 와 같은 노드가 있다면 리턴한다.
cNode* cNode::FindNode(const int id)
{
	if (GetId() == id)
		return this;

	BOOST_FOREACH (auto node, m_children)
	{


	}

	return NULL;
}


bool cNode::RemoveNode(const int id)
{

	return true;
}


void cNode::Clear()
{

}
