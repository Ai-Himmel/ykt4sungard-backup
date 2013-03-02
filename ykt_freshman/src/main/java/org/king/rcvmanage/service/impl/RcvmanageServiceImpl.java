/**
 * 
 */
package org.king.rcvmanage.service.impl;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.List;

import org.king.classmanage.domain.MenuTime;
import org.king.framework.exception.BusinessException;
import org.king.framework.service.impl.BaseService;
import org.king.framework.util.MyUtils;
import org.king.rcvmanage.dao.StuarriveinfoDAO;
import org.king.rcvmanage.domain.Stuarriveinfo;
import org.king.rcvmanage.service.RcvmanageService;
import org.king.security.domain.Account;
import org.king.utils.DateUtil;

/**
 * @author jackey
 *
 */
public class RcvmanageServiceImpl extends BaseService implements RcvmanageService{

    private StuarriveinfoDAO stuarriveinfoDAO;
	
	public void setStuarriveinfoDAO(StuarriveinfoDAO stuarriveinfoDAO) {
		this.stuarriveinfoDAO = stuarriveinfoDAO;
	}
	
    public void save(Stuarriveinfo stuarriveinfo){
		
		try{
			stuarriveinfoDAO.save(stuarriveinfo);
			System.out.println("add ok");
		}catch(Exception e){
			e.printStackTrace();
			System.out.println("add error");
		}
		
	}
    
    public void update(Stuarriveinfo stuarriveinfo){
		try{
			System.out.println("serviceimpl");
			stuarriveinfoDAO.update(stuarriveinfo);
			System.out.println("update ok");
		}catch(Exception e){
			e.printStackTrace();
			System.out.println("serviceimpl update error");
		}
	}
	
	public void delete(Stuarriveinfo stuarriveinfo){
		try{
			System.out.println("serviceimpl");
			stuarriveinfoDAO.delete(stuarriveinfo);
			System.out.println("delete ok");
		}catch(Exception e){
			e.printStackTrace();
			System.out.println("serviceimpl delete error");
		}
	}
    
    public List find(String query){
		List result=null;
		try{
			result=stuarriveinfoDAO.find(query);
			//System.out.println("find ok");
		}catch(Exception e){
			e.printStackTrace();
			System.out.println("find error");
		}
		if(result==null)
			System.out.println("findresult is null");
		return result;
	}
    
    public Stuarriveinfo findbyId(String id){
    	
	    Stuarriveinfo stuarriveinfo = null;
	    try{
	         stuarriveinfo = stuarriveinfoDAO.findbyId(id);
	         return stuarriveinfo;
	    }catch(Exception e){
			e.printStackTrace();
			System.out.println("find by id error");
		}
		if(stuarriveinfo==null)
			System.out.println("stuarriveinfo is null");
		return stuarriveinfo;
}
	
	public List getList(){
		List stuarriveinfoList = new ArrayList();

		try{
			stuarriveinfoList = stuarriveinfoDAO.getAll();
		
		}catch(Exception e){
			e.printStackTrace();
			System.out.println("list error");
		}
		if(stuarriveinfoList==null)
			System.out.println("stuarriveinfoList is null");
		return stuarriveinfoList;
				
	}
	
	public String checkTimeUp(String menuid){
		boolean flag=false;
		String begindate="";
    	String begintime="00:00:00";
    	String enddate="";
    	String endtime="00:00:00";
		List menutimeList=find(" select a from MenuTime a where a.menuId='"+menuid+"'");
        if(menutimeList!=null&&menutimeList.size()>0){
        	
        	MenuTime menuTime=(MenuTime)menutimeList.get(0);	        	
        	
        	String curdate=DateUtil.getNow("yyyy-MM-dd HH:mm:ss");
        	
        	SimpleDateFormat sdfdate=new SimpleDateFormat("yyyy-MM-dd");
        	SimpleDateFormat sdftime=new SimpleDateFormat("HH:mm:ss");
        	
        	if(menuTime.getBeginDate()!=null){
        		begindate=sdfdate.format(menuTime.getBeginDate());
        		if(menuTime.getBeginTime()!=null){
	        		begintime=sdftime.format(menuTime.getBeginTime());
	        	}
        		begindate=begindate+" "+begintime;
        	}
        	
        	if(menuTime.getEndDate()!=null){
        		enddate=sdfdate.format(menuTime.getEndDate());
        		if(menuTime.getEndTime()!=null){
	        		endtime=sdftime.format(menuTime.getEndTime());
	        	}
        		enddate=enddate+" "+endtime;
        	}
        	
        	if(!begindate.equals("")&&!enddate.equals("")){
        		if(curdate.compareTo(begindate)>0&&curdate.compareTo(enddate)<0)
        			flag=true;
        	}
        	else if(!begindate.equals("")&&enddate.equals("")){//只设前期限
        		if(curdate.compareTo(begindate)>0)
        			flag=true;
        	}
        	else if(begindate.equals("")&&!enddate.equals("")){//只设后期限
        		if(curdate.compareTo(enddate)<0)
        			flag=true;
        	}
        	else
        		flag=true;
        	        	
        }
        else
        	flag=true;
        
        String timespan="";        
        	
		if(!flag){
		    if(!begindate.equals("")){
		    	if(begindate.length()>18)
		    		begindate=begindate.substring(0,begindate.length()-3);
		    	timespan=timespan+begindate;
		    }
		    else
		    	timespan=timespan+"---";
		    timespan=timespan+" 到 ";
		    if(!enddate.equals("")){
		    	if(enddate.length()>18)
		    		enddate=enddate.substring(0,enddate.length()-3);
		    	timespan=timespan+enddate;
		    }
		    else
		    	timespan=timespan+"---";
		    
		    return timespan;	
		}
		else
			return "";
	}

}
