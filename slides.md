---
theme: seriph
title: You Shall Not Pass*!
info: CppCon 2026 - Daniel Pfeifer
fonts:
  sans: Noto Sans
  serif: Noto Serif
  mono: Fantasque Sans Mono
codeCopy: false
contextMenu: false
---

<div class="absolute inset-0">
  <img src="/title-card.png" class="w-full h-full object-cover" />
</div>

---
layout: center
---

**Tribute** to *C++ Seasoning: 3 Goals for Better Code*

---
layout: center
---

**Goal 1**: No Raw Loops

---
layout: center
---

<div class="absolute inset-0">
  <img src="/rule1.svg" class="w-full h-full object-cover" />
</div>

---
layout: center
---

# 👌

---
layout: center
---

**Goal 2**: No Raw Synchronization Primitives

---
layout: center
---

<div class="absolute inset-0">
  <img src="/rule2.svg" class="w-full h-full object-cover" />
</div>

---
layout: center
---

# 🤔

---
layout: center
---

What are **Raw** Synchronization Primitives?

---
layout: center
clicks: 3
---

<p>
  A <em>raw <MorphPhrase
    from="loop"
    to="synchronization primitive"
    :at="1"
    color="#bbf7d0"
  /></em><br>
  is any <MorphPhrase
    from="loop"
    to="synchronization primitive"
    :at="1"
    color="#bbf7d0"
  /><br>
  inside a <MorphPhrase
    from="function"
    to="class / function"
    :at="3"
    color="#fecaca"
  /><br>
  where the <MorphPhrase
    from="function"
    to="class / function"
    :at="3"
    color="#fecaca"
  /><br>
  serves purpose larger than<br>
  <MorphPhrase
    from="the algorithm implemented by the loop"
    to="synchronizing the access of the data it manages"
    :at="2"
    color="#bfdbfe"
  />
</p>

---
layout: center
---

**Goal 2**: No Raw Synchronization Primitives

* Use Structured Concurrency
* C++26 Execution control library 

---
layout: center
---

**Goal 3**: No Raw Pointers

---
layout: center
---

<div class="absolute inset-0">
  <img src="/rule3.svg" class="w-full h-full object-cover" />
</div>

---
layout: center
---

# 🤔

---
layout: center
clicks: 3
---

<p>
  A <em>raw <MorphPhrase
    from="loop"
    to="pointer"
    :at="1"
    color="#bbf7d0"
  /></em><br>
  is any <MorphPhrase
    from="loop"
    to="pointer"
    :at="1"
    color="#bbf7d0"
  /><br>
  inside a <MorphPhrase
    from="function"
    to="class"
    :at="3"
    color="#fecaca"
  /><br>
  where the <MorphPhrase
    from="function"
    to="class"
    :at="3"
    color="#fecaca"
  /><br>
  serves purpose larger than<br>
  <MorphPhrase
    from="the algorithm implemented by the loop"
    to="managing the data pointed to"
    :at="2"
    color="#bfdbfe"
  />
</p>

---
layout: center
---

# C++ Core Guidelines

**I.11: Never transfer ownership by a raw pointer (`T*`) or reference (`T&`)**

* **Alternative**: Pass ownership using a "smart pointer", such as `unique_ptr`
  (for exclusive ownership) and `shared_ptr` (for shared ownership).
  However, ...

<!-- The important take away is that the CCG frames smart as alternative to raw -->

---
layout: center
---

Naming conflict!

---
layout: two-cols
layoutClass: content-center
---

# C++ Core Guidelines

* `T*` is a raw pointer
* smart pointers are not

::right::

# C++ Seasoning

* smart pointers are raw pointers
* `T*` is not necessarily a raw pointer<br>
  (it may not hold ownership)

---
layout: center
---

# C++ Core Guidelines

**F.7: For general use, take `T*` or `T&` arguments rather than smart pointers**

**Reason** Passing a smart pointer transfers or shares ownership and should
only be used when ownership semantics are intended. A function that does not
manipulate lifetime should take raw pointers or references instead.

Passing by smart pointer restricts the use of a function to callers that use
smart pointers. A function that needs a widget should be able to accept any
widget object, not just ones whose lifetimes are managed by a particular kind
of smart pointer.

---
layout: two-cols
layoutClass: content-center
---

# C++ Core Guidelines

* `T*` is a raw pointer
* smart pointers are not

::right::

# C++ Seasoning

* smart pointers are raw pointers
* `T*` is not necessarily a raw pointer<br>
  (it may not hold ownership)

---
layout: center
---

We need a better Goal

---
layout: center
---

# Why Pointers

<v-clicks>

* details unknown
  * runtime dynamic count (container)
  * runtime dynamic type (polymorphism)
* details private
  * API/ABI stability
  * faster compilation (compiler firewall)
* complexity / stability requirement
  * $O(1)$ copy (views)
  * stability (list vs vector)
  * Deferral of rare and expensive work (copy-on-write)

</v-clicks>

---
layout: center
---

````md magic-move
```cpp
Type​* object = ...
```
```cpp
Type const​* object = ...
```
```cpp
std::shared_ptr​<Type​> object = ...
```
```cpp
std::shared_ptr​<Type const​> object = ...
```
```cpp
std::unique_ptr​<Type​> object = ...
```
```cpp
int object = ...
```
```cpp
Class object = ...
```
````

<ul>
  <ClickBullet :at="[1, 2, 3, 4, 5, 6]">Am I responsible for <code>delete</code>/<code>free</code>?</ClickBullet>
  <ClickBullet :at="[2, 3, 4, 5, 6]">What actions will cause this to dangle?</ClickBullet>
  <ClickBullet :at="[1, 3, 5]">Am I allowed to modify?</ClickBullet>
  <ClickBullet :at="[5]">What actions may cause a modification?</ClickBullet>
  <ClickBullet :at="[1, 3, 5]">Does modification require synchronization?</ClickBullet>
  <ClickBullet :at="[5]">Does reading require synchronization?</ClickBullet>
</ul>

---
layout: center
---

Does `Class` behave like `int`, or `Type*`?

---
layout: center
---

There is a single place to look at!

---
layout: center
---

Local Reasoning

---
layout: center
class: text-center
---

Require that a pointer be the only data member of a class?

<v-click>

No.

</v-click>
<v-click>

Example: A node class in a doubly linked list holds multiple pointers.<br>
Serves a single purpose. Allows local reasoning.

</v-click>

---
layout: center
class: text-center
---

Only allow pointers as class data members?

<v-click>

No.

</v-click>
<v-click>

A pointer that is local to a function still allows local reasoning.

</v-click>

---
layout: center
class: text-center
---

The ability for local reasoning ends as soon as a pointer is passed around.

<v-click>

Either as return type, or as function parameter.

</v-click>

---

<div class="absolute inset-0">
  <img src="/meme.png" class="w-full h-full object-cover" />
</div>

---
layout: center
---

The End

---
layout: center
---

Bonus Slides

---
layout: two-cols-header
layoutClass: gap-4
---

# Have you seen this pattern before?

::left::

```cpp
class Foo
{
public:
  using Ptr = std::shared_ptr<Foo>;

  Ptr Make();

private:
  Foo();
};
```

::right::

```cpp
{
  // This is prevented:
  // Foo* foo = new Foo;

  // This is allowed
  Foo::Ptr foo = Foo::Make();
}
```

---
layout: center
---

Start from scratch.

---
layout: two-cols-header
layoutClass: gap-4
---

# RAII: Resource Acquisition Is Initialization

::left::

<<< @/snippets/class/00-raii.cpp

::right::

````md magic-move
```cpp
{
  // Acquire a resource by initializion
  Foo foo;
}
```
```cpp
{
  // Acquire a resource by initializion
  Foo foo;

  // Release at destruction
}
```
```cpp
{
  // Acquire a resource by initializion
  Foo foo;

  if (...) {
    return;
  }

  // Release at destruction
}
```
```cpp
{
  // Acquire a resource by initializion
  Foo foo;

  if (...) {
    return;
  }

  if (...) {
    throw Error;
  }

  // Release at destruction
}
```
````

<v-click>

RAII provides *basic exception safety* guarantee.

</v-click>

---
layout: two-cols-header
layoutClass: gap-4
---

# Trick question: Can you see the bug?

::left::

<<< @/snippets/class/00-raii.cpp

::right::

---
layout: fact
---

A bug is a **defect** that may lead to a **fault**.

---
layout: two-cols-header
layoutClass: gap-4
---

# Trick question: Can you see the *defect*?

::left::

````md magic-move {at:5}
<<< @/snippets/class/00-raii.cpp
<<< @/snippets/class/01-provided.cpp {7-14}
````

::right::

````md magic-move
```cpp
{
  Foo a;
}
```
```cpp
{
  Foo a;
  Foo b = a;
}
```
```cpp
{
  Foo a;
  Foo b = a;
  // fault!
}
```
````

<v-clicks>

* The user code is correct.
* The destructor is correct.
* The defect is provided by the compiler!

</v-clicks>

---
layout: two-cols-header
layoutClass: gap-4
---

# Implementing copy

::left::

````md magic-move {at:0}
<<< @/snippets/class/01-provided.cpp {7-14}
<<< @/snippets/class/02-fixed-copy.cpp {8}
<<< @/snippets/class/02-fixed-copy.cpp {8}
<<< @/snippets/class/03-new-in-assign.cpp {12}
<<< @/snippets/class/04-del-in-assign.cpp {12,13}
<<< @/snippets/class/04-del-in-assign.cpp {12,13}
<<< @/snippets/class/05-cond-in-assign.cpp {12,15}
<<< @/snippets/class/06-temp-in-assign.cpp {13,15}
<<< @/snippets/class/07-custom-assign.cpp
````

::right::

````md magic-move {at:0}
```cpp
{
  Foo a;
  Foo b = a;
  // fault!
}
```
```cpp
{
  Foo a;
  Foo b = a;
}
```
```cpp
{
  Foo a;
  Foo b = a;
  a = b;
  // fault!
}
```
```cpp
{
  Foo a;
  Foo b = a;
  a = b;  // memory leak!
}
```
```cpp
{
  Foo a;
  Foo b = a;
  a = b;
}
```
```cpp
{
  Foo a;
  Foo b = a;
  a = b;
  a = a;  // fault!
}
```
```cpp
{
  Foo a;
  Foo b = a;
  a = b;
  a = a;
}
```
````

<v-switch>
  <template #0>Copy constructor causes fault!</template>
  <template #1>Copy constructor ok</template>
  <template #2>Assignment causes fault!</template>
  <template #3>Assignment causes leak!</template>
  <template #4>Assignment leak is fixed, but ...</template>
  <template #5>Assignment leak is fixed, but<br>self assignment causes fault</template>
  <template #6>Assignment is not exception safe</template>
  <template #7>Assignment is optimized for edge case</template>
  <template #8>Assignment ok</template>
</v-switch>

---
layout: center
---

# Rule of three (C++98 Guideline)

If a class requires a user-defined *destructor*, a user-defined *copy
constructor*, or a user-defined *copy assignment operator*, it almost certainly
requires *all three*.

---
layout: two-cols-header
layoutClass: gap-4
---

# Templates, beware!

::left::

<<< @/snippets/class/08-template.cpp

::right::

````md magic-move
```cpp
{
  Foo<float> a;
  Foo<double> b = a;
  Foo<float> c = a;
  // fault!
}
```
````

---
layout: center
---

A constructor template or assignment operator template\
does not inhibit the provision of the \
copy constructor or copy assignment operator.

---
layout: two-cols-header
layoutClass: gap-4
---

# C++11

::left::

````md magic-move
<<< @/snippets/class/07-custom-assign.cpp
<<< @/snippets/class/09-cpp11-move.cpp {18-30}
<<< @/snippets/class/10-cpp11-assert.cpp {8,13}
````

::right::

---
layout: two-cols-header
layoutClass: gap-4
---

# Reasoning about value semantics

::left::

````md magic-move
<<< @/snippets/class/10-cpp11-assert.cpp {*}
<<< @/snippets/class/11-equality.cpp {34-37}
<<< @/snippets/class/12-inequality.cpp {34-42}
<<< @/snippets/class/13-order.cpp {44-47}
<<< @/snippets/class/14-full-order.cpp {44-62}
````

::right::

````md magic-move
```cpp
{
  Foo a;
  Foo b = a;
  assert(b == a);
}
```
````

Required to reason about equality.

---
layout: center
---

Status: 66 Lines of pure boilerplate. No business logic yet.

---
layout: two-cols-header
layoutClass: gap-4
---

# `std::exchange` (C++14)

::left::

````md magic-move
<<< @/snippets/class/14-full-order.cpp {21-22,28-29}
<<< @/snippets/class/15-exchange.cpp {21,27}
````

::right::

---
layout: two-cols-header
layoutClass: gap-4
---

# `std::swap` (C++98)

::left::

````md magic-move
<<< @/snippets/class/15-exchange.cpp {13-17,25-29}
<<< @/snippets/class/16-swap1.cpp {13-15,23-27}
<<< @/snippets/class/16-swap2.cpp {13-15,23-25}
<<< @/snippets/class/17-copy-move.cpp {13,21-23}
````

::right::

---
layout: two-cols-header
layoutClass: gap-4
---

# `std::unique_ptr` (C++11), `std::make_unique` (C++14)

::left::

````md magic-move
<<< @/snippets/class/17-copy-move.cpp
<<< @/snippets/class/18-unique-ptr1.cpp {57}
<<< @/snippets/class/18-unique-ptr2.cpp {5}
<<< @/snippets/class/18-unique-ptr3.cpp {16}
<<< @/snippets/class/18-unique-ptr4.cpp {16-17}
<<< @/snippets/class/19-make-unique.cpp {4,9}
````

::right::

---
layout: two-cols-header
layoutClass: gap-4
---

# `operator<=>` (C++20)

::left::

````md magic-move
<<< @/snippets/class/19-make-unique.cpp {29-47}
<<< @/snippets/class/20-operators1.cpp {29-32}
<<< @/snippets/class/20-operators2.cpp {19-27}
````

::right::

---
layout: center
---

Down to 31 lines of boilerplate.

---
layout: two-cols-header
layoutClass: gap-4
---

# Business Logic

::left::

````md magic-move
<<< @/snippets/class/20-operators2.cpp {19-27}
<<< @/snippets/class/21-business-logic.cpp {29-37}
````

::right::

Prefer terms *observer* and *modifier*\
over *getter* and *setter*.

---
layout: two-cols-header
layoutClass: gap-4
---

# Constness Pitfall

::left::

````md magic-move
<<< @/snippets/class/21-business-logic.cpp {29-37}
<<< @/snippets/class/21-business-logic.cpp {31}
<<< @/snippets/class/22-impl-accessor1.cpp {40-48}
<<< @/snippets/class/22-impl-accessor2.cpp {30}
<<< @/snippets/class/22-impl-accessor3.cpp {20,24}
<<< @/snippets/class/22-impl-accessor4.cpp {8}
````

::right::

```cpp
struct FooImpl {
  std::size_t size() {
    std::println("I am mutable");
    return _size;
  }

  std::size_t size() const {
    std::println("I am const");
    return _size;
  }
};
```

<v-switch at="0">
  <template #1-3>I am mutable</template>
  <template #3>I am const</template>
</v-switch>

---
layout: center
---

**Optimization**: If the class does not have *modifiers*,
consider Transparent Sharing.

---
layout: two-cols-header
layoutClass: gap-4
---

# Optimization: Transparent Sharing

::left::

````md magic-move
<<< @/snippets/class/22-impl-accessor4.cpp {26-32}
<<< @/snippets/class/23-transparent-sharing0.cpp {26-28}
<<< @/snippets/class/23-transparent-sharing1.cpp {4}
<<< @/snippets/class/23-transparent-sharing2.cpp {36}
<<< @/snippets/class/23-transparent-sharing3.cpp {4}
<<< @/snippets/class/23-transparent-sharing5.cpp {7,8}
<<< @/snippets/class/23-transparent-sharing6.cpp {14}
````

::right::

<v-click>

* No difference in API
* Copy has $O(1)$ complexity (atomic increment)

</v-click>

---
layout: center
---

# Rule of zero

Classes that have custom *destructors*, *copy/move constructors* or *copy/move
assignment operators*<br>should deal exclusively with ownership (which follows from
the Single-responsibility principle).

Other classes should not have custom destructors, copy/move constructors<br>
or copy/move assignment operators.

---
layout: two-cols-header
layoutClass: gap-4
---

# `std::indirect` (C++26)

::left::

````md magic-move
<<< @/snippets/class/22-impl-accessor4.cpp {26-32}
<<< @/snippets/class/24-indirect0.cpp {45}
<<< @/snippets/class/24-indirect1.cpp {35}
<<< @/snippets/class/24-indirect2.cpp {27,31}
<<< @/snippets/class/24-indirect3.cpp {7,8}
<<< @/snippets/class/24-indirect4.cpp {13,14}
<<< @/snippets/class/24-indirect5.cpp {4}
<<< @/snippets/class/24-indirect6.cpp
````

::right::

* Reduce boilerplate
* Solve const propagation issue

---
layout: two-cols-header
layoutClass: gap-4
---

# `std::copy_on_write` (P4210)

::left::

````md magic-move
<<< @/snippets/class/24-indirect6.cpp
<<< @/snippets/class/25-copy-on-write0.cpp {18}
<<< @/snippets/class/25-copy-on-write1.cpp {14}
<<< @/snippets/class/25-copy-on-write2.cpp {17-23}
<<< @/snippets/class/25-copy-on-write3.cpp {22-28}
````

::right::

<v-clicks at="0">

- Copy has $O(1)$ complexity (atomic increment)
- `modify` copies `Impl` *iff* object is shared
- `modify` takes an *action*, ...
- ... and (optionally) a *transformation*.

</v-clicks>

---
layout: center
---

# Guidelines

* Wrap all pointers in custom classes with regular semantics.

---
layout: center
---

# Guidelines (pre C++26)

* Use `std::shared_ptr<T const>` for immutable types when copy<br>is more expensive than atomic increment.
* Otherwise, use `std::unique_ptr<T>`.

---
layout: center
---

# Guidelines (C++26)

* Use `std::shared_ptr<T const>` for immutable types when copy<br>is more expensive than atomic increment.
* Otherwise, use `std::indirect<T>` for things that you allocate.
* Use `std::unique_ptr<T>` with a custom deleter for wrapping C APIs.

---
layout: center
---

# Guidelines (Future)

* Use `std::copy_on_write<T>` when copy is more common than modifications
and copy is more expensive than atomic increment.

---
layout: center
---

And now for something completely different.

---
layout: two-cols-header
layoutClass: gap-4
---

# Runtime Polymorphism

::left::

<<< @/snippets/polymorphism/1.cpp

::right::

---
layout: center
---

# C++ Core Guideline

C.35: A base class destructor should be either public and virtual, or protected and non-virtual

**Reason** To prevent undefined behavior. If the destructor is public, then
calling code can attempt to destroy a derived class object through a base class
pointer, and the result is undefined if the base class’s destructor is
non-virtual. If the destructor is protected, then calling code cannot destroy
through a base class pointer and the destructor does not need to be virtual; it
does need to be protected, not private, so that derived destructors can invoke
it. In general, the writer of a base class does not know the appropriate action
to be done upon destruction.

---
layout: two-cols-header
layoutClass: gap-4
---

# Runtime Polymorphism

::left::

````md magic-move
<<< @/snippets/polymorphism/1.cpp
<<< @/snippets/polymorphism/2.cpp
````

::right::

---
layout: center
---

# C++ Core Guideline

C.67: A polymorphic class should suppress public copy/move

**Reason** A *polymorphic class* is a class that defines or inherits at least
one virtual function. It is likely that it will be used as a base class for
other derived classes with polymorphic behavior. If it is accidentally passed by
value, with the implicitly generated copy constructor and assignment, we risk
slicing: only the base portion of a derived object will be copied, and the
polymorphic behavior will be corrupted.

If the class has no data, `=delete` the copy/move functions. Otherwise, make
them protected.

---
layout: two-cols-header
layoutClass: gap-4
---

# Runtime Polymorphism

::left::

````md magic-move
<<< @/snippets/polymorphism/2.cpp
<<< @/snippets/polymorphism/3.cpp
<<< @/snippets/polymorphism/4.cpp
````

::right::

<v-switch at="0">
  <template #2>

**Non-Virtual Interface (NVI)**:

separate the specification of interface from the specification of the
implementation's customizable behavior

  </template>
</v-switch>

---
layout: center
---

<div class="absolute inset-0 flex items-center justify-center">
  <img src="/nvi.png" class="h-full object-cover" />
</div>

---
layout: two-cols-header
layoutClass: gap-4
---

# Runtime Polymorphism

::left::

````md magic-move {at:0}
<<< @/snippets/polymorphism/4.cpp
<<< @/snippets/polymorphism/3.cpp
<<< @/snippets/polymorphism/5.cpp {9}
````

::right::

<v-switch at="0">
  <template #2>

Should `virtual` functions be `const`?

  </template>
</v-switch>

---
layout: two-cols-header
layoutClass: gap-4
---

# Runtime Polymorphism

::left::

````md magic-move {at:0}
<<< @/snippets/polymorphism/5.cpp {9}
<<< @/snippets/polymorphism/const/1.cpp {12-24}
<<< @/snippets/polymorphism/const/1.cpp {12-24}
<<< @/snippets/polymorphism/const/1.cpp {12-24}
<<< @/snippets/polymorphism/const/1.cpp {12-24}
````

::right::

<v-switch at="0">
  <template #0>

<<< @/snippets/polymorphism/3.cpp {9}

  </template>
  <template #2>

Sean Parent: "I am not convinced that polymorphism ever requries mutability".

  </template>
  <template #3>

But: Why decide in a base class whether a derived class may modify its data members?

  </template>
  <template #4>

We should be able to archive indepencence with copying!

  </template>
</v-switch>

---
layout: two-cols-header
layoutClass: gap-4
---

# Runtime Polymorphism (C++26)

::left::

````md magic-move {at:0}
<<< @/snippets/polymorphism/const/1.cpp {12-24}
<<< @/snippets/polymorphism/const/1.cpp {12-24}
<<< @/snippets/polymorphism/const/1.cpp {12-24}
````

::right::

````md magic-move {at:0}
<<< @/snippets/polymorphism/3.cpp {6,7}
<<< @/snippets/polymorphism/2.cpp
<<< @/snippets/polymorphism/mutable/1.cpp {9-21}
````

---
layout: center
---

# Guidelines

<v-clicks>

* Wrap all pointers in custom classes with regular semantics.
* For polymorphic types,
  * implement in terms of `std::shared_ptr<Base const>` when all `virtual` functions are `const`,
  * otherwise, use `std::polymorphic<Base>`.
* I call this the NVI 2.0.
  * The specification of the interface and the specification of the
    implementation's customizable behavior are in two distinct classes.

</v-clicks>

---
layout: center
---

Neither `std::shared_ptr<Base const>` nor `std::polymorphic<Base>`<br>
destroys the object through `Base` pointer!

---
layout: center
---

A base class destructor should be <del>either public and virtual, or</del> protected and non-virtual.

---
layout: two-cols-header
layoutClass: gap-4
---

# Runtime Polymorphism (C++26)

::left::

````md magic-move {at:0}
<<< @/snippets/polymorphism/const/1.cpp {4}
<<< @/snippets/polymorphism/const/2.cpp {3,4}
````

::right::

````md magic-move {at:0}
<<< @/snippets/polymorphism/mutable/1.cpp {4}
<<< @/snippets/polymorphism/mutable/2.cpp {3,4}
````

---
layout: two-cols-header
layoutClass: gap-4
---

# Why inheritance and `virtual` functions at all?

::left::

```cpp
struct Container
{
  auto size()  const -> std::size_t;
  auto empty() const -> bool;
  auto clear()       -> void;
};

rjk::duck<Container> d{std::vector{1, 2, 3}};
d.size(); // 3
d = std::string{"hello"}; // swap type at runtime
d.size(); // 5
d = std::map<int, int>{{1, 2}, {3, 4}};
d.empty(); // false
d.clear();
d.empty(); // true
```

::right::

`std::vector`, `std::string`, and `std::map` are structural subtypes of `Container` according to LSP.

---
layout: center
---

# Summary

* Pointers - smart or not - shall not appear in function signatures.
* Wrap pointer in custom classes with regular semantics.
  * `std::shared_ptr` and `std::unique_ptr` are useful building blocks.
  * `std::indirect` and `std::polymorphic` are better building blocks.
  * More building blocks are needed.

---

<div class="absolute inset-0">
  <img src="/meme.png" class="w-full h-full object-cover" />
</div>
