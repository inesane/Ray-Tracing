#include "rtweekend.h"
#include "camera.h"

#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "material.h"
#include <iostream>
#include "aarect.h"
#include "box.h"
#include "aatri.h"
#include <time.h>
#include "bvh.h"
#include "triangle.h"

color ray_color(const ray &r, const color &background, const hittable &world, int depth)
{
    hit_record rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return color(0, 0, 0);
    // std::cerr << "here1" << '\n';

    // If the ray hits nothing, return the background color.
    if (!world.hit(r, 0.001, infinity, rec))
        return background;

    // std::cerr << "here2" << '\n';

    ray scattered;
    color attenuation;
    // std::cerr << rec.u << " " << rec.v << "\n";
    color emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);
    // color emitted = vec3(0.5, 0.5, 0.5);

    if (!rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        return emitted;

    return emitted + attenuation * ray_color(scattered, background, world, depth - 1);
    // return attenuation * ray_color(scattered, background, world, depth-1);
}

// color ray_color(const ray &r, const color &background, const hittable &world, int depth) {
//     hit_record rec;
//     if (world.hit(r, 0, infinity, rec)) {
//         return 0.5 * (rec.normal + color(1,1,1));
//     }
//     vec3 unit_direction = unit_vector(r.direction());
//     auto t = 0.5*(unit_direction.y() + 1.0);
//     return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
// }

hittable_list cornell_box()
{
    hittable_list objects, objects2, objs;

    auto red = make_shared<lambertian>(color(.65, .05, .05));
    auto white = make_shared<lambertian>(color(.5, .5, .5));
    auto green = make_shared<lambertian>(color(.12, .45, .15));
    auto light = make_shared<diffuse_light>(color(15, 15, 15));
    auto col = make_shared<lambertian>(color(.30, .30, .40));
    auto bl = make_shared<lambertian>(color(.1, .1, .1));
    auto wh = make_shared<lambertian>(color(.9, .9, .9));
    auto checker = make_shared<checker_texture>(color(0.2, 0.3, 0.1), color(0.9, 0.9, 0.9));
    auto material_trans = make_shared<dielectric>(1.5);
    auto material_metal = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);

    objects.add(make_shared<yz_rect>(0, 555, 0, 555, 555, green));
    objects.add(make_shared<yz_rect>(0, 555, 0, 555, 0, red));
    objects.add(make_shared<xz_rect>(213, 343, 227, 332, 554, light));
    // objects.add(make_shared<xz_rect>(0, 555, 0, 555, 0, white));

    objects.add(make_shared<xz_rect>(0, 139, 0, 139, 0, bl));
    objects.add(make_shared<xz_rect>(0, 139, 139, 279, 0, wh));
    objects.add(make_shared<xz_rect>(0, 139, 279, 416, 0, bl));
    objects.add(make_shared<xz_rect>(0, 139, 416, 555, 0, wh));
    objects.add(make_shared<xz_rect>(139, 279, 0, 139, 0, wh));
    objects.add(make_shared<xz_rect>(139, 279, 139, 279, 0, bl));
    objects.add(make_shared<xz_rect>(139, 279, 279, 416, 0, wh));
    objects.add(make_shared<xz_rect>(139, 279, 416, 555, 0, bl));
    objects.add(make_shared<xz_rect>(279, 416, 0, 139, 0, bl));
    objects.add(make_shared<xz_rect>(279, 416, 139, 279, 0, wh));
    objects.add(make_shared<xz_rect>(279, 416, 279, 416, 0, bl));
    objects.add(make_shared<xz_rect>(279, 416, 416, 555, 0, wh));
    objects.add(make_shared<xz_rect>(416, 555, 0, 139, 0, wh));
    objects.add(make_shared<xz_rect>(416, 555, 139, 279, 0, bl));
    objects.add(make_shared<xz_rect>(416, 555, 279, 416, 0, wh));
    objects.add(make_shared<xz_rect>(416, 555, 416, 555, 0, bl));

    // objects.add(make_shared<xz_rect>(0, 555, 0, 555, 0, make_shared<lambertian>(checker)));

    objects.add(make_shared<xz_rect>(0, 555, 0, 555, 555, white));
    objects.add(make_shared<xy_rect>(0, 555, 0, 555, 555, white));
    objects.add(make_shared<triangle>(point3(200, 200, 100), point3(300, 0, 150), point3(100, 0, 150), col));
    objects.add(make_shared<triangle>(point3(200, 200, 100), point3(300, 0, 150), point3(200, 0, 50), col));
    objects.add(make_shared<triangle>(point3(200, 200, 100), point3(100, 0, 150), point3(200, 0, 50), col));
    // objects.add(make_shared<triangle>(point3(300, 200, 50), point3(200, 0, 75), point3(300, 0, 25), col));
    // objects.add(make_shared<tri>(point3(0, 0, 0), point3(100, 0, 0), point3(0, 0, 100), col));
    // objects.add(make_shared<tri>(point3(0, 0, 0), point3(100, 0, 0), point3(0, 1000, 0), col));
    // objects.add(make_shared<tri>(point3(100, 0, 0), point3(0, 100, 0), point3(0, 0, 100), col));

    // objects.add(make_shared<box>(point3(130, 0, 65), point3(295, 165, 230), white));

    // objs.add(make_shared<bvh_node>(objects, 0, 1));


    objects.add(make_shared<sphere>(point3(280, 340, 280), 40.0, material_trans));

    objects.add(make_shared<box>(point3(400, 0, 100), point3(550, 140, 370), white));

    // objs.add(make_shared<bvh_node>(objects2, 0, 1));

    // objects.add(make_shared<bvh_node>(objects, 0, 1));

    // objects.add(make_shared<box>(point3(130, 0, 65), point3(295, 165, 230), white));
    // objects.add(make_shared<sphere>(point3(280, 340, 280), 40.0, col));


    return objects;
}

int main()
{

    // Image

    auto aspect_ratio = 16.0 / 9.0;
    int image_width =50;
    int samples_per_pixel = 100;
    const int max_depth = 50;

    // World

    hittable_list world;

    point3 lookfrom;
    point3 lookat;
    auto vfov = 40.0;
    auto aperture = 0.0;
    color background(0, 0, 0);

    world = cornell_box();
    aspect_ratio = 1.0;
    image_width = 600;
    samples_per_pixel = 400;
    background = color(0, 0, 0);
    lookfrom = point3(278, 278, -800);
    lookat = point3(278, 278, 0);
    vfov = 40.0;

    // Camera

    vec3 vup(0, 1, 0);
    auto dist_to_focus = 10.0;
    int image_height = static_cast<int>(image_width / aspect_ratio);

    camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus, 0.0, 1.0);

    // Render

    std::cout << "P3\n"
              << image_width << " " << image_height << "\n255\n";
    clock_t tStart = clock();
    for (int j = image_height - 1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i)
        {
            color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s)
            {
                auto u = (i + random_double()) / (image_width - 1);
                auto v = (j + random_double()) / (image_height - 1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, background, world, max_depth);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }

    std::cerr << "\nDone.\n";
    double val = (clock() - tStart) / CLOCKS_PER_SEC;

    std::cerr << "Time taken: " << val << "s\n";
}