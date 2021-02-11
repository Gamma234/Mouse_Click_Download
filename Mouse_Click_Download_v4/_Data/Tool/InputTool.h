#ifndef INPUT_TOOL_H
#define INPUT_TOOL_H

#include <iostream>
#include <string>

#include "CheckTool.h"
#include "TransformTool.h"

class InputTool {

public:

	InputTool() ; // constructor 
	~InputTool() ; // destructor 

	char InputChar( std::string statement, bool ignoreWhite ) ;
	int InputInteger( std::string statement ) ; // + - 0
	std::string InputStringLine( std::string statement, bool allowEmpty ) ; 

private:

	CheckTool * mCT ;
	TransformTool * mTT ;

} ; // class InputTool

InputTool::InputTool() { // constructor 

	mCT = new CheckTool() ;
	mTT = new TransformTool() ;

} // InputTool::InputTool()

InputTool::~InputTool() { // destructor 

	delete mCT ;
	mCT = NULL ;
	delete mTT ;
	mTT = NULL ;

} // InputTool::~InputTool()

char InputTool::InputChar( std::string statement, bool ignoreWhite ) {

	std::string inputStr = "" ;
	int i = 0 ;

	while ( true ) {

		mTT->SetColor( 14 ) ;
		std::cout << statement ;
		std::getline( std::cin, inputStr ) ;
		mTT->SetColor( 7 ) ;
		
		if ( inputStr.length() != 0 && ( ! ignoreWhite ) ) {
			return inputStr[0] ;
		} // if
		else {
			
			for ( i = 0 ; i < inputStr.length() ; i++ ) {
				if ( ! mCT->IsWhite( inputStr[i] ) ) {
					std::cout << "Get your input : " << inputStr[i] << "\n" ;
					return inputStr[i] ;
				} // if
			} // for
			
		} // else

	} // while

} // InputTool::InputChar()

int InputTool::InputInteger( std::string statement ) { // + - 0

	std::string inputStr = "" ;
	int i = 0, num = 0 ;

	while ( true ) {

		mTT->SetColor( 14 ) ;
		std::cout << statement ;
		std::getline( std::cin, inputStr ) ;
		mTT->SetColor( 7 ) ;

		if ( mCT->IsInteger( inputStr, false ) ) {
			num = mTT->StringToInt( inputStr ) ;
			std::cout << "Get your input : " << num << "\n" ;
			return num ;
		} // if

		mTT->SetColor( 12 ) ;
		std::cout << "[Not a number !]" << "\n\n" ; // ERROR
		mTT->SetColor( 7 ) ;

	} // while

} // InputTool::InputInteger()

std::string InputTool::InputStringLine( std::string statement, bool allowEmpty ) {
	
	std::string inputStr = "" ;
	
	do {		
		mTT->SetColor( 14 ) ;
		std::cout << statement ;
		std::getline( std::cin, inputStr ) ;
		mTT->SetColor( 7 ) ;	
	} while ( ( ! allowEmpty ) && inputStr.length() == 0 ) ;
	
	std::cout << "Get your input : " << inputStr << "\n" ;
	
	return inputStr ;	
	
} // InputTool::InputStringLine()

#endif // INPUT_TOOL_H








