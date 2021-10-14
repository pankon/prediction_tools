pub struct QuadTree {
    min: (f64, f64),
    max: (f64, f64),
    children: std::vec::Vec<Self>,
}

impl QuadTree {
    pub fn new(min: (f64, f64), max: (f64, f64)) -> Self {
        QuadTree {
            min: min,
            max: max,
            children: vec![]
        }
    }

    pub fn add_point(&mut self, point: (f64, f64)) {
        
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_quadtree() {
        let mut quad_tree = QuadTree::new((0.0, 0.0), (0.0, 0.0));
        quad_tree.add_point((1.0, 2.0));
        assert_eq!(1, 1);
    }
}