/*
 * Created on 2003-10-15
 */

import java.util.Iterator;
import java.util.List;

import com.wiscom.is.*;

/**
 * @author tzxu
 *
 */
public class GetUserAttribute {
	public static void main(String[] args) throws Exception{
		IdentityFactory factory = IdentityFactory.createFactory( args[0] );
		
		IdentityManager manager = factory.getIdentityManager();
		
		String id = "amAdmin";
		String attrName = "cn";
		
		if ( manager.isUserExist( id ))
		{
			String[] attrs = manager.getUserAttribute( id, "cn");
			for ( int i=0; i<attrs.length; i++)
			{
				System.out.println( attrName + "=" + attrs[i]);
			}
		}else
		{
			System.out.println( "用户 " + id + " 不存在");		
		}
		List allGroups = manager.getGroups();
		
		for ( Iterator i = allGroups.iterator(); i.hasNext();)
		{
			Group g = (Group)i.next();
			System.out.println( g );	
		}
		
	}
}
