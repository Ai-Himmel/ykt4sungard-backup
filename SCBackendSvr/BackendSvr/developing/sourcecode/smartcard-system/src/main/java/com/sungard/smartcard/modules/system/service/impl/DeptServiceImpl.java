package com.sungard.smartcard.modules.system.service.impl;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import com.sungard.smartcard.domain.Dept;
import com.sungard.smartcard.modules.system.dao.DeptDao;
import com.sungard.smartcard.modules.system.service.DeptService;

/**
 * 部门业务处理实现
 * 
 * @author chuxiong.long
 * @version v1.00
 * @since 2012-02-22
 */
@Service
@Transactional
public class DeptServiceImpl implements DeptService{
	@Autowired
	@Qualifier("deptDaoImpl")
	private DeptDao deptDao;
	
	@Override
	public List<Dept> allDepts(Dept dept) {
		return this.deptDao.allDepts(dept);
	}
	/**
	 * 新增处理
	 * */
	@Override
	public int addDept(Dept dept) {
		String deptname=dept.getDeptname().trim();
		String fdeptcode=dept.getFdeptcode().trim();		
		/**
		 * 根据上级部门code。获得上级部门对象
		 * */		
		Dept deptemp=this.deptDao.getDept(fdeptcode);
		/**
		 * 通过上级部门全称加本级名称拼接全称名称
		 * */
		String fulldeptname=deptemp.getDeptfullname();		
		String fullnametemp="";
		if(fulldeptname!=null&&!"".equals(fulldeptname)){
			fullnametemp=fulldeptname+"/"+deptname;			
		}else{
			fullnametemp="/"+deptname;
		}
		dept.setDeptfullname(fullnametemp);
		/**
		 * 上级部门级别加1得到本级部门级别
		 */
		int deptlevel =0;
		if(deptemp!=null){
			Integer i=deptemp.getDeptlevel();
			
			deptlevel =(i!=null?i:0)+1;
		}else{
			deptlevel=1;
		}		
		dept.setDeptlevel(deptlevel);
		
		/**
		 * 通过fdeptcode,deptlevel 获取deptcode
		 */
		String deptcode=this.Deptcode(fdeptcode, deptlevel);
		dept.setDeptcode(deptcode);
		
		/**
		 * 最近一次更新时间
		 */
		SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMddHHmmss");		
		dept.setLastsaved(sdf.format(new Date()));
		
		return this.deptDao.addDept(dept);
	}
	
	public String Deptcode(String fdeptcode,int deptlevel){
		String code=null;
		/**
		 * 通过fdeptcode,deptlevel;得到同级别部门最大值的后三位,得到tempmax 值
		 * tempmax 值 为0则赋值为100；不为0则自增
		 * 通过级别判断是不是根节点的
		 * 不是根节点则由fdeptcode和tempmax拼接作为code值
		 * 是根节点则取tempmax值
		 * */		
		int tempmax=this.deptDao.getDeptcode(fdeptcode);			
		if(tempmax!=0){
			tempmax++;
		}else{
			tempmax=100;
		}		
		if(deptlevel>1){
			code=fdeptcode+String.valueOf(tempmax);			
		}else{	
			code=String.valueOf(tempmax);	
		}
		return code;
	}
	/**
	 * 删除
	 * */
	@Override
	public int deleDept(String deptcode) {
		
		return this.deptDao.deleDept(deptcode);
	}

	/**
	 * 根据code查询是否存在记录
	 * */
	@Override
	public boolean isExitDept(String deptcode) {
		return this.deptDao.isExitDept(deptcode);
	}

	/**
	 * 根据code和name查询是否存在重复name
	 * */
	@Override
	public boolean isExitDeptName(String deptcode,String deptname) {
		return this.deptDao.isExitDeptName(deptcode,deptname);
	}

	/**
	 * 根据code判断是否是根节点
	 * */
	@Override
	public boolean isFarDept(String deptcode) {
		return this.deptDao.isFarDept(deptcode);
	}

	/**
	 * 根据fdeptcode判断是否存在下级部门
	 * */
	@Override
	public boolean isExistSonDept(String fdeptcode) {
		return this.deptDao.isExistSonDept(fdeptcode);
	}
	/**
	 * 更新
	 * */
	@Override
	public int updateDept(Dept dept) {
		String deptname=dept.getDeptname().trim();
		String fdeptcode=dept.getFdeptcode().trim();		
		/**
		 * 根据上级部门code。获得上级部门对象
		 * */		
		Dept deptemp=this.deptDao.getDept(fdeptcode);
		/**
		 * 通过上级部门全称加本级名称拼接全称名称
		 * */
		String fulldeptname=deptemp.getDeptfullname().trim();		
		String fullnametemp=fulldeptname+"/"+deptname;
		dept.setDeptfullname(fullnametemp);
		
		/**
		 * 最近保存时间
		 */
		SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMddHHmmss");	
		dept.setLastsaved(sdf.format(new Date()));
		return this.deptDao.updateDept(dept);
	}

}
