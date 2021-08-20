// this file will run various tests on a forward_list to test if it colplies with the stl.
#include <forward_list>
#include <memory>
#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "/home/brian/Documents/cpp/stl/forward_list/forward_list.h"
#include <iostream>
#include <algorithm>
using Type = int;
using my_list_t = brian::forward_list<Type>;
using their_list_t = std::forward_list<Type>;
template <template<typename,typename> class List, typename T, typename Alloc>
size_t get_size(List<T,Alloc> const& l) {
	return std::count_if(l.begin(), l.end(), [](auto const& a){return true;});
}
bool equal(my_list_t const& m, their_list_t const& t) {
	auto m_it = m.begin();auto t_it = t.begin();
	for (; m_it != m.end() && t_it != t.end();++m_it,++t_it) {
		if (*m_it != *t_it) {
			return false;
		}
	}
	return (m_it == m.end() && t_it == t.end()) ? true : false ;
}
bool equal(their_list_t const& m, my_list_t const& t) {
	auto m_it = m.begin();auto t_it = t.begin();
	for (; m_it != m.end() && t_it != t.end();++m_it,++t_it) {
		if (*m_it != *t_it) {
			return false;
		}
	}
	return (m_it == m.end() && t_it == t.end()) ? true : false ;
}

TEST_CASE("testing forward_list constructors") {
	my_list_t* mine = nullptr;	
	their_list_t* theirs = nullptr;

	/*1) default constructor */
	mine = new my_list_t();
	theirs = new their_list_t();
	REQUIRE(equal(*mine,*theirs));

	delete mine;
	delete theirs;
	/*2) allocator constructor*/
	mine = new my_list_t(std::allocator<Type>());
	theirs = new their_list_t(std::allocator<Type>());
	REQUIRE(equal(*mine,*theirs));

	delete mine;
	delete theirs;
	/*3) default fill constructor*/
	mine = new my_list_t(4);
	theirs = new their_list_t(4);
	REQUIRE(equal(*mine,*theirs));

	/*4) fill constructor*/
	mine = new my_list_t(4,10);
	theirs = new their_list_t(4,10);
	REQUIRE(equal(*mine,*theirs));

	delete mine;
	delete theirs;
	/*5) range constructor*/
	std::forward_list<Type> l = {1,2,3,4};
	mine = new my_list_t(l.begin(), l.end());
	theirs = new their_list_t(l.begin(), l.end());
	REQUIRE(equal(*mine,*theirs));

	delete mine;
	delete theirs;
	
	/*6) copy constructor*/
	my_list_t my_l {1,2,3,4};
	their_list_t their_l {1,2,3,4};
	mine = new my_list_t(my_l);
	theirs = new their_list_t(their_l);
	REQUIRE(equal(*mine,*theirs));

	delete mine;
	delete theirs;

	/*7) allocator extended copy constructor*/
	mine = new my_list_t(my_l,std::allocator<Type>());
	theirs = new their_list_t(their_l, std::allocator<Type>());
	REQUIRE(equal(*mine,*theirs));

	delete mine;
	delete theirs;

	/*8) move constructor*/
	my_list_t my_l_moved1 {1,2,3,4};
	their_list_t their_l_moved1 {1,2,3,4};
	mine = new my_list_t(my_l_moved1);
	theirs = new their_list_t(their_l_moved1);
	REQUIRE(equal(*mine,*theirs));

	delete mine;
	delete theirs;

	/*allocator extended move constructor*/
	my_list_t my_l_moved1a {1,2,3,4};
	their_list_t their_l_moved1a {1,2,3,4};
	mine = new my_list_t(my_l_moved1a, std::allocator<Type>());
	theirs = new their_list_t(their_l_moved1a,std::allocator<Type>());
	REQUIRE(equal(*mine,*theirs));

	delete mine;
	delete theirs;
	// ADD: test case(s) for when the new allocator does not compare equal

	/*initializer_list constructor*/
	std::initializer_list<Type> il {1,2,3,4};
	mine = new my_list_t(il);
	theirs = new their_list_t(il);
	REQUIRE(equal(*mine,*theirs));

	delete mine;
	delete theirs;
}

TEST_CASE("extra constructor tests") {

}
