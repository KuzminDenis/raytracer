#include "model.h"

glm::mat4 identityM(1, 0, 0, 0,
                    0, 1, 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1);

Model::Model() : material()
{
    l3ds_file = lib3ds_file_open("models/bunny.3ds");

    model_matrix = identityM;    

    model_invM = glm::inverse(model_matrix);
    model_inv_dirM = model_invM;
}

Model::Model(std::string file_name,
             glm::vec3 scale_p, glm::vec3 rotate_p, glm::vec3 translate_p)
{
    l3ds_file = lib3ds_file_open(file_name.c_str());

    glm::quat q = glm::quat(rotate_p);
    glm::mat4 tmp = glm::toMat4(q);

    tmp = glm::scale(tmp, scale_p);
    model_inv_dirM = glm::inverse(tmp);
    tmp = glm::translate(tmp, translate_p);

    model_matrix = tmp;
    model_invM = glm::inverse(tmp);
}

bool Model::is_intersected(Ray &ray, float max_distance)
{
    glm::vec3 bary_position;

    // translating ray to local coordinates
    glm::vec4 origin4 = glm::vec4(ray.get_origin(), 0) * model_invM;
    glm::vec4 direction4 = glm::vec4(ray.get_direction(), 0) * model_inv_dirM;

    glm::vec3 origin = glm::vec3(origin4.x, origin4.y, origin4.z);
    glm::vec3 direction = glm::vec3(direction4.x, direction4.y, direction4.z);

    for (int i = 0; i < l3ds_file->nmeshes; i++)
    {
        Lib3dsMesh& mesh = *l3ds_file->meshes[i];
        for (int j = 0; j < mesh.nfaces; j++)
        {
            Lib3dsFace& face = mesh.faces[j];

            glm::vec3 point1 = glm::vec3(mesh.vertices[face.index[0]][0],
                                         mesh.vertices[face.index[0]][1],
                                         mesh.vertices[face.index[0]][2]);
            glm::vec3 point2 = glm::vec3(mesh.vertices[face.index[1]][0],
                                         mesh.vertices[face.index[1]][1],
                                         mesh.vertices[face.index[1]][2]);
            glm::vec3 point3 = glm::vec3(mesh.vertices[face.index[2]][0],
                                         mesh.vertices[face.index[2]][1],
                                         mesh.vertices[face.index[2]][2]);

            bool triangle_intersected =
                    glm::intersectRayTriangle(origin, direction,
                                              point1, point2, point3,
                                              bary_position);

            if (triangle_intersected && bary_position.z > 0.001f &&
                bary_position.z < max_distance)
            {
                return true;
            }
        }
    }

    return false;
}

Intersection_info Model::intersection(Ray &ray)
{
    Intersection_info closest_intersection;
    float closest_distance = 999999.0;

    // translating ray to local coordinates
    glm::vec4 origin4 = glm::vec4(ray.get_origin(), 0) * model_invM;
    glm::vec4 direction4 = glm::vec4(ray.get_direction(), 0) * model_inv_dirM;

    glm::vec3 origin = glm::vec3(origin4.x, origin4.y, origin4.z);
    glm::vec3 direction = glm::vec3(direction4.x, direction4.y, direction4.z);

    for (int i = 0; i < l3ds_file->nmeshes; i++)
    {
        Lib3dsMesh& mesh = *l3ds_file->meshes[i];
        for (int j = 0; j < mesh.nfaces; j++)
        {
            Lib3dsFace& face = mesh.faces[j];

            glm::vec3 point1 = glm::vec3(mesh.vertices[face.index[0]][0],
                                         mesh.vertices[face.index[0]][1],
                                         mesh.vertices[face.index[0]][2]);
            glm::vec3 point2 = glm::vec3(mesh.vertices[face.index[1]][0],
                                         mesh.vertices[face.index[1]][1],
                                         mesh.vertices[face.index[1]][2]);
            glm::vec3 point3 = glm::vec3(mesh.vertices[face.index[2]][0],
                                         mesh.vertices[face.index[2]][1],
                                         mesh.vertices[face.index[2]][2]);


            glm::vec3 edge1 = point2 - point1;
            glm::vec3 edge2 = point3 - point1;

            glm::vec3 pvec = glm::cross(direction, edge2);
            float det = glm::dot(edge1, pvec);

            float epsilon = 0.00001;

            if (det > -epsilon && det < epsilon)
                continue;

            float inv_det = 1.0 / det;

            glm::vec3 tvec = origin - point1;

            float u = glm::dot(tvec, pvec) * inv_det;
            if (u < 0.0 || u > 1.0)
                continue;

            glm::vec3 qvec = glm::cross(tvec, edge1);

            float v = glm::dot(direction, qvec) * inv_det;
            if (v < 0.0 || u + v > 1.0)
                continue;

            float distance = glm::dot(edge2, qvec) * inv_det;

            if (distance < closest_distance)
            {
                closest_distance = distance;
                closest_intersection.is_intersected = true;
                closest_intersection.distance = distance;
                closest_intersection.intersection_point =
                        origin +
                        direction * distance;

                typedef float arr3[3];
                arr3 *vertex_normals;
//                face_normals = new arr3[mesh.nfaces];
                vertex_normals = new arr3[3 * mesh.nfaces];

//                lib3ds_mesh_calculate_face_normals(&mesh, face_normals);
                lib3ds_mesh_calculate_vertex_normals(&mesh, vertex_normals);

//                glm::vec3 normal = glm::vec3 ((face_normals[j])[0],
//                                              (face_normals[j])[1],
//                                              (face_normals[j])[2]);

                glm::vec3 n1 = glm::vec3(vertex_normals[3 * j + 0][0],
                                         vertex_normals[3 * j + 0][1],
                                         vertex_normals[3 * j + 0][2]);

                glm::vec3 n2 = glm::vec3(vertex_normals[3 * j + 1][0],
                                         vertex_normals[3 * j + 1][1],
                                         vertex_normals[3 * j + 1][2]);

                glm::vec3 n3 = glm::vec3(vertex_normals[3 * j + 2][0],
                                         vertex_normals[3 * j + 2][1],
                                         vertex_normals[3 * j + 2][2]);

                glm::vec3 E1 = point2 - point1;
                glm::vec3 E2 = point3 - point1;
                glm::vec3 T = origin - point1;
                glm::vec3 D = direction;

                glm::vec3 P = glm::cross(D, E2);
                glm::vec3 Q = glm::cross(T, E1);

                float scalar = glm::dot(P, E1);
                float u = glm::dot(P, T) / scalar;
                float v = glm::dot(Q, D) / scalar;

                glm::vec3 normal = (1 - u - v) * n1 + v * n3 + u * n2;

                closest_intersection.normal = glm::normalize(normal);

                Lib3dsMaterial **materials = l3ds_file->materials;

                Material material;
                material.ambient_color = glm::vec3(255.0 * materials[i]->ambient[0],
                                                   255.0 * materials[i]->ambient[1],
                                                   255.0 * materials[i]->ambient[2]);

                material.diffuse_color = glm::vec3(255.0 * materials[i]->diffuse[0],
                                                   255.0 * materials[i]->diffuse[1],
                                                   255.0 * materials[i]->diffuse[2]);

                material.shiness_color = glm::vec3(255.0 * materials[i]->specular[0],
                                                   255.0 * materials[i]->specular[1],
                                                   255.0 * materials[i]->specular[2]);

                material.shiness_power = materials[i]->shin_strength;

                material.specular_coeff = materials[i]->transparency;

                closest_intersection.material = material;
                delete[] vertex_normals;
            }
        }
    }

    return closest_intersection;
}
