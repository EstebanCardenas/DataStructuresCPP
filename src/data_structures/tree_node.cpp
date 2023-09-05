template <typename T>
class TreeNode {
public:
	TreeNode* left;
	TreeNode* right;
	T val;

	TreeNode(T val) {
		this->val = val;
		left = nullptr;
		right = nullptr;
	}
	TreeNode(T val, TreeNode* left, TreeNode* right) {
		this->val = val;
		this->left = left;
		this->right = right;
	}
};
