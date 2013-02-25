package com.sungard.smartcard.modules.system.dao;

import java.util.List;

import com.sungard.smartcard.domain.Area;

/**
 * 区域数据库操作类接口
 *
 * @author chuxiong.long
 * @version v1.00
 * @since 2012-02-22
 */
public interface AreaDao {

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
	 * 根据areacode得到区域信息
	 * */
	public Area getArea(String areacode);
	
	/**
	 * 根据areacode查询存在子区域数目
	 * */
	public boolean isExistSonArea(String areacode);
	
	/**
	 * 根据areacode查询是已存在
	 * */
	public boolean isExistArea(String areacode);
	
	/**
	 * 根据areaname查询是已存在重复的区域名称
	 * */
	public boolean isExistAreaName(String areacode,String areaname);
	
	/**
	 * 根据areacode查询是否为根区域
	 * */
	public boolean isFareArea(String areacode);
	
}
