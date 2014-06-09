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
		
		sRawMeshGroup* LoadModel( const string &fileName );
		sRawMeshGroup* FindModel( const string &fileName );
		cTexture* LoadTexture( const string &fileName );
		void Clear();


	private:
		map<string, sRawMeshGroup*> m_meshes; // key = fileName
		map<string, cTexture*> m_textures; // key = fileName
	};

}
