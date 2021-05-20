#ifndef Symulacja_Cyfrowa_Symulacja_Cyfrowa_Stats_H_
#define Symulacja_Cyfrowa_Symulacja_Cyfrowa_Stats_H_

#pragma once
#include <vector>

#include "User.h"
#include "spdlog/spdlog.h"


class Stats
{
public:

	/// GETTERS ///
	int Get_AVG_Throughput() { return AVG_Throughput_; }
	int Get_AVG_BTS_Throughput() { return AVG_BTS_Throughput_; }
	int Get_AVG_Wait_Time(){ return AVG_Wait_Time_; }
	std::vector<int>Get_AVG_Users_Throughput(){ return AVG_Users_Throughput_; }
	
	void Update_User_Bitrate(int Bit_Rate,User* User);
	//void Update_Bts_Throughputs_Sum();
	void Update_Users_Throughputs_Sum(User* User);
	void Update_Throughputs_Sum(User* User, int Bit_Rate);
	void Update_Wait_Times_Sum(int Time_Elapsed, User* User, bool Arive);

	void Calculate_AVG_BTS_Throughput();
	void Calculate_AVG_Throughput(int Time_Elapsed);
	void Calculate_AVG_Wait_Time(int Time_Elapsed);
	void Calculate_Users_AVG_Throughput();

	
	void Reserve_Place_For_User_Bitrate();
private:

	double AVG_Throughput_; // �redni� przep�ywno�� systemu mierzon� liczb� danych przes�anych poprawnie przez stacj� bazow� w jednostce czasu
	int AVG_BTS_Throughput_; // �redni� przep�ywno�� u�ytkownika mierzon� liczb� danych odebranych poprawnie od stacji bazowej w jednostce czasu, u�rednion� po wszystkich u�ytkownikach sieci; ta warto�� uwzgl�dnia okresy kiedy u�ytkownik nie mia� przydzielonego �adnego bloku zasob�w
	std::vector<int> AVG_Users_Throughput_; // Tablica �rednich przep�ywno�ci dla wszystkich u�ytkownik�w sieci.
	std::vector<int> User_Transmission_Count;
	double AVG_Wait_Time_; // �redni czas oczekiwania, tzn. czas mi�dzy pojawieniem si� u�ytkownika w sieci, a zako�czeniem odbierania danych
	bool First_Apear_Flag = false;
	std::vector<int> Users_Throughput_Sum;
	bool Start_Gathering_Stats_ = false;
	int Transmissions_Count = 0;
	int Throughputs_Sum_ = 0;
	int Bts_Throughputs_Sum_ = 0;
	int Users_Throughputs_Sum_ = 0;
	int First_User_That_Apeared_After_Early_Phase_Id = 0;
	std::vector<int> Wait_Times_Tab;

	//std::vector<>
	
};

#endif