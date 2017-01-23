#include "TreeDB.h"

TreeDB::TreeDB(){
    root = NULL;
}

TreeDB::~TreeDB(){
    removeAll(root);
}

bool TreeDB::insert(DBentry* newEntry){
   if(find(newEntry->getName()) != NULL)
        return false;
    TreeNode* new_node =  new TreeNode(newEntry);    
    if(root == NULL){
        root = new_node;
       return true;
    }
        insert_(new_node,root);
        return true;
}

void TreeDB::insert_(TreeNode* new_node,TreeNode* cur_node){
   if(new_node->getEntry()->getName().compare(cur_node->getEntry()->getName()) >0 ){ //new > cur 
       if(cur_node->getRight() == NULL){
           cur_node->setRight(new_node);
       }else{
            insert_(new_node,cur_node->getRight());
       }    
    }else{
        if(cur_node->getLeft() == NULL){
            cur_node->setLeft(new_node);
        }else{
            insert_(new_node,cur_node->getLeft());
        }
    }
    return;
}

DBentry* TreeDB::find(string name){
    probesCount = 0;
    TreeNode* found;
    if(root ==  NULL){
        return NULL;
    }else{
        found = find_(root, name);
        if(found == NULL){
             return NULL;
        }else{
            return found->getEntry();
        }
    }
    
}

TreeNode* TreeDB::find_(TreeNode* root, string name){
    probesCount++;
    if(root==NULL){
        return NULL;
    }else if(root->getEntry()->getName().compare(name) == 0 ){
        return root;
    }else if(root->getEntry()->getName().compare(name) <0 ){
        return find_(root->getRight(),name);
    }else{
        return find_(root->getLeft(),name);
    }
    return NULL;
}

void TreeDB::countActive () const{ 
    int count = 0;
    countActive_(root,count);
    cout <<count<<endl;   
    return;   
}
void TreeDB::countActive_(TreeNode* root,int &count)const{
    if(root !=NULL ){
        countActive_(root->getLeft(),count);
        if(root ->getEntry()->getActive())
            count++;
        countActive_(root->getRight(),count);
    }
    return;
}

void TreeDB::printProbes() const{
    cout<<probesCount<<endl;
    return;
}
bool TreeDB::remove(string name){
    if(name==""){
        removeAll(root);
        root = NULL;
        return true;
    } else{
        if(removeOne(name))
            return true;
        else
            return false;        
    }
} 

void TreeDB::removeAll( TreeNode* const &temp){
    DBentry* deleteNode;
    if(temp !=NULL ){
        removeAll(temp->getLeft());
        removeAll(temp->getRight());
        delete temp;
    }
    return;
}

bool TreeDB::removeOne(string name){
    TreeNode* prev_node;
    TreeNode* prev_node_left;
    TreeNode* prev_node_right;
    TreeNode* node_delete;
    if(root == NULL){
        return false;     
    }
    if(root->getEntry()->getName().compare(name) == 0){
        removeOne_(NULL,root,1);
        return true;
    }
    prev_node = findNode(name);
    if(prev_node==NULL){
        return false;
    }
    prev_node_left = prev_node->getLeft();
    prev_node_right = prev_node->getRight();
 
    if((prev_node_left->getEntry()->getName()).compare(name)==0){
        removeOne_(prev_node,prev_node_left,1);
    }else{
        removeOne_(prev_node,prev_node_right,0);
    }
    return true;
}

void TreeDB::removeOne_(TreeNode* const &prev_node, TreeNode* const &node_del,int if_left){
    TreeNode* max_in_left;
    TreeNode* new_root;
    TreeNode* prev_node_max;
    DBentry* max_in_left_entry;
    TreeNode* root_left;
    TreeNode* root_right;
    if(node_del->getLeft()==NULL && node_del->getRight()==NULL){
        if(prev_node != NULL){
            if(if_left)
                prev_node->setLeft(NULL);
            else
                prev_node->setRight(NULL);
        }
        delete node_del;
    }else if(node_del->getLeft()!= NULL && node_del->getRight()==NULL){
        if(prev_node != NULL){
            if(if_left)
                prev_node->setLeft(node_del->getLeft());
            else
                prev_node->setRight(node_del->getLeft());
            delete node_del;
        }else{
            root_left = root->getLeft();
            delete root;
            root =  root_left;
        }
    }else if(node_del->getLeft()== NULL && node_del->getRight()!=NULL){
        if(prev_node != NULL){
            if(if_left)
                prev_node->setLeft(node_del->getRight());
            else
                prev_node->setRight(node_del->getRight());
            delete node_del;
        }else{
            root_right = root->getRight();
            delete root;
            root =  root_right;
        }        
    }else{
        max_in_left = max(node_del->getLeft());
        max_in_left_entry = new DBentry(max_in_left->getEntry()->getName(),
                max_in_left->getEntry()->getIPaddress(),max_in_left->getEntry()->getActive());
      
        new_root = new TreeNode(max_in_left_entry);
        
        prev_node_max = findNode(max_in_left->getEntry()->getName());
        if(prev_node_max != node_del)
            removeOne_(prev_node_max,prev_node_max->getRight(),0);
        else
            removeOne_(prev_node_max,prev_node_max->getLeft(),1);
        if(prev_node != NULL){
            if(if_left)
                prev_node->setLeft(new_root);
            else
                prev_node->setRight(new_root);        
            new_root->setLeft(node_del->getLeft());
            new_root->setRight(node_del->getRight());
            delete node_del;
        }else{
            root_right = root->getRight();
            root_left = root->getLeft();
            delete node_del;
            root = new_root;
            new_root->setLeft(root_left);
            new_root->setRight(root_right);            
        }
    }
}

TreeNode* TreeDB::max(TreeNode* curNode){
    if(curNode->getRight() == NULL)
        return curNode;   
    else
        return max(curNode->getRight());
}
//return prev_node of the query
TreeNode* TreeDB::findNode(string name){
    TreeNode* temp_root = root;
    TreeNode* prev_root;
   
    while(temp_root!=NULL && ((temp_root->getEntry())->getName()).compare(name) != 0){
        if((temp_root->getEntry()->getName()).compare(name)>0  ){//str 1 < str 2
            prev_root = temp_root;
            temp_root = temp_root->getLeft();
        }else{
            prev_root = temp_root;
            temp_root = temp_root->getRight();
        }
    }
    if(temp_root !=NULL && (temp_root->getEntry()->getName()).compare(name) == 0){
        return prev_root;//if temproot==null,return prev_node
    }    
    return NULL;
}

// You *may* choose to implement the function below to help print the 
// tree.  You do not have to implement this function if you do not wish to.
ostream& operator<< (ostream& out, TreeNode* rhs){
    if(rhs !=NULL ){
        out<<(rhs->getLeft());
        out << *(rhs->getEntry());
        out<<(rhs->getRight());
    }
    return out ;
} 

ostream& operator<< (ostream& out, const TreeDB& rhs){ 
   if(rhs.root!=NULL)
        return out<<rhs.root;
   
   return out;
}