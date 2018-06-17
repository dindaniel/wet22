#ifndef HW1_AVLTREE_H
#define HW1_AVLTREE_H

//
// Created by din on 14/05/2018.
//




//
// Created by din on 14/05/2018.
//

//TODO: add ranks!
//TODO: each node needs to contain the sum of keys in it's subtree

#include <assert.h>
#include <iostream>


typedef enum {
    AVL_SUCCESS, AVL_ALREADY_EXIST, AVL_NOT_EXIST
} AVLResult;


/**
 * AVL node class. pointer to parent might not be crucial, but why not?
 * data would be a pointer to either a player or a clan.
 * @tparam T,K - Generics
 */
template <class K, class T>
class AVLnode{
public:
    K key;
    T data;
    int height;
    int val,sum,l_size, r_size;
    AVLnode *left, *right, *parent;

    /**
     * Constructor of a Node
     * @param key - could be an array of two parameters. will be fine with function objects.
     * @param date - a pointer to a player or a clan.
     * @param parent - parent node. if it's the root then this should be null.
     */
    AVLnode(K key, T data,AVLnode *parent= nullptr,int height=0){
        this->l_size=0;
        this->r_size=0;
        this->parent=parent;
        right=nullptr;
        left=nullptr;
        this->key=key;
        this->data=data;
        this->height=height;
    }
    AVLnode(){
        this->data=nullptr;
    };


    /**
     * Destructor. All you should do is delete right and left
     */
     ~AVLnode(){

    }

};

template <class K, class T>
class AVLtree {
    AVLnode<K, T> *root;
    int size;
    int original;
    int copies;
    AVLtree<K,T>* source;


    AVLnode<K, T> *getNodeByRank(int rank) {
        AVLnode<K, T> *current = root;
        int counter = 0;
        int place;
        while (true) {
            assert(current);
            place = counter + current->l_size + 1;
            if (place == rank) {
                return current;
            }
            if (rank < place) {
                current = current->left;
            }
            if (rank > place) {
                counter = current->l_size + 1;
                current = current->right;
            }
        }
    };
    int Size(AVLnode<K, T> *node) {
        if (node) {
            return node->r_size + node->l_size;
        }
        return -1;
    }
    int getSum(AVLnode<K, T> *node) {
        if (node) {
            return node->sum;
        }
        return 0;
    }
    void changeVertical(AVLnode<K, T> *node) {
        node->l_size = Size(node->left) + 1;
        node->r_size = Size(node->right) + 1;
        node->sum = getSum(node->left) + getSum(node->right) + node->val;
        node->height = maxHeight(node->right, node->left) + 1;
    }

    /** these are private methods**/
    /**
     * single left rotation
     * @param a - "root" node sub tree we rotate
     * @return -the pointer to the sub tree after rotation
     */
    AVLnode<K, T> *rotateLeft(AVLnode<K, T> *a) {
        assert(a && a->right);
        AVLnode<K, T> *ap = a->parent;
        AVLnode<K, T> *ar = a->right;
        AVLnode<K, T> *arl = ar->left;
        a->right = arl;
        if (arl) arl->parent = a;
        changeVertical(a); //switch with changeVertical
        ar->left = a;
        a->parent = ar;
        changeVertical(ar); //switch with changeVertical
        ar->parent = ap;
        if (ap) {
            if (ar->key < ap->key) {
                ap->left = ar;
            } else {
                ap->right = ar;
            }
            while (ap) {
                changeVertical(ap); //switch with changeVertical
                ap = ap->parent;
            }
        } else {
            root = ar;
        }
        return ar;
    };

    /**
     * single rigt rotation
     * @param a - "root" node sub tree we rotate
     * @return -the pointer to the sub tree after rotation
     */
    AVLnode<K, T> *rotateRight(AVLnode<K, T> *a) {
        assert(a && a->left);
        AVLnode<K, T> *ap = a->parent;
        AVLnode<K, T> *al = a->left;
        AVLnode<K, T> *alr = al->right;
        a->left = alr;
        if (alr) alr->parent = a;
        changeVertical(a); //switch with changeVertical
        al->right = a;
        a->parent = al;
        changeVertical(al); //switch with changeVertical
        al->parent = ap;
        if (ap) {
            if (al->key < ap->key) {
                ap->left = al;
            } else {
                ap->right = al;
            }
            while (ap) {
                changeVertical(ap); //switch with changeVertical
                ap = ap->parent;
            }
        } else {
            root = al;
        }
        return al;
    };

    /** great exapmles in Tutorial on AVL trees
     * use the two basic rotation "left" and "right"**/
    AVLnode<K, T> *LLrotation(AVLnode<K, T> *a) {
        return rotateRight(a);
    };

    AVLnode<K, T> *RRrotation(AVLnode<K, T> *a) {
        return rotateLeft(a);
    };

    AVLnode<K, T> *LRrotation(AVLnode<K, T> *a) {
        a = rotateLeft(a->left);
        return rotateRight(a->parent);
    };

    AVLnode<K, T> *RLrotation(AVLnode<K, T> *a) {
        a = rotateRight(a->right);
        return rotateLeft(a->parent);
    };

    /**
     * rebalancing the tree after an insert or a remove, using rotations
     * @param root - the root of the tree (not a subtree)
     */
    void rebalance(AVLnode<K, T> *root) {
        AVLnode<K, T> *current = root;
        while (current) {
            int bf = getBF(current);
            if (bf == 2) {
                AVLnode<K, T> *left_son = current->left;
                int bf_left_son = getBF(left_son);
                if (bf_left_son == -1) {
                    current = LRrotation(current);

                } else {
                    current = LLrotation(current);
                }
            }
            if (bf == -2) {
                AVLnode<K, T> *right_son = current->right;
                int bf_right_son = getBF(right_son);
                if (bf_right_son == 1) {
                    current = RLrotation(current);

                } else {
                    current = RRrotation(current);
                }
            }
            current = current->parent;
        }
    }

    /**
     * calculate the height of a specific node
     * @param a - the node you want to calculate height for
     * @return height
     */
    int height(AVLnode<K, T> *a) {
        if (!a) {
            return -1;
        }
        return a->height;
    }

    /**
     * get the balance factor for node a, based on height of it's sons
     * @param a
     */
    int getBF(AVLnode<K, T> *a) {
        return height(a->left) - height(a->right);
    }

    void delTree(AVLnode<K, T> *root) {
        if (root) {
            delTree(root->left);
            delTree(root->right);
            delete root;
        }
    }

    void Fixing(AVLnode<K, T> *node) {
        while (node) {
            changeVertical(node);
            node = node->parent;
        }
    }

    int maxHeight(AVLnode<K, T> *a, AVLnode<K, T> *b) {
        int ha = height(a);
        int hb = height(b);
        return ha > hb ? ha : hb;
    }

    AVLnode<K, T> *getMin(AVLnode<K, T> *root) {
        AVLnode<K, T> *node = nullptr;
        while (root) {
            node = root;
            root = root->left;
        }
        return node;
    }

    AVLnode<K, T> *insertBinary(K &key, T &data, int value) {
        if (!root) {
            root = new AVLnode<K, T>(key, data, nullptr);
            root->val = value;
            root->sum = value;
            return root;
        }
        AVLnode<K, T> *current = root;
        AVLnode<K, T> *current_perant = nullptr;
        while (current) {
            if (key == current->key) {
                return nullptr;
            }
            current_perant = current;
            if (key < current->key) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        assert(current_perant);
        if (key < current_perant->key) {
            current_perant->left = new AVLnode<K, T>(key, data, current_perant);
            current_perant->left->val = value;
            current_perant->left->sum = value;
            return current_perant->left;
        } else {
            current_perant->right = new AVLnode<K, T>(key, data, current_perant);
            current_perant->right->val = value;
            current_perant->right->sum = value;
            return current_perant->right;
        }
    }

    AVLResult removeBinary(K &key, AVLnode<K, T> **p_parent) {//maybe change this
        //3 types of remove leaf ,root,other
        AVLnode<K, T> *current = find(key);
        if (!current) {
            return AVL_NOT_EXIST;
        }
        int number_of_sons = getNumOfSons(current);
        switch (number_of_sons) {
            case 0:
                current = removeLeaf(current);
                break;
            case 1:
                current = removeVertexWithOneSon(current);
                break;
            case 2:
                current = removeVertexWithTwoSons(current);
                break;
            default:
                break;
        }
        *p_parent = current;
        return AVL_SUCCESS;
    }

    AVLnode<K, T> *removeLeaf(AVLnode<K, T> *v) {
        AVLnode<K, T> *parent = v->parent;
        if (parent) {
            if (parent->left == v) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
        } else {
            assert(root == v);
            root = nullptr;
        }
        delete v;
        return parent;
    };

    int getNumOfSons(AVLnode<K, T> *current) {
        int num_of_sons = 0;
        if (current->right) num_of_sons++;
        if (current->left) num_of_sons++;
        return num_of_sons;
    }

    AVLnode<K, T> *removeVertexWithOneSon(AVLnode<K, T> *v) {
        AVLnode<K, T> *parent = v->parent;
        AVLnode<K, T> *vr(v->right), *vl(v->left);
        if (parent) {
            if (parent->left == v) {
                if (v->left) {
                    parent->left = v->left;
                    vl->parent = parent;
                }
                if (v->right) {
                    parent->left = v->right;
                    vr->parent = parent;
                }
            } else {
                if (v->left) {
                    parent->right = v->left;
                    vl->parent = parent;
                }
                if (v->right) {
                    parent->right = v->right;
                    vr->parent = parent;
                }
            }
        } else {
            assert(root == v);
            if (v->left) {
                root = v->left;
                vl->parent = parent;
            }
            if (v->right) {
                root = v->right;
                vr->parent = parent;
            }
        }
        delete v;
        return parent;
    };

    AVLnode<K, T> *removeVertexWithTwoSons(AVLnode<K, T> *v) {
        AVLnode<K, T> *parent;
        AVLnode<K, T> *after_v = getMin(v->right);
        int num_of_sons = getNumOfSons(after_v);
        v->data = after_v->data;
        v->key = after_v->key;
        assert(num_of_sons != 2);
        if (num_of_sons == 0) {
            parent = removeLeaf(after_v);
        } else {
            parent = removeVertexWithOneSon(after_v);
        }
        return parent;
    }

    AVLnode<K, T> *find(K key) {
        AVLnode<K, T> *current = root;
        while (current) {
            if (key == current->key) {
                return current;
            }
            if (key < current->key) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return nullptr;
    }

    void inorder(AVLnode<K, T> **output, AVLnode<K, T> *root) const {
        if (root) {
            static int i = 0;
            inorder(output, root->left);
            *(output + i) = root;
            i++;
            if (i == size) i = 0;
            inorder(output, root->right);
        }
    }

    int getTreeHeight(int num_of_vertices, int *diff) {
        int num = 1;
        int h = 0;
        while (num - 1 < num_of_vertices) {
            num = num * 2;
            h++;
        }
        *diff = num - 1 - num_of_vertices;
        return h - 1;
    }


public:
    /**
     * creates empty tree
     */
    int getSumByRank(int rank) {// heigher then
        AVLnode<K, T> *node = getNodeByRank(rank);
        AVLnode<K, T> *parent = node->parent;
        AVLnode<K, T> *current = node;
        int sum = getSum(node->right);
        while (parent) {
            if (parent->left == current) {
                sum += parent->val + getSum(parent->right);
            }
            current = parent;
            parent = parent->parent;
        }
        return sum;
    }

    AVLtree() : root(nullptr), size(0),original(1),copies(0),source(nullptr) {}

    /**
     * destructor. delete root and automatic d'tor calling should take care of everything else(but check me on it)
     */
    ~AVLtree() {


    }

    AVLtree(AVLtree<K, T> &tree) {
        static int counter=0;
        counter++;
        this->original=0;
        if(tree.original){
            this->source=&tree;
            this->source->copies++;
        }else{
            this->source=tree.source;
            tree.source->copies++;
        }
    };

    AVLtree<K, T> operator=(AVLtree<K, T>&tree){
        static int counter=0;
        counter++;
        AVLtree t1(tree);
        return t1;
    };

    /**
     * insert new node to tree, don't forget to rebalance it after and change balance factor while you do it
     * @param key
     * @param data
     * @return boolean value if inserted or not
     */
    AVLResult insert(K key, T data, int value=0) {
        AVLnode<K, T> *node = insertBinary(key, data, value);
        if (!node) {
            return AVL_ALREADY_EXIST;
        }
        size++;
        Fixing(node);
        rebalance(node);
        return AVL_SUCCESS;
    }

    AVLResult remove(K key) {
        AVLnode<K, T> *parent;
        AVLResult res = removeBinary(key, &parent);
        if (res == AVL_NOT_EXIST) {
            return AVL_NOT_EXIST;
        }
        size--;
        Fixing(parent);
        rebalance(parent);
        return AVL_SUCCESS;
    }

    /**
     * does an element with the key is in the tree
     * @param key
     * @return boolean value
     */
    bool contains(const K &key) {
        if (find(key)) {
            return true;
        }
        return false;
    }

    /**
     * returns the data of the certain key
     * @param key
     * @return T - usually pointer to player or clan
     */
    T getByKey(const K &key) {
        AVLnode<K, T> *tmp = find(key);
        if (tmp) {
            return tmp->data;
        }
        //shouldnt get here.
        return 0;
    }

    /**
     * inorder tour of the tree
     * @param root . getRoot()
     */
    void reverse_inorder(T *output, AVLnode<K, T> *node) {
        if (node) {
            static int i = 0;
            reverse_inorder(output, node->right);
            *(output + i) = node->data;
            i++;
            if (i == size) i = 0;
            reverse_inorder(output, node->left);
        }
    }


    /**
     * get best node
     * @return the node that has the highest key in the tree
     */
    T getBest() {
        assert(root);
        AVLnode<K, T> *current = root;
        AVLnode<K, T> *current_prev;
        while (current) {
            current_prev = current;
            current = current->right;
        }
        return current_prev->data;
    }

    int getSize() {
        return size;
    }

    AVLnode<K, T> *getRoot() {
        return root;
    }
};













#endif //HW1_AVLTREE_H