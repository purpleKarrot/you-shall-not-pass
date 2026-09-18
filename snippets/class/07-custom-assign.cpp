class Foo
{
public:
  Foo() { _impl = new FooImpl; }
  ~Foo() { delete _impl; }

  Foo(Foo const& other) {
    _impl = new FooImpl(*other._impl);
  }

  Foo& operator=(Foo const& other) {
    FooImpl* tmp = new FooImpl(*other._impl);
    delete _impl;
    _impl = tmp;
    return *this;
  }

private:
  FooImpl* _impl;
};
