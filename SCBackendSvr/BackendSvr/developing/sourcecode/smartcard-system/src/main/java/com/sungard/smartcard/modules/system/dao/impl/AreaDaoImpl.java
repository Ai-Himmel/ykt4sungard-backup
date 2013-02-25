package com.sungard.smartcard.modules.system.dao.impl;

import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.BeanPropertyRowMapper;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Repository;

import com.sungard.smartcard.domain.Area;
import com.sungard.smartcard.modules.system.dao.AreaDao;
/**
 * 区域数据库操作类实现
 *
 * @author chuxiong.long
 * @version v1.00
 * @since 2012-02-22
 */
@Repository
public class AreaDaoImpl implements AreaDao {
	
	@Autowired
    private JdbcTemplate jdbcTemplate;	
	/**
	 * 查询得到所有的区域信息
	 * */
	@Override
	public List<Area> allAreas() {
		return this.jdbcTemplate.query(" select * from t_area where 1=1　order by areacode ",
				new BeanPropertyRowMapper(Area.class));
	}

	/**
	 * 添加保存
	 * */
	@Override
	public int addArea(Area area) {
		return this.jdbcTemplate.update("insert into t_area(areacode,areaname,fareacode,arealevel,addr,remark) values(?,?,?,?,?,?) ",
				area.getAreacode(),area.getAreaname(),area.getFareacode(),area.getArealevel(),area.getAddr(),area.getRemark());
	}

	/**
	 * 根据code删除
	 * */
	@Override
	public int deleArea(String areacode) {
		return this.jdbcTemplate.update("delete from t_area where areacode=? ", areacode);
	}
	/**
	 * 根据code获得Area对象
	 * */
	@Override
	public Area getArea(String areacode) {
		return this.jdbcTemplate.queryForObject("select * from t_area where 1=1 and areacode=? ", 
				new BeanPropertyRowMapper(Area.class),areacode);
	}

	/**
	 * 更新保存
	 * */
	@Override
	public int updateArea(Area area) {
		return this.jdbcTemplate.update("update t_area set areaname=?,addr=?,remark=? where areacode=? ", 
				area.getAreaname(),area.getAddr(),area.getRemark(),area.getAreacode());
	}
	
	/**
	 * 根据传入的code 判断是否存在子区域
	 * 删除的时候需要判断
	 * 存在：true
	 * 不存在：false
	 * */
	@Override
	public boolean isExistSonArea(String fareacode){
		int i=0;
		i=this.jdbcTemplate.queryForInt("select count(*) from t_area where 1=1 and fareacode=? ", fareacode);
		if(i>0){
			return true;
		}
		return false;
	}
	
	/**
	 * 根据传入的code 判断是否存在区域记录
	 * 存在：true
	 * 不存在：false
	 * */
	@Override
	public boolean isExistArea(String areacode) {
		int i=0;
		i=this.jdbcTemplate.queryForInt("select count(*) from t_area where 1=1 and areacode=? ", areacode);
		if(i>0){
			return true;
		}
		return false;
	}
	
	
	/**
	 * 判断是否存在相同name的区域
	 * 存在：true
	 * 不存在：false
	 * */
	@Override
	public boolean isExistAreaName(String areacode,String areaname) {
		String sql ="select count(*) from t_area where 1=1 ";
		int i=0;
		if(areacode!=null&&!"".equals(areacode)){//修改的时候判断是否名称
			sql+=" and areacode!=?  and areaname=? ";
			i=this.jdbcTemplate.queryForInt(sql, areacode,areaname);
		}else{//新增的时候判断是否相同名称
			sql+=" and areaname=? ";
			i=this.jdbcTemplate.queryForInt(sql, areaname);
		}		
		if(i>0){
			return true;
		}
		return false;
	}
	
	/**
	 * 根据传入的code 判断是根区域
	 * 是：true
	 * 否：false
	 * */
	@Override
	public boolean isFareArea(String areacode){
		int i=0;
		i=this.jdbcTemplate.queryForInt("select count(*) from t_area where 1=1 and fareacode is null and areacode=? ", areacode);
		if(i>0){
			return true;
		}
		return false;
	}
}
