package com.sungard.smartcard.modules.system.service.impl;

import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import com.sungard.smartcard.domain.Specialty;
import com.sungard.smartcard.modules.system.dao.SpecialtyDao;
import com.sungard.smartcard.modules.system.service.SpecialtyService;

/**
 * 专业信息维护处理实现
 * 
 * @author chuxiong.long
 * @version v1.00
 * @since 2012-02-20
 */
@Service
@Transactional
public class SpecialtyServiceImpl implements SpecialtyService {

	@Autowired
	@Qualifier("specialtyDaoImpl")
	private SpecialtyDao specialtyDao;

	/**
	 * 根据条件查询 返回List<Specialty>
	 * */
	@Override
	public List<Specialty> allSpecialty(Specialty specialty) {
		return specialtyDao.allSpecialty(specialty);
	}

	/**
	 * 新增保存
	 * */
	@Override
	public int addSpecialty(Specialty specialty) {
		return specialtyDao.addSpecialty(specialty);
	}

	/**
	 * 更新保存
	 * */
	@Override
	@Transactional
	public int updateSpecialty(Specialty specialty) {
		return specialtyDao.updateSpecialty(specialty);
	}

	/**
	 * 根据specialtycode删除
	 * */
	@Override
	@Transactional
	public int deleSpecialty(String specialtycode) {
		return specialtyDao.deleSpecialty(specialtycode);
	}

	/**
	 * 根据specialtycode判断是否已存在
	 * 
	 * */
	@Override
	public boolean isExistSpecialtyCode(String specialtycode) {
		return this.specialtyDao.isExistSpecialtyCode(specialtycode);
	}
	
	/**
	 * 根据specialtyname判断是否已存在
	 * 
	 * */
	@Override
	public boolean isExistSpecialtyName(String specialtycode,String specialtyname) {
		return this.specialtyDao.isExistSpecialtyName(specialtycode,specialtyname);
	}

}
