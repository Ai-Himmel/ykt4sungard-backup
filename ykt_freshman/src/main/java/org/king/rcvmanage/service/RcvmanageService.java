/**
 * 
 */
package org.king.rcvmanage.service;

import java.util.List;

import org.king.framework.service.Service;
import org.king.rcvmanage.domain.Stuarriveinfo;

/**
 * @author jackey
 *
 */
public interface RcvmanageService extends Service {

	public void save(Stuarriveinfo stuarriveinfo);
	
	public void update(Stuarriveinfo stuarriveinfo);
	
	public void delete(Stuarriveinfo stuarriveinfo);
	
	public List find(String query);
	
	public Stuarriveinfo findbyId(String id);
	
	public List getList();
	
	public String checkTimeUp(String menuid);
}
