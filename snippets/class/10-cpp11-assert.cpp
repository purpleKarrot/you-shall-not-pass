class Foo
{
public:
  Foo() { _impl = new FooImpl; }
  ~Foo() { delete _impl; }

  Foo(Foo const& other) {
    assert(other._impl);
    _impl = new FooImpl(*other._impl);
  }

  Foo& operator=(Foo const& other) {
    assert(other._impl);
    FooImpl* tmp = new FooImpl(*other._impl);
    delete _impl;
    _impl = tmp;
    return *this;
  }

  Foo(Foo&& other) noexcept {
    _impl = other._impl;
    other._impl = nullptr;
  }

  Foo& operator=(Foo&& other) noexcept {
    if (this != &other) {
      delete _impl;
      _impl = other._impl;
      other._impl = nullptr;
    }
    return *this;
  }

private:
  FooImpl* _impl;
};
