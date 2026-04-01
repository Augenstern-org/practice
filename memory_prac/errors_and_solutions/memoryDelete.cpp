class Data {
  private:
    char c;
    int i;
    double d;

  public:
    Data(char _c, int _i, double _d) : c(_c), i(_i), d(_d) {}
    ~Data() = default;
};

class MyClass {
  public:
    MyClass(char _c, int _i, double _d, char _c_, int _i_)
        : other_char(_c_), other_int(_i_) {
        d = new Data(_c, _i, _d);
    }
    // 这里如果不禁止拷贝或者设置为深拷贝，d会二次释放
    MyClass(const MyClass& m)
        : other_char(m.other_char), other_int(m.other_int) {
        d = new Data(*(m.d));
    }
    ~MyClass() {
        if (d != nullptr) {
            delete d;
            d = nullptr;
        }
    }

  private:
    char other_char;
    int other_int;
    Data* d;
};

int main() {
    MyClass m = MyClass('a', 1, 3.25, 'i', 0);
    MyClass m2(m);
    return 0;
}