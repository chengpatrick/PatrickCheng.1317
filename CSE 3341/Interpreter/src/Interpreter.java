import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.HashMap;
import java.util.Scanner;

public class Interpreter {

    private static Tokenizer tokenizer = null;

    public static void main(String args[]) {

        Scanner myIn = new Scanner(System.in); // Create a Scanner object

        //read in file
        try {
            System.out.print(
                    "Parser:Enter file to read (Example:data/test1.txt): ");
            String userInput = myIn.nextLine();
            File file = new File(userInput);
            Scanner readFile = new Scanner(file);
            tokenizer = new Tokenizer(readFile);
            readFile.close();

            Prog program = new Prog();

            try {
                program.ParseProg();
            } catch (IOException e) {
                e.printStackTrace();
                System.out.println("Invalid Token Structure");
            }

            program.PrintProg();
            program.ExecProg();

        } catch (FileNotFoundException error) {
            System.out.println("An error occurred.");
            error.printStackTrace();
        }
    }

}

/* class for prog node */
class Prog {
    private Decl_Seq ds;
    private Stmt_Seq ss;
    Printer out;

    public Prog() {
        this.ds = null;
        this.ss = null;
    }

    void ParseProg() throws IOException {
        Tokenizer.skipToken(); //skip program
        this.ds = new Decl_Seq();
        this.ds.ParseDeclSeq();
        Tokenizer.skipToken(); // begin
        this.ss = new Stmt_Seq();
        this.ss.ParseStmtSeq();
    }

    void ExecProg() {
        this.ds.ExecDeclSeq();
        this.ss.ExecStmtSeq();
    }

    void PrintProg() {
        //System.out.println("program");
        //Printer.indentUp();
        //this.out.indent();
        this.ds.PrintDeclSeq();
        //System.out.println("begin");
        this.ss.PrintStmtSeq();
        //this.out.indentDown();
        //System.out.println("end");
    }

}

/* class for decl node */
class Decl {
    private ID_List list;

    public Decl() {
        this.list = null;
    }

    void ParseDecl() {
        if (Tokenizer.idName().equals("int")) {
            Tokenizer.skipToken();
        }
        this.list = new ID_List();
        this.list.ParseIdList();
    }

    void ExecDecl() {
        this.list.ExecIDList();
    }

    void PrintDecl() {
        System.out.print("int ");
        this.list.PrintIDList();
        System.out.println();
    }
}

/* class for decl_seq node */
class Decl_Seq {
    private Decl d;
    private Decl_Seq ds;
    private int altno;

    public Decl_Seq() {
        this.d = null;
        this.ds = null;
    }

    void ParseDeclSeq() {
        this.d = new Decl();
        this.d.ParseDecl();
        Tokenizer.skipToken();
        if (!Tokenizer.idName().equals("begin")) {
            this.ds = new Decl_Seq();
            this.ds.ParseDeclSeq();
            this.altno = 1;
        }
    }

    void ExecDeclSeq() {
        this.d.ExecDecl();
        if (this.altno == 1) {
            this.ds.ExecDeclSeq();
        }
    }

    void PrintDeclSeq() {
        this.d.PrintDecl();
        if (this.ds != null) {
            this.ds.PrintDeclSeq();
        }
    }
}

/* class for stmt node */
class Stmt {
    /*
     * 1 assign 2 if 3 loop 4 input 5 output
     */
    private Assign as;
    private If i;
    private Loop loop;
    private In in;
    private Out out;
    private int altno;

    public Stmt() {
        this.as = null;
        this.i = null;
        this.loop = null;
        this.in = null;
        this.out = null;
        this.altno = 0;
    }

    void ParseStmt() {
        int token_num = Tokenizer.getToken();
        if (token_num == 32) {
            this.as = new Assign();
            this.as.ParseAssign();
            this.altno = 1;
        } else if (token_num == 5) {
            this.i = new If();
            this.i.ParseIf();
            this.altno = 2;
        } else if (token_num == 8) {
            this.loop = new Loop();
            this.loop.ParseLoop();
            this.altno = 3;
        } else if (token_num == 10) {
            this.in = new In();
            this.in.ParseIn();
            this.altno = 4;
        } else if (token_num == 11) {
            this.out = new Out();
            this.out.ParseOut();
            this.altno = 5;
        }
    }

    void ExecStmt() {
        //System.out.println(this.altno);
        if (this.altno == 1) {
            this.as.ExecAssign();
        }
        if (this.altno == 2) {
            this.i.ExecIf();
        }
        if (this.altno == 3) {
            this.loop.ExecLoop();
        }
        if (this.altno == 4) {
            this.in.ExecIn();
        }
        if (this.altno == 5) {
            this.out.ExecOut();
        }
    }

    void PrintStmt() {
        //System.out.println(this.altno);
        if (this.altno == 1) {
            this.as.PrintAssign();
        }
        if (this.altno == 2) {
            this.i.PrintIf();
        }
        if (this.altno == 3) {
            this.loop.PrintLoop();
        }
        if (this.altno == 4) {
            this.in.PrintInput();
        }
        if (this.altno == 5) {
            this.out.PrintOutput();
        }
    }

}

/* class for stmt_seq node */
class Stmt_Seq {
    private Stmt st;
    private Stmt_Seq sq;

    public Stmt_Seq() {
        this.st = null;
        this.sq = null;
    }

    void ParseStmtSeq() {
        this.st = new Stmt();
        this.st.ParseStmt();
        String token = Tokenizer.idName();
        if (!token.equals("end") && !token.equals("else")) {
            this.sq = new Stmt_Seq();
            this.sq.ParseStmtSeq();
        }
    }

    void ExecStmtSeq() {
        this.st.ExecStmt();
        if (this.sq != null) {
            this.sq.ExecStmtSeq();
        }
    }

    void PrintStmtSeq() {
        Printer.indent();
        this.st.PrintStmt();
        if (this.sq != null) {
            this.sq.PrintStmtSeq();
        }
    }
}

/* class for id_list node */
class ID_List {
    public ID id;
    private ID_List list;

    public ID_List() {
        this.id = null;
        this.list = null;
    }

    void ParseIdList() {
        this.id = ID.ParseId();
        Tokenizer.skipToken(); // skip ID
        if (!Tokenizer.idName().equals(";")) {
            Tokenizer.skipToken();
            this.list = new ID_List();
            this.list.ParseIdList();
        }
    }

    void ExecIDList() {
        if (this.list != null) {
            this.list.ExecIDList();
        }
    }

    void WriteIdList() {
        this.id.OutputId();
        if (this.list != null) {
            this.list.WriteIdList();
        }
    }

    void PrintIDList() {
        this.id.PrintId();
        if (this.list != null) {
            System.out.print(",");
            this.list.PrintIDList();
        } else {
            System.out.print("");
        }
    }

    void ReadIdList() {
        String next;
        Scanner Myin = new Scanner(System.in);

        System.out.print("Enter value for ");
        this.id.PrintId();
        System.out.print(": ");
        next = Myin.nextLine();
        //stuck here, run to see whats wrong
        this.id.setVal(Integer.parseInt(next));
        if (this.list != null) {
            this.list.ReadIdList();
        }

    }
}

/* class for assign */
class Assign {
    private ID id;
    private Exp exp;

    public Assign() {
        this.id = null;
        this.exp = null;
    }

    void ParseAssign() {
        this.id = ID.ParseId();
        Tokenizer.skipToken(); //skip id=
        Tokenizer.skipToken();
        this.exp = new Exp();
        this.exp.ParseExp();
        Tokenizer.skipToken();
    }

    void ExecAssign() {
        this.id.setVal(this.exp.getVal());
    }

    void PrintAssign() {
        this.id.PrintId();
        System.out.print(" = ");
        this.exp.PrintExp();
        System.out.println(";");
    }
}

/* class for if */
class If {
    private Cond cond;
    private Stmt_Seq ss1;
    private Stmt_Seq ss2;

    public If() {
        this.cond = null;
        this.ss1 = null;
        this.ss2 = null;
    }

    void ParseIf() {
        Tokenizer.skipToken(); //skip if
        this.cond = new Cond();
        this.cond.ParseCond();
        Tokenizer.skipToken(); //then
        this.ss1 = new Stmt_Seq();
        this.ss1.ParseStmtSeq();
        if (!Tokenizer.idName().equals("end")) {
            Tokenizer.skipToken(); //else
            this.ss2 = new Stmt_Seq();
            this.ss2.ParseStmtSeq();
            Tokenizer.skipToken(); //end;
            Tokenizer.skipToken();
        } else {
            Tokenizer.skipToken();
            Tokenizer.skipToken();
        }
    }

    void ExecIf() {
        if (this.cond.EvalCond()) {
            this.ss1.ExecStmtSeq();
        } else {
            if (this.ss2 != null) {
                this.ss2.ExecStmtSeq();
            }
        }
    }

    void PrintIf() {
        System.out.print("if ");
        this.cond.PrintCond();
        System.out.println(" then");
        Printer.indentUp();
        this.ss1.PrintStmtSeq();
        if (this.ss2 != null) {
            Printer.indentDown();
            Printer.indent();
            System.out.println("else");
            Printer.indentUp();
            this.ss2.PrintStmtSeq();
        }
        Printer.indentDown();
        //this.out.indent();
        //System.out.println("end;");
    }
}

/* class for loop */
class Loop {
    private Cond cond;
    private Stmt_Seq ss;
    Printer out;

    public Loop() {
        this.cond = null;
        this.ss = null;
    }

    void ParseLoop() {
        Tokenizer.skipToken(); //skip while
        this.cond = new Cond();
        this.cond.ParseCond();
        Tokenizer.skipToken();
        this.ss = new Stmt_Seq();
        this.ss.ParseStmtSeq();
        Tokenizer.skipToken(); //skip end and semicolon
        Tokenizer.skipToken();
    }

    void ExecLoop() {
        while (this.cond.EvalCond()) {
            this.ss.ExecStmtSeq();
        }
    }

    void PrintLoop() {
        System.out.print("while ");
        this.cond.PrintCond();
        System.out.println();
        Printer.indentUp();
        this.ss.PrintStmtSeq();
        Printer.indentDown();
        //this.out.indent();
        //System.out.println("end;");
    }
}

/* class for in */
class In {
    private ID_List list;
    static Scanner Myin = new Scanner(System.in);

    public In() {
        this.list = null;
    }

    void ParseIn() {
        Tokenizer.skipToken(); //skip read
        this.list = new ID_List();
        this.list.ParseIdList();
        Tokenizer.skipToken();
    }

    public void ExecIn() {
        this.list.ReadIdList();
    }

    void PrintInput() {
        System.out.print("input(");
        this.list.PrintIDList();
        System.out.println(")");
    }
}

/* class for out */
class Out {
    private ID_List list;

    public Out() {
        this.list = null;
    }

    void ParseOut() {
        Tokenizer.skipToken(); //skip write
        this.list = new ID_List();
        this.list.ParseIdList();
        Tokenizer.skipToken();
    }

    void ExecOut() {
        this.list.WriteIdList();
    }

    void PrintOutput() {
        System.out.print("print(");
        this.list.PrintIDList();
        System.out.println(")");
    }
}

/* class for cond */
class Cond {
    private Comp comp;
    private Cond cond1;
    private Cond cond2;
    private Boolean not;
    private Boolean and;
    private Boolean or;

    public Cond() {
        this.comp = null;
        this.cond1 = null;
        this.cond2 = null;
        this.not = false;
        this.and = false;
        this.or = false;
    }

    void ParseCond() {
        String token = Tokenizer.idName();

        if (token.equals("(")) {
            this.comp = new Comp();
            this.comp.ParseComp();
        } else if (token.equals("!")) {
            Tokenizer.skipToken(); //skip !
            this.cond1 = new Cond();
            this.cond1.ParseCond();
            this.not = true;
        } else if (token.equals("[")) {
            Tokenizer.skipToken(); //skip [
            this.cond1 = new Cond();
            this.cond1.ParseCond();
            token = Tokenizer.idName();
            if (token.equals("&&")) {
                Tokenizer.skipToken(); //skip &&
                this.and = true;
                this.cond2 = new Cond();
                this.cond2.ParseCond();
                Tokenizer.skipToken(); //skip ]
            } else if (token.equals("||")) {
                Tokenizer.skipToken(); //skip ||
                this.cond2 = new Cond();
                this.cond2.ParseCond();
                this.or = true;
                Tokenizer.skipToken(); //skip ]
            }
        }
    }

    public boolean EvalCond() {
        if (this.and) {
            return (this.cond1.EvalCond() && this.cond2.EvalCond());
        } else if (this.or) {
            return (this.cond1.EvalCond() || this.cond2.EvalCond());
        } else {
            if (this.cond1 != null) {
                return this.cond1.EvalCond();
            } else {
                return this.comp.EvalComp();
            }
        }
    }

    void PrintCond() {
        if (this.not) {
            System.out.print("!");
        }
        if (this.and) {
            System.out.print("[");
            this.cond1.PrintCond();
            System.out.print("&&");
            this.cond2.PrintCond();
            System.out.print("]");
        } else if (this.or) {
            System.out.print("[");
            this.cond1.PrintCond();
            System.out.print("||");
            this.cond2.PrintCond();
            System.out.print("]");
        } else {
            if (this.cond1 != null) {
                this.cond1.PrintCond();
            } else {
                this.comp.PrintComp();
            }
        }
    }
}

/* class for comp */
class Comp {
    private Op op1;
    private Op op2;
    private Comp_Op coop;

    public Comp() {
        this.op1 = null;
        this.op2 = null;
        this.coop = null;
    }

    void ParseComp() {
        Tokenizer.skipToken(); //skip (
        this.op1 = new Op();
        this.op1.ParseOp();
        this.coop = new Comp_Op();
        this.coop.ParseCompOp();
        this.op2 = new Op();
        this.op2.ParseOp();
        Tokenizer.skipToken(); //skip )
    }

    public boolean EvalComp() {
        Boolean result = false;
        if (this.coop.getVal() == "==") {
            result = (this.op1.getVal() == this.op2.getVal());
        } else if (this.coop.getVal() == "!=") {
            result = (this.op1.getVal() != this.op2.getVal());
        } else if (this.coop.getVal() == "<") {
            result = (this.op1.getVal() < this.op2.getVal());
        } else if (this.coop.getVal() == ">") {
            result = (this.op1.getVal() > this.op2.getVal());
        } else if (this.coop.getVal() == "<=") {
            result = (this.op1.getVal() <= this.op2.getVal());
        } else if (this.coop.getVal() == ">=") {
            result = (this.op1.getVal() >= this.op2.getVal());
        }
        return result;
    }

    void PrintComp() {
        System.out.print("(");
        this.op1.PrintOp();
        this.coop.PrintCompOp();
        this.op2.PrintOp();
        System.out.print(")");
    }
}

/* class for comp_op */
class Comp_Op {
    private String coop;

    void ParseCompOp() {
        String token = Tokenizer.idName();
        if (token.equals("!=")) {
            this.coop = "!=";
        }
        if (token.equals("==")) {
            this.coop = "==";
        }
        if (token.equals("<")) {
            this.coop = "<";
        }
        if (token.equals(">")) {
            this.coop = ">";
        }
        if (token.equals("<=")) {
            this.coop = "<=";
        }
        if (token.equals(">=")) {
            this.coop = ">=";
        }
        Tokenizer.skipToken();
    }

    public String getVal() {
        return this.coop;
    }

    void PrintCompOp() {
        System.out.print(this.coop);
    }
}

/* class for exp */
class Exp {
    private Fac fac;
    private Exp exp;
    private boolean add;
    private boolean sub;

    public Exp() {
        this.fac = null;
        this.exp = null;
        this.add = false;
        this.sub = false;
    }

    void ParseExp() {
        this.fac = new Fac();
        this.fac.ParseFac();
        String token = Tokenizer.idName();
        if (token.equals("+")) {
            this.add = true;
            Tokenizer.skipToken();
            this.exp = new Exp();
            this.exp.ParseExp();
        } else if (token.equals("-")) {
            this.sub = true;
            Tokenizer.skipToken(); //skip -
            this.exp = new Exp();
            this.exp.ParseExp();
        }
    }

    public int getVal() {
        if (this.exp == null) {
            return this.fac.getVal();
        } else {
            if (this.add) {
                return this.fac.getVal() + this.exp.getVal();
            } else if (this.sub) {
                return this.fac.getVal() - this.exp.getVal();
            }
        }
        return 0;
    }

    void PrintExp() {
        if (this.fac != null) {
            this.fac.PrintFac();
        }
        if (this.add) {
            System.out.print("+");
        }
        if (this.sub) {
            System.out.print("-");
        }
        if (this.exp != null) {
            this.exp.PrintExp();
        }
    }
}

/* class for fac */
class Fac {
    private Op op;
    private Fac fac;
    private Boolean mtp;

    public Fac() {
        this.op = null;
        this.fac = null;
        this.mtp = false;
    }

    void ParseFac() {
        this.op = new Op();
        this.op.ParseOp();
        if (Tokenizer.idName().equals("*")) {
            this.mtp = true;
            Tokenizer.skipToken();
            this.fac = new Fac();
            this.fac.ParseFac();
        }
    }

    public int getVal() {
        if (this.mtp) {
            return (this.op.getVal() * this.fac.getVal());
        } else {
            return this.op.getVal();
        }
    }

    void PrintFac() {
        if (this.op != null) {
            this.op.PrintOp();
        }
        if (this.mtp) {
            System.out.print("*");
        }
        if (this.fac != null) {
            this.fac.PrintFac();
        }
    }
}

/* class for op */
class Op {
    private Integer i;
    private ID id;
    private Exp exp;

    public Op() {
        this.i = null;
        this.id = null;
        this.exp = null;
    }

    void ParseOp() {
        String token = Tokenizer.idName();
        if (token.equals("(")) {
            Tokenizer.skipToken(); //skip "("
            this.exp = new Exp();
            this.exp.ParseExp();
            Tokenizer.skipToken(); //skip ")"
        } else if (token.matches("\\d*")) {
            this.i = Integer.valueOf(token);
            Tokenizer.skipToken();
        } else {
            this.id = ID.ParseId();
            Tokenizer.skipToken();
        }
    }

    public int getVal() {
        if (this.i != null) {
            return this.i;
        } else if (this.id != null) {
            return this.id.getVal();
        } else if (this.exp != null) {
            return this.exp.getVal();
        }
        return 0;
    }

    void PrintOp() {
        if (this.i != null) {
            System.out.print(this.i);
        }
        if (this.id != null) {
            this.id.PrintId();
        }
        if (this.exp != null) {
            System.out.print("(");
            this.exp.PrintExp();
            System.out.print(")");
        }
    }
}

/* class for id */
class ID {
    private String name;
    private Integer num;
    private static HashMap<String, ID> idSet = new HashMap<String, ID>();

    private ID(String n) {
        this.name = n;
        this.num = null;
    }

    public static ID ParseId() {
        String token = Tokenizer.idName();
        if (idSet.containsKey(token)) {
            return idSet.get(token);
        } else {
            ID id = new ID(token);
            idSet.put(token, id);
            return id;
        }
    }

    public int getVal() {
        return this.num;
    }

    public void setVal(int num) {
        this.num = num;
    }

    void OutputId() {
        System.out.println(this.name + " = " + this.num);
    }

    void PrintId() {
        System.out.print(this.name);
    }
}
