#include "Simulator.h"
#include <locale.h>
#include <iostream>
#include "spdlog/spdlog.h"
#include "Network.h"


bool Simulator::Mode_Select(int Mode_Selection)
{ 
	
	if(Mode_Selection == 0)
	{
		std::cout << "Wybrano Tryb Pracy Ci¹g³ej" << std::endl;
		spdlog::info("Continuous mode has been selected \n");
		return false;
	}
	if (Mode_Selection == 1)
	{
		std::cout << "Wybrano Tryb Pracy Krokowej" << std::endl;
		spdlog::info("Step mode has been selected \n");
		return true;
	}
	int Retry_Mode;
	std::cout << "Proszê o wybranie opcji 0 lub 1: " << std::endl;
	std::cin >> Retry_Mode;
	Mode_Select(Retry_Mode);
	
}
void Simulator::Operation(Network* network, bool Mode, int time)
{
	int Simulation_Time = time;
	simulator_clock_ = 0;
	std::cout << "Rozpoczêto symulacjê z³¹ metotd¹ \n";
	spdlog::info("Simulation Started \n");
	//int First_User_Arival_time = network->Draw_User_Arival_Time();
	int User_Arival_time = network->Draw_User_Arival_Time(0);
	int Block_Assignment_Time = network->Calculate_Block_Assingment_Time(simulator_clock_);
	spdlog::info("Arival time of the first user has been drawn \n");
	int ID = 0;
	spdlog::info("ID of the first user has been drawn \n");
	while(simulator_clock_ < Simulation_Time){

		bool no_event = false;
		
		if (Mode)
		{
			char key;
			std::cout << "Naciœnij przycisk aby kontynuowaæ" << std::endl;
			key = getchar();
		}
		
		std::cout << "Czas który up³yn¹³ od pocz¹tku symulacji: " << simulator_clock_ << std::endl;
		
		if (User_Arival_time == simulator_clock_)
		{
			if(!network->Get_User_list().empty())
				network->Remove_User();
			User* New_User = new User(ID);
			spdlog::info("New user has been created \n");
			std::cout << std::endl<< "Pojawienie siê u¿ytkownika " << New_User->Get_User_ID() << std::endl;
			network->Add_New_User(New_User);
			++ID;
			User_Arival_time = network->Draw_User_Arival_Time(simulator_clock_);
			
			//network->Remove_User();
		}
		
		if(Block_Assignment_Time == simulator_clock_ && network->Get_User_list().empty())//nie ma komu przydzieliæ zasobów wiêc "Przesuwamy" czas przydzielenia zasobów
		{
			Block_Assignment_Time = network->Calculate_Block_Assingment_Time(simulator_clock_);
		}
		
		if (Block_Assignment_Time == simulator_clock_ && !network->Get_User_list().empty())
		//if (!network->Get_User_list().empty())
		{
			
			
			if (!network->Check_Bts_Blocks_Depleted())
			{
				std::cout << "Przydzielono zasoby u¿ytkownikowi o ID: " <<network->Get_User_list().front()->Get_User_ID()<< std::endl;
				network->Grant_Blocks_To_User();
				network->Set_BTS_Error(ID);
				
			}
			Block_Assignment_Time = network->Calculate_Block_Assingment_Time(simulator_clock_);
		}
		++simulator_clock_;

	}
	Remove_All_Users(network);
}
///  Xddd???? ////
void Simulator::M1_Operation(Network* network, bool Mode,bool Toggle_Logs, int time)
{
	simulator_clock_ = 0;
	Remove_All_Users(network);
	std::cout << "Rozpoczêto symulacjê metotd¹ M1! \n";
	int Id = -1;
	network->Set_Chanel_Busy_Flag(false);
	network->Draw_User_Arival_Time(simulator_clock_);//losujemy czas przyjœcia pierwszego usera

	while (simulator_clock_ < time)
	{
		bool No_Event = false;
		if (Mode)
		{
			char key;
			std::cout << "Naciœnij przycisk aby kontynuowaæ" << std::endl;
			key = getchar();
		}
		std::cout << "Czas który up³yn¹³ od pocz¹tku symulacji: " << simulator_clock_ << std::endl;

		while (No_Event == false)
		{
			No_Event = true;
			if (network->Get_Time_Until_New_User_Arives() == 0) /// czy w tej chwili czasowej pojawi siê u¿ytkownik?
			{
				
				++Id;
				std::cout << "Nowy u¿ytkownik! " << std::endl;
				if (Toggle_Logs_)
				spdlog::info("New user has been created \n \n");
				network->Set_Time_Until_New_User_Arives(network->Draw_User_Arival_Time(0));
				network->Generate_Packet_And_Add_New_User(Id);
				//network->Set_User_Data_To_Be_Fetched();
				No_Event = false;
			}
			if (!network->Get_User_list().empty() && network->Get_User_list().front()->Get_Data_To_Be_Fetched() <= 0)// koniec transmisji
			{
				std::cout << "przydzielono wszystkie bloki u¿ytkownikowi" << std::endl;
				if (Toggle_Logs_)
				spdlog::info("All Resource blocks has been assigned to user \n \n");
				network->Set_Chanel_Busy_Flag(false);
				network->Remove_User();
				//spdlog::info("User removed from queue \n \n");
				No_Event = false;
				
			}
			//if(!network->Get_User_list().empty() && network->Get_Channel_Busy_Flag()== false)//start transmisji
			if (!network->Get_User_list().empty())
			{
				std::cout << "przydzielam bloki" << std::endl;
				if (Toggle_Logs_)
				spdlog::info("Resource block has been assigned to user \n \n");
				network->Set_Chanel_Busy_Flag(true);
				//network->Grant_Blocks_To_User();
				network->Send_Bts_Block(network->Get_User_list().front());
				network->Map_Blocks_To_User();
				network->Set_Time_Until_Bts_Assigns_Block(1);
				No_Event = false;
				std::cout << "Czas który up³yn¹³ od pocz¹tku symulacji: " << simulator_clock_ << std::endl;
				simulator_clock_++;
			}
			//if (network->Get_User_list().front()->Get_Data_To_Be_Fetched() == 0 && !network->Get_User_list().empty() && network->Get_Channel_Busy_Flag() == true) // czy u¿ytkownik zassa³ wszystkie dane?

		}

		network->Set_Time_Until_New_User_Arives(network->Get_Time_Until_New_User_Arives()-1);
		network->Set_Time_Until_Bts_Assigns_Block(network->Get_Time_Until_Bts_Assigns_Block() - 1);
		//network->Draw_User_Arival_Time(simulator_clock_);
		//network->Calculate_Block_Assingment_Time(simulator_clock_);
		//std::cout << network->Get_Block_Assingment_Time()<<std::endl;
		++simulator_clock_;
	}
	
}

void Simulator::Remove_All_Users(Network* network)
{
	while (!network->Get_User_list().empty())
	{
		network->Remove_User();
		
	}

}

void Simulator::Main()
{
	setlocale(LC_CTYPE, "Polish");
	std::cout << "Czy chcesz wyœwietlaæ logi? " << std::endl << "0 - Nie     1 - Tak" << std::endl << "Twój Wybór: ";
	std::cin >> Toggle_Logs_;
	
	Network* network = new Network();
	if(Toggle_Logs_)
	spdlog::info( "Network Has been created \n");

	network->Create_New_Bts();
	if (Toggle_Logs_)
	spdlog::info("Base Station has been created \n");
	network->Set_BTS_Data();
	if (Toggle_Logs_)
	spdlog::info("Drawing Data \n");
	int Mode_Selection;
	bool Current_Mode;

	//spdlog::info("TEST");

	std::cout << "Proszê wybraæ tryb symulacji: " << std::endl << "0 - Tryb ci¹g³y     1 - Tryb Krokowy" << std::endl << "Twój Wybór: ";
	
	std::cin >> Mode_Selection;
	Current_Mode = Mode_Select(Mode_Selection);
	//Operation(network, Current_Mode, 200);
	M1_Operation(network, Current_Mode,Toggle_Logs_,200);
	
	

}

