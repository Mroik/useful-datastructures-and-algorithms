use std::{cell::{RefCell, RefMut}, mem};

struct Node<T> {
    value: T,
    priority: i32,
    children: RefCell<Vec<Box<Node<T>>>>,
}

impl<T: Copy> Node<T> {
    fn new(value: T, priority: i32) -> Node<T> {
        Node {
            value,
            priority,
            children: RefCell::new(vec![]),
        }
    }

    fn top(&self) -> T {
        return self.value;
    }

    fn meld(&mut self, mut h2: Box<Node<T>>) {
        if !(self.priority < h2.priority) {
            mem::swap(self, &mut h2);
        }
        self.children.borrow_mut().push(h2);
    }

    fn push(&mut self, value: T, priority: i32) {
        let other = Node::new(value, priority);
        self.meld(Box::new(other));
    }

    fn merge_pairs(mut nodes: RefMut<Vec<Box<Node<T>>>>) -> Option<Box<Node<T>>> {
        if nodes.is_empty() {
            return None;
        }
        if nodes.len() == 1 {
            return Some(nodes.remove(0));
        }
        let mut n1 = nodes.remove(0);
        let n2 = nodes.remove(0);

        match Node::merge_pairs(nodes) {
            None => {
                n1.meld(n2);
                return Some(n1)
            },
            Some(rest) => {
                n1.meld(n2);
                n1.meld(rest);
                return Some(n1);
            },
        }
    }

    fn pop(&self) -> Option<Box<Node<T>>> {
        let a = self.children.borrow_mut();
        return Node::merge_pairs(a);
    }
}

struct PriorityQueue<T> {
    root: Option<Box<Node<T>>>,
}

impl<T: Copy> PriorityQueue<T> {
    fn new() -> Self {
        PriorityQueue {
            root: None,
        }
    }

    fn push(&mut self, value: T, priority: i32) {
        if let Some(rr) = &mut self.root {
            rr.push(value, priority);
            return;
        }
        self.root = Some(Box::new(Node::new(value, priority)));
    }

    fn top(&self) -> Option<T> {
        if let Some(root) = &self.root {
            return Some(root.top());
        }
        return None;
    }

    fn pop(&mut self) -> Result<(), ()> {
        if let Some(root) = &mut self.root {
            self.root = root.pop();
            return Ok(());
        }
        return Err(());
    }
}

fn main() {
    let mut queue: PriorityQueue<&str> = PriorityQueue::new();
    queue.push("Ten", 10);
    queue.push("Three", 3);
    queue.push("Eight", 8);
    queue.push("Seven", 7);
    queue.push("One", 1);
    queue.push("Six", 6);
    queue.push("Two", 2);
    queue.push("Nine", 9);
    queue.push("Four", 4);
    queue.push("Five", 5);

    for _ in 0..10 {
        println!("{}", queue.top().unwrap());
        match queue.pop() {
            Ok(_) => (),
            Err(_) => break,
        }
    }
}
