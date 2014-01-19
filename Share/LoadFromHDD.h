/*
Author: Gudakov Ramil Sergeevich a.k.a. Gauss 
������� ������ ��������� 
Contacts: [ramil2085@mail.ru, ramil2085@gmail.com]
See for more information License.h.
*/


#ifndef LoadFromHDDH
#define LoadFromHDDH


#include <stdio.h>
#include <string>

#include "TypeDef.h"
#include "ContainerTypes.h"
/*
  �������� �� �����
*/

class SHARE_EI TLoadFromHDD
{
  std::string sPath;
  FILE* pFile;

public:

	TLoadFromHDD(char* path = NULL);
	~TLoadFromHDD();

	bool ReOpen(char* path);

	bool IsOpen();
	unsigned int Size();

  unsigned int Read(void* buffer, unsigned int size, unsigned int offset = 0);
  
  int ReadSmall(TContainer& c);

 	void Close();

};

#endif
