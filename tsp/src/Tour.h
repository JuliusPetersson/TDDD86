#ifndef TOUR_H
#define TOUR_H

#include "Node.h"
#include "Point.h"

class Tour {
public:

    /**
     * @brief Tour is a list of points
     */
    Tour();
    ~Tour();
    /**
     * @brief Prints the all the points in the tour in order
     */
    void show() const;
    /**
     * @brief Creates a window to graphicly display the tour
     * @param QTgrapics obejct to draw on/with
     */
    void draw(QGraphicsScene* scene) const;
    /**
     * @brief Walks the list and count the number of points
     * @return Number of points in the tour
     */
    int size() const;
    /**
     * @brief Walks the list and return the distance it "travelled"
     */
    double distance() const;
    /**
     * @brief Insert the point at the closest node
     */
    void insertNearest(Point p);
    /**
     * @brief Insert the point where it would add the leastest distance to the tour
     */
    void insertSmallest(Point p);

    /**
     * @brief nodeInterchange tries all possible combinations of swapping two nodes. Swap if shorter tour. Call on an already existing tour
     *
     */
    void nodeInterchange();

    void unravelAll();


private:
    Node* firstNode;
    double testInterchange(int swapNode);
    void doInterchange(int swapNode);

};

#endif // TOUR_H
