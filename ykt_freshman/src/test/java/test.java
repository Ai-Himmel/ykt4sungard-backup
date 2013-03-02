	/**
	 *
	 * @author Zenny Chen
	 */

	class Parent
	{
	    protected int t;
	    
	    public Parent()
	    {
	        System.out.println("Creating Parent...");
	        create();
	    }
	    
	    public void create()
	    {
	        System.out.println("Parent created!");
	        
	        t = 1;
	    }
	}

	class Child extends Parent
	{
	    private int c;
	    
	    public void create()
	    {
	        c = 1;
	        System.out.println("Child created!");
	    }
	    
	    public Child()
	    {
	        System.out.println("Creating Child...");
	        create();
	    }
	    
	    public int getValue()
	    {
	        return c + t;
	    }
	}
public class test {
	

	/**
	 * Description: TODO
	 *@param args
	 * @return void
	 * Modify History: 2006-8-21 jackey create
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		 
        Child ch = new Child();
        
        System.out.println("The result is: "+ch.getValue());

	}

}


