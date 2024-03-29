#include "stdafx.h"
#pragma hdrstop

#include "ui_tools.h"
#include "FrameLight.h"
#include "ELight.h"
#include "Scene.h"
#include "ui_main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CloseBtn"
#pragma link "RXCtrls"
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
__fastcall TfraLight::TfraLight(TComponent* Owner)
        : TFrame(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfraLight::PaneMinClick(TObject *Sender)
{
    PanelMinimizeClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TfraLight::ExpandClick(TObject *Sender)
{
    PanelMaximizeOnlyClick(Sender);
}
//---------------------------------------------------------------------------

void TfraLight::UseInD3D(bool bAll, bool bFlag){
	ObjectIt _F = Scene->FirstObj(OBJCLASS_LIGHT);
    ObjectIt _E = Scene->LastObj(OBJCLASS_LIGHT);
	for(;_F!=_E;_F++){
		CLight* L=(CLight*)*_F;
    	if(bAll){
            L->AffectD3D(bFlag);
        }else{
			if(L->Selected() && L->Visible()) L->AffectD3D(bFlag);
        }
    }
    UI->RedrawScene();
}

//----------------------------------------------------

void __fastcall TfraLight::ebUseSelInD3DClick(TObject *Sender)
{
	UseInD3D(false, true);
}
//---------------------------------------------------------------------------

void __fastcall TfraLight::ebUnuseSelInD3DClick(TObject *Sender)
{
	UseInD3D(false, false);
}
//---------------------------------------------------------------------------

void __fastcall TfraLight::ebUseAllInD3DClick(TObject *Sender)
{
	UseInD3D(true, true);
}
//---------------------------------------------------------------------------

void __fastcall TfraLight::ebUnuseAllInD3DClick(TObject *Sender)
{
	UseInD3D(true, false);
}
//---------------------------------------------------------------------------


