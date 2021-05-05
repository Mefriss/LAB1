#ifndef Symulacja_Cyfrowa_Symulacja_Cyfrowa_User_H_
#define Symulacja_Cyfrowa_Symulacja_Cyfrowa_User_H_

#pragma once
#include <vector>
//#include "BTS.h"
#include <iostream>

class User
{
public:

	//std::vector<int>Get_Bit_Rate();

	User(int User_ID, int Resource_Block_Count);
	~User();
	
	void Save_Blocks(std::vector<int>Recived_Blocks);
	int Draw_Data_To_Be_Fetched();
	//float Draw_Bit_Rate_Table();
	//void Draw_Bit_Rate();
	int Draw_New_Bit_Rate();
	// GETTERS //
	int Get_User_ID();
	int Get_Data_To_Be_Fetched() { return User_Data_; }
	std::vector<int> Get_Bit_Rate_Vector() { return Bit_Rate_; }
	int Get_User_Data() { return User_Data_; }
	// SETTERS //
	void Set_User_Data(int Data_Fetched);
	void Set_Bit_Rate();
	void Set_Data_To_Be_Fetched();
	void Update_Bit_Rate();

private:
	int User_ID_;
	int User_Data_;
	std::vector<int>Bit_Rate_;////Przepływność - r,k – zmienna losowa o rozkładzie jednostajnym w przedziale <20, 800> kbit/s
	std::vector<int>Recived_Blocks_;
	
};

#endif //Symulacja_Cyfrowa_Symulacja_Cyfrowa_User_H_