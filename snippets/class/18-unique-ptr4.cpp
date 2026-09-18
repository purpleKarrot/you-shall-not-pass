class Foo
{
public:
  Foo() { _impl = new FooImpl; }
  ~Foo() = default;

  Foo(Foo const& other) {
    assert(other._impl);
    _impl = new FooImpl(*other._impl);
  }

  Foo& operator=(Foo const& other) {
    return *this = Foo(other);
  }

  Foo(Foo&& other) noexcept = default;
  Foo& operator=(Foo&& other) noexcept = default;

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
