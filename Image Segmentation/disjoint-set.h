#ifndef DISJOINT_SET  
#define DISJOINT_SET  
  
// disjoint-set forests using union-by-rank and path compression (sort of).  
  
typedef struct {  
  int rank; //   
  int p;  
  int size;  
} uni_elt;  
  
class universe {  
public:  
  universe(int elements);  
  ~universe();  
  int find(int x);    
  void join(int x, int y);  
  int size(int x) const { return elts[x].size; }  
  int num_sets() const { return num; }  
//private £º  
public :  
  uni_elt *elts;  
  int num;  
};  
  
universe::universe(int elements) {  
  elts = new uni_elt[elements];  
  num = elements;  
  for (int i = 0; i < elements; i++) {  
    elts[i].rank = 0;  
    elts[i].size = 1;  
    elts[i].p = i;  
  }  
}  
    
universe::~universe() {  
  delete [] elts;  
}  
  
int universe::find(int x) {  
  int y = x;  
  while (y != elts[y].p) // it was first initialized with itself ,  
    y = elts[y].p;       // if it doesn't point to itself then it must have merged to other component.   
                         // elts[y] indicate to which component it connect, flowing this link iteratively we can find the component Id which they formed at last.    
  elts[x].p = y;         // keep track with the latest component to avoid indirect finding the latest component to save time    
  return y;  
}  
  
void universe::join(int x, int y) {  
  if (elts[x].rank > elts[y].rank) {  
    elts[y].p = x; //update the head of y to x   
    elts[x].size += elts[y].size; //size after merged   
  } else {  
    elts[x].p = y;  
    elts[y].size += elts[x].size;  
    if (elts[x].rank == elts[y].rank) // there must be only one head    
      elts[y].rank++;  // ,so just appoint the later as leader   
  }  
  num--; // component number remain   
}  
  
#endif  