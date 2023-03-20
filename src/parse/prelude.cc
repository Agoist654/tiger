#include "parse/tiger-parser.hh"

namespace parse
{
  const char* TigerParser::prelude () const
  {
    return
R"(primitive print(string : string)
primitive print_err(string : string)
primitive print_int(int : int)
primitive flush()
primitive getchar() : string
primitive ord(string : string) : int
primitive chr(code : int) : string
primitive size(string : string) : int
primitive streq(s1 : string, s2 : string) : int
primitive strcmp(s1 : string, s2 : string) : int
primitive substring(string : string, start : int, length : int) : string
primitive concat(fst : string, snd : string) : string
primitive not(boolean : int) : int
primitive exit(status : int)
)";
  }
} // namespace parse
