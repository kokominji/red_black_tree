#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  // TODO: initialize struct if needed
  node_t *nil = (node_t *)calloc(1,sizeof(node_t));
  nil->color = RBTREE_BLACK; //nill은 블랙

  p->nil = nil; //트리의 nill과 루트를 nill로 초기화
  p->root = nil;

  return p;
}

//모든 메모리 해제
//후위순회하며 모두 삭제
void free_node(rbtree *t, node_t *node) {
    if (node == t->nil) return; //노드가 nill이라면 return

    free_node(t, node->left); //왼쪽 먼저, 오른쪽, 자신
    free_node(t, node->right);
    free(node);
  }

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  if (t == NULL) return;

  free_node(t, t->root);
  free(t->nil);
  free(t);
}
//루트 먼저 삭제
//nill삭제
//free(t)

//트리 좌회전용 함수
void LEFT_ROTATE(rbtree *t, node_t *x){
  node_t *y = x->right; //y는 회전 후 x의 부모
  x->right = y->left;
  
  if (y->left != t->nil){
    y->left->parent = x; //y->left의 부모를 x로 바꿈
  }
  y->parent = x->parent;

  if (x->parent == t->nil){ //루트라면! parent가 nill이라는 것은 위가 없다. 루트이다
    t->root = y;
  }
  else if (x==x->parent->left){ //루트가 따로 존재한다면
    x->parent->left = y; //y는 왼쪽 자식
  }
  else x->parent->right = y; 

  y->left = x;
  x->parent = y;
}

//트리 우회전용 함수
void RIGHT_ROTATE(rbtree *t, node_t *x){
  node_t *y = x->left; //y는 회전 후 x의 부모
  x->left = y->right;
  
  if (y->right != t->nil){
    y->right->parent = x; //y->right의 부모를 x로 바꿈
  }
  y->parent = x->parent;

  if (x->parent == t->nil){ //루트라면! parent가 nill이라는 것은 위가 없다. 루트이다
    t->root = y;
  }
  else if (x==x->parent->right){ //루트가 따로 존재한다면
    x->parent->right = y; //y는 오른쪽 자식
  }
  else x->parent->left = y; 

  y->right = x;
  x->parent = y;
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  node_t *new_node = (node_t *)calloc(1,sizeof(node_t)); //새로운 노드 동적 할당 및 초기화
  new_node->key = key;
  new_node->color = RBTREE_RED;
  new_node->left = t->nil; //아직 자식이 없어서 nill로 초기화
  new_node->right = t->nil;

  //삽입 위치 탐색을 위한 포인터 설정
  //현재 값이 root라서 parent값은 nil
  node_t *parent = t->nil; 
  node_t *cur = t->root;

  //BST 삽입 위치 찾기
  while (cur != t->nil){
    parent = cur;
    if(key < cur -> key) {
      cur = cur->left;
    } else {
      cur = cur->right;
    }
  }

  //부모 연결
  new_node->parent = parent;

  if (parent == t->nil){
    t->root = new_node;   //루트노드에 삽입되는 경우
  } else if (key < parent -> key){
    parent->left = new_node;
  } else{
    parent->right = new_node;
  }
  
    rbtree_insert_fixup(t, new_node);
    return new_node;
}
  //색칠
  void rbtree_insert_fixup(rbtree *t, node_t *z){

    while (z->parent->color == RBTREE_RED){
      if (z->parent == z->parent->parent->left){ 
        node_t *y = z->parent->parent->right;  //y는 z의 삼촌
      
      if (y->color == RBTREE_RED) {
        //case1 부모와 삼촌이 red
        z->parent->color == RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
      }
      else{
        //case2 부모는 red, 삼촌은 black, z는 오른쪽 자식
        if (z == z->parent->right){
          z = z->parent;
          LEFT_ROTATE(t, z);
        }
        //case3 부모는 red, 삼촌은 black z는 왼쪽 자식
      z->parent->color = RBTREE_BLACK;
      z->parent->parent = RBTREE_RED;
      RIGHT_ROTATE(t,z->parent->parent);
      }     
    } else {
      //부모가 오른쪽 자식일때 : 좌우대칭
       node_t *y = z->parent->parent->left;  
      
      if (y->color == RBTREE_RED) {
        //case1 부모와 삼촌이 red
        z->parent->color == RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
      }
      else{
        //case2 
        if (z == z->parent->left){
          z = z->parent;
          RIGHT_ROTATE(t, z);
        }
        //case3
        z->parent->color = RBTREE_BLACK;
        z->parent->parent = RBTREE_RED;
        LEFT_ROTATE(t,z->parent->parent);
      }     
    }
  }
  //root는 항상 black
  t->root->color = RBTREE_BLACK;
}


node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}
