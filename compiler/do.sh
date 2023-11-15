#!/usr/bin/env bash
grace <../examples/ex1.grc
grace <../examples/ex1.grc>  temp.ll
llc -o temp.s temp.ll
clang -o a.out temp.s libgrc.a -no-pie
rm temp.s temp.ll
a.out