%{
    /**********************************************************************
     *  Yihang Yin 1005644144 yinyiha2 yihangmichael.yin@mail.utoronto.ca
     *  Mingdong Li 1000529617 limingdo mingdong.li@mail.utoronto.ca
     *  Interface to the scanner module for CSC467 course project
     **********************************************************************/

#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <string.h>

#include "common.h"
#include "parser.tab.h"

#define YY_USER_INIT { yyin = inputFile; }
#define yyinput      input
#define yTRACE(x)    { if (traceScanner) fprintf(traceFile, "TOKEN %3d : %s\n", x, yytext); }
#define yERROR(x)    { fprintf(errorFile, "\nLEXICAL ERROR, LINE %d: %s\n", yyline, x); errorOccurred = TRUE; }
#define yRET_TRACE(x)      { yTRACE(x); return x; }

/* forward declarations */
int ParseComment(void);
int ParseInt(void);
int ParseFloat(void);
int ParseIdent(void);
int yyline = 1;

%}
%option noyywrap

%%

"/*"                          { if(!ParseComment()) { yyterminate(); } }

[ \t]                         { }
\r?\n                         { yyline++; }
<<EOF>>                       { yyterminate(); }

","			                      { yRET_TRACE(','); }
"+"	                          { yRET_TRACE('+'); }
"-"	                          { yRET_TRACE('-'); }
"*"	                          { yRET_TRACE('*'); }
"/"	                          { yRET_TRACE('/'); }
"^"	                          { yRET_TRACE('^'); }

"("	                          { yRET_TRACE('('); }
")"	                          { yRET_TRACE(')'); }
"["	                          { yRET_TRACE('['); }
"]"	                          { yRET_TRACE(']'); }
"{"	                          { yRET_TRACE('{'); }
"}"	                          { yRET_TRACE('}'); }

"<"	                          { yRET_TRACE('<'); }
">"	                          { yRET_TRACE('>'); }
"="	                          { yRET_TRACE('='); }
"!"	                          { yRET_TRACE('!'); }

";"	                          { yRET_TRACE(';'); }

"&&"                          { yRET_TRACE(AND); }
"||"                          { yRET_TRACE(OR); }
"!="                          { yRET_TRACE(NEQ); }
"<="                          { yRET_TRACE(LEQ); }
">="                          { yRET_TRACE(GEQ); }
"=="                          { yRET_TRACE(EQ); }

if                            { yRET_TRACE(IF); }
else                          { yRET_TRACE(ELSE); }
while                         { yRET_TRACE(WHILE); }

const                         { yRET_TRACE(CONST); }
bool                          { yRET_TRACE(BOOL); }
int                           { yRET_TRACE(INT); }
float                         { yRET_TRACE(FLOAT); }

ivec2   											{ yylval.vec = 1; yRET_TRACE(IVEC); }
ivec3   											{ yylval.vec = 2; yRET_TRACE(IVEC); }
ivec4   											{ yylval.vec = 3; yRET_TRACE(IVEC); }

vec2    											{ yylval.vec = 1; yRET_TRACE(VEC); }
vec3    											{ yylval.vec = 2; yRET_TRACE(VEC); }
vec4    											{ yylval.vec = 3; yRET_TRACE(VEC); }

bvec2   											{ yylval.vec = 1; yRET_TRACE(BVEC); }
bvec3   											{ yylval.vec = 2; yRET_TRACE(BVEC); }
bvec4   											{ yylval.vec = 3; yRET_TRACE(BVEC); }

true                          { yRET_TRACE(TRUE_V); }
false                         { yRET_TRACE(FALSE_V); }

dp3                           { yRET_TRACE(DP3); }
rsq                           { yRET_TRACE(RSQ); }
lit                           { yRET_TRACE(LIT); }

0                             { yylval.int_val = 0; yRET_TRACE(INT_V); }                  
[1-9][0-9]*                   { if(ParseInt()) { yRET_TRACE(INT_V); } yyterminate(); }

(0|([1-9][0-9]*))\.[0-9]*     { if(ParseFloat()) { yRET_TRACE(FLOAT_V); } yyterminate(); }
\.[0-9]+                      { if(ParseFloat()) { yRET_TRACE(FLOAT_V); } yyterminate(); }

[A-Za-z_][A-Za-z0-9_]*        { if(ParseIdent()) { yRET_TRACE(ID); } yyterminate(); }




0[0-9]+                       { yERROR("Octal numbers are not allowed.");  yyterminate(); }
[0-9]+[a-zA-Z_]+              { yERROR("Integers and identifiers/keywords must be separated by whitespace.");  yyterminate(); }
.                             { yERROR("Unknown token");  yyterminate(); }

%%

/* Constants used later */
enum {
  MAX_INT_LIT = (1 << 21) - 1,
  MIN_INT_LIT = -MAX_INT_LIT,
  MAX_IDENT_LEN = 32
};

/* Eat a C-style comment. */
int ParseComment(void) {
  int c1 = 0;
  int c2 = yyinput();
  int curline = yyline;
  for(;;) {
    if (c2 == EOF) {
      fprintf(errorFile, "\nLEXICAL ERROR, LINE %d: Unmatched /*\n", curline);
      errorOccurred = TRUE;
      return 0;
    }
    if ('*' == c1 && '/' == c2) {
      break;
    }
    c1 = c2;
    c2 = yyinput();
    if ('\n' == c1 && EOF != c2) {
      yyline++;
    }
  }
  return 1;
}

/* Convert a string to an integer token. */
int ParseInt(void) {
  long num = strtol(yytext, NULL, 10);
  if(ERANGE == errno) {
    if(LONG_MAX == num || LONG_MIN == num) {
      yERROR("Integer literal is out of range (case 1).");
      return 0;
    }
  }

  if(MAX_INT_LIT < num || MIN_INT_LIT > num) {
    yERROR("Integer literal is out of range (case 2).");
    return 0;
  }

  yylval.int_val = (int) num;
  return 1;
}

/* Convert a string to a float token. */
int ParseFloat(void) {
  double num = strtod(yytext, NULL);
  
  if(ERANGE == errno) {
    if(HUGE_VAL == num || -HUGE_VAL == num) {
      yERROR("Floating point literal is out of range (case 1).");
      return 0;
    }
  }

  /* a NaN value; this is weird */
  if(num != num) {
    yERROR("Floating point literal is NaN.");
    return 0;
  }

  /* out of range; we consider overflow but not underflow */
  if(FLT_MAX < num || -FLT_MAX > num) {
    yERROR("Floating point literal is out of range (case 2).");
    return 0;
  }  

  yylval.float_val = (float) num;
  return 1;
}

/* Convert a string into an identifier token. */
int ParseIdent(void) {
  if(MAX_IDENT_LEN < yyleng) {
    yERROR("Identifier is too long.");
    return 0;
  }

  char *ident = (char *) calloc(yyleng + 1, sizeof(char));
  memcpy(ident, yytext, yyleng);

  yylval.str_val = ident;
  return 1; 
}

