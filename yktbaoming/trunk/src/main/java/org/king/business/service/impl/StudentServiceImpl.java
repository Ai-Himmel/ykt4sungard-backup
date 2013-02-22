package org.king.business.service.impl;

import java.sql.Types;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Date;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

import org.apache.poi.hssf.usermodel.HSSFRow;
import org.apache.poi.hssf.usermodel.HSSFSheet;
import org.king.business.domain.BmStuBm;
import org.king.business.domain.BmStudent;
import org.king.business.domain.BmTest;
import org.king.business.domain.StuTestUpdate;
import org.king.business.service.StudentService;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.framework.exception.BusinessException;
import org.king.security.dao.AccountDAO;
import org.king.security.dao.RoleDAO;
import org.king.security.domain.Account;
import org.king.security.domain.Person;
import org.king.security.domain.Role;
import org.king.utils.DateUtil;
import org.king.web.util.Constants;

public class StudentServiceImpl implements StudentService {
	

	private BaseDAO baseDAO;
	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}
	
	private AccountDAO accountDAO;	
	public void setAccountDAO(AccountDAO accountDAO) {
		this.accountDAO = accountDAO;
	}
	
	private RoleDAO roleDAO;	
	public void setRoleDAO(RoleDAO roleDAO) {
		this.roleDAO = roleDAO;
	}
	
	public List   getfeeTestList(Map  m,String startpage){
		MyQuery mq=new MyQuery();
		StringBuffer  sql = new StringBuffer("");                                                                                            
		sql.append(" select new Map ( a.id as id ,a.bmStudent.studentNo as  studentNo ,a.bmStudent.stuName as stuName ,a.oldBmTest.bmTestCat.testCatName  as oldtest , a.newBmTest.bmTestCat.testCatName as newtest ,")
		   .append(" a.updateTime  as  updateTime  )from  StuTestUpdate  a where 1=1 ")
		   .append(" and  a.updator='"+m.get("operator")+"'");
		/*sql.append(" select new Map ( a.id as id  )from  StuTestUpdate  a where 1=1 ");*/
		if(m.get("studentno")!=null&&!((String)m.get("studentno")).equals("")){
			sql.append(" and a.bmStudent.studentNo like ? ");
			mq.addPara("%"+(String)m.get("studentno")+"%",Types.VARCHAR);
		}
		if(m.get("stuname")!=null&&!((String)m.get("stuname")).equals("")){
			sql.append(" and a.bmStudent.stuName like ? ");
			mq.addPara("%"+(String)m.get("stuname")+"%",Types.VARCHAR);
		}
		if(m.get("oldtestId")!=null&&!((String)m.get("oldtestId")).equals("")){
			sql.append(" and a.oldBmTest.id=? ");
			mq.addPara((String)m.get("oldtestId"),Types.VARCHAR);
		}
		if(m.get("newtestId")!=null&&!((String)m.get("newtestId")).equals("")){
			sql.append(" and a.newBmTest.id=? ");
			mq.addPara((String)m.get("newtestId"),Types.VARCHAR);
		}
		mq.setOrderby("order by a.updateTime desc ");
		mq.setQueryString(sql.toString());
		mq.setPageStartNo(Integer.parseInt(startpage));
		mq.setOffset(true);
		List li= baseDAO.findEntity(mq);
		return li;
	}
	
	public Integer  getfeeTestCount(Map m){
		MyQuery mq=new MyQuery();
		Integer feeTestCount=new Integer(0);
		StringBuffer  sql = new StringBuffer("");
		sql.append(" select count(a.id)  ")
		   .append(" from  StuTestUpdate  a where 1=1 ")
		   .append(" and  a.updator='"+m.get("operator")+"'");
		if(m.get("studentno")!=null&&!((String)m.get("studentno")).equals("")){
			sql.append(" and a.bmStudent.studentNo like ? ");
			mq.addPara("%"+(String)m.get("studentno")+"%",Types.VARCHAR);
		}
		if(m.get("stuname")!=null&&!((String)m.get("stuname")).equals("")){
			sql.append(" and a.bmStudent.stuName like ? ");
			mq.addPara("%"+(String)m.get("stuname")+"%",Types.VARCHAR);
		}
		if(m.get("oldtestId")!=null&&!((String)m.get("oldtestId")).equals("")){
			sql.append(" and a.oldBmTest.id=? ");
			mq.addPara((String)m.get("oldtestId"),Types.VARCHAR);
		}
		if(m.get("newtestId")!=null&&!((String)m.get("newtestId")).equals("")){
			sql.append(" and a.newBmTest.id=? ");
			mq.addPara((String)m.get("newtestId"),Types.VARCHAR);
		}
		mq.setQueryString(sql.toString());
        List li= baseDAO.findEntity(mq);
		
		if(li!=null&&li.size()>0)
			feeTestCount = (Integer) li.get(0);
		return feeTestCount;
		
	}
	
	
	public BmStudent getDetail(String studentNo){
		BmStudent bmStudent=null;
		List li=baseDAO.findEntity("select a from BmStudent a where a.studentNo='"+studentNo+"'");
		if(li!=null&&li.size()>0){
			bmStudent=(BmStudent)li.get(0);
		}		
		return bmStudent;
	}
	
	public BmStuBm getStuBmDetail(String id){
		BmStuBm bmStubm=null;
		try{
		
		List li=baseDAO.findEntity("select a from BmStuBm a where a.id='"+id+"'");
		if(li!=null&&li.size()>0){
		    bmStubm=(BmStuBm)li.get(0);
		}
		}catch(Exception e){
			
			e.printStackTrace();
		}
		return bmStubm;
	}
	
    public List getList(Map m,String startpage) {
		StringBuffer sbhql=new StringBuffer("");
		StringBuffer sWhere=new StringBuffer("");
		List li=new ArrayList();
		MyQuery mq=new MyQuery();
		
		sbhql.append(" select new Map(a.id as id,a.bmStudent.studentNo as studentNo,a.bmStudent.stuName as stuName,a.bmStudent.gender as gender,a.bmStudent.enrollYear as enrollYear," +
				"a.deptName as deptName,a.majorName as majorName,a.curGrade as curGrade,a.curClass as curClass,a.bmStudent.idType as idType,a.bmStudent.idCard as idCard,a.bmStudent.email as email" +
				",a.bmTest.bmTestCat.testCatName as testCatName,(a.bmTest.bmTestCat.testCatName||' '||a.bmTest.testDate||' '||a.bmTest.testBeginTime||'---'||a.bmTest.testEndTime) as testInfo,a.bmTest.bmTestCat.ifFee as ifFee,a.bmTest.bmTestCat.fee as fee" +
				",a.ifBm as ifBm,a.bmTime as bmTime,a.ifPay as ifPay,a.feePayed as feePayed,a.grades as grades,a.updator as updator,a.updateTime as updateTime " +
				",a.bmDepartment.deptCode as deptCode,a.bmMajor.majorCode as majorCode " +
				" ) from BmStuBm a  where 1=1  and  a.updator='"+m.get("operator")+"'");
		if(m.get("search_studentno")!=null&&!((String)m.get("search_studentno")).equals("")){
			sWhere.append(" and a.bmStudent.studentNo like ? ");
			mq.addPara("%"+(String)m.get("search_studentno")+"%",Types.VARCHAR);
		}
		if(m.get("search_stuname")!=null&&!((String)m.get("search_stuname")).equals("")){
			sWhere.append(" and a.bmStudent.stuName like ? ");
			mq.addPara("%"+(String)m.get("search_stuname")+"%",Types.VARCHAR);
		}
		if(m.get("search_deptname")!=null&&!((String)m.get("search_deptname")).equals("")){
			sWhere.append(" and a.deptName like ? ");
			mq.addPara("%"+(String)m.get("search_deptname")+"%",Types.VARCHAR);
		}
		if(m.get("search_majorname")!=null&&!((String)m.get("search_majorname")).equals("")){
			sWhere.append(" and a.majorName like ? ");
			mq.addPara("%"+(String)m.get("search_majorname")+"%",Types.VARCHAR);
		}
		if(m.get("search_curgrade")!=null&&!((String)m.get("search_curgrade")).equals("")){
			sWhere.append(" and a.curGrade like ? ");
			mq.addPara("%"+(String)m.get("search_curgrade")+"%",Types.VARCHAR);
		}
		if(m.get("search_curclass")!=null&&!((String)m.get("search_curclass")).equals("")){
			sWhere.append(" and a.curClass like ? ");
			mq.addPara("%"+(String)m.get("search_curclass")+"%",Types.VARCHAR);
		}
		if(m.get("search_idtype")!=null&&!((String)m.get("search_idtype")).equals("")){
			sWhere.append(" and a.bmStudent.idType like ? ");
			mq.addPara("%"+(String)m.get("search_idtype")+"%",Types.VARCHAR);
		}
		if(m.get("search_idcard")!=null&&!((String)m.get("search_idcard")).equals("")){
			sWhere.append(" and a.bmStudent.idCard like ? ");
			mq.addPara("%"+(String)m.get("search_idcard")+"%",Types.VARCHAR);
		}
		if(m.get("search_testcatname")!=null&&!((String)m.get("search_testcatname")).equals("")){
			sWhere.append(" and a.bmTest.bmTestCat.testCatName like ? ");
			mq.addPara("%"+(String)m.get("search_testcatname")+"%",Types.VARCHAR);
		}	
		if(m.get("search_testid")!=null&&!((String)m.get("search_testid")).equals("")){
			sWhere.append(" and a.bmTest.id=? ");
			mq.addPara((String)m.get("search_testid"),Types.VARCHAR);
		}
		if(m.get("search_ifbm")!=null&&!((String)m.get("search_ifbm")).equals("")&&((String)m.get("search_ifbm")).equals(Constants.yesCode)){
			sWhere.append(" and a.ifBm='"+Constants.yesCode+"' ");
		}
		else if(m.get("search_ifbm")!=null&&!((String)m.get("search_ifbm")).equals("")&&((String)m.get("search_ifbm")).equals(Constants.noCode)){
			sWhere.append(" and (a.ifBm<>'"+Constants.yesCode+"' or a.ifBm is null) ");
		}
		if(m.get("search_ifpay")!=null&&!((String)m.get("search_ifpay")).equals("")&&((String)m.get("search_ifpay")).equals(Constants.yesCode)){
			sWhere.append(" and a.ifPay='"+Constants.yesCode+"' ");
		}
		else if(m.get("search_ifpay")!=null&&!((String)m.get("search_ifpay")).equals("")&&((String)m.get("search_ifpay")).equals(Constants.noCode)){
			sWhere.append(" and (a.ifPay<>'"+Constants.yesCode+"' or a.ifPay is null) ");
		}
		if(m.get("search_afterdate")!=null&&!((String)m.get("search_afterdate")).equals("")){
			sWhere.append(" and (a.bmTest.testDate is null or a.bmTest.testDate='' or a.bmTest.testDate> ?) ");
			mq.addPara((String)m.get("search_afterdate"),Types.VARCHAR);
		}
		
		//sWhere.append(" order by a.bmStudent.studentNo ");

		mq.setOrderby(" order by a.bmStudent.studentNo ");
		mq.setQueryString(sbhql.append(sWhere).toString());
		mq.setPageStartNo(Integer.parseInt(startpage));
		mq.setOffset(true);
		
		li= baseDAO.findEntity(mq);
		
		if(li!=null&&li.size()>0)
			changeIfBmPayName(li);
		        		
		return li;
	}
    
    public Integer getStudentCount(Map m) {
		StringBuffer sbhql=new StringBuffer("");
		StringBuffer sWhere=new StringBuffer("");
		Integer stuCount = new Integer("0");
		List li=new ArrayList();
		MyQuery mq=new MyQuery();
		
		sbhql.append(" select count(a.id)" +
				" from BmStuBm a where 1=1 ");
		if(m.get("search_studentno")!=null&&!((String)m.get("search_studentno")).equals("")){
			sWhere.append(" and a.bmStudent.studentNo like ? ");
			mq.addPara("%"+(String)m.get("search_studentno")+"%",Types.VARCHAR);
		}
		if(m.get("search_stuname")!=null&&!((String)m.get("search_stuname")).equals("")){
			sWhere.append(" and a.bmStudent.stuName like ? ");
			mq.addPara("%"+(String)m.get("search_stuname")+"%",Types.VARCHAR);
		}
		if(m.get("search_deptname")!=null&&!((String)m.get("search_deptname")).equals("")){
			sWhere.append(" and a.bmStudent.deptName like ? ");
			mq.addPara("%"+(String)m.get("search_deptname")+"%",Types.VARCHAR);
		}
		if(m.get("search_majorname")!=null&&!((String)m.get("search_majorname")).equals("")){
			sWhere.append(" and a.bmStudent.majorName like ? ");
			mq.addPara("%"+(String)m.get("search_majorname")+"%",Types.VARCHAR);
		}
		if(m.get("search_curgrade")!=null&&!((String)m.get("search_curgrade")).equals("")){
			sWhere.append(" and a.bmStudent.curGrade like ? ");
			mq.addPara("%"+(String)m.get("search_curgrade")+"%",Types.VARCHAR);
		}
		if(m.get("search_curclass")!=null&&!((String)m.get("search_curclass")).equals("")){
			sWhere.append(" and a.bmStudent.curClass like ? ");
			mq.addPara("%"+(String)m.get("search_curclass")+"%",Types.VARCHAR);
		}
		if(m.get("search_idtype")!=null&&!((String)m.get("search_idtype")).equals("")){
			sWhere.append(" and a.bmStudent.idType like ? ");
			mq.addPara("%"+(String)m.get("search_idtype")+"%",Types.VARCHAR);
		}
		if(m.get("search_idcard")!=null&&!((String)m.get("search_idcard")).equals("")){
			sWhere.append(" and a.bmStudent.idCard like ? ");
			mq.addPara("%"+(String)m.get("search_idcard")+"%",Types.VARCHAR);
		}
		if(m.get("search_testcatname")!=null&&!((String)m.get("search_testcatname")).equals("")){
			sWhere.append(" and a.bmTest.bmTestCat.testCatName like ? ");
			mq.addPara("%"+(String)m.get("search_testcatname")+"%",Types.VARCHAR);
		}	
		if(m.get("search_testid")!=null&&!((String)m.get("search_testid")).equals("")){
			sWhere.append(" and a.bmTest.id=? ");
			mq.addPara((String)m.get("search_testid"),Types.VARCHAR);
		}
		if(m.get("search_ifbm")!=null&&!((String)m.get("search_ifbm")).equals("")&&((String)m.get("search_ifbm")).equals(Constants.yesCode)){
			sWhere.append(" and a.ifBm='"+Constants.yesCode+"' ");
		}
		else if(m.get("search_ifbm")!=null&&!((String)m.get("search_ifbm")).equals("")&&((String)m.get("search_ifbm")).equals(Constants.noCode)){
			sWhere.append(" and (a.ifBm<>'"+Constants.yesCode+"' or a.ifBm is null) ");
		}
		if(m.get("search_ifpay")!=null&&!((String)m.get("search_ifpay")).equals("")&&((String)m.get("search_ifpay")).equals(Constants.yesCode)){
			sWhere.append(" and a.ifPay='"+Constants.yesCode+"' ");
		}
		else if(m.get("search_ifpay")!=null&&!((String)m.get("search_ifpay")).equals("")&&((String)m.get("search_ifpay")).equals(Constants.noCode)){
			sWhere.append(" and (a.ifPay<>'"+Constants.yesCode+"' or a.ifPay is null) ");
		}
		if(m.get("search_afterdate")!=null&&!((String)m.get("search_afterdate")).equals("")){
			sWhere.append(" and (a.bmTest.testDate is null or a.bmTest.testDate='' or a.bmTest.testDate> ?) ");
			mq.addPara((String)m.get("search_afterdate"),Types.VARCHAR);
		}
		
		mq.setQueryString(sbhql.append(sWhere).toString());
		
		li= baseDAO.findEntity(mq);
		
		if(li!=null&&li.size()>0)
			stuCount = (Integer) li.get(0);
		
		return stuCount;
	}
    
    public List getList(Map m) {
		StringBuffer sbhql=new StringBuffer("");
		StringBuffer sWhere=new StringBuffer("");
		List li=new ArrayList();
		MyQuery mq=new MyQuery();
		
		sbhql.append(" select new Map(a.id as id,a.bmStudent.studentNo as studentNo,a.bmStudent.stuName as stuName,a.bmStudent.gender as gender,a.bmStudent.enrollYear as enrollYear," +
				"a.deptName as deptName,a.majorName as majorName,a.curGrade as curGrade,a.curClass as curClass,a.bmStudent.idType as idType,a.bmStudent.idCard as idCard,a.bmStudent.email as email," +
				"a.bmTest.bmTestCat.testCatName as testCatName,(a.bmTest.bmTestCat.testCatName||' '||a.bmTest.testDate||' '||a.bmTest.testBeginTime||'---'||a.bmTest.testEndTime) as testInfo,a.bmTest.bmTestCat.ifFee as ifFee,a.bmTest.bmTestCat.fee as fee,a.ifBm as ifBm,a.bmTime as bmTime,a.ifPay as ifPay,a.feePayed as feePayed,a.grades as grades,a.updator as updator,a.updateTime as updateTime, " +
				"a.bmDepartment.deptCode as deptNo,a.bmMajor.majorCode as majorCode" +
				" ) from BmStuBm a where 1=1  ");
		if(m.get("search_studentno")!=null&&!((String)m.get("search_studentno")).equals("")){
			sWhere.append(" and a.bmStudent.studentNo like ? ");
			mq.addPara("%"+(String)m.get("search_studentno")+"%",Types.VARCHAR);
		}
		if(m.get("search_stuname")!=null&&!((String)m.get("search_stuname")).equals("")){
			sWhere.append(" and a.bmStudent.stuName like ? ");
			mq.addPara("%"+(String)m.get("search_stuname")+"%",Types.VARCHAR);
		}
		if(m.get("search_deptname")!=null&&!((String)m.get("search_deptname")).equals("")){
			sWhere.append(" and a.deptName like ? ");
			mq.addPara("%"+(String)m.get("search_deptname")+"%",Types.VARCHAR);
		}
		if(m.get("search_majorname")!=null&&!((String)m.get("search_majorname")).equals("")){
			sWhere.append(" and a.majorName like ? ");
			mq.addPara("%"+(String)m.get("search_majorname")+"%",Types.VARCHAR);
		}
		if(m.get("search_curgrade")!=null&&!((String)m.get("search_curgrade")).equals("")){
			sWhere.append(" and a.curGrade like ? ");
			mq.addPara("%"+(String)m.get("search_curgrade")+"%",Types.VARCHAR);
		}
		if(m.get("search_curclass")!=null&&!((String)m.get("search_curclass")).equals("")){
			sWhere.append(" and a.curClass like ? ");
			mq.addPara("%"+(String)m.get("search_curclass")+"%",Types.VARCHAR);
		}
		if(m.get("search_idtype")!=null&&!((String)m.get("search_idtype")).equals("")){
			sWhere.append(" and a.bmStudent.idType like ? ");
			mq.addPara("%"+(String)m.get("search_idtype")+"%",Types.VARCHAR);
		}
		if(m.get("search_idcard")!=null&&!((String)m.get("search_idcard")).equals("")){
			sWhere.append(" and a.bmStudent.idCard like ? ");
			mq.addPara("%"+(String)m.get("search_idcard")+"%",Types.VARCHAR);
		}
		if(m.get("search_testcatname")!=null&&!((String)m.get("search_testcatname")).equals("")){
			sWhere.append(" and a.bmTest.bmTestCat.testCatName like ? ");
			mq.addPara("%"+(String)m.get("search_testcatname")+"%",Types.VARCHAR);
		}	
		if(m.get("search_testid")!=null&&!((String)m.get("search_testid")).equals("")){
			sWhere.append(" and a.bmTest.id=? ");
			mq.addPara((String)m.get("search_testid"),Types.VARCHAR);
		}
		if(m.get("search_ifbm")!=null&&!((String)m.get("search_ifbm")).equals("")&&((String)m.get("search_ifbm")).equals(Constants.yesCode)){
			sWhere.append(" and a.ifBm='"+Constants.yesCode+"' ");
		}
		else if(m.get("search_ifbm")!=null&&!((String)m.get("search_ifbm")).equals("")&&((String)m.get("search_ifbm")).equals(Constants.noCode)){
			sWhere.append(" and (a.ifBm<>'"+Constants.yesCode+"' or a.ifBm is null) ");
		}
		if(m.get("search_ifpay")!=null&&!((String)m.get("search_ifpay")).equals("")&&((String)m.get("search_ifpay")).equals(Constants.yesCode)){
			sWhere.append(" and a.ifPay='"+Constants.yesCode+"' ");
		}
		else if(m.get("search_ifpay")!=null&&!((String)m.get("search_ifpay")).equals("")&&((String)m.get("search_ifpay")).equals(Constants.noCode)){
			sWhere.append(" and (a.ifPay<>'"+Constants.yesCode+"' or a.ifPay is null) ");
		}
		
		if(m.get("search_afterdate")!=null&&!((String)m.get("search_afterdate")).equals("")){
			sWhere.append(" and (a.bmTest.testDate is null or a.bmTest.testDate='' or a.bmTest.testDate> ?) ");
			mq.addPara((String)m.get("search_afterdate"),Types.VARCHAR);
		}
		
		sWhere.append(" order by a.bmStudent.studentNo ");

		mq.setQueryString(sbhql.append(sWhere).toString());
		
		li= baseDAO.findEntity(mq);
		
		if(li!=null&&li.size()>0)
			changeIfBmPayName(li);
		        		
		return li;
	}
    public List getnewaddList(Map m) {
		StringBuffer sbhql=new StringBuffer("");
		StringBuffer sWhere=new StringBuffer("");
		List li=new ArrayList();
		List oli=new ArrayList();
		MyQuery mq=new MyQuery();
		
		if(m.get("newidstring")!=null&&!((String)m.get("newidstring")).equals("")){
			
			String newids=(String)m.get("newidstring");
			
			sbhql.append(" select new Map(a.id as id,a.bmStudent.studentNo as studentNo,a.bmStudent.stuName as stuName,a.bmStudent.gender as gender,a.bmStudent.enrollYear as enrollYear,a.bmStudent.deptName as deptName,a.bmStudent.majorName as majorName,a.bmStudent.curGrade as curGrade,a.bmStudent.curClass as curClass,a.bmStudent.idType as idType,a.bmStudent.idCard as idCard,a.bmStudent.email as email,a.bmTest.bmTestCat.testCatName as testCatName,a.ifBm as ifBm,a.bmTime as bmTime,a.ifPay as ifPay,a.feePayed as feePayed,a.grades as grades,a.updator as updator,a.updateTime as updateTime) from BmStuBm a where 1=1 ");
								
			sWhere.append(" and a.id in ("+newids+") ");		    		
			
			sWhere.append(" order by a.updateTime desc ");
			mq.setQueryString(sbhql.append(sWhere).toString());        
			
			li= baseDAO.findEntity(mq);
		}
		
		sbhql=new StringBuffer("");
		sWhere=new StringBuffer("");
		mq=new MyQuery();
		
		sbhql.append(" select new Map(a.id as id,a.bmStudent.studentNo as studentNo,a.bmStudent.stuName as stuName,a.bmStudent.gender as gender,a.bmStudent.enrollYear as enrollYear,a.bmStudent.deptName as deptName,a.bmStudent.majorName as majorName,a.bmStudent.curGrade as curGrade,a.bmStudent.curClass as curClass,a.bmStudent.idType as idType,a.bmStudent.idCard as idCard,a.bmStudent.email as email,a.bmTest.bmTestCat.testCatName as testCatName,a.ifBm as ifBm,a.bmTime as bmTime,a.ifPay as ifPay,a.feePayed as feePayed,a.grades as grades,a.updator as updator,a.updateTime as updateTime) from BmStuBm a where 1=1 ");
		
		if(m.get("newidstring")!=null&&!((String)m.get("newidstring")).equals("")){
			String newids=(String)m.get("newidstring");
			sWhere.append(" and a.id not in ("+newids+") ");			
		}		
		
		sWhere.append(" order by a.bmStudent.studentNo ");
		mq.setQueryString(sbhql.append(sWhere).toString());        
		
		oli= baseDAO.findEntity(mq);
						
		if(oli!=null&&oli.size()>0){
			for(int i=0;i<oli.size();i++){
				li.add(li.size(),oli.get(i));				
			}
		}
		
		if(li!=null&&li.size()>0)
			changeIfBmPayName(li);
						
		return li;
	}
    
    public List gethistoryList(Map m) {
		StringBuffer sbhql=new StringBuffer("");
		StringBuffer sWhere=new StringBuffer("");
		List li=new ArrayList();
		MyQuery mq=new MyQuery();
		
		sbhql.append(" select new Map(a.id as id,a.bmStudent.studentNo as studentNo,a.bmStudent.stuName as stuName,a.bmStudent.gender as gender,a.bmStudent.enrollYear as enrollYear," +
				"a.deptName as deptName,a.majorName as majorName,a.curGrade as curGrade,a.curClass as curClass,a.bmStudent.idType as idType,a.bmStudent.idCard as idCard,a.bmStudent.email as email," +
				"(a.bmTest.bmTestCat.testCatName||' '||a.bmTest.testDate||' '||a.bmTest.testBeginTime||'---'||a.bmTest.testEndTime) as testInfo,a.updator as updator,a.updateTime as updateTime)" +
				" from BmStuBm a where 1=1 and a.bmTest.testDate<'"+DateUtil.getNow("yyyy-MM-dd")+"'");
			
		if(m.get("search_testid")!=null&&!((String)m.get("search_testid")).equals("")){
			sWhere.append(" and a.bmTest.id=? ");
			mq.addPara((String)m.get("search_testid"),Types.VARCHAR);
		}
				
		sWhere.append(" order by a.bmStudent.studentNo ");
		
		mq.setQueryString(sbhql.append(sWhere).toString());
		
		li= baseDAO.findEntity(mq);
		
		if(li!=null&&li.size()>0)
			changeIfBmPayName(li);
		        		
		return li;
	}
    
    public List gethistoryList(Map m,String startpage) {
		StringBuffer sbhql=new StringBuffer("");
		StringBuffer sWhere=new StringBuffer("");
		List li=new ArrayList();
		MyQuery mq=new MyQuery();
		
		sbhql.append(" select new Map(a.id as id,a.bmStudent.studentNo as studentNo,a.bmStudent.stuName as stuName,a.bmStudent.gender as gender,a.bmStudent.enrollYear as enrollYear," +
				"a.bmStudent.deptName as deptName,a.bmStudent.majorName as majorName,a.bmStudent.curGrade as curGrade,a.bmStudent.curClass as curClass,a.bmStudent.idType as idType,a.bmStudent.idCard as idCard,a.bmStudent.email as email," +
				"(a.bmTest.bmTestCat.testCatName||' '||a.bmTest.testDate||' '||a.bmTest.testBeginTime||'---'||a.bmTest.testEndTime) as testInfo,a.updator as updator,a.updateTime as updateTime)" +
				" from BmStuBm a where 1=1 and a.bmTest.testDate<'"+DateUtil.getNow("yyyy-MM-dd")+"'")
			 .append(" and  a.updator='"+m.get("operator")+"'");
			
		if(m.get("search_testid")!=null&&!((String)m.get("search_testid")).equals("")){
			sWhere.append(" and a.bmTest.id=? ");
			mq.addPara((String)m.get("search_testid"),Types.VARCHAR);
		}
				
		mq.setOrderby(" order by a.bmStudent.studentNo ");
		
		mq.setQueryString(sbhql.append(sWhere).toString());
		mq.setPageStartNo(Integer.parseInt(startpage));
		mq.setOffset(true);
		
		li= baseDAO.findEntity(mq);
		
		if(li!=null&&li.size()>0)
			changeIfBmPayName(li);
		        		
		return li;
	}
    
    public Integer gethistoryCount(Map m) {
		StringBuffer sbhql=new StringBuffer("");
		StringBuffer sWhere=new StringBuffer("");
		Integer stuCount = new Integer("0");
		List li=new ArrayList();
		MyQuery mq=new MyQuery();
		
		sbhql.append(" select count(a.id)" +
				" from BmStuBm a where 1=1 and a.bmTest.testDate<'"+DateUtil.getNow("yyyy-MM-dd")+"'")
				.append(" and  a.updator='"+m.get("operator")+"'");
			
		if(m.get("search_testid")!=null&&!((String)m.get("search_testid")).equals("")){
			sWhere.append(" and a.bmTest.id=? ");
			mq.addPara((String)m.get("search_testid"),Types.VARCHAR);
		}
		
		mq.setQueryString(sbhql.append(sWhere).toString());
		
		li= baseDAO.findEntity(mq);
		
		if(li!=null&&li.size()>0)
            stuCount = (Integer) li.get(0);
		
		return stuCount;
	}
    
    public List getBMTongji(){
    	
    	String sqlstring="";
    	String nowstr=DateUtil.getNow("yyyy-MM-dd");
		List li=null;
		List bmli=null;
		List notbmli=null;
		List payli=null;
		List notpayli=null;
		
		sqlstring="select new Map(count(a.id) as stuNum,a.bmTest.id as testId) from BmStuBm a where a.bmTest.testDate is null or a.bmTest.testDate='' or a.bmTest.testDate>'"+nowstr+"' group by a.bmTest.id order by a.bmTest.id ";
		li= baseDAO.findEntity(sqlstring);
		
		sqlstring="select new Map(count(a.id) as bmNum,a.bmTest.id as testId) from BmStuBm a where (a.bmTest.testDate is null or a.bmTest.testDate='' or a.bmTest.testDate>'"+nowstr+"') and a.ifBm='"+Constants.yesCode+"' group by a.bmTest.id order by a.bmTest.id ";
		bmli= baseDAO.findEntity(sqlstring);
		
		sqlstring="select new Map(count(a.id) as notbmNum,a.bmTest.id as testId) from BmStuBm a where (a.bmTest.testDate is null or a.bmTest.testDate='' or a.bmTest.testDate>'"+nowstr+"') and (a.ifBm is null or a.ifBm!='"+Constants.yesCode+"') group by a.bmTest.id order by a.bmTest.id ";
		notbmli= baseDAO.findEntity(sqlstring);
		
		sqlstring="select new Map(count(a.id) as payNum,a.bmTest.id as testId) from BmStuBm a where (a.bmTest.testDate is null or a.bmTest.testDate='' or a.bmTest.testDate>'"+nowstr+"') and a.ifBm='"+Constants.yesCode+"' and a.ifPay='"+Constants.yesCode+"' group by a.bmTest.id order by a.bmTest.id ";
		payli= baseDAO.findEntity(sqlstring);
		
		sqlstring="select new Map(count(a.id) as notpayNum,a.bmTest.id as testId) from BmStuBm a where (a.bmTest.testDate is null or a.bmTest.testDate='' or a.bmTest.testDate>'"+nowstr+"') and a.ifBm='"+Constants.yesCode+"' and (a.ifPay is null or a.ifPay!='"+Constants.yesCode+"') group by a.bmTest.id order by a.bmTest.id ";
		notpayli= baseDAO.findEntity(sqlstring);	
		
		HashMap bmMap=new HashMap();
		if(bmli!=null&&bmli.size()>0){
			for (int i = 0; i < bmli.size(); i++) {
				HashMap temp = (HashMap) bmli.get(i);
				bmMap.put(temp.get("testId"), temp
						.get("bmNum"));
		 }
		}
		HashMap notbmMap=new HashMap();
		if(notbmli!=null&&notbmli.size()>0){
			for (int i = 0; i < notbmli.size(); i++) {
				HashMap temp = (HashMap) notbmli.get(i);
				notbmMap.put(temp.get("testId"), temp
						.get("notbmNum"));
		 }
		}
		
		HashMap payMap=new HashMap();
		if(payli!=null&&payli.size()>0){
			for (int i = 0; i < payli.size(); i++) {
				HashMap temp = (HashMap) payli.get(i);
				payMap.put(temp.get("testId"), temp
						.get("payNum"));
		 }
		}
		HashMap notpayMap=new HashMap();
		if(notpayli!=null&&notpayli.size()>0){
			for (int i = 0; i < notpayli.size(); i++) {
				HashMap temp = (HashMap) notpayli.get(i);
				notpayMap.put(temp.get("testId"), temp
						.get("notpayNum"));
		 }
		}
		
		List testli=baseDAO.findEntity("select new Map(a.id as testId,(a.bmTestCat.testCatName||' '||a.testDate||' '||a.testBeginTime||'---'||a.testEndTime) as testInfo) from BmTest a where a.testDate is null or a.testDate='' or a.testDate>'"+nowstr+"' ");
		HashMap testMap=new HashMap();
		if(testli!=null&&testli.size()>0){
			for (int i = 0; i < testli.size(); i++) {
				HashMap temp = (HashMap) testli.get(i);
				testMap.put(temp.get("testId"), temp
						.get("testInfo"));
		 }
		}
		
		if(li!=null&&li.size()>0){
			for(int i=0;i<li.size();i++){
				Map lim=(Map)li.get(i);
				String testid=(String)lim.get("testId");
				
				if(bmMap.get(testid)!=null)
					lim.put("bmNum",bmMap.get(testid));
				else
					lim.put("bmNum",new Integer(0));
				
				if(notbmMap.get(testid)!=null)
					lim.put("notbmNum",notbmMap.get(testid));
				else
					lim.put("notbmNum",new Integer(0));
				
				if(payMap.get(testid)!=null)
					lim.put("payNum",payMap.get(testid));
				else
					lim.put("payNum",new Integer(0));
				
				if(notpayMap.get(testid)!=null)
					lim.put("notpayNum",notpayMap.get(testid));
				else
					lim.put("notpayNum",new Integer(0));
				
				if(testMap.get(testid)!=null)
					lim.put("testInfo",testMap.get(testid));
				else
					lim.put("testInfo","");
			}
			
            //按考试排序
			Comparator comp1 = new Comparator() { 
				 public int compare(Object o1, Object o2){ 
				 Map m1 = (Map)o1; 
				 Map m2 = (Map)o2; 
				 String curName1 = (String)m1.get("testInfo"); 
				 String curName2 = (String)m2.get("testInfo");      				

				com.ibm.icu.text.Collator collator = com.ibm.icu.text.Collator.getInstance(java.util.Locale.CHINA);
				com.ibm.icu.text.CollationKey c1= collator.getCollationKey(curName1);
				com.ibm.icu.text.CollationKey c2= collator.getCollationKey(curName2);
	            //注意,返回值是比较的结果>0,=0,或者<0
			     return collator.compare(c1.getSourceString(),c2.getSourceString());			 
				 } 
			} ;
			Collections.sort(li, comp1);
		}
		
		return li;
    }
    
    public List getBMTongjiTotal(){
    	
    	String sqlstring="";
    	String nowstr=DateUtil.getNow("yyyy-MM-dd");
    	List litotal=null;
		List bmlitotal=null;
		List notbmlitotal=null;
		List paylitotal=null;
		List notpaylitotal=null;
		
		sqlstring="select new Map(count(a.id) as stuNum) from BmStuBm a where a.bmTest.testDate is null or a.bmTest.testDate='' or a.bmTest.testDate>'"+nowstr+"' ";
		litotal= baseDAO.findEntity(sqlstring);
		
		sqlstring="select count(a.id) as bmNum from BmStuBm a where (a.bmTest.testDate is null or a.bmTest.testDate='' or a.bmTest.testDate>'"+nowstr+"') and a.ifBm='"+Constants.yesCode+"' ";
		bmlitotal= baseDAO.findEntity(sqlstring);
		
		sqlstring="select count(a.id) as notbmNum from BmStuBm a where (a.bmTest.testDate is null or a.bmTest.testDate='' or a.bmTest.testDate>'"+nowstr+"') and (a.ifBm is null or a.ifBm!='"+Constants.yesCode+"') ";
		notbmlitotal= baseDAO.findEntity(sqlstring);
		
		sqlstring="select count(a.id) as payNum from BmStuBm a where (a.bmTest.testDate is null or a.bmTest.testDate='' or a.bmTest.testDate>'"+nowstr+"') and a.ifBm='"+Constants.yesCode+"' and a.ifPay='"+Constants.yesCode+"' ";
		paylitotal= baseDAO.findEntity(sqlstring);
		
		sqlstring="select count(a.id) as notpayNum from BmStuBm a where (a.bmTest.testDate is null or a.bmTest.testDate='' or a.bmTest.testDate>'"+nowstr+"') and a.ifBm='"+Constants.yesCode+"' and (a.ifPay is null or a.ifPay!='"+Constants.yesCode+"') ";
		notpaylitotal= baseDAO.findEntity(sqlstring);	
		
		if(litotal!=null&&litotal.size()>0){
			Map limtotal=(Map)litotal.get(0);
			
			if(bmlitotal!=null&&bmlitotal.size()>0){
				Integer bmNum=(Integer)bmlitotal.get(0);
				limtotal.put("bmNum",bmNum);
			}
			else
				limtotal.put("bmNum",new Integer(0));
			
			if(notbmlitotal!=null&&notbmlitotal.size()>0){
				Integer notbmNum=(Integer)notbmlitotal.get(0);
				limtotal.put("notbmNum",notbmNum);
			}
			else
				limtotal.put("notbmNum",new Integer(0));
			
			if(paylitotal!=null&&paylitotal.size()>0){
				Integer payNum=(Integer)paylitotal.get(0);
				limtotal.put("payNum",payNum);
			}
			else
				limtotal.put("payNum",new Integer(0));
			
			if(notpaylitotal!=null&&notpaylitotal.size()>0){
				Integer notpayNum=(Integer)notpaylitotal.get(0);
				limtotal.put("notpayNum",notpayNum);
			}
			else
				limtotal.put("notpayNum",new Integer(0));
		}
		
		return litotal;
    }
    
    public List getStuBm4Update(String id){
    	
    	StringBuffer sbhql=new StringBuffer("");
		List li=new ArrayList();
		
		sbhql.append("select new Map(a.id as id,a.bmStudent.studentNo as studentNo,a.bmStudent.stuName as stuName,a.ifBm  as ifBm ,a.ifPay as ifPay ,a.bmStudent.gender as gender,a.bmStudent.enrollYear as enrollYear,a.deptName as deptName,a.majorName as majorName,a.curGrade as curGrade,a.curClass as curClass,a.bmStudent.idType as idType,a.bmStudent.idCard as idCard,a.bmStudent.email as email,a.bmTest.id as testId,(a.bmTest.bmTestCat.testCatName||' '||a.bmTest.testDate||' '||a.bmTest.testBeginTime||' '||a.bmTest.testEndTime) as testInfo) from BmStuBm a where 1=1 and a.id='"+id+"'");
				
		li= baseDAO.findEntity(sbhql.toString());
		return li;
    }
    
    public boolean save(StuTestUpdate  stuTestupdate){
    	baseDAO.saveEntity(stuTestupdate);
    	return true;
    }
    
    public boolean save(BmStudent bmStudent) {
		
		baseDAO.saveEntity(bmStudent);
		
		return true;
	}
	public boolean update(BmStudent bmStudent) {
				
		baseDAO.updateEntity(bmStudent);
		
        //修改Person表
		List personList=find("select a from Person a where a.personCode='"+bmStudent.getStudentNo()+"'");
		if(personList!=null&&personList.size()>0){
			Person psn=(Person)personList.get(0);
			psn.setPersonName(bmStudent.getStuName());
			baseDAO.updateEntity(psn);
		}
							
		return true;
	}
	public boolean delete(BmStudent bmStudent) {
		
		baseDAO.removeEntity(bmStudent);
	
		return true;
	}
	
    public String saveStuBm(BmStudent bmStudent,BmTest bmTest,String userId) throws Exception{
		
    	String resultstring="";
    	
		baseDAO.saveEntity(bmStudent);
		
		BmStuBm bmStuBm=new BmStuBm();
		bmStuBm.setBmStudent(bmStudent);
		bmStuBm.setBmTest(bmTest);
		bmStuBm.setUpdator(userId);
		//lizw 2009/6/5
		bmStuBm.setDeptName(bmStudent.getDeptName());
		bmStuBm.setMajorName(bmStudent.getMajorName());
		bmStuBm.setCurClass(bmStudent.getCurClass());
		bmStuBm.setCurGrade(bmStudent.getCurGrade());		
		//
		bmStuBm.setUpdateTime(DateUtil.getDateTime("yyyy-MM-dd HH:mm",new Date()));
		baseDAO.saveEntity(bmStuBm);
		
		resultstring=resultstring+"'"+bmStuBm.getId()+"'";
		
		BmTest bmTest4=null;
        //能报考六级的考生也能报考四级
		if(bmTest.getBmTestCat().getId().equals("e6")){			
			List test4li=baseDAO.findEntity("select a from BmTest a where a.bmTestCat.id='e4' and (a.testDate>'"+DateUtil.getNow("yyyy-MM-dd")+"' or a.testDate is null or a.testDate='') order by a.testDate ");
		    if(test4li!=null&&test4li.size()>0){
		    	bmTest4=(BmTest)test4li.get(0);
		    	BmStuBm bmStuBm4=new BmStuBm();
    			bmStuBm4.setBmStudent(bmStudent);
    			bmStuBm4.setBmTest(bmTest4);
    			bmStuBm4.setUpdator(userId);
    			//lizw 2009/6/4
    			bmStuBm4.setDeptName(bmStudent.getDeptName());
    			bmStuBm4.setMajorName(bmStudent.getMajorName());
    			bmStuBm4.setCurClass(bmStudent.getCurClass()); 
    			bmStuBm4.setCurGrade(bmStudent.getCurGrade());    			
    			bmStuBm4.setUpdateTime(DateUtil.getDateTime("yyyy-MM-dd HH:mm",new Date()));
    			baseDAO.saveEntity(bmStuBm4); 
    			
    			resultstring=resultstring+","+"'"+bmStuBm4.getId()+"'";
		    }		            			
		}//e6
		
        //生成该考生的登录数据
		List accountList=find("select a.name from Account a where a.name='"+bmStudent.getStudentNo()+"'");
		
		if(accountList==null||accountList.size()==0){
			
			String ksrole=getRoleidByName("考生");
			
			Person psn=new Person();						
			psn.setPersonCode(bmStudent.getStudentNo());
			if(bmStudent.getStuName()!=null)
			    psn.setPersonName(bmStudent.getStuName());
			else
				psn.setPersonName("");
			
			psn.setCreatedate(DateUtil.getNow().substring(0,8));
			psn.setLastdate(DateUtil.getNow().substring(0,8));
			
			Account act=new Account();
			act.setPerson(psn);
			act.setName(bmStudent.getStudentNo());
			
			accountDAO.save(act);
			
            //加考生角色权限
			List roleList = new ArrayList();
			String roleid =null;
			roleid=ksrole;
			if(roleid!=null&&roleid.length()>0)
				roleList.add(roleid);						
			String[] roleArr =  new String[roleList.size()];
			if(roleList!=null&&roleList.size()>0){
			  roleList.toArray(roleArr);
			  grantAccountRoles(act.getId(),roleArr);						  
			}
		}
		
		return resultstring;
	}
    
    public boolean check4Save(BmStudent bmStudent){
        //是否有重复学号
    	System.out.println("check4Save 检查是否有重复学号: "+bmStudent.getStudentNo());
    	String sqlstring="select a.studentNo from BmStudent a where a.studentNo='"+bmStudent.getStudentNo()+"'";
				
		List testList=baseDAO.findEntity(sqlstring);
		if(testList!=null&&testList.size()>0) {
			System.out.println("check4Save 存在 学号 '+bmStudent.getStudentNo()+' ! 返回 false ");
			return false;
		}
		else{
			sqlstring="select a from BmStudent a " +
			" where a.stuName='"+bmStudent.getStuName()+"'" +
			" and a.gender='"+bmStudent.getGender()+"'" +
			" and a.enrollYear='"+bmStudent.getEnrollYear()+"'" +
			" and a.deptName='"+bmStudent.getDeptName()+"'" +
			" and a.majorName='"+bmStudent.getMajorName()+"'" +
			" and a.curGrade='"+bmStudent.getCurGrade()+"'" +
			" and a.curClass='"+bmStudent.getCurClass()+"'" +
			" and a.idType='"+bmStudent.getIdType()+"'" +
			" and a.idCard='"+bmStudent.getIdCard()+"'" +
			" and a.email='"+bmStudent.getEmail()+"'";
			testList=baseDAO.findEntity(sqlstring);
			if(testList!=null&&testList.size()>0)
				return false;
			else
			    return true;
		}
	} 
    
    public boolean check4Update(BmStudent bmStudent){
		String sqlstring="select a from BmStudent a " +
				" where a.stuName='"+bmStudent.getStuName()+"'" +
				" and a.gender='"+bmStudent.getGender()+"'" +
				" and a.enrollYear='"+bmStudent.getEnrollYear()+"'" +
				" and a.deptName='"+bmStudent.getDeptName()+"'" +
				" and a.majorName='"+bmStudent.getMajorName()+"'" +
				" and a.curGrade='"+bmStudent.getCurGrade()+"'" +
				" and a.curClass='"+bmStudent.getCurClass()+"'" +
				" and a.idType='"+bmStudent.getIdType()+"'" +
				" and a.idCard='"+bmStudent.getIdCard()+"'" +
				" and a.email='"+bmStudent.getEmail()+"'";
		
		sqlstring=sqlstring+" and a.studentNo<>'"+bmStudent.getStudentNo()+"'";
		
		List testList=baseDAO.findEntity(sqlstring);
		if(testList!=null&&testList.size()>0)
			return false;
		else
			return true;
	} 
    
    public boolean check4UpdateStuBm(String id){//是否已报过名
    	boolean checkstring=false;
    	BmStuBm bmStuBm=getStuBmDetail(id);
    	if(bmStuBm==null){//无此记录
    		return false;
    	}
		String sqlstring=" select a.id from BmStuBm a " +
				" where a.bmStudent.studentNo='"+bmStuBm.getBmStudent().getStudentNo()+"'" +
				" and a.ifBm='"+Constants.yesCode+"'";
				
		List stubmList=baseDAO.findEntity(sqlstring);
		if(stubmList!=null&&stubmList.size()>0){
			int i=0;
			for(i=0;i<stubmList.size();i++){
				String curid=(String)stubmList.get(i);
				if(curid.equals(id)){
					checkstring=true;//只修改个人信息		
					break;
				}
			}
			if(i==stubmList.size())
			    checkstring=false;//可修改任意信息
		}
		
		return checkstring;
	}
    
    public String saveBm(BmStuBm bmStuBm) {
		
    	String resultstring="";
    	baseDAO.saveEntity(bmStuBm);
    	
        resultstring=resultstring+"'"+bmStuBm.getId()+"'";
        
        BmStudent bmStudent=bmStuBm.getBmStudent();
        BmTest bmTest=bmStuBm.getBmTest();
		
		BmTest bmTest4=null;
        //能报考六级的考生也能报考四级
		if(bmTest.getBmTestCat().getId().equals("e6")){			
			List stubm4li=baseDAO.findEntity("select a.id from BmStuBm a where a.bmStudent.studentNo='"+bmStudent.getStudentNo()+"' and a.bmTest.bmTestCat.id='e4'");
			if(stubm4li==null||stubm4li.size()==0){
				List test4li=baseDAO.findEntity("select a from BmTest a where a.bmTestCat.id='e4' and (a.testDate>'"+DateUtil.getNow("yyyy-MM-dd")+"' or a.testDate is null or a.testDate='') order by a.testDate ");
			    if(test4li!=null&&test4li.size()>0){
			    	bmTest4=(BmTest)test4li.get(0);
			    	BmStuBm bmStuBm4=new BmStuBm();
        			bmStuBm4.setBmStudent(bmStudent);
        			bmStuBm4.setBmTest(bmTest4);
        			bmStuBm4.setUpdator(bmStuBm.getUpdator());
        			bmStuBm4.setUpdateTime(DateUtil.getDateTime("yyyy-MM-dd HH:mm",new Date()));
        			//lizw 2009/6/4
        			bmStuBm4.setDeptName(bmStudent.getDeptName());
        			bmStuBm4.setMajorName(bmStudent.getMajorName());
        			bmStuBm4.setCurClass(bmStudent.getCurClass());
        			bmStuBm4.setCurGrade(bmStudent.getCurGrade());        			
        			baseDAO.saveEntity(bmStuBm4);   
        			
        			resultstring=resultstring+","+"'"+bmStuBm4.getId()+"'";
			    }
			} 		            			
		}//e6
		
		return resultstring;
	}
	public boolean updateBm(BmStuBm bmStuBm) {
				
		baseDAO.updateEntity(bmStuBm);
		
		BmStudent bmStudent=bmStuBm.getBmStudent();
        BmTest bmTest=bmStuBm.getBmTest();
		
		BmTest bmTest4=null;
        //能报考六级的考生也能报考四级
		if(bmTest.getBmTestCat().getId().equals("e6")){			
			List stubm4li=baseDAO.findEntity("select a.id from BmStuBm a where a.bmStudent.studentNo='"+bmStudent.getStudentNo()+"' and a.bmTest.bmTestCat.id='e4'");
			if(stubm4li==null||stubm4li.size()==0){
				List test4li=baseDAO.findEntity("select a from BmTest a where a.bmTestCat.id='e4' and (a.testDate>'"+DateUtil.getNow("yyyy-MM-dd")+"' or a.testDate is null or a.testDate='') order by a.testDate ");
			    if(test4li!=null&&test4li.size()>0){
			    	bmTest4=(BmTest)test4li.get(0);
			    	BmStuBm bmStuBm4=new BmStuBm();
        			bmStuBm4.setBmStudent(bmStudent);
        			bmStuBm4.setBmTest(bmTest4);
        			bmStuBm4.setUpdator(bmStuBm.getUpdator());
        			bmStuBm4.setUpdateTime(DateUtil.getDateTime("yyyy-MM-dd HH:mm",new Date()));
        			
        			//lizw 2009/6/4
        			bmStuBm4.setDeptName(bmStudent.getDeptName());
        			bmStuBm4.setMajorName(bmStudent.getMajorName());
        			bmStuBm4.setCurClass(bmStudent.getCurClass()); 
        			bmStuBm4.setCurGrade(bmStudent.getCurGrade());        			
        			baseDAO.saveEntity(bmStuBm4);            				    	
			    }
			} 		            			
		}//e6
							
		return true;
	}
	
	
	public boolean updateBmStuBm(BmStuBm bmStuBm) {
		baseDAO.updateEntity(bmStuBm);
		return true;
	}
	
	
	public boolean deleteBm(BmStuBm bmStuBm) {
		
		List stubmli=baseDAO.findEntity("select a from BmStuBm a where a.bmStudent.studentNo='"+bmStuBm.getBmStudent().getStudentNo()+"'");
		if(stubmli!=null&&stubmli.size()==1){//最后一条考生数据，级联删除基本记录
			BmStudent bmStudent=bmStuBm.getBmStudent();
			String studentNo=bmStudent.getStudentNo();
			baseDAO.removeEntity(bmStuBm);
		    baseDAO.removeEntity(bmStudent);
		    
		    //删除考生account
            List accountli=baseDAO.findEntity("select a from Account a where a.name='"+studentNo+"'");
            if(accountli!=null&&accountli.size()>0){
            	for(int k=0;k<accountli.size();k++){
            		Account act=(Account)accountli.get(k);
            		accountDAO.delete(act);
            	}
            }
		}
		else
			baseDAO.removeEntity(bmStuBm);
	
		return true;
	}
	
    public boolean deleteHistory(BmStuBm bmStuBm) {
		String testId=bmStuBm.getBmTest().getId();
		String bmId=bmStuBm.getId();
		
		List stubmli=baseDAO.findEntity("select a from BmStuBm a where a.bmStudent.studentNo='"+bmStuBm.getBmStudent().getStudentNo()+"'");
		if(stubmli!=null&&stubmli.size()==1){//最后一条考生数据，级联删除基本记录
			BmStudent bmStudent=bmStuBm.getBmStudent();
			String studentNo=bmStudent.getStudentNo();
			baseDAO.removeEntity(bmStuBm);
		    baseDAO.removeEntity(bmStudent);
		    
		    //删除考生account
            List accountli=baseDAO.findEntity("select a from Account a where a.name='"+studentNo+"'");
            if(accountli!=null&&accountli.size()>0){
            	for(int k=0;k<accountli.size();k++){
            		Account act=(Account)accountli.get(k);
            		accountDAO.delete(act);
            	}
            }
		}
		else
			baseDAO.removeEntity(bmStuBm);
	
		//检查是否是当前test的最后一条引用记录
		List testli=baseDAO.findEntity("select a from BmStuBm a where a.bmTest.id='"+testId+"' and a.id<>'"+bmId+"'");
		if(testli==null||testli.size()==0){
			BmTest bmTest=(BmTest)baseDAO.getEntity(BmTest.class,testId);
			baseDAO.removeEntity(bmTest);
		}
		
		return true;
	}
    
    public boolean check4SaveBm(String stuNo,String testId,String stubmId){
		String sqlstring=" select a from BmStuBm a " +
				" where a.bmStudent.studentNo='"+stuNo+"'" +
				" and a.bmTest.id='"+testId+"'";
		
		if(stubmId!=null)
			sqlstring=sqlstring+" and a.id<>'"+stubmId+"'";
		
		List testList=baseDAO.findEntity(sqlstring);
		if(testList!=null&&testList.size()>0)
			return false;
		else
			return true;
	}
    
    //是否缴费
    public boolean  isFee(String stuNo,String testId){
	
	String sqlstring=" select a.id from BmStuBm a " +
			" where a.bmStudent.studentNo='"+stuNo+"'" +
			" and  a.bmTest.id='"+testId+"'"+
			" and a.ifFee='"+Constants.yesCode+"'";
			
	List stubmList=baseDAO.findEntity(sqlstring);
	if(stubmList!=null&&stubmList.size()>0){
		return true;
	}
	return false;
    }
    
            	
	public String check4DeleteBm(String id){
		String sqlstring="select new Map(a.id as id,a.bmStudent.studentNo as studentNo,a.bmStudent.stuName as stuName,a.bmTest.bmTestCat.testCatName as testCatName) from BmStuBm a where (a.bmTest.testDate>'"+DateUtil.getNow("yyyy-MM-dd")+"' or a.bmTest.testDate='"+DateUtil.getNow("yyyy-MM-dd")+"' or a.bmTest.testDate='' or a.bmTest.testDate is null) and a.ifBm='"+Constants.yesCode+"' and a.id='"+id+"'";
				
		List stubmList=baseDAO.findEntity(sqlstring);
		if(stubmList!=null&&stubmList.size()>0){
			Map m=(Map)stubmList.get(0);
			String studentNo=(String)m.get("studentNo");
			String stuName=(String)m.get("stuName");
			String testcatName=(String)m.get("testCatName");
			return (studentNo+stuName+" 已报名 "+testcatName);
		}
		else
			return null;
	}
	
	public String check4Bm(String id,String stuNo){
		String resultstring="";
		
		String sqlstring="select new Map(a.id as id,a.bmTest.bmTestCat.id as testCatId,a.bmTest.testDate as testDate,(a.bmTest.testDate||' '||a.bmTest.testBeginTime) as bTime,(a.bmTest.testDate||' '||a.bmTest.testEndTime) as eTime,(a.bmTest.bmTestCat.testCatName||' '||a.bmTest.testDate||' '||a.bmTest.testBeginTime||' '||a.bmTest.testEndTime) as testInfo) from BmStuBm a" +
				" where a.bmStudent.studentNo='"+stuNo+"' and a.ifBm='"+Constants.yesCode+"' and a.id<>'"+id+"'";
				
		List stubmList=baseDAO.findEntity(sqlstring);
		
		sqlstring="select new Map(a.id as id,a.bmTest.bmTestCat.id as testCatId,a.bmTest.testDate as testDate,(a.bmTest.testDate||' '||a.bmTest.testBeginTime) as bTime,(a.bmTest.testDate||' '||a.bmTest.testEndTime) as eTime,(a.bmTest.bmTestCat.testCatName||' '||a.bmTest.testDate||' '||a.bmTest.testBeginTime||' '||a.bmTest.testEndTime) as testInfo) from BmStuBm a where a.id='"+id+"'";
		
		List curList=baseDAO.findEntity(sqlstring);
		
		if(curList!=null&&curList.size()>0){
			Map curm=(Map)curList.get(0);
			String curtcid=(String)curm.get("testCatId");
			String curbtime=(String)curm.get("bTime");
			String curetime=(String)curm.get("eTime");
			String curtestDate=(String)curm.get("testDate");
			
			if(stubmList!=null&&stubmList.size()>0){
				for(int i=0;i<stubmList.size();i++){
					Map tempm=(Map)stubmList.get(i);
					String temptcid=(String)tempm.get("testCatId");
					String tempbtime=(String)tempm.get("bTime");
					String tempetime=(String)tempm.get("eTime");
			        String temptestDate=(String)tempm.get("testDate");
			        
					if((curtcid.equals("e6")&&temptcid.equals("e4"))||(curtcid.equals("e4")&&temptcid.equals("e6"))){
						if ( curtestDate.compareTo(temptestDate)==0 ) { 
						  String curtinfo=(String)curm.get("testInfo");
						  String temptinfo=(String)tempm.get("testInfo");
						  resultstring=resultstring+curtinfo+" 与 "+temptinfo+" 同天考试，只能选报其中之一";
						  break;
						}
					}
					
					if(!(tempbtime.compareTo(curetime)>0||tempetime.compareTo(curbtime)<0)){
						String curtinfo=(String)curm.get("testInfo");
						String temptinfo=(String)tempm.get("testInfo");
						resultstring=resultstring+curtinfo+" 与 "+temptinfo+" 考试时间相冲突，只能选报其中之一";
						break;
					}
				}//for
			}
			
		}
		
		return resultstring;
		
	}
	
	public String check4NotBm(String id){
		String resultstring="";
						
		String sqlstring="select new Map(a.id as id,a.ifPay as ifPay,(a.bmTest.bmTestCat.testCatName||' '||a.bmTest.testDate||' '||a.bmTest.testBeginTime||' '||a.bmTest.testEndTime) as testInfo) from BmStuBm a where a.id='"+id+"'";
		
		List curList=baseDAO.findEntity(sqlstring);
		
		if(curList!=null&&curList.size()>0){
			Map curm=(Map)curList.get(0);
			if(curm.get("ifPay")!=null&&curm.get("ifPay").equals(Constants.yesCode)){
			    String testInfo=(String)curm.get("testInfo");
			    resultstring=resultstring+testInfo+",";
			}			
		}
		
		return resultstring;
		
	}
	
	public String check4NotBmDue(String id){
		String resultstring="";
						
		String sqlstring="select new Map(a.id as id,a.bmTest.testDate as testDate,(a.bmTest.bmTestCat.testCatName||' '||a.bmTest.testDate||' '||a.bmTest.testBeginTime||' '||a.bmTest.testEndTime) as testInfo) from BmStuBm a where a.id='"+id+"'";
		
		List curList=baseDAO.findEntity(sqlstring);
		
		if(curList!=null&&curList.size()>0){
			Map curm=(Map)curList.get(0);
			if(curm.get("testDate")!=null&&((String)curm.get("testDate")).compareTo(DateUtil.getNow("yyyy-MM-dd"))<0){
			    String testInfo=(String)curm.get("testInfo");
			    resultstring=resultstring+testInfo+",";
			}
			
		}
		
		return resultstring;
		
	}
	
	public List getStuBmList(String stuNo,boolean ifbm){
		
		String nowStr=DateUtil.getNow("yyyy-MM-dd HH:mm");
		
		String sqlstring=" select new Map(a.id as id,(a.bmTest.bmTestCat.testCatName||' '||a.bmTest.testDate||' '||a.bmTest.testBeginTime||'---'||a.bmTest.testEndTime) as testInfo,(a.bmTest.bmBeginDate||' '||a.bmTest.bmBeginTime||'——'||a.bmTest.bmEndDate||' '||a.bmTest.bmEndTime) as bmInfo,(a.bmTest.bmEndDate||' '||a.bmTest.bmEndTime) as bmEnd,a.bmTest.testMemo as testMemo," +
				"a.bmTest.bmTestCat.ifFee as ifFee,a.bmTest.bmTestCat.fee as fee,a.ifPay as ifPay,a.feePayed as feePayed,a.grades as grades)" +
				" from BmStuBm a where 1=1";
		if(ifbm)
			sqlstring=sqlstring+" and a.ifBm='"+Constants.yesCode+"' ";
		else{
			sqlstring=sqlstring+" and (not (a.bmTest.bmBeginDate||' '||a.bmTest.bmBeginTime)>'"+nowStr+"' and not (a.bmTest.bmEndDate||' '||a.bmTest.bmEndTime)<'"+nowStr+"' )";
			sqlstring=sqlstring+" and (a.ifBm is null or a.ifBm<>'"+Constants.yesCode+"') ";
		}
		
		sqlstring=sqlstring+" and a.bmStudent.studentNo='"+stuNo+"' ";
		
		List stubmList=baseDAO.findEntity(sqlstring);
		
		if(stubmList!=null&&stubmList.size()>0)
			changeIfName(stubmList);
		
		return stubmList;
	}
	
	public boolean updateStuBm(BmStuBm bmStuBm) {
		
		baseDAO.updateEntity(bmStuBm);
		
		return true;
	}
		
    /*----------------------------------*/
	/* lizw  2009/5/25 修改 */
    public String saveStuBmbyImport(HSSFSheet sheet,String testId,String userId) throws Exception{
				
    	String importresult="";

    	importresult="开始时间:"+DateUtil.getNow()+"\n";
    	
    	int rowCount=sheet.getPhysicalNumberOfRows();
		if(rowCount>0){	        	  	        	
        	int savenum=0;
        	int notsavenum=0;
        	BmTest bmTest=(BmTest)baseDAO.getEntity(BmTest.class,testId);           
           for(int i=1;i<rowCount;i++){
        	   
        	   HSSFRow row = sheet.getRow(i);
        	
        	//检查是否已有此考生在数据库
        	String studentNo=row.getCell((short)0).getStringCellValue().trim();
        	if(studentNo!=null&&studentNo.length()>0){
        		List stuli=baseDAO.findEntity(" select a from BmStudent a where a.studentNo='"+studentNo+"' ");
        		if(stuli!=null&&stuli.size()>0){
        			BmStudent bmStudent=(BmStudent)stuli.get(0);
        			
        			List stubmli=baseDAO.findEntity(" select new Map(a.id as id,(a.bmTest.bmTestCat.testCatName||' '||a.bmTest.testDate||' '||a.bmTest.testBeginTime||' '||a.bmTest.testEndTime) as testInfo) from BmStuBm a where a.bmStudent.studentNo='"+studentNo+"' and a.bmTest.id='"+testId+"'");
            		if(stubmli!=null&&stubmli.size()>0){
            			Map stubmm=(Map)stubmli.get(0);
            			String testInfo=(String)stubmm.get("testInfo");
            			importresult=importresult+"学号 "+studentNo+" 可报考 "+testInfo+" 的数据已经存在，未导入数据库！\n";
                		notsavenum++;
                		
                        //能报考六级的考生也能报考四级
            			if(bmTest.getBmTestCat().getId().equals("e6")){
            				List stubm4li=baseDAO.findEntity("select a.id from BmStuBm a where a.bmStudent.studentNo='"+studentNo+"' and a.bmTest.bmTestCat.id='e4'");
            				if(stubm4li==null||stubm4li.size()==0){
            					List test4li=baseDAO.findEntity("select a from BmTest a where a.bmTestCat.id='e4' and (a.testDate>'"+DateUtil.getNow("yyyy-MM-dd")+"' or a.testDate is null or a.testDate='') order by a.testDate ");
            				    if(test4li!=null&&test4li.size()>0){
            				    	BmTest bmTest4=(BmTest)test4li.get(0);
            				    	BmStuBm bmStuBm4=new BmStuBm();
                        			bmStuBm4.setBmStudent(bmStudent);
                        			bmStuBm4.setBmTest(bmTest4);
                        			bmStuBm4.setUpdator(userId);
                        			bmStuBm4.setUpdateTime(DateUtil.getDateTime("yyyy-MM-dd HH:mm",new Date()));
                        			//lizw 2009/6/4
                        			bmStuBm4.setDeptName(bmStudent.getDeptName());
                        			bmStuBm4.setMajorName(bmStudent.getMajorName());
                        			bmStuBm4.setCurClass(bmStudent.getCurClass()); 
                        			bmStuBm4.setCurGrade(bmStudent.getCurGrade());        			
                        			baseDAO.saveEntity(bmStuBm4);            				    	
            				    }
            				}            			
            			}//e6
                		
                		continue;
            		}
            		else{            			            			
            			BmStuBm bmStuBm=new BmStuBm();
            			bmStuBm.setBmStudent(bmStudent);
            			bmStuBm.setBmTest(bmTest);
            			bmStuBm.setUpdator(userId);
            			bmStuBm.setUpdateTime(DateUtil.getDateTime("yyyy-MM-dd HH:mm",new Date()));
            			//lizw 2009/6/4
            			bmStuBm.setDeptName(bmStudent.getDeptName());
            			bmStuBm.setMajorName(bmStudent.getMajorName());
            			bmStuBm.setCurClass(bmStudent.getCurClass());  
            			bmStuBm.setCurGrade(bmStudent.getCurGrade());      			
            			baseDAO.saveEntity(bmStuBm);
            			
            			//能报考六级的考生也能报考四级
            			if(bmTest.getBmTestCat().getId().equals("e6")){
            				List stubm4li=baseDAO.findEntity("select a.id from BmStuBm a where a.bmStudent.studentNo='"+studentNo+"' and a.bmTest.bmTestCat.id='e4'");
            				if(stubm4li==null||stubm4li.size()==0){
            					List test4li=baseDAO.findEntity("select a from BmTest a where a.bmTestCat.id='e4' and (a.testDate>'"+DateUtil.getNow("yyyy-MM-dd")+"' or a.testDate is null or a.testDate='') order by a.testDate ");
            				    if(test4li!=null&&test4li.size()>0){
            				    	BmTest bmTest4=(BmTest)test4li.get(0);
            				    	BmStuBm bmStuBm4=new BmStuBm();
                        			bmStuBm4.setBmStudent(bmStudent);
                        			bmStuBm4.setBmTest(bmTest4);
                        			bmStuBm4.setUpdator(userId);
                        			bmStuBm4.setUpdateTime(DateUtil.getDateTime("yyyy-MM-dd HH:mm",new Date()));

                        			bmStuBm4.setDeptName(bmStudent.getDeptName());
                        			bmStuBm4.setMajorName(bmStudent.getMajorName());
                        			bmStuBm4.setCurClass(bmStudent.getCurClass()); 
                        			bmStuBm4.setCurGrade(bmStudent.getCurGrade());                    			
                        			baseDAO.saveEntity(bmStuBm4);            				    	
            				    }
            				}            			
            			}//e6
            		}
            	}//ifhasstu  
        		else{//生成考生记录
        			BmStudent bmStudent=new BmStudent();
        			bmStudent.setStudentNo(studentNo);        			
        			if(row.getCell((short)1)!=null){//姓名
        				bmStudent.setStuName(row.getCell((short)1).getStringCellValue().trim());
        	        }
        			if(row.getCell((short)2)!=null){//性别
        				bmStudent.setGender(row.getCell((short)2).getStringCellValue().trim());
        	        }
        			if(row.getCell((short)3)!=null){//入学年份
        				bmStudent.setEnrollYear(row.getCell((short)3).getStringCellValue().trim());
        	        }
        			if(row.getCell((short)4)!=null){//学院名称
        				bmStudent.setDeptName(row.getCell((short)4).getStringCellValue().trim());
        	        }
        			if(row.getCell((short)5)!=null){//专业名称
        				bmStudent.setMajorName(row.getCell((short)5).getStringCellValue().trim());
        	        }
        			if(row.getCell((short)6)!=null){//年级
        				bmStudent.setCurGrade(row.getCell((short)6).getStringCellValue().trim());
        	        }
        			if(row.getCell((short)7)!=null){//班级
        				bmStudent.setCurClass(row.getCell((short)7).getStringCellValue().trim());
        	        }
        			if(row.getCell((short)8)!=null&&!row.getCell((short)8).getStringCellValue().trim().equals("")){//证件类型
        				bmStudent.setIdType(row.getCell((short)8).getStringCellValue().trim());
        	        }
        			else{
        				bmStudent.setIdType("身份证");
        			}
        			if(row.getCell((short)9)!=null){//证件号码
        				bmStudent.setIdCard(row.getCell((short)9).getStringCellValue().trim());
        	        }
        			if(row.getCell((short)10)!=null){//电子邮件
        				bmStudent.setEmail(row.getCell((short)10).getStringCellValue().trim());
        	        }
        			bmStudent.setUpdator(userId);
        			bmStudent.setUpdateTime(DateUtil.getDateTime("yyyy-MM-dd HH:mm",new Date()));
        			baseDAO.saveEntity(bmStudent);
        			
        			BmStuBm bmStuBm=new BmStuBm();
        			bmStuBm.setBmStudent(bmStudent);
        			bmStuBm.setBmTest(bmTest);
        			bmStuBm.setUpdator(userId);
        			bmStuBm.setUpdateTime(DateUtil.getDateTime("yyyy-MM-dd HH:mm",new Date()));
        			//lizw 2009/6/4
        			bmStuBm.setDeptName(bmStudent.getDeptName());
        			bmStuBm.setMajorName(bmStudent.getMajorName());
        			bmStuBm.setCurClass(bmStudent.getCurClass()); 
        			bmStuBm.setCurGrade(bmStudent.getCurGrade());      			
        			baseDAO.saveEntity(bmStuBm);
        			
                    //能报考六级的考生也能报考四级
        			if(bmTest.getBmTestCat().getId().equals("e6")){
        				List stubm4li=baseDAO.findEntity("select a.id from BmStuBm a where a.bmStudent.studentNo='"+studentNo+"' and a.bmTest.bmTestCat.id='e4'");
        				if(stubm4li==null||stubm4li.size()==0){
        					List test4li=baseDAO.findEntity("select a from BmTest a where a.bmTestCat.id='e4' and (a.testDate>'"+DateUtil.getNow("yyyy-MM-dd")+"' or a.testDate is null or a.testDate='') order by a.testDate ");
        				    if(test4li!=null&&test4li.size()>0){
        				    	BmTest bmTest4=(BmTest)test4li.get(0);
        				    	BmStuBm bmStuBm4=new BmStuBm();
                    			bmStuBm4.setBmStudent(bmStudent);
                    			bmStuBm4.setBmTest(bmTest4);
                    			bmStuBm4.setUpdator(userId);
                    			bmStuBm4.setUpdateTime(DateUtil.getDateTime("yyyy-MM-dd HH:mm",new Date()));
                    			//lizw 2009/6/4
                    			bmStuBm4.setDeptName(bmStudent.getDeptName());
                    			bmStuBm4.setMajorName(bmStudent.getMajorName());
                    			bmStuBm4.setCurClass(bmStudent.getCurClass());
                    			bmStuBm4.setCurGrade(bmStudent.getCurGrade());               			
                    			baseDAO.saveEntity(bmStuBm4);            				    	
        				    }
        				}            			
        			}//e6
        			
        			//生成该考生的登录数据
        			List accountList=find("select a.name from Account a where a.name='"+studentNo+"'");
    				
    				if(accountList==null||accountList.size()==0){
    					
    					String ksrole=getRoleidByName("考生");
    					
    					Person psn=new Person();						
						psn.setPersonCode(studentNo);
						if(bmStudent.getStuName()!=null)
						    psn.setPersonName(bmStudent.getStuName());
						else
							psn.setPersonName("");
						
						psn.setCreatedate(DateUtil.getNow().substring(0,8));
						psn.setLastdate(DateUtil.getNow().substring(0,8));
						
						Account act=new Account();
						act.setPerson(psn);
						act.setName(studentNo);
						
						accountDAO.save(act);
						
                        //加考生角色权限
						List roleList = new ArrayList();
						String roleid =null;
						roleid=ksrole;
						if(roleid!=null&&roleid.length()>0)
							roleList.add(roleid);						
						String[] roleArr =  new String[roleList.size()];
						if(roleList!=null&&roleList.size()>0){
						  roleList.toArray(roleArr);
						  grantAccountRoles(act.getId(),roleArr);						  
						}
    				}
    				
        		}//newstu
        		savenum++;
        	}
        	else
        		notsavenum++;
        	
           }//for
              importresult=importresult+"已导入记录数："+savenum+"\n";
              importresult=importresult+"未导入记录数："+notsavenum+"\n"; 
          	  importresult=importresult+"结束时间:"+DateUtil.getNow()+"\n";              
        }
		return importresult;
	}
    
    public String updateStuBmbyImport(HSSFSheet sheet,String testId,String userId) throws Exception{
				
    	String importresult="开始时间:"+DateUtil.getNow()+"\n";
    	int rowCount=sheet.getPhysicalNumberOfRows();
    	
		if(rowCount>0){	        	  	        	
        	int savenum=0;
        	int notsavenum=0;
        	BmTest bmTest=null;
        	if(testId!=null&&testId.length()>0)
        	    bmTest=(BmTest)baseDAO.getEntity(BmTest.class,testId);  
        	
           for(int i=1;i<rowCount;i++){
        	   
        	   HSSFRow row = sheet.getRow(i);
        	
        	//检查是否已有此考生在数据库
        	String studentNo=row.getCell((short)0).getStringCellValue().trim();
        	if(studentNo!=null&&studentNo.length()>0){
        		List stuli=baseDAO.findEntity(" select a from BmStudent a where a.studentNo='"+studentNo+"' ");
        		if(stuli!=null&&stuli.size()>0){  // 存在考生数据
        			
                    //I.若选择了考试，则更新该学号的考试数据
        			if(bmTest!=null){
        				
                        //查询该学号当前考试的数据
            			List notbmList=baseDAO.findEntity("select a from BmStuBm a where a.bmStudent.studentNo='"+studentNo+"' and (a.ifBm<>'"+Constants.yesCode+"' or a.ifBm is null)"
            					+" and a.bmTest.id='"+testId+"'");
        				
        				//删除该学号 尚未报名 的考生报名记录
            			
        				if(notbmList!=null&&notbmList.size()>0){
        					for(int j=0;j<notbmList.size();j++){
        						BmStuBm bmStuBm=(BmStuBm)notbmList.get(j);
        						baseDAO.removeEntity(bmStuBm);
        					}
        				}
        				
          			
        				List stubmli=baseDAO.findEntity(" select a.id from BmStuBm a where a.bmStudent.studentNo='"+studentNo+"' and a.bmTest.id='"+testId+"'");
        				//该学号的学生不存在，就添加进去
        				if(stubmli==null||stubmli.size()==0){
                			BmStudent bmStudent=(BmStudent)stuli.get(0);         			            			
                			            			
                			BmStuBm bmStuBm=new BmStuBm();
                			bmStuBm.setBmStudent(bmStudent);
                			bmStuBm.setBmTest(bmTest);
                			bmStuBm.setUpdator(userId);
                			bmStuBm.setUpdateTime(DateUtil.getDateTime("yyyy-MM-dd HH:mm",new Date()));
                			//lizw 2009/6/4
                			bmStuBm.setDeptName(bmStudent.getDeptName());
                			bmStuBm.setMajorName(bmStudent.getMajorName());
                			bmStuBm.setCurClass(bmStudent.getCurClass());  
                			bmStuBm.setCurGrade(bmStudent.getCurGrade());       			
                			baseDAO.saveEntity(bmStuBm);
                			
                			//能报考六级的考生也能报考四级
                			if(bmTest.getBmTestCat().getId().equals("e6")){
                				List stubm4li=baseDAO.findEntity("select a.id from BmStuBm a where a.bmStudent.studentNo='"+studentNo+"' and a.bmTest.bmTestCat.id='e4'");
                				if(stubm4li==null||stubm4li.size()==0){
                					List test4li=baseDAO.findEntity("select a from BmTest a where a.bmTestCat.id='e4' and (a.testDate>'"+DateUtil.getNow("yyyy-MM-dd")+"' or a.testDate is null or a.testDate='') order by a.testDate ");
                				    if(test4li!=null&&test4li.size()>0){
                				    	BmTest bmTest4=(BmTest)test4li.get(0);
                				    	BmStuBm bmStuBm4=new BmStuBm();
                            			bmStuBm4.setBmStudent(bmStudent);
                            			bmStuBm4.setBmTest(bmTest4);
                            			bmStuBm4.setUpdator(userId);
                            			bmStuBm4.setUpdateTime(DateUtil.getDateTime("yyyy-MM-dd HH:mm",new Date()));
                            			//lizw 2009/6/4
                            			bmStuBm4.setDeptName(bmStudent.getDeptName());
                            			bmStuBm4.setMajorName(bmStudent.getMajorName());
                            			bmStuBm4.setCurClass(bmStudent.getCurClass());
                            			bmStuBm4.setCurGrade(bmStudent.getCurGrade());                   			
                            			baseDAO.saveEntity(bmStuBm4);            				    	
                				    }
                				}            			
                			}//e6
                		}
        			}
        			/*
                    //II.若该学号从未报过名,则还可以更新其基本信息
        			List bmList=baseDAO.findEntity("select a from BmStuBm a where a.bmStudent.studentNo='"+studentNo+"' and a.ifBm='"+Constants.yesCode+"'");
        			if(bmList==null||bmList.size()==0){
        			*/
        			// 修改学生信息
        			List bmList=baseDAO.findEntity("select a from BmStuBm a where a.bmStudent.studentNo='"+studentNo+"' ");
        			if(bmList!=null&&bmList.size()>0){
        			
        				BmStudent bmStudent=(BmStudent)stuli.get(0);
        				if(row.getCell((short)1)!=null&&!row.getCell((short)1).getStringCellValue().trim().equals("")){//姓名
            				bmStudent.setStuName(row.getCell((short)1).getStringCellValue().trim());
            				
            				//修改Person表
            				List personList=find("select a from Person a where a.personCode='"+studentNo+"'");
            				if(personList!=null&&personList.size()>0){
            					Person psn=(Person)personList.get(0);
            					psn.setPersonName(bmStudent.getStuName());
            					baseDAO.updateEntity(psn);
            				}
            	        }
            			if(row.getCell((short)2)!=null&&!row.getCell((short)2).getStringCellValue().trim().equals("")){//性别
            				bmStudent.setGender(row.getCell((short)2).getStringCellValue().trim());
            	        }
            			if(row.getCell((short)3)!=null&&!row.getCell((short)3).getStringCellValue().trim().equals("")){//入学年份
            				bmStudent.setEnrollYear(row.getCell((short)3).getStringCellValue().trim());
            	        }
            			if(row.getCell((short)4)!=null&&!row.getCell((short)4).getStringCellValue().trim().equals("")){//学院名称
            				bmStudent.setDeptName(row.getCell((short)4).getStringCellValue().trim());
            	        }
            			if(row.getCell((short)5)!=null&&!row.getCell((short)5).getStringCellValue().trim().equals("")){//专业名称
            				bmStudent.setMajorName(row.getCell((short)5).getStringCellValue().trim());
            	        }
            			if(row.getCell((short)6)!=null&&!row.getCell((short)6).getStringCellValue().trim().equals("")){//年级
            				bmStudent.setCurGrade(row.getCell((short)6).getStringCellValue().trim());
            	        }
            			if(row.getCell((short)7)!=null&&!row.getCell((short)7).getStringCellValue().trim().equals("")){//班级
            				bmStudent.setCurClass(row.getCell((short)7).getStringCellValue().trim());
            	        }
            			if(row.getCell((short)8)!=null&&!row.getCell((short)8).getStringCellValue().trim().equals("")){//证件类型
            				bmStudent.setIdType(row.getCell((short)8).getStringCellValue().trim());
            	        }
            			if(row.getCell((short)9)!=null&&!row.getCell((short)9).getStringCellValue().trim().equals("")){//证件号码
            				bmStudent.setIdCard(row.getCell((short)9).getStringCellValue().trim());
            	        }
            			if(row.getCell((short)10)!=null&&!row.getCell((short)10).getStringCellValue().trim().equals("")){//电子邮件
            				bmStudent.setEmail(row.getCell((short)10).getStringCellValue().trim());
            	        }
            			bmStudent.setUpdator(userId);
            			bmStudent.setUpdateTime(DateUtil.getDateTime("yyyy-MM-dd HH:mm",new Date()));
            			baseDAO.updateEntity(bmStudent);            			
        			}
        			
        		}//ifhasstu 
        		else{  // 不存在考生数据
        			if(bmTest!=null){
        				BmStudent bmStudent=new BmStudent();
            			bmStudent.setStudentNo(studentNo);        			
            			if(row.getCell((short)1)!=null){//姓名
            				bmStudent.setStuName(row.getCell((short)1).getStringCellValue().trim());
            	        }
            			if(row.getCell((short)2)!=null){//性别
            				bmStudent.setGender(row.getCell((short)2).getStringCellValue().trim());
            	        }
            			if(row.getCell((short)3)!=null){//入学年份
            				bmStudent.setEnrollYear(row.getCell((short)3).getStringCellValue().trim());
            	        }
            			if(row.getCell((short)4)!=null){//学院名称
            				bmStudent.setDeptName(row.getCell((short)4).getStringCellValue().trim());
            	        }
            			if(row.getCell((short)5)!=null){//专业名称
            				bmStudent.setMajorName(row.getCell((short)5).getStringCellValue().trim());
            	        }
            			if(row.getCell((short)6)!=null){//年级
            				bmStudent.setCurGrade(row.getCell((short)6).getStringCellValue().trim());
            	        }
            			if(row.getCell((short)7)!=null){//班级
            				bmStudent.setCurClass(row.getCell((short)7).getStringCellValue().trim());
            	        }
            			if(row.getCell((short)8)!=null&&!row.getCell((short)8).getStringCellValue().trim().equals("")){//证件类型
            				bmStudent.setIdType(row.getCell((short)8).getStringCellValue().trim());
            	        }
            			else{
            				bmStudent.setIdType("身份证");
            			}
            			if(row.getCell((short)9)!=null){//证件号码
            				bmStudent.setIdCard(row.getCell((short)9).getStringCellValue().trim());
            	        }
            			if(row.getCell((short)10)!=null){//电子邮件
            				bmStudent.setEmail(row.getCell((short)10).getStringCellValue().trim());
            	        }
            			bmStudent.setUpdator(userId);
            			bmStudent.setUpdateTime(DateUtil.getDateTime("yyyy-MM-dd HH:mm",new Date()));
            			baseDAO.saveEntity(bmStudent);
            			
            			BmStuBm bmStuBm=new BmStuBm();
            			bmStuBm.setBmStudent(bmStudent);
            			bmStuBm.setBmTest(bmTest);
            			bmStuBm.setUpdator(userId);
            			bmStuBm.setUpdateTime(DateUtil.getDateTime("yyyy-MM-dd HH:mm",new Date()));
            			//lizw 2009/6/4
            			bmStuBm.setDeptName(bmStudent.getDeptName());
            			bmStuBm.setMajorName(bmStudent.getMajorName());
            			bmStuBm.setCurClass(bmStudent.getCurClass());
            			bmStuBm.setCurGrade(bmStudent.getCurGrade());        			
            			baseDAO.saveEntity(bmStuBm);
            			
                        //能报考六级的考生也能报考四级
            			if(bmTest.getBmTestCat().getId().equals("e6")){
            				List stubm4li=baseDAO.findEntity("select a.id from BmStuBm a where a.bmStudent.studentNo='"+studentNo+"' and a.bmTest.bmTestCat.id='e4'");
            				if(stubm4li==null||stubm4li.size()==0){
            					List test4li=baseDAO.findEntity("select a from BmTest a where a.bmTestCat.id='e4' and (a.testDate>'"+DateUtil.getNow("yyyy-MM-dd")+"' or a.testDate is null or a.testDate='') order by a.testDate ");
            				    if(test4li!=null&&test4li.size()>0){
            				    	BmTest bmTest4=(BmTest)test4li.get(0);
            				    	BmStuBm bmStuBm4=new BmStuBm();
                        			bmStuBm4.setBmStudent(bmStudent);
                        			bmStuBm4.setBmTest(bmTest4);
                        			bmStuBm4.setUpdator(userId);
                        			bmStuBm4.setUpdateTime(DateUtil.getDateTime("yyyy-MM-dd HH:mm",new Date()));
                        			//lizw 2009/6/4	
                        			bmStuBm4.setDeptName(bmStudent.getDeptName());
                        			bmStuBm4.setMajorName(bmStudent.getMajorName());
                        			bmStuBm4.setCurClass(bmStudent.getCurClass());
                        			bmStuBm4.setCurGrade(bmStudent.getCurGrade());              			
                        			baseDAO.saveEntity(bmStuBm4);            				    	
            				    }
            				}            			
            			}//e6
            			
                        //生成该考生的登录数据
            			List accountList=find("select a.name from Account a where a.name='"+studentNo+"'");
        				
        				if(accountList==null||accountList.size()==0){
        					
        					String ksrole=getRoleidByName("考生");
        					
        					Person psn=new Person();						
    						psn.setPersonCode(studentNo);
    						if(bmStudent.getStuName()!=null)
    						    psn.setPersonName(bmStudent.getStuName());
    						else
    							psn.setPersonName("");
    						
    						psn.setCreatedate(DateUtil.getNow().substring(0,8));
    						psn.setLastdate(DateUtil.getNow().substring(0,8));
    						
    						Account act=new Account();
    						act.setPerson(psn);
    						act.setName(studentNo);
    						
    						accountDAO.save(act);
    						
                            //加考生角色权限
    						List roleList = new ArrayList();
    						String roleid =null;
    						roleid=ksrole;
    						if(roleid!=null&&roleid.length()>0)
    							roleList.add(roleid);						
    						String[] roleArr =  new String[roleList.size()];
    						if(roleList!=null&&roleList.size()>0){
    						  roleList.toArray(roleArr);
    						  grantAccountRoles(act.getId(),roleArr);						  
    						}
        				}
        				
        			}//newstu
        			else{//未选择考试
        				importresult=importresult+"学号 "+studentNo+" 缺少考试数据，无法导入数据库！\n";
                		notsavenum++;
                		continue;
        			}
        		}//nosuchstu
        		savenum++; 
        	}
        	else
        		notsavenum++;        	          
        	
           }//for
              importresult=importresult+"已导入记录数："+savenum+"\n";
              importresult=importresult+"未导入记录数："+notsavenum+"\n"; 
              importresult=importresult+"结束时间:"+DateUtil.getNow()+"\n";
        }
		return importresult;
	}
    
    public String deleteStuBmbyImport(HSSFSheet sheet,String testId,String userId) throws Exception{
		
    	String importresult="";
    	int rowCount=sheet.getPhysicalNumberOfRows();
    	
		if(rowCount>0){	        	  	        	
        	int savenum=0;
        	int notsavenum=0;
        	BmTest bmTest=(BmTest)baseDAO.getEntity(BmTest.class,testId); 
        	
        	String delstuNos="";
        	//删除考试日期早于于当前日期的所有报名表记录
        	List hisbmli=baseDAO.findEntity("select a from BmStuBm a where a.bmTest.testDate<'"+DateUtil.getNow("yyyy-MM-dd")+"'");
            for(int i=0;i<hisbmli.size();i++){
            	BmStuBm bmStuBm=(BmStuBm)hisbmli.get(i);            	
            	baseDAO.removeEntity(bmStuBm);
            }
            //剩余报名记录中，再删除未报名的报名表记录
            List notbmli=baseDAO.findEntity("select a from BmStuBm a where a.ifBm is null or a.ifBm<>'"+Constants.yesCode+"'");
            for(int i=0;i<notbmli.size();i++){
            	BmStuBm bmStuBm=(BmStuBm)notbmli.get(i);            	
            	baseDAO.removeEntity(bmStuBm);
            }
           //删除学号不在报名表中的考生基本表记录
            List delstuli=baseDAO.findEntity("select a from BmStudent a where a.studentNo not in (select b.bmStudent.studentNo from BmStuBm b)");
            for(int i=0;i<delstuli.size();i++){
            	BmStudent bmStudent=(BmStudent)delstuli.get(i);
            	delstuNos=delstuNos+"'"+bmStudent.getStudentNo()+"'"+",";
            	baseDAO.removeEntity(bmStudent);
            }
            
            if(delstuNos.length()>0){
            	delstuNos=delstuNos.substring(0,delstuNos.length()-1);
            	if(delstuNos.length()>0){
                    //删除delstuNos中的考生account
                    List accountli=baseDAO.findEntity("select a from Account a where a.name in ("+delstuNos+")");
                    if(accountli!=null&&accountli.size()>0){
                    	for(int k=0;k<accountli.size();k++){
                    		Account act=(Account)accountli.get(k);
                    		accountDAO.delete(act);
                    	}
                    }//ifaccount
            	}
            
            }            
                        
        for(int i=1;i<rowCount;i++){
        	   
        	HSSFRow row = sheet.getRow(i);
        	
        	//检查是否已有此考生在数据库
        	String studentNo=row.getCell((short)0).getStringCellValue().trim();
        	if(studentNo!=null&&studentNo.length()>0){
        		List stuli=baseDAO.findEntity(" select a from BmStudent a where a.studentNo='"+studentNo+"' ");
        		if(stuli!=null&&stuli.size()>0){
        			BmStudent bmStudent=(BmStudent)stuli.get(0);
        			
        			List stubmli=baseDAO.findEntity(" select new Map(a.id as id,(a.bmTest.bmTestCat.testCatName||' '||a.bmTest.testDate||' '||a.bmTest.testBeginTime||' '||a.bmTest.testEndTime) as testInfo) from BmStuBm a where a.bmStudent.studentNo='"+studentNo+"' and a.bmTest.id='"+testId+"'");
            		if(stubmli!=null&&stubmli.size()>0){
            			Map stubmm=(Map)stubmli.get(0);
            			String testInfo=(String)stubmm.get("testInfo");
            			importresult=importresult+"学号 "+studentNo+" 可报考 "+testInfo+" 的数据已经存在，未导入数据库！\n";
                		notsavenum++;
                		
                        //能报考六级的考生也能报考四级
            			if(bmTest.getBmTestCat().getId().equals("e6")){
            				List stubm4li=baseDAO.findEntity("select a.id from BmStuBm a where a.bmStudent.studentNo='"+studentNo+"' and a.bmTest.bmTestCat.id='e4'");
            				if(stubm4li==null||stubm4li.size()==0){
            					List test4li=baseDAO.findEntity("select a from BmTest a where a.bmTestCat.id='e4' and (a.testDate>'"+DateUtil.getNow("yyyy-MM-dd")+"' or a.testDate is null or a.testDate='') order by a.testDate ");
            				    if(test4li!=null&&test4li.size()>0){
            				    	BmTest bmTest4=(BmTest)test4li.get(0);
            				    	BmStuBm bmStuBm4=new BmStuBm();
                        			bmStuBm4.setBmStudent(bmStudent);
                        			bmStuBm4.setBmTest(bmTest4);
                        			bmStuBm4.setUpdator(userId);
                        			bmStuBm4.setUpdateTime(DateUtil.getDateTime("yyyy-MM-dd HH:mm",new Date()));
                        			//lizw 2009/6/4
                        			bmStuBm4.setDeptName(bmStudent.getDeptName());
                        			bmStuBm4.setMajorName(bmStudent.getMajorName());
                        			bmStuBm4.setCurClass(bmStudent.getCurClass());
                        			bmStuBm4.setCurGrade(bmStudent.getCurGrade());
                        			baseDAO.saveEntity(bmStuBm4);            				    	
            				    }
            				}            			
            			}//e6
                		
                		continue;
            		}
            		else{            			            			
            			BmStuBm bmStuBm=new BmStuBm();
            			bmStuBm.setBmStudent(bmStudent);
            			bmStuBm.setBmTest(bmTest);
            			bmStuBm.setUpdator(userId);
            			bmStuBm.setUpdateTime(DateUtil.getDateTime("yyyy-MM-dd HH:mm",new Date()));
            			bmStuBm.setDeptName(bmStudent.getDeptName());
            			bmStuBm.setMajorName(bmStudent.getMajorName());
            			bmStuBm.setCurClass(bmStudent.getCurClass());
            			bmStuBm.setCurGrade(bmStudent.getCurGrade());            			
            			baseDAO.saveEntity(bmStuBm);
            			
            			//能报考六级的考生也能报考四级
            			if(bmTest.getBmTestCat().getId().equals("e6")){
            				List stubm4li=baseDAO.findEntity("select a.id from BmStuBm a where a.bmStudent.studentNo='"+studentNo+"' and a.bmTest.bmTestCat.id='e4'");
            				if(stubm4li==null||stubm4li.size()==0){
            					List test4li=baseDAO.findEntity("select a from BmTest a where a.bmTestCat.id='e4' and (a.testDate>'"+DateUtil.getNow("yyyy-MM-dd")+"' or a.testDate is null or a.testDate='') order by a.testDate ");
            				    if(test4li!=null&&test4li.size()>0){
            				    	BmTest bmTest4=(BmTest)test4li.get(0);
            				    	BmStuBm bmStuBm4=new BmStuBm();
                        			bmStuBm4.setBmStudent(bmStudent);
                        			bmStuBm4.setBmTest(bmTest4);
                        			bmStuBm4.setUpdator(userId);
                        			bmStuBm4.setUpdateTime(DateUtil.getDateTime("yyyy-MM-dd HH:mm",new Date()));
                        			//lizw 2009/6/4
                        			bmStuBm4.setDeptName(bmStudent.getDeptName());
                        			bmStuBm4.setMajorName(bmStudent.getMajorName());
                        			bmStuBm4.setCurClass(bmStudent.getCurClass());
                        			bmStuBm4.setCurGrade(bmStudent.getCurGrade());
                        			baseDAO.saveEntity(bmStuBm4);            				    	
            				    }
            				}            			
            			}//e6
            		}
            	}//ifhasstu  
        		else{//生成考生记录
        			BmStudent bmStudent=new BmStudent();
        			bmStudent.setStudentNo(studentNo);        			
        			if(row.getCell((short)1)!=null){//姓名
        				bmStudent.setStuName(row.getCell((short)1).getStringCellValue().trim());
        	        }
        			if(row.getCell((short)2)!=null){//性别
        				bmStudent.setGender(row.getCell((short)2).getStringCellValue().trim());
        	        }
        			if(row.getCell((short)3)!=null){//入学年份
        				bmStudent.setEnrollYear(row.getCell((short)3).getStringCellValue().trim());
        	        }
        			if(row.getCell((short)4)!=null){//学院名称
        				bmStudent.setDeptName(row.getCell((short)4).getStringCellValue().trim());
        	        }
        			if(row.getCell((short)5)!=null){//专业名称
        				bmStudent.setMajorName(row.getCell((short)5).getStringCellValue().trim());
        	        }
        			if(row.getCell((short)6)!=null){//年级
        				bmStudent.setCurGrade(row.getCell((short)6).getStringCellValue().trim());
        	        }
        			if(row.getCell((short)7)!=null){//班级
        				bmStudent.setCurClass(row.getCell((short)7).getStringCellValue().trim());
        	        }
        			if(row.getCell((short)8)!=null&&!row.getCell((short)8).getStringCellValue().trim().equals("")){//证件类型
        				bmStudent.setIdType(row.getCell((short)8).getStringCellValue().trim());
        	        }
        			else{
        				bmStudent.setIdType("身份证");
        			}
        			if(row.getCell((short)9)!=null){//证件号码
        				bmStudent.setIdCard(row.getCell((short)9).getStringCellValue().trim());
        	        }
        			if(row.getCell((short)10)!=null){//电子邮件
        				bmStudent.setEmail(row.getCell((short)10).getStringCellValue().trim());
        	        }
        			bmStudent.setUpdator(userId);
        			bmStudent.setUpdateTime(DateUtil.getDateTime("yyyy-MM-dd HH:mm",new Date()));
        			baseDAO.saveEntity(bmStudent);
        			
        			BmStuBm bmStuBm=new BmStuBm();
        			bmStuBm.setBmStudent(bmStudent);
        			bmStuBm.setBmTest(bmTest);
        			bmStuBm.setUpdator(userId);
        			bmStuBm.setUpdateTime(DateUtil.getDateTime("yyyy-MM-dd HH:mm",new Date()));

        			bmStuBm.setDeptName(bmStudent.getDeptName());
        			bmStuBm.setMajorName(bmStudent.getMajorName());
        			bmStuBm.setCurClass(bmStudent.getCurClass());
        			bmStuBm.setCurGrade(bmStudent.getCurGrade());
        			baseDAO.saveEntity(bmStuBm);
        			
                    //能报考六级的考生也能报考四级
        			if(bmTest.getBmTestCat().getId().equals("e6")){
        				List stubm4li=baseDAO.findEntity("select a.id from BmStuBm a where a.bmStudent.studentNo='"+studentNo+"' and a.bmTest.bmTestCat.id='e4'");
        				if(stubm4li==null||stubm4li.size()==0){
        					List test4li=baseDAO.findEntity("select a from BmTest a where a.bmTestCat.id='e4' and (a.testDate>'"+DateUtil.getNow("yyyy-MM-dd")+"' or a.testDate is null or a.testDate='') order by a.testDate ");
        				    if(test4li!=null&&test4li.size()>0){
        				    	BmTest bmTest4=(BmTest)test4li.get(0);
        				    	BmStuBm bmStuBm4=new BmStuBm();
                    			bmStuBm4.setBmStudent(bmStudent);
                    			bmStuBm4.setBmTest(bmTest4);
                    			bmStuBm4.setUpdator(userId);
                    			bmStuBm4.setUpdateTime(DateUtil.getDateTime("yyyy-MM-dd HH:mm",new Date()));

                    			bmStuBm4.setDeptName(bmStudent.getDeptName());
                    			bmStuBm4.setMajorName(bmStudent.getMajorName());
                    			bmStuBm4.setCurClass(bmStudent.getCurClass());
                    			bmStuBm4.setCurGrade(bmStudent.getCurGrade());
                    			baseDAO.saveEntity(bmStuBm4);            				    	
        				    }
        				}            			
        			}//e6
        			
                    //生成该考生的登录数据
        			List accountList=find("select a.name from Account a where a.name='"+studentNo+"'");
    				
    				if(accountList==null||accountList.size()==0){
    					
    					String ksrole=getRoleidByName("考生");
    					
    					Person psn=new Person();						
						psn.setPersonCode(studentNo);
						if(bmStudent.getStuName()!=null)
						    psn.setPersonName(bmStudent.getStuName());
						else
							psn.setPersonName("");
						
						psn.setCreatedate(DateUtil.getNow().substring(0,8));
						psn.setLastdate(DateUtil.getNow().substring(0,8));
						
						Account act=new Account();
						act.setPerson(psn);
						act.setName(studentNo);
						
						accountDAO.save(act);
						
                        //加考生角色权限
						List roleList = new ArrayList();
						String roleid =null;
						roleid=ksrole;
						if(roleid!=null&&roleid.length()>0)
							roleList.add(roleid);						
						String[] roleArr =  new String[roleList.size()];
						if(roleList!=null&&roleList.size()>0){
						  roleList.toArray(roleArr);
						  grantAccountRoles(act.getId(),roleArr);						  
						}
    				}
    				
        		}//newstu
        		savenum++;
        	}
        	else
        		notsavenum++;
        	
           }//for
              importresult=importresult+"已导入记录数："+savenum+"\n";
              importresult=importresult+"未导入记录数："+notsavenum+"\n";           
        }
		return importresult;
	}
	
    public String updateStuGrades(HSSFSheet sheet,String testId,String userId) throws Exception{
		
    	String importresult="";
    	int rowCount=sheet.getPhysicalNumberOfRows();
    	
		if(rowCount>0){
        	int savenum=0;
        	int notsavenum=0;
        	BmTest bmTest=(BmTest)baseDAO.getEntity(BmTest.class,testId); 
        	String testInfo="";
        	List testli=baseDAO.findEntity("select (a.bmTestCat.testCatName||' '||a.testDate||' '||a.testBeginTime||' '||a.testEndTime) as testInfo from BmTest a where a.id='"+testId+"'");
        	if(testli!=null&&testli.size()>0){
        		testInfo=(String)testli.get(0);
        	}
        	
           for(int i=1;i<rowCount;i++){
        	   
        	   HSSFRow row = sheet.getRow(i);
        	
        	//检查是否已有此考生在数据库
        	String studentNo=row.getCell((short)0).getStringCellValue().trim();
        	if(studentNo!=null&&studentNo.length()>0){
        		List stuli=baseDAO.findEntity(" select a from BmStudent a where a.studentNo='"+studentNo+"' ");
        		if(stuli!=null&&stuli.size()>0){//有考生信息
        			List stubmli=baseDAO.findEntity(" select a from BmStuBm a where a.bmStudent.studentNo='"+studentNo+"' and a.bmTest.id='"+bmTest.getId()+"'");
                    if(stubmli!=null&&stubmli.size()>0){//有考生报名记录
                    	BmStuBm bmStuBm=(BmStuBm)stubmli.get(0);
                    	if(bmStuBm.getIfBm()!=null&&bmStuBm.getIfBm().equals(Constants.yesCode)){//已报名
                    		if(row.getCell((short)1)!=null){//成绩
                				bmStuBm.setGrades(row.getCell((short)1).getNumericCellValue());
                	        }
                    		else{
                    			bmStuBm.setGrades(0);
                    		} 
                    		bmStuBm.setUpdator(userId);
                    		bmStuBm.setUpdateTime(DateUtil.getDateTime("yyyy-MM-dd HH:mm",new Date()));
                    		baseDAO.updateEntity(bmStuBm);
                    	}
                    	else{//未报名
                    		importresult=importresult+"学号 "+studentNo+" 没有报考 "+testInfo+" ，成绩未导入数据库！\n";
                    		notsavenum++;
                    		continue;
                    	}
                    }
                    else{//考生不能报名该考试
                    	importresult=importresult+"学号 "+studentNo+" 不能报考 "+testInfo+" ，成绩未导入数据库！\n";
                		notsavenum++;
                		continue;
                    }
        			
        		}//ifhasstu 
        		else{//没有该考生的信息
        			importresult=importresult+"数据库中没有学号 "+studentNo+" 的考生信息，成绩未导入数据库！\n";
            		notsavenum++;
            		continue;
        		}//nosuchstu
        		savenum++; 
        	}
        	else
        		notsavenum++;        	          
        	
           }//for
              importresult=importresult+"已导入记录数："+savenum+"\n";
              importresult=importresult+"未导入记录数："+notsavenum+"\n";           
        }
		return importresult;
	}
    
	public List find(String sqlstring){
		List li=baseDAO.findEntity(sqlstring);
		return li;
	}
	
	public String getRoleidByName(String roleName) {
		String roleId = "";
		List list = find("select a.id from Role a where a.name='" + roleName
						+ "'");
		if (list.size() > 0) {
			roleId = list.get(0).toString();
		}
		return roleId;
	}
	
	public void grantAccountRoles(String accountId, String[] currentRole) throws BusinessException {
		Account account = accountDAO.get(accountId);
		Set currentAccountRole = new HashSet();
		if(currentRole!=null) {
			for(int i=0;i<currentRole.length;i++){
				currentAccountRole.add((Role)roleDAO.get(currentRole[i]));
			}
		}
		account.setRoles(currentAccountRole);
		accountDAO.update(account);
	}

	public void changeIfName(List list){
		String[][] onoff= Constants.onoff_flag;
		for(int i=0;i<list.size();i++){
			Map m=(Map)list.get(i);
			
			String iffValue=(String)m.get("ifFee");
			for(int j=0;j<onoff.length;j++){
				if(onoff[j][0].equals(iffValue)){
					m.put("ifFeeName",onoff[j][1]);
				}
			}
			
			String ifPayName="否";
			if(m.get("ifPay")!=null){
			    String ifpValue=(String)m.get("ifPay");
			    for(int j=0;j<onoff.length;j++){
				    if(onoff[j][0].equals(ifpValue)){
				    	ifPayName=onoff[j][1];
				    }
			    }
			}
			m.put("ifPayName",ifPayName);
		}//for
		
	}
	
	public void changeIfBmPayName(List list){
		String[][] onoff= Constants.onoff_flag;
		for(int i=0;i<list.size();i++){
			Map m=(Map)list.get(i);
						
			String ifBmName="否";
			if(m.get("ifBm")!=null){
			    String ifbValue=(String)m.get("ifBm");
			    for(int j=0;j<onoff.length;j++){
				    if(onoff[j][0].equals(ifbValue)){
				    	ifBmName=onoff[j][1];
				    }
			    }
			}
			m.put("ifBmName",ifBmName);
			
			String ifPayName="否";
			if(m.get("ifPay")!=null){
				String ifpay=(String)m.get("ifPay");
				for(int j=0;j<onoff.length;j++){
					if(onoff[j][0].equals(ifpay)){
						ifPayName=onoff[j][1];
					}
				}				
			}
			m.put("ifPayName",ifPayName);
		}//for
		
	}
	
	public List getStuPhoto(String cutId){
		String sqlstring="select cif.id.photo from TCifPhoto cif where cif.id.cutId="+cutId;
		List li=baseDAO.findEntity(sqlstring);
		return li;
	}
	
	public List getPhotoList(Map m) {
		StringBuffer sbhql=new StringBuffer("");
		StringBuffer sWhere=new StringBuffer("");
		List list=new ArrayList();
		MyQuery mq=new MyQuery();
		
		sbhql.append(" select new Map(stubm.bmStudent.studentNo as studentNo,cif.id.photo as photo)" +
				" from TCifPhoto cif,TCifCustomer cut,BmStuBm stubm" +
				" where cif.id.cutId=cut.cutId and cut.stuempNo=stubm.bmStudent.studentNo");
		if(m.get("search_studentno")!=null&&!((String)m.get("search_studentno")).equals("")){
			sWhere.append(" and stubm.bmStudent.studentNo like ? ");
			mq.addPara("%"+(String)m.get("search_studentno")+"%",Types.VARCHAR);
		}
		if(m.get("search_stuname")!=null&&!((String)m.get("search_stuname")).equals("")){
			sWhere.append(" and stubm.bmStudent.stuName like ? ");
			mq.addPara("%"+(String)m.get("search_stuname")+"%",Types.VARCHAR);
		}
		if(m.get("search_deptname")!=null&&!((String)m.get("search_deptname")).equals("")){
			sWhere.append(" and stubm.bmStudent.deptName like ? ");
			mq.addPara("%"+(String)m.get("search_deptname")+"%",Types.VARCHAR);
		}
		if(m.get("search_majorname")!=null&&!((String)m.get("search_majorname")).equals("")){
			sWhere.append(" and stubm.bmStudent.majorName like ? ");
			mq.addPara("%"+(String)m.get("search_majorname")+"%",Types.VARCHAR);
		}
		if(m.get("search_curgrade")!=null&&!((String)m.get("search_curgrade")).equals("")){
			sWhere.append(" and stubm.bmStudent.curGrade like ? ");
			mq.addPara("%"+(String)m.get("search_curgrade")+"%",Types.VARCHAR);
		}
		if(m.get("search_curclass")!=null&&!((String)m.get("search_curclass")).equals("")){
			sWhere.append(" and stubm.bmStudent.curClass like ? ");
			mq.addPara("%"+(String)m.get("search_curclass")+"%",Types.VARCHAR);
		}
		if(m.get("search_idtype")!=null&&!((String)m.get("search_idtype")).equals("")){
			sWhere.append(" and stubm.bmStudent.idType like ? ");
			mq.addPara("%"+(String)m.get("search_idtype")+"%",Types.VARCHAR);
		}
		if(m.get("search_idcard")!=null&&!((String)m.get("search_idcard")).equals("")){
			sWhere.append(" and stubm.bmStudent.idCard like ? ");
			mq.addPara("%"+(String)m.get("search_idcard")+"%",Types.VARCHAR);
		}
		if(m.get("search_testcatname")!=null&&!((String)m.get("search_testcatname")).equals("")){
			sWhere.append(" and stubm.bmTest.bmTestCat.testCatName like ? ");
			mq.addPara("%"+(String)m.get("search_testcatname")+"%",Types.VARCHAR);
		}	
		if(m.get("search_testid")!=null&&!((String)m.get("search_testid")).equals("")){
			sWhere.append(" and stubm.bmTest.id=? ");
			mq.addPara((String)m.get("search_testid"),Types.VARCHAR);
		}
		if(m.get("search_ifbm")!=null&&!((String)m.get("search_ifbm")).equals("")&&((String)m.get("search_ifbm")).equals(Constants.yesCode)){
			sWhere.append(" and stubm.ifBm='"+Constants.yesCode+"' ");
		}
		else if(m.get("search_ifbm")!=null&&!((String)m.get("search_ifbm")).equals("")&&((String)m.get("search_ifbm")).equals(Constants.noCode)){
			sWhere.append(" and (stubm.ifBm<>'"+Constants.yesCode+"' or stubm.ifBm is null) ");
		}
		if(m.get("search_ifpay")!=null&&!((String)m.get("search_ifpay")).equals("")&&((String)m.get("search_ifpay")).equals(Constants.yesCode)){
			sWhere.append(" and stubm.ifPay='"+Constants.yesCode+"' ");
		}
		else if(m.get("search_ifpay")!=null&&!((String)m.get("search_ifpay")).equals("")&&((String)m.get("search_ifpay")).equals(Constants.noCode)){
			sWhere.append(" and (stubm.ifPay<>'"+Constants.yesCode+"' or stubm.ifPay is null) ");
		}
		if(m.get("search_afterdate")!=null&&!((String)m.get("search_afterdate")).equals("")){
			sWhere.append(" and (stubm.bmTest.testDate is null or stubm.bmTest.testDate='' or stubm.bmTest.testDate> ?) ");
			mq.addPara((String)m.get("search_afterdate"),Types.VARCHAR);
		}
		
		sWhere.append(" order by stubm.bmStudent.studentNo ");
		
		mq.setQueryString(sbhql.append(sWhere).toString());
		
		list= baseDAO.findEntity(mq);				
		        		
		return list;
	}
	
}
