class IWidget
{
public:
  virtual ~IWidget() = default;

  IWidget(IWidget const&) = delete;
  IWidget& operator=(IWidget const&) = delete;

  virtual void foo() const = 0;
};
