#ifndef CAMERA_H
#define CAMERA_H


class Camera
{
    public:
        Camera();
        float x;
        float y;
        float z;
        float s;
        float t;
        float r;
        void findPointOnSphere(float s, float t, float radius);
        void przesunDoModelu(float s, float t, float r);
    protected:
    private:
};

#endif // CAMERA_H
