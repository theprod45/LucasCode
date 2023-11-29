public class Stack {
    // Variables
    private class Node{
        private Task task;
        private String method; // Either "add","remove",or "complete";
        private Node next;
        public Node(Task task, String method){
            this.task = task;
            this.method = method;
            this.next = null;
        }
        public Node(){
            this.task = null;
            this.method = null;
            this.next = null;
        }
    }

    private Node head;
    // Methods
    public Stack(){
        head = new Node();
    }
    // When we add to stack we need Task and methodName
    public void push(Task task, String methodName){
        head.next = new Node(task,methodName);
    }
    // Pop first element
    public Task pop(){
        Node temp = head;
        if(temp != null) {
            head = head.next;
            return temp.task;
        }
        return null;
    }
    // Peek first elements string
    public String peek(){
        return head.next.method;
    }
    public String lookTaskName(){
        return head.next.task.getTaskName();
    }
    public Task lookHead(){
        return head.next.task;
    }
}
