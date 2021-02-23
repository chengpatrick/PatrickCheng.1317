import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.ListIterator;
import java.util.Scanner;

/* author: Patrick Cheng */

public class Tokenizer {

    //list of tokens, 33 in total, 0-10 reserve words, 11-29 special symbols, 30 int, 31 iden, 32 eof
    private static List<String> Token_IDs = Arrays.asList("program", "begin",
            "end", "int", "if", "then", "else", "while", "loop", "read",
            "write", ";", ",", "=", "!", "[", "]", "&&", "||", "(", ")", "+",
            "-", "*", "!=", "==", "<", ">", "<=", ">=", "num", "iden", "EOF");
    //types of tokens
    private static List<String> Token_Type = Arrays.asList("Reserve Words",
            "Special Symbol", "Integer", "Identifier", "EOF");
    //string for reserve words
    public static final String Reserve_Words = "program,begin,end,int,if,then,else,while,loop,read,write";
    //string for special symbols
    public static final String Symbols = ";,=![]&&||()+-*!===<><=>=";
    //string for white space
    public static final String Whitespace = " \t\n\r";

    //id for integer
    private static final int Integer_ID = 30;
    //id for identifier
    private static final int Identifier_ID = 31;

    //list of original token
    List<String> token = new ArrayList<String>();
    //list of token id names
    List<String> token_ID_name = new ArrayList<String>();
    //list of token id num
    List<Integer> token_ID_num = new ArrayList<Integer>();
    //list iterator of token id names
    ListIterator<String> LI_token = null;
    int current_pos = 0;

    private Tokenizer(Scanner readFile) {
        //counter
        int i = 0;
        //read from file and store info
        this.storeInfo(readFile);
        //save the id names of the token into token_ID_name
        this.token_ID_name = new ArrayList<String>(this.token);
        i = 0;
        while (i < this.token_ID_name.size()) {
            String temp = IDNameOfToken(this.token_ID_name.get(i));
            if (!temp.equals(this.token_ID_name.get(i))) {
                this.token_ID_name.set(i, temp);
            }
            i++;
        }

        //store id num in list
        while (this.current_pos < this.token.size()) {
            this.token_ID_num.add(this.current_pos, this.getToken());
            this.skipToken();
        }
        this.current_pos = 0;
    }

    /* function to see if string s is an int or not */
    private static boolean isInt(String s) {
        try {
            Integer.parseInt(s);
            return true;
        } catch (NumberFormatException e) {
            return false;
        }
    }

    /* raed and store the info into the token */
    private void storeInfo(Scanner readFile) {
        String data = "";
        //flag to check if error occurs or not
        boolean error = false;

        while (readFile.hasNextLine() && !error) {
            int i = 0;
            data = readFile.nextLine();
            /* test if file is read */
            //System.out.println("File data: " + data);
            //store read line in list
            while (i < data.length()) {
                String next = nextTokenOrWhitespace(data, i);
                //add to token if not whitespace
                if (Whitespace.indexOf(next.substring(0, 1)) == -1) {
                    //check if token is legal or not
                    if (isInt(next) || isIdentifier(next)
                            || (Token_IDs.contains(next))) {
                        this.token.add(next);
                        System.out.print(next + " ");
                    } else {
                        System.out.println("\nError, invalid token.");
                        i = data.length();
                        error = true;
                    }
                }
                i += next.length();
            }
            System.out.println();
        }
        if (!error) {
            this.token.add("EOF");
        }
    }

    /* function to see if token is identifier */
    private static boolean isIdentifier(String token) {

        if (token.length() > 8) {
            return false;
        }
        if (!Character.isUpperCase(token.charAt(0))) {
            return false;
        }
        int i = 1;
        while (i < token.length()) {
            if (Character.isUpperCase(token.charAt(i))) {
                i++;
            } else {
                if (isInt(Character.toString(token.charAt(i)))) {
                    i++;
                } else {
                    return false;
                }
            }
        }

        return true;
    }

    /* returns the id name of the token */
    private static String IDNameOfToken(String token) {
        if (Token_IDs.indexOf(token) != -1) {
            return Token_IDs.get(Token_IDs.indexOf(token));
        } else if (isInt(token)) {
            return Token_IDs.get(Integer_ID);
        } else if (isIdentifier(token)) {
            return Token_IDs.get(Identifier_ID);
        } else if (token.toUpperCase().equals("EOF")) {
            return "EOF";
        } else {
            return "error";
        }
    }

    /* returns (info about) current token, the id num of the token */
    private int getToken() {
        return (this.current_pos < this.token.size())
                ? (Token_IDs.indexOf(this.token_ID_name.get(this.current_pos))
                        + 1)
                : (Token_IDs.indexOf("EOF") + 1);
    }

    /* skips current token */
    private void skipToken() {
        if (this.current_pos < this.token.size()) {
            this.current_pos++;
        }
    }

    /* return the value of the current(integer) token */
    private int intVal() {

        return Integer.valueOf(this.token.get(this.current_pos));
    }

    /* returns the name(string) of the current (id) token */
    private String idName() {

        return this.token.get(this.current_pos);
    }

    /* return the next token or whitespace */
    private static String nextTokenOrWhitespace(String input, int position) {

        final int tf = 25;
        StringBuilder str = new StringBuilder(tf);
        String type;

        // position is whitespace
        if (Whitespace.indexOf(input.charAt(position)) != -1) {
            while (position < input.length()
                    && Whitespace.indexOf(input.charAt(position)) != -1) {
                str.append(input.charAt(position));
                position++;
            }
            // position is part of token
        } else {
            while (position < input.length()
                    && Whitespace.indexOf(input.charAt(position)) == -1) {
                //deal with special symbols
                if (Symbols
                        .contains(Character.toString(input.charAt(position)))) {
                    //check if there are tokens before symbol
                    if (str.length() == 0) {
                        //check for two symbols
                        if (input.charAt(position) == '!'
                                || input.charAt(position) == '<'
                                || input.charAt(position) == '>'
                                || input.charAt(position) == '=') {
                            str.append(input.charAt(position));
                            position++;
                            if (input.charAt(position) == '=') {
                                str.append(input.charAt(position));
                                position++;
                            } else {
                                return str.toString();
                            }
                        } else if (input.charAt(position) == '&'
                                || input.charAt(position) == '|') {
                            str.append(input.charAt(position));
                            str.append(input.charAt(position + 1));
                            position += 2;
                            return str.toString();
                        } else {
                            str.append(input.charAt(position));
                            position++;
                            return str.toString();
                        }
                    } else {
                        return str.toString();
                    }
                    //this position is not special symbol
                } else {
                    //check if there are tokens after symbol
                    if (str.length() == 0 || !Symbols.contains(
                            Character.toString(str.charAt(str.length() - 1)))) {
                        str.append(input.charAt(position));
                        position++;
                    } else {
                        return str.toString();
                    }
                }
            }
        }
        return str.toString();
    }

    public static void main(String[] args) throws IOException {

        Tokenizer t = null;
        ListIterator<Integer> LI_t = null;
        Scanner myIn = new Scanner(System.in); // Create a Scanner object

        //read in file
        try {
            System.out.print("Enter file to read (Example:data/test1.txt): ");
            String userInput = myIn.nextLine(); // Read user input
            File file = new File(userInput);
            Scanner readFile = new Scanner(file);
            t = new Tokenizer(readFile);
            readFile.close();
            LI_t = t.token_ID_num.listIterator();
            //print the id num of tokens

            try {
                System.out.print(
                        "Enter file name of output, the output file will be saved in the data folder (Example:output.txt): ");
                userInput = myIn.nextLine(); // Read user input
                FileWriter myWriter = new FileWriter("data/" + userInput);

                //print output and write to file
                while (LI_t.hasNext()) {
                    int output = LI_t.next();
                    System.out.print(output + " ");
                    myWriter.write(output + " ");
                }
                myWriter.close();
            } catch (IOException e) {
                System.out.println("An error occurred.");
                e.printStackTrace();
            }

        } catch (FileNotFoundException error) {
            System.out.println("An error occurred.");
            error.printStackTrace();
        }
    }
}
