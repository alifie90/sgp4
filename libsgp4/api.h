// api.h
// uses C calling convention

#include <stdio.h>

#ifndef __WRAPPER_H__
#define __WRAPPER_H__

#ifdef __cplusplus
extern "C" {
#endif

	typedef void* Tle_C;

	typedef void* SGP4_C;

	typedef void* Eci_C;

	// Constructor for TLE
	void* create_Tle(char* line_one, char* line_two, int size);

	// Destructor for TLE
	void destroy_Tle(Tle_C* tle_in);

	// Function to test the TLE
	void test_Tle(Tle_C* tle_in);

	// Constructor for SGP4
	void* create_SGP4(Tle_C* tle_in);

	// Wrapper for FindPosition(tSince)
	void FindPosition_wrap(SGP4_C* thisSGP, double timeSince, FILE* ptr_to_file);

	//// Destructor for SGP4
	//void* destroy_SGP4(SGP4_C sgp4_in);

#ifdef __cplusplus
}
#endif
#endif