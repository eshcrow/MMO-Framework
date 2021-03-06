/*
Author: Gudakov Ramil Sergeevich a.k.a. Gauss 
Гудаков Рамиль Сергеевич 
Contacts: [ramil2085@mail.ru, ramil2085@gmail.com]
See for more information License.h.
*/

#ifndef ModulesThreadManagerH
#define ModulesThreadManagerH

#include <vector>
#include "CallBackRegistrator.h"
#include "TypeDef.h"

class IModule;
class TThreadModules;

class DllExport TModulesThreadManager
{
  typedef std::vector<TThreadModules*> TVecPtrThread;
  TVecPtrThread mVecThread;

public:
  TModulesThreadManager();
  ~TModulesThreadManager();

  void SetCountThread(int cnt);
  void AddModuleByThread(int indexThread, IModule* pModule);
  void SetCallbackStop(TCallBackRegistrator1<std::string>* pCB);
  void Start();
  void Stop();
private:
  void Done();
};

#endif