#include <core/particle.h>

#include <catch2/catch.hpp>

using namespace idealgas;

TEST_CASE("Constructor") {
  double rad = 2.5;
  double mass = 1;
  glm::vec2 pos(10, 15);
  glm::vec2 vel(2, -1);
  Particle p(rad, mass, pos, vel);

  SECTION("Test radius is held properly") {
    REQUIRE(rad == Approx(p.GetRadius()));
  }

  SECTION("Test mass is held properly") {
    REQUIRE(mass == Approx(p.GetMass()));
  }

  SECTION("Test position is held properly") {
    REQUIRE(pos == p.GetPosition());
  }

  SECTION("Test velocity is held properly") {
    REQUIRE(vel == p.GetVelocity());
  }
}

TEST_CASE("UpdatePosition()") {
  double rad = 1;
  double mass = 1;
  glm::vec2 pos(-1, 0);

  SECTION("Velocity is zero-vector") {
    glm::vec2 vel(0, 0);
    Particle p(rad, mass, pos, vel);
    p.UpdatePosition();
    REQUIRE(pos == p.GetPosition());
  }

  SECTION("Velocity x component is zero") {
    glm::vec2 vel(0, -2);
    Particle p(rad, mass, pos, vel);
    p.UpdatePosition();
    REQUIRE(pos + vel == p.GetPosition());
  }

  SECTION("Velocity y component is zero") {
    glm::vec2 vel(3.5, 0);
    Particle p(rad, mass, pos, vel);
    p.UpdatePosition();
    REQUIRE(pos + vel == p.GetPosition());
  }

  SECTION("Average case") {
    glm::vec2 vel(0.5, -7);
    Particle p(rad, mass, pos, vel);
    p.UpdatePosition();
    REQUIRE(pos + vel == p.GetPosition());
  }

  SECTION("Multiple calls of UpdatePosition()") {
    glm::vec2 vel(0.5, -7);
    Particle p(rad, mass, pos, vel);

    /* Call UpdatePosition n times */
    size_t n = 5;
    for (size_t i = 0; i < n; i++) {
      p.UpdatePosition();
    }
    REQUIRE(pos + ((float) n)*vel == p.GetPosition());
  }
}

TEST_CASE("InvertVelocityComponent()") {
  double rad = 1;
  double mass = 1;
  glm::vec2 pos(-1, 0);

  SECTION("Bad input to method") {
    glm::vec2 vel(0, 0);
    Particle p(rad, mass, pos, vel);

    p.InvertVelocityComponent('z');
    /* Velocity should not change on bad input */
    REQUIRE(vel == p.GetVelocity());
  }
  SECTION("Velocity is zero-vector") {
    glm::vec2 vel(0, 0);
    Particle p(rad, mass, pos, vel);

    /* Inverting both x and y returns zero-vector either way */
    p.InvertVelocityComponent('x');
    REQUIRE(vel == p.GetVelocity());

    p.InvertVelocityComponent('y');
    REQUIRE(vel == p.GetVelocity());
  }

  SECTION("Velocity x component is zero") {
    glm::vec2 vel(0, -2);
    Particle p(rad, mass, pos, vel);

    p.InvertVelocityComponent('x');
    /* Velocity should not change since x component is zero */
    REQUIRE(vel == p.GetVelocity());

    p.InvertVelocityComponent('y');
    REQUIRE(glm::vec2(0, 2) == p.GetVelocity());
  }

  SECTION("Velocity y component is zero") {
    glm::vec2 vel(3.5, 0);
    Particle p(rad, mass, pos, vel);

    p.InvertVelocityComponent('y');
    /* Velocity should not change since y component is zero */
    REQUIRE(vel == p.GetVelocity());

    p.InvertVelocityComponent('x');
    REQUIRE(glm::vec2(-3.5, 0) == p.GetVelocity());
  }

  SECTION("Average case") {
    glm::vec2 vel(0.5, -7);
    Particle p(rad, mass, pos, vel);

    p.InvertVelocityComponent('x');
    REQUIRE(glm::vec2(-0.5, -7) == p.GetVelocity());

    p.InvertVelocityComponent('y');
    REQUIRE(glm::vec2(-0.5, 7) == p.GetVelocity());
  }
}