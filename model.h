#ifndef MODEL_H
#define MODEL_H

#include "lib/glm/glm/glm.hpp"
#include "lib/glm/glm/gtx/intersect.hpp"
#include "lib/glm/glm/gtx/quaternion.hpp"
#include "lib/glm/glm/gtc/matrix_transform.hpp"

#include "lib/lib3ds/src/lib3ds.h"
#include "lib/lib3ds/src/lib3ds_impl.h"

#include "types.h"

#include <vector>

#include "scene_object.h"
#include "ray.h"

class Model : public Scene_object
{

    Lib3dsFile *l3ds_file;
    glm::mat4 model_matrix;
    glm::mat4 model_inv_dirM;
    glm::mat4 model_invM;

    Material material;

public:

    Model();
    Model(std::string file_name,
                 glm::vec3 scale_p, glm::vec3 rotate_p, glm::vec3 translate_p);

    bool is_intersected(Ray &ray, float max_distance);
    Intersection_info intersection(Ray &ray);

    ~Model() { lib3ds_file_free(l3ds_file); }
};

#endif // MODEL_H
