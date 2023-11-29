// Class to create and test LL
public class DHLinkedListDriver{
  public static void main(String[] args){
    // Create a LL obj
    DHSingleLinkedList<Integer> list = new DHSingleLinkedList<>();
    System.out.println(list);
    list.add(0,10); System.out.println(list);
    list.add(0,20); System.out.println(list);
    list.add(0,30); System.out.println(list);
    list.add(1,99); System.out.println(list);
    list.add(2,55); System.out.println(list);
    list.remove(0); System.out.println(list);
    list.remove(1); System.out.println(list);
    list.set(0,1); System.out.println(list);
    list.set(1,0); System.out.println(list);
    System.out.println(list.get(0));
    System.out.println(list.get(1));
  }
}
