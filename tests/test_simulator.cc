#include <core/simulator.h>

#include <catch2/catch.hpp>

using namespace idealgas;

TEST_CASE("AddParticle functionality") {
  Simulator simulator;

  SECTION("Add one particle") {
    Particle p(1, 1, glm::vec2(1, 1), glm::vec2(1, 1));
    simulator.AddParticle(p);
    std::vector<Particle> particles = simulator.GetParticles();

    REQUIRE(p == particles[0]);
  }

  SECTION("Add two particles") {
    Particle p1(1, 1, glm::vec2(1, 1), glm::vec2(1, 1));
    Particle p2(2, 1, glm::vec2(2, 2), glm::vec2(2, 2));
    simulator.AddParticle(p1);
    simulator.AddParticle(p2);
    std::vector<Particle> particles = simulator.GetParticles();

    REQUIRE(p1 == particles[0]);
    REQUIRE(p2 == particles[1]);
  }
}

TEST_CASE("AddRandomParticle functionality") {
  Simulator simulator;

  SECTION("Add a single random particle") {
    simulator.AddRandomParticle();

    std::vector<Particle> particles = simulator.GetParticles();
    REQUIRE(particles.size() == 1);
  }

  SECTION("Add two random particles") {
    simulator.AddRandomParticle();
    simulator.AddRandomParticle();

    std::vector<Particle> particles = simulator.GetParticles();
    REQUIRE(particles.size() == 2);
  }

  SECTION("Add multiple random particles") {
    size_t n = 10;
    for (size_t i = 0; i < 10; i++) {
      simulator.AddRandomParticle();
    }

    std::vector<Particle> particles = simulator.GetParticles();
    REQUIRE(particles.size() == n);
  }
}

TEST_CASE("Reset functionality") {
  Simulator simulator;

  /*
   * Simulator should be empty of particles no matter how many particles are
   * added to it
   */
  SECTION("Empty simulator") {
    simulator.Reset();
    REQUIRE(simulator.GetParticles().empty());
  }

  SECTION("Simulator with one particle") {
    simulator.AddRandomParticle();
    simulator.Reset();
    REQUIRE(simulator.GetParticles().empty());
  }

  SECTION("Simulator with multiple particles") {
    for (size_t i = 0; i < 10; i++) {
      simulator.AddRandomParticle();
    }
    simulator.Reset();
    REQUIRE(simulator.GetParticles().empty());
  }
}

TEST_CASE("Update functionality") {
  Simulator simulator;

  /*********************************
   * Test particle-wall collisions *
   *********************************/

  /* X-component should invert signs */
  SECTION("Particle moves towards and collides with left wall") {
    Particle particle(1, 1, glm::vec2(1, 50), glm::vec2(-1, 5));
    simulator.AddParticle(particle);

    simulator.Update();
    std::vector<Particle> particles = simulator.GetParticles();

    REQUIRE(particles[0].GetVelocity() == glm::vec2(1, 5));
  }

  SECTION("Particle moves towards and collides with right wall") {
    Particle particle(1, 1, glm::vec2(99, 50), glm::vec2(2, -7));
    simulator.AddParticle(particle);

    simulator.Update();
    std::vector<Particle> particles = simulator.GetParticles();

    REQUIRE(particles[0].GetVelocity() == glm::vec2(-2, -7));
  }

  /* Y-component should invert signs */
  SECTION("Particle moves towards and collides with top wall") {
    Particle particle(1, 1, glm::vec2(25, 99), glm::vec2(-1, 9));
    simulator.AddParticle(particle);

    simulator.Update();
    std::vector<Particle> particles = simulator.GetParticles();

    REQUIRE(particles[0].GetVelocity() == glm::vec2(-1, -9));
  }

  SECTION("Particle moves towards and collides with bottom wall") {
    Particle particle(1, 1, glm::vec2(34, 0.75), glm::vec2(-5, -3));
    simulator.AddParticle(particle);

    simulator.Update();
    std::vector<Particle> particles = simulator.GetParticles();

    REQUIRE(particles[0].GetVelocity() == glm::vec2(-5, 3));
  }

  /* Both components should invert signs */
  SECTION("Particle moves towards and collides with top-left corner") {
    Particle particle(1, 1, glm::vec2(1, 99), glm::vec2(-1, 1));
    simulator.AddParticle(particle);

    simulator.Update();
    std::vector<Particle> particles = simulator.GetParticles();

    REQUIRE(particles[0].GetVelocity() == glm::vec2(1, -1));
  }

  SECTION("Particle moves towards and collides with top-right corner") {
    Particle particle(1, 1, glm::vec2(99, 99), glm::vec2(1, 1));
    simulator.AddParticle(particle);

    simulator.Update();
    std::vector<Particle> particles = simulator.GetParticles();

    REQUIRE(particles[0].GetVelocity() == glm::vec2(-1, -1));
  }

  SECTION("Particle moves towards and collides with bottom-left corner") {
    Particle particle(1, 1, glm::vec2(1, 1), glm::vec2(-1, -1));
    simulator.AddParticle(particle);

    simulator.Update();
    std::vector<Particle> particles = simulator.GetParticles();

    REQUIRE(particles[0].GetVelocity() == glm::vec2(1, 1));
  }

  SECTION("Particle moves towards and collides with bottom-right corner") {
    Particle particle(1, 1, glm::vec2(99, 1), glm::vec2(1, -1));
    simulator.AddParticle(particle);

    simulator.Update();
    std::vector<Particle> particles = simulator.GetParticles();

    REQUIRE(particles[0].GetVelocity() == glm::vec2(-1, 1));
  }

  /**
   * Since the particle is not moving towards the wall, the velocity should
   * remain the same for all
   */
  SECTION("Particle moves away but in contact with left wall") {
    Particle particle(1, 1, glm::vec2(1, 50), glm::vec2(1, 5));
    simulator.AddParticle(particle);

    simulator.Update();
    std::vector<Particle> particles = simulator.GetParticles();

    REQUIRE(particles[0].GetVelocity() == glm::vec2(1, 5));
  }

  SECTION("Particle moves away but in contact with right wall") {
    Particle particle(1, 1, glm::vec2(99, 50), glm::vec2(-2, -7));
    simulator.AddParticle(particle);

    simulator.Update();
    std::vector<Particle> particles = simulator.GetParticles();

    REQUIRE(particles[0].GetVelocity() == glm::vec2(-2, -7));
  }

  SECTION("Particle moves away but in contact with top wall") {
    Particle particle(1, 1, glm::vec2(25, 99), glm::vec2(-1, -9));
    simulator.AddParticle(particle);

    simulator.Update();
    std::vector<Particle> particles = simulator.GetParticles();

    REQUIRE(particles[0].GetVelocity() == glm::vec2(-1, -9));
  }

  SECTION("Particle moves away but in contact with bottom wall") {
    Particle particle(1, 1, glm::vec2(34, 0.75), glm::vec2(-5, 3));
    simulator.AddParticle(particle);

    simulator.Update();
    std::vector<Particle> particles = simulator.GetParticles();

    REQUIRE(particles[0].GetVelocity() == glm::vec2(-5, 3));
  }

  SECTION("Particle moves away but in contact with top-left corner") {
    Particle particle(1, 1, glm::vec2(1, 99), glm::vec2(1, -1));
    simulator.AddParticle(particle);

    simulator.Update();
    std::vector<Particle> particles = simulator.GetParticles();

    REQUIRE(particles[0].GetVelocity() == glm::vec2(1, -1));
  }

  SECTION("Particle moves away but in contact with top-right wall") {
    Particle particle(1, 1, glm::vec2(99, 99), glm::vec2(-1, -1));
    simulator.AddParticle(particle);

    simulator.Update();
    std::vector<Particle> particles = simulator.GetParticles();

    REQUIRE(particles[0].GetVelocity() == glm::vec2(-1, -1));
  }

  SECTION("Particle moves away but in contact with bottom-left wall") {
    Particle particle(1, 1, glm::vec2(1, 1), glm::vec2(1, 1));
    simulator.AddParticle(particle);

    simulator.Update();
    std::vector<Particle> particles = simulator.GetParticles();

    REQUIRE(particles[0].GetVelocity() == glm::vec2(1, 1));
  }

  SECTION("Particle moves away but in contact with bottom-right wall") {
    Particle particle(1, 1, glm::vec2(99, 1), glm::vec2(-1, 1));
    simulator.AddParticle(particle);

    simulator.Update();
    std::vector<Particle> particles = simulator.GetParticles();

    REQUIRE(particles[0].GetVelocity() == glm::vec2(-1, 1));
  }

  /*************************************
   * Test particle-particle collisions *
   *************************************/

  /* Particles should swap velocities in elastic collision */
  SECTION("Particles moving directly towards each other") {
    Particle p1(1, 1, glm::vec2(30, 51), glm::vec2(0, 1));
    Particle p2(1, 1, glm::vec2(30, 53), glm::vec2(0, -1));
    simulator.AddParticle(p1);
    simulator.AddParticle(p2);

    simulator.Update();
    std::vector<Particle> particles = simulator.GetParticles();

    REQUIRE(particles[0].GetVelocity() == glm::vec2(0, -1));
    REQUIRE(particles[1].GetVelocity() == glm::vec2(0, 1));
  }

  SECTION("Particles moving in the exact same direction") {
    Particle p1(1, 1, glm::vec2(22, 53), glm::vec2(5, 0));
    Particle p2(1, 1, glm::vec2(24, 53), glm::vec2(2, 0));
    simulator.AddParticle(p1);
    simulator.AddParticle(p2);

    simulator.Update();
    std::vector<Particle> particles = simulator.GetParticles();

    REQUIRE(particles[0].GetVelocity() == glm::vec2(2, 0));
    REQUIRE(particles[1].GetVelocity() == glm::vec2(5, 0));
  }

  /* Particles should swap y-components */
  SECTION("Particles moving towards each other in a glancing collision") {
    Particle p1(1, 1, glm::vec2(30, 51), glm::vec2(1, 4));
    Particle p2(1, 1, glm::vec2(30, 53), glm::vec2(-2, -5));
    simulator.AddParticle(p1);
    simulator.AddParticle(p2);

    simulator.Update();
    std::vector<Particle> particles = simulator.GetParticles();

    REQUIRE(particles[0].GetVelocity() == glm::vec2(1, -5));
    REQUIRE(particles[1].GetVelocity() == glm::vec2(-2, 4));
  }

  /* Particles should swap x-components */
  SECTION("Particles moving in the same direction in a glancing collision") {
    Particle p1(1, 1, glm::vec2(22, 53), glm::vec2(7, 1));
    Particle p2(1, 1, glm::vec2(24, 53), glm::vec2(3, -3));
    simulator.AddParticle(p1);
    simulator.AddParticle(p2);

    simulator.Update();
    std::vector<Particle> particles = simulator.GetParticles();

    REQUIRE(particles[0].GetVelocity() == glm::vec2(3, 1));
    REQUIRE(particles[1].GetVelocity() == glm::vec2(7, -3));
  }

  /* Particle velocities should not change */
  SECTION("Particles in contact but moving away from each other") {
    Particle p1(1, 1, glm::vec2(30, 51), glm::vec2(0, -3));
    Particle p2(1, 1, glm::vec2(30, 53), glm::vec2(0, 4));
    simulator.AddParticle(p1);
    simulator.AddParticle(p2);

    simulator.Update();
    std::vector<Particle> particles = simulator.GetParticles();

    REQUIRE(particles[0].GetVelocity() == p1.GetVelocity());
    REQUIRE(particles[1].GetVelocity() == p2.GetVelocity());
  }

  SECTION("Particles contact, move in the same direction, but don't collide") {
    /**
     * This edge case happens when the particle "behind" the other particle is
     * traveling slower, so they will never be in contact again
     */
    Particle p1(1, 1, glm::vec2(22, 53), glm::vec2(2, 1));
    Particle p2(1, 1, glm::vec2(24, 53), glm::vec2(7, -3));
    simulator.AddParticle(p1);
    simulator.AddParticle(p2);

    simulator.Update();
    std::vector<Particle> particles = simulator.GetParticles();

    REQUIRE(particles[0].GetVelocity() == p1.GetVelocity());
    REQUIRE(particles[1].GetVelocity() == p2.GetVelocity());
  }

  /************************************************************
   * Test to ensure that particle positions are being updated *
   ************************************************************/
  SECTION("A singleton particle's position is updated correctly") {
    Particle p1(1, 1, glm::vec2(22, 53), glm::vec2(2, 1));
    simulator.AddParticle(p1);

    simulator.Update();
    std::vector<Particle> particles = simulator.GetParticles();

    REQUIRE(particles[0].GetPosition() == p1.GetPosition() + p1.GetVelocity());
  }

  SECTION("Multiple particles' positions are updated correctly") {
    std::vector<Particle> org_particles;
    org_particles.push_back(Particle(1, 1, glm::vec2(22, 53), glm::vec2(2, 1)));
    org_particles.push_back(Particle(1, 1, glm::vec2(3, 7), glm::vec2(7, 4)));
    org_particles.push_back(Particle(1, 1, glm::vec2(22, 3.4), glm::vec2(-2, 10)));
    org_particles.push_back(Particle(1, 1, glm::vec2(2.2, 9), glm::vec2(5, -1)));
    org_particles.push_back(Particle(1, 1, glm::vec2(7, 3), glm::vec2(2.1, -8.3)));

    for (const Particle& p : org_particles) {
      simulator.AddParticle(p);
    }
    simulator.Update();

    /* Require all particles were updated properly */
    std::vector<Particle> particles = simulator.GetParticles();
    for (size_t i = 0; i < org_particles.size(); i++) {
      REQUIRE(particles[i].GetPosition() ==
              org_particles[i].GetPosition() + org_particles[i].GetVelocity());
    }
  }
}