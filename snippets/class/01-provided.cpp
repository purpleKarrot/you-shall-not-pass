class Foo
{
public:
  Foo() { _impl = new FooImpl; }
  ~Foo() { delete _impl; }

  Foo(Foo const& other) {
    _impl = other._impl;
  }

  Foo& operator=(Foo const& other) {
    _impl = other._impl;
    return *this;
  }

private:
  FooImpl* _impl;
};
