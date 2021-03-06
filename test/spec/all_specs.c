#include "spectacular.h"

begin_description(ast)
    use_description(mj_ast_list)
    use_description(mj_binary_operation)
    use_description(ast_walk)
    use_description(mj_boolean)
    use_description(mj_call)
    use_description(mj_identifier)
    use_description(mj_integer)
    use_description(mj_main_class)
    use_description(mj_new_object)
    use_description(mj_print)
    use_description(mj_this)
    use_description(mj_unary_operation)
    use_description(mj_class)
    use_description(mj_type)
    use_description(mj_var_decl)
    use_description(mj_method_arg)
    use_description(mj_method_body)
    use_description(mj_method_decl)
    use_description(mj_if)
    use_description(mj_while)
    use_description(mj_assignment)
    use_description(mj_array_assignment)

    add_description(mj_ast_list)
    add_description(mj_binary_operation)
    add_description(ast_walk)
    add_description(mj_boolean)
    add_description(mj_call)
    add_description(mj_identifier)
    add_description(mj_integer)
    add_description(mj_main_class)
    add_description(mj_new_object)
    add_description(mj_print)
    add_description(mj_this)
    add_description(mj_unary_operation)
    add_description(mj_class)
    add_description(mj_type)
    add_description(mj_var_decl)
    add_description(mj_method_arg)
    add_description(mj_method_body)
    add_description(mj_method_decl)
    add_description(mj_if)
    add_description(mj_while)
    add_description(mj_assignment)
    add_description(mj_array_assignment)
end_description

begin_description(lexer)
    use_description(single_token_lexer)
    use_description(multiple_token_lexer)

    add_description(single_token_lexer)
    add_description(multiple_token_lexer)
end_description

begin_description(parser)
    use_description(main_class_parser)
    use_description(statement_parser)
    use_description(ast_parser)
    use_description(exp_parser)

    add_description(main_class_parser)
    add_description(statement_parser)
    add_description(ast_parser)
    add_description(exp_parser)
end_description

begin_description(jurov)
    use_description(list)
    use_description(errors)
    use_description(jrv_string)

    add_description(ast)
    add_description(lexer)
    add_description(parser)
    add_description(list)
    add_description(errors)
    add_description(jrv_string)
end_description

int main()
{
    return run_description(jurov)
}
