
public class LinkedList{
  // Node Class
  private class Node{
    private Task data;
    private Node next;

    //Constructors
    public Node(Task data, Node next){
      this.data = data;
      this.next = next;
    }
    public Node(Task data){
      this(data,null); // calls previous constructor
    }
    public String toString(){
      return this.data.toString();
    }
  }

  // LL Data
  private Node head;
  private int size;

  // Methods
  public LinkedList(){
    this.head = new Node(null); // Head points to null
    this.size = 0; // Variable for easy size()
  }

  public void add(int index, Task item){
    // Method adds element to LL Depending on index
    if(index < 0 || index > size){ // Checking for valid index
      System.out.println("Invalid Index!");
      return;
    }
    else if(index == 0){
      addFirst(item);
    }
    else{
      Node node = getNode(index); // get reference of prev node
      addAfter(node, item);
    }
  }
  // Add element to end of ll, useful for queue, too lazy to add rear ptr rn
  public void addLast(Task item){
    if(size == 0){
      add(0,item);
      return;
    }
    Node p = head;
    for(int i = 0; i < size; i++){
      p = p.next;
    }
    p.next = new Node(item,p.next);
    size++;


  }

  private void addAfter(Node node, Task item){
    node.next = new Node(item, node.next);
    size++;

  }
  private Node getNode(int index){
    if(index < 0 || index > size){
      System.out.println("Invalid Index!");
      return null;
    }
    // Loops over LL, returns ref to index
    Node node = head;
    for(int i = 0; i < index && node != null; i++){
      node = node.next;
    }
    return node;
  }
  private void addFirst(Task item){
    head.next = new Node(item, head.next);
    size++;
  }

  public Task remove(String taskName){
    // index to pass to remove()
    Node t = head.next;
    for(int i = 0; i < size; i++){
      if(t.data.getTaskName().equals(taskName)){
        return remove(i);
      }
      t = t.next;
    }
    return null;

  }
  public Task remove(int index){
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
      Node node = getNode(index);
      return removeAfter(node);
    }
    
  }
  
  private Task removeAfter(Node node){
    Node temp = node.next;
    if(temp != null){
      node.next = temp.next;
      size--;
      return temp.data;
    }
    return null;
  }

  private Task removeFirst(){
    Node temp = head;
    if(temp != null){
      head = head.next;
      size--;
      return temp.data;
    }
    return null;
  }


  public Task get(int index){
    Node p = head;
    for(int i = 0; i < size; i++){
      p = p.next;
      if(i == index) break;
    }

    return p.data;
  }

  public Task set(int index, Task newValue){
    Node p = head;
    for(int i = 0; i < size; i++){
      p = p.next;
      if(i == index) break;
    }
    // set node
    p.data = newValue;

    return p.data;
  }

  public int size(){
    return this.size;
  }
  
  public String toString(){
    String s = "[";
    Node p = head; // ref to head
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
  // Simple Bubble Sort
  public void sort(){
    // No need to sort if <= 1
    if(size <= 1){
      return;
    }
    Node F = head.next;
    Node P = head.next.next;
    for(int i = size-1; i > 0; i--){
      F = head.next;
      P = head.next.next;
      for(int x = 0; x < i; x++){
        if(F.data.getPriority() > P.data.getPriority()){
          Node temp = new Node(new Task(F.data.getTaskName(),F.data.getPriority(),F.data.getDueDate()));
          F.data.setPriority(P.data.getPriority());
          F.data.setDueDate(P.data.getDueDate());
          F.data.setTaskName(P.data.getTaskName());
          P.data.setPriority(temp.data.getPriority());
          P.data.setDueDate(temp.data.getDueDate());
          P.data.setTaskName(temp.data.getTaskName());
        }
        F = F.next;
        P = P.next;
      }
    }
  }

}

