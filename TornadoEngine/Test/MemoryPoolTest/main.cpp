#include "HiTimer.h"
#include "MemoryObjectPoolAllocator.h"
#include "fmt/core.h"
#include "MemoryPool.h"

#include <functional>
#include <algorithm>

#include "DataExchange2ThreadElement.h"
#include <boost/pool/pool.hpp>

struct A{};
typedef A TestingClass;
//---------------------------------------------------------------------------------------------
#if _DEBUG
const long TEST_COUNT = 1000;
const long ELEMENT_COUNT = 1000;
#else
const long TEST_COUNT = 30000;
const long ELEMENT_COUNT = 10000;
#endif
TestingClass* g_Arr[ELEMENT_COUNT];
TMemoryPool<TestingClass>::TPointerDesc* g_DescArr[ELEMENT_COUNT];

struct TTestResult
{
  std::string name;
  int timePerCycle;
};
std::vector<TTestResult> g_TestResult;
//---------------------------------------------------------------------------------------------
void Test_NewDelete( int testCount, int elementCount )
{
  for ( long i = 0; i < testCount; i++ )
  {
    for ( long e = 0; e < elementCount; e++ )
    {
      auto pA = new TestingClass();
      delete pA;
    }
  }
}
//---------------------------------------------------------------------------------------------
void Test_MemoryObjectPoolAllocator( int testCount, int elementCount )
{
  for ( long i = 0; i < testCount; i++ )
  {
    for ( long e = 0; e < elementCount; e++ )
      g_Arr[e] = TMemoryObjectPoolAllocator::AllocateFunc<TestingClass>();

    for ( long e = 0; e < elementCount; e++ )
      TMemoryObjectPoolAllocator::DeallocateFunc( g_Arr[e] );
  }
}
//---------------------------------------------------------------------------------------------
void Test_MemoryPool( int testCount, int elementCount )
{
  auto pMP = SingletonManager()->Get<TMemoryPool<TestingClass>>();

  for ( long i = 0; i < testCount; i++ )
  {
    for ( long e = 0; e < elementCount; e++ )
      g_DescArr[e] = pMP->Pop( 1 );

    for ( long e = 0; e < elementCount; e++ )
      pMP->Push( g_DescArr[e] );
  }
}
//---------------------------------------------------------------------------------------------
void Test_BoostAllocator( int testCount, int elementCount )
{
  auto allocator = new boost::pool<>(sizeof(TestingClass));

  for ( long i = 0; i < testCount; i++ )
  {
    for ( long e = 0; e < elementCount; e++ )
      g_Arr[e] = (TestingClass*)allocator->malloc();

    for ( long e = 0; e < elementCount; e++ )
      allocator->free( g_Arr[e] );
  }
}
//---------------------------------------------------------------------------------------------
void Test_MemoryObjectPool( int testCount, int elementCount )
{
  auto pMOP = SingletonManager()->Get<TMemoryObjectPool<TestingClass>>();

  for ( long i = 0; i < testCount; i++ )
  {
    for ( long e = 0; e < elementCount; e++ )
      g_Arr[e] = pMOP->Pop();

    for ( long e = 0; e < elementCount; e++ )
      pMOP->Push( g_Arr[e] );
  }
}
//---------------------------------------------------------------------------------------------
void Test( std::string testName, std::function<void( int, int )> func )
{
  auto start = ht_GetMSCount();

  func( TEST_COUNT, ELEMENT_COUNT );

  auto stop = ht_GetMSCount();
  auto delta = stop - start;
  
  TTestResult result;
  result.timePerCycle = (int)(( 1000000.0*delta ) / ( TEST_COUNT * ELEMENT_COUNT ));
  result.name = testName;
  g_TestResult.push_back( result );

  fmt::print( "test ended {}\n", g_TestResult.size() );
}
//---------------------------------------------------------------------------------------------
int main( int argc, char *argv[] )
{
  Test( "MemoryObjectPoolAllocator", Test_MemoryObjectPoolAllocator );
  Test( "MemoryPool", Test_MemoryPool );
  Test( "Boost", Test_BoostAllocator );
  Test( "MemoryObjectPool", Test_MemoryObjectPool );
  Test( "new/delete", Test_NewDelete );

  int maxTime = 0;
  for ( auto& test : g_TestResult)
  {
    maxTime = std::max( maxTime, test.timePerCycle );
  }

  for ( auto& test : g_TestResult)
  {
    auto percentage = (( 100.0f * test.timePerCycle ) / maxTime);
    fmt::print( "{:30}: speed {:3.2} ns - {:3} %\n", test.name, test.timePerCycle, percentage );
  }

  getchar();
  return 0;
}
//---------------------------------------------------------------------------------------------
