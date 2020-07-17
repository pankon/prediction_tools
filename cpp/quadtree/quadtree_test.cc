#include "quadtree.h"

using namespace PredictionTools;

int test_quadtree_add(QuadTree<int> &quadtree) {
    return (int)quadtree.AddPoint(std::vector<int> {5, 5});
}

int main() {
    QuadTree<int> tester(std::vector<int> {0, 0}, std::vector<int> {100, 100});

    test_quadtree_add(tester);

    return 0;
}