#pragma  once


namespace graphic
{
	struct sRawMesh;
	struct sRawAni;

	class cResourceManager : public common::cSingleton<cResourceManager>
	{
	public:
		cResourceManager();
		virtual ~cResourceManager();
		
		sRawMesh* LoadModel( const string &fileName );
		sRawMesh* FindModel( const string &fileName );
		sRawAni* FindAni( const string &fileName );
		cTexture* LoadTexture( const string &fileName );
		void Clear();


	private:
		map<string, sRawMesh*> m_meshes; // key = fileName
		map<string, sRawAni*> m_anies;	// key = fileName
		map<string, cTexture*> m_textures; // key = fileName
	};

}
