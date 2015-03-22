/*************************************************************************
** SVGOutputTest.cpp                                                    **
**                                                                      **
** This file is part of dvisvgm -- the DVI to SVG converter             **
** Copyright (C) 2005-2015 Martin Gieseking <martin.gieseking@uos.de>   **
**                                                                      **
** This program is free software; you can redistribute it and/or        **
** modify it under the terms of the GNU General Public License as       **
** published by the Free Software Foundation; either version 3 of       **
** the License, or (at your option) any later version.                  **
**                                                                      **
** This program is distributed in the hope that it will be useful, but  **
** WITHOUT ANY WARRANTY; without even the implied warranty of           **
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the         **
** GNU General Public License for more details.                         **
**                                                                      **
** You should have received a copy of the GNU General Public License    **
** along with this program; if not, see <http://www.gnu.org/licenses/>. **
*************************************************************************/

#include <gtest/gtest.h>
#include <fstream>
#include "gzstream.h"
#include "MessageException.h"
#include "SVGOutput.h"

using namespace std;

static string adapt (const char *str) {
#if __WIN32__
	string ret;
	for (const char *p=str; *p; p++)
		ret += tolower(*p);
	return ret;
#else
	return str;
#endif
}


TEST(SVGOutputTest, defaults) {
	SVGOutput out("SVGOutputTest.cpp", "");
	EXPECT_EQ(out.filename(1, 1), adapt("SVGOutputTest.svg"));
	EXPECT_EQ(out.filename(5, 9), adapt("SVGOutputTest-5.svg"));
	EXPECT_EQ(out.filename(5, 10), adapt("SVGOutputTest-05.svg"));
	EXPECT_EQ(out.filename(5, 256), adapt("SVGOutputTest-005.svg"));
}


TEST(SVGOutputTest, widthSpecifier) {
	{
		SVGOutput out("SVGOutputTest.cpp", "%f--%3p");
		EXPECT_EQ(out.filename(5, 9), adapt("SVGOutputTest--005.svg"));
		EXPECT_EQ(out.filename(54, 65), adapt("SVGOutputTest--054.svg"));
		EXPECT_EQ(out.filename(543, 654), adapt("SVGOutputTest--543.svg"));
	}{
		SVGOutput out("SVGOutputTest.cpp", "%f--%3p--%P");
		EXPECT_EQ(out.filename(5, 9), adapt("SVGOutputTest--005--9.svg"));
		EXPECT_EQ(out.filename(54, 65), adapt("SVGOutputTest--054--65.svg"));
		EXPECT_EQ(out.filename(543, 654), adapt("SVGOutputTest--543--654.svg"));
	}{
		SVGOutput out("SVGOutputTest.cpp", "%f--%3p--%3P");
		EXPECT_EQ(out.filename(5, 9), adapt("SVGOutputTest--005--009.svg"));
		EXPECT_EQ(out.filename(54, 65), adapt("SVGOutputTest--054--065.svg"));
		EXPECT_EQ(out.filename(543, 654), adapt("SVGOutputTest--543--654.svg"));
	}{
		SVGOutput out("SVGOutputTest.cpp", "%5f--%3p--%3P");
		EXPECT_EQ(out.filename(5, 9), adapt("SVGOutputTest--005--009.svg"));
		EXPECT_EQ(out.filename(54, 65), adapt("SVGOutputTest--054--065.svg"));
		EXPECT_EQ(out.filename(543, 654), adapt("SVGOutputTest--543--654.svg"));
	}
}


TEST(SVGOutputTest, expressions) {
	{
		SVGOutput out("SVGOutputTest.cpp", "no-macro");
		EXPECT_EQ(out.filename(5, 9), adapt("no-macro.svg"));
		EXPECT_EQ(out.filename(54, 65), adapt("no-macro.svg"));
		EXPECT_EQ(out.filename(543, 654), adapt("no-macro.svg"));
	}{
		SVGOutput out("SVGOutputTest.cpp", "%f--%(p-1)");
		EXPECT_EQ(out.filename(5, 9), adapt("SVGOutputTest--4.svg"));
		EXPECT_EQ(out.filename(54, 65), adapt("SVGOutputTest--53.svg"));
		EXPECT_EQ(out.filename(543, 654), adapt("SVGOutputTest--542.svg"));
	}{
		SVGOutput out("SVGOutputTest.cpp", "%f--%3(p-1)");
		EXPECT_EQ(out.filename(5, 9), adapt("SVGOutputTest--004.svg"));
		EXPECT_EQ(out.filename(54, 65), adapt("SVGOutputTest--053.svg"));
		EXPECT_EQ(out.filename(543, 654), adapt("SVGOutputTest--542.svg"));
	}{
		SVGOutput out("SVGOutputTest.cpp", "%f--%3(P+2p)");
		EXPECT_EQ(out.filename(5, 9), adapt("SVGOutputTest--019.svg"));
		EXPECT_EQ(out.filename(54, 65), adapt("SVGOutputTest--173.svg"));
		EXPECT_EQ(out.filename(543, 654), adapt("SVGOutputTest--1740.svg"));
	}
}


TEST(SVGOutputTest, getPageStream) {
	{
		SVGOutput out(0, "");
		ostream &os = out.getPageStream(1, 10);
		EXPECT_EQ(&os, &cout);
	}{
		SVGOutput out("SVGOutputTest.cpp", "%f-%p");
		ostream &os1 = out.getPageStream(1, 10);
		EXPECT_TRUE(dynamic_cast<ofstream&>(os1));
		ostream &os2 = out.getPageStream(1, 10);
		EXPECT_EQ(&os1, &os2);
	}{
		SVGOutput out("SVGOutputTest.cpp", "%f-%p", 9);
		ostream &os = out.getPageStream(1, 10);
		EXPECT_TRUE(dynamic_cast<ogzstream&>(os));
	}
}


TEST(SVGOutputTest, ignore) {
	SVGOutput out("SVGOutputTest.cpp", "%x %y");
	EXPECT_EQ(out.filename(5, 9), adapt("SVGOutputTest-5.svg"));
}


TEST(SVGOutputTest, error) {
	SVGOutput out("SVGOutputTest.cpp", "%(p/0)");
	EXPECT_THROW(out.filename(5, 9), MessageException);
}
