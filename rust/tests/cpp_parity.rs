use tinyeasings::{ease, Curve};
#[test]
fn all_curves_match_cpp_at_101_samples_in_both_precisions() {
    let mut count = 0;
    for line in include_str!("data/cpp_reference.txt").lines() {
        let mut words = line.split_whitespace();
        let curve = Curve::try_from(words.next().unwrap().parse::<u8>().unwrap()).unwrap();
        let x: f64 = words.next().unwrap().parse().unwrap();
        let expected: f64 = words.next().unwrap().parse().unwrap();
        let expected_f32: f32 = words.next().unwrap().parse().unwrap();
        let actual = ease(curve, x);
        let actual_f32 = ease(curve, x as f32);
        assert!(
            (actual - expected).abs() < 1e-12,
            "{curve:?} at {x}: {actual} != {expected}"
        );
        assert!(
            (actual_f32 - expected_f32).abs() < 2e-6,
            "{curve:?} f32 at {x}: {actual_f32} != {expected_f32}"
        );
        count += 1;
    }
    assert_eq!(count, 3030);
}
