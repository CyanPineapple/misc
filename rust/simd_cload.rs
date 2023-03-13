pub use clocker::Clocker;
pub use howlong::*;
mod clocker;

#[cfg(target_arch = "x86")]
use std::arch::x86::_mm256_add_epi64;
#[cfg(target_arch = "x86_64")]
use std::arch::x86_64::*;

unsafe fn conditional_load(target: __m256i) -> __m256i {
    // twice for smaller than 3
    let twice = _mm256_add_epi32(target, target);
    // twice for greater than 3
    let square = _mm256_mullo_epi16(target, target);

    let mut cmp = _mm256_cmpgt_epi32(target, _mm256_set1_epi32(3));

    let hi = _mm256_and_si256(square, cmp);
    // negate cmp
    cmp = _mm256_xor_si256(cmp, _mm256_set1_epi32(-1));
    let lo = _mm256_and_si256(twice, cmp);

    // add hi and lo
    _mm256_add_epi32(hi, lo)

    

}
fn main() {

        // cast mem into raw pointer
        let mut mem = [1,2,3,4,5,6,7,8];
        unsafe {
            let opr1 = _mm256_loadu_si256(mem.as_mut_ptr() as *const __m256i);
            let res = conditional_load(opr1);
            // store res into array
            _mm256_storeu_si256(mem.as_mut_ptr() as *mut __m256i, res);
            println!("{:?}", mem);
        }
    }