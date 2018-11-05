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

//vec means the number of elements-1
%union {
    char *str_val;
    int int_val;
    float float_val;
    int vec_size;
}

// Tokens are classified by the types acording to MiniGLSL specification.

%token <vec_size> IVEC
%token <vec_size> BVEC
%token <vec_size> VEC

%token <float_val>  FLOAT_V
%token <int_val>    INT_V 
%token <str_val>    ID 
   
%token			RSQ LIT DP3

// Data types
%token INT BOOL FLOAT 

// Binary operators
%token AND OR EQ NEQ LEQ GEQ         

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
%left		'&'
%nonassoc   '=' EQ NEQ LEQ GEQ '<' '>'
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

declaration:									
	type ID ';'									{yTRACE("declaration -> type ID ';'"); }				|
	type ID '=' expression ';'					{yTRACE("declaration -> type ID '=' expression ';'"); }	|
	CONST type ID '=' expression ';'			{yTRACE("declaration -> CONST type ID '=' expression ';'"); }|
												{yTRACE("declaration -> type epsilon ';'"); }
	;
statement:
	variable '=' expression ';'					{yTRACE("statement -> variable = expression;");}		|
	IF '(' expression ')' statement else_statement 
												{yTRACE("statement -> if (expression) statement else_statement");}	|
	WHILE '(' expression ')' statement 			{yTRACE("statement -> while (expression) statement");}	|
	scope										{yTRACE("statement-> scope");}							|
	';'
	;
else_statement:						
	ELSE statement 								{yTRACE("else_statement-> else statement");}			|
												{yTRACE("else_statement-> epsilon");}					
	;
type:
	INT 										{yTRACE("type -> INT");} 								|
	IVEC 										{yTRACE("type -> IVEC");}								|
	FLOAT 										{yTRACE("type -> FLOAT");} 								| 
	VEC											{yTRACE("type -> VEC");}								|
	BOOL 										{yTRACE("type -> BOOL");} 								| 
	BVEC										{yTRACE("type -> BVEC");}								
	;
expression:
	constructor									{yTRACE("expression -> constructor");}					|
	function 									{yTRACE("expression -> function");}						|
	INT_V										{yTRACE("expression -> INT_V");}						|
	FLOAT_V										{yTRACE("expression -> FLOAT_V");}						|
	TRUE_V										{yTRACE("expression -> TRUE_V");}						|
	FALSE_V										{yTRACE("expression -> FALSE_V");}						|
	variable									{yTRACE("expression -> variable");}						|
	unary_op expression							{yTRACE("expression -> unary_op expression");}			|
	expression AND expression					{yTRACE("expression -> expression AND expression");}	|
	expression OR  expression					{yTRACE("expression -> expression OR  expression");}	|
	expression EQ  expression					{yTRACE("expression -> expression EQ  expression");}	|
	expression NEQ expression 					{yTRACE("expression -> expression NEQ expression");}	|
	expression LEQ expression					{yTRACE("expression -> expression LEQ expression");}	|
	expression GEQ expression					{yTRACE("expression -> expression GEQ expression");}	|
	expression '<' expression 					{yTRACE("expression -> expression '<' expression");}	|
	expression '>' expression 					{yTRACE("expression -> expression '>' expression");}	|
	expression '+' expression 					{yTRACE("expression -> expression '+' expression");}	|
	expression '−' expression 					{yTRACE("expression -> expression '-' expression");}	|
	expression '∗' expression 					{yTRACE("expression -> expression '*' expression");}	|
	expression '/' expression					{yTRACE("expression -> expression '/' expression");}	|
	expression '^' expression					{yTRACE("expression -> expression '^' expression");}	|
	'(' expression ')'							{yTRACE("expression -> (expression)");}
	;
variable:
	ID											{yTRACE("variable -> ID");}								|
	ID '[' INT_V ']'							{yTRACE("variable -> ID '[' INT_V ']'");}
	;
unary_op:
	'!'											{yTRACE("unary_op -> '!'");}							|
	'−' %prec UMINUS							{yTRACE("unary_op -> UMINUS");}
	;
constructor:
	type '(' arguments ')'						{yTRACE("constructor -> type '(' arguments ')'");}							
	;
function:
	function_name '(' arguments_opt ')'			{yTRACE("function -> function_name '(' arguments_opt ')'");}		
	;
function_name:
	DP3											{yTRACE("function_name -> DP3");}						|
	LIT											{yTRACE("function_name -> LIT");}						|
	RSQ											{yTRACE("function_name -> RSQ");}						|
	;
arguments_opt:
	arguments 									{yTRACE("arguments_opt -> arguments");}					| 
												{yTRACE("arguments_opt -> epsilon");}
	;
arguments:
	arguments ',' expression					{yTRACE("arguments -> arguments ',' expression");}		|
	expression									{yTRACE("arguments -> arguments  expression");}
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

