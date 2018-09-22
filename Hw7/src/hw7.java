import javafx.util.Pair;
import java.security.InvalidParameterException;

public class hw7 {
    public static void main(String[] args) {
    
    GTUSet <Integer>  Set = new GTUSet <>(); 
    GTUSet <Integer> temp = new GTUSet <>();
    GTUSet  Set1 = new GTUSet ();
    GTUMap <Integer,Double>Map = new GTUMap ();
    GTUMap <Integer,Double> Map1 = new GTUMap ();
    GTUIterator <Pair <Integer,Double>> MapIteraror = new GTUIterator <>();
    GTUIterator <Integer> SetIteraror = new GTUIterator <>();
    try {
        Map.insert(new Pair(2,-93.7));
        Map.insert(new Pair(8,11.0));
        Map.insert(new Pair(-63,47.5));
        Map.insert(new Pair(9,-5.1));
        Map.insert(new Pair(7,5.5));
        Map.insert(new Pair(3,6.6));
        Map1.insert(new Pair(2,-93.9));
        Map1.insert(new Pair(8,10));
        Map1.insert(new Pair(-63,47.5));
        Map1.insert(new Pair(9,0.0));
        Map1.insert(new Pair(7,5.2));
        Map1.insert(new Pair(3,6.6));
        Set1.insert(10);
        Set1.insert(0);
        Set1.insert(13);
        Set1.insert(40);
        Set1.insert(12);
        Set1.insert(60);
        Set.insert(10);
        Set.insert(13);
        Set.insert(21);
        Set.insert(12);
        Set.insert(60);
    }
    
    catch(InvalidParameterException except) {
        System.out.printf("Exception handled  %s", except.getMessage());
        System.exit(8);
    }
    System.out.println("insert 10,13,21,12,60 to Set :\n");
    SetIteraror=Set.begin();
    while (SetIteraror.hasNext()) {
         System.out.println(SetIteraror.getCurrentItem());
          SetIteraror.next();
    }
    System.out.println("\n\n");
    System.out.println("insert (2,-93.7),(8,11.0),(-63,47.5),(9,-5.1),(7,5.5),(3,6.6) to Map :\n");
    MapIteraror = Map.end();
    while (MapIteraror.hasPrevious()) {
         MapIteraror.previous(); 
        System.out.printf("Key --> %s ,Value --> : %s\n", MapIteraror.getCurrentItem().getKey(),
                MapIteraror.getCurrentItem().getValue());
        
    }
    System.out.println("at(9) in Map");
    System.out.printf("Value ---> %f",Map.at((Integer)(new Pair(9,-5.1)).getKey()));
    System.out.println("\n\n");
    SetIteraror=Set.find(13);
    System.out.println("Find 13 in Set:\n");
    while (SetIteraror.hasNext()) {
         System.out.println(SetIteraror.getCurrentItem());
          SetIteraror.next();
    }
//    System.out.println("\n\n");
//    System.out.println("find((9,-5.1)) in Map:");
//    MapIteraror=Map.find(new Pair(9,-5.1));
//    while (MapIteraror.hasNext()) {
// 
//        System.out.printf("Key --> %s ,Value --> : %s\n", MapIteraror.getCurrentItem().getKey(), // sıkıntı var.
//                MapIteraror.getCurrentItem().getValue());
//          MapIteraror.next(); 
//    }
      System.out.println("\n\n");
      System.out.println("count 20 in Set:");
      System.out.println(Set.count(21));
      System.out.println("\n\n");
      System.out.println("count Pair(7,5.5) in Map:");
      System.out.println(Map.count(new Pair(7,5.5)));
      System.out.println("\n\n");
      System.out.println("Set is empty() ?:");
      System.out.println(Set.empty());
      System.out.println("\n\n");
      System.out.println("Map is empty() ?:");
      System.out.println("\n\n");
      System.out.println(Map.empty());
      System.out.println("\n\n");
      System.out.println("Size of Set:");
      System.out.println(Set.size());
      System.out.println("\n\n");
      System.out.println("Size of Map:");
      System.out.println(Map.size());
      System.out.println("\n\n");
      System.out.println("max size of Set:");
      System.out.println(Set.max_size());
      System.out.println("\n\n");
      System.out.println("max size of Map:");
      System.out.println(Map.max_size());

    System.out.println("\n\n");
    temp=(GTUSet) Set.intersection(Set1);
    System.out.println("Intersection of Set1 and Set2:");
    SetIteraror = temp.begin();
    System.out.println("\n\n");
    while (SetIteraror.hasNext()) {
         System.out.println(SetIteraror.getCurrentItem());
          SetIteraror.next();
    }
    System.out.println("\n\n");
    Map1 = (GTUMap) Map.intersection(Map1);
    MapIteraror = Map1.end();
    System.out.println("Intersection of Map1 and Map2:");
    while (MapIteraror.hasPrevious()) {
         MapIteraror.previous(); 
        System.out.printf("Key --> %s ,Value --> : %s\n", MapIteraror.getCurrentItem().getKey(),
                MapIteraror.getCurrentItem().getValue());
        
        
    }
          System.out.println("\n\n");
      Set.erase(10);
      Set.erase(13);
      Set.erase(60);
      System.out.println("Set elements:10,13,21,12,60:\n");
      System.out.println("erase 10,13,60:\n");
      SetIteraror=Set.begin();
      while (SetIteraror.hasNext()) {
         System.out.println(SetIteraror.getCurrentItem());
          SetIteraror.next();
      }
    System.out.println("\n\n");
    System.out.println("insert (2,-93.7),(8,11.0),(-63,47.5),(9,-5.1),(7,5.5),(3,6.6) to Map :\n");
    System.out.println("erase (2,-93.7),(-63,47.5),(3,6.6) to Map :\n");
    Map.erase(new Pair(2,-93.7));
    Map.erase(new Pair(-63,47.5));
    Map.erase(new Pair(3,6.6));
    MapIteraror = Map.end();
    while (MapIteraror.hasPrevious()) {
         MapIteraror.previous(); 
        System.out.printf("Key --> %s ,Value --> : %s\n", MapIteraror.getCurrentItem().getKey(),
                MapIteraror.getCurrentItem().getValue());
        
        
    }
    System.out.println("\n\n");
    System.out.println("Clear all set elements:");
    Set.clear();
    SetIteraror = Set.begin();
    while (SetIteraror.hasNext()) {
         System.out.println(SetIteraror.getCurrentItem());
          SetIteraror.next();
    }
    System.out.println("\n\n");
    System.out.println("Clear all Map elements:");
    Map.clear();
    MapIteraror = Map.begin();
    while (MapIteraror.hasPrevious()) {
         MapIteraror.previous(); 
        System.out.printf("Key --> %s ,Value --> : %s\n", MapIteraror.getCurrentItem().getKey(),
                MapIteraror.getCurrentItem().getValue());   
    }
      System.out.println("\n\n");
      System.out.println("Set is empty() ?:");
      System.out.println(Set.empty());
      System.out.println("\n\n");
      System.out.println("Map is empty() ?:");
      System.out.println("\n\n");
      System.out.println(Map.empty());  
    }
}
