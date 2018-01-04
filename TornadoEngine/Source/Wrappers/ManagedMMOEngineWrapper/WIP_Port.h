/*
Author: Gudakov Ramil Sergeevich a.k.a. Gauss 
Гудаков Рамиль Сергеевич 
Contacts: [ramil2085@mail.ru, ramil2085@gmail.com]
See for more information License.h.
*/

#ifndef WrapperBaseIP_PortH
#define WrapperBaseIP_PortH

namespace WrapperMMOEngine
{
  public ref class WIP_Port
  {
  public:
    unsigned int ip;
    unsigned short port;
    WIP_Port();
    WIP_Port(unsigned int _ip, unsigned short _port);
    void Set(unsigned int _ip, unsigned short _port);
  };
}

#endif