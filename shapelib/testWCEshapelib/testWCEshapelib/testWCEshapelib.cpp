// testWCEshapelib.cpp : Defines the entry point for the application.
//

// GDI Support for Windows CE
// http://msdn.microsoft.com/en-us/library/ms903434.aspx
/*

Windows CE GDI does not support the following features:

    Transformation functions of coordinate space, such as SetMapMode, GetMapMode, SetViewportExt, and SetWindowExt. 
	Coordinate space is equivalent to device space.
    World Transform API.
    MoveTo and LineTo functions.

*/

#include "stdafx.h"
#include "testWCEshapelib.h"

// VSMathLib - Very Simple Matrix Library
// http://www.lighthouse3d.com/very-simple-libs/vsml/


//Program to Parse ESRI Shapefile and render it in OpenGL
//Author : Dhulipudi Durga Prasad
//Contact: dgplinux@yahoo.com
//Libraries Used: Shapelib ,OpenGL

//#include "GLES/glutes.h"
////#include <GL/glut.h>
////#include <stdlib.h>
// 
////#include "shapelib\shapefil.h"
//#include "shapefil.h"
//
//#include <vector>

using namespace std;

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE			g_hInst;			// current instance
HWND				g_hWndMenuBar;		// menu bar handle

// Forward declarations of functions included in this code module:
ATOM			MyRegisterClass(HINSTANCE, LPTSTR);
BOOL			InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

/// number of settable matrices
#define COUNT_MATRICES 4

/// Enumeration of the matrix types
///* MatrixMode */
//#define GL_MODELVIEW                      0x1700
//#define GL_PROJECTION                     0x1701
//#define GL_TEXTURE                        0x1702
enum MatrixTypes{
        MODEL,
        VIEW,
        PROJECTION,  // GL_PROJECTION
        AUX0,
        AUX1,
        AUX2,
        AUX3
} ;

/// The storage for matrices
float mMatrix[COUNT_MATRICES][16];
//float mCompMatrix[COUNT_COMPUTED_MATRICES][16];

void
multMatrix(MatrixTypes aType, float *aMatrix);

/** Similar to glOrtho and gluOrtho2D (just leave the
  * last two params blank).
  *
  * \param left,right coordinates for the left and right vertical
  * clipping planes
  * \param bottom,top coordinates for the bottom and top horizontal
  * clipping planes
  * \param nearp,farp distance to the near and far planes
*/
void glOrtho(float left, float right, float bottom, float top,
                float nearp=-1.0f, float farp=1.0f);

// sets the square matrix mat to the identity matrix,
// size refers to the number of rows (or columns)
void
setIdentityMatrix( float *mat, int size);

// Compute res = M * point
void
multMatrixPoint(MatrixTypes aType, float *point, float *res);
//multMatrixPoint(float *point, float *res);

typedef struct MyPoint2D
{
 double dX;
 double dY;
 
}MyPoint2D;
 
//Holds Coordinates of Point Shapefile
vector<MyPoint2D> vPoints;
 


typedef struct MyLineString2D
{
 vector<MyPoint2D> vPointList;
 
}MyLineString2D;

//Holds Coordinates of Line Shapefile
vector<MyLineString2D> vLines;
  


typedef struct MyPolygon2D
{
 vector<MyPoint2D> vPointList;
 
}MyPolygon2D;
//Holds Coordinates of Polygon Shapefile 
vector<MyPolygon2D> vPolygons;
  



typedef struct SBoundingBox
{
 float fMaxX;
 float fMaxY;
 float fMinX;
 float fMinY;
 
}SBoundingBox;
//Bounding Box of Shapefile 
SBoundingBox sBoundingBox;

//Function to Open Shapefile and parse the info 
void OpenShapeFile(char* fileName)
{
           
    SHPHandle hSHP=SHPOpen(fileName, "rb" );


	//Read Bounding Box of Shapefile
    sBoundingBox.fMaxX=(float)hSHP->adBoundsMax[0];
    sBoundingBox.fMaxY=(float)hSHP->adBoundsMax[1];

    sBoundingBox.fMinX=(float)hSHP->adBoundsMin[0];
    sBoundingBox.fMinY=(float)hSHP->adBoundsMin[1];

    if(hSHP == NULL) return;

	//Point Shapefile
    if(hSHP->nShapeType == SHPT_POINT)
    {
        SHPObject *psShape;
        for(int i=0;i<hSHP->nRecords;i++)
        {
            psShape = SHPReadObject(hSHP, i);

            double fX = psShape->padfX[0];
            double fY = -psShape->padfY[0];

            //Plot these points
            MyPoint2D pt;
            pt.dX=fX;
            pt.dY=-fY;
            vPoints.push_back(pt);
        }
    }


	//Line Shapefile
    else if(hSHP->nShapeType == SHPT_ARC)
    {
        SHPObject *psShape;
	    for(int i=0;i<hSHP->nRecords;i++)
        {
            psShape = SHPReadObject(hSHP, i);
            vector<MyPoint2D> tempPointArray;

            for(int j=0;j<psShape->nVertices;j++)
            {
				double fX = psShape->padfX[j];
				double fY = psShape->padfY[j];
				MyPoint2D pt;
				pt.dX=fX;
				pt.dY=fY;
				tempPointArray.push_back(pt);
            }
           
			MyLineString2D linestring;
            linestring.vPointList=tempPointArray;
            vLines.push_back(linestring);
           
        }
    }

 	//Polygon Shapefile
    if(hSHP->nShapeType == SHPT_POLYGON)
    {
		SHPObject *psShape;
		for(int i=0;i<hSHP->nRecords;i++)
		{
			psShape = SHPReadObject(hSHP, i);
      		vector<MyPoint2D> tempPointArray;
     
			for(int j=0;j<psShape->nVertices;j++)
			{
				double fX = psShape->padfX[j];
				double fY = psShape->padfY[j];
				MyPoint2D pt;
				pt.dX=fX;
				pt.dY=fY;
      			tempPointArray.push_back(pt);
			}
			MyPolygon2D polygon;
			polygon.vPointList=tempPointArray;
			vPolygons.push_back(polygon);
		}

    }
  
}



void initializeGL()
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
//	glClearColor (1.0, 1.0, 1.0, 1.0);
	glShadeModel (GL_FLAT);
	glEnable (GL_LINE_SMOOTH);
	glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
	
	glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);  



	//Assign Default Map Bounds to glOrtho
	sBoundingBox.fMaxX=180.0f;
	sBoundingBox.fMaxY=90.0f;
	sBoundingBox.fMinX=-180.0f;
	sBoundingBox.fMinY=-90.0f;
}
 
void resizeGL(int w, int h)
{
	if(h<=0) h=1 ;

	//  glViewport defines the area of the window you are using into which you want to draw. 
	// Here is how to tell OpenGL that you want to use your entire window to draw in: 
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();

	//Assign Bounding Box Coordinates of Shapefile to glOrtho()
	// 06-21-2012 Implemented local function glOrtho by Gerson in replacement because of lack in OpenGL ES for WinCE / PPC / WinMob
	// Original implementation is at OpenGL Win32/x86 for Windows at GL.h in C:\Program Files\Microsoft SDKs\Windows\v6.0A\Include\gl
	//glOrtho(sBoundingBox.fMinX, sBoundingBox.fMaxX,sBoundingBox.fMinY,sBoundingBox.fMaxY,-1,1);
	glOrthof(sBoundingBox.fMinX, sBoundingBox.fMaxX,sBoundingBox.fMinY,sBoundingBox.fMaxY,-1,1);

	// OpenGL ES 2: Who stole all my functions? 
	// http://igamedev.posterous.com/opengl-es-2-who-stole-all-my-functions
	// But isn't that a lot of extra work?
	// Yup, sure is. Until you've built up some reusable code, it's a ton of extra work. 
	// Hopefully as I write these tutorials you'll get some code that you can use.

	// http://forums.macrumors.com/showthread.php?t=593661
	//So... most of the functions don't work. glOrtho, glBegin, glEnd, glVertex3f (and 2f), all got errors. 
	//What would be the proper OpenGL ES functions ...

	// Here, totally free for everyone, is my current graphics engine 
	// http://www.khronos.org/message_boards/viewtopic.php?f=9&t=3140

	// http://www.khronos.org/opengles/sdk/1.1/docs/man/

	// implementation:
	// http://www.khronos.org/opengles/documentation/opengles1_0/html/glOrtho.html

	// http://stackoverflow.com/questions/7131037/how-do-you-implement-glortho-for-opengles-2-0-with-or-without-tx-ty-tz-values-f
	// implement my own glOtho function

	// The glOrtho function multiplies the current matrix by an orthographic matrix.
	// http://msdn.microsoft.com/en-us/library/windows/desktop/dd373965%28v=vs.85%29.aspx

	//http://stackoverflow.com/questions/7131037/how-do-you-implement-glortho-for-opengles-2-0-with-or-without-tx-ty-tz-values-f

	glMatrixMode(GL_MODELVIEW);
}

void draw()
{
  
	glClear (GL_COLOR_BUFFER_BIT);

	// 06-21-2012 by Gerson This function of OpenGL is not supported by mobileplatforms
	//	glColor3f (0.0, 0.0, 1.0);
	// The alpha channel is normally used as an opacity channel. 
	//If a pixel has a value of 0% in its alpha channel, 
	//it is fully transparent (and, thus, invisible), 
	//whereas a value of 100% in the alpha channel gives a fully opaque pixel (traditional digital images)
	glColor4x(0, 0, 1, 1); 

	glLoadIdentity ();
	
	//Render Point Shapefile
//	glColor3f (0.0, 0.0, 1.0);
	glColor4x(0, 0, 1, 1); 

	glEnable(GL_POINT_SMOOTH) ;
	glPointSize(5.0);

	//Two of the more significant differences between OpenGL ES and OpenGL are the removal of the glBegin ... 
	//glEnd calling semantics for primitive rendering (in favor of vertex arrays) and the introduction 
	//of fixed-point data types for vertex coordinates and attributes to better support the 
	//computational abilities of embedded processors, which often lack a floating point unit (FPU).

	// The glBegin and glend functions delimit the vertices of a primitive or a group of like primitives.
	//glBegin(GL_POINTS);

	GLfloat vPoints_OpenGLMobile[250];

	int j=0;
	
	for(int i=0; i < (int)vPoints.size();i++)
	{
		// Specifies a vertex.
		/*
		The glVertex function commands are used within glBegin/glEnd pairs to specify point, line, and polygon vertices. 
		The current color, normal, and texture coordinates are associated with the vertex when glVertex is called. 
		When only x and y are specified, z defaults to 0.0 and w defaults to 1.0. 
		When x, y, and z are specified, w defaults to 1.0. 
		Invoking glVertex outside of a glBegin/glEnd pair results in undefined behavior. 
		*/
//		glVertex2f(vPoints[i].dX,vPoints[i].dY);

		// 06-21-2012 by Gerson - porting OpenGL code to OpenGL-ES for MS Mobile platforms (WCE, PPC and Win Mobile)
		vPoints_OpenGLMobile[j++]=vPoints[i].dX;
		vPoints_OpenGLMobile[j++]=vPoints[i].dY;

		// 06-21-2012 by Gerson - END of porting OpenGL code to OpenGL-ES for MS Mobile platforms (WCE, PPC and Win Mobile)

	}

	// 06-21-2012 by Gerson - porting OpenGL code to OpenGL-ES for MS Mobile platforms (WCE, PPC and Win Mobile)
	//http://stackoverflow.com/questions/835903/opengl-to-opengl-es-changing-color-of-triangles-in-a-strip
	//glEnableClientState (GL_VERTEX_ARRAY);
	//glEnableClientState (GL_COLOR_ARRAY); // enables the color-array.

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, vPoints_OpenGLMobile); // set your vertex-coordinates here..
	//glColorPointer (...   // set your color-coordinates here..
	glDrawArrays(GL_TRIANGLE_FAN,0,(int)vPoints.size());
	glDisableClientState(GL_VERTEX_ARRAY);
	
//	glEnd();
	
	//Render Line Shapefile
//	glColor3f (0.0, 1.0, 0.0);
	for( int i=0; i < (int)vLines.size();i++)
	{
		
//		glBegin(GL_LINE_STRIP);
		for(int j=0; j < (int)vLines[i].vPointList.size();j++)
		{
//		  glVertex2f(vLines[i].vPointList[j].dX,vLines[i].vPointList[j].dY);
	
		}
		
//		glEnd();
	}
	
	//Render Polygon Shapefile
//	glColor3f(1.0,0.0, 0.0);
	for(int i=0; i < (int)vPolygons.size();i++)
	{
//		glBegin(GL_LINE_LOOP);
		for(int j=0; j < (int)vPolygons[i].vPointList.size();j++)
		{
//			glVertex2f(vPolygons[i].vPointList[j].dX,vPolygons[i].vPointList[j].dY);
		}
		
//		glEnd();
	}
 
   glFlush();
}
 
void paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw();
}


int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPTSTR    lpCmdLine,
                   int       nCmdShow)
{
	MSG msg;

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	HACCEL hAccelTable;
	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TESTWCESHAPELIB));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
ATOM MyRegisterClass(HINSTANCE hInstance, LPTSTR szWindowClass)
{
	WNDCLASS wc;

	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = WndProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInstance;
	wc.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TESTWCESHAPELIB));
	wc.hCursor       = 0;
	wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName  = 0;
	wc.lpszClassName = szWindowClass;

	return RegisterClass(&wc);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    HWND hWnd;
    TCHAR szTitle[MAX_LOADSTRING];		// title bar text
    TCHAR szWindowClass[MAX_LOADSTRING];	// main window class name

    g_hInst = hInstance; // Store instance handle in our global variable

    // SHInitExtraControls should be called once during your application's initialization to initialize any
    // of the device specific controls such as CAPEDIT and SIPPREF.
    SHInitExtraControls();

    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING); 
    LoadString(hInstance, IDC_TESTWCESHAPELIB, szWindowClass, MAX_LOADSTRING);

    //If it is already running, then focus on the window, and exit
    hWnd = FindWindow(szWindowClass, szTitle);	
    if (hWnd) 
    {
        // set focus to foremost child window
        // The "| 0x00000001" is used to bring any owned windows to the foreground and
        // activate them.
        SetForegroundWindow((HWND)((ULONG) hWnd | 0x00000001));
        return 0;
    } 

    if (!MyRegisterClass(hInstance, szWindowClass))
    {
    	return FALSE;
    }

    hWnd = CreateWindow(szWindowClass, szTitle, WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

    if (!hWnd)
    {
        return FALSE;
    }

    // When the main window is created using CW_USEDEFAULT the height of the menubar (if one
    // is created is not taken into account). So we resize the window after creating it
    // if a menubar is present
    if (g_hWndMenuBar)
    {
        RECT rc;
        RECT rcMenuBar;

        GetWindowRect(hWnd, &rc);
        GetWindowRect(g_hWndMenuBar, &rcMenuBar);
        rc.bottom -= (rcMenuBar.bottom - rcMenuBar.top);
		
        MoveWindow(hWnd, rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top, FALSE);
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);


    return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId, wmEvent;
    PAINTSTRUCT ps;
    HDC hdc;

	wchar_t  temp[] = L"SHP Viewer";

    static SHACTIVATEINFO s_sai;
	
    switch (message) 
    {
        case WM_COMMAND:
            wmId    = LOWORD(wParam); 
            wmEvent = HIWORD(wParam); 

            // Parse the menu selections:
            switch (wmId)
            {
                case IDM_HELP_ABOUT:
                    DialogBox(g_hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, About);
                    break;
                case IDM_OK:
                    SendMessage (hWnd, WM_CLOSE, 0, 0);				
                    break;
				case ID_HELP_SHPVIEWER:
					MessageBox(NULL, temp, _T(""), MB_OK);

					int argc; char** argv;
					//glutInit(&argc, argv);
					glutInitDisplayMode (GLUT_SINGLE| GLUT_RGB);
					glutInitWindowSize (600,600);
					glutCreateWindow ("Render Shapefiles");
					initializeGL();

					//DialogBox(g_hInst, (LPCTSTR)IDD_SHP_VIEWER, hWnd, About);
					break;
                default:
                    return DefWindowProc(hWnd, message, wParam, lParam);
            }
            break;
        case WM_CREATE:
            SHMENUBARINFO mbi;

            memset(&mbi, 0, sizeof(SHMENUBARINFO));
            mbi.cbSize     = sizeof(SHMENUBARINFO);
            mbi.hwndParent = hWnd;
            mbi.nToolBarId = IDR_MENU;
            mbi.hInstRes   = g_hInst;

            if (!SHCreateMenuBar(&mbi)) 
            {
                g_hWndMenuBar = NULL;
            }
            else
            {
                g_hWndMenuBar = mbi.hwndMB;
            }

            // Initialize the shell activate info structure
            memset(&s_sai, 0, sizeof (s_sai));
            s_sai.cbSize = sizeof (s_sai);
            break;
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            
            // TODO: Add any drawing code here...
            
            EndPaint(hWnd, &ps);
            break;
        case WM_DESTROY:
            CommandBar_Destroy(g_hWndMenuBar);
            PostQuitMessage(0);
            break;

        case WM_ACTIVATE:
            // Notify shell of our activate message
            SHHandleWMActivate(hWnd, wParam, lParam, &s_sai, FALSE);
            break;
        case WM_SETTINGCHANGE:
            SHHandleWMSettingChange(hWnd, wParam, lParam, &s_sai);
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_INITDIALOG:
            {
                // Create a Done button and size it.  
                SHINITDLGINFO shidi;
                shidi.dwMask = SHIDIM_FLAGS;
                shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN | SHIDIF_EMPTYMENU;
                shidi.hDlg = hDlg;
                SHInitDialog(&shidi);
            }
            return (INT_PTR)TRUE;

        case WM_COMMAND:
            if (LOWORD(wParam) == IDOK)
            {
                EndDialog(hDlg, LOWORD(wParam));
                return TRUE;
            }
            break;

        case WM_CLOSE:
            EndDialog(hDlg, message);
            return TRUE;

    }
    return (INT_PTR)FALSE;
}

void glOrtho(float left, float right,
            float bottom, float top,
            float nearp, float farp)
{
    float m[16];
 
    setIdentityMatrix(m,4);
 
    m[0 * 4 + 0] = 2 / (right - left);
    m[1 * 4 + 1] = 2 / (top - bottom);
    m[2 * 4 + 2] = -2 / (farp - nearp);
    m[3 * 4 + 0] = -(right + left) / (right - left);
    m[3 * 4 + 1] = -(top + bottom) / (top - bottom);
    m[3 * 4 + 2] = -(farp + nearp) / (farp - nearp);
 
    multMatrix(PROJECTION, m);
}

// -----------------------------------------------------
//                      AUX functions
// -----------------------------------------------------
 
// sets the square matrix mat to the identity matrix,
// size refers to the number of rows (or columns)
void
setIdentityMatrix( float *mat, int size) {
 
    // fill matrix with 0s
    for (int i = 0; i < size * size; ++i)
            mat[i] = 0.0f;
 
    // fill diagonal with 1s
    for (int i = 0; i < size; ++i)
        mat[i + i * size] = 1.0f;
}

// Compute res = M * point
void
multMatrixPoint(MatrixTypes aType, float *point, float *res) {
//multMatrixPoint(float *mat, float *point, float *res){
 
    for (int i = 0; i < 4; ++i) {
 
        res[i] = 0.0f;
 
        for (int j = 0; j < 4; j++) {
 
            res[i] += point[j] * mMatrix[aType][j*4 + i];
        }
    }
}


// glMultMatrix implementation
void
multMatrix(MatrixTypes aType, float *aMatrix)
{
 
    float *a, *b, res[16];
    a = mMatrix[aType];
    b = aMatrix;
 
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            res[j*4 + i] = 0.0f;
            for (int k = 0; k < 4; ++k) {
                res[j*4 + i] += a[k*4 + i] * b[j*4 + k];
            }
        }
    }
    memcpy(mMatrix[aType], res, 16 * sizeof(float));
}

//
//void ES2Renderer::_applyOrtho(float left, float right,float bottom, float top,float near, float far) const{ 
//
//        float a = 2.0f / (right - left);
//        float b = 2.0f / (top - bottom);
//        float c = -2.0f / (far - near);
//
//        float tx = - (right + left)/(right - left);
//        float ty = - (top + bottom)/(top - bottom);
//        float tz = - (far + near)/(far - near);
//
//        float ortho[16] = {
//            a, 0, 0, tx,
//            0, b, 0, ty,
//            0, 0, c, tz,
//            0, 0, 0, 1
//        };
//
//
//        GLint projectionUniform = glGetUniformLocation(_shaderProgram, "Projection");
//        glUniformMatrix4fv(projectionUniform, 1, 0, &ortho[0]);
//
//}
//
//void ES2Renderer::_renderScene()const{
//    GLfloat vVertices[] = {
//        0.0f,  5.0f, 0.0f,  
//        -5.0f, -5.0f, 0.0f,
//        5.0f, -5.0f,  0.0f};
//
//    GLuint positionAttribute = glGetAttribLocation(_shaderProgram, "Position");
//
//    glEnableVertexAttribArray(positionAttribute);
//
//
//    glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, 0, vVertices);  
//    glDrawArrays(GL_TRIANGLES, 0, 3);       
//
//
//    glDisableVertexAttribArray(positionAttribute);
//
//}


// http://stackoverflow.com/questions/7131037/how-do-you-implement-glortho-for-opengles-2-0-with-or-without-tx-ty-tz-values-f
// implement my own glOtho function
  

/*

http://www.gamedev.net/topic/576574-opengl-to-opengl-es-code/

Hello
how would be translated this opengl code:


glBegin(GL_QUADS);

glTexCoord2f(u1, v1); glVertex2f(sx, sy);
glTexCoord2f(u2, v1); glVertex2f(sx+sw, sy);
glTexCoord2f(u2, v2); glVertex2f(sx+sw, sy+sh);
glTexCoord2f(u1, v2); glVertex2f(sx, sy+sh);

glEnd();

into OpenGL ES ? ( i know that there si no begin/end on ES)

hello
not at all, nothing to see with VBO.
i think this shall work:
GL_FLOAT vertex2[]={sx, sy, sx+sw, sy, sx+sw, sy+sh, sx, sy+sh};
GL_FLOAT textureCoor2[]={u1,v1, u2, v1, u2,v2, u1,v2};

glEnableClientState(GL_VERTEX_ARRAY);
glEnableClientState(GL_TEXTURE_COOR_ARRAY);

glVertexPointer(2, GL_FLOAT, 0, &vertex2);
glTexCoordPointer( 2, GL_FLOAT, 0, &textureCoor2);

glDrawArrays(GL_QUADS, 0, 4);

will try, it is actually better than the begin end for sure. 

Hi,

glDrawArrays and glDrawElements work fine, but VBO is another way to do it, and more efficiently.

Here is an article about it (in French s'il vous plait ;)) :

http://www.game-lab....=showtut&id=244

Bye 

The way I see the difference between glBegin/End, glDraw and VBO :

- glBegin / glEnd : A lot of function calls is needed

- glDraw : It is the same as glBegin, but reduce considerably the number of function calls

- VBO : Reduce bus activity (only if your geometry is static maybe ? because if it is dynamic you'll have to transfer data each time)

I've seen some interesting bechmarks about it, for geometry composed of hundreds of thousand (and more) polygons, you can esperate a ratio of 3 to 4 time faster.

However, for a lower count of polygons you will not see great performance differences. 

*/


/*


http://forum.nevercorner.net/viewtopic.php?id=2302

#if !defined(HAVE_GLES)
  glBegin(GL_QUADS);
  glVertex2f(-10,-10);
  glVertex2f(10,-10);
  glVertex2f(10,10);
  glVertex2f(-10,10);
  glEnd();
#else
    GLfloat q3[] = {
        -10,-10,
        10,-10,
        10,10,
        -10,10
    };
 
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, q3);
    glDrawArrays(GL_TRIANGLE_FAN,0,4);
    glDisableClientState(GL_VERTEX_ARRAY);
#endif

	*/

	// 06-21-2012 by Gerson - porting OpenGL code to OpenGL-ES for MS Mobile platforms (WCE, PPC and Win Mobile)
	//http://stackoverflow.com/questions/835903/opengl-to-opengl-es-changing-color-of-triangles-in-a-strip
	//#if !defined(HAVE_GLES)
	#if defined(HAVE_GLES)
	  glBegin(GL_QUADS);
	  glVertex2f(-10,-10);
	  glVertex2f(10,-10);
	  glVertex2f(10,10);
	  glVertex2f(-10,10);
	  glEnd();
	//#else
		GLfloat q3[] = {
			-10,-10,
			10,-10,
			10,10,
			-10,10
		};
	 
		//glEnableClientState(GL_VERTEX_ARRAY);
		//glVertexPointer(2, GL_FLOAT, 0, q3);
		//glDrawArrays(GL_TRIANGLE_FAN,0,4);
		//glDisableClientState(GL_VERTEX_ARRAY);		
		
		//glVertexPointer (...  // set your vertex-coordinates here..
		//glColorPointer (...   // set your color-coorinates here..

		//glDrawArrays (... // draw your triangles
	#endif