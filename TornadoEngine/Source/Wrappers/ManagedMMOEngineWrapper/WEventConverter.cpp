/*
Author: Gudakov Ramil Sergeevich a.k.a. Gauss 
Гудаков Рамиль Сергеевич 
Contacts: [ramil2085@mail.ru, ramil2085@gmail.com]
See for more information License.h.
*/

#include "WEventConverter.h"
#include <stddef.h>

namespace WrapperMMOEngine
{
  WEventConverter::WEventConverter()
  {

  }
  //-------------------------------------------------------------------------
  WEventConverter::~WEventConverter()
  {

  }
  //-------------------------------------------------------------------------
  WBaseEvent^ WEventConverter::GetEvent()
  {
     return nullptr;//gcnew WBaseEvent();
  }
  //-------------------------------------------------------------------------
}