package com.sungard.smartcard.modules.system.service.impl;


import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import com.sungard.smartcard.domain.Area;
import com.sungard.smartcard.modules.system.dao.AreaDao;
import com.sungard.smartcard.modules.system.service.AreaService;

/**
 * 区域业务处理实现
 * 
 * @author chuxiong.long
 * @version v1.00
 * @since 2012-02-22
 */
@Service
@Transactional
public class AreaServiceImpl implements AreaService{

	@Autowired
	@Qualifier("areaDaoImpl")
	private AreaDao areaDao;

	@Override
	public List<Area> allAreas() {
		return this.areaDao.allAreas();
	}	

	@Override
	public int updateArea(Area area) {
		return this.areaDao.updateArea(area);
	}

	//新增
	@Override
	public int addArea(Area area) {
		String fareacode=area.getFareacode().trim();
		Area temparea=this.areaDao.getArea(fareacode);
		
		//通过上级区域基本加1得到本级区域级别
		int templevel=0;
		if(temparea!=null){
			Integer i=temparea.getArealevel();
			templevel=(i!=null?i:0)+1;
		}else{
			templevel=1;
		}	
		area.setArealevel(templevel);
		
		return this.areaDao.addArea(area);
	}

	@Override
	public int deleArea(String areacode) {		
		return this.areaDao.deleArea(areacode);
	}
	/**
	 * 根据code 不同条件查询是否存在相同下级区域的记录
	 * */
	@Override
	public boolean isExistSonArea(String areacode){
		return this.areaDao.isExistSonArea(areacode);
	}
	/**
	 * 根据code 不同条件查询是否存在相同code的记录
	 * */
	@Override
	public boolean isExistArea(String areacode) {
		return this.areaDao.isExistArea(areacode);
	}

	/**
	 * 根据code 和 name 不同条件查询是否存在同名
	 * */
	@Override
	public boolean isExistAreaName(String areacode,String areaname) {
		return this.areaDao.isExistAreaName(areacode,areaname);
	}
	/**
	 * 根据code 不同条件查询是否存在相同上级区域的记录
	 * */
	@Override
	public boolean isFareArea(String areacode) {
		return this.areaDao.isFareArea(areacode);
	}	
		
}
