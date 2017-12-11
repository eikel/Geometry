/*
	This file is part of the Geometry library.
	Copyright (C) 2011-2017 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2012 Claudius Jähn <claudius@uni-paderborn.de>

	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "Vec3.h"
#include <cstdint>
#include <limits>
#include <sstream>

TEST_CASE("3D vector operations", "[Geometry][Vec3]") {
	const Geometry::Vec3d a(1.0, 2.0, 3.0);
	const Geometry::Vec3d b(3.0, 2.0, 1.0);
	Geometry::Vec3d c;
	SECTION("Addition") {
		c = a + b;
		REQUIRE(c.x() == Approx(4.0));
		REQUIRE(c.y() == Approx(4.0));
		REQUIRE(c.z() == Approx(4.0));
	}
	SECTION("Subtraction") {
		c = a - b;
		REQUIRE(c.x() == Approx(-2.0));
		REQUIRE(c.y() == Approx(0.0));
		REQUIRE(c.z() == Approx(2.0));
	}
	SECTION("Cross product") {
		c = a.cross(b);
		REQUIRE(c.x() == Approx(-4.0));
		REQUIRE(c.y() == Approx(8.0));
		REQUIRE(c.z() == Approx(-4.0));
	}
	SECTION("Dot product") {
		REQUIRE(a.dot(b) == Approx(10.0));
	}
	SECTION("Length") {
		REQUIRE(a.length() == Approx(std::sqrt(14.0)));
		REQUIRE(b.length() == Approx(std::sqrt(14.0)));
	}
	SECTION("Normalize") {
		const double epsilon = 1.0e-6;
		REQUIRE(Geometry::Vec3d(12.34567, 0.0, 0.0).normalize().equals(Geometry::Vec3d(1.0, 0.0, 0.0), epsilon));
		REQUIRE(Geometry::Vec3d(0.0, 2.34567, 0.0).normalize().equals(Geometry::Vec3d(0.0, 1.0, 0.0), epsilon));
		REQUIRE(Geometry::Vec3d(0.0, 0.0, 345.6789).normalize().equals(Geometry::Vec3d(0.0, 0.0, 1.0), epsilon));
	}
}

SCENARIO("3D vectors can be serialized", "[Geometry][Vec3]") {
	GIVEN("An empty stream") {
		std::stringstream stream;
		WHEN("3D integer vectors are written") {
			using IntVec3 = Geometry::_Vec3<int32_t>;
			for (int32_t x = -10; x <= 10; ++x) {
				for (int32_t y = -10; y <= 10; ++y) {
					for (int32_t z = -10; z <= 10; ++z) {
						stream << IntVec3(x, y, z) << ' ';
					}
				}
			}
			THEN("3D integer vectors can be read") {
				for (int32_t x = -10; x <= 10; ++x) {
					for (int32_t y = -10; y <= 10; ++y) {
						for (int32_t z = -10; z <= 10; ++z) {
							IntVec3 vec;
							stream >> vec;
							REQUIRE(vec.getX() == x);
							REQUIRE(vec.getY() == y);
							REQUIRE(vec.getZ() == z);
						}
					}
				}
			}
		}
		WHEN("3D float vectors are written") {
			using FloatVec3 = Geometry::_Vec3<float>;
			for (float x = -1.0f; x <= 1.0f; x += 0.1f) {
				for (float y = -1.0f; y <= 1.0f; y += 0.1f) {
					for (float z = -1.0f; z <= 1.0f; z += 0.1f) {
						stream << FloatVec3(x, y, z) << ' ';
					}
				}
			}
			THEN("3D float vectors can be read") {
				for (float x = -1.0f; x <= 1.0f; x += 0.1f) {
					for (float y = -1.0f; y <= 1.0f; y += 0.1f) {
						for (float z = -1.0f; z <= 1.0f; z += 0.1f) {
							FloatVec3 vec;
							stream >> vec;
							REQUIRE(vec.getX() == Approx(x));
							REQUIRE(vec.getY() == Approx(y));
							REQUIRE(vec.getZ() == Approx(z));
						}
					}
				}
			}
		}
	}
}
