#ifndef STRING_ADJUSTER_H
#define STRING_ADJUSTER_H

#include <iostream>
#include <string>
#include <vector>

#include "CheckTool.h"

class StringAdjuster {
	
public :

	StringAdjuster() ; // constructor
	~StringAdjuster() ; // destructor
	
	std::string ClearWhite( std::string str ) ;
	std::string ClearHeadTailWhite( std::string str ) ;
	
	std::string CutHead( std::string str, int cutSize ) ;
	std::string CutTail( std::string str, int cutSize ) ;
	
	std::vector<std::string> SplitTokens( std::string str ) ;
	
private:

	CheckTool * mCT ;
	
} ; // class StringAdjuster

StringAdjuster::StringAdjuster() { // constructor
	
	mCT = new CheckTool() ;
	
} // StringAdjuster::StringAdjuster()

StringAdjuster::~StringAdjuster() { // destructor
	
	delete mCT ;
	mCT = NULL ;
	
} // StringAdjuster::~StringAdjuster()

std::string StringAdjuster::ClearWhite( std::string str ) {
	
	std::string retStr = "" ;
	
	for ( int i = 0 ; i < str.length() ; i++ ) {
		if ( ! mCT->IsWhite( str[i] ) ) {
			retStr += str[i] ;
		} // if
	} // for	
	
	return retStr ;
	
} // StringAdjuster::ClearWhite()

std::string StringAdjuster::ClearHeadTailWhite( std::string str ) {
	
	int hi = 0, ti = -1, i = 0 ;
	std::string retStr = "" ;
	
	for ( i = 0 ; i < str.length() ; i++ ) {
		if ( ! mCT->IsWhite( str[i] ) ) {
			hi = i ;
			break ;
		} // if
	} // for
	
	for ( i = str.length() - 1 ; i >= 0 ; i-- ) {
		if ( ! mCT->IsWhite( str[i] ) ) {
			ti = i ;
			break ;
		} // if
	} // for
	
	for ( i = hi ; i <= ti ; i++ ) {
		retStr += str[i] ;
	} // for	
	
	return retStr ;
	
} // StringAdjuster::ClearHeadTailWhite()

std::string StringAdjuster::CutHead( std::string str, int cutSize ) {
	
	std::string retStr = "" ;
	
	for ( int i = cutSize ; i < str.length() ; i++ ) {
		retStr += str[i] ;
	} // for	
	
	return retStr ;
	
} // StringAdjuster::CutHead()

std::string StringAdjuster::CutTail( std::string str, int cutSize ) {
	
	std::string retStr = "" ;
	
	for ( int i = 0 ; i < str.length() - cutSize ; i++ ) {
		retStr += str[i] ;
	} // for
	
	return retStr ;
	
} // StringAdjuster::CutTail()

std::vector<std::string> StringAdjuster::SplitTokens( std::string str ) {
	
	std::vector<std::string> retVec ;
	std::string temp = "" ;
	
	for ( int i = 0 ; i < str.length() ; i++ ) {
		
		if ( mCT->IsWhite( str[i] ) ) {			
			if ( temp != "" ) {
				retVec.push_back( temp ) ;
				temp = "" ;
			} // if			
		} // if
		else {
			temp += str[i] ;
		} // else
		
	} // for
	
	if ( temp != "" ) {
		retVec.push_back( temp ) ;
	} // if
	
	return retVec ;
	
} // StringAdjuster::SplitTokens()
	
#endif // STRING_ADJUSTER_H








