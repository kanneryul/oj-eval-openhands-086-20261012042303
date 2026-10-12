#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct TreeNode {
    int left;
    int right;
    TreeNode() : left(-1), right(-1) {}
};

class BinaryTree {
private:
    vector<TreeNode> nodes;
    int n;
    
public:
    BinaryTree(int size) : n(size) {
        nodes.resize(size + 1); // 1-indexed
    }
    
    void setChildren(int node, int left, int right) {
        if (node >= 1 && node <= n) {
            nodes[node].left = left;
            nodes[node].right = right;
        }
    }
    
    void swapAtDepthMultiple(int k) {
        if (k <= 0) return;
        
        queue<pair<int, int>> q; // {node, depth}
        q.push({1, 1}); // root is at depth 1
        
        while (!q.empty()) {
            int current = q.front().first;
            int depth = q.front().second;
            q.pop();
            
            if (current == -1) continue;
            
            // If depth is a multiple of k, swap children
            if (depth % k == 0) {
                swap(nodes[current].left, nodes[current].right);
            }
            
            // Add children to queue
            if (nodes[current].left != -1) {
                q.push({nodes[current].left, depth + 1});
            }
            if (nodes[current].right != -1) {
                q.push({nodes[current].right, depth + 1});
            }
        }
    }
    
    void inorderTraversal() {
        vector<int> result;
        inorder(1, result);
        
        for (size_t i = 0; i < result.size(); i++) {
            if (i > 0) cout << " ";
            cout << result[i];
        }
        cout << endl;
    }
    
private:
    void inorder(int node, vector<int>& result) {
        if (node == -1) return;
        
        inorder(nodes[node].left, result);
        result.push_back(node);
        inorder(nodes[node].right, result);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    BinaryTree tree(n);
    
    for (int i = 1; i <= n; i++) {
        int left, right;
        cin >> left >> right;
        tree.setChildren(i, left, right);
    }
    
    int t;
    cin >> t;
    
    for (int i = 0; i < t; i++) {
        int k;
        cin >> k;
        tree.swapAtDepthMultiple(k);
        tree.inorderTraversal();
    }
    
    return 0;
}