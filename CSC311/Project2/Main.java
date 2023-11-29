// Press Shift twice to open the Search Everywhere dialog and type `show whitespaces`,
// then press Enter. You can now see whitespace characters in your code.
import java.util.Scanner;
public class Main {
    public static void main(String[] args) {
        // This is where User interface is
        TaskScheduler ts = new TaskScheduler();
        ts.readFromFile();
        Scanner user = new Scanner(System.in);
        while(true){
            System.out.println("[1] addTask:\n[2] removeTask:\n[3] completeTask:\n[4] displayTasks:\n[5] prioritySorting:\n[6] undoAction:\n");
            String inp = user.nextLine();
            switch(inp){
                case "1":
                    System.out.println("Enter TaskName:");
                    String taskName = user.nextLine();
                    System.out.println("Priority:");
                    int priority = Integer.parseInt(user.nextLine());
                    System.out.println("DueDate:");
                    String dueDate = user.nextLine();
                    ts.addTask(taskName,priority,dueDate);
                    break;
                case "2":
                    // Ask to enter name to check which removeTask to use
                    System.out.println("Enter taskName(y/n?)");
                    inp = user.nextLine();
                    if(inp.equals("y")){
                        System.out.println("Enter taskName:");
                        inp = user.nextLine();
                        ts.removeTask(inp);
                    }
                    else{
                        ts.removeTask();
                    }
                    break;
                case "3":
                    ts.completeTask();
                    break;
                case "4":
                    ts.displayTask();
                    break;
                case "5":
                    ts.prioritySorting();
                    break;
                case "6":
                    ts.undoAction();
                    break;
            }
        }

    }
}