#include "spectacular.h"
#include "ast.h"
#include "list.h"

static call* create(ast *object, ast *method, ast_list *parameters)
{
    return (call *) new_call(object, method, parameters);
}

begin_spec(call, should_have_call_as_type)
    list *list = new_list();
    ast_list *params = (ast_list *) new_ast_list(list);
    ast *method;
    ast *obj;
    
    should_pass(new_identifier("bar", &obj))
    should_pass(new_identifier("foo", &method))
    call *c = create(obj, method, params);
    should_eq_int(CALL, c->type)

    free(list);
    free(params);
    free(method);
    free(obj);
    free(c);
end_spec

begin_spec(call, should_have_the_parameters_as_members)
    list *list = new_list();
    ast_list *params = (ast_list *) new_ast_list(list);
    ast *method;
    ast *obj;
    
    should_pass(new_identifier("foo", &method))
    should_pass(new_identifier("bar", &obj))
    call *c = create(obj, method, params);
    should_eq_ptr(obj, c->object)
    should_eq_ptr(method, c->method)
    should_eq_ptr(params, c->parameters)

    free(list);
    free(params);
    free(method);
    free(obj);
    free(c);
end_spec

begin_blueprint(call)
    add_spec(should_have_call_as_type)
    add_spec(should_have_the_parameters_as_members)
end_blueprint
