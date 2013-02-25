package com.sungard.smartcard.modules.system.service.impl;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.List;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.util.StringUtils;

import com.sungard.modules.utils.StringHelper;
import com.sungard.smartcard.RetCode;
import com.sungard.smartcard.domain.Branch;
import com.sungard.smartcard.exception.FunctionException;
import com.sungard.smartcard.modules.system.dao.BranchDao;
import com.sungard.smartcard.modules.system.dao.OperatorDao;
import com.sungard.smartcard.modules.system.service.BranchService;

@Service
public class BranchServiceImpl implements BranchService {
	private static final Logger logger = LoggerFactory.getLogger(OperatorServiceImpl.class);
    @Autowired
    private BranchDao branchDao;
    @Autowired
    private OperatorDao operatorDao;
	public void setOperatorDao(OperatorDao operatorDao) {
		this.operatorDao = operatorDao;
	}
	public void setBranchDao(BranchDao branchDao) {
		this.branchDao = branchDao;
	}

	@Override
	@Transactional
	public void addNewBranch(Branch b) throws FunctionException {
		logger.info("添加网点"+b.getBranchname());
		/**网点名称不能为空*/
		String branchName = b.getBranchname().trim();
		if(StringHelper.isBlank(branchName)){
			throw new FunctionException(RetCode.ADDBRANCH_WRONG_NULLBRANCHNAME);
		}
		/**网点类型不能为空*/
		String branchType = b.getBranchtype().trim();
		if(StringHelper.isBlank(branchType)){
			throw new FunctionException(RetCode.ADDBRANCH_WRONG_NULLBRANCHTYPE);
		}
		/**区域号不能为空*/
		String areacode = b.getAreacode().trim();
		if(StringHelper.isBlank(areacode)){
			throw new FunctionException(RetCode.ADDBRANCH_WRONG_NULLAREACODE);
		}
		/**网点名称长度不能超过50*/
		if(branchName.length()>50){
			throw new FunctionException(RetCode.ADDBRANCH_WRONG_TOOLONGBRANCHNAME);
		}
		/**网点名称不能重复*/
		int duplicatename = branchDao.getBranchNumByParam(branchName,null);
		if(duplicatename!=0){
			throw new FunctionException(RetCode.ADDBRANCH_WRONG_DUPLICATEBRANCHNAME);
		}
		/**增加网点*/
		b.setUseflag("0");
		/**将操作员登出时间为当前时间*/
		SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMddHHmmss");
		String dd = sdf.format(new Date());
		SimpleDateFormat sdf1 = new SimpleDateFormat("yyyyMMdd");
		String ddd = sdf1.format(new Date());
		b.setOpendate(ddd);
		b.setLastsaved(dd);
		//TODO 网点未添加日志功能
		branchDao.addBranch(b);
	}

	@Override
	@Transactional
	public void delBranch(Branch b) throws FunctionException {
		/**判断是否存在该条网点记录 */
		int bn = b.getBranchno();
		int isexists = branchDao.getBranchNumByParam(null, bn);
		if(isexists==0){
			//不存在抛出错误码
			throw new FunctionException(RetCode.DELBRANCH_WRONG_NOTEXISTBRANCH);
		}
		/**判断是否存在关联操作员*/
		int operatornum = operatorDao.getOperatorNumRelateBranch(bn);
		if(operatornum >0){
			//不存在抛出错误码
			throw new FunctionException(RetCode.DELBRANCH_WRONG_EXISTOPERATOR);
		}
		SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMddHHmmss");
		String d = sdf.format(new Date());
		b.setLastsaved(d);
		b.setUseflag("0");
		//TODO 网点未添加日志功能
		branchDao.delBranch(b);
	}

	@Override
	@Transactional
	public void modifyBranch(Branch b) throws FunctionException {
		logger.info("修改网点"+b.getBranchname());
		/**网点名称不能为空*/
		String branchName = b.getBranchname().trim();
		if(StringHelper.isBlank(branchName)){
			throw new FunctionException(RetCode.ADDBRANCH_WRONG_NULLBRANCHNAME);
		}
		/**网点类型不能为空*/
		String branchType = b.getBranchtype().trim();
		if(StringHelper.isBlank(branchType)){
			throw new FunctionException(RetCode.ADDBRANCH_WRONG_NULLBRANCHTYPE);
		}
		/**区域号不能为空*/
		String areacode = b.getAreacode().trim();
		if(StringHelper.isBlank(areacode)){
			throw new FunctionException(RetCode.ADDBRANCH_WRONG_NULLAREACODE);
		}
		/**网点名称长度不能超过50*/
		if(branchName.length()>50){
			throw new FunctionException(RetCode.ADDBRANCH_WRONG_TOOLONGBRANCHNAME);
		}
		/**网点名称不能重复*/
		int duplicatename = branchDao.getBranchNumByParam(branchName,b.getBranchno());
		if(duplicatename!=0){
			throw new FunctionException(RetCode.ADDBRANCH_WRONG_DUPLICATEBRANCHNAME);
		}
		/**增加网点*/
		/**将操作员登出时间为当前时间*/
		SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMddHHmmss");
		String dd = sdf.format(new Date());
		b.setLastsaved(dd);
		//TODO 网点未添加日志功能
		branchDao.updateBranch(b);
	}

	@Override
	public List<Branch> queryBranch(Branch b) throws FunctionException {
		List<Branch> branches= branchDao.queryBranch(b);
		return branches;
	}

}
