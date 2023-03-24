                                                                // -*- C++ -*-
%require "3.8"
%language "c++"
// Set the namespace name to `parse', instead of `yy'.
%define api.prefix {parse}
%define api.namespace {parse}
%define api.parser.class {parser}
%define api.value.type variant
%define api.token.constructor

// We use a GLR parser because it is able to handle Shift-Reduce and
// Reduce-Reduce conflicts by forking and testing each way at runtime. GLR
// permits, by allowing few conflicts, more readable and maintainable grammars.
%glr-parser
%skeleton "glr2.cc"

// In TC, we expect the GLR to resolve one Shift-Reduce and zero Reduce-Reduce
// conflict at runtime. Use %expect and %expect-rr to tell Bison about it.
  // FIXME: Some code was deleted here (Other directives).
%expect 1
%expect-rr 0
%define parse.error verbose
%defines
%debug
// Prefix all the tokens with TOK_ to avoid colisions.
%define api.token.prefix {TOK_}

/* We use pointers to store the filename in the locations.  This saves
   space (pointers), time (no deep copy), but leaves the problem of
   deallocation.  This would be a perfect job for a misc::symbol
   object (passed by reference), however Bison locations require the
   filename to be passed as a pointer, thus forcing us to handle the
   allocation and deallocation of this object.

   Nevertheless, all is not lost: we can still use a misc::symbol
   object to allocate a flyweight (constant) string in the pool of
   symbols, extract it from the misc::symbol object, and use it to
   initialize the location.  The allocated data will be freed at the
   end of the program (see the documentation of misc::symbol and
   misc::unique).  */
%define api.filename.type {const std::string}
%locations

/*---------------------.
| Support for tokens.  |
`---------------------*/
%code requires
{
#include <string>
#include <misc/algorithm.hh>
#include <misc/separator.hh>
#include <misc/symbol.hh>
#include <parse/fwd.hh>
#include <ast/all.hh>
  // Pre-declare parse::parse to allow a ``reentrant'' parsing within
  // the parser.
  namespace parse
  {
    ast_type parse(Tweast& input);
  }
}

// The parsing context.
%param { ::parse::TigerParser& tp }
%parse-param { ::parse::Lexer& lexer }

%printer { yyo << $$; } <int> <std::string> <misc::symbol>;

%token <std::string>    STRING "string"
%token <misc::symbol>   ID     "identifier"
%token <int>            INT    "integer"


/*-----------------------------------------.
| Code output in the implementation file.  |
`-----------------------------------------*/

%code
{
# include <parse/tweast.hh>
# include <misc/separator.hh>
# include <misc/symbol.hh>

  namespace
  {

    /// Get the metavar from the specified map.
    template <typename T>
    T*
    metavar(parse::TigerParser& tp, unsigned key)
    {
      parse::Tweast* input = tp.input_;
      return input->template take<T>(key);
    }

  }
}

%code
{
  #include <parse/scantiger.hh>  // header file generated with reflex --header-file
  #undef yylex
  #define yylex lexer.lex  // Within bison's parse() we should invoke lexer.lex(), not the global lex()
}

// Definition of the tokens, and their pretty-printing.
%token AND          "&"
       ARRAY        "array"
       ASSIGN       ":="
       BREAK        "break"
       CAST         "_cast"
       CLASS        "class"
       COLON        ":"
       COMMA        ","
       DIVIDE       "/"
       DO           "do"
       DOT          "."
       ELSE         "else"
       END          "end"
       EQ           "="
       EXTENDS      "extends"
       FOR          "for"
       FUNCTION     "function"
       GE           ">="
       GT           ">"
       IF           "if"
       IMPORT       "import"
       IN           "in"
       LBRACE       "{"
       LBRACK       "["
       LE           "<="
       LET          "let"
       LPAREN       "("
       LT           "<"
       MINUS        "-"
       METHOD       "method"
       NE           "<>"
       NEW          "new"
       NIL          "nil"
       OF           "of"
       OR           "|"
       PLUS         "+"
       PRIMITIVE    "primitive"
       RBRACE       "}"
       RBRACK       "]"
       RPAREN       ")"
       SEMI         ";"
       THEN         "then"
       TIMES        "*"
       TO           "to"
       TYPE         "type"
       VAR          "var"
       WHILE        "while"
       EOF 0        "end of file"


%type <ast::Exp*>             exp
%type <ast::ChunkList*>       chunks
%type <ast::TypeChunk*>       tychunk
%type <ast::TypeDec*>         tydec
%type <ast::NameTy*>          typeid
%type <ast::Ty*>              ty
%type <ast::Field*>           tyfield
%type <ast::fields_type*>     tyfields tyfields.1
%type <ast::fieldinits_type*> list_id
%type <ast::Var*>             lvalue
%type <ast::VarChunk*>        varchunk funfields funfields.1 
%type <ast::VarDec*>          vardec funfield
%type <ast::FunctionChunk*>   funchunk
%type <ast::exps_type*>       exps list_exp
%type <ast::FunctionDec*>     fundec








  // FIXME: Some code was deleted here (Priorities/associativities).
//%precedence DO
//%right "else" "then"
//%precedence O

%precedence DO THEN
%precedence ELSE
%precedence ASSIGN
%left "|"
%left "&"
%left "," ";"
%nonassoc ">=" "<=" "=" "<>"
%nonassoc ">" "<"
%left "+" "-"
%left "*" "/"

// Solving conflicts on:
// let type foo = bar
//     type baz = bat
// which can be understood as a list of two TypeChunk containing
// a unique TypeDec each, or a single TypeChunk containing two TypeDec.
// We want the latter.
%precedence CHUNKS
%precedence TYPE

  // FIXME: Some code was deleted here (Other declarations).
%precedence FUNCTION PRIMITIVE
%precedence OF


%start program

%%
program:
  /* Parsing a source program.  */
  exp                                   { tp.ast_ = $1; }
   
| /* Parsing an imported file.  */
  chunks                                { tp.ast_ = $1; }
;

list_id: ID "=" exp "," list_id         { $$->push_back(tp.td_.make_FieldInit(@$, $1, $3)); }
       | ID "=" exp                     { $$ = tp.td_.make_fieldinits_type(); $$->push_back(tp.td_.make_FieldInit(@$, $1, $3)); }
       ;
/*
list_id: list_id "," ID "=" exp {
            $$ = $1;
             ast::Field* newfield = tp.td_.make_FieldInit($3, $5);
            $$->push_back(newfield);
        }
       | ID "=" exp {
            $$ = tp.td_.make_FieldInit(@$, $1, $3);
        }
       ;
*/
list_exp: exp "," list_exp              { $$ = tp.td_.make_exps_type($1); $$->emplace_back($1); }
        | exp                           { $$ = tp.td_.make_exps_type($1); }
;

%token EXP "_exp";
exps: exp ";" exps           { $$ = $3; $$->push_back($1); }
    | exp                    { $$ = tp.td_.make_exps_type($1); }
    ;

exp:
    NIL                 { $$ = tp.td_.make_NilExp(@$); }
  | INT                 { $$ = tp.td_.make_IntExp(@$, $1); }
  | STRING              { $$ = tp.td_.make_StringExp(@$, $1); }
   /* Array and record creations. */

  | ID  "[" exp "]" "of" exp            { $$ = tp.td_.make_ArrayExp(@$, tp.td_.make_NameTy(@$,$1), $3, $6); }
  | typeid  LBRACE list_id RBRACE       { $$ = tp.td_.make_RecordExp(@$, $1, $3); }
  | typeid LBRACE RBRACE                { $$ = tp.td_.make_RecordExp(@$, $1, nullptr); }

  /* Variables, field, elements of an array. */
  | lvalue                              { $$ = $1; }

  /* Function call. */
  | ID "(" ")"          { $$ = tp.td_.make_CallExp(@$, $1, nullptr); }
  | ID "(" list_exp ")" { $$ = tp.td_.make_CallExp(@$, $1, $3); }

    
  /* Operations. */
  | exp "|" exp         {
                            $$ = tp.enable_extensions().parse(Tweast()
                               << "if"
                               <<    /* erreur ici*/
                                   "_exp(0)"
                                  
                               << "= 0 else 1 then"
                               << 
                                    "_exp(1)"
                                  
                               << "<> 0 else 0");
                          }
 

  | exp "&" exp         { 
                            $$ = tp.enable_extensions().parse(Tweast()
                               << "if"
                               << 
                                   "_exp(0)"
                                  
                               << "then"
                               << 
                                    "_exp(1)"
                                  
                               << "<> 0 else 0");
                          }

  | exp "<=" exp        { $$ = tp.td_.make_OpExp(@$, $1, ast::OpExp::Oper::le, $3); }
  | exp "=" exp         { $$ = tp.td_.make_OpExp(@$, $1, ast::OpExp::Oper::eq, $3); }
  | exp "<>" exp        { $$ = tp.td_.make_OpExp(@$, $1, ast::OpExp::Oper::ne, $3); }
  | exp "<" exp         { $$ = tp.td_.make_OpExp(@$, $1, ast::OpExp::Oper::lt, $3); }
  | exp ">" exp         { $$ = tp.td_.make_OpExp(@$, $1, ast::OpExp::Oper::gt, $3); }
  | exp ">=" exp        { $$ = tp.td_.make_OpExp(@$, $1, ast::OpExp::Oper::ge, $3); }
  | "-" exp             {
                            $$ = tp.enable_extensions().parse(Tweast()
                               << "0 -"
                               <<
                                    "_exp("
                                << $2
                                << ")" )
                                  ;
                        }


  | exp "+" exp         { $$ = tp.td_.make_OpExp(@$, $1, ast::OpExp::Oper::add, $3); }
  | exp "-" exp         { $$ = tp.td_.make_OpExp(@$, $1, ast::OpExp::Oper::sub, $3); }
  | exp "*" exp         { $$ = tp.td_.make_OpExp(@$, $1, ast::OpExp::Oper::mul, $3); }
  | exp "/" exp         { $$ = tp.td_.make_OpExp(@$, $1, ast::OpExp::Oper::div, $3); }
  | "(" exps ")"        { $$ = tp.td_.make_SeqExp(@$, $2); }
  | "(" ")"             { $$ = tp.td_.make_SeqExp(@$, nullptr); }

  /* Assignment. */
  | lvalue ":=" exp     { $$ = tp.td_.make_AssignExp(@$, $1, $3); }

  /* Control structures. */
  | "if" exp "then" exp                 { $$ = tp.td_.make_IfExp(@$, $2, $4); }
  | "if" exp "then" exp "else" exp      { $$ = tp.td_.make_IfExp(@$, $2, $4, $6); }
  | "while" exp "do" exp                { $$ = tp.td_.make_WhileExp(@$, $2, $4); }
  | "for" ID ":=" exp "to" exp "do" exp { $$ = tp.td_.make_ForExp(@$, tp.td_.make_VarDec(@$, $2, nullptr, $4), $6 ,$8); }
  | "break"                             { $$ = tp.td_.make_BreakExp(@$); }
  | "let" chunks "in" exps "end"        { $$ = tp.td_.make_LetExp(@$, $2, tp.td_.make_SeqExp(@4, $4)); }
  | "let" chunks "in" "end"             { $$ = tp.td_.make_LetExp(@$, $2, nullptr); }



  /* Cast of an expression to a given type */
  | "_cast" "(" exp "," ty ")"          { $$ = tp.td_.make_CastExp(@$, $3, $5); }
  /* An expression metavariable */
  | "_exp" "(" INT ")"                  { $$ = metavar<ast::Exp>(tp, $3); }
  ;
%token LVALUE "_lvalue";
lvalue:
    ID                                  { $$ = tp.td_.make_SimpleVar(@$, $1); }
  /* Record field access. */
  | lvalue "." ID                       { $$ = tp.td_.make_FieldVar(@$, $1, $3); }
  /* Array subscript. */
  | lvalue "[" exp "]"                  { $$ = tp.td_.make_SubscriptVar(@$, $1, $3); }
  /* A l-value metavariable*/
   | "_lvalue" "(" INT ")"              { $$ = metavar<ast::Var>(tp, $3);  }
  ;


//op: "+" | "-" | "*" | "/" | "=" | "<>" | ">" | "<" | ">=" | "<=" | "&" | "|" ;
/*---------------.
| Declarations.  |
`---------------*/

%token CHUNKS "_chunks";

chunks:
  /* Chunks are contiguous series of declarations of the same type
     (TypeDec, FunctionDec...) to which we allow certain specfic behavior like
     self referencing.
     They are held by a ChunkList, that can be empty, like in this case:
        let
        in
            ..
        end
     which is why we end the recursion with a %empty. */
  %empty                                 { $$ = tp.td_.make_ChunkList(@$); }
| tychunk chunks                         { $$ = $2; $$->push_front($1); }
| funchunk chunks                        { $$ = $2; $$->push_front($1); }
| varchunk chunks                        { $$ = $2; $$->push_front($1); }
|"import" STRING chunks                  { $$ = $3; tp.parse_import($2, @$);}
/* A list of chunk metavariable */
| "_chunks" "(" INT ")" chunks           { $$ = $5; $$->splice_back(*metavar<ast::ChunkList>(tp, $3)); }
;

/*--------------------.
| Type Declarations.  |
`--------------------*/

tychunk:
  /* Use `%prec CHUNKS' to do context-dependent precedence and resolve a
     shift-reduce conflict. */
  tydec %prec CHUNKS                    { $$ = tp.td_.make_TypeChunk(@$); }
| tydec tychunk                         { $$ = $2; $$->push_front(*$1); }
;

funchunk:
        fundec %prec CHUNKS            { $$ = tp.td_.make_FunctionChunk(@$); $$->push_front(*$1); }
        | fundec funchunk              { $$ = $2; $$->push_front(*$1); }
   
;

varchunk:
        vardec                          { $$ = tp.td_.make_VarChunk(@$); }

;

vardec:
      "var" ID ":=" exp                 { $$ = tp.td_.make_VarDec(@$, $2, nullptr, $4); }
    | "var" ID  ":" typeid ":=" exp     { $$ = tp.td_.make_VarDec(@$, $2, $4, $6); }
;


tydec:
  "type" ID "=" ty                      { $$ = tp.td_.make_TypeDec(@$, $2, $4); } 
;

fundec:
      "function" ID "(" funfields ")" ":" typeid "=" exp
                            { $$ = tp.td_.make_FunctionDec(@$, $2, $4, $7, $9); } 
    | "primitive" ID "(" funfields ")" ":" typeid
                            { $$ = tp.td_.make_FunctionDec(@$, $2, $4, $7, nullptr); }
    | "function" ID "(" funfields ")"  "=" exp
                            { $$ = tp.td_.make_FunctionDec(@$, $2, $4, nullptr, $7); }
    | "primitive" ID "(" funfields ")"
                            { $$ = tp.td_.make_FunctionDec(@$, $2, $4, nullptr, nullptr); }


  ;

ty:
  typeid                                { $$ = $1; }
| "{" tyfields "}"                      { $$ = tp.td_.make_RecordTy(@$, $2); }
| "array" "of" typeid                   { $$ = tp.td_.make_ArrayTy(@$, $3); }
;

tyfields:
  %empty                                { $$ = tp.td_.make_fields_type(); }
| tyfields.1                            { $$ = $1; }
;

tyfields.1:
  tyfields.1 "," tyfield                { $$ = $1; $$->emplace_back($3); }
| tyfield                               { $$ = tp.td_.make_fields_type($1); }
;

tyfield:
  ID ":" typeid                         { $$ = tp.td_.make_Field(@$, $1, $3); }
;

funfields:
  %empty                                  { $$ = tp.td_.make_VarChunk(@$); }
  | funfields.1                           { $$ = $1; }
;
funfields.1:
  funfields.1 "," funfield              { $$ = $1; $$->emplace_back(*$3); }
| funfield                              { $$ = tp.td_.make_VarChunk(@$); $$->emplace_back(*$1); } 
;
funfield:
  ID ":" typeid                         { $$ = tp.td_.make_VarDec(@$, $1, $3, nullptr); }
;


%token NAMETY "_namety";
typeid:
      ID                                { $$ = tp.td_.make_NameTy(@$, $1); }
  /* This is a metavariable. It it used internally by TWEASTs to retrieve
     already parsed nodes when given an input to parse. */
| NAMETY "(" INT ")"                    { $$ = metavar<ast::NameTy>(tp, $3);  }
;

%%

void
parse::parser::error(const location_type& l, const std::string& m)
{
  // FIXME: Some code was deleted here.
  tp.error_ << misc::error::error_type::parse << l << " : "  << m; // tp.location_ replace l ?
}
