package org.king.business.service.impl;

import java.sql.Types;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Date;
import java.util.List;
import java.util.Map;

import org.king.business.domain.BmStudent;
import org.king.business.domain.BmTestCat;
import org.king.business.service.TestCategoryService;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.utils.DateUtil;
import org.king.web.util.Constants;

public class TestCategoryServiceImpl implements TestCategoryService {
	
	private BaseDAO baseDAO;
	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}
	public BmTestCat getDetail(String id) {
		BmTestCat bmTestCat=null;
		List li=baseDAO.findEntity("select a from BmTestCat a where a.id='"+id+"'");
		if(li!=null&&li.size()>0){
			bmTestCat=(BmTestCat)li.get(0);
		}		
		return bmTestCat;
	}
    public List get4Update(String id){
		
		StringBuffer sbhql=new StringBuffer("");
		List li=new ArrayList();
		
		sbhql.append(" select new Map(a.id as id,a.testCatName as testCatName,a.ifFee as ifFee,a.fee as fee,a.state as state,a.updator as updator,a.updateTime as updateTime )"
				+"from BmTestCat a where 1=1 and a.id='"+id+"'");
				
		li= baseDAO.findEntity(sbhql.toString());
		return li;
		
	}
    public List get4View(String id){
		
		StringBuffer sbhql=new StringBuffer("");
		List li=new ArrayList();
		
		sbhql.append(" select new Map(a.id as id,a.testCatName as testCatName,a.ifFee as ifFee,a.fee as fee,a.state as state,a.updator as updator,a.updateTime as updateTime )"
				+"from BmTestCat a where 1=1 and a.id='"+id+"'");
				
		li= baseDAO.findEntity(sbhql.toString());
		
		if(li!=null&&li.size()>0){
			  changeIfName(li);
		      changeStateName(li);		      
		}
		return li;
		
	}
    
    public List getList(Map m) {
		StringBuffer sbhql=new StringBuffer("");
		StringBuffer sWhere=new StringBuffer("");
		List li=new ArrayList();
		MyQuery mq=new MyQuery();
		
		sbhql.append(" select new Map(a.id as id,(a.id||'_'||a.testCatName) as idmc,a.testCatName as testCatName,a.ifFee as ifFee,a.fee as fee,a.state as state,a.updator as updator,b.personName as updatorName,a.updateTime as updateTime) from BmTestCat a,Person b where 1=1 and b.personCode=a.updator ");
		sbhql.append(" and  a.updator ='"+m.get("operator")+"' " );
		
		if(m.get("search_id")!=null&&!((String)m.get("search_id")).equals("")){
			sWhere.append(" and a.id= ? ");
			mq.addPara((String)m.get("search_id"),Types.VARCHAR);
		}
		if(m.get("search_testcatname")!=null&&!((String)m.get("search_testcatname")).equals("")){
			sWhere.append(" and a.testCatName like ? ");
			mq.addPara("%"+(String)m.get("search_testcatname")+"%",Types.VARCHAR);
		}		
		if(m.get("search_state")!=null&&!((String)m.get("search_state")).equals("")){
			sWhere.append(" and a.state= ? ");
			mq.addPara((String)m.get("search_state"),Types.VARCHAR);
		}
				
		mq.setQueryString(sbhql.append(sWhere).toString());
		
		li= baseDAO.findEntity(mq);
		
		if(m.get("search_includeid")!=null&&!((String)m.get("search_includeid")).equals("")){
			String sqlstring=" select new Map(a.id as id,(a.id||'_'||a.testCatName) as idmc,a.testCatName as testCatName,a.ifFee as ifFee,a.fee as fee,a.state as state,a.updator as updator,b.personName as updatorName,a.updateTime as updateTime) from BmTestCat a,Person b where 1=1 and b.personCode=a.updator and a.id='"+(String)m.get("search_includeid")+"'";
		    List thisli=baseDAO.findEntity(sqlstring);
		    if(thisli!=null&&thisli.size()>0){
		    	Map thismap=(Map)thisli.get(0);
		    	if(thismap.get("state").equals(Constants.notUsingCode))
		    	    li.add(thismap);
		    }
		
		}
		
        //按名称排序
		Comparator comp1 = new Comparator() { 
			 public int compare(Object o1, Object o2){ 
			 Map m1 = (Map)o1; 
			 Map m2 = (Map)o2; 
			 String curName1 = (String)m1.get("testCatName"); 
			 String curName2 = (String)m2.get("testCatName");      				

			com.ibm.icu.text.Collator collator = com.ibm.icu.text.Collator.getInstance(java.util.Locale.CHINA);
			com.ibm.icu.text.CollationKey c1= collator.getCollationKey(curName1);
			com.ibm.icu.text.CollationKey c2= collator.getCollationKey(curName2);
            //注意,返回值是比较的结果>0,=0,或者<0
		     return collator.compare(c1.getSourceString(),c2.getSourceString());			 
			 } 
		} ;			
		 
	    Collections.sort(li, comp1);
		
		if(li!=null&&li.size()>0){
			  changeIfName(li);
		      changeStateName(li);		      
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
			
			sbhql.append(" select new Map(a.id as id,(a.id||'_'||a.testCatName) as idmc,a.testCatName as testCatName,a.ifFee as ifFee,a.fee as fee,a.state as state,a.updator as updator,b.personName as updatorName,a.updateTime as updateTime) from BmTestCat a,Person b where 1=1 and b.personCode=a.updator ");
			
			sWhere.append(" and  a.updator ='"+m.get("operator")+"'");
			
			sWhere.append(" and a.id='"+newids+"' ");		    		
			
			sWhere.append(" order by a.updateTime desc ");
			mq.setQueryString(sbhql.append(sWhere).toString());        
			
			li= baseDAO.findEntity(mq);
		}
		
		sbhql=new StringBuffer("");
		sWhere=new StringBuffer("");
		mq=new MyQuery();
		
		sbhql.append(" select new Map(a.id as id,(a.id||'_'||a.testCatName) as idmc,a.testCatName as testCatName,a.ifFee as ifFee,a.fee as fee,a.state as state,a.updator as updator,b.personName as updatorName,a.updateTime as updateTime) from BmTestCat a,Person b where 1=1 and b.personCode=a.updator ");
		
		sbhql.append(" and  a.updator ='"+m.get("operator")+"'");
		
		if(m.get("newidstring")!=null&&!((String)m.get("newidstring")).equals("")){
			String newids=(String)m.get("newidstring");
			sWhere.append(" and a.id!='"+newids+"' ");			
		}		
				
		mq.setQueryString(sbhql.append(sWhere).toString());        
		
		oli= baseDAO.findEntity(mq);
		
//		按名称排序
		Comparator comp1 = new Comparator() { 
			 public int compare(Object o1, Object o2){ 
			 Map m1 = (Map)o1; 
			 Map m2 = (Map)o2; 
			 String curName1 = (String)m1.get("testCatName"); 
			 String curName2 = (String)m2.get("testCatName");      				

			com.ibm.icu.text.Collator collator = com.ibm.icu.text.Collator.getInstance(java.util.Locale.CHINA);
			com.ibm.icu.text.CollationKey c1= collator.getCollationKey(curName1);
			com.ibm.icu.text.CollationKey c2= collator.getCollationKey(curName2);
            //注意,返回值是比较的结果>0,=0,或者<0
		     return collator.compare(c1.getSourceString(),c2.getSourceString());			 
			 } 
		} ;		
		 
	    Collections.sort(oli, comp1);
				
		if(oli!=null&&oli.size()>0){
			for(int i=0;i<oli.size();i++){
				li.add(li.size(),oli.get(i));				
			}
		}
		
		if(li!=null&&li.size()>0){
			changeIfName(li);
		    changeStateName(li);
		}     
		return li;
	}
	
    public boolean save(BmTestCat bmTestCat) {
				
		baseDAO.saveEntity(bmTestCat);
		
		return true;
	}
	public boolean update(BmTestCat bmTestCat) {
				
		baseDAO.updateEntity(bmTestCat);
							
		return true;
	}
	public boolean delete(BmTestCat bmTestCat) {
		
		if(!bmTestCat.getId().equals("e4")&&!bmTestCat.getId().equals("e6"))
		    baseDAO.removeEntity(bmTestCat);
	
		return true;
	}
	
	public boolean check4Save(String testcatName,String id){
		String sqlstring="select a from BmTestCat a where a.testCatName='"+testcatName+"'";
		if(id!=null)
			sqlstring=sqlstring+" and a.id<>'"+id+"'";
		
		List testcatList=baseDAO.findEntity(sqlstring);
		if(testcatList!=null&&testcatList.size()>0)
			return false;
		else
			return true;
	}
	
	public String check4Delete(String id){
		String sqlstring="select a from BmTest a where a.bmTestCat.id='"+id+"'";
				
		List testList=baseDAO.findEntity(sqlstring);
		if(testList!=null&&testList.size()>0){
			BmTestCat bmTestCat=getDetail(id);
			return bmTestCat.getTestCatName();
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
}
