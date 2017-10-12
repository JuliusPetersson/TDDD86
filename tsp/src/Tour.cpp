// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"

Tour::Tour()
{
    //Node* firstNode = nullptr;

    Point p0(100.0,100.0);
    Point p1(500.0,100.0);
    Point p2(500.0,500.0);
    Point p3(100.0,100.0);

    Node node3(p3);
    Node node2(p2,&node3);
    Node node1(p1,&node2);
    Node node0(p0,&node1);

    node3.next = &node0;
    std::cout << *(node3.next)<< endl;
    Node* firstNode = &node0;
}

Tour::~Tour()
{
    // TODO: write this member
    delete firstNode;
}

void Tour::show()
{
    // TODO: write this member

    Node* currNode = firstNode->next;

    std::cout << &firstNode << endl;
    while(currNode != firstNode){
        std::cout << "start while" << endl;

        std::cout << &currNode << endl;
        std::cout << "middle while" << endl;
        currNode = currNode->next;
        std::cout << "about to crash" << endl;
    }
    std::cout << &firstNode << endl;

}

void Tour::draw(QGraphicsScene *scene)
{
    // TODO: write this member
}

int Tour::size()
{
    // TODO: write this member
}

double Tour::distance()
{
    // TODO: write this member
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
