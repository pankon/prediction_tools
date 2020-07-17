#ifndef CPP_POINT_H_
#define CPP_POINT_H_

#include <vector>

class Point {
public:
    Point(const std::vector<int> points) : values_(points), n_dimensions_(points.size()) {}
    Point(int n_dimensions) : values_(n_dimensions, 0), n_dimensions_(n_dimensions) {} 
    ~Point();

    int& operator[](int i) { return values_[i]; }

    int GetDimension() { return n_dimensions_; } const
    inline const int& Get(int dimension) { return values_[dimension]; }
    inline void Set(int dimension, int value) { values_[dimension] = value; }

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
    int Compare(const Point& other) const {
        if (other.values_.size() != values_.size()) {
            // don't compare two points without equal dimension
            return -1;
        }

        int equal_count = 0;
        int bucket = 0;

        int temp_diff = 0;
        for (int i = 0; n_dimensions_ > i; ++i) {
            temp_diff = other.values_[i] - values_[i];
            equal_count += (int)(temp_diff == 0);
            bucket |= (temp_diff > 0) << i;
        }

        if (n_dimensions_ == equal_count) {
            return 0;
        }

        // I realize there is a penalty for
        // not making eq == 4
        // I think it is worth it for the gain
        // in potential user intuition
        if (0 == bucket) {
            return 1 << (n_dimensions_ + 1); // 4
        }

        // if eq == 4, one if would be cut out
        return bucket;
    }

private:
    Point(const Point&) {}
    int n_dimensions_;
    std::vector<int> values_; 
};

#endif // CPP_POINT_H_