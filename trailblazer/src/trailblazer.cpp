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

vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    PriorityQueue<Vertex*> prioQue;
    start->cost = 0;

    for (Vertex* i : graph.getNodeSet()){
        if (i != start){
            i->cost = numeric_limits<double>::infinity();
            i->previous = NULL;
        }
        prioQue.enqueue(i,i->cost);
    }
    while(prioQue.size() != 0){
        Vertex* minNode = prioQue.front();
        for (Vertex* i : graph.getNeighbors(minNode)){
            Arc* c;
            c->start = i;
            c->finish = minNode;
            double dist = i->cost + c->cost;
    }
    }
    vector<Vertex*> path;
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
