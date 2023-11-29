public interface BareBonesArrayList<E>{
  public void add(E a);
  public void add(E a, int index);
  public E remove(int index);
  public E get(int index);
  public void set(E a, int index);
  public int getSize();
  public int indexOf(E a);
}
