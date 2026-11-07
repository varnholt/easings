//! All 30 easings.net curves, for `f32` and `f64`, with no dependencies.
//!
//! Inputs are not clamped. Back and elastic curves intentionally overshoot.
//!
//! ```
//! use tinyeasings::{ease, ease_out_bounce, Curve};
//! assert_eq!(ease_out_bounce(0.5_f64), 0.765625);
//! let y: f32 = ease(Curve::InOutCubic, 0.5);
//! assert_eq!(y, 0.5);
//! const QUARTER: f64 = tinyeasings::f64::ease_in_quad(0.5);
//! assert_eq!(QUARTER, 0.25);
//! ```

#[derive(Clone, Copy, Debug, PartialEq, Eq, Hash)]
#[repr(u8)]
pub enum Curve {
    InSine,
    OutSine,
    InOutSine,
    InQuad,
    OutQuad,
    InOutQuad,
    InCubic,
    OutCubic,
    InOutCubic,
    InQuart,
    OutQuart,
    InOutQuart,
    InQuint,
    OutQuint,
    InOutQuint,
    InExpo,
    OutExpo,
    InOutExpo,
    InCirc,
    OutCirc,
    InOutCirc,
    InBack,
    OutBack,
    InOutBack,
    InElastic,
    OutElastic,
    InOutElastic,
    InBounce,
    OutBounce,
    InOutBounce,
}
pub const CURVE_COUNT: usize = 30;
pub const ALL_CURVES: [Curve; CURVE_COUNT] = [
    Curve::InSine,
    Curve::OutSine,
    Curve::InOutSine,
    Curve::InQuad,
    Curve::OutQuad,
    Curve::InOutQuad,
    Curve::InCubic,
    Curve::OutCubic,
    Curve::InOutCubic,
    Curve::InQuart,
    Curve::OutQuart,
    Curve::InOutQuart,
    Curve::InQuint,
    Curve::OutQuint,
    Curve::InOutQuint,
    Curve::InExpo,
    Curve::OutExpo,
    Curve::InOutExpo,
    Curve::InCirc,
    Curve::OutCirc,
    Curve::InOutCirc,
    Curve::InBack,
    Curve::OutBack,
    Curve::InOutBack,
    Curve::InElastic,
    Curve::OutElastic,
    Curve::InOutElastic,
    Curve::InBounce,
    Curve::OutBounce,
    Curve::InOutBounce,
];
impl Curve {
    pub const fn name(self) -> &'static str {
        match self {
            Self::InSine => "easeInSine",
            Self::OutSine => "easeOutSine",
            Self::InOutSine => "easeInOutSine",
            Self::InQuad => "easeInQuad",
            Self::OutQuad => "easeOutQuad",
            Self::InOutQuad => "easeInOutQuad",
            Self::InCubic => "easeInCubic",
            Self::OutCubic => "easeOutCubic",
            Self::InOutCubic => "easeInOutCubic",
            Self::InQuart => "easeInQuart",
            Self::OutQuart => "easeOutQuart",
            Self::InOutQuart => "easeInOutQuart",
            Self::InQuint => "easeInQuint",
            Self::OutQuint => "easeOutQuint",
            Self::InOutQuint => "easeInOutQuint",
            Self::InExpo => "easeInExpo",
            Self::OutExpo => "easeOutExpo",
            Self::InOutExpo => "easeInOutExpo",
            Self::InCirc => "easeInCirc",
            Self::OutCirc => "easeOutCirc",
            Self::InOutCirc => "easeInOutCirc",
            Self::InBack => "easeInBack",
            Self::OutBack => "easeOutBack",
            Self::InOutBack => "easeInOutBack",
            Self::InElastic => "easeInElastic",
            Self::OutElastic => "easeOutElastic",
            Self::InOutElastic => "easeInOutElastic",
            Self::OutBounce => "easeOutBounce",
            Self::InBounce => "easeInBounce",
            Self::InOutBounce => "easeInOutBounce",
        }
    }
    pub fn sample<T: Float>(self, x: T) -> T {
        T::evaluate(self, x)
    }
}
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct InvalidCurve(pub u8);
impl std::fmt::Display for InvalidCurve {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "curve index {} is outside 0..30", self.0)
    }
}
impl std::error::Error for InvalidCurve {}
impl TryFrom<u8> for Curve {
    type Error = InvalidCurve;
    fn try_from(value: u8) -> Result<Self, Self::Error> {
        ALL_CURVES
            .get(value as usize)
            .copied()
            .ok_or(InvalidCurve(value))
    }
}
mod sealed {
    pub trait Sealed {}
    impl Sealed for f32 {}
    impl Sealed for f64 {}
}
/// Supported scalar types: `f32` and `f64`.
pub trait Float: sealed::Sealed + Copy {
    fn evaluate(curve: Curve, x: Self) -> Self;
}
pub fn ease<T: Float>(curve: Curve, x: T) -> T {
    T::evaluate(curve, x)
}
pub const fn name(curve: Curve) -> &'static str {
    curve.name()
}
pub fn ease_in_sine<T: Float>(x: T) -> T {
    ease(Curve::InSine, x)
}
pub fn ease_out_sine<T: Float>(x: T) -> T {
    ease(Curve::OutSine, x)
}
pub fn ease_in_out_sine<T: Float>(x: T) -> T {
    ease(Curve::InOutSine, x)
}
pub fn ease_in_quad<T: Float>(x: T) -> T {
    ease(Curve::InQuad, x)
}
pub fn ease_out_quad<T: Float>(x: T) -> T {
    ease(Curve::OutQuad, x)
}
pub fn ease_in_out_quad<T: Float>(x: T) -> T {
    ease(Curve::InOutQuad, x)
}
pub fn ease_in_cubic<T: Float>(x: T) -> T {
    ease(Curve::InCubic, x)
}
pub fn ease_out_cubic<T: Float>(x: T) -> T {
    ease(Curve::OutCubic, x)
}
pub fn ease_in_out_cubic<T: Float>(x: T) -> T {
    ease(Curve::InOutCubic, x)
}
pub fn ease_in_quart<T: Float>(x: T) -> T {
    ease(Curve::InQuart, x)
}
pub fn ease_out_quart<T: Float>(x: T) -> T {
    ease(Curve::OutQuart, x)
}
pub fn ease_in_out_quart<T: Float>(x: T) -> T {
    ease(Curve::InOutQuart, x)
}
pub fn ease_in_quint<T: Float>(x: T) -> T {
    ease(Curve::InQuint, x)
}
pub fn ease_out_quint<T: Float>(x: T) -> T {
    ease(Curve::OutQuint, x)
}
pub fn ease_in_out_quint<T: Float>(x: T) -> T {
    ease(Curve::InOutQuint, x)
}
pub fn ease_in_expo<T: Float>(x: T) -> T {
    ease(Curve::InExpo, x)
}
pub fn ease_out_expo<T: Float>(x: T) -> T {
    ease(Curve::OutExpo, x)
}
pub fn ease_in_out_expo<T: Float>(x: T) -> T {
    ease(Curve::InOutExpo, x)
}
pub fn ease_in_circ<T: Float>(x: T) -> T {
    ease(Curve::InCirc, x)
}
pub fn ease_out_circ<T: Float>(x: T) -> T {
    ease(Curve::OutCirc, x)
}
pub fn ease_in_out_circ<T: Float>(x: T) -> T {
    ease(Curve::InOutCirc, x)
}
pub fn ease_in_back<T: Float>(x: T) -> T {
    ease(Curve::InBack, x)
}
pub fn ease_out_back<T: Float>(x: T) -> T {
    ease(Curve::OutBack, x)
}
pub fn ease_in_out_back<T: Float>(x: T) -> T {
    ease(Curve::InOutBack, x)
}
pub fn ease_in_elastic<T: Float>(x: T) -> T {
    ease(Curve::InElastic, x)
}
pub fn ease_out_elastic<T: Float>(x: T) -> T {
    ease(Curve::OutElastic, x)
}
pub fn ease_in_out_elastic<T: Float>(x: T) -> T {
    ease(Curve::InOutElastic, x)
}
pub fn ease_out_bounce<T: Float>(x: T) -> T {
    ease(Curve::OutBounce, x)
}
pub fn ease_in_bounce<T: Float>(x: T) -> T {
    ease(Curve::InBounce, x)
}
pub fn ease_in_out_bounce<T: Float>(x: T) -> T {
    ease(Curve::InOutBounce, x)
}

macro_rules! scalar_functions {
    ($scalar:ty, $pi:expr) => {
        pub fn ease_in_sine(x: $scalar) -> $scalar {
            if x == 0.0 || x == 1.0 {
                return x;
            }

            return 1.0 - (x * $pi * 0.5).cos();
        }
        pub fn ease_out_sine(x: $scalar) -> $scalar {
            if x == 0.0 || x == 1.0 {
                return x;
            }

            return (x * $pi * 0.5).sin();
        }
        pub fn ease_in_out_sine(x: $scalar) -> $scalar {
            if x == 0.0 || x == 1.0 {
                return x;
            }

            return (1.0 - ($pi * x).cos()) * 0.5;
        }
        pub const fn ease_in_quad(x: $scalar) -> $scalar {
            return x * x;
        }
        pub const fn ease_out_quad(x: $scalar) -> $scalar {
            let u: $scalar = 1.0 - x;
            return 1.0 - u * u;
        }
        pub const fn ease_in_out_quad(x: $scalar) -> $scalar {
            if (x < 0.5) {
                return 2.0 * x * x;
            }

            let u: $scalar = 2.0 - 2.0 * x;
            return 1.0 - u * u * 0.5;
        }
        pub const fn ease_in_cubic(x: $scalar) -> $scalar {
            return x * x * x;
        }
        pub const fn ease_out_cubic(x: $scalar) -> $scalar {
            let u: $scalar = 1.0 - x;
            return 1.0 - u * u * u;
        }
        pub const fn ease_in_out_cubic(x: $scalar) -> $scalar {
            if (x < 0.5) {
                return 4.0 * x * x * x;
            }

            let u: $scalar = 2.0 - 2.0 * x;
            return 1.0 - u * u * u * 0.5;
        }
        pub const fn ease_in_quart(x: $scalar) -> $scalar {
            return x * x * x * x;
        }
        pub const fn ease_out_quart(x: $scalar) -> $scalar {
            let u: $scalar = 1.0 - x;
            return 1.0 - u * u * u * u;
        }
        pub const fn ease_in_out_quart(x: $scalar) -> $scalar {
            if (x < 0.5) {
                return 8.0 * x * x * x * x;
            }

            let u: $scalar = 2.0 - 2.0 * x;
            return 1.0 - u * u * u * u * 0.5;
        }
        pub const fn ease_in_quint(x: $scalar) -> $scalar {
            return x * x * x * x * x;
        }
        pub const fn ease_out_quint(x: $scalar) -> $scalar {
            let u: $scalar = 1.0 - x;
            return 1.0 - u * u * u * u * u;
        }
        pub const fn ease_in_out_quint(x: $scalar) -> $scalar {
            if (x < 0.5) {
                return 16.0 * x * x * x * x * x;
            }

            let u: $scalar = 2.0 - 2.0 * x;
            return 1.0 - u * u * u * u * u * 0.5;
        }
        pub fn ease_in_expo(x: $scalar) -> $scalar {
            return if x == 0.0 {
                0.0
            } else {
                (10.0 * x - 10.0).exp2()
            };
        }
        pub fn ease_out_expo(x: $scalar) -> $scalar {
            return if x == 1.0 {
                1.0
            } else {
                1.0 - (-10.0 * x).exp2()
            };
        }
        pub fn ease_in_out_expo(x: $scalar) -> $scalar {
            if (x == 0.0 || x == 1.0) {
                return x;
            }

            if (x < 0.5) {
                return (20.0 * x - 10.0).exp2() * 0.5;
            }

            return (2.0 - (10.0 - 20.0 * x).exp2()) * 0.5;
        }
        pub fn ease_in_circ(x: $scalar) -> $scalar {
            return 1.0 - (1.0 - x * x).sqrt();
        }
        pub fn ease_out_circ(x: $scalar) -> $scalar {
            let u: $scalar = x - 1.0;
            return (1.0 - u * u).sqrt();
        }
        pub fn ease_in_out_circ(x: $scalar) -> $scalar {
            if (x < 0.5) {
                let u: $scalar = 2.0 * x;
                return (1.0 - (1.0 - u * u).sqrt()) * 0.5;
            }

            let u: $scalar = 2.0 - 2.0 * x;
            return ((1.0 - u * u).sqrt() + 1.0) * 0.5;
        }
        pub const fn ease_in_back(x: $scalar) -> $scalar {
            return x * x * (x + 1.70158 * (x - 1.0));
        }
        pub const fn ease_out_back(x: $scalar) -> $scalar {
            let u: $scalar = x - 1.0;

            return 1.0 + u * u * (u + 1.70158 * (u + 1.0));
        }
        pub const fn ease_in_out_back(x: $scalar) -> $scalar {
            let c2: $scalar = (1.70158 * 1.525);

            if (x < 0.5) {
                let u: $scalar = 2.0 * x;
                return u * u * (u + c2 * (u - 1.0)) * 0.5;
            }

            let u: $scalar = 2.0 * x - 2.0;
            return (u * u * (u + c2 * (u + 1.0)) + 2.0) * 0.5;
        }
        pub fn ease_in_elastic(x: $scalar) -> $scalar {
            if (x == 0.0 || x == 1.0) {
                return x;
            }

            return -(10.0 * x - 10.0).exp2() * ((10.0 * x - 10.75) * (2.0 * $pi / 3.0)).sin();
        }
        pub fn ease_out_elastic(x: $scalar) -> $scalar {
            if (x == 0.0 || x == 1.0) {
                return x;
            }

            return (-10.0 * x).exp2() * ((10.0 * x - 0.75) * (2.0 * $pi / 3.0)).sin() + 1.0;
        }
        pub fn ease_in_out_elastic(x: $scalar) -> $scalar {
            if (x == 0.0 || x == 1.0) {
                return x;
            }

            let s: $scalar = ((20.0 * x - 11.125) * (2.0 * $pi / 4.5)).sin();

            if (x < 0.5) {
                return -(20.0 * x - 10.0).exp2() * s * 0.5;
            }

            return (10.0 - 20.0 * x).exp2() * s * 0.5 + 1.0;
        }
        pub const fn ease_out_bounce(mut x: $scalar) -> $scalar {
            let n1: $scalar = 7.5625;
            let d1: $scalar = 2.75;

            if (x < 1.0 / d1) {
                return n1 * x * x;
            }

            if (x < 2.0 / d1) {
                x -= 1.5 / d1;
                return n1 * x * x + 0.75;
            }

            if (x < 2.5 / d1) {
                x -= 2.25 / d1;
                return n1 * x * x + 0.9375;
            }

            x -= 2.625 / d1;
            return n1 * x * x + 0.984375;
        }
        pub const fn ease_in_bounce(x: $scalar) -> $scalar {
            return 1.0 - ease_out_bounce(1.0 - x);
        }
        pub const fn ease_in_out_bounce(x: $scalar) -> $scalar {
            if (x < 0.5) {
                return (1.0 - ease_out_bounce(1.0 - 2.0 * x)) * 0.5;
            }

            return (1.0 + ease_out_bounce(2.0 * x - 1.0)) * 0.5;
        }
    };
}
/// Explicit single-precision functions; polynomial curves are also `const fn`.
pub mod f32 {
    scalar_functions!(f32, std::f32::consts::PI);
}
/// Explicit double-precision functions; polynomial curves are also `const fn`.
pub mod f64 {
    scalar_functions!(f64, std::f64::consts::PI);
}
macro_rules! implement_float {
    ($scalar:ty, $module:ident) => {
        impl Float for $scalar {
            fn evaluate(curve: Curve, x: Self) -> Self {
                match curve {
                    Curve::InSine => $module::ease_in_sine(x),
                    Curve::OutSine => $module::ease_out_sine(x),
                    Curve::InOutSine => $module::ease_in_out_sine(x),
                    Curve::InQuad => $module::ease_in_quad(x),
                    Curve::OutQuad => $module::ease_out_quad(x),
                    Curve::InOutQuad => $module::ease_in_out_quad(x),
                    Curve::InCubic => $module::ease_in_cubic(x),
                    Curve::OutCubic => $module::ease_out_cubic(x),
                    Curve::InOutCubic => $module::ease_in_out_cubic(x),
                    Curve::InQuart => $module::ease_in_quart(x),
                    Curve::OutQuart => $module::ease_out_quart(x),
                    Curve::InOutQuart => $module::ease_in_out_quart(x),
                    Curve::InQuint => $module::ease_in_quint(x),
                    Curve::OutQuint => $module::ease_out_quint(x),
                    Curve::InOutQuint => $module::ease_in_out_quint(x),
                    Curve::InExpo => $module::ease_in_expo(x),
                    Curve::OutExpo => $module::ease_out_expo(x),
                    Curve::InOutExpo => $module::ease_in_out_expo(x),
                    Curve::InCirc => $module::ease_in_circ(x),
                    Curve::OutCirc => $module::ease_out_circ(x),
                    Curve::InOutCirc => $module::ease_in_out_circ(x),
                    Curve::InBack => $module::ease_in_back(x),
                    Curve::OutBack => $module::ease_out_back(x),
                    Curve::InOutBack => $module::ease_in_out_back(x),
                    Curve::InElastic => $module::ease_in_elastic(x),
                    Curve::OutElastic => $module::ease_out_elastic(x),
                    Curve::InOutElastic => $module::ease_in_out_elastic(x),
                    Curve::OutBounce => $module::ease_out_bounce(x),
                    Curve::InBounce => $module::ease_in_bounce(x),
                    Curve::InOutBounce => $module::ease_in_out_bounce(x),
                }
            }
        }
    };
}
implement_float!(f32, f32);
implement_float!(f64, f64);
