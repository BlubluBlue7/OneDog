#include "Data_Manager.h"

Data_Manager::Data_Manager()
{
	// Bag = NewObject<UData_Bag>();
	Bag = new UData_Bag();

	Clear();
}

void Data_Manager::Clear()
{
	Bag->Init();
}
