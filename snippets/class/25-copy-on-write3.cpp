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
    _impl.modify([&](auto& impl) { impl.resize(s); });
  }

  void push_front(int val) {
    _impl.modify(
      [&](std::vector<int>& impl) {
        impl.push_front(val);
      },
      [&](std::vector<int> const& impl) {
        auto r = std::vector<int>{};
        r.reserve(impl.size() + 1);
        r.insert(r.end(), val);
        r.insert(r.end(), impl.begin(), impl.end());
        return r;
      }
    );
  }

private:
  std::copy_on_write<std::vector<int>> _impl;
};
