#pragma once

/*
	Copyright 2020 Robert S. Christensen

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

		http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/

/*
	attr.hpp

	Gives quick, easy, intuitive access to inline variable-specific getters
	and setters, without any clunky-looking calls to GetX() or SetX().
	Heavily based on the Attribute feature of C#.

	Ideally this we would offload this to the compiler using template
	metaprogramming and/or macros, but this is the next best thing.

	Also: Due to template-linker badness, everything must be declared and
	defined in the same place, so we can't split it into attr.cpp
*/

#include <functional>

template<typename T>
class attr final {
private:
	T value; //Depending on getter and setter, might not even be used!

	typedef std::function<   T(T&          )> getter_t;
	typedef std::function<void(T&, const T&)> setter_t;

	const getter_t getter;
	const setter_t setter;

	//Internal defaults
	T    _dget(T& internal_value) { return internal_value; }
	void _dset(T& internal_value, const T& rhs) { internal_value = rhs; }

public:
	//Getter or setter can be null; if so, uses the internal default.
	attr(const T& v, const getter_t& _g = nullptr, const setter_t& _s = nullptr) :
		value{ v },
		getter{ _g ? _g : std::bind(&attr<T>::_dget, this, std::placeholders::_1) },
		setter{ _s ? _s : std::bind(&attr<T>::_dset, this, std::placeholders::_1, std::placeholders::_2) }
	{}
	
	//Attributes shouldn't be copyable.
	attr(const attr<T>&) = delete;

	//Assigning from another Attribute is both a getter and setter call
	inline void operator=(const attr<T>& rhs) { operator=((T)rhs); }

	//Setter override
	inline attr<T> operator=(T rhs) {
		setter(this->value, rhs);
		return *this;
	}

	//Getter override
	inline operator T() {
		return getter(this->value);
	}
};