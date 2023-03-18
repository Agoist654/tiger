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
/*DONE*/
#define YY_USER_ACTION \
    tp.location_.columns(size());


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
                << misc::escape(text()) << "\n";       \
  } while (false)

%}

%x SC_COMMENT SC_STRING

/* Abbreviations.  */

/* FIXME: Some code was deleted here. */
/*DONE*/

int             [0-9]+;
string          [a-zA-Z]+;
id              [[a-zA-Z][a-zA-Z0-9_]*|"_main"];
space           [ \t]


%class{
// FIXME: Some code was deleted here (Local variables).
/*DONE*/
int nb_quote = 0;
int nb_comment = 0;
std::string growing_string = "";
long ouais = 0;
}

%%
/* The rules. */
/* FIXME: Some code was deleted here. */
/*ONGOING*//*should be DONE*/

"array"       return parser::make_ARRAY(tp.location_);
"&"           return TOKEN(AND);
":="          return TOKEN(ASSIGN);
"break"       return TOKEN(BREAK    );
"_cast"       return TOKEN(CAST     );
"class"       return TOKEN(CLASS    );
":"           return TOKEN(COLON    );

","           return TOKEN(COMMA    );
"/"           return TOKEN(DIVIDE   );
"do"          return TOKEN(DO       );
"."           return TOKEN(DOT      );

"else"        return TOKEN(ELSE     );
"end"         return TOKEN(END      );
"="           return TOKEN(EQ       );
"extends"     return TOKEN(EXTENDS  );
"for"         return TOKEN(FOR      );
"function"    return TOKEN(FUNCTION );
">="          return TOKEN(GE       );
">"           return TOKEN(GT       );
"if"          return TOKEN(IF       );
"import"      return TOKEN(IMPORT   );
"in"          return TOKEN(IN       );
"{"           return TOKEN(LBRACE   );
"["           return TOKEN(LBRACK   );
"<="          return TOKEN(LE       );
"let"         return TOKEN(LET      );
"("           return TOKEN(LPAREN   );

"<"           return TOKEN(LT       );
"-"           return TOKEN(MINUS    );
"method"      return TOKEN(METHOD   );
"<>"          return TOKEN(NE       );
"new"         return TOKEN(NEW      );
"nil"         return TOKEN(NIL      );
"of"          return TOKEN(OF       );
"|"           return TOKEN(OR       );
"+"           return TOKEN(PLUS     );
"primitive"   return TOKEN(PRIMITIVE);
"}"           return TOKEN(RBRACE   );
"]"           return TOKEN(RBRACK   );
")"           return TOKEN(RPAREN   );
";"           return TOKEN(SEMI     );
"then"        return TOKEN(THEN     );
"*"           return TOKEN(TIMES    );
"to"          return TOKEN(TO       );
"type"        return TOKEN(TYPE     );
"var"         return TOKEN(VAR      );
"while"       return TOKEN(WHILE    );
<<EOF>>       return TOKEN(EOF      );

{int} {
        int val = 0;
    //FIXME:Some code was deleted here (Decode, and check the value).
        /*DONE*/
        val = (int)strtol(text(), 0, 10);
        if (val > 2147483647 || val < -2147483647)
            if (!tp.enable_extensions_p_)                       \
            tp.error_ << misc::error::error_type::scan        \
            << tp.location_                         \
            << ": invalid identifier: `"            \
            << misc::escape(text()) << "\n";       \
        return TOKEN_VAL(INT, val);
      }

{id}          return TOKEN_VAL(ID, text());

{string}      return TOKEN_VAL(ID, text());

{space}       tp.location_.columns();

/*lines*/
\n       { tp.location_.lines();
tp.location_.end.column = 0;
}

\r       { tp.location_.lines();
tp.location_.end.column = 0;
}

\r\n       {
    tp.location_.lines();
    tp.location_.end.column = 0;
}

\n\r       { tp.location_.lines();
tp.location_.end.column = 0;
}


"/*" {
    nb_comment++;

    std::cout << "comment mathc\n";
    growing_string.clear();
    start(SC_COMMENT);
}

"\"" {
    growing_string.clear();
    start(SC_STRING);;
}


/*sublexer*/
<SC_COMMENT> {

<<<EOF>>> {
    std::cout << "end of file match\n";
     tp.error_ << misc::error::error_type::scan        \
     << tp.location_                         \
     << "EOF in comment"                     \
     << misc::escape(text()) << "\n";       \
    start(INITIAL);
}

"/*" {nb_comment++; start(SC_COMMENT);}

[^*]*

"*"+[^*/]*

"*/" {
     nb_comment--;
     if (nb_comment == 0)
     start(INITIAL);
}

}

<SC_STRING> {

<<<EOF>>> {
        tp.error_ << misc::error::error_type::scan        \
        << tp.location_                         \
        << "string unclosed\n";                     \
        start(INITIAL);
}

\\\"  {growing_string = growing_string + "\"";}
\" {
    start(INITIAL);
    return TOKEN_VAL(STRING, growing_string);
}

\\a {growing_string = growing_string + '\a';}
\\b {growing_string = growing_string + '\b';}
\\f {growing_string = growing_string + '\f';}
\\n {growing_string = growing_string + '\n';}
\\r {growing_string = growing_string + '\r';}
\\t {growing_string = growing_string + '\t';}
\\v {growing_string = growing_string + '\v';}

\\\\ {growing_string = growing_string + "\\";
      growing_string = growing_string + "\\";}


\\[0-7]{3} {
    ouais += strtol(text() + 1, 0, 8);
    if (ouais > 255)
        tp.error_ << misc::error::error_type::scan        \
        << tp.location_                                   \
        << "wrong octal\n"                                \
        << misc::escape(text()) << "\n";                 \
    start(INITIAL);
}

\\x[0-9a-fA-F]{2}  {
  growing_string += strtol(text() + 2, 0, 16);
}

\\. {
            tp.error_ << misc::error::error_type::scan        \
            << tp.location_                                   \
            << "wrong escape\n"                                \
            << misc::escape(text()) << "\n";                 \
    start(INITIAL);
}

. {growing_string = growing_string + text();}

}

%%
