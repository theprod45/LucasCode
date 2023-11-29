
public class DHSingleLinkedList <E> implements BareBonesLinkedList<E>{
  // Node Class
  private class Node<F>{
    private F data;
    private Node<F> next;

    //Constructors
    public Node(F data, Node<F> next){
      this.data = data;
      this.next = next;
    }
    public Node(F data){
      this(data,null); // calls previous constructor
    }
  }

  // LL Data
  private Node<E> head;
  private int size;

  // Methods
  public DHSingleLinkedList(){
    this.head = new Node<E>(null); // Head points to null
    this.size = 0; // Varirable for easy size()
  }

  @Override
  public void add(int index, E item){
    // Method adds element to LL Depending on index
    if(index < 0 || index > size){ // Checking for valid index
      System.out.println("Invalid Index!");
      return;
    }
    else if(index == 0){
      addFirst(item);
    }
    else{
      Node<E> node = getNode(index); // get refernce of prev node
      addAfter(node, item);
    }
  }

  private void addAfter(Node<E> node, E item){
    node.next = new Node<E>(item, node.next);
    size++;

  }
  private Node<E> getNode(int index){
    if(index < 0 || index > size){
      System.out.println("Invalid Index!");
      return null;
    }
    // Loops over LL, returns ref to index
    Node<E> node = head;
    for(int i = 0; i < index && node != null; i++){
      node = node.next;
    }
    return node;
  }
  private void addFirst(E item){
    head.next = new Node<E>(item, head.next);
    size++;
  }

  @Override
  public E remove(int index){
    // removes an element from index
    // Check if valid
    if(index < 0 || index > size){
      System.out.println("Invalid Index!");
      return null;
    }
    else if(index == 0){
      return removeFirst();
    }
    else{
      Node<E> node = getNode(index);
      return removeAfter(node);
    }
    
  }
  
  private E removeAfter(Node<E> node){
    Node<E> temp = node.next;
    if(temp != null){
      node.next = temp.next;
      size--;
      return temp.data;
    }
    return null;
  }

  private E removeFirst(){
    Node<E> temp = head;
    if(temp != null){
      head = head.next;
      size--;
      return temp.data;
    }
    return null;
  }


  @Override
  public E get(int index){
    Node<E> p = head;
    for(int i = 0; i < size; i++){
      p = p.next;
      if(i == index) break;
    }

    return p.data;
  }

  @Override
  public E set(int index, E newValue){
    Node<E> p = head;
    for(int i = 0; i < size; i++){
      p = p.next;
      if(i == index) break;
    }
    // set node
    p.data = newValue;

    return p.data;
  }
  
  @Override
  public int size(){
    return this.size;
  }
  
  public String toString(){
    String s = "[";
    Node<E> p = head; // ref to head
    if( p!= null){
      while(p.next != null){
        s += p.next.data + " -> ";
        p = p.next;
      }
    }
    // end of ll
    s += "]";
    return s;
  }
}
