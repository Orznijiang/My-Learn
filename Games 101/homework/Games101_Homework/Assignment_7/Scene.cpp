//
// Created by Göksu Güvendiren on 2019-05-14.
//

#include "Scene.hpp"


void Scene::buildBVH() {
    printf(" - Generating BVH...\n\n");
    this->bvh = new BVHAccel(objects, 1, BVHAccel::SplitMethod::NAIVE);
}

Intersection Scene::intersect(const Ray &ray) const
{
    return this->bvh->Intersect(ray);
}

void Scene::sampleLight(Intersection &pos, float &pdf) const
{
    float emit_area_sum = 0;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        if (objects[k]->hasEmit()){
            emit_area_sum += objects[k]->getArea();
        }
    }
    float p = get_random_float() * emit_area_sum;
    emit_area_sum = 0;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        if (objects[k]->hasEmit()){
            emit_area_sum += objects[k]->getArea();
            if (p <= emit_area_sum){
                objects[k]->Sample(pos, pdf);
                break;
            }
        }
    }
}

bool Scene::trace(
        const Ray &ray,
        const std::vector<Object*> &objects,
        float &tNear, uint32_t &index, Object **hitObject)
{
    *hitObject = nullptr;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        float tNearK = kInfinity;
        uint32_t indexK;
        Vector2f uvK;
        if (objects[k]->intersect(ray, tNearK, indexK) && tNearK < tNear) {
            *hitObject = objects[k];
            tNear = tNearK;
            index = indexK;
        }
    }


    return (*hitObject != nullptr);
}

// Implementation of Path Tracing
Vector3f Scene::castRay(const Ray &ray, int depth) const
{
    // TO DO Implement Path Tracing Algorithm here

    Vector3f result = Vector3f{ 0.0,0.0,0.0 };

    Intersection intersection = std::move(Scene::intersect(ray));

    if (intersection.happened) {

        auto saturate = [](auto num)->auto{
            return num > 0 ? num : 0;
        };

        auto mat = intersection.m;

        if (mat->hasEmission() && depth == 0) {
            return mat->getEmission();
        }

        Intersection light_pos;
        float light_pdf;
        sampleLight(light_pos, light_pdf);

        Vector3f p = intersection.coords;
        Vector3f N = intersection.normal;
        Vector3f wo = ray.direction;        // view to p

        Vector3f x = light_pos.coords;
        Vector3f NN = light_pos.normal;
        Vector3f ws = (p - x).normalized(); // light to p
        
        Vector3f block_test_origin = (dotProduct(wo, N) < 0) ? p + N * EPSILON : p - N * EPSILON;
        auto block_test = Scene::intersect(Ray(block_test_origin, -ws));
        // need to judge, because light is also a object in this frame
        bool isBlocked = block_test.happened && !block_test.m->hasEmission();

        Vector3f L_dir{ 0.0 };
        if (!isBlocked) {
            Vector3f f_r = mat->eval(wo, -ws, N);
            float cos_theta = saturate(dotProduct(N, -ws));
            float cos_theta_prime = saturate(dotProduct(NN, ws));
            float distance2 = pow((x - p).norm(), 2);
            L_dir = light_pos.emit * f_r * cos_theta * cos_theta_prime / distance2 / light_pdf;
        }
        Vector3f L_indir{ 0.0 };
        if (get_random_float() < Scene::RussianRoulette) {
            Vector3f wi = mat->sample(wo, N).normalized();
            Intersection intersect_wi = Scene::intersect(Ray(block_test_origin, wi));
            if (intersect_wi.happened && !intersect_wi.m->hasEmission()) {
                Vector3f f_r = mat->eval(wo, wi, N);
                float cos_theta = saturate(dotProduct(N, wi));
                float pdf = mat->pdf(wo, wi, N);
                L_indir = castRay(Ray(block_test_origin, wi), depth + 1) * f_r * cos_theta / pdf / Scene::RussianRoulette;
            }
        }
        //std::cout << "dir: " << L_dir << "indir: " << L_indir << std::endl;
        result = L_dir + L_indir;
    }
    return result;
}