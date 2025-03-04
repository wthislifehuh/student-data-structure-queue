#include <iostream>
#include <fstream>
#include <algorithm>
#include "BST.h"


using namespace std;


BST::BST() {
	root = NULL;
	count = 0;
}


bool BST::empty() {
	if (count == 0) return true;
	return false;
}


int BST::size() {
	return count;
}


void BST::preOrderPrint() {
	if (root == NULL) return;// handle special case
	else preOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::preOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;
	cur->item.print(cout);
	preOrderPrint2(cur->left);
	preOrderPrint2(cur->right);
}


void BST::inOrderPrint(ostream& out) {	// To print on screen or in file
	if (root == NULL) return;// handle special case
	else inOrderPrint2(root, out);// do normal process
	cout << endl;
}


void BST::inOrderPrint2(BTNode *cur, ostream& out) {

	if (cur == NULL) return;

	inOrderPrint2(cur->left, out);
	cur->item.print(out);
	inOrderPrint2(cur->right, out);
}


void BST::postOrderPrint() {
	if (root == NULL) return;// handle special case
	else postOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::postOrderPrint2(BTNode *cur) {
	if (cur == NULL) return;
	postOrderPrint2(cur->left);
	postOrderPrint2(cur->right);
	cur->item.print(cout);
}



int BST::countNode() {
	int	counter = 0;
	if (root == NULL) return 0;
	countNode2(root, counter);
	return counter;
}


void BST::countNode2(BTNode *cur, int &count) {
	if (cur == NULL) return;
	countNode2(cur->left, count);
	countNode2(cur->right, count);
	count++;
}


bool BST::findGrandsons(type grandFather) {
	if (root == NULL) return false;
	return (fGS2(grandFather, root));
}


bool BST::fGS2(type grandFather, BTNode *cur) {
	if (cur == NULL) return false;
	//if (cur->item == grandFather) {
	if (cur->item.compare2(grandFather)){

		fGS3(cur, 0);// do another TT to find grandsons
		return true;
	}
	if (fGS2(grandFather, cur->left)) return true;
	return fGS2(grandFather, cur->right);
}


void BST::fGS3(BTNode *cur, int level) {
	if (cur == NULL) return;
	if (level == 2) {
		cur->item.print(cout);
		return;  // No need to search downward
	}
	fGS3(cur->left, level + 1);
	fGS3(cur->right, level + 1);
}



void BST::topDownLevelTraversal() {
	BTNode			*cur;
	Queue		    q;


	if (empty()) return; 	// special case
	q.enqueue(root);	// Step 1: enqueue the first node
	while (!q.empty()) { 	// Step 2: do 2 operations inside
		q.dequeue(cur);
		if (cur != NULL) {
			cur->item.print(cout);

			if (cur->left != NULL)
				q.enqueue(cur->left);

			if (cur->right != NULL)
				q.enqueue(cur->right);
		}
	}
}

//insert for BST
bool BST::insert(type newItem) {
	BTNode	*cur = new BTNode(newItem);
	if (!cur) return false;		// special case 1
	if (root == NULL) {
		root = cur;
		count++;
		return true; 			// special case 2
	}
	insert2(root, cur);			// normal
	count++;
	return true;
}


void BST::insert2(BTNode *cur, BTNode *newNode) {
	//if (cur->item > newNode->item) {
	if (cur->item.compare1(newNode->item)){
		if (cur->left == NULL)
			cur->left = newNode;
		else
			insert2(cur->left, newNode);
	}
	else {
		if (cur->right == NULL)
			cur->right = newNode;
		else
			insert2(cur->right, newNode);
	}
}



bool BST::remove(type item) {
	if (root == NULL) return false; 		// special case 1: tree is empty
	return remove2(root, root, item); 		// normal case
}

bool BST::remove2(BTNode *pre, BTNode *cur, type item) {

	// Turn back when the search reaches the end of an external path
	if (cur == NULL) return false;

	// normal case: manage to find the item to be removed
	//if (cur->item == item) {
	if (cur->item.compare2(item)){
		if (cur->left == NULL || cur->right == NULL)
			case2(pre, cur);	// case 2 and case 1: cur has less than 2 sons
		else
			case3(cur);		// case 3, cur has 2 sons
		count--;				// update the counter
		return true;
	}

	// Current node does NOT store the current item -> ask left sub-tree to check
	//if (cur->item > item)
	if (cur->item.compare1(item))
		return remove2(cur, cur->left, item);

	// Item is not in the left subtree, try the right sub-tree instead
	return remove2(cur, cur->right, item);
}


void BST::case2(BTNode *pre, BTNode *cur) {

	// special case: delete root node
	if (pre == cur) {
		if (cur->left != NULL)	// has left son?
			root = cur->left;
		else
			root = cur->right;

		free(cur);
		return;
	}

	if (pre->right == cur) {		// father is right son of grandfather? 
		if (cur->left == NULL)			// father has no left son?
			pre->right = cur->right;			// connect gfather/gson
		else
			pre->right = cur->left;
	}
	else {						// father is left son of grandfather?
		if (cur->left == NULL)			// father has no left son? 
			pre->left = cur->right;				// connect gfather/gson
		else
			pre->left = cur->left;
	}

	free(cur);					// remove item
}


void BST::case3(BTNode *cur) {
	BTNode		*is, *isFather;

	// get the IS and IS_parent of current node
	is = isFather = cur->right;
	while (is->left != NULL) {
		isFather = is;
		is = is->left;
	}

	// copy IS node into current node
	cur->item = is->item;

	// Point IS_Father (grandfather) to IS_Child (grandson)
	if (is == isFather)
		cur->right = is->right;		// case 1: There is no IS_Father    
	else
		isFather->left = is->right;	// case 2: There is IS_Father

	// remove IS Node
	free(is);
}


/*============================================ Assignment Code ===================================================*/
/*============================================== Function(b) =====================================================*/


// Find height of the tree
int BST::getHeight(BTNode* cur) {
	if (cur == NULL) return -1;

	int leftHeight = getHeight(cur->left);
	int rightHeight = getHeight(cur->right);

	// Return the largest value + 1 for root edge (keep accumulating everytime return to caller)
	return max(leftHeight, rightHeight) + 1;
}


// Find and print all the nodes (student id) at the deepest level 
bool BST::deepestNodes() {

	// Variable declaration
	int nodeCount = 0;

	// Return false for empty tree
	if (root == NULL) return false;

	deepestNodes2(root, getHeight(root), nodeCount);
	return true;
}

void BST::deepestNodes2(BTNode* cur, int level, int &nodeCount) {

	// Return if the cur pointer is NULL
	if (!cur) return;
	else if (level == 0) {
		++nodeCount;
		cout << "Deepest node " << nodeCount << ": " << cur->item.id << endl;
	}
	else {
		deepestNodes2(cur->left, level - 1, nodeCount);
		deepestNodes2(cur->right, level - 1, nodeCount);
	}
}


/*============================================== Function(c) =====================================================*/


// Print in Descending order
void BST::DesOrderPrint(ostream& out) {

	// Quit on empty tree
	if (root == NULL) return;
	else DesOrderPrint2(root, out);
	cout << endl;
}


void BST::DesOrderPrint2(BTNode* cur, ostream& out) {

	// Quit on empty tree
	if (cur == NULL) return;

	DesOrderPrint2(cur->right, out);
	cur->item.print(out);
	DesOrderPrint2(cur->left, out);
}


// Print the content of every node 
bool BST::display(int order, int source) {

	// Return false for empty tree
	if (root == NULL) return false;

	// Print to screen
	if (source == 1) {

		system("cls");

		// Print ascending order
		if (order == 1) {	
			cout << "===================================================================\n"
				<< "\t\tStudent Info in ASCENDING ORDER \n"
				<< "===================================================================\n";
			inOrderPrint(cout);
			cout << "\n===================================================================\n\n";
		}
		// Print in descending order
		else {
			cout << "===================================================================\n"
				<< "\t\tStudent Info in DESCENDING ORDER \n"
				<< "===================================================================\n";
			DesOrderPrint(cout);
			cout << "\n===================================================================\n";
		}
	}
	// Print to student_info.txt
	else {
		cout << "\nPrinting the students records to the file...\n\n" ;

		// Open the file for output
		ofstream outFile("student-info.txt");

		// Check if the file exists
		if (!outFile) return false;

		// Print in ascending order
		if (order == 1) {
			outFile << "===================================================================\n"
				<< "\t\tStudent Info in ASCENDING ORDER \n"
				<< "===================================================================\n";
			inOrderPrint(outFile);
			outFile << "\n===================================================================\n\n";
		}
		// Print in descending order
		else {
			outFile << "===================================================================\n"
				<< "\t\tStudent Info in DESCENDING ORDER \n"
				<< "===================================================================\n";
			DesOrderPrint(outFile);
			outFile << "\n===================================================================\n\n";
		}
		outFile.close();
	 }
	 return true;
 }


/*============================================== Function(d) =====================================================*/


 // Clone a subtree in t1 where the root of the subtree contain value item
 bool BST::CloneSubtree(BST t1, type item) {

	 // Variable declaration
	 bool find = false;
	 
	 // Quit on empty tree
	 if (t1.empty()) {		
		 cout << "The tree is empty!\n\n";
		 return false;				
	 }
	 
	 CloneSubtree1(t1.root, item, find);

	 // If the item can be found
	 if(find) 
		 return true;	
	 // If the item cannot be found
	 else {
		 cout << "\nStudent ID cannot be found!\n\n";
		 return false;
	 }
	
 }


 // To find same item id
 void BST::CloneSubtree1(BTNode* cur, type item, bool& find) {

	 // Quit on empty node
	 if (cur == NULL) return;

	 // If the item id and the current id is the same
	 if (cur->item.compare2(item)) { 
		 CloneSubtree2(cur);
		 find = true;
	 } 
	 // Traverse t1 to find the same id
	 else {
		 // If the current item is greater, go to the left
		 if(cur->item.compare1(item))	
			CloneSubtree1(cur->left, item, find);
		 // If the current item is smaller, go to the right
		 else CloneSubtree1(cur->right, item, find);	
	 }
 }


 // After finding the item, clone all the subtree in t2
 void BST::CloneSubtree2(BTNode* cur) {

	 // Quit on empty node
	 if (cur == NULL) return;

	 // Insert the subtree into t2
	 insert(cur->item);

	 // Traverse t1 to add in subtree
	 CloneSubtree2(cur->left);
	 CloneSubtree2(cur->right);
 }


 // To clear the clone t2 before cloning (making sure the t2 must be an empty tree before cloning)
 bool BST::ClearSubtree() {

	 while (root != NULL) remove(root->item);
	 return true;
 }


 /*============================================== Function(e) =====================================================*/


 // Print nodes according to level in a BST
 bool BST::printLevelNodes() {

	 // Quit on empty tree
	 if (root == NULL)  return false;

	 // Level = Height + 1
	 int level = getHeight(root) + 1;

	 for (int i = 1; i <= level; i++) {
		 cout << "Level " << i << " nodes:\t";
		 printLevelNodes1(root, i);
		 cout << endl;
	 }
	 return true;
 }

 // Print nodes at a specific level
 void BST::printLevelNodes1(BTNode* cur, int level) {

	 // Quit on empty root
	 if (!cur) return;

	 // Print when reach level
	 if (level == 1) cout << cur->item.id << "\t";	
	 else {
		 printLevelNodes1(cur->left, level - 1);
		 printLevelNodes1(cur->right, level - 1);
	 }
 }

/*============================================== Function(f) =====================================================*/

// Print all the external path in a BST
bool BST::printPath() {

	// Return false on empty tree
	if (root == NULL) return false;
	cout << "Below are all the external paths for the tree:\n\n";

	int path[100];	// Array of paths
	printPath1(root, path, 0);	// Print the path
	return true;
}


void BST::printPath1(BTNode* cur, int path[], int pathLen) {

	// Quit on empty root
	if (cur == NULL) return;	

	// Append the id to path array
	path[pathLen] = cur->item.id;	
	++pathLen;
	
	// Print the path when reaching the last node
	if (cur->left == NULL && cur->right == NULL) {
		for (int i = 0; i < pathLen; i++) cout << path[i] << "\t";
		cout << endl;
	}
	// Continue to traverse the subtrees
	else {	
		printPath1(cur->left, path, pathLen);
		printPath1(cur->right, path, pathLen);	
	}
}