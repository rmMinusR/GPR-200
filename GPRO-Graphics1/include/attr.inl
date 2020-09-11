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
	attr.inl

	Gives quick, easy, intuitive access to inline variable-specific getters
	and setters, without any clunky-looking calls to GetX() or SetX().
	Heavily based on the Attribute feature of C#.

	Ideally we would offload this to the compiler using template
	metaprogramming and/or macros, but this is the next best thing.
	
	C# example:

	private int _state = 0;
	public int State {
		get { return _state; }
		set { _state = value%5; }
	}

	C++ example (note the semicolon after accessor block, and comma after getter):

	attr<int> state {
		[](int& _state)                   -> int  { return _state; },    //getter
		[](int& _state, const int& value) -> void { _state = value%5; } //setter
	};

	If ATTR_SHORTCUTS is defined, the following is also valid; however it will not capture any local variables:

	attr<int> state {
		attr_get(int) { return _state; },   //getter
		attr_set(int) { _state = value%5; } //setter
	};

*/

#include <functional>

#ifdef ATTR_SHORTCUTS

#ifndef attr_get
#define attr_get(T) [](T& _state) mutable -> T
#endif

#ifndef attr_set
#define attr_set(T) [](T& _state, const T& value) mutable
#endif

#endif

//constexpr get(capture_args) [capture_args](T& _state)                 mutable -> T;
//constexpr set(capture_args) [capture_args](T& _state, const T& value) mutable -> void;

template<typename T>
class const_attr final {
private:
	T* const value_ptr;
	bool using_internal_value;

	typedef std::function<T(T&)> getter_t;
	const getter_t _getter;

	T default_get(T& internal_value) { return internal_value; }

	//Creates an internal value, and marks it for deletion upon dtor call
	const_attr(const getter_t& getter = nullptr) :
		using_internal_value{ true },
		value_ptr{ new T },
		_getter{ getter ? getter : std::bind(&const_attr<T>::default_get, this, std::placeholders::_1) }
	{}
public:

	//Getter or setter can be null; if so, uses the internal default.

	//Creates an internal value, initializes it, then deletes it once done
	const_attr(const T& initial_value, const getter_t& getter = nullptr) : const_attr(getter) { *value_ptr = initial_value; }

	//Uses an external value. NOT RECOMMENDED.
	const_attr(T* const state, const getter_t& getter = nullptr) :
		using_internal_value{ false },
		value_ptr{ state },
		_getter{ getter ? getter : std::bind(&const_attr<T>::_dget, this, std::placeholders::_1) }
	{}

	//Attributes shouldn't be copyable.
	const_attr(const const_attr<T>&) = delete;

	//If we're using an internal value, clean up our mess!
	~const_attr() { if (using_internal_value) delete value_ptr; }

	//Disable assignment
	inline void operator=(const const_attr<T>& rhs) = delete;

	//Getter override
	inline operator T() {
		return _getter(*value_ptr);
	}
};

template<typename T>
class attr final {
private:
	T* const value_ptr; //Depending on getter and setter, might not even be used!
	bool using_internal_value;

	typedef std::function<   T(T&          )> getter_t;
	typedef std::function<void(T&, const T&)> setter_t;

	const getter_t _getter;
	const setter_t _setter;

	//Internal defaults
	T    default_get(T& internal_value) { return internal_value; }
	void default_set(T& internal_value, const T& rhs) { internal_value = rhs; }

public:

	//Getter or setter can be null; if so, uses the internal default.

	//Creates an internal value, and marks it for deletion upon dtor call
	attr(const getter_t& getter = nullptr, const setter_t& setter = nullptr) :
		attr(new T, getter, setter)
	{ using_internal_value = true; }

	//Creates an internal value, initializes it, then deletes it once done
	attr(const T& initial_value, const getter_t& getter = nullptr, const setter_t& setter = nullptr) : attr(getter, setter) { *value_ptr = initial_value; }
	
	//Uses an external value. NOT RECOMMENDED.
	attr(T* const state, const getter_t& getter = nullptr, const setter_t& setter = nullptr) :
		using_internal_value{ false },
		value_ptr{ state },
		_getter{ getter ? getter : std::bind(&attr<T>::default_get, this, std::placeholders::_1                       ) },
		_setter{ setter ? setter : std::bind(&attr<T>::default_set, this, std::placeholders::_1, std::placeholders::_2) }
	{}
	
	//Uses an external value, and assigns to it. NOT RECOMMENDED.
	attr(T* const state, const T& initial_value, const getter_t& getter = nullptr, const setter_t& setter = nullptr) : attr(state, getter, setter) { *value_ptr = initial_value; }

	//Attributes shouldn't be copyable.
	attr(const attr<T>&) = delete;
	
	//If we're using an internal value, clean up our mess!
	~attr() { if (using_internal_value) delete value_ptr; }

	//Assigning from another attribute is both a getter and setter call
	inline void operator=(const attr<T>& rhs) { operator=((T)rhs); }

	//Setter override
	inline attr<T>& operator=(T rhs) {
		_setter(*value_ptr, rhs);
		return *this;
	}
	
	//Getter override
	inline operator T() {
		return _getter(*value_ptr);
	}

	inline operator const_attr<T>() {
		return const_attr<T>(*value_ptr, _getter);
	}
};