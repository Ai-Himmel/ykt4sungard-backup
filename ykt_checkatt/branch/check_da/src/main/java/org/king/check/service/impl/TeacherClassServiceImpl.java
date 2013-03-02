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

        // ������ʾ�������Լ���ص���ʽ
        HSSFFont font = wb.createFont();
        font.setFontHeightInPoints((short) 10);
        font.setItalic(false);
        font.setStrikeout(false);

        // ���ñ�������Ԫ�����ʽ
        HSSFCellStyle cellHeadStyle = wb.createCellStyle();
        cellHeadStyle.setAlignment(HSSFCellStyle.ALIGN_LEFT);
        cellHeadStyle.setBorderBottom((short) 1);
        cellHeadStyle.setBorderLeft((short) 1);
        cellHeadStyle.setBorderRight((short) 1);
        cellHeadStyle.setBorderTop((short) 1);
        cellHeadStyle.setFillForegroundColor(HSSFColor.GREY_25_PERCENT.index);
        cellHeadStyle.setFillPattern(HSSFCellStyle.SOLID_FOREGROUND);

        // ���������е������Լ��Լ���صĶ��뷽ʽ
        HSSFCellStyle cellDataStyle = wb.createCellStyle();
        cellDataStyle.setAlignment(HSSFCellStyle.ALIGN_LEFT);
        cellDataStyle.setFont(font);

        HSSFSheet sheet1 = wb.createSheet("Sheet1");

        // Grab & populate the Column Names
        HSSFRow row = sheet1.createRow((short) 0);

        // Populate the first row of the spreadsheet with the column names
        List columnNames = new ArrayList();


        columnNames.add(0, "��ʦ����");
        columnNames.add(1, "����");
        columnNames.add(2, "�༶����");
        columnNames.add(3, "�༶����");
        columnNames.add(4, "�Ƿ񸨵�Ա");
        columnNames.add(5, "У������");
        columnNames.add(6, "У������");


        HSSFCellStyle keycellHeadStyle = wb.createCellStyle();//�����ֶεı�������ʽ
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

        String[][] data = new String[][]{{"040839", "������", "103100000012009", "2010�������ű���(ר�����)10������������˳��012009", "��", "11", "��˳·У��"}
                , {"040839", "������", "103100000012011", "2010�������ű���(ר�����)10���������ѧ�뼼������˳��012011", "��", "11", "��˳·У��"}
                , {"001258", "������", "093100000012018", "2009�＾���ű���(ר�����)09�������������£�012018", "��", "13", "����·У��"}
                , {"040743", "����", "093100000012022", "2009�＾���ű���(ר�����)09������������ԭ��012022 ", "��", "14", "��ԭ·У��"}};
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
                    msg.append("��").append(t_id).append("�н�ʦ������Ч��<br>");
                }
                if (row.get("a_areacode") == null) {
                    msg.append("��").append(t_id).append("��У��������Ч��<br>");
                }
                if (row.get("d_dept_id") == null) {
                    msg.append("��").append(t_id).append("�а༶������Ч��<br>");
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
            //t_idΪ������¼��excel�ж�Ӧ����������������tempList�е��±�С2
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
                //����Ѿ����ڸ���Ա��༶��ϵ�������µ���ĸ���Ա��ϵ���Ƿ񸨵�Ա�ֶ�Ϊ����ôɾ���Ѿ����ڵĸ���Ա�༶��ϵ
                if ("0".equals(tTeacherClassTemp.getCounselor())) {
                    teacherClassDAO.delete(tTeacherClass);
                }
            }

            //���༶���иü�¼��Ӧ�İ༶У������Ϊ��ʱ�����°༶У������
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
        //����ø���Ա�༶��ϵ�Ѵ��ڣ����������
        if (instance != null) {
            throw new BusinessException("�ø���Ա�༶��ϵ�Ѿ����ڣ�");
        }
        TCustomer tCustomer = customerDAO.getCustomerByStuempno(tTeacherClass.getStuempno());
        if (tCustomer == null) {
            throw new BusinessException("��ʦѧ������Ч��");
        }
        tTeacherClass.setCustid(tCustomer.getCustid());
        Department department = departmentDAO.findDepartment(tTeacherClass.getDeptId());
        if (department == null) {
            throw new BusinessException("�༶������Ч��");
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
                    stuempno = getTrimedStr(row.getCell((short) 0).getStringCellValue()).trim();//��ʦ����
                    custname = getTrimedStr(row.getCell((short) 1).getStringCellValue()).trim();//��ʦ����
                    deptId = getTrimedStr(row.getCell((short) 2).getStringCellValue()).trim();//�༶����
                    deptName = getTrimedStr(row.getCell((short) 3).getStringCellValue()).trim();//�༶����
                    counselor = getTrimedStr(row.getCell((short) 4).getStringCellValue()).trim();//�Ƿ񸨵�Ա
                    areaCode = getTrimedStr(row.getCell((short) 5).getStringCellValue()).trim();//У������
                    areaName = getTrimedStr(row.getCell((short) 6).getStringCellValue()).trim();//У������

                    //check all of the not null fields
                    if (StringUtils.isBlank(stuempno)) {
                        msg.append("��").append(i + 1).append("�н�ʦ���Ų���Ϊ�ա�<br>");
                    }
                    if (StringUtils.isBlank(deptId)) {
                        msg.append("��").append(i + 1).append("�а༶���벻��Ϊ�ա�<br>");
                    }
                    if (StringUtils.isBlank(counselor)) {
                        msg.append("��").append(i + 1).append("���Ƿ񸨵�Ա����Ϊ�ա�<br>");
                    } else {
                        if (!"��".equals(counselor) && !"��".equals(counselor)) {
                            msg.append("��").append(i + 1).append("�Ƿ����Ա��Ӧ��д�ǻ��<br>");
                        }
                    }
                    if (StringUtils.isBlank(areaCode)) {
                        msg.append("��").append(i + 1).append("��У�����벻��Ϊ�ա�<br>");
                    }
                    TTeacherClassTemp tTeacherClassTemp = new TTeacherClassTemp();
                    tTeacherClassTemp.setOperId(custid);
                    tTeacherClassTemp.setId(Integer.valueOf(i + 1));
                    tTeacherClassTemp.setStuempno(stuempno);
                    tTeacherClassTemp.setCustname(custname);
                    tTeacherClassTemp.setDeptId(deptId);
                    tTeacherClassTemp.setDeptName(deptName);
                    tTeacherClassTemp.setCounselor("��".equals(counselor) ? "1" : "0");
                    tTeacherClassTemp.setAreaCode(areaCode);
                    tTeacherClassTemp.setAreaName(areaName);
                    result.add(tTeacherClassTemp);
                } catch (NumberFormatException ne) {
                    msg.append("��").append(i + 1).append("���������ݷ��ı����ͣ��޸��ı����ͺ��ٵ��롣<br>");
                } catch (NullPointerException n) {
                    msg.append("��").append(i + 1).append("���п����ݣ��������ٵ��롣<br>");
                }
            }
        } else {
            msg.append("û���ҵ���Ч�ļ�¼");
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
