import java.io.FileWriter;
import java.util.*;

/**
 * Created by Burak Akten on 17/05/2017.
 */
public abstract class AbstractGraphExtended extends AbstractGraph {
    /**
     * This method finds the indexes that have the value -1 that are after the parent index.
     * @param arr the array that is searched
     * @return an array that holds the indexes
     */
    private int[] findMinus1(int[] arr , int parent){
        /*holds the indexes*/
        LinkedList<Integer> minus = new LinkedList<>();

        /*Searching is making */
        for (int i = parent + 1; i < arr.length ; i++)
            if(arr[i] == -1)
                minus.add(i);
        /* The result is array that hold indexes*/
        int[] result = new int[minus.size()];
        for (int i = 0 ; i < minus.size() ; i++)
            result[i] = minus.get(i);

        return result;
    }

    /**
     * This method signs the indexes as visited. To do this , firstly look the previous visited places then signs
     * other places as visited according to helper array(minusArr)
     * @param marked visited array
     * @param minusArr helper array that says indexes to sign
     * @return an array that holds all the visited indexes till now
     */
    private boolean[] makeVisited(boolean[] marked , int[] minusArr ){
        boolean flag ;
        for(int i = 0;  i < marked.length ; i++){
            flag = true;
            for(int j = 0; j < minusArr.length && flag; j++){
                if(i == minusArr[j])
                    flag = false;
            }
            if (flag)
                marked[i] = true;
        }
        return marked;
    }

    /**
     * This method is making mapping to the vertex in set.
     * @param vertex the vertex set that are mapped
     * @return a map.
     */
    private Map<Integer , Integer> mappingVertices(Set<Integer> vertex){

        Map<Integer , Integer> result = new HashMap<>();
        Iterator<Integer> itr = vertex.iterator();
        int i = 0;
        while(itr.hasNext())
            result.put(itr.next() , i++);
        return result;
    }

    /**
     * Construct a graph with the specified number of vertices
     * and the directed flag. If the directed flag is true,
     * this is a directed graph.
     *
     * @param numV     The number of vertices
     * @param directed The directed flag
     */
    public AbstractGraphExtended(int numV, boolean directed) {
        super(numV, directed);
    }

    /**
     * This method selects a random number between 0 and edgeLimit then adds that much edges to calling graph.
     * The source and destination vertices of edges will be random again. The inserted edges will be directed or
     * undirected according to calling graph
     * @param edgeLimit the limit for the edges that is added.
     * @return the number  edges that is added
     */
    public int addRandomEdgesToGraph (int edgeLimit){
        /*Random number is created*/
        Random rand = new Random();
        int edgeNum = rand.nextInt(edgeLimit);
        int count = 0 ; // holds the added edges numbers
        /*The insertion is applying*/
        for(int i = 0 ; i < edgeNum ; i++){
            int firstV , secondV ;

            firstV = rand.nextInt(this.getNumV());
            secondV = rand.nextInt(this.getNumV());

            if(!isEdge(firstV , secondV)) {
                insert(new Edge(firstV, secondV));
                count++;
            }
            else
                edgeNum--;
        }
        return count ;
    }

    /**
     *This method performs a breadth first search on calling graph starting from vertex start.
     * @param start starting vertex.
     * @return contains the predecessor of each vertex in the breadth-first search tree
     */
    public int [] breadthFirstSearch (int start){
        Queue<Integer> theQueue = new LinkedList<>();

        //parent array is declaring and every index is initializing to -1.
        int parent[] = new int[super.getNumV()];
        for (int i = 0 ; i < super.getNumV() ; i++)
            parent[i] = -1;

        // Declare array identified and
        // initialize its elements to false.
        boolean[] identified = new boolean[this.getNumV()];

        /* Mark the start vertex as identified and insert it into the queue */
        identified[start] = true;
        theQueue.offer(start);

        /* While the queue is not empty */
        while (!theQueue.isEmpty()) {
            /* Take a vertex, current, out of the queue.  (Begin visiting current). */
            int current = theQueue.remove();
            /* Examine each vertex, neighbor, adjacent to current. */
            Iterator<Edge> itr = this.edgeIterator(current);
            while (itr.hasNext()) {
                Edge edge = itr.next();
                int neighbor = edge.getDest();
                // If neighbor has not been identified
                if (!identified[neighbor]) {
                    // Mark it identified.
                    identified[neighbor] = true;
                    // Place it into the queue.
                    theQueue.offer(neighbor);
                    /* Insert the edge (current, neighbor) into the tree. */
                    parent[neighbor] = current;
                }
            }
        }
        return parent;
    }

    /**
     *This method finds connected components in a graph, creates ListGraph or MatrixGraph instances for
     * each connected component and returns them in a Graph array. The method will only work for undirected graphs.
     * @return a Graph array
     */
    public Graph [] getConnectedComponentUndirectedGraph (){
        /*if the graph is directed then return null*/
        if(isDirected())
            return null;
        int parent = 0;
        ArrayList<Integer> parents = new ArrayList<>(); // this arraylist holds all subgraphs parents.
        /*This part find the vertexes of the sub-graphs parents */
        int[] parentArr = this.breadthFirstSearch(parent);
        boolean[] marked = new boolean[getNumV()];
        parents.add(0);
        while(parent < getNumV()){
            int[] minusIndexes = findMinus1(parentArr , parent);
            marked = makeVisited(marked , minusIndexes);

            boolean flag = false;
            for (int j = 0; j < minusIndexes.length && !flag ; j++)
                if(parentArr[minusIndexes[j]] == -1 && !marked[minusIndexes[j]] ){
                    parent = minusIndexes[j]; // parent is updated
                    flag = true;
                    parents.add(parent);
                    parentArr = this.breadthFirstSearch(parent); // parentArr is updated according to parent
                }
            if (!flag)
                parent = getNumV();
        }
        /*This part create a Graph array with size of the parents*/
        Graph[] result;
        boolean list; // for controlling listGraph or not
        if(this instanceof ListGraph) {
            result = new ListGraph[parents.size()];
            list = true;
        } else {
            result = new MatrixGraph[parents.size()];
            list = false;
        }
        for (int i = 0 ; i < parents.size() ; i++)
            result[i] = null;

        /*This part of the code , fills the all indexex of the graph array. */
        Set<Integer> vertex; // holds the vertexes
        for(int i = 0; i <parents.size(); i++){

            /*This part fill the set is called vertex by using BFS algorithm*/
            Queue<Integer> thequeue = new LinkedList<>();
            vertex = new HashSet<>();

            boolean[] identified = new boolean[this.getNumV()];
            identified[parents.get(i)] = true;
            thequeue.offer(parents.get(i));

            while (!thequeue.isEmpty()) {
                /* Take a vertex, current, out of the queue.  (Begin visiting current). */
                int current = thequeue.remove();
                /* Examine each vertex, neighbor, adjacent to current. */
                Iterator<Edge> itr = this.edgeIterator(current);
                while (itr.hasNext()) {
                    Edge edge = itr.next();
                    if(!identified[edge.getDest()]) {
                        vertex.add(edge.getSource());
                        vertex.add(edge.getDest());

                        identified[edge.getDest()] = true;
                        thequeue.add(edge.getDest());
                    }
                }
            }
            /*After fiiling the vertex set , mapping is done on these vertexes. And the ith index of the graph array is
            * created.*/
            Map<Integer , Integer> newVertex = mappingVertices(vertex);
            if(list)
                result[i] = new ListGraph(newVertex.size() , isDirected() );
            else
                result[i] = new MatrixGraph(newVertex.size() , isDirected());

            /*Lastly, mapped vertexes are added as edges on the graph on ith index of the Graph array by using BFS */
            thequeue = new LinkedList<>();
            identified = new boolean[this.getNumV()];
            identified[parents.get(i)] = true;
            thequeue.offer(parents.get(i));

            while (!thequeue.isEmpty()) {
                /* Take a vertex, current, out of the queue.  (Begin visiting current). */
                int current = thequeue.remove();
                /* Examine each vertex, neighbor, adjacent to current. */
                Iterator<Edge> itr = this.edgeIterator(current);
                while (itr.hasNext()) {
                    Edge edge = itr.next();

                    if(!identified[edge.getDest()]) {
                        result[i].insert(new Edge(newVertex.get(edge.getSource()) ,newVertex.get(edge.getDest()) ));

                        identified[edge.getDest()] = true;
                        thequeue.add(edge.getDest());
                    }
                }
            }
        }
        return result;
    }

    /**
     * This method returns true if calling graph instance is bipartite graph, false otherwise
     * @return returns true if calling graph instance is bipartite graph, false otherwise
     */
    public boolean isBipartiteUndirectedGraph (){

        if(isDirected())
            return false;
        // 1 = Red , -1 = Blue
        int[] colorArr = new int[this.getNumV()]; // represents colors
        for(int i = 0; i < this.getNumV() ; i++) // set as default (0)
            colorArr[i] = 0; // No color

        int parent = 0;

        while (parent < this.getNumV()){
            /*For traverse the graph*/
            Queue<Integer> theQueue = new LinkedList<>();
            theQueue.offer(parent);
            //parent sign as blue
            colorArr[parent] = -1;
            /*Then BFS strategy is applying*/
            while(!theQueue.isEmpty()){
                int currentV = theQueue.remove();
                Iterator<Edge> itr = this.edgeIterator(currentV);
                while(itr.hasNext()){
                    int neighbour = itr.next().getDest();
                    /*if neighbour doesn't have color then set the color of neighbour opposite of parent. */
                    if(colorArr[neighbour] == 0){
                        colorArr[neighbour] = -1*colorArr[currentV];
                        theQueue.offer(neighbour);
                    }
                    else if(colorArr[neighbour] == colorArr[currentV]) // if both are same then return false
                        return false;
                }
            }
            /*When the graph has subgraphs than this part is important to update parent*/
            boolean flag = false;
            for (int j = 0; j < colorArr.length && !flag ; j++)
                if(colorArr[j] == 0) {
                    parent = j;
                    flag = true;
                }
            if (!flag)
                parent = getNumV();
        }
        return true;
    }

    /**
     * This method will do the reverse of createGraph method in the AbstractGraph abstract class and write number
     * of vertices source and destination vertex of each edge in a file.
     * @param fileName file name of the outut file.
     */
    public void writeGraphToFile (String fileName){
        //the string for writing to the output file.
        StringBuilder outStr = new StringBuilder();
        LinkedList<Edge> edges = new LinkedList<>(); // for controlling same edges when graph is undirected
        int parent = 0;
        outStr.append(this.getNumV());
        outStr.append("\n");

        int[] parentArr = this.breadthFirstSearch(parent);// helper array for finding subgraphs
        boolean[] marked = new boolean[getNumV()];

        do {
            int[] minus1 = findMinus1(parentArr , parent);
            marked = makeVisited(marked , minus1);

            /*The BFS algorithm is applying*/
            Queue<Integer> theQueue = new LinkedList<>();
            theQueue.offer(parent);
            while (!theQueue.isEmpty()) {
                int currentVertex = theQueue.remove();
                Iterator<Edge> itr = this.edgeIterator(currentVertex);
                while (itr.hasNext()) {
                    Edge current = itr.next();
                    if (this.isDirected() && !edges.contains(new Edge(current.getSource(),current.getDest()))) {
                        outStr.append(current.getSource());
                        outStr.append(" ");
                        outStr.append(current.getDest());
                        outStr.append("\n");
                        edges.add(current);
                        if (!theQueue.contains(current.getDest()))
                            theQueue.offer(current.getDest());

                    } else if (!edges.contains(new Edge(current.getDest(), current.getSource()))) {
                        outStr.append(current.getSource());
                        outStr.append(" ");
                        outStr.append(current.getDest());
                        outStr.append("\n");
                        edges.add(current);
                        if (!theQueue.contains(current.getDest()))
                            theQueue.offer(current.getDest());
                    }
                }
            }
             /*When the graph has subgraphs than this part is important to update parent*/
            boolean flag = false;
            for (int j = 0; j < minus1.length && !flag ; j++)
                if(parentArr[minus1[j]] == -1 && !marked[minus1[j]] ){
                    parent = minus1[j];
                    flag = true;
                    parentArr = this.breadthFirstSearch(parent);
                }
            if (!flag)
                parent = getNumV();
        }while(parent < getNumV());

        /*Writing to the graph*/
        try {
            FileWriter outputFile = new FileWriter(fileName);
            outputFile.write(outStr.toString());
            outputFile.close();
        }catch (Exception e){
            e.printStackTrace();
        }
    }

}
