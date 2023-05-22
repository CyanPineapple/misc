//! Being Flexible
use quote::quote;
fn main() {
    let elements = vec!["Hello", "World", "42", "false"];
    let res = quote! {
        let arr = [#(#elements),*];
        println!("{:?}", arr);
    };
    println!("{}",res);

}
