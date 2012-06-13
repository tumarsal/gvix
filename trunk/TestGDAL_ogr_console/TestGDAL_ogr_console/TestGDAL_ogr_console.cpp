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

			//The wkbFlatten() macro is used above to convert the type for a wkbPoint25D 
			//(a point with a z coordinate) into the base 2D geometry type code (wkbPoint). 
			//For each 2D geometry type there is a corresponding 2.5D type code. 
			//The 2D and 2.5D geometry cases are handled by the same C++ class, so our code will handle 2D or 3D cases properly.
        {
            OGRPoint *poPoint = (OGRPoint *) poGeometry;

            printf( "%.3f,%3.f\n", poPoint->getX(), poPoint->getY() );
        }
        else
        {
            printf( "no point geometry\n" );
        } 

		// Note that OGRFeature::GetGeometryRef() returns a pointer to the internal geometry owned by the OGRFeature.
		// There we don't actually deleted the return geometry. However, the OGRLayer::GetNextFeature() method 
		// returns a copy of the feature that is now owned by us. So at the end of use we must free the feature.
		//We could just "delete" it, but this can cause problems in windows builds where the GDAL DLL has a different "heap" from the main program. 
		//To be on the safe side we use a GDAL function to delete the feature.
		OGRFeature::DestroyFeature( poFeature );

	}

	// The OGRLayer returned by OGRDataSource::GetLayerByName() is also 
	// a reference to an internal layer owned by the OGRDataSource so we don't need to delete it. 
	// But we do need to delete the datasource in order to close the input file. 
	// Once again we do this with a custom delete method to avoid special win32 heap issus.
	OGRDataSource::DestroyDataSource( poDS );

	return 0;
}

