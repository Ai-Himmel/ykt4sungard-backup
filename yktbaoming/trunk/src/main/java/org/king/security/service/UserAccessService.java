/**
 * 
 */
package org.king.security.service;

import java.util.List;

import org.king.business.domain.BmAccessInfo;
import org.king.framework.service.Service;
import org.king.security.domain.FirstpageAccess;
import org.king.security.domain.MainpageAccess;

/**
 * @author jackey
 *
 */
public interface UserAccessService extends Service{
	
	public void saveFirst(FirstpageAccess firstpageAccess);
	
	public void saveMain(MainpageAccess mainpageAccess);
	
	public List findFirst(String query);
	
	public List findMain(String query);
	
	public void saveAccess(BmAccessInfo bmAccessInfo);

}
