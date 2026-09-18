class IWidget
{
public:
  virtual ~IWidget() = default;

  virtual void foo() = 0;
};
