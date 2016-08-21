/*
Author: Gudakov Ramil Sergeevich a.k.a. Gauss 
Гудаков Рамиль Сергеевич 
Contacts: [ramil2085@mail.ru, ramil2085@gmail.com]
See for more information License.h.
*/

#include "GP_Scenario_Destructor.h"

TGP_Scenario_Destructor::TGP_Scenario_Destructor()
{

}
//---------------------------------------------------------------------------------
TGP_Scenario_Destructor::~TGP_Scenario_Destructor()
{

}
//---------------------------------------------------------------------------------
void TGP_Scenario_Destructor::UnloadAll()
{

}
//---------------------------------------------------------------------------------
bool TGP_Scenario_Destructor::DeleteGameObject(int id)
{
  return false;
}
//---------------------------------------------------------------------------------
void TGP_Scenario_Destructor::SetScene(TScene* pScene)
{

}
//---------------------------------------------------------------------------------
void TGP_Scenario_Destructor::Thread_Bullet()
{

}
//---------------------------------------------------------------------------------
void TGP_Scenario_Destructor::Thread_Ogre()
{

}
//---------------------------------------------------------------------------------
void TGP_Scenario_Destructor::Thread_Logic()
{

}
//---------------------------------------------------------------------------------
void TGP_Scenario_Destructor::Thread_OpenAL()
{

}
//---------------------------------------------------------------------------------
bool TGP_Scenario_Destructor::IsBlock()
{
  return true;
}
//-------------------------------------------------------------------------------
nsGameProcess::GP_TypeScenario TGP_Scenario_Destructor::GetType()
{
  return nsGameProcess::eDestructor;
}
//-----------------------------------------------------------------------------
