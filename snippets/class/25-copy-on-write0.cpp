class Foo
{
public:
  Foo(std::size_t s) : _impl{std::in_place, s} {}

  bool operator==(Foo const& other) const = default;
  auto operator<=>(Foo const& other) const = default;

  bool empty() const {
    return _impl->size() != 0;
  }

  void resize(std::size_t s) {
    _impl->resize(s);
  }

private:
  std::copy_on_write<FooImpl> _impl;
};
