
import javafx.util.Pair;
/**
 *
 * @author cengo
 * @param <K>
 * @param <V>
 */
public class  GTUMap <K ,V> extends GTUSet < Pair < K,V > > {
   
    public GTUMap() {
        
        super();
    }

    /**
     * insert function add elements to end of array if element is
     * not present in array and return an pair.
     * @param value
     * @return
     */
    @Override
    public Pair<GTUIterator<Pair<K, V>>, Pair<K, V>> insert(Pair<K, V> value) {
        if (0==size()) {
            setİtem(0, value);
           ++size;
             return (new Pair(it,value));
        }
        for (int i=0; i<size(); ++i) {
            
            if ((getItem(i).getKey().equals(value.getKey()))){
                  throw new UnsupportedOperationException("Element exist already.");                 
            }          
          }
         setİtem(size, value);
         ++size;
        return (new Pair(it,value)); 
    }

    /**
     * function erase given value  and return 1 if it is present
     * in array,if not return 0.
     * @param value
     * @return
     */
    @Override
    public int erase( Pair <K,V> value) {
    
        for (int i = 0; i < size(); i++) {
             
            if (value.getKey().equals(getItem(i).getKey()) && i==0) {
                Pair []temp = new Pair[size()-1];
                for (int j=0; j< size()-1; ++j){
                    temp[j]=getItem(j+1);
                }
                --size;
                for (int j=0; j < size(); ++j) 
                     setİtem(j, temp[j]);
                 return 1;
            }
            if (i==size()-1 && value.equals(getItem(i))) {
                --size;
                return 1;
            }
            if (value.equals(getItem(i))) {
                 Pair []temp = new Pair[size()-1];
                 for (int k=i+1,l=0; k < size(); ++k,++l){
                     temp[l]=getItem(k);
                 }
                 
                 for (int m=i,l=0; m < size(); ++m,++l) {
                     
                     setİtem(m, temp[l]);
                 }
                 --size;
                 return 1;
                 
            }
        }
       return 0;
    }

    /**
     * This function take two maps 
     * and return new map of intersection of 
     * given maps.
     * @param other
     * @return
     */
    @Override
    public GTUSetInt< Pair<K, V> > intersection(GTUSetInt< Pair<K, V> > other) {
        
        GTUIterator <Pair <K,V> > iterator1 = new GTUIterator<>();
        GTUIterator <Pair <K,V> > iterator2 = new GTUIterator<>();
        
        GTUMap temp = new GTUMap <>();    
        for (iterator1 = begin(); iterator1.hasNext(); iterator1.next()) {
        
            for (iterator2 =other.begin(); iterator2.hasNext(); iterator2.next()) {
                   if (iterator1.getCurrentItem().getKey().equals(iterator2.getCurrentItem().getKey())
                      && iterator1.getCurrentItem().getValue().equals(iterator2.getCurrentItem().getValue())) {
                      temp.arr[(temp.size)]=iterator1.getCurrentItem();
                      ++(temp.size);
                   }
            }
        }
        return temp;
    }
    
    @Override
    public GTUIterator < Pair<K, V> > find(final Pair<K, V> value) {
        for (int i = 0; i < size(); ++i) {
            if(value.getKey().equals(getItem(i).getKey())){
               
              it.setMembers(arr, size, i);
               return it;
            }
        }
        return end();
    }

    /**
     * if k matchs to any k of elements in collection ,function return 
     * value of that elements.
     * @param k
     * @return
     */
    public V at(K k) {
        for (int i = 0; i<size(); ++i) {
            if (getItem(i).getKey()==k) return (getItem(i).getValue());
        }
        throw new UnsupportedOperationException("Value is not found");
    }

}
