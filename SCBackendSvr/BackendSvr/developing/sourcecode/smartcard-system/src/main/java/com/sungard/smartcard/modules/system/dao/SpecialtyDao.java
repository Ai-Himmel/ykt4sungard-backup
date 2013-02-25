package com.sungard.smartcard.modules.system.dao;

import java.util.List;

import com.sungard.smartcard.domain.Specialty;


/**
 * 专业信息数据库操作类接口
 *
 * @author chuxiong.long
 * @version v1.00
 * @since 2012-02-20
 */
public interface SpecialtyDao {

	/**
	 * 查询所有专业信息
	 * */
	public List<Specialty> allSpecialty(Specialty specialty);
	
	/**
	 * 更新专业信息
	 * */
	public int updateSpecialty(Specialty specialty);
	
	/**
	 * 添加专业信息
	 * */
	public int addSpecialty(Specialty specialty);
	
	/**
	 * 根据code删除专业信息
	 * */
	public int deleSpecialty(String specialtycode);
	
	
	/**
	 * 根据code查询是否存在该专业
	 * */
	public boolean isExistSpecialtyCode(String specialtycode);
	
	/**
	 * 根据name查询是否存在该专业
	 * */
	public boolean isExistSpecialtyName(String specialtycode,String specialtyname);
}
