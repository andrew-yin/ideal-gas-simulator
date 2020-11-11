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
    simulator.AddRandomSmallParticle();

    std::vector<Particle> particles = simulator.GetParticles();
    REQUIRE(particles.size() == 1);
  }

  SECTION("Add two random particles") {
    simulator.AddRandomSmallParticle();
    simulator.AddRandomSmallParticle();

    std::vector<Particle> particles = simulator.GetParticles();
    REQUIRE(particles.size() == 2);
  }

  SECTION("Add multiple random particles") {
    size_t n = 10;
    for (size_t i = 0; i < 10; i++) {
      simulator.AddRandomSmallParticle();
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
    simulator.AddRandomSmallParticle();
    simulator.Reset();
    REQUIRE(simulator.GetParticles().empty());
  }

  SECTION("Simulator with multiple particles") {
    for (size_t i = 0; i < 10; i++) {
      simulator.AddRandomSmallParticle();
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
    org_particles.push_back(
        Particle(1, 1, glm::vec2(22, 3.4), glm::vec2(-2, 10)));
    org_particles.push_back(
        Particle(1, 1, glm::vec2(2.2, 9), glm::vec2(5, -1)));
    org_particles.push_back(
        Particle(1, 1, glm::vec2(7, 3), glm::vec2(2.1, -8.3)));

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

  /************************************************************
   * Tests that collisions can be detected in simulation with *
   *                more than two particles                   *
   *      (Repeat tests above with additional particle)       *
   ************************************************************/

  SECTION("Particles moving directly towards each other, one uninvolved") {
    Particle p1(1, 1, glm::vec2(30, 51), glm::vec2(0, 1));
    Particle p2(1, 1, glm::vec2(30, 53), glm::vec2(0, -1));
    Particle p3(1, 1, glm::vec2(2, 2), glm::vec2(1, 1));
    simulator.AddParticle(p1);
    simulator.AddParticle(p2);
    simulator.AddParticle(p3);

    simulator.Update();
    std::vector<Particle> particles = simulator.GetParticles();

    REQUIRE(particles[0].GetVelocity() == glm::vec2(0, -1));
    REQUIRE(particles[1].GetVelocity() == glm::vec2(0, 1));
    REQUIRE(particles[2].GetVelocity() == p3.GetVelocity());
  }

  SECTION("Particles moving in the exact same direction, one uninvolved") {
    Particle p1(1, 1, glm::vec2(22, 53), glm::vec2(5, 0));
    Particle p2(1, 1, glm::vec2(24, 53), glm::vec2(2, 0));
    Particle p3(1, 1, glm::vec2(97, 97), glm::vec2(1, 1));
    simulator.AddParticle(p1);
    simulator.AddParticle(p2);
    simulator.AddParticle(p3);

    simulator.Update();
    std::vector<Particle> particles = simulator.GetParticles();

    REQUIRE(particles[0].GetVelocity() == glm::vec2(2, 0));
    REQUIRE(particles[1].GetVelocity() == glm::vec2(5, 0));
    REQUIRE(particles[2].GetVelocity() == p3.GetVelocity());
  }

  SECTION(
      "Particles moving towards each other in a glancing collision, one "
      "uninvolved") {
    Particle p1(1, 1, glm::vec2(30, 51), glm::vec2(1, 4));
    Particle p2(1, 1, glm::vec2(30, 53), glm::vec2(-2, -5));
    Particle p3(1, 1, glm::vec2(97, 97), glm::vec2(1, 1));
    simulator.AddParticle(p1);
    simulator.AddParticle(p2);
    simulator.AddParticle(p3);

    simulator.Update();
    std::vector<Particle> particles = simulator.GetParticles();

    REQUIRE(particles[0].GetVelocity() == glm::vec2(1, -5));
    REQUIRE(particles[1].GetVelocity() == glm::vec2(-2, 4));
    REQUIRE(particles[2].GetVelocity() == p3.GetVelocity());
  }

  SECTION(
      "Particles moving in the same direction in a glancing collision, one "
      "uninvolved") {
    Particle p1(1, 1, glm::vec2(22, 53), glm::vec2(7, 1));
    Particle p2(1, 1, glm::vec2(24, 53), glm::vec2(3, -3));
    Particle p3(1, 1, glm::vec2(75, 24), glm::vec2(0, 0));
    simulator.AddParticle(p1);
    simulator.AddParticle(p2);
    simulator.AddParticle(p3);

    simulator.Update();
    std::vector<Particle> particles = simulator.GetParticles();

    REQUIRE(particles[0].GetVelocity() == glm::vec2(3, 1));
    REQUIRE(particles[1].GetVelocity() == glm::vec2(7, -3));
    REQUIRE(particles[2].GetVelocity() == p3.GetVelocity());
  }

  SECTION(
      "Particles in contact but moving away from each other, one uninvolved") {
    Particle p1(1, 1, glm::vec2(30, 51), glm::vec2(0, -3));
    Particle p2(1, 1, glm::vec2(30, 53), glm::vec2(0, 4));
    Particle p3(1, 1, glm::vec2(7, 97), glm::vec2(4, -2));
    simulator.AddParticle(p1);
    simulator.AddParticle(p2);
    simulator.AddParticle(p3);

    simulator.Update();
    std::vector<Particle> particles = simulator.GetParticles();

    REQUIRE(particles[0].GetVelocity() == p1.GetVelocity());
    REQUIRE(particles[1].GetVelocity() == p2.GetVelocity());
    REQUIRE(particles[2].GetVelocity() == p3.GetVelocity());
  }

  SECTION(
      "Particles contact, move in the same direction, but don't collide, one "
      "uninvolved") {
    Particle p1(1, 1, glm::vec2(22, 53), glm::vec2(2, 1));
    Particle p2(1, 1, glm::vec2(24, 53), glm::vec2(7, -3));
    Particle p3(1, 1, glm::vec2(98, 97), glm::vec2(-1, -1));
    simulator.AddParticle(p1);
    simulator.AddParticle(p2);
    simulator.AddParticle(p3);

    simulator.Update();
    std::vector<Particle> particles = simulator.GetParticles();

    REQUIRE(particles[0].GetVelocity() == p1.GetVelocity());
    REQUIRE(particles[1].GetVelocity() == p2.GetVelocity());
    REQUIRE(particles[2].GetVelocity() == p3.GetVelocity());
  }
}

TEST_CASE("Get___ParticleSpeeds() functionality") {
  Simulator simulator;

  SECTION("Empty simulator") {
    std::vector<double> small_particles = simulator.GetSmallParticleSpeeds();
    std::vector<double> med_particles = simulator.GetMediumParticleSpeeds();
    std::vector<double> large_particles = simulator.GetLargeParticleSpeeds();
    REQUIRE(small_particles.empty());
    REQUIRE(med_particles.empty());
    REQUIRE(large_particles.empty());
  }

  /************************************************************
   *                 GetSmallParticleSpeeds()                 *
   ************************************************************/
  SECTION("Simulator has particles but no small particles") {
    simulator.AddRandomLargeParticle();
    simulator.AddRandomMediumParticle();
    std::vector<double> small_particles = simulator.GetSmallParticleSpeeds();
    REQUIRE(small_particles.empty());
  }

  SECTION("Single small particle") {
    /* Small particles have mass and radius 1 */
    Particle p(1, 1, glm::vec2(1, 1), glm::vec2(1, 1));
    simulator.AddParticle(p);

    std::vector<double> small_particles = simulator.GetSmallParticleSpeeds();
    REQUIRE(small_particles[0] == glm::length(p.GetVelocity()));
  }

  SECTION("Multiple small particles") {
    Particle p1(1, 1, glm::vec2(1, 1), glm::vec2(1, 1));
    Particle p2(1, 1, glm::vec2(2, 1), glm::vec2(2, 1));
    Particle p3(1, 1, glm::vec2(3, 1), glm::vec2(3, 1));
    Particle p4(1, 1, glm::vec2(4, 1), glm::vec2(4, 1));
    simulator.AddParticle(p1);
    simulator.AddParticle(p2);
    simulator.AddParticle(p3);
    simulator.AddParticle(p4);

    std::vector<double> small_particles = simulator.GetSmallParticleSpeeds();
    REQUIRE(small_particles[0] == glm::length(p1.GetVelocity()));
    REQUIRE(small_particles[1] == glm::length(p2.GetVelocity()));
    REQUIRE(small_particles[2] == glm::length(p3.GetVelocity()));
    REQUIRE(small_particles[3] == glm::length(p4.GetVelocity()));
  }

  SECTION("Multiple small particles with multiple non-small particles") {
    Particle p1(1, 1, glm::vec2(1, 1), glm::vec2(1, 1));
    Particle p2(1, 1, glm::vec2(2, 1), glm::vec2(2, 1));
    Particle p3(1, 1, glm::vec2(3, 1), glm::vec2(3, 1));
    Particle p4(1, 1, glm::vec2(4, 1), glm::vec2(4, 1));
    simulator.AddParticle(p1);
    simulator.AddParticle(p2);
    simulator.AddParticle(p3);
    simulator.AddParticle(p4);

    /* Add extra non-small particles */
    simulator.AddRandomMediumParticle();
    simulator.AddRandomMediumParticle();
    simulator.AddRandomLargeParticle();
    simulator.AddRandomLargeParticle();

    std::vector<double> small_particles = simulator.GetSmallParticleSpeeds();
    REQUIRE(small_particles[0] == glm::length(p1.GetVelocity()));
    REQUIRE(small_particles[1] == glm::length(p2.GetVelocity()));
    REQUIRE(small_particles[2] == glm::length(p3.GetVelocity()));
    REQUIRE(small_particles[3] == glm::length(p4.GetVelocity()));
  }

  /************************************************************
   *                 GetMediumParticleSpeeds()                *
   ************************************************************/
  SECTION("Simulator has particles but no medium particles") {
    simulator.AddRandomLargeParticle();
    simulator.AddRandomSmallParticle();
    std::vector<double> med_particles = simulator.GetMediumParticleSpeeds();
    REQUIRE(med_particles.empty());
  }

  SECTION("Single medium particle") {
    /* Medium particles have mass 2 and radius 1.25 */
    Particle p(1.25, 2, glm::vec2(1, 1), glm::vec2(1, 1));
    simulator.AddParticle(p);

    std::vector<double> med_particles = simulator.GetMediumParticleSpeeds();
    REQUIRE(med_particles[0] == glm::length(p.GetVelocity()));
  }

  SECTION("Multiple medium particles") {
    Particle p1(1.25, 2, glm::vec2(1, 1), glm::vec2(1, 1));
    Particle p2(1.25, 2, glm::vec2(2, 1), glm::vec2(2, 1));
    Particle p3(1.25, 2, glm::vec2(3, 1), glm::vec2(3, 1));
    Particle p4(1.25, 2, glm::vec2(4, 1), glm::vec2(4, 1));
    simulator.AddParticle(p1);
    simulator.AddParticle(p2);
    simulator.AddParticle(p3);
    simulator.AddParticle(p4);

    std::vector<double> med_particles = simulator.GetMediumParticleSpeeds();
    REQUIRE(med_particles[0] == glm::length(p1.GetVelocity()));
    REQUIRE(med_particles[1] == glm::length(p2.GetVelocity()));
    REQUIRE(med_particles[2] == glm::length(p3.GetVelocity()));
    REQUIRE(med_particles[3] == glm::length(p4.GetVelocity()));
  }

  SECTION("Multiple medium particles with multiple non-medium particles") {
    Particle p1(1.25, 2, glm::vec2(1, 1), glm::vec2(1, 1));
    Particle p2(1.25, 2, glm::vec2(2, 1), glm::vec2(2, 1));
    Particle p3(1.25, 2, glm::vec2(3, 1), glm::vec2(3, 1));
    Particle p4(1.25, 2, glm::vec2(4, 1), glm::vec2(4, 1));
    simulator.AddParticle(p1);
    simulator.AddParticle(p2);
    simulator.AddParticle(p3);
    simulator.AddParticle(p4);

    /* Add extra non-medium particles */
    simulator.AddRandomSmallParticle();
    simulator.AddRandomSmallParticle();
    simulator.AddRandomLargeParticle();
    simulator.AddRandomLargeParticle();

    std::vector<double> med_particles = simulator.GetMediumParticleSpeeds();
    REQUIRE(med_particles[0] == glm::length(p1.GetVelocity()));
    REQUIRE(med_particles[1] == glm::length(p2.GetVelocity()));
    REQUIRE(med_particles[2] == glm::length(p3.GetVelocity()));
    REQUIRE(med_particles[3] == glm::length(p4.GetVelocity()));
  }

  /************************************************************
   *                 GetLargeParticleSpeeds()                 *
   ************************************************************/
  SECTION("Simulator has particles but no large particles") {
    simulator.AddRandomSmallParticle();
    simulator.AddRandomMediumParticle();
    std::vector<double> large_particles = simulator.GetLargeParticleSpeeds();
    REQUIRE(large_particles.empty());
  }

  SECTION("Single large particle") {
    /* Large particles have mass 4 and radius 1.5 */
    Particle p(1.5, 4, glm::vec2(1, 1), glm::vec2(1, 1));
    simulator.AddParticle(p);

    std::vector<double> large_particles = simulator.GetLargeParticleSpeeds();
    REQUIRE(large_particles[0] == glm::length(p.GetVelocity()));
  }

  SECTION("Multiple small particles") {
    Particle p1(1.5, 4, glm::vec2(1, 1), glm::vec2(1, 1));
    Particle p2(1.5, 4, glm::vec2(2, 1), glm::vec2(2, 1));
    Particle p3(1.5, 4, glm::vec2(3, 1), glm::vec2(3, 1));
    Particle p4(1.5, 4, glm::vec2(4, 1), glm::vec2(4, 1));
    simulator.AddParticle(p1);
    simulator.AddParticle(p2);
    simulator.AddParticle(p3);
    simulator.AddParticle(p4);

    std::vector<double> large_particles = simulator.GetLargeParticleSpeeds();
    REQUIRE(large_particles[0] == glm::length(p1.GetVelocity()));
    REQUIRE(large_particles[1] == glm::length(p2.GetVelocity()));
    REQUIRE(large_particles[2] == glm::length(p3.GetVelocity()));
    REQUIRE(large_particles[3] == glm::length(p4.GetVelocity()));
  }

  SECTION("Multiple small particles with multiple non-small particles") {
    Particle p1(1.5, 4, glm::vec2(1, 1), glm::vec2(1, 1));
    Particle p2(1.5, 4, glm::vec2(4, 1), glm::vec2(2, 1));
    Particle p3(1.5, 4, glm::vec2(8, 1), glm::vec2(3, 1));
    Particle p4(1.5, 4, glm::vec2(12, 1), glm::vec2(4, 1));
    simulator.AddParticle(p1);
    simulator.AddParticle(p2);
    simulator.AddParticle(p3);
    simulator.AddParticle(p4);

    /* Add extra non-large particles */
    simulator.AddRandomMediumParticle();
    simulator.AddRandomMediumParticle();
    simulator.AddRandomSmallParticle();
    simulator.AddRandomSmallParticle();

    std::vector<double> large_particles = simulator.GetLargeParticleSpeeds();
    REQUIRE(large_particles[0] == glm::length(p1.GetVelocity()));
    REQUIRE(large_particles[1] == glm::length(p2.GetVelocity()));
    REQUIRE(large_particles[2] == glm::length(p3.GetVelocity()));
    REQUIRE(large_particles[3] == glm::length(p4.GetVelocity()));
  }
}