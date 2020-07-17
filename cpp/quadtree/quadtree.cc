#include "quadtree.h"

namespace PredictionTools {

template <typename T>
std::vector<T> dot(std::vector<T> point1, std::vector<T> point2) {
    int n_dimensions = point1.size();
    if (n_dimensions != point2.size()) {
        throw new Exception("cannot add two unequal vectors");
    }

    // todo: should this be on the heap / std::unique_ptr?
    std::vector<T> out(point1); 
    for (int i = 0; i < point1.size(); ++i) {
        out[i] += point2[i];
    }
    return out;
}

template <typename T>
QuadTree<T>::QuadTree(const std::vector<T>& min, const std::vector<T>& max) 
    : min_(min), max_(max), center_((max + min) / 2), data_point_(0), level_(0) {

}


template <typename T>
QuadTree<T>::QuadTree(const std::vector<T>& min, const std::vector<T>& max, 
                      int level) 
    : min_(min), max_(max), center_((max + min) / 2), data_point_(0), level_(level) {
}

template <typename T>
QuadTree<T>::~QuadTree() {
    for (std::vector<QuadTree<T>*>::iterator it = children_.begin();
         children_.end() != it; 
         ++it) {
             delete *it;
             *it = 0;
         }
}

template <typename T>
void QuadTree<T>::CalculateBounds(int bucket, std::vector<T>& child_min, std::vector<T>& child_max, int i) {
    if (0 == bucket & 0) {
        child_min[i] = min_[i];
        child_max[i] = center_[i];
    } else {
        child_min[i] = center_[i];
        child_max[i] = max_[i];
    }
}

template <typename T>
bool QuadTree<T>::AddPoint(const std::vector<T>& point) {
    int bucket = Compare(center_, point);
    if (0 == bucket) {
        data_point_ = point; // pointer to reference?
        return true;
    }

    if (0 > bucket) {
        // this includes the case where our points
        // are not of the same dimension
        return false;
    }

    bucket -= 1;

    if (children_.size() > bucket) {
        QuadTree<T>* bucket = children_[bucket];
        if (NULL != bucket) {
            return children_[bucket]->AddPoint(point);
        }
    }

    // ensure that the vector has enough space
    for (int i = 0; i < bucket; i++) {
        if (children_.size() < i) {
            children_.push_back(0);
        }
    }

    Point child_min(center_.size(), 0);
    Point child_max(center_.size(), 0);

    for (int i = 0; 2 > i; ++i) {
        CalculateBounds(bucket, child_min, child_max, 0);
    }
    
    children_[bucket] = new QuadTree(child_min, child_max);
}

template <typename T>
std::vector<std::vector<T>> QuadTree<T>::FindBetween(const std::vector<T>& min, 
                                                     const std::vector<T>& max) {
    return std::vector<std::vector<T>>();
}

template <typename T>
int QuadTree<T>::CountBetween(const std::vector<T>& min, 
                           const std::vector<T>& max) {
    return 0;
}

template <typename T>
int QuadTree<T>::CountChildrenAtLevel(int level) {
    return 0;
}

}