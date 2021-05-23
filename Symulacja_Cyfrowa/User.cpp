#include "User.h"
#include "spdlog/spdlog.h"
#include "RNG.h"


User::User(bool Early_Phase_User,int User_ID, int Resource_Block_Count,bool rng)
{
	//Bit_Rate_.reserve(1);
	//for (int i = 0; i < 15; i++)	
	//	Bit_Rate_.push_back(Draw_New_Bit_Rate(rng)); //Przep³ywnoœæ - r,k – zmienna losowa o rozk³adzie jednostajnym w przedziale <20, 800> kbit/s
	//Rng_ = new RNG(1);1
	
	Early_Phase_User_ = Early_Phase_User;
	User_ID_ = User_ID;
	User_Data_ = Draw_Data_To_Be_Fetched();
	Assigned_Blocks_ = 3;
	
}

User::~User()
{
	std::cout << "Usuniêto u¿ytkownika nr: " << User_ID_<< std::endl;
}



int User::Draw_Data_To_Be_Fetched()
{
	RNG* Rng_ = new RNG(44);
	return (static_cast<int>( Rng_->Rand(250, 2500)));
}
int User::Draw_New_Bit_Rate(bool rng)
{
	RNG* Rng_ = new RNG(44);
	
	
	if(rng)
	return static_cast<int>(Rng_->Rand(20, 800));
	else
	{
		return 1000;
	}
}





//void User::Draw_New_Bit_Rate()
//{
//	Bit_Rate_.pop_back();
//	Bit_Rate_.push_back(rand() % 800 + 21);
//	
//}

void User::Subtract_User_Data(int Data_Fetched)
{
	
	if (User_Data_ >= Data_Fetched)
		User_Data_ -= Data_Fetched;
	else
		User_Data_ = 0;
}

void User::Update_Amount_Of_Recived_Resource_Blocks()
{
	Assigned_Blocks_ -= 1;
}

void User::Set_Amount_Of_Recived_Resource_Blocks(int blocks)
{
	Assigned_Blocks_ = blocks;
}

void User::Set_Data_To_Be_Fetched()
{
	User_Data_ = Draw_Data_To_Be_Fetched();
}

void User::Push_New_Bitrtate(int BitRate)
{
	Bit_Rate_.push_back(BitRate);
}

void User::Update_Bit_Rate(bool rng)
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
		Bit_Rate_.push_back(Draw_New_Bit_Rate(rng));
	}
}


void User::Pop_Bit_Rate_Vector()
{
	Bit_Rate_.pop_back();
}

int User::Get_User_ID()
{
	return User_ID_;
}
