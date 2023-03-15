                                                            /* -*- C++ -*- */
// %option defines the parameters with which the reflex will be launched
%option noyywrap
// To enable compatibility with bison
%option bison-complete
%option bison-cc-parser=parser
%option bison_cc_namespace=parse
%option bison-locations

%option lex=lex
// Add a param of function lex() generate in Lexer class
%option params="::parse::TigerParser& tp"
%option namespace=parse
// Name of the class generate by reflex
%option lexer=Lexer

%top{

#define YY_EXTERN_C extern "C" // For linkage rule

#include <cerrno>
#include <climits>
#include <regex>
#include <string>

#include <boost/lexical_cast.hpp>

#include <misc/contract.hh>
  // Using misc::escape is very useful to quote non printable characters.
  // For instance
  //
  //    std::cerr << misc::escape('\n') << '\n';
  //
  // reports about `\n' instead of an actual new-line character.
#include <misc/escape.hh>
#include <misc/symbol.hh>
#include <parse/parsetiger.hh>
#include <parse/tiger-parser.hh>

  // FIXME: Some code was deleted here (Define YY_USER_ACTION to update locations).

#define TOKEN(Type)                             \
  parser::make_ ## Type(tp.location_)

#define TOKEN_VAL(Type, Value)                  \
  parser::make_ ## Type(Value, tp.location_)

# define CHECK_EXTENSION()                              \
  do {                                                  \
    if (!tp.enable_extensions_p_)                       \
      tp.error_ << misc::error::error_type::scan        \
                << tp.location_                         \
                << ": invalid identifier: `"            \
                << misc::escape(text()) << "'\n";       \
  } while (false)


%}

%x SC_COMMENT SC_STRING

/* Abbreviations.  */

and      "&"                    { return TOKEN(AND    );}
array    "array"                { return TOK(ARRAY    );}
assign   ":="                   { return TOK(ASSIGN   );}
break    "break"                { return TOK(BREAK    );}
cast     "_cast"                { return TOK(CAST     );}
class    "class"                { return TOK(CLASS    );}
colon    ":"                    { return TOK(COLON    );}

comma    ","                    { return TOK(COMMA    );}
divide   "/"                    { return TOK(DIVIDE   );}
do       "do"                   { return TOK(DO       );}
dot      "."                    { return TOK(DOT      );}

else     "else"                 { return TOK(ELSE     );}
end      "end"                  { return TOK(END      );}
equal    "="                    { return TOK(EQ       );}
extends  "extends"              { return TOK(EXTENDS  );}
for      "for"                  { return TOK(FOR      );}
function "function"             { return TOK(FUNCTION );}
ge       ">="                   { return TOK(GE       );}
gt       ">"                    { return TOK(GT       );}
if       "if"                   { return TOK(IF       );}
import   "import"               { return TOK(IMPORT   );}
in       "in"                   { return TOK(IN       );}
lbrace   "{"                    { return TOK(LBRACE   );}
lbrack   "["                    { return TOK(LBRACK   );}
le       "<="                   { return TOK(LE       );}
let      "let"                  { return TOK(LET      );}
lparen   "("                    { return TOK(LPAREN   );}
lt       "<"                    { return TOK(LT       );}
minus    "-"                    { return TOK(MINUS    );}
method   "method"               { return TOK(METHOD   );}
ne       "<>"                   { return TOK(NE       );}
new      "new"                  { return TOK(NEW      );}
nil      "nil"                  { return TOK(NIL      );}
of       "of"                   { return TOK(OF       );}
or       "|"                    { return TOK(OR       );}
plus     "+"                    { return TOK(PLUS     );}
primitive"primitive"            { return TOK(PRIMITIVE);}
rbrace   "}"                    { return TOK(RBRACE   );}
rbrack   "]"                    { return TOK(RBRACK   );}
rparen   ")"                    { return TOK(RPAREN   );}
semi     ";"                    { return TOK(SEMI     );}
then     "then"                 { return TOK(THEN     );}
times    "*"                    { return TOK(TIMES    );}
to       "to"                   { return TOK(TO       );}
type     "type"                 { return TOK(TYPE     );}
var      "var"                  { return TOK(VAR      );}
while    "while"                { return TOK(WHILE    );}
eof      "end of file"          { return TOK(EOF      );}


int             [0-9]+;
string [a-zA-Z]+
id              [a-z][a-z0-9]*
/* FIXME: Some code was deleted here. */
           %class{
// FIXME: Some code was deleted here (Local variables).
}
%%
/* The rules. */
{int} {
        int val = 0;
    //FIXME:Some code was deleted here (Decode, and check the value).
                return TOKEN_VAL(INT, val);
      }
/* FIXME: Some code was deleted here. */
%%











