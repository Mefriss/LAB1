#ifndef Symulacja_Cyfrowa_Symulacja_Cyfrowa_Network_H_
#define Symulacja_Cyfrowa_Symulacja_Cyfrowa_Network_H_

#pragma once
#include <vector>
#include <queue>
#include "User.h"
#include "BTS.h"
#include <random>

class Network
{
public:

	void Create_New_Bts();
	int Draw_User_Arival_Time();
	int Draw_User_Arival_Time(int Time_Elapsed);
	void Add_New_User(User* New_User);

	bool Check_Bts_Blocks_Depleted();
	int Calculate_Block_Assingment_Time(int Time_Elapsed, int Assingmnet_Time_Step = 1);
	void Remove_User();
	void Grant_Blocks_To_User();
	void Generate_Packet_And_Add_New_User(int Id);
	void Pop_Arival_Time();
	std::vector<int> Map_Bts_Blocks(int Blocs_Per_User = 1);
	void Draw_New_Bit_Rate_For_The_First_User(User* user);
	void Map_Blocks_To_User();
	void Send_Bts_Block(User* user);

	float Draw_Bit_Rate_Change_Time(float Tau);

	void Push_User_To_The_End_Of_The_Queue();
	
	/// GETTERS ///
	
	std::queue<User*> Get_User_list();
	int Get_User_Arival_Time() { return User_Arival_Time_; }
	int Get_First_User_Arival_Time() { return User_Arival_Times_.front(); }
	int Get_Block_Assingment_Time() { return Block_Assignment_Time_; }
	int Get_Time_Until_Bts_Assigns_Block() { return Time_Until_Bts_Assigns_Block_; }
	int Get_Time_Until_New_User_Arives() { return Time_Until_New_User_Arives_; }
	bool Get_Channel_Busy_Flag() { return Channel_Busy_; }
	int Get_First_User_ID();
	int Get_Data_From_User(User* user);
	float Get_Bit_Rate_Change_Time() { return Time_Until_New_Bit_Rate_Is_Being_Drawn_; }
	int Get_Resource_Block_Count_From_Bts() { return Bts_->Get_Resource_Block_Count(); }
	
	/// SETTERS ///
	
	void Set_BTS_Data();
	void Set_BTS_Error(int User_Id);
	void Set_Time_Until_New_User_Arives(int Time_Until_New_User_Arives);
	void Set_Time_Until_Bts_Assigns_Block(int Time_Until_Bts_Assigns_Block);
	void Set_Bit_Rate_Change_Time(float Time_Until_New_Bit_Rate_Is_Being_Drawn);
	void Set_Chanel_Busy_Flag(bool Channel_Busy);
	void Set_User_Data_To_Be_Fetched();
	

private:
	std::queue<User*> User_List_;
	std::queue<int> User_Arival_Times_;
	//std::queue<int> User_Arival_Times_;
	BTS* Bts_;
	//int User_Creation_Time
	bool Channel_Busy_;
	float Time_Until_New_Bit_Rate_Is_Being_Drawn_;
	int User_Arival_Time_;
	int Time_Until_New_User_Arives_;
	int Block_Assignment_Time_;
	int Time_Until_Bts_Assigns_Block_;
	int Block_Assignment_Timer_;

};



#endif
