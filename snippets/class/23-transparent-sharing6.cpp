class Foo
{
public:
  Foo(std::size_t s) : _impl{std::make_shared<FooImpl>(s)} {}
  ~Foo() = default;

  Foo(Foo const& other) = default;
  Foo& operator=(Foo const& other) = default;

  Foo(Foo&& other) noexcept = default;
  Foo& operator=(Foo&& other) noexcept = default;

  bool operator==(Foo const& other) const {
    return _impl == other._impl || impl() == other.impl();
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

  std::shared_ptr<FooImpl const​> _impl;
};
