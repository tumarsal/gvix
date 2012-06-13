// TestGDAL_ogr_console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "gdal.h"
#include "gdal_alg.h"
#include "ogr_srs_api.h"
#include "cpl_string.h"
#include "cpl_conv.h"
#include "cpl_multiproc.h"

#include "gdal_priv.h"

#include "ogrsf_frmts.h"


int _tmain(int argc, _TCHAR* argv[])
{
	//Initially it is necessary to register all the format drivers that are desired. 
	// This is normally accomplished by calling OGRRegisterAll() which registers all format drivers built into GDAL/OGR.
	OGRRegisterAll();
    
	OGRDataSource       *poDS;

    poDS = OGRSFDriverRegistrar::Open( "point.shp", FALSE );
    if( poDS == NULL )
    {
        printf( "Open failed.\n" );
        exit( 1 );
    }

	OGRLayer  *poLayer;

    poLayer = poDS->GetLayerByName( "point" );

	return 0;
}

