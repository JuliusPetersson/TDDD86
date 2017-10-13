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

    p0 = new Point(100.0,100.0);
    p1 = new Point(500.0,100.0);
    p2 = new Point(500.0,500.0);
    p3 = new Point(100.0,500.0);

    //Point p0(100.0,100.0);

    node3 = new Node(*p3);
    node2 = new Node(*p2,node0);
    node1 = new Node(*p1,node2);
    node0 = new Node(*p0,node1);

    node3->next = node0;
    firstNode = node0;
}

Tour::~Tour()
{
    // TODO: write this member
    delete firstNode;
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
        Node node(p);
    }
}

void Tour::insertSmallest(Point p)
{
    // TODO: write this member
}
