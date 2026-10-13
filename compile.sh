#!/bin/bash

rm -f *.pdf
lualatex -shell-escape -jobname=icpc-trd main.tex
lualatex -shell-escape -jobname=icpc-trd main.tex
find . -type f -regextype posix-extended -regex '^.+\.(aux|toc|bcf|blg|bbl|log|xml|out)$' -delete
rm -r _minted-icpc-trd
