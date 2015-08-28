#ifndef SIMULATE_H_
#define SIMULATE_H_

#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>
#include <ios>
#include <fstream>//for file input
#include <map>//for maps
#include <utility>//for pairs for maps
#include "Random.h"
#include "Patient.h"
#include "Patient_Queue.h"

Random my_random;  // Global variable 

class Simulator
{
private:
	int clock;       // current time
	double arrival_rate;

	Patient_Queue* hospital; //holds "patient" types which use the first overloaded constructor to make a container full of all people who live in town
	std::vector<std::string> citizens;
	std::vector<Care_Giver*> docs;
	std::map < std::string, std::vector<Record*> > patientRecords;


	/**reads an integer and checks to make sure it is in a specified range*/
	int read_int(const std::string &prompt, int low, int high)
	{
		if (low >= high) // invalid range
			throw std::invalid_argument("invalid range specified");

		std::cin.exceptions(std::ios_base::failbit);
		int num = 0;
		while (true)
		{
			try
			{
				while (true)
				{
					std::cout << prompt;
					std::cin >> num;
					if (num >= low && num <= high)
					{ // within the specified range
						std::cout << std::endl;
						return num;
					}
				}
			}
			catch (std::ios_base::failure)
			{
				std::cout << "Bad numeric string -- try again\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			}
		}
	}

public:
	/**constructor for Simulator*/
	Simulator()
	{
		fill_citizens();
		hospital = new Patient_Queue(citizens);//passes in the parameter of the previous container of all residents
	}
	/**finds a patient in the map of patients*/
	void findPatient(std::string p)
	{
		std::map<std::string, std::vector<Record*>>::iterator itr = patientRecords.find(p);//checks for patient
		
		
		if (itr != patientRecords.end())//if the patient is in the map
		{
			std::vector < Record* > vec= itr->second;
			for (int i = 0; i < vec.size(); i++)
			{
				Record* patient = vec[i];
				std::cout << p << "--Treated By: " << patient->careGivenBy << ", Care Time: "<< patient->careTime << 
					", Priority: " << patient->priorityNum << std::endl;//print out results
			}
		}
		else
			std::cout << "Patient " << p << " not found." << std::endl;
	}
	/**lists all of the patients served this week*/
	std::string listPatients()
	{
		std::string nameList = "";
		std::map<std::string, std::vector<Record*>>::iterator itr;
		for (itr = patientRecords.begin(); itr != patientRecords.end(); itr++)//until we reach the last patient
		{
			std::string temp = itr->first;
			temp.append("\n");
			nameList.append(temp);
		}
		return nameList;
	}
	/**fills the vector of citizens from the file of people*/
	void fill_citizens()
	{

		std::ifstream fin;
		fin.open("residents_273ville.txt");
		if (!fin)//if it couldn't find the file
		{
			std::cout << "can't open file" << std::endl;
			return;
		}
		while (!fin.eof())//until we reach the end of the final
		{
			std::string name;
			getline(fin, name);
			citizens.push_back(name);
		}
		fin.close();
	}

	/**enter the data to start the program*/
	void enter_data()
	{
		std::cout << "Welcome to the CS273ville Hospital Simulator.\n\n";
		std::cout << "Our emergency room is small, but it has a big heart.\n";
		
		int rate = -1;
		rate = read_int("Please enter the patient arrival rate (patients/hour): ", 1, 60);
		arrival_rate = rate / 60.0;
		hospital->set_arrival_rate(arrival_rate);


		int num_doctors = read_int("Please enter the number of doctors on call: ", 0, INT_MAX);
		int num_nurses = read_int("Please enter the number of nurses on call: ", 0, INT_MAX);


		for (int i = 0; i < num_nurses; i++)
			docs.push_back(new Nurse); //adds the nurses on call to the vector of Care_givers
		for (int i = 0; i < num_doctors; i++)
			docs.push_back(new Doctor);//adds the doctors on call to the vector of Care_givers		
		hospital->set_caregivers(docs);
	}
	/**run the simulation*/
	void run_simulation()
	{
		// run the simulation
		for (clock = 0; clock < 10080; ++clock)
		{
			hospital->update(clock);
		}
		patientRecords = hospital->getMap();
	}

	/**show the statistics for the week in the hospital*/
	void show_stats()
	{
		std::cout << "Number of people served: " << hospital->get_num_served() << std::endl;
		std::cout << "Total wait time: " << hospital->get_total_wait() << std::endl;
		std::cout << "Average wait time: " << hospital->get_average_wait() << std::endl;
		std::cout << "Number of people still waiting: " << hospital->num_in_queue() << std::endl;

		std::cout << std::endl;
	}
};

#endif