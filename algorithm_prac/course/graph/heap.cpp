#include <vector>

class Heap {
    std::vector<int> data;

  public:
    Heap() {}

    int left_child(int i) const { return data[i * 2 + 1]; }
    
};