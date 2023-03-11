use howlong::*;

pub struct Clocker {
    timer: HighResolutionTimer,
}

impl Clocker {
    pub fn new() -> Self {
        Clocker {
            timer: HighResolutionTimer::new(),
        }
    }
}

impl Drop for Clocker {
    fn drop(&mut self) {
        println!("{:?} has passed.", self.timer.elapsed())
    }
}
