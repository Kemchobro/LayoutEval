//
// Created by Vidhatu Patel on 9/22/25.
//

#ifndef WALL_H
#define WALL_H
#include <tuple>
#include <vector>

using namespace std;


class wall {
    private:
    tuple<float, float> start;
    tuple<float, float> end;
    float size;
    float maxDist;

    public:
    vector<float> aLayout;
    vector<float> bLayout;

    wall(tuple<float, float> a, tuple<float, float> b, float wallLength,  float max);
    wall(tuple<float, float> a, tuple<float, float> b,  float max);


    tuple<float, float> interpolate(float t);

    float findDistance(tuple<float, float> a, tuple<float, float> b);

    bool isNearWall(tuple<float, float> c);

    bool segmentsIntersect(tuple<float,float> p1, tuple<float,float> p2,
                                 tuple<float,float> q1, tuple<float,float> q2);


    bool isVisible(tuple<int, int>  c, tuple<float, float>  p);

    float cross(tuple<float, float> a, tuple<float, float> b);

    tuple<float, float> center() const;

    float dot(tuple<float, float> a, tuple<float, float> b);

    tuple<float, float> add(tuple<float, float> a, tuple<float, float> b);
    tuple<float, float> subtract(tuple<float, float> a, tuple<float, float> b);

    tuple<float, float> scale(tuple<float, float> a, float f);

};
#endif //WALL_H
