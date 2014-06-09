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
		void Clear();

		void SetTM(const Matrix44 &tm);
		void MultiplyTM(const Matrix44 &tm);
		const Matrix44& GetTM();


	private:
		vector<cNode*> m_meshes;
		Matrix44 m_matTM;
	};


	inline void cModel::SetTM(const Matrix44 &tm) { m_matTM = tm; }
	inline void cModel::MultiplyTM(const Matrix44 &tm) { m_matTM *= tm; }
	inline const Matrix44& cModel::GetTM() { return m_matTM; }
}
