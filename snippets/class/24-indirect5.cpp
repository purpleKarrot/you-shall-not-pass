class Foo
{
public:
  Foo(std::size_t s) : _impl{std::in_place, s} {}
  ~Foo() = default;

  Foo(Foo const& other) = default;
  Foo& operator=(Foo const& other) = default;

  Foo(Foo&& other) noexcept = default;
  Foo& operator=(Foo&& other) noexcept = default;

  bool operator==(Foo const& other) const = default;
  auto operator<=>(Foo const& other) const = default;

  bool empty() const {
    return _impl->size() != 0;
  }

  void resize(std::size_t s) {
    _impl->resize(s);
  }

private:
  std::indirect<FooImpl> _impl;
};
