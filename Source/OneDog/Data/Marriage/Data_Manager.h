#pragma once
#include "Data_Bag.h"
#include "Base/SingletonBase.h"

class Data_Manager: public SingletonBase<Data_Manager>
{
public:
	Data_Manager();
	void Clear();
	UData_Bag* Bag;
};
