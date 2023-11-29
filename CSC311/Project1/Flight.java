public class Flight {
  // Class Variables
  private String flightId; // ID for flight
  private String status; // Status of flight Arriving or Departing
  private String priority; // Emergency, VIP, Regular
  private int time; // Taken as Military Time 0100-2400
  // Constructor
  public Flight(String flightId, String status, String priority, int time) {
    this.flightId = flightId;
    this.status = status;
    this.priority = priority;
    this.time = time;
  }
  // Returns String of Flight
  public String toString() {
    String sTime = String.valueOf(this.time); // Time is Stored as 1200 so need to cnvrt to 12:00  
    return (this.flightId + " " + this.status + " " + this.priority + " " + sTime.substring(0, 2) + ":" + sTime.substring(2));
  }
  // Some Getters
  public int getTime() {
    return this.time;
  }
  public String getFlightId() {
    return this.flightId;
  }
}
