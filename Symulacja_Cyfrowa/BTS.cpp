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
void BTS::Map_Reource_Block()
{
	
}
void BTS::Set_Data()
{
	
	//for(int i = 0; i < Resource_Block_Count_;i++)
	for (int i = 0; i < 15;i++)
	{
		//Resource_Block_Map_.push_back(rand() % 800 + 21);
		Resource_Block_Map_.push_back((rand() % 10 + 1)*250);
		std::cout << Resource_Block_Map_[i]<<" ";
	}
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	
}

void BTS::Set_Transmission_Succes_Flag(int Current_User_Handled_ID)
{


	Transmission_Succes_Flag_.push_back(Draw_Error());


}
void BTS::Wipe_Resource_Blocks_To_Be_Sent()
{
	int i = 0;
	while(!Resource_Blocks_To_Be_Sent.empty())
	{
		Resource_Blocks_To_Be_Sent.pop_back();
	}
}
void BTS::Wipe_Resource_Block_Map()
{
	
	while (!Resource_Blocks_To_Be_Sent.empty())
	{
		Resource_Blocks_To_Be_Sent.pop_back();
	}
}


std::vector<int> BTS::Set_Resource_Block_To_User(int Packets_Per_User)// OBSELOTE
{
	Blocks_Depleted = false;
	Wipe_Resource_Blocks_To_Be_Sent();
	if(Resource_Block_Count_ >= Packets_Per_User)
	{
		for (int i = 0; i < Packets_Per_User;i++)
		{
			Resource_Blocks_To_Be_Sent.push_back(Resource_Block_Map_[Resource_Block_Count_-i]);
			Resource_Block_Map_.pop_back();
			Resource_Block_Count_--;
			//std::cout<<Resource_Blocks_To_Be_Sent[i]<< " ";
		}
		
		return Resource_Blocks_To_Be_Sent;
	}
	else if(Resource_Block_Count_ < Packets_Per_User && Resource_Block_Count_>= 0)
	{
		for (int i = Resource_Block_Count_; i >= 0;i--)
		{
				Resource_Blocks_To_Be_Sent.push_back(Resource_Block_Map_[i]);
				Resource_Block_Map_.pop_back();
				Resource_Block_Count_--;
				//std::cout<<Resource_Blocks_To_Be_Sent[i]<< " ";


		}
		Resource_Block_Count_ = -1;
		Blocks_Depleted = true;
		return Resource_Blocks_To_Be_Sent;
	}

}
bool BTS::Get_Blocks_Depleted_Flag()
{
	return Blocks_Depleted;
}
bool BTS::Draw_Error()
{
	bool Error_Var = (rand() % 10 + 1) / 10;
	if (!Error_Var)
		std::cout << "Transmisja odby³a siê bez b³êdów" << std::endl;
	else
	{
		std::cout << "Transmisja odby³a siê z b³êdem" << std::endl;
		spdlog::error("Transimission Error");
	}
	return Error_Var;
}

void BTS::Send_Data_To_User(int Bit_Rate)
{
	
}

void BTS::Send_Block_To_User(int Resource_Block_Count, std::vector<int>User_Bit_Rate_Vector,User* user)
{
	if(!((rand() % 10 + 1) / 10))
		if(user -> Get_Data_To_Be_Fetched()>Resource_Block_Map_.front())
			Resource_Block_Map_.push_back(User_Bit_Rate_Vector.front());
		else
			Resource_Block_Map_.push_back(user->Get_Data_To_Be_Fetched());
	else
		spdlog::error("Transimission Error");
	Wipe_Resource_Block_Map();
	User_Bit_Rate_Vector.pop_back();
}


BTS::BTS(int Resource_Block_Count)
{
	Resource_Block_Map_.reserve(Resource_Block_Count);
	Resource_Block_Count_ = Resource_Block_Count;
	--Resource_Block_Count_;
}
