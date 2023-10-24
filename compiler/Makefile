.PHONY: clean distclean default

LLVMCONFIG=llvm-config
CXX = c++ -std=c++11
CXXFLAGS=-Wall -g `$(LLVMCONFIG) --cxxflags` -O3
LDFLAGS=`$(LLVMCONFIG) --ldflags --system-libs --libs all`

default: grace

lexer/lexer.cpp: lexer/lexer.l
	flex -s -olexer/lexer.cpp lexer/lexer.l

parser/parser.hpp parser/parser.cpp: parser/parser.y
	bison -dv -oparser/parser.cpp parser/parser.y

lexer/lexer.o: lexer/lexer.cpp lexer/lexer.hpp parser/parser.hpp 

parser/parser.o: parser/parser.cpp parser/parser.hpp

ast/ast.o: ast/ast.cpp ast/ast.hpp ast/astClass.hpp

ast/printAST.o: ast/printAST.cpp ast/ast.hpp
	$(CXX) $(CXXFLAGS) -c -o ast/printAST.o ast/printAST.cpp

sem/sem.o: ast/sem.cpp ast/ast.hpp
	$(CXX) $(CXXFLAGS) -c -o ast/sem.o ast/sem.cpp

ast/preCompile.o: ast/ast.hpp ast/preCompile.cpp

ast/compile.o: ast/ast.hpp ast/compile.cpp

grace: lexer/lexer.o parser/parser.o ast/printAST.o ast/sem.o ast/ast.o ast/compile.o ast/preCompile.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	$(RM) lexer/lexer.cpp parser/parser.cpp parser/parser.hpp parser/parser.output *.o

distclean: clean
	$(RM) grace
