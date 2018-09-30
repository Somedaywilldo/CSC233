%{
    /**********************************************************************
     *  Yihang Yin 1005644144 yinyiha2 yihangmichael.yin@mail.utoronto.ca
     *  Mingdong Li 1000529617 limingdo mingdong.li@mail.utoronto.ca
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

    int CheckInt(void);
    int yyline = 1;
    
%}

%option noyywrap


WS      [ \t]+

LETTER  [A-Za-z]
DIGIT   [0-9]
NUMBER  {digit}+(\.{digit}+)?(E[+-]?{digit}+)?

/*RegEx for identifiers, start with _ or A or a, max length to 512*/
ID_reg 	      [A-Za-z_][A-Za-z0-9_]{1,512}
# 整数、实数和ID的最大长度没有限制，尽量不要使用+或者*这样的正则。
INT_V_reg     -?[1-9]\d{1,10}
FLOAT_V_reg   -?[0-9]{0,38}\.?[0-9]{1,38}


%%

{WS} {}

# \n是否应该算作是white space？，我认为不能算，否则可能没法给出错误行号。
"\n" {yyline++;}

int     {yRET_TRACE(INT)}
ivec2   {yRET_TRACE(IVEC2)}
ivec3   {yRET_TRACE(IVEC3)}
ivec4   {yRET_TRACE(IVEC4)}

float   {yRET_TRACE(FLOAT)}
vec2    {yRET_TRACE(VEC2)}
vec3    {yRET_TRACE(VEC3)}
vec4    {yRET_TRACE(VEC4)}

bool    {yRET_TRACE(BOOL)}
bvec2   {yRET_TRACE(BVEC2)}
bvec3   {yRET_TRACE(BVEC3)}
bvec4   {yRET_TRACE(BVEC4)}

dp3     {yRET_TRACE(DP3)}
lit     {yRET_TRACE(LIT)}
rsq     {yRET_TRACE(RSQ)}

"+"     {yRET_TRACE(PLUS)}
"-"     {yRET_TRACE(MINUS)}
"*"     {yRET_TRACE(MULT)}
"/"     {yRET_TRACE(DIV)}
"^"     {yRET_TRACE(POW)}
"="     {yRET_TRACE(ASSIGN)}

"!"     {yRET_TRACE(NOT)}
"&&"    {yRET_TRACE(AND)}
"||"    {yRET_TRACE(OR)}

"=="    {yRET_TRACE(EQ)}
"!="    {yRET_TRACE(NEQ)}
"<"     {yRET_TRACE(LT)}
"<="    {yRET_TRACE(LE)}
">"     {yRET_TRACE(GT)}
">="    {yRET_TRACE(GE)}

"("     {yRET_TRACE(LSB)}
")"     {yRET_TRACE(RSB)}
"["     {yRET_TRACE(LMB)}
"]"     {yRET_TRACE(RMB)}
"{"     {yRET_TRACE(LBB)}
"}"     {yRET_TRACE(RBB)}

if      {yRET_TRACE(IF)}
else    {yRET_TRACE(ELSE)}
while   {yRET_TRACE(WHILE)}

const   {yRET_TRACE(CONST)}

";"     {yRET_TRACE(SEMI)}
","     {yRET_TRACE(COMMA)}

true    {yRET_TRACE(TRUE_V)} /*TRUE VALUE*/
false   {yRET_TRACE(FALSE_V)}


# 联合变量的意义还需要明确一下
# 整数和float的范围需要确定一下，应该有报错

{INT_V_reg} {
    yylval.ival = atoi(yytext);
    yRET_TRACE(INT_V);
}

{FLOAT_V_reg} {
    yylval.fval = atof(yytext);
    yRET_TRACE(FLOAT_V);
}

{ID_reg} {
    if (strlen(yytext) > MAX_ID) /*有待考证*/
        yERROR("ERROR: Identifier exceeds maximum_length");
    yylval.sval = yytext; 
    yRET_TRACE(ID);
}

/*Deal with the comments*/

"/*" {
    char last_char = '\0';
    char now_char = yyinput();
    bool comment_matched = false;
    int now_line = yyline;
    while(now_char != EOF){
        if(now_char == '\n')
            yyline++;
        if(last_char == '*' && now_char == '/'){
            comment_matched = true;
            break;
        }
        last_char = now_char;
        now_char = yyinput();
    }
    if(!comment_matched){
        yERROR("Unmatched comment");
    }
}

/*If a string didn't match any of the rules above are not matched, */
.       {yERROR("Unknown token"); }


%%
