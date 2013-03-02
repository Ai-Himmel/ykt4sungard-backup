package org.king.check.service;

import java.util.List;

import org.king.check.domain.TArea;

public interface AreaService {
	
	public List findArea()throws Exception;
	
	public TArea findAreaByName(String name)throws Exception;
	
	public TArea getArea(String areaCode) throws Exception;

}
