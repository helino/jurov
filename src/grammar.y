%{
    #include "stddef.h"
    #include "list.h"
    #include "ast/ast.h"
    #include "ast/mj_identifier.h"
    #include "ast/mj_unary_operation.h"
    #include "ast/mj_binary_operation.h"
    #include "ast/mj_integer.h"
    #include "ast/mj_boolean.h"
    #include "ast/mj_new_object.h"
    #include "ast/ast_list.h"
    #include "ast/mj_call.h"
    #include "ast/mj_this.h"
    #include "ast/mj_print.h"
    #include "ast/mj_main_class.h"
    #include "ast/mj_class.h"
    #include "ast/mj_type.h"
    #include "ast/mj_var_decl.h"
    #include "ast/mj_method_arg.h"
    #include "ast/mj_method_body.h"
    #include "ast/mj_method_decl.h"
    #include "ast/mj_if.h"
    #include "ast/mj_while.h"
    #include "ast/mj_assignment.h"
    #include "ast/mj_array_assignment.h"
    #include "utils.h"
    void yyerror(ast **result, char *s);
    int yylex(void);
    extern int yylineno;
    extern char *yytext;
%}

%parse-param {ast **result}

%union {
    char* id;
    int number;
    struct ast_ *tree;
}

%token MAIN PUBLIC CLASS
%token PRINT LENGTH
%token LCURLY RCURLY LPAREN RPAREN LSQUARE RSQUARE
%token IF ELSE WHILE RETURN
%token TRUE FALSE
%token THIS NEW
%token BOOLEAN INT STRING
%token AND LESS PLUS MINUS MUL BANG DOT COMMA SEMICOLON EQUALS
%token <id> ID
%token <number> NUMBER

%type <tree> program main_class main_method begin_class 
             function_body statements statement print_statement expression
             class_declarations class_declaration variable_declarations 
             variable_declaration method_declarations method_declaration
             arguments more_arguments argument type identifier 
             if_statement while_statement assign_statement method_body
             array_assignment_statement boolean number this relational_exp 
             additive_exp multiplicative_exp new_exp call_exp basic_exp
             unary_exp expressions more_expressions
             
%destructor { delete_ast($$); } program main_class main_method begin_class 
                                function_body statements statement 
                                print_statement expression class_declarations
                                class_declaration variable_declarations 
                                variable_declaration method_declarations 
                                method_declaration arguments more_arguments 
                                argument type identifier if_statement
                                while_statement assign_statement method_body
                                array_assignment_statement boolean number
                                this relational_exp additive_exp 
                                multiplicative_exp new_exp call_exp basic_exp
                                unary_exp expressions more_expressions
%destructor { jrv_free(&$$); } ID
%%
start: program { *result = $1; }

program: main_class class_declarations { mj_ast_list_prepend($2, $1); $$ = $2;}

main_class: begin_class main_method function_body RCURLY 
            { ast *mc; 
              new_mj_main_class($1, $2, $3, &mc);
              $$ = mc; }

main_method: MAIN LPAREN STRING LSQUARE RSQUARE ID RPAREN 
             { ast *a;
               new_mj_identifier($6, &a);
               $$ = a; }

class_declarations:  /* nothing, return an empty mj_ast_list */
                    { ast *node;
                      empty_mj_ast_list(&node);
                      $$ = node; }
                  | class_declaration class_declarations
                    { mj_ast_list_prepend($2, $1);
                      $$ = $2; }

class_declaration: begin_class variable_declarations method_declarations RCURLY
                   { ast *class;
                     new_mj_class($1, $2, $3, &class);
                     $$ = class; }

variable_declarations: /* nothing, return the empty list */
                       { ast *node;
                         empty_mj_ast_list(&node);
                         $$ = node; }
                     | variable_declaration variable_declarations
                       { mj_ast_list_prepend($2, $1);
                         $$ = $2; }

variable_declaration: type identifier SEMICOLON
                      { ast *var_decl;
                        new_mj_var_decl($1, $2, &var_decl);
                        $$ = var_decl; }

method_declarations: /* nothing, return the empty list */
                     { ast *list;
                       empty_mj_ast_list(&list);
                       $$ = list; }
                   | method_declaration method_declarations
                     { mj_ast_list_prepend($2, $1);
                       $$ = $2; }

method_declaration: PUBLIC type identifier LPAREN arguments RPAREN LCURLY 
                    method_body RETURN expression 
                    SEMICOLON RCURLY
                    { ast *method;
                      new_mj_method_decl($2, $3, $5, $8, $10, &method);
                      $$ = method; }

method_body: /* nothing */
            { ast *vars, *stmts, *b;
              empty_mj_ast_list(&vars);
              empty_mj_ast_list(&stmts);
              new_mj_method_body(vars, stmts, &b);
              $$ = b; }
           | variable_declaration method_body
             { mj_method_body_add_var_decl($1, $2); 
               $$ = $2; }
           | statement statements
             { ast *b, *vars;
               empty_mj_ast_list(&vars);
               new_mj_method_body(vars, $2, &b);
               mj_method_body_add_statement($1, b);
               $$ = b; }

arguments: /* nothing, return the empty list */
           { ast *node;
             empty_mj_ast_list(&node);
             $$ = node; }
         | argument more_arguments
           { mj_ast_list_prepend($2, $1);
             $$ = $2; }

more_arguments: /* nothing, return the empty list */
                { ast *node;
                  empty_mj_ast_list(&node);
                  $$ = node; }
              | COMMA argument more_arguments 
                { mj_ast_list_prepend($3, $2);
                  $$ = $3; }

argument: type identifier
          { ast *var_decl;
            new_mj_method_arg($1, $2, &var_decl);
            $$ = var_decl; }

type: BOOLEAN 
      { ast *type;
        new_mj_type(MJ_TYPE_BOOLEAN, NULL, &type);
        $$ = type; }
    | INT
      { ast *type;
        new_mj_type(MJ_TYPE_INTEGER, NULL, &type);
        $$ = type; }
    | INT LSQUARE RSQUARE
      { ast *type;
        new_mj_type(MJ_TYPE_INT_ARRAY, NULL, &type);
        $$ = type; }
    | identifier
      { ast *type;
        new_mj_type(MJ_TYPE_USER_DEFINED, $1, &type);
        $$ = type; }

identifier: ID
            { ast *id;
              new_mj_identifier($1, &id);
              $$ = id; }

begin_class: CLASS identifier LCURLY { $$ = $2; }

function_body: LCURLY statements RCURLY { $$ = $2; }

statements: /* nothing, return an empty mj_ast_list */ 
            { ast *node;
              empty_mj_ast_list(&node);
              $$ = node; }
          | statement statements { mj_ast_list_prepend($2, $1); $$ = $2; }

statement: LCURLY statements RCURLY { $$ = $2; }
         | if_statement { $$ = $1; }
         | print_statement { $$ = $1; }
         | while_statement { $$ = $1; }
         | assign_statement { $$ = $1; }
         | array_assignment_statement { $$ = $1; }

array_assignment_statement: identifier LSQUARE expression RSQUARE EQUALS 
                            expression SEMICOLON
                            { ast *aa;
                              new_mj_array_assignment($1, $3, $6, &aa);
                              $$ = aa; }

assign_statement: identifier EQUALS expression SEMICOLON
                  { ast *a;
                    new_mj_assignment($1, $3, &a);
                    $$ = a; }

while_statement: WHILE LPAREN expression RPAREN statement
                 { ast *w;
                   new_mj_while($3, $5, &w);
                   $$ = w; }

if_statement: IF LPAREN expression RPAREN statement ELSE statement
              { ast *i;
                new_mj_if($3, $5, $7, &i);
                $$ = i; }

print_statement: PRINT LPAREN expression RPAREN SEMICOLON 
                 { ast *node;
                   new_mj_print($3, &node);
                   $$ = node; }

expressions: /* nothing, return the empty list */
             { ast *node;
               empty_mj_ast_list(&node);
               $$ = node; }
           | expression more_expressions
             { mj_ast_list_prepend($2, $1);
               $$ = $2; }

more_expressions: /* nothing, return the empty list */
                  { ast *node;
                    empty_mj_ast_list(&node);
                    $$ = node; }
                | COMMA expression more_expressions
                  { mj_ast_list_prepend($3, $2);
                    $$ = $3; }

expression: expression AND relational_exp
            { ast *node;
              new_mj_binary_operation(MJ_AND, $1, $3, &node);
              $$ = node; }
          | relational_exp { $$ = $1; }

relational_exp: relational_exp LESS additive_exp
                { ast *node;
                  new_mj_binary_operation(MJ_LESS_THAN, $1, $3, &node);
                  $$ = node; }
              | additive_exp { $$ = $1; }

additive_exp: additive_exp PLUS multiplicative_exp
              { ast *node;
                new_mj_binary_operation(MJ_ADDITION, $1, $3, &node);
                $$ = node; }
            | additive_exp MINUS multiplicative_exp
              { ast *node;
                new_mj_binary_operation(MJ_SUBTRACTION, $1, $3, &node);
                $$ = node; }
            | multiplicative_exp { $$ = $1; }

multiplicative_exp: multiplicative_exp MUL unary_exp
                    { ast *node;
                      new_mj_binary_operation(MJ_MULTIPLICATION, $1, $3, &node);
                      $$ = node; }
                  | unary_exp { $$ = $1; }

unary_exp: BANG unary_exp
           { ast *node;
             new_mj_unary_operation(MJ_NOT, $2, &node);
             $$ = node; }
         | call_exp { $$ = $1; }

call_exp: call_exp DOT LENGTH
          { ast *node;
            new_mj_unary_operation(MJ_ARRAY_LENGTH, $1, &node);
            $$ = node; }
        | call_exp DOT identifier LPAREN expressions RPAREN
          { ast *node;
            new_mj_call($1, $3, $5, &node);
            $$ = node; }
        | call_exp LSQUARE new_exp RSQUARE
          { ast *node;
            new_mj_binary_operation(MJ_ARRAY_LOOKUP, $1, $3, &node);
            $$ = node; }
        | new_exp { $$ = $1; }

new_exp: NEW identifier LPAREN RPAREN
         { ast *node;
           new_mj_new_object($2, &node);
           $$ = node; }
       | NEW INT LSQUARE new_exp RSQUARE
         { ast *node;
           new_mj_unary_operation(MJ_NEW_ARRAY, $4, &node);
           $$ = node; }
       | basic_exp { $$ = $1; }

basic_exp: boolean { $$ = $1; }
         | number { $$ = $1; }
         | this { $$ = $1; }
         | identifier { $$ = $1; }
         | LPAREN expression RPAREN { $$ = $2; }

this: THIS
      { ast *node;
        new_mj_this(&node);
        $$ = node; }

boolean: TRUE 
         { ast *node; 
           new_mj_boolean(1, &node); 
           $$ = node; }
       | FALSE 
         { ast *node; 
           new_mj_boolean(0, &node); 
           $$ = node; }

number: NUMBER 
        { ast *node;
          new_mj_integer($1, &node);
          $$ = node; }

%%

void yyerror(ast **result, char *msg)
{
    fprintf(stderr, "%d: %s at '%s'\n", yylineno, msg, yytext);
}
