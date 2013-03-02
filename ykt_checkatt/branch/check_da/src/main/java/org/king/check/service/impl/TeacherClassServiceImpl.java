package org.king.check.service.impl;

import org.apache.commons.lang.StringUtils;
import org.apache.poi.hssf.usermodel.*;
import org.apache.poi.hssf.util.HSSFColor;
import org.apache.struts.action.DynaActionForm;
import org.king.check.common.ec.DBPageLimit;
import org.king.check.common.query.QueryTranslate;
import org.king.check.dao.CustomerDAO;
import org.king.check.dao.DepartmentDAO;
import org.king.check.dao.TeacherClassDAO;
import org.king.check.dao.TeacherClassTempDAO;
import org.king.check.domain.Department;
import org.king.check.domain.TCustomer;
import org.king.check.domain.TTeacherClass;
import org.king.check.domain.TTeacherClassTemp;
import org.king.check.service.TeacherClassService;
import org.king.framework.exception.BusinessException;
import org.springframework.jdbc.core.JdbcTemplate;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

/**
 * .
 * User: Yiming.You
 * Date: 2010-12-16
 */
public class TeacherClassServiceImpl implements TeacherClassService {
    private TeacherClassTempDAO teacherClassTempDAO;

    private JdbcTemplate jdbcTemplate;

    private DepartmentDAO departmentDAO;

    private TeacherClassDAO teacherClassDAO;

    private CustomerDAO customerDAO;

    public void setTeacherClassTempDAO(TeacherClassTempDAO teacherClassTempDAO) {
        this.teacherClassTempDAO = teacherClassTempDAO;
    }

    public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
        this.jdbcTemplate = jdbcTemplate;
    }

    public void setDepartmentDAO(DepartmentDAO departmentDAO) {
        this.departmentDAO = departmentDAO;
    }

    public void setTeacherClassDAO(TeacherClassDAO teacherClassDAO) {
        this.teacherClassDAO = teacherClassDAO;
    }

    public void setCustomerDAO(CustomerDAO customerDAO) {
        this.customerDAO = customerDAO;
    }

    public HSSFWorkbook getTeacherClassModel() {
        // Create the Sheet with the name of the Table
        HSSFWorkbook wb = new HSSFWorkbook();

        // 设置显示的字体以及相关的样式
        HSSFFont font = wb.createFont();
        font.setFontHeightInPoints((short) 10);
        font.setItalic(false);
        font.setStrikeout(false);

        // 设置标题栏单元格的样式
        HSSFCellStyle cellHeadStyle = wb.createCellStyle();
        cellHeadStyle.setAlignment(HSSFCellStyle.ALIGN_LEFT);
        cellHeadStyle.setBorderBottom((short) 1);
        cellHeadStyle.setBorderLeft((short) 1);
        cellHeadStyle.setBorderRight((short) 1);
        cellHeadStyle.setBorderTop((short) 1);
        cellHeadStyle.setFillForegroundColor(HSSFColor.GREY_25_PERCENT.index);
        cellHeadStyle.setFillPattern(HSSFCellStyle.SOLID_FOREGROUND);

        // 设置数据行的字体以及以及相关的对齐方式
        HSSFCellStyle cellDataStyle = wb.createCellStyle();
        cellDataStyle.setAlignment(HSSFCellStyle.ALIGN_LEFT);
        cellDataStyle.setFont(font);

        HSSFSheet sheet1 = wb.createSheet("Sheet1");

        // Grab & populate the Column Names
        HSSFRow row = sheet1.createRow((short) 0);

        // Populate the first row of the spreadsheet with the column names
        List columnNames = new ArrayList();


        columnNames.add(0, "教师工号");
        columnNames.add(1, "姓名");
        columnNames.add(2, "班级代码");
        columnNames.add(3, "班级名称");
        columnNames.add(4, "是否辅导员");
        columnNames.add(5, "校区代码");
        columnNames.add(6, "校区名称");


        HSSFCellStyle keycellHeadStyle = wb.createCellStyle();//必填字段的标题栏格式
        keycellHeadStyle.setAlignment(HSSFCellStyle.ALIGN_LEFT);
        keycellHeadStyle.setBorderBottom((short) 1);
        keycellHeadStyle.setBorderLeft((short) 1);
        keycellHeadStyle.setBorderRight((short) 1);
        keycellHeadStyle.setBorderTop((short) 1);
        keycellHeadStyle.setFillForegroundColor(HSSFColor.LIGHT_ORANGE.index);
        keycellHeadStyle.setFillPattern(HSSFCellStyle.SOLID_FOREGROUND);

        for (int i = 0; i < columnNames.size(); i++) {
            HSSFCell cname = row.createCell((short) i);
            if (i == 0 || i == 2 || i == 4 || i == 5) {
                cname.setCellStyle(keycellHeadStyle);
            } else {
                cname.setCellStyle(cellHeadStyle);
            }
            cname.setEncoding(HSSFCell.ENCODING_UTF_16);
            cname.setCellValue((String) columnNames.get(i));
        }

        String[][] data = new String[][]{{"040839", "熊玉利", "103100000012009", "2010春季开放本科(专科起点)10春物流管理（国顺）012009", "是", "11", "国顺路校区"}
                , {"040839", "熊玉利", "103100000012011", "2010春季开放本科(专科起点)10春计算机科学与技术（国顺）012011", "是", "11", "国顺路校区"}
                , {"001258", "朱文嵘", "093100000012018", "2009秋季开放本科(专科起点)09秋行政管理（阜新）012018", "是", "13", "阜新路校区"}
                , {"040743", "翁肃", "093100000012022", "2009秋季开放本科(专科起点)09秋物流管理（中原）012022 ", "是", "14", "中原路校区"}};
        for (int i = 0; i < data.length; i++) {
            // create row in spreadsheet
            row = sheet1.createRow(i + 1);
            for (int j = 0; j < data[i].length; j++) {
                // populate the spreadsheet with the cell
                HSSFCell ctitle = row.createCell((short) j);
                ctitle.setCellStyle(cellDataStyle);
                ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
                ctitle.setCellValue(data[i][j]);
            }
        }
        return wb;
    }

    public List implTeacherClass(HSSFWorkbook wb, Integer custid, StringBuffer msg) {
        List result = readWorkbook(wb, msg, custid);
        //if there is no error,continue to save TTeacherClassTemp object
        if (StringUtils.isBlank(msg.toString())) {
            for (int i = 0; i < result.size(); i++) {
                TTeacherClassTemp tTeacherClassTemp = (TTeacherClassTemp) result.get(i);
                teacherClassTempDAO.save(tTeacherClassTemp);
            }
        }
        return result;
    }

    public List checkTeacherClass(Integer custid, StringBuffer msg) {
        StringBuffer query = new StringBuffer("select t.id as t_id,t.stuempno as t_stuempno,t.dept_id as t_dept_id,t.area_code as t_area_code,cus.stuempno as cus_stuempno,a.areacode as a_areacode,d.dept_id as d_dept_id,cus.custid as cus_custid,d.area_code as d_area_code");
        query.append(" from ykt_ck.t_teacher_class_temp t left join ykt_cur.t_customer cus on t.stuempno = cus.stuempno");
        query.append(" left join ykt_cur.t_area a on t.area_code = a.areacode left join ykt_ck.department d on t.dept_id = d.dept_id");
        query.append(" where t.oper_id =").append(custid);
        query.append(" order by t.id");
        List checkList = jdbcTemplate.queryForList(query.toString());
        if (checkList != null && checkList.size() > 0) {
            for (int i = 0; i < checkList.size(); i++) {
                Map row = (Map) checkList.get(i);
                Integer t_id = Integer.valueOf(row.get("t_id").toString());
                if (row.get("cus_stuempno") == null) {
                    msg.append("第").append(t_id).append("行教师工号无效。<br>");
                }
                if (row.get("a_areacode") == null) {
                    msg.append("第").append(t_id).append("行校区代码无效。<br>");
                }
                if (row.get("d_dept_id") == null) {
                    msg.append("第").append(t_id).append("行班级代码无效。<br>");
                }
            }
        }
        return checkList;
    }

    public void saveTeacherClass(List tempList, List checkList) {
        //the two list have the same length
        if (tempList == null || tempList.size() == 0) {
            return;
        }
        for (int i = 0; i < checkList.size(); i++) {
            Map row = (Map) checkList.get(i);
            //t_id为该条记录在excel中对应的行数，即比其在tempList中的下标小2
            Integer t_id = Integer.valueOf(row.get("t_id").toString());
            TTeacherClassTemp tTeacherClassTemp = (TTeacherClassTemp) tempList.get(t_id.intValue() - 2);
            Integer custid = Integer.valueOf(row.get("cus_custid").toString());

            TTeacherClass tTeacherClass = teacherClassDAO.get(custid, tTeacherClassTemp.getDeptId());
            if (tTeacherClass == null) {
                //save TTeacherClass
                if ("1".equals(tTeacherClassTemp.getCounselor())) {
                    tTeacherClass = new TTeacherClass();
                    tTeacherClass.setCustid(custid);
                    tTeacherClass.setStuempno(tTeacherClassTemp.getStuempno());
                    tTeacherClass.setDeptId(tTeacherClassTemp.getDeptId());
                    teacherClassDAO.save(tTeacherClass);
                }
            } else {
                //如果已经存在辅导员与班级关系，并且新导入的辅导员关系的是否辅导员字段为否，那么删除已经存在的辅导员班级关系
                if ("0".equals(tTeacherClassTemp.getCounselor())) {
                    teacherClassDAO.delete(tTeacherClass);
                }
            }

            //当班级表中该记录对应的班级校区代码为空时，更新班级校区代码
            if (row.get("d_area_code") == null) {
                Department department = departmentDAO.get(tTeacherClassTemp.getDeptId());
                department.setAreaCode(tTeacherClassTemp.getAreaCode());
                department.setName(tTeacherClassTemp.getDeptName());
                departmentDAO.save(department);
            }
        }
    }

    public void cleanTeacherClassTemp(Integer custid) {
        String sql = "delete from ykt_ck.t_teacher_class_temp t where t.oper_id=" + custid;
        jdbcTemplate.execute(sql);
    }

    public void findTeacherClass(DynaActionForm dform, DBPageLimit page) {
        String areaCode = (String) dform.get("areaCode");
        String pid = (String) dform.get("pid");
        String deptId = (String) dform.get("deptId");
        String stuempNo = (String) dform.get("stuempNo");
        String custName = (String) dform.get("custName");
        String departmentName = (String) dform.get("departmentName");

        QueryTranslate queryTranslate = new QueryTranslate();
        queryTranslate.setQueryString("select tc.id as id,tc.custid as custid,tc.deptId as deptid,c.stuempno as stuempno,c.custname as custname,d.name as deptname,a.areaName as areaName,f.pname as faculty from TTeacherClass tc,TCustomer c,Department d,TArea a,TFaculty f where tc.custid=c.custid and tc.deptId=d.id and d.areaCode=a.areaCode and f.value=d.faculty");
        queryTranslate.setOffset(true);
        queryTranslate.setPageStartNo((page.getPageNo() - 1) * page.getPageSize());
        queryTranslate.setPageSize(page.getPageSize());
        queryTranslate.setOrderby(" order by d.areaCode,d.faculty,d.name");

        if (StringUtils.isNotBlank(areaCode)) {
            queryTranslate.addEqualCondition("d.areaCode", areaCode);
        }
        if (StringUtils.isNotBlank(pid)) {
            queryTranslate.addEqualCondition("f.pid", pid);
        }
        if (StringUtils.isNotBlank(deptId)) {
            queryTranslate.addEqualCondition("d.id", deptId);
        }
        if (StringUtils.isNotBlank(stuempNo)) {
            queryTranslate.addEqualCondition("c.stuempno", stuempNo);
        }
        if (StringUtils.isNotBlank(custName)) {
            queryTranslate.addLikeCondition("c.custname", custName);
        }
        if (StringUtils.isNotBlank(departmentName)) {
            queryTranslate.addLikeCondition("d.name", departmentName);
        }

        page.setMap(true);
        teacherClassDAO.findTeacherClassByPage(page, queryTranslate);
    }

    public void deleteTeacherClass(String[] ids) {
        if (ids == null || ids.length == 0) {
            return;
        }
        for (int i = 0; i < ids.length; i++) {
            if (StringUtils.isNotBlank(ids[i])) {
                TTeacherClass teacherClass = teacherClassDAO.get(ids[i]);
                teacherClassDAO.delete(teacherClass);
            }
        }
    }

    public void saveTeacherClass(TTeacherClass tTeacherClass, String areaCode,String shortName) throws BusinessException {
        TTeacherClass instance = teacherClassDAO.get(tTeacherClass.getStuempno(), tTeacherClass.getDeptId());
        //如果该辅导员班级关系已存在，则不允许插入
        if (instance != null) {
            throw new BusinessException("该辅导员班级关系已经存在！");
        }
        TCustomer tCustomer = customerDAO.getCustomerByStuempno(tTeacherClass.getStuempno());
        if (tCustomer == null) {
            throw new BusinessException("教师学工号无效！");
        }
        tTeacherClass.setCustid(tCustomer.getCustid());
        Department department = departmentDAO.findDepartment(tTeacherClass.getDeptId());
        if (department == null) {
            throw new BusinessException("班级代码无效！");
        }
        teacherClassDAO.save(tTeacherClass);
        if (!areaCode.equals(department.getAreaCode()) || !shortName.equals(department.getName())) {
            department.setAreaCode(areaCode);
            department.setName(shortName);
            departmentDAO.save(department);
        }
    }

    /**
     * read from the excel file,then convert the row into TTeacherClassTemp object
     *
     * @param wb .
     * @return .
     */
    private List readWorkbook(HSSFWorkbook wb, StringBuffer msg, Integer custid) {
        String tableName = wb.getSheetName(0);
        HSSFSheet sheet = wb.getSheet(tableName);

        List result = new ArrayList();
        int rowCount = sheet.getPhysicalNumberOfRows();
        if (rowCount > 0) {
            String stuempno;
            String custname;
            String deptId;
            String deptName;
            String counselor;
            String areaCode;
            String areaName;
            for (int i = 1; i < rowCount; i++) {
                try {
                    HSSFRow row = sheet.getRow(i);
                    stuempno = getTrimedStr(row.getCell((short) 0).getStringCellValue()).trim();//教师工号
                    custname = getTrimedStr(row.getCell((short) 1).getStringCellValue()).trim();//教师姓名
                    deptId = getTrimedStr(row.getCell((short) 2).getStringCellValue()).trim();//班级代码
                    deptName = getTrimedStr(row.getCell((short) 3).getStringCellValue()).trim();//班级名称
                    counselor = getTrimedStr(row.getCell((short) 4).getStringCellValue()).trim();//是否辅导员
                    areaCode = getTrimedStr(row.getCell((short) 5).getStringCellValue()).trim();//校区代码
                    areaName = getTrimedStr(row.getCell((short) 6).getStringCellValue()).trim();//校区名称

                    //check all of the not null fields
                    if (StringUtils.isBlank(stuempno)) {
                        msg.append("第").append(i + 1).append("行教师工号不能为空。<br>");
                    }
                    if (StringUtils.isBlank(deptId)) {
                        msg.append("第").append(i + 1).append("行班级代码不能为空。<br>");
                    }
                    if (StringUtils.isBlank(counselor)) {
                        msg.append("第").append(i + 1).append("行是否辅导员不能为空。<br>");
                    } else {
                        if (!"是".equals(counselor) && !"否".equals(counselor)) {
                            msg.append("第").append(i + 1).append("是否管理员，应填写是或否。<br>");
                        }
                    }
                    if (StringUtils.isBlank(areaCode)) {
                        msg.append("第").append(i + 1).append("行校区代码不能为空。<br>");
                    }
                    TTeacherClassTemp tTeacherClassTemp = new TTeacherClassTemp();
                    tTeacherClassTemp.setOperId(custid);
                    tTeacherClassTemp.setId(Integer.valueOf(i + 1));
                    tTeacherClassTemp.setStuempno(stuempno);
                    tTeacherClassTemp.setCustname(custname);
                    tTeacherClassTemp.setDeptId(deptId);
                    tTeacherClassTemp.setDeptName(deptName);
                    tTeacherClassTemp.setCounselor("是".equals(counselor) ? "1" : "0");
                    tTeacherClassTemp.setAreaCode(areaCode);
                    tTeacherClassTemp.setAreaName(areaName);
                    result.add(tTeacherClassTemp);
                } catch (NumberFormatException ne) {
                    msg.append("第").append(i + 1).append("行数字数据非文本类型，修改文本类型后再导入。<br>");
                } catch (NullPointerException n) {
                    msg.append("第").append(i + 1).append("行有空数据，请填充后再导入。<br>");
                }
            }
        } else {
            msg.append("没有找到有效的记录");
        }
        return result;
    }

    private String getTrimedStr(String input) {
        if (input.startsWith("sz")) {
            return input.substring(2);
        } else {
            return input;
        }
    }
}
