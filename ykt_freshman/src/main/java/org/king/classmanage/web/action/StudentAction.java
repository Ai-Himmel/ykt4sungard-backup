/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: StudentAction.java
 * Description: TODO
 * Modify History（或Change Log）:  
 * 操作类型（创建、修改等）   操作日期       操作者             操作内容简述
 * 创建  				 2006-5-9     何林青             
 * <p>
 *
 * @author      何林青
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
		
		
		// 性别
		List genderList = studentService.getDiction("1");
		request.setAttribute("genderList", genderList);
		// 民族
		List nationList = studentService.getDiction("2");
		request.setAttribute("nationList", nationList);
		// 生源地
		List provinceList = studentService.getDiction("10");
		request.setAttribute("provinceList", provinceList);
		// 政治面貌
		List polityList = studentService.getDiction("4");
		request.setAttribute("polityList", polityList);
		// 专业
		List majorinList = studentService.getDiction("11");
		request.setAttribute("majorinList", majorinList);
		// 国籍
		List nationalityList = studentService.getDiction("12");
		request.setAttribute("nationalityList", nationalityList);

		// 书院列表
		List collegeList = collegeService.getAllCollegeByfdxy();
		

//		// 区域列表
//		List locationList = studentService.getDiction("6");
//		request.setAttribute("locationList", locationList);
//		// 楼列表
//		List buildingList = studentService.getDiction("7");
//		request.setAttribute("buildingList", buildingList);
		
		classService.initForm(request);
		
//		院系列表
		studentService.findDepartments(request);
		
		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院
			// 性别
			genderList = studentService.getDiction("1");
			request.setAttribute("genderList", genderList);
			// 民族
			nationList = studentService.getnationList();
			request.setAttribute("nationList", nationList);
			// 生源地
			provinceList = studentService.getfromProvinceList();
			request.setAttribute("provinceList", provinceList);
			// 政治面貌
			polityList = studentService.getDiction("4");
			request.setAttribute("polityList", polityList);
			// 专业
			majorinList = studentService.getmajorList();
			request.setAttribute("majorinList", majorinList);
			// 国籍
			nationalityList = studentService.getcountryList();
			request.setAttribute("nationalityList", nationalityList);
			// 辅导员列表
			List assistantList = managerService.getClassAssitant_hlxy();
			request.setAttribute("assistantList", assistantList);
			// 班级列表
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
			//-------------------------------------------------复旦学院
			// 性别
			genderList = studentService.getDiction("1");
			request.setAttribute("genderList", genderList);
			// 民族
			nationList = studentService.getnationList();
			request.setAttribute("nationList", nationList);
			// 生源地
			provinceList = studentService.getfromProvinceList();
			request.setAttribute("provinceList", provinceList);
			// 政治面貌
			polityList = studentService.getDiction("4");
			request.setAttribute("polityList", polityList);
			// 专业
			majorinList = studentService.getmajorList();
			request.setAttribute("majorinList", majorinList);
			// 国籍
			nationalityList = studentService.getcountryList();
			request.setAttribute("nationalityList", nationalityList);
			// 辅导员列表
			List assistantList = managerService.getClassAssitant();
			request.setAttribute("assistantList", assistantList);
			request.setAttribute("collegeList", collegeList);
			// 班级列表
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
			//-------------------------------------------------本科生和高职生
			// 辅导员列表
			List assistantList = managerService.getClassAssitant();
			List assistantList2 = managerService.getClassAssitant_hlxy();
			assistantList.addAll(assistantList2);
			request.setAttribute("assistantList", assistantList);
			Collegemodel m = new Collegemodel();
			m.setCollegeId("0002");
			m.setCollegeName("护理学院");
			collegeList.add(m);
			request.setAttribute("collegeList", collegeList);
			List areaList = directoryService.getAreas();
			request.setAttribute("areaList", areaList);
			request.setAttribute("locationList",Collections.EMPTY_LIST);
			request.setAttribute("dormitoryList",Collections.EMPTY_LIST);
			// 班级列表
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
		// 性别
		List genderList = studentService.getDiction("1");
		request.setAttribute("genderList", genderList);
		// 民族
		List nationList = studentService.getnationList();
		request.setAttribute("nationList", nationList);
		// 生源地
		List provinceList = studentService.getfromProvinceList();
		request.setAttribute("provinceList", provinceList);
		// 政治面貌
		List polityList = studentService.getDiction("4");
		request.setAttribute("polityList", polityList);
		// 专业
		List majorinList = studentService.getmajorList();
		request.setAttribute("majorinList", majorinList);
		// 国籍
		List nationalityList = studentService.getcountryList();
		request.setAttribute("nationalityList", nationalityList);
//		// 区域列表
//		List locationList = studentService.getDiction("6");
//		request.setAttribute("locationList", locationList);
//		// 楼列表
//		List buildingList = studentService.getDiction("7");
//		request.setAttribute("buildingList", buildingList);
		
		dormitoryService.initForm_fdy(request);
		
		//院系列表
		studentService.findDepartments(request);
		
		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院
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
			//-------------------------------------------------复旦学院
			
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
//      <!-- 证件类型 -->
//      <property name="idType" type="string">
//      <!-- 培养层次 -->
//      <property name="cultureMode" type="string">
//      <!-- 学生性质 -->
//      <property name="studentChar" type="string">
//      <!-- 是否在籍 -->
//      <property name="checkornot" type="integer">
//      <!-- 是否在校 -->
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
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院
			//-------------------------------------------------
			String schoolId = "0002";
			if (request.getParameter("export") == null
					|| "".equals(request.getParameter("export"))) {
				studentmodels = studentService.getStudent(args,schoolId);
				Integer studentCount = studentService.getStudentCount(args,schoolId);
				
				request.setAttribute("listcount", studentCount);
				
				request.setAttribute("myclass", classId);
				request.setAttribute("mydormitory", dormitory);
				// 总行数
				request.setAttribute("studentCount", studentCount);
				request.setAttribute("studentmodels", studentmodels);

				// 性别
				List genderList = studentService.getDiction("1");
				request.setAttribute("genderList", genderList);
				// 民族
				List nationList = studentService.getnationList();
				request.setAttribute("nationList", nationList);
				// 生源地
				List provinceList = studentService.getfromProvinceList();
				request.setAttribute("provinceList", provinceList);
				// 政治面貌
				List polityList = studentService.getDiction("4");
				request.setAttribute("polityList", polityList);
				// 专业
				List majorinList = studentService.getmajorList();
				request.setAttribute("majorinList", majorinList);
				// 国籍
				List nationalityList = studentService.getcountryList();
				request.setAttribute("nationalityList", nationalityList);
				// 书院列表
				List collegeList = collegeService.getAllCollegeByfdxy();
				request.setAttribute("collegeList", collegeList);
				// 班级列表
				List classList = classService.getClassmodelbyschoolId("0002");
				request.setAttribute("classList", classList);
				// 辅导员列表
				List assistantList = managerService.getClassAssitant_hlxy();
				request.setAttribute("assistantList", assistantList);
//				// 区域列表
//				List locationList = studentService.getDiction("6");
//				request.setAttribute("locationList", locationList);
//				// 楼列表
//				List buildingList = studentService.getDiction("7");
//				request.setAttribute("buildingList", buildingList);
				classService.initForm(request);
				
				//院系列表
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

				// 设置显示的字体以及相关的样式
				HSSFFont font = wb.createFont();
				font.setFontHeightInPoints((short) 8);
				font.setItalic(false);
				font.setStrikeout(false);

				// 设置标题栏单元格的样式
				HSSFCellStyle cellHeadStyle = wb.createCellStyle();
				cellHeadStyle.setAlignment(HSSFCellStyle.ALIGN_CENTER);
				cellHeadStyle.setBorderBottom(HSSFCellStyle.BORDER_DOUBLE);
				cellHeadStyle.setBorderLeft((short) 1);
				cellHeadStyle.setBorderRight((short) 1);
				cellHeadStyle.setBorderTop(HSSFCellStyle.BORDER_DOUBLE);
				cellHeadStyle.setFillForegroundColor(HSSFColor.LIGHT_YELLOW.index);
				cellHeadStyle.setFillPattern(HSSFCellStyle.SOLID_FOREGROUND);

				// 设置数据行的字体以及以及相关的对齐方式
				HSSFCellStyle cellDataStyle = wb.createCellStyle();
				cellDataStyle.setAlignment(HSSFCellStyle.ALIGN_CENTER);
				cellDataStyle.setFont(font);

				HSSFSheet sheet1 = wb.createSheet("Sheet1");

				// Grab & populate the Column Names
				HSSFRow row = sheet1.createRow((short) 0);

				// Populate the first row of the spreadsheet with the column names
				List columnNames = new ArrayList();
//				columnNames.add(0, "书院");
				columnNames.add(0, "班级");
				columnNames.add(1, "辅导员");
				columnNames.add(2, "学号");
				columnNames.add(3, "录取通知书号");
				columnNames.add(4, "姓名");
				columnNames.add(5, "性别");	
//				columnNames.add(7, "录取院系");
//				columnNames.add(8, "录取专业");	
			
				columnNames.add(6, "证件类型");
				columnNames.add(7, "证件号码");				
				columnNames.add(8, "培养层次");
				columnNames.add(9, "学生性质");	
				columnNames.add(10, "是否在籍");
				columnNames.add(11, "是否在校");					
				
				columnNames.add(12, "民族");
				columnNames.add(13, "国籍");
//				columnNames.add(16, "生源地");
				columnNames.add(14, "政治面貌");
				columnNames.add(15, "校区");
				columnNames.add(16, "区域");
				columnNames.add(17, "楼号");
				columnNames.add(18, "宿舍号");
				columnNames.add(19, "生日");
				columnNames.add(20, "家庭电话");
				columnNames.add(21, "临时一卡通卡号");
//				columnNames.add(25, "浴卡卡号");	

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
					ctitle.setCellValue(tableData.getCheckornot()==null?"":tableData.getCheckornot().intValue()==1?"是":"否");

					ctitle = row.createCell((short) 11);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getSchoolornot()==null?"":tableData.getSchoolornot().intValue()==1?"是":"否");
					
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
			//-------------------------------------------------复旦学院
			String schoolId = "0001";
			if (request.getParameter("export") == null
					|| "".equals(request.getParameter("export"))) {
				studentmodels = studentService.getStudent(args,schoolId);
				Integer studentCount = studentService.getStudentCount(args,schoolId);
				
				request.setAttribute("listcount", studentCount);
				
				request.setAttribute("myclass", classId);
				request.setAttribute("mydormitory", dormitory);
				// 总行数
				request.setAttribute("studentCount", studentCount);
				request.setAttribute("studentmodels", studentmodels);

				// 性别
				List genderList = studentService.getDiction("1");
				request.setAttribute("genderList", genderList);
				// 民族
				List nationList = studentService.getnationList();
				request.setAttribute("nationList", nationList);
				// 生源地
				List provinceList = studentService.getfromProvinceList();
				request.setAttribute("provinceList", provinceList);
				// 政治面貌
				List polityList = studentService.getDiction("4");
				request.setAttribute("polityList", polityList);
				// 专业
				List majorinList = studentService.getmajorList();
				request.setAttribute("majorinList", majorinList);
				// 国籍
				List nationalityList = studentService.getcountryList();
				request.setAttribute("nationalityList", nationalityList);
				// 书院列表
				List collegeList = collegeService.getAllCollegeByfdxy();
				request.setAttribute("collegeList", collegeList);
				// 班级列表
				List classList = classService.getClassmodelbyschoolId("0001");
				request.setAttribute("classList", classList);
				// 辅导员列表
				List assistantList = managerService.getClassAssitant();
				request.setAttribute("assistantList", assistantList);
//				// 区域列表
//				List locationList = studentService.getDiction("6");
//				request.setAttribute("locationList", locationList);
//				// 楼列表
//				List buildingList = studentService.getDiction("7");
//				request.setAttribute("buildingList", buildingList);		
				classService.initForm(request);
				//院系列表
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

				// 设置显示的字体以及相关的样式
				HSSFFont font = wb.createFont();
				font.setFontHeightInPoints((short) 8);
				font.setItalic(false);
				font.setStrikeout(false);

				// 设置标题栏单元格的样式
				HSSFCellStyle cellHeadStyle = wb.createCellStyle();
				cellHeadStyle.setAlignment(HSSFCellStyle.ALIGN_CENTER);
				cellHeadStyle.setBorderBottom(HSSFCellStyle.BORDER_DOUBLE);
				cellHeadStyle.setBorderLeft((short) 1);
				cellHeadStyle.setBorderRight((short) 1);
				cellHeadStyle.setBorderTop(HSSFCellStyle.BORDER_DOUBLE);
				cellHeadStyle.setFillForegroundColor(HSSFColor.LIGHT_YELLOW.index);
				cellHeadStyle.setFillPattern(HSSFCellStyle.SOLID_FOREGROUND);

				// 设置数据行的字体以及以及相关的对齐方式
				HSSFCellStyle cellDataStyle = wb.createCellStyle();
				cellDataStyle.setAlignment(HSSFCellStyle.ALIGN_CENTER);
				cellDataStyle.setFont(font);

				HSSFSheet sheet1 = wb.createSheet("Sheet1");

				// Grab & populate the Column Names
				HSSFRow row = sheet1.createRow((short) 0);

				// Populate the first row of the spreadsheet with the column names
				List columnNames = new ArrayList();
				columnNames.add(0, "书院");
				columnNames.add(1, "班级");
				columnNames.add(2, "辅导员");
				columnNames.add(3, "学号");
				columnNames.add(4, "录取通知书号");
				columnNames.add(5, "姓名");
				columnNames.add(6, "性别");	
				columnNames.add(7, "录取院系");
				columnNames.add(8, "录取专业");			
				columnNames.add(9, "民族");
				columnNames.add(10, "国籍");
				columnNames.add(11, "生源地");
				
				columnNames.add(12, "证件类型");
				columnNames.add(13, "证件号码");				
				columnNames.add(14, "培养层次");
				columnNames.add(15, "学生性质");	
				columnNames.add(16, "是否在籍");
				columnNames.add(17, "是否在校");						
				
				columnNames.add(18, "政治面貌");
				columnNames.add(19, "校区");
				columnNames.add(20, "楼号");
				columnNames.add(21, "宿舍号");
				columnNames.add(22, "生日");
				columnNames.add(23, "家庭电话");
				columnNames.add(24, "临时一卡通卡号");
				columnNames.add(25, "浴卡卡号");	
				columnNames.add(26, "报到状态");

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
					ctitle.setCellValue(tableData.getCheckornot()==null?"":tableData.getCheckornot().intValue()==1?"是":"否");

					ctitle = row.createCell((short) 17);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getSchoolornot()==null?"":tableData.getSchoolornot().intValue()==1?"是":"否");

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
					ctitle.setCellValue(tableData.getExamNo()==null?"":tableData.getExamNo().equals("1")?"已报到":"未报到");

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

			//-------------------------------------------------本科生/高职生
			String schoolId = null;
			
			
			if (request.getParameter("export") == null
					|| "".equals(request.getParameter("export"))) {
				studentmodels = studentService.getStudent(args,schoolId);
				Integer studentCount = studentService.getStudentCount(args,schoolId);
				
				request.setAttribute("listcount", studentCount);
				
				request.setAttribute("myclass", classId);
				request.setAttribute("mydormitory", dormitory);
				// 总行数
				request.setAttribute("studentCount", studentCount);
				request.setAttribute("studentmodels", studentmodels);

				// 性别
				List genderList = studentService.getDiction("1");
				request.setAttribute("genderList", genderList);
				// 民族
				List nationList = studentService.getDiction("2");
				request.setAttribute("nationList", nationList);
				// 生源地
				List provinceList = studentService.getDiction("10");
				request.setAttribute("provinceList", provinceList);
				// 政治面貌
				List polityList = studentService.getDiction("4");
				request.setAttribute("polityList", polityList);
				// 专业
				List majorinList = studentService.getDiction("11");
				request.setAttribute("majorinList", majorinList);
				// 国籍
				List nationalityList = studentService.getDiction("12");
				request.setAttribute("nationalityList", nationalityList);
				// 书院列表
				List collegeList = collegeService.getAllCollegeByfdxy();
				Collegemodel m = new Collegemodel();
				m.setCollegeId("0002");
				m.setCollegeName("护理学院");
				collegeList.add(m);
				request.setAttribute("collegeList", collegeList);
				// 班级列表
				List classList = classService.getClassmodelbyschoolId(null);
				request.setAttribute("classList", classList);
				// 辅导员列表
				List assistantList = managerService.getClassAssitant();
				List assistantList2 = managerService.getClassAssitant_hlxy();
				assistantList.addAll(assistantList2);
				request.setAttribute("assistantList", assistantList);
//				// 区域列表
//				List locationList = studentService.getDiction("6");
//				request.setAttribute("locationList", locationList);
//				// 楼列表
//				List buildingList = studentService.getDiction("7");
//				request.setAttribute("buildingList", buildingList);		
				classService.initForm(request);
				//院系列表
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

				// 设置显示的字体以及相关的样式
				HSSFFont font = wb.createFont();
				font.setFontHeightInPoints((short) 8);
				font.setItalic(false);
				font.setStrikeout(false);

				// 设置标题栏单元格的样式
				HSSFCellStyle cellHeadStyle = wb.createCellStyle();
				cellHeadStyle.setAlignment(HSSFCellStyle.ALIGN_CENTER);
				cellHeadStyle.setBorderBottom(HSSFCellStyle.BORDER_DOUBLE);
				cellHeadStyle.setBorderLeft((short) 1);
				cellHeadStyle.setBorderRight((short) 1);
				cellHeadStyle.setBorderTop(HSSFCellStyle.BORDER_DOUBLE);
				cellHeadStyle.setFillForegroundColor(HSSFColor.LIGHT_YELLOW.index);
				cellHeadStyle.setFillPattern(HSSFCellStyle.SOLID_FOREGROUND);

				// 设置数据行的字体以及以及相关的对齐方式
				HSSFCellStyle cellDataStyle = wb.createCellStyle();
				cellDataStyle.setAlignment(HSSFCellStyle.ALIGN_CENTER);
				cellDataStyle.setFont(font);

				HSSFSheet sheet1 = wb.createSheet("Sheet1");

				// Grab & populate the Column Names
				HSSFRow row = sheet1.createRow((short) 0);

				// Populate the first row of the spreadsheet with the column names
				List columnNames = new ArrayList();
				columnNames.add(0, "书院");
				columnNames.add(1, "班级");
				columnNames.add(2, "辅导员");
				columnNames.add(3, "学号");
				columnNames.add(4, "录取通知书号");
				columnNames.add(5, "姓名");
				columnNames.add(6, "性别");	
				columnNames.add(7, "录取院系");
				columnNames.add(8, "录取专业");			
				columnNames.add(9, "民族");
				columnNames.add(10, "国籍");
				columnNames.add(11, "生源地");
				
				columnNames.add(12, "证件类型");
				columnNames.add(13, "培养层次");
				columnNames.add(14, "学生性质");	
				columnNames.add(15, "是否在籍");
				columnNames.add(16, "是否在校");						
				
				columnNames.add(17, "政治面貌");
				columnNames.add(18, "校区");
				columnNames.add(19, "楼号");
				columnNames.add(20, "宿舍号");
				columnNames.add(21, "生日");
				columnNames.add(22, "家庭电话");
				columnNames.add(23, "临时一卡通卡号");
				columnNames.add(24, "浴卡卡号");	

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
					ctitle.setCellValue(tableData.getCheckornot()==null?"":tableData.getCheckornot().intValue()==1?"是":"否");

					ctitle = row.createCell((short) 16);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getSchoolornot()==null?"":tableData.getSchoolornot().intValue()==1?"是":"否");

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
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院
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
							// 总行数
							request.setAttribute("studentCount", studentCount);
							request.setAttribute("studentmodels", studentmodels);

							// 性别
							List genderList = studentService.getDiction("1");
							request.setAttribute("genderList", genderList);
							// 民族
							List nationList = studentService.getnationList();
							request.setAttribute("nationList", nationList);
							// 生源地
							List provinceList = studentService.getfromProvinceList();
							request.setAttribute("provinceList", provinceList);
							// 政治面貌
							List polityList = studentService.getDiction("4");
							request.setAttribute("polityList", polityList);
							// 专业
							List majorinList = studentService.getmajorList();
							request.setAttribute("majorinList", majorinList);
							// 国籍
							List nationalityList = studentService.getcountryList();
							request.setAttribute("nationalityList", nationalityList);
//							// 区域列表
//							List locationList = studentService.getDiction("6");
//							request.setAttribute("locationList", locationList);
//							// 楼列表
//							List buildingList = studentService.getDiction("7");
//							request.setAttribute("buildingList", buildingList);
							dormitoryService.initForm_fdy(request);
							
							//院系列表
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

							// 设置显示的字体以及相关的样式
							HSSFFont font = wb.createFont();
							font.setFontHeightInPoints((short) 8);
							font.setItalic(false);
							font.setStrikeout(false);

							// 设置标题栏单元格的样式
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

							// 设置数据行的字体以及以及相关的对齐方式
							HSSFCellStyle cellDataStyle = wb.createCellStyle();
							cellDataStyle.setAlignment(HSSFCellStyle.ALIGN_CENTER);
							cellDataStyle.setFont(font);

							HSSFSheet sheet1 = wb.createSheet("Sheet1");

							// Grab & populate the Column Names
							HSSFRow row = sheet1.createRow((short) 0);
							 
							// Populate the first row of the spreadsheet with the
							// column names
							List columnNames = new ArrayList();
							columnNames.add(0, "班级");
							columnNames.add(1, "学号");
							columnNames.add(2, "录取通知书号");
							columnNames.add(3, "姓名");
							columnNames.add(4, "性别");						
					
							columnNames.add(5, "民族");
							columnNames.add(6, "国籍");
							
							columnNames.add(7, "证件类型");
							columnNames.add(8, "证件号码");
							columnNames.add(9, "培养层次");
							columnNames.add(10, "学生性质");	
							columnNames.add(11, "是否在籍");
							columnNames.add(12, "是否在校");		

							columnNames.add(13, "政治面貌");
							columnNames.add(14, "校区");
							columnNames.add(15, "区域");
							columnNames.add(16, "楼号");
							columnNames.add(17, "宿舍号");
							columnNames.add(18, "生日");
							columnNames.add(19, "家庭电话");
							columnNames.add(20, "临时一卡通考号");
//							columnNames.add(19, "浴卡卡号");

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
								ctitle.setCellValue(tableData.getCheckornot()==null?"":tableData.getCheckornot().intValue()==1?"是":"否");

								ctitle = row.createCell((short) 12);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getSchoolornot()==null?"":tableData.getSchoolornot().intValue()==1?"是":"否");

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
			//-------------------------------------------------复旦学院
			
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
							// 总行数
							request.setAttribute("studentCount", studentCount);
							request.setAttribute("studentmodels", studentmodels);

							// 性别
							List genderList = studentService.getDiction("1");
							request.setAttribute("genderList", genderList);
							// 民族
							List nationList = studentService.getnationList();
							request.setAttribute("nationList", nationList);
							// 生源地
							List provinceList = studentService.getfromProvinceList();
							request.setAttribute("provinceList", provinceList);
							// 政治面貌
							List polityList = studentService.getDiction("4");
							request.setAttribute("polityList", polityList);
							// 专业
							List majorinList = studentService.getmajorList();
							request.setAttribute("majorinList", majorinList);
							// 国籍
							List nationalityList = studentService.getcountryList();
							request.setAttribute("nationalityList", nationalityList);
//							// 区域列表
//							List locationList = studentService.getDiction("6");
//							request.setAttribute("locationList", locationList);
//							// 楼列表
//							List buildingList = studentService.getDiction("7");
//							request.setAttribute("buildingList", buildingList);
							dormitoryService.initForm_fdy(request);
							
							//院系列表
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

							// 设置显示的字体以及相关的样式
							HSSFFont font = wb.createFont();
							font.setFontHeightInPoints((short) 8);
							font.setItalic(false);
							font.setStrikeout(false);

							// 设置标题栏单元格的样式
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

							// 设置数据行的字体以及以及相关的对齐方式
							HSSFCellStyle cellDataStyle = wb.createCellStyle();
							cellDataStyle.setAlignment(HSSFCellStyle.ALIGN_CENTER);
							cellDataStyle.setFont(font);

							HSSFSheet sheet1 = wb.createSheet("Sheet1");

							// Grab & populate the Column Names
							HSSFRow row = sheet1.createRow((short) 0);
							 
							// Populate the first row of the spreadsheet with the
							// column names
							List columnNames = new ArrayList();
							columnNames.add(0, "学号");
							columnNames.add(1, "录取通知书号");
							columnNames.add(2, "姓名");
							columnNames.add(3, "性别");						
							columnNames.add(4, "录取院系");						
							columnNames.add(5, "录取专业");						
							columnNames.add(6, "民族");
							columnNames.add(7, "国籍");
							columnNames.add(8, "生源地");
							
							columnNames.add(9, "证件类型");
							columnNames.add(10, "证件号码");
							columnNames.add(11, "培养层次");
							columnNames.add(12, "学生性质");	
							columnNames.add(13, "是否在籍");
							columnNames.add(14, "是否在校");									
							
							columnNames.add(15, "政治面貌");
							columnNames.add(16, "校区");
							columnNames.add(17, "楼号");
							columnNames.add(18, "宿舍号");
							columnNames.add(19, "生日");
							columnNames.add(20, "家庭电话");
							columnNames.add(21, "临时一卡通考号");
							columnNames.add(22, "浴卡卡号");
							columnNames.add(23, "报到状态");

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
								ctitle.setCellValue(tableData.getCheckornot()==null?"":tableData.getCheckornot().intValue()==1?"是":"否");

								ctitle = row.createCell((short) 14);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getSchoolornot()==null?"":tableData.getSchoolornot().intValue()==1?"是":"否");								

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
								ctitle.setCellValue(tableData.getExamNo()==null?"":tableData.getExamNo().equals("1")?"已报到":"未报到");

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
		// // 国籍
		// request
		// .setAttribute("nationalityList", studentService
		// .getDiction("12"));
		// // 专业
		// request.setAttribute("majorinList", studentService.getDiction("11"));
		// // 性别
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

		// 国籍
		List nationalityList = studentService.getDiction("12");
		request.setAttribute("nationalityList", nationalityList);
		// 专业
		List majorinList = studentService.getDiction("11");
		request.setAttribute("majorinList", majorinList);
		// 性别
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
		// 书院列表
		List collegeList = collegeService.getAllCollegeByfdxy();
		request.setAttribute("collegeList", collegeList);
		// 班级列表
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
		// 留学生分班
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
	// // 学生分班
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
		// 学院列表
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
			// 学生分班
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
		// 统计分配结果
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
		// 总计
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
			// 学生分班
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
		// 总计
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
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院
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
			//-------------------------------------------------复旦学院
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
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院
			//-------------------------------------------------
			String schoolId = "0002";
			try {
				studentService.deleteStudentDormDistribution(schoolId);
				// 学生分班
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
			//-------------------------------------------------复旦学院
			String schoolId = "0001";		
			try {
				studentService.deleteStudentDormDistribution(schoolId);
				// 学生分班
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
			// 学生分班
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

		if (form instanceof UpLoadForm) {// 如果form是UpLoadsForm
			String encoding = request.getCharacterEncoding();

			if ((encoding != null) && (encoding.equalsIgnoreCase("utf-8"))) {
				response.setContentType("text/html; charset=gb2312");
			}
			UpLoadForm theForm = (UpLoadForm) form;
			FormFile file = theForm.getTheFile();// 取得上传的文件
			String contentType = file.getContentType();

			String size = (file.getFileSize() + " bytes");// 文件大小
			String fileName = file.getFileName();// 文件名
			InputStream is = file.getInputStream();
			try {

				is = file.getInputStream(); // 把文件读入
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
				list.add(row.getCell((short) 0).getStringCellValue());//录取通知书号
				list.add(row.getCell((short) 1).getStringCellValue());//姓名
				list.add(row.getCell((short) 2).getStringCellValue());//性别
				
				
				
//				Date date = (row.getCell((short) 3).getDateCellValue());
//				Date date1 = sdf1.parse(row.getCell((short) 3).getDateCellValue().toLocaleString());   
//
//				String ss = ((row.getCell((short) 3).getDateCellValue())).toLocaleString();
//				String datebuf = sdfDate.format(date);
//				list.add(datebuf);//生日	
				list.add(row.getCell((short) 3).getStringCellValue());//生日
				list.add(row.getCell((short) 4).getStringCellValue());//民族
				list.add(row.getCell((short) 5).getStringCellValue());//政治面貌
				list.add(row.getCell((short) 6).getStringCellValue());//录取院系
				list.add(row.getCell((short) 7).getStringCellValue());//录取专业	
				list.add(row.getCell((short) 8).getStringCellValue());//国籍
				list.add(row.getCell((short) 9).getStringCellValue());//生源地				
		

				list.add(row.getCell((short) 10).getStringCellValue());	//上海地区		
				list.add(row.getCell((short) 11).getStringCellValue());//家庭地址
				list.add(row.getCell((short) 12).getStringCellValue());//邮编
				list.add(row.getCell((short) 13).getStringCellValue());//电话
				list.add(row.getCell((short) 14).getStringCellValue());//身份证


				list.add(row.getCell((short) 15).getStringCellValue());//高考科类
				list.add(String.valueOf(row.getCell((short) 16).getNumericCellValue()));//高考总分	
				list.add(row.getCell((short) 17).getStringCellValue());//学生性质
			
				list.add(row.getCell((short) 18).getStringCellValue());//学生类别
				list.add(row.getCell((short) 19).getStringCellValue());//培养层次

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

			// 设置显示的字体以及相关的样式
			HSSFFont font = wb.createFont();
			font.setFontHeightInPoints((short) 8);
			font.setItalic(false);
			font.setStrikeout(false);

			// 设置标题栏单元格的样式
			HSSFCellStyle cellHeadStyle = wb.createCellStyle();
			cellHeadStyle.setAlignment(HSSFCellStyle.ALIGN_CENTER);
			cellHeadStyle.setBorderBottom(HSSFCellStyle.BORDER_DOUBLE);
			cellHeadStyle.setBorderLeft((short) 1);
			cellHeadStyle.setBorderRight((short) 1);
			cellHeadStyle.setBorderTop(HSSFCellStyle.BORDER_DOUBLE);
			cellHeadStyle.setFillForegroundColor(HSSFColor.LIGHT_YELLOW.index);
			cellHeadStyle.setFillPattern(HSSFCellStyle.SOLID_FOREGROUND);

			// 设置数据行的字体以及以及相关的对齐方式
			HSSFCellStyle cellDataStyle = wb.createCellStyle();
			cellDataStyle.setAlignment(HSSFCellStyle.ALIGN_CENTER);
			cellDataStyle.setFont(font);

			HSSFSheet sheet1 = wb.createSheet("Sheet1");

			// Grab & populate the Column Names
			HSSFRow row = sheet1.createRow((short) 0);

			// Populate the first row of the spreadsheet with the column names
			List columnNames = new ArrayList();
			columnNames.add(0, "学号");
			columnNames.add(1, "录取通知书号");
			columnNames.add(2, "姓名");
			columnNames.add(3, "性别");
			columnNames.add(4, "高考科类");
			columnNames.add(5, "高考总分");
			columnNames.add(6, "班级");	
			columnNames.add(7, "生日");
			columnNames.add(8, "民族");
			columnNames.add(9, "政治面貌");
			columnNames.add(10, "录取院系");
			columnNames.add(11, "录取专业");				
			columnNames.add(12, "国籍");	
			columnNames.add(13, "省市");
			columnNames.add(14, "地区");
			columnNames.add(15, "家庭地址");
			columnNames.add(16, "邮编");
			columnNames.add(17, "电话");		
			columnNames.add(18, "身份证");	
			columnNames.add(19, "学生性质");
			columnNames.add(20, "学生类别");
			columnNames.add(21, "培养层次");
			columnNames.add(22, "入学年份");

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
		String stuNoPrefix = request.getParameter("stuNoPrefix");//前缀
		String startNo = request.getParameter("startNo");//起始号

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

		if (form instanceof UpLoadForm) {// 如果form是UpLoadsForm
			String encoding = request.getCharacterEncoding();

			if ((encoding != null) && (encoding.equalsIgnoreCase("utf-8"))) {
				response.setContentType("text/html; charset=gb2312");
			}
			UpLoadForm theForm = (UpLoadForm) form;
			FormFile file = theForm.getTheFile();// 取得上传的文件
			String contentType = file.getContentType();

			String size = (file.getFileSize() + " bytes");// 文件大小
			String fileName = file.getFileName();// 文件名
			InputStream is = file.getInputStream();
			try {

				is = file.getInputStream(); // 把文件读入
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
				list.add(row.getCell((short) 0).getStringCellValue());//学号
				list.add(row.getCell((short) 1).getStringCellValue());//临时一卡通卡号

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
