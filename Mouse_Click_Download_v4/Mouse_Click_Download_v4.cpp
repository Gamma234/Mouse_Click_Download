#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <conio.h>

// <conio.h> : kbhit()

#include "_Data/Tool/CheckTool.h"
#include "_Data/Tool/TransformTool.h"
#include "_Data/Tool/InputTool.h"
#include "_Data/Tool/StringAdjuster.h"

#define POSITION_SIZE 8

#define CURSOR_POSITION_FILE_PATH "_Data\\CursorPositionFilePath.txt"
#define OUTPUT_PATH "_Data\\OutputPath.txt"

#define FIND_POSITION_OPT "f"
#define DOWNLOAD_OPT "d"
#define CHANGE_DURATION_OPT "c"
#define OPEN_CLOSE_NUMBERING_OPT "n"
#define OPEN_CLOSE_CREATING_A_FILE_OPT "a"
#define SET_CURSOR_POSITION_FILE_PATH_OPT "p"
#define SET_OUTPUT_PATH_OPT "o"
#define QUIT_OPT "q"

class Mission {

public:	

	Mission() ; // constructor 
	~Mission() ; // destructor

	void Action() ;

private:

	int mTime ;
	std::string mCursorPositionFilePath, mOutputPath ;
	bool mNumbering, mCreatingAFile ;
	InputTool * mIT ;
	TransformTool * mTT ;
	CheckTool * mCT ;
	StringAdjuster * mSA ;
	
	/* basic methods */

    bool Initialize() ; 
	void Introduction() ;
	void PrintErrorMessage( std::string errorMsg ) ;
	
	/* methods for options */

	void FindPosition() ;
	void Download() ;
	void ChangeDuration() ;
	void OpenCloseNumbering() ;
	void OpenCloseCreatingAFile() ;
	void SetCursorPositionFilePath() ;
	void SetOutputPath() ;
	
	/* other methods */

	bool CursorAction( int position[POSITION_SIZE], int serialNum );
	void PushNumberKey( int number ) ;	
	
	bool SetStringByFile( std::string fileName, std::string & str, bool allowEmpty ) ;
	bool SetCursorPosition( int position[POSITION_SIZE] ) ;

} ; // class Mission

int main() {

	Mission mission ;
	mission.Action() ;

} // main()

Mission::Mission() : mTime( 2000 ), mNumbering( false ), mCreatingAFile( false ) { // constructor 

	mIT = new InputTool() ;
	mTT = new TransformTool() ;
	mCT = new CheckTool() ;
	mSA = new StringAdjuster() ;
	
	mCursorPositionFilePath = "" ;
	mOutputPath = "" ;

} // Mission::Mission()

Mission::~Mission() { // destructor

	delete mIT ;
	mIT = NULL ;
	delete mTT ;
	mTT = NULL ;
	delete mCT ;
	mCT = NULL ;
	delete mSA ;
	mSA = NULL ;

} // Mission::~Mission()

void Mission::Action() {

	std::string option = "" ;
	bool running = Initialize() ;

	while ( running ) {

		Introduction() ;
		option = mIT->InputStringLine( "Input an option : ", false ) ;
		std::cout << "\n" ;
		
		if ( option == FIND_POSITION_OPT ) FindPosition() ;
		else if ( option == DOWNLOAD_OPT ) Download() ;
		else if ( option == CHANGE_DURATION_OPT ) ChangeDuration() ;
		else if ( option == OPEN_CLOSE_NUMBERING_OPT ) OpenCloseNumbering() ;
		else if ( option == OPEN_CLOSE_CREATING_A_FILE_OPT ) OpenCloseCreatingAFile() ;
		else if ( option == SET_CURSOR_POSITION_FILE_PATH_OPT ) SetCursorPositionFilePath() ;
		else if ( option == SET_OUTPUT_PATH_OPT ) SetOutputPath() ;
		else if ( option == QUIT_OPT ) running = false ;
		else PrintErrorMessage( "[This option doesn't exist.]" ) ;

	} // while

	std::cout << "Quit" << "\n" ;

} // Mission::Action()  

/* ------------- */
/* basic methods */
/* ------------- */

bool Mission::Initialize() {	
	
	if ( ! SetStringByFile( CURSOR_POSITION_FILE_PATH, mCursorPositionFilePath, false ) ) {
		return false ;
	} // if
	
	if ( ! mCT->IsExistingFile( mCursorPositionFilePath ) ) {
		PrintErrorMessage( "[\"" + mCursorPositionFilePath + "\" does not exist !]" ) ;
		return false ;
	} // if
	
	if ( ! SetStringByFile( OUTPUT_PATH, mOutputPath, true ) ) {
		return false ;
	} // if
	
	if ( ! mCT->IsExistingPath( mOutputPath ) ) {
		PrintErrorMessage( "[\"" + mOutputPath + "\" does not exist !]" ) ;
		return false ;
	} // if
	
	return true ;
	
} // Mission::Initialize()

void Mission::Introduction() {

	std::cout << "========== Status ===========" << "\n" ;
	std::cout << "Duration : " << mTime / 1000 << " s" << "\n" ;
	std::cout << "Cursor Position File Path : " << mCursorPositionFilePath << "\n" ;
	std::cout << "Output Path : " << mOutputPath << "\n" ;
	std::cout << "Numbering : " << ( mNumbering ? "Open" : "Close" ) << "\n" ;
	std::cout << "Creating a File : " << ( mCreatingAFile ? "Open" : "Close" ) << "\n" ;
	std::cout << "=============================" << "\n\n" ;
	
	std::cout << "========== Options ==========" << "\n" ;
	std::cout << FIND_POSITION_OPT << " : Find Position" << "\n" ;
	std::cout << DOWNLOAD_OPT << " : Download" << "\n" ;
	std::cout << CHANGE_DURATION_OPT << " : Change Duration" << "\n" ;
	std::cout << OPEN_CLOSE_NUMBERING_OPT << " : Open/Close Numbering" << "\n" ;
	std::cout << OPEN_CLOSE_CREATING_A_FILE_OPT << " : Open/Close Creating a File" << "\n" ;
	std::cout << SET_CURSOR_POSITION_FILE_PATH_OPT << " : Set Cursor Position File Path" << "\n" ;
	std::cout << SET_OUTPUT_PATH_OPT << " : Set Output Path" << "\n" ;
	std::cout << QUIT_OPT << " : Quit" << "\n" ;
	std::cout << "=============================" << "\n\n" ;

} // Mission::Introduction() 

void Mission::PrintErrorMessage( std::string errorMsg ) {

	mTT->SetColor( 12 ) ;
	std::cout << errorMsg << "\n\n" ;
	mTT->SetColor( 7 ) ;

} // Mission::PrintErrorMessage()

/* ------------------- */
/* methods for options */
/* ------------------- */

void Mission::FindPosition() {

	std::cout << "------Find Position--------" << "\n\n" ;
	std::cout << "keep pressing \"any key\" to stop\n" << "-----" << "\n";

	POINT aPos; // mouse position

	while ( true ) {

		// if ( KEY_DOWM(VK_ESCAPE) ) break;

		if ( kbhit() ) // check whether press a key on the keyboard 
			break;

		Sleep( 1000 ); // stop 1 second
		GetCursorPos( &aPos ); // get "mouse position"
		std::cout << aPos.x << " " << aPos.y << "\n";
		Sleep( 1000 ); // stop 1 second

	} // while

	std::cout << "STOP\n" << "---------------------" << "\n\n" ;

} // Mission::FindPosition()

void Mission::Download() {

	std::cout << "------Download--------" << "\n\n" ;
	
	int position[POSITION_SIZE] ;
	
	if ( ! SetCursorPosition( position ) ) {
		return ;
	} // if
	
	/* suggestion */

	std::cout << "Please open the website first." << "\n";
	std::cout << "\n" << "Return to the black window.\nPress any key to Stop\n" << "\n";

	/* mNumbering */

	int serialNum = 1 ;

	if ( mNumbering ) {

		std::cout << "Set a begin integer for numbering" << "\n" ;
		int num = mIT->InputInteger( "Input a begin integer : " ) ;

		while ( num < 0 ) {
			PrintErrorMessage( "[Can not be negative integer !]" ) ;
			num = mIT->InputInteger( "Input a begin integer : " ) ;
		} // while

		serialNum = num ;
		std::cout << "Successfully Set" << "\n\n" ;

	} // if 
	
	/* mCreatingAFile */
	
	if ( mCreatingAFile ) {
		
		std::cout << "Set a string for the file" << "\n" ;
		
		std::string outFileName = ( mOutputPath == "" ? "source.txt" :
		                                                ( mOutputPath + "\\source.txt" ) )  ;		
		std::fstream outFile( outFileName.c_str(), std::ios::out ) ;
		
		if ( ! outFile ) {
		    PrintErrorMessage( "[Fail to create \"" + outFileName + "\"]" ) ;
		    return ;
		} // if	
		
		outFile << mIT->InputStringLine( "Input a string : ", true ) ;
		outFile.close() ;
		
		std::cout << "Successfully create : " << outFileName << "\n\n" ;
		
	} // if

	/* num of download */

	int num = mIT->InputInteger( "How many do you want to download : " ) ;

	while ( num < 0 ) {
		PrintErrorMessage( "[Can't be negative !]" ) ;
		num = mIT->InputInteger( "How many do you want to download : " ) ;
	} // while

    /* countdown */
    
	for ( int i = 3 ; i > 0 ; i-- ) {
		std::cout << "begin : " << i << "\n" ;
		Sleep( 1000 ) ;
	} // for
	std::cout << "\n" ;
	
	/* download */
	
	for ( int i = 0; i < num; i++ ) {

		if ( kbhit() || !CursorAction( position, serialNum ) ) {
			std::cout << "STOP\n----------------------" << "\n" ;
			return ;
		} // if

		/* one is done */
		
		std::cout << "done " << i + 1 << "\n";
		serialNum++ ;
		Sleep( mTime );

	} // for	

	std::cout << "\n" << "END" << "\n" ;
	std::cout << "----------------------" << "\n\n" ;

} // Mission::Download()

void Mission::ChangeDuration() {

	std::cout << "--------Change Duration--------" << "\n\n" ;

	std::cout << "Duration now is : " << mTime / 1000 << " s" << "\n" << "\n" ;

	int num = mIT->InputInteger( "Input a positive integer : " ) ;

	while ( num <= 0 ) {
		PrintErrorMessage( "[Not a positive integer !]" ) ;
		num = mIT->InputInteger( "Input a positive integer : " ) ;
	} // while

	mTime = num * 1000 ;

	std::cout << "\n" << "Duration now is : " << mTime / 1000 << " s" << "\n" << "\n" ;

	std::cout << "-------------------------------" << "\n\n" ;

} // Mission::ChangeDuration()

void Mission::OpenCloseNumbering() {

	std::cout << "--------Open/Close mNumbering--------" << "\n\n" ;

	mNumbering = ( !mNumbering ) ;
	
	std::cout << "Numbering : " << ( ! mNumbering ? "Open" : "Close" ) << "\n" ;
	std::cout << "Change To" << "\n" ;
	std::cout << "Numbering : " << ( mNumbering ? "Open" : "Close" ) << "\n" << "\n" ;

	std::cout << "------------------------------------" << "\n\n" ;

} // Mission::OpenCloseNumbering() 

void Mission::OpenCloseCreatingAFile() {
	
    std::cout << "------Open/Close Creating a File-----" << "\n\n" ;

	mCreatingAFile = ( !mCreatingAFile ) ;
	
	std::cout << "Creating a File : " << ( ! mCreatingAFile ? "Open" : "Close" ) << "\n" ;
	std::cout << "Change To" << "\n" ;
	std::cout << "Creating a File : " << ( mCreatingAFile ? "Open" : "Close" ) << "\n" << "\n" ;

	std::cout << "------------------------------------" << "\n\n" ;
	
} // Mission::OpenCloseCreatingAFile()

void Mission::SetCursorPositionFilePath() {
	
	std::cout << "------Set Cursor Position File Path-----" << "\n\n" ;
	
	std::string inputStr = "" ;
	
	while ( true ) {
		
		inputStr = mSA->ClearHeadTailWhite( mIT->InputStringLine( "Input a file path : ", false ) ) ;
		
		if ( mCT->IsExistingFile( inputStr ) ) {
			break ;
		} // if
		else {
			PrintErrorMessage( "[\"" + inputStr + "\" does not exist !]" ) ;
		} // else
		
	} // while
	
	std::fstream outFile( CURSOR_POSITION_FILE_PATH, std::ios::out ) ;
	
	if ( outFile ) {
		outFile << inputStr ;
		outFile.close() ;
		mCursorPositionFilePath = inputStr ;
		std::cout << "Successfully Set" << "\n\n" ;
	} // if
	else {
		PrintErrorMessage( std::string( "[\"" ) + CURSOR_POSITION_FILE_PATH + "\" does not exist !]" ) ;
	} // else
	
	std::cout << "----------------------------------------" << "\n\n" ;
	
} // Mission::SetCursorPositionFilePath()

void Mission::SetOutputPath() {
	
	std::cout << "------Set Output Path-------------------" << "\n\n" ;
	
	std::string inputStr = "" ;
	
	while ( true ) {
		
		inputStr = mSA->ClearHeadTailWhite( mIT->InputStringLine( "Input a path : ", true ) ) ;
		
		if ( mCT->IsExistingPath( inputStr ) ) {
			break ;
		} // if
		else {
			PrintErrorMessage( "[\"" + inputStr + "\" does not exist !]" ) ;
		} // else
		
	} // while
	
	std::fstream outFile( OUTPUT_PATH, std::ios::out ) ;
	
	if ( outFile ) {
		outFile << inputStr ;
		outFile.close() ;
		mOutputPath = inputStr ;
		std::cout << "Successfully Set" << "\n\n" ;
	} // if
	else {
		PrintErrorMessage( std::string( "[\"" ) + OUTPUT_PATH + "\" does not exist !]" ) ;
	} // else
	
	std::cout << "----------------------------------------" << "\n\n" ;
	
} // Mission::SetOutputPath()

/* ------------- */
/* other methods */
/* ------------- */

bool Mission::CursorAction( int position[POSITION_SIZE], int serialNum ) {

	mouse_event( MOUSEEVENTF_WHEEL, 0, 0, 10000, 0 ); // roll to top

	/* initial */
	
	SetCursorPos( position[0], position[1] ); // move the mouse to a certain position
	mouse_event( MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0 ); // right click (down)
	mouse_event( MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0 ); // right click (up)

	Sleep( mTime );
	if ( kbhit() ) return false ;

	/* "Save As ..." */
	
	SetCursorPos( position[2], position[3] ); // move the mouse to a certain position
	mouse_event( MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0 ); // left click (down)
	mouse_event( MOUSEEVENTF_LEFTUP, 0, 0, 0, 0 ); // left click (up)

	Sleep( mTime );
	if ( kbhit() ) return false ;

    /* mNumbering */

	if ( mNumbering ) {

		PushNumberKey( serialNum ) ;

		Sleep( mTime );
		if ( kbhit() ) return false ;

	} // if 		

    /* "Save" */
	
	SetCursorPos( position[4], position[5] ); // move the mouse to a certain position
	mouse_event( MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0 ); // left click (down)
	mouse_event( MOUSEEVENTF_LEFTUP, 0, 0, 0, 0 ); // left click (up)

	Sleep( mTime );
	if ( kbhit() ) return false ;

    /* next */
	
	SetCursorPos( position[6], position[7] ); // move the mouse to a certain position
	mouse_event( MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0 ); // left click (down)
	mouse_event( MOUSEEVENTF_LEFTUP, 0, 0, 0, 0 ); // left click (up)

	return true ;

} // Mission::CursorAction()

void Mission::PushNumberKey( int number ) {

	// 0 -> 96 ~ 9 -> 105 // from "small key board" 

	std::string numStr = mTT->IntToString( number ) ;

	for ( int i = 0 ; i < numStr.length() ; i++ ) {
		keybd_event( numStr[i] + '0', 0, 0, 0 );
		keybd_event( numStr[i] + '0', 0, KEYEVENTF_KEYUP, 0 );
	} // for 

} // Mission::PushNumberKey() 

bool Mission::SetStringByFile( std::string fileName, std::string & str, bool allowEmpty ) {
	
	std::fstream inFile( fileName.c_str(), std::ios::in ) ;	
	std::string temp = "" ;
	
	if ( ! inFile ) {
		PrintErrorMessage( "[\"" + fileName + "\" does not exist !]" ) ;
		return false ;
	} // if
	
	while ( getline( inFile, temp ) ) {
		if ( mCT->IsWhiteString( temp ) ) {
			temp = "" ;
		} // if
		else {
			break ;
		} // else
	} // while
	
	str = ( temp == "" ? "" : mSA->ClearHeadTailWhite( temp ) ) ;
	
	inFile.close() ;
	
	if ( str == "" && ( ! allowEmpty ) ) {
		PrintErrorMessage( "[\"" + fileName + "\" contains nothing !]" ) ;
		return false ;
	} // if
	else {
		return true ;
	} // else
	
} // Mission::SetStringByFile()

bool Mission::SetCursorPosition( int position[POSITION_SIZE] ) {
	
	std::fstream inFile( mCursorPositionFilePath.c_str(), std::ios::in ) ;

	if ( ! inFile ) {
		PrintErrorMessage( "[\"" + mCursorPositionFilePath + "\" does not exist !]" ) ;
		return false ;
	} // if

	for ( int i = 0; i < POSITION_SIZE; i++ ) {

		inFile >> position[i];

		if ( inFile.fail() ) {
			PrintErrorMessage( "[Position ERROE]" ) ;
			inFile.clear();
			inFile.sync();
			inFile.close();
			return false ;
		} // if

	} // for

	inFile.close() ;
	
	return true ;
	
} // Mission::SetCursorPosition()















