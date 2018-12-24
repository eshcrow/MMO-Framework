/*
Author: Gudakov Ramil Sergeevich a.k.a. Gauss
Гудаков Рамиль Сергеевич
Contacts: [ramil2085@mail.ru, ramil2085@gmail.com]
See for more information License.h.
*/

#include "SingletonManager.h"
#include "Config.h"
#include "TokenInfoManager.h"
#include "TokenInfo.h"
#include "Parser.h"
#include "ConfigContainer.h"
#include "Requirements.h"
#include "readerwriterqueue.h"
#include "TypeManager.h"
#include "CodeGeneratorFactory.h"
#include "fmt/time.h"
#include "fmt/color.h"
#include "MemberTypeExtendedInfoAnalyzer.h"
#include "SetupConfig.h"

const std::string _VERSION = "0.2";
const int _COUNTER_BUILD = 3;

using namespace boost::wave;

using namespace moodycamel;
void TestQueue()
{
  ReaderWriterQueue<int> q( 100 );       // Reserve space for at least 100 elements up front

  q.enqueue( 17 );                       // Will allocate memory if the queue is full
  bool succeeded = q.try_enqueue( 18 );  // Will only succeed if the queue has an empty slot (never allocates)
  assert( succeeded );

  int number;
  succeeded = q.try_dequeue( number );  // Returns false if the queue was empty

  assert( succeeded && number == 17 );

  // You can also peek at the front item of the queue (consumer only)
  int* front = q.peek();
  assert( *front == 18 );
  succeeded = q.try_dequeue( number );
  assert( succeeded && number == 18 );
  front = q.peek();
  assert( front == nullptr );           // Returns nullptr if the queue was empty
}
//---------------------------------------------------------------------------------------

void ShowTitle()
{
  fmt::print( "The world needs reflection in C++. I give it. You take it!\n" );
  fmt::print( "ReflectionCodeGenerator version {}.b{}\n", _VERSION, _COUNTER_BUILD );
}
//---------------------------------------------------------------------------------------
int main( int argc, char *argv [] )
{
  ShowTitle();

  TSetupConfig setupConfig;
  if ( setupConfig.Work() == false )
    return 0;

  TParser parser;
  parser.Work();

  // дополнить расширенной информацией
  TMemberTypeExtendedInfoAnalyzer analyzer;
  analyzer.Work();

  //TCodeGeneratorFactory cgFactory;
  //cgFactory.Work();
  getchar();
  return 0;
}