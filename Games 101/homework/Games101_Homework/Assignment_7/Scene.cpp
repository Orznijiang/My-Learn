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
    if (depth > this->maxDepth) {
        return Vector3f(0.0, 0.0, 0.0);
    }
    Intersection intersection = std::move(Scene::intersect(ray));
    Material* m = intersection.m;
    Object* hitObject = intersection.obj;
    Vector3f hitColor = Vector3f(0.0, 0.0, 0.0); // initialization
    Vector2f uv;
    uint32_t index = 0;
    if (intersection.happened) {

        auto saturate = [](auto num)->auto{
            return num > 0 ? num : 0;
        };

        Vector3f hitPoint = intersection.coords;
        Vector3f N = intersection.normal;
        Vector2f st;
        hitObject->getSurfaceProperties(hitPoint, ray.direction, index, uv, N, st);

        if (intersection.m->hasEmission()) {
            return intersection.m->getEmission();
        }

        Intersection light_pos;
        float light_pdf;
        sampleLight(light_pos, light_pdf);

        Vector3f shadow_origin = (dotProduct(ray.direction, N) < 0) ?
            hitPoint + N * EPSILON :
            hitPoint - N * EPSILON;
        Vector3f shadow_dir = std::move((light_pos.coords - hitPoint).normalized());
        // need to judge, because light is also a object in this frame
        auto block_test = Scene::intersect(Ray(shadow_origin, shadow_dir));
        bool isBlocked = block_test.happened && !block_test.m->hasEmission();
        Vector3f L_dir{};
        if (!isBlocked) {
            Vector3f f_r = m->eval(ray.direction, shadow_dir, N);
            float cos_theta = saturate(dotProduct(N, shadow_dir));
            float cos_theta_prime = saturate(dotProduct(light_pos.normal, -shadow_dir));
            float distance2 = pow((light_pos.coords - hitPoint).norm(), 2);
            L_dir = light_pos.emit * f_r * cos_theta * cos_theta_prime / distance2 / light_pdf;
        }
        Vector3f L_indir{};
        float p = get_random_float();
        //std::cout << "p: " << p << std::endl;
        if (p < Scene::RussianRoulette) {
            Vector3f wi_origin = (dotProduct(ray.direction, N) < 0) ?
                hitPoint + N * EPSILON :
                hitPoint - N * EPSILON;
            Vector3f wi = m->sample(ray.direction, N);
            Intersection intersect_wi = Scene::intersect(Ray(wi_origin, wi));
            if (intersect_wi.happened && !intersect_wi.m->hasEmission()) {
                Vector3f f_r = m->eval(ray.direction, wi, N);
                float cos_theta = saturate(dotProduct(N, wi));
                float pdf = m->pdf(ray.direction, wi, N);
                L_indir = castRay(Ray(wi_origin, wi), depth + 1) * f_r * cos_theta / pdf / Scene::RussianRoulette;
            }
        }
        //std::cout << "dir: " << L_dir << "indir: " << L_indir << std::endl;
        //注意pdf接近0的情况，这时候就会引入白色噪点，作业说明里有说的
        return L_dir + L_indir;
    }
    return hitColor;
}