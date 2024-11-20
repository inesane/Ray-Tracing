#ifndef AATRI_H
#define AATRI_H

#include "rtweekend.h"

#include "hittable.h"

#include <algorithm>

class tri : public hittable
{
public:
    tri() {}

    tri(point3 _p1, point3 _p2, point3 _p3,
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

int SignedVolume(point3 a, point3 b, point3 c, point3 d){
        return (1.0/6.0)*dot(cross(b-a,c-a),d-a);
    }

bool tri::hit(const ray &r, double t_min, double t_max, hit_record &rec) const
{
    point3 q1 = r.at(-10.0);
    point3 q2 = r.at(10.0);


    int a1 = SignedVolume(q1, p1, p2, p3);
    int a2 = SignedVolume(q2, p1, p2, p3);
    int a3 = SignedVolume(q1, q2, p1, p2);
    int a4 = SignedVolume(q1, q2, p2, p3);
    int a5 = SignedVolume(q1, q2, p3, p1);
    
    if(a1*a2 < 0 && ((a3 > 0 && a4 > 0 && a5 > 0) || (a3 < 0 && a4 < 0 && a5 < 0))){
        
        vec3 N = cross(p2-p1, p3-p1);

        double T = -dot(q1-p1,N)/dot(q2-q1,N);

        vec3 min(fmin(p1.x(), fmin(p2.x(), p3.x())),
                 fmin(p1.y(), fmin(p2.y(), p3.y())),
                 fmin(p1.z(), fmin(p2.z(), p3.z())));

        vec3 max(fmax(p1.x(), fmax(p2.x(), p3.x())),
                 fmax(p1.y(), fmax(p2.y(), p3.y())),
                 fmax(p1.z(), fmax(p2.z(), p3.z())));

        auto outward_normal = vec3(0, 0, 1);

        rec.set_face_normal(r, outward_normal);

        rec.p = (q1+T*(q2-q1));
        rec.u = ((q1+T*(q2-q1)).x() - min.x())/(max.x() - min.x());
        rec.v = ((q1+T*(q2-q1)).y() - min.y())/(max.y() - min.y());
        if (rec.u > 1){
            rec.u = 1;
        }
        if (rec.v > 1) {
            rec.v = 1;
        }
        if (rec.u < 0) {
            rec.u = 0;
        }
        if (rec.v < 0) {
            rec.v = 0;
        }
        std::cerr << rec.u << " " << rec.v << "\n";
        rec.t = T;

        return true;
    }
    return false;
    
}

#endif