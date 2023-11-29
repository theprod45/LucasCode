public class LinkedList {
  // Creating my own Node class
  private class Node {
    private Flight data;
    private Node next;

    public Node(Flight data, Node next) {
      this.data = data;
      this.next = next;
    }
    public Node(Flight data) {
      this(data, null);
    }
    public Flight getFlight() {
      return data; // Used to return Flight to get Time and flightId
    }
  }

  // LinkedList Data
  private Node head;
  private int size;

  // Methods
  public LinkedList() {
    this.head = new Node(null); // head points to null
    this.size = 0;
  }

  // Adds item to LL using time as index
  public void add(Flight item) {
    // Checks if list is empty then adds
    if (size == 0) {
      addFirst(item);
      return;
    }
    Node tempI = head.next;
    Node temp = head.next;
    // Checks to see if time < head and adds to front
    if (item.getTime() < tempI.getFlight().getTime()) {
      addFirst(item);
      return;
    }
    // If not adding in the front then get the node it will add after
    for (int i = 0; i < size; i++) {
      if (tempI.getFlight().getTime() < item.getTime()) {
        temp = tempI;
      }
      tempI = tempI.next;
    }
    addAfter(temp, item);
  }
  private void addFirst(Flight item) { // Add first method
    head.next = new Node(item, head.next);
    this.size++;
  }
  private void addAfter(Node node, Flight item) { // Add After method
    node.next = new Node(item, node.next);
    this.size++;
  }

  // Remove a Node based on flightId
  public void remove(String flightId) {
    if (head.next.getFlight().getFlightId().equals(flightId)) {
      removeFirst();
      return;
    } else {
      // Find which node is before our node
      Node temp = head.next;
      for (int i = 0; i < size; i++) {
        if (temp.next.getFlight().getFlightId().equals(flightId)) {
          removeAfter(temp);
          return;
        }
        temp = temp.next;
      }
    }
  }
  private void removeAfter(Node node) {
    Node temp = node.next;
    if (temp != null) {
      node.next = temp.next;
      size--;
      return;
    }
  }
  private void removeFirst() {
    Node temp = head;
    if (temp != null) {
      head = head.next;
      this.size--;
      return;
    }
  }
  //Returns true if FlightID already exists
  public boolean find(String flightId) {
    if (size == 0) {
      return false;
    }
    Node temp = head.next;
    for (int i = 0; i < size; i++) {
      if (temp.getFlight().getFlightId().equals(flightId)) {
        return true;
      }
      temp = temp.next;
    }
    return false;
  }
  // Returns true if time already exists
  public boolean find(int time) {
    if (size == 0) {
      return false;
    }
    Node temp = head.next;
    for (int i = 0; i < size; i++) {
      if (temp.getFlight().getTime() == time) {
        return true;
      }
      temp = temp.next;
    }
    return false;
  }

  public String toString() {
    String s = "";
    Node p = head;
    if (p != null) {
      while (p.next != null) {
        s += p.next.data + "\n";
        p = p.next;
      }
    }
    return s;
  }

  public int size() {
    return this.size;
  }

}
