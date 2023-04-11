///**
// ** \file bind/tasks.cc
// ** \brief Bind module tasks implementation.
// */
//
//// FIXME: Some code was deleted here.
/////*ONGOING*/
//
#include <ast/libast.hh>
#include <ast/tasks.hh>
#define DEFINE_TASKS 1
#include <bind/tasks.hh>
#undef DEFINE_TASKS
#include <bind/libbind.hh>

namespace bind::tasks
{
    void bindings_compute() { bind::bindings_compute(*ast::tasks::the_program); }
    void bindings_display() { ast::bindings_display(std::cout) = true; }
    void rename() { bind::rename(*ast::tasks::the_program); }
}
//void rename() { bind::new_name_compute(*ast::tasks::the_program); }

