#pragma once


namespace graphic
{

	class cVertexBuffer
	{
	public:
		cVertexBuffer();
		virtual ~cVertexBuffer();

		bool Create(int vertexCount, int sizeofVertex, int fvf);
		void* Lock();
		void Unlock();
		void Bind() const;
		void Clear();

		int GetFVF() const;
		int GetSizeOfVertex() const;
		int GetVertexCount() const;


	private:
		LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
		int m_fvf;
		int m_sizeOfVertex;
		int m_vertexCount;
	};

	
	inline int cVertexBuffer::GetFVF() const { return m_fvf; }
	inline int cVertexBuffer::GetSizeOfVertex() const { return m_sizeOfVertex; }
	inline int cVertexBuffer::GetVertexCount() const { return m_vertexCount; }
}
