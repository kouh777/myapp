
#include <Windows.h>
#include <fstream>
#include <malloc.h>
#include "stringlist.h"

using namespace std;


//--------------------------------------------------------------------------------------------------------
// �g�����@��
 std::wstring TrimLeft( std::wstring &text )
{
	const TCHAR *data = text.c_str(); 
	const int len = text.length();
	int nSt = 0;

	// ���䕶�����̂���
	for( nSt=0; nSt<len; nSt++ ) {
		if( data[nSt] > 0x20 ) {
			text = text.substr( nSt ); 
			break;
		}
	}
	return text;
}
//--------------------------------------------------------------------------------------------------------
// �g�����@�E
 std::wstring TrimRight( std::wstring &text )
{
	const TCHAR *data = text.c_str(); 
	const int len = text.length();
	int nEd = 0;

	// ���䕶�����̂���
	for( nEd=len-1; nEd>=0; nEd-- ) {
		if( data[nEd] > 0x20 ) {
			text = text.substr( 0, nEd+1 ); 
			break;
		}
	}

	return text;
}
//--------------------------------------------------------------------------------------------------------
// �g����
 std::wstring Trim( std::wstring &text )
{
	text = TrimLeft( text ); 
	text = TrimRight( text );
	return text;
}

//--------------
// StringList
//--------------

//--------------------------------------------------------------------------------------------------------
//
TStringList::TStringList( void ) 
{ 
	Clear(); 
}

//----------------------------------------------------------------------
//
TStringList::~TStringList( void ) 
{ 
	Clear(); 
}

//--------------------------------------------------------------------------------------------------------
//
void TStringList::Clear( void ) 
{ 
	FStrings.clear(); 
} 

//--------------------------------------------------------------------------------------------------------
int TStringList::GetCount( void ) const 
{ 
	return FStrings.size(); 
}

//--------------------------------------------------------------------------------------------------------
// �e�L�X�g�@�擾
std::wstring &TStringList::operator []( int index ) 
{ 
	if( index < 0 || (int)FStrings.size() <= index ) throw TEXT("StringList::operator []");

	return (std::wstring &)FStrings[index]; 
}

//--------------------------------------------------------------------------------------------------------
// �e�L�X�g�@�擾 const
const std::wstring &TStringList::operator []( int index ) const 
{ 
	if( index < 0 || (int)FStrings.size() <= index ) throw TEXT("StringList::operator []");

	return (const std::wstring &)FStrings[index]; 
} 

//--------------------------------------------------------------------------------------------------------
// �ǉ�
int TStringList::Add( std::wstring value )
{
	FStrings.push_back( value ); 

	return GetCount() - 1;
}

//--------------------------------------------------------------------------------------------------------
// �ǂݍ���
int TStringList::ReadFromFile( const std::wstring AFileName )
{
	int result = 0;
	std::ifstream ifs;
	static char line[255];
	static wchar_t strW[255]; 

	// �N���A
	Clear();

	ifs.open( AFileName.c_str(), ios::in); // �ǂݎ���p�ŊJ��
	if( ifs.fail() )	return -1;	// ���s

	// �P�s�Âǂݍ���
	while( !ifs.eof() ){
		ifs.getline(line, sizeof(line));
		// change wide char 
		MultiByteToWideChar(CP_ACP, 0, line, -1, strW, 255);

		FStrings.push_back( strW ); 

		result++;
	}
	ifs.close();

	return result;
}
//--------------------------------------------------------------------------------------------------------
// ��������
int TStringList::WriteToFile( std::wstring AFileName ) const
{
	int result = 0;
	static char str[255];
	ofstream ofs;
	const int lines = GetCount();

	ofs.open( AFileName.c_str(), ios::out);
	if( ofs.fail() )	return -1;	// ���s

	for( int i=0; i<lines; i++ ) {
		// change mult char 
		int len = FStrings[i].length() + 1; 
		WideCharToMultiByte( CP_THREAD_ACP, 0, FStrings[i].c_str(), len, str, len*2, NULL, NULL );

		ofs << str << endl;
		result++;
	}

	ofs.close();

	return result;
}

//--------------------------------------------------------------------------------------------------------
// �J���}�e�L�X�g
int TStringList::CommaText( std::wstring text )
{
	int result = 0;
	int cnt;
	int current = 0;

	// �N���A
	Clear();
	// �J���}������
	while( (cnt = text.find( TEXT(","), 0 )) != std::wstring::npos ) { 
		std::wstring str = Trim( text.substr(0, cnt) );
		if( str != TEXT("") ) {	
			FStrings.push_back( str );
			result++;
		}
		text = text.substr(cnt+1); 
	}
	Trim( text );
	if( text != TEXT("") ) {
		FStrings.push_back( text );
		result++;
	}
	return result;
}

//--------------------------------------------------------------------------------------------------------

