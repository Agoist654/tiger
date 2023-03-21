#!/bin/sh


./src/tc -X --parse tests/good/array-of-alias.tig; echo " got: " $?
./src/tc -X --parse tests/good/array.tig; echo " got: " $?
./src/tc -X --parse tests/good/break-in-while.tig; echo " got: " $?
./src/tc -X --parse tests/good/comments-nested.tig; echo " got: " $?
./src/tc -X --parse tests/good/compare-record-and-nil.tig; echo " got: " $?
./src/tc -X --parse tests/good/fact.tig; echo " got: " $?
./src/tc -X --parse tests/good/for-in-let.tig
./src/tc -X --parse tests/good/fun-vs-var.tig; echo " got: " $?
./src/tc -X --parse tests/good/if.tig; echo " got: " $?
./src/tc -X --parse tests/good/local-vs-global-type.tig; echo " got: " $?
./src/tc -X --parse tests/good/merge.tig; echo " got: " $?
./src/tc -X --parse tests/good/mutually-recursive-functions.tig; echo " got: " $?
./src/tc -X --parse tests/good/mutually-recursive-procedures.tig; echo " got: " $?
./src/tc -X --parse tests/good/queens.tig; echo " got: " $?
./src/tc -X --parse tests/good/record.tig; echo " got: " $?
./src/tc -X --parse tests/good/recursive-types.tig; echo " got: " $?
./src/tc -X --parse tests/good/shadowing-functions.tig; echo " got: " $?
./src/tc -X --parse tests/good/shadowing-types-separate.tig; echo " got: " $?
./src/tc -X --parse tests/good/test27.tig; echo " got: " $?
./src/tc -X --parse tests/good/test30.tig; echo " got: " $?
./src/tc -X --parse tests/good/test37.tig; echo " got: " $?
./src/tc -X --parse tests/good/test42.tig; echo " got: " $?
./src/tc -X --parse tests/good/test44.tig; echo " got: " $?
./src/tc -X --parse tests/good/test64.tig; echo " got: " $?
./src/tc -X --parse tests/good/test64.tih; echo " got: " $?
./src/tc -X --parse tests/good/three-name-spaces.tig; echo " got: " $?
