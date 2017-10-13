// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"
#include "math.h"

Tour::Tour()
{
    //Node* firstNode = nullptr;

    Point p0(100.0,100.0);
    Point p1(500.0,100.0);
    Point p2(500.0,500.0);
    Point p3(100.0,500.0);

    node3 = new Node(p3);
    node2 = new Node(p2,node3);
    node1 = new Node(p1,node2);
    node0 = new Node(p0,node1);

    //node2->next = node0;
    node3->next = node0;
    firstNode = node0;
}

Tour::~Tour()
{
    delete firstNode;
    delete node0;
    delete node1;
    delete node2;
    delete node3;
}

void Tour::show()
{
    Node* currNode = firstNode->next;

    std::cout << *firstNode << endl;
    while(currNode != firstNode){
        std::cout << *currNode << endl;

        currNode = currNode->next;
    }
}

void Tour::draw(QGraphicsScene *scene)
{
    // TODO: write this member
    Node* currNode = firstNode;
    bool firstTime = true;
    while(currNode != firstNode || firstTime){
        firstTime = false;
        currNode->point.draw(scene);
        currNode->next->point.draw(scene);
        currNode->point.drawTo(currNode->next->point,scene);

        currNode = currNode->next;
    }
}

int Tour::size()
{
    // TODO: write this member    
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

double Tour::distance()
{
    // TODO: write this member
    Node* currNode = firstNode;
    double distance = 0;
    bool firstTime = true;
    while(currNode != firstNode || firstTime){
        firstTime = false;
        double currX = currNode->point.x;
        double currY = currNode->point.y;

        double nextX = currNode->next->point.x;
        double nextY = currNode->next->point.y;

        double valueX = nextX - currX;
        double valueY = nextY - currY;

        distance += hypot(valueX,valueY);

        currNode = currNode->next;
    }


    return distance;
}

void Tour::insertNearest(Point p)
{
    // TODO: write this member
    if(firstNode == nullptr){
        firstNode = new Node(p,nullptr);

    }else{
        Node* currNode = firstNode->next;

        Node* closestNode = nullptr;
        double cloestDistance;

        while(currNode != firstNode){
            double valueX = currNode->point.x - p.x;
            double valueY = currNode->point.y - p.y;

            //Qr warning is wrong, if not set it will not try it since ==nullptr is true!
            if ((closestNode == nullptr) | (hypot(valueX,valueY)< cloestDistance)){
                closestNode = currNode;
            }
            currNode = currNode->next;

        }
    }
}

void Tour::insertSmallest(Point p)
{
    // TODO: write this member
}
