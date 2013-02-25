package com.sungard.smartcard.modules.system.function;


import java.util.List;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Component;

import com.sungard.smartcard.AbstractFunction;
import com.sungard.smartcard.RetCode;
import com.sungard.smartcard.annotation.SmartCardFunction;
import com.sungard.smartcard.annotation.TransfersNodeType;
import com.sungard.smartcard.bccsvr.BccServerThread;
import com.sungard.smartcard.bccsvr.Function;
import com.sungard.smartcard.domain.Specialty;
import com.sungard.smartcard.exception.FunctionException;
import com.sungard.smartcard.modules.system.service.SpecialtyService;

/**
 * 专业信息增删改查
 * 
 * @author chuxiong.long
 * @version v1.00
 * @since 2012-2-20
 */

@SmartCardFunction(infotype = 3, funcnum = 10006100, name = "专业信息维护")
@Component
public class SpecialtyFunction extends AbstractFunction {
	private static final Logger logger = LoggerFactory.getLogger(SpecialtyFunction.class);

	@Autowired
	@Qualifier("specialtyServiceImpl")
	private SpecialtyService specialtyService;

	/**
	 * 新增 
	 * specialtycode必填 
	 * specialtyname必填
	 * 
	 * */
	@Override
	public void add(Function function, BccServerThread session)throws FunctionException {
		String specialtycode = session.GetStringFieldByName(0,TransfersNodeType.scert_no.getName()); // 专业代码
		String specialtyname = session.GetStringFieldByName(0,TransfersNodeType.sall_name.getName());//专业名称

		/**
		 * 空值判断
		 * */
		if (specialtycode == null || "".equals(specialtycode)) {
			throw new FunctionException(RetCode.IS_NOT_NULL, "专业代码");
		}
		if (specialtyname == null || "".equals(specialtyname)) {
			throw new FunctionException(RetCode.IS_NOT_NULL, "专业名称");
		}
		/**
		 * 通过code判断是否有该条记录
		 * false 不存在
		 * true  存在
		 * */
		if (this.specialtyService.isExistSpecialtyCode(specialtycode) == true) {
			throw new FunctionException(RetCode.IS_EXISTS, "专业代码"+specialtycode);
		}
		/**
		 * 判断是否有该name
		 * false 不存在
		 * true  存在
		 * */
		if(this.specialtyService.isExistSpecialtyName(null,specialtyname)==true){
			throw new FunctionException(RetCode.IS_EXISTS, "专业名称"+specialtyname);
		}
		
		Specialty specialty = new Specialty();
		specialty.setSpecialtycode(specialtycode);
		specialty.setSpecialtyname(specialtyname);
		specialty.setUseflag("1");//使用标志 0：未使用；1：使用 
		int adds = specialtyService.addSpecialty(specialty);

		logger.info("[{} records was add]", specialtycode);
	}

	/**
	 * 删除
	 * 根据code删除
	 * */
	@Override
	public void delete(Function function, BccServerThread session)throws FunctionException {
		String specialtycode = session.GetStringFieldByName(0,TransfersNodeType.scert_no.getName()); // 专业代码

		/**
		 * 空值判断
		 * */
		if (specialtycode == null || "".equals(specialtycode)) {
			throw new FunctionException(RetCode.IS_NOT_NULL, "专业代码");
		}
		/**
		 * 判断是否有该条记录
		 * false 不存在
		 * true  存在
		 * */
		if(this.specialtyService.isExistSpecialtyCode(specialtycode)==false){
			throw new FunctionException(RetCode.IS_NOT_EXISTS, "专业信息");
		}
		int deletes = specialtyService.deleSpecialty(specialtycode);
		logger.info("[{} records was delete]", specialtycode);
	}

	/**
	 * 更新保存
	 * */
	@Override
	public void update(Function function, BccServerThread session)throws FunctionException {
		String specialtycode = session.GetStringFieldByName(0,TransfersNodeType.scert_no.getName()); // 专业代码
		String specialtyname = session.GetStringFieldByName(0,TransfersNodeType.sall_name.getName());// 专业名称

		/**
		 * 空值判断
		 * */
		if (specialtycode == null || "".equals(specialtycode)) {
			throw new FunctionException(RetCode.IS_NOT_NULL, "专业代码");
		}
		if (specialtyname == null || "".equals(specialtyname)) {
			throw new FunctionException(RetCode.IS_NOT_NULL, "专业名称");
		}
		/**
		 * 判断是否有该条记录  不存在 不修改
		 * false 不存在
		 * true  存在
		 * */
		if(this.specialtyService.isExistSpecialtyCode(specialtycode)==false){
			throw new FunctionException(RetCode.IS_NOT_EXISTS, "专业代码"+specialtycode);
		}
		
		/**
		 * 判断是否有该name
		 * false 不存在
		 * true  存在
		 * */
		if(this.specialtyService.isExistSpecialtyName(specialtycode,specialtyname)==true){
			throw new FunctionException(RetCode.IS_EXISTS, "专业名称"+specialtyname);
		}
				
		Specialty specialty = new Specialty();
		specialty.setSpecialtycode(specialtycode);
		specialty.setSpecialtyname(specialtyname);
		int updates = this.specialtyService.updateSpecialty(specialty);
		logger.info("[{} records was update]", specialtycode);
	}

	/**
	 * 根据输入的查询条件获得对应的 List<Specialty>
	 * */
	@Override
	public void query(Function function, BccServerThread session)throws FunctionException {
		Specialty param = super.getParameter(Specialty.class, session);
		List<Specialty> listspe = this.specialtyService.allSpecialty(param);
		super.outPack(listspe, Specialty.class, session);
	}

}
