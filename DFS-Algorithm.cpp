#include<iostream>
using namespace std; 

class Node { //Class structure that holds the connection between nodes
    public:
        char from; //The variable where the first node is held
        char to; //The variable that will hold the node's connections
};


void DFS(char start);//BFS function definition
int edge_num;//Variable that holds the total number of connections
Node * nodes;//Define nodes object connected to Node class

int main() 
{
    //The nodes of the graph and the nodes it is connected to
    //It will be read from the edges.txt file.
    FILE *edges;
    edges=fopen("edges.txt","r");
    fscanf(edges, "%d", &edge_num); //The first line of the file contains the number of links.

    nodes = new Node [edge_num];//The array is created by containing the variables that depend on the Node class.
    
    //Node links read from the file are assigned to the "from" and "to" variables, respectively.
    //Connections "from" are defined as the first node and "to" as its child child nodes.
    for(int i=0; i<edge_num; i++){
        fscanf(edges, "\n %c %c", &nodes[i].from, &nodes[i].to);
    }
    
    DFS('S'); //The DFS function is called by specifying the starting node in parentheses.
    //Since nodes are defined as char type in the program, they are specified using ' in parentheses.
}

void DFS(char start) { //DFS function is initialized with 'start' of type char
    char visited[edge_num]; //Array to keep visited nodes
    int visit{0};//Variable used to control visited nodes
    char stack[edge_num];//Stack array that will contain the connection of each node, as it must visit the nodes in order
    int st{0};//Variable used to control the stack array
    int last{0};//Variable to hold the index number of the last used node in the stack.
    
    ////Each element of the arrays is entered first as a ' ' (space) to make it easier to control the visited and stack arrays.
    for(int i=0; i<edge_num; i++){
        visited[i] = ' ';
        stack[i] = ' ';
    }
      
    cout << "Result when using Depth-First search (start node: " << start << "):";
    stack[st] = start;//Assigning the starting node to the stack array.
    visited[visit] = start;//Assigning the starting node to the visited array.
    //The first node is saved as visited and printed to the screen.
    cout  << " " << visited[visit];
    L1: //In the DFS algorithm, when a node has no unvisited connections,
		//it checks the previous node's connections by going back in the stack.
        //In order to provide this control and first visit the first port defined for each node,
		//we specify the point to return to with the 'goto' statement.
        
        //This loop is used to list the ports of the visited node.
        for(int i=0; i<edge_num; i++){
            if(visited[visit] == nodes[i].from){//visited[visit] = last visited node. nodes[i].from = The master node defined within the Node class, retrieved from edges.txt.
            //The equality is checked and when the two nodes match, the nodes that the corresponding node is linked to by index number are added to the Stack array.
                st++;//Incrementing the control variable of the stack array by 1.
                stack[st] = nodes[i].to;//Connected nodes are stored sequentially in the Stack array. nodes[i].to = Linked node defined within the Node class, retrieved from edges.txt.
            }
        }
        
        //This loop is used to find the first unvisited node in the stack array.
        for(int i=last; i<=st; i++){
            //Using the nested loop, all elements of the visited array and all elements of the stack array are compared.
            for(int j=0; j<edge_num; j++){
                if(visited[j] == stack[i]){
                    break;//If the node in the stack array exists in the visited array, the loop is exited and the next node is checked.
                }
                else if(visited[j] == ' '){//If no element of the Heap array and the visited array match, and the corresponding element of the visited array is empty;
                    visit++;//Incrementing the control variable of the visited array by 1.
                    visited[visit] = stack[i];//The relevant element of the stack array is added to the visited array.
                    cout  << " " << visited[visit];//The new node visited in this control is printed to the screen.
                    last = st+1;//The index number of the element in the last visited stack array is assigned to the variable last.
                    //**The purpose here is that a node does not visit its second connection after its first connection,
					//as the nodes in the operation of the DFS algorithm visit the first node to which they are connected,
					//and reach other connections through the connections of the next nodes, if not,
					//or by going backwards in the heap and listing the unvisited nodes. For this reason,
					//we continue the loop from the last variable.
                    
                    goto L1;//Since we must always list the connections by going forward from the starting node in the graph first,
					//to avoid leaving an unvisited node in the forwards, when there is a new node visited,
					//we return to the beginning of the loop to list its connections and add them to the visited ones if they are not visited.
                }
            }
        } 
        //This loop is used to scan backwards through the Stack when there are no unvisited nodes in the forwards.
        for(int i=st; i>=0; i--){//This time we scan backwards from the number of elements in the stack array.
            for(int j=0; j<edge_num; j++){
                if(visited[j] == stack[i]){
                    break;//If the last node in the stack is in the visited array, the loop is exited and the previous node is checked.
                }
                else if(visited[j] == ' '){//If the corresponding element of the visited array is empty,
				//the compared node in the stack array is added to the visited array.
                
                //The following lines of code were used for the same purposes as in the previous loop.
                    visit++;
                    visited[visit] = stack[i];
                    cout << " " << visited[visit];
                    last = st+1;
                    goto L1;
                }
            }
        }
        cout << endl;
}