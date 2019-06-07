#ifndef PARTICLE_H
#define PARTICLE_H


class particle
{
    public:
        particle();
        virtual ~particle();
    protected:
        bool update();
    private:
        vec3 position;
        vec3 velocity;
        float gravity;
        float lifeLength;
        float rotation;
        float scale;
        float elapsedTime = 0;
};

#endif // PARTICLE_H
