#pragma once


namespace graphic
{
	class cBoneNode;

	class cBoneMgr
	{
	public:
		cBoneMgr(const int id, const sRawMeshGroup &rawMeshes);
		virtual ~cBoneMgr();

		void SetAnimation( const sRawAniGroup &rawAnies, int nAniFrame );
		bool Move(const float elapseTime);
		void Render(const Matrix44 &parentTm);
		void Clear();	
		cBoneNode* FindBone(const int id);
		vector<Matrix44>& GetPalette();


	protected:
		void SetAnimationRec( cBoneNode *node, const sRawAniGroup &rawAni, int nAniFrame );


	private:
		int m_id;
		cBoneNode *m_root;
		vector<Matrix44> m_palette;
	};


	inline vector<Matrix44>& cBoneMgr::GetPalette() { return m_palette; }
}
