class Foo
{
public:
  Foo(std::size_t s) : _impl{std::make_unique<FooImpl>(s)} {}
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
    return impl().size() != 0;
  }

private:
  FooImpl const& impl() const {
    assert(_impl);
    return *_impl;
  }

  std::unique_ptr<FooImpl> _impl;
};
