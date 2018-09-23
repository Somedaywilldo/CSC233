%{
    /**********************************************************************
     *  Interface to the scanner module for CSC467 course project
     **********************************************************************/
    
    
    #include "common.h"
    #include "parser.tab.h"
    #include "string.h"
    
    
    #define YY_USER_INIT { yyin = inputFile; }
    #define    yyinput      input
    #define yTRACE(x)    { if (traceScanner) fprintf(traceFile, "TOKEN %3d : %s\n", x, yytext); }
    #define yERROR(x)    { fprintf(errorFile, "\nLEXICAL ERROR, LINE %d: %s\n", yyline, x); errorOccurred = TRUE; yyterminate(); }
    
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

"const"    {yTRACE(CONST); return CONST;}

"void"  {yTRACE(VOID); return VOID;}

"int"  {yTRACE(INT); return INT;}
"ivec2" {yTRACE(IVEC2); return IVEC2;}
"ivec3" {yTRACE(IVEC3); return IVEC3;}
"ivec4"  {yTRACE(IVEC4); return IVEC4;}

"float"   {yTRACE(FLOAT); return FLOAT;}
"vec2"   {yTRACE(VEC2); return VEC2;}
"vec3"   {yTRACE(VEC3); return VEC3;}
"vec4"   {yTRACE(VEC4); return VEC4;}

"bool"   {yTRACE(BOOL); return BOOL;}
"bvec2"    {yTRACE(BVEC2); return BVEC2;}
"bvec3"    {yTRACE(BVEC3); return BVEC3;}
"bvec4"    {yTRACE(BVEC4); return BVEC4;}


"if"    {yTRACE(IF); return IF;}
"else"    {yTRACE(ELSE); return ELSE;}
"while"    {yTRACE(WHILE); return WHILE;}


"gl_FragColor"           {yTRACE(GL_FRAGCOLOR); return GL_FRAGCOLOR;}
"gl_FragDepth"           {yTRACE(GL_FRAGDEPTH); return GL_FRAGDEPTH;}
"gl_FragCoord"           {yTRACE(GL_FRAGCOORD); return GL_FRAGCOORD;}
"gl_TexCoord"            {yTRACE(GL_TEXCOORD); return GL_TEXCOORD;}
"gl_Color"                  {yTRACE(GL_COLOR); return GL_COLOR;}
"gl_Secondary"           {yTRACE(GL_SECONDARY); return GL_SECONDARY;}
"gl_FogFragCoord"        {yTRACE(GL_FOGFRAGCOORD); return gl_FOGFRAGCOORD;}
"gl_Light_Half"          {yTRACE(GL_LIGHT_HALF); return GL_LIGHT_HALF;}
"gl_Light_Ambient"       {yTRACE(GL_LIGHT_AMBIENT); return GL_LIGHT_AMBIENT;}
"gl_Material_Shininess"  {yTRACE(GL_MATERIAL_SHININESS); return GL_MATERIAL_SHININESS;}
"env1"                   {yTRACE(ENV1); return ENV1;}
"env2"                   {yTRACE(ENV2); return ENV2;}
"env3"                   {yTRACE(ENV3); return ENV3;}

=                 {yTRACE(EQ); return EQ;}
==            {yTRACE(COMPARE);return COMPARE;}
!             {yTRACE(NOT); return NOT;}
!=                                 {yTRACE(NOTEQ); return NOTEQ;}
<                               {yTRACE(LT); return LT;}
<=                               {yTRACE(LE); return LE;}
>                               {yTRACE(GT); return GT;}
>=                              {yTRACE(GE); return GE;}

&&                              {yTRACE(AND);return AND;}
| |                             {yTRACE(OR); return OR;}


+                               {yTRACE(PLUS); return PLUS;}
-                               {yTRACE(MINUS); return MINUS;}
*                               {yTRACE(TIMES); return TIMES;}
/                               {yTRACE(DIVIDE); return DIVIDE;}
^                               {yTRACE(POWER); return POWER;}
%                               {yTRACE(MOD); return MOD;}
,                               {yTRACE(COMA); return COMA;}
;                               {yTRACE(SEMICO); return SEMICO;}

(                               {yTRACE(LSB); return LSB;}

)                               {yTRACE(RSB); return RSB;}

[                               {yTRACE(LMB); return LMB;}

]                               {yTRACE(RMB); return RMB;}

{                               {yTRACE(LBB); return LBB;}
    
}                               {yTRACE(RBB); return RBB;}

[A-Za-z]][A-za-z0-9]*/{WS}      {
    yylval.idName=(char *) malloc((yyleng+1)*sizeof(char));
    strncpy(yylval.idName,yytext,yyleng+1);
    {yTRACE(IDENTIFIER); return IDENTIFIER;}
}


[+-]?[0-9]+/{WS}                     {
    yylval.intValue =atoi(yytext);
    yTRACE(INT_VALUE); return INT_VALUE;
}

[+-]?(([0-9]+"."[0-9]*)|([0-9]*"."[0-9]+))/{WS}{
    yylval.floatValue =atof(yytext);
    yTRACE(FLOAT_VALUE); return FLOAT_VALUE;
}

(true|false)/{WS}   {
    int a=0;
    if(strncmp(yytext,”true”)==0){
        a=1;
    }
    else{
        a=0;
    }
    yylval.boolValue=a;
    
    {yTRACE(BOOL_VALUE); return BOOL_VALUE;}
}




"/*"        { SKIP LINKES
}


{WS}

}

.           { yERROR("Unknown token"); }

%%





