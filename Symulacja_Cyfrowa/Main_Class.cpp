#include "RNG.h"

#include "Simulator.h"

int main()
{
	std::cout << "How many runs to perform: ";
	int run_count;
	std::cin >> run_count;
	RNG* Rng_ = new RNG(1);
	

		for (int i = 0; i < run_count; i++)
		{
			Rng_->Generate_Seeds(i+rand()%100+1);
			Simulator* simulator = new Simulator();
			simulator->Main();
		}

	return 0;
}
