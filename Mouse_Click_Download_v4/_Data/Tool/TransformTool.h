#ifndef TRANSFORM_TOOL_H
#define TRANSFORM_TOOL_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <windows.h>

class TransformTool {

public :

	TransformTool() {} ; // constructor

	int StringToInt( std::string str ) ; // std::string -> int
    std::string IntToString( int num ) ; // int -> std::string 

    void SetColor( int color ) ;

} ; // class TransformTool

int TransformTool::StringToInt( std::string str ) { // std::string -> int

	return atoi( str.c_str() ) ;

} // TransformTool::StringToInt()

std::string TransformTool::IntToString( int num ) { // int -> std::string 

	std::string temp = "" ;
	bool positive = true ;

	if ( num < 0 ) {
		num *= ( -1 ) ;
		positive = false ;
	} // if	

	do {
		temp = (char)( num % 10 + '0' ) + temp ;
		num /= 10 ;
	} while ( num != 0 ) ;

	return ( positive ? temp : "-" + temp ) ;

} // TransformTool::IntToString()

void TransformTool::SetColor( int color ) {

	// 7  : original
	// 12 : red
	// 14 : yellow  

	HANDLE hConsole ;
	hConsole = GetStdHandle( STD_OUTPUT_HANDLE ) ;
	SetConsoleTextAttribute( hConsole, color ) ;

} // TransformTool::SetColor()

#endif // TRANSFORM_TOOL_H








