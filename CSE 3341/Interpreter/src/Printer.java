public class Printer {
    private static int indentation = 0;

    //set indentation
    public static void indent() {
        String s = "";
        int i = 0;
        while (i < Printer.indentation * 8) {
            s += " ";
            i++;
        }
        System.out.print(s);
    }

    //print empty line
    public static void println() {
        System.out.print("\n");
    }

    //increase current indentation
    public static void indentUp() {
        Printer.indentation++;
    }

    //decrease current indentation
    public static void indentDown() {
        Printer.indentation--;
    }

}
