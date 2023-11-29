import java.util.Scanner;
public class UserInterface {
  public static void main(String[] args) {
    // Create The runway
    RunwayScheduler tempRunway = new RunwayScheduler();
    Scanner user = new Scanner(System.in);
    while (true) {
      System.out.println("Enter 1 to: Schedule Flight");
      System.out.println("Enter 2 to: Cancel Flight");
      System.out.println("Enter 3 to: Display Schedule");
      System.out.println("Enter 4 to: Read From File");
      System.out.println("Enter 5 to: Write to File");
      System.out.println("Enter 6 to: Exit Program");
      String userInput = user.nextLine();
      switch (userInput) {
      case "1":
        System.out.println("Enter FlightID:");
        String flightId = user.nextLine();
        System.out.println("Enter Status:");
        String status = user.nextLine();
        System.out.println("Enter Priority:");
        String priority = user.nextLine();
        System.out.println("Enter Time:");
        int time = tempRunway.timeString(user.nextLine());
        tempRunway.scheduleFlight(flightId, status, priority, time);
        break;
      case "2":
        System.out.println("Enter flightId:");
        String flightID = user.nextLine();
        tempRunway.cancelFlight(flightID);
        break;
      case "3":
        tempRunway.displaySchedule();
        break;
      case "4":
        System.out.println("Enter Filename:");
        String filename = user.nextLine();
        tempRunway.readFromFile(filename);
        break;
      case "5":
        System.out.println("Enter Filename:");
        String output = user.nextLine();
        tempRunway.writeToFile(output);
        break;
      case "6":
        return;
      }
    }
  }
}
