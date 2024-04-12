# Compiler for the programming language Grace
Team 34: <br>
Βασίλης Παπαδόπουλος, 03119701, vasilis.papadopoulos2000@gmail.com <br>
Αριστείδης Τζιαπούρας, 03119703, atjiapo@gmail.com

After cloning the code, you should run:
cd compiler <br>
make <br>
Then in order to run a .grc program you must run these:
grace <path to .grc program>  temp.ll <br>
llc -o temp.s temp.ll <br>
clang -o a.out temp.s libgrc.a -no-pie <br>
rm temp.s temp.ll <br>
a.out <br>

IMPORTANT NOTES:
There are some things not implemented properly/executed with small differences:
- We encountered a problem compiling the program with the given functions : strlen , strcmp, strcopy, strcat, writeString, readString. For that reason we tried to implement strlen and writeString by ourselves. In order to use these functions one can create a code for them in grace,
  For example : strcpy(cp, ev); <br>
  l <- strlen(ev);   <br>
  j<-0;   <br>
  while (j<l) do{  <br>
    cp[j]<-ev[j]; <br>
    j<-j+1; <br>
  }

- Because of the problem with the strings we implemented this statement as valid: w<-"abc";
  In functions when a "string" argument is required we changed the code to something similar
  For example:
      hanoi(NumberOfRings, ”left”, ”right”, ”middle”); => <br>
   x1<-"left";  <br>
   x2<-"right"; <br>
   x3<-"middle"; <br>
   hanoi(NumberOfRings,x1,x2,x3); <br>
  
- 2d+ arrays are implemented in semantic analysis, but not in the actual compiler(llvm).
 
- For every example availabe in https://github.com/kostis/ntua_compilers/blob/master/grace/programs/ we provide similar code in grace in the examples folder that works for our compiler.

