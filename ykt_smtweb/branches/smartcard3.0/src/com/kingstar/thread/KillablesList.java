package com.kingstar.thread;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;

//threads manager
public class KillablesList
{
	//线程管理器
   public static HashMap threadlist = new HashMap();
    
    private static String clearedName = null;
    
   
    //kill thread operation 
	public static void kill(String name)
    {
        ArrayList list = new ArrayList();
        list.addAll(threadlist.keySet());
        
        Iterator iter = list.iterator();
        while (iter.hasNext())
        {
            Object obj = iter.next();
           
            if (name.equalsIgnoreCase((String)(threadlist.get(obj))))
            {
                if (obj instanceof Killable)
                {                    
                       ((Killable)obj).kill();
                    System.out.println("killed");                 
                }
                threadlist.remove(obj);
            }
        }
    }
    
    public static void setEngineName(String name)
    {       
    	threadlist.put(Thread.currentThread(),name);   
    }
    
    //add operation
    public static void add (Object obj)
    {
        String name = (String)threadlist.get(Thread.currentThread());
        if (name != null)  
        	threadlist.put(obj, name);
    }
    
    public static void remove (Object obj)
    {       
    	threadlist.remove(obj);
    }
    
    public static void remove ()
    {       
    	threadlist.remove(Thread.currentThread());
    }
    
    public static void clear()
    {
        if (clearedName != null)
        {
           
            throw new RuntimeException("nested clear action not allowed");
        }
        clearedName = (String)threadlist.get(Thread.currentThread());
       System.out.println("clearedName=" + clearedName);
        remove();
    }
    
    public static void restore()
    {
        if (clearedName != null)
        {
            setEngineName(clearedName);
            clearedName = null;
        }
    }
   
}