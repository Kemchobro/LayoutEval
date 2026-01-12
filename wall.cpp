//
// Created by Vidhatu Patel on 9/22/25.
//

#include "wall.h"

#include <iostream>
#include <vector>
#include <tuple>

wall::wall(tuple<float, float> a, tuple<float, float> b, float wallLength, float max) {
    start = a;
    end = b;
    size = wallLength;
    maxDist = max;


}

wall::wall(tuple<float, float> a, tuple<float, float> b, float max) {
    start = a;
    end = b;
    size = sqrt(pow(get<0>(a)-get<0>(b),2) + pow(get<1>(a)-get<1>(b),2));
    maxDist = max;


}

tuple<float, float> wall::interpolate(float t) {
    return make_tuple(get<0>(start) * (1-t) + get<0>(end) * t, get<1>(start) * (1-t) + get<1>(end) * t);
}

float wall::findDistance(tuple<float, float> a, tuple<float, float> b) {
    return static_cast<float> (sqrt(pow(get<0>(b) - get<0>(a), 2) + pow(get<1>(b) - get<1>(a), 2)));
}



    bool wall::isNearWall(tuple<float, float> c) {
        tuple<float, float> a = subtract(end, start);
        tuple<float, float> b = subtract(c, start);
    if (dot(b,b) == 0) {
        return true;
    }
    if (dot(a,a) == 0) return false; // degenerate wall

    float t = dot(a, b) / dot(a,a);  // projection scalar

    // clamp t to [0,1] so it stays on the segment
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;

    auto closest = interpolate(t); // closest point on segment
    float dist = findDistance(c, closest);
    return dist < maxDist;
    }

float wall::dot(tuple<float, float> a, tuple<float, float> b) {
    return get<0>(a) * get<0>(b) + get<1>(a) * get<1>(b);
}


tuple<float, float> wall::add(tuple<float, float> a, tuple<float, float> b) {
    return make_tuple(get<0>(a) + get<0>(b), get<1>(a) + get<1>(b));
}

tuple<float, float> wall::subtract(tuple<float, float> a, tuple<float, float> b) {
    return make_tuple(get<0>(a) - get<0>(b), get<1>(a) - get<1>(b));
}

tuple<float, float> wall::scale(tuple<float, float> a, float f) {
    return make_tuple(get<0>(a) * f, get<1>(a) * f);
}
float wall::cross(tuple<float,float> a, tuple<float,float> b) {
    return get<0>(a)*get<1>(b) - get<1>(a)*get<0>(b);
};

// Returns true if line segments (p1-p2) and (q1-q2) intersect
bool wall::segmentsIntersect(tuple<float,float> p1, tuple<float,float> p2,
                             tuple<float,float> q1, tuple<float,float> q2) {

// vector from point to camera
    tuple<float,float> r = subtract(p2, p1);
    // vector from end to start
    tuple<float,float> s = subtract(q2, q1);
    // vector from start to camera
    tuple<float,float> qp = subtract(q1, p1);

    float rxs = cross(r, s);
    float qpxr = cross(qp, r);

    if (rxs == 0.0f) return false; // parallel lines

    float t = cross(qp, s) / rxs;
    if (1.5f * findDistance(p1, interpolate(t)) <= findDistance(interpolate(t),p2 )) {

        return false;

    }
    float u = qpxr / rxs;

    return (t >= 0 && t <= 1 && u >= 0 && u <= 1);
}

bool wall::isVisible(tuple<int,int> c, tuple<float,float> p) {
    // If any wall intersects the line from camera to point, it's not visible
    if (isNearWall(c)) {
        return true;
    }
        if (segmentsIntersect(c, p, start, end)) return false;

    return true;
}
