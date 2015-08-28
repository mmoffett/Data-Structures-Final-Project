#ifndef CARE_GIVER_H_
#define CARE_GIVER_H_


#include <iostream>
#include "Random.h"
#include "Patient.h"
extern Random my_random; // Enables us to access the global variable declared in Simulator.h


class Care_Giver
{
public:
	/**Constructor for care_Giver*/
	Care_Giver()
	{
		start_time = -1;
		ref_count = 0;
	}
	int care_length;
	int start_time;
	/**a virtual method that will be set in child classes to choose care length*/
	void virtual choose_care_length() = 0;
	/**set the start time*/
	void set_start_time(int clock)
	{
		start_time = clock;
	}
	/**checks if the care_giver is availible or has a current patient*/
	bool is_availible(int clock)
	{
		return (clock - start_time >= care_length);
	}
	/**looks to see what time the appt will be done*/
	int timeDone()
	{
		return start_time + care_length;
	}
	/**sets the Patient that the caregiver is currently serving*/
	void set_patient(Patient* p)
	{
		myPatient = p;
	}
	/**finishes the appt by setting the appropriate attributes to reflect*/
	Patient* doPaperWork()
	{
		myPatient->care_time = care_length;
		return myPatient;
	}
	/**destructor for Care_Giver*/
	virtual ~Care_Giver()
	{
		--*ref_count;
		if (*ref_count == 0)
		{
			delete[] myPatient;
			delete ref_count;
		}
	}
	/**Copy constructor*/
	Care_Giver(const Care_Giver &copy)
	{
		this->myPatient=copy.myPatient;
		this->care_length = copy.care_length;
		this->start_time = copy.start_time;
		this->ref_count = copy.ref_count;
		++*ref_count;
	}
private:
	Patient* myPatient;
	int *ref_count;
	/**swaps the contents of two Care_Givers*/
	void swap(Care_Giver &a, Care_Giver &b)
	{
		std::swap(a.myPatient, b.myPatient);
		std::swap(a.care_length, b.care_length);
		std::swap(a.ref_count, b.ref_count);
		std::swap(a.start_time, b.start_time);
	}
	friend class Doctor;
	friend class Nurse;
};

#endif