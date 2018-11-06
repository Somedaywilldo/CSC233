/***********************************************************************
 * Yihang Yin 1005644144 yinyiha2 yihangmichael.yin@mail.utoronto.ca
 * Mingdong Li 1000529617 limingdo mingdong.li@mail.utoronto.ca
 **********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>

#include "ast.h"
#include "common.h"
#include "parser.tab.h"

#define DEBUG_PRINT_TREE 0
#define CASE_FPRINT(x,y) {case x: print_tab(depth,1);fprintf(dumpFile, ""#y"\n");break;}
//#define CASE_FPRINT(x,y) {case x: fprintf(dumpFile, #y);break;}

#define CASE_TOKEN_TO_STR(x) {case x: return #x;}
#define CASE_VEC_TOKEN_TO_STR(x) {case x: char str[6]; sprintf(str, ""#x"%d",type->vec_size); return str; }


node *ast = NULL;

node *ast_allocate(node_kind kind, ...)
{
	va_list args;

	// make the node
	node *ast = (node *)malloc(sizeof(node));
	memset(ast, 0, sizeof *ast);
	ast->kind = kind;

	va_start(args, kind);

	switch (kind)
	{
    case SCOPE_NODE:
      ast->scope.declarations = va_arg(args, node *); 
      ast->scope.stmts = va_arg(args, node *);        
      break;

    case DECLARATIONS_NODE:
      ast->declarations.declarations = va_arg(args, node *); 
      ast->declarations.declaration = va_arg(args, node *);        
      break;

    case STATEMENTS_NODE:
      ast->stmts.stmts = va_arg(args, node *); 
      ast->stmts.stmt = va_arg(args, node *);        
      break;

    case DECLARATION_NODE:
      ast->declaration.is_const = va_arg(args, int); 
      ast->declaration.id = va_arg(args, char *);  
      ast->declaration.type_node = va_arg(args, node *);        
      ast->declaration.expr = va_arg(args, node *);        
      break;

    case UNARY_EXPRESSION_NODE:
			ast->unary_expr.op = va_arg(args, int);
			ast->unary_expr.right = va_arg(args, node *);
			break;
		
		case BINARY_EXPRESSION_NODE:
			ast->binary_expr.op = va_arg(args, int);
			ast->binary_expr.left = va_arg(args, node *);
			ast->binary_expr.right = va_arg(args, node *);
			break;

    case VARIABLE_NODE:
			ast->variable.id = va_arg(args, char *);
			ast->variable.is_array = va_arg(args, int);
			ast->variable.index = va_arg(args, int);
			break;
    
    case NESTED_SCOPE_NODE:
      ast->nested_scope.scope = va_arg(args, node *);
			break;

    case NESTED_EXPRESSION_NODE:
      ast->nested_expr.expr = va_arg(args, node *);
			break;
    
    case BOOL_NODE:
      ast->type.is_const = 1;
      ast->type.type_token = BOOL_T;
      ast->type.vec_size = 1;
      ast->bool_val = va_arg(args, int);
	    break;

    case INT_NODE:
      ast->type.is_const = 1;
      ast->type.type_token = INT_T;
      ast->type.vec_size = 1;
      ast->int_val = va_arg(args, int);
      break;

    case FLOAT_NODE:
      ast->type.is_const = 1;
      ast->type.type_token = FLOAT_T;
      ast->type.vec_size = 1;
      ast->float_val = (float) va_arg(args, double);
      break;
    
    case TYPE_NODE:{
      ast->type.type_token = va_arg(args, int);
	    int vec_index = va_arg(args, int);
	    if(ast->type.type_token == FLOAT_T || ast->type.type_token == BOOL_T|| ast->type.type_token == INT_T)
		    ast->type.vec_size = 1;
	    else
		    ast->type.vec_size = vec_index + 1;
	    break;
    }
    
    case ASSIGNMENT_NODE:
      ast->assignment.variable = va_arg(args, node *);
      ast->assignment.expr = va_arg(args, node *);
      break;

    case CONSTRUCTOR_NODE:
      ast->constructor.type_node = va_arg(args, node *);
      ast->constructor.args = va_arg(args, node *);
      break;
  
    case ARGUMENTS_NODE:
      ast->args.args = va_arg(args, node *);
      ast->args.expr = va_arg(args, node *);
      break;
    
    case FUNCTION_NODE:
      ast->func.name = va_arg(args, int); 
      ast->func.args = va_arg(args, node *);
      break;

    case IF_STATEMENT_NODE:
      ast->if_stmt.cond_expr = va_arg(args, node *);
      ast->if_stmt.then_stmt = va_arg(args, node *);
      ast->if_stmt.else_stmt = va_arg(args, node *);
      break;

		default:
		  break;
	}

	va_end(args);

	return ast;
}


void print_tab(int x, int is_open){
  int i;
  fprintf(dumpFile, "\n");
  for(i=0;i<x;i++)
    fprintf(dumpFile, "\t");
  fprintf(dumpFile, is_open ? "(" : ")");
}


// const char* type_to_str(struct type_attribute *type){
//   switch(type->type_token) {
//     CASE_TOKEN_TO_STR(BOOL_T)
//     CASE_TOKEN_TO_STR(INT_T)
//     CASE_TOKEN_TO_STR(FLOAT_T)
//     CASE_VEC_TOKEN_TO_STR(BVEC_T)
//     CASE_VEC_TOKEN_TO_STR(IVEC_T)
//     CASE_VEC_TOKEN_TO_STR(VEC_T)
//     default:
//       return "ANY";
//   }
// }

const char *type_to_str(struct type_attribute *type) {
  switch(type->type_token) {
    case FLOAT_T:
      return "FLOAT";
    case INT_T:
      return "INT";
    case BOOL_T:
      return "BOOL";
    case BVEC_T:
      switch(type->vec_size){
        case 2:
          return "BVEC2";
        case 3:
          return "BVEC3";
        case 4:
          return "BVEC4";
      }
    case IVEC_T:
      switch(type->vec_size){
        case 2:
          return "IVEC2";
        case 3:
          return "IVEC3";
        case 4:
          return "IVEC4";
      }
    case VEC_T:
      switch(type->vec_size){
        case 2:
          return "VEC2";
        case 3:
          return "VEC3";
        case 4:
          return "VEC4";
      }
    default:
      return "ANY";
  }
}

const char *op_to_str(int op) {
  switch(op) {
    case '-':
      return "-";
    case '!':
      return "!";
    case AND:
      return "&&";
    case OR:
      return "||";
    case EQ:
      return "==";
    case NEQ:
      return "!=";
    case '<':
      return "<";
    case LEQ:
      return "<=";
    case '>':
      return ">";
    case GEQ:
      return ">=";
    case '+':
      return "+";
    case '*':
      return "*";
    case '/':
      return "/";
    case '^':
      return "^";
    default:
      return "";
  }
}

const char* func_to_str(int name){
  switch(name) {
    case 0:
      return "DP3";
    case 1:
      return "RSQ";
    case 2:
      return "LIT";
    default:
      return "";
  }
}

void ast_print_node(node *ast, int depth){
  switch(ast->kind){
    CASE_FPRINT(SCOPE_NODE, SCOPE)
    CASE_FPRINT(DECLARATIONS_NODE, DECLARATIONS)
    CASE_FPRINT(STATEMENTS_NODE, STATEMENTS)

    //type and expr is another two node
    case DECLARATION_NODE:
      print_tab(depth, 1);
      fprintf(dumpFile, "DECLARATION %s", ast->declaration.id); 
      break;

    case UNARY_EXPRESSION_NODE:
      print_tab(depth, 1);
      fprintf(dumpFile, "UNARY %s %s", type_to_str(&ast->type), op_to_str(ast->unary_expr.op));
      break;

    case BINARY_EXPRESSION_NODE:
      print_tab(depth, 1);
      fprintf(dumpFile, "BINARY %s %s", type_to_str(&ast->type), op_to_str(ast->binary_expr.op));
      break;

    case VARIABLE_NODE:
      fprintf(dumpFile, " ");
      if (ast->variable.is_array) {
        fprintf(dumpFile, "INDEX %s %s %d", type_to_str(&ast->type), ast->variable.id, ast->variable.index);
      } 
      else {
        fprintf(dumpFile, "%s", ast->variable.id);
      }
      break;

    case NESTED_SCOPE_NODE:
      break;
    
    case NESTED_EXPRESSION_NODE:
      break;

    case BOOL_NODE:
      fprintf(dumpFile, " %s", (ast->bool_val == 1) ? "true" : "false");
      break;

    case INT_NODE:
      fprintf(dumpFile, " %d", ast->int_val);
      break;

    case FLOAT_NODE:
      fprintf(dumpFile, " %f", ast->float_val);
      break;

    case TYPE_NODE:
      fprintf(dumpFile, " %s", type_to_str(&ast->type));
      break;
    
    case ASSIGNMENT_NODE:
      // print_tab(depth);
      fprintf(dumpFile, "ASSIGNMENT %s", type_to_str(&ast->assignment.type));
      break;
    
    CASE_FPRINT(CONSTRUCTOR_NODE, CALL)

    case ARGUMENTS_NODE:
      break;
    
    case FUNCTION_NODE:
      print_tab(depth, 1);
      fprintf(dumpFile, "CALL %s", func_to_str(ast->func.name));
      break;

    CASE_FPRINT(IF_STATEMENT_NODE, IF)

    default:
      break;
  }
}

void ast_free_node(node *ast) {
	if(ast->kind == DECLARATION_NODE)
		free(ast->declaration.id);
	else if(ast->kind == VARIABLE_NODE)
		free(ast->variable.id);
	free(ast);
}

void print_after_dfs(node *ast, int depth)
{
  if(ast==NULL)
    return;
  switch (ast->kind)
  {
    case SCOPE_NODE:
      print_tab(depth, 0);
      break;

    case DECLARATIONS_NODE:
      print_tab(depth, 0);
      break;

    case STATEMENTS_NODE:
      print_tab(depth, 0);
      break;

    case DECLARATION_NODE:
      print_tab(depth, 0);
      break;

    case UNARY_EXPRESSION_NODE:
      print_tab(depth, 0);
      break;
    
    case BINARY_EXPRESSION_NODE:
      print_tab(depth, 0);
      break;

    case VARIABLE_NODE:
      break;
    
    case NESTED_SCOPE_NODE:
      break;

    case NESTED_EXPRESSION_NODE:
      break;
    
    case BOOL_NODE:
      break;

    case INT_NODE:
      break;

    case FLOAT_NODE:
      break;
    
    case TYPE_NODE:
      break;
    
    case ASSIGNMENT_NODE:
      print_tab(depth, 0);
      break;

    case CONSTRUCTOR_NODE:
      print_tab(depth, 0);
      break;
  
    case ARGUMENTS_NODE:
      print_tab(depth, 0);
      break;
    
    case FUNCTION_NODE:
      print_tab(depth, 0);
      break;

    case IF_STATEMENT_NODE:
      print_tab(depth, 0);
      break;

    default:
      break;
  }
}


void ast_dfs(node *ast, int depth, int is_print)
{
  if(ast==NULL)
    return;
  if(is_print){
    ast_print_node(ast, depth);
  }
  switch (ast->kind)
  {
    case SCOPE_NODE:
      ast_dfs(ast->scope.declarations, depth+1, is_print);
      ast_dfs(ast->scope.stmts, depth+1, is_print);
      break;

    case DECLARATIONS_NODE:
      ast_dfs(ast->declarations.declarations, depth+1, is_print);
      ast_dfs(ast->declarations.declaration, depth+1, is_print);
      break;

    case STATEMENTS_NODE:
      ast_dfs(ast->stmts.stmts, depth+1, is_print);
      ast_dfs(ast->stmts.stmt, depth+1, is_print);
      break;

    case DECLARATION_NODE:
      ast_dfs(ast->declaration.type_node, depth+1, is_print);
      if(ast->declaration.expr){
        ast_dfs(ast->declaration.expr, depth+1, is_print);
      }
      break;

    case UNARY_EXPRESSION_NODE:
      ast_dfs(ast->unary_expr.right, depth+1, is_print);
      break;
    
    case BINARY_EXPRESSION_NODE:
      ast_dfs(ast->binary_expr.left, depth+1, is_print);
      ast_dfs(ast->binary_expr.right, depth+1, is_print);
      break;

    case VARIABLE_NODE:
      break;
    
    case NESTED_SCOPE_NODE:
      ast_dfs(ast->nested_scope.scope, depth+1, is_print);
      break;

    case NESTED_EXPRESSION_NODE:
      ast_dfs(ast->nested_expr.expr, depth+1, is_print);
      break;
    
    case BOOL_NODE:
      break;

    case INT_NODE:
      break;

    case FLOAT_NODE:
      break;
    
    case TYPE_NODE:
      break;
    
    case ASSIGNMENT_NODE:
      ast_dfs(ast->assignment.variable, depth+1, is_print);
      ast_dfs(ast->assignment.expr, depth+1, is_print);
      break;

    case CONSTRUCTOR_NODE:
      ast_dfs(ast->constructor.type_node, depth+1, is_print);
      ast_dfs(ast->constructor.args, depth+1, is_print);
      break;
  
    case ARGUMENTS_NODE:
      ast_dfs(ast->args.args, depth+1, is_print);
      ast_dfs(ast->args.expr, depth+1, is_print);
      break;
    
    case FUNCTION_NODE:
      ast_dfs(ast->func.args, depth+1, is_print);
      break;

    case IF_STATEMENT_NODE:
      ast_dfs(ast->if_stmt.cond_expr, depth+1, is_print);
      ast_dfs(ast->if_stmt.then_stmt, depth+1, is_print);
      if(ast->if_stmt.else_stmt){
        ast_dfs(ast->if_stmt.else_stmt, depth+1, is_print);
      }
      break;

    default:
      break;
  }
  if(is_print){
    print_after_dfs(ast, depth);
  }
  if(!is_print){
    ast_free_node(ast);
  }
}


void ast_free(node *ast)
{
  ast_dfs(ast, 0, 0);
}


void ast_print(node *ast)
{
  ast_dfs(ast, 0, 1);
}
