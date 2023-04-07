/**
 ** \file bind/tasks.hh
 ** \brief Bind module related tasks.
 */

// FIXME: Some code was deleted here.
/*ONGOING | implement Tasks macros for binding-compute, bindings-display and bound*/

#pragma once

#include <task/libtask.hh>

namespace bind::tasks
{
    TASK_GROUP("3. Bind");

    TASK_DECLARE("b|bindings-compute",
                 "compute binding of variables and functions",
                 bindings_compute,
                 "parse");
    TASK_DECLARE("B|bindings-display",
                 "show details of variable and function bindings in AST",
                 bindings_display,
                 "binding-compute");
    DISJUNCTIVE_TASK_DECLARE("bound",
                 "ensures binding has been computed "
                 "at least one way, executes binding-compute"
                 "if not.",
                 "binding-compute"
                 "object-bindings-compute"
                 "combine-types-compute");
    /*TASK_DECLARE("rename",
                 "rename all symbols so all ids are unique",
                 rename,
                 "bindings-compute");*/
}
