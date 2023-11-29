import java.io.FileWriter;
import java.io.IOException;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
// This class manages LL for 2 runways
public class RunwayScheduler {
  // Private Variables
  private LinkedList runway1;
  private LinkedList runway2;

  // Public Methods
  // Constructor
  public RunwayScheduler() {
    runway1 = new LinkedList();
    runway2 = new LinkedList();
  }
  public void scheduleFlight(String flightId, String status, String priority, int time) {
    if (runway1.find(flightId) || runway2.find(flightId)) { // Checks if flight already exists
      System.out.println("Flight " + flightId + " Already exists!");
    }
    Flight f = new Flight(flightId, status, priority, time);
    if (runway1.find(time) && !runway2.find(time)) { // If Time exists in runway1 and not runway2 add to r2
      runway2.add(f);
    } else if (!runway1.find(time)) { // If time doesn't exist in runway1 add to runway1
      runway1.add(f);
    }

  }
  public void cancelFlight(String flightId) {
    // Check runway1 if not check runway2
    if (runway1.find(flightId)) {
      runway1.remove(flightId);
      return;
    } else if (runway2.find(flightId)) {
      runway2.remove(flightId);
      return;
    }
    System.out.println(flightId + "DOESN't EXIST!");

  }
  public void displaySchedule() {
    System.out.println("+-----------------");
    System.out.println("RUNWAY1\n" + runway1);
    System.out.println("RUNWAY2\n" + runway2);
    System.out.println("+-----------------");
  }
  public void readFromFile(String filename) {
    try {
      File file = new File(filename);
      Scanner reader = new Scanner(file);
      while (reader.hasNextLine()) {
        String line = reader.nextLine();
        String[] flightData = line.split("[\\s']");
        scheduleFlight(flightData[0], flightData[1], flightData[2], timeString(flightData[3]));

      }
    } catch (Exception e) {
      System.out.println("An Error Occured");
    }
  }
  // THIS CONVERTS STRING 12:00 to 1200, used for how i handle data
  public int timeString(String time) {
    return Integer.parseInt(time.replace(":", ""));
  }
  public void writeToFile(String filename) {
    try {
      FileWriter writer = new FileWriter(filename);
      writer.write("" + runway1); // Writes runway1 to file
      writer.write("" + runway2); // Writes runway2 to file
      writer.close();
    } catch (IOException e) {
      System.out.println("An Error Occured");
    }
  }
}
