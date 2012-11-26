#include "portableparser.hh"

using namespace bats;

// Really large table..

Parser::ParseEntry PortableParser::s_initializerState[256] = 
  {
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
    {Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},{Parser::Error,Parser::s_unifiedTable},
  };