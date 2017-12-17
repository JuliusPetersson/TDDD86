#include "costs.h"
#include "trailblazer.h"
#include "stack"
#include "iostream"
#include "pqueue.h"
using namespace std;

vector<Node *> helperDepthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    vector<Node*> path;
    start->setColor(GREEN);
    start->visited = true;

    if(start == end){
        path.push_back(start);
    }
    else{
        for (Node* a: graph.getNeighbors(start)){
            if(!(a->visited)){
                a->previous = start;
                path = helperDepthFirstSearch(graph, a, end);

                if (path.size() > 0){
                    path.push_back(start);
                    break;
                }
                else{
                    a->setColor(GRAY);
                }
            }
        }
    }


    return path;

}


vector<Node *> depthFirstSearch(BasicGraph &graph, Vertex *start, Vertex *end){
    graph.resetData();
    return helperDepthFirstSearch(graph, start, end);
}




vector<Node *> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    vector<Vertex*> path;
    return path;
}

void reversePath(Node* start,Node* end,vector<Node*> &reversedPath){
    Node* currNode = end;
    while(currNode != start){
        reversedPath.push_back(currNode);
        currNode = currNode->previous;
    }

    reversedPath.push_back(start);

    for (int i = 0; i < (reversedPath.size()/2); i++){
        Node* first = reversedPath[i];
        Node* second = reversedPath[reversedPath.size() - i];
        reversedPath[i] = second;
        reversedPath[reversedPath.size() - i] = first;
    }
}

vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    vector<Vertex*> path;
    PriorityQueue<Vertex*> prioQue;
    start->cost = 0;

    for (Vertex* i : graph.getNodeSet()){
        if (i != start){
            i->cost = numeric_limits<double>::infinity();
            i->previous = NULL;
        }
        i->setColor(YELLOW);
        prioQue.enqueue(i,i->cost);
    }

    while(prioQue.size() != 0){
        Vertex* minNode = prioQue.dequeue();
        minNode->setColor(GREEN);
        for (Vertex* i : graph.getNeighbors(minNode)){
            Arc* c = graph.getEdge(minNode,i);
            double dist = minNode->cost + c->cost;
            if(i == end){
                i->setColor(GREEN);
                cout << "foo" << endl;
                reversePath(start,end,path);
                return path;
            }
            if (dist < i->cost){
                i->cost = dist;
                i->previous = minNode;
                prioQue.changePriority(i,dist);
            }
        }
    }
    return path;
}

vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    vector<Vertex*> path;
    return path;
}
