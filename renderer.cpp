#include "renderer.h"
#include <qdebug.h>

Renderer* Renderer::_instance = NULL;

Renderer* Renderer::Instance(Render_settings settings_p)
{
    if (_instance == NULL)
        _instance = new Renderer(settings_p);

    return _instance;
}

Renderer::Renderer(Render_settings settings_p) :
    settings(settings_p) { }

Ray Renderer::make_ray(Camera &camera, int x, int y)
{
    int img_width = camera.get_x_resolution();
    int img_height = camera.get_y_resolution();

    glm::vec3 origin = camera.get_position();
    float coeff_right = (x - img_width / 2) * 1.0f;
    coeff_right /= img_width;
    float coeff_up = (y - img_height / 2) * 1.0f;
    coeff_up /= img_height;

    glm::vec3 right = coeff_right * camera.get_half_right();
    glm::vec3 up = coeff_up * camera.get_half_up();

    glm::vec3 plane_point = camera.get_plane_center() + right + up;
    glm::vec3 direction = plane_point - origin;
    direction = glm::normalize(direction);

    return Ray(origin, direction, 1);
}

void Renderer::render_image(World &world, Camera &camera, Tracer &tracer,
                            Ui::MyDialog * ui)
{
    omp_set_dynamic(0);
    omp_set_num_threads(1);

    int i = 0, j = 0;

#pragma omp parallel for firstprivate(j) lastprivate(i)
    for (i = 0; i < camera.get_x_resolution(); i++)
    {
        ui->progressBar->setValue(100*(float)(i+1)/((float)camera.get_x_resolution()));
        for (j = 0; j < camera.get_y_resolution(); j++)
        {
            Ray ray = make_ray(camera, i, j);
            glm::vec3 color = tracer.trace_ray(ray, world, camera);
            camera.set_pixel(i, j, color);
        }
    }
}

void Renderer::save_image(Camera &camera)
{
    int width = camera.get_x_resolution();
    int height = camera.get_y_resolution();

    FreeImage_Initialise();

    FIBITMAP* bitmap = FreeImage_Allocate(width, height, 24);
    RGBQUAD color;

    if (!bitmap)
        exit(1);

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            glm::vec3 pixel = camera.get_pixel(i, j);
            color.rgbRed = pixel.x;
            color.rgbGreen = pixel.y;
            color.rgbBlue = pixel.z;
            FreeImage_SetPixelColor(bitmap, i, j, &color);
        }
    }

    if (FreeImage_Save(FIF_PNG, bitmap, settings.file_name.c_str(), 0))
        std::cout << "Image successfully saved!" << '\n';

    FreeImage_DeInitialise();
}
