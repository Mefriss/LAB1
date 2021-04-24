#ifndef Symulacja_Cyfrowa_Symulacja_Cyfrowa_BTS_H_
#define Symulacja_Cyfrowa_Symulacja_Cyfrowa_BTS_H_


#pragma once
#include <vector>
#include "User.h"
#include <iostream>

class BTS
{
public:
	void Set_Resource_Block_Count(int Resource_Block_Count);
	void Set_Reousrce_Block_Cap();
	void Map_Reource_Block();
	void Set_Data();
	void Set_Transmission_Succes_Flag(int Current_User_Handled_ID);
	void Wipe_Resource_Blocks_To_Be_Sent();
	bool Get_Blocks_Depleted_Flag();
	bool Draw_Error();
	void Wipe_Resource_Block_Map();
	void Send_Data_To_User(int Bit_Rate);
	void Send_Block_To_User(int Resource_Block_Count, std::vector<int>User_Bit_Rate_Vector);
	//void Map_User(User* user);
	std::vector<int> Set_Resource_Block_To_User(int Packets_Per_User);

	std::vector<int>Get_Resource_Block_Map() { return Resource_Block_Map_; }
	
	BTS(int Resource_Block_Count);

private:

	
	bool Blocks_Depleted;
	int Resource_Block_Count_; // Zmienna k = 15
	std::vector<int>Resource_Block_Cap_; // l maksymalnie 3
	std::vector<int>Resource_Block_Map_; // tablica przypisuj¹ca bloki zasobów u¿ytkownikom o rozmiarze = Reource_block_count
	std::vector<int>Resource_Blocks_To_Be_Sent;
	std::vector<bool> Transmission_Succes_Flag_;
	
	
		//std::vector<int>Resource_Block_Cap, 
		//std::vector<int>Resource_Block_Map, 
		//std::vector<bool> Transmission_Succes_Flag)
		//)
	//:Resource_Block_Count_(Resource_Block_Count)
	//,Resource_Block_Cap_(Resource_Block_Cap)
	//,Resource_Block_Map_(Resource_Block_Map)
	//,Transmission_Succes_Flag_(Transmission_Succes_Flag)
	//	{
	//	
	//}
	//
};
#endif
