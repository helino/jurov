#ifndef INCLUDE_jrv_ast_h__
#define INCLUDE_jrv_ast_h__
#include "list.h"

/**
 * Represents all different kinds of nodes that can exists in the AST
 */
typedef enum {
    /** An identifier struct */
    MJ_IDENTIFIER,
    /** Addition, a binary_operation struct */
    MJ_ADDITION,
    /** Subtraction, a binary_operation struct */
    MJ_SUBTRACTION,
    /** Division, a binary_operation struct */
    MJ_DIVISION,
    /** Multiplication, a binary_operation struct */
    MJ_MULTIPLICATION,
    /** Less than, a binary_operation struct */
    MJ_LESS_THAN,
    /** Array lookup, a binary_operation struct */
    MJ_ARRAY_LOOKUP,
    /** Array length, an unary_operation struct */
    MJ_ARRAY_LENGTH,
    /** Logical not, an unary_operation struct */
    MJ_NOT,
    /** New array, an unary_operation struct */
    MJ_NEW_ARRAY,
    /** An integer struct */
    MJ_INTEGER,
    /** A boolean struct */
    MJ_BOOLEAN,
    /** A new_object struct */
    MJ_NEW_OBJECT,
    /** Represents the this type */
    MJ_THIS,
    /** Represents an ast_list struct */
    MJ_AST_LIST,
    /** Represents a call struct */
    MJ_CALL,
    /** Represensts a print struct */
    MJ_PRINT,
    /** Represents a main_class struct */
    MJ_MAIN_CLASS
} nodetype;

/**
 * Represents an abstract syntax tree (AST). 
 */
typedef struct ast_ {
    /**  The type of the node */
    nodetype type; 
} ast;

/**
 * Represents an identifier node in the AST.
 */
typedef struct {
    /** The type of the node (nodetype.IDENTIFIER) */
    nodetype type;
    /** The name of the identifier */
    char *name;
} mj_identifier;

/**
 * Creates a new identifier with the given name.
 *
 * @param[in] name The name of the identifier
 * @param[out] node The addres of the pointer that will point at the result 
 *                  of the function
 * @return An integer describing the result of the function
 */
int new_mj_identifier(char *name, ast **node);

/**
 * Represents a binary operation (such as +,-,*,< etc.) node in the AST
 */
typedef struct {
    /** The type of the node */
    nodetype type;
    /** The left operand to the operation */
    ast *left_operand;
    /** The right operand to the operation */
    ast *right_operand;

} mj_binary_operation;

/**
 * Creates a new binary operation with the given type and 
 * operands.
 *
 * @param[in] type The type of the operation
 * @param[in] left_operand The left operand of the expression
 * @param[in] right_operand The right operand of the expression
 * @param[out] node The addres of the pointer that will point at the result 
 *                  of the function
 * @return An integer describing the result of the function
 */
int new_mj_binary_operation(nodetype type, ast* left_operand, 
                            ast* right_operand, ast **node);

/**
 * Represents an unary operation (such as .length, new, not) node in the AST
 */
typedef struct {
    /** The type of the node */
    nodetype type;
    /** The argument to the operation */
    ast *operand;
} mj_unary_operation;

/**
 * Creates a new unary operation with the given type and 
 * operand.
 *
 * @param[in] type The type of the operation
 * @param[in] operand The operand of the expression
 * @param[out] node The addres of the pointer that will point at the result 
 *                  of the function
 * @return An integer describing the result of the function
 */
int new_mj_unary_operation(nodetype type, ast* operand, ast **node);

/**
 * Represents an integer node in the AST
 */
typedef struct {
    /** the type of the integer (nodetype.INTEGER) */
    nodetype type;
    /** the value of the integer */
    int value;
} mj_integer;

/**
 * Creates a new integer with the given value.
 *
 * @param[in] value The value of the integer
 * @param[out] node The addres of the pointer that will point at the result 
 *                  of the function
 * @return An integer describing the result of the function
 */
int new_mj_integer(int value, ast **node);

/**
 * Represents a boolean in the AST
 */
typedef struct {
    /** The type of the node (nodetype.BOOL) */
    nodetype type;
    /** The value of the boolean */
    int value;
} mj_boolean;

/**
 * Creates a new boolean with the given value.
 *
 * @param[in] value The value of the boolean expression
 * @param[out] node The addres of the pointer that will point at the result 
 *                  of the function
 * @return An integer describing the result of the function
 */
int new_mj_boolean(int value, ast **node);
 
/**
 * Represents a new object operation in the AST
 */
typedef struct {
    /** The type of the node (nodetype.NEW_OBJECT) */
    nodetype type;

    /** The id of the class of the object */
    mj_identifier *class_id;
} mj_new_object;

/**
 * Creates a new new_object with the given id.
 *
 * @param[in] id The identifier of the class of the object
 * @param[out] node The addres of the pointer that will point at the result 
 *                  of the function
 * @return An integer describing the result of the function
 */
int new_mj_new_object(ast *class_id, ast **node);

/**
 * This struct represents a list of ast elements
 */
typedef struct {
    /** The type of the node, this will be nodetype.AST_LIST */
    nodetype type;

    /** The actual list of ast nodes */
    list* list;
} mj_ast_list;

/**
 * Creates a new ast list with the given list.
 *
 * @param[in] list The list of of AST nodes
 * @param[out] node The addres of the pointer that will point at the result 
 *                  of the function
 * @return An integer describing the result of the function
 */
int new_mj_ast_list(list* list, ast **node);

/**
 * Creates an empty ast list and assigns it to node
 *
 * @param[out] The address of the pointer that will point to the empty list
 * @return An integer describing the result
 */
int empty_mj_ast_list(ast **node);

/**
 * Prepends an AST node to a ast_list
 *
 * @param[in] list The list of AST nodes
 * @param[in] node The AST node to prepend
 * @return An integer describing the result of the function
 */
int mj_ast_list_prepend(ast *list, ast *node);

/**
 * Represents a method call in the AST
 */
typedef struct {
    /** The type of the node, this will be nodetype.CALL */
    nodetype type;
    
    /* The expression that evaluates to the object to call the method on */
    ast* object;

    /* The id of the method to invoke */
    mj_identifier *method;

    /* The parameters to the method */
    mj_ast_list *parameters;
} mj_call;

/**
 * Creates a new call node for the AST with the given parameters.
 *
 * @param[in] object The object to call the method on
 * @param[in] method_id The id of the method to call
 * @param[in] parameters The parameters for the method call
 * @param[out] node The addres of the pointer that will point at the result 
 *                  of the function
 * @return An integer describing the result of the function
 */
int new_mj_call(ast *object, ast *method, mj_ast_list *parameters, ast **node);

/**
 * Creates a new ast struct with type nodetype.THIS
 *
 * @param[out] node The addres of the pointer that will point at the result 
 *                  of the function
 * @return An integer describing the result of the function
 */
int new_mj_this(ast **node);

/**
 * This struct represents a print statement
 */
typedef struct {
    /** The type of the node (nodetype.PRINT) */
    nodetype type;

    /** The expression that will evaluate to the print argument */
    ast *expression;
} mj_print;

/**
 * Creates a new print node with the given expression.
 *
 * @param[in] expression The expression which result will be printed
 * @param[out] node The addres of the pointer that will point at the result 
 *                  of the function
 * @return An integer describing the result of the function
 */
int new_mj_print(ast* expression, ast **node);

/**
 * Represents the main class of a MiniJava program
 */
typedef struct {
    /** The type of the node (nodetype.PRINT) */
    nodetype type;

    /** The id of the main class */
    mj_identifier *class_id;

    /** The id of the String[] parameter to the main method */
    mj_identifier *parameter_id;

    /** The statement inside the main methods body */
    ast *statements;
} mj_main_class;

/**
 * Creates a new main_class node with the given parameters
 *
 * @param[in] class_id The identifier of the main class
 * @param[in] parameter_id The identifier of the String[] parameter to the main 
 *                     method
 * @param[in] statements The statements inside the main methods body
 * @param[out] node The addres of the pointer that will point at the result 
 *                  of the function
 * @return An integer describing the result of the function
 */
int new_mj_main_class(ast *class_id, ast *parameter_id, ast* statements, 
                      ast **node);

/**
 * This struct stores the callbacks for the ast_walk function. Each time the 
 * ast_walk function encounters a node of a given type, the corresponding 
 * callback will be called.
 *
 * For example, if ast_walk function encounters a identifier node, 
 * the function pointer in the member on_identifier will be 
 * dereferenced and called.
 */
typedef struct {
    /** The callback for an identifier node */
    void (*on_mj_identifier)(mj_identifier *node, void *result);
    
    /** The callback for the addition binary operation */
    void (*on_mj_addition)(mj_binary_operation *node, void *result);
    
    /** The callback for the subtraction binary operation */
    void (*on_mj_subtraction)(mj_binary_operation *node, void *result);
    
    /** The callback for the division binary operation */
    void (*on_mj_division)(mj_binary_operation *node, void *result);

    /** The callback for the multiplication binary operation */
    void (*on_mj_multiplication)(mj_binary_operation *node, void *result);

    /** The callback for the logical and binary operation */
    void (*on_mj_and)(mj_binary_operation *node, void *result);

    /** The callback for the less than binary operation */
    void (*on_mj_less_than)(mj_binary_operation *node, void *result);
    
    /** The callback for the array lookup unary operation */
    void (*on_mj_array_lookup)(mj_binary_operation *node, void *result);

    /** The callback for the array length unary operation */
    void (*on_mj_array_length)(mj_unary_operation *node, void *result);
    
    /** The callback for the logical not unary operation */
    void (*on_mj_not)(mj_unary_operation *node, void *result);
   
    /** The callback for the new array unary operation */
    void (*on_mj_new_array)(mj_unary_operation *node, void *result);

    /** The callback for an integer */
    void (*on_mj_integer)(mj_integer *node, void *result);

    /** The callback for a this object */
    void (*on_mj_this)(ast *node, void *result);

    /** The callback for a boolean */
    void (*on_mj_boolean)(mj_boolean *node, void *result);

    /** The callback for an ast_list */
    void (*on_mj_ast_list)(mj_ast_list *node, void *result);

    /** The callback for a new_object operation */
    void (*on_mj_new_object)(mj_new_object *node, void *result);

    /** The callback for a call operation */
    void (*on_mj_call)(mj_call *node, void *result);

    /** The callback for a print statement */
    void (*on_mj_print)(mj_print *node, void *result);

    /** The callback for a main_class */
    void (*on_mj_main_class)(mj_main_class *node, void *result);
} ast_callbacks;

/**
 * This function walks an AST depth-first, left to right. 
 * Each time a node is encountered, the registered callback in 
 * the parameter callback will be called.
 *
 * @param[in] tree The AST to walk
 * @param[in] callbacks All the callbacks to call upon encountering nodes of 
 *                      specific types
 * @param[out] result A pointer to the result of the walk
 */
void ast_walk(ast* tree, ast_callbacks callbacks, void *result);

/**
 * This function visits the given node, that is, it calls the
 * callback that is registered for the nodes type.
 * This function should typically be called from the callback functions
 * in order to evaluate child nodes.
 *
 * @param[in] node The node to visit
 * @param[out] result The result from the visit
 */
void ast_visit(ast* node, void *result);

/**
 * Deletes an AST and all the nodes in the AST. 
 * NOTE: it also frees the char* in an mj_identifier, so make sure that you 
 * have copied this pointer if you use it elsewhere.
 *
 * @parameter tree The tree to delete
 */
void delete_ast(ast* tree);

#endif /* INCLUDE_jrv_ast_h__ */
