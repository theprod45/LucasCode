#include<iostream>
#include<string>
#include<cassert>
#include"Map.h"
//using KeyType = std::string;
//using ValueType = double;
//------- CHECK LIST ----------
// [ ] 1st create working BST
// [ ] 2nd Start getting map insert working with BST
// [ ] 3rd get() function working with BST and different KeyTypes
// [ ] 4th contains() function working

//constructor
Map::Map(){
  root = nullptr;
}

//Destructor
void Map::destructorR(Node *c){
  if(c == nullptr) return;
  destructorR(c->m_right);
  destructorR(c->m_left);
  delete c;
}

Map::~Map(){
  destructorR(root);
}

// Return true if the map is empty, otherwise false.
bool Map::empty() const{
  if(root == nullptr) return true;
  return false;
}

// If key is not equal to any key currently in the map, and if the
// key/value pair can be added to the map, then do so and return true.
// Otherwise, make no change to the map and return false (indicating
// that either the key is already in the map).
bool Map::insert(const KeyType& key, const ValueType& value){
  // MITE WANT TO CHECK B4 IF THE KEY EXISTS
  // If the tree is empty
  if(empty()){
    // Add the node
    root = new Node();
    root->m_right = nullptr;
    root->m_left = nullptr;
    root->m_key = key;
    root->m_value = value;
    // TEST LINE
    //
    return true;
  }
  else{
    Node *temp = root;
    while(true){
      // If the key already exists
      if(temp->m_key == key){
        // TEST LINE
        return false;
      }
      else if(key > temp->m_key){
        // If greater then the current Node
        if(temp->m_right != nullptr){
          // If a node exists under to the right
          temp = temp->m_right;
          continue;
        }
        else{
          // If a node doesn't exist under to the right add one
          // Add the node
          //TEST LINE
          //
          temp->m_right = new Node();
          temp->m_right->m_right = nullptr;
          temp->m_right->m_left = nullptr;
          temp->m_right->m_key = key;
          temp->m_right->m_value = value;
          return true;
        }
      }
      else if(key < temp->m_key){
        // If < current node
        if(temp->m_left != nullptr){
          temp = temp->m_left;
          continue;
        }
        else{
          // IF a node doesnt exist bottom left add one
          // Add the node
          //TEST LINE
          //
          temp->m_left = new Node();
          temp->m_left->m_right = nullptr;
          temp->m_left->m_left = nullptr;
          temp->m_left->m_key = key;
          temp->m_left->m_value = value;
          return true;
        }
      }
    }
  }
}

// If key is equal to a key currently in the map, then make that key no
// longer map to the value it currently maps to, but instead map to
// the value of the second parameter; return true in this case.
// Otherwise, make no change to the map and return false.
bool Map::update(const KeyType& key, const ValueType& value){
  // If empty return false
  if(empty()) return false;

  //Search for the key
  Node *temp = root;
  while(true){
    // IF key found
      if(temp->m_key == key){
        temp->m_value = value;
        //TEST CODE
        //
        return true;
      } // IF >
      else if(key > temp->m_key){
        // IF RIGHT BRANCH EXISTS
        if(temp->m_right != nullptr){
          temp = temp->m_right;
          continue;
        }
        else{
          // REACHED END OF TREE
          return false;
        }
      } // If <
      else if(key < temp->m_key){
        if(temp->m_left != nullptr){
          temp = temp->m_left;
          continue;
        }
        else{
          // REACHED END OF TREE
          return false;
        }
      }
  }
}

// If key is equal to a key currently in the map, then make that key no
// longer map to the value it currently maps to, but instead map to
// the value of the second parameter; return true in this case.
// If key is not equal to any key currently in the map then add it and
// return true. In fact this function always returns true.
bool Map::insertOrUpdate(const KeyType& key, const ValueType& value){
  // If the tree is empty
  if(empty()){
    // Add the node
    root = new Node();
    root->m_right = nullptr;
    root->m_left = nullptr;
    root->m_key = key;
    root->m_value = value;
    // TEST LINE
    //
    return true;
  }
  else{
    Node *temp = root;
    while(true){
      // If the key already exists
      if(temp->m_key == key){
        // TEST LINE
        temp->m_value = value;
        return true;
      }
      else if(key > temp->m_key){
        // If greater then the current Node
        if(temp->m_right != nullptr){
          // If a node exists under to the right
          temp = temp->m_right;
          continue;
        }
        else{
          // If a node doesn't exist under to the right add one
          // Add the node
          //TEST LINE
          //
          temp->m_right = new Node();
          temp->m_right->m_right = nullptr;
          temp->m_right->m_left = nullptr;
          temp->m_right->m_key = key;
          temp->m_right->m_value = value;
          return true;
        }
      }
      else if(key < temp->m_key){
        // If < current node
        if(temp->m_left != nullptr){
          temp = temp->m_left;
          continue;
        }
        else{
          // IF a node doesnt exist bottom left add one
          // Add the node
          //TEST LINE
          //
          temp->m_left = new Node();
          temp->m_left->m_right = nullptr;
          temp->m_left->m_left = nullptr;
          temp->m_left->m_key = key;
          temp->m_left->m_value = value;
          return true;
        }
      }
    }
  }
}

// Return true if key is equal to a key currently in the map, otherwise
// false.
bool Map::contains(const KeyType& key) const{
  // If EMPTY
  if(empty()) return false;

  Node *temp = root;
  while(true){
    if(key == temp->m_key){
      // Found it
      return true;
    }
    else if(key > temp->m_key){
      // IF >
      // If right exists
      if(temp->m_right != nullptr){
        temp = temp->m_right;
        continue;
      }
      else{
        // Doesnt exist
        return false;
      }
    }
    else if(key < temp->m_key){
      // If <
      // If left EXISTS
      if(temp->m_left != nullptr){
        temp = temp->m_left;
        continue;
      }
      else{
        //Doesnt exists
        return false;
      }
    }
  }
}

void Map::inOrder(Node *c,int& amount) const{
  // LEFT MIDDLE THEN RIGHT
  if(c == nullptr) return;
  inOrder(c->m_left,amount);
  amount++;
  inOrder(c->m_right,amount);
}

// Return the number of key/value pairs in the map.
int Map::size() const{
    int size = 0;
    inOrder(this->root,size);
    return size;
}


// If key is equal to a key currently in the map, set value to the
// value in the map that that key maps to, and return true.  Otherwise,
// make no change to the value parameter of this function and return
// false.
// value = What key maps to
bool Map::get(const KeyType& key, ValueType& value) const{
  // If EMPTY
  if(empty()) return false;

  Node *temp = root;
  while(true){
    if(temp->m_key == key){
      value = temp->m_value;
      return true;
    }
    else if(key > temp->m_key){
      if(temp->m_right == nullptr) return false;
      temp = temp->m_right;
      continue;
    }
    else if(key < temp->m_key){
      if(temp->m_left == nullptr) return false;
      temp = temp->m_left;
      continue;
    }
  }
}


// If 0 <= i < size(), copy into the key and value parameters the
// key and value of one of the key/value pairs in the map and return
// true.  Otherwise, leave the key and value parameters unchanged and
// return false.  (See below for details about this function.)
bool Map::get(int i, KeyType& key, ValueType& value) const{
  Node *temp = root;
  int j = 0;
  return PreOrder(temp,key,value,j,i);
}

bool Map::PreOrder(Node *c,KeyType& key, ValueType& value,int &j, int &i) const{
  // LEFT MIDDLE THEN RIGHT
  if(c == nullptr) return false;
  if(j==i){
    value = c->m_value;
    key = c->m_key;
    return true;
  }
  if(c->m_left != nullptr){
    PreOrder(c->m_left,key,value,++j,i);
  }
  if(c->m_right != nullptr){
    PreOrder(c->m_right,key,value,++j,i);
  }
  return false;
}

// COPY CONTRUCTOR

void Map::copyTree(Node* &c,const Node* source){
  if(source == nullptr){
    c = nullptr;
  }
  else{
    c = new Node;
    c->m_value = source->m_value;
    c->m_key = source->m_key;
    copyTree(c->m_left, source->m_left);
    copyTree(c->m_right,source->m_right);
  }

}

Map::Map(const Map& rhs){
  if(rhs.root == nullptr){
    root = nullptr;
  }
  else{
    copyTree(this->root, rhs.root);
  }
}

const Map& Map::operator=(const Map& rhs){
  if(rhs.root == nullptr){
    root = nullptr;
  }
  else{
    copyTree(this->root, rhs.root);
  }
  return *this;
}


// Exchange the contents of this map with the other one.
void Map::swap(Map& other){
  Node *temp = root;
  root = other.root;
  other.root = temp;
}


void subtract(const Map& m1, const Map& m2, Map& result){
  ValueType v;
  KeyType k;
  for(int i = 0; i < m1.size(); i++){
    m1.get(i,k,v);
    if(!m2.contains(k)){
      result.insert(k,v);
    }
  }
}

bool combine(const Map& m1, const Map& m2, Map& result){
  bool f = true;
  KeyType k;
  ValueType v;
  // Copy over 1st map to results
  result = m1;
  for(int i = 0; i < m2.size(); i++){
    m2.get(i,k,v);

    KeyType k2;
    ValueType v2;
    //Check if 2nd map Key exists in results and if values are the same
    for(int j = 0; j < result.size(); j++){
      result.get(j,k2,v2);
      // if key and value ==
      if(k2 == k && v2 == v){
        break;
      }
      // if key and value are diff
      if(k2 == k && v2 != v){
        result.erase(k2);
        bool f = false;
        break;
      }
    }
    return f;
  }


  return true;
}

// If key is equal to a key currently in the map, remove the key/value
// pair with that key from the map and return true.  Otherwise, make
// no change to the map and return false.
bool Map::erase(const KeyType& key){
  Node *temp = root;
  return eraseR(temp,key);
}

bool Map::eraseR(Node* c, const KeyType& key){
  // Find KEY NODE
  bool found = false;
  Node *p = nullptr;
  Node *cur = c;
  if(cur == nullptr){
    return false;
  }
  while(cur != nullptr){
    if(cur->m_key == key){
      found = true;
      break;
    }
    else{
      p = cur;
      if(key > c->m_key){
        cur = cur->m_right;
      }
      else
        cur=cur->m_left;
    }
  }
  // if not Found
  if(!found){
    return false;
  }
  //Single Child
  if((cur->m_right == nullptr && cur->m_left != nullptr)||(cur->m_right != nullptr && cur->m_left == nullptr)){
    // m_right child
    if(cur->m_left == nullptr && cur->m_right != nullptr){
      // if part of p's m_left TREE
      if(p->m_left == cur){
        // p's m_left tree is now c m_right TREE
        p->m_left = cur->m_right;
        delete cur;
        cur = nullptr;
        return true;
      }
      else{
        // if part of p's m_right tree
        p->m_right = cur->m_right;
        delete cur;
        cur = nullptr;
        return true;
      }
    }
    else{ // m_left child
      if(p->m_left == cur){
        p->m_left = cur->m_left;
        delete cur;
        cur = nullptr;
        return true;
      }
      else{
        p->m_right = cur->m_left;
        delete cur;
        cur = nullptr;
        return true;
      }
    }

  }
  // Leaf node
  if(cur->m_left == nullptr && c->m_right == nullptr){
    if(p->m_left == cur){
      p->m_left = nullptr;
    }
    else{
      p->m_right = nullptr;
    }
    delete cur;
    return true;
  }
  //2 Children
  if(cur->m_left != nullptr && cur->m_right != nullptr){
    Node* temp = cur->m_right;
    if(cur->m_left == nullptr && cur->m_right == nullptr){
      cur = temp;
      delete temp;
      cur->m_right = nullptr;
      return true;
    }
    else{
      if(cur->m_right->m_left!=nullptr){
        Node* lc;
        Node* lc2;
        lc2 = cur->m_right;
        lc = cur->m_right->m_left;
        while(lc->m_left != nullptr){
          lc2 = lc;
          lc = lc->m_left;
        }
        cur->m_key = lc->m_key;
        cur->m_value = lc->m_value;
        delete lc;
        lc2->m_left = nullptr;
        return true;
      }
      else{
        Node* t = cur->m_right;
        cur->m_key = t->m_key;
        cur->m_value = t->m_value;
        cur->m_right = t->m_right;
        delete t;
        return true;
      }
    }
    return false;
  }
  return false;
}

/*
int main(){
  Map m;
   assert(m.insert(123, "Fred"));
   assert(m.insert(456, "Ethel"));
   assert(m.size() == 2);
   std::string s;
   assert(m.get(123, s)  &&  s == "Fred");
   s = "";
   int i1;
   assert(m.get(0, i1, s)  && ((i1 == 123  &&  s == "Fred")  ||  (i1 == 456  &&  s == "Ethel")));
   m.get(0,i1,s);
   std::cout << i1 << " " << s << std::endl;
   int i2;
   m.get(1,i2,s);
   std::cout << "i1 " << i1 << " i2 " << i2 << std::endl;
   std::cout << i2 << s << std::endl;
   assert(m.get(1, i2, s) && ((i2 == 123  &&  s == "Fred")  ||  (i2 == 456  &&  s == "Ethel")));
   //assert(m.get(1, i2, s)  &&  i1 != i2  && ((i2 == 123  &&  s == "Fred")  ||  (i2 == 456  &&  s == "Ethel")));
}
*/
/*
int main(){
  Map m;
  std::cout << m.empty() << std::endl;
  // TRY DIFFERENT KEY TYPES
  KeyType k1 = "A";
  ValueType v1 = 1.0;
  KeyType k2 = "B";
  ValueType v2 = 2.0;
  KeyType k3 = "C";
  ValueType v3 = 3.0;
  KeyType k4 = "D";
  ValueType v4 = 4.0;
  KeyType k5 = "E";
  ValueType v5 = 5.0;
  KeyType k6 = "F";
  ValueType v6 = 6.0;
  KeyType k7 = "G";
  ValueType v7 = 7.0;
  KeyType k8 = "H";
  ValueType v8 = 8.0;
  m.insert(k4,v1);
  m.insert(k2,v2);
  m.insert(k6,v6);
  m.insert(k1,v1);
  m.insert(k7,v7);
  m.contains(k7);
  ValueType vTest;
  m.get(k7,vTest);
  std::cout << vTest << std::endl;
  ValueType vTest2;
  KeyType kTest;
  //for(int i = 0; i < m.size(); i++){
  //  m.get(i,kTest,vTest2);
  //  std::cout << kTest << " " << vTest2 << std::endl;
  //}
  Map m2;
  m2.insert(k2,v1);
  Map r;
  m.combine(m,m2,r);
  for(int i = 0; i < m.size(); i++){
    m.get(i,kTest,vTest2);
    std::cout << kTest << " " << vTest2 << std::endl;
  }
  std::cout<< " \n";
  m.erase(k2);
  //m.erase(k6);
  for(int i = 0; i < m.size(); i++){
    m.get(i,kTest,vTest2);
    std::cout << kTest << " " << vTest2 << std::endl;
  }
}
*/
