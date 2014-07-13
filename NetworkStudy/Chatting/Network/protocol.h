
#pragma once


namespace network
{

	namespace PROTOCOL
	{
		enum TYPE
		{
			LOGIN,
			CHATTING,
		};
	}


	struct sPacketHeader
	{
		PROTOCOL::TYPE protocol;
	};


	struct sLoginProtocol
	{
		sPacketHeader header;
		char name[ 32];
		char pass[ 8];
	};


	struct sChatProtocol
	{
		sPacketHeader header;
		char msg[ 64];
	};

}