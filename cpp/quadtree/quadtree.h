#ifndef CPP_QUADTREE_H_
#define CPP_QUADTREE_H_

#include <vector>

#include "point.h"

namespace PredictionTools {

template <typename T>
class QuadTree {
public:
    QuadTree(const std::vector<T>& min, const std::vector<T>& max);
    ~QuadTree();

    bool AddPoint(const std::vector<T>& point);

    std::vector<std::vector<T>> FindBetween(const std::vector<T>& min, const std::vector<T>& max);
    int CountBetween(const std::vector<T>& min, const std::vector<T>& max);

    int CountChildrenAtLevel(int level);
private:
    QuadTree(const std::vector<T>& min, const std::vector<T>& max, int level);
    void CalculateBounds(int bucket, std::vector<T>& child_min, std::vector<T>& child_max, 
                         int i);

    // position and splitting information
    const std::vector<T>& min_;
    const std::vector<T>& max_;
    const std::vector<T>& center_;

    // data and children
    int level_;
    std::vector<QuadTree<T>*> children_;
    std::vector<T>* data_point_;

    /*
     * clockwise
     * other.x > this.x - first bit
     * other.y > this.y - second bit
     * if both are false, return 4
     * if equal, return 0 as per strcmp convention
     * so to use for a bucket, use:
     *      int idx = center.Compare(other_pt) - 1;
     * 
     * 0000 equal
     *
     * 0001 other.x > this.x && other.y < this.y
     * 0011 other.x > this.x && other.y > this.y
     *
     * 0010 other.x < this.x && other.y > this.y
     * 0100 other.x < this.x && other.y < this.y
     */
    int Compare(const std::vector& point1, const std::vector& point2) const {
        int n_dimensions = point1.size();
        if (n_dimensions != point2.size()) {
            // don't compare two points without equal dimension
            return -1;
        }
        
        int equal_count = 0;
        int bucket = 0;

        int temp_diff = 0;
        for (int i = 0; n_dimensions > i; ++i) {
            temp_diff = point2[i] - point1[i];
            equal_count += (int)(temp_diff == 0);
            bucket |= (temp_diff > 0) << i;
        }

        if (n_dimensions == equal_count) {
            return 0;
        }

        // I realize there is a penalty for
        // not making eq == 4
        // I think it is worth it for the gain
        // in potential user intuition
        if (0 == bucket) {
            return 1 << (n_dimensions + 1); // 4
        }

        // if eq == 4, one if would be cut out
        return bucket;
    }
};

}

#endif // CPP_QUADTREE_H_