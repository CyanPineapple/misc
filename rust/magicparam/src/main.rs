
#[derive(Clone)]
pub struct Context {
    param: String,
    id: i32,
}

impl Context {
    fn new(str: String, id: i32) -> Self {
        Self { param: str, id: id }
    }
}

#[derive(Debug)]
struct Param (pub String);

trait FromContext {
    fn from_context(context: &Context) -> Self;
}

impl FromContext for Param {
    fn from_context(context: &Context) -> Self {
        Self(context.clone().param)
    }
}

struct Id(i32);

impl FromContext for Id {
    fn from_context(context: &Context) -> Id {
        Self(context.id)
    }
}

pub trait Handler<T> {
    fn handle(self, context: Context);
}

impl<F, T> Handler<T> for F
    where
    F: Fn(T),
    T: FromContext,
{
    fn handle(self, context: Context) {
        (self)(T::from_context(&context));
    }
}

impl<F, T1, T2> Handler<(T1, T2)> for F
    where
    F: Fn(T1, T2),
    T1: FromContext,
    T2: FromContext,
{
    fn handle(self, context: Context) {
        (self)(T1::from_context(&context), T2::from_context(&context));
    }
}

pub fn trigger<F, T>(ctx: Context, clo: F)
where
    F: Handler<T>,
{
    clo.handle(ctx);
}


fn print_id(id: Id) {
    println!("id is {}", id.0);
}

// Param(param) is just pattern matching
fn print_all(Param(param): Param, Id(id): Id) {
    println!("param is {param}, id is {id}");
}

pub fn main() {
    let context = Context::new("magic".into(), 33);

    trigger(context.clone(), print_id);
    trigger(context.clone(), print_all);
}
