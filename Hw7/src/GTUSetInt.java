
import javafx.util.Pair;
/**
 *
 * @author cengo
 * @param <T>
 */
public interface GTUSetInt < T > {
    boolean empty();
    int size();
    int max_size();
    int count(final T value);
    void clear();
    GTUIterator< T > end();
    GTUIterator< T > begin();
    GTUIterator< T > find(final T value);
    int erase(final T value);
    Pair < GTUIterator < T >,T >  insert(final T value);
    GTUSetInt < T > intersection(GTUSetInt < T > other);
}
