#include <memory>
#include <catch2/catch_test_macros.hpp>
#include "../include/vector2d.hpp"

TEST_CASE("vectors can be created for several types", "[vector2d]" ) {
    Vector2f fvec;
    Vector2i ivec;
    CHECK(fvec == Vector2D<real32>(0.f, 0.f));
    CHECK(ivec == Vector2D<sint32>(0, 0));

    Vector2i ivec2(fvec);
    CHECK(ivec == ivec2);
}

TEST_CASE("vectors: getters & setters", "[vector2d]" ) {
    Vector2i ivec;
    CHECK(ivec == Vector2D<sint32>(0, 0));
    ivec.setX(10);
    CHECK(ivec == Vector2D<sint32>(10, 0));
    ivec.setY(20);
    CHECK(ivec == Vector2D<sint32>(10, 20));

    CHECK(ivec.x() == 10);
    CHECK(ivec.y() == 20);
    CHECK(ivec[0] == 10);
    CHECK(ivec[1] == 20);
    CHECK_THROWS(ivec['x'] == 10);
    CHECK_THROWS(ivec['y'] == 20);
    CHECK(ivec["x"] == 10);
    CHECK(ivec["y"] == 20);

    ivec[0] = 30;
    ivec[1] = 40;
    CHECK(ivec[0] == 30);
    CHECK(ivec[1] == 40);
    CHECK(ivec["x"] == 30);
    CHECK(ivec["y"] == 40);

    ivec["x"] = -30;
    ivec["y"] = -40;
    CHECK(ivec[0] == -30);
    CHECK(ivec[1] == -40);
    CHECK(ivec["x"] == -30);
    CHECK(ivec["y"] == -40);
}

TEST_CASE("arithmetics operations on vectors", "[vector2d]" ) {
    Vector2f fvec{1.f, 1.f};

    fvec = fvec + Vector2f({10.f, 10.f});
    CHECK(fvec == Vector2D<real32>(11.f, 11.f));

    fvec += Vector2f({5.5f, 5.5f});
    CHECK(fvec == Vector2D<real32>(16.5f, 16.5f));

    fvec = fvec - Vector2f({16.5f, 16.5f});
    CHECK(fvec == Vector2D<real32>(0.0f, 0.0f));

    fvec -= Vector2f({3.3f, 3.3f});
    CHECK( fvec == Vector2D<real32>(-3.3f, -3.3f));
    CHECK(-fvec == Vector2D<real32>( 3.3f,  3.3f));

    fvec = fvec * 10.f;
    CHECK(fvec == Vector2D<real32>(-33.f, -33.f));

    fvec *= -1.f;
    CHECK(fvec == Vector2D<real32>(33.f, 33.f));

    fvec = fvec / -11.f;
    CHECK(fvec == Vector2D<real32>(-3.f, -3.f));

    auto no_eq(fvec);
    no_eq /= -.333f;
    CHECK(fvec != Vector2D<real32>(9.f, 9.f));
    fvec /= -.3333333f; // check PRECISION RATE in types.hpp
    CHECK(fvec == Vector2D<real32>(9.f, 9.f));
}

TEST_CASE("vectors on surface: rotations & angles", "[vector2d]" ) {
    // using rotation for integers not smart =)
    // ROTATION
    Vector2f vec(1.f, 1.f);
    auto res = vec.rotate(PI_HALF);
    CHECK(res == Vector2D<real32>(1.f, -1.f));
    res = vec.rotate(PI);
    CHECK(res == Vector2D<real32>(-1.f, -1.f));
    res = vec.rotate(PI+PI_HALF);
    CHECK(res == Vector2D<real32>(-1.f, 1.f));
    res = vec.rotate(2.f * PI);
    CHECK(res == Vector2D<real32>(1.f, 1.f));

    res = vec.rotate(0.5 * PI_HALF);
    CHECK(res == Vector2D<real32>(std::sqrt(2.f), 0.f));
    res = vec.rotate(-0.5 * PI_HALF);
    CHECK(res == Vector2D<real32>(0.f, std::sqrt(2.f)));

    vec = {0.f, 0.f};
    res = vec.rotate(0.5 * PI_HALF);
    CHECK(res == Vector2D<real32>(0.f, 0.f));
    res = vec.rotate(-0.5 * PI_HALF);
    CHECK(res == Vector2D<real32>(0.f, 0.f));
    
    vec = {2.f, -16.f};
    res = vec.rotate(0.f);
    CHECK(res == Vector2D<real32>(2.f, -16.f));

    // ROTATION In-Place
    res = {2.f, 2.f};
    res.rotate_ip(PI);
    CHECK(res == Vector2D<real32>(-2.f, -2.f));
    res.rotate_ip(PI_HALF);
    CHECK(res == Vector2D<real32>(-2.f, 2.f));
    res.rotate_ip(0.f);
    CHECK(res == Vector2D<real32>(-2.f, 2.f));

    // Get Angle
    vec = {2.f, 2.f};
    CHECK(vec.angle() == 0.5*PI_HALF);
    vec = {0.f, 2.f};
    CHECK(vec.angle() == PI_HALF);
    vec = {2.f, 0.f};
    CHECK(vec.angle() == 0.f);
    vec = {-12.f, 0.f};
    CHECK(vec.angle() == PI);
    vec = {-16.f, -16.f};
    CHECK(vec.angle() == -(PI - 0.5f*PI_HALF));
    vec = {1.f, -1.f};
    CHECK(vec.angle() == -(0.5f*PI_HALF));

    // Get Angle Between Vectors (max = 90 degree = PI_HALF)
    Vector2f vecA(1.f, 0.f);
    Vector2f vecB(0.f, 1.f);
    Radian angle(vecA.angleBetween(vecB));
    CHECK(angle == PI_HALF);
    
    vecB = {1.f, 1.f};
    angle = vecA.angleBetween(vecB);
    CHECK(angle == PI_HALF*0.5f);

    vecB = {0.f, 0.f};
    angle = vecA.angleBetween(vecB);
    CHECK(angle == 0.f);

    vecB = {-1.f, 0.f};
    angle = vecA.angleBetween(vecB);
    CHECK(angle == PI);

    vecB = {-1.f, -1.f};
    angle = vecA.angleBetween(vecB);
    CHECK(angle == (PI - 0.5f*PI_HALF));

    vecA = {0.f, 0.f};
    vecB = {0.f, 0.f};
    angle = vecA.angleBetween(vecB);
    CHECK(angle == 0.f);

    vecA = {0.f, -10.f};
    vecB = {0.f, 0.f};
    angle = vecA.angleBetween(vecB);
    CHECK(angle == 0.f);
}

TEST_CASE("vectors on surface: magnituted & normalizing", "[vector2d]" ) {
    // Magnitude (better name of length =) )
    Vector2i ivec;
    Vector2f fvec;
    CHECK(ivec.magnitude() == 0.f);
    CHECK(fvec.magnitude() == 0.f);

    ivec.setX(3);
    fvec.setX(4.f);
    CHECK(ivec.magnitude() == 3.f);
    CHECK(fvec.magnitude() == 4.f);

    ivec.setY(-4);
    fvec.setY(3.f);
    CHECK(ivec.magnitude() == 5.f);
    CHECK(fvec.magnitude() == 5.f);

    // Vector2i vec_max(INT32_MAX, INT32_MAX);
    // CHECK(vec_max.magnitude() == float(INT32_MAX)*sqrt(2.f));

    // Normalize
    Vector2f fvec_not_norm;
    Vector2i ivec_not_norm;
    auto fvec_norm(fvec_not_norm.normalize());
    auto ivec_norm(ivec_not_norm.normalize());
    CHECK(fvec_norm == Vector2D<real32>(0.f, 0.f));
    CHECK(ivec_norm == Vector2D<sint32>(0, 0));

    fvec_not_norm = {0.5f, 0.5f};
    fvec_norm = fvec_not_norm.normalize();
    CHECK(fvec_norm == Vector2D<real32>( std::sqrt(0.5f), std::sqrt(0.5f)) );

    fvec_not_norm = { 1, -1 };
    fvec_norm = fvec_not_norm.normalize();
    CHECK(fvec_norm == Vector2D<real32>( std::sqrt(0.5f), -std::sqrt(0.5f) ));

    real32 x_(0.001f);
    real32 y_(-99999.f);
    fvec_not_norm = { x_, y_ };
    fvec_norm = fvec_not_norm.normalize();
    CHECK(fvec_norm == Vector2D<real32>( x_/y_, - y_/y_ ));

    // Normalize In-Place
    Vector2f vec_f { -1.f, 1.f };
    CHECK(vec_f.normalize_ip() == Vector2D<real32>( -std::sqrt(0.5f), std::sqrt(0.5f) ));
    CHECK(vec_f.normalize_ip() == Vector2D<real32>( -std::sqrt(0.5f), std::sqrt(0.5f) ));
    vec_f = { 0.f, 0.f };
    CHECK(vec_f.normalize_ip() == Vector2D<real32>( 0.f, 0.f) );
}

TEST_CASE("vectors on surface: relation between two vectors", "[vector2d]" ) {
    // INTEGERs
    // DOT product
    Vector2i ivecA;
    Vector2i ivecB;
    CHECK(ivecA.dot(ivecB) == 0.f);
    ivecB.setY(1);
    CHECK(ivecA.dot(ivecB) == 0.f);
    ivecB.setX(-1);
    CHECK(ivecA.dot(ivecB) == 0.f);

    ivecA = { 200, 200 };
    CHECK(ivecA.dot(ivecB) == 0.f);
    ivecB.setX(1);
    CHECK(ivecA.dot(ivecB) == 400.f);

    // Are Vecs Collinear?
    CHECK(ivecA.isCollinear(ivecB) == true);
    ivecA.setX(-200);
    CHECK(ivecA.isCollinear(ivecB) == false);
    ivecA.setX(0);
    CHECK(ivecA.isCollinear(ivecB) == false);
    ivecA.setY(0);
    CHECK(ivecA.isCollinear(ivecB) == true);
    
    ivecB = { -11, -5 };
    ivecA = { -11, -5 };
    CHECK(ivecA.isCollinear(ivecB) == true);
    ivecA = { 11, 5 };
    CHECK(ivecA.isCollinear(ivecB) == true);

    // Are Vecs Ortho?
    ivecB = { -11, -5 };
    ivecA = { -11, -5 };
    CHECK(ivecA.isOrtho(ivecB) == false);

    ivecB = { 0, 0 };
    ivecA = { -11, -5 };
    CHECK(ivecA.isOrtho(ivecB) == true);
    ivecB = { 0, 0 };
    ivecA = { 0, 0 };
    CHECK(ivecA.isOrtho(ivecB) == true);
    
    ivecB = { 100, 0 };
    ivecA = { 0, 1000 };
    CHECK(ivecA.isOrtho(ivecB) == true);

    ivecB = { -100, 100 };
    ivecA = { 1000, -1000 };
    CHECK(ivecA.isOrtho(ivecB) == false);
    ivecA.setY(1000);
    CHECK(ivecA.isOrtho(ivecB) == true);

    ivecB = { 3, -4 };
    ivecA = { -4, -3 };
    CHECK(ivecA.isOrtho(ivecB) == true);
    
    // FLOATs
    // DOT product
    Vector2f fvecA;
    Vector2f fvecB;
    CHECK(fvecA.dot(fvecB) == 0.f);
    fvecB.setY(1.f);
    CHECK(fvecA.dot(fvecB) == 0.f);
    fvecB.setX(-1.f);
    CHECK(fvecA.dot(fvecB) == 0.f);

    fvecA = { 200.f, 200.f };
    CHECK(fvecA.dot(fvecB) == 0.f);
    fvecB.setX(1.f);
    CHECK(fvecA.dot(fvecB) == 400.f);

    // Are Vecs Collinear?
    CHECK(fvecA.isCollinear(fvecB) == true);
    fvecA.setX(-200.f);
    CHECK(fvecA.isCollinear(fvecB) == false);
    fvecA.setX(0.f);
    CHECK(fvecA.isCollinear(fvecB) == false);
    fvecA.setY(0.f);
    CHECK(fvecA.isCollinear(fvecB) == true);
    
    fvecA = { -11.f, -5.f };
    fvecB = { -11.f, -5.f };
    CHECK(fvecA.isCollinear(fvecB) == true);
    fvecA = { 11.f, 5.f };
    CHECK(fvecA.isCollinear(fvecB) == true);

    // Are Vecs Ortho?
    fvecB = { -11.f, -5.f };
    fvecA = { -11.f, -5.f };
    CHECK(fvecA.isOrtho(fvecB) == false);

    fvecB = { 0.f, 0.f };
    fvecA = { -11, -5 };
    CHECK(fvecA.isOrtho(fvecB) == true);
    fvecB = { 0.f, 0.f };
    fvecA = { 0.f, 0.f };
    CHECK(fvecA.isOrtho(fvecB) == true);
    
    fvecB = { 100.f, 0.f };
    fvecA = { 0.f, 1000.f };
    CHECK(fvecA.isOrtho(fvecB) == true);

    fvecB = { -100.f, 100.f };
    fvecA = { 1000.f, -1000.f };
    CHECK(fvecA.isOrtho(fvecB) == false);
    fvecA.setY(1000.f);
    CHECK(fvecA.isOrtho(fvecB) == true);

    fvecB = { 3.f, -4.f };
    fvecA = { -4.f, -3.f };
    CHECK(fvecA.isOrtho(fvecB) == true);
}
