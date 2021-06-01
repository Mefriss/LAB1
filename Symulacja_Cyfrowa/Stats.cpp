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

void Stats::Update_Sytem_Throughput(int bit_rate)
{
	System_Throughput_.push_back(bit_rate);
}

void Stats::Calculate_AVG_BTS_Throughput()
{
	int sum = 0;
	int size = System_Throughput_.size();
	for (int i = 0; i < System_Throughput_.size(); i++)
	{
		sum += System_Throughput_.back();
		System_Throughput_.pop_back();
	}
	AVG_System_Throughput_.push_back(sum / size);
}

void Stats::Calculate_AVG_Throughput(int Time_Elapsed)
{
	double time = Time_Elapsed;
	AVG_Throughput_ = Throughputs_Sum_ / static_cast<double>(Transmissions_Count);
	spdlog::info("Average Throughput : {} kbp/s", AVG_Throughput_);


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
	spdlog::info("Average wait time : {} ms",AVG_Wait_Time_);
}

void Stats::Calculate_Users_AVG_Throughput()
{
	for(int i = First_User_That_Apeared_After_Early_Phase_Id; i < AVG_Users_Throughput_.size(); i++)
	{
		if(User_Transmission_Count[i]!= 0)
		{
			AVG_Users_Throughput_[i] /= User_Transmission_Count[i];
			spdlog::debug("User with Id: {} Had average Throughput of: {} kbps/s", i + First_User_That_Apeared_After_Early_Phase_Id, AVG_Users_Throughput_[i]);

		}
	}
	std::ofstream output_file("./example.txt");
	std::ostream_iterator<int> output_iterator(output_file, "\n");
	std::copy(AVG_System_Throughput_.begin(), AVG_System_Throughput_.end(), output_iterator);
}

void Stats::Save_To_File()
{
	std::ofstream output_file("./throughputs.txt");
	std::ostream_iterator<int> output_iterator(output_file, "\n");
	std::copy(AVG_Users_Throughput_.begin(), AVG_Users_Throughput_.end(), output_iterator);
	//spdlog::debug("Average Throughput : {} kbp/s", AVG_Throughput_);
}

void Stats::Inc_Err_Count()
{
	Error_Count_++;
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
