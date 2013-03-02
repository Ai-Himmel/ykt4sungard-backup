package org.king.check.service.impl;

import java.util.List;
import java.util.Map;

import org.king.check.dao.TimeDAO;
import org.king.check.domain.TTime;
import org.king.check.service.TimeService;

public class TimeSereviceImpl implements TimeService{
	
	private TimeDAO timeDAO;

	public void setTimeDAO(TimeDAO timeDAO) {
		this.timeDAO = timeDAO;
	}
	
	public void deleClassTime(TTime time) throws Exception {
		timeDAO.deleClassTime(time);
		
	}

    public List findAllTimes(){
        String hql = "from TTime";
        return timeDAO.findClassTimes(hql);
    }

	public List findClassTimes() throws Exception {
		StringBuffer   query = new StringBuffer(" select  new Map( t.classNum as classNum ,t.beginTime as beginTime ")
		               .append(",t.endTime as endTime )from TTime t  ");
		List list = timeDAO.findClassTimes(query.toString());
		return list;
	}
	
	/*public  boolean  findErrorTimes(String begindate ,String enddate)  throws Exception {
		         StringBuffer   query = new StringBuffer(" from TTime  t where t t.endTime >='").append(begindate).append("'");
		            query.append(" and  t.beginTime <='").append(enddate).append("'");
		         List times =  timeDAO.findClassTimes(query.toString());
		        if(times !=null &&times.size()>0){
		        	return true;
		        }else{
		        	return false;
		        }       
		               
	}*/

	public void saveClassTimes(TTime time) throws Exception {
		timeDAO.saveClassTimes(time);
		
	}

	public void updateClassTime(TTime time) throws Exception {
		timeDAO.updateClassTime(time);
		
	}

	public TTime getTime(Integer classNum) throws Exception {
		StringBuffer   query = new StringBuffer(" from TTime t where t.classNum=").append(classNum);
        List list = timeDAO.findClassTimes(query.toString());
        if(list!=null && !list.isEmpty()){
        	return (TTime)list.get(0);
        }else{
        	return null;
        }
          
	
	}

	public Map getTimeByClass(String ClassNum)
			throws Exception {
		StringBuffer query = new StringBuffer("");
		   	query.append(" select new Map ( t.beginTime as beginTime , t.endTime as endTime ) from  TTime t ")
		   	.append(" where t.classNum ='").append(ClassNum).append("'");
		List list = timeDAO.findClassTimes(query.toString());
	    if(list !=null && list.size()>0){
	    	return (Map)list.get(0);
	    }    
		return null;
	}
}
