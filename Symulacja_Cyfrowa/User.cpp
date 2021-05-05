#include "User.h"
#include "spdlog/spdlog.h"

//std::vector<int>User::Get_Bit_Rate()
//{
//	return;
//}

User::User(int User_ID, int Resource_Block_Count)
{
	//Bit_Rate_.reserve(1);
	for (int i = 0; i < Resource_Block_Count; i++)	
		Bit_Rate_.push_back(Draw_New_Bit_Rate()); //Przep³ywnoœæ - r,k – zmienna losowa o rozk³adzie jednostajnym w przedziale <20, 800> kbit/s
	User_ID_ = User_ID;
	User_Data_ = 3;
}

User::~User()
{
	std::cout << "Usuniêto u¿ytkownika nr: " << User_ID_<< std::endl;
}

void User::Save_Blocks(std::vector<int>Recived_blocks)
{
	for (int i = 0; i < Recived_blocks.size(); i++)
		{
			Recived_Blocks_.push_back(Recived_blocks[i]);
		}



}

int User::Draw_Data_To_Be_Fetched()
{
	return (rand() % 10 + 1) * 250;
}
int User::Draw_New_Bit_Rate()
{
	return (rand() % 800 + 21) * 1000;
}


//void User::Draw_New_Bit_Rate()
//{
//	Bit_Rate_.pop_back();
//	Bit_Rate_.push_back(rand() % 800 + 21);
//	
//}

void User::Set_User_Data(int Data_Fetched)
{
	User_Data_ -= Data_Fetched;
}

void User::Set_Data_To_Be_Fetched()
{
	User_Data_ = Draw_Data_To_Be_Fetched();
}

void User::Update_Bit_Rate()
{
	int temp = 0;
	while(!Bit_Rate_.empty())
	{
		Bit_Rate_.pop_back();
		++temp;
		
	}
	while (temp!=0)
	{
		--temp;
		Bit_Rate_.push_back(Draw_New_Bit_Rate());
	}
}


int User::Get_User_ID()
{
	return User_ID_;
}
