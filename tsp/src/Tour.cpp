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
    firstNode = nullptr;
}

Tour::~Tour()
{
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
    if(firstNode == nullptr){
        firstNode = new Node(p);
        firstNode->next = firstNode;
    }else{
            Node* currNode = firstNode;

            Node* closestNode = firstNode;
            double cloestDistance = 0;

            bool firstTime = true;
            while((currNode != firstNode) | firstTime){
                firstTime = false;
                double valueX = currNode->point.x - p.x;
                double valueY = currNode->point.y - p.y;

                double currNodeDistance = hypot(valueX,valueY);
                if ((cloestDistance == 0) | (currNodeDistance < cloestDistance)){
                    closestNode = currNode;
                    cloestDistance = currNodeDistance;
                }
                currNode = currNode->next;

            }
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

            bool firstTime = true;
            while((currNode != firstNode) | firstTime){
                firstTime = false;
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

            }
            Node* inNode = new Node(p, closestNode->next);
            closestNode->next = inNode;
        }
    }

