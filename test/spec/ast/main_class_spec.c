#include "expectations.h"
#include "ast/ast_list.h"
#include "ast/mj_identifier.h"
#include "ast/mj_main_class.h"

begin_example(mj_main_class, should_have_mj_main_class_as_type)
    mj_main_class *mc;

    should_pass(new_mj_main_class(NULL, NULL, NULL, (ast **) &mc))
    should_eq_int(MJ_MAIN_CLASS, mc->type)

    free(mc);
end_example

begin_example(mj_main_class, should_have_the_given_parameters_as_members)
    ast* class_id;
    ast* param_id;
    ast* statement;
    mj_main_class *mc;

    should_pass(new_mj_identifier("args", &param_id))
    should_pass(new_mj_identifier("Main", &class_id))
    should_pass(empty_mj_ast_list(&statement))
    should_pass(new_mj_main_class(class_id, param_id, statement, (ast **) &mc))
    should_eq_ptr(class_id, mc->class_id)
    should_eq_ptr(param_id, mc->parameter_id)
    should_eq_ptr(statement, mc->statements) 

    free(class_id);
    free(param_id);
    delete_ast(statement);
    free(mc);
end_example

begin_description(mj_main_class)
    add_example(should_have_mj_main_class_as_type)
    add_example(should_have_the_given_parameters_as_members)
end_description
