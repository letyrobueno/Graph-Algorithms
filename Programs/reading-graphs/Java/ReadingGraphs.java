/* Example of how to read a graph from an input file (the format is set by the programmer) and 
store it into an adjacency list and into an adjacency matrix.
    Command line to compile it: javac ReadingGraphs.java
    Command line to run it: java ReadingGraphs G1.in
*/

import java.io.*;
import java.util.ArrayList;
import java.io.IOException;

public class ReadingGraphs {

    static void readMatrix(String nameFile) {
        try { // try to read the file
            FileReader input = new FileReader(nameFile); // associate variable to the file
            BufferedReader br = new BufferedReader(input); // open file for reading
            String line;
            String[] fields = null;
            String[] fields2 = null;

            int n = Integer.parseInt(br.readLine()); // read first line
            int M[][] = new int[n + 1][n + 1]; // take the number of vertices

            while ((line = br.readLine()) != null) {
                fields = line.split(":"); // split data divided by ":"
                int u = Integer.parseInt(fields[0]);
                fields2 = fields[1].split(","); // split data divided by ","
                for (String edge : fields2) {
                    int v = Integer.parseInt(edge);
                    M[u][v] = 1;
                    M[v][u] = 1;
                }
            }
            br.close(); // close the file

            // traverse the adjacency matrix to write it
            System.out.print("    ");
            for (int i = 1; i <= n; i++) {
                System.out.printf(" %2d |", i);
            }
            System.out.println();
            for (int i = 1; i <= n; i++) {
                System.out.printf(" %2d|", i);
                for (int j = 1; j <= n; j++) {
                    if (M[i][j] == 1) {
                        System.out.print("  X |");
                    } else if (i == j) {
                        System.out.print("  0 |");
                    } else {
                        System.out.print("    |");
                    }
                }
                System.out.println();
            }
        } catch (IOException ioException) { // couldn't read the file
            System.out.println("Error reading the input file!");
        }
    }

    static void leituraLista(String nameFile) {
        try { // try to read the file
            FileReader input = new FileReader(nameFile); // associate variable to the file
            BufferedReader br = new BufferedReader(input); // open file for reading
            String line;
            String[] fields = null;
            String[] fields2 = null;
            int n = Integer.parseInt(br.readLine()); // read 1st line
            @SuppressWarnings("unchecked")
            ArrayList<Integer>[] L = (ArrayList<Integer>[]) new ArrayList[n + 1];

            for (int i = 1; i <= n; i++) {
                L[i] = new ArrayList<Integer>();
            }

            while ((line = br.readLine()) != null) {
                fields = line.split(":"); // split data divided by ":"
                int u = Integer.parseInt(fields[0]);

                fields2 = fields[1].split(",");
                for (String edge : fields2) {
                    int v = Integer.parseInt(edge);
                    L[u].add(v);
                    L[v].add(u); // if the graph is undirected
                }
            }
            br.close(); // close the file

            // traverse the adjacency list to write it
            for (int j = 1; j <= n; j++) {
                System.out.printf(" | %2d | ", j);
                for (int i = 0; i < L[j].size(); i++) {
                    System.out.printf("=> %2d", L[j].get(i));
                }
                System.out.println("");
            }
        } catch (IOException ioException) { // couldn't read the file
            System.out.println("Error reading the input file!");
        }
    }

    public static void main(String[] args) {
        String inputFile = args[0]; // it takes the name of the input file

        System.out.println("\n************\n Graph from the Adjacency Matrix \n************\n");
        readMatrix(inputFile);

        System.out.println("\n************\n Graph from the Adjacency List \n************\n");
        leituraLista(inputFile);
    }
}
