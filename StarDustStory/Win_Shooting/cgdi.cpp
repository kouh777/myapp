//testcommit


#include "cgdi.h"

//----------------------------------------------
TCgdi::TCgdi( void )
{
	FhBlackPen	= CreatePen( PS_SOLID, 1, colors[black] );
	FhWhitePen	= CreatePen( PS_SOLID, 1, colors[white] );
	FhRedPen	= CreatePen( PS_SOLID, 1, colors[red] );
	FhGreenPen	= CreatePen( PS_SOLID, 1, colors[green] );
	FhBluePen	= CreatePen( PS_SOLID, 1, colors[blue] );
	FhGrayPen	= CreatePen( PS_SOLID, 1, colors[grey] );
	FhPinkPen	= CreatePen( PS_SOLID, 1, colors[pink] );
	FhOrangePen	= CreatePen( PS_SOLID, 1, colors[orange] );
	FhYellowPen	= CreatePen( PS_SOLID, 1, colors[yellow] );
	FhPurplePen	= CreatePen( PS_SOLID, 1, colors[purple] );
	FhBrownPen	= CreatePen( PS_SOLID, 1, colors[brown] );

	FhDarkGreenPen	= CreatePen( PS_SOLID, 1, colors[dark_green] );
	FhLightBluePen	= CreatePen( PS_SOLID, 1, colors[light_blue] );
	FhLightGrayPen	= CreatePen( PS_SOLID, 1, colors[light_grey] );
	FhLightPinkPen	= CreatePen( PS_SOLID, 1, colors[light_pink] );	

	FhThickBlackPen	= CreatePen( PS_SOLID, 2, colors[black] );
	FhThickWhitePen	= CreatePen( PS_SOLID, 2, colors[white] );
	FhThickRedPen	= CreatePen( PS_SOLID, 2, colors[red] );
	FhThickGreenPen	= CreatePen( PS_SOLID, 2, colors[green] );
	FhThickBluePen	= CreatePen( PS_SOLID, 2, colors[blue] );

	FhRedBrush		= CreateSolidBrush( colors[red] );
	FhGreenBrush	= CreateSolidBrush( colors[green] );
	FhBlueBrush		= CreateSolidBrush( colors[blue] );
	FhGrayBrush		= CreateSolidBrush( colors[grey] );
	FhBrownBrush	= CreateSolidBrush( colors[brown] );
	FhYellowBrush	= CreateSolidBrush( colors[yellow] );
	FhOrangeBrush	= CreateSolidBrush( colors[orange] );

	FhLightBlueBrush= CreateSolidBrush( colors[light_blue] );
	FhDarkGreenBrush= CreateSolidBrush( colors[dark_green] );
}

//----------------------------------------------
TCgdi::~TCgdi( void )
{
	DeleteObject(FhBlackPen);
	DeleteObject(FhWhitePen);
	DeleteObject(FhRedPen);
	DeleteObject(FhGreenPen);
	DeleteObject(FhBluePen);
	DeleteObject(FhGrayPen);
	DeleteObject(FhPinkPen);
	DeleteObject(FhOrangePen);
	DeleteObject(FhYellowPen);
	DeleteObject(FhPurplePen);
	DeleteObject(FhBrownPen);

	DeleteObject(FhDarkGreenPen);
	DeleteObject(FhLightBluePen);
	DeleteObject(FhLightGrayPen);
	DeleteObject(FhLightPinkPen);

	DeleteObject(FhThickBlackPen);
	DeleteObject(FhThickWhitePen);
	DeleteObject(FhThickRedPen);
	DeleteObject(FhThickGreenPen);
	DeleteObject(FhThickBluePen);
	
	DeleteObject(FhRedBrush);
	DeleteObject(FhGreenBrush);
	DeleteObject(FhBlueBrush);
	DeleteObject(FhGrayBrush);
	DeleteObject(FhBrownBrush);
	DeleteObject(FhYellowBrush);
	DeleteObject(FhOrangeBrush);
	
	DeleteObject(FhLightBlueBrush);
	DeleteObject(FhDarkGreenBrush); 
}