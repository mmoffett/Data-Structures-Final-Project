#include <iostream>
struct Record
{
	std::string careGivenBy;
	int priorityNum;
	int waitTime;
	int careTime;
	int totalTime;
	Record(const std::string careGive, int priNum, int wait, int care, int total) :
		careGivenBy(careGive), priorityNum(priNum), waitTime(wait), careTime(care), totalTime(total) {}
};