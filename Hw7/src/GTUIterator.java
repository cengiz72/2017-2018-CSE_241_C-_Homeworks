/**
 *
 * @author cengo
 * @param <T>
 */
public class GTUIterator < T > {

           
            public GTUIterator(T[] arr,int _size) {

                data=(T[])new Object[_size];
                data=arr;
                size=_size;
            }
            
    /**
     * This function return item of array that 
     * iterator indicate.
     * @return
     */
    public T getCurrentItem() {return data[current];}
            public T[] getArr() { return data;}
            public GTUIterator(){}
            public void setMembers(T[] arr,int _size,int _current) {
                data=arr;
                size=_size;
                current=_current;
            }

    /**
     * This function return item of array  
     * next one from iterator show.
     * @return
     */
    public T next() {
                ++current;
                return data[current];
            }

    /**
     * anymore iterator indicate element indexed  of array.
     * @param index
     */
    public void setİndex(int index) {current=index;}

    /**
     * function return item of array previous one from iterator indicates. 
     * @return
     */
    public T previous() {
                --current;
                return data[current];
            }
           
    /**
     * This function return true if next one from iterator indicates exist in
     * array, if not return false.
     * @return
     */
    public boolean hasNext() {
                if (current < size) return true;
                 return false;
            }

    /**
     * This function return true if previous one from iterator indicates exists 
     * in array ,if not return false.
     * @return
     */
    public boolean hasPrevious(){
                 if (current - 1 < 0) return false;
                 return true;
            }
            private  int current=0;
            private  int size;
            private  T[] data;
        }
