template <typename T>
class Foo
{
public:
  Foo() { _impl = new FooImpl<T>; }
  ~Foo() { delete _impl; }

  template <typename U>
  Foo(Foo<U> const& other) {
    _impl = new FooImpl<T>(*other._impl);
  }

  template <typename U>
  Foo& operator=(Foo<U> const& other) { ... }

private:
  FooImpl<T>* _impl;
};
