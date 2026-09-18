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
    return *this = Foo(other);
  }

  Foo(Foo&& other) noexcept {
    _impl = std::exchange(other._impl, nullptr);
  }

  Foo& operator=(Foo&& other) noexcept {
    Foo tmp(std::move(other));
    std::swap(_impl, tmp._impl);
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
  std::unique_ptr<FooImpl> _impl;
};
