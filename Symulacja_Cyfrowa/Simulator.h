#ifndef Symulacja_Cyfrowa_Symulacja_Cyfrowa_Simulator_H_
#define Symulacja_Cyfrowa_Symulacja_Cyfrowa_Simulator_H_

#pragma once
#include "Network.h"
#include "BTS.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
class Simulator
{
public:

	bool Mode_Select(int Mode_Selection);
	void Main();
	void Operation(Network* network, bool Mode, int time = 200);
	void M1_Operation(Network* network, bool Mode,int Early_Phase_Time,bool Rng_Toggle, bool Toggle_Logs = true, int time=200);
	//void Continous_Mode(Network* network);
	bool Key_Down();
	void Display_Throughput();
	void Remove_All_Users(Network* network);
	void Step_In(int Mode);

private:

	
	int Simulation_Time_ = 0;
	bool Early_Phase = true;
	int Early_Phase_Time = 0;
	bool Rng_Toggle;
	size_t simulator_clock_ = 0;
	bool Toggle_Logs_;
};

#endif
