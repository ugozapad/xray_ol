//-----------------------------------------------------------------------------
// File: XRaySkinExp.h
//
// Desc: Export interface to max definition
//
// Copyright (C) 1998-2000 Microsoft Corporation. All Rights Reserved.
//-----------------------------------------------------------------------------
#ifndef __XRAYSKINEXP__H
#define __XRAYSKINEXP__H

// The unique ClassID
#define XRAYSKINEXP_CLASS_ID    Class_ID(0x313b1dce, 0x210e26d7)//Class_ID(0x8788d182, 0x43774da6)

#define VERSION_NUMBER 1
#define RELEASE(x) if(x) {x->Release(); x = NULL;}

#define MAX_OFFSET_VECTORS 20

extern TCHAR *GetString(int id);
extern HINSTANCE g_hInstance;

// ================================================== XSkinExp
class XRaySkinExp : public SceneExport {
public:
    //Constructor/Destructor
							XRaySkinExp		();
	virtual					~XRaySkinExp	();
	
	virtual int             ExtCount		();			// Number of extensions supported
	virtual const TCHAR *   Ext				(int n);	// Extension #n (i.e. "3DS")
	virtual const TCHAR *   LongDesc		();         // Long ASCII description (i.e. "Autodesk 3D Studio File")
	virtual const TCHAR *   ShortDesc		();         // Short ASCII description (i.e. "3D Studio")
	virtual const TCHAR *   AuthorName		();         // ASCII Author name
	virtual const TCHAR *   CopyrightMessage();         // ASCII Copyright message
	virtual const TCHAR *   OtherMessage1	();         // Other message #1
	virtual const TCHAR *   OtherMessage2	();         // Other message #2
	virtual unsigned int	Version			();         // Version number * 100 (i.e. v3.01 = 301)
	virtual void            ShowAbout		(HWND hWnd);// Show DLL's "About..." box
	virtual int             DoExport		(
		const TCHAR *name,
		ExpInterface *ei,
		Interface *i, 
		BOOL suppressPrompts, 
		DWORD options); 
	virtual BOOL			SupportsOptions	(int ext, DWORD options);
};

// ================================================== XSkinExpClassDesc
// This is the Class Descriptor for the XSkinExp plug-in
class XRaySkinExpClassDesc:public ClassDesc {
public:
    int						IsPublic		()						{return 1;}
    void *					Create			(BOOL loading = FALSE)	{return new XRaySkinExp();}
    const TCHAR *			ClassName		()						{return GetString(IDS_CLASS_NAME);}
    SClass_ID				SuperClassID	()						{return SCENE_EXPORT_CLASS_ID;}
    Class_ID				ClassID			()						{return XRAYSKINEXP_CLASS_ID;}
    const TCHAR*			Category		()						{return GetString(IDS_CATEGORY);}
    void					ResetClassParams(BOOL fileReset);
};

#endif // __XRAYSKINEXP__H
