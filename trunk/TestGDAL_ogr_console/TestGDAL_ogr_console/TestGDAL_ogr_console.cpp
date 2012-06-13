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
	// http://www.gdal.org/ogr/ogr_apitut.html

	//Initially it is necessary to register all the format drivers that are desired. 
	// This is normally accomplished by calling OGRRegisterAll() which registers all format drivers built into GDAL/OGR.
	OGRRegisterAll();
    
	OGRDataSource       *poDS;

	// Next we need to open the input OGR datasource. 
	//Datasources can be files, RDBMSes or directories full of files.
	//However, the datasource name is always a single string. 
	//The second argument (FALSE) tells the OGRSFDriverRegistrar::Open() method that we don't require update access. 
	//On failure NULL is returned, and we report an error.
    poDS = OGRSFDriverRegistrar::Open( "point.shp", FALSE );
    if( poDS == NULL )
    {
        printf( "Open failed.\n" );
        exit( 1 );
    }

	// An OGRDataSource can potentially have many layers associated with it. 
	//The number of layers available can be queried with OGRDataSource::GetLayerCount() 
	//and individual layers fetched by index using OGRDataSource::GetLayer(). However, we wil just fetch the layer by name.
	OGRLayer  *poLayer;

    poLayer = poDS->GetLayerByName( "point" );

	// Now we want to start reading features from the layer. 
	//Before we start we could assign an attribute or spatial filter to 
	//the layer to restrict the set of feature we get back, but for now we are interested in getting all features.

	//While it isn't strictly necessary in this circumstance since we are starting fresh with the layer, 
	//it is often wise to call OGRLayer::ResetReading() to ensure we are starting at the beginning of the layer. 
	//We iterate through all the features in the layer using OGRLayer::GetNextFeature(). It will return NULL when we run out of features.
    OGRFeature *poFeature;

    poLayer->ResetReading();
    while( (poFeature = poLayer->GetNextFeature()) != NULL )
    {
		//In order to dump all the attribute fields of the feature, it is helpful to get the OGRFeatureDefn. 
		//This is an object, associated with the layer, containing the definitions of all the fields.
        OGRFeatureDefn *poFDefn = poLayer->GetLayerDefn();
        int iField;		

		//We loop over all the fields, and fetch and report the attributes based on their type.
        for( iField = 0; iField < poFDefn->GetFieldCount(); iField++ )
        {
            OGRFieldDefn *poFieldDefn = poFDefn->GetFieldDefn( iField );

			if( poFieldDefn->GetType() == OFTInteger ){				
				int fieldAsInteger = poFeature->GetFieldAsInteger( iField );
				//sprintf(fieldAsInteger, "%d,",  poFeature->GetFieldAsInteger( iField ));

				printf( "%d,", poFeature->GetFieldAsInteger( iField ) );
			}

			else if( poFieldDefn->GetType() == OFTReal ){			
				float fp = poFeature->GetFieldAsDouble(iField);
				//sprintf(fp, "%.3f,",  poFeature->GetFieldAsDouble(iField)  );

                printf( "%.3f,", poFeature->GetFieldAsDouble(iField) );
			}

			else if( poFieldDefn->GetType() == OFTString ){
				char   fieldAsString[1024];
				if(sizeof(poFeature->GetFieldAsString(iField))<=1023)
					sprintf(fieldAsString, "%s", poFeature->GetFieldAsString(iField) );

                printf( "%s,", poFeature->GetFieldAsString(iField) );
			}

			else{
				char   fieldAsString[1024];
				if(sizeof(poFeature->GetFieldAsString(iField))<=1023)
					sprintf(fieldAsString, "%s", poFeature->GetFieldAsString(iField) );

                printf( "%s,", poFeature->GetFieldAsString(iField) );
			}
        }

		// There are a few more field types than those explicitly handled above, but a reasonable 
		//representation of them can be fetched with the OGRFeature::GetFieldAsString() method. 
		//In fact we could shorten the above by using OGRFeature::GetFieldAsString() for all the types.

		// Next we want to extract the geometry from the feature, and write out the point geometry x and y. 
		//Geometries are returned as a generic OGRGeometry pointer. We then determine the specific geometry type, 
		//and if it is a point, we cast it to point and operate on it. If it is something else we write placeholders.
		OGRGeometry *poGeometry;

        poGeometry = poFeature->GetGeometryRef();
        if( poGeometry != NULL 
            && wkbFlatten(poGeometry->getGeometryType()) == wkbPoint )
        {
            OGRPoint *poPoint = (OGRPoint *) poGeometry;

            printf( "%.3f,%3.f\n", poPoint->getX(), poPoint->getY() );
        }
        else
        {
            printf( "no point geometry\n" );
        } 
	}

	return 0;
}

