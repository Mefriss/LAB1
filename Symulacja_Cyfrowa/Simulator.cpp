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



void Simulator::M1_Operation(Network* network, bool Mode, bool Rng_Toggle, bool Toggle_Logs, int time)
{
	simulator_clock_ = 0;
	Remove_All_Users(network);
	std::cout << "Rozpoczêto symulacjê metotd¹ M1! \n";
	int Id = -1;
	network->Set_Chanel_Busy_Flag(false);
	network->Draw_User_Arival_Time(simulator_clock_);//losujemy czas przyjœcia pierwszego usera
	network->Set_Bit_Rate_Change_Time(network->Draw_Bit_Rate_Change_Time(1, Rng_Toggle));
	bool Draw_Forever = true;
	//network->Bts_INIT();

	while (simulator_clock_ < time)
	{
		bool No_Event = false;
		Step_In(Mode);
		std::cout << std::endl;
		std::cout << "Czas który up³yn¹³ od pocz¹tku symulacji: " << simulator_clock_ << std::endl;
		spdlog::info("Time Elapsed: {} \n",simulator_clock_);
		
		while (No_Event == false)
		{
			No_Event = true;
			if (static_cast<int>(network->Get_Bit_Rate_Change_Time()) == 0)
			{
				if(network->Get_User_list().size() == 0)
				{
					std::cout << std::endl;
					spdlog::debug("Bitrate Has not Been redrawn; No users waiting in queue! \n");
				}
				for (int i = 0; i < network->Get_User_list().size(); i++)
				{
					network->Get_User_list().front()->Update_Bit_Rate(Rng_Toggle);
					std::cout << std::endl;
					spdlog::debug("Bitrate Drawn for user with id: {} \n", network->Get_User_list().front()->Get_User_ID());
					network->Push_User_To_The_End_Of_The_Queue();

				}
				network->Set_Bit_Rate_Change_Time(network->Draw_Bit_Rate_Change_Time(1, Rng_Toggle));
				No_Event = false;
			}
			if (network->Get_Time_Until_New_User_Arives() == 0) /// czy w tej chwili czasowej pojawi siê u¿ytkownik?
			//if (network->Get_First_User_Arival_Time() == 0) /// czy w tej chwili czasowej pojawi siê u¿ytkownik?
			{
				//if(simulator_clock_ < 50 || Draw_Forever == true)
				//{
				++Id;

				//if (Toggle_Logs_)
				spdlog::debug("New user has been created \n \n");
				network->Set_Time_Until_New_User_Arives(network->Draw_User_Arival_Time(0)); // Uncomment for random time
				//network->Set_Time_Until_New_User_Arives(2);
				network->Generate_Packet_And_Add_New_User(Id, Rng_Toggle);
				std::cout << "Nowy u¿ytkownik! ID: " << network->Get_User_list().back()->Get_User_ID() << std::endl;
				spdlog::debug("Data to fetch: {} \n", network->Get_User_list().back()->Get_User_Data() );
				//network->Set_User_Data_To_Be_Fetched();
				No_Event = false;
				//}

			}

			if (!network->Get_User_list().empty() && network->Get_User_list().front()->Get_User_Data() == 0)// koniec transmisji
			{

				std::cout << "przydzielono wszystkie bloki u¿ytkownikowi o ID: " << network->Get_First_User_ID() << std::endl;
				//if (Toggle_Logs_)
				spdlog::debug("All Resource blocks has been assigned to user \n \n");
				network->Set_Chanel_Busy_Flag(false);
				//network->Free_Up_The_Resource_Blocks(network->Get_User_list().front());
				network->Remove_User();

				//spdlog::info("User removed from queue \n \n");
				No_Event = false;



			}
			//if(!network->Get_User_list().empty() && network->Get_Channel_Busy_Flag()== false)

			//start transmisji

			if (!network->Get_User_list().empty() && network->Get_Time_Until_Bts_Assigns_Block() == 0)
			{
				network->Free_Up_All_Of_The_Resource_Blocks();
				network->Set_Chanel_Busy_Flag(true);
				network->Set_Time_Until_Bts_Assigns_Block(1);

				for (int i = 0; i < network->Get_User_list().size(); i++)
				{
					network->Get_User_list().front()->Set_Amount_Of_Recived_Resource_Blocks(3);
					network->Push_User_To_The_End_Of_The_Queue();

				}
				for (int i = 0; i < network->Get_Resource_Block_Count_From_Bts(); i++)
				{
					if (network->Get_User_list().front()->Get_Assigneed_Blocks_Count() > 0)
					{
						
						network->Assign_User_To_Resource_Block(network->Get_User_list().front(), Rng_Toggle);
						//network->Get_User_list().front()->Get_Bit_Rate_Vector().pop_back();
						network->Get_User_list().front()->Update_Amount_Of_Recived_Resource_Blocks();
						spdlog::debug("Remaining number of Blocks: {} For User with ID: {}", network->Get_User_list().front()->Get_Assigneed_Blocks_Count(), network->Get_User_list().front()->Get_User_ID());
						network->Push_User_To_The_End_Of_The_Queue();
						
					}

					//network->Push_User_To_The_End_Of_The_Queue();
				}
				for (int i = 0; i < network->Get_User_list().size(); i++)
				{
					//spdlog::debug("Transmission Rate for user with ID: {} = {} kbps/s",network->Get_User_list().front()->Get_User_ID(), network->Send_Data_To_User(network->Get_User_list().front()));
					network->Send_Data_To_User(network->Get_User_list().front());
					spdlog::debug("Remaining Data for user with ID: {} = {} bytes",network->Get_User_list().front()->Get_User_ID() , network->Get_User_list().front()->Get_User_Data());
					
					//spdlog::debug("Resource block has been assigned to user \n \n");
					network->Push_User_To_The_End_Of_The_Queue();

				}

				No_Event = false;
				Step_In(Mode);

			}

			//if (network->Get_User_list().front()->Get_Data_To_Be_Fetched() == 0 && !network->Get_User_list().empty() && network->Get_Channel_Busy_Flag() == true) // czy u¿ytkownik zassa³ wszystkie dane?

		}

		network->Set_Time_Until_New_User_Arives(network->Get_Time_Until_New_User_Arives() - 1);
		network->Set_Time_Until_Bts_Assigns_Block(network->Get_Time_Until_Bts_Assigns_Block() - 1);
		if (network->Get_Time_Until_Bts_Assigns_Block() < 0)
		{
			network->Set_Time_Until_Bts_Assigns_Block(0);
		}
		network->Set_Bit_Rate_Change_Time(network->Get_Bit_Rate_Change_Time() - 1);
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

void Simulator::Step_In(int Mode)
{
	if (Mode)
	{
		char key;
		std::cout << "Naciœnij przycisk aby kontynuowaæ" << std::endl;
		key = getchar();
	}
}

void Simulator::Main()
{
	setlocale(LC_CTYPE, "Polish");
	std::cout << "Czy chcesz wyœwietlaæ logi? " << std::endl << "0 - Nie     1 - Tak" << std::endl << "Twój Wybór: ";
	std::cin >> Toggle_Logs_;
	if (Toggle_Logs_)
	spdlog::set_level(spdlog::level::debug);
	Network* network = new Network();
	//if(Toggle_Logs_)
	spdlog::debug( "Network Has been created \n");

	network->Create_New_Bts();
	//if (Toggle_Logs_)
	spdlog::debug("Base Station has been created \n");
	std::cout << "Czy chcesz w³¹czyæ losowoœæ?" << std::endl << "0 - Nie     1 - Tak" << std::endl << "Twój Wybór: ";
	std::cin >> Rng_Toggle;
	//network->Set_BTS_Data(Rng_Toggle);
	//if (Toggle_Logs_)

	spdlog::debug("Drawing Data \n");
	int Mode_Selection;
	bool Current_Mode;

	//spdlog::info("TEST");

	std::cout << "Proszê wybraæ tryb symulacji: " << std::endl << "0 - Tryb ci¹g³y     1 - Tryb Krokowy" << std::endl << "Twój Wybór: ";
	
	std::cin >> Mode_Selection;
	Current_Mode = Mode_Select(Mode_Selection);
	//Operation(network, Current_Mode, 200);
	M1_Operation(network, Current_Mode,Rng_Toggle,Toggle_Logs_,200);
	
	

}

