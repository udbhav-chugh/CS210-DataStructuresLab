How hashing works:
For insertion of a key(K) – value(V) pair into a hash map, 2 steps are required:

K is converted into a small integer (called its hash code) using a hash function.
The hash code is used to find an index (hashCode % arrSize) and the entire linked list at that index(Separate chaining) is first searched for the presence of the K already.
If found, it’s value is updated and if not, the K-V pair is stored as a new node in the list.
Complexity and Load Factor
For the first step, time taken depends on the K and the hash function.
For example, if the key is a string “abcd”, then it’s hash function may depend on the length of the string. But for very large values of n, the number of entries into the map, length of the keys is almost negligible in comparison to n so hash computation can be considered to take place in constant time, i.e, O(1).
For the second step, traversal of the list of K-V pairs present at that index needs to be done. For this, the worst case may be that all the n entries are at the same index. So, time complexity would be O(n). But, enough research has been done to make hash functions uniformly distribute the keys in the array so this almost never happens.
So, on an average, if there are n entries and b is the size of the array there would be n/b entries on each index. This value n/b is called the load factor that represents the load that is there on our map.
This Load Factor needs to be kept low, so that number of entries at one index is less and so is the complexity almost constant, i.e., O(1).
Rehashing:
As the name suggests, rehashing means hashing again. Basically, when the load factor increases to more than its pre-defined value (default value of load factor is 0.75), the complexity increases. So to overcome this, the size of the array is increased (doubled) and all the values are hashed again and stored in the new double sized array to maintain a low load factor and low complexity.

Why rehashing?
Rehashing is done because whenever key value pairs are inserted into the map, the load factor increases, which implies that the time complexity also increases as explained above. This might not give the required time complexity of O(1).

Hence, rehash must be done, increasing the size of the bucketArray so as to reduce the load factor and the time complexity.

How Rehashing is done?
Rehashing can be done as follows:

For each addition of a new entry to the map, check the load factor.
If it’s greater than its pre-defined value (or default value of 0.75 if not given), then Rehash.
For Rehash, make a new array of double the previous size and make it the new bucketarray.
Then traverse to each element in the old bucketArray and call the insert() for each so as to insert it into the new larger bucket array.
Program to implement Rehashing:
// Java program to implement Rehashing 
  
import java.util.ArrayList; 
  
class Map<K, V> { 
  
    class MapNode<K, V> { 
  
        K key; 
        V value; 
        MapNode<K, V> next; 
  
        public MapNode(K key, V value) 
        { 
            this.key = key; 
            this.value = value; 
            next = null; 
        } 
    } 
  
    // The bucket array where 
    // the nodes containing K-V pairs are stored 
    ArrayList<MapNode<K, V> > buckets; 
  
    // No. of pairs stored - n 
    int size; 
  
    // Size of the bucketArray - b 
    int numBuckets; 
  
    // Default loadFactor 
    final double DEFAULT_LOAD_FACTOR = 0.75; 
  
    public Map() 
    { 
        numBuckets = 5; 
  
        buckets = new ArrayList<>(numBuckets); 
  
        for (int i = 0; i < numBuckets; i++) { 
            // Initialising to null 
            buckets.add(null); 
        } 
        System.out.println("HashMap created"); 
        System.out.println("Number of pairs in the Map: " + size); 
        System.out.println("Size of Map: " + numBuckets); 
        System.out.println("Default Load Factor : " + DEFAULT_LOAD_FACTOR + "\n"); 
    } 
  
    private int getBucketInd(K key) 
    { 
  
        // Using the inbuilt function from the object class 
        int hashCode = key.hashCode(); 
  
        // array index = hashCode%numBuckets 
        return (hashCode % numBuckets); 
    } 
  
    public void insert(K key, V value) 
    { 
        // Getting the index at which it needs to be inserted 
        int bucketInd = getBucketInd(key); 
  
        // The first node at that index 
        MapNode<K, V> head = buckets.get(bucketInd); 
  
        // First, loop through all the nodes present at that index 
        // to check if the key already exists 
        while (head != null) { 
  
            // If already present the value is updated 
            if (head.key.equals(key)) { 
                head.value = value; 
                return; 
            } 
            head = head.next; 
        } 
  
        // new node with the K and V 
        MapNode<K, V> newElementNode = new MapNode<K, V>(key, value); 
  
        // The head node at the index 
        head = buckets.get(bucketInd); 
  
        // the new node is inserted 
        // by making it the head 
        // and it's next is the previous head 
        newElementNode.next = head; 
  
        buckets.set(bucketInd, newElementNode); 
  
        System.out.println("Pair(" + key + ", " + value + ") inserted successfully.\n"); 
  
        // Incrementing size 
        // as new K-V pair is added to the map 
        size++; 
  
        // Load factor calculated 
        double loadFactor = (1.0 * size) / numBuckets; 
  
        System.out.println("Current Load factor = " + loadFactor); 
  
        // If the load factor is > 0.75, rehashing is done 
        if (loadFactor > DEFAULT_LOAD_FACTOR) { 
            System.out.println(loadFactor + " is greater than " + DEFAULT_LOAD_FACTOR); 
            System.out.println("Therefore Rehashing will be done.\n"); 
  
            // Rehash 
            rehash(); 
  
            System.out.println("New Size of Map: " + numBuckets + "\n"); 
        } 
  
        System.out.println("Number of pairs in the Map: " + size); 
        System.out.println("Size of Map: " + numBuckets + "\n"); 
    } 
  
    private void rehash() 
    { 
  
        System.out.println("\n***Rehashing Started***\n"); 
  
        // The present bucket list is made temp 
        ArrayList<MapNode<K, V> > temp = buckets; 
  
        // New bucketList of double the old size is created 
        buckets = new ArrayList<MapNode<K, V> >(2 * numBuckets); 
  
        for (int i = 0; i < 2 * numBuckets; i++) { 
            // Initialised to null 
            buckets.add(null); 
        } 
        // Now size is made zero 
        // and we loop through all the nodes in the original bucket list(temp) 
        // and insert it into the new list 
        size = 0; 
        numBuckets *= 2; 
  
        for (int i = 0; i < temp.size(); i++) { 
  
            // head of the chain at that index 
            MapNode<K, V> head = temp.get(i); 
  
            while (head != null) { 
                K key = head.key; 
                V val = head.value; 
  
                // calling the insert function for each node in temp 
                // as the new list is now the bucketArray 
                insert(key, val); 
                head = head.next; 
            } 
        } 
  
        System.out.println("\n***Rehashing Ended***\n"); 
    } 
  
    public void printMap() 
    { 
  
        // The present bucket list is made temp 
        ArrayList<MapNode<K, V> > temp = buckets; 
  
        System.out.println("Current HashMap:"); 
        // loop through all the nodes and print them 
        for (int i = 0; i < temp.size(); i++) { 
  
            // head of the chain at that index 
            MapNode<K, V> head = temp.get(i); 
  
            while (head != null) { 
                System.out.println("key = " + head.key + ", val = " + head.value); 
  
                head = head.next; 
            } 
        } 
        System.out.println(); 
    } 
} 
  
public class GFG { 
  
    public static void main(String[] args) 
    { 
  
        // Creating the Map 
        Map<Integer, String> map = new Map<Integer, String>(); 
  
        // Inserting elements 
        map.insert(1, "Geeks"); 
        map.printMap(); 
  
        map.insert(2, "forGeeks"); 
        map.printMap(); 
  
        map.insert(3, "A"); 
        map.printMap(); 
  
        map.insert(4, "Computer"); 
        map.printMap(); 
  
        map.insert(5, "Portal"); 
        map.printMap(); 
    } 
} 