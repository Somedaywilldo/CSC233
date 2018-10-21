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
	'else' statement 							{yTRACE("else_statement-> else statement");}					|
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





