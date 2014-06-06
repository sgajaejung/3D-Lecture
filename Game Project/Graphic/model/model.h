#pragma once


namespace graphic
{
	class cNode;

	class cModel
	{
	public:
		cModel();
		virtual ~cModel();

		bool Create(const string &modelName);
		virtual bool Move(const float elapseTime);
		virtual void Render();


	private:
		cNode *m_root;
	};

}
