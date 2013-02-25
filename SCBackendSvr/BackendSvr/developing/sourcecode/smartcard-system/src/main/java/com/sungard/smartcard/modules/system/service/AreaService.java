package com.sungard.smartcard.modules.system.service;

import java.util.List;

import com.sungard.smartcard.domain.Area;

/**
 * 区域业务处理接口
 *
 * @author chuxiong.long
 * @version v1.00
 * @since 2012-02-22
 */
public interface AreaService {

	/**
	 * 获得所有的区域信息
	 * */
	public List<Area> allAreas();
	
	/**
	 * 添加保存区域信息
	 * */
	public int addArea(Area area);
	
	/**
	 * 根据areacode删除区域信息
	 * */
	public int deleArea(String areacode);
	
	/**
	 * 修改保存区域信息
	 * */
	public int updateArea(Area area);
	
	
	/**
	 * 根据areacode判断是否已存在子区域
	 * */
	public boolean isExistSonArea(String areacode);
	
	/**
	 * 根据areacode判断是否已存在
	 * */
	public boolean isExistArea(String areacode);
	
	/**
	 * 根据areaname查询是已存在重复名字的记录
	 * */
	public boolean isExistAreaName(String areacode,String areaname);
	
	/**
	 * 根据areacode查询是否为根区域
	 * */
	public boolean isFareArea(String areacode);
	
}
