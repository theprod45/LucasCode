import java.io.File;
import java.util.Scanner;
public class TaskScheduler {
    // Variables
    private Queue qTask;
    private LinkedList completedTasks;
    private Stack actions;
    // Methods
    public TaskScheduler(){
        qTask = new Queue();
        completedTasks = new LinkedList();
        actions = new Stack();
    }
    public void readFromFile(){
        try{
            File file = new File("data.txt");
            Scanner reader = new Scanner(file);
            while(reader.hasNextLine()){
                String line = reader.nextLine();
                String[] taskData = line.split("[\\s']");
                addTask(taskData[0],Integer.parseInt(taskData[1]),taskData[2]);
            }
        } catch(Exception e){
            System.out.println("No File Found. Name File data.txt");
        }
    }
    public void addTask(String taskName, int priority, String dueDate){
        Task temp = new Task(taskName,priority,dueDate);
        qTask.add(temp);
        actions.push(temp,"add");
    }
    public void removeTask(){
        actions.push(qTask.peek(),"remove");
        qTask.remove();
    }
    public void removeTask(String taskName){
        actions.push(qTask.peek(),"remove");
        qTask.remove(taskName);
    }
    public void completeTask(){
        actions.push(qTask.peek(),"completed");
        completedTasks.addLast(qTask.peek());
        qTask.remove();
    }
    public void displayTask(){
        System.out.println(qTask.toString() + "\nCompleted Tasks:\n" + completedTasks.toString());
    }
    public void prioritySorting(){
        qTask.sort();
    }
    public void undoAction(){
        switch(actions.peek()){
            case "add":
                qTask.remove(actions.lookTaskName());
                actions.pop();
                break;
            case "remove":
                qTask.add(actions.lookHead());
                actions.pop();
                break;
            case "completed":
                completedTasks.remove(actions.lookTaskName());
                qTask.add(actions.lookHead());
                actions.pop();
                break;
        }
    }
}
