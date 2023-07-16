use std::vec;

pub struct Solution;

impl Solution {
  pub fn valid_arrangement(pairs: Vec<Vec<i32>>) -> Vec<Vec<i32>> {
    use std::collections::HashMap;
    let mut index = HashMap::new();
    for p in &pairs {
      for &i in p {
        if !index.contains_key(&i) {
          index.insert(i, index.len());
        }
      }
    }
    let n = index.len();
    let mut e_in = vec![Vec::new(); n];
    let mut e_out = vec![Vec::new(); n];

    for a in 0..pairs.len() {
      let p = &pairs[a];
      let i = *index.entry(p[0]).or_default();
      let j = *index.entry(p[1]).or_default();
      assert!(i < n && j < n);
      e_in[j].push((i, a));
      e_out[i].push((j, a));
    }

    let mut start = 0;
    let mut end = 0;
    for i in 0..n {
      if e_out[i].len() > e_in[i].len() {
        start = i;
      } else if e_in[i].len() > e_out[i].len() {
        end = i;
      }
    }

    let mut path_v = Vec::new();
    let mut path_e = Vec::new();

    let mut vis = vec![false; pairs.len()];
    let mut parent = vec![pairs.len(); pairs.len()];

    // Start with any path between start and end
    if start != end {
      use std::collections::VecDeque;
      let mut q = VecDeque::from([start]);
      let mut par_bfs = vec![pairs.len(); n];
      let mut vis_bfs = vec![false; n];
      vis_bfs[start] = true;

      while !q.is_empty() {
        let v = *q.front().unwrap();
        q.pop_front();
        if v == end {
          assert!(par_bfs[v] != n);
          break;
        }
        for &(u, e) in &e_out[v] {
          if !vis_bfs[u] {
            vis_bfs[u] = true;
            assert!(e < pairs.len());
            par_bfs[u] = e;
            q.push_back(u);
          }
        }
      }
      let mut v = end;
      while par_bfs[v] != pairs.len() {
        path_v.push(v);
        let e = par_bfs[v];
        assert!(e < pairs.len());
        path_e.push(e);
        assert!(index.contains_key(&pairs[e][0]));
        v = *index.entry(pairs[e][0]).or_default();
      }
      assert_eq!(v, start);
      path_v.push(v);
      path_v.reverse();
      path_e.reverse();
      assert!(path_e.len() > 1);
      vis[path_e[0]] = true;
      for i in 1..path_e.len() {
        vis[path_e[i]] = true;
        parent[path_e[i]] = path_e[i - 1];
      }
    } else {
      // start == end
      path_v.push(start);
    }

    while path_v.len() != n {
      assert!(path_v.len() < n);
      assert_eq!(path_v.len(), path_e.len() + 1);
      
      for &v in &path_v {
        for &(u,e) in &e_out[v] {
          if !vis[e] {
            let w = e
          }  
        }        
      }
    }

    // let mut starts_width = HashMap::new();

    // for i in 0..pairs.len() {
    //   let p = &pairs[i];
    //   let sw = starts_width.entry(p[0]).or_insert(Vec::new());
    //   sw.push(i);
    // }

    // let mut g = Vec::with_capacity(pairs.len());
    // for p in &pairs {
    //   let nbs = starts_width.entry(p[1]).or_default();
    //   g.push(nbs.clone());
    // }

    return Vec::new();
  }
}

pub fn main() {
  println!(
    "{:?}",
    Solution::valid_arrangement(vec![
      vec![5, 1],
      vec![4, 5],
      vec![11, 9],
      vec![9, 4]
    ])
  );
  println!(
    "{:?}",
    Solution::valid_arrangement(vec![vec![1, 3], vec![3, 2], vec![2, 1]])
  );
  println!(
    "{:?}",
    Solution::valid_arrangement(vec![vec![1, 2], vec![1, 3], vec![2, 1]])
  );
}
