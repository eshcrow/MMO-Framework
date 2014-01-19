/*
Author: Gudakov Ramil Sergeevich a.k.a. Gauss 
������� ������ ��������� 
Contacts: [ramil2085@mail.ru, ramil2085@gmail.com]
See for more information License.h.
*/

#define _USE_MATH_DEFINES

#include <cmath>

#include "IBaseObject.h"

#include "ManagerBaseObject.h"
#include <map>
#include "BL_Debug.h"
#include "AutoCreateVar.h"

using namespace nsStruct3D;
using namespace std;

static TAutoCreateVarT<TManagerBaseObject> mManagerObject;

IBaseObject::IBaseObject()
{
  mPtrInherits = NULL;
  ID_model = 0;
  ID_map = 0;
  mV = 0;
  mA = 0;

  SetMatrixIdentity(&mWorld);
}
//------------------------------------------------------------------------------------------------
IBaseObject::~IBaseObject()
{
  int cnt = mVectorMatrix.size();
  for(int i = 0 ; i < cnt ; i++)
    delete mVectorMatrix[i];

  mVectorMatrix.clear();
  delete pLoadedTree;
  pLoadedTree = NULL;
}
//------------------------------------------------------------------------------------------------
void IBaseObject::SetState(vector<unsigned char>* state)
{
  BL_ASSERT(mState.size()==state->size());
  mState = *state;
}
//------------------------------------------------------------------------------------------------
void IBaseObject::SetTree(TTreeJoint::TLoadedJoint* pTree)
{
  delete pLoadedTree;
  pLoadedTree = new TTreeJoint::TLoadedJoint;
  *pLoadedTree = *pTree;// �������� ���������
}
//------------------------------------------------------------------------------------------------
// ��������� ������ ���� �� ���� ���� � GUI -
// ������� � ������� ���������� � ������, 
// ��������� ������������� �� ������ ��������������� ����� � ������ � ���� � ���� CheckBox
void IBaseObject::SetMapUse(map<string, int>* mapUse)
{
  if(mapUse)
    mMapUse = *mapUse;
  mTree.Setup(pLoadedTree,&mMapUse);// ������������� ������������� ��������
  mTree.SetOrderMatrixByName(&mVectorOrderPart);// � ����� ������� ����� ��������� �������

  SetDefaultMatrix();// � ������������ � ������� ��������� ������� ��-���������
  SetupState();// ������ �������� ������� ���������
  SetupMask();// �������� ���-�� � ������� ���������� ���������
}
//------------------------------------------------------------------------------------------------
void IBaseObject::SetDefaultMatrix() 
{
  int cnt = mTree.GetCountPart();
  for(int i = 0 ; i < cnt ; i++) 
  {
    TMatrix16* pIdentity = new TMatrix16;
    SetMatrixIdentity(pIdentity);

    mVectorMatrix.push_back(pIdentity);
  }
  mTree.GetMatrix(&mVectorMatrix);
}
//------------------------------------------------------------------------------------------------
void IBaseObject::SetupState()
{
  int cnt = mTree.GetCountPart();
  if(cnt==mState.size()) return;
  //------------------------------------
  mState.clear();
  for(int i = 0 ; i < cnt ; i++ )
    mState.push_back(1);// ��-���������
}
//------------------------------------------------------------------------------------------------
void IBaseObject::SetupMask()
{
  BL_ASSERT(mVectorNamePart.size());// ������� ������ ���� ������������������� ������!
  //-------------------------------------------------------------------------------
  int cntMask = mVectorNamePart.size();
  mMask.clear();
  for(int i = 0 ; i < cntMask ; i++ )
    mMask.push_back(0);// ������ ����� ������ ���� ����� �� ��� ��� ����� ������
  //-----------------------------------------------
  int sumMask = 0;
  // mMask - �����
  // mapUse - ��� - �����, �� �������������
  // mVectorNamePart - ������������ ���� ������, �������������
  for(int i = 0 ; i < cntMask ; i++)
  {
    TPart part = mVectorNamePart.at(i);
    // ��������� ����� ����� ��� ������� �����
    map<string,int>::iterator fit = mMapUse.find(part.name);
    if(fit->second==part.use)
    {
      mMask.at(i) = 1;
      sumMask++;
    }
  }
  BL_ASSERT(sumMask==mVectorOrderPart.size());
}
//------------------------------------------------------------------------------------------------
void IBaseObject::SetID_Model(unsigned int id)
{
  ID_model = id;
  mManagerObject->AddObject(this);
}
//------------------------------------------------------------------------------------------------
int IBaseObject::GetCountPart(const char* name,vector<string>* pVec)
{
  int found = 0;
  int cnt = pVec->size();
  for(int i = 0 ; i < cnt ; i++)
  {
    if(pVec->at(i).compare(name)==0)
      found++;
  }
  return found;
}
//------------------------------------------------------------------------------------------------
void IBaseObject::GetDefaultMapUse(map<string,int>* mapUse)
{
  *mapUse = mMapUse;
}
//------------------------------------------------------------------------------------------------
void IBaseObject::SetupDefaultMapUse()
{
  mMapUse.clear();
  int cnt = mVectorOrderPart.size();
  for(int i = 0 ; i < cnt ; i++)
  { 
    string name = mVectorOrderPart.at(i);
    map<string,int>::value_type val(name,0);
    mMapUse.insert(val);
  }
  SetMapUse();
}
//------------------------------------------------------------------------------------------------
void IBaseObject::SetWorld(TMatrix16* world)
{
  mWorld=*world;
  Notify(eWorld);
}
//------------------------------------------------------------------------------------------------