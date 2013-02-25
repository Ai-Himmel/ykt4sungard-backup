package com.sungard.smartcard.modules.system.dao.impl;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.BeanPropertyRowMapper;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Repository;
import com.sungard.smartcard.domain.Specialty;
import com.sungard.smartcard.modules.system.dao.SpecialtyDao;

/**
 * 专业管理数据库操作类实现
 *
 * @author chuxiong.long
 * @version v1.00
 * @since 2012-02-20
 */
@Repository
public class SpecialtyDaoImpl implements SpecialtyDao{

	@Autowired
    private JdbcTemplate jdbcTemplate;

	/**
	 * 根据查询条件
	 * 返回List<Specialty>
	 * */
	@Override
	public List<Specialty> allSpecialty(Specialty specialty) {
		List<Specialty> listspe=null;
		StringBuffer selectsql = new StringBuffer("select * from t_specialty where 1=1 ");
		List args = new ArrayList();		
		if(specialty!=null){
			if(specialty.getSpecialtycode().trim()!=null&&!"".equals(specialty.getSpecialtycode().trim())){
				selectsql.append("and specialtycode= ? ");
				args.add(specialty.getSpecialtycode().trim());
				
			}
			if(specialty.getSpecialtyname().trim()!=null&&!"".equals(specialty.getSpecialtyname().trim())){
				selectsql.append("and specialtyname like ?");
				args.add("%"+specialty.getSpecialtyname().trim()+"%");
			}	
			
		}
		selectsql.append("order by specialtycode");		
		listspe= jdbcTemplate.query(selectsql.toString(), (args!=null&&args.size()>0)?args.toArray():null,
				new BeanPropertyRowMapper(Specialty.class));		
		return listspe;
	}

	/**
	 * 新增保存
	 * */
	@Override
	public int addSpecialty(Specialty specialty) {
		String addsql="insert into t_specialty(specialtycode,specialtyname,useflag,lastsaved) values(?,?,?,?) ";
		//当前时间格式化
		SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMddHHmmss");
		int i=jdbcTemplate.update(addsql, specialty.getSpecialtycode(),
				specialty.getSpecialtyname(),specialty.getUseflag(),sdf.format(new Date()));
		return i;
	}

	/**
	 * 根据specialtycode删除专业
	 * */
	@Override
	public int deleSpecialty(String specialtycode) {	
		String deletesql="delete from t_specialty where specialtycode=? ";
		int i=jdbcTemplate.update(deletesql, specialtycode);
		return i;
	}


	/**
	 * 修改保存
	 * */
	@Override
	public int updateSpecialty(Specialty specialty) {
		String updatesql="update t_specialty set specialtyname=?,lastsaved=? where specialtycode=?  ";
		//当前时间格式化
		SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMddHHmmss");
		return jdbcTemplate.update(updatesql, specialty.getSpecialtyname(),sdf.format(new Date()),specialty.getSpecialtycode());
	}

	/**
	 * 是否已存在该专业code
	 * */
	@Override
	public boolean isExistSpecialtyCode(String specialtycode) {
		String sql="select count(*) from t_specialty where 1=1 and specialtycode = ? ";
		int i=this.jdbcTemplate.queryForInt(sql, specialtycode);
		if(i>0){
			return true;
		}
		return false;
	}
	
	/**
	 * 是否已存在该专业name
	 * */
	@Override
	public boolean isExistSpecialtyName(String specialtycode,String specialtyname) {
		String sql="select count(*) from t_specialty where 1=1  ";
		int i=0;
		//code  不为null时为更新的判断是否重复名称
		if(specialtycode!=null&&!"".equals(specialtycode)){
			sql+=" and specialtycode!=? and specialtyname = ?  ";
			i=this.jdbcTemplate.queryForInt(sql, specialtycode,specialtyname);
		}else{
			sql+=" and specialtyname = ?  ";
			i=this.jdbcTemplate.queryForInt(sql, specialtyname);
		}
		if(i>0){
			return true;
		}
		return false;
	}

}
