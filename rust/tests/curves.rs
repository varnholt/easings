use tinyeasings::*;
#[test]
fn exact_endpoints_and_runtime_selection() {
    let mut names = std::collections::HashSet::new();
    for (index, curve) in ALL_CURVES.into_iter().enumerate() {
        assert_eq!(Curve::try_from(index as u8), Ok(curve));
        assert!(names.insert(curve.name()));
        assert_eq!(ease(curve, 0f32), 0.);
        assert_eq!(ease(curve, 1f32), 1.);
        assert_eq!(ease(curve, 0f64), 0.);
        assert_eq!(ease(curve, 1f64), 1.);
    }
    assert!(Curve::try_from(30).is_err());
    assert!(Curve::try_from(255).is_err());
}
#[test]
fn symmetry_and_precision() {
    for family in ALL_CURVES.chunks_exact(3) {
        for i in 0..=100 {
            let x = i as f64 / 100.;
            assert!((ease(family[1], x) - (1. - ease(family[0], 1. - x))).abs() < 1e-9);
            for &curve in family {
                assert!((f64::from(ease(curve, x as f32)) - ease(curve, x)).abs() < 1e-5);
            }
        }
    }
}
#[test]
fn polynomial_const_functions_and_overshoot() {
    const QUAD: f64 = tinyeasings::f64::ease_in_quad(0.5);
    const BOUNCE: f32 = tinyeasings::f32::ease_out_bounce(0.5);
    assert_eq!(QUAD, 0.25);
    assert_eq!(BOUNCE, 0.765625);
    assert!(ease_out_back(0.5_f64) > 1.);
    assert!(ease_in_elastic(0.9_f64) < 0.);
    assert_eq!(ease_in_quad(2_f32), 4.);
}
#[test]
fn nonfinite_input_is_not_clamped() {
    assert!(ease_in_sine(f64::NAN).is_nan());
    assert!(ease_in_circ(2_f64).is_nan());
}
