// Interface for LL
public interface BareBonesLinkedList <E>{
  // add elements to LL
  public void add(int index, E item);
  // Remove item at index
  public E remove(int index);
  // Getter Setter
  public E get(int index);
  public E set(int index, E newValue);
  // get size
  public int size();
}
