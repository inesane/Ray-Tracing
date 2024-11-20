#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "rtweekend.h"

#include "hittable.h"

#include <algorithm>

class triangle : public hittable
{
public:
    triangle() {}

    triangle(point3 _p1, point3 _p2, point3 _p3,
        shared_ptr<material> mat)
        : p1(_p1), p2(_p2), p3(_p3), mp(mat){};

    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;

    virtual bool bounding_box(double time0, double time1, aabb &output_box) const override
    {
        vec3 min(fmin(p1.x(), fmin(p2.x(), p3.x())),
                 fmin(p1.y(), fmin(p2.y(), p3.y())),
                 fmin(p1.z(), fmin(p2.z(), p3.z())));

        vec3 max(fmax(p1.x(), fmax(p2.x(), p3.x())),
                 fmax(p1.y(), fmax(p2.y(), p3.y())),
                 fmax(p1.z(), fmax(p2.z(), p3.z())));

        output_box = aabb(min, max);

        return true;
    }

public:
    shared_ptr<material> mp;
    point3 p1, p2, p3;
};


bool triangle::hit(const ray &r, double t_min, double t_max, hit_record &rec) const
{

 
    vec3 p1p2 = p2 - p1;
    vec3 p1p3 = p3 - p1;
 
    vec3 pvec = cross(r.direction(), p1p3);
    double det = dot(p1p2, pvec); 
 
    constexpr double kEpsilon = std::numeric_limits<double>::epsilon();
 
    if (det < kEpsilon)
    {
        return false;
    }
 
    double invDet = 1 / det;
 
    vec3 tvec = r.origin() - p1;
    double u = dot(tvec, pvec) * invDet; 
    if (u < 0 || u > 1)
    {
        return false;
    }
 
    vec3 qvec = cross(tvec, p1p2);     
    double v = dot(r.direction(), qvec) * invDet; 
    if (v < 0 || u + v > 1)
    {
        return false;
    }
 
    double t = dot(p1p3, qvec) * invDet;
 
    if (t < t_min || t_max < t)
    {
        return false;
    }
 
    // Hit Record
    rec.u = u;
    rec.v = v;
    rec.t = t;	
    auto outward_normal = cross(p1p2, p1p3);
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mp;
    rec.p = r.at(t);
 
    return true;
}

#endif