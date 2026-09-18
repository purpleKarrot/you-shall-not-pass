class Foo
{
public:
  Foo() { _impl = new FooImpl; }
  ~Foo() { delete _impl; }

  Foo(Foo const& other) {
    _impl = new FooImpl(*other._impl);
  }

  Foo& operator=(Foo const& other) {
    if (this != &other) {
      delete _impl;
      _impl = new FooImpl(*other._impl);
    }
    return *this;
  }

private:
  FooImpl* _impl;
};
