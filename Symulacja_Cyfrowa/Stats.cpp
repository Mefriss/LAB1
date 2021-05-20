#include "Stats.h"
#include <fstream>
#include <iterator>

void Stats::Update_Throughputs_Sum(User* User,int Bit_Rate)
{
	if(User->Get_Early_Phase_Flag() == false)
	{
		Throughputs_Sum_ += Bit_Rate;
		++Transmissions_Count;
	}

}

void Stats::Update_Wait_Times_Sum(int Time_Elapsed, User* User, bool Arive)
{

		if (Arive)
		{
			Wait_Times_Tab.push_back(Time_Elapsed);
			if(User->Get_Early_Phase_Flag() == false)
			spdlog::debug("User ID: {} Arival Time = {} ", User->Get_User_ID(), Time_Elapsed);
		}

		if (Arive == false && User->Get_Early_Phase_Flag() == false)
		{
			if (!Wait_Times_Tab.empty())
			{
				Wait_Times_Tab[User->Get_User_ID()] = Time_Elapsed - Wait_Times_Tab[User->Get_User_ID()];
				spdlog::debug("User ID: {} Wait Time = {} ", User->Get_User_ID(), Wait_Times_Tab[User->Get_User_ID()]);
			}

		
		
	}

		
}

void Stats::Calculate_AVG_Throughput(int Time_Elapsed)
{
	double time = Time_Elapsed;
	AVG_Throughput_ = Throughputs_Sum_ / static_cast<double>(Transmissions_Count);
	spdlog::debug("Average Throughput : {} kbp/s", AVG_Throughput_);
}


void Stats::Calculate_AVG_Wait_Time(int Time_Elapsed)
{
	double Sum = 0;
	int User_Count = Wait_Times_Tab.size() - First_User_That_Apeared_After_Early_Phase_Id;
	for(int i = First_User_That_Apeared_After_Early_Phase_Id; i< Wait_Times_Tab.size(); i++)
	{
		Sum += Wait_Times_Tab[i];
	}
	//spdlog::debug("Sum : {}", Sum);
	spdlog::debug("User_Count : {}", User_Count );
	AVG_Wait_Time_ = Sum / User_Count;
	spdlog::debug("Average wait time : {} ms",AVG_Wait_Time_);
}

void Stats::Calculate_Users_AVG_Throughput()
{
	for(int i = First_User_That_Apeared_After_Early_Phase_Id; i < AVG_Users_Throughput_.size(); i++)
	{
		AVG_Users_Throughput_[i] /= User_Transmission_Count[i];
		spdlog::debug("User with Id: {} Had average Throughput of: {} kbps/s", i+First_User_That_Apeared_After_Early_Phase_Id, AVG_Users_Throughput_[i]);
	}
	//std::ofstream output_file("./example.txt");
	//std::ostream_iterator<double> output_iterator(output_file, "\n");
	//std::copy(First_User_That_Apeared_After_Early_Phase_Id, AVG_Users_Throughput_.size(), output_iterator);
}

void Stats::Update_User_Bitrate(int Bit_Rate,User* User)
{
	
	if (User->Get_Early_Phase_Flag() == false)
	{
		if( First_Apear_Flag ==false)
		{
			First_User_That_Apeared_After_Early_Phase_Id = User->Get_User_ID();
			First_Apear_Flag = true;
		}
		
		
			AVG_Users_Throughput_[User->Get_User_ID()] += Bit_Rate;
			User_Transmission_Count[User->Get_User_ID()]++;

	}
	

}

void Stats::Reserve_Place_For_User_Bitrate()
{

		AVG_Users_Throughput_.push_back(0);
		User_Transmission_Count.push_back(0);

}
