/*
Author: Gudakov Ramil Sergeevich a.k.a. Gauss 
Гудаков Рамиль Сергеевич 
Contacts: [ramil2085@mail.ru, ramil2085@gmail.com]
See for more information License.h.
*/

#pragma once

#include "GraphicEngine/BaseGUI.h"
#include <MyGUI.h>
#include <Ogre.h>

class TPlateVarGeomParam : public TBaseGUI
{

public:
  TPlateVarGeomParam();
  virtual ~TPlateVarGeomParam();

protected:
  virtual void Activate();
  virtual void* GetParent();
  virtual const char* GetNameLayout();
  virtual void SetupTabChild();

  virtual void KeyEvent(MyGUI::Widget* _sender, MyGUI::KeyCode _key, MyGUI::Char _char);
protected:

  void sl_Apply(MyGUI::Widget* _sender);
  void sl_Close(MyGUI::Widget* _sender);
protected:

  MyGUI::Button* bApply;
  MyGUI::Button* bClose;

  MyGUI::EditBox* ebThickness;
  MyGUI::EditBox* ebWidth; 
  MyGUI::EditBox* ebLength;
  
  MyGUI::ImageBox* ibGeom;
};

