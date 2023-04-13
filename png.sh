#! /bin/sh


./src/tc -X --ast-dump $1 > t.tig
dot -Tpng t.tig -o t.png
chromium t.png
