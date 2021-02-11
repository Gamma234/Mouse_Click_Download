#ifndef CHECK_TOOL_H
#define CHECK_TOOL_H

#include <iostream>
#include <string>
#include <fstream>

class CheckTool {

public:

	CheckTool() {} // constructor 

	bool IsInteger( std::string & str, bool squeeze ) ; // + - 0
	bool IsDigit( char ch ) ;
	bool IsWhite( char ch ) ;
	
	bool IsEmptyString( std::string str ) ;
	bool IsWhiteString( std::string str ) ;
	
	bool IsExistingFile( std::string file ) ;
	bool IsExistingPath( std::string path ) ;

} ; // class InputTool

bool CheckTool::IsInteger( std::string & str, bool squeeze ) { // + - 0

	std::string temp = "" ;
	bool meetFirstChar = false ;
	int i = 0 ;

	if ( squeeze ) {

		for ( i = 0 ; i < str.length() ; i++ ) {
			if ( ! IsWhite( str[i] ) ) {
				temp = temp + str[i] ;
			} // if
		} // for

		str = temp ;

	} // if

	for ( i = 0 ; i < str.length() ; i++ ) {
		if ( IsDigit( str[i] ) ) {
			meetFirstChar = true ;
		} // if
		else {
			if ( meetFirstChar ) {
				return false ;
			} // if
			else {
				if ( str[i] == '-' ) {
					meetFirstChar = true ;
				} // if
				else {
					return false ;
				} // else				
			} // else
		} // else
	} // for

	return true ;

} // CheckTool::IsInteger()

bool CheckTool::IsDigit( char ch ) {

	return ( '0' <= ch && ch <= '9' ) ;

} // CheckTool::IsDigit()

bool CheckTool::IsWhite( char ch ) {

	return ( ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' ) ;

} // CheckTool::IsWhite()

bool CheckTool::IsEmptyString( std::string str ) {
	
	return ( str.length() == 0 ) ;
	
} // CheckTool::IsEmptyString()

bool CheckTool::IsWhiteString( std::string str ) {
	
	for ( int i = 0 ; i < str.length() ; i++ ) {
		if ( ! IsWhite( str[i] ) ) {
			return false ;
		} // if
	} // for
	
	return true ;
	
} // CheckTool::IsWhiteString()

bool CheckTool::IsExistingFile( std::string file ) {
	
	std::fstream inFile( file.c_str(), std::ios::in ) ;	
	
	if ( inFile ) {
		inFile.close() ;
		return true ;
	} // if
	else {
		return false ;
	} // else	
	
} // CheckTool::IsExistingFile()

bool CheckTool::IsExistingPath( std::string path ) {
	
	std::string testFileName = "ThisIsATestFile.txt" ;
	
	if ( path.length() != 0 ) {
		if ( path[path.length() - 1] == '\\' ) {
			testFileName = path + testFileName ;
		} // if
		else {
			testFileName = path + "\\" + testFileName ;
		} // else
	} // if
	
	std::fstream outFile( testFileName.c_str(), std::ios::out ) ;	
	
	if ( outFile ) {
		outFile.close() ;
		remove( testFileName.c_str() ) ;
		return true ;
	} // if
	else {
		return false ;		
	} // else	
	
} // CheckTool::IsExistingPath()

#endif // CHECK_TOOL_H








