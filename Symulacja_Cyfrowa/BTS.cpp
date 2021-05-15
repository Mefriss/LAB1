#include "BTS.h"

#include <iostream>
#include <spdlog/spdlog.h>

//void BTS::Set_Resource_Block_Count(int Resource_Block_Count)
//{
//	Resource_Block_Count_ = Resource_Block_Count;
//}
void BTS::Set_Reousrce_Block_Cap()
{
	
}

void BTS::Set_Transmission_Succes_Flag(int Current_User_Handled_ID)
{


	Transmission_Succes_Flag_.push_back(Draw_Error());


}

void BTS::Set_User_Pointer_To_Resource_Block(User* user, int Vector_i)
{
	Resource_Blocks_[Vector_i].user = user;
}

void BTS::Set_Bit_Rate(int Bit_Rate, int Vector_i)
{
	Resource_Blocks_[Vector_i].Bit_Rate_ = Bit_Rate;
}

void BTS::Set_Error_Flag(bool Error_Flag, int Vector_i)
{
	Resource_Blocks_[Vector_i].Error_Flag_ = Error_Flag;
}


bool BTS::Get_Blocks_Depleted_Flag()
{
	return Blocks_Depleted;
}
bool BTS::Draw_Error()
{
	bool Error_Var = (rand() % 10 + 1) / 10;
	if (!Error_Var)
	{
		//std::cout << "Transmisja odby³a siê bez b³êdów" << std::endl;
		
	}
	else
	{
		//std::cout << "Transmisja odby³a siê z b³êdem" << std::endl;
		spdlog::debug("Transimission Error");
	}
	return Error_Var;
}

void BTS::Send_Data_To_User(int Bit_Rate)
{
	
}

void BTS::Send_Block_To_User(int Resource_Block_Count, std::vector<int>User_Bit_Rate_Vector,User* user)
{


	
	//if (!((rand() % 10 + 1) / 10))
	//{
	//	Transmission_Succes_Flag_.push_back(true);
	//	user->Set_User_Data(1);
	//}
	//	
	//else
	//{
	//	Transmission_Succes_Flag_.push_back(false);
	//	user->Set_User_Data(0);
	//	spdlog::debug("Transimission Error");
	//}
	//	
	//	
	//Wipe_Resource_Block_Map();
	////User_Bit_Rate_Vector.pop_back();
}

void BTS::init()
{

	for (int i = 0; i < Get_Resource_Block_Count(); i++)
	{
		Resource_Block_ Resource_Block;
		Resource_Blocks_.push_back(Resource_Block);
	}
}


BTS::BTS(int Resource_Block_Count)
{
	//Resource_Blocks_.reserve(Resource_Block_Count);
	Resource_Block_Count_ = Resource_Block_Count;
	//--Resource_Block_Count_;
}
