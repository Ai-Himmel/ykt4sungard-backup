package org.king.yangong.dormitorymanage.service;

import java.util.List;

import javax.servlet.http.HttpServletRequest;

import org.apache.struts.action.DynaActionForm;
import org.king.classmanage.domain.Dictionary;
import org.king.classmanage.domain.Studentmodel;
import org.king.dormitorymanage.domain.DormDept;
import org.king.yangong.dormitorymanage.domain.GraduateType;
import org.king.yangong.dormitorymanage.domain.YxGraduate;
import org.king.yangong.dormitorymanage.domain.YxGzdormapply;

public interface DormAppService {
	public List getGraduateList(DynaActionForm graduateSearchForm,String page);
	public List getGraduateList(DynaActionForm graduateSearchForm,String page,String user);
	public void updateGraduateInfo(String[] itemlist,String flag);
	public void updateGraduateInfo(String itemlist,String flag,String memo);
	
	public List getGraduate(String personCode);

	public List list4DeptBundingTJ(DynaActionForm graduateSearchForm);

	public List list4DeptBundedTJ(DynaActionForm graduateSearchForm);

	public List listDormBundByDept(String deptId);

	public List list4BuildBundingTJ(DynaActionForm buildBundSearchForm);

	public List listDormBundByDormitory(String areaCode,String locationCode,String dormitoryId);

	public List list4DeptBundingTotalTJ(DynaActionForm deptBundSearchForm);

	public List list4DeptBundedTotalTJ(DynaActionForm deptBundSearchForm);

	public List list4BuildBundingTotalTJ(DynaActionForm buildBundSearchForm);

	public Object getEntity(String deptId);

	public List getDictionaryModel(int i, String areaCode);
	public List getGzList(DynaActionForm graduateSearchForm, String page);
	public YxGzdormapply getGzdormapply(String itemList);
	public void deleteGzDormAppInfo(String[] itemList,HttpServletRequest request);
	public List getStudentModel(String string);
	public void updateGzdormappInfo(YxGzdormapply yg);
	public void saveGzdormappInfo(YxGzdormapply yg);
	public void updateGzDormAppModify(String[] itemlist, String string);
	public List getGzdormapplyByStuNo(String operator);
	public List getGzList4NeedDorm(DynaActionForm graduateSearchForm, String page);
	public void updateGraduateInfo(String[] itemlist, String[] itemList);
	public List getGzdormapplyByEnterenceNo(String string);
	public List getGzdormapplyByStudentNo(String string);
	
	public Integer getGzList4NeedDormCount(DynaActionForm graduateSearchForm);
	
	public Integer getGzListCount(DynaActionForm graduateSearchForm);
	
	public void initForm(HttpServletRequest request);
	
	public void updateGZStudentInfo(String[] itemlist, String[] itemList2);
	
	public Integer getGraduateListCount(DynaActionForm graduateSearchForm,String user);
	
	public List getGzList4NeedDormExport(DynaActionForm graduateSearchForm);
	public void updateGraduateInfo(String gid, String memo);
	public YxGraduate getGEntity(String gid);
	public YxGzdormapply gethlEntity(String gid);
	public List getGraduateListExport(DynaActionForm graduateSearchForm, String page,String user);
	public List getGzListExport(DynaActionForm graduateSearchForm, String page);


}