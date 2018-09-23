%{
    /**********************************************************************
     *  Interface to the scanner module for CSC467 course project
     **********************************************************************/
    
    
    #include "common.h"
    #include "parser.tab.h"
    #include "string.h"
    
    
    #define YY_USER_INIT { yyin = inputFile; }
    #define yyinput      input
    #define yTRACE(x)    { if (traceScanner) fprintf(traceFile, "TOKEN %3d : %s\n", x, yytext); }
    #define yERROR(x)    { fprintf(errorFile, "\nLEXICAL ERROR, LINE %d: %s\n", yyline, x); errorOccurred = TRUE; yyterminate(); }
    #define yRET_TRACE(x) { yTRACE(x) return x;}
    #define MAX_ID_LENGTH 512

    int CheckInt(void);
    int yyline = 1;
    
%}

%option noyywrap


WS      [ \t]+


LETTER  [A-Za-z]
DIGIT   [0-9]
NUMBER  {digit}+(\.{digit}+)?(E[+-]?{digit}+)?

# 正则问题，ID中的下划线没有考虑
ID_reg      {letter}({letter}|digit}){1,MAX_ID_LENGTH}
ID_reg 	      [a-zA-Z][a-zA-Z_]{1,MAX_ID_LENGTH}
# 整数、实数和ID的最大长度没有限制，尽量不要使用+或者*这样的正则。
INT_V_reg     0|([1-9][0-9]*)
FLOAT_V_reg   {integer}\.{integer}([eE][+\-]?{integer})? 


%%

{WS} {}

# \n是否应该算作是white space？，我认为不能算，否则可能没法给出错误行号。
"\n" {yyline++;}

int   {yRET_TRACE(INT)}
ivec2 {yRET_TRACE(IVEC2)}
ivec3 {yRET_TRACE(IVEC3)}
ivec4 {yRET_TRACE(IVEC4)}

float  {yRET_TRACE(FLOAT)}
vec2   {yRET_TRACE(VEC2)}
vec3   {yRET_TRACE(VEC3)}
vec4   {yRET_TRACE(VEC4)}

bool     {yRET_TRACE(BOOL)}
bvec2    {yRET_TRACE(BVEC2)}
bvec3    {yRET_TRACE(BVEC3)}
bvec4    {yRET_TRACE(BVEC4)}

dp3       {yRET_TRACE(DP3)}
lit       {yRET_TRACE(LIT)}
rsq       {yRET_TRACE(RSQ)}

"+"           {yRET_TRACE(PLUS)}
"-"           {yRET_TRACE(MINUS)}
"*"           {yRET_TRACE(MULT)}
"/"           {yRET_TRACE(DIV)}
"^"           {yRET_TRACE(POW)}
"="           {yRET_TRACE(ASSIGN)}

"!"           {yRET_TRACE(NOT)}
"&&"          {yRET_TRACE(AND)}
"||"          {yRET_TRACE(OR)}

"=="          {yRET_TRACE(EQ)}
"!="          {yRET_TRACE(NEQ)}
"<"           {yRET_TRACE(LT)}
"<="          {yRET_TRACE(LE)}
">"           {yRET_TRACE(GT)}
">="          {yRET_TRACE(GE)}

"("           {yRET_TRACE(LSB)}
")"           {yRET_TRACE(RSB)}
"["           {yRET_TRACE(LMB)}
"]"           {yRET_TRACE(RMB)}
"{"           {yRET_TRACE(LBB)}
"}"           {yRET_TRACE(RBB)}

if        {yRET_TRACE(IF)}
else      {yRET_TRACE(ELSE)}
while     {yRET_TRACE(WHILE)}

const     {yRET_TRACE(CONST)}

";"        {yRET_TRACE(SEMI)}
","        {yRET_TRACE(COMMA)}

true {yRET_TRACE(TRUE_V)} /*TRUE VALUE*/
false {yRET_TRACE(FALSE_V)}


# 联合变量的意义还需要明确一下
{integer} {
    yylval.ival = atoi(yytext);
    yRET_TRACE(INT_V);
}

{float} {
    yylval.fval = atof(yytext);
    yRET_TRACE(FLOAT_V);
}

{id} {
    if (strlen(yytext) > 512)
        yERROR("ERROR: Identifier exceeds maximum_length");
    yylval.sval = yytext; 
    yRET_TRACE(ID);
}

%%
