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
        }while((currNode->next != firstNode));

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
        if(counter == (swapNode - 1) || (counter == 0)){
            if((swapNode - 1) != -1){
                //normal case
                newDistance += currNode->point.distanceTo(currNode->next->next->point);

            }else{
                //if swapNode - 1 = 0 need last to be swapped
                Node* tmpCurrNode = firstNode;
                do{
                    tmpCurrNode = tmpCurrNode->next;
                }while((tmpCurrNode->next != firstNode));

                newDistance += tmpCurrNode->point.distanceTo(tmpCurrNode->next->next->point);

            }

        }else if(counter == swapNode){
            newDistance += currNode->point.distanceTo(currNode->next->next->point);
            //since singly linked  list we must take change the next pointer here even though messy
            newDistance += currNode->next->point.distanceTo(currNode->point);

        }else if(counter == (swapNode + 1)){
            //do nothing since done in previous state

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

    }while((currNode != firstNode));

    return newDistance;
}

void Tour::doInterchange(int swapNode){
    Node* currNode = firstNode;
    Node* memNode = nullptr;
    int counter = 0;
    do{
        if(counter == (swapNode - 1)){
            if((swapNode - 1) != -1){
                //normal case
                memNode = currNode->next;
                currNode->next = currNode->next->next;

            }else{
                //if swapNode - 1 = 0 need last to be swapped
                Node* currNode = firstNode->next;
                do{
                    currNode = currNode->next;
                }while(currNode != firstNode->next);
                memNode = currNode->next;
                currNode->next = currNode->next->next;

            }

        }else if(counter == swapNode){
            //since last pointer changed this is now the second pointer to be swapped compaired to the last time order
            memNode->next = currNode->next;
            currNode->next = memNode;

        }
        counter++;
        currNode = currNode->next;


    }while(currNode != firstNode);
}


void Tour::nodeInterchange(){
    for(int i = 0; i < size(); i++){
        double lengthIfSwap = testInterchange(i);
        if((0 < lengthIfSwap) && (lengthIfSwap < distance())){
            //cout << lengthIfSwap << endl;
            doInterchange(i);
        }
    }
}

void unravel(Node* node1, Node* node2){
    Node* curr = node2->next->next;
    Node* old = node2->next;
    Node* next;

    node2->next->next = node1->next;
    node2->next = node1;

    while(old != node1){
        next = curr->next;
        curr->next = old;
        old = curr;
        curr = next;
    }
}

bool noCrossing(Node* node1, Node* node2){
    double lengthBefore = node1->point.distanceTo(node1->next->point) +node2->point.distanceTo(node2->next->point);
    double lengthAfter = node1->point.distanceTo(node2->point) + node1->next->point.distanceTo(node2->next->point);

    if(lengthBefore > lengthAfter){
        unravel(node1, node2);
        return false;
    }
    else{
        return true;
    }
}
void Tour::unravelAll(){
    bool unraveld = true;
    Node* node1;
    Node* node2;




    do{
        //std::cout << i << std::endl;
        unraveld = true;
        node1 = firstNode;
        do{

            //std::cout << "iterating low level" << std::endl;
            node2 = node1->next;
            do{
              //  std::cout << "iterating high level" << std::endl;
                if(node1 != node2){
                    unraveld = unraveld&&noCrossing(node1, node2);

                    //std::cout << unraveld << std::endl;
                }
                node2 = node2->next;
            }while(node2 != firstNode);
            node1 = node1->next;
        }while(node1 != firstNode);
    }while(!unraveld);
}
