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
    Foo tmp(other);
    std::swap(_impl, tmp._impl);
    return *this;
  }

  Foo(Foo&& other) noexcept {
    _impl = std::exchange(other._impl, nullptr);
  }

  Foo& operator=(Foo&& other) noexcept {
    if (this != &other) {
      delete _impl;
      _impl = std::exchange(other._impl, nullptr);
    }
    return *this;
  }

  bool operator==(Foo const& other) const {
    assert(_impl && other._impl);
    return *_impl == *other._impl;
  }

  bool operator!=(Foo const& other) const {
    assert(_impl && other._impl);
    return *_impl != *other._impl;
  }

  bool operator<(Foo const& other) const {
    assert(_impl && other._impl);
    return *_impl < *other._impl;
  }

  bool operator<=(Foo const& other) const {
    assert(_impl && other._impl);
    return *_impl <= *other._impl;
  }

  bool operator>(Foo const& other) const {
    assert(_impl && other._impl);
    return *_impl > *other._impl;
  }

  bool operator>=(Foo const& other) const {
    assert(_impl && other._impl);
    return *_impl >= *other._impl;
  }

private:
  FooImpl* _impl;
};
