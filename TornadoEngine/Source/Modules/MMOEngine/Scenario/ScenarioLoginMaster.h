/*
Author: Gudakov Ramil Sergeevich a.k.a. Gauss
Гудаков Рамиль Сергеевич
Contacts: [ramil2085@mail.ru, ramil2085@gmail.com]
See for more information License.h.
*/

#pragma once

#include "IScenario.h"
#include "ContextScLoginMaster.h"
#include "MakerScenario.h"
#include "ScenarioBaseHeader.h"

#ifdef WIN32
#pragma pack(push, 1)
#endif

namespace nsMMOEngine
{
  class TScenarioLoginMaster : public IScenario
  {
    enum{ eFromMaster, eAnswerFromSS, };
    struct THeaderLoginMaster : public TScenarioBaseHeader
    {
      THeaderLoginMaster(){ type = TMakerScenario::eLoginMaster; }
    }_PACKED;
    //-------------------------------------------------
    struct THeaderFromMaster : public THeaderLoginMaster
    {
      THeaderFromMaster(){ subType = eFromMaster; }
    }_PACKED;
    //-------------------------------------------------
    struct THeaderAnswerFromSS : public THeaderLoginMaster
    {
      THeaderAnswerFromSS(){ subType = eAnswerFromSS; }
    }_PACKED;
    //-------------------------------------------------

    enum{
      eTimeoutWait_ms = 20000,
    };
  public:
    TScenarioLoginMaster();
    virtual ~TScenarioLoginMaster();
    virtual void Recv( TDescRecvSession* pDesc );

    void ConnectToSuperServer( TIP_Port& ip_port, std::string& login, std::string& password, unsigned char subNet );
  protected:
    virtual void Work();

    void RecvFromSuperServer( TDescRecvSession* pDesc );
    void RecvFromMaster( TDescRecvSession* pDesc );

    TContextScLoginMaster* Context(){ return (TContextScLoginMaster*) mCurContext; }

    void ConnectToSuperServerAfterConnect( int sessionID );
  };
}

#ifdef WIN32
#pragma pack(pop)
#endif
