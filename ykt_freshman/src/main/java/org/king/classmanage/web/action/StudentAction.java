/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: StudentAction.java
 * Description: TODO
 * Modify History����Change Log��:  
 * �������ͣ��������޸ĵȣ�   ��������       ������             �������ݼ���
 * ����  				 2006-5-9     ������             
 * <p>
 *
 * @author      ������
 * @version     1.0
 * @since       1.0
 */
package org.king.classmanage.web.action;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.UnsupportedEncodingException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.poi.hssf.usermodel.HSSFCell;
import org.apache.poi.hssf.usermodel.HSSFCellStyle;
import org.apache.poi.hssf.usermodel.HSSFFont;
import org.apache.poi.hssf.usermodel.HSSFRow;
import org.apache.poi.hssf.usermodel.HSSFSheet;
import org.apache.poi.hssf.usermodel.HSSFWorkbook;
import org.apache.poi.hssf.util.HSSFColor;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionMessage;
import org.apache.struts.action.ActionMessages;
import org.apache.struts.action.DynaActionForm;
import org.apache.struts.upload.FormFile;
import org.king.classmanage.domain.Classmodel;
import org.king.classmanage.domain.Collegemodel;
import org.king.classmanage.domain.Managermodel;
import org.king.classmanage.domain.StudentListColumns;
import org.king.classmanage.domain.StudentfdyListColmns;
import org.king.classmanage.domain.SdListhlxy;
import org.king.classmanage.domain.SdfdyListhlxy;
import org.king.classmanage.domain.Studentmodel;
import org.king.classmanage.exception.EnterenceNoNotExistException;
import org.king.classmanage.exception.FamilyAddressNotExistException;
import org.king.classmanage.exception.MakeStuNoFailException;
import org.king.classmanage.exception.StuNameNotExistException;
import org.king.classmanage.exception.TotalScoreNotExistException;
import org.king.classmanage.service.ClassService;
import org.king.classmanage.service.CollegeService;
import org.king.classmanage.service.ManagerService;
import org.king.classmanage.service.StudentService;
import org.king.classmanage.web.help.StudentWithAllInfo;
import org.king.common.service.IDirectoryService;
import org.king.dormitorymanage.exception.DormitoryNotEnoughException;
import org.king.dormitorymanage.exception.StudentAlreadyInDormException;
import org.king.dormitorymanage.service.DormitoryService;
import org.king.framework.web.action.BaseAction;
import org.king.security.domain.Account;
import org.king.upload.web.form.UpLoadForm;
import org.king.utils.DateUtil;

public class StudentAction extends BaseAction {

	private StudentService studentService;

	private CollegeService collegeService;

	private ManagerService managerService;
	private IDirectoryService directoryService;
	private ClassService classService;

	private DormitoryService dormitoryService;
	
	public static SimpleDateFormat sdfDate = new SimpleDateFormat("yyyymmdd");

	/**
	 * @param dormitoryService
	 *            The dormitoryService to set.
	 */
	public void setDormitoryService(DormitoryService dormitoryService) {
		this.dormitoryService = dormitoryService;
	}

	/**
	 * @param classService
	 *            The classService to set.
	 */
	public void setClassService(ClassService classService) {
		this.classService = classService;
	}

	/**
	 * @param studentService
	 *            The studentService to set.
	 */
	public void setStudentService(StudentService studentService) {
		this.studentService = studentService;
	}

	/**
	 * @param collegeService
	 *            The collegeService to set.
	 */
	public void setCollegeService(CollegeService collegeService) {
		this.collegeService = collegeService;
	}

	/**
	 * @param managerService
	 *            The managerService to set.
	 */
	public void setManagerService(ManagerService managerService) {
		this.managerService = managerService;
	}

	public ActionForward load4List(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		

		HttpSession session = request.getSession(false);
		String operator = "";
		if (request.getSession().getAttribute("accountPerson") != null) {
			operator = ((Account) request.getSession().getAttribute(
					"accountPerson")).getPerson().getId();
		}
		
		
		// �Ա�
		List genderList = studentService.getDiction("1");
		request.setAttribute("genderList", genderList);
		// ����
		List nationList = studentService.getDiction("2");
		request.setAttribute("nationList", nationList);
		// ��Դ��
		List provinceList = studentService.getDiction("10");
		request.setAttribute("provinceList", provinceList);
		// ������ò
		List polityList = studentService.getDiction("4");
		request.setAttribute("polityList", polityList);
		// רҵ
		List majorinList = studentService.getDiction("11");
		request.setAttribute("majorinList", majorinList);
		// ����
		List nationalityList = studentService.getDiction("12");
		request.setAttribute("nationalityList", nationalityList);

		// ��Ժ�б�
		List collegeList = collegeService.getAllCollegeByfdxy();
		

//		// �����б�
//		List locationList = studentService.getDiction("6");
//		request.setAttribute("locationList", locationList);
//		// ¥�б�
//		List buildingList = studentService.getDiction("7");
//		request.setAttribute("buildingList", buildingList);
		
		classService.initForm(request);
		
//		Ժϵ�б�
		studentService.findDepartments(request);
		
		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//����ѧԺ
			// �Ա�
			genderList = studentService.getDiction("1");
			request.setAttribute("genderList", genderList);
			// ����
			nationList = studentService.getnationList();
			request.setAttribute("nationList", nationList);
			// ��Դ��
			provinceList = studentService.getfromProvinceList();
			request.setAttribute("provinceList", provinceList);
			// ������ò
			polityList = studentService.getDiction("4");
			request.setAttribute("polityList", polityList);
			// רҵ
			majorinList = studentService.getmajorList();
			request.setAttribute("majorinList", majorinList);
			// ����
			nationalityList = studentService.getcountryList();
			request.setAttribute("nationalityList", nationalityList);
			// ����Ա�б�
			List assistantList = managerService.getClassAssitant_hlxy();
			request.setAttribute("assistantList", assistantList);
			// �༶�б�
			List classList = classService.getClassmodelbyschoolId("0002");
			request.setAttribute("classList", classList);
			List ntableheadrightList = classService.getNTableHeadList(operator,"sdListhlxy","1");
			String width="250%";
			if(ntableheadrightList.size()<=10)
			{
				 width="100%";
			}
			if(10<ntableheadrightList.size()&&ntableheadrightList.size()<=13)
			{
				 width="150%";
			}
			if(13<ntableheadrightList.size()&&ntableheadrightList.size()<=16)
			{
				 width="200%";
			}
			request.setAttribute("width", width);
			SdListhlxy studentlc = classService.getUserSessionhlxyColumns(operator, "sdListhlxy");
			request.setAttribute("studentlc", studentlc);
			
			//-------------------------------------------------
			return mapping.findForward("list_hlxy");
		}
		else if (getrole!=null&&!"".equals(getrole)&&getrole.equals("1")){
			//-------------------------------------------------����ѧԺ
			// �Ա�
			genderList = studentService.getDiction("1");
			request.setAttribute("genderList", genderList);
			// ����
			nationList = studentService.getnationList();
			request.setAttribute("nationList", nationList);
			// ��Դ��
			provinceList = studentService.getfromProvinceList();
			request.setAttribute("provinceList", provinceList);
			// ������ò
			polityList = studentService.getDiction("4");
			request.setAttribute("polityList", polityList);
			// רҵ
			majorinList = studentService.getmajorList();
			request.setAttribute("majorinList", majorinList);
			// ����
			nationalityList = studentService.getcountryList();
			request.setAttribute("nationalityList", nationalityList);
			// ����Ա�б�
			List assistantList = managerService.getClassAssitant();
			request.setAttribute("assistantList", assistantList);
			request.setAttribute("collegeList", collegeList);
			// �༶�б�
			List classList = classService.getClassmodelbyschoolId("0001");
			request.setAttribute("classList", classList);
			List ntableheadrightList = classService.getNTableHeadList(operator,"studentList.jsp","1");
			String width="250%";
			if(ntableheadrightList.size()<=10)
			{
				 width="100%";
			}
			if(10<ntableheadrightList.size()&&ntableheadrightList.size()<=13)
			{
				 width="150%";
			}
			if(13<ntableheadrightList.size()&&ntableheadrightList.size()<=16)
			{
				 width="200%";
			}
			request.setAttribute("width", width);
			StudentListColumns studentlc = classService.getUserSessionColumns(operator, "studentList.jsp");
			request.setAttribute("studentlc", studentlc);
			
			return mapping.findForward("list");
		}
		else{
			//-------------------------------------------------�������͸�ְ��
			// ����Ա�б�
			List assistantList = managerService.getClassAssitant();
			List assistantList2 = managerService.getClassAssitant_hlxy();
			assistantList.addAll(assistantList2);
			request.setAttribute("assistantList", assistantList);
			Collegemodel m = new Collegemodel();
			m.setCollegeId("0002");
			m.setCollegeName("����ѧԺ");
			collegeList.add(m);
			request.setAttribute("collegeList", collegeList);
			List areaList = directoryService.getAreas();
			request.setAttribute("areaList", areaList);
			request.setAttribute("locationList",Collections.EMPTY_LIST);
			request.setAttribute("dormitoryList",Collections.EMPTY_LIST);
			// �༶�б�
			List classList = classService.getClassmodelbyschoolId(null);
			request.setAttribute("classList", classList);
			return mapping.findForward("list_all");
		}

		
	}

	public ActionForward load4fdyList(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		String operator = "";
		if (request.getSession().getAttribute("accountPerson") != null) {
			operator = ((Account) request.getSession().getAttribute(
					"accountPerson")).getPerson().getId();
		}
		// �Ա�
		List genderList = studentService.getDiction("1");
		request.setAttribute("genderList", genderList);
		// ����
		List nationList = studentService.getnationList();
		request.setAttribute("nationList", nationList);
		// ��Դ��
		List provinceList = studentService.getfromProvinceList();
		request.setAttribute("provinceList", provinceList);
		// ������ò
		List polityList = studentService.getDiction("4");
		request.setAttribute("polityList", polityList);
		// רҵ
		List majorinList = studentService.getmajorList();
		request.setAttribute("majorinList", majorinList);
		// ����
		List nationalityList = studentService.getcountryList();
		request.setAttribute("nationalityList", nationalityList);
//		// �����б�
//		List locationList = studentService.getDiction("6");
//		request.setAttribute("locationList", locationList);
//		// ¥�б�
//		List buildingList = studentService.getDiction("7");
//		request.setAttribute("buildingList", buildingList);
		
		dormitoryService.initForm_fdy(request);
		
		//Ժϵ�б�
		studentService.findDepartments(request);
		
		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//����ѧԺ
			//-------------------------------------------------
			List ntableheadrightList = classService.getNTableHeadList(operator,"sdhdyListhlxy","1");
			String width="250%";
			if(ntableheadrightList.size()<=10)
			{
				 width="100%";
			}
			if(10<ntableheadrightList.size()&&ntableheadrightList.size()<=13)
			{
				 width="150%";
			}
			if(13<ntableheadrightList.size()&&ntableheadrightList.size()<=16)
			{
				 width="200%";
			}
			request.setAttribute("width", width);
			SdfdyListhlxy studentlc = classService.getUserSessionfdyhlxyColumns(operator, "sdhdyListhlxy");
			request.setAttribute("studentlc", studentlc);
			return mapping.findForward("fdylist_hlxy");
		}else{
			//-------------------------------------------------����ѧԺ
			
			List ntableheadrightList = classService.getNTableHeadList(operator,"sdfdyList.jsp","1");
			String width="250%";
			if(ntableheadrightList.size()<=10)
			{
				 width="100%";
			}
			if(10<ntableheadrightList.size()&&ntableheadrightList.size()<=13)
			{
				 width="150%";
			}
			if(13<ntableheadrightList.size()&&ntableheadrightList.size()<=16)
			{
				 width="200%";
			}
			request.setAttribute("width", width);
			StudentfdyListColmns studentlc = classService.getUserSessionfdyColumns(operator, "sdfdyList.jsp");
			request.setAttribute("studentlc", studentlc);
			studentService.findAssistantList(request);
		
			return mapping.findForward("fdylist");
		}


	}

	public ActionForward load4Search(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		String operator = "";
		if (request.getSession().getAttribute("accountPerson") != null) {
			operator = ((Account) request.getSession().getAttribute(
					"accountPerson")).getPerson().getId();
		}
		
		DynaActionForm studentForm = (DynaActionForm) form;
		Studentmodel studentmodel = (Studentmodel) studentForm
				.get("studentmodel");
		String studentNo = studentmodel.getStudentNo();
		String stuName = studentmodel.getStuName();
		String gender = studentmodel.getGender();
		String nation = studentmodel.getNation();
		String province = studentmodel.getFromProvince();
		String polity = studentmodel.getPolityBg();
		
		String department = studentmodel.getDepartment();
		
		String majorin = studentmodel.getMajorin();
//      <!-- ֤������ -->
//      <property name="idType" type="string">
//      <!-- ������� -->
//      <property name="cultureMode" type="string">
//      <!-- ѧ������ -->
//      <property name="studentChar" type="string">
//      <!-- �Ƿ��ڼ� -->
//      <property name="checkornot" type="integer">
//      <!-- �Ƿ���У -->
//      <property name="schoolornot" type="integer">		
		String idType = studentmodel.getIdType();
		String cultureMode = studentmodel.getCultureMode();
		String studentChar = studentmodel.getStudentChar();
//		Integer checkornot = studentmodel.getCheckornot();
//		Integer schoolornot = studentmodel.getSchoolornot();
		
		String nationality = studentmodel.getNationality();
		String college = studentForm.getString("college");
		String classId = studentForm.getString("classId");
		String location = studentForm.getString("location");
		String area = studentForm.getString("area");
		String dormitory = studentForm.getString("dormitory");
		String roomnumber = studentForm.getString("roomnumber");
		String assistant = studentForm.getString("assistant");
		
		String checkornot = studentForm.getString("checkornot1");
		String schoolornot = studentForm.getString("schoolornot1");		
		String enterenceNo = studentmodel.getEnterenceNo();		
		
		String idCard = studentmodel.getIdCard();		
		
		String page = request.getParameter("pager.offset");

		String order = request.getParameter("horder");
		String odr = "asc";
		if (order != null && order.length() > 0 && order.equals("d"))
			odr = "desc";
		String orderby = request.getParameter("orderby");

		String[] args = { studentNo, stuName, gender, nation, province, polity,
				college, classId, location, dormitory, roomnumber, assistant,
				majorin, nationality, page, orderby, odr,department,area,
				idType,cultureMode,studentChar,checkornot,schoolornot,enterenceNo,idCard };
		List studentmodels = null;
		
		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//����ѧԺ
			//-------------------------------------------------
			String schoolId = "0002";
			if (request.getParameter("export") == null
					|| "".equals(request.getParameter("export"))) {
				studentmodels = studentService.getStudent(args,schoolId);
				Integer studentCount = studentService.getStudentCount(args,schoolId);
				
				request.setAttribute("listcount", studentCount);
				
				request.setAttribute("myclass", classId);
				request.setAttribute("mydormitory", dormitory);
				// ������
				request.setAttribute("studentCount", studentCount);
				request.setAttribute("studentmodels", studentmodels);

				// �Ա�
				List genderList = studentService.getDiction("1");
				request.setAttribute("genderList", genderList);
				// ����
				List nationList = studentService.getnationList();
				request.setAttribute("nationList", nationList);
				// ��Դ��
				List provinceList = studentService.getfromProvinceList();
				request.setAttribute("provinceList", provinceList);
				// ������ò
				List polityList = studentService.getDiction("4");
				request.setAttribute("polityList", polityList);
				// רҵ
				List majorinList = studentService.getmajorList();
				request.setAttribute("majorinList", majorinList);
				// ����
				List nationalityList = studentService.getcountryList();
				request.setAttribute("nationalityList", nationalityList);
				// ��Ժ�б�
				List collegeList = collegeService.getAllCollegeByfdxy();
				request.setAttribute("collegeList", collegeList);
				// �༶�б�
				List classList = classService.getClassmodelbyschoolId("0002");
				request.setAttribute("classList", classList);
				// ����Ա�б�
				List assistantList = managerService.getClassAssitant_hlxy();
				request.setAttribute("assistantList", assistantList);
//				// �����б�
//				List locationList = studentService.getDiction("6");
//				request.setAttribute("locationList", locationList);
//				// ¥�б�
//				List buildingList = studentService.getDiction("7");
//				request.setAttribute("buildingList", buildingList);
				classService.initForm(request);
				
				//Ժϵ�б�
				studentService.findDepartments(request);	
				List ntableheadrightList = classService.getNTableHeadList(operator,"sdListhlxy","1");
				String width="250%";
				if(ntableheadrightList.size()<=10)
				{
					 width="100%";
				}
				if(10<ntableheadrightList.size()&&ntableheadrightList.size()<=13)
				{
					 width="150%";
				}
				if(13<ntableheadrightList.size()&&ntableheadrightList.size()<=16)
				{
					 width="200%";
				}
				request.setAttribute("width", width);
				SdListhlxy studentlc = classService.getUserSessionhlxyColumns(operator, "sdListhlxy");
				request.setAttribute("studentlc", studentlc);

				request.setAttribute("orderby", orderby);
				request.setAttribute("order", order);
				return mapping.findForward("list_hlxy");
			} else {
				// =================================================================
				studentmodels = studentService.getStudentExport(args,schoolId);
				// Create the Excel File
				String fileName = "studentInfo.xls";
				// Create the Sheet with the name of the Table
				HSSFWorkbook wb = new HSSFWorkbook();

				// ������ʾ�������Լ���ص���ʽ
				HSSFFont font = wb.createFont();
				font.setFontHeightInPoints((short) 8);
				font.setItalic(false);
				font.setStrikeout(false);

				// ���ñ�������Ԫ�����ʽ
				HSSFCellStyle cellHeadStyle = wb.createCellStyle();
				cellHeadStyle.setAlignment(HSSFCellStyle.ALIGN_CENTER);
				cellHeadStyle.setBorderBottom(HSSFCellStyle.BORDER_DOUBLE);
				cellHeadStyle.setBorderLeft((short) 1);
				cellHeadStyle.setBorderRight((short) 1);
				cellHeadStyle.setBorderTop(HSSFCellStyle.BORDER_DOUBLE);
				cellHeadStyle.setFillForegroundColor(HSSFColor.LIGHT_YELLOW.index);
				cellHeadStyle.setFillPattern(HSSFCellStyle.SOLID_FOREGROUND);

				// ���������е������Լ��Լ���صĶ��뷽ʽ
				HSSFCellStyle cellDataStyle = wb.createCellStyle();
				cellDataStyle.setAlignment(HSSFCellStyle.ALIGN_CENTER);
				cellDataStyle.setFont(font);

				HSSFSheet sheet1 = wb.createSheet("Sheet1");

				// Grab & populate the Column Names
				HSSFRow row = sheet1.createRow((short) 0);

				// Populate the first row of the spreadsheet with the column names
				List columnNames = new ArrayList();
//				columnNames.add(0, "��Ժ");
				columnNames.add(0, "�༶");
				columnNames.add(1, "����Ա");
				columnNames.add(2, "ѧ��");
				columnNames.add(3, "¼ȡ֪ͨ���");
				columnNames.add(4, "����");
				columnNames.add(5, "�Ա�");	
//				columnNames.add(7, "¼ȡԺϵ");
//				columnNames.add(8, "¼ȡרҵ");	
			
				columnNames.add(6, "֤������");
				columnNames.add(7, "֤������");				
				columnNames.add(8, "�������");
				columnNames.add(9, "ѧ������");	
				columnNames.add(10, "�Ƿ��ڼ�");
				columnNames.add(11, "�Ƿ���У");					
				
				columnNames.add(12, "����");
				columnNames.add(13, "����");
//				columnNames.add(16, "��Դ��");
				columnNames.add(14, "������ò");
				columnNames.add(15, "У��");
				columnNames.add(16, "����");
				columnNames.add(17, "¥��");
				columnNames.add(18, "�����");
				columnNames.add(19, "����");
				columnNames.add(20, "��ͥ�绰");
				columnNames.add(21, "��ʱһ��ͨ����");
//				columnNames.add(25, "ԡ������");	

				for (int i = 0; i < columnNames.size(); i++) {
					HSSFCell cname = row.createCell((short) i);
					cname.setCellStyle(cellHeadStyle);
					cname.setEncoding(HSSFCell.ENCODING_UTF_16);
					cname.setCellValue((String) columnNames.get(i));
				}

				// Populate the Row Data to the SpreadSheet
				int rowCount = studentmodels.size();
				// goal houses the number of cells in the target spreadsheet
				int goal = rowCount * columnNames.size();

				// actual population of target spreadsheet
				int currentCell = 0;

				for (int i = 0; i < rowCount; i++) {
					StudentWithAllInfo tableData = (StudentWithAllInfo) studentmodels
							.get(i);
					// create row in spreadsheet
					row = sheet1.createRow((short) (i + 1));

//					 populate the spreadsheet with the cell
					HSSFCell ctitle = row.createCell((short) 0);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getClassId());

					ctitle = row.createCell((short) 1);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getAssistant());

					ctitle = row.createCell((short) 2);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getStudentNo());
					
					ctitle = row.createCell((short) 3);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getEnterenceNo());
					
					ctitle = row.createCell((short) 4);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getStuName());

					ctitle = row.createCell((short) 5);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getGender());	
					
//					ctitle = row.createCell((short) 7);
//					ctitle.setCellStyle(cellDataStyle);
//					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
//					ctitle.setCellValue(tableData.getDepartment());
//					
//					ctitle = row.createCell((short) 8);
//					ctitle.setCellStyle(cellDataStyle);
//					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
//					ctitle.setCellValue(tableData.getMajorin());	
					
					ctitle = row.createCell((short) 6);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getIdType());
					
					ctitle = row.createCell((short) 7);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getIdCard());

					ctitle = row.createCell((short) 8);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getCultureMode());

					ctitle = row.createCell((short) 9);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getStudentChar());

					ctitle = row.createCell((short) 10);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getCheckornot()==null?"":tableData.getCheckornot().intValue()==1?"��":"��");

					ctitle = row.createCell((short) 11);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getSchoolornot()==null?"":tableData.getSchoolornot().intValue()==1?"��":"��");
					
					ctitle = row.createCell((short) 12);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getNation());

					ctitle = row.createCell((short) 13);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getNationality());

//					ctitle = row.createCell((short) 16);
//					ctitle.setCellStyle(cellDataStyle);
//					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
//					ctitle.setCellValue(tableData.getFromProvince());

					ctitle = row.createCell((short) 14);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getPolityBg());

					ctitle = row.createCell((short) 15);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getArea());
					
					ctitle = row.createCell((short) 16);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getLocation());

					ctitle = row.createCell((short) 17);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getDormitory());

					ctitle = row.createCell((short) 18);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getRoomnumber());				
					
					ctitle = row.createCell((short) 19);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getBirthday());

					ctitle = row.createCell((short) 20);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getHomeTelephone());

					ctitle = row.createCell((short) 21);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getTempecardNo()==null?"":tableData.getTempecardNo().toString());

//					ctitle = row.createCell((short) 25);
//					ctitle.setCellStyle(cellDataStyle);
//					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
//					ctitle.setCellValue(tableData.getBathcardNo());		

					// System.out.println(columnData);
					currentCell++;

				}
				OutputStream os;
				try {
					response.setContentType("application/x-msdownload");
					response.setHeader("Content-Disposition", "attachment;"
							+ " filename="
							+ new String(fileName.getBytes(), "ISO-8859-1"));
					os = response.getOutputStream();
					wb.write(os);
					return null;
				} catch (UnsupportedEncodingException e) {
					e.printStackTrace();
					return null;
				} catch (IOException e) {
					e.printStackTrace();
					return null;
				}
				// =================================================================
			}			
		}else if(getrole!=null&&!"".equals(getrole)&&getrole.equals("1")){
			//-------------------------------------------------����ѧԺ
			String schoolId = "0001";
			if (request.getParameter("export") == null
					|| "".equals(request.getParameter("export"))) {
				studentmodels = studentService.getStudent(args,schoolId);
				Integer studentCount = studentService.getStudentCount(args,schoolId);
				
				request.setAttribute("listcount", studentCount);
				
				request.setAttribute("myclass", classId);
				request.setAttribute("mydormitory", dormitory);
				// ������
				request.setAttribute("studentCount", studentCount);
				request.setAttribute("studentmodels", studentmodels);

				// �Ա�
				List genderList = studentService.getDiction("1");
				request.setAttribute("genderList", genderList);
				// ����
				List nationList = studentService.getnationList();
				request.setAttribute("nationList", nationList);
				// ��Դ��
				List provinceList = studentService.getfromProvinceList();
				request.setAttribute("provinceList", provinceList);
				// ������ò
				List polityList = studentService.getDiction("4");
				request.setAttribute("polityList", polityList);
				// רҵ
				List majorinList = studentService.getmajorList();
				request.setAttribute("majorinList", majorinList);
				// ����
				List nationalityList = studentService.getcountryList();
				request.setAttribute("nationalityList", nationalityList);
				// ��Ժ�б�
				List collegeList = collegeService.getAllCollegeByfdxy();
				request.setAttribute("collegeList", collegeList);
				// �༶�б�
				List classList = classService.getClassmodelbyschoolId("0001");
				request.setAttribute("classList", classList);
				// ����Ա�б�
				List assistantList = managerService.getClassAssitant();
				request.setAttribute("assistantList", assistantList);
//				// �����б�
//				List locationList = studentService.getDiction("6");
//				request.setAttribute("locationList", locationList);
//				// ¥�б�
//				List buildingList = studentService.getDiction("7");
//				request.setAttribute("buildingList", buildingList);		
				classService.initForm(request);
				//Ժϵ�б�
				studentService.findDepartments(request);			
				

				request.setAttribute("orderby", orderby);
				request.setAttribute("order", order);
				List ntableheadrightList = classService.getNTableHeadList(operator,"studentList.jsp","1");
				String width="250%";
				int aa=ntableheadrightList.size();
				if(ntableheadrightList.size()<=10)
				{
					 width="100%";
				}
				if(10<ntableheadrightList.size()&&ntableheadrightList.size()<=13)
				{
					 width="150%";
				}
				if(13<ntableheadrightList.size()&&ntableheadrightList.size()<=16)
				{
					 width="200%";
				}
				request.setAttribute("width", width);
				StudentListColumns studentlc = classService.getUserSessionColumns(operator, "studentList.jsp");
				request.setAttribute("studentlc", studentlc);
				
				return mapping.findForward("list");
			} else {
				// =================================================================
				studentmodels = studentService.getStudentExport(args,schoolId);
				// Create the Excel File
				String fileName = "studentInfo.xls";
				// Create the Sheet with the name of the Table
				HSSFWorkbook wb = new HSSFWorkbook();

				// ������ʾ�������Լ���ص���ʽ
				HSSFFont font = wb.createFont();
				font.setFontHeightInPoints((short) 8);
				font.setItalic(false);
				font.setStrikeout(false);

				// ���ñ�������Ԫ�����ʽ
				HSSFCellStyle cellHeadStyle = wb.createCellStyle();
				cellHeadStyle.setAlignment(HSSFCellStyle.ALIGN_CENTER);
				cellHeadStyle.setBorderBottom(HSSFCellStyle.BORDER_DOUBLE);
				cellHeadStyle.setBorderLeft((short) 1);
				cellHeadStyle.setBorderRight((short) 1);
				cellHeadStyle.setBorderTop(HSSFCellStyle.BORDER_DOUBLE);
				cellHeadStyle.setFillForegroundColor(HSSFColor.LIGHT_YELLOW.index);
				cellHeadStyle.setFillPattern(HSSFCellStyle.SOLID_FOREGROUND);

				// ���������е������Լ��Լ���صĶ��뷽ʽ
				HSSFCellStyle cellDataStyle = wb.createCellStyle();
				cellDataStyle.setAlignment(HSSFCellStyle.ALIGN_CENTER);
				cellDataStyle.setFont(font);

				HSSFSheet sheet1 = wb.createSheet("Sheet1");

				// Grab & populate the Column Names
				HSSFRow row = sheet1.createRow((short) 0);

				// Populate the first row of the spreadsheet with the column names
				List columnNames = new ArrayList();
				columnNames.add(0, "��Ժ");
				columnNames.add(1, "�༶");
				columnNames.add(2, "����Ա");
				columnNames.add(3, "ѧ��");
				columnNames.add(4, "¼ȡ֪ͨ���");
				columnNames.add(5, "����");
				columnNames.add(6, "�Ա�");	
				columnNames.add(7, "¼ȡԺϵ");
				columnNames.add(8, "¼ȡרҵ");			
				columnNames.add(9, "����");
				columnNames.add(10, "����");
				columnNames.add(11, "��Դ��");
				
				columnNames.add(12, "֤������");
				columnNames.add(13, "֤������");				
				columnNames.add(14, "�������");
				columnNames.add(15, "ѧ������");	
				columnNames.add(16, "�Ƿ��ڼ�");
				columnNames.add(17, "�Ƿ���У");						
				
				columnNames.add(18, "������ò");
				columnNames.add(19, "У��");
				columnNames.add(20, "¥��");
				columnNames.add(21, "�����");
				columnNames.add(22, "����");
				columnNames.add(23, "��ͥ�绰");
				columnNames.add(24, "��ʱһ��ͨ����");
				columnNames.add(25, "ԡ������");	
				columnNames.add(26, "����״̬");

				for (int i = 0; i < columnNames.size(); i++) {
					HSSFCell cname = row.createCell((short) i);
					cname.setCellStyle(cellHeadStyle);
					cname.setEncoding(HSSFCell.ENCODING_UTF_16);
					cname.setCellValue((String) columnNames.get(i));
				}

				// Populate the Row Data to the SpreadSheet
				int rowCount = studentmodels.size();
				// goal houses the number of cells in the target spreadsheet
				int goal = rowCount * columnNames.size();

				// actual population of target spreadsheet
				int currentCell = 0;

				for (int i = 0; i < rowCount; i++) {
					StudentWithAllInfo tableData = (StudentWithAllInfo) studentmodels
							.get(i);
					// create row in spreadsheet
					row = sheet1.createRow((short) (i + 1));

//					 populate the spreadsheet with the cell
					HSSFCell ctitle = row.createCell((short) 0);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getCollege());

					ctitle = row.createCell((short) 1);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getClassId());

					ctitle = row.createCell((short) 2);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getAssistant());

					ctitle = row.createCell((short) 3);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getStudentNo());
					
					ctitle = row.createCell((short) 4);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getEnterenceNo());
					
					ctitle = row.createCell((short) 5);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getStuName());

					ctitle = row.createCell((short) 6);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getGender());	
					
					ctitle = row.createCell((short) 7);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getDepartment());
					
					ctitle = row.createCell((short) 8);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getMajorin());			

					ctitle = row.createCell((short) 9);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getNation());

					ctitle = row.createCell((short) 10);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getNationality());

					ctitle = row.createCell((short) 11);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getFromProvince());
					
					ctitle = row.createCell((short) 12);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getIdType());

					ctitle = row.createCell((short) 13);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getIdCard());
					
					ctitle = row.createCell((short) 14);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getCultureMode());

					ctitle = row.createCell((short) 15);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getStudentChar());

					ctitle = row.createCell((short) 16);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getCheckornot()==null?"":tableData.getCheckornot().intValue()==1?"��":"��");

					ctitle = row.createCell((short) 17);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getSchoolornot()==null?"":tableData.getSchoolornot().intValue()==1?"��":"��");

					ctitle = row.createCell((short) 18);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getPolityBg());
					
					

					ctitle = row.createCell((short) 19);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getLocation());

					ctitle = row.createCell((short) 20);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getDormitory());

					ctitle = row.createCell((short) 21);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getRoomnumber());				
					
					ctitle = row.createCell((short) 22);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getBirthday());

					ctitle = row.createCell((short) 23);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getHomeTelephone());

					ctitle = row.createCell((short) 24);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getTempecardNo()==null?"":tableData.getTempecardNo().toString());

					ctitle = row.createCell((short) 25);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getBathcardNo());		
					
					ctitle = row.createCell((short) 26);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getExamNo()==null?"":tableData.getExamNo().equals("1")?"�ѱ���":"δ����");

					// System.out.println(columnData);
					currentCell++;

				}
				OutputStream os;
				try {
					response.setContentType("application/x-msdownload");
					response.setHeader("Content-Disposition", "attachment;"
							+ " filename="
							+ new String(fileName.getBytes(), "ISO-8859-1"));
					os = response.getOutputStream();
					wb.write(os);
					return null;
				} catch (UnsupportedEncodingException e) {
					e.printStackTrace();
					return null;
				} catch (IOException e) {
					e.printStackTrace();
					return null;
				}
				// =================================================================
			}
		}		
		else {

			//-------------------------------------------------������/��ְ��
			String schoolId = null;
			
			
			if (request.getParameter("export") == null
					|| "".equals(request.getParameter("export"))) {
				studentmodels = studentService.getStudent(args,schoolId);
				Integer studentCount = studentService.getStudentCount(args,schoolId);
				
				request.setAttribute("listcount", studentCount);
				
				request.setAttribute("myclass", classId);
				request.setAttribute("mydormitory", dormitory);
				// ������
				request.setAttribute("studentCount", studentCount);
				request.setAttribute("studentmodels", studentmodels);

				// �Ա�
				List genderList = studentService.getDiction("1");
				request.setAttribute("genderList", genderList);
				// ����
				List nationList = studentService.getDiction("2");
				request.setAttribute("nationList", nationList);
				// ��Դ��
				List provinceList = studentService.getDiction("10");
				request.setAttribute("provinceList", provinceList);
				// ������ò
				List polityList = studentService.getDiction("4");
				request.setAttribute("polityList", polityList);
				// רҵ
				List majorinList = studentService.getDiction("11");
				request.setAttribute("majorinList", majorinList);
				// ����
				List nationalityList = studentService.getDiction("12");
				request.setAttribute("nationalityList", nationalityList);
				// ��Ժ�б�
				List collegeList = collegeService.getAllCollegeByfdxy();
				Collegemodel m = new Collegemodel();
				m.setCollegeId("0002");
				m.setCollegeName("����ѧԺ");
				collegeList.add(m);
				request.setAttribute("collegeList", collegeList);
				// �༶�б�
				List classList = classService.getClassmodelbyschoolId(null);
				request.setAttribute("classList", classList);
				// ����Ա�б�
				List assistantList = managerService.getClassAssitant();
				List assistantList2 = managerService.getClassAssitant_hlxy();
				assistantList.addAll(assistantList2);
				request.setAttribute("assistantList", assistantList);
//				// �����б�
//				List locationList = studentService.getDiction("6");
//				request.setAttribute("locationList", locationList);
//				// ¥�б�
//				List buildingList = studentService.getDiction("7");
//				request.setAttribute("buildingList", buildingList);		
				classService.initForm(request);
				//Ժϵ�б�
				studentService.findDepartments(request);
				
				List areaList = directoryService.getAreas();
				request.setAttribute("areaList", areaList);
				request.setAttribute("locationList",Collections.EMPTY_LIST);
				request.setAttribute("dormitoryList",Collections.EMPTY_LIST);
				if (area != null) {
					List locationList = directoryService.getLocations(area);
					request.setAttribute("locationList",locationList);
				}
				if (location != null){
					List dormitoryList = directoryService.getDormitory(location);
					request.setAttribute("dormitoryList",dormitoryList);
				}

				request.setAttribute("orderby", orderby);
				request.setAttribute("order", order);
				return mapping.findForward("list_all");
			} else {
				// =================================================================
				studentmodels = studentService.getStudentExport(args,schoolId);
				// Create the Excel File
				String fileName = "studentInfo.xls";
				// Create the Sheet with the name of the Table
				HSSFWorkbook wb = new HSSFWorkbook();

				// ������ʾ�������Լ���ص���ʽ
				HSSFFont font = wb.createFont();
				font.setFontHeightInPoints((short) 8);
				font.setItalic(false);
				font.setStrikeout(false);

				// ���ñ�������Ԫ�����ʽ
				HSSFCellStyle cellHeadStyle = wb.createCellStyle();
				cellHeadStyle.setAlignment(HSSFCellStyle.ALIGN_CENTER);
				cellHeadStyle.setBorderBottom(HSSFCellStyle.BORDER_DOUBLE);
				cellHeadStyle.setBorderLeft((short) 1);
				cellHeadStyle.setBorderRight((short) 1);
				cellHeadStyle.setBorderTop(HSSFCellStyle.BORDER_DOUBLE);
				cellHeadStyle.setFillForegroundColor(HSSFColor.LIGHT_YELLOW.index);
				cellHeadStyle.setFillPattern(HSSFCellStyle.SOLID_FOREGROUND);

				// ���������е������Լ��Լ���صĶ��뷽ʽ
				HSSFCellStyle cellDataStyle = wb.createCellStyle();
				cellDataStyle.setAlignment(HSSFCellStyle.ALIGN_CENTER);
				cellDataStyle.setFont(font);

				HSSFSheet sheet1 = wb.createSheet("Sheet1");

				// Grab & populate the Column Names
				HSSFRow row = sheet1.createRow((short) 0);

				// Populate the first row of the spreadsheet with the column names
				List columnNames = new ArrayList();
				columnNames.add(0, "��Ժ");
				columnNames.add(1, "�༶");
				columnNames.add(2, "����Ա");
				columnNames.add(3, "ѧ��");
				columnNames.add(4, "¼ȡ֪ͨ���");
				columnNames.add(5, "����");
				columnNames.add(6, "�Ա�");	
				columnNames.add(7, "¼ȡԺϵ");
				columnNames.add(8, "¼ȡרҵ");			
				columnNames.add(9, "����");
				columnNames.add(10, "����");
				columnNames.add(11, "��Դ��");
				
				columnNames.add(12, "֤������");
				columnNames.add(13, "�������");
				columnNames.add(14, "ѧ������");	
				columnNames.add(15, "�Ƿ��ڼ�");
				columnNames.add(16, "�Ƿ���У");						
				
				columnNames.add(17, "������ò");
				columnNames.add(18, "У��");
				columnNames.add(19, "¥��");
				columnNames.add(20, "�����");
				columnNames.add(21, "����");
				columnNames.add(22, "��ͥ�绰");
				columnNames.add(23, "��ʱһ��ͨ����");
				columnNames.add(24, "ԡ������");	

				for (int i = 0; i < columnNames.size(); i++) {
					HSSFCell cname = row.createCell((short) i);
					cname.setCellStyle(cellHeadStyle);
					cname.setEncoding(HSSFCell.ENCODING_UTF_16);
					cname.setCellValue((String) columnNames.get(i));
				}

				// Populate the Row Data to the SpreadSheet
				int rowCount = studentmodels.size();
				// goal houses the number of cells in the target spreadsheet
				int goal = rowCount * columnNames.size();

				// actual population of target spreadsheet
				int currentCell = 0;

				for (int i = 0; i < rowCount; i++) {
					StudentWithAllInfo tableData = (StudentWithAllInfo) studentmodels
							.get(i);
					// create row in spreadsheet
					row = sheet1.createRow((short) (i + 1));

//					 populate the spreadsheet with the cell
					HSSFCell ctitle = row.createCell((short) 0);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getCollege());

					ctitle = row.createCell((short) 1);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getClassId());

					ctitle = row.createCell((short) 2);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getAssistant());

					ctitle = row.createCell((short) 3);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getStudentNo());
					
					ctitle = row.createCell((short) 4);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getEnterenceNo());
					
					ctitle = row.createCell((short) 5);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getStuName());

					ctitle = row.createCell((short) 6);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getGender());	
					
					ctitle = row.createCell((short) 7);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getDepartment());
					
					ctitle = row.createCell((short) 8);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getMajorin());			

					ctitle = row.createCell((short) 9);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getNation());

					ctitle = row.createCell((short) 10);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getNationality());

					ctitle = row.createCell((short) 11);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getFromProvince());
					
					ctitle = row.createCell((short) 12);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getIdType());

					ctitle = row.createCell((short) 13);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getCultureMode());

					ctitle = row.createCell((short) 14);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getStudentChar());

					ctitle = row.createCell((short) 15);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getCheckornot()==null?"":tableData.getCheckornot().intValue()==1?"��":"��");

					ctitle = row.createCell((short) 16);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getSchoolornot()==null?"":tableData.getSchoolornot().intValue()==1?"��":"��");

					ctitle = row.createCell((short) 17);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getPolityBg());
					
					

					ctitle = row.createCell((short) 18);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getLocation());

					ctitle = row.createCell((short) 19);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getDormitory());

					ctitle = row.createCell((short) 20);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getRoomnumber());				
					
					ctitle = row.createCell((short) 21);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getBirthday());

					ctitle = row.createCell((short) 22);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getHomeTelephone());

					ctitle = row.createCell((short) 23);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getTempecardNo()==null?"":tableData.getTempecardNo().toString());

					ctitle = row.createCell((short) 24);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getBathcardNo());		

					// System.out.println(columnData);
					currentCell++;

				}
				OutputStream os;
				try {
					response.setContentType("application/x-msdownload");
					response.setHeader("Content-Disposition", "attachment;"
							+ " filename="
							+ new String(fileName.getBytes(), "ISO-8859-1"));
					os = response.getOutputStream();
					wb.write(os);
					return null;
				} catch (UnsupportedEncodingException e) {
					e.printStackTrace();
					return null;
				} catch (IOException e) {
					e.printStackTrace();
					return null;
				}
				// =================================================================
			}
		
		}

	}

	public ActionForward load4fdySearch(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		String operator = "";
		if (request.getSession().getAttribute("accountPerson") != null) {
			operator = ((Account) request.getSession().getAttribute(
					"accountPerson")).getPerson().getId();
		}
		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//����ѧԺ
			//-------------------------------------------------
			HttpSession session = request.getSession(false);
			ActionMessages messages = new ActionMessages();
			DynaActionForm studentForm = (DynaActionForm) form;
			Studentmodel studentmodel = (Studentmodel) studentForm
					.get("studentmodel");
			String studentNo = studentmodel.getStudentNo();
			String enterenceNo = studentmodel.getEnterenceNo();
			String stuName = studentmodel.getStuName();
			String gender = studentmodel.getGender();
			String nation = studentmodel.getNation();
			String province = studentmodel.getFromProvince();
			String polity = studentmodel.getPolityBg();
			String majorin = studentmodel.getMajorin();
			String nationality = studentmodel.getNationality();

			String idCard = studentmodel.getIdCard();
			String idType = studentmodel.getIdType();
			String cultureMode = studentmodel.getCultureMode();
			String studentChar = studentmodel.getStudentChar();
			String checkornot = studentForm.getString("checkornot1");
			String schoolornot = studentForm.getString("schoolornot1");
			
			String classId = studentForm.getString("classId");
			
			String area = studentForm.getString("area");
			String location = studentForm.getString("location");
			String dormitory = studentForm.getString("dormitory");
			String roomnumber = studentForm.getString("roomnumber");
			String page = request.getParameter("pager.offset");

			String department = studentmodel.getDepartment();
			
			String order = request.getParameter("horder");
			String odr = "asc";
			if (order != null && order.length() > 0 && order.equals("d"))
				odr = "desc";
			String orderby = request.getParameter("orderby");

			String[] args = { studentNo, stuName, gender, nation, province, polity,
					location, dormitory, roomnumber, majorin, nationality, page,
					orderby, odr,department,area,
					idType,cultureMode,studentChar,checkornot,schoolornot,classId,enterenceNo,idCard };
			Account account = null;
			if (session.getAttribute("accountPerson") != null) {
				account = (Account) session.getAttribute("accountPerson");
				String managerNo = account.getPerson().getPersonCode();
				List managerList = managerService.getManagerByNo(managerNo);
				if (managerList.size() > 0) {
					Managermodel Managermodel = (Managermodel) managerList.get(0);
					List classlist = managerService.findManagerclass_hlxy(Managermodel.getManagerId());
					List studentmodels = null;
					if (classlist!=null&&classlist.size()>0) {
						if (request.getParameter("export") == null
								|| "".equals(request.getParameter("export"))) {
//							Classmodel model = classService.getClassmodel(managerclass);
							studentmodels = studentService.getfdyStudent_hlxy(args,
									classlist);
							Integer studentCount = studentService
									.getfdyStudentCount_hlxy(args, classlist);
							
							request.setAttribute("listcount", studentCount);
							
							request.setAttribute("mydormitory", dormitory);
							// ������
							request.setAttribute("studentCount", studentCount);
							request.setAttribute("studentmodels", studentmodels);

							// �Ա�
							List genderList = studentService.getDiction("1");
							request.setAttribute("genderList", genderList);
							// ����
							List nationList = studentService.getnationList();
							request.setAttribute("nationList", nationList);
							// ��Դ��
							List provinceList = studentService.getfromProvinceList();
							request.setAttribute("provinceList", provinceList);
							// ������ò
							List polityList = studentService.getDiction("4");
							request.setAttribute("polityList", polityList);
							// רҵ
							List majorinList = studentService.getmajorList();
							request.setAttribute("majorinList", majorinList);
							// ����
							List nationalityList = studentService.getcountryList();
							request.setAttribute("nationalityList", nationalityList);
//							// �����б�
//							List locationList = studentService.getDiction("6");
//							request.setAttribute("locationList", locationList);
//							// ¥�б�
//							List buildingList = studentService.getDiction("7");
//							request.setAttribute("buildingList", buildingList);
							dormitoryService.initForm_fdy(request);
							
							//Ժϵ�б�
							List ntableheadrightList = classService.getNTableHeadList(operator,"sdhdyListhlxy","1");
							String width="250%";
							if(ntableheadrightList.size()<=10)
							{
								 width="100%";
							}
							if(10<ntableheadrightList.size()&&ntableheadrightList.size()<=13)
							{
								 width="150%";
							}
							if(13<ntableheadrightList.size()&&ntableheadrightList.size()<=16)
							{
								 width="200%";
							}
							request.setAttribute("width", width);
							studentService.findDepartments(request);						
							SdfdyListhlxy studentlc = classService.getUserSessionfdyhlxyColumns(operator, "sdhdyListhlxy");
							request.setAttribute("studentlc", studentlc);
							request.setAttribute("myclassNo", null);
							request.setAttribute("orderby", orderby);
							request.setAttribute("order", order);
						} else {
							// =================================================================
							studentmodels = studentService.getfdyStudentExport_hlxy(
									args, classlist);
							// Create the Excel File
							String fileName = "student_fdy_Info.xls";
							// Create the Sheet with the name of the Table
							HSSFWorkbook wb = new HSSFWorkbook();

							// ������ʾ�������Լ���ص���ʽ
							HSSFFont font = wb.createFont();
							font.setFontHeightInPoints((short) 8);
							font.setItalic(false);
							font.setStrikeout(false);

							// ���ñ�������Ԫ�����ʽ
							HSSFCellStyle cellHeadStyle = wb.createCellStyle();
							cellHeadStyle.setAlignment(HSSFCellStyle.ALIGN_CENTER);
							cellHeadStyle
									.setBorderBottom(HSSFCellStyle.BORDER_DOUBLE);
							cellHeadStyle.setBorderLeft((short) 1);
							cellHeadStyle.setBorderRight((short) 1);
							cellHeadStyle.setBorderTop(HSSFCellStyle.BORDER_DOUBLE);
							cellHeadStyle
									.setFillForegroundColor(HSSFColor.LIGHT_YELLOW.index);
							cellHeadStyle
									.setFillPattern(HSSFCellStyle.SOLID_FOREGROUND);

							// ���������е������Լ��Լ���صĶ��뷽ʽ
							HSSFCellStyle cellDataStyle = wb.createCellStyle();
							cellDataStyle.setAlignment(HSSFCellStyle.ALIGN_CENTER);
							cellDataStyle.setFont(font);

							HSSFSheet sheet1 = wb.createSheet("Sheet1");

							// Grab & populate the Column Names
							HSSFRow row = sheet1.createRow((short) 0);
							 
							// Populate the first row of the spreadsheet with the
							// column names
							List columnNames = new ArrayList();
							columnNames.add(0, "�༶");
							columnNames.add(1, "ѧ��");
							columnNames.add(2, "¼ȡ֪ͨ���");
							columnNames.add(3, "����");
							columnNames.add(4, "�Ա�");						
					
							columnNames.add(5, "����");
							columnNames.add(6, "����");
							
							columnNames.add(7, "֤������");
							columnNames.add(8, "֤������");
							columnNames.add(9, "�������");
							columnNames.add(10, "ѧ������");	
							columnNames.add(11, "�Ƿ��ڼ�");
							columnNames.add(12, "�Ƿ���У");		

							columnNames.add(13, "������ò");
							columnNames.add(14, "У��");
							columnNames.add(15, "����");
							columnNames.add(16, "¥��");
							columnNames.add(17, "�����");
							columnNames.add(18, "����");
							columnNames.add(19, "��ͥ�绰");
							columnNames.add(20, "��ʱһ��ͨ����");
//							columnNames.add(19, "ԡ������");

							for (int i = 0; i < columnNames.size(); i++) {
								HSSFCell cname = row.createCell((short) i);
								cname.setCellStyle(cellHeadStyle);
								cname.setEncoding(HSSFCell.ENCODING_UTF_16);
								cname.setCellValue((String) columnNames.get(i));
							}

							// Populate the Row Data to the SpreadSheet
							int rowCount = studentmodels.size();
							// goal houses the number of cells in the target
							// spreadsheet
							int goal = rowCount * columnNames.size();

							// actual population of target spreadsheet
							int currentCell = 0;

							for (int i = 0; i < rowCount; i++) {
								StudentWithAllInfo tableData = (StudentWithAllInfo) studentmodels
										.get(i);
								// create row in spreadsheet
								row = sheet1.createRow((short) (i + 1));

								// populate the spreadsheet with the cell
								HSSFCell ctitle = row.createCell((short) 0);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getClassId());
								
								ctitle = row.createCell((short) 1);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getStudentNo());
								
								ctitle = row.createCell((short) 2);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getEnterenceNo());
								
								ctitle = row.createCell((short) 3);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getStuName());

								ctitle = row.createCell((short) 4);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getGender());	
								

								ctitle = row.createCell((short) 5);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getNation());

								ctitle = row.createCell((short) 6);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getNationality());
								
								ctitle = row.createCell((short) 7);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getIdType());
								
								ctitle = row.createCell((short) 8);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getIdCard());

								ctitle = row.createCell((short) 9);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getCultureMode());

								ctitle = row.createCell((short) 10);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getStudentChar());

								ctitle = row.createCell((short) 11);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getCheckornot()==null?"":tableData.getCheckornot().intValue()==1?"��":"��");

								ctitle = row.createCell((short) 12);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getSchoolornot()==null?"":tableData.getSchoolornot().intValue()==1?"��":"��");

								ctitle = row.createCell((short) 13);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getPolityBg());

								ctitle = row.createCell((short) 14);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getArea());
								
								ctitle = row.createCell((short) 15);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getLocation());

								ctitle = row.createCell((short) 16);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getDormitory());

								ctitle = row.createCell((short) 17);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getRoomnumber());
								
								ctitle = row.createCell((short) 18);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getBirthday());

								ctitle = row.createCell((short) 19);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getHomeTelephone());

								ctitle = row.createCell((short) 20);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getTempecardNo()==null?"":tableData.getTempecardNo().toString());

//								ctitle = row.createCell((short) 19);
//								ctitle.setCellStyle(cellDataStyle);
//								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
//								ctitle.setCellValue(tableData.getBathcardNo());		

								// System.out.println(columnData);
								currentCell++;

							}
							OutputStream os;
							try {
								response.setContentType("application/x-msdownload");
								response.setHeader("Content-Disposition",
										"attachment;"
												+ " filename="
												+ new String(fileName.getBytes(),
														"ISO-8859-1"));
								os = response.getOutputStream();
								wb.write(os);
								return null;
							} catch (UnsupportedEncodingException e) {
								e.printStackTrace();
								return null;
							} catch (IOException e) {
								e.printStackTrace();
								return null;
							}
							// =================================================================
						}
					}else{
						messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"classAlert.loginFirstornotass"));
						saveErrors(request, messages);
					return load4fdyList(mapping, form, request, response);
					}
				}else{
					messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"classAlert.loginFirstornotass"));
					saveErrors(request, messages);
				return load4fdyList(mapping, form, request, response);
				}
			} else {
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"classAlert.loginFirstornotass"));
				saveErrors(request, messages);
				return load4fdyList(mapping, form, request, response);
			}

			return mapping.findForward("fdylist_hlxy");
		}else{
			//-------------------------------------------------����ѧԺ
			
			studentService.findAssistantList(request);
			List ntableheadrightList = classService.getNTableHeadList(operator,"sdfdyList.jsp","1");
			String width="250%";
			if(ntableheadrightList.size()<=10)
			{
				 width="100%";
			}
			if(10<ntableheadrightList.size()&&ntableheadrightList.size()<=13)
			{
				 width="150%";
			}
			if(13<ntableheadrightList.size()&&ntableheadrightList.size()<=16)
			{
				 width="200%";
			}
			request.setAttribute("width", width);
			StudentfdyListColmns studentlc = classService.getUserSessionfdyColumns(operator, "sdfdyList.jsp");
			request.setAttribute("studentlc", studentlc);
			HttpSession session = request.getSession(false);
			ActionMessages messages = new ActionMessages();
			DynaActionForm studentForm = (DynaActionForm) form;
			Studentmodel studentmodel = (Studentmodel) studentForm
					.get("studentmodel");
			String studentNo = studentmodel.getStudentNo();
			String enterenceNo = studentmodel.getEnterenceNo();
			String stuName = studentmodel.getStuName();
			String gender = studentmodel.getGender();
			String nation = studentmodel.getNation();
			String province = studentmodel.getFromProvince();
			String polity = studentmodel.getPolityBg();
			String majorin = studentmodel.getMajorin();
			String nationality = studentmodel.getNationality();
			String location = studentForm.getString("location");
			String dormitory = studentForm.getString("dormitory");
			String roomnumber = studentForm.getString("roomnumber");
			String page = request.getParameter("pager.offset");

			String department = studentmodel.getDepartment();
			
			String idCard = studentmodel.getIdCard();			
			String idType = studentmodel.getIdType();
			String cultureMode = studentmodel.getCultureMode();
			String studentChar = studentmodel.getStudentChar();
			
			String checkornot = studentForm.getString("checkornot1");
			String schoolornot = studentForm.getString("schoolornot1");
			
//			Integer schoolornot = studentmodel.getSchoolornot();
			
			String order = request.getParameter("horder");
			String odr = "asc";
			if (order != null && order.length() > 0 && order.equals("d"))
				odr = "desc";
			String orderby = request.getParameter("orderby");

			String[] args = { studentNo, stuName, gender, nation, province, polity,
					location, dormitory, roomnumber, majorin, nationality, page,
					orderby, odr,department,
					idType,cultureMode,studentChar,
					checkornot,schoolornot,enterenceNo,idCard };
			Account account = null;
			if (session.getAttribute("accountPerson") != null) {
				account = (Account) session.getAttribute("accountPerson");
				String managerNo = account.getPerson().getPersonCode();
				List managerList = managerService.getManagerByNo(managerNo);
				if (managerList.size() > 0) {
					Managermodel Managermodel = (Managermodel) managerList.get(0);
					String managerclass = managerService
							.findManagerclass(Managermodel.getManagerId());
					List studentmodels = null;
					if (!"".equals(managerclass)) {
						if (request.getParameter("export") == null
								|| "".equals(request.getParameter("export"))) {
							Classmodel model = classService.getClassmodel(managerclass);
							studentmodels = studentService.getfdyStudent(args,
									managerclass);
							Integer studentCount = studentService
									.getfdyStudentCount(args, managerclass);
							
							request.setAttribute("listcount", studentCount);
							
							request.setAttribute("mydormitory", dormitory);
							// ������
							request.setAttribute("studentCount", studentCount);
							request.setAttribute("studentmodels", studentmodels);

							// �Ա�
							List genderList = studentService.getDiction("1");
							request.setAttribute("genderList", genderList);
							// ����
							List nationList = studentService.getnationList();
							request.setAttribute("nationList", nationList);
							// ��Դ��
							List provinceList = studentService.getfromProvinceList();
							request.setAttribute("provinceList", provinceList);
							// ������ò
							List polityList = studentService.getDiction("4");
							request.setAttribute("polityList", polityList);
							// רҵ
							List majorinList = studentService.getmajorList();
							request.setAttribute("majorinList", majorinList);
							// ����
							List nationalityList = studentService.getcountryList();
							request.setAttribute("nationalityList", nationalityList);
//							// �����б�
//							List locationList = studentService.getDiction("6");
//							request.setAttribute("locationList", locationList);
//							// ¥�б�
//							List buildingList = studentService.getDiction("7");
//							request.setAttribute("buildingList", buildingList);
							dormitoryService.initForm_fdy(request);
							
							//Ժϵ�б�
							studentService.findDepartments(request);						
							
							request.setAttribute("myclassNo", model.getClassNo());
							request.setAttribute("orderby", orderby);
							request.setAttribute("order", order);
						} else {
							// =================================================================
							studentmodels = studentService.getfdyStudentExport(
									args, managerclass);
							// Create the Excel File
							String fileName = "student_fdy_Info.xls";
							// Create the Sheet with the name of the Table
							HSSFWorkbook wb = new HSSFWorkbook();

							// ������ʾ�������Լ���ص���ʽ
							HSSFFont font = wb.createFont();
							font.setFontHeightInPoints((short) 8);
							font.setItalic(false);
							font.setStrikeout(false);

							// ���ñ�������Ԫ�����ʽ
							HSSFCellStyle cellHeadStyle = wb.createCellStyle();
							cellHeadStyle.setAlignment(HSSFCellStyle.ALIGN_CENTER);
							cellHeadStyle
									.setBorderBottom(HSSFCellStyle.BORDER_DOUBLE);
							cellHeadStyle.setBorderLeft((short) 1);
							cellHeadStyle.setBorderRight((short) 1);
							cellHeadStyle.setBorderTop(HSSFCellStyle.BORDER_DOUBLE);
							cellHeadStyle
									.setFillForegroundColor(HSSFColor.LIGHT_YELLOW.index);
							cellHeadStyle
									.setFillPattern(HSSFCellStyle.SOLID_FOREGROUND);

							// ���������е������Լ��Լ���صĶ��뷽ʽ
							HSSFCellStyle cellDataStyle = wb.createCellStyle();
							cellDataStyle.setAlignment(HSSFCellStyle.ALIGN_CENTER);
							cellDataStyle.setFont(font);

							HSSFSheet sheet1 = wb.createSheet("Sheet1");

							// Grab & populate the Column Names
							HSSFRow row = sheet1.createRow((short) 0);
							 
							// Populate the first row of the spreadsheet with the
							// column names
							List columnNames = new ArrayList();
							columnNames.add(0, "ѧ��");
							columnNames.add(1, "¼ȡ֪ͨ���");
							columnNames.add(2, "����");
							columnNames.add(3, "�Ա�");						
							columnNames.add(4, "¼ȡԺϵ");						
							columnNames.add(5, "¼ȡרҵ");						
							columnNames.add(6, "����");
							columnNames.add(7, "����");
							columnNames.add(8, "��Դ��");
							
							columnNames.add(9, "֤������");
							columnNames.add(10, "֤������");
							columnNames.add(11, "�������");
							columnNames.add(12, "ѧ������");	
							columnNames.add(13, "�Ƿ��ڼ�");
							columnNames.add(14, "�Ƿ���У");									
							
							columnNames.add(15, "������ò");
							columnNames.add(16, "У��");
							columnNames.add(17, "¥��");
							columnNames.add(18, "�����");
							columnNames.add(19, "����");
							columnNames.add(20, "��ͥ�绰");
							columnNames.add(21, "��ʱһ��ͨ����");
							columnNames.add(22, "ԡ������");
							columnNames.add(23, "����״̬");

							for (int i = 0; i < columnNames.size(); i++) {
								HSSFCell cname = row.createCell((short) i);
								cname.setCellStyle(cellHeadStyle);
								cname.setEncoding(HSSFCell.ENCODING_UTF_16);
								cname.setCellValue((String) columnNames.get(i));
							}

							// Populate the Row Data to the SpreadSheet
							int rowCount = studentmodels.size();
							// goal houses the number of cells in the target
							// spreadsheet
							int goal = rowCount * columnNames.size();

							// actual population of target spreadsheet
							int currentCell = 0;

							for (int i = 0; i < rowCount; i++) {
								StudentWithAllInfo tableData = (StudentWithAllInfo) studentmodels
										.get(i);
								// create row in spreadsheet
								row = sheet1.createRow((short) (i + 1));

								// populate the spreadsheet with the cell
								HSSFCell ctitle = row.createCell((short) 0);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getStudentNo());
								
								ctitle = row.createCell((short) 1);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getEnterenceNo());
								
								ctitle = row.createCell((short) 2);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getStuName());

								ctitle = row.createCell((short) 3);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getGender());
								
								ctitle = row.createCell((short) 4);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getDepartment());
													

								ctitle = row.createCell((short) 5);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getMajorin());		
								

								ctitle = row.createCell((short) 6);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getNation());

								ctitle = row.createCell((short) 7);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getNationality());

								ctitle = row.createCell((short) 8);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getFromProvince());
								
								ctitle = row.createCell((short) 9);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getIdType());

								ctitle = row.createCell((short) 10);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getIdCard());
								
								ctitle = row.createCell((short) 11);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getCultureMode());

								ctitle = row.createCell((short) 12);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getStudentChar());

								ctitle = row.createCell((short) 13);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getCheckornot()==null?"":tableData.getCheckornot().intValue()==1?"��":"��");

								ctitle = row.createCell((short) 14);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getSchoolornot()==null?"":tableData.getSchoolornot().intValue()==1?"��":"��");								

								ctitle = row.createCell((short) 15);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getPolityBg());

								ctitle = row.createCell((short) 16);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getLocation());

								ctitle = row.createCell((short) 17);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getDormitory());

								ctitle = row.createCell((short) 18);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getRoomnumber());
								
								ctitle = row.createCell((short) 19);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getBirthday());

								ctitle = row.createCell((short) 20);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getHomeTelephone());

								ctitle = row.createCell((short) 21);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getTempecardNo()==null?"":tableData.getTempecardNo().toString());

								ctitle = row.createCell((short) 22);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getBathcardNo());		
								
								ctitle = row.createCell((short) 23);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getExamNo()==null?"":tableData.getExamNo().equals("1")?"�ѱ���":"δ����");

								// System.out.println(columnData);
								currentCell++;

							}
							OutputStream os;
							try {
								response.setContentType("application/x-msdownload");
								response.setHeader("Content-Disposition",
										"attachment;"
												+ " filename="
												+ new String(fileName.getBytes(),
														"ISO-8859-1"));
								os = response.getOutputStream();
								wb.write(os);
								return null;
							} catch (UnsupportedEncodingException e) {
								e.printStackTrace();
								return null;
							} catch (IOException e) {
								e.printStackTrace();
								return null;
							}
							// =================================================================
						}
					}else{
						messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"classAlert.loginFirstornotass"));
						saveErrors(request, messages);
					return load4fdyList(mapping, form, request, response);
					}
				}else{
					messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"classAlert.loginFirstornotass"));
					saveErrors(request, messages);
				return load4fdyList(mapping, form, request, response);
				}
			} else {
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"classAlert.loginFirstornotass"));
				saveErrors(request, messages);
				return load4fdyList(mapping, form, request, response);
			}

			return mapping.findForward("fdylist");
		}
		

	}

	public ActionForward abroad4List(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		// // ����
		// request
		// .setAttribute("nationalityList", studentService
		// .getDiction("12"));
		// // רҵ
		// request.setAttribute("majorinList", studentService.getDiction("11"));
		// // �Ա�
		// request.setAttribute("genderList", studentService.getDiction("1"));
		// List abroadStu = studentService.getAbroadStudent();
		// request.setAttribute("abroadmodels", abroadStu);
		return mapping.findForward("abroadStudentlist");
	}

	public ActionForward abroad4Search(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		DynaActionForm studentForm = (DynaActionForm) form;
		Studentmodel studentmodel = (Studentmodel) studentForm
				.get("studentmodel");
		String studentNo = studentmodel.getStudentNo();
		String stuName = studentmodel.getStuName();
		String nationality = studentmodel.getNationality();
		String majorin = studentmodel.getMajorin();
		String[] args = { studentNo, stuName, nationality, majorin };
		List abroadStu = studentService.getAbroadStudent(args);
		request.setAttribute("abroadmodels", abroadStu);

		// ����
		List nationalityList = studentService.getDiction("12");
		request.setAttribute("nationalityList", nationalityList);
		// רҵ
		List majorinList = studentService.getDiction("11");
		request.setAttribute("majorinList", majorinList);
		// �Ա�
		List genderList = studentService.getDiction("1");
		request.setAttribute("genderList", genderList);

		return mapping.findForward("abroadStudentlist");
	}

	public ActionForward class4List(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		DynaActionForm classesForm = (DynaActionForm) form;
		// get all studentId info
		String[] deleteX = request.getParameterValues("deleteX");
		String studentIds = "";
		for (int i = 0; deleteX != null && i < deleteX.length; i++) {
			if (i < deleteX.length - 1) {
				studentIds += deleteX[i] + ",";
			} else {
				studentIds += deleteX[i];
			}
		}
		classesForm.set("studentIds", studentIds);

		return mapping.findForward("abroadClasslist");
	}

	public ActionForward class4Search(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		DynaActionForm classesForm = (DynaActionForm) form;
		String college = classesForm.getString("college");
		String classId = classesForm.getString("classId");
		String[] args = { college, classId };
		// get all studentId info
		String[] deleteX = request.getParameterValues("deleteX");
		String studentIds = "";
		for (int i = 0; deleteX != null && i < deleteX.length; i++) {
			if (i < deleteX.length - 1) {
				studentIds += deleteX[i] + ",";
			} else {
				studentIds += deleteX[i];
			}
		}
		classesForm.set("studentIds", studentIds);
		// ��Ժ�б�
		List collegeList = collegeService.getAllCollegeByfdxy();
		request.setAttribute("collegeList", collegeList);
		// �༶�б�
		List classList = classService.getClassmodelbyschoolId("0001");
		request.setAttribute("classList", classList);
		List abroadClasses = classService.findClassList(args);
		request.setAttribute("abroadClasses", abroadClasses);
		return mapping.findForward("abroadClasslist");
	}

	public ActionForward abroadDistribution(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) {
		DynaActionForm classesForm = (DynaActionForm) form;
		String studentIds = classesForm.get("studentIds").toString();
		String[] deleteX = request.getParameterValues("deleteX");
		// Extract attributes and parameters we will need
		ActionMessages messages = new ActionMessages();
		try {
			studentService.distributAbroadtoClass(studentIds, deleteX);
		} catch (Exception e) {
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"abroadDistribution.notsuccess"));
			saveErrors(request, messages);
			return abroad4List(mapping, form, request, response);
		}
		// ��ѧ���ְ�
		messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
				"abroadDistribution.success"));
		saveErrors(request, messages);
		List majorList = classService.abroadMajorinList();
		request.setAttribute("majorList", majorList);
		List majorStatistic = classService.abroadMajorinResultStatistic();
		
		String schoolId = "0001";
		List collegeclassList = classService.getCollegeClassList(schoolId);
		request.setAttribute("collegeclassList", collegeclassList);
		request.setAttribute("majorinStatistic", majorStatistic);
		return mapping.findForward("abroadStudentlist");
	}

	public ActionForward Distr4ClsList(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		return mapping.findForward("dormDistributionClslist");
	}

	public ActionForward Distr4ClsSearch(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) {
		List dormDistributionClslist = classService.findClassList();
		request
				.setAttribute("dormDistributionClslist",
						dormDistributionClslist);
		return mapping.findForward("dormDistributionClslist");
	}

	// public ActionForward dormDstrbution(ActionMapping mapping, ActionForm
	// form,
	// HttpServletRequest request, HttpServletResponse response) {
	// String[] deleteX = request.getParameterValues("deleteX");
	// // Extract attributes and parameters we will need
	// ActionMessages messages = new ActionMessages();
	// try {
	// dormitoryService.saveDistribution(deleteX);
	// // ѧ���ְ�
	// messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
	// "dormDistribution.success"));
	// saveErrors(request, messages);
	// } catch (StudentAlreadyInDormException e) {
	// messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
	// "dormDistribution.studentalreadyindorm"));
	// saveErrors(request, messages);
	// return Distr4ClsList(mapping, form, request, response);
	// } catch (DormitoryNotEnoughException e) {
	// messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
	// "dormDistribution.dormitorynotenough"));
	// saveErrors(request, messages);
	// return Distr4ClsList(mapping, form, request, response);
	// }
	// List dormStat = null;
	// dormStat = dormitoryService.getDormStat();
	// Integer dormStatCount = new Integer(0);
	// dormStatCount = dormitoryService.getDormStatCount();
	// if (dormStatCount.intValue() != 0) {
	// request.setAttribute("dormStat", dormStat);
	// request.setAttribute("dormStatCount", dormStatCount);
	// }
	// return mapping.findForward("dormStat");
	// }

	public ActionForward dormDistributionFirstStep(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) {
		// ѧԺ�б�
		List collegeList = collegeService.getAllCollegeByfdxy();
		request.setAttribute("collegeList", collegeList);
		List MajorinList = studentService.getAllMajorinInfo();
		request.setAttribute("MajorinList", MajorinList);
		List CHNStudentCount = studentService.getCHNStudentCount();
		request.setAttribute("CHNStudentCount", CHNStudentCount);
		List AbroadStudentCount = studentService.getAbroadStudentCount();
		request.setAttribute("AbroadStudentCount", AbroadStudentCount);
		List hisDistribution = studentService.getHisDistribution();
		request.setAttribute("hisDistribution", hisDistribution);

		return mapping.findForward("dormDistrFS");
	}

	public ActionForward dormDistributionSecondStep(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) {
		List collegeList = collegeService.getAllCollegeByfdxy();
		String[][] deleteX = new String[collegeList.size()][200];
		for (int i = 0; i < collegeList.size(); i++) {
			Collegemodel collegemodel = (Collegemodel) collegeList.get(i);
			deleteX[i] = request
					.getParameterValues(collegemodel.getCollegeId());
		}

		ActionMessages messages = new ActionMessages();
		try {
			dormitoryService.saveCollegeDistribution(deleteX, collegeList);
			// ѧ���ְ�
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"dormDistribution.success"));
			saveErrors(request, messages);
		} catch (StudentAlreadyInDormException e) {
//			e.printStackTrace();
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"dormDistribution.studentalreadyindorm"));
			saveErrors(request, messages);
//			return dormDistributionThirdStep(mapping, form, request, response);
		} catch (Exception e) {
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"dormDistribution.error"));
			saveErrors(request, messages);
			return dormDistributionFirstStep(mapping, form, request, response);
		}
		// ͳ�Ʒ�����
		request.setAttribute("collegeList", collegeList);
		List CollegeCHNStudentCount = studentService
				.getCollegeCHNStudentCount();
		request.setAttribute("CollegeCHNStudentCount", CollegeCHNStudentCount);
		List CollegeAbroadStudentCount = studentService
				.getCollegeAbroadStudentCount();
		request.setAttribute("CollegeAbroadStudentCount",
				CollegeAbroadStudentCount);
		List CollegeDormitoryStatistic = studentService.getCollegeDormitoryStatistic();
		request.setAttribute("CollegeDormitoryStatistic",
				CollegeDormitoryStatistic);
//		
//		String schoolId = "0001";
		List collegeList1 = collegeService.getAllCollegeByfdxy();
		Collegemodel colmap = new Collegemodel();
		colmap.setCollegeId("daleiCount");
		colmap.setCollegeName("daleiCount");
		colmap.setCollegeNo("");
		collegeList1.add(collegeList.size(),colmap);
		request.setAttribute("collegeList1", collegeList1);
		List daleiList = studentService.getDiction("14");
		request.setAttribute("daleiList", daleiList);
		List daleiResultStatistic = classService.daleiResultStatisticDormDistr();
		request.setAttribute("daleiResultStatistic", daleiResultStatistic);
		
		return mapping.findForward("dormDistrSS");
	}

	public ActionForward dormDistributionThirdStep(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) {
		List collegeList = collegeService.getAllCollegeByfdxy();
		request.setAttribute("collegeList", collegeList);
		List CollegeCHNStudentCount = studentService
				.getCollegeCHNStudentCount();
		request.setAttribute("CollegeCHNStudentCount", CollegeCHNStudentCount);
		List CollegeAbroadStudentCount = studentService
				.getCollegeAbroadStudentCount();
		request.setAttribute("CollegeAbroadStudentCount",
				CollegeAbroadStudentCount);
		List CollegeDormitoryStatistic = studentService.getCollegeDormitoryStatistic();
		request.setAttribute("CollegeDormitoryStatistic",
				CollegeDormitoryStatistic);
		return mapping.findForward("dormDistrSS");
	}

	public ActionForward dormDistributionFourStep(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) {
		List collegeList = collegeService.getAllCollegeByfdxy();
		request.setAttribute("collegeList", collegeList);
		List daleiList = studentService.getDiction("14");
		request.setAttribute("daleiList", daleiList);
		
		String schoolId = "0001";
		List daleiResultStatistic = classService.daleiResultStatistic(schoolId);
		request.setAttribute("daleiResultStatistic", daleiResultStatistic);

		List collegeclassList = classService.getCollegeClassList(schoolId);
		
		String collegeId = "";
		String collegename = "";
		for (int i = 0; i < collegeclassList.size(); i++) {
			HashMap temp = (HashMap) collegeclassList.get(i);
			if (collegename.equals(temp.get("collegeName").toString())
					|| i == 0) {
				collegeId = temp.get("collegeId").toString();
				collegename = temp.get("collegeName").toString();
			}
			if (i == collegeclassList.size() - 1) {
				HashMap addmap = new HashMap();
				addmap.put("collegeId", collegeId);
				addmap.put("collegeName", collegename);
				addmap.put("classNo", "smallCount");
				collegeclassList.add(i + 1, addmap);
				break;
			}
			if (!collegename.equals(temp.get("collegeName").toString())
					&& i > 0) {
				HashMap addmap = new HashMap();
				addmap.put("collegeId", collegeId);
				addmap.put("collegeName", collegename);
				addmap.put("classNo", "smallCount");
				collegeclassList.add(i, addmap);
				collegename = temp.get("collegeName").toString();
			}
		}
		// �ܼ�
		HashMap addmap = new HashMap();
		addmap.put("collegeId", "allCount");
		addmap.put("collegeName", "allCount");
		addmap.put("classNo", "--");
		collegeclassList.add(collegeclassList.size(), addmap);
		request.setAttribute("collegeclassList", collegeclassList);
		request.setAttribute("zhuanyeResultStatistic", classService
				.zhuanyeResultStatistic());
		return mapping.findForward("dormDistrTS");
	}

	public ActionForward dormDistributionLastStep(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) {
		ActionMessages messages = new ActionMessages();
		try {
			dormitoryService.saveLastDistribution();
			// ѧ���ְ�
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"dormDistribution.success"));
			saveErrors(request, messages);
		} catch (StudentAlreadyInDormException e) {
//			e.printStackTrace();
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"dormDistribution.studentalreadyindorm"));
			saveErrors(request, messages);
			return dormDistributionFirstStep(mapping, form, request, response);
		} catch (DormitoryNotEnoughException e) {
//			e.printStackTrace();
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"dormDistribution.dormitorynotenough"));
			saveErrors(request, messages);
			return dormDistributionFirstStep(mapping, form, request, response);
		} catch (Exception e) {
//			e.printStackTrace();
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"dormDistribution.error"));
			saveErrors(request, messages);
			return dormDistributionFirstStep(mapping, form, request, response);
		}
		List collegeList = collegeService.getAllCollegeByfdxy();
		request.setAttribute("collegeList", collegeList);
		List daleiList = studentService.getDiction("14");
		request.setAttribute("daleiList", daleiList);
		
		String schoolId = "0001";
		List daleiResultStatistic = classService.daleiResultStatistic(schoolId);
		request.setAttribute("daleiResultStatistic", daleiResultStatistic);
		//
		List collegeclassList = classService.getCollegeClassList(schoolId);
		String collegeId = "";
		String collegename = "";
		for (int i = 0; i < collegeclassList.size(); i++) {
			HashMap temp = (HashMap) collegeclassList.get(i);
			if (collegename.equals(temp.get("collegeName").toString())
					|| i == 0) {
				collegeId = temp.get("collegeId").toString();
				collegename = temp.get("collegeName").toString();
			}
			if (i == collegeclassList.size() - 1) {
				HashMap addmap = new HashMap();
				addmap.put("collegeId", collegeId);
				addmap.put("collegeName", collegename);
				addmap.put("classNo", "smallCount");
				collegeclassList.add(i + 1, addmap);
				break;
			}
			if (!collegename.equals(temp.get("collegeName").toString())
					&& i > 0) {
				HashMap addmap = new HashMap();
				addmap.put("collegeId", collegeId);
				addmap.put("collegeName", collegename);
				addmap.put("classNo", "smallCount");
				collegeclassList.add(i, addmap);
				collegename = temp.get("collegeName").toString();
			}
		}
		// �ܼ�
		HashMap addmap = new HashMap();
		addmap.put("collegeId", "allCount");
		addmap.put("collegeName", "allCount");
		addmap.put("classNo", "--");
		collegeclassList.add(collegeclassList.size(), addmap);
		request.setAttribute("collegeclassList", collegeclassList);
		List zhuanyeResultStatistic = classService.zhuanyeResultStatistic();
		request.setAttribute("zhuanyeResultStatistic", zhuanyeResultStatistic);
		return mapping.findForward("dormDistrTS");
	}

	public ActionForward dormDstrbutionResetPage(ActionMapping mapping,			
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) {		
		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//����ѧԺ
			//-------------------------------------------------
			String schoolId = "0002";
			Integer studentDistributionResult = studentService
			.getStudentDistributionResult();
			request.setAttribute("studentDistributionResult",
					studentDistributionResult);
		//	Integer dormDistributionResult = studentService
		//			.getDormDistributionResult();
		//	request.setAttribute("dormDistributionResult", dormDistributionResult);
			return mapping.findForward("dormDstrbutionResetPage");
		}else{
			//-------------------------------------------------����ѧԺ
			String schoolId = "0001";
			Integer studentDistributionResult = studentService
			.getStudentDistributionResult(schoolId);
			request.setAttribute("studentDistributionResult",
					studentDistributionResult);
		//	Integer dormDistributionResult = studentService
		//			.getDormDistributionResult();
		//	request.setAttribute("dormDistributionResult", dormDistributionResult);
			return mapping.findForward("dormDstrbutionResetPage");
		}
		

	}
	public ActionForward dormDstrbutionResetPage4yg(ActionMapping mapping,			
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) {
		HttpSession session = request.getSession();
		Account account = (Account) session.getAttribute("accountPerson");
		String accCode = account.getPerson().getPersonCode();
		Integer studentDistributionResult = studentService
				.getStudentDistributionResult4yg(accCode);
		request.setAttribute("studentDistributionResult",
				studentDistributionResult);
//		Integer dormDistributionResult = studentService
//				.getDormDistributionResult();
//		request.setAttribute("dormDistributionResult", dormDistributionResult);
		return mapping.findForward("dormDstrbutionResetPage4yg");
	}
	public ActionForward dormDstrbutionReset(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) {
		// Extract attributes and parameters we will need
		ActionMessages messages = new ActionMessages();
		
		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//����ѧԺ
			//-------------------------------------------------
			String schoolId = "0002";
			try {
				studentService.deleteStudentDormDistribution(schoolId);
				// ѧ���ְ�
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"dormDistribution.resetsuccess"));
				saveErrors(request, messages);
			} catch (Exception e) {
				e.printStackTrace();
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"dormDistribution.resetnotsuccess"));
				saveErrors(request, messages);
			}
			Integer studentDistributionResult = studentService
					.getStudentDistributionResult(schoolId);
			request.setAttribute("studentDistributionResult",
					studentDistributionResult);
			Integer dormDistributionResult = studentService
					.getDormDistributionResult(schoolId);
			request.setAttribute("dormDistributionResult", dormDistributionResult);
			return mapping.findForward("dormDstrbutionResetPage");
		}else{
			//-------------------------------------------------����ѧԺ
			String schoolId = "0001";		
			try {
				studentService.deleteStudentDormDistribution(schoolId);
				// ѧ���ְ�
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"dormDistribution.resetsuccess"));
				saveErrors(request, messages);
			} catch (Exception e) {
				e.printStackTrace();
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"dormDistribution.resetnotsuccess"));
				saveErrors(request, messages);
			}
			Integer studentDistributionResult = studentService
					.getStudentDistributionResult(schoolId);
			request.setAttribute("studentDistributionResult",
					studentDistributionResult);
			Integer dormDistributionResult = studentService
					.getDormDistributionResult(schoolId);
			request.setAttribute("dormDistributionResult", dormDistributionResult);
			return mapping.findForward("dormDstrbutionResetPage");
		}		
		

	}
	public ActionForward dormDstrbutionReset4yg(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) {
		// Extract attributes and parameters we will need
		ActionMessages messages = new ActionMessages();
		String operator = "";
		if (request.getSession().getAttribute("accountPerson") != null) {
			operator = ((Account) request.getSession().getAttribute(
					"accountPerson")).getPerson().getPersonCode();
		}
		try {
			studentService.deleteStudentDormDistribution4gy(operator);
			// ѧ���ְ�
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"dormDistribution.resetsuccess"));
			saveErrors(request, messages);
		} catch (Exception e) {
			e.printStackTrace();
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"dormDistribution.resetnotsuccess"));
			saveErrors(request, messages);
		}
		Integer studentDistributionResult = studentService
				.getStudentDistributionResult4yg(operator);
		request.setAttribute("studentDistributionResult",
				studentDistributionResult);
		Integer dormDistributionResult = studentService
				.getDormDistributionResult();
		request.setAttribute("dormDistributionResult", dormDistributionResult);
		return mapping.findForward("dormDstrbutionResetPage4yg");
	}
	public ActionForward init4Upload(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		return mapping.findForward("init4Upload");
	}
	
	public ActionForward importDormitoryFile(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		ActionMessages messages = new ActionMessages();

		if (form instanceof UpLoadForm) {// ���form��UpLoadsForm
			String encoding = request.getCharacterEncoding();

			if ((encoding != null) && (encoding.equalsIgnoreCase("utf-8"))) {
				response.setContentType("text/html; charset=gb2312");
			}
			UpLoadForm theForm = (UpLoadForm) form;
			FormFile file = theForm.getTheFile();// ȡ���ϴ����ļ�
			String contentType = file.getContentType();

			String size = (file.getFileSize() + " bytes");// �ļ���С
			String fileName = file.getFileName();// �ļ���
			InputStream is = file.getInputStream();
			try {

				is = file.getInputStream(); // ���ļ�����
				List stuList = reloadSpreadsheetModel(is);
				if (stuList == null) {
					messages.add(ActionMessages.GLOBAL_MESSAGE,
							new ActionMessage("student.empty"));
				} else if (stuList.size() > 0) {
					studentService.addConvertDorm(stuList);
					messages.add(ActionMessages.GLOBAL_MESSAGE,
							new ActionMessage("student.importsuccess"));
				}

			} catch (EnterenceNoNotExistException e) {
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"student.enterenceNonotexist"));
			} catch (FamilyAddressNotExistException e) {
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"student.familyAddressnotexist"));

			} catch (StuNameNotExistException e) {
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"student.stuNamenotexist"));
			} catch (TotalScoreNotExistException e) {
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"student.totalScorenotexist"));
			} catch (FileNotFoundException e) {
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"student.fileError"));
			} catch (IOException e) {
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"student.ioError"));
			} catch (Exception e) {
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"student.ioError"));
			} finally {				
				is.close();
			}

		}

		if (!messages.isEmpty()) {
			saveErrors(request, messages);
		}
		return mapping.findForward("init4Upload");
	}

	public List reloadSpreadsheetModel(InputStream is) throws IOException {
		// Use POI to read the selected Excel Spreadsheet
		List result = new ArrayList();
		HSSFWorkbook wb = new HSSFWorkbook(is);
		// Extract the name of the first worksheet and use this for the
		// tableName
		String tableName = wb.getSheetName(0);
		// Select the first worksheet
		HSSFSheet sheet = wb.getSheet(tableName);
		try {

			int rowCount = sheet.getPhysicalNumberOfRows();
			int colCount = sheet.getRow(0).getPhysicalNumberOfCells();
			if (colCount < 20) {
				return null;
			}
			for (int i = 1; i < rowCount; i++) {

				HSSFRow row = sheet.getRow(i);

				ArrayList list = new ArrayList();
				list.add(row.getCell((short) 0).getStringCellValue());//¼ȡ֪ͨ���
				list.add(row.getCell((short) 1).getStringCellValue());//����
				list.add(row.getCell((short) 2).getStringCellValue());//�Ա�
				
				
				
//				Date date = (row.getCell((short) 3).getDateCellValue());
//				Date date1 = sdf1.parse(row.getCell((short) 3).getDateCellValue().toLocaleString());   
//
//				String ss = ((row.getCell((short) 3).getDateCellValue())).toLocaleString();
//				String datebuf = sdfDate.format(date);
//				list.add(datebuf);//����	
				list.add(row.getCell((short) 3).getStringCellValue());//����
				list.add(row.getCell((short) 4).getStringCellValue());//����
				list.add(row.getCell((short) 5).getStringCellValue());//������ò
				list.add(row.getCell((short) 6).getStringCellValue());//¼ȡԺϵ
				list.add(row.getCell((short) 7).getStringCellValue());//¼ȡרҵ	
				list.add(row.getCell((short) 8).getStringCellValue());//����
				list.add(row.getCell((short) 9).getStringCellValue());//��Դ��				
		

				list.add(row.getCell((short) 10).getStringCellValue());	//�Ϻ�����		
				list.add(row.getCell((short) 11).getStringCellValue());//��ͥ��ַ
				list.add(row.getCell((short) 12).getStringCellValue());//�ʱ�
				list.add(row.getCell((short) 13).getStringCellValue());//�绰
				list.add(row.getCell((short) 14).getStringCellValue());//���֤


				list.add(row.getCell((short) 15).getStringCellValue());//�߿�����
				list.add(String.valueOf(row.getCell((short) 16).getNumericCellValue()));//�߿��ܷ�	
				list.add(row.getCell((short) 17).getStringCellValue());//ѧ������
			
				list.add(row.getCell((short) 18).getStringCellValue());//ѧ�����
				list.add(row.getCell((short) 19).getStringCellValue());//�������

				result.add(list);
			}

			return result;

		} catch (Exception e) {
//			System.out.println("A POI error has occured.");
			e.printStackTrace();
			return null;
		}
	}	
	
	public ActionForward init4studentNoAutoMake(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		
		if (request.getParameter("export") == null
				|| "".equals(request.getParameter("export"))) {		 
			studentService.getStudent_hlxy(request);
		}else{
			List studentmodels = studentService.getStudentExport_hlxy(request);

			// =================================================================
			// Create the Excel File
			String fileName = "studentInfo.xls";
			// Create the Sheet with the name of the Table
			HSSFWorkbook wb = new HSSFWorkbook();

			// ������ʾ�������Լ���ص���ʽ
			HSSFFont font = wb.createFont();
			font.setFontHeightInPoints((short) 8);
			font.setItalic(false);
			font.setStrikeout(false);

			// ���ñ�������Ԫ�����ʽ
			HSSFCellStyle cellHeadStyle = wb.createCellStyle();
			cellHeadStyle.setAlignment(HSSFCellStyle.ALIGN_CENTER);
			cellHeadStyle.setBorderBottom(HSSFCellStyle.BORDER_DOUBLE);
			cellHeadStyle.setBorderLeft((short) 1);
			cellHeadStyle.setBorderRight((short) 1);
			cellHeadStyle.setBorderTop(HSSFCellStyle.BORDER_DOUBLE);
			cellHeadStyle.setFillForegroundColor(HSSFColor.LIGHT_YELLOW.index);
			cellHeadStyle.setFillPattern(HSSFCellStyle.SOLID_FOREGROUND);

			// ���������е������Լ��Լ���صĶ��뷽ʽ
			HSSFCellStyle cellDataStyle = wb.createCellStyle();
			cellDataStyle.setAlignment(HSSFCellStyle.ALIGN_CENTER);
			cellDataStyle.setFont(font);

			HSSFSheet sheet1 = wb.createSheet("Sheet1");

			// Grab & populate the Column Names
			HSSFRow row = sheet1.createRow((short) 0);

			// Populate the first row of the spreadsheet with the column names
			List columnNames = new ArrayList();
			columnNames.add(0, "ѧ��");
			columnNames.add(1, "¼ȡ֪ͨ���");
			columnNames.add(2, "����");
			columnNames.add(3, "�Ա�");
			columnNames.add(4, "�߿�����");
			columnNames.add(5, "�߿��ܷ�");
			columnNames.add(6, "�༶");	
			columnNames.add(7, "����");
			columnNames.add(8, "����");
			columnNames.add(9, "������ò");
			columnNames.add(10, "¼ȡԺϵ");
			columnNames.add(11, "¼ȡרҵ");				
			columnNames.add(12, "����");	
			columnNames.add(13, "ʡ��");
			columnNames.add(14, "����");
			columnNames.add(15, "��ͥ��ַ");
			columnNames.add(16, "�ʱ�");
			columnNames.add(17, "�绰");		
			columnNames.add(18, "���֤");	
			columnNames.add(19, "ѧ������");
			columnNames.add(20, "ѧ�����");
			columnNames.add(21, "�������");
			columnNames.add(22, "��ѧ���");

			for (int i = 0; i < columnNames.size(); i++) {
				HSSFCell cname = row.createCell((short) i);
				cname.setCellStyle(cellHeadStyle);
				cname.setEncoding(HSSFCell.ENCODING_UTF_16);
				cname.setCellValue((String) columnNames.get(i));
			}

			// Populate the Row Data to the SpreadSheet
			int rowCount = studentmodels.size();
			// goal houses the number of cells in the target spreadsheet
			int goal = rowCount * columnNames.size();

			// actual population of target spreadsheet
			int currentCell = 0;

			for (int i = 0; i < rowCount; i++) {
				HashMap tableData = (HashMap) studentmodels
						.get(i);
				// create row in spreadsheet
				row = sheet1.createRow((short) (i + 1));

//				 populate the spreadsheet with the cell
				HSSFCell ctitle = row.createCell((short) 0);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("studentNo"));

				ctitle = row.createCell((short) 1);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("enrollNo"));

				ctitle = row.createCell((short) 2);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("stuName"));

				ctitle = row.createCell((short) 3);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("gender"));
				
				
				ctitle = row.createCell((short) 4);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("examType"));							
				
				ctitle = row.createCell((short) 5);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue(((Double)tableData.get("totalScore")).doubleValue());

				ctitle = row.createCell((short) 6);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("classNo"));	
				
				ctitle = row.createCell((short) 7);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("birthday"));

				ctitle = row.createCell((short) 8);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("nation"));

				ctitle = row.createCell((short) 9);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("polityBg"));
				
				
				ctitle = row.createCell((short) 10);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("department"));							
				
				ctitle = row.createCell((short) 11);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("majorin"));

				ctitle = row.createCell((short) 12);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("nationality"));	
				
				ctitle = row.createCell((short) 13);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("fromProvince"));
							
				ctitle = row.createCell((short) 14);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("district"));							
				
				ctitle = row.createCell((short) 15);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("familyAddress"));

				ctitle = row.createCell((short) 16);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("postCode"));	
				
				ctitle = row.createCell((short) 17);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("telephone"));

				ctitle = row.createCell((short) 18);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("idCard"));

				ctitle = row.createCell((short) 19);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("enrollType"));
				
				
				ctitle = row.createCell((short) 20);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("studentType"));							
				
				ctitle = row.createCell((short) 21);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("cultureMode"));
				
				ctitle = row.createCell((short) 22);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("enrollYear"));				
				currentCell++;

			}
			OutputStream os;
			try {
				response.setContentType("application/x-msdownload");
				response.setHeader("Content-Disposition", "attachment;"
						+ " filename="
						+ new String(fileName.getBytes(), "ISO-8859-1"));
				os = response.getOutputStream();
				wb.write(os);
				return null;
			} catch (UnsupportedEncodingException e) {
				e.printStackTrace();
				return null;
			} catch (IOException e) {
				e.printStackTrace();
				return null;
			}
			// =================================================================
		
			
		}
				 
		return mapping.findForward("init4studentNoAutoMake");
		
	}
	
	public ActionForward studentNoAutoMake(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		
		ActionMessages messages = new ActionMessages();
		String stuNoPrefix = request.getParameter("stuNoPrefix");//ǰ׺
		String startNo = request.getParameter("startNo");//��ʼ��

		if(stuNoPrefix!=null&&startNo!=null&&!"".equals(stuNoPrefix)&&!"".equals(startNo)){
			try {	
				
			studentService.AutoMakeByStartNo(request);
			
	//		studentService.getStudent_hlxy(request);
			
			messages.add(ActionMessages.GLOBAL_MESSAGE,
					new ActionMessage("student.makeStuNosuccess"));	
			
			}catch (MakeStuNoFailException e) {
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
				"student.makeStuNoFail"));
			}catch (Exception e) {
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"student.ioError"));
			}
		}
		if (!messages.isEmpty()) {
			saveErrors(request, messages);
		}
		return init4studentNoAutoMake(mapping,form,request,response);
	}

	public void setDirectoryService(IDirectoryService directoryService) {
		this.directoryService = directoryService;
	}
	
	public ActionForward init4tempecardUpload(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		return mapping.findForward("init4tempecardUpload");
	}
	
	public ActionForward importTempecardFile(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		ActionMessages messages = new ActionMessages();

		if (form instanceof UpLoadForm) {// ���form��UpLoadsForm
			String encoding = request.getCharacterEncoding();

			if ((encoding != null) && (encoding.equalsIgnoreCase("utf-8"))) {
				response.setContentType("text/html; charset=gb2312");
			}
			UpLoadForm theForm = (UpLoadForm) form;
			FormFile file = theForm.getTheFile();// ȡ���ϴ����ļ�
			String contentType = file.getContentType();

			String size = (file.getFileSize() + " bytes");// �ļ���С
			String fileName = file.getFileName();// �ļ���
			InputStream is = file.getInputStream();
			try {

				is = file.getInputStream(); // ���ļ�����
				List stuList = reloadTempecardSpreadsheetModel(is);
				if (stuList == null) {
					messages.add(ActionMessages.GLOBAL_MESSAGE,
							new ActionMessage("student.empty"));
				} else if (stuList.size() > 0) {
					studentService.addConvertTempecard(stuList);
					messages.add(ActionMessages.GLOBAL_MESSAGE,
							new ActionMessage("student.importsuccess"));
				}

			} catch (EnterenceNoNotExistException e) {
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"student.stuNonotexist"));
			} catch (FamilyAddressNotExistException e) {
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"student.familyAddressnotexist"));

			} catch (StuNameNotExistException e) {
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"student.tempecardNonotexist"));
			} catch (TotalScoreNotExistException e) {
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"student.totalScorenotexist"));
			} catch (FileNotFoundException e) {
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"student.fileError"));
			} catch (IOException e) {
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"student.ioError"));
			} catch (Exception e) {
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"student.ioError"));
			} finally {				
				is.close();
			}

		}

		if (!messages.isEmpty()) {
			saveErrors(request, messages);
		}
		return mapping.findForward("init4tempecardUpload");
	}
	
	public List reloadTempecardSpreadsheetModel(InputStream is) throws IOException {
		// Use POI to read the selected Excel Spreadsheet
		List result = new ArrayList();
		HSSFWorkbook wb = new HSSFWorkbook(is);
		// Extract the name of the first worksheet and use this for the
		// tableName
		String tableName = wb.getSheetName(0);
		// Select the first worksheet
		HSSFSheet sheet = wb.getSheet(tableName);
		try {

			int rowCount = sheet.getPhysicalNumberOfRows();
			int colCount = sheet.getRow(0).getPhysicalNumberOfCells();
			if (colCount < 2) {
				return null;
			}
			for (int i = 1; i < rowCount; i++) {

				HSSFRow row = sheet.getRow(i);

				ArrayList list = new ArrayList();
				list.add(row.getCell((short) 0).getStringCellValue());//ѧ��
				list.add(row.getCell((short) 1).getStringCellValue());//��ʱһ��ͨ����

				result.add(list);
			}

			return result;

		} catch (Exception e) {
//			System.out.println("A POI error has occured.");
			e.printStackTrace();
			return null;
		}
	}	
	
	public ActionForward load4StudentListColumnSelect(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		
		String operator = "";
		if (request.getSession().getAttribute("accountPerson") != null) {
			operator = ((Account) request.getSession().getAttribute(
					"accountPerson")).getPerson().getId();
		}
		List ntableheadleftList = classService.getNTableHeadList(operator,"studentList.jsp","0");
		request.setAttribute("ntableheadleftList", ntableheadleftList);
		List ntableheadrightList = classService.getNTableHeadList(operator,"studentList.jsp","1");
		request.setAttribute("ntableheadrightList", ntableheadrightList);
		StudentListColumns studentlc = classService.getUserSessionColumns(operator, "studentList.jsp");
		request.setAttribute("studentlc", studentlc);
		String page="studentList.jsp";
		request.setAttribute("page", page);
		return mapping.findForward("load4StudentListColumnSelect");
		
	}
	public ActionForward load4StudentfdyListColumnSelect(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		
		String operator = "";
		if (request.getSession().getAttribute("accountPerson") != null) {
			operator = ((Account) request.getSession().getAttribute(
					"accountPerson")).getPerson().getId();
		}
		List ntableheadleftList = classService.getNTableHeadList(operator,"sdfdyList.jsp","0");
		request.setAttribute("ntableheadleftList", ntableheadleftList);
		List ntableheadrightList = classService.getNTableHeadList(operator,"sdfdyList.jsp","1");
		request.setAttribute("ntableheadrightList", ntableheadrightList);
		StudentfdyListColmns studentlc = classService.getUserSessionfdyColumns(operator, "sdfdyList.jsp");
		request.setAttribute("studentlc", studentlc);
		String page="sdfdyList.jsp";
		request.setAttribute("page", page);
		return mapping.findForward("load4StudentListColumnSelect");
		
	}
	public ActionForward load4StudentfdyhlxyListColumnSelect(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		
		String operator = "";
		if (request.getSession().getAttribute("accountPerson") != null) {
			operator = ((Account) request.getSession().getAttribute(
					"accountPerson")).getPerson().getId();
		}
		List ntableheadleftList = classService.getNTableHeadList(operator,"sdhdyListhlxy","0");
		request.setAttribute("ntableheadleftList", ntableheadleftList);
		List ntableheadrightList = classService.getNTableHeadList(operator,"sdhdyListhlxy","1");
		request.setAttribute("ntableheadrightList", ntableheadrightList);
		StudentfdyListColmns studentlc = classService.getUserSessionfdyColumns(operator, "sdhdyListhlxy");
		request.setAttribute("studentlc", studentlc);
		String page="sdhdyListhlxy";
		request.setAttribute("page", page);
		return mapping.findForward("load4StudentListColumnSelect");
		
	}
	public ActionForward load4StudenthlxyListColumnSelect(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		
		String operator = "";
		if (request.getSession().getAttribute("accountPerson") != null) {
			operator = ((Account) request.getSession().getAttribute(
					"accountPerson")).getPerson().getId();
		}
		List ntableheadleftList = classService.getNTableHeadList(operator,"sdListhlxy","0");
		request.setAttribute("ntableheadleftList", ntableheadleftList);
		List ntableheadrightList = classService.getNTableHeadList(operator,"sdListhlxy","1");
		request.setAttribute("ntableheadrightList", ntableheadrightList);
		StudentfdyListColmns studentlc = classService.getUserSessionfdyColumns(operator, "sdListhlxy");
		request.setAttribute("studentlc", studentlc);
		String page="sdListhlxy";
		request.setAttribute("page", page);
		return mapping.findForward("load4StudentListColumnSelect");
		
	}
	public ActionForward saveColumnSelect(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		String operator = "";
		if (request.getSession().getAttribute("accountPerson") != null) {
			operator = ((Account) request.getSession().getAttribute(
					"accountPerson")).getPerson().getId();
		}
		String page=request.getParameter("page");
		DynaActionForm classesForm = (DynaActionForm) form;
		String tableheadleftarr[] = classesForm.getStrings("tableheadleft");
		String tableheadrightarr[] = classesForm.getStrings("tableheadright");
		String tableheadleft ="";
		String tableheadright ="";
		for(int i=0;i<tableheadleftarr.length;i++){
			tableheadleft+=tableheadleftarr[i]+",";
		}
		for(int i=0;i<tableheadrightarr.length;i++){
			tableheadright+=tableheadrightarr[i]+",";
		}
		classService.saveUserSessionColumns(operator, page, tableheadleft, tableheadright);
		
		
		return null;
//		return load4StudentListColumnSelect(mapping,form,request,response);
		
	}
}
