pub mod fractal_dimension;
pub mod quadtree;

pub struct TimeSeries {
    values: std::vec::Vec<(f64, f64)>
}

impl TimeSeries {   
    pub fn new() -> Self {
        TimeSeries {
            values: vec![],
        }
    }

    pub fn add(&mut self, time: f64, value: f64) {
        self.values.push((time, value));
    }

    pub fn len(&self) -> usize {
        self.values.len()
    }

    pub fn subarray(&mut self, start: usize, end: usize) -> Self {
        TimeSeries{
            values: self.values.drain(start..end).collect(),
        }
    }
}


#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn test_basic_add() {
        let mut series = TimeSeries::new();
        series.add(0.1232, 123.0);
        assert_eq!(1, series.len());
        series.add(0.1233, 124.0);
        assert_eq!(2, series.len());
        let subarray = series.subarray(1, 2);
        assert_eq!((0.1233, 124.0), subarray.values[0]);
    }
}