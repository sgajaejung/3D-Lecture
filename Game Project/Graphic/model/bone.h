#pragma once


namespace graphic
{
	class cBoneNode;

	class cBone
	{
	public:
		cBone(const int id, const sRawMeshGroup &rawMeshes);
		virtual ~cBone();

		void SetAnimation( const sRawAniGroup &rawAnies, int nAniFrame );
		bool Move(const float elapseTime);
		void Render(const Matrix44 &parentTm);
		void Clear();	


	protected:
		void SetAnimationRec( cBoneNode *node, const sRawAniGroup &rawAni, int nAniFrame );
		bool MoveRec(cBoneNode *node, const float elapseTime);
		void RenderRec(cBoneNode *node, const Matrix44 &parentTm);


	private:
		cBoneNode *m_root;
		int m_id;
	};

}
