/*
Author: Gudakov Ramil Sergeevich a.k.a. Gauss
Гудаков Рамиль Сергеевич
Contacts: [ramil2085@mail.ru, ramil2085@gmail.com]
See for more information License.h.
*/

#pragma once
#include "TestStruct.h"

REFLECTION_ATTRIBUTE
class TTestClass
{
public:
  std::string str;

  nsBS::TTestStruct ts;
};
