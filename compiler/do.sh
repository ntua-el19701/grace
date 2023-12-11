#!/usr/bin/env bash
grace <../examples/ex1.grc

grace <../examples/ex1.grc>  temp.ll
llc -o temp.s temp.ll
clang -o a.out temp.s libgrc.a -no-pie
rm temp.s temp.ll
a.out


grace <../examples/ex2.grc>  temp.ll
llc -o temp.s temp.ll
clang -o a.out temp.s libgrc.a -no-pie
rm temp.s temp.ll
a.out

grace <../examples/primes.grc>  temp.ll
llc -o temp.s temp.ll
clang -o a.out temp.s libgrc.a -no-pie
rm temp.s temp.ll
a.out   

grace <../examples/evenodd.grc>  temp.ll
llc -o temp.s temp.ll
clang -o a.out temp.s libgrc.a -no-pie
rm temp.s temp.ll
a.out

grace <../examples/shortcircuit.grc>  temp.ll
llc -o temp.s temp.ll
clang -o a.out temp.s libgrc.a -no-pie
rm temp.s temp.ll
a.out

grace <../examples/addchar.grc>  temp.ll
llc -o temp.s temp.ll
clang -o a.out temp.s libgrc.a -no-pie
rm temp.s temp.ll
a.out


grace <../examples/divisibleby3.grc>  temp.ll
llc -o temp.s temp.ll
clang -o a.out temp.s libgrc.a -no-pie
rm temp.s temp.ll
a.out

grace <../examples/bsort.grc>  temp.ll
llc -o temp.s temp.ll
clang -o a.out temp.s libgrc.a -no-pie
rm temp.s temp.ll
a.out

grace <../examples/hanoi.grc>  temp.ll
llc -o temp.s temp.ll
clang -o a.out temp.s libgrc.a -no-pie
rm temp.s temp.ll
a.out

grace <../examples/stepinski.grc>  temp.ll
llc -o temp.s temp.ll
clang -o a.out temp.s libgrc.a -no-pie
rm temp.s temp.ll
a.out

grace <../examples/s.grc>  temp.ll
llc -o temp.s temp.ll
clang -o a.out temp.s libgrc.a -no-pie
rm temp.s temp.ll
a.out

grace <../examples/strrev.grc>  temp.ll
llc -o temp.s temp.ll
clang -o a.out temp.s libgrc.a -no-pie
rm temp.s temp.ll
a.out

grace <../examples/error.grc>  temp.ll
llc -o temp.s temp.ll
clang -o a.out temp.s libgrc.a -no-pie
rm temp.s temp.ll
a.out

grace <../examples/undvar.grc>  temp.ll
llc -o temp.s temp.ll
clang -o a.out temp.s libgrc.a -no-pie
rm temp.s temp.ll
a.out

grace <../examples/wrongfunc.grc>  temp.ll
llc -o temp.s temp.ll
clang -o a.out temp.s libgrc.a -no-pie
rm temp.s temp.ll
a.out

grace <../examples/redefine.grc>  temp.ll
llc -o temp.s temp.ll
clang -o a.out temp.s libgrc.a -no-pie
rm temp.s temp.ll
a.out