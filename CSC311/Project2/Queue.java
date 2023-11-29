public class Queue {
    // Variables
    private LinkedList ll; // Creating a Queue with LL

    // Public Methods
    public Queue(){
        ll = new LinkedList();
    }
    // Returns first element of the queue
    public Task peek(){
        return ll.get(0); // Always returns first element in ll
    }
    // Removes first element
    public Task remove(){
        return ll.remove(0);
    }
    // Removes element based on taskName
    public Task remove(String taskName){
        return ll.remove(taskName);
    }
    // Adds element to end of queue
    public void add(Task t){
        ll.addLast(t);
    }
    public String toString(){
        return ll.toString();
    }
    public void sort(){
        ll.sort();
    }
}
