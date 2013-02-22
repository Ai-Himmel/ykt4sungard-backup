package org.king.business.service.impl;

import java.sql.Types;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Date;
import java.util.List;
import java.util.Map;

import org.king.business.domain.BmStudent;
import org.king.business.domain.BmTest;
import org.king.business.service.TestService;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.utils.DateUtil;
import org.king.web.util.Constants;

public class TestServiceImpl implements TestService {
	
	private BaseDAO baseDAO;
	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}
	public BmTest getDetail(String id) {
		BmTest bmTest=null;
		List li=baseDAO.findEntity("select a from BmTest a where a.id='"+id+"'");
		if(li!=null&&li.size()>0){
			bmTest=(BmTest)li.get(0);
		}
		return bmTest;
	}
	

    public List get4Update(String id){
		
		StringBuffer sbhql=new StringBuffer("");
		List li=new ArrayList();
		
		sbhql.append(" select new Map(a.id as id,a.bmTestCat.id as testCatId,a.bmBeginDate as bmBeginDate,a.bmBeginTime as bmBeginTime,a.bmEndDate as bmEndDate,a.bmEndTime as bmEndTime,a.testDate as testDate,a.testBeginTime as testBeginTime,a.testEndTime as testEndTime,a.testMemo as testMemo,a.updator as updator,a.updateTime as updateTime )"
				+"from BmTest a where 1=1 and a.id='"+id+"'");
				
		li= baseDAO.findEntity(sbhql.toString());
		return li;
		
	}
    public List get4View(String id){
		
		StringBuffer sbhql=new StringBuffer("");
		List li=new ArrayList();
		
		sbhql.append(" select new Map(a.id as id,a.bmTestCat.testCatName as testCatName,a.bmBeginDate as bmBeginDate,a.bmBeginTime as bmBeginTime,a.bmEndDate as bmEndDate,a.bmEndTime as bmEndTime,a.testDate as testDate,a.testBeginTime as testBeginTime,a.testEndTime as testEndTime,a.testMemo as testMemo,a.updator as updator,a.updateTime as updateTime )"
				+"from BmTest a where 1=1 and a.id='"+id+"'");
				
		li= baseDAO.findEntity(sbhql.toString());
			
		if(li!=null&&li.size()>0){
			CatBmDateTime(li);
		}
		
		return li;
		
	}
    
    public List getList(Map m) {
		StringBuffer sbhql=new StringBuffer("");
		StringBuffer sWhere=new StringBuffer("");
		List li=new ArrayList();
		MyQuery mq=new MyQuery();
		
		sbhql.append(" select new Map(a.id as id,a.bmTestCat.testCatName as testCatName,a.bmBeginDate as bmBeginDate,a.bmBeginTime as bmBeginTime,a.bmEndDate as bmEndDate,a.bmEndTime as bmEndTime,a.testDate as testDate,a.testBeginTime as testBeginTime,a.testEndTime as testEndTime,a.testMemo as testMemo,a.updator as updator,b.personName as updatorName,a.updateTime as updateTime) from BmTest a,Person b where 1=1 and b.personCode=a.updator ");
		sbhql.append(" and  a.updator ='"+(String)m.get("operator")+"'");
		if(m.get("search_id")!=null&&!((String)m.get("search_id")).equals("")){
			sWhere.append(" and a.id= ? ");
			mq.addPara((String)m.get("search_id"),Types.VARCHAR);
		}
		if(m.get("search_testcatname")!=null&&!((String)m.get("search_testcatname")).equals("")){
			sWhere.append(" and a.bmTestCat.testCatName like ? ");
			mq.addPara("%"+(String)m.get("search_testcatname")+"%",Types.VARCHAR);
		}	
		if(m.get("search_afterdate")!=null&&!((String)m.get("search_afterdate")).equals("")){
			sWhere.append(" and (a.testDate is null or a.testDate='' or a.testDate> ?) ");
			mq.addPara((String)m.get("search_afterdate"),Types.VARCHAR);
		}
		if(m.get("search_beforedate")!=null&&!((String)m.get("search_beforedate")).equals("")){
			sWhere.append(" and (a.testDate is null or a.testDate='' or a.testDate< ?) ");
			mq.addPara((String)m.get("search_beforedate"),Types.VARCHAR);
		}
		
		sWhere.append(" order by a.updateTime desc ");
		mq.setQueryString(sbhql.append(sWhere).toString());
		
		li= baseDAO.findEntity(mq);
		
		if(li!=null&&li.size()>0){
			CatBmDateTime(li);
		}
		        		
		return li;
	}
	
	public List getnewaddList(Map m) {
		StringBuffer sbhql=new StringBuffer("");
		StringBuffer sWhere=new StringBuffer("");
		List li=new ArrayList();
		List oli=new ArrayList();
		MyQuery mq=new MyQuery();
		
		if(m.get("newidstring")!=null&&!((String)m.get("newidstring")).equals("")){
			
			String newids=(String)m.get("newidstring");
			
			sbhql.append(" select new Map(a.id as id,a.bmTestCat.testCatName as testCatName,a.bmBeginDate as bmBeginDate,a.bmBeginTime as bmBeginTime,a.bmEndDate as bmEndDate,a.bmEndTime as bmEndTime,a.testDate as testDate,a.testBeginTime as testBeginTime,a.testEndTime as testEndTime,a.testMemo as testMemo,a.updator as updator,b.personName as updatorName,a.updateTime as updateTime) from BmTest a,Person b where 1=1 and b.personCode=a.updator ");
			
			sWhere.append(" and  a.updator= '"+(String)m.get("operator")+"'");					
			
			sWhere.append(" and a.id='"+newids+"' ");		    		
			
			sWhere.append(" order by a.updateTime desc ");
			mq.setQueryString(sbhql.append(sWhere).toString());        
			
			li= baseDAO.findEntity(mq);
		}
		
		sbhql=new StringBuffer("");
		sWhere=new StringBuffer("");
		mq=new MyQuery();
		
		sbhql.append(" select new Map(a.id as id,a.bmTestCat.testCatName as testCatName,a.bmBeginDate as bmBeginDate,a.bmBeginTime as bmBeginTime,a.bmEndDate as bmEndDate,a.bmEndTime as bmEndTime,a.testDate as testDate,a.testBeginTime as testBeginTime,a.testEndTime as testEndTime,a.testMemo as testMemo,a.updator as updator,b.personName as updatorName,a.updateTime as updateTime) from BmTest a,Person b where 1=1 and b.personCode=a.updator ");
		
		if(m.get("newidstring")!=null&&!((String)m.get("newidstring")).equals("")){
			String newids=(String)m.get("newidstring");
			sWhere.append(" and a.id!='"+newids+"' ");			
		}		
		sWhere.append(" and  a.updator= '"+(String)m.get("operator")+"'");		
		
		sWhere.append(" order by a.updateTime desc ");
		mq.setQueryString(sbhql.append(sWhere).toString());        
		
		oli= baseDAO.findEntity(mq);
						
		if(oli!=null&&oli.size()>0){
			for(int i=0;i<oli.size();i++){
				li.add(li.size(),oli.get(i));				
			}
		}
		    
		if(li!=null&&li.size()>0){
			CatBmDateTime(li);
		}
		
		return li;
	}
	
    public boolean save(BmTest bmTest) {
				
		baseDAO.saveEntity(bmTest);
		
		return true;
	}
	public boolean update(BmTest bmTest) {
				
		baseDAO.updateEntity(bmTest);
							
		return true;
	}
	public boolean delete(BmTest bmTest) {
		
		baseDAO.removeEntity(bmTest);
	
		return true;
	}
	
	public boolean check4Save(BmTest bmTest){
		String sqlstring="select a from BmTest a " +
				" where a.bmTestCat.id='"+bmTest.getBmTestCat().getId()+"'" +
				" and a.bmBeginDate='"+bmTest.getBmBeginDate()+"'" +
				" and a.bmBeginTime='"+bmTest.getBmBeginTime()+"'" +
				" and a.bmEndDate='"+bmTest.getBmEndDate()+"'" +
				" and a.bmEndTime='"+bmTest.getBmEndTime()+"'" +
				" and a.testDate='"+bmTest.getTestDate()+"'" +
				" and a.testBeginTime='"+bmTest.getTestBeginTime()+"'" +
				" and a.testEndTime='"+bmTest.getTestEndTime()+"'";
		
		if(bmTest.getId()!=null)
			sqlstring=sqlstring+" and a.id<>'"+bmTest.getId()+"'";
		
		List testList=baseDAO.findEntity(sqlstring);
		if(testList!=null&&testList.size()>0)
			return false;
		else
			return true;
	}
	
	public String check4Delete(String id){
		String sqlstring="select new Map(a.id as id,a.bmTest.bmTestCat.testCatName as testCatName) from BmStuBm a where a.bmTest.id='"+id+"'";
				
		List testList=baseDAO.findEntity(sqlstring);
		if(testList!=null&&testList.size()>0){
			Map m=(Map)testList.get(0);
			String testcatName=(String)m.get("testCatName");
			return testcatName;
		}
		else
			return null;
	}
	
	public void changeIfName(List list){
		String[][] onoff= Constants.onoff_flag;
		for(int i=0;i<list.size();i++){
			Map m=(Map)list.get(i);			
			String stateValue=(String)m.get("ifFee");
			for(int j=0;j<onoff.length;j++){
				if(onoff[j][0].equals(stateValue)){
					m.put("ifFeeName",onoff[j][1]);
				}
			}
		}//for
		
	}
    
	public void changeStateName(List list){
		String[][] mczt= Constants.mczt;
		for(int i=0;i<list.size();i++){
			Map m=(Map)list.get(i);			
			String stateValue=(String)m.get("state");
			for(int j=0;j<mczt.length;j++){
				if(mczt[j][0].equals(stateValue)){
					m.put("stateName",mczt[j][1]);
				}
			}
		}//for
		
	}
	
	public void CatBmDateTime(List list){
		for(int i=0;i<list.size();i++){
			Map m=(Map)list.get(i);			
			String bmbegindate="";
			String bmbegintime="";
			String bmenddate="";
			String bmendtime="";
			String bmbegin="";
			String bmend="";
			if(m.get("bmBeginDate")!=null){
				bmbegindate=(String)m.get("bmBeginDate");
				bmbegin=bmbegindate;
				if(m.get("bmBeginTime")!=null){
					bmbegintime=(String)m.get("bmBeginTime");
					bmbegin=bmbegin+" "+bmbegintime;
				}					
			}
			if(m.get("bmEndDate")!=null){
				bmenddate=(String)m.get("bmEndDate");
				bmend=bmenddate;
				if(m.get("bmEndTime")!=null){
					bmendtime=(String)m.get("bmEndTime");
					bmend=bmend+" "+bmendtime;
				}					
			}
			m.put("bmBegin",bmbegin);
			m.put("bmEnd",bmend);
		}//for
	}
	
	public List find(String sqlstring){
		List li=baseDAO.findEntity(sqlstring);
		return li;
	}
}
