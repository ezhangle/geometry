// Boost.Geometry (aka GGL, Generic Geometry Library) test file
//
// Copyright Barend Gehrels 2007-2009, Geodan, Amsterdam, the Netherlands
// Copyright Bruno Lalande 2008, 2009
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <sstream>

#include <geometry_test_common.hpp>


#include <boost/geometry/util/for_each_coordinate.hpp>

#include <boost/geometry/algorithms/assign.hpp>


#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/adapted/c_array_cartesian.hpp>
#include <boost/geometry/geometries/adapted/tuple_cartesian.hpp>
#include <test_common/test_point.hpp>

namespace bg = boost::geometry;

struct test_operation
{
    template <typename P, int I>
    static void apply(P& p)
    {
        bg::set<I>(p, bg::get<I>(p) * 10);
    }
};

struct get_operation
{
    std::string s;

    template <typename P, int I>
    inline void apply(P const& p)
    {
        std::ostringstream out;
        out << bg::get<I>(p);
        s += out.str();
    }
};


template <typename P>
void test_all()
{
    P p;
    boost::geometry::assign(p, 1, 2, 3);
    boost::geometry::for_each_coordinate(p, test_operation());
    BOOST_CHECK(bg::get<0>(p) == 10);
    BOOST_CHECK(bg::get<1>(p) == 20);
    BOOST_CHECK(bg::get<2>(p) == 30);

    P const& cp = p;
    get_operation op;
    op = boost::geometry::for_each_coordinate(cp, op);
    BOOST_CHECK(op.s == std::string("102030"));
}

int test_main(int, char* [])
{
    test_all<int[3]>();
    test_all<float[3]>();
    test_all<double[3]>();
    test_all<test::test_point>();
    test_all<bg::point<int, 3, bg::cs::cartesian> >();
    test_all<bg::point<float, 3, bg::cs::cartesian> >();
    test_all<bg::point<double, 3, bg::cs::cartesian> >();

    return 0;
}
