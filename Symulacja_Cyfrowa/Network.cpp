#include "Network.h"

#include <spdlog/spdlog.h>

#include "BTS.h"
#include "Stats.h"
#include "RNG.h"
#include "fstream"

Network::Network()
{
	
	
	std::fstream Seeds;
	Seeds.open("seeds.txt");
	std::string seed;
	for (int i = 0; i < 100; ++i)
	{
		std::getline(Seeds, seed);
		Seeds_.push_back(stoi(seed));
		
	}
	Data_Generator_ = new RNG(Seeds_.back());
	Seeds_.pop_back();
	Zero_And_One_Generator_ = new RNG(Seeds_.back());
	Seeds_.pop_back();
	Bit_Rate_Time_Change_Generator_ = new RNG(Seeds_.back());
	Seeds_.pop_back();
	Bit_Rate_Generator_ = new RNG(Seeds_.back());
	Seeds_.pop_back();
	User_Arrival_Time_Generator_ = new RNG(Seeds_.back());
	Seeds_.pop_back();

}

void Network::Create_New_Bts()
{
	Bts_ = new BTS(15);// k = 15
	Bts_->init();
}

int Network::Draw_User_Arival_Time(int Time_Elapsed)
{

	//User_Arival_Time_ = Time_Elapsed + rand() % 10 + 1;
	User_Arival_Time_ = User_Arrival_Time_Generator_->RndExp(1.52);
	//User_Arival_Times_.push(User_Arival_Time_);
	return User_Arival_Time_;
}

void Network::Add_New_User(User* New_User)
{
	User_List_.push(New_User);
}

int Network::Get_First_User_ID()
{
	return User_List_.front()->Get_User_ID();
}

int Network::Get_Data_From_User(User* user)
{
	return  user ->Get_User_Data();
}



void Network::Set_BTS_Error(int User_Id)
{
	
	Bts_->Set_Transmission_Succes_Flag(User_Id);
}

void Network::Set_Time_Until_New_User_Arives(int Time_Until_New_User_Arives)
{
	Time_Until_New_User_Arives_ = Time_Until_New_User_Arives;
}

void Network::Set_Time_Until_Bts_Assigns_Block(int Time_Until_Bts_Assigns_Block)
{
	Time_Until_Bts_Assigns_Block_ = Time_Until_Bts_Assigns_Block;
}

void Network::Set_Bit_Rate_Change_Time(float Time_Until_New_Bit_Rate_Is_Being_Drawn)
{
	Time_Until_New_Bit_Rate_Is_Being_Drawn_ = Time_Until_New_Bit_Rate_Is_Being_Drawn;
}

void Network::Set_Chanel_Busy_Flag(bool Channel_Busy)
{
	Channel_Busy_ = Channel_Busy;
}

void Network::Set_User_Data_To_Be_Fetched()
{
	User_List_.front()->Set_Data_To_Be_Fetched();
}


void Network::Draw_New_Bit_Rate_For_The_First_User(User* user, bool rng)
{
	user->Draw_New_Bit_Rate(rng);
}

void Network::Map_Blocks_To_User()
{
	int Downloaded_Data = Bts_->Get_Resource_Block_Map().front();
	//User_List_.front()->Set_User_Data(Downloaded_Data);
}

void Network::Send_Bts_Block(User* user)
{
	Bts_->Send_Block_To_User(15,User_List_.front()->Get_Bit_Rate_Vector(),user);
}



//float Network::Draw_Bitrate_Change_Time(float Tau)
//{
//	///return rand()%0.1 
//}

void Network::Push_User_To_The_End_Of_The_Queue()
{
	User_List_.push(User_List_.front());
	User_List_.pop();
}

void Network::Free_Up_The_Resource_Blocks(User* user)
{
	for (int i = 0; i < Bts_->Get_Resource_Block_Count() ; i++)
	{
		if(Bts_->Get_Resource_Blocks_()[i].user != nullptr && Bts_->Get_Resource_Blocks_()[i].user->Get_User_ID() == user->Get_User_ID())
		{
			Bts_->Set_User_Pointer_To_Resource_Block(nullptr, i);
			Bts_->Set_Bit_Rate(0, i);
			Bts_->Set_Error_Flag(false, i);
		}
		
	}
}

void Network::Free_Up_All_Of_The_Resource_Blocks()
{
	for (int i = 0; i < Bts_->Get_Resource_Block_Count(); i++)
	{
		Bts_->Set_User_Pointer_To_Resource_Block(nullptr, i);
		Bts_->Set_Bit_Rate(0, i);
		Bts_->Set_Error_Flag(false, i);

	}
}

void Network::Assign_User_To_Resource_Block(User* User, bool rng,Stats* Stats)
{

	int Iterator = Bts_->Get_Resource_Block_Count() - 1;
	while(Bts_->Get_Resource_Blocks_()[Iterator].user != nullptr && Iterator >= 0)
	{
		--Iterator;
	}
	if (Iterator > 0)
		Bts_->Set_User_Pointer_To_Resource_Block(User, Iterator);
	if (rng)
		Bts_->Set_Error_Flag(Zero_And_One_Generator_->RndZeroOne(0.1), Iterator);
	else
		Bts_->Set_Error_Flag(false, Iterator);
	
	Bts_-> Set_Bit_Rate(User->Get_Bit_Rate_Vector().back(), Iterator);
	User->Pop_Bit_Rate_Vector();
	//User->Push_New_Bitrtate();
	Draw_Bitrates_Table_For_User(User);
	
	if (Bts_->Get_Resource_Blocks_()[Iterator].Error_Flag_ == true)
	{
		Bts_->Set_Bit_Rate(0, Iterator);
		if(User->Get_Early_Phase_Flag()==false)
		{
			Stats->Inc_Err_Count();
		}
	}
		
	
	
	
}

void Network::Bts_INIT()
{
	Bts_->init();
}

int Network::Send_Data_To_User(User* user)
{
	int Data_To_Send = 0;
	for (int i = 0; i < Get_Resource_Block_Count_From_Bts(); i++)
	{
		if(Bts_->Get_Resource_Blocks_()[i].user != nullptr && Bts_->Get_Resource_Blocks_()[i].user->Get_User_ID() == user->Get_User_ID())// sprawdzamy czy ten użytkownik odbiera dane
		{
			spdlog::debug("Block no. {} assigned to user with ID: {}", i, Bts_->Get_Resource_Blocks_()[i].user->Get_User_ID());
			Data_To_Send += Bts_->Get_Resource_Blocks_()[i].Bit_Rate_;
		}
		
	}
	
	std::cout << std::endl;
	Bit_Rate_Temp = Data_To_Send;
	spdlog::debug("Transmission Rate for user with ID: {} = {} kbps/s", user->Get_User_ID(), Data_To_Send);
	user->Subtract_User_Data(Data_To_Send);
	return Data_To_Send;
}

void Network::Draw_Bitrates_Table_For_User(User* user)
{
	user->Push_New_Bitrtate(static_cast<int>(Bit_Rate_Generator_->Rand(20, 800)));
}

std::queue<User*> Network::Get_User_list()
{
	return User_List_;
}

bool Network::Check_Bts_Blocks_Depleted()
{
	return Bts_->Get_Blocks_Depleted_Flag();
}

int Network::Calculate_Block_Assingment_Time(int Time_Elapsed,int Assingmnet_Time_Step)
{
	Block_Assignment_Time_ = Time_Elapsed + Assingmnet_Time_Step -1;
	return Block_Assignment_Time_;
}

void Network::Remove_User()
{
	std::cout << "Usunięto użytkownika nr: " << User_List_.front()->Get_User_ID() << std::endl;
	spdlog::debug("User has been removed from queue \n");
	User_List_.pop();
}


void Network::Generate_Packet_And_Add_New_User(bool Early_Phase_User,int Id,bool rng)
{
	
	User* New_User = new User(Early_Phase_User,Id, Bts_->Get_Resource_Block_Count(),rng,Bit_Rate_Generator_->Rand(20,800));
	//spdlog::debug("New user with id: {} \n", net)
	//New_User->Set_Data_To_Be_Fetched();
	for (int i = 0; i < 15; i++)
	{
		Draw_Bitrates_Table_For_User(New_User);
	}
	
	User_List_.push(New_User);
}

void Network::Pop_Arival_Time()
{
	//User_Arival_Times_.pop();
}
float Network::Draw_Bit_Rate_Change_Time(float Tau,bool rng)
{
	float time;
	//if(rng)
	//	time = rand() % 10 + 1;
	//else
	//	time = 5;
	//
	if (rng)
		time = static_cast<int>(Bit_Rate_Time_Change_Generator_->RndExp(Tau));
	else
		time = 1;
	
	return time;
}
