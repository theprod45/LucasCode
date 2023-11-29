public class DHArrayList<E> implements BareBonesArrayList<E>{
  
  //Data
  private int size; // Elements inside
  private int capacity; // Array Size
  private E[] myArray;
  private static final int INITIAL_CAPACITY = 10;

  
  
  //Methods
  
  public DHArrayList(){
    this.capacity = INITIAL_CAPACITY;
    this.size = 0;
    myArray = (E[]) new Object[this.capacity];
  }

  public DHArrayList(int capacity){
    this.capacity = capacity;
    this.size = 0;
    myArray = (E[]) new Object[this.capacity];
  }

  @Override
  public void add(E a){
    // Adds element to end of list
    if(this.size < this.capacity){
      myArray[size] = a;
      size++;
    }
    else{
      // Create new array and move stuff over
      System.out.println("There isn't space, calling reallocate");
      this.reallocate();
      this.add(a);
    }
  }
  private void reallocate(){
    this.capacity *= 2;
    E[] temp = (E[]) new Object[this.capacity];
    // Copy stuff over
    for(int i = 0; i < myArray.length; i++){
      temp[i] = myArray[i];
    }
    this.myArray = temp; // jAvA PoiNtErS
  }

  @Override
  public void add(E a, int index){
    if(index < 0 || index > size){
      System.out.println("Invalid index!");
      return;
    }
    else if(index == size){
      this.add(a);
    }
    else{
      if(this.size == this.capacity){
        this.reallocate();
      }
      for(int i = size; i > index; i--){
          this.myArray[i] = this.myArray[i-1];
      }
      this.myArray[index] = a;
      this.size++;
    }

  }
  
  @Override
  public E remove(int index){
    if(index < 0 || index >= size){
      System.out.println("Invalid Index!");
      return null;
    }
    E temp = myArray[index];
    for(int i = index; i < size -1; i++){
      this.myArray[i] = this.myArray[i+1];
    }
    this.size--;
    return temp;
  }

  @Override
  public E get(int index){
    if(index < 0 || index >= size){
      System.out.println("Invalid Index");
      return null;
    }
    return myArray[index];
  }

  @Override
  public void set(E a, int index){
    if(index < 0 || index >= size){
      System.out.println("invalid index");
      return;
    }
    myArray[index] = a;
    return;
  }

  @Override
  public int getSize(){
    return this.size;
  }
  
  @Override
  public int indexOf(E a){
    // finds first location of element
    for(int i = 0; i < this.size; i++){
      if(myArray[i] == a) return i;
    }
    return -1;
  }

  public String toString(){
    // array as String
      String s =  "";
    for(int i = 0; i < this.size; i++){
      s = s+ myArray[i] + ", "; 
    }
    return s;
  }
}
