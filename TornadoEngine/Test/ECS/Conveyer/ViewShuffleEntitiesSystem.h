/*
Author: Gudakov Ramil Sergeevich a.k.a. Gauss 
Гудаков Рамиль Сергеевич 
Contacts: [ramil2085@mail.ru, ramil2085@gmail.com]
See for more information License.h.
*/

#pragma once
#include "ECS/include/ExecuteSystem.h"
#include "SpeedCalculationSystem.h"
#include <iostream>
#include "ShuffledComponents.h"

class TViewShuffleEntitiesSystem : public nsECSFramework::TExecuteSystem, public TSpeedCalculationSystem
{
#ifdef _DEBUG
  const int groupTestCount = 1;//200000;
#else
  const int groupTestCount = 20000000;
#endif
public:

  virtual void Execute() override
  {
    Group<ShuffledComponents::A>();
    Group<ShuffledComponents::B>();
    Group<ShuffledComponents::C>();
    Group<ShuffledComponents::D>();
    Group<ShuffledComponents::E>();
    Group<ShuffledComponents::F>();
    //Group<ShuffledComponents::F, ShuffledComponents::C>();
    //Group<ShuffledComponents::F, ShuffledComponents::B, ShuffledComponents::C>();
    //Group<ShuffledComponents::F, ShuffledComponents::B, ShuffledComponents::C, ShuffledComponents::D>();
    //Group<ShuffledComponents::F, ShuffledComponents::B, ShuffledComponents::C, ShuffledComponents::D, ShuffledComponents::E>();
    //Group<ShuffledComponents::A, ShuffledComponents::B, ShuffledComponents::C, ShuffledComponents::D, ShuffledComponents::E, ShuffledComponents::F>();
  }

  template<typename ... Args>
  void Group()
  {
    auto registry = GetRegistry();

    Start();

    for( int i = 0; i < groupTestCount; i++ )
    {
      auto packetGroup = registry->view<Args ...>();
      auto count = packetGroup.size();
    }

    Stop();
    auto speed = Speed( groupTestCount );
    auto componentCount = sizeof ... (Args);
    auto speedPerComponent = speed / (componentCount * 1.0f);
    speedPerComponent *= 1000.0f;
    std::cout << "Make grouped CC=" << componentCount << " ,speed = " << speedPerComponent << "(" << speed << ") ns per component" << std::endl;
  }
};