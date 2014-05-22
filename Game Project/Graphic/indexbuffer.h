#pragma once

namespace graphic
{

	class cIndexBuffer
	{
	public:
		cIndexBuffer();
		virtual ~cIndexBuffer();

		bool Create(int faceCount);
		void* Lock();
		void Unlock();
		void Bind() const;


	protected:


	private:
		LPDIRECT3DINDEXBUFFER9 m_pIdxBuff; // 인덱스 버퍼
	};

}
