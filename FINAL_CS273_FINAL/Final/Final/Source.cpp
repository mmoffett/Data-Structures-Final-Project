/**
@author Marissa Moffett and Hannah Cobb
*/

#include "Simulator.h"

int main()
{
	std::vector<std::string> citizens;
	Simulator hospital; // create the simulator
	hospital.enter_data();  // enter data for the simulator
	hospital.run_simulation(); // run the simulation
	hospital.show_stats(); // report the run statistics

	std::string f = "";
	while (f != "3")
	{
		std::cout << "Choose option 1 or 2 or 3: \n1. list all patients treated\n2. find a patient's record\n3. end program" << std::endl;
		std::cin >> f;
		if (f == "1")//if want to look at  all patients
		{
			std::string list = hospital.listPatients();
			std::cout << list;
		}
		else if (f == "2")//if want to look at specific patient
		{
			std::cout << "Enter the name to search: " << std::endl;

			std::string name;
			std::cin >> name;

			hospital.findPatient(name);
		}
	}
}