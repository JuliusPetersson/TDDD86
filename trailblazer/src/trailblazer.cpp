#include "costs.h"
#include "trailblazer.h"
#include "stack"
#include "iostream"
#include "algorithm"


#include "pqueue.h"

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

void reversePath(Node* start,Node* end,vector<Node*> &reversedPath){
    Node* currNode = end;
    while(currNode != start){
        reversedPath.push_back(currNode);
        currNode = currNode->previous;
    }

    reversedPath.push_back(start);

    reverse(reversedPath.begin(),reversedPath.end());

}

vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    vector<Vertex*> path;
    PriorityQueue<Vertex*> prioQue;
    start->cost = 0;

    prioQue.enqueue(start,start->cost);
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
        for (Vertex* i : graph.getNeighbors(minNode)){
            double dist = graph.getArc(minNode, i)->cost + i->cost;
            if(i == end){
                end->previous = minNode;
                //ask for cost?!
                i->setColor(GREEN);
                cout << "foo" << endl;
                reversePath(start, end, path);
                return path;
            }
            if (dist < i->cost){
                i->cost = dist;
                i->previous = minNode;
                prioQue.changePriority(i,dist);
            }
        }
        minNode->setColor(GREEN);

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
