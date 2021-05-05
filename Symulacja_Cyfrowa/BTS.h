#ifndef Symulacja_Cyfrowa_Symulacja_Cyfrowa_BTS_H_
#define Symulacja_Cyfrowa_Symulacja_Cyfrowa_BTS_H_


#pragma once
#include <vector>
#include "User.h"
#include <iostream>

class BTS
{
public:

	struct Resource_Block_;
	
	/// SETTERS ///

	void Set_Resource_Block_Count(int Resource_Block_Count);
	void Set_Reousrce_Block_Cap();
	std::vector<Resource_Block_>Get_Resource_Blocks_() { return Resource_Blocks_; }
	void Set_Data();
	void Set_Transmission_Succes_Flag(int Current_User_Handled_ID);
	void Set_Resource_Blocks_Size();
	//std::vector<int> Set_Resource_Block_To_User(int Packets_Per_User);

	/// GETTERS ///

	bool Get_Blocks_Depleted_Flag();
	int Get_Resource_Block_Count() { return Resource_Block_Count_; }
	std::vector<int>Get_Resource_Block_Map() { return Resource_Block_Map_; }
	
	void Map_Reource_Block();
	void Wipe_Resource_Blocks_To_Be_Sent();
	bool Draw_Error();
	void Wipe_Resource_Block_Map();
	void Send_Data_To_User(int Bit_Rate);
	void Send_Block_To_User(int Resource_Block_Count, std::vector<int>User_Bit_Rate_Vector,User* user);

	//void Map_User(User* user);
	void init();
	
	BTS(int Resource_Block_Count);

private:

	struct Resource_Block_
	{
		User* user = nullptr;
		bool Error_Flag_;
		int Bit_Rate_;
	};
	bool Blocks_Depleted;

	std::vector<Resource_Block_>Resource_Blocks_;
	
	int Resource_Block_Count_;
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
