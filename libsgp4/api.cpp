
#include "api.h"
#include "Tle.h"
#include <string>
#include <sstream>
#include "SGP4.h"
//#include "Vector.h"

void* create_Tle(char* line_one, char* line_two, int size)
{
	// Format lines to strings
	std::string line_one_local;
	std::string line_two_local;

	// 
	for (int i = 0; i <= size-1; i++)
	{
		line_one_local += *(line_one + i);
		line_two_local += *(line_two + i);
		//printf("%s", line_one_local.at(i));
	}

	// Return variable
	return reinterpret_cast<void*>(new Tle(line_one_local, line_two_local));

}

void test_Tle(Tle_C* tle_in)
{
	// Define stringstream to hold data from the ToString method.
	std::string tle_string;

	tle_string = reinterpret_cast<Tle*>(tle_in)->ToString();

	printf("TLE Data log:\n");
	printf("--------------\n");

	for (int i = 0; i < tle_string.size(); i++)
	{
		printf("%c", tle_string.at(i));
	}

	printf("--------------\n");
}

void destroy_Tle(Tle_C* tle_in)
{
	delete reinterpret_cast<Tle*>(tle_in);
}

void* create_SGP4(Tle_C* tle_in)
{
	// Get data from pointer
	Tle tle_actual = *(reinterpret_cast<Tle*>(tle_in));

	// Create SGP4 object and return a pointer to it
	return reinterpret_cast<void*>(new SGP4(tle_actual));

}

// Function to convert from ECI_C pointer to ECI pointer
Eci* ptr_Eci_C_to_Eci(Eci_C* thisPos)
{
	return reinterpret_cast<Eci*>(thisPos);
}

Eci_C* ptr_Eci_to_Eci_C(Eci* thisPos)
{
	return reinterpret_cast<Eci_C*>(thisPos);
}

void FindPosition_wrap(SGP4_C* thisSGP, double timeSince, FILE* ptr_to_file)
{

	// Get data from input pointer
	SGP4 sgp_actual = *(reinterpret_cast<SGP4*>(thisSGP));

	// Now call function to find position for the time given by timeSince
	// Note: this works because i call the fuction FindPosition(), then
	// get the address of the result and give it to a pointer - position_new.
	Eci position_new_in_eci = (sgp_actual.FindPosition(timeSince));

	// Get strings for date [UTC], position and velocity
	Vector sat_position = position_new_in_eci.Position();
	Vector sat_velocity = position_new_in_eci.Velocity();
	DateTime date_time = position_new_in_eci.GetDateTime();

	std::string line = date_time.ToString() + " " + sat_position.ToString() + " " + sat_velocity.ToString() ;
	printf("%s\n", line.c_str());

	// Write strings to file
	fprintf(ptr_to_file, "%s\n", line.c_str());
}
