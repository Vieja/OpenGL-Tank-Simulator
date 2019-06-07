#include "particle.h"

particle::particle(vec3 position, vec3 velocity, float life)
{
    this.position = position;
    this.velocity = velocity;
    this.life = life;
}

bool update(double frameTime) {
    velocity[1] += gravity * frameTime;
    vec3 change = new vec3(velocity);
}

particle::~particle()
{
    //dtor
}
