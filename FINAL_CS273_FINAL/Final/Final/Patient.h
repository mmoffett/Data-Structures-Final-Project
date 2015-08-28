#ifndef PATIENT_H_
#define PATIENT_H_


#include <iostream>
#include "Record.h"
#include "Random.h"

extern Random my_random;
/*
We want to be able to keep track of information about our patients,
including their arrival time, priority number, and number of visits.
The wait_time int will be calculated based on the difference between
their arrival time and the time on the clock when they leave.
*/

class Patient
{
private:
	int *ref_count;
public:
	/**A constructor for Patient*/
	Patient(std::string name) :
		name(name), arrival_time(-1), priority_number(-1), wait_time(-1), ref_count(0){}
	/**Another constructor for Patient*/
	Patient(std::string name, int clock) :
		name(name), arrival_time(clock), priority_number(-1), wait_time(-1), ref_count(0){}
	int arrival_time;
	int priority_number;
	int wait_time;
	int care_time;
	std::string care_by;
	std::string name;
	/**sets arrival time*/
	void set_arrival_time(int clock)
	{
		arrival_time = clock;
	}
	/**Generates a priority for the patient*/
	int generate_priority()
	{
		double num = my_random.next_double();
		if (num < 0.7)//for priority of lower values
		{
			priority_number = my_random.next_int(9) + 1;
		}
		else if (num >= 0.7 && num < 0.9)//middle priority
		{
			priority_number = my_random.next_int(5) + 11;
		}
		else//num greater or equal to .09 and under 1->for upper priority
		{
			priority_number = my_random.next_int(5) + 16;
		}

		return priority_number;
	}
	/**assignement override for <*/
	bool operator< (const Patient &p2) const
	{
		return (priority_number < p2.priority_number);
	}
	/**Destructor for Patients*/
	virtual ~Patient()
	{
		--*ref_count;
		if (*ref_count == 0)
		{
			delete ref_count;
		}
	}
	/** Copy constructor*/
	Patient(const Patient &copy)
	{
		this->arrival_time=copy.arrival_time;
		this->wait_time = copy.wait_time;
		this->ref_count=copy.ref_count;
		this->priority_number=copy.priority_number;
		this->care_time=copy.care_time;
	    this->name=copy.name;
		this->care_by=copy.care_by;
		++*ref_count;
	}
	/**Assignment Operator*/
	Patient &operator=(Patient copy)
	{
		swap(*this, copy);
		return *this;
	}

private:
	/**Swaps the contents of two patients*/
	void swap(Patient &a, Patient &b)
	{
		std::swap(a.arrival_time, b.arrival_time);
		std::swap(a.wait_time, b.wait_time);
		std::swap(a.ref_count, b.ref_count);
		std::swap(a.priority_number, b.priority_number);
		std::swap(a.care_time, b.care_time);
		std::swap(a.name, b.name);
		std::swap(a.care_by, b.care_by);
	}
};

#endif