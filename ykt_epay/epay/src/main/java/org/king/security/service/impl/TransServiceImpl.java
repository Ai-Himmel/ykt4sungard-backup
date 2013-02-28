package org.king.security.service.impl;

import java.sql.Types;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.common.displaytag.DBPaginatedList;
import org.king.common.query.QueryTranslate;
import org.king.framework.service.impl.BaseService;
import org.king.security.dao.VTransdtlDAO;
import org.king.security.service.TransService;

public class TransServiceImpl extends BaseService implements TransService {
	
	private static Log log = LogFactory.getLog(TransServiceImpl.class);
	
	private VTransdtlDAO vTransdtlDAO;
	

	public void setvTransdtlDAO(VTransdtlDAO vTransdtlDAO) {
		this.vTransdtlDAO = vTransdtlDAO;
	}



	public void getEayTransdtlList(DBPaginatedList page, Object[] conditions) {
		String hql = " from VTransdtl t where t.transcode = 6230 and t.id.accdate>=? and t.id.accdate<=? " ;
		
		if(conditions[2]!=null&&!"".equals(conditions[2])){
			hql+="and t.revflag = ? ";
		}
		
		if(conditions[3]!=null&&!"".equals(conditions[3])){
			hql+="and t.custid = ? ";
		}
		
		if(conditions[4]!=null&&!"".equals(conditions[4])){
			hql+="and t.stuempno = ? ";
		}
		hql += "and t.transcode in (select c.transcode from TTranscode c where c.feeflag = 1 or c.transflag = 1) " ;
		
		if(conditions[5]!=null&&!"".equals(conditions[5])){
			hql+="and t.status = ? ";
		}
		hql += 	"order by t.id.accdate desc, t.acctime desc, t.devseqno desc";
		
		QueryTranslate queryTranslate = new QueryTranslate();
        queryTranslate.setQueryString(hql);
        queryTranslate.setOffset(true);
        queryTranslate.setPageStartNo((page.getPageNumber() - 1) * page.getObjectsPerPage());
        queryTranslate.setPageSize(page.getObjectsPerPage());
        
        queryTranslate.addPara(conditions[0], Types.VARCHAR);
        queryTranslate.addPara(conditions[1], Types.VARCHAR);
        if(conditions[2]!=null&&!"".equals(conditions[2]))
        	queryTranslate.addPara(conditions[2], Types.VARCHAR);
    	if(conditions[3]!=null&&!"".equals(conditions[3]))
    		queryTranslate.addPara(conditions[3], Types.VARCHAR);
    	if(conditions[4]!=null&&!"".equals(conditions[4]))
    		queryTranslate.addPara(conditions[4], Types.VARCHAR);
    	if(conditions[5]!=null&&!"".equals(conditions[5]))
    		queryTranslate.addPara(conditions[5], Types.VARCHAR);
    	
    	vTransdtlDAO.findByPage(page, queryTranslate);
		
	}

}
