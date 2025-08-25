#define CURR_SIZE_INSTR (totalInstr*sizeof(instruction)) 
#define NEW_SIZE_INSTR (EXPAND_SIZE*sizeof(instruction) + CURR_SIZE_INSTR)

#define CURR_SIZE_STR (totalStringConsts*sizeof(char *)) 
#define NEW_SIZE_STR (EXPAND_SIZE*sizeof(char *) + CURR_SIZE_STR)

#define CURR_SIZE_CONST (totalNumConsts*sizeof(double *)) 
#define NEW_SIZE_CONST (EXPAND_SIZE*sizeof(double *) + CURR_SIZE_CONST)

#define CURR_SIZE_LIBS (totalnamedLibfuncs*sizeof(char *)) 
#define NEW_SIZE_LIBS (EXPAND_SIZE*sizeof(char *) + CURR_SIZE_LIBS)

#define CURR_SIZE_USER_FUNCS (totalUserFuncs*sizeof(userfunc*)) 
#define NEW_SIZE_USER_FUNCS (EXPAND_SIZE*sizeof(userfunc*) + CURR_SIZE_USER_FUNCS)

int currInstr=0;
int totalInstr=0;
typedef void (*generator_func_t)(quad*);

typedef enum vmopcode {
    assign_v,
    add_v,
    sub_v,
    mul_v,
    div_v,
    mod_v,
    uminus_v,
    and_v,
    or_v,
    not_v,
    jeq_v,
    jne_v,
    jle_v,
    jge_v,
    jlt_v,
    jgt_v,
    call_v,
    pusharg_v,
    funcenter_v,
    funcexit_v,
    newtable_v,
    tablegetelem_v,
    tablesetelem_v,
    nop_v,
    jump_v
} vmopcode;

typedef enum vmarg_t {
    label_a = 0,
    global_a = 1,
    formal_a = 2,
    local_a = 3,
    number_a = 4,
    string_a = 5,
    bool_a = 6,
    nil_a = 7,
    userfunc_a = 8,
    libfunc_a = 9,
    retval_a = 10
} vmarg_t;

typedef struct vmarg {
    vmarg_t type;
    unsigned val;
  //  unsigned* jumpaddr;
} vmarg;

typedef struct instruction {
    vmopcode opcode;
    vmarg result;
    vmarg arg1;
    vmarg arg2;
    unsigned srcLine;
} instruction;

instruction* instructions = (instruction*)0;

typedef struct userfunc {
    unsigned address;
    unsigned localSize;
    unsigned saved_index;
    char* id;
} userfunc;

double* numConsts;
unsigned totalNumConsts = 0;
unsigned currNumConsts = 0;

char** stringConsts;
unsigned totalStringConsts = 0;
unsigned currStringConsts = 0;

char** namedLibfuncs;
unsigned totalnamedLibfuncs = 0;
unsigned currnamedLibfuncs = 0;

userfunc* userFuncs;
unsigned totalUserFuncs = 0;
unsigned currUserFuncs = 0;

typedef struct FuncStack{
    int size;    
    int top;
    sym_t** elems;
}funcStack;

typedef enum avm_memcell_t {
    number_m = 0,
    string_m = 1,
    bool_m = 2,
    table_m = 3,
    userfunc_m = 4,
    libfunc_m = 5,
    nil_m = 6,
    undef_m = 7
} avm_memcell_t;


typedef struct avm_memcell {
    avm_memcell_t type;
    union {
        double numVal;
        char* strVal;
        unsigned char boolVal;
        struct avm_table* tableVal;
        unsigned funcVal;
        char* libfuncVal;
    } data;
} avm_memcell;



void reset_operand(vmarg* arg){
        arg = (vmarg*)0;
}

int nextinstructionlabel(){
    return currInstr;
}

/*STRINGS*/
void expandStr(){
    assert(totalStringConsts==currStringConsts);
    char** t = (char**)malloc(NEW_SIZE_STR);
    if(stringConsts){
        memcpy(t,stringConsts,CURR_SIZE_INSTR);
        free(stringConsts);
    }
    stringConsts=t;
    totalStringConsts +=EXPAND_SIZE;
}

unsigned consts_newstring(char* s){
    if(totalStringConsts==currStringConsts)
    {
        expandStr();
    }
    char ** t = stringConsts + currStringConsts++;
    *t = s;
    return currStringConsts-1;
}
/*CONSTS*/
void expandConst(){
    assert(totalNumConsts==currNumConsts);
    double* t = (double*)malloc(NEW_SIZE_CONST);
    if(numConsts){
        memcpy(t,numConsts,CURR_SIZE_CONST);
        free(numConsts);
    }
    numConsts=t;
    totalNumConsts +=EXPAND_SIZE;
}

unsigned consts_newnumber(double n){
    if(totalNumConsts==currNumConsts)
    {
        expandConst();
    }
     double*  t = numConsts + currNumConsts++;
    *t = n;
    return currNumConsts-1;
}

/*LIBS*/
void expandLibs(){
    assert(totalnamedLibfuncs==currnamedLibfuncs);
   char** t = (char** )malloc(NEW_SIZE_LIBS);
    if(namedLibfuncs){
        memcpy(t,namedLibfuncs,CURR_SIZE_LIBS);
        free(namedLibfuncs);
    }
    namedLibfuncs=t;
    totalnamedLibfuncs +=EXPAND_SIZE;
}
unsigned libfuncs_newused(const char* s){
    if(totalnamedLibfuncs==currnamedLibfuncs)
    {
        expandLibs();
    }
     char**  t = namedLibfuncs + currnamedLibfuncs++;
    *t = s;
    return currnamedLibfuncs-1;
}

/*USERFUNC*/
void expandUserFunc(){
    assert(totalUserFuncs==currUserFuncs);
    userfunc* t = (userfunc* )malloc(NEW_SIZE_USER_FUNCS);
    if(userFuncs){
        memcpy(t,userFuncs,CURR_SIZE_USER_FUNCS);
        free(userFuncs);
    }
    userFuncs=t;
    totalUserFuncs +=EXPAND_SIZE;
}
unsigned userfuncs_newfunc(sym_t* sym){
    if(totalUserFuncs==currUserFuncs)
    {
        expandUserFunc();
    }
    userfunc* t = userFuncs + currUserFuncs++;

	t->address = sym->address;
	t->localSize = sym->totallocals;
	t->saved_index  = currUserFuncs-1;
	t->id =	(char*)strdup(sym->name);

    return currUserFuncs-1;
}

/*INSTRUCTIONS*/
void expandInstr(){
    assert(totalInstr==currInstr);
    instruction* t = (instruction*)malloc(NEW_SIZE_INSTR);
    if(instructions){
        memcpy(t,instructions,CURR_SIZE_INSTR);
        free(instructions);
    }
    instructions=t;
    totalInstr +=EXPAND_SIZE;
}

void emitInstr(instruction *inst){
    /*allocate memory for new quad*/
    if(currInstr==totalInstr) expandInstr();
    instruction *t = instructions + currInstr++;
    t->opcode=inst->opcode;
    t->arg1=inst->arg1;
    t->arg2=inst->arg2;
    t->result=inst->result;
    t->srcLine=inst->srcLine; 
}


/*GENERATE*/
void generate(vmopcode op,quad* quadd) {
 

    instruction* t = (instruction*)malloc(sizeof(instruction));;
    t->opcode = op;
    t->srcLine=quadd->line;
    make_operand(quadd->arg1, &(t->arg1));
    make_operand(quadd->arg2, &(t->arg2));
    make_operand(quadd->result, &(t->result));
    quadd->taddress = nextinstructionlabel();
  
    emitInstr(t);
}

void generate_ADD (quad* quadd) { generate(add_v, quadd); }
void generate_SUB (quad* quadd) { generate(sub_v, quadd); }
void generate_MUL (quad* quadd) { generate(mul_v, quadd); }
void generate_DIV (quad* quadd) { generate(div_v, quadd); }
void generate_MOD (quad* quadd) { generate(mod_v, quadd); }
void generate_NEWTABLE   (quad* quadd) { generate(newtable_v, quadd); }
void generate_TABLEGETELEM (quad* quadd) { generate(tablegetelem_v, quadd); }
void generate_TABLESETELEM (quad* quadd) { generate(tablegetelem_v, quadd); }
void generate_ASSIGN (quad* quadd) { generate(assign_v, quadd); }
void generate_NOP () { instruction* t = (instruction*)malloc(sizeof(instruction)); t->opcode=nop_v; emitInstr(t);}

void generate_relational (vmopcode op,quad* quadd) {
    instruction* t = (instruction*)malloc(sizeof(instruction));
    t->opcode = op;
    make_operand(quadd->arg1, &(t->arg1));
    make_operand(quadd->arg2, &(t->arg2));
    t->result.type = label_a;
    if(quadd->label < nextQuad()){
       //  printf("quad->label : %u\n",quadd->label);
        // printf("quad->taddress : %u\n",quadd->taddress);
      //  printf("taddress : %u\n",quads[quadd->label].taddress);
        // printf("result NumConst : %u\n",quads[quadd->label].result->numConst);
        // printf("Line : %u\n",quads[quadd->label].line);
        // printf("Label: %u\n",quads[quadd->label].label);
        //quads[quadd->label].taddress=8;
     //   t->result.jumpaddr = &(quads[quadd->label].taddress);
      //  printf("jump addr : %u\n",&(quads[quadd->label].taddress));
       t->result.val = quadd->label;
    }else{
        add_incomplete_jump(nextinstructionlabel(), quadd->label);
    }
    quadd->taddress = nextinstructionlabel();
    emitInstr(t);
} 

void generate_JUMP (quad* quadd) { generate_relational(jump_v, quadd); }
void generate_IF_EQ (quad* quadd) { generate_relational(jeq_v, quadd); }
void generate_IF_NOTEQ(quad* quadd) { generate_relational(jne_v, quadd); }
void generate_IF_GREATER (quad* quadd) { generate_relational(jgt_v, quadd); }
void generate_IF_GREATEREQ(quad* quadd) { generate_relational(jge_v, quadd); }
void generate_IF_LESS (quad* quadd) { generate_relational(jlt_v, quadd); }
void generate_IF_LESSEQ (quad* quadd) { generate_relational(jle_v, quadd); }

void generate_NOT (quad* quadd) {
    quadd->taddress = nextinstructionlabel();
    instruction* t = (instruction*)malloc(sizeof(instruction));
    t->opcode = jeq_v;
    make_operand(quadd->arg1, &(t->arg1));
    make_booloperand(&(t->arg2), 0);
    t->result.type = label_a;
    t->result.val = nextinstructionlabel()+3;
    emitInstr(t);
    t->opcode = assign_v;
    make_booloperand(&(t->arg1), 0);
    reset_operand(&(t->arg2));
    make_operand(quadd->result, &(t->result));
    emitInstr(t); 
    t->opcode = jump_v;
    reset_operand (&(t->arg1));
    reset_operand(&(t->arg2));
    t->result.type = label_a;
    t->result.val = nextinstructionlabel()+2;
    emitInstr(t);
    t->opcode = assign_v;
    make_booloperand(&(t->arg1), 1);
    reset_operand(&(t->arg2));
    make_operand(quadd->result, &(t->result));
    emitInstr(t);
}

void generate_OR (quad* quadd) {
    quadd->taddress = nextinstructionlabel();
    instruction* t = (instruction*)malloc(sizeof(instruction));
    t->opcode = jeq_v;
    make_operand(quadd->arg1, &(t->arg1));
    make_booloperand(&(t->arg2), 1);
    t->result.type = label_a;
    t->result.val = nextinstructionlabel()+4;
    emitInstr(t);
    make_operand(quadd->arg2, &(t->arg1));
    t->result.val = nextinstructionlabel()+3;
    emitInstr(t); 
    t->opcode = assign_v;
    make_booloperand(&(t->arg1), 0);
    reset_operand(&(t->arg2));
    make_operand(quadd->result, &(t->result));
    emitInstr(t);
    t->opcode = jump_v;
    reset_operand (&(t->arg1));
    reset_operand(&(t->arg2));
    t->result.type = label_a;
    t->result.val = nextinstructionlabel()+2;
    emitInstr(t);
    t->opcode = assign_v;
    make_booloperand(&(t->arg1), 1);
    reset_operand(&(t->arg2));
    make_operand(quadd->result, &(t->result));
    emitInstr(t);
} 

void generate_AND (quad* quadd) {
    quadd->taddress = nextinstructionlabel();
    instruction* t = (instruction*)malloc(sizeof(instruction));
    t->opcode = jeq_v;
    make_operand(quadd->arg1, &(t->arg1));
    make_booloperand(&(t->arg2), 0);
    t->result.type = label_a;
    t->result.val = nextinstructionlabel()+4;
    emitInstr(t);
    make_operand(quadd->arg2, &(t->arg1));
    t->result.val = nextinstructionlabel()+3;
    emitInstr(t); 
    t->opcode = assign_v;
    make_booloperand(&(t->arg1), 1);
    reset_operand(&(t->arg2));
    make_operand(quadd->result, &(t->result));
    emitInstr(t);
    t->opcode = jump_v;
    reset_operand (&(t->arg1));
    reset_operand(&(t->arg2));
    t->result.type = label_a;
    t->result.val = nextinstructionlabel()+2;
    emitInstr(t);
    t->opcode = assign_v;
    make_booloperand(&(t->arg1), 0);
    reset_operand(&(t->arg2));
    make_operand(quadd->result, &(t->result));
    emitInstr(t);
} 

void generate_PARAM(quad *quadd) {
    quadd->taddress = nextinstructionlabel();
    instruction* t = (instruction*)malloc(sizeof(instruction));
    t->opcode = pusharg_v;
    make_operand(quadd->result, &(t->result));
    emitInstr(t);
}
void generate_CALL(quad *quadd) {
    quadd->taddress = nextinstructionlabel();
    instruction* t = (instruction*)malloc(sizeof(instruction));
    t->opcode = call_v;
   // t->result = (vmarg*)malloc(sizeof(vmarg));
    make_operand(quadd->result, &(t->result));
    emitInstr(t);
}
void generate_GETRETVAL(quad *quadd) {
    quadd->taddress = nextinstructionlabel();
    instruction* t = (instruction*)malloc(sizeof(instruction));
    t->opcode = assign_v;
    make_operand(quadd->result, &t->result);
    printf("1 getretval make operand me result type %u\n",quadd->result->type);
    printf("1 getretval make operand me INSTRUCTION result type %u\n",t->result.type);


    make_retvaloperand(&(t->arg1));
    printf("2 makeRETVAL OPERAND  se arg1 retval_a\n");

    emitInstr(t);
} 

void generate_FUNCSTART(quad* quadd) {
    sym_t* f;
    f = quadd->arg1->sym;
    f->address = nextinstructionlabel();
    quadd->taddress = nextinstructionlabel();
    
    instruction* t = (instruction*)malloc(sizeof(instruction));
    t->opcode = funcenter_v;
    make_operand(quadd->arg1, &(t->result));
    emitInstr(t);
}
void generate_RETURN(quad* quadd) {
    quadd->taddress = nextinstructionlabel();
    instruction* t = (instruction*)malloc(sizeof(instruction));
    t->opcode = assign_v;
    make_retvaloperand(&(t->arg1));
    make_operand(quadd->result, &(t->result));
    emitInstr(t);
}
void generate_FUNCEND(quad* q) {
   

    q->taddress = nextinstructionlabel();
    instruction* t = (instruction*)malloc(sizeof(instruction));
    t->opcode = funcexit_v;
    make_operand(q->arg1, &(t->result));
    emitInstr(t);
    
}
void generate_UMINUS(quad* q) {
    generate(mul_v,q);
}

generator_func_t generators[] = {
    generate_ASSIGN,
    generate_ADD,
    generate_SUB,
    generate_MUL,
    generate_DIV,
    generate_MOD,
    generate_UMINUS,
    generate_AND,
    generate_OR,
    generate_NOT,
    generate_IF_EQ,
    generate_IF_NOTEQ,
    generate_IF_LESSEQ,
    generate_IF_GREATEREQ,
    generate_IF_LESS,
    generate_IF_GREATER,
    generate_CALL,
    generate_PARAM,
    generate_RETURN,
    generate_GETRETVAL,
    generate_FUNCSTART,
    generate_FUNCEND,
    generate_NEWTABLE,
    generate_JUMP,
    generate_TABLEGETELEM,
    generate_TABLESETELEM,
    generate_NOP
};

void generate_mapping(void) {
    unsigned i;
    for (i = 0; i < nextQuad(); ++i) {
        (*generators[quads[i].op])(quads+i);
    }
}

/*INCOMPLETE JUMPS*/
typedef struct incomplete_jump {
    unsigned instrNo; // the jump instruction number
    unsigned iaddress;  // the i-code jump-target address
    struct incomplete_jump* next;
} incomplete_jump;

incomplete_jump* ij_head = (incomplete_jump*) 0;
unsigned ij_total = 0;

void add_incomplete_jump(unsigned instrNo, unsigned iaddress){
    incomplete_jump* incomplete_j = (incomplete_jump*)malloc(sizeof(incomplete_jump));
    incomplete_j->instrNo = instrNo;
    incomplete_j->iaddress = iaddress;
    incomplete_j->next = ij_head;
    ij_head = incomplete_j;
    ij_total++;
}
/*TSEKARE TO*/
void patch_incomplete_jumps() {
    incomplete_jump* tmpHead = (incomplete_jump*)malloc(sizeof(incomplete_jump));
    tmpHead = ij_head;

    while(tmpHead!= NULL)
    {
        if(tmpHead->iaddress == nextQuad())
        {
            instructions[tmpHead->instrNo].result.val = nextinstructionlabel();
        }else
        {
            instructions[tmpHead->instrNo].result.val = quads[tmpHead->iaddress].taddress;
        }
    }
} 


void make_operand(expr* e, vmarg* arg){ //input , output
    if(e){
        switch(e->type){
            case var_e:{
                assert(e->sym);
                arg->val=e->sym->offset;
                switch(e->sym->space){
                    case programvar: 	arg->type = global_a; 	break;
                    case functionlocal: 	arg->type = local_a; 	break;
                    case formalarg:		arg->type = formal_a;	break;
                    default: assert(0);
                }
            }
            case tableitem_e:{
                assert(e->sym);
                arg->val=e->sym->offset;
                switch(e->sym->space){
                    case programvar: 	arg->type = global_a; 	break;
                    case functionlocal: 	arg->type = local_a; 	break;
                    case formalarg:		arg->type = formal_a;	break;
                    default: assert(0);
                }
            }
            case arithexpr_e:{
                assert(e->sym);
                arg->val=e->sym->offset;
                switch(e->sym->space){
                    case programvar: 	arg->type = global_a; 	break;
                    case functionlocal: 	arg->type = local_a; 	break;
                    case formalarg:		arg->type = formal_a;	break;
                    default: assert(0);
                }
            }
            case boolexpr_e:
            case assignexpr_e:{
                assert(e->sym);
                arg->val=e->sym->offset;
                switch(e->sym->space){
                    case programvar: 	arg->type = global_a; 	break;
                    case functionlocal: 	arg->type = local_a; 	break;
                    case formalarg:		arg->type = formal_a;	break;
                    default: assert(0);
                }
            }
            case newtable_e: {
                assert(e->sym);
                arg->val = e->sym->offset;
                switch(e->sym->space){
                    case programvar: 	arg->type = global_a; 	break;
                    case functionlocal: 	arg->type = local_a; 	break;
                    case formalarg:		arg->type = formal_a;	break;
                    default: assert(0);
                }
                break; 
            }

            /* Constants */
            case constbool_e:{
                arg->val = e->boolConst;
                arg->type = bool_a;
                break;
            }
            case conststring_e:{
                arg->val = consts_newstring(e->strConst);
                arg->type = string_a;
                break;
            }
            case constnum_e:{
                arg->val = consts_newnumber(e->numConst);
                arg->type = number_a;
                break;
            }
            case nil_e: arg->type = nil_a; break;

            case programfunc_e:{
                arg->type = userfunc_a;
                arg->val = userfuncs_newfunc(e->sym);
                break;
            }
            case libraryfunc_e:{
                arg->type = libfunc_a;
                arg->val = libfuncs_newused(e->sym->name);
                break;
            }
            default: assert(0);
        }
    }
}

void *make_numberoperand(vmarg* arg, double val){
   arg->val = consts_newnumber(val);
   arg->type = number_a;
}

void make_booloperand(vmarg* arg, unsigned val){
	arg->val = val;
	arg->type = bool_a;
}

void make_retvaloperand(vmarg* arg){
    arg->type = retval_a;
}

void writeBinary(){
    int i=0;
    unsigned int magicNumber = 340200501;
    unsigned stringSize,nameSize;
    FILE *f;
    f = fopen("binFile.abc","wb");  
    fwrite(&magicNumber,sizeof(unsigned int),1,f);
    fwrite(&currStringConsts,sizeof(unsigned),1,f);
    for(i=0;i<currStringConsts;i++){
        stringSize = strlen(stringConsts[i]);
        fwrite(&(stringSize),sizeof(unsigned),1,f);
        fwrite(&(stringConsts[i]),sizeof(char*),1,f);
    }
    fwrite(&currNumConsts,sizeof(unsigned),1,f);
    for(i=0;i<currNumConsts;i++){
        fwrite(&(numConsts[i]),sizeof(double*),1,f);
    }
    fwrite(&currUserFuncs,sizeof(unsigned),1,f);
    for(i=0;i<currUserFuncs;i++){
        fwrite(&(userFuncs[i].address),sizeof(unsigned),1,f);
        fwrite(&(userFuncs[i].localSize),sizeof(unsigned),1,f);
        fwrite(&(userFuncs[i].id),sizeof(char*),1,f);
    }
    fwrite(&currnamedLibfuncs,sizeof(unsigned),1,f);
    for(i=0;i<currnamedLibfuncs;i++){
        nameSize = strlen(namedLibfuncs[i]);
        fwrite(&(nameSize),sizeof(unsigned),1,f);
        fwrite(&(namedLibfuncs[i]),sizeof(char*),1,f);
    }
    fwrite(&currInstr,sizeof(unsigned),1,f);
    for(i=0;i<currInstr;i++){
        fwrite(&(instructions[i].opcode),sizeof(unsigned),1,f);
        fwrite(&(instructions[i].result.type),sizeof(int),1,f);
        fwrite(&(instructions[i].result.val),sizeof(unsigned),1,f);
        fwrite(&(instructions[i].arg1.type),sizeof(int),1,f);
        fwrite(&(instructions[i].arg1.val),sizeof(unsigned),1,f);
        fwrite(&(instructions[i].arg2.type),sizeof(int),1,f);
        fwrite(&(instructions[i].arg2.val),sizeof(unsigned),1,f);
        fwrite(&(instructions[i].srcLine),sizeof(unsigned),1,f);
    }
    fwrite(&globalVariables,sizeof(unsigned),1,f);
    fclose(f);

// !!!!!!!!!!!!!!!  na to svhsoume meta !!!!!!!!!!!!


    FILE *b;
    b = fopen("binReadable.txt","w");
    fprintf(b, "%u\n", magicNumber);
    fprintf(b, "%u\n", currStringConsts);
    for(i=0;i<currStringConsts;i++){
        fprintf(b, "%u %s\n", strlen(stringConsts[i]), stringConsts[i]);
    }
    fprintf(b, "%u\n", currNumConsts);
    for(i=0;i<currNumConsts;i++){
        fprintf(b, "%f \n", numConsts[i]);
    }
    fprintf(b, "%u\n", currUserFuncs);
    for(i=0;i<currUserFuncs;i++){
        fprintf(b, "%u %u %s \n", userFuncs[i].address, userFuncs[i].localSize, userFuncs[i].id);
    }
    for(i=0;i<currnamedLibfuncs;i++){
        fprintf(b, "%s \n", namedLibfuncs[i]);
    }
    // target code
    fprintf(b, "%u\n", currInstr);
    for(i=0;i<currInstr;i++){
        fprintf(b, "%u %u %u %u\n", instructions[i].opcode, instructions[i].result, instructions[i].arg1, instructions[i].arg2);
    }
    fclose(b);
}