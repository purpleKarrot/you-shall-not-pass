class Foo
{
public:
  Foo() { _impl = new FooImpl; }
  ~Foo() { delete _impl; }

private:
  FooImpl* _impl;
};
