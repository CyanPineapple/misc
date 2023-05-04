//! Async Model
//! ===========
//! async keyword turn function into a state machine
//! Executor controls which future needs to be polled 
//! upon the signal he gets from the Reactor through Waker. 
//! 
//! In our program, the spawner sends the top-level future (Task) to the executor.
//! The executor only has a receiver
//! 
mod timer_future;

pub use std::future::{self, Future};
use std::task::Context;
use std::time::Duration;
use std::sync::{Arc, Mutex};
use timer_future::TimerFuture;
use futures::future::BoxFuture;
use futures::task::{ArcWake, waker_ref};

struct Task {
    /// In-progress future that should be pushed to completion.
    ///
    /// The `Mutex` is not necessary for correctness, since we only have
    /// one thread executing tasks at once. However, Rust isn't smart
    /// enough to know that `future` is only mutated from one thread,
    /// so we need to use the `Mutex` to prove thread-safety. A production
    /// executor would not need this, and could use `UnsafeCell` instead.
    future: Mutex<Option<BoxFuture<'static, ()>>>,
    /// Handle to place the task itself back onto the task queue.
    task_sender: Mutex<std::sync::mpsc::Sender<Arc<Task>>>,
}

impl ArcWake for Task {
    fn wake_by_ref(arc_self: &Arc<Self>) {
        let cloned_me = arc_self.clone();
        arc_self.task_sender
                .lock()
                .unwrap()
                .send(cloned_me)
                .expect("wake failed: cannot send");
    }
}

struct Executor {
    task_receiver: std::sync::mpsc::Receiver<Arc<Task>>,
}

struct Spawner {
    task_sender: std::sync::mpsc::Sender<Arc<Task>>,
}

impl Spawner {
    fn spawn(&self, fut: impl Future<Output = ()> + Send + 'static) {
        // Produce a Task and send it to executor
        let box_fut = Box::pin(fut) ;
        let task = Task {
            future: Mutex::new(Some(box_fut)),
            task_sender: Mutex::new(self.task_sender.clone())
        };
        self.task_sender.send(Arc::new(task)).expect("send error");
    }
}

impl Executor {
    fn run(&self) {
        while let Ok(task) = self.task_receiver.recv() {
            // pass it the context and poll and check ret of poll
            // pass a context needs a Waker
            let mut future = task.future.lock().unwrap();
            if let Some(mut fut) = future.take() {
                let waker = waker_ref(&task);
                let mut cx = Context::from_waker(&*waker);
                if fut.as_mut().poll(&mut cx).is_pending() {
                    // We're not done processing the future, so put it
                    // back in its task to be run again in the future.
                    //*future = Some(fut);
                }
            }
            println!("miss here");
        }
    }
}

fn new_executor_and_spawner() -> (Executor, Spawner) {
    let (task_sender, task_receiver) = std::sync::mpsc::channel();
    (Executor { task_receiver }, Spawner { task_sender }) 
}

fn main() {
    let (executor, spawner) = new_executor_and_spawner();

    // Spawn a task to print before and after waiting on a timer.
    spawner.spawn(async {
        println!("hello");
        // Wait for our timer future to complete after two seconds.
        TimerFuture::new(Duration::new(2, 0)).await;
        println!("world!");
    });

    // Drop the spawner so that our executor knows it is finished and won't
    // receive more incoming tasks to run.
    drop(spawner);
    // After `drop` here the references are only in the tasks.

    // Run the executor until the task queue is empty.
    // This will print "howdy!", pause, and then print "done!".
    println!("First: in Main");
    executor.run();
}
