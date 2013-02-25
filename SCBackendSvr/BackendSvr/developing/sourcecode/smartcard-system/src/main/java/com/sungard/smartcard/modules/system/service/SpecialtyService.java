package com.sungard.smartcard.modules.system.service;

import java.util.List;

import com.sungard.smartcard.domain.Specialty;

/**
 * 专业信息业务处理接口
 *
 * @author chuxiong.long
 * @version v1.00
 * @since 2012-2-20
 */
public interface SpecialtyService {

	
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
	 * 根据code判断是否已存在
	 * */
	public boolean isExistSpecialtyCode(String specialtycode);
	
	/**
	 * 根据code和name判断是否已存在重复的专业名称
	 * */
	public boolean isExistSpecialtyName(String specialtycode,String specialtyname);	
}
