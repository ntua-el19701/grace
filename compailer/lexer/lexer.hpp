#ifndef __LEXER_HPP__
#define __LEXER_HPP__

int yylex();
void yyerror(const char *msg);
void yyerror(const char *msg, int line);
#endif