/*
Author: Gudakov Ramil Sergeevich a.k.a. Gauss 
Гудаков Рамиль Сергеевич 
Contacts: [ramil2085@mail.ru, ramil2085@gmail.com]
See for more information License.h.
*/

#include "WClient.h"
#include "Client.h"

namespace WrapperMMOEngine
{
  WClient::WClient() : WBase( new nsMMOEngine::TClient() )
  {
    mClient = (nsMMOEngine::TClient*)GetBase();
  }
  //---------------------------------------------------------------
  void WClient::Login(unsigned int ip, unsigned short port, void* pLogin, int sizeLogin, void* pPassword, int sizePassword)
  {
    mClient->Login(ip, port, pLogin, sizeLogin, pPassword, sizePassword);
  }
  //---------------------------------------------------------------
  void WClient::LeaveQueue()
  {
    mClient->LeaveQueue();
  }
  //---------------------------------------------------------------
}