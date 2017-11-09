#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"
#include "math.h"

Tour::Tour()
{
    firstNode = nullptr;
}

Tour::~Tour()
{
    if (firstNode != nullptr){

        Node* currNode = firstNode->next;

        std::cout << *firstNode << endl;
        while(currNode != firstNode){

            Node* tmp = currNode->next;
            delete currNode;
            currNode = tmp;
        }
    }
    delete firstNode;
}

void Tour::show() const
{
    if (firstNode != nullptr){

        Node* currNode = firstNode->next;

        std::cout << *firstNode << endl;
        while(currNode != firstNode){
            std::cout << *currNode << endl;

            currNode = currNode->next;
        }
    }
}

void Tour::draw(QGraphicsScene *scene) const
{
    if (firstNode != nullptr){
        Node* currNode = firstNode;

        do{
            currNode->point.draw(scene);
            currNode->next->point.draw(scene);
            currNode->point.drawTo(currNode->next->point,scene);

            currNode = currNode->next;
        }while(currNode != firstNode);
    }
}

int Tour::size() const
{
    if (firstNode == nullptr){
        return 0;
    }
    Node* currNode = firstNode->next;

    if(currNode == nullptr){
        return 0;
    }

    int size = 1;

    while(currNode != firstNode){
        size++;
        currNode = currNode->next;
    }
    return size;
}

double Tour::distance() const
{
    if (firstNode == nullptr){
        return 0;
    }
    Node* currNode = firstNode;
    double distance = 0;
    do{
        double currX = currNode->point.x;
        double currY = currNode->point.y;

        double nextX = currNode->next->point.x;
        double nextY = currNode->next->point.y;

        double valueX = nextX - currX;
        double valueY = nextY - currY;

        distance += hypot(valueX,valueY);

        currNode = currNode->next;

    }while(currNode != firstNode);

    return distance;
}

void Tour::insertNearest(Point p)
{
    if(firstNode == nullptr){
        firstNode = new Node(p);
        firstNode->next = firstNode;
    }else{
        Node* currNode = firstNode;

        Node* closestNode = firstNode;
        double cloestDistance = 0;

        do{
            double valueX = currNode->point.x - p.x;
            double valueY = currNode->point.y - p.y;

            double currNodeDistance = hypot(valueX,valueY);
            if ((cloestDistance == 0) | (currNodeDistance < cloestDistance)){
                closestNode = currNode;
                cloestDistance = currNodeDistance;
            }
            currNode = currNode->next;

        }while((currNode != firstNode));

        Node* inNode = new Node(p, closestNode->next);
        closestNode->next = inNode;
    }
}


void Tour::insertSmallest(Point p)
{
    if(firstNode == nullptr){
        firstNode = new Node(p,nullptr);
        firstNode->next = firstNode;
    }else{
        Node* currNode = firstNode;

        Node* closestNode = firstNode;
        double leastRaise = 0;

        do{
            double valueX = currNode->point.x - p.x;
            double valueY = currNode->point.y - p.y;

            double nextValueX = currNode->next->point.x - p.x;
            double nextValueY = currNode->next->point.y - p.y;

            double currValueX = currNode->point.x - currNode->next->point.x;
            double currValueY = currNode->point.y - currNode->next->point.y;

            double currNodeRaise = hypot(valueX,valueY) + hypot(nextValueX,nextValueY) - hypot(currValueX,currValueY);
            if ((leastRaise == 0) | (currNodeRaise < leastRaise)){
                closestNode = currNode;
                leastRaise = currNodeRaise;
            }
            currNode = currNode->next;
        }while((currNode != firstNode));

        Node* inNode = new Node(p, closestNode->next);
        closestNode->next = inNode;
    }
}

double Tour::testInterchange(int swapNode){
    if (firstNode == nullptr){
        return 0;
    }
    Node* currNode = firstNode;
    double newDistance = 0;
    int counter = 0;
    do{
        if(counter == (swapNode - 1)){
            if((swapNode - 1) != -1){
                //normal case
            }else{
                //if -1 need last to be swapped
            }
        }else if(counter == swapNode){

        }else if(counter == (swapNode + 1)){

        }else{
            double currX = currNode->point.x;
            double currY = currNode->point.y;

            double nextX = currNode->next->point.x;
            double nextY = currNode->next->point.y;

            double valueX = nextX - currX;
            double valueY = nextY - currY;

            newDistance += hypot(valueX,valueY);
        }
        counter++;
        currNode = currNode->next;

    }while(currNode != firstNode);

    return newDistance;
}

void Tour::nodeInterchange(Point p){
    insertNearest(p);

    for(int i = 0; i < size(); i++){
        testInterchange(i);
    }
    do stuff :
}

