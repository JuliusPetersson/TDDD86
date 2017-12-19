/*
 * TDDD86 Pattern Recognition
 * This program computes and plots all line segments involving 4 points
 * in a file using Qt.
 */

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include "Point.h"
#include <set>
#include <map>
#include <math.h>

// constants
static const int SCENE_WIDTH = 512;
static const int SCENE_HEIGHT = 512;

void render_points(QGraphicsScene* scene, const vector<Point>& points) {
    for(const auto& point : points) {
        point.draw(scene);
    }
}

void render_line(QGraphicsScene* scene, const Point& p1, const Point& p2) {
    p1.lineTo(scene, p2);
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // open file
    string filename = "input200.txt";
    ifstream input;
    input.open(filename);

    // the vector of points
    vector<Point> points;

    // read points from file
    int N;
    int x;
    int y;

    input >> N;

    for (int i = 0; i < N; ++i) {
        input >> x >> y;
        points.push_back(Point(x, y));
    }
    input.close();

    // setup graphical window
    QGraphicsView *view = new QGraphicsView();
    QGraphicsScene *scene = new QGraphicsScene(0, 0, SCENE_WIDTH, SCENE_HEIGHT);
    view->setScene(scene);
    // draw points to screen all at once
    render_points(scene, points);
    view->scale(1, -1); //screen y-axis is inverted
    view->resize(view->sizeHint());
    view->setWindowTitle("Faster than the speed of light");
    view->show();

    // sort points by natural order
    // makes finding endpoints of line segments easy
    sort(points.begin(), points.end());
    auto begin = chrono::high_resolution_clock::now();

    int counter = 0;/*
 * TDDD86 Pattern Recognition
 * This program computes and plots all line segments involving 4 points
 * in a file using Qt.
 */

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include "Point.h"
#include <set>
#include <map>
#include <math.h>

// constants
static const int SCENE_WIDTH = 512;
static const int SCENE_HEIGHT = 512;

void render_points(QGraphicsScene* scene, const vector<Point>& points) {
    for(const auto& point : points) {
        point.draw(scene);
    }
}

void render_line(QGraphicsScene* scene, const Point& p1, const Point& p2) {
    p1.lineTo(scene, p2);
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // open file
    string filename = "input200.txt";
    ifstream input;
    input.open(filename);

    // the vector of points
    vector<Point> points;

    // read points from file
    int N;
    int x;
    int y;

    input >> N;

    for (int i = 0; i < N; ++i) {
        input >> x >> y;
        points.push_back(Point(x, y));
    }
    input.close();

    // setup graphical window
    QGraphicsView *view = new QGraphicsView();
    QGraphicsScene *scene = new QGraphicsScene(0, 0, SCENE_WIDTH, SCENE_HEIGHT);
    view->setScene(scene);
    // draw points to screen all at once
    render_points(scene, points);
    view->scale(1, -1); //screen y-axis is inverted
    view->resize(view->sizeHint());
    view->setWindowTitle("Faster than the speed of light");
    view->show();

    // sort points by natural order
    // makes finding endpoints of line segments easy
    sort(points.begin(), points.end());
    auto begin = chrono::high_resolution_clock::now();

    int counter = 0;

    for (int i = 0; i < N; i++){
        map<double, set<Point>> slopes;
        bool drawn = false;
        for (int k = i ; k < N ; k++){
            double slope = points.at(i).slopeTo(points.at(k));
            slopes[slope].insert(points.at(k));
            if(slopes[slope].size() > 3){
                Point bestDraw = *(slopes[slope].begin());
                if (drawn == false){
                    for (std::set<Point>::iterator it = slopes[slope].begin(); it != slopes[slope].end(); ++it){
                        if(bestDraw < (*it)){
                            bestDraw = (*it);
                        }
                    }
                    render_line(scene, points.at(i), bestDraw);
                    std::cout << points.at(i) << "  andra  punkt" << bestDraw << std::endl;
                    drawn = true;
                    counter++;
                    a.processEvents();
                }

            }else if (slopes[slope].size() > 2){
                render_line(scene, points.at(i), points.at(k));
                counter++;
                a.processEvents();
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();
    cout << "Computing line segments took "
         << std::chrono::duration_cast<chrono::milliseconds>(end - begin).count()
         << " milliseconds." << counter <<endl;

    return a.exec(); // start Qt event loop
}



    for (int i = 0; i < N; i++){
        map<double, set<Point>> slopes;
        bool drawn = false;
        for (int k = i ; k < N ; k++){
            double slope = points.at(i).slopeTo(points.at(k));
            slopes[slope].insert(points.at(k));
            if(slopes[slope].size() > 3){
                Point bestDraw = *(slopes[slope].begin());
                if (drawn == false){
                    for (std::set<Point>::iterator it = slopes[slope].begin(); it != slopes[slope].end(); ++it){
                        if(bestDraw < (*it)){
                            bestDraw = (*it);
                        }
                    }
                    render_line(scene, points.at(i), bestDraw);
                    std::cout << points.at(i) << "  andra  punkt" << bestDraw << std::endl;
                    drawn = true;
                    counter++;
                    a.processEvents();
                }

            }else if (slopes[slope].size() > 2){
                render_line(scene, points.at(i), points.at(k));
                counter++;
                a.processEvents();
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();
    cout << "Computing line segments took "
         << std::chrono::duration_cast<chrono::milliseconds>(end - begin).count()
         << " milliseconds." << counter <<endl;

    return a.exec(); // start Qt event loop
}
