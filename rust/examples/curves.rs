use tinyeasings::{ease, ALL_CURVES};
fn main() {
    for curve in ALL_CURVES {
        println!("{}: {}", curve.name(), ease(curve, 0.25_f64));
    }
}
