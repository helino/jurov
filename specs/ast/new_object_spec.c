#include "expectations.h"
#include "ast.h"

static new_object* create(ast *id)
{
    return (new_object *) new_new_object(id);
}

begin_example(new_object, should_have_new_object_as_type)
    ast *class_id;
    new_object *node;

    should_pass(new_identifier("foo", &class_id))
    node = create(class_id);
    should_eq_int(NEW_OBJECT, node->type);

    free(class_id);
    free(node);
end_example

begin_example(new_object, should_have_the_given_class_id_as_member)
    ast *class_id;
    new_object *node;

    should_pass(new_identifier("foo", &class_id))
    node = create(class_id);
    should_eq_ptr(class_id, node->class_id);

    free(class_id);
    free(node);
end_example

begin_description(new_object)
    add_example(should_have_new_object_as_type)
    add_example(should_have_the_given_class_id_as_member)
end_description
