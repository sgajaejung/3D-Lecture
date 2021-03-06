
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

#pragma pack(4)
	struct sPacketHeader
	{
		PROTOCOL::TYPE protocol;
		char sendId[32];
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
#pragma pack()

}