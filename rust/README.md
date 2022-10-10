# Rust

[Refenrece won't move](https://stackoverflow.com/questions/70761024/references-and-move-vs-copy)

From `reference.rs` We can see that
* Scope for outer variable only means nothing, there's no move or copy happen.
* Reference must be copied, so `println!` won't consume it. Rather, what the static checking does is: it checks `mutable reference` between generation and `last use` of `unmutable reference`
