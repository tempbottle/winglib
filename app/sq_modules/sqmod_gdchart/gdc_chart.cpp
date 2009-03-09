// gdc_chart.cpp

#include "stdafx.h"

#include "gdc.h"
#include "gdchart.h"

// !!! Never call this function !!!
// This is just a dummy function to pull in these function definitions
extern "C" void dummy_to_import_symbols()
{
	out_err( 0, 0, 0, 0, 0, 0 );
}

int
out_graph( short		GIFWIDTH,		/* no check for a gif that's too small to fit */
		   short		GIFHEIGHT,		/* needed info (labels, etc), could core dump */
		   FILE			*gif_fptr,		// open file pointer (gif out)
		   GDC_CHART_T	type,
		   int			num_points,     // points along x axis (even iterval)
										//	all arrays dependant on this
		   char			*xlbl[],		// array of xlabels
		   int			num_sets,
						... );

CGdcChart::CGdcChart()
{
}

CGdcChart::~CGdcChart()
{
}

#define MAX_DIMENSIONS		32
int CGdcChart::SaveChart(	const sqbind::stdString &x_sFile,
							const sqbind::stdString &x_sParams,
							const sqbind::stdString &x_sLabels,
							const sqbind::stdString &x_sData1,
							const sqbind::stdString &x_sData2 )
{
	sqbind::CSqMulti mLabels( x_sLabels.c_str() ); // = (sqbind::CSqMulti*)&x_mLabels;
	sqbind::CSqMulti mData1( x_sData1.c_str() ); // = (sqbind::CSqMulti*)&x_mData1;
	sqbind::CSqMulti mData2( x_sData2.c_str() ); // = (sqbind::CSqMulti*)&x_mData2;
	sqbind::CSqMulti mParams( x_sParams.c_str() );

	int nDimensions = 1;
	oex::oexCSTR szLabels[ MAX_DIMENSIONS ];
	int nDataPts = mLabels.size();
	if ( !nDataPts )
		return -1;

	if ( !mData1.size() )
		return -2;

	if ( mData2.size() >= nDataPts )
		nDimensions++;

	// Copy label pointers
	int i = 0;
	for ( sqbind::CSqMulti::iterator it = mLabels.begin();
		  i < nDataPts && mLabels.end() != it; it++, i++ )
		szLabels[ i++ ] = it->second.str().c_str();

	oex::TMem< float > dat[ 8 ];
	if ( 1 >= nDimensions )
	{
		if ( !dat[ 0 ].OexNew( nDataPts ).Ptr() )
			return -2;
		dat[ 0 ].Zero();

		int i = 0;
		for ( sqbind::CSqMulti::iterator it = mData1.begin();
			  i < nDataPts && mData1.end() != it; it++, i++ )
		{
			dat[ i ][ i ] = oexStrToFloat( it->second.str().c_str() );

		} // end for

	} // end if

	FILE *fd = fopen( x_sFile.c_str(), "wb" );

	out_graph( oexStrToLong( mParams[ "width" ].str().c_str() ),
	   		   oexStrToLong( mParams[ "height" ].str().c_str() ),
			   fd,
			   (GDC_CHART_T)oexStrToLong( mParams[ "type" ].str().c_str() ),
			   nDataPts, (char**)szLabels, nDimensions,
			   dat[ 0 ].Ptr(), dat[ 1 ].Ptr() );

	fclose( fd );

                              /* ----- call the lib ----- * /
    out_graph( x_nWidth, x_nHeight,
               outgif,        /* FILE*       open FILE pointer * /
               GDC_3DBAR,     /* GDC_CHART_T chart type * /
               6,             /* int         number of points per data set * /
               t,             /* char*[]     array of X labels * /
               2,             /* int         number of data sets * /
               a,             /* float[]     data set 1 * /
               b );           /*  ...        data set n * /

	fclose( outgif );



/*

    /* ----- set some data ----- * /
    float   a[6]  = { 0.5, 0.09, 0.6, 0.85, 0.0, 0.90 },
            b[6]  = { 1.9, 1.3,  0.6, 0.75, 0.1, 2.0 };
    /* ----- X labels ----- * /
    char    *t[6] = { "Chicago", "New York", "L.A.", "Atlanta", "Paris, MD\n(USA) ", "London" };
    /* ----- data set colors (RGB) ----- * /
    unsigned long   sc[2]    = { 0xFF8080, 0x8080FF };

    GDC_BGColor   = 0xFFFFFFL;                  /* backgound color (white) * /
    GDC_LineColor = 0x000000L;                  /* line color      (black)  /
    GDC_SetColor  = &(sc[0]);                   /* assign set colors * /

	GDC_stack_type = GDC_STACK_BESIDE;
//    printf( "Content-Type: image/gif\n\n" );    /* tell browser type * /

	FILE *outgif = fopen( x_sFile.c_str(), "wb" );	/* rem: test open() fail * /

                              /* ----- call the lib ----- * /
    out_graph( x_nWidth, x_nHeight,
               outgif,        /* FILE*       open FILE pointer * /
               GDC_3DBAR,     /* GDC_CHART_T chart type * /
               6,             /* int         number of points per data set * /
               t,             /* char*[]     array of X labels * /
               2,             /* int         number of data sets * /
               a,             /* float[]     data set 1 * /
               b );           /*  ...        data set n * /

	fclose( outgif );


/*

	/* set some sample data points * /
	float	h[12]  = {	17.8,  17.1,  17.3,  GDC_NOVALUE,  17.2,  17.1,
						17.3,  17.3,  17.3,  17.1,         17.5,  17.4 };

	float	c[12]  =  { 17.0,  16.8,  16.9,  GDC_NOVALUE,  16.9,  16.8,
					    17.2,  16.8,  17.0,  16.9,         16.4,  16.1 };

	float	l[12]  = {  16.8,  16.8,  16.7,  GDC_NOVALUE,  16.5,  16.0,
						16.1,  16.8,  16.5,  16.9,         16.2,  16.0 };

	float	v[12]  = {  150.0, 100.0, 340.0,  GDC_NOVALUE, 999.0, 390.0,
						420.0, 150.0, 100.0,  340.0,       1590.0, 700.0 };
	char	*t[12] = {	"May", "Jun", "Jul",  "Aug",       "Sep",  "Oct",
						"Nov", "Dec", "Jan", "Feb",        "Mar",  "Apr" };

//	/* set color RGB as ulong array */
//	unsigned long	setcolor[3]    = { 0xC0C0FF, 0xFF4040, 0xFFFFFF };

	GDC_ANNOTATION_T	anno;

	/* need an open FILE pointer  - can be stdout * /
	FILE				*outgif1 = fopen( "g2.gif", "wb" );	/* rem: test open() fail * /


	anno.color = 0x00FF00;
	strncpy( anno.note, "Did Not\nTrade", MAX_NOTE_LEN );	/* don't exceed MAX_NOTE_LEN * /
	anno.point = 3;											/* first is 0 * /
	GDC_annotation_font = GDC_TINY;
	GDC_annotation = &anno;									/* set annote option * /

	GDC_HLC_style = (GDC_HLC_STYLE_T)( GDC_HLC_I_CAP | GDC_HLC_CLOSE_CONNECTED );
	GDC_HLC_cap_width = 45;

	GDC_bar_width     = 75;									/* % * /

//	GDC_BGImage = "W.gif";

	GDC_title = "Widget Corp.";
	GDC_ytitle = "Price ($)";
	GDC_ytitle2 = "Volume (K)";
	GDC_ytitle_size = GDC_SMALL;
	GDC_VolColor = 0x4040FFL;								/* aka combo * /
	GDC_3d_depth  = 4.0;									/* % entire gif * /

//	GDC_SetColor  = setcolor;								/* see README * /
	GDC_PlotColor = 0xFFFFFF;
	GDC_grid = FALSE;

//	GDC_xtitle="fy.1998";

//	fprintf( stdout, "Content-Type: image/gif\n\n" );		/* rem: for web use * /
															/* finally: make the call * /
	out_graph( x_nWidth, x_nHeight,									// overall width, height
			   	   outgif1,										// open FILE pointer
				   GDC_COMBO_HLC_AREA,							// chart type
				   12,											// number of points
				   t,											// X axis label array
				   1,											// number of sets (see README)
				   h,											// set 1 (high)
				   l,											// low
				   c,											// close
				   v );											// combo/volume

	fclose( outgif1 );

*/
}
