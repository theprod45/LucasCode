public class ArrayListDriver{
  public static void main(String[] args){
    // Test the methods
    DHArrayList<Integer> list = new DHArrayList<>(1);
    list.add(10);
    System.out.println(list);
    list.add(20);
    System.out.println(list);
    list.add(30);
    System.out.println(list);
    list.add(40);
    System.out.println(list);
    list.add(50);
    System.out.println(list);
    list.add(100,3);
    System.out.println(list);
    list.remove(1);
    System.out.println(list);
    Integer value = list.get(0);
    System.out.println("Tje value at location 0 is: " + value);
    System.out.println(list);
    list.set(99,0);
    System.out.println(list);
    System.out.println(list.indexOf(50));

  }

}
