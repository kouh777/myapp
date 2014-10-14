
#ifndef __STRINGLIST_H__
#define __STRINGLIST_H__

//--------------------------------------------------------------------------------------------------------
#include <string>
#include <vector>


//--------------------------------------------------------------------------------------------------------
std::wstring TrimLeft( std::wstring &text );
std::wstring TrimRight( std::wstring &text );
std::wstring Trim( std::wstring &text );

//--------------------------------------------------------------------------------------------------------
// StringList
class TStringList
{
private:
	std::vector <std::wstring> FStrings;

public:
	TStringList( void );
	~TStringList( void );
	void Clear( void );
	int GetCount( void ) const;
	
	std::wstring &operator []( int index );
	const std::wstring &operator []( int index ) const;

	int Add( std::wstring value ); 

	int ReadFromFile( const std::wstring AFileName ); 
	int WriteToFile( std::wstring AFileName ) const; 
	int CommaText( std::wstring text );	
};


#endif	// __STRINGLIST_H__