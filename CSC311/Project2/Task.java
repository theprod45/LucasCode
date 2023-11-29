public class Task {
    // Variables
    String taskName;
    int priority;
    String dueDate;

    public Task(String taskName, int priority, String dueDate){
        this.taskName = taskName;
        this.priority = priority;
        this.dueDate = dueDate;
    }

    public String getTaskName() {
        return taskName;
    }

    public void setTaskName(String taskName) {
        this.taskName = taskName;
    }

    public int getPriority() {
        return priority;
    }

    public void setPriority(int priority) {
        this.priority = priority;
    }

    public String getDueDate() {
        return dueDate;
    }

    public void setDueDate(String dueDate) {
        this.dueDate = dueDate;
    }

    public String toString(){
        return taskName + " " + String.format("%d",priority) + " " + dueDate;
    }
}
