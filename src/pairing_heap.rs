use std::{cell::{RefCell, RefMut}, mem};

struct Node<T> {
    value: T,
    children: RefCell<Vec<Box<Node<T>>>>,
}

impl<T: Copy + Ord> Node<T> {
    fn new(value: T) -> Node<T> {
        Node {
            value,
            children: RefCell::new(vec![]),
        }
    }

    fn top(&self) -> T {
        return self.value;
    }

    fn meld(&mut self, mut h2: Box<Node<T>>) {
        if self.value < h2.value {
            self.children.borrow_mut().push(h2);
            return;
        }
        mem::swap(self, &mut h2);
        self.children.borrow_mut().push(h2);
    }

    fn push(&mut self, value: T) {
        let other = Node::new(value);
        self.meld(Box::new(other));
    }

    fn merge_pairs(mut nodes: RefMut<Vec<Box<Node<T>>>>) -> Option<Box<Node<T>>> {
        let mut n1;
        let n2;
        {
            if nodes.is_empty() {
                return None;
            }
            if nodes.len() == 1 {
                return Some(nodes.remove(0));
            }
            n1 = nodes.remove(0);
            n2 = nodes.remove(0);
        }

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

impl<T: Copy + Ord> PriorityQueue<T> {
    fn new() -> Self {
        PriorityQueue {
            root: None,
        }
    }

    fn push(&mut self, value: T) {
        if let Some(rr) = &mut self.root {
            (*rr).push(value);
            return;
        }
        self.root = Some(Box::new(Node::new(value)));
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
    let mut queue: PriorityQueue<i32> = PriorityQueue::new();
    queue.push(10);
    queue.push(3);
    queue.push(8);
    queue.push(7);
    queue.push(1);
    queue.push(6);
    queue.push(2);
    queue.push(9);
    queue.push(4);
    queue.push(5);

    for _ in 0..10 {
        println!("{}", queue.top().unwrap());
        match queue.pop() {
            Ok(_) => (),
            Err(_) => break,
        }
    }
}
