#include "costs.h"
#include "trailblazer.h"
#include "stack"
#include "iostream"
using namespace std;


vector<Node *> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();

    stack<Vertex*> s, currPath;
    vector<Vertex*> path;

    s.push(start);
    while(s.size() != 0){
        start = s.top();
        s.pop();
        Color c = start->getColor();
        start->setColor(GREEN);

        if(!start->visited){
            currPath.push(start);
            start->visited = true;
            for (Arc* i:start->arcs){
                i->finish->setColor(YELLOW);
                s.push(i->finish);
            }
        }
        else{
            currPath.pop();
            start->setColor(GRAY);
        }
    }
}


/*
vector<Node *> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    vector<Vertex*> path;
    start->visited = true;
    start->setColor(YELLOW);
    if(start == end){
        path.push_back(start);
        return path;
    }
    for (Arc* i:start->arcs){
        if (!(i->finish->visited)){
            path = depthFirstSearch(graph,i->finish,end);
            cout << path.size() << endl;
            if(path.size() != 0){
                path.push_back(start);
                start->setColor(GREEN);
            }else{
                start->setColor(GRAY);
            }

        }
    }
    return path;
}
*/

vector<Node *> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    vector<Vertex*> path;
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
