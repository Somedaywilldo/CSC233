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
    #define yRET_TRACE(x) {yTRACE(x); return x}

    int CheckInt(void);
    int yyline = 1;
    
    %}
%option noyywrap


WS  [ \t\n]+

LETTER [A-Za-z]

DIGIT [0-9]

ID {letter}({letter}|digit})*

NUMBER {digit}+(\.{digit}+)?(E[+-]?{digit}+)?


%%

"int"   {yRET_TRACE(INT)}
"ivec2" {yRET_TRACE(IVEC2)}
"ivec3" {yRET_TRACE(IVEC3)}
"ivec4" {yRET_TRACE(IVEC4)}

"float"  {yRET_TRACE(FLOAT)}
"vec2"   {yRET_TRACE(VEC2)}
"vec3"   {yRET_TRACE(VEC3)}
"vec4"   {yRET_TRACE(VEC4)}

"bool"     {yRET_TRACE(BOOL)}
"bvec2"    {yRET_TRACE(BVEC2)}
"bvec3"    {yRET_TRACE(BVEC3)}
"bvec4"    {yRET_TRACE(BVEC4)}

"dp3"       {yRET_TRACE(DP3)}
"lit"       {yRET_TRACE(LIT)}
"rsq"       {yRET_TRACE(RSQ)}

+           {yRET_TRACE(PLUS)}
-           {yRET_TRACE(MINUS)}
*           {yRET_TRACE(MULT)}
/           {yRET_TRACE(DIV)}
^           {yRET_TRACE(POW)}
=           {yRET_TRACE(ASSIGN)}

!           {yRET_TRACE(NOT)}
&&          {yRET_TRACE(AND}
||          {yRET_TRACE(OR)}

==          {yRET_TRACE(EQ}
!=          {yRET_TRACE(NEQ)}
<           {yRET_TRACE(LT)}
<=          {yRET_TRACE(LE)}
>           {yRET_TRACE(GT)}
>=          {yRET_TRACE(GE)}

(           {yRET_TRACE(LSB)}
)           {yRET_TRACE(RSB)}
[           {yRET_TRACE(LMB)}
]           {yRET_TRACE(RMB)}
{           {yRET_TRACE(LBB)}
}           {yRET_TRACE(RBB)}

"if"        {yRET_TRACE(IF)}
"else"      {yRET_TRACE(ELSE)}
"while"     {yRET_TRACE(WHILE)}

"const"     {yRET_TRACE(CONST)}
"void"      {yRET_TRACE(VOID)}

;           {yRET_TRACE(SEMI)}
,           {yRET_TRACE(COMA)}

/*
"gl_FragColor"           {yRET_TRACE(GL_FRAGCOLOR)}
"gl_FragDepth"           {yRET_TRACE(GL_FRAGDEPTH)}
"gl_FragCoord"           {yRET_TRACE(GL_FRAGCOORD)}
"gl_TexCoord"            {yRET_TRACE(GL_TEXCOORD)}
"gl_Color"               {yRET_TRACE(GL_COLOR)}
"gl_Secondary"           {yRET_TRACE(GL_SECONDARY)}
"gl_FogFragCoord"        {yRET_TRACE(GL_FOGFRAGCOORD)}
"gl_Light_Half"          {yRET_TRACE(GL_LIGHT_HALF)}
"gl_Light_Ambient"       {yRET_TRACE(GL_LIGHT_AMBIENT)}
"gl_Material_Shininess"  {yRET_TRACE(GL_MATERIAL_SHININESS)}
"env1"                   {yRET_TRACE(ENV1)}
"env2"                   {yRET_TRACE(ENV2)}
"env3"                   {yRET_TRACE(ENV3)}
*/





(true|false)/{WS}   {
    int a=0;
    if(strncmp(yytext,”true”)==0){
        a=1;
    }
    else{
        a=0;
    }
    yylval.boolValue=a;
    yRET_TRACE(BOOL_V);
}

[+-]?[0-9]+/{WS}    {
    yylval.intValue =atoi(yytext);
    yRET_TRACE(INT_V);
}

[+-]?(([0-9]+"."[0-9]*)|([0-9]*"."[0-9]+))/{WS}     {
    yylval.floatValue =atof(yytext);
    yRET_TRACE(FLOAT_V);
}

[A-Za-z]][A-za-z0-9]*/{WS}    {
    yylval.idName=(char *) malloc((yyleng+1)*sizeof(char));
    strncpy(yylval.idName,yytext,yyleng+1);
    yRET_TRACE(ID);
}



"/*"        { SKIP LINKES
}


{WS}

}

.           { yERROR("Unknown token"); }

%%





