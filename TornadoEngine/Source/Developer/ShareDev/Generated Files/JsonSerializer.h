/*
Author: Gudakov Ramil Sergeevich a.k.a.Gauss
Гудаков Рамиль Сергеевич
Contacts : [ramil2085@mail.ru, ramil2085@gmail.com]
See for more information License.h.
*/
// File has been generated by ReflectionCodeGenerator version 1.7 build 36, at 2019_02_08 17:12:02.701
	
#pragma once

#include <string>
#include "JsonMaster.h"
#include "json11.h"
#include "IncludeList.h"

namespace nsSharedDev
{
  class TJsonSerializer
  {
    typedef TJsonMaster::Jobj Jobj;
    typedef TJsonMaster::Jarr Jarr;
  public:
    template <typename Type>
    static void Serialize( Type* p, std::string& str );
    template <typename Type>
    static void Deserialize( Type*& p, std::string& str );
    template <typename Type>
    static void Fill( Type* p, std::string& str );
  private:
    template <typename Type>
    static void _Deserialize( Type*& p, std::string& str, bool checkPtr );
  private:
    static void _Serialize( TBaseResources* p, Jobj& obj );
    static void _Deserialize( TBaseResources* p, const json11::Json& json );
    
    static void _Serialize( TFrameworkResources* p, Jobj& obj );
    static void _Deserialize( TFrameworkResources* p, const json11::Json& json );
    
    static void _Serialize( TGUIResources* p, Jobj& obj );
    static void _Deserialize( TGUIResources* p, const json11::Json& json );
    
    static void _Serialize( TGameEngineResources* p, Jobj& obj );
    static void _Deserialize( TGameEngineResources* p, const json11::Json& json );
    
    static void _Serialize( TGameResources* p, Jobj& obj );
    static void _Deserialize( TGameResources* p, const json11::Json& json );
    
    static void _Serialize( TGraphicEngineResources* p, Jobj& obj );
    static void _Deserialize( TGraphicEngineResources* p, const json11::Json& json );
    
    static void _Serialize( TOgreCfg* p, Jobj& obj );
    static void _Deserialize( TOgreCfg* p, const json11::Json& json );
    
    static void _Serialize( TOgreResources* p, Jobj& obj );
    static void _Deserialize( TOgreResources* p, const json11::Json& json );
    
  };
  //------------------------------------------------------------------------------------------------------------
  template <typename Type>
  static void TJsonSerializer::Serialize( Type* p, std::string& str )
  {
    Jobj obj;
    _Serialize( p, obj );
    json11::Json json( obj );
    str = json.dump();
  }
  //------------------------------------------------------------------------------------------------------------
  template <typename Type>
  static void TJsonSerializer::Deserialize( Type*& p, std::string& str )
  {
    _Deserialize( p, str, true );
  }
  //------------------------------------------------------------------------------------------------------------
  template <typename Type>
  static void TJsonSerializer::Fill( Type* p, std::string& str )
  {
    _Deserialize( p, str, false );
  }
  //------------------------------------------------------------------------------------------------------------
  template <typename Type>
  static void TJsonSerializer::_Deserialize( Type*& p, std::string& str, bool checkPtr )
  {
    std::string err;
    auto json = json11::Json::parse( str, err, json11::JsonParse::COMMENTS );
    if ( err.size() > 0 )
      return;
  
    if ( checkPtr )
      p = p ? p : new Type();
  
    _Deserialize( p, json.object_items() );
  }
}