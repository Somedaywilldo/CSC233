%{
/***********************************************************************
 *  Yihang Yin 1005644144 yinyiha2 yihangmichael.yin@mail.utoronto.ca
 *  Mingdong Li 1000529617 limingdo mingdong.li@mail.utoronto.ca
 *
 * Interface to the parser module for CSC467 course project.
 * 
 *   Phase 2: Implement context free grammar for source language, and
 *            parse tracing functionality.
 *   Phase 3: Construct the AST for the source language program.
 ***********************************************************************/

/***********************************************************************
 *  C Definitions and external declarations for this module.
 *
 *  Phase 3: Include ast.h if needed, and declarations for other global or
 *           external vars, functions etc. as needed.
 ***********************************************************************/

#include <string.h>
#include "common.h"
//#include "ast.h"
//#include "symbol.h"
//#include "semantic.h"
#define YYERROR_VERBOSE
#define yTRACE(x)    { if (traceParser) fprintf(traceFile, "%s\n", x); }

void yyerror(const char* s);    /* what to do in case of error            */
int yylex();              /* procedure for calling lexical analyzer */
extern int yyline;        /* variable holding current line number   */

%}

/***********************************************************************
 *  Yacc/Bison declarations.
 *  Phase 2:
 *    1. Add precedence declarations for operators (after %start declaration)
 *    2. If necessary, add %type declarations for some nonterminals
 *  Phase 3:
 *    1. Add fields to the union below to facilitate the construction of the
 *       AST (the two existing fields allow the lexical analyzer to pass back
 *       semantic info, so they shouldn't be touched).
 *    2. Add <type> modifiers to appropriate %token declarations (using the
 *       fields of the union) so that semantic information can by passed back
 *       by the scanner.
 *    3. Make the %type declarations for the language non-terminals, utilizing
 *       the fields of the union as well.
 ***********************************************************************/

%{
#define YYDEBUG 1
%}


// TODO:Modify me to add more data types
// Can access me from flex useing yyval

%union {
    char *str_val;
    int int_val;
    float float_val;
    int vec;
    int func; 
}

// Tokens are classified by the types acording to MiniGLSL specification.

%token <vec> IVEC
%token <vec> BVEC
%token <vec> VEC

%token <float_val>  FLOAT_V
%token <int_val>    INT_V 
%token <str_val>    ID 
   
// Data types
%token INT BOOL FLOAT 
%token FUNC

// Binary operators
%token AND OR EQ NEQ LEQ GEQ LT GT          
// LT: less than; LEQ: less than or equal; GT: greater than; GE: greater than or equal.

// Key words
%token IF ELSE WHILE

// Qualifiers
%token CONST 

// Boolean Literal
TRUE_V FALSE_V


// Operators' precedence and associativity
// Should be the reverse order of that in Handout2
%left       OR
%left       AND
%nonassoc   EQ NEQ LEQ GEQ '<' '>'
%left       '+' '-'
%left       '*' '/'
%right      '^'
%nonassoc   '!' UMINUS
%left       '(' ')' '[' ']'




%start    program

%%

/***********************************************************************
 *  Yacc/Bison rules
 *  Phase 2:
 *    1. Replace grammar found here with something reflecting the source
 *       language grammar
 *    2. Implement the trace parser option of the compiler
 *  Phase 3:
 *    1. Add code to rules for construction of AST.
 ***********************************************************************/
program:		
	scope 										{yTRACE("program -> scope");}
	; 
scope:
	'{' declarations statements '}'				{yTRACE("scope -> { declarations statements }");}
	;

declarations:
	declarations declaration 					{yTRACE("declarations -> declarations declaration");}	|					
												{yTRACE("declarations -> epsilon");}
	;
statements:
	statements statement 						{yTRACE("statements -> statements statement");}			|
												{yTRACE("statements -> epsilon");}
	;
/***************************/
#XX
declaration:									
	type identifier ';'							{yTRACE("declaration -> epsilon");}						|
	type identifier ' =' expression ';'			{yTRACE("statements -> epsilon");}						|
	'const' type identifier ' =' expression ';'	{yTRACE("statements -> epsilon");}						|
												{yTRACE("statements -> epsilon");}
	;



statement:
	variable '=' expression ';'					{yTRACE("statement -> variable = expression;");}		|
	'if' '(' expression ')' statement else_statement 
												{yTRACE("statement -> if (expression) statement else_statement");}	|
	'while' '(' expression ')' statement 		{yTRACE("statement -> while (expression) statement");}	|
	scope										{yTRACE("statement-> scope");}							|
	';'
	;
else_statement:						
	'else' statement 							{yTRACE("else_statement-> else statement");}			|
												{yTRACE("else_statement-> epsilon");}					
	;
/*********************************************/
#XX
type:
	'int'|'ivec2'|'ivec3'|'ivec4'
	'bool'|'bvec2'|'bvec3'|'bvec4'
	'float'|'vec2'|'vec3'|'vec4'




expression:
	constructor									{yTRACE("expression -> constructor");}					|
	function 									{yTRACE("expression -> constructor");}					|
	integer_literal								{yTRACE("expression -> constructor");}					|
	float_literal								{yTRACE("expression -> constructor");}					|
	'true'|'false'								{yTRACE("expression -> constructor");}					|
	variable									{yTRACE("expression -> variable");}						|
	unary_op expression							{yTRACE("expression -> unary_op expression");}			|
	expression binary_op expression 			{yTRACE("expression -> expression binary_op expression");}|
	'(' expression ')'							{yTRACE("expression -> (expression)");}
	;

/*************************************/
#XX
variable:
	identifier									{fTRACE("variable-> ID   __ID: %s", $1);}
	identifier'['integer_literal']'





unary_op:
	'!'											{yTRACE("unary_op -> !");}								|
	'−'											{yTRACE("unary_op -> -");}
	;
binary_op:
	'&&'										{yTRACE("binary_op -> &&");}							|
	'||'										{yTRACE("binary_op -> ||");}							|
	'=='										{yTRACE("binary_op -> ==");}							|
	'!=' 										{yTRACE("binary_op -> !=");}							|
	'<' 										{yTRACE("binary_op -> <");}								|
	'<='										{yTRACE("binary_op -> <=");}							|
	'>' 										{yTRACE("binary_op -> >");}								|
	'<'											{yTRACE("binary_op -> <");}								|
	'+' 										{yTRACE("binary_op -> +");}								|
	'−' 										{yTRACE("binary_op -> -");}								|
	'∗' 										{yTRACE("binary_op -> *");}								|
	'/'											{yTRACE("binary_op -> /");}								|
	;
constructor:
	type '(' arguments ')'						{yTRACE("constructor -> /");}							
	;
/***************************************/
#XX
function:
	function_name '(' arguments_opt ')'			


#XX
function_name:
	'dp3'|'lit'|'rsq'

arguments_opt:
	arguments 									{yTRACE("arguments_opt -> arguments");}					|					| 
												{yTRACE("arguments_opt -> epsilon");}
	;
arguments:
	arguments ',' expression					{yTRACE("arguments -> arguments , expression");}		|
	expression									{yTRACE("arguments -> arguments , expression");}
	;



%%

/***********************************************************************ol
 * Extra C code.
 *
 * The given yyerror function should not be touched. You may add helper
 * functions as necessary in subsequent phases.
 ***********************************************************************/
void yyerror(const char* s) {
  if (errorOccurred)
    return;    /* Error has already been reported by scanner */
  else
    errorOccurred = 1;
        
  fprintf(errorFile, "\nPARSER ERROR, LINE %d",yyline);
  if (strcmp(s, "parse error")) {
    if (strncmp(s, "parse error, ", 13))
      fprintf(errorFile, ": %s\n", s);
    else
      fprintf(errorFile, ": %s\n", s+13);
  } else
    fprintf(errorFile, ": Reading token %s\n", yytname[YYTRANSLATE(yychar)]);
}

