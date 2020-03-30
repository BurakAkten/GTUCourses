import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Scanner;

/**
 * Created by Burak Akten on 19/05/2017.
 */
public class main {

    public static void main(String[] args){

        MatrixGraph matrixObj = null;
        ListGraph listbj = null;
        System.out.println("**********Graph is Testing with undirected MatrixGraph***********!!!\n");
        testingGraphMatrix("input1.txt" , matrixObj , "MatrixGraph" , false);
        System.out.println("\n**********Graph is Testing with undirected ListGraph************!!!\n");
        testingGraphList("input2.txt" , listbj , "ListGraph" , false);
        System.out.println("\n**********Graph is Testing with directed ListGraph************!!!\n");
        testingGraphList("input2.txt" , listbj , "ListGraph" , true);

    }

    private static void testingGraphMatrix(String filename , MatrixGraph graph , String ouputFile , boolean directed){
        File graphData = new File(filename);
        Scanner scnr = null;
        try {
            scnr = new Scanner(graphData );
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        try {
            graph = (MatrixGraph) AbstractGraph.createGraph(scnr, directed, "Matrix");

        } catch (IOException e) {
            e.printStackTrace();
        }
        System.out.println("Is this grapg directed? : " + directed);

        if(!graph.isDirected()) {
            int[] a = graph.breadthFirstSearch(0);
            int i = 0;
            System.out.println("The BFS result!");
            for (int x : a)
                System.out.printf("i : %d - value : %d\n", i++, x);
        }

        System.out.println("Is Graph is BipartiteUndirectedGraph? : " + graph.isBipartiteUndirectedGraph() );

        MatrixGraph[] CC = (MatrixGraph[])graph.getConnectedComponentUndirectedGraph();
        StringBuilder file = new StringBuilder();
        for (int j = 0 ;CC != null&& j < CC.length ; j++){
            file.append(ouputFile);
            file.append(j);
            file.append(".txt");
            CC[j].writeGraphToFile (file.toString());
            file = new StringBuilder();
        }
        if(CC == null) {
            file.append(ouputFile);
            file.append(".txt");
            graph.writeGraphToFile(file.toString());
        }

        System.out.printf("Edges adding to the graph( %d edges!)!\n",graph.addRandomEdgesToGraph(10));
        System.out.println("Is Graph is BipartiteUndirectedGraph after adding edges? : "+graph.isBipartiteUndirectedGraph());
    }
    private static void testingGraphList(String filename , ListGraph graph , String ouputFile , boolean directed){
        File graphData = new File(filename);
        Scanner scnr = null;
        try {
            scnr = new Scanner(graphData );
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        try {
            graph = (ListGraph) AbstractGraph.createGraph(scnr, directed, "List");

        } catch (IOException e) {
            e.printStackTrace();
        }
        System.out.println("Is this grapg directed? : " + directed);

        if(!graph.isDirected()) {
            int[] a = graph.breadthFirstSearch(0);
            int i = 0;
            System.out.println("The BFS result!");
            for (int x : a)
                System.out.printf("i : %d - value : %d\n", i++, x);
        }
        System.out.println("Is Graph is BipartiteUndirectedGraph? : " + graph.isBipartiteUndirectedGraph() );

        ListGraph[] CC = (ListGraph[]) graph.getConnectedComponentUndirectedGraph();
        StringBuilder file = new StringBuilder();
        for (int j = 0 ; CC != null && j < CC.length ; j++){
            file.append(ouputFile);
            file.append(j);
            file.append(".txt");
            CC[j].writeGraphToFile (file.toString());
            file = new StringBuilder();
        }
        if(CC == null) {
            file.append(ouputFile);
            file.append(".txt");
            graph.writeGraphToFile(file.toString());
        }

        System.out.printf("Edges adding to the graph( %d edges!)!\n",graph.addRandomEdgesToGraph(10));
        System.out.println("Is Graph is BipartiteUndirectedGraph after adding edges? : "+graph.isBipartiteUndirectedGraph());
    }
}
