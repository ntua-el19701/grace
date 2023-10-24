%{
#include <cstdio>
#include <iostream>
#include "lexer.hpp"
#include "ast.hpp"
#include <string>

%}

%union{   
   AST *program;
   int num;
   char *id;
   char op;
   char *const_char;
   char *const_str;
   Expr *expr;
   Stmt *stmt;
   Cond *cond; 
   Block *stmt_list;
   Func_def *func_def;
   Local_def_gen *local_def_gen;
   Header *header;
   Fpar_def_gen *fpar_def_gen;
   Fpar_def *fpar_def;
   Comma_id_gen *comma_id_gen;
   Data_type data_type;
   Type_gen *type_gen;
   Ret_type ret_type;
   Fpar_type *fpar_type;
   Local_def *local_def;
   Func_decl *func_decl;
   Var_def *var_def;
   Func_call *func_call;
   Comma_expr_gen *comma_expr_gen;
   L_value *l_value;
   UnOp *expr_high;
   Cond *cond_high;
 
}


%token T_eof     0
%token T_and     "and"
%token T_char    "char"
%token T_div     "div"
%token T_do      "do"
%token T_else    "else"
%token T_fun     "fun"
%token T_if      "if"
%token T_int     "int"
%token T_mod     "mod"
%token T_not     "not"
%token T_nothing "nothing" 
%token T_or      "or"
%token T_ref     "ref"
%token T_return  "return"
%token T_then    "then"
%token T_var     "var"
%token T_while   "while"

%token<id>  T_id      
%token<num> T_const_int "const_int"
%token<const_char> T_const_char 
%token<const_str> T_const_string 
%token T_geq ">="
%token T_leq "<="
%token T_assign "<-"



%left '+' '-'
%left '*' "div" "mod" 
%nonassoc '=' '#' '>' '<' "<=" ">=" 
%nonassoc "not"
%left "and"
%left "or"


%expect 1 //if then else

%type<program> program
%type<stmt> stmt
%type<expr> expr
%type<cond> cond
%type<stmt_list> stmt_list 
%type<stmt_list> block
%type<func_def> func_def
%type<local_def_gen> local_def_gen
%type<header> header
%type<fpar_def_gen> fpar_def_gen
%type<fpar_def> fpar_def
%type<comma_id_gen> comma_id_gen
%type<data_type> type
%type<data_type> data_type
%type<type_gen> type_gen
%type<ret_type> ret_type 
%type<fpar_type> fpar_type 
%type<local_def> local_def
%type<func_decl> func_decl
%type<var_def> var_def
%type<func_call> func_call 
%type<comma_expr_gen> comma_expr_gen;
%type<l_value> l_value
%type<expr_high> expr_high
%type<cond_high> cond_high



%%

program:
        func_def                                                   { $$ = $1; }                    
        ;

func_def: 
        header local_def_gen block                                 { $$ = new Func_def($1, $2, $3); }                    
        ;

local_def_gen: 
        /*nothing*/                                                { $$ = nullptr; }
        | local_def local_def_gen                                  { $$ = new Local_def_gen($1, $2); }     
        ;
        
header:                                                            
        T_fun T_id '(' ')' ':' ret_type                            { $$ = new Header($2, nullptr, nullptr, $6); }
        | T_fun T_id '(' fpar_def fpar_def_gen ')' ':' ret_type    { $$ = new Header($2, $4, $5, $8); }     
        ;
        
fpar_def_gen: 
        /*nothing*/                                                { $$ = nullptr; }
        | ';' fpar_def fpar_def_gen                                { $$ = new Fpar_def_gen($2, $3); }
        ;

fpar_def:
        T_ref T_id comma_id_gen ':' fpar_type                      { $$ = new Fpar_def("True", $2, $3, $5); }
        | T_id comma_id_gen ':' fpar_type                          { $$ = new Fpar_def("False", $1, $2, $4); }
        ;

comma_id_gen: 
        /*nothing*/                                                { $$ = nullptr; }
        | ',' T_id comma_id_gen                                    { $$ = new Comma_id_gen($2, $3); }
        ;

data_type:                                                         
        T_int                                                      { $$ = new Data_type("int"); }     
        | T_char                                                   { $$ = new Data_type("char"); }                                  
        ;

type:                                                              
        data_type type_gen                                         { $$  = new Type($1, $2); }     
        ;       

type_gen: 
        /*nothing*/                                                { $$ = nullptr; }
        | '[' T_const_int ']' type_gen                             { $$ = new Type_gen($2, $4); }
        ;

ret_type:
        data_type                                                  { $$ = new Ret_type($1); }     
        | T_nothing                                                { $$ = new Ret_type("nothing"); }     
        ;

fpar_type:
        data_type '[' ']' type_gen                                 { $$ = new Fpar_type($1, $4); }
        | data_type type_gen                                       { $$ = new Fpar_type($1, $2); }
        ;

local_def:                                                     
        func_def                                                   { $$ = $1 }      
        | func_decl                                                { $$ = $1 }     
        | var_def                                                  { $$ = $1 } 
        ;

func_decl: 
        header ';'                                                 { $$ = new Func_decl($1); }     
        ;

var_def: 
        T_var T_id comma_id_gen ':' type ';'                       { $$ = new Var_def( $2, $3, $5); }     
        ;

stmt: 
        ';'                                                        { $$ = nullptr;}        
        | l_value T_assign expr ';'                                { $$ = new Assign($1, $3); }
        | block                                                    { $$ = $1; }
        | func_call ';'                                            { $$ = $1; }
        | T_if cond T_then stmt                                    { $$ = new If($2, $4); }
        | T_if cond T_then stmt T_else stmt                        { $$ = new If($2, $4, $6); }
        | T_while cond T_do stmt                                   { $$ = new While($2, $4); }
        | T_return ';'                                             { $$ = new Return(); }
        | T_return expr ';'                                        { $$ = new Return($2); }       
        ;

block: '{' stmt_list '}'                                           { $$ = $2; }
        ;

stmt_list:                                                      
        /*nothing*/                                                { $$ = new Block(); }
        | stmt stmt_list                                           { $2->append($1); $$ = $2;}
        ;

func_call: 
        T_id '(' ')'                                               { $$ = new Func_call($1, nullptr, nullptr); /* $$ = $1;*/ }
        | T_id '(' expr comma_expr_gen ')'                         { $$ = new Func_call($1, $3, $4); }
        ;

comma_expr_gen: 
        /*nothing*/                                                { $$ = nullptr; }
        | ',' expr comma_expr_gen                                  { $$ = new Comma_expr_gen($2, $3); }
        ;

l_value:                                                           
        T_id                                                       { $$ = new Id($1); }
        | T_const_string                                           { $$ = new Const_string($1); }
        | l_value '[' expr ']'                                     { $$ = new L_value($1, $3); }
        ;

expr: 
        T_const_int                                                { $$ = new Const_int($1); }
        | T_const_char                                             { $$ = new Const_char($1); }
        | l_value                                                  { $$ = $1; }
        | expr_high                                                { $$ = $1; }
        | func_call                                                { $$ = $1; }
        | expr '+' expr                                            { $$ = new BinOp($1, '+', $3); }     
        | expr '-' expr                                            { $$ = new BinOp($1, '-', $3); }      
        | expr '*' expr                                            { $$ = new BinOp($1, '*', $3); } 
        | expr T_div expr                                          { $$ = new BinOp($1, "div", $3); } 
        | expr T_mod expr                                          { $$ = new BinOp($1, "mod", $3); } 
        ;

expr_high: 
        '(' expr ')'                                               { $$ = $2; }
        | '+' expr                                                 { $$ = new UnOp('+', $2); }
        | '-' expr                                                 { $$ = new UnOp('-', $2); }
        ;

cond:
        cond_high                                                  { $$ = $1; }
        | cond T_and cond                                          { $$ = new Cond_combine($1, "and", $3); }
        | cond T_or cond                                           { $$ = new Cond_combine($1, "or", $3); }     
        | expr '=' expr                                            { $$ = new Expr($1, '=', $3); }
        | expr '#' expr                                            { $$ = new Expr($1, '#', $3); }
        | expr '>' expr                                            { $$ = new Expr($1, '>', $3); }
        | expr '<' expr                                            { $$ = new Expr($1, '<', $3); }
        | expr T_geq expr                                          { $$ = new Expr($1, ">=", $3); }
        | expr T_leq expr                                          { $$ = new Expr($1, "<=", $3); }
        ;

cond_high: 
        '(' cond ')'                                               { $$ = $2; }
        | T_not cond                                               { $$ = new Not_cond($2); }
        ;





%%

int main() {
  int result = yyparse();
  if (result == 0) printf("Success.\n");
  return result;

}