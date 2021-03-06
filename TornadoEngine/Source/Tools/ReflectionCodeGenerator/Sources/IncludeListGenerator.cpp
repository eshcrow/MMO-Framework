/*
Author: Gudakov Ramil Sergeevich a.k.a. Gauss
Гудаков Рамиль Сергеевич
Contacts: [ramil2085@mail.ru, ramil2085@gmail.com]
See for more information License.h.
*/

#include "IncludeListGenerator.h"
#include "IncludeListFileGenerator.h"
#include <filesystem>

namespace fs = std::filesystem;
using namespace nsReflectionCodeGenerator;

void TIncludeListGenerator::Work()
{
  TIncludeListFileGenerator fileGenerator;

  mPairList->push_back( TStrListPair() );

  auto& pair = mPairList->back();

  pair.first = GeneratedFileFullPath( mConfig->targetForCodeGeneration.includeListFileName + ".h" );

  fileGenerator.Init( pair );
  fileGenerator.Work();
}
//-----------------------------------------------------------------------------------