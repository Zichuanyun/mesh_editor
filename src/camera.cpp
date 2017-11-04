#include "camera.h"

#include <la.h>
#include <iostream>


using namespace glm;

Camera::Camera():
    Camera(400, 400)
{
    look = glm::vec3(0,0,-1);
    up = glm::vec3(0,1,0);
    right = glm::vec3(1,0,0);
}

Camera::Camera(unsigned int w, unsigned int h):
    Camera(w, h, glm::vec3(0,0,10), glm::vec3(0,0,0), glm::vec3(0,1,0))
{}

Camera::Camera(unsigned int w, unsigned int h, const glm::vec3 &e, const glm::vec3 &r, const glm::vec3 &worldUp):
    fovy(45),
    width(w),
    height(h),
    near_clip(0.1f),
    far_clip(1000),
    eye(e),
    ref(r),
    world_up(worldUp),
    theta(0),
    phi(0)
{
    RecomputeAttributes();
}

Camera::Camera(const Camera &c):
    fovy(c.fovy),
    width(c.width),
    height(c.height),
    near_clip(c.near_clip),
    far_clip(c.far_clip),
    aspect(c.aspect),
    eye(c.eye),
    ref(c.ref),
    look(c.look),
    up(c.up),
    right(c.right),
    world_up(c.world_up),
    V(c.V),
    H(c.H),
    theta(0),
    phi(0)
{}



//Modify here
void Camera::RecomputeAttributes()
{
    float dis = distance(vec3(ref), vec3(eye));
    float y = ref.y + sin(phi) * dis;
    float x = ref.x + cos(phi) * dis * sin(theta);
    float z = ref.z + cos(phi) * dis * cos(theta);

    eye = vec3(x, y, z);

    look = glm::normalize(ref - eye);
    right = glm::normalize(glm::cross(look, world_up));
    up = glm::cross(right, look);

    float tan_fovy = tan(glm::radians(fovy/2));
    float len = glm::length(ref - eye);
    aspect = width/height;
    V = up*len*tan_fovy;
    H = right*len*aspect*tan_fovy;
}

glm::mat4 Camera::getViewProj()
{
    return glm::perspective(glm::radians(fovy), width / (float)height, near_clip, far_clip) * glm::lookAt(eye, ref, up); //get view
}

//change eye and ref
void Camera::RotateAboutUp(float deg)
{
//#define NOPE
#ifdef NOPE
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(deg), up);

    ref = glm::vec3(rotation * glm::vec4(ref, 1));
    ref = ref + eye;
#endif
    theta -= deg * pi<float>() / 180.0;
    if(theta < -pi<float>() * 2) {
        theta += pi<float>() * 2;
    }
    if(theta > pi<float>() * 2) {
        theta -= pi<float>() * 2;
    }
    RecomputeAttributes();
}

void Camera::RotateAboutRight(float deg)
{
    //#define NOPE
#ifdef NOPE
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(deg), right);
    ref = ref - eye;
    ref = glm::vec3(rotation * glm::vec4(ref, 1));
    ref = ref + eye;
#endif
    phi -= deg * pi<float>() / 180.0;

    if(phi < -pi<float>() * 0.5) {
        phi = -pi<float>() * 0.5 * 0.999;
    }

    if(phi > pi<float>() * 0.5) {
        phi = pi<float>() * 0.5 * 0.999;
    }

    RecomputeAttributes();
}

//No need to change
void Camera::TranslateAlongLook(float amt)
{
    glm::vec3 translation = look * amt;
    eye += translation;
//#define NOPE
#ifdef NOPE
    ref += translation;
#endif
}

void Camera::TranslateAlongRight(float amt)
{
    glm::vec3 translation = right * amt;
    eye += translation;
    ref += translation;
}
void Camera::TranslateAlongUp(float amt)
{
    glm::vec3 translation = up * amt;
    eye += translation;
    ref += translation;
}
