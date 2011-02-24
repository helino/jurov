#include "stddef.h"
#include "stdlib.h"
#include "CuTest.h"
#include "ast.h"
#include "errors.h"

static print* create(ast *expression)
{
    return (print *) new_print(expression);
}

void should_have_print_as_type(CuTest *tc)
{
    print *p = create(NULL);
    CuAssertIntEquals(tc, SYSTEM_OUT_PRINT, p->type);
    free(p);
}

void should_have_the_given_expression_as_member(CuTest *tc)
{
    ast* id;
    int res = new_identifier("foo", &id);
    CuAssertIntEquals(tc, JRV_SUCCESS, res);
    print *p = create(id);
    CuAssertPtrEquals(tc, id, p->expression);
    free(id);
    free(p);
}

CuSuite* ast_test_print()
{
    CuSuite *print = CuSuiteNew();

    SUITE_ADD_TEST(print, should_have_print_as_type);
    SUITE_ADD_TEST(print, should_have_the_given_expression_as_member);

    return print;
}
