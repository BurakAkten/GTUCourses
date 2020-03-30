
import java.util.NavigableMap;


public class Main
{
    public static void main(String args[]){

       try {
           final Boolean q1 = Q1Test();
           final Boolean q2 = Q2Test();
           if (q1 == q2 == Boolean.TRUE) {
               System.out.println("Your tests is done. Make sure that you test all methods of class!! ");
               return;
           }
       }catch (Exception e){
           System.err.println("An Exception is caught : " + e);
           System.exit(1);
       }
    }
    public static Boolean Q1Test(){


        System.out.println("***************************Q1 TESTING************************");
        NavigableMap<String,String> turkey = new BinaryNavMap<String,String>();
        turkey.put("uskudar","istanbul");
        turkey.put("kadıkoy","istanbul");
        turkey.put("cekirge","bursa");
        turkey.put("gebze","kocaeli");
        turkey.put("niksar","tokat");
        turkey.put("kecıoren","ankara");
        turkey.put("aksaray","istanbul");
        turkey.put("foca","izmir");
        turkey.put("manavgat","antalya");
        turkey.put("kahta","adıyaman");
        turkey.put("biga","canakkale");

        System.out.println("The original set odds is \n" + turkey);
        NavigableMap<String,String> m = turkey.subMap("uskudar",true,"gebze",false);
        System.out.println("The ordered set m is \n" + m);
        System.out.println("Entry Set : \n" + turkey.entrySet() + "\n");
        System.out.println("The first entry is " +turkey.firstEntry() + "The first key " + turkey.firstKey());
        System.out.println("The last entry is " +turkey.lastEntry() + "The last key "+turkey.lastKey());
        System.out.println("The lower entry of uskudar :" +turkey.lowerEntry("uskudar"));
        System.out.println( "Lower key of uskudar :" + turkey.lowerKey("uskudar"));
        System.out.println("The Floor entry of kahta :" +turkey.floorEntry("kahta"));
        System.out.println( "Floor key of kahta :" + turkey.floorKey("kahta"));
        System.out.println("The higher key of kahta :" +turkey.higherKey("kahta") );
        System.out.println( "HigherKey  of kahta:" + turkey.higherKey("kahta"));
        System.out.println("The CeilingKey key of kahta :" +turkey.ceilingKey("uskudar") );
        System.out.println( "CeilingKey  of kahta :" + turkey.ceilingKey("uskudar"));
        System.out.println("pollFirstEntry() returned : " + turkey.pollFirstEntry());
        System.out.println("pollLastEntry() returned : " + turkey.pollLastEntry());
        System.out.println("The navigableKeySet of the object : \n" + turkey.navigableKeySet());
        System.out.println("The descendingMap of the object : \n" + turkey.descendingMap());
        System.out.println("The descendingKeySet of the object : \n" + turkey.descendingKeySet());
        /*diger fonksiyonlar (headMap , tailMAp ,  ...) içersinde subMap kullandığımdan burada onları tekrardan çağırmadım*/


        return Boolean.TRUE;

    }
    public static Boolean Q2Test(){
        System.out.println("***************************Q2 TESTING************************");

        HashMap<String,String> turkey=new HashTableChaining<String,String>();

        System.out.println("The hashmap is empty? : " + turkey.isEmpty());

        turkey.put("edremit","balikesir");
        turkey.put("edremit","van");
        turkey.put("kemalpasa","bursa");
        turkey.put("kemalpasa","izmir");
        turkey.put("ortakoy","istanbul");//we assume a district
        turkey.put("ortakoy","aksaray");
        turkey.put("ortakoy","corum");
        turkey.put("kecıoren","ankara");
        turkey.put("pinarbasi","kastamonu");
        turkey.put("pinarbasi","kayseri");
        turkey.put("eregli","konya");
        turkey.put("eregli","tekirdag");
        turkey.put("eregli","zonguldak");
        turkey.put("golbasi","adıyaman");
        turkey.put("golbasi","ankara");
        turkey.put("biga","canakkale");


        System.out.println("The original set odds is \n" + turkey);
        System.out.println("The hashmap is empty? : " + turkey.isEmpty());
        System.out.println("The size of hashmap : " + turkey.size());
        System.out.println("The value of golbasi : " + turkey.get("golbasi"));
        System.out.println("The value of remove(biga) : " + turkey.remove("biga"));
        System.out.println("The value of remove(golbasi) : " + turkey.remove("golbasi"));
        System.out.println("The size of hashmap : " + turkey.size());
        //System.out.println("The value of biga : " + turkey.get("biga"));
        //System.out.println("The original set odds is \n" + turkey);


        return Boolean.TRUE;
    }


}
