#pragma once
#include "../Base/SingletonBase.h"
#include "cl.pb.h"

class ProtobufManager: public SingletonBase<ProtobufManager>
{
public:
	std::string Encode();
	void Decode(TArray<uint8> Buffer);
};
