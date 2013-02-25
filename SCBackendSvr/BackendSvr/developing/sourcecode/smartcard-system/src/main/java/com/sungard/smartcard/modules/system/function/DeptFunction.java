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
import com.sungard.smartcard.domain.Dept;
import com.sungard.smartcard.exception.FunctionException;
import com.sungard.smartcard.modules.system.service.DeptService;

/**
 * 部门信息增删改查
 * 
 * @author chuxiong.long
 * @version v1.00
 * @since 2012-2-22
 */
@SmartCardFunction(infotype = 3, funcnum = 10005100, name = "部门信息设置及查询")
@Component
public class DeptFunction  extends AbstractFunction {
	private static final Logger logger = LoggerFactory.getLogger(SpecialtyFunction.class);
	
	
	@Autowired
	@Qualifier("deptServiceImpl")
	private DeptService deptService;
	 	
	public void setDeptService(DeptService deptService) {
		this.deptService = deptService;
	}

	/**
	 * 新增保存
	 * 
	 * */
	@Override
	public void add(Function function, BccServerThread session)
			throws FunctionException {		
		/**
		 * 上级部门代码为空判断，是否存在上级部门代码
		 * */
		String fdeptcode= session.GetStringFieldByName(0, TransfersNodeType.sbank_acc.getName()); //上级部门代码
		if(fdeptcode==null||"".equals(fdeptcode)){
			throw new FunctionException(RetCode.IS_NOT_NULL,"上级部门代码");
		}
		if(this.deptService.isExitDept(fdeptcode)==false){
			throw new FunctionException(RetCode.IS_NOT_EXISTS,"上级部门代码"+fdeptcode);
		}
		/**
		 * 部门名称为空判断，重复名称判断
		 * */
		String deptname= session.GetStringFieldByName(0, TransfersNodeType.vsvarstr0.getName()); //部门名称
		if(deptname==null||"".equals(deptname)){
			throw new FunctionException(RetCode.IS_NOT_NULL,"部门名称");
		}
		if(this.deptService.isExitDeptName(null,deptname)==true){
			throw new FunctionException(RetCode.IS_EXISTS,"部门名称"+deptname);
		}
		/**
		 * 部门英文名称
		 * */
		String deptename= session.GetStringFieldByName(0, TransfersNodeType.vsvarstr1.getName()); //部门英文名
		/**
		 * 区域代码
		 * */
		String areacode= session.GetStringFieldByName(0, TransfersNodeType.sroom_no.getName()); //区域代码

		/**
		 *原部门代码
		 * */
		String olddeptcode= session.GetStringFieldByName(0, TransfersNodeType.sbank_acc2.getName()); //原部门代码


		Dept dept = new Dept();
		
		dept.setFdeptcode(fdeptcode);
		dept.setDeptename(deptename);//英文名称
		dept.setAreacode(areacode);
		dept.setDeptname(deptname);//部门名称
		dept.setOlddeptcode(olddeptcode);
		dept.setUseflag("1");//使用标志，0：未使用；1：使用 
		int adds =this.deptService.addDept(dept);	
		logger.info("[{} records was add]", adds+" dept");
	}

	/**
	 * 删除
	 * 
	 * */
	@Override
	public void delete(Function function, BccServerThread session)
			throws FunctionException {
		String deptcode= session.GetStringFieldByName(0, TransfersNodeType.scust_limit.getName()); //部门代码 
		if(deptcode==null||"".equals(deptcode)){
			throw new FunctionException(RetCode.IS_NOT_NULL,"部门代码 ");
		}
		//是否存在该记录
		if(this.deptService.isExitDept(deptcode)==false){
			throw new FunctionException(RetCode.IS_NOT_EXISTS,"部门记录");
		}
		/**
		 * 判断是不是根部门     是根部门不能删除
		 * false 不存在
		 * true  存在
		 * */
		if(this.deptService.isFarDept(deptcode)==true){
			throw new FunctionException(RetCode.NO_DELORUPD_FARTHERNODE,"删除");
		}
		/**
		 * 判断是不是存在下级部门     有下级部门不能删除，需要先删除下级部门
		 * false 不存在
		 * true  存在
		 * */
		if(this.deptService.isExistSonDept(deptcode)==true){
			throw new FunctionException(RetCode.FIRST_DELETE_SONNODE,"部门");//先删除下级部门
		}
		
		int deletes= this.deptService.deleDept(deptcode);
		logger.info("[{} records was delete]", deptcode);
	}

	/**
	 * 修改保存
	 * 
	 * */
	@Override
	public void update(Function function, BccServerThread session)
			throws FunctionException {
		/**
		 * 部门代码为空判断和是否存在
		 * */
		String deptcode= session.GetStringFieldByName(0, TransfersNodeType.scust_limit.getName()); //部门代码 
		if(deptcode==null||"".equals(deptcode)){
			throw new FunctionException(RetCode.IS_NOT_NULL,"部门代码 ");
		}
		if(this.deptService.isExitDept(deptcode)==false){
			throw new FunctionException(RetCode.IS_NOT_EXISTS,"部门记录");
		}
		/**
		 * 上级部门代码为空判断，是否存在上级部门代码
		 * */
		String fdeptcode= session.GetStringFieldByName(0, TransfersNodeType.sbank_acc.getName()); //上级部门代码
		if(fdeptcode==null||"".equals(fdeptcode)){
			throw new FunctionException(RetCode.IS_NOT_NULL,"上级部门代码");
		}
		if(this.deptService.isExitDept(fdeptcode)==false){
			throw new FunctionException(RetCode.IS_NOT_EXISTS,"上级部门记录"+fdeptcode);
		}
		/**
		 * 部门名称为空判断，重复名称判断
		 * */
		String deptname= session.GetStringFieldByName(0, TransfersNodeType.vsvarstr0.getName()); //部门名称
		if(deptname==null||"".equals(deptname)){
			throw new FunctionException(RetCode.IS_NOT_NULL,"部门名称");
		}
		if(this.deptService.isExitDeptName(deptcode,deptname)==true){
			throw new FunctionException(RetCode.IS_EXISTS,"部门名称"+deptname);
		}
		/**
		 * 部门英文名称
		 * */
		String deptename= session.GetStringFieldByName(0, TransfersNodeType.vsvarstr1.getName()); //部门英文名
		/**
		 * 区域代码
		 * */
		String areacode= session.GetStringFieldByName(0, TransfersNodeType.sroom_no.getName()); //区域代码
		/**
		 *原部门代码
		 * */
		String olddeptcode= session.GetStringFieldByName(0, TransfersNodeType.sbank_acc2.getName()); //原部门代码
		
		Dept dept = new Dept();
		
		dept.setDeptcode(deptcode);
		dept.setFdeptcode(fdeptcode);
		dept.setDeptename(deptename);//英文名称
		dept.setAreacode(areacode);
		dept.setDeptname(deptname);//部门名称
		dept.setOlddeptcode(olddeptcode);
		
		int updates =this.deptService.updateDept(dept);
		logger.info("[{} records was update]", deptcode);
	}

	/**
	 * 根据条件查询
	 * */
	@Override
	public void query(Function function, BccServerThread session)
			throws FunctionException {
		Dept params=super.getParameter(Dept.class, session);
		List<Dept> listdept=this.deptService.allDepts(params);
	
		super.outPack(listdept, Dept.class, session);
	}
	
}
