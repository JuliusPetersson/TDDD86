#include "costs.h"
#include "trailblazer.h"
#include "stack"
#include "iostream"
#include "queue"
using namespace std;

vector<Node *> helperDepthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    vector<Node*> path;
    start->setColor(GREEN);
    start->visited = true;

    if(start == end){
        path.push_back(start);
    }
    else{
        for (Node* node: graph.getNeighbors(start)){
            if(!(node->visited)){
                node->previous = start;
                path = helperDepthFirstSearch(graph, node, end);

                if (path.size() > 0){
                    path.insert(path.begin(),start);
                    break;
                }
                else{
                    node->setColor(GRAY);
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
    graph.resetData();
    vector<Node*> path;
    queue<Node*> nodeQueue;
    nodeQueue.push(start);

    while(nodeQueue.size() > 0 && start != end){
        start = nodeQueue.front();
        nodeQueue.pop();

        start->visited = true;
        start->setColor(GREEN);

        for(Node* node : graph.getNeighbors(start)){
            if (!node->visited){
                node->previous = start;
                node->setColor(YELLOW);
                nodeQueue.push(node);
            }
        }
    }

    while(start->previous != nullptr){
        path.insert(path.begin(), start);
        start = start->previous;
    }

    path.insert(path.begin(), start);
    return path;
}

vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
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
