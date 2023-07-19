#ifndef __AST_HPP__
#define __AST_HPP__

#include <iostream>
#include <string>
#include <vector>

class AST {
 public:
  virtual void printAST(std::ostream &out) const = 0;
};

inline std::ostream &operator<<(std::ostream &out, const AST &ast) {
  ast.printAST(out);
  return out;
}

class Expr : public AST {};

class Stmt : public AST {};

class Return : public Stmt {
public: 
    Return(Expr *e = nullptr) : expr(e) {}
private:
    Expr *expr;
};

class Id : public Expr {
public: 
    Id(char *s) : name(s) {}
    void printAST(std::ostream &out) const override {
        out << "Id(" << name << ")";
    }
private:
    char *name;
};

class Cond : public Expr {};

/*
class Cond : public AST {
public:
    Cond(Expr *e1, const char *o, Expr *e2) : expr1(e1), op(o), expr2(e2) {}
     void printAST(std::ostream &out) const override {
        out << "Cond(" << *expr1 << ", " << op << ", " << *expr2 << ")";
  }
private:
    Expr *expr1;
    const char *op;
    Expr *expr2;
};
*/
class Cond_combine : public  Cond {
public: 
    Cond_combine(Cond *c1, char *o, Cond *c2) : cond1(c1), op(o), cond2(c2) {}
    void printAST(std::ostream &out) const override {
        out << "Cond_Combine(" << *cond1 << ", " << op << ", " << *cond2 << ")";
  }
private:
    Cond *cond1;
    char *op;
    Cond *cond2;

};

class Not_cond : public Cond {
public: 
    Not_cond(Cond *c1) : cond(c1) {}
    void printAST(std::ostream &out) const override {
        out << "Not_cond(" << "Not " << *cond << ")";
  }
private:
    Cond *cond;
};

class If : public Stmt {
public:
    If(Cond *c, Stmt *s1, Stmt *s2 = nullptr) : condition(c), stmt1(s1), stmt2(s2){}
    void printAST(std::ostream &out) const override {
        out << "If(" << *condition << ", " << *stmt1;
        if(stmt2 != nullptr) out << ", " << *stmt2;
        out << ")";
    }
private: 
    Cond *condition;
    Stmt *stmt1;
    Stmt *stmt2;

};

class While : public Stmt {
public:
    While(Cond *c, Expr *e) :  condition(c), ex(e){}
    void printAST(std::ostream &out) const override {
        out << "While(" << *condition << ", " << *ex << ")";
    }
private:
    Cond *condition;
    Expr *ex;
};

class Block : public Stmt{
public: 
    Block() : stmt_list() {}
    void append(Stmt *s) { stmt_list.push_back(s); }
    void printAST(std::ostream &out) const override {
        out<<"Block(";
        bool first = true;
        for (const auto &s : stmt_list) {
            if(!first) out << ", ";
            first = false;
            out << *s;
        }
    }
private:
    std::vector<Stmt *> stmt_list;
};

class Comma_id_gen : public AST{
public:
    Comma_id_gen(Id i, Comma_id_gen *c) : name(i), comma_id_gen(c) {}
    void printAST(std::ostream &out) const override {
        out<< "Comma_id_gen("  << name;
        if(comma_id_gen != nullptr) { out << ", " <<  *comma_id_gen << ")"; }
    }
private:
    Id name;
    Comma_id_gen *comma_id_gen;    
};

class Data_type : public AST {
public:
    Data_type(char *s) : type(s) {}
    void printAST(std::ostream &out) const override {
        out << "Data_type(" << type << ")";
    }
private:
    char *type;
};

class Type_gen : public AST{
public:
    Type_gen(int a, Type_gen *tg = nullptr) : n(a), type_gen(tg){}
    void printAST(std::ostream &out) const override {
        out<< "Type_gen("  << n;
        if(type_gen != nullptr) { out << ", " <<  *type_gen << ")"; }
    }
private:
    int n;
    Type_gen *type_gen;

};

class Fpar_type : public AST {
public:
    Fpar_type(Data_type dt, Type_gen *tg) : data_type(dt), type_gen(tg){}
    void printAST(std::ostream &out) const override {
        out << "Fpar_type(" << data_type;
        if(type_gen != nullptr) { out << ", " << *type_gen; }
    }
private:
    Data_type data_type;
    Type_gen *type_gen;

};

class Fpar_def : public AST {
public:
    Fpar_def(bool flag, Id i, Comma_id_gen *c = nullptr, Fpar_type *fpt = nullptr) : ref(flag), name(i), comma_id_gen(c), fpar_type(fpt) {}
     void printAST(std::ostream &out) const override {
        out << "Fpar_def(" << name;
        if(comma_id_gen != nullptr){ out << " ," << *comma_id_gen ;}
        out<< ", "<< *fpar_type << ")";
     }
private:
    bool ref;
    Id name;
    Comma_id_gen *comma_id_gen;
    Fpar_type *fpar_type;
};

class Fpar_def_gen : public AST {
public:
     Fpar_def_gen(Fpar_def *fp, Fpar_def_gen *fpg) : fpar_def(fp), fpar_def_gen(fpg) {}
      void printAST(std::ostream &out) const override {
        if(fpar_def_gen == nullptr){
            out << "Fpar_def_gen("; fpar_def->printAST(out); out << ")";
        }
        else{
            out << "Fpar_def_gen("; fpar_def_gen->printAST(out); out << ", "; fpar_def->printAST(out); out << ")";
        }
      }
private :
    Fpar_def *fpar_def;
    Fpar_def_gen *fpar_def_gen;     
};

class Ret_type : public AST {
public:
    Ret_type(char *s) : type(s){}
    void printAST(std::ostream &out) const override {
        out << "Ret_type(" << type << ")";
    }
private:
    char *type;   
};

class Header : public  AST {
public: 
    Header(Id i, Fpar_def *fp , Fpar_def_gen *fpg , Ret_type *r) : name(i), fpar_def(fp), fpar_def_gen(fpg), ret_type(r) {}
    void printAST(std::ostream &out) const override {
        out << "Header " << name << ", ";
        if(fpar_def != nullptr) out << *fpar_def;
        if(fpar_def_gen != nullptr) out << *fpar_def_gen;
        out << *ret_type << ")";
    }
private:
    Id name;
    Fpar_def *fpar_def;
    Fpar_def_gen *fpar_def_gen;
    Ret_type *ret_type;
};

class Type : public AST {
public:
    Type(Data_type dt, Type_gen *tg) : data_type(dt), type_gen(tg){}
    void printAST(std::ostream &out) const override {
        out<< "Type("  << data_type;
        if(type_gen != nullptr) { out << ", " <<  *type_gen << ")"; }
    }
private:
    Data_type data_type;
    Type_gen *type_gen;
};


class Func_decl : public  AST {
public:
    Func_decl(Header *h) : header(h){}
    void printAST(std::ostream &out) const override {
        out << "Func_decl(" << *header << ")";
    }
private:
    Header *header;
};

class Var_def : public AST {
public:
    Var_def(Id i, Comma_id_gen *c, Type *t) : id(i), comma_id_gen(c), type(t){}
     void printAST(std::ostream &out) const override {
        out << "Var_def(" << id;
        if(comma_id_gen != nullptr) out << ", " << *comma_id_gen;
        if(type != nullptr) out << ", " << *type;
        out << ")";
     }
private:
    Id id;
    Comma_id_gen *comma_id_gen;
    Type *type;
};

class Comma_expr_gen : public AST{
public:
    Comma_expr_gen(Expr *e, Comma_expr_gen *c) : expr(e), comma_expr_gen(c){}
    void printAST(std::ostream &out) const override {
        out << "Comma_expr_gen(" << *expr;
        if(comma_expr_gen != nullptr) out << ", " << *comma_expr_gen;
        out << ")";
     }
private:
    Expr *expr;
    Comma_expr_gen *comma_expr_gen;
};

class Func_call : public  AST{
public:
    Func_call(Id i, Expr *e, Comma_expr_gen *c) : id(i), expr(e), comma_expr_gen(c){}
    void printAST(std::ostream &out) const override {
        out << "Func_call(" << id;
        out << ", " << *expr;
        if(comma_expr_gen != nullptr) out << ", " << *comma_expr_gen;
        out << ")";
     }
private:
    Id id;
    Expr *expr;
    Comma_expr_gen *comma_expr_gen;
};

class Local_def : public AST {};

class Local_def_gen : public AST {
public:
    Local_def_gen(Local_def *ld, Local_def_gen *ldg) : local_def(ld), local_def_gen(ldg) {}
    void printAST(std::ostream &out) const override {
        if(local_def_gen == nullptr){
            out << "Local_def_gen"; local_def->printAST(out); out << ")";
        }
        else{
            out << "Local_def_gen"; local_def_gen->printAST(out); out << ", "; local_def->printAST(out); out << ")";
        }
      }
private: 
    Local_def *local_def;    
    Local_def_gen *local_def_gen;
};

class Func_def : public AST {
public:
    Func_def(Header *h, Local_def_gen *ldg, Block *blk) : header(h), local_def_gen(ldg), block(blk) {}
     void printAST(std::ostream &out) const override {
        out << "aris(" << *header << ", " << *local_def_gen << ", " << *block << ")";
     }
private:
    Header *header;
    Local_def_gen *local_def_gen;
    Block *block;    
};
/*
class Local_def : public AST {
public:
    Local_def(Func_def *fdf, Fun_decl *fdl, Var_def *vdef) : func_def(fdf), func_decl(fdl), var_def(vdef){}
    void printAST(std::ostream &out) const override {
        out << "Local_def(";
        if(func_def != nullptr) out << *func_def;
        else if (func_decl != nullptr) out << *func_decl;
        else if (var_def != nullptr) out << *var_def;
        out <<")";  

    }
private:
    Func_def *func_def;  
    Func_decl *func_decl; 
    Var_def *var_def;  
};*/

class L_value : public  AST {
public:
    L_value(L_value *l, Expr *e) : l_value(l), expr(e){}
    void printAST(std::ostream &out) const override {
        out << "L_value(" << *l_value << ", " << *expr << ")";
    }
private:
    L_value *l_value;
    Expr *expr;
};

class Const_int : public Expr {
public:
    Const_int(int c): constant(c){}
    void printAST(std::ostream &out) const override {
        out << "Const_int(" << constant << ")";
    }
private:
    int constant;
};

class Const_string : public Expr {
public:
    Const_string(char *c): constant(c){}
    void printAST(std::ostream &out) const override {
        out << "Const_string(" << constant << ")";
    }
private:
    char *constant;
};

class Const_char : public Expr {
public:
    Const_char(char *c): constant(c){}
    void printAST(std::ostream &out) const override {
        out << "Const_char(" << constant << ")";
    }
private:
    char *constant;
};

class BinOp : public  Expr {
public:
    BinOp(Expr *e1, char *o, Expr *e2) : expr1(e1), op(o), expr2(e2) {}
    void printAST(std::ostream &out) const override {
        out << op << "(" << *expr1 << ", " << *expr2 << ")";
  }
private:
    Expr *expr1;
    char *op;
    Expr *expr2;
};

class UnOp : public  Expr {
public : 
    UnOp(char *o, Expr *e) : op(o), expr(e) {}
    void printAST(std::ostream &out) const override {
        out << "UnOp(" <<  op << ", " << *expr << ")";
  }
private:
    char *op;
    Expr *expr;
};





#endif