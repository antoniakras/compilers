%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "syntax_header.h"
    #include "tcode.h"
    #include "avm.h"
    #define  YY_DECL int alpha_yylex (void* ylval)
    int yylex(void);
    int  curr_scope=0; // current scope variable.
    int function_nested=0;
    int buf_counter=0;
    int namespace_flag=0;
    int for_flag=0;	
    int while_flag=0;
    int flagSemicolon=0;
    int flagLogical=0;
    char buf[50];
    extern int yylineno;
    extern char* yytext;
    int yyerror (char* yaccProvidedMessage);
    extern FILE* yyin;

%}

%start program

%union {int int_val; 
double real_val; 
char* string_Val; 
unsigned int unint_val;
struct sym_t* sym;
struct expr* expr;
struct stmt_t* stmt;
struct call* call_f;
struct for_p* for_p;
}


%token IF
%token ELSE
%token WHILE
%token FOR
%token FUNCTION
%token RETURN          
%token <stmt> BREAK           
%token <stmt> CONTINUE     
%token AND    
%token NOT    
%token OR              
%token LOCAL           
%token TRUE            
%token FALSE           
%token NIL             
%token EQUAL		
%token PLUS		
%token MINUS		
%token MULTIPLY
%token SLASH_F
%token PERCENT	
%token EQUAL_TWO	
%token NOT_EQUAL	
%token PLUS_TWO	
%token MINUS_TWO	
%token GREATER		
%token LESS		
%token B_EQUAL	
%token L_EQUAL	
%token <int_val> NUM		
%token <real_val> FLOAT		
%token <string_Val> STRING	   
%token LEFT_BRACKET	
%token RIGHT_BRACKET     
%token LEFT_SQ_BRACKET	
%token RIGHT_SQ_BRACKET	
%token LEFT_PARENTH
%token RIGHT_PARENTH	
%token SEMICOLON		
%token COMMA			
%token COLON			
%token NAMESPACE_ 
%token DOT			
%token DOT_TWO		
%token <string_Val> ID 		

//set order of operations.

%right EQUAL NOT
%left LEFT_PARENTH RIGHT_PARENTH 
%left  AND OR 
%nonassoc EQUAL_TWO  NOT_EQUAL
%left GREATER B_EQUAL LESS L_EQUAL 
%left COMMA
%right  MINUS	
%right  PLUS_TWO MINUS_TWO
%left PLUS 
%left LEFT_BRACKET RIGHT_BRACKET
%left MULTIPLY SLASH_F PERCENT 
%left DOT DOT_TWO


%type <expr> lvalue
%type <expr> member
%type <expr> const
%type <expr> expr
%type <expr> exprs
%type <expr> assignexpr
%type <expr> funcdef
%type <expr> call
%type <expr> term
%type <expr> elist
%type <expr> idlist
%type <call_f> callsuffix
%type <call_f> methodcall
%type <call_f> normcall
%type <expr> primary
%type <int_val> ifprefix 
%type <int_val> elseprefix
%type <int_val> M
%type <int_val> N
%type <expr> objectdef 
%type <int_val> whilestart
%type <int_val> whilecond
%type <stmt> stmt stmts returnstmt
%type <expr> indexed
%type <expr> indexedelem
%type <expr> indexedelems
%type <for_p> forprefix

%%
program: stmts  
        ;

 stmts: stmt  stmts {
        $$=$1;
         
        // if($2!=NULL && $1!=NULL){
        //         $$->breakList = mergeList($1->breakList, $2->breakList);
        //         $$->contList = mergeList($1->contList, $2->contList);   
        // }
        }
        |{$$=NULL;}
        ;

stmt: expr SEMICOLON {
        namespace_flag=0; 
 
        if($1->type==boolexpr_e || $1->type==constbool_e){
        backPatch($1->trueList,nextQuad());
        backPatch($1->falseList,nextQuad()+2);

        emit(assign,newExpr_constBool(1),NULL,$1,-1,yylineno);
        emit(jump,NULL,NULL,NULL,nextQuad()+2,yylineno);
        emit(assign,newExpr_constBool(0),NULL,$1,-1,yylineno);
        
        }


        }
    |ifstmt {}
    |while {$$ = NULL;}
    |for {$$=NULL;}
    |returnstmt {

        $1 = make_stmt($1);
        $1->returnList = newList(nextQuad());
        push(returnst,$1->returnList);
        emit(jump, NULL, NULL, newExpr(var_e), -1, yylineno);

    }
 |BREAK { if(while_flag==0 && for_flag==0){
         yyerror("Break out of loop");
        }else{
                $1 = make_stmt($1);
                $1->breakList = newList(nextQuad());
                push(breakst,$1->breakList);
                emit(jump, NULL, NULL, NULL, -1, yylineno);
        } 
    }  SEMICOLON   	
    |CONTINUE { if(while_flag==0 && for_flag==0){
            yyerror("Continue out of loop");
        }else{
                $1 = make_stmt($1);
                $1->contList = newList(nextQuad());
                push(contst,$1->contList);
                emit(jump, NULL, NULL, NULL, -1, yylineno);
        }  
    }  SEMICOLON 
    |block {$$=NULL;}   
    |funcdef {}  
    |SEMICOLON {$$=NULL;}
    ;


expr: assignexpr {$$=$1; flagSemicolon=1;}

    | expr PLUS expr {   
        $$=newExpr(arithexpr_e);
        $$->sym=newtemp();
        if($1->type==constnum_e && $3->type==constnum_e) $$->type = constnum_e;
        emit(add,$1, $3, $$ ,-1 ,yylineno);       
    } 
    | expr MINUS expr  {
        $$=newExpr(arithexpr_e);
        $$->sym=newtemp();
        if($1->type==constnum_e && $3->type==constnum_e) $$->type = constnum_e;
        emit(sub,$1, $3, $$ ,-1 ,yylineno);
    }  
    | expr MULTIPLY expr{
        $$=newExpr(arithexpr_e);
        $$->sym=newtemp();
        if($1->type==constnum_e && $3->type==constnum_e) $$->type = constnum_e;
        emit(mul,$1, $3, $$ ,-1 ,yylineno);
    }   
    | expr SLASH_F expr{
        $$=newExpr(arithexpr_e);
        $$->sym=newtemp();
        if($1->type==constnum_e && $3->type==constnum_e) $$->type = constnum_e;
        emit(_div,$1, $3, $$ ,-1 ,yylineno);
    }    
    | expr PERCENT expr{
        $$=newExpr(arithexpr_e);
        $$->sym=newtemp();
        if($1->type==constnum_e && $3->type==constnum_e) $$->type = constnum_e;
        emit(mod,$1, $3, $$ ,-1 ,yylineno);
    }    
    | expr LESS expr{            
        $$=newExpr(boolexpr_e);
        $$->sym=newtemp();

        $$->trueList = makeList(nextQuad());

        $$->falseList = makeList(nextQuad()+1);

        emit(if_less,$1, $3, $$ ,-1 ,yylineno);

        emit(jump,NULL,NULL,NULL,-1,yylineno);
       
    }    
    | expr B_EQUAL expr {


        $$=newExpr(boolexpr_e);
        $$->sym=newtemp();

        $$->trueList = makeList(nextQuad());

        $$->falseList = makeList(nextQuad()+1);

        emit(if_greatereq,$1, $3, $$ ,-1 ,yylineno);

        emit(jump,NULL,NULL,NULL,-1,yylineno);
    } 
    | expr EQUAL_TWO expr {


        $$=newExpr(boolexpr_e);
        $$->sym=newtemp();

        $$->trueList = makeList(nextQuad());

        $$->falseList = makeList(nextQuad()+1);

        emit(if_eq,$1, $3, $$ ,-1 ,yylineno);

        emit(jump,NULL,NULL,NULL,-1,yylineno);
    }  
    | expr GREATER expr{

        $$=newExpr(boolexpr_e);
        $$->sym=newtemp();

        $$->trueList = makeList(nextQuad());

        $$->falseList = makeList(nextQuad()+1);


        emit(if_greater,$1, $3, $$ ,-1 ,yylineno);

        emit(jump,NULL,NULL,NULL,-1,yylineno);
    }   
    | expr L_EQUAL expr {


        $$=newExpr(boolexpr_e);
        $$->sym=newtemp();

        $$->trueList = makeList(nextQuad());

        $$->falseList = makeList(nextQuad()+1);


        emit(if_lesseq,$1, $3, $$ ,-1 ,yylineno);

        emit(jump,NULL,NULL,NULL,-1,yylineno);
    }  
    | expr NOT_EQUAL expr{

        $$=newExpr(boolexpr_e);
        $$->sym=newtemp();

        $$->trueList = makeList(nextQuad());

        $$->falseList = makeList(nextQuad()+1);

        emit(if_noteq,$1, $3, $$ ,-1 ,yylineno);

        emit(jump,NULL,NULL,NULL,-1,yylineno);
    }    
    | expr OR M expr {  
          
            if($1->type!=boolexpr_e)
        {     
                convert2Bool($1);
                $1->trueList = makeList(nextQuad());
                $1->falseList = makeList(nextQuad()+1);
                emit(if_eq,$1, newExpr_constBool(1), $$ ,nextQuad(),yylineno);
                emit(jump,NULL,NULL,NULL,nextQuad()+1,yylineno);
                $3= nextQuad();
            
        }
         if($4->type!=boolexpr_e)
        {    
               
                convert2Bool($4);
                $4->trueList = makeList(nextQuad());
                $4->falseList = makeList(nextQuad()+1);
                emit(if_eq,$4, newExpr_constBool(1), $$ ,nextQuad(),yylineno);
                emit(jump,NULL,NULL,NULL,nextQuad()+1,yylineno);

        }

        $$=newExpr(boolexpr_e);
        $$->sym=newtemp();
        backPatch($1->falseList, $3);
        backPatch($1->trueList,nextQuad());
        // orQuad = $1->trueList->label;
       
        $$->trueList = mergeBackPatch($1->trueList,$4->trueList);
        $$->falseList = $4->falseList;

    } 
     | expr AND M expr {
        if($1->type!=boolexpr_e)
        {      
                convert2Bool($1);
                $1->trueList = makeList(nextQuad());
                $1->falseList = makeList(nextQuad()+1);
                emit(if_eq,$1, newExpr_constBool(1), $$ ,nextQuad(),yylineno);
                emit(jump,NULL,NULL,NULL,nextQuad()+1,yylineno);
                      $3= nextQuad();
        }
         if($4->type!=boolexpr_e )
        {       
                convert2Bool($4);
                $4->trueList = makeList(nextQuad());
                $4->falseList = makeList(nextQuad()+1);
                emit(if_eq,$4, newExpr_constBool(1), $$ ,nextQuad(),yylineno);
                emit(jump,NULL,NULL,NULL,nextQuad()+1,yylineno);
          

        }
        $$=newExpr(boolexpr_e);
        $$->sym=newtemp();
        backPatch($1->trueList, $3);
        backPatch($1->falseList,nextQuad()+2);
        
        $$->trueList = $4->trueList;
        $$->falseList = mergeBackPatch($1->falseList,$4->falseList);
//   if(eimaiOr==1)
//   {
//           backPatch(orQuad,nextQuad()+2);
//   }
    }    
        | term  {$$=$1; }
    ;

M : {$$=nextQuad();}
N: { $$ = nextQuad(); emit(jump,NULL,NULL,NULL,0,yylineno); }

term: LEFT_PARENTH expr RIGHT_PARENTH {$$=$2;}
      | MINUS expr {
                check_arith($2,yylineno);
                $$ = newExpr(arithexpr_e);
                $$->sym = istempexpr($2) ? $2->sym : newtemp();
                emit(uminus,$2, NULL, $$,nextQuad(),yylineno);
      } 
      | NOT expr  {
        flagLogical=1;
        if($2->type!=boolexpr_e)
        {      
               // convert2Bool($2);
                $2->trueList = makeList(nextQuad());
                $2->falseList = makeList(nextQuad()+1);
                emit(if_eq,$2, newExpr_constBool(1), $$ ,nextQuad(),yylineno);
                emit(jump,NULL,NULL,NULL,nextQuad()+1,yylineno);               
        }
              $$=newExpr(boolexpr_e);
              $$->sym=newtemp();                            
              $$->trueList = $2->falseList;
              $$->falseList = $2->trueList;
      }
      | PLUS_TWO lvalue {
                if($2 != NULL && ($2->sym->type == LIB || $2->sym->type == USERF))
                        {
                                yyerror("Symbol is function");
                        }

                               else{                                        
                                flagSemicolon =1;
                                check_arith($2,yylineno);
                                if ($2->type == tableitem_e) {
                                $$ = emit_ifTableItem($2);
                                emit(add, $$, num_expr(1), $$,nextQuad(),yylineno);
                                emit(tablesetelem, $2, $2->index, $$,nextQuad(),yylineno);
                                }
                                else {
                                emit(add, $2, num_expr(1), $2,nextQuad(),yylineno);
                                $$ = newExpr(arithexpr_e);
                                $$->sym = newtemp();
                                emit(assign, $2, NULL, $$,-1,yylineno);
                                }}
                                                        
                        }
                        

      | lvalue PLUS_TWO  {
               if($1 != NULL && ($1->sym->type == LIB || $1->sym->type == USERF))
                        {
                                yyerror("Symbol is function");
                        }
         else{
                                flagSemicolon =1;
                                // NA KANOYME AYTO
                                 check_arith($1,yylineno);
                                $$ = newExpr(var_e);
                                $$->sym = newtemp();
                                if ($1->type == tableitem_e) {
                                expr* val = emit_ifTableItem($1);
                                emit(assign, val, NULL, $$,-1,yylineno);
                                emit(add, val, num_expr(1), val,nextQuad(),yylineno);
                                emit(tablesetelem, $1, $1->index, val,nextQuad(),yylineno);
                                }
                                else {
                                emit(assign, $1, NULL, $$,-1,yylineno);
                                emit(add, $1, num_expr(1), $1,nextQuad(),yylineno);
                                }
                                
                                }
      }
      
      | lvalue MINUS_TWO {
                       if($1 != NULL && ($1->sym->type == LIB || $1->sym->type == USERF))
                        {
                                yyerror("Symbol is function");
                        }
              else{
                                flagSemicolon =1;
                                check_arith($1,yylineno);
                                $$ = newExpr(var_e);
                                $$->sym = newtemp();
                                if ($1->type == tableitem_e) {
                                expr* val = emit_ifTableItem($1);
                                emit(assign, val, NULL, $$,-1,yylineno);
                                emit(sub, val, num_expr(1), val,nextQuad(),yylineno);
                                emit(tablesetelem, $1, $1->index, val,nextQuad(),yylineno);
                                }
                                else {
                                emit(assign, $1, NULL, $$,-1,yylineno);
                                emit(sub, $1, num_expr(1), $1,nextQuad(),yylineno);
                                }
                                
                                }
        
        }
      | MINUS_TWO lvalue {
         if($2 != NULL && ($2->sym->type == LIB || $2->sym->type == USERF))
                        {
                                yyerror("Symbol is function");
                        }
        else{ 
                                       
                                flagSemicolon =1;
                                check_arith($2,yylineno);
                                if ($2->type == tableitem_e) {
                                $$ = emit_ifTableItem($2);
                                emit(sub, $$, num_expr(1), $$,nextQuad(),yylineno);
                                emit(tablesetelem, $2, $2->index, $$,nextQuad(),yylineno);
                                }
                                else {
                                emit(sub, $2, num_expr(1), $2,nextQuad(),yylineno);
                                $$ = newExpr(arithexpr_e);
                                $$->sym = newtemp();
                                emit(assign, $2, NULL, $$,-1,yylineno);
                                }
                                }
                                                        
                        
      }
      |primary {$$=$1;}
      ;

assignexpr: lvalue {                
                         if($1 != NULL && ($1->sym->type == LIB || $1->sym->type == USERF))
                        {
                                yyerror("Symbol is function");
                        }       
                }
        EQUAL expr   {
        flagSemicolon=1;
        if($4->type==boolexpr_e)
        {    
                backPatch($4->trueList,nextQuad());
                backPatch($4->falseList,nextQuad()+2);
                emit(assign,newExpr_constBool(1),NULL,$4,0,yylineno);
                emit(jump,NULL,NULL,NULL,nextQuad()+2,yylineno);
                emit(assign,newExpr_constBool(0),NULL,$4,0,yylineno);
        }

        if ($1!=NULL && $1->type == tableitem_e){
                emit(
                tablesetelem,$1,$1->index,$4,nextQuad(),yylineno);
                $$ = emit_ifTableItem($1);
                $$->type = assignexpr_e;
        }
        else
        {
                $$=newExpr(assignexpr_e);
                $$->sym=newtemp();
                emit(assign,$4, NULL, $1 ,-1 ,yylineno); //x=2; 
                emit(assign,$1, NULL, $$ ,-1 ,yylineno); //assign olo to assignment sto tmp
        }
       
    }
;


primary: lvalue  {   
        $$=$1;
        //TSEKARE TO
         $$ = emit_ifTableItem($1);
        }
        | call  
        | objectdef {}
        | LEFT_PARENTH funcdef RIGHT_PARENTH  {
                $$ = newExpr(programfunc_e);
                $$->sym = tmpFuncName->sym;
                $$=$2;
        }
        | const  {$$=$1; }
        ;

lvalue: ID  { 
        //if(is_Function(yylval.string_Val,curr_scope)==1){
                sym_t* result;
                result=lookup_X(curr_scope,yylval.string_Val,4,yylineno);   
                if(result==NULL){
                        yyerror("Variable with Function in between");
                }else{
                        $$=lvalue_expr(result);
                }         
        //}  
        }
        | LOCAL ID{
                sym_t* result;
                result=lookup_LocalVar(curr_scope,yylval.string_Val,0,yylineno);
                if(result==NULL){
                        yyerror("Exists as library function");
                }else{
                        $$=lvalue_expr(result);
                }         
        }
        | NAMESPACE_ ID  {
                namespace_flag=1; 
                sym_t* result;
                strcpy(func_name,yylval.string_Val);  
                result= lookup_GlblVar(yylval.string_Val);
                if(result==NULL) {
                        yyerror("global symbol does not exist");
                }else{
                        $$=lvalue_expr(result);
                }
        }
        | member {
                       
                $$=$1; }
        ;

member:  lvalue DOT ID  { 
                 $$ = member_item($1,$3);
                }
        |lvalue LEFT_SQ_BRACKET expr  RIGHT_SQ_BRACKET {
                     
                flagSemicolon=1;
                $1 = emit_ifTableItem($1);
                $$ = newExpr(tableitem_e);
                $$->sym = $1->sym;
                $$->index = $3;

        }  
        |call LEFT_SQ_BRACKET expr RIGHT_SQ_BRACKET {flagSemicolon=1;}
        ;

call: call LEFT_PARENTH elist  RIGHT_PARENTH {flagSemicolon=1; $$=make_call($1,$3,yylineno);}
    |lvalue callsuffix {
                flagSemicolon=1;    
                if(namespace_flag==1){
                        sym_t* result;
                        result=lookup_GlblVar(func_name);
                        if(result==NULL){ yyerror("Not Found");
                        }
                        else{
                                $$=make_call($1,$2->elist,yylineno);}

                }else{
                        sym_t* result;
                        if($2->method==1){
                                result=lookup_X(curr_scope,$2->name,2,yylineno);
                        }else{
                                result=lookup_X(curr_scope,$1->sym->name,2,yylineno);
                        }
                        if(result==NULL) {yyerror("Variable with function in between");}
                        else{
                           $$=emit_ifTableItem($1);  
                           if($2->method==1){
                                   expr *t=$1;
                                   $1=emit_ifTableItem(member_item(t,$2->name));
                                   expr *tmplist;
                                   tmplist=t;
                                   tmplist->next=$2->elist;
                                   $2->elist=tmplist;
                           }else{
                                   $1=lvalue_expr(result);
                           }  
                           $$=make_call($1,$2->elist,yylineno);
                        }
                        ;
                }
            } 
    |LEFT_PARENTH funcdef RIGHT_PARENTH LEFT_PARENTH elist RIGHT_PARENTH {
                flagSemicolon=1;    
            //expr* funcCall = newExpr(programfunc_e);
            //funcCall->sym = $2->sym;
            $$ = make_call(tmpFuncName,$5,yylineno);  //ftiaxto mori tebela plizz
    }
    ;

callsuffix: normcall {$$=$1;}
        |methodcall {$$=$1;}
        ;

normcall: LEFT_PARENTH elist RIGHT_PARENTH {
        $$->elist=$2;
        $$->method=0;
        $$->name=NULL;
}
;

methodcall: DOT_TWO ID LEFT_PARENTH elist RIGHT_PARENTH {
                sym_t* result;
                result=lookup_X(curr_scope,$2,2,yylineno); //sosto?
                if(result==NULL){
                        yyerror("Variable with function in between");
                }else{
                        $$->elist=$4;
                        $$->method=1;
                        $$->name=result->name;
                }
        }
;
 

elist: expr exprs {$$=$1; $$->next=$2; }
        | {$$=NULL;}
        ;

exprs: COMMA expr exprs {$$=$2; $$->next=$3; } 
        | {$$=NULL;}
        ;        

objectdef: LEFT_SQ_BRACKET elist RIGHT_SQ_BRACKET{

        flagSemicolon=1;
        expr* newTableExpr = newExpr(newtable_e);
        newTableExpr->sym = newtemp();
        emit(tablecreate, newTableExpr, NULL, NULL,nextQuad(),yylineno);
        int i=0;
       while($2!=NULL)
       { 
        emit(tablesetelem, newTableExpr, num_expr(i++), $2,nextQuad(),yylineno);
        $2=$2->next;
       }
        $$ = newTableExpr;

 }
        |  LEFT_SQ_BRACKET indexed RIGHT_SQ_BRACKET{

                flagSemicolon=1;
                expr* newTableExpr = newExpr(newtable_e);
                newTableExpr->sym = newtemp();
                emit(tablecreate, newTableExpr, NULL, NULL,nextQuad(),yylineno);
                while($2!=NULL)
                { 

                        emit(tablesetelem, newTableExpr, $2, $2->index,nextQuad(),yylineno);
                        $2=$2->next;
                }

                $$ = newTableExpr;

        }
        ;
// NA TA PROSTHESW AYRIO
indexed: indexedelem indexedelems{$$=$1; $$->next=$2;}
        ;

indexedelems: COMMA indexedelem indexedelems {$$=$2; $$->next=$3;}
        | {$$=NULL;}
        ;

indexedelem: LEFT_BRACKET expr COLON expr RIGHT_BRACKET{ $$=$4; $$->index=$2; }
        ;



block: LEFT_BRACKET {if(scope_flag==0){curr_scope++;} newDummyScope(curr_scope); scope_flag=0;} stmts RIGHT_BRACKET { deactivate(curr_scope); curr_scope--; }
        ;


funcdef: FUNCTION ID{
                flagSemicolon=1;    
                int result;
                result=lookup_FuncDef(curr_scope,yylval.string_Val,1,yylineno);
                if(result==1) {yyerror("Exists as library function");}
                else if(result==2){ yyerror("Variable and function have the same name");}
                else if(result==4) {yyerror("Function Redeclaration");}
                else{
                       // expr *arg1 expr *arg2, expr *result,unsigned int label , unsigned int line
                        $<expr>$=lvalue_expr(put($2,USERF,"FUNC",yylineno,curr_scope)); 
                        $<expr>$->sym->address=nextQuad();                       
                        tmpFuncName =  $<expr>$;
                        functionJump=nextQuad();
                        emit(jump, NULL, NULL, NULL, -1, yylineno);
                        emit(funcstart, $<expr>$ , NULL,NULL,nextQuad() ,yylineno);
                        push(locals,currScopeOffset());
                        enterScopeSpace();
                        resetFormalArgsOffset();
               }
       } LEFT_PARENTH{scope_flag=1; curr_scope++;} idlist RIGHT_PARENTH {function_nested++; enterScopeSpace(); resetFuncLocalsOffset();} block { function_nested--;
                        $<expr>$=tmpFuncName;
                        $<expr>$->sym->totallocals=currScopeOffset();
                        exitScopeSpace();
                        exitScopeSpace();
                        restoreCurrScopeOffset(pop(locals));
                        patchList(pop(returnst),nextQuad());
                        emit(funcend,tmpFuncName, NULL, NULL , nextQuad() ,yylineno);
                        printf("next Quad function %d\n",nextQuad());
                        patchList(functionJump, nextQuad());
                }
        |FUNCTION{       
                flagSemicolon=1;    
                snprintf(buf, 50, "_f%d", buf_counter);  
                $<expr>$=lvalue_expr(put(buf,USERF,"FUNC",yylineno,curr_scope)); 
                $<expr>$->sym->address=nextQuad();                       
                tmpFuncName =  $<expr>$;
                functionJump=nextQuad();
                emit(jump, NULL, NULL, NULL, -1, yylineno);
                emit(funcstart, $<expr>$, NULL,NULL ,nextQuad() ,yylineno);
                push(locals,currScopeOffset());
                enterScopeSpace();
                resetFormalArgsOffset();
                buf_counter++;
        } LEFT_PARENTH {scope_flag=1; curr_scope++;} idlist RIGHT_PARENTH {function_nested++; enterScopeSpace(); resetFuncLocalsOffset();}  block {
                        function_nested--;
                        $<expr>$=tmpFuncName;
                        $<expr>$->sym->totallocals=currScopeOffset();
                        exitScopeSpace();
                        exitScopeSpace();
                        restoreCurrScopeOffset(pop(locals));
                        patchList(pop(returnst),nextQuad());
                        emit(funcend,tmpFuncName, NULL, NULL , nextQuad() ,yylineno);
                        patchList(functionJump, nextQuad());
                        }
        ;


const: NUM {$$=num_expr(yylval.int_val);  }	
       |STRING {  $$=newExpr_constString(yylval.string_Val);}	
       |NIL  {$$=newExpr(nil_e);}	
       |TRUE {
        $$=newExpr_constBool(1);
        // $$->trueList = makeList(nextQuad());
        // $$->falseList = makeList(nextQuad()+1);

       }	
       |FALSE {
        $$=newExpr_constBool(0);
        // $$->trueList = makeList(nextQuad());
        // $$->falseList = makeList(nextQuad()+1);
        }	
       |FLOAT {$$=num_expr(yylval.real_val);}	
       ;

idlist: ID{int result= lookup_Formal(curr_scope, yylval.string_Val,5,yylineno);
                if(result==1){
                yyerror("ID exists as library function");
                }else if(result==2){
                yyerror("Formal redeclaration");
                }
        }
        |idlist COMMA ID {int result= lookup_Formal(curr_scope, yylval.string_Val,5,yylineno);
                if(result==1){
                yyerror("ID exists as library function");
                }else if(result==2){
                yyerror("Formal redeclaration");
                }
        }
        | {}
        ;

ifprefix:IF LEFT_PARENTH expr RIGHT_PARENTH{
        flagSemicolon=1;
 if($3->type==boolexpr_e)
        {    
        backPatch($3->trueList,nextQuad());
        backPatch($3->falseList,nextQuad()+2);
        emit(assign,newExpr_constBool(1),NULL,$3,0,yylineno);
        emit(jump,NULL,NULL,NULL,nextQuad()+2,yylineno);
        emit(assign,newExpr_constBool(0),NULL,$3,0,yylineno);
        }
        emit(
        if_eq, $3,
        newExpr_constBool(1),
        NULL, nextQuad() + 2, yylineno
        );
        $$ = nextQuad();
        emit(jump, NULL, NULL, NULL, 0, yylineno);

}

elseprefix: ELSE {
        $$=nextQuad();
        emit(jump, NULL, NULL, NULL, 0, yylineno);

}

ifstmt: ifprefix stmt  { patchLabel($1,nextQuad()); }
	|ifprefix stmt elseprefix stmt  {
                patchLabel($1,$3+1);
                patchLabel($3,nextQuad());
        }
	;


whilestart:WHILE { $$=nextQuad(); while_flag++; };


whilecond: LEFT_PARENTH expr RIGHT_PARENTH{
        if($2->type==boolexpr_e)
        {    
                backPatch($2->trueList,nextQuad());
                backPatch($2->falseList,nextQuad()+2);
                emit(assign,newExpr_constBool(1),NULL,$2,0,yylineno);
                emit(jump,NULL,NULL,NULL,nextQuad()+2,yylineno);
                emit(assign,newExpr_constBool(0),NULL,$2,0,yylineno);
        }
        emit(if_eq, $2, newExpr_constBool(1), NULL, nextQuad()+2, yylineno);
        $$=nextQuad();
        emit(jump,NULL,NULL,NULL,0, yylineno);
}
;


while: whilestart whilecond stmt{
        emit(jump,NULL,NULL,NULL,$1, yylineno);
        patchLabel($2, nextQuad());
        patchList(pop(breakst), nextQuad());
        patchList(pop(contst), $1);  
        while_flag--;

}
;



forprefix: FOR{for_flag++;} LEFT_PARENTH elist SEMICOLON  {namespace_flag=0;} M expr SEMICOLON {namespace_flag=0;} {
        if($8->type==boolexpr_e)
        {    
                backPatch($8->trueList,nextQuad());
                backPatch($8->falseList,nextQuad()+2);
                emit(assign,newExpr_constBool(1),NULL,$8,0,yylineno);
                emit(jump,NULL,NULL,NULL,nextQuad()+2,yylineno);
                emit(assign,newExpr_constBool(0),NULL,$8,0,yylineno);
        }
        $$ = malloc(sizeof(for_p));
        $$->test=$7;
        $$->enter=nextQuad();
        emit(if_eq, $8, newExpr_constBool(1),NULL,0,yylineno);
}

for: forprefix N elist RIGHT_PARENTH N stmt N{
        patchLabel($1->enter, $5+1); 
        patchLabel($2, nextQuad()); 
        patchLabel($5, $1->test); 
        patchLabel($7, $2+1);

       patchList(pop(breakst), nextQuad());
       patchList(pop(contst), $2+1);
        for_flag--;
}



//forstmt: FOR{for_flag++;} LEFT_PARENTH elist SEMICOLON {namespace_flag=0;} expr SEMICOLON {namespace_flag=0;}  elist RIGHT_PARENTH stmt {for_flag--;}

returnstmt: RETURN expr SEMICOLON {if(function_nested==0){yyerror("Return out of function");}
              else{ emit(ret,NULL,NULL,$2 ,nextQuad() ,yylineno);}
                printf("EIMAI RETURN STMT ME RESULT TYPE %d\n\n",$2->type);
              }
            |RETURN SEMICOLON {if(function_nested==0){yyerror("Return out of function");}
              else{emit(ret,NULL,NULL, NULL ,nextQuad() ,yylineno);}}
            ;

%%


int yyerror(char* yaccProvideMessage){
    fprintf(stderr, "\x1B[31m" "ERROR, %s at line: %d\n" "\x1B[0m",yaccProvideMessage, yylineno);
}

int main(int argc,char** argv){
    init();
    FILE *f=fopen("output.txt","w");
    locals=newStack(NEW_SIZE);
    formals=newStack(NEW_SIZE);
    breakst=newStack(NEW_SIZE);
    contst=newStack(NEW_SIZE);
    returnst=newStack(NEW_SIZE);
    yyin = stdin; 
    yyparse();
    /*print_output();*/
   // print_quads(f);
    generate_mapping();
    writeBinary();
  
    FILE *b=fopen("binFile.abc","rb");
    readAll(b);
    avm_initialize();
    while(executionFinished==0){
        execute_cycle();
    }

    fclose(f);
    fclose(b);

}
