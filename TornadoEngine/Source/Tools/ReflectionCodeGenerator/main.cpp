/*
Author: Gudakov Ramil Sergeevich a.k.a. Gauss
Гудаков Рамиль Сергеевич
Contacts: [ramil2085@mail.ru, ramil2085@gmail.com]
See for more information License.h.
*/

//#include <boost/wave/cpplexer/re2clex/scanner.hpp>
//
//
//#include <stdio.h>
//#include "InputCmdReflectionCodeGenerator.h"
//
//std::string code = "class A{};";
//
//
//int main( int argc, char** argv )
//{
//  printf( "Reflection code generator.\n" );
//
//  TInputCmdReflectionCodeGenerator inputCmd;
//  inputCmd.Init();
//  inputCmd.SetArg( argc, argv );
//  //inputCmd.mInput;
//
//  boost::wave::cpplexer::re2clex::Scanner lexer;
//  //lexer.
//
//  return 0;
//}

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

///////////////////////////////////////////////////////////////////////////////
//  Include Wave itself
#include <boost/wave.hpp>

///////////////////////////////////////////////////////////////////////////////
// Include the lexer stuff
#include <boost/wave/cpplexer/cpp_lex_token.hpp>    // token class
#include <boost/wave/cpplexer/cpp_lex_iterator.hpp> // lexer class
#include <conio.h>
#include "LoadFromFile.h"
#include "ReflectionMacro.h"
#include "IBinaryMarshaller.h"

template <typename PositionT>
inline std::ostream& operator<< ( std::ostream &stream, boost::wave::cpplexer::lex_token<PositionT> const &t )
{
  using namespace std;
  using namespace boost::wave;

  token_id id = token_id( t );
  stream << setw( 16 )
    << left << boost::wave::get_token_name( id ) << " ("
    << "#" << setw( 3 ) << BASEID_FROM_TOKEN( id );

  if ( ExtTokenTypeMask & id )
  {
    // this is an extended token id
    if ( AltTokenType == ( id & ExtTokenOnlyMask ) )
    {
      stream << ", AltTokenType";
    }
    else if ( TriGraphTokenType == ( id & ExtTokenOnlyMask ) )
    {
      stream << ", TriGraphTokenType";
    }
    else if ( AltExtTokenType == ( id & ExtTokenOnlyMask ) )
    {
      stream << ", AltExtTokenType";
    }
  }

  stream
    << ") at " << t.get_position().get_file() << " ("
    << setw( 3 ) << right << t.get_position().get_line() << "/"
    << setw( 2 ) << right << t.get_position().get_column()
    << "): >";

  typedef typename boost::wave::cpplexer::lex_token<PositionT>::string_type string_type;

  auto value = t.get_value();
  auto size = value.size();
  for ( std::size_t i = 0; i < size; ++i )
  {
    auto v = value [i];
    switch ( v )
    {
      case '\r':  stream << "\\r"; break;
      case '\n':  stream << "\\n"; break;
      case '\t':  stream << "\\t"; break;
      default:
        stream << v;
        break;
    }
  }
  stream << "<";
  return stream;
}
//-----------------------------------------------------------------------------------------------
int main( int argc, char *argv [] )
{
  float i = 0;
  TBinaryMarshaller bm;
  IBinaryMarshaller<TBinaryMarshaller>* ibm = &bm;
  bm.Serialize( &i );

  //std::string data;
  TLoadFromFile loader;
  if ( loader.ReOpen( argv [1] ) == false )
    return -1;
  TContainer data;
  loader.ReadSmall( data );

  if ( 2 != argc )
  {
    std::cerr << "Usage: lexed_tokens infile" << std::endl;
    return -1;
  }

  // current file position is saved for exception handling
  boost::wave::util::file_position_type current_position;

  try
  {
    //  Open and read in the specified input file.
    std::ifstream instream( argv [1] );

    if ( !instream.is_open() )
    {
      std::cerr << "Could not open input file: " << argv [1] << std::endl;
      return -2;
    }
    instream.unsetf( std::ios::skipws );
    std::string instr = std::string( std::istreambuf_iterator<char>( instream.rdbuf() ),
      std::istreambuf_iterator<char>() );

    // tokenize the input data into C++ tokens using the C++ lexer
    typedef boost::wave::cpplexer::lex_token<> token_type;
    typedef boost::wave::cpplexer::lex_iterator<token_type> lexer_type;
    typedef token_type::position_type position_type;

    auto flags = boost::wave::language_support( boost::wave::support_cpp | boost::wave::support_option_long_long );

    position_type pos( argv [1] );
    lexer_type it = lexer_type( instr.begin(), instr.end(), pos, flags );
    lexer_type end = lexer_type();

    while ( it != end )
    {
      current_position = ( *it ).get_position();  // for error reporting
      std::cout << *it << std::endl;            // dump the tokens info
      ++it;
    }
  }
  catch ( boost::wave::cpplexer::lexing_exception const& e )
  {
    // some lexing error
    std::cerr
      << e.file_name() << "(" << e.line_no() << "): "
      << e.description() << std::endl;
    return 2;
  }
  catch ( std::exception const& e )
  {
    // use last recognized token to retrieve the error position
    std::cerr
      << current_position.get_file()
      << "(" << current_position.get_line() << "): "
      << "exception caught: " << e.what()
      << std::endl;
    return 3;
  }
  catch ( ... )
  {
    // use last recognized token to retrieve the error position
    std::cerr
      << current_position.get_file()
      << "(" << current_position.get_line() << "): "
      << "unexpected exception caught." << std::endl;
    return 4;
  }

  _getch();
  return 0;
}