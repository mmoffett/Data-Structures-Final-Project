#ifndef NURSE_H_
#define NURSE_H_


#include <iostream>
#include "Care_Giver.h"


class Nurse : public Care_Giver
{
public:
	/**Constructor for Nurse*/
	Nurse() {}
	/**chooses the care length*/
	void virtual choose_care_length()
	{
		care_length = my_random.next_int(9) + 1;
	}
	/**Assignment Operator*/
	Nurse &operator=(Nurse copy)
	{
		swap(*this, copy);
		return *this;
	}
};

#endif