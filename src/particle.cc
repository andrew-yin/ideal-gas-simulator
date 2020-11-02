#include <particle.h>

namespace idealgas {

Particle::Particle()
    : mass_(1), radius_(1), position_(50, 50), velocity_(1, 3) {
}

Particle::Particle(double mass, double radius, const glm::vec2& position,
                   const glm::vec2& velocity)
    : mass_(mass), radius_(radius), position_(position), velocity_(velocity) {
}

}  // namespace idealgas
