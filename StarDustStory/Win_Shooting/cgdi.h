
#ifndef __CGDI_H__
#define __CGDI_H__

//------------------------------------------------
#include <Windows.h>
#include <vector>
#include <string>
#include "Vector2D.h"

//------------------------------------------------
#ifdef _UNICODE
	#define STRING std::wstring
#else
	#define STRING std::string
#endif

//------------------------------------------------
const int NumColors = 15;
const COLORREF colors[NumColors] = 
{
	RGB( 255,   0,   0 ),
	RGB(   0,   0, 255 ),
	RGB(   0, 255,   0 ),
	RGB(   0,   0,   0 ),
	RGB( 255, 200, 200 ),
	RGB( 200, 200, 200 ),
	RGB( 255, 255,   0 ),
	RGB( 255, 170,   0 ),
	RGB( 255,   0, 170 ),
	RGB( 133,  90,   0 ),
	RGB( 255, 255, 255 ),
	RGB(   0, 100,   0 ),	// dark green
	RGB(   0, 255, 255 ),	// light blue
	RGB( 200, 200, 200 ),	// light gray
	RGB( 255, 230, 230 ),	// light pink
};


//----------------------------------------------
class TCgdi
{
public:
	int NumPenColors( void ) const { return NumColors; }
	// カラー一覧
	enum {
		red, 
		blue, 
		green,
		black,
		pink,
		grey,
		yellow,
		orange,
		purple,
		brown,
		white,
		dark_green,
		light_blue,
		light_grey,
		light_pink,
		hollow
	};
private:
	TCgdi( void );

	// コピーコンストラクタを無効化する
	TCgdi( const TCgdi & );
	// =演算子を無効化する
	TCgdi operator =( const TCgdi & );
public:
	static TCgdi &GetIsntance( void ) {
		static TCgdi instance;	// 唯一のインスタンス
		return instance;
	}

	~TCgdi( void );

private:
	HPEN FhOldPen;

	// all the pens
	HPEN FhBlackPen;
	HPEN FhWhitePen;
	HPEN FhRedPen;
	HPEN FhGreenPen;
	HPEN FhBluePen;
	HPEN FhGrayPen;
	HPEN FhPinkPen;
	HPEN FhOrangePen;
	HPEN FhYellowPen;
	HPEN FhPurplePen;
	HPEN FhBrownPen;

	HPEN FhDarkGreenPen;
	HPEN FhLightBluePen;
	HPEN FhLightGrayPen;
	HPEN FhLightPinkPen;
	
	HPEN FhThickBlackPen;
	HPEN FhThickWhitePen;
	HPEN FhThickRedPen;
	HPEN FhThickGreenPen;
	HPEN FhThickBluePen;

	HBRUSH FhOldBrush;

	// all the brushes
	HBRUSH FhRedBrush;
	HBRUSH FhGreenBrush;
	HBRUSH FhBlueBrush;
	HBRUSH FhGrayBrush;
	HBRUSH FhBrownBrush;
	HBRUSH FhYellowBrush;
	HBRUSH FhOrangeBrush;

	HBRUSH FhLightBlueBrush;
	HBRUSH FhDarkGreenBrush;

	HDC FhDc;

public:
	void BlackPen( void )	{ if(FhDc) {SelectObject( FhDc, FhBlackPen );} }  
	void WhitePen( void )	{ if(FhDc) {SelectObject( FhDc, FhWhitePen );} }  
	void RedPen( void )		{ if(FhDc) {SelectObject( FhDc, FhRedPen );} }  
	void GreenPen( void )	{ if(FhDc) {SelectObject( FhDc, FhGreenPen );} }  
	void BluePen( void )	{ if(FhDc) {SelectObject( FhDc, FhBluePen );} }  
	void GreyPen( void )	{ if(FhDc) {SelectObject( FhDc, FhGrayPen );} }  
	void PinkPen( void )	{ if(FhDc) {SelectObject( FhDc, FhPinkPen );} }  
	void OrangePen( void )	{ if(FhDc) {SelectObject( FhDc, FhOrangePen );} }  
	void YellowPen( void )	{ if(FhDc) {SelectObject( FhDc, FhYellowPen );} }  
	void PurplePen( void )	{ if(FhDc) {SelectObject( FhDc, FhPurplePen );} }  
	void BrownPen( void )	{ if(FhDc) {SelectObject( FhDc, FhBrownPen );} }  

	void DarkGreenPen( void ){ if(FhDc) {SelectObject( FhDc, FhDarkGreenPen );} }  
	void LightBluePen( void ){ if(FhDc) {SelectObject( FhDc, FhLightBluePen );} }  
	void LightGreyPen( void ){ if(FhDc) {SelectObject( FhDc, FhLightGrayPen );} }  
	void LightPinkPen( void ){ if(FhDc) {SelectObject( FhDc, FhLightPinkPen );} }  

	void ThickBlackPen( void )	{ if(FhDc) {SelectObject( FhDc, FhThickBlackPen );} }  
	void ThickWhitePen( void )	{ if(FhDc) {SelectObject( FhDc, FhThickWhitePen );} }  
	void ThickRedPen( void )	{ if(FhDc) {SelectObject( FhDc, FhThickRedPen );} }  
	void ThickGreenPen( void )	{ if(FhDc) {SelectObject( FhDc, FhThickGreenPen );} }  
	void ThickBluePen( void )	{ if(FhDc) {SelectObject( FhDc, FhThickBluePen );} }  
	
	void BlackBrush( void )	{ if(FhDc) {SelectObject( FhDc, GetStockObject(BLACK_BRUSH) );} }   
	void WhiteBrush( void )	{ if(FhDc) {SelectObject( FhDc, GetStockObject(WHITE_BRUSH) );} }   
	void HollowBrush( void ){ if(FhDc) {SelectObject( FhDc, GetStockObject(HOLLOW_BRUSH) );} }   
	void RedBrush( void )	{ if(FhDc) {SelectObject( FhDc, FhRedBrush );} } 
	void GreenBrush( void )	{ if(FhDc) {SelectObject( FhDc, FhGreenBrush );} } 
	void BlueBrush( void )	{ if(FhDc) {SelectObject( FhDc, FhBlueBrush );} } 
	void GrayBrush( void )	{ if(FhDc) {SelectObject( FhDc, FhGrayBrush );} } 
	void BrownBrush( void )	{ if(FhDc) {SelectObject( FhDc, FhBrownBrush );} } 
	void YellowBrush( void ){ if(FhDc) {SelectObject( FhDc, FhYellowBrush );} } 
	void OrangeBrush( void ){ if(FhDc) {SelectObject( FhDc, FhOrangeBrush );} } 
	
	void LightBlueBrush( void ){ if(FhDc) {SelectObject( FhDc, FhLightBlueBrush );} } 
	void DarkGreenBrush( void ){ if(FhDc) {SelectObject( FhDc, FhDarkGreenBrush );} }

	// ※描く前に必ずこの関数を呼ぶこと
	void StartDrawing( HDC hdc ) {
		FhDc = hdc;
		// 現在のペンを取得する
		FhOldPen = (HPEN)SelectObject( hdc, FhBlackPen );  
		SelectObject( hdc, FhOldPen );  
		// 現在のブラシを取得する
		FhOldBrush = (HBRUSH)SelectObject( hdc, FhRedBrush );  
		SelectObject( hdc, FhOldBrush );  
	}

	// ※描いた後に必ずこの関数を呼ぶこと
	void StopDrawing( HDC hdc ) {
		// 元の状態に戻す
		SelectObject( hdc, FhOldPen );	
		SelectObject( hdc, FhOldBrush ); 
		
		FhDc = NULL;
	}

	// Draw Pixel
	void SetDot( int x, int y , DWORD color) {
		::SetPixel( FhDc, x, y, color );
	}
	// Draw Line
	void Line( const Vector2D &to, const Vector2D &from ) {
		::MoveToEx( FhDc, (int)to.x, (int)to.y, NULL );
		::LineTo( FhDc, (int)from.x, (int)from.y );
	}
	void Line( double x1, double y1, double x2, double y2 ) {
		::MoveToEx( FhDc, (int)x1, (int)y1, NULL );
		::LineTo( FhDc, (int)x2, (int)y2 );
	}

	// Draw Rectangle
	void Rectangle( const Vector2D &lt, const Vector2D &rb ) {
		::Rectangle( FhDc, (int)lt.x, (int)lt.y, (int)rb.x, (int)rb.y );
	}
	void Rectangle( double l, double t, double r, double b ) {
		::Rectangle( FhDc, (int)l, (int)t, (int)r, (int)b );
	}

	// Draw Circle
	void Circle( const Vector2D &center, double redious ) {
		::Ellipse( FhDc,(int)( center.x-redious ),
						(int)( center.y-redious ),
						(int)( center.x+redious ),
						(int)( center.y+redious ) );
	}

	void Cross( const Vector2D &pos, double diameter ) {
		Line( (int)pos.x-diameter, (int)pos.y-diameter, (int)pos.x+diameter, (int)pos.y+diameter );
		Line( (int)pos.x-diameter, (int)pos.y+diameter, (int)pos.x+diameter, (int)pos.y-diameter );
	}

	void PolyLine( const std::vector<Vector2D> &vertexs ) {

		for( DWORD i=1; i<vertexs.size(); i++ ) {
			Line( vertexs[i-1], vertexs[i] );
		}
		Line( vertexs[vertexs.size()-1], vertexs[0] );
	}

	void LineWithArrow( Vector2D from, Vector2D to, double size ) {

		Line( from, to );

		std::vector<Vector2D> vertexs;

		Vector2D crossPoint = to + Vec2DNormalize(from-to) * size;
		Vector2D sidePoint = Vec2DNormalize(from-to).Perp() * 0.4 * size;

		vertexs.push_back( to );
		vertexs.push_back( crossPoint + sidePoint );
		vertexs.push_back( crossPoint - sidePoint );
		PolyLine( vertexs );
	}

	//-----------------
	// Text Drawing 
	//-----------------
	void TextOutAtPos( double x, double y, const STRING &s ) {
		::TextOut( FhDc, (int)x, (int)y, s.c_str(), (int)s.size() );
	}
	void TextOutAtPos( const Vector2D &pos, const STRING &s ) {
		::TextOut( FhDc, (int)pos.x, (int)pos.y, s.c_str(), (int)s.size() );
	}
	void TextColor( BYTE r, BYTE g, BYTE b ) {
		::SetTextColor( FhDc, RGB(r,g,b) ); 
	}
	void TransparentText( void ) {
		::SetBkMode( FhDc, TRANSPARENT ); 
	}
	void OpaqueText( void ) {
		::SetBkMode( FhDc, OPAQUE );
	}
	void TextBGColor( BYTE r, BYTE g, BYTE b ) {
		::SetBkColor( FhDc, RGB(r,g,b) ); 
	}
	void DrawText(LPCTSTR lpString,	// 描画するテキスト
				  int nCount,		// テキストの長さ
				  LPRECT lpRect,	// テキストを描画する長方形領域
				  UINT uFormat ) {	// テキスト描画オプション
					
		::DrawText( FhDc, lpString, nCount, lpRect, uFormat );
	}
};

//----------------------------------------------
inline TCgdi &Cgdi( void ) { return TCgdi::GetIsntance(); }

//----------------------------------------------
#endif	// __CGDI_H__