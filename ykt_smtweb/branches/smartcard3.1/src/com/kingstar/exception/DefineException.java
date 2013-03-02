package com.kingstar.exception;


public class DefineException extends Exception 
{

   public  String errMessage=""; 
   public  String errCode="";
   public  Exception rootCause=null;

	DefineException() 
    {
        super();
    }
	  
	DefineException(String msg) 
    {  
        this.errMessage=msg;
    }                        
    
	DefineException(String errcode,String msg) 
    {   this.errCode=errcode;
        this.errMessage=msg;
    }                        
  
                         

	DefineException(String msg, Exception root)
    {
        super(msg,root);
    }
	 public String toString()
	    {
	        return "[ " + errCode + " : " +
	               ((errMessage == null) ? "" : errMessage ) +
	               ((rootCause == null) ? "" : (" caused by " + rootCause)) +
	               " ]";
	    }

}