package org.king.business.service.impl;

import java.sql.Types;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Date;
import java.util.List;
import java.util.Map;

import org.king.business.domain.BmStudent;
import org.king.business.domain.BmTestPublish;
import org.king.business.service.TestPublishService;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.utils.DateUtil;
import org.king.web.util.Constants;

public class TestPublishServiceImpl implements TestPublishService {
	
	private BaseDAO baseDAO;
	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}
	public BmTestPublish getDetail(String id) {
		BmTestPublish bmTestPublish=null;
		List li=baseDAO.findEntity("select a from BmTestPublish a where a.id='"+id+"'");
		if(li!=null&&li.size()>0){
			bmTestPublish=(BmTestPublish)li.get(0);
		}
		return bmTestPublish;
	}
    public List get4Update(String id){
		
		StringBuffer sbhql=new StringBuffer("");
		List li=new ArrayList();
		
		sbhql.append(" select new Map(a.id as id,a.title as title,a.body as body,a.ifDisplay as ifDisplay,a.ifPublic as ifPublic,a.creator as creator,a.createTime as createTime,a.updator as updator,a.updateTime as updateTime )"
				+"from BmTestPublish a where 1=1 and a.id='"+id+"'");
				
		li= baseDAO.findEntity(sbhql.toString());
		return li;
		
	}
    public List get4View(String id){
		
		StringBuffer sbhql=new StringBuffer("");
		List li=new ArrayList();
		
		sbhql.append(" select new Map(a.id as id,a.title as title,a.body as body,a.ifDisplay as ifDisplay,a.ifPublic as ifPublic,a.creator as creator,a.createTime as createTime,a.creator as creator,b.personName as creatorName,a.createTime as createTime,a.updator as updator,d.personName as updatorName,a.updateTime as updateTime )"
				+"from BmTestPublish a,Person b,Person d where 1=1 and b.personCode=a.creator and d.personCode=a.updator and a.id='"+id+"'");
				
		li= baseDAO.findEntity(sbhql.toString());
		
		if(li!=null&&li.size()>0)
			changeIfName(li);
		
		return li;
		
	}
    
    public List getList(Map m) {
		StringBuffer sbhql=new StringBuffer("");
		StringBuffer sWhere=new StringBuffer("");
		List li=new ArrayList();
		MyQuery mq=new MyQuery();
		
		sbhql.append(" select new Map(a.id as id,a.title as title,a.body as body,a.ifDisplay as ifDisplay,a.ifPublic as ifPublic,a.creator as creator,a.createTime as createTime,a.creator as creator,b.personName as creatorName,a.createTime as createTime,a.updator as updator,d.personName as updatorName,a.updateTime as updateTime )"
				+"from BmTestPublish a,Person b,Person d where 1=1 and b.personCode=a.creator and d.personCode=a.updator and a.ifDisplay!='9' and a.ifPublic!='9' ")
				.append(" and  a.updator ='"+(String)m.get("operator")+"'");
		
		if(m.get("search_id")!=null&&!((String)m.get("search_id")).equals("")){
			sWhere.append(" and a.id= ? ");
			mq.addPara((String)m.get("search_id"),Types.VARCHAR);
		}
		if(m.get("search_title")!=null&&!((String)m.get("search_title")).equals("")){
			sWhere.append(" and a.title like ? ");
			mq.addPara("%"+(String)m.get("search_title")+"%",Types.VARCHAR);
		}
		if(m.get("search_ifdisplay")!=null&&!((String)m.get("search_ifdisplay")).equals("")){
			sWhere.append(" and a.ifDisplay= ? ");
			mq.addPara((String)m.get("search_ifdisplay"),Types.VARCHAR);
		}
		if(m.get("search_ifpublic")!=null&&!((String)m.get("search_ifpublic")).equals("")){
			sWhere.append(" and a.ifPublic= ? ");
			mq.addPara((String)m.get("search_ifpublic"),Types.VARCHAR);
		}
		
		sWhere.append(" order by a.updateTime desc ");
		mq.setQueryString(sbhql.append(sWhere).toString());
		
		li= baseDAO.findEntity(mq);
		
		if(li!=null&&li.size()>0)
			changeIfName(li);
		
		return li;
	}
		
    public boolean save(BmTestPublish bmTestPublish) {
				
		baseDAO.saveEntity(bmTestPublish);
		
		return true;
	}
	public boolean update(BmTestPublish bmTestPublish) {
				
		baseDAO.updateEntity(bmTestPublish);
							
		return true;
	}
	public boolean delete(BmTestPublish bmTestPublish) {
		
		baseDAO.removeEntity(bmTestPublish);
	
		return true;
	}
	
	public List find(String sqlstring){
		List li=baseDAO.findEntity(sqlstring);
		return li;
	}
	
	public void changeIfName(List list){
		String[][] onoff= Constants.onoff_flag;
		for(int i=0;i<list.size();i++){
			Map m=(Map)list.get(i);
			
			String ifdValue=(String)m.get("ifDisplay");
			for(int j=0;j<onoff.length;j++){
				if(onoff[j][0].equals(ifdValue)){
					m.put("ifDisplayName",onoff[j][1]);
				}
			}
			
			String ifpValue=(String)m.get("ifPublic");
			for(int j=0;j<onoff.length;j++){
				if(onoff[j][0].equals(ifpValue)){
					m.put("ifPublicName",onoff[j][1]);
				}
			}
		}//for
		
	}	
			
}
