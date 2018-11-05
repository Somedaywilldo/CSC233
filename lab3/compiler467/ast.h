#ifndef AST_H_
#define AST_H_ 1

#include <stdarg.h>

/***********************************************************************
 * Yihang Yin 1005644144 yinyiha2 yihangmichael.yin@mail.utoronto.ca
 * Mingdong Li 1000529617 limingdo mingdong.li@mail.utoronto.ca
 **********************************************************************/


// Dummy node just so everything compiles, create your own node/nodes
//
// The code provided below is an example ONLY. You can use/modify it,
// but do not assume that it is correct or complete.
//
// There are many ways of making AST nodes. The approach below is an example
// of a descriminated union.
//

// Forward declarations
struct node_;
typedef struct node_ node;
extern node *ast;

typedef enum {
  UNKNOWN               = 0,

  SCOPE_NODE            = (1 << 0),
  
  EXPRESSION_NODE       = (1 << 2),
  UNARY_EXPRESSION_NODE = (1 << 2) | (1 << 3),
  BINARY_EXPRESSION_NODE= (1 << 2) | (1 << 4),

  BOOL_NODE             = (1 << 3) | (1 << 4), //added
  INT_NODE              = (1 << 2) | (1 << 5), 
  FLOAT_NODE            = (1 << 2) | (1 << 6),
  TYPE_NODE             = (1 << 3) | (1 << 6), //added

  IDENT_NODE            = (1 << 2) | (1 << 7),
  VARIABLE_NODE              = (1 << 2) | (1 << 8),
  FUNCTION_NODE         = (1 << 2) | (1 << 9),
  ARGUMENTS_NODE        = (1 << 3) | (1 << 9), //added

  CONSTRUCTOR_NODE      = (1 << 2) | (1 << 10),

  STATEMENT_NODE        = (1 << 1),
  OPTIONAL_STATEMENT_NODE=(1 << 2) | (1 << 12), //added
  STATEMENTS_NODE       = (1 << 1) | (1 << 12), //added

  IF_STATEMENT_NODE     = (1 << 1) | (1 << 11),
  // WHILE_STATEMENT_NODE  = (1 << 1) | (1 << 12),
  ASSIGNMENT_NODE       = (1 << 1) | (1 << 13),
  NESTED_SCOPE_NODE     = (1 << 1) | (1 << 14),
  NESTED_EXPRESSION_NODE= (1 << 2) | (1 << 14), //added

  DECLARATION_NODE      = (1 << 15),
  DECLARATIONS_NODE     = (1 << 1) | (1 << 15)  //added
} node_kind;


struct node_ {

  // an example of tagging each node with a type
  node_kind kind;

  union {
    struct {
      node *declarations;
      node *stmts;
    } scope;

    struct{
      node *declarations;
      node *declaration;
    } declarations;
    
    struct{
      node *stmts;
      node *stmt;
    } stmts;

    struct{
      int is_const;
      char *id;
      node *type;
      node *expr;
    } declaration;

    struct {
      int op;
      node *right;
    } unary_expr;

    struct {
      int op;
      node *left;
      node *right;
    } binary_expr;

    struct {
      char* id;
      int is_array;
      int index;
    } variable;

    // Don't know if necessary
    struct{
       node *scope;
    } nested_scope;
    // Don't know if necessary
    struct{
       node *expr;
    } nested_expr;

    int bool_val;
    int int_val;
    float float_val;

    struct {
      int type_attribute;
      int vec_size;
      int is_const; 
    } type;

    struct {
      node *type; // XX
      node *variable;
      node *expr;
    } assignment;

    // TODO: add more type of node
    struct{
      node *type;
      node *args;
    } constructor;

    struct {
      node *args;
      node *expr;
    } args;

    struct {
      int name;
      node *args;
    } func;

    struct{
      node *cond_expr;
      node *then_stmt;
      node *else_stmt; //optional
    } if_stmt;

  };
};

node *ast_allocate(node_kind type, ...);
void ast_free(node *ast);
void ast_print(node * ast);
int semantic_check(node * ast);

#endif /* AST_H_ */
