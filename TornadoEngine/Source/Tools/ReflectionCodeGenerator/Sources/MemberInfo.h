/*
Author: Gudakov Ramil Sergeevich a.k.a. Gauss
Гудаков Рамиль Сергеевич
Contacts: [ramil2085@mail.ru, ramil2085@gmail.com]
See for more information License.h.
*/

#pragma once
#include "MemberTypeExtendedInfo.h"

struct TMemberInfo
{
  enum AccessLevel
  {
    ePublic, eProtected, ePrivate
  };
  AccessLevel mAccessLevel;

  std::string mName;

  std::string mTypeName;

  TMemberTypeExtendedInfo mExtendedInfo;

  std::vector<TMemberTypeExtendedInfo> CreateExtArray();
};
