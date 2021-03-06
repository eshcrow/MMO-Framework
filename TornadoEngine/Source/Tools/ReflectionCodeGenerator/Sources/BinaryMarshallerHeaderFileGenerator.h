/*
Author: Gudakov Ramil Sergeevich a.k.a. Gauss
Гудаков Рамиль Сергеевич
Contacts: [ramil2085@mail.ru, ramil2085@gmail.com]
See for more information License.h.
*/

#pragma once

#include "BinaryMarshallerFileGenerator.h"
#include "fmt/core.h"

namespace nsReflectionCodeGenerator
{
  class TBinaryMarshallerHeaderFileGenerator : public TBinaryMarshallerFileGenerator
  {
    const std::string s_MemoryObjectPoolAllocator = "TMemoryObjectPoolAllocator";

    const std::list<std::string> s_BinaryDeclBeforeEnum =
    {
      "public:",
      fmt::format( "  typedef unsigned short {};", s_TypeID ),
      "private:",
      "#ifdef WIN32",
      "#pragma pack(push, 1)",
      "#endif",
      fmt::format( "  struct {}", s_THeader ),
      "  {",
      fmt::format( "    {} type : 15;", s_TypeID ),
      fmt::format( "    {} useCompression : 1;", s_TypeID ),
      "    unsigned char ratio = 0;",
      "  }_PACKED;",
      "#ifdef WIN32",
      "#pragma pack(pop)",
      "#endif",
      "  // upper use LZ4 for compression",
      "  int mSetLimitForCompression = 0x40;",
      "",
      "  TContainerRise mBuffer;",
      "  // collectors",
      fmt::format( "  TBinaryPushMaster {};", s_PushMaster ),
      fmt::format( "  TBinaryPopMaster {};", s_PopMaster ),
      "public:",
      fmt::format( "  enum SerializableUniqueID : {}", s_TypeID ),
      "  {",
    };

    const std::list<std::string> s_BinaryDeclAfterEnum_BeforeTypesDecl =
    {
      "  };",
      "",
      fmt::format( "  void {}( int binarySize );", s_SetLimitForCompression ),
      "",
      "  // serialize / deserialize",
      "  template <typename Type>",
      "  void Serialize( Type* p, TContainerRise& c );",
      "  template <typename Type>",
      "  void Deserialize( Type*& p, char* serData, int size );",
      "  template <typename Type>",
      "  void Fill( Type* p, char* serData, int size );",
      "",
      "  // pack / unpack",
      "  template <typename Type>",
      "  void Pack( Type* p, TContainerRise& c );",
      "  // WARNING! handle in {} определяется настройками генератора",
      "  void Unpack( char* packedData, int size );",
      "",
      "  TypeID GetID( char* packedData, int size );",
      "  template <typename Type>",
      "  Type* HandleUnpack( char* packedData, int size );",
      "  template <typename Type>",
      "  void FillUnpack( Type* p, char* packedData, int size );",
      "",
      "  template <typename Type>",
      fmt::format( "  static void {}( Type* p );", s_GeneralDeallocate ),
      "private:",
      "  void PushIsNotNullptr( void* p );",
      "  bool PopIsNotNullptr();",
      "",
      "  template <typename Type>",
      fmt::format( "  static Type* {}();", s_GeneralAllocate ),
      "  template <typename Type>",
      "  void _Deserialize( Type*& p, char* serData, int size, bool checkPtr );",
      fmt::format( "  {} PrepareForUnpackPopMaster( char* packedData, int size );", s_TypeID ),
      "private:",
    };

    const std::list<std::string> s_BinaryImpl =
    {
      "//-----------------------------------------------------------------------------",
      "template <typename Type>",
      fmt::format( "void {}::Serialize( Type* p, TContainerRise& c )", mBinaryMarshaller->className ),
      "{",
      fmt::format( "  {}.Clear();", s_PushMaster ),
      fmt::format( "  {}( p );", s_Serialize ),
      fmt::format( "  {}.CopyInBuffer( c, 0 );", s_PushMaster ),
      "}",
      "//-----------------------------------------------------------------------------",
      "template <typename Type>",
      fmt::format( "void {}::Deserialize( Type*& p, char* serData, int size )", mBinaryMarshaller->className ),
      "{",
      "  _Deserialize( p, serData, size, true );",
      "}",
      "//-----------------------------------------------------------------------------",
      "template <typename Type>",
      fmt::format( "void {}::Fill( Type* p, char* serData, int size )", mBinaryMarshaller->className ),
      "{",
      "  _Deserialize( p, serData, size, false );",
      "}",
      "//-----------------------------------------------------------------------------",
      "template <typename Type>",
      fmt::format( "void {}::Pack( Type* p, TContainerRise& c )", mBinaryMarshaller->className ),
      "{",
      "  Serialize( p, c );",
      "",
      "  int headerSize = sizeof( THeader );",
      "  THeader header;",
      "  header.type = _GetTypeID( p );",
      "  header.useCompression = 0;",
      "  header.ratio = 0;",
      "  if ( c.GetSize() - headerSize > mSetLimitForCompression )",
      "  {",
      "    header.useCompression = 1;",
      "    // compression",
      "    mBuffer.Clear();",
      "    mBuffer.Shift( LZ4_compressBound( c.GetSize() ) );",
      "    int compressedSize = LZ4_compress_default( c.GetPtr(), mBuffer.GetPtr(),",
      "      c.GetSize(), mBuffer.GetSize() );",
      "    header.ratio = c.GetSize() / compressedSize + 1;",
      "",
      "    c.Clear();",
      "    c.Shift( headerSize + compressedSize );",
      "    memcpy( c.GetPtr() + headerSize, mBuffer.GetPtr(), compressedSize );",
      "  }",
      "  else",
      "  {",
      "    auto size = c.GetSize();",
      "    c.Shift( headerSize );",
      "    memmove( c.GetPtr() + headerSize, c.GetPtr(), size );",
      "  }",
      "  memcpy( c.GetPtr(), &header, headerSize );",
      "}",
      "//-----------------------------------------------------------------------------",
      "template <typename Type>",
      fmt::format( "Type* {}::HandleUnpack( char* packedData, int size )", mBinaryMarshaller->className ),
      "{",
      "  Type* p = nullptr;",
      "  auto typeFromBinary = PrepareForUnpackPopMaster( packedData, size );",
      "  auto typeByUserGuest = _GetTypeID( p );",
      "  BL_ASSERT( typeFromBinary == typeByUserGuest );",
      fmt::format( "  p = {}<Type>();", s_GeneralAllocate),
      fmt::format( "  {}( p );", s_Deserialize ),
      "  return p;",
      "}",
      "//-----------------------------------------------------------------------------",
      "template <typename Type>",
      fmt::format( "void {}::FillUnpack( Type* p, char* packedData, int size )", mBinaryMarshaller->className ),
      "{",
      "  auto typeFromBinary = PrepareForUnpackPopMaster( packedData, size );",
      "  auto typeByUserGuest = _GetTypeID( p );",
      "  BL_ASSERT( typeFromBinary == typeByUserGuest );",
      fmt::format( "  {}( p );", s_Deserialize ),
      "}",
      "//-----------------------------------------------------------------------------",
      "template <typename Type>",
      fmt::format( "void {}::{}( Type* p )", mBinaryMarshaller->className, s_GeneralDeallocate  ),
      "{",
      fmt::format( "  {}( p );", s_Deallocate ),
      fmt::format( "  {}::DeallocateFunc( p );", s_MemoryObjectPoolAllocator ),
      "}",
      "//-----------------------------------------------------------------------------",
      "template <typename Type>",
      fmt::format( "static Type* {}::{}()", mBinaryMarshaller->className, s_GeneralAllocate ),
      "{",
      fmt::format( "  return {}::AllocateFunc<Type>();", s_MemoryObjectPoolAllocator ),
      "}",
      "//-----------------------------------------------------------------------------",
      "template <typename Type>",
      fmt::format( "void {}::_Deserialize( Type*& p, char* serData, int size, bool checkPtr )", mBinaryMarshaller->className ),
      "{",
      "  if ( checkPtr )",
      "    p = p ? p : new Type();",
      "",
      fmt::format( "  {}.SetBuffer( serData, size, 0 );", s_PopMaster ),
      fmt::format( "  {}( p );", s_Deserialize ),
      "}",
    };

  public:
    virtual void Work() override;

  private:
    void AddDeclarations();
    void AddEnums();

  };
}

