
import javafx.util.Pair;
/**
 *
 * @author cengo
 * @param <T>
 */
public class  GTUSet< T > implements GTUSetInt< T >{
        
    public GTUSet() {
        size=0;
        max_size=1000;
        arr= (T[])new Object[max_size];
    }

    /**
     * return element of at i. location of array.
     * @param i
     * @return
     */
    public T getItem(int i){ return arr[i];}
    
    /**
     * assigns value to  at desired index in collection.
     * @param index
     * @param value
     */
    public void setİtem(int index, T value) { arr[index]=value;}
    public GTUIterator < T >  it;

    /**
     * return true if collections has no elements.
     * Otherwise return false.
     * @return
     */
    @Override
    public boolean empty() {return (0==size());}

    /** 
     * function return number of elemement in collection.
     * @return
     */
    @Override
    public int size() { return size;}

    /**
     * function return maximum capasity of collection.
     * @return
     */
    @Override
    public int max_size() {return max_size;}
    
    /**
     * if value match with any elements in collections
     * it returns 1,if not returns 0.
     * @param value
     * @return
     */
    @Override
    public int count(final T value) {
        for (int i = 0; i < size(); i++) {
            if (value.equals(arr[i])) return 1;
        }
        return 0;
    }

    /**
     * clear all data in collection
     * and make size is zero.
     */
    @Override
    public void clear() {
        size=0;
    }
    
    @Override
    public GTUIterator < T > end() {
        it = new GTUIterator < T >(arr,size());
        it.setİndex(size());
        return it;
    }

    @Override
    public GTUIterator<T> begin() {
       it = new GTUIterator < T >(arr,size());
       it.setİndex(0);
       return it;
    }

    /**
     *
     * @param value
     * @return
     */
    @Override
    public GTUIterator < T > find(final T value) {
        for (int i = 0; i < size(); ++i) {
            if(value==arr[i]){
               GTUIterator < T > temp = new GTUIterator<>(arr, size);
               temp.setMembers(arr, size, i);
               return temp;
            }
        }
        return end();
    }

    @Override
    public int erase(final T value) {
        for (int i = 0; i < size(); i++) {
             
            if (value.equals(getItem(i)) && i==0) {
                
                T[] temp =(T[]) new Object[size()-1];
                for (int j=0; j< size()-1; ++j){
                    temp[j]=getItem(j+1);
                }
                --size;
                for (int j=0; j < size(); ++j) 
                     arr[j]=temp[j];
                 return 1;
            }
            if (i==size()-1 && value.equals(getItem(i))) {
                --size;
                return 1;
            }
            if (value.equals(getItem(i))) {
                 T[] temp =(T[]) new Object[size()-i];
                 for (int k=i+1,l=0; k < size(); ++k,++l){
                     temp[l]=arr[k];
                 }
                 
                 for (int m=i,l=0; m < size(); ++m,++l) {
                 
                     arr[m]=temp[l];
                 }
                 --size;
                 return 1;
                 
            }
           
        }
       return 0;
    }

    @Override
    public Pair<GTUIterator<T>, T> insert(final T value) {
        if (0==size()) {
         setİtem(0, value);
         ++size;
             it = new GTUIterator < T >(arr,size());
             //System.out.println(value);
             return (new Pair(it,value));
        }
        for (int i=0; i<size(); ++i) {
            
            if ((getItem(i).equals(value))){
                  throw new UnsupportedOperationException("Element exist already.");                 
            }          
          }
        setİtem(size, value);
         ++size;
        it = new GTUIterator < T >(arr,size());
        return (new Pair(it,value)); 
    }

    /**
     *
     * @param other
     * @return
     */
    @Override
    public GTUSetInt<T> intersection(GTUSetInt<T> other) {
        
        GTUSet < T > temp = new GTUSet < >();
        GTUIterator < T > iterator1 = new GTUIterator<>();
        GTUIterator < T > iterator2 = new GTUIterator<>();
        
        for (iterator1 = begin(); iterator1.hasNext(); iterator1.next()) {
        
            for (iterator2 = other.begin(); iterator2.hasNext(); iterator2.next()) {
            
                if (iterator1.getCurrentItem().equals(iterator2.getCurrentItem())) {
                
                    temp.setİtem(temp.size, iterator1.getCurrentItem());
                    ++(temp.size);
                }
            }
        
        }
               
        return temp;
        
    }
    protected int size;
    private final int max_size;
    protected  T [] arr;
}
