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
%expect 0
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


/*--------------------------------.
| Support for the non-terminals.  |
`--------------------------------*/

%code requires
{
# include <ast/fwd.hh>
// Provide the declarations of the following classes for the
// %destructor clauses below to work properly.
# include <ast/exp.hh>
# include <ast/var.hh>
# include <ast/ty.hh>
# include <ast/name-ty.hh>
# include <ast/field.hh>
# include <ast/field-init.hh>
# include <ast/function-dec.hh>
# include <ast/type-dec.hh>
# include <ast/var-dec.hh>
# include <ast/chunk.hh>
# include <ast/chunk-list.hh>
}

  // FIXME: Some code was deleted here (Printers and destructors).

/*-----------------------------------------.
| Code output in the implementation file.  |
`-----------------------------------------*/

%code
{
# include <parse/tweast.hh>
# include <misc/separator.hh>
# include <misc/symbol.hh>
# include <ast/all.hh>
# include <ast/libast.hh>
# include <parse/tiger-driver.hh>

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
  // FIXME: Some code was deleted here (More %types).

  // FIXME: Some code was deleted here (Priorities/associativities).
//%precedence DO
//%right "else" "then"
//%precedence OF
%precedence ELSE
%precedence THEN DO
%precedence ASSIGN
%left "|"
%left "&"
%left ","
%nonassoc ">=" "<=" "=" "<>"
%nonassoc ">"
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

%start program

%%
program:
  /* Parsing a source program.  */
  exp
   { tp.ast_ = $1; }
| /* Parsing an imported file.  */
  chunks
   { tp.ast_ = $1; }
;

<<<<<<< HEAD
list_id: list_id "," list_id
       | ID "=" exp
       ;
=======
exp:
  INT
   { $$ = tp.td_.make_IntExp(@$, $1); }
  // FIXME: Some code was deleted here (More rules).
>>>>>>> 2025-tc-2.0

list_exp: list_exp "," list_exp
        | exp
;

%token EXP "_exp";
exps: %empty
    | list_exp;
exp:
    NIL
  | INT
  | STRING
   /* Array and record creations. */

  //| typeid "[" exp "]" "of" exp
  | typeid LBRACE list_id RBRACE
  | typeid LBRACE RBRACE

  /* Variables, field, elements of an array. */
  | lvalue

  /* Function call. */
  | ID "(" ")"
  | ID "(" list_exp ")"
    
  /* Operations. */
  | exp "|" exp
  | exp "&" exp 
  | exp "<=" exp
  | exp "=" exp
  | exp "<>" exp
  | exp ">" exp
  | exp ">=" exp
  | "-" exp
  | exp "+" exp
  | exp "-" exp
  | exp "*" exp
  | exp "/" exp
  | "(" exps ")"

  /* Assignment. */
  | lvalue ":=" exp

  /* Control structures. */
  | "if" exp "then" exp
  | "if" exp "then" exp "else" exp
  | "while" exp "do" exp
  | "for" ID ":=" exp "to" exp "do" exp
  | "break"
  | "let" chunks "in" exps "end"

  /* Cast of an expression to a given type */
  | "_cast" "(" exp "," ty ")"
  /* An expression metavariable */
  | "_exp" "(" INT ")"
  ;

lvalue:
    ID
  /* Record field access. */
  | lvalue "." ID
  /* Array subscript. */
  | lvalue "[" exp "]"
  /* A l-value metavariable
   | "_lvalue" "(" INT ")"*/
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
<<<<<<< HEAD
  %empty
| tychunk chunks      
| funchunk chunks
| varchunk chunks
|"import" STRING chunks;
=======
  %empty                  { $$ = tp.td_.make_ChunkList(@$); }
| tychunk   chunks        { $$ = $2; $$->push_front($1); }
  // FIXME: Some code was deleted here (More rules).
;
>>>>>>> 2025-tc-2.0

/*--------------------.
| Type Declarations.  |
`--------------------*/

tychunk:
  /* Use `%prec CHUNKS' to do context-dependent precedence and resolve a
     shift-reduce conflict. */
  tydec %prec CHUNKS  { $$ = tp.td_.make_TypeChunk(@1); $$->push_front(*$1); }
| tydec tychunk       { $$ = $2; $$->push_front(*$1); }
;

funchunk:
        fundec %prec CHUNKS  
    | fundec funchunk       
;

varchunk:
        vardec

;

vardec:
      "var" ID ":=" exp
    | "var" ID  ":" typeid ":=" exp 
;


tydec:
  "type" ID "=" ty { $$ = tp.td_.make_TypeDec(@$, $2, $4); }
;

fundec:
      "function" ID "(" tyfields ")" ":" typeid "=" exp
    | "primitive" ID "(" tyfields ")" ":" typeid
  ;

ty:
  typeid               { $$ = $1; }
| "{" tyfields "}"     { $$ = tp.td_.make_RecordTy(@$, $2); }
| "array" "of" typeid  { $$ = tp.td_.make_ArrayTy(@$, $3); }
;

tyfields:
  %empty               { $$ = tp.td_.make_fields_type(); }
| tyfields.1           { $$ = $1; }
;

tyfields.1:
<<<<<<< HEAD
  tyfields.1 "," tyfield
| tyfield                
=======
  tyfields.1 "," tyfield { $$ = $1; $$->emplace_back($3); }
| tyfield                { $$ = tp.td_.make_fields_type($1); }
>>>>>>> 2025-tc-2.0
;

tyfield:
  ID ":" typeid     { $$ = tp.td_.make_Field(@$, $1, $3); }
;

%token NAMETY "_namety";
typeid:
  ID                    { $$ = tp.td_.make_NameTy(@$, $1); }
  /* This is a metavariable. It it used internally by TWEASTs to retrieve
     already parsed nodes when given an input to parse. */
| NAMETY "(" INT ")"    { $$ = metavar<ast::NameTy>(tp, $3); }
;

%%

void
parse::parser::error(const location_type& l, const std::string& m)
{
  // FIXME: Some code was deleted here.
  tp.error_ << misc::error::error_type::parse << l << " : "  << m; // tp.location_ replace l ?
}
