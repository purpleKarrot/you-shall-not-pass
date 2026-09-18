class Foo
{
public:
  Foo() : _impl{std::make_unique<FooImpl>()} {}
  ~Foo() = default;

  Foo(Foo const& other)
    : _impl{std::make_unique<FooImpl>(other.impl())}
  {}

  Foo& operator=(Foo const& other) {
    return *this = Foo(other);
  }

  Foo(Foo&& other) noexcept = default;
  Foo& operator=(Foo&& other) noexcept = default;

  bool operator==(Foo const& other) const {
    return impl() == other.impl();
  }

  auto operator<=>(Foo const& other) const {
    return impl() <=> other.impl();
  }

  bool empty() const {
    return _impl->size() != 0;
  }

  void resize(std::size_t s) {
    _impl->resize(s);
  }

private:
  std::indirect<FooImpl> _impl;
};
