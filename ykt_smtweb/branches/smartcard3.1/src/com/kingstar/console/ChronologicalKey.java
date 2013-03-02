package com.kingstar.console;

//²úÉúÎ¨Ò»ºÅ
public class ChronologicalKey
{
    private static final long KEY_MULTIPLIER = 1000L;
    
    private static long key        = -1;
    private static long prevMillis = -1;
    
    static
    {
        // Must initialize key and prevMillis...
    	next();
    }
    
    public static synchronized long next()
    {
        long currentMillis = System.currentTimeMillis();
        if (prevMillis == currentMillis)
            return (++key);
        else
        {
            prevMillis = currentMillis;
            key = millisToKey(currentMillis);
            return key;
        }
    }
    
    public static long millisToKey(long timeMillis)
    {
        return timeMillis * KEY_MULTIPLIER;
    }
    
    public static long keyToMillis(long timeMillis)
    {
        return timeMillis / KEY_MULTIPLIER;
    }
    
    public static long maxKey()
    {
        return Long.MAX_VALUE;
    }
    
    public static long nowKey()
    {
        long currentMillis = System.currentTimeMillis();
        return (prevMillis == currentMillis) ? key : millisToKey(currentMillis);
    }
    public static void main(String args[]){
   	System.out.println(ChronologicalKey.maxKey());
//    	
//    	System.out.println(System.currentTimeMillis());
   	System.out.println(ChronologicalKey.nowKey());
    	System.out.println(ChronologicalKey.next());
    	System.out.println(ChronologicalKey.next());
    	
    	System.out.println(ChronologicalKey.next());
    	System.out.println(ChronologicalKey.next());
    	
    }
}