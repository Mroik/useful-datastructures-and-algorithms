struct Node<'a> {
    value: i32,
    children: Vec<&'a mut Node<'a>>,
}

impl<'a> Node<'a> {
    fn new(value: i32) -> Node<'a> {
        Node { value, children: Vec::new() }
    }

    fn top(&self) -> i32 {
        self.value
    }

    fn meld(h1: &'a mut Node<'a>, h2: &'a mut Node<'a>) -> &'a mut Node {
        if h1.value < h2.value {
            h1.children.push(h2);
            return h1;
        }
        h2.children.push(h1);
        return h2;
    }

    fn insert(&'a mut self, other: &'a mut Node<'a>) -> &'a mut Node {
        return Node::meld(self, other);
    }

    fn merge_pairs(nodes: &'a mut Vec<&mut Node<'a>>) -> Option<&'a mut Node<'a>> {
        let n1;
        let n2;
        if nodes.is_empty() {
            return None;
        }
        if nodes.len() == 1 {
            return Some(nodes.remove(0));
        }
        n1 = nodes.remove(0);
        n2 = nodes.remove(0);
        match Node::merge_pairs(nodes) {
            None => return Some(Node::meld(n1, n2)),
            Some(rest) => return Some(Node::meld(Node::meld(n1, n2), rest)),
        }
    }

    fn pop(&'a mut self) -> Option<&mut Node<'a>> {
        return Node::merge_pairs(&mut self.children);
    }
}


// With this one I'm keeping the main too.
// It's hard to keep track of all the lifetimes, this is a somewhat
// ok example to reference in the future.
fn main() {
    let mut resources: Vec<Node> = Vec::new();
    resources.push(Node::new(10));
    resources.push(Node::new(3));
    resources.push(Node::new(8));
    resources.push(Node::new(7));
    resources.push(Node::new(1));
    resources.push(Node::new(6));
    resources.push(Node::new(2));
    resources.push(Node::new(9));
    resources.push(Node::new(4));
    resources.push(Node::new(5));

    let mut root = resources.remove(0);
    let mut root_ref = &mut root;

    for x in resources.iter_mut() {
        root_ref = root_ref.insert(x);
    }

    for _ in 0..10 {
        println!("{}", root_ref.top());
        match root_ref.pop() {
            None => break,
            Some(next_ref) => root_ref = next_ref,
        }
    }
}
