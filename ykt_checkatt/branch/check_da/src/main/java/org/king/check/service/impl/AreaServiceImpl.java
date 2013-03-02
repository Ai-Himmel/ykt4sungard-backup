package org.king.check.service.impl;

import java.util.List;

import org.king.check.dao.AreaDAO;
import org.king.check.domain.TArea;
import org.king.check.service.AreaService;
import org.apache.commons.io.output.DeferredFileOutputStream;
public class AreaServiceImpl implements AreaService{
	
	private AreaDAO  areaDAO;

	public void setAreaDAO(AreaDAO areaDAO) {
		this.areaDAO = areaDAO;
	}

	public List findArea() throws Exception{
		String query = "select new Map(a.areaCode as areaCode , " +
				" a.areaName as areaName ) from  TArea a where areaLevel=2 ";
	    return 	areaDAO.findArea(query);
	}
	
	public TArea findAreaByName(String name)throws Exception{
		StringBuffer  query =new StringBuffer( " from TArea  a  where a.areaName ='")
			.append(name).append("'");
		List list = areaDAO.findArea(query.toString());
		if(list !=null && !list.isEmpty()){
			TArea area =  (TArea)list.get(0);
			return area;
		}else{
			return null;
		}
		
	}

	public TArea getArea(String areaCode) throws Exception {
		return (TArea)areaDAO.get(areaCode);
	}
}
