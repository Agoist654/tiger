//**
// ** \file bind/libbind.cc
// ** \brief Define exported bind functions.
// */
//
//// FIXME: Some code was deleted here.
///*ONGOING*/
//

#include <bind/libbind.hh>
#include <bind/binder.hh>
namespace bind
{
    void bindings_compute(ast::Ast& tree)
    {
        Binder binding_compute;
        binding_compute(tree);
    }
}
