package com.kingstar.files;

import java.io.*;
import java.util.*;

//读取参数可取不同类型的，如读INT,BOOLENA,LONG等类型
public class Parameters extends Properties
{

	private static final long serialVersionUID = -413749769910222090L;
	private HashMap randomAccessFiles = new HashMap(); //#1
    private String fileName = null;
    

    public Parameters( Properties props )
    {      
        Enumeration fullList = props.propertyNames();
       
        String propertyName;
         
        while ( fullList.hasMoreElements() )
        {           
            propertyName = (String) fullList.nextElement();     
            this.setProperty( propertyName, props.getProperty( propertyName ));            
        }
    }
//    public String getSubSet( String key, int index )
//    {
//        return this.getProperty( key + "["+ index +"]" );
//    }
//
//    public void setSub(String key, int index, String value )
//    {
//        this.setProperty( key + "[" + index + "]", value );
//    }


    public Parameters()
    {
        super();
    }

    public Parameters(String fileName)
    {
        this();
        this.fileName = fileName;
    }

    public void setFileName(String fileName)
    {
        this.fileName = fileName;
    }
    
    public String getFileName()
    {
        return fileName;
    }

    public void load(String fileName)
    throws IOException
    {
    	FileInputStream f=new FileInputStream(fileName);
        load(f);
        this.fileName = fileName;
        f.close();
    }

    public void load()
    throws IOException
    {
        load(this.fileName);
    }

    public void saveAs(String fileName) //#1
    throws IOException
    {
        StringWriter sw = new StringWriter();
        PrintWriter out = new PrintWriter(sw);
        out.print("#");
        list(out);
        String content = sw.toString();
        out.close();//#2
        RandomAccessFile raf = null;
        
        synchronized (randomAccessFiles)
        {
            raf = (RandomAccessFile)randomAccessFiles.get(fileName);
            if (raf == null)
            {
                raf = new RandomAccessFile(fileName, "rw");
                randomAccessFiles.put(fileName, raf);
            }
        }
        
        synchronized (raf)
        {
            raf.setLength(0);//#3
            raf.writeBytes(content);
        }
    }


    public void save(String fileName)
    throws IOException
    {
        saveAs( fileName );        
        this.fileName = fileName;
    }

    public void save()
    throws IOException
    {
        save(fileName);
    }


    public void setPropertyBool( String propName, boolean value )
    {
        if ( value )
            put( propName, "YES" );
        else
            put( propName, "NO"  );
    }

    public boolean getPropertyBool( String propName, boolean def )
    {
        String temp = getProperty( propName );
        
        if (temp != null)
        {
            temp = temp.toLowerCase().trim();
        
            if ( temp.equals("y")  || temp.equals("yes") || temp.equals("true"))
                    return true;
            
            if ( temp.equals("n")  || temp.equals("no") || temp.equals("false"))
                    return false;
        }
        
        return def;
    }

    //get boolean value 
    public boolean getPropertyBool( String propName )
    {
        return getPropertyBool( propName, false );
    }
      
    public void setPropertyL( String key, long value )
    {                
        put(key, String.valueOf(value));
    }
    //get long value           
    public long getPropertyL( String key, long defaultValue )
    {
        String value = getProperty(key);
        try
        {
            return (value == null) ? defaultValue : Long.parseLong(value.trim());
        }
        catch (NumberFormatException e)
        {
            throw new NumberFormatException("The value of " + key + 
                " is not numeric. " + e);
        }
    }
    //get int value
    public int getPropertyI(String key)
    {
        try
        {
            return Integer.valueOf(getProperty(key).trim()).intValue();
        }
        catch (NullPointerException npe)
        {
            throw new NullPointerException(key + 
                " does not exist in setup. " + npe);
        }
        catch (NumberFormatException nfe)
        {
            throw new NumberFormatException("The value of " + key + 
                " is not numeric in setup. " + nfe);
        }
    }
    
    //get int value
    public int getPropertyI(String key, int defaultValue)
    {
        String value = getProperty(key);
        try
        {
            return (value == null) ? defaultValue : Integer.parseInt(value.trim());
        }
        catch (NullPointerException npe)
        {
            throw new NullPointerException(key + 
                " does not exist in setup. " + npe);
        }
        catch (NumberFormatException nfe)
        {
            throw new NumberFormatException("The value of " + key + 
                " is not numeric in setup. " + nfe);
        }
    }
    
    public Object put(String key, int value)
    {
        return put(key,String.valueOf(value));
    }
    public static void main(String[] args) throws Exception{
    	
    	Parameters p=new Parameters();
     	p.load("console.ini");
    	p.put("test","test");
    	p.setFileName("standby_console.ini");
     	p.save();

    }
}