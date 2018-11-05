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
      ast->type.type_token = BOOL;
      ast->type.vec_size = 1;
      ast->bool_val = va_arg(args, int);
	    break;

    case INT_NODE:
      ast->type.is_const = 1;
      ast->type.type_token = INT;
      ast->type.vec_size = 1;
      ast->int_val = va_arg(args, int);
      break;

    case FLOAT_NODE:
      ast->type.is_const = 1;
      ast->type.type_token = FLOAT;
      ast->type.vec_size = 1;
      ast->float_val = (float) va_arg(args, double);
      break;
    
    case TYPE_NODE:{
      ast->type.type_token = va_arg(args, int);
	    int vec_index = va_arg(args, int);
	    if(ast->type.type_token == FLOAT || ast->type.type_token == BOOL|| ast->type.type_token == INT)
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
      // can add to parser.y
      // enum {
      //   DP3 = 0, 
      //   LIT = 1, 
      //   RSQ = 2
      // };
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

void ast_free(node *ast)
{
	
}

void ast_print(node *ast)
{
	// ast_traversal(ast, print_node_pre, print_node_post);
    printf("THIS IS HARD!\n");
}
