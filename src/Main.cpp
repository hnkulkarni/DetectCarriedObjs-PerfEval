//============================================================================
// Name        : Main.cpp
// Author      : Hrushikesh
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include "Args.h"
#include "App.h"

/*******************************************************************
 * Function Name: Main
 * Return Type 	: int
 * Created 		: Dec 31, 2012
 * Created By 	: hrushi
 * Comments		: This is the Main of the Code
 *******************************************************************/
int main( int argc, char* argv[])
{
	Args args;
	App app;

	int iRet = args.parse(argc, argv);

	if( iRet != EXIT_SUCCESS )
	{
		return ERR_INVALID_ARGS;
	}

	iRet = app.Run( args );

	return EXIT_SUCCESS;
}

