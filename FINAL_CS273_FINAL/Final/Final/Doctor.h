#ifndef DOCTOR_H_
#define DOCTOR_H_


#include <iostream>
#include "Care_Giver.h"

class Doctor : public Care_Giver
{
public:
	/**Constructor for Doctor*/
	Doctor() {}
	/**chooses the care length*/
	void virtual choose_care_length()
	{
		care_length = my_random.next_int(19) + 1;
	}
	/**Assignment operator*/
	Doctor &operator=(Doctor copy)
	{
		swap(*this, copy);
		return *this;
	}
};

#endif