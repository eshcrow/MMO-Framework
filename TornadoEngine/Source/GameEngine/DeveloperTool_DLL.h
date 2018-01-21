/*
Author: Gudakov Ramil Sergeevich a.k.a. Gauss 
Гудаков Рамиль Сергеевич 
Contacts: [ramil2085@mail.ru, ramil2085@gmail.com]
See for more information License.h.
*/

#ifndef DeveloperTool_DLLH
#define DeveloperTool_DLLH

#include "TypeDef.h"

class IDevTool;

#define StrGetDevTool  "GetDevTool"
#define StrFreeDevTool "FreeDevTool"

typedef IDevTool* (*FuncGetDevTool)(int);
typedef void (*FuncFreeDevTool)(IDevTool*);

DllExport_C IDevTool* GetDevTool(int variant_use);
DllExport_C void FreeDevTool(IDevTool* p);

#endif
