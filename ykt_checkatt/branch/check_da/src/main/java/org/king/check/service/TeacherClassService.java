package org.king.check.service;

import org.apache.poi.hssf.usermodel.HSSFWorkbook;
import org.apache.struts.action.DynaActionForm;
import org.king.check.common.ec.DBPageLimit;
import org.king.check.domain.TTeacherClass;
import org.king.framework.exception.BusinessException;

import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2010-12-16
 */
public interface TeacherClassService {
    public HSSFWorkbook getTeacherClassModel();

    public List implTeacherClass(HSSFWorkbook wb, Integer custid, StringBuffer msg);

    public List checkTeacherClass(Integer custid, StringBuffer msg);

    public void saveTeacherClass(List tempList, List checkList);

    public void cleanTeacherClassTemp(Integer custid);

    public void findTeacherClass(DynaActionForm dform, DBPageLimit page);

    public void deleteTeacherClass(String[] ids);

    public void saveTeacherClass(TTeacherClass tTeacherClass,String areaCode,String shortName) throws BusinessException;
}
