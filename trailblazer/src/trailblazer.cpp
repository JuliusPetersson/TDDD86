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
                node->visited = true;
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
    graph.resetData();
    PriorityQueue<Node*> pQue;
    vector<Node *> path;
    pQue.enqueue(start,0);
    start->setColor(GREEN);

    while(!(pQue.isEmpty())){
        Node *minNode = pQue.dequeue();
        if (minNode == end){
            minNode->setColor(GREEN);
            Node* temp = end;
            while(temp != start){
                path.insert(path.begin(), temp);
                temp = temp->previous;
            }
            path.insert(path.begin(), temp);
            temp->setColor(GREEN);

            return path;
        }
        for (Node* neighbour : graph.getNeighbors(minNode)){
            double dist = graph.getArc(minNode,neighbour)->cost + minNode->cost;
            if(!(neighbour->visited)){
                if (neighbour->getColor() != YELLOW){
                    neighbour->cost = dist;
                    pQue.enqueue(neighbour,neighbour->cost);
                    neighbour->previous = minNode;
                    neighbour->setColor(YELLOW);
                }else if(dist < neighbour->cost){
                    neighbour->cost = dist;
                    neighbour->previous = minNode;
                    pQue.changePriority(neighbour, dist);
                }
            }
        }
        minNode->visited = true;
        minNode->setColor(GREEN);
    }
    return path;
}
vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    PriorityQueue<Node*> pQue;
    vector<Node *> path;
    map<Node *, double> aStarScore;
    pQue.enqueue(start,0);
    start->setColor(GREEN);

    while(!(pQue.isEmpty())){
        Node *minNode = pQue.dequeue();
        if (minNode == end){
            minNode->setColor(GREEN);
            Node* temp = end;
            while(temp != start){
                path.insert(path.begin(), temp);
                temp = temp->previous;
            }
            path.insert(path.begin(), temp);
            temp->setColor(GREEN);

            return path;
        }
        for (Node* neighbour : graph.getNeighbors(minNode)){
            double dist = minNode->cost + graph.getArc(minNode, neighbour)->cost;
            if(!(neighbour->visited)){
                if (neighbour->getColor() != YELLOW){
                    neighbour->cost = dist;
                    pQue.enqueue(neighbour,neighbour->cost + neighbour->heuristic(end));
                    neighbour->previous = minNode;
                    neighbour->setColor(YELLOW);
                }else if(dist < neighbour->cost){
                    neighbour->cost = dist;
                    neighbour->previous = minNode;

                    pQue.changePriority(neighbour, dist + neighbour->heuristic(end));
                }
            }
        }
        minNode->visited = true;
        minNode->setColor(GREEN);
    }
    return path;
}
