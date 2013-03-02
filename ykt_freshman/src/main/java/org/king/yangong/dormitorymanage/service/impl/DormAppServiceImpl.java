package org.king.yangong.dormitorymanage.service.impl;

import java.sql.SQLException;
import java.sql.Types;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;

import org.apache.commons.lang.StringUtils;
import org.apache.struts.action.DynaActionForm;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;
import org.king.classmanage.domain.Department;
import org.king.classmanage.domain.Dictionary;
import org.king.classmanage.domain.Studentmodel;
import org.king.common.dao.AllDAO;
import org.king.dictionary.service.DictionaryService;
import org.king.dormitorymanage.domain.DormDept;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.framework.dao.hibernate.BaseDAOHibernate;
import org.king.quarters.domain.TabSsDept;
import org.king.utils.DateUtil;
import org.king.yangong.dormitorymanage.dao.YxGraduateDAO;
import org.king.yangong.dormitorymanage.domain.GraduateType;
import org.king.yangong.dormitorymanage.domain.YxGraduate;
import org.king.yangong.dormitorymanage.domain.YxGzdormapply;
import org.king.yangong.dormitorymanage.service.DormAppService;
import org.king.yangong.dormitorymanage.service.DormTypeManageService;
import org.king.yangong.dormitorymanage.service.YxGraduateService;
import org.springframework.orm.hibernate.HibernateCallback;

public class DormAppServiceImpl implements DormAppService {

	private BaseDAO baseDAO;
	private AllDAO allDAO;
	private DictionaryService dictionaryService;
	private YxGraduateService yxGraduateService;

	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}
	public void setAllDAO(AllDAO allDAO) {
		this.allDAO = allDAO;
	}
	public List getGzList(DynaActionForm graduateSearchForm, String page) {
		List li = new ArrayList();
		StringBuffer hqlStrBuf = 
			new StringBuffer("select new Map(a.id as id,a.studentNo as studentNo,b.stuName as stuName," +
					"b.gender as gender,c.dictCaption as district ,a.curAddress as curAddress," +
					"a.curTelephone as curTelephone,a.ifNeedDorm as ifNeedDorm,a.ifGiveDorm as ifGiveDorm,a.memo as memo,a.updateTime as updateTime) "
				+ " from YxGzdormapply a,Studentmodel b,Dictionary c");
		StringBuffer whereStrBuf = 
			new StringBuffer(" where 1=1 and a.enrollNo=b.enterenceNo " +
					" and c.id.dictNo = 23 and c.id.dictValue = a.district and b.enrollYear='"+DateUtil.getNow("yyyy")+"'");
		MyQuery mq = new MyQuery();
		
		if(graduateSearchForm.getString("graduateNoSearch") != null && !graduateSearchForm.getString("graduateNoSearch").equals("")){
			whereStrBuf.append(" and a.studentNo like ?");
			mq.addPara("%" + graduateSearchForm.getString("graduateNoSearch") + "%", Types.VARCHAR);
		}
		if(graduateSearchForm.getString("graduateNameSearch") != null && !graduateSearchForm.getString("graduateNameSearch").equals("")){
			whereStrBuf.append(" and b.stuName like ?");
			mq.addPara("%" + graduateSearchForm.getString("graduateNameSearch") + "%", Types.VARCHAR);
		}
		if(graduateSearchForm.getString("studentTypeSearch") != null && !graduateSearchForm.getString("studentTypeSearch").equals("")){
			whereStrBuf.append(" and b.gender = ?");
			mq.addPara(graduateSearchForm.getString("studentTypeSearch"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("matriculateTypeSearch") != null && !graduateSearchForm.getString("matriculateTypeSearch").equals("")){
			whereStrBuf.append(" and a.district = ?");
			mq.addPara(graduateSearchForm.getString("matriculateTypeSearch"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("curCollegeSearch") != null && !graduateSearchForm.getString("curCollegeSearch").equals("")){
			whereStrBuf.append(" and b.yxClass.classId = ?");
			mq.addPara(graduateSearchForm.getString("curCollegeSearch"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("specialitySearch") != null && !graduateSearchForm.getString("specialitySearch").equals("")){
			whereStrBuf.append(" and a.ifNeedDorm = ?");
			mq.addPara(graduateSearchForm.getString("specialitySearch"), Types.VARCHAR);
		}
		if (StringUtils.isNumeric(page)) {
			mq.setPageStartNo(Integer.parseInt(page));
		} else {
			mq.setPageStartNo(0);
		}
		whereStrBuf.append(" order by a.studentNo asc");

		hqlStrBuf.append(whereStrBuf);
		mq.setQueryString(hqlStrBuf.toString());
		li = baseDAO.findEntity(mq);
		return li;
	}
	
	public List getGzListExport(DynaActionForm graduateSearchForm, String page) {
		List li = new ArrayList();
		StringBuffer hqlStrBuf = 
			new StringBuffer("select new Map(a.id as id,a.studentNo as studentNo,b.stuName as stuName," +
					"b.gender as gender,c.dictCaption as district ,a.curAddress as curAddress," +
					"a.curTelephone as curTelephone,a.ifNeedDorm as ifNeedDorm,a.ifGiveDorm as ifGiveDorm,a.memo as memo,a.updateTime as updateTime) "
				+ " from YxGzdormapply a,Studentmodel b,Dictionary c");
		StringBuffer whereStrBuf = 
			new StringBuffer(" where 1=1 and a.enrollNo=b.enterenceNo " +
					" and c.id.dictNo = 23 and c.id.dictValue = a.district and b.enrollYear='"+DateUtil.getNow("yyyy")+"'");
		MyQuery mq = new MyQuery();
		
		if(graduateSearchForm.getString("graduateNoSearch") != null && !graduateSearchForm.getString("graduateNoSearch").equals("")){
			whereStrBuf.append(" and a.studentNo like ?");
			mq.addPara("%" + graduateSearchForm.getString("graduateNoSearch") + "%", Types.VARCHAR);
		}
		if(graduateSearchForm.getString("graduateNameSearch") != null && !graduateSearchForm.getString("graduateNameSearch").equals("")){
			whereStrBuf.append(" and b.stuName like ?");
			mq.addPara("%" + graduateSearchForm.getString("graduateNameSearch") + "%", Types.VARCHAR);
		}
		if(graduateSearchForm.getString("studentTypeSearch") != null && !graduateSearchForm.getString("studentTypeSearch").equals("")){
			whereStrBuf.append(" and b.gender = ?");
			mq.addPara(graduateSearchForm.getString("studentTypeSearch"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("matriculateTypeSearch") != null && !graduateSearchForm.getString("matriculateTypeSearch").equals("")){
			whereStrBuf.append(" and a.district = ?");
			mq.addPara(graduateSearchForm.getString("matriculateTypeSearch"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("curCollegeSearch") != null && !graduateSearchForm.getString("curCollegeSearch").equals("")){
			whereStrBuf.append(" and b.yxClass.classId = ?");
			mq.addPara(graduateSearchForm.getString("curCollegeSearch"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("specialitySearch") != null && !graduateSearchForm.getString("specialitySearch").equals("")){
			whereStrBuf.append(" and a.ifNeedDorm = ?");
			mq.addPara(graduateSearchForm.getString("specialitySearch"), Types.VARCHAR);
		}
//		if (StringUtils.isNumeric(page)) {
//			mq.setPageStartNo(Integer.parseInt(page));
//		} else {
//			mq.setPageStartNo(0);
//		}
		
		whereStrBuf.append(" order by a.studentNo asc");

		hqlStrBuf.append(whereStrBuf);
		mq.setQueryString(hqlStrBuf.toString());
		li = baseDAO.findEntity(mq);
		return li;
	}
	
	public Integer getGzListCount(DynaActionForm graduateSearchForm) {
		List li = new ArrayList();
		StringBuffer hqlStrBuf = 
			new StringBuffer("select count(a.id) as count "
				+ " from YxGzdormapply a,Studentmodel b,Dictionary c ");
		StringBuffer whereStrBuf = 
			new StringBuffer(" where 1=1 and a.enrollNo=b.enterenceNo " +
					" and c.id.dictNo=23 and c.id.dictValue=a.district and b.enrollYear='"+DateUtil.getNow("yyyy")+"'");
		MyQuery mq = new MyQuery();
		
		if(graduateSearchForm.getString("graduateNoSearch") != null && !graduateSearchForm.getString("graduateNoSearch").equals("")){
			whereStrBuf.append(" and a.studentNo like ?");
			mq.addPara("%" + graduateSearchForm.getString("graduateNoSearch") + "%", Types.VARCHAR);
		}
		if(graduateSearchForm.getString("graduateNameSearch") != null && !graduateSearchForm.getString("graduateNameSearch").equals("")){
			whereStrBuf.append(" and b.stuName like ?");
			mq.addPara("%" + graduateSearchForm.getString("graduateNameSearch") + "%", Types.VARCHAR);
		}
		if(graduateSearchForm.getString("studentTypeSearch") != null && !graduateSearchForm.getString("studentTypeSearch").equals("")){
			whereStrBuf.append(" and b.gender = ?");
			mq.addPara(graduateSearchForm.getString("studentTypeSearch"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("matriculateTypeSearch") != null && !graduateSearchForm.getString("matriculateTypeSearch").equals("")){
			whereStrBuf.append(" and a.district = ?");
			mq.addPara(graduateSearchForm.getString("matriculateTypeSearch"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("curCollegeSearch") != null && !graduateSearchForm.getString("curCollegeSearch").equals("")){
			whereStrBuf.append(" and b.yxClass.classId = ?");
			mq.addPara(graduateSearchForm.getString("curCollegeSearch"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("specialitySearch") != null && !graduateSearchForm.getString("specialitySearch").equals("")){
			whereStrBuf.append(" and a.ifNeedDorm = ?");
			mq.addPara(graduateSearchForm.getString("specialitySearch"), Types.VARCHAR);
		}
//		if (StringUtils.isNumeric(page)) {
//			mq.setPageStartNo(Integer.parseInt(page));
//		} else {
//			mq.setPageStartNo(0);
//		}
//		whereStrBuf.append(" order by a.updateTime desc");
		mq.setPageStartNo(0);
		hqlStrBuf.append(whereStrBuf);
		mq.setQueryString(hqlStrBuf.toString());
		li = baseDAO.findEntity(mq);
		Integer count = (Integer)li.get(0);
		return count;
	}
	
	public List getGzList4NeedDorm(DynaActionForm graduateSearchForm, String page) {
		List li = new ArrayList();
		StringBuffer hqlStrBuf = 
			new StringBuffer("select new Map(a.id as id,a.studentNo as stuNo,a.enrollNo as enterenceNo,b.stuName as stuName," +
					"b.gender as gender,a.district as district ,a.curAddress as curAddress," +
					"a.curTelephone as curTelephone,a.ifNeedDorm as ifNeedDorm,a.ifGiveDorm as ifGiveDorm,a.memo as memo) "
				+ " from YxGzdormapply a,Studentmodel b");
		StringBuffer whereStrBuf = 
			new StringBuffer(" where 1=1 and a.enrollNo=b.enterenceNo " +
					" and a.ifNeedDorm='1' and b.enrollYear='"+DateUtil.getNow("yyyy")+"'");
		MyQuery mq = new MyQuery();
		
		if(graduateSearchForm.getString("graduateNoSearch") != null && !graduateSearchForm.getString("graduateNoSearch").equals("")){
			whereStrBuf.append(" and a.studentNo like ?");
			mq.addPara("%" + graduateSearchForm.getString("graduateNoSearch") + "%", Types.VARCHAR);
		}
		if(graduateSearchForm.getString("graduateNameSearch") != null && !graduateSearchForm.getString("graduateNameSearch").equals("")){
			whereStrBuf.append(" and b.stuName like ?");
			mq.addPara("%" + graduateSearchForm.getString("graduateNameSearch") + "%", Types.VARCHAR);
		}
		if(graduateSearchForm.getString("studentTypeSearch") != null && !graduateSearchForm.getString("studentTypeSearch").equals("")){
			whereStrBuf.append(" and b.gender = ?");
			mq.addPara(graduateSearchForm.getString("studentTypeSearch"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("matriculateTypeSearch") != null && !graduateSearchForm.getString("matriculateTypeSearch").equals("")){
			whereStrBuf.append(" and a.district = ?");
			mq.addPara(graduateSearchForm.getString("matriculateTypeSearch"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("curCollegeSearch") != null && !graduateSearchForm.getString("curCollegeSearch").equals("")){
			whereStrBuf.append(" and b.yxClass.classId = ?");
			mq.addPara(graduateSearchForm.getString("curCollegeSearch"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("specialitySearch") != null && !graduateSearchForm.getString("specialitySearch").equals("")){
			whereStrBuf.append(" and a.ifGiveDorm = ?");
			mq.addPara(graduateSearchForm.getString("specialitySearch"), Types.VARCHAR);
		}
		if (StringUtils.isNumeric(page)) {
			mq.setPageStartNo(Integer.parseInt(page));
		} else {
			mq.setPageStartNo(0);
		}
		whereStrBuf.append(" order by a.studentNo asc");

		hqlStrBuf.append(whereStrBuf);
		mq.setQueryString(hqlStrBuf.toString());
		li = baseDAO.findEntity(mq);
		return li;
	}
	
	public List getGzList4NeedDormExport(DynaActionForm graduateSearchForm) {
		List li = new ArrayList();
		StringBuffer hqlStrBuf = 
			new StringBuffer("select new Map(a.id as id,b.studentNo as stuNo,a.enrollNo as enterenceNo,b.stuName as stuName," +
					"b.gender as gender,a.district as district ,a.curAddress as curAddress," +
					"a.curTelephone as curTelephone,a.ifNeedDorm as ifNeedDorm,a.ifGiveDorm as ifGiveDorm,a.memo as memo) "
				+ " from YxGzdormapply a,Studentmodel b");
		StringBuffer whereStrBuf = 
			new StringBuffer(" where 1=1 and a.enrollNo=b.enterenceNo " +
					" and a.ifNeedDorm='1' and b.enrollYear='"+DateUtil.getNow("yyyy")+"'");
		MyQuery mq = new MyQuery();
		
		if(graduateSearchForm.getString("graduateNoSearch") != null && !graduateSearchForm.getString("graduateNoSearch").equals("")){
			whereStrBuf.append(" and a.studentNo like ?");
			mq.addPara("%" + graduateSearchForm.getString("graduateNoSearch") + "%", Types.VARCHAR);
		}
		if(graduateSearchForm.getString("graduateNameSearch") != null && !graduateSearchForm.getString("graduateNameSearch").equals("")){
			whereStrBuf.append(" and b.stuName like ?");
			mq.addPara("%" + graduateSearchForm.getString("graduateNameSearch") + "%", Types.VARCHAR);
		}
		if(graduateSearchForm.getString("studentTypeSearch") != null && !graduateSearchForm.getString("studentTypeSearch").equals("")){
			whereStrBuf.append(" and b.gender = ?");
			mq.addPara(graduateSearchForm.getString("studentTypeSearch"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("matriculateTypeSearch") != null && !graduateSearchForm.getString("matriculateTypeSearch").equals("")){
			whereStrBuf.append(" and a.district = ?");
			mq.addPara(graduateSearchForm.getString("matriculateTypeSearch"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("curCollegeSearch") != null && !graduateSearchForm.getString("curCollegeSearch").equals("")){
			whereStrBuf.append(" and b.yxClass.classId = ?");
			mq.addPara(graduateSearchForm.getString("curCollegeSearch"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("specialitySearch") != null && !graduateSearchForm.getString("specialitySearch").equals("")){
			whereStrBuf.append(" and a.ifGiveDorm = ?");
			mq.addPara(graduateSearchForm.getString("specialitySearch"), Types.VARCHAR);
		}

		whereStrBuf.append(" order by a.studentNo asc");

		hqlStrBuf.append(whereStrBuf);
		mq.setPageStartNo(0);
		mq.setQueryString(hqlStrBuf.toString());
		li = baseDAO.findEntity(mq);
		return li;
	}	
	
	public Integer getGzList4NeedDormCount(DynaActionForm graduateSearchForm) {
		List li = new ArrayList();
		StringBuffer hqlStrBuf = 
			new StringBuffer("select count(a.id) as count "
				+ " from YxGzdormapply a,Studentmodel b");
		StringBuffer whereStrBuf = 
			new StringBuffer(" where 1=1 and a.enrollNo=b.enterenceNo " +
					" and a.ifNeedDorm='1' and b.enrollYear='"+DateUtil.getNow("yyyy")+"'");
		MyQuery mq = new MyQuery();
		
		if(graduateSearchForm.getString("graduateNoSearch") != null && !graduateSearchForm.getString("graduateNoSearch").equals("")){
			whereStrBuf.append(" and a.studentNo like ?");
			mq.addPara("%" + graduateSearchForm.getString("graduateNoSearch") + "%", Types.VARCHAR);
		}
		if(graduateSearchForm.getString("graduateNameSearch") != null && !graduateSearchForm.getString("graduateNameSearch").equals("")){
			whereStrBuf.append(" and b.stuName like ?");
			mq.addPara("%" + graduateSearchForm.getString("graduateNameSearch") + "%", Types.VARCHAR);
		}
		if(graduateSearchForm.getString("studentTypeSearch") != null && !graduateSearchForm.getString("studentTypeSearch").equals("")){
			whereStrBuf.append(" and b.gender = ?");
			mq.addPara(graduateSearchForm.getString("studentTypeSearch"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("matriculateTypeSearch") != null && !graduateSearchForm.getString("matriculateTypeSearch").equals("")){
			whereStrBuf.append(" and a.district = ?");
			mq.addPara(graduateSearchForm.getString("matriculateTypeSearch"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("curCollegeSearch") != null && !graduateSearchForm.getString("curCollegeSearch").equals("")){
			whereStrBuf.append(" and b.yxClass.classId = ?");
			mq.addPara(graduateSearchForm.getString("curCollegeSearch"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("specialitySearch") != null && !graduateSearchForm.getString("specialitySearch").equals("")){
			whereStrBuf.append(" and a.ifGiveDorm = ?");
			mq.addPara(graduateSearchForm.getString("specialitySearch"), Types.VARCHAR);
		}
		
//		if (StringUtils.isNumeric(page)) {
//			mq.setPageStartNo(Integer.parseInt(page));
//		} else {
//			mq.setPageStartNo(0);
//		}
		mq.setPageStartNo(0);
//		whereStrBuf.append(" order by a.updateTime desc");

		hqlStrBuf.append(whereStrBuf);
		mq.setQueryString(hqlStrBuf.toString());
		li = baseDAO.findEntity(mq);
		
		Integer count = (Integer)li.get(0);
		return count;

	}
	public List getGraduateList(DynaActionForm graduateSearchForm,String page,String operator) {
		
		List li = new ArrayList();
		StringBuffer hqlStrBuf = 
			new StringBuffer("select new Map(a.id as id,a.graduateNo as graduateNo,a.graduateName as graduateName," +
					"b.dictCaption as studentType,a.matriculateType as matriculateType,a.curCollege as curCollege," +
					"a.speciality as speciality,a.residentNeed as residentNeed,a.lengthofschool as lengthofschool,a.sex as sex," +
					"a.graduateType as graduateType,a.distriction as distriction,a.registerTime as registerTime,a.memo as memo) "
				+ " from YxGraduate a,Dictionary b,Department d,Dictionary e,TabSsManager f ");
		StringBuffer whereStrBuf = 
			new StringBuffer(" where 1=1 and a.requestAvailable='1' and a.enrollYear='"+DateUtil.getNow("yyyy")+"' " +
					" and (b.id.dictNo = 15 and a.studentType = b.id.dictValue) " +
					" and d.deptCode = a.curCollege "+
					" and f.tabSsDept.id = a.distriction and f.stuNo='"+operator+"' "+
					" and (e.id.dictNo = 28 and a.speciality = e.id.dictValue) ");

		MyQuery mq = new MyQuery();		
		if(graduateSearchForm.getString("graduateNoSearch") != null && !graduateSearchForm.getString("graduateNoSearch").equals("")){
			whereStrBuf.append(" and a.graduateNo like ?");
			mq.addPara("%" + graduateSearchForm.getString("graduateNoSearch") + "%", Types.VARCHAR);
		}
		if(graduateSearchForm.getString("graduateNameSearch") != null && !graduateSearchForm.getString("graduateNameSearch").equals("")){
			whereStrBuf.append(" and a.graduateName like ?");
			mq.addPara("%" + graduateSearchForm.getString("graduateNameSearch") + "%", Types.VARCHAR);
		}
		if(graduateSearchForm.getString("graduateNoSearch1") != null && !graduateSearchForm.getString("graduateNoSearch1").equals("")){
			whereStrBuf.append(" and a.graduateNo >= ?");
			mq.addPara( graduateSearchForm.getString("graduateNoSearch1"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("graduateNoSearch2") != null && !graduateSearchForm.getString("graduateNoSearch2").equals("")){
			whereStrBuf.append(" and a.graduateNo <= ?");
			mq.addPara( graduateSearchForm.getString("graduateNoSearch2"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("studentTypeSearch") != null && !graduateSearchForm.getString("studentTypeSearch").equals("")){
			whereStrBuf.append(" and a.studentType = ?");
			mq.addPara(graduateSearchForm.getString("studentTypeSearch"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("matriculateTypeSearch") != null && !graduateSearchForm.getString("matriculateTypeSearch").equals("")){
			whereStrBuf.append(" and a.matriculateType = ?");
			mq.addPara( graduateSearchForm.getString("matriculateTypeSearch"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("curCollegeSearch") != null && !graduateSearchForm.getString("curCollegeSearch").equals("")){
			whereStrBuf.append(" and a.curCollege = ?");
			mq.addPara(graduateSearchForm.getString("curCollegeSearch"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("specialitySearch") != null && !graduateSearchForm.getString("specialitySearch").equals("")){
			whereStrBuf.append(" and a.speciality = ?");
			mq.addPara(graduateSearchForm.getString("specialitySearch"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("sex") != null && !graduateSearchForm.getString("sex").equals("")){
			whereStrBuf.append(" and a.sex = ?");
			mq.addPara(graduateSearchForm.getString("sex"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("distriction") != null && !graduateSearchForm.getString("distriction").equals("")){
			whereStrBuf.append(" and a.distriction = ?");
			mq.addPara(graduateSearchForm.getString("distriction"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("residentneed") != null && !graduateSearchForm.getString("residentneed").equals("")){
			whereStrBuf.append(" and a.residentNeed = ?");
			mq.addPara(graduateSearchForm.getString("residentneed"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("graduateTypeSearch")!=null&&!graduateSearchForm.getString("graduateTypeSearch").equals("")){
			if(graduateSearchForm.getString("graduateTypeSearch").equals("NULL")){
				whereStrBuf.append(" and a.graduateType is null");
			}else{
				whereStrBuf.append(" and a.graduateType = ?");
				mq.addPara(graduateSearchForm.getString("graduateTypeSearch"), Types.VARCHAR);
			}
		}
		if(graduateSearchForm.getString("lengthofschoolSearch") != null && !graduateSearchForm.getString("lengthofschoolSearch").equals("")){
			whereStrBuf.append(" and a.lengthofschool = ?");
			mq.addPara(new Double(Double.parseDouble(graduateSearchForm.getString("lengthofschoolSearch"))), Types.DOUBLE);
		}
		if(graduateSearchForm.getString("memo") != null && !graduateSearchForm.getString("memo").equals("")){
			if(graduateSearchForm.getString("memo").equals("0")){
				whereStrBuf.append(" and (a.memo is null or a.memo='')");
			}else{
				whereStrBuf.append(" and a.memo is not null and a.memo<>''");
			}
		}
		if (StringUtils.isNumeric(page)) {
			mq.setPageStartNo(Integer.parseInt(page));
		} else {
			mq.setPageStartNo(0);
		}

		whereStrBuf.append(" order by a.id asc");

		hqlStrBuf.append(whereStrBuf);
		mq.setQueryString(hqlStrBuf.toString());
		li = baseDAO.findEntity(mq);
		
		List mli = dictionaryService.getDictionaryList("16");
		List sli = dictionaryService.getDictionaryList("28");
		List dli = yxGraduateService.getCollegeListFromGraduateTable();
		List dtli = baseDAO.findEntity("select new map(a.id as id,a.graduateType as graduateType,b.personName as updator,a.updateTime as updateTime) "
				+ " from GraduateType a,Person b where 1=1 and a.ifdeleted='1' and a.updator = b.id");
		for(int i1=0; i1<li.size();i1++){
			Map lim = (Map)li.get(i1);
			if(lim.get("matriculateType")!=null){
				for(int j1=0;j1<mli.size();j1++){
					if(lim.get("matriculateType").equals(((Map)mli.get(j1)).get("dictValue"))){
						lim.put("matriculateType", ((Map)mli.get(j1)).get("dictCaption"));
						break;
					}
				}
			}else{
				lim.put("matriculateType", " ");
			}
			if(lim.get("speciality")!=null){
				for(int k1=0;k1<sli.size();k1++){
					if(lim.get("speciality").equals(((Map)sli.get(k1)).get("dictValue"))){
						lim.put("speciality", ((Map)sli.get(k1)).get("dictCaption"));
						break;
					}
				}	
			}else{
				lim.put("speciality", " ");
			}
			if(lim.get("curCollege")!=null){
				for(int m1=0;m1<dli.size();m1++){
					if(lim.get("curCollege").equals(((Department)dli.get(m1)).getDeptCode())){
						lim.put("curCollege", ((Department)dli.get(m1)).getDeptName());
						break;
					}
				}
			}else{
				lim.put("curCollege", " ");
			}
			if(lim.get("graduateType")!=null){
				for(int n1=0;n1<dtli.size();n1++){
					if(lim.get("graduateType").equals(((Map)dtli.get(n1)).get("id"))){
						lim.put("graduateType", ((Map)dtli.get(n1)).get("graduateType"));
						break;
					}
				}
			}else{
				lim.put("graduateType", " ");
			}
			if (lim.get("distriction") != null) {
				List cap_list = baseDAO.findEntity
						("select a.name from TabSsDept a where a.id='"
								+ lim.get("distriction") + "'");

				if (cap_list.size() > 0) {
					String Cap = cap_list.get(0).toString();
					lim.put("distriction", Cap);
				}
			}else{
				lim.put("distriction", " ");
			}
		}
		return li;
	}
	public List getGraduateList(DynaActionForm graduateSearchForm,String page) {
		List li = new ArrayList();
		StringBuffer hqlStrBuf = 
			new StringBuffer("select new Map(a.id as id,a.graduateNo as graduateNo,a.graduateName as graduateName," +
					"b.dictCaption as studentType,a.matriculateType as matriculateType,a.curCollege as curCollege," +
					"a.speciality as speciality,a.residentNeed as residentNeed,a.lengthofschool as lengthofschool,a.sex as sex," +
					"a.graduateType as graduateType,a.registerTime as registerTime,a.memo as memo) "
				+ " from YxGraduate a,Dictionary b,Department d,Dictionary e ");
		StringBuffer whereStrBuf = 
			new StringBuffer(" where 1=1 and a.requestAvailable='1' " +
					" and (b.id.dictNo = 15 and a.studentType = b.id.dictValue) " +
					" and d.deptCode = a.curCollege "+
					" and (e.id.dictNo = 28 and a.speciality = e.id.dictValue) ");
	
		
		MyQuery mq = new MyQuery();		
		if(graduateSearchForm.getString("graduateNoSearch") != null && !graduateSearchForm.getString("graduateNoSearch").equals("")){
			whereStrBuf.append(" and a.graduateNo like ?");
			mq.addPara("%" + graduateSearchForm.getString("graduateNoSearch") + "%", Types.VARCHAR);
		}
		if(graduateSearchForm.getString("graduateNameSearch") != null && !graduateSearchForm.getString("graduateNameSearch").equals("")){
			whereStrBuf.append(" and a.graduateName like ?");
			mq.addPara("%" + graduateSearchForm.getString("graduateNameSearch") + "%", Types.VARCHAR);
		}
		if(graduateSearchForm.getString("graduateNoSearch1") != null && !graduateSearchForm.getString("graduateNoSearch1").equals("")){
			whereStrBuf.append(" and a.graduateNo >= ?");
			mq.addPara( graduateSearchForm.getString("graduateNoSearch1"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("graduateNoSearch2") != null && !graduateSearchForm.getString("graduateNoSearch2").equals("")){
			whereStrBuf.append(" and a.graduateNo <= ?");
			mq.addPara( graduateSearchForm.getString("graduateNoSearch2"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("studentTypeSearch") != null && !graduateSearchForm.getString("studentTypeSearch").equals("")){
			whereStrBuf.append(" and a.studentType = ?");
			mq.addPara(graduateSearchForm.getString("studentTypeSearch"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("matriculateTypeSearch") != null && !graduateSearchForm.getString("matriculateTypeSearch").equals("")){
			whereStrBuf.append(" and a.matriculateType = ?");
			mq.addPara( graduateSearchForm.getString("matriculateTypeSearch"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("sex") != null && !graduateSearchForm.getString("sex").equals("")){
			whereStrBuf.append(" and a.sex = ?");
			mq.addPara(graduateSearchForm.getString("sex"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("distriction") != null && !graduateSearchForm.getString("distriction").equals("")){
			whereStrBuf.append(" and a.distriction = ?");
			mq.addPara(graduateSearchForm.getString("distriction"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("residentneed") != null && !graduateSearchForm.getString("residentneed").equals("")){
			whereStrBuf.append(" and a.residentNeed = ?");
			mq.addPara(graduateSearchForm.getString("residentneed"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("curCollegeSearch") != null && !graduateSearchForm.getString("curCollegeSearch").equals("")){
			whereStrBuf.append(" and a.curCollege = ?");
			mq.addPara(graduateSearchForm.getString("curCollegeSearch"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("specialitySearch") != null && !graduateSearchForm.getString("specialitySearch").equals("")){
			whereStrBuf.append(" and a.speciality = ?");
			mq.addPara(graduateSearchForm.getString("specialitySearch"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("graduateTypeSearch") != null && !graduateSearchForm.getString("graduateTypeSearch").equals("")){
			whereStrBuf.append(" and a.graduateType = ?");
			mq.addPara(graduateSearchForm.getString("graduateTypeSearch"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("lengthofschoolSearch") != null && !graduateSearchForm.getString("lengthofschoolSearch").equals("")){
			whereStrBuf.append(" and a.lengthofschool = ?");
			mq.addPara(new Double(Double.parseDouble(graduateSearchForm.getString("lengthofschoolSearch"))), Types.DOUBLE);
		}		
		if(graduateSearchForm.getString("memo") != null && !graduateSearchForm.getString("memo").equals("")){
			if(graduateSearchForm.getString("memo").equals("0")){
				whereStrBuf.append(" and (a.memo is null or a.memo='')");
			}else{
				whereStrBuf.append(" and a.memo is not null and a.memo<>''");
			}
		}
		if (StringUtils.isNumeric(page)) {
			mq.setPageStartNo(Integer.parseInt(page));
		} else {
			mq.setPageStartNo(0);
		}

		whereStrBuf.append(" order by a.id asc");

		hqlStrBuf.append(whereStrBuf);
		mq.setQueryString(hqlStrBuf.toString());
		li = baseDAO.findEntity(mq);
		
		List mli = dictionaryService.getDictionaryList("16");
		List sli = dictionaryService.getDictionaryList("28");
		List dli = yxGraduateService.getCollegeListFromGraduateTable();
		List dtli = baseDAO.findEntity("select new map(a.id as id,a.graduateType as graduateType,b.personName as updator,a.updateTime as updateTime) "
				+ " from GraduateType a,Person b where 1=1 and a.ifdeleted='1' and a.updator = b.id");
		for(int i1=0; i1<li.size();i1++){
			Map lim = (Map)li.get(i1);
			if(lim.get("matriculateType")!=null){
				for(int j1=0;j1<mli.size();j1++){
					if(lim.get("matriculateType").equals(((Map)mli.get(j1)).get("dictValue"))){
						lim.put("matriculateType", ((Map)mli.get(j1)).get("dictCaption"));
						break;
					}
				}
			}else{
				lim.put("matriculateType", " ");
				break;
			}
			if(lim.get("speciality")!=null){
				for(int k1=0;k1<sli.size();k1++){
					if(lim.get("speciality").equals(((Map)sli.get(k1)).get("dictValue"))){
						lim.put("speciality", ((Map)sli.get(k1)).get("dictCaption"));
						break;
					}
				}	
			}else{
				lim.put("speciality", " ");
				break;
			}
			if(lim.get("curCollege")!=null){
				for(int m1=0;m1<dli.size();m1++){
					if(lim.get("curCollege").equals(((Department)dli.get(m1)).getDeptCode())){
						lim.put("curCollege", ((Department)dli.get(m1)).getDeptName());
						break;
					}
				}
			}else{
				lim.put("curCollege", " ");
				break;
			}
			if(lim.get("graduateType")!=null){
				for(int n1=0;n1<dtli.size();n1++){
					if(lim.get("graduateType").equals(((Map)dtli.get(n1)).get("id"))){
						lim.put("graduateType", ((Map)dtli.get(n1)).get("graduateType"));
						break;
					}
				}
			}else{
				lim.put("graduateType", " ");
				break;
			}
		}
		return li;
	}
	public List getGraduateListExport(DynaActionForm graduateSearchForm,String page,String operator) {
		
		List li = new ArrayList();
			
		StringBuffer hqlStrBuf = 
			new StringBuffer("select new Map(a.id as id,a.graduateNo as graduateNo,a.graduateName as graduateName,a.distriction as distriction," +
					"b.dictCaption as studentType,a.matriculateType as matriculateType,a.curCollege as curCollege,a.memo as memo," +
					"a.speciality as speciality,a.residentNeed as residentNeed,a.lengthofschool as lengthofschool,a.sex as sex,a.registerTime as registerTime," +
					"a.graduateType as graduateType,a.registerTime as registerTime,a.memo as memo) "
				+ " from YxGraduate a,Dictionary b,Department d,Dictionary e,TabSsManager f ");
		StringBuffer whereStrBuf = 
			new StringBuffer(" where 1=1 and a.requestAvailable='1' and a.enrollYear='"+DateUtil.getNow("yyyy")+"' " +
					" and (b.id.dictNo = 15 and a.studentType = b.id.dictValue) " +
					" and d.deptCode = a.curCollege "+
					" and f.tabSsDept.id = a.distriction and f.stuNo='"+operator+"' "+
					" and (e.id.dictNo = 28 and a.speciality = e.id.dictValue) ");
	
		
		MyQuery mq = new MyQuery();		
		if(graduateSearchForm.getString("graduateNoSearch") != null && !graduateSearchForm.getString("graduateNoSearch").equals("")){
			whereStrBuf.append(" and a.graduateNo like ?");
			mq.addPara("%" + graduateSearchForm.getString("graduateNoSearch") + "%", Types.VARCHAR);
		}
		if(graduateSearchForm.getString("graduateNameSearch") != null && !graduateSearchForm.getString("graduateNameSearch").equals("")){
			whereStrBuf.append(" and a.graduateName like ?");
			mq.addPara("%" + graduateSearchForm.getString("graduateNameSearch") + "%", Types.VARCHAR);
		}
		if(graduateSearchForm.getString("graduateNoSearch1") != null && !graduateSearchForm.getString("graduateNoSearch1").equals("")){
			whereStrBuf.append(" and a.graduateNo >= ?");
			mq.addPara( graduateSearchForm.getString("graduateNoSearch1"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("graduateNoSearch2") != null && !graduateSearchForm.getString("graduateNoSearch2").equals("")){
			whereStrBuf.append(" and a.graduateNo <= ?");
			mq.addPara( graduateSearchForm.getString("graduateNoSearch2"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("studentTypeSearch") != null && !graduateSearchForm.getString("studentTypeSearch").equals("")){
			whereStrBuf.append(" and a.studentType = ?");
			mq.addPara(graduateSearchForm.getString("studentTypeSearch"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("matriculateTypeSearch") != null && !graduateSearchForm.getString("matriculateTypeSearch").equals("")){
			whereStrBuf.append(" and a.matriculateType = ?");
			mq.addPara( graduateSearchForm.getString("matriculateTypeSearch"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("sex") != null && !graduateSearchForm.getString("sex").equals("")){
			whereStrBuf.append(" and a.sex = ?");
			mq.addPara(graduateSearchForm.getString("sex"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("distriction") != null && !graduateSearchForm.getString("distriction").equals("")){
			whereStrBuf.append(" and a.distriction = ?");
			mq.addPara(graduateSearchForm.getString("distriction"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("residentneed") != null && !graduateSearchForm.getString("residentneed").equals("")){
			whereStrBuf.append(" and a.residentNeed = ?");
			mq.addPara(graduateSearchForm.getString("residentneed"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("curCollegeSearch") != null && !graduateSearchForm.getString("curCollegeSearch").equals("")){
			whereStrBuf.append(" and a.curCollege = ?");
			mq.addPara(graduateSearchForm.getString("curCollegeSearch"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("specialitySearch") != null && !graduateSearchForm.getString("specialitySearch").equals("")){
			whereStrBuf.append(" and a.speciality = ?");
			mq.addPara(graduateSearchForm.getString("specialitySearch"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("graduateTypeSearch") != null && !graduateSearchForm.getString("graduateTypeSearch").equals("")){
			whereStrBuf.append(" and a.graduateType = ?");
			mq.addPara(graduateSearchForm.getString("graduateTypeSearch"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("lengthofschoolSearch") != null && !graduateSearchForm.getString("lengthofschoolSearch").equals("")){
			whereStrBuf.append(" and a.lengthofschool = ?");
			mq.addPara(new Double(Double.parseDouble(graduateSearchForm.getString("lengthofschoolSearch"))), Types.DOUBLE);
		}		
		if(graduateSearchForm.getString("memo") != null && !graduateSearchForm.getString("memo").equals("")){
			if(graduateSearchForm.getString("memo").equals("0")){
				whereStrBuf.append(" and (a.memo is null or a.memo='')");
			}else{
				whereStrBuf.append(" and a.memo is not null and a.memo<>''");
			}
		}
		if (StringUtils.isNumeric(page)) {
			mq.setPageStartNo(Integer.parseInt(page));
		} else {
			mq.setPageStartNo(0);
		}

		whereStrBuf.append(" order by a.id asc");

		hqlStrBuf.append(whereStrBuf);
		mq.setQueryString(hqlStrBuf.toString());
		li = baseDAO.findEntity(mq);
		
		List mli = dictionaryService.getDictionaryList("16");
		List sli = dictionaryService.getDictionaryList("28");
		List dli = yxGraduateService.getCollegeListFromGraduateTable();
		List dtli = baseDAO.findEntity("select new map(a.id as id,a.graduateType as graduateType,b.personName as updator,a.updateTime as updateTime) "
				+ " from GraduateType a,Person b where 1=1 and a.ifdeleted='1' and a.updator = b.id");
		List disli = baseDAO.findEntity("select a from TabSsDept a");
		for(int i1=0; i1<li.size();i1++){
			Map lim = (Map)li.get(i1);
			if(lim.get("matriculateType")!=null){
				for(int j1=0;j1<mli.size();j1++){
					if(lim.get("matriculateType").equals(((Map)mli.get(j1)).get("dictValue"))){
						lim.put("matriculateType", ((Map)mli.get(j1)).get("dictCaption"));
						break;
					}
				}
			}else{
				lim.put("matriculateType", " ");
			}
			if(lim.get("distriction")!=null){
				for(int m1=0;m1<mli.size();m1++){
					if(lim.get("distriction").equals(((TabSsDept)disli.get(m1)).getId())){
						lim.put("distriction", ((TabSsDept)disli.get(m1)).getName());
						break;
					}
				}
			}else{
				lim.put("matriculateType", " ");
			}
			if(lim.get("speciality")!=null){
				for(int k1=0;k1<sli.size();k1++){
					if(lim.get("speciality").equals(((Map)sli.get(k1)).get("dictValue"))){
						lim.put("speciality", ((Map)sli.get(k1)).get("dictCaption"));
						break;
					}
				}	
			}else{
				lim.put("speciality", " ");
			}
			if(lim.get("curCollege")!=null){
				for(int m1=0;m1<dli.size();m1++){
					if(lim.get("curCollege").equals(((Department)dli.get(m1)).getDeptCode())){
						lim.put("curCollege", ((Department)dli.get(m1)).getDeptName());
						break;
					}
				}
			}else{
				lim.put("curCollege", " ");
			}
			if(lim.get("graduateType")!=null){
				for(int n1=0;n1<dtli.size();n1++){
					if(lim.get("graduateType").equals(((Map)dtli.get(n1)).get("id"))){
						lim.put("graduateType", ((Map)dtli.get(n1)).get("graduateType"));
						break;
					}
				}
			}else{
				lim.put("graduateType", " ");
			}
		}
		return li;
	}
	
	public Integer getGraduateListCount(DynaActionForm graduateSearchForm,String operator) {
		
		List li = new ArrayList();
			
		StringBuffer hqlStrBuf = 
			new StringBuffer("select count(a.id) as count "
				+ " from YxGraduate a,Dictionary b,Department d,Dictionary e,TabSsManager f ");
		StringBuffer whereStrBuf = 
			new StringBuffer(" where 1=1 and a.requestAvailable='1' and a.enrollYear='"+DateUtil.getNow("yyyy")+"' " +
					" and (b.id.dictNo = 15 and a.studentType = b.id.dictValue) " +
					" and d.deptCode = a.curCollege "+
					" and f.tabSsDept.id = a.distriction and f.stuNo='"+operator+"' "+	
					" and (e.id.dictNo = 28 and a.speciality = e.id.dictValue) ");
		
		MyQuery mq = new MyQuery();		
		if(graduateSearchForm.getString("graduateNoSearch") != null && !graduateSearchForm.getString("graduateNoSearch").equals("")){
			whereStrBuf.append(" and a.graduateNo like ?");
			mq.addPara("%" + graduateSearchForm.getString("graduateNoSearch") + "%", Types.VARCHAR);
		}
		if(graduateSearchForm.getString("graduateNoSearch1") != null && !graduateSearchForm.getString("graduateNoSearch1").equals("")){
			whereStrBuf.append(" and a.graduateNo > ?");
			mq.addPara( graduateSearchForm.getString("graduateNoSearch1"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("graduateNoSearch2") != null && !graduateSearchForm.getString("graduateNoSearch2").equals("")){
			whereStrBuf.append(" and a.graduateNo < ?");
			mq.addPara( graduateSearchForm.getString("graduateNoSearch2"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("graduateNameSearch") != null && !graduateSearchForm.getString("graduateNameSearch").equals("")){
			whereStrBuf.append(" and a.graduateName like ?");
			mq.addPara("%" + graduateSearchForm.getString("graduateNameSearch") + "%", Types.VARCHAR);
		}
		if(graduateSearchForm.getString("sex") != null && !graduateSearchForm.getString("sex").equals("")){
			whereStrBuf.append(" and a.sex = ?");
			mq.addPara(graduateSearchForm.getString("sex"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("studentTypeSearch") != null && !graduateSearchForm.getString("studentTypeSearch").equals("")){
			whereStrBuf.append(" and a.studentType = ?");
			mq.addPara(graduateSearchForm.getString("studentTypeSearch"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("matriculateTypeSearch") != null && !graduateSearchForm.getString("matriculateTypeSearch").equals("")){
			whereStrBuf.append(" and a.matriculateType = ?");
			mq.addPara( graduateSearchForm.getString("matriculateTypeSearch"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("curCollegeSearch") != null && !graduateSearchForm.getString("curCollegeSearch").equals("")){
			whereStrBuf.append(" and a.curCollege = ?");
			mq.addPara(graduateSearchForm.getString("curCollegeSearch"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("specialitySearch") != null && !graduateSearchForm.getString("specialitySearch").equals("")){
			whereStrBuf.append(" and a.speciality = ?");
			mq.addPara(graduateSearchForm.getString("specialitySearch"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("lengthofschoolSearch") != null && !graduateSearchForm.getString("lengthofschoolSearch").equals("")){
			whereStrBuf.append(" and a.lengthofschool = ?");
			mq.addPara(new Double(Double.parseDouble(graduateSearchForm.getString("lengthofschoolSearch"))), Types.DOUBLE);
		}
		if(graduateSearchForm.getString("graduateTypeSearch") != null && !graduateSearchForm.getString("graduateTypeSearch").equals("")){
			whereStrBuf.append(" and a.graduateType = ?");
			mq.addPara(graduateSearchForm.getString("graduateTypeSearch"), Types.VARCHAR);
		}
			
		if(graduateSearchForm.getString("distriction") != null && !graduateSearchForm.getString("distriction").equals("")){
			whereStrBuf.append(" and a.distriction = ?");
			mq.addPara(graduateSearchForm.getString("distriction"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("residentneed") != null && !graduateSearchForm.getString("residentneed").equals("")){
			whereStrBuf.append(" and a.residentNeed = ?");
			mq.addPara(graduateSearchForm.getString("residentneed"), Types.VARCHAR);
		}
		if(graduateSearchForm.getString("memo") != null && !graduateSearchForm.getString("memo").equals("")){
			if(graduateSearchForm.getString("memo").equals("0")){
				whereStrBuf.append(" and (a.memo is null or a.memo='')");
			}else{
				whereStrBuf.append(" and a.memo is not null and a.memo<>''");
			}
		}
//		if (StringUtils.isNumeric(page)) {
//			mq.setPageStartNo(Integer.parseInt(page));
//		} else {
//			mq.setPageStartNo(0);
//		}
//
//		whereStrBuf.append(" order by a.id asc");
		mq.setPageStartNo(0);

		hqlStrBuf.append(whereStrBuf);
		mq.setQueryString(hqlStrBuf.toString());
		li = baseDAO.findEntity(mq);
		return (Integer)li.get(0);
	}

	public void updateDormTypeInfo(GraduateType graduateType) {
		// TODO Auto-generated method stub
		baseDAO.updateEntity(graduateType);
	}
	
	public void updateGraduateInfo(String[] itemlist,String requestAvailable){
		for(int i=0;i<itemlist.length;i++){
			YxGraduate graduate = (YxGraduate)baseDAO.getEntity(YxGraduate.class, itemlist[i]);
			graduate.setResidentNeed(requestAvailable);
			if(!graduate.getResidentNeed().equals(requestAvailable)){
				graduate.setRegisterTime(DateUtil.getNow("yyyy-MM-dd HH:mm"));
			}
			baseDAO.saveEntity(graduate);
		}
	}
	public void updateGraduateInfo(String[] itemlist, String[] itemlist2) {
		for(int i=0;i<itemlist.length;i++){
			int tag = 0;
			YxGraduate graduate = (YxGraduate)baseDAO.getEntity(YxGraduate.class, itemlist[i]);
			if(itemlist2!=null&&itemlist2.length!=0){
				for(int j=0;j<itemlist2.length;j++){				
					if(itemlist[i].equals(itemlist2[j])){
						if(graduate.getResidentNeed().equals("2")){
							graduate.setResidentNeed("1");
							graduate.setRegisterTime(DateUtil.getNow("yyyy-MM-dd HH:mm"));
							baseDAO.saveEntity(graduate);
							break;
						}
					}else{
						tag++;
					}			
				}
				if(tag==itemlist2.length){
					if(graduate.getResidentNeed().equals("1")){
						graduate.setResidentNeed("2");
						graduate.setRegisterTime(DateUtil.getNow("yyyy-MM-dd HH:mm"));
						baseDAO.saveEntity(graduate);
					}
				}
			}else{
				if(graduate.getResidentNeed().equals("1")){
						graduate.setResidentNeed("2");
						graduate.setRegisterTime(DateUtil.getNow("yyyy-MM-dd HH:mm"));
						baseDAO.saveEntity(graduate);
						continue;
				}
			}
		}
	}
	
	public void updateGZStudentInfo(String[] itemlist, String[] itemlist2) {
		for(int i=0;i<itemlist.length;i++){
			int tag = 0;
			YxGzdormapply gz = (YxGzdormapply)baseDAO.getEntity(YxGzdormapply.class, itemlist[i]);
			if(itemlist2!=null&&itemlist2.length!=0){
				for(int j=0;j<itemlist2.length;j++){				
					if(itemlist[i].equals(itemlist2[j])){
						if("0".equals(gz.getIfGiveDorm())){
							gz.setIfGiveDorm("1");
							gz.setUpdateTime(new Date());
							baseDAO.saveEntity(gz);
							break;
						}
					}else{
						tag++;
					}			
				}
				if(tag==itemlist2.length){
					if("1".equals(gz.getIfGiveDorm())){
						gz.setIfGiveDorm("0");
						gz.setUpdateTime(new Date());
						baseDAO.saveEntity(gz);
					}
				}
			}else{
				if("1".equals(gz.getIfGiveDorm())){
					gz.setIfGiveDorm("0");
					gz.setUpdateTime(new Date());
						baseDAO.saveEntity(gz);
						continue;
				}
			}
		}
		
	}
	public void updateGraduateInfo(String itemlist,String requestAvailable,String memo){
		
			YxGraduate graduate = (YxGraduate)baseDAO.getEntity(YxGraduate.class, itemlist);
			graduate.setResidentNeed(requestAvailable);
			graduate.setMemo(memo);
			graduate.setRegisterTime(DateUtil.getNow("yyyy-MM-dd HH:mm"));
			baseDAO.updateEntity(graduate);
	}
	public void updateGraduateInfo(String itemlist,String memo){
		YxGraduate graduate = (YxGraduate)baseDAO.getEntity(YxGraduate.class, itemlist);
		graduate.setMemo(memo);
		graduate.setRegisterTime(DateUtil.getNow("yyyy-MM-dd HH:mm"));
		baseDAO.updateEntity(graduate);
}
	public List getGraduate(String personCode) {
		List li = new ArrayList();
		StringBuffer hqlStrBuf = 
			new StringBuffer("select new Map(a.id as id,a.graduateNo as graduateNo,a.graduateName as graduateName,a.sex as gender," +
					"b.dictCaption as studentType,c.dictCaption as matriculateType,a.curCollege as curCollege," +
					"a.speciality as speciality,a.residentNeed as residentNeed,a.registerTime as updateDate,a.memo as memo,a.distriction as distriction) "
				+ " from YxGraduate a,Dictionary b,Dictionary c");
		StringBuffer whereStrBuf = 
			new StringBuffer(" where 1=1 and a.requestAvailable='1' " +
					" and (b.id.dictNo = 15 and a.studentType = b.id.dictValue) " +
					" and (c.id.dictNo = 16 and a.matriculateType = c.id.dictValue) ");

		MyQuery mq = new MyQuery();
		whereStrBuf.append(" and a.graduateNo = ?");
		mq.addPara(personCode, Types.VARCHAR);
		
		hqlStrBuf.append(whereStrBuf);
		mq.setQueryString(hqlStrBuf.toString());
		li = baseDAO.findEntity(mq);
		if(li!=null&&li.size()!=0){
			if("".equals(((Map)li.get(0)).get("memo"))||((Map)li.get(0)).get("memo")==null){
				((Map)li.get(0)).put("memo", "");
			}
			if("".equals(((Map)li.get(0)).get("registerTime"))||((Map)li.get(0)).get("registerTime")==null){
				((Map)li.get(0)).put("registerTime", "暂无");
			}
			if (((Map)li.get(0)).get("distriction") != null) {
				List cap_list = baseDAO.findEntity("select a.name from TabSsDept a where a.id='"
						+ (String)(((Map)li.get(0)).get("distriction")) + "'");

				if (cap_list.size() > 0) {
					String Cap = cap_list.get(0).toString();
					((Map)li.get(0)).put("distriction", Cap);
				}
			}
		}
		
		return li;
	}
	
	/*
	 * 统计院系、性别、应绑定人数
	 * @see org.king.yangong.dormitorymanage.service.DormAppService#list4BuildBundingTJ(org.apache.struts.action.DynaActionForm)
	 */
	public List list4DeptBundingTJ(DynaActionForm deptSearchForm) {
		List li = new ArrayList();
		String curYear = DateUtil.getNow("yyyy");
		StringBuffer hqlStrBuf = 
			new StringBuffer("select new Map(a.curCollege as deptCode,b.deptName as deptName,c.dictCaption as sex,a.sex as gender,count(a.id) as bundingNum,count(a.id) as bundedNum)" +
					" from YxGraduate a,Department b,Dictionary c ");
		
		StringBuffer whereStrBuf = 
			new StringBuffer(" where 1=1 and a.curCollege = b.deptCode and c.id.dictNo=1 and c.id.dictValue = a.sex and a.enrollYear = ? and a.residentNeed='1'");
		MyQuery mq = new MyQuery();
		mq.addPara(curYear, Types.VARCHAR);
		if(deptSearchForm.getString("deptcodeSearch") != null && !deptSearchForm.getString("deptcodeSearch").equals("")){
			whereStrBuf.append(" and a.curDepartment = ?");
			mq.addPara(deptSearchForm.getString("deptcodeSearch"), Types.VARCHAR);
		}
		if(deptSearchForm.getString("sexSearch") != null && !deptSearchForm.getString("sexSearch").equals("")){
			whereStrBuf.append(" and a.sex = ?");
			mq.addPara( deptSearchForm.getString("sexSearch"), Types.VARCHAR);
		}
		whereStrBuf.append(" group by a.curCollege,c.dictCaption,b.deptName,a.sex ");
		whereStrBuf.append(" order by a.curCollege,c.dictCaption,b.deptName,a.sex ");
		hqlStrBuf.append(whereStrBuf);
		mq.setQueryString(hqlStrBuf.toString());
		li = baseDAO.findEntity(mq);
		return li;
	}
	
	/*
	 * 统计院系、性别、已绑定人数
	 * @see org.king.yangong.dormitorymanage.service.DormAppService#list4BuildBundingTJ(org.apache.struts.action.DynaActionForm)
	 */
	public List list4DeptBundedTJ(DynaActionForm deptSearchForm) {
		List li = new ArrayList();
		String curYear = DateUtil.getNow().substring(0, 4);
		StringBuffer hqlStrBuf = 
			new StringBuffer("select new Map(a.classId as deptCode, a.sex as sex, sum(a.distributeNum) as bundedNum) " +
					" from ClassDorm a ");
		MyQuery mq = new MyQuery();
		StringBuffer whereStrBuf = 
			new StringBuffer(" where 1=1 and (a.studentType = 'M' or a.studentType='D') and a.curYear = ?");
		mq.addPara(curYear, Types.VARCHAR);
		if(deptSearchForm.getString("deptcodeSearch") != null && !deptSearchForm.getString("deptcodeSearch").equals("")){
			whereStrBuf.append(" and a.classId = ?");
			mq.addPara(deptSearchForm.getString("deptcodeSearch"), Types.VARCHAR);
		}
		if(deptSearchForm.getString("sexSearch") != null && !deptSearchForm.getString("sexSearch").equals("")){
			whereStrBuf.append(" and b.gender = ?");
			mq.addPara( deptSearchForm.getString("sexSearch"), Types.VARCHAR);
		}
		whereStrBuf.append(" group by a.classId ,a.sex ");
		whereStrBuf.append(" order by a.classId ,a.sex ");
		hqlStrBuf.append(whereStrBuf);
		mq.setQueryString(hqlStrBuf.toString());
		li = baseDAO.findEntity(mq);
		return li;
	}
	
	/*
	 * 合计、性别、应绑定人数
	 * @see org.king.yangong.dormitorymanage.service.DormAppService#list4BuildBundingTJ(org.apache.struts.action.DynaActionForm)
	 */
	public List list4DeptBundingTotalTJ(DynaActionForm deptSearchForm) {
		List li = new ArrayList();
		String curYear = DateUtil.getNow().substring(0, 4);
		StringBuffer hqlStrBuf = 
			new StringBuffer("select new Map(count(a.id) as bundingNum,count(a.id) as bundedNum)" +
					" from YxGraduate a "); 
		MyQuery mq = new MyQuery();
		StringBuffer whereStrBuf = 
			new StringBuffer(" where 1=1 and a.enrollYear = ? and a.residentNeed='1'");
		mq.addPara(curYear, Types.VARCHAR);
		if(deptSearchForm.getString("deptcodeSearch") != null && !deptSearchForm.getString("deptcodeSearch").equals("")){
			whereStrBuf.append(" and a.curDepartment = ?");
			mq.addPara(deptSearchForm.getString("deptcodeSearch"), Types.VARCHAR);
		}
		if(deptSearchForm.getString("sexSearch") != null && !deptSearchForm.getString("sexSearch").equals("")){
			whereStrBuf.append(" and a.sex = ?");
			mq.addPara( deptSearchForm.getString("sexSearch"), Types.VARCHAR);
		}
		hqlStrBuf.append(whereStrBuf);
		mq.setQueryString(hqlStrBuf.toString());
		li = baseDAO.findEntity(mq);
		return li;
	}
	
	/*
	 * 合计、性别、已绑定人数
	 * @see org.king.yangong.dormitorymanage.service.DormAppService#list4BuildBundingTJ(org.apache.struts.action.DynaActionForm)
	 */
	public List list4DeptBundedTotalTJ(DynaActionForm deptSearchForm) {
		List li = new ArrayList();
		String curYear = DateUtil.getNow().substring(0, 4);
		StringBuffer hqlStrBuf = 
			new StringBuffer("select new Map(sum(a.distributeNum) as bundedNum) " +
					"from ClassDorm a ");
		MyQuery mq = new MyQuery();
		StringBuffer whereStrBuf = 
			new StringBuffer(" where 1=1 and (a.studentType = 'M' or a.studentType = 'D') and a.curYear = ?");
		mq.addPara(curYear, Types.VARCHAR);
		if(deptSearchForm.getString("deptcodeSearch") != null && !deptSearchForm.getString("deptcodeSearch").equals("")){
			whereStrBuf.append(" and a.classId = ?");
			mq.addPara(deptSearchForm.getString("deptcodeSearch"), Types.VARCHAR);
		}
		if(deptSearchForm.getString("sexSearch") != null && !deptSearchForm.getString("sexSearch").equals("")){
			whereStrBuf.append(" and b.gender = ?");
			mq.addPara( deptSearchForm.getString("sexSearch"), Types.VARCHAR);
		}
		hqlStrBuf.append(whereStrBuf);
		mq.setQueryString(hqlStrBuf.toString());
		li = baseDAO.findEntity(mq);
		return li;
	}
	
	/*
	 * 院系绑定到哪些房间
	 * @see org.king.yangong.dormitorymanage.service.DormAppService#list4BuildBundingTJ(org.apache.struts.action.DynaActionForm)
	 */
	public List listDormBundByDept(String deptId) {
		List li = new ArrayList();
		String curYear = DateUtil.getNow().substring(0,4);
		StringBuffer hqlStrBuf = 
			new StringBuffer("select new Map(d.deptName as deptName,b.area as area, b.location as location,b.dormitory as dormitory,b.roomNumber as roomNumber, c.dictCaption as sex, a.distributeNum as distributeNum) " +
				"from ClassDorm a,Dormitorymodel b,Dictionary c,Department d ");
		MyQuery mq = new MyQuery();
		StringBuffer whereStrBuf = 
			new StringBuffer(" where 1=1 and a.dormId = b.dormitoryId and a.classId = d.deptCode and c.id.dictNo=1 and c.id.dictValue = b.gender and a.curYear = ? and a.classId = ?");
		mq.addPara(curYear, Types.VARCHAR);
		mq.addPara(deptId, Types.VARCHAR);
		whereStrBuf.append(" order by d.deptName,b.area ,b.location,b.dormitory,b.roomNumber,c.dictCaption,a.distributeNum ");
		hqlStrBuf.append(whereStrBuf);
		mq.setQueryString(hqlStrBuf.toString());
		li = baseDAO.findEntity(mq);
		List arli = dictionaryService.getDictionaryList("17");
		List loli = dictionaryService.getDictionaryList("20");
		List doli = dictionaryService.getDictionaryList("21");
		for(int i=0;i<li.size();i++){
			for(int i1=0;i<arli.size();i1++){
				if(((Map)li.get(i)).get("area").equals(((Map)arli.get(i1)).get("dictValue"))){
					((Map)li.get(i)).put("area", ((Map)arli.get(i1)).get("dictCaption"));
					break;
				}
			}
			for(int i2=0;i2<loli.size();i2++){
				if(((Map)li.get(i)).get("location").equals(((Map)loli.get(i2)).get("dictValue"))){
					((Map)li.get(i)).put("location", ((Map)loli.get(i2)).get("dictCaption"));
					break;
				}
			}
			for(int i3=0;i3<doli.size();i3++){
				if(((Map)li.get(i)).get("dormitory").equals(((Map)doli.get(i3)).get("dictValue"))){
					((Map)li.get(i)).put("dormitory", ((Map)doli.get(i3)).get("dictCaption"));
					break;
				}
			}
		}
		return li;
	}
	
	/*
	 * 统计楼号、可绑定人数、已绑定人数
	 * @see org.king.yangong.dormitorymanage.service.DormAppService#list4BuildBundingTJ(org.apache.struts.action.DynaActionForm)
	 */
	public List list4BuildBundingTJ(DynaActionForm buildBundSearchForm) {
		List li = new ArrayList();
		String curYear = DateUtil.getNow("yyyy");
		StringBuffer hqlStrBuf = 
			new StringBuffer("select new Map(d.dictCaption as area,e.dictCaption as location,f.dictCaption as dormitory,a.area as areaCode,a.location as locationCode,a.dormitory as dormitoryCode,sum(a.emptyNum) as canBundNum,sum(b.distributeNum) as bundedNum) " +
					"from Dormitorymodel a,ClassDorm b,TabSsDept c,Dictionary d,Dictionary e,Dictionary f "); 
		MyQuery mq = new MyQuery();
		StringBuffer whereStrBuf = 
			new StringBuffer(" where 1=1 and a.dormitoryId = b.dormId and b.curYear = ? and c.id = a.curDormDept and (b.studentType='M' or b.studentType='D')" +
					" and (d.id.dictNo = 17 and a.area = d.id.dictValue) and (e.id.dictNo = 20 and a.location = e.id.dictValue)and (f.id.dictNo = 21 and a.dormitory = f.id.dictValue)");
		mq.addPara(curYear, Types.VARCHAR);

		whereStrBuf.append(" group by a.area,a.location,a.dormitory,d.dictCaption,e.dictCaption,f.dictCaption");
		whereStrBuf.append(" order by d.dictCaption,e.dictCaption,a.dormitory");
		hqlStrBuf.append(whereStrBuf);
		mq.setQueryString(hqlStrBuf.toString());
		li = baseDAO.findEntity(mq);
		return li;
	}
	
	/*
	 * 房间绑定到那些院系
	 * @see org.king.yangong.dormitorymanage.service.DormAppService#list4BuildBundingTJ(org.apache.struts.action.DynaActionForm)
	 */
	public List listDormBundByDormitory(String areaCode,String locationCode,String dormitoryId) {
		List li = new ArrayList();
		String curYear = DateUtil.getNow("yyyy");
		StringBuffer hqlStrBuf = 
			new StringBuffer("select new Map(b.roomNumber as roomNumber,b.gender as gender,d.deptName as deptName,a.distributeNum as distributeNum) " +
				"from ClassDorm a,Dormitorymodel b,TabSsDept c,Department d");
		MyQuery mq = new MyQuery();
		StringBuffer whereStrBuf = 
			new StringBuffer(" where 1=1 and a.dormId = b.dormitoryId and a.classId = d.deptCode and a.curYear = ? and c.id = b.curDormDept and b.dormitory = ?" +
					" and b.area = ? and b.location = ? and (a.studentType='M' or a.studentType='D')");
		mq.addPara(curYear, Types.VARCHAR);
		mq.addPara(dormitoryId, Types.VARCHAR);
		mq.addPara(areaCode, Types.VARCHAR);
		mq.addPara(locationCode, Types.VARCHAR);
		whereStrBuf.append(" order by b.roomNumber,b.gender,d.deptName,a.distributeNum ");
		hqlStrBuf.append(whereStrBuf);
		mq.setQueryString(hqlStrBuf.toString());
		li = baseDAO.findEntity(mq);
		return li;
	}
	public List list4BuildBundingTotalTJ(DynaActionForm buildBundSearchForm) {
		List li = new ArrayList();
		String curYear = DateUtil.getNow().substring(0,4);
		StringBuffer hqlStrBuf = 
			new StringBuffer("select new Map(sum(a.emptyNum) as canBundNum,sum(b.distributeNum) as bundedNum) " +
					" from Dormitorymodel a,ClassDorm b,TabSsDept c"); 
		MyQuery mq = new MyQuery();
		StringBuffer whereStrBuf = 
			new StringBuffer(" where 1=1 and a.dormitoryId = b.dormId and b.curYear = ? and c.id = a.curDormDept and (b.studentType='M' or b.studentType='D')");
		mq.addPara(curYear, Types.VARCHAR);
		if(buildBundSearchForm.getString("locationSearch") != null && !buildBundSearchForm.getString("locationSearch").equals("")){
			whereStrBuf.append(" and a.location = ?");
			mq.addPara(buildBundSearchForm.getString("locationSearch"), Types.VARCHAR);
		}
		if(buildBundSearchForm.getString("dormitorySearch") != null && !buildBundSearchForm.getString("dormitorySearch").equals("")){
			whereStrBuf.append(" and a.dormitory like ?");
			mq.addPara("%" +buildBundSearchForm.getString("dormitorySearch")+ "%", Types.VARCHAR);
		}
		hqlStrBuf.append(whereStrBuf);
		mq.setQueryString(hqlStrBuf.toString());
		li = baseDAO.findEntity(mq);
		return li;
	}
	public Object getEntity(String deptId) {
		
		return (Department)baseDAO.getEntity(Department.class, deptId);
	}

	public List getDictionaryModel(int i, String areaCode) {
		List li = new ArrayList();
		String hqlStr = " select new Map(a.dictCaption as dictCaption) from Dictionary a where a.id.dictNo = "+ i +" and a.id.dictValue = '"+ areaCode+"'";
		li = baseDAO.findEntity(hqlStr);
		return li;
	}
	public YxGzdormapply getGzdormapply(String itemList) {
		
		return (YxGzdormapply)baseDAO.getEntity(YxGzdormapply.class, itemList);
	}
	public void deleteGzDormAppInfo(String[] itemList,HttpServletRequest request) {
		// TODO Auto-generated method stub
		if(itemList!=null&&itemList.length>0){
			String show = "";
			for(int i=0;i<itemList.length;i++){
				YxGzdormapply yg = (YxGzdormapply)baseDAO.getEntity(YxGzdormapply.class, itemList[i]);
				if(yg.getIfGiveDorm()==null||"0".equals(yg.getIfGiveDorm())){
					baseDAO.removeEntity(yg);
				}else{
					List st = (List)baseDAO.findEntity("select distinct a from Studentmodel a where a.majorin='623' and a.enterenceNo='"+yg.getEnrollNo()+"'");
					show+=((Studentmodel)st.get(0)).getStuName()+",";
				}
			}
			if(show.length()>0)
			    request.setAttribute("show", show.substring(0, show.length()-1));
		}
	}
	public List getStudentModel(String stren) {
		// TODO Auto-generated method stub
		String hql = "select a from Studentmodel a where 1=1 and a.enterenceNo='"+stren+"' and a.enrollYear='"+DateUtil.getNow("yyyy")+"' and a.studentType='03'";
		return (List)baseDAO.findEntity(hql);
	}	
	public List getGzdormapplyByStuNo(String stren) {
		// TODO Auto-generated method stub
		String hql = "select new Map(a.id as id,b.studentNo as stuNo,b.yxClass.classNo as classNo,a.enrollNo as enrollNo,b.stuName as stuName,b.gender as gender," +
				"c.dictCaption as district,a.curAddress as curAddress,a.curTelephone as curTelephone," +
				"a.ifNeedDorm as ifNeedDorm,a.memo as memo) " +
				"from YxGzdormapply a,Studentmodel b,Dictionary c " +
				"where 1=1 and a.enrollNo = b.enterenceNo and c.id.dictValue=a.district and c.id.dictNo=23 and b.enrollYear='"+DateUtil.getNow("yyyy")+"' and a.enrollNo='"+stren+"'";
		return (List)baseDAO.findEntity(hql);
	}
	public void saveGzdormappInfo(YxGzdormapply yg) {
		// TODO Auto-generated method stub
		baseDAO.saveEntity(yg);
	}
	public void updateGzdormappInfo(YxGzdormapply yg) {
		// TODO Auto-generated method stub
		baseDAO.updateEntity(yg);
	}
	public void updateGzDormAppModify(String[] itemlist, String str) {
		// TODO Auto-generated method stub
		for(int i=0;i<itemlist.length;i++){
			YxGzdormapply yg = (YxGzdormapply)baseDAO.getEntity(YxGzdormapply.class, itemlist[i]);
			yg.setIfGiveDorm(str);
			baseDAO.saveEntity(yg);
		}
	}
	public List getGzdormapplyByEnterenceNo(String str) {	
		return baseDAO.findEntity("from GzDormApply where enrollNo='"+str+"'");
	}
	public List getGzdormapplyByStudentNo(String str) {
		return baseDAO.findEntity("from GzDormApply where studentNo='"+str+"'");
	}

	public void initForm(HttpServletRequest request){
		
		// 所属区县
		List districtList = getDiction("23");
		request.setAttribute("districtList", districtList);
		
		String hql="select new Map(" +
		"c.id as id," +
		"c.graduateType as graduateType) " +
		"from GraduateType c " +
		"where 1=1 "  +
		" and c.ifdeleted='1' ";
		List list = baseDAO.findEntity(hql);
		request.setAttribute("graduateTypeList", list);

	}
	
	public List getDiction(String dicId) {
		return baseDAO.findEntity("from Dictionary a where a.id.dictNo="
				+ dicId + " order by a.id.dictValue");
	}
	public void setDictionaryService(DictionaryService dictionaryService) {
		this.dictionaryService = dictionaryService;
	}
	public void setYxGraduateService(YxGraduateService yxGraduateService) {
		this.yxGraduateService = yxGraduateService;
	}
	public YxGraduate getGEntity(String gid) {
		// TODO Auto-generated method stub
		return (YxGraduate)baseDAO.getEntity(YxGraduate.class, gid);
	}
	public YxGzdormapply gethlEntity(String gid) {
		// TODO Auto-generated method stub
	return (YxGzdormapply)baseDAO.getEntity(YxGzdormapply.class, gid);
	}
	

}
