#include "Random.h"
#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <utility>
#include "Patient.h"
#include "Care_Giver.h"
#include "Nurse.h"
#include "Doctor.h"

extern Random my_random; // Enables us to access the global variable declared in Simulator.h

class Patient_Queue
{
private:
	int*ref_count;
	double arrival_rate;
	int total_wait;
	int num_served;
	std::priority_queue<Patient *> the_queue_top;
	std::priority_queue<Patient *> the_queue_low;
	std::vector<Care_Giver *> caregivers;//vector to hold all Doctor and Nurse types that attend to patients
	std::vector<std::string> citizens;//something to hold the citizens
	std::map<std::string, std::vector<Record*>> patientRecord;//a map for the records of hospital visits
	/**swaps the contents of two Patient_Queues*/
	void swap(Patient_Queue &a, Patient_Queue &b)
	{
		std::swap(a.arrival_rate, b.arrival_rate);
		std::swap(a.total_wait, b.total_wait);
		std::swap(a.ref_count, b.ref_count);
		std::swap(a.num_served, b.num_served);
		std::swap(a.the_queue_top, b.the_queue_top);
		std::swap(a.the_queue_low, b.the_queue_low);
		std::swap(a.caregivers, b.caregivers);
		std::swap(a.citizens, b.citizens);
		std::swap(a.patientRecord, b.patientRecord);
	}

public:
	/**Constructor of the Patient Queue Class*/
	Patient_Queue(std::vector<std::string> possible) : citizens(possible), num_served(0), ref_count(0) {}

	/**Destructor of for Patient_Queue */
	virtual ~Patient_Queue()
	{
		--*ref_count;
		if (*ref_count == 0)
		{
			delete ref_count;
		}
	}

	/** Copy constructor*/
	Patient_Queue(const Patient_Queue &copy)
	{
		this->arrival_rate=copy.arrival_rate;
		this->total_wait=copy.total_wait;
		this->ref_count=copy.ref_count;
		this->num_served=copy.num_served;
		this->the_queue_top = copy.the_queue_top;
		this->the_queue_low=copy.the_queue_low;
		this->caregivers=copy.caregivers;
		this->citizens=copy.citizens;
		this->patientRecord=copy.patientRecord;
		++*ref_count;
	}

	/**Assignment Opperator*/
	Patient_Queue &operator=(Patient_Queue copy)
	{
		swap(*this, copy);
		return *this;
	}

	/**Updates the Records related to the given Patient in the map of patients*/
	void update_record(Patient* patient)
	{
		std::map<std::string, std::vector<Record*>>::iterator itr = patientRecord.find(patient->name);
		std::vector<Record*> vec;
		Record* rec = new Record(patient->care_by, patient->priority_number, patient->wait_time, patient->care_time, (patient->care_time + patient->wait_time));
		if (itr==patientRecord.end())//if the patient has not been seen before
		{
			vec.push_back(rec);
			patientRecord.insert(make_pair(patient->name, vec));
		}
		else
		{
			vec = itr->second;
			vec.push_back(rec);
			itr->second = vec;
		}
	}
	/**returns the map of patients*/
	std::map<std::string, std::vector<Record*>> getMap()
	{
		return patientRecord;
	}
	/**returns the number of people in both queues*/
	int num_in_queue()
	{
		return the_queue_top.size() + the_queue_low.size();
	}
	/**sets the arrival rate*/
	void set_arrival_rate(double arrival_rate)
	{
		this->arrival_rate = arrival_rate;
	}
	/**sets the vector of caregivers*/
	void set_caregivers(std::vector<Care_Giver*> care)
	{
		caregivers = care;
	}
	/**reutrns the total wait*/
	int get_total_wait()
	{
		return total_wait;
	}
	/**returns the number served*/
	int get_num_served()
	{
		return num_served;
	}
	/**returns the average wait*/
	double get_average_wait()
	{
		if (num_served > 0)
			return total_wait / num_served;
		else
			return total_wait;
	}
	/**chooses a patient using random to be the next patient added to the queue*/
	int choose_patient()
	{
		return my_random.next_int(citizens.size() - 1);
	}
	/**begins the appointment by setting the various parts of the caregiver to be that of the patient and notes who is caring for the patient*/
	void start_appt(std::string who, int care, int queue, int clock)
	{
		Patient* p;
		if (queue == 1)
		{
			p = the_queue_low.top();
			the_queue_low.pop();
		}
		else//queue is 2
		{
			p = the_queue_top.top();
			the_queue_top.pop();
		}
		caregivers[care]->set_start_time(clock);
		caregivers[care]->choose_care_length();
		caregivers[care]->set_patient(p);
		int wait = clock - p->arrival_time;
		p->wait_time = wait;
		total_wait += wait;
		p->care_by = who;//the care_by attribute of the patient
	}
	/**updates the hospital for the new minute*/
	void update(int clock)
	{
		if (my_random.next_double() < arrival_rate)//checks for probability that new patient was added
		{
			int newP = choose_patient();
			Patient* patient = new Patient(citizens[newP], clock);
			patient->generate_priority();
			if ((patient->priority_number) <= 10)//priority 1-10
				the_queue_low.push(patient);
			else//they are in priority 11-20
			{
				the_queue_top.push(patient);
			}
		}

		for (int i = 0; i < caregivers.size(); i++)//go through the vector of caregivers so that each is looked at
		{
			if (caregivers[i]->is_availible(clock))//if the caregiver is availible for appts
			{
				if (caregivers[i]->timeDone()==clock)//it is the first time after an appt has ended
				{
					update_record(caregivers[i]->doPaperWork());
					num_served++;
				}
				if (typeid(Nurse) == typeid(*caregivers[i]))//if the care giver is a nurse and is availible
				{
					if (!the_queue_low.empty())//if the low priority queue is not empty nurse i is assigned to the patient at the front of the queue
						start_appt("Nurse", i, 1, clock);//who=nurse, using caregiver at i and the_queue_low with current time
				}
				else if (typeid(Doctor) == typeid(*caregivers[i]))//if the caregiver is a doctor who is availible
				{
					if (!the_queue_top.empty())//high_priority queue is not empty doctor i is assigned to the patient at the front of the queue
						start_appt("Doctor", i, 2, clock);//who=doctor, using caregiver at i and the_queue_top with current time
					else if (!the_queue_low.empty())//low_priority queue is not empty doctor i is assigned to the patient at the front of the queue
						start_appt("Doctor", i, 1, clock);//who=doctor, using caregiver at i and the_queue_low with current time
				}
			}
		}
	}
};