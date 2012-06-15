<html>
<body>
<pre>
<h1>Build Log</h1>
<h3>
--------------------Configuration: wmimgvwr - Win32 (WCE ARMV4) Debug--------------------
</h3>
<h3>Command Lines</h3>
Creating temporary file "C:\DOCUME~1\ADMINI~1\CONFIG~1\Temp\RSP5F1.tmp" with contents
[
/nologo /W3 /Zi /Od /D "DEBUG" /D "ARM" /D "_ARM_" /D "ARMV4" /D UNDER_CE=420 /D _WIN32_WCE=420 /D "WIN32_PLATFORM_PSPC=400" /D "UNICODE" /D "_UNICODE" /FR"ARMV4Dbg/" /Fp"ARMV4Dbg/wmimgvwr.pch" /Yu"stdafx.h" /Fo"ARMV4Dbg/" /Fd"ARMV4Dbg/" /MC /c 
"C:\AirScanner\Projects\WinCE\Others\Image_prj\wmimgvwr\wmimgvwr.cpp"
]
Creating command line "clarm.exe @C:\DOCUME~1\ADMINI~1\CONFIG~1\Temp\RSP5F1.tmp" 
Creating temporary file "C:\DOCUME~1\ADMINI~1\CONFIG~1\Temp\RSP5F2.tmp" with contents
[
/nologo /base:"0x00010000" /stack:0x10000,0x1000 /entry:"wWinMainCRTStartup" /incremental:yes /pdb:"ARMV4Dbg/wmimgvwr.pdb" /debug /out:"ARMV4Dbg/wmimgvwr.exe" /subsystem:windowsce,4.20 /align:"4096" /MACHINE:ARM 
.\ARMV4Dbg\globals.obj
.\ARMV4Dbg\StdAfx.obj
.\ARMV4Dbg\wmimgvwr.obj
.\ARMV4Dbg\wmimgvwrDlg.obj
.\ARMV4Dbg\wmimgvwr.res
]
Creating command line "link.exe @C:\DOCUME~1\ADMINI~1\CONFIG~1\Temp\RSP5F2.tmp"
<h3>Output Window</h3>
Compiling...
wmimgvwr.cpp
Linking...
   Creating library ARMV4Dbg/wmimgvwr.lib and object ARMV4Dbg/wmimgvwr.exp
Creating command line "bscmake.exe /nologo /o"ARMV4Dbg/wmimgvwr.bsc"  .\ARMV4Dbg\StdAfx.sbr .\ARMV4Dbg\globals.sbr .\ARMV4Dbg\wmimgvwr.sbr .\ARMV4Dbg\wmimgvwrDlg.sbr"
Creating browse info file...
<h3>Output Window</h3>




<h3>Results</h3>
wmimgvwr.exe - 0 error(s), 0 warning(s)
</pre>
</body>
</html>
