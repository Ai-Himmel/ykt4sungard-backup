/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: ClassAction.java
 * Description: TODO
 * Modify History（或Change Log）:  
 * 操作类型（创建、修改等）   操作日期       操作者             操作内容简述
 * 创建  				 2006-4-29     何林青             
 * <p>
 *
 * @author      何林青
 * @version     1.0
 * @since       1.0
 */
package org.king.classmanage.web.action;

import java.io.IOException;
import java.io.OutputStream;
import java.io.UnsupportedEncodingException;
import java.sql.Date;
import java.sql.Time;
import java.sql.Timestamp;
import java.util.ArrayList;
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
import org.apache.struts.action.RedirectingActionForward;
import org.apache.struts.validator.DynaValidatorForm;
import org.king.classmanage.domain.ClassAlertHis;
import org.king.classmanage.domain.Classmanager;
import org.king.classmanage.domain.ClassmanagerId;
import org.king.classmanage.domain.Classmodel;
import org.king.classmanage.domain.Collegemodel;
import org.king.classmanage.domain.Managermodel;
import org.king.classmanage.domain.MenuTime;
import org.king.classmanage.domain.StudentListColumns;
import org.king.classmanage.domain.Studentmodel;
import org.king.classmanage.service.ClassService;
import org.king.classmanage.service.CollegeService;
import org.king.classmanage.service.ManagerService;
import org.king.classmanage.service.StudentService;
import org.king.classmanage.web.help.ClassAlertHistory;
import org.king.classmanage.web.help.ClassWithDormitory;
import org.king.classmanage.web.help.ClassWithManager;
import org.king.classmanage.web.help.StudentWithAllInfo;
import org.king.dormitorymanage.exception.DormitoryHasStuException;
import org.king.dormitorymanage.service.DormitoryService;
import org.king.framework.web.action.BaseAction;
import org.king.rcvmanage.domain.Stuarriveinfo;
import org.king.security.domain.Account;
import org.king.utils.DateUtil;
import org.king.utils.StringUtil;

public class ClassAction extends BaseAction {

	private CollegeService collegeService;

	private ManagerService managerService;

	private ClassService classService;

	private StudentService studentService;

	private DormitoryService dormitoryService;

	/**
	 * @param dormitoryService
	 *            The dormitoryService to set.
	 */
	public void setDormitoryService(DormitoryService dormitoryService) {
		this.dormitoryService = dormitoryService;
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

	public ActionForward load4List(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		

		String getrole = request.getParameter("getrole");//使用学院
		request.setAttribute("getrole", getrole);
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院
			// 班级列表
			List classList = classService.getClassmodelbyschoolId(new String("0002"));
			request.setAttribute("classList", classList);
			// 辅导员列表
			List assistantList = managerService.getClassAssitant_hlxy();
			request.setAttribute("assistantList", assistantList);
			// 导师列表
			List tutorList = managerService.getClassTutor_hlxy();
			request.setAttribute("tutorList", tutorList);	
			
			return mapping.findForward("list_hlxy");
			
		}else{
			// 学院列表
			List collegeList = collegeService.getAllCollegeByfdxy();
			request.setAttribute("collegeList", collegeList);
			// 班级列表
			List classList = classService.getClassmodelbyschoolId(new String("0001"));
			request.setAttribute("classList", classList);
			// 辅导员列表
			List assistantList = managerService.getClassAssitant();
			request.setAttribute("assistantList", assistantList);
			// 导师列表
			List tutorList = managerService.getClassTutor();
			request.setAttribute("tutorList", tutorList);
			
			return mapping.findForward("list");
		}

	}

	public ActionForward load4Search(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		DynaActionForm classForm = (DynaActionForm) form;
		Classmodel classmodel = (Classmodel) classForm.get("classmodel");
		
		
		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);
		
		if (request.getParameter("msg") != null&&"add".equals(request.getParameter("msg"))) {
			request.setAttribute("msg", "添加或修改成功");
		}
		if (request.getParameter("msg") != null&&"del".equals(request.getParameter("msg"))) {
			request.setAttribute("msg", "删除成功");
		}		
		
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院
			
			String classId = classmodel.getClassId();
			//String college = classForm.get("college").toString();
			String assistant = classForm.get("assistant").toString();
			String tutor = classForm.get("tutor1").toString();
			String page = request.getParameter("pager.offset");
			String[] args = { classId,  assistant, tutor, page };
			List classmodels = null;
			if (request.getParameter("export") == null
					|| "".equals(request.getParameter("export"))) {
				Integer classCount = classService.getClassCount_hlxy(args);
				
				request.setAttribute("listcount", classCount);
				
				classmodels = classService.findClass_hlxy(args);
				request.setAttribute("myclass", classId);
				request.setAttribute("classCount", classCount);
				request.setAttribute("classmodels", classmodels);

			} else {

				// =================================================================
				classmodels = classService.findClassExport_hlxy(args);
				// Create the Excel File
				String fileName = "classInfo.xls";
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
				columnNames.add(0, "班级");
//				columnNames.add(1, "所属书院");
				columnNames.add(1, "辅导员");
				columnNames.add(2, "班级导师");
				columnNames.add(3, "单位");
//				columnNames.add(4, "班级导师2");
//				columnNames.add(5, "单位");

				for (int i = 0; i < columnNames.size(); i++) {
					HSSFCell cname = row.createCell((short) i);
					cname.setCellStyle(cellHeadStyle);
					cname.setEncoding(HSSFCell.ENCODING_UTF_16);
					cname.setCellValue((String) columnNames.get(i));
				}

				// Populate the Row Data to the SpreadSheet
				int rowCount = classmodels.size();
				// goal houses the number of cells in the target spreadsheet
				int goal = rowCount * columnNames.size();

				// actual population of target spreadsheet
				int currentCell = 0;

				for (int i = 0; i < rowCount; i++) {
					ClassWithManager tableData = (ClassWithManager) classmodels
							.get(i);
					// create row in spreadsheet
					row = sheet1.createRow((short) (i + 1));

					// populate the spreadsheet with the cell
					HSSFCell ctitle = row.createCell((short) 0);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getClassNo());

//					ctitle = row.createCell((short) 1);
//					ctitle.setCellStyle(cellDataStyle);
//					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
//					ctitle.setCellValue(tableData.getCollegeName());

					ctitle = row.createCell((short) 1);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getAssistantName());

					ctitle = row.createCell((short) 2);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getTutor1Name());

					ctitle = row.createCell((short) 3);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getTutor1org());

//					ctitle = row.createCell((short) 4);
//					ctitle.setCellStyle(cellDataStyle);
//					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
//					ctitle.setCellValue(tableData.getTutor2Name());
//
//					ctitle = row.createCell((short) 5);
//					ctitle.setCellStyle(cellDataStyle);
//					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
//					ctitle.setCellValue(tableData.getTutor2org());

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
		
			
			return load4List(mapping,form,request,response);
			
		}else{
			String classId = classmodel.getClassId();
			String college = classForm.get("college").toString();
			String assistant = classForm.get("assistant").toString();
			String tutor = classForm.get("tutor1").toString();
			String page = request.getParameter("pager.offset");
			String[] args = { classId, college, assistant, tutor, page };
			List classmodels = null;
			if (request.getParameter("export") == null
					|| "".equals(request.getParameter("export"))) {
				Integer classCount = classService.getClassCount(args);
				
				request.setAttribute("listcount", classCount);
				
				classmodels = classService.findClass(args);
				request.setAttribute("myclass", classId);
				request.setAttribute("classCount", classCount);
				request.setAttribute("classmodels", classmodels);
				// 学院列表
				List collegeList = collegeService.getAllCollegeByfdxy();
				request.setAttribute("collegeList", collegeList);
				// 班级列表
				List classList = classService.getClassmodelbyschoolId(new String("0001"));
				request.setAttribute("classList", classList);
				// 辅导员列表
				List assistantList = managerService.getClassAssitant();
				request.setAttribute("assistantList", assistantList);
				// 导师列表
				List tutorList = managerService.getClassTutor();
				request.setAttribute("tutorList", tutorList);
				return mapping.findForward("list");
			} else {

				// =================================================================
				classmodels = classService.findClassExport(args);
				// Create the Excel File
				String fileName = "classInfo.xls";
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
				columnNames.add(0, "班级");
				columnNames.add(1, "所属书院");
				columnNames.add(2, "辅导员");
				columnNames.add(3, "班级导师1");
				columnNames.add(4, "单位");
				columnNames.add(5, "班级导师2");
				columnNames.add(6, "单位");

				for (int i = 0; i < columnNames.size(); i++) {
					HSSFCell cname = row.createCell((short) i);
					cname.setCellStyle(cellHeadStyle);
					cname.setEncoding(HSSFCell.ENCODING_UTF_16);
					cname.setCellValue((String) columnNames.get(i));
				}

				// Populate the Row Data to the SpreadSheet
				int rowCount = classmodels.size();
				// goal houses the number of cells in the target spreadsheet
				int goal = rowCount * columnNames.size();

				// actual population of target spreadsheet
				int currentCell = 0;

				for (int i = 0; i < rowCount; i++) {
					ClassWithManager tableData = (ClassWithManager) classmodels
							.get(i);
					// create row in spreadsheet
					row = sheet1.createRow((short) (i + 1));

					// populate the spreadsheet with the cell
					HSSFCell ctitle = row.createCell((short) 0);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getClassNo());

					ctitle = row.createCell((short) 1);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getCollegeName());

					ctitle = row.createCell((short) 2);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getAssistantName());

					ctitle = row.createCell((short) 3);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getTutor1Name());

					ctitle = row.createCell((short) 4);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getTutor1org());

					ctitle = row.createCell((short) 5);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getTutor2Name());

					ctitle = row.createCell((short) 6);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getTutor2org());

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

	public ActionForward load4Edit(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		
		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);
		
		DynaActionForm classForm = (DynaActionForm) form;
		String classId = request.getParameter("classId");
		
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院
			
			if (null != classId) {
				Classmodel classmodel = classService.getClassmodel(classId);
				if (null == classmodel) {
					load4List(mapping, form, request, response);
				}
				classForm.set("classmodel", classmodel);
//				classForm.set("college", classmodel.getYxCollege().getCollegeId());

				List assistantList = managerService.getClassAssitant_hlxy(classId);
				if (assistantList.size() > 0) {
					Managermodel managermodel = (Managermodel) assistantList.get(0);
					classForm.set("assistant", managermodel.getManagerId());
				}
				List tutorList = managerService.getClassTutor_hlxy(classId);
				if (1 == tutorList.size()) {
					Managermodel managermodel = (Managermodel) tutorList.get(0);
					classForm.set("tutor1", managermodel.getManagerId());
				} else if (tutorList.size() >= 2) {
					Managermodel managermodel1 = (Managermodel) tutorList.get(0);
					classForm.set("tutor1", managermodel1.getManagerId());
					Managermodel managermodel2 = (Managermodel) tutorList.get(1);
					classForm.set("tutor2", managermodel2.getManagerId());
				}
			}	
			
			// 辅导员列表
			List assistantList = managerService.getClassAssitant_hlxy(false);
			request.setAttribute("assistantList", assistantList);
			// 导师列表
			List tutorList = managerService.getClassTutor_hlxy(false);
			request.setAttribute("tutorList", tutorList);
			
			return mapping.findForward("edit_hlxy");
		}else{

			if (null != classId) {
				Classmodel classmodel = classService.getClassmodel(classId);
				if (null == classmodel) {
					load4List(mapping, form, request, response);
				}
				classForm.set("classmodel", classmodel);
				classForm.set("college", classmodel.getYxCollege().getCollegeId());

				List assistantList = managerService.getClassAssitant(classId);
				if (assistantList.size() > 0) {
					Managermodel managermodel = (Managermodel) assistantList.get(0);
					classForm.set("assistant", managermodel.getManagerId());
				}
				List tutorList = managerService.getClassTutor(classId);
				if (1 == tutorList.size()) {
					Managermodel managermodel = (Managermodel) tutorList.get(0);
					classForm.set("tutor1", managermodel.getManagerId());
				} else if (tutorList.size() >= 2) {
					Managermodel managermodel1 = (Managermodel) tutorList.get(0);
					classForm.set("tutor1", managermodel1.getManagerId());
					Managermodel managermodel2 = (Managermodel) tutorList.get(1);
					classForm.set("tutor2", managermodel2.getManagerId());
				}
			}
			// 学院列表
			List collegeList = collegeService.getAllCollegeByfdxy();
			request.setAttribute("collegeList", collegeList);

//			// 辅导员列表
//			List assistantList = managerService.getClassAssitant();
//			request.setAttribute("assistantList", assistantList);
//			// 导师列表
//			List tutorList = managerService.getClassTutor();
//			request.setAttribute("tutorList", tutorList);
			classService.initClassForm(request, classId);

			request.setAttribute("actionFlag", "Modify");
			return mapping.findForward("edit");
		}
		
		

	}

	public ActionForward load4Add(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		
		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院

			// 辅导员列表
			List assistantList = managerService.getClassAssitant_hlxy(false);
			request.setAttribute("assistantList", assistantList);
			// 导师列表
			List tutorList = managerService.getClassTutor_hlxy(false);
			request.setAttribute("tutorList", tutorList);
			// 标示添加
			request.setAttribute("actionFlag", "Add");			
			return mapping.findForward("edit_hlxy");
		}else{
			// 学院列表
			List collegeList = collegeService.getAllCollegeByfdxy();
			request.setAttribute("collegeList", collegeList);

			// 辅导员列表
			List assistantList = managerService.getClassAssitant(true);
			request.setAttribute("assistantList", assistantList);
			// 导师列表
			List tutorList = managerService.getClassTutor(true);
			request.setAttribute("tutorList", tutorList);
			// 标示添加
			request.setAttribute("actionFlag", "Add");
			return mapping.findForward("add");
		}

	}

	public ActionForward load4View(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		return null;
	}

	public ActionForward save(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		
		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);
		
		DynaActionForm classForm = (DynaActionForm) form;
		Classmodel classmodel = (Classmodel) classForm.get("classmodel");
		String msg = null;
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院
			
			
//			String collegeId = classForm.getString("college");
			String assistant = classForm.getString("assistant");
			String tutor1 = classForm.getString("tutor1");
//			String tutor2 = classForm.getString("tutor2");
			String tutor2 = "";
			// classmodel.setYxCollege(collegeService.getCollege(collegeId));

			// Extract attributes and parameters we will need
			ActionMessages messages = new ActionMessages();

			List list = new ArrayList();
			if ("".equals(classmodel.getClassId())) {
				// 添加
				if (!"".equals(assistant)) {
					Classmanager classmanager = new Classmanager();
					ClassmanagerId classmanagerid = new ClassmanagerId();
					classmanagerid.setClassId("0");
					classmanagerid.setManagerId(assistant);
					classmanager.setId(classmanagerid);
					list.add(classmanager);

//					if (managerService.getClassAssistantByManagerId(assistant)
//							.size() != 0) {
//						// 辅导员已分配班级
//						messages.add(ActionMessages.GLOBAL_MESSAGE,
//								new ActionMessage("class.thesameassistant"));
//						saveErrors(request, messages);
//						return load4Add(mapping, form, request, response);
//					}
				}
				if (!"".equals(tutor1)) {
					Classmanager classmanager = new Classmanager();
					ClassmanagerId classmanagerid = new ClassmanagerId();
					classmanagerid.setClassId("1");
					classmanagerid.setManagerId(tutor1);
					classmanager.setId(classmanagerid);
					list.add(classmanager);
				}
				if (!"".equals(tutor2)) {
					Classmanager classmanager = new Classmanager();
					ClassmanagerId classmanagerid = new ClassmanagerId();
					classmanagerid.setClassId("2");
					classmanagerid.setManagerId(tutor2);
					classmanager.setId(classmanagerid);
					list.add(classmanager);
					if ((!"".equals(tutor1)) && (tutor1.equals(tutor2))) {
						// 两导师员相同
						messages.add(ActionMessages.GLOBAL_MESSAGE,
								new ActionMessage("class.thesametutor"));
						saveErrors(request, messages);
						return load4Add(mapping, form, request, response);
					}
				}
				try {
					if (classService.getClassmodelbyNo(classmodel.getClassNo())
							.size() != 0) {
						// 编号重复
						messages.add(ActionMessages.GLOBAL_MESSAGE,
								new ActionMessage("class.thesameclassno",
										classmodel.getClassNo()));
						saveErrors(request, messages);
						return load4Add(mapping, form, request, response);
					} else {
						classService.saveClassandManager_hlxy(classmodel, list);
						msg = "add";
						messages.add(ActionMessages.GLOBAL_MESSAGE,
								new ActionMessage("class.added", classmodel
										.getClassName()));
						saveErrors(request, messages);
					}
				} catch (Exception e) {
					messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
							"class.notadded", classmodel.getClassName()));
					saveErrors(request, messages);
					return load4Add(mapping, form, request, response);
				}

			} else {
				// 修改
				List managerList = managerService.getClassAssitant(classmodel
						.getClassId());
				String managerid = "";
				if (managerList.size() > 0) {
					Managermodel managers = (Managermodel) managerList.get(0);
					managerid = managers.getManagerId();
				}

				if (!"".equals(assistant)) {
					Classmanager classmanager = new Classmanager();
					ClassmanagerId classmanagerid = new ClassmanagerId();
					classmanagerid.setClassId(classmodel.getClassId());
					classmanagerid.setManagerId(assistant);
					classmanager.setId(classmanagerid);
					list.add(classmanager);
//					if ("".equals(managerid) || !managerid.equals(assistant)) {
//						if (managerService.getClassAssistantByManagerId(assistant)
//								.size() > 0) {
//							// 辅导员已分配班级
//							messages.add(ActionMessages.GLOBAL_MESSAGE,
//									new ActionMessage("class.thesameassistant"));
//							saveErrors(request, messages);
//							return load4Add(mapping, form, request, response);
//						}
//					}
				}
				if (!"".equals(tutor1)) {
					Classmanager classmanager = new Classmanager();
					ClassmanagerId classmanagerid = new ClassmanagerId();
					classmanagerid.setClassId(classmodel.getClassId());
					classmanagerid.setManagerId(tutor1);
					classmanager.setId(classmanagerid);
					classmanager.setTutorType(null);
					list.add(classmanager);

				}
				if (!"".equals(tutor2)) {
					Classmanager classmanager = new Classmanager();
					ClassmanagerId classmanagerid = new ClassmanagerId();
					classmanagerid.setClassId(classmodel.getClassId());
					classmanagerid.setManagerId(tutor2);
					classmanager.setId(classmanagerid);
					classmanager.setTutorType(null);
					list.add(classmanager);
					if ((!"".equals(tutor1)) && (tutor1.equals(tutor2))) {
						// 两导师员相同
						messages.add(ActionMessages.GLOBAL_MESSAGE,
								new ActionMessage("class.thesametutor"));
						saveErrors(request, messages);
						return load4Edit(mapping, form, request, response);
					}
				}
				try {
					classService.updateClassandManager_hlxy(classmodel, list);
					msg = "add";
					messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
							"class.mofidied", classmodel.getClassNo()));
					saveErrors(request, messages);
				} catch (Exception e) {
					messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
							"class.notmofidied", classmodel.getClassNo()));
					saveErrors(request, messages);
					return load4Edit(mapping, form, request, response);
				}
			}
			// classForm.reset(mapping, request);
//			removeAttribute(mapping, request);
			//return mapping.findForward("classlistgoto_hlxy");
			//return mapping.findForward("list_hlxy");			
//			return load4Search(mapping,form,request,response);
			return new RedirectingActionForward("/classAction.do?method=load4Search&getrole=2" + "&msg="+ msg);			
			
		}else{
			//-----------------------------------------------------------------复旦学院
			String collegeId = classForm.getString("college");
			String assistant = classForm.getString("assistant");
			String tutor1 = classForm.getString("tutor1");
			String tutor2 = classForm.getString("tutor2");

			// classmodel.setYxCollege(collegeService.getCollege(collegeId));

			// Extract attributes and parameters we will need
			ActionMessages messages = new ActionMessages();

			List list = new ArrayList();
			if ("".equals(classmodel.getClassId())) {
				// 添加
				if (!"".equals(assistant)) {
					Classmanager classmanager = new Classmanager();
					ClassmanagerId classmanagerid = new ClassmanagerId();
					classmanagerid.setClassId("0");
					classmanagerid.setManagerId(assistant);
					classmanager.setId(classmanagerid);
					list.add(classmanager);

					if (managerService.getClassAssistantByManagerId(assistant)
							.size() != 0) {
						// 辅导员已分配班级
						messages.add(ActionMessages.GLOBAL_MESSAGE,
								new ActionMessage("class.thesameassistant"));
						saveErrors(request, messages);
						return load4Add(mapping, form, request, response);
					}
				}
				if (!"".equals(tutor1)) {
					Classmanager classmanager = new Classmanager();
					ClassmanagerId classmanagerid = new ClassmanagerId();
					classmanagerid.setClassId("1");
					classmanagerid.setManagerId(tutor1);
					classmanager.setId(classmanagerid);
					list.add(classmanager);
				}
				if (!"".equals(tutor2)) {
					Classmanager classmanager = new Classmanager();
					ClassmanagerId classmanagerid = new ClassmanagerId();
					classmanagerid.setClassId("2");
					classmanagerid.setManagerId(tutor2);
					classmanager.setId(classmanagerid);
					list.add(classmanager);
					if ((!"".equals(tutor1)) && (tutor1.equals(tutor2))) {
						// 两导师员相同
						messages.add(ActionMessages.GLOBAL_MESSAGE,
								new ActionMessage("class.thesametutor"));
						saveErrors(request, messages);
						return load4Add(mapping, form, request, response);
					}
				}
				try {
					if (classService.getClassmodelbyNo(classmodel.getClassNo())
							.size() != 0) {
						// 编号重复
						messages.add(ActionMessages.GLOBAL_MESSAGE,
								new ActionMessage("class.thesameclassno",
										classmodel.getClassNo()));
						saveErrors(request, messages);
						return load4Add(mapping, form, request, response);
					} else {
						classService.saveClassandManager(classmodel, list,
								collegeId);
						messages.add(ActionMessages.GLOBAL_MESSAGE,
								new ActionMessage("class.added", classmodel
										.getClassName()));
						msg = "add";
						saveErrors(request, messages);
					}
				} catch (Exception e) {
					messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
							"class.notadded", classmodel.getClassName()));
					saveErrors(request, messages);
					return load4Add(mapping, form, request, response);
				}

			} else {
				// 修改
				List managerList = managerService.getClassAssitant(classmodel
						.getClassId());
				String managerid = "";
				if (managerList.size() > 0) {
					Managermodel managers = (Managermodel) managerList.get(0);
					managerid = managers.getManagerId();
				}

				if (!"".equals(assistant)) {
					Classmanager classmanager = new Classmanager();
					ClassmanagerId classmanagerid = new ClassmanagerId();
					classmanagerid.setClassId(classmodel.getClassId());
					classmanagerid.setManagerId(assistant);
					classmanager.setId(classmanagerid);
					list.add(classmanager);
					if ("".equals(managerid) || !managerid.equals(assistant)) {
						if (managerService.getClassAssistantByManagerId(assistant)
								.size() > 0) {
							// 辅导员已分配班级
							messages.add(ActionMessages.GLOBAL_MESSAGE,
									new ActionMessage("class.thesameassistant"));
							saveErrors(request, messages);
							return load4Add(mapping, form, request, response);
						}
					}
				}
				if (!"".equals(tutor1)) {
					Classmanager classmanager = new Classmanager();
					ClassmanagerId classmanagerid = new ClassmanagerId();
					classmanagerid.setClassId(classmodel.getClassId());
					classmanagerid.setManagerId(tutor1);
					classmanager.setId(classmanagerid);
					classmanager.setTutorType(null);
					list.add(classmanager);

				}
				if (!"".equals(tutor2)) {
					Classmanager classmanager = new Classmanager();
					ClassmanagerId classmanagerid = new ClassmanagerId();
					classmanagerid.setClassId(classmodel.getClassId());
					classmanagerid.setManagerId(tutor2);
					classmanager.setId(classmanagerid);
					classmanager.setTutorType(null);
					list.add(classmanager);
					if ((!"".equals(tutor1)) && (tutor1.equals(tutor2))) {
						// 两导师员相同
						messages.add(ActionMessages.GLOBAL_MESSAGE,
								new ActionMessage("class.thesametutor"));
						saveErrors(request, messages);
						return load4Edit(mapping, form, request, response);
					}
				}
				try {
					classService.updateClassandManager(classmodel, list, collegeId);
					messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
							"class.mofidied", classmodel.getClassNo()));
					msg = "add";
					saveErrors(request, messages);
				} catch (Exception e) {
					messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
							"class.notmofidied", classmodel.getClassNo()));
					saveErrors(request, messages);
					return load4Edit(mapping, form, request, response);
				}
			}
			// classForm.reset(mapping, request);
//			removeAttribute(mapping, request);
			// return load4Search(mapping, form, request, response);
//			return mapping.findForward("classlistgoto");
			return new RedirectingActionForward("/classAction.do?method=load4Search" + "&msg="+ msg);			
			
		}


	}

	public ActionForward delete(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		
		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);
		
		String[] deleteX = request.getParameterValues("deleteX");
		// Extract attributes and parameters we will need
		ActionMessages messages = new ActionMessages();		
		String msg = null;
		try {
			Classmodel classmodel = null;
			if (deleteX != null) {
				for (int i = 0; i < deleteX.length; i++) {
					classmodel = classService.getClassmodel(deleteX[i]);
					if (studentService.getStudentbyClass(
							classmodel.getClassId()).size() > 0) {
						messages.add(ActionMessages.GLOBAL_MESSAGE,
								new ActionMessage("class.cannotbedelete",
										classmodel.getClassNo()));
						saveErrors(request, messages);
						return load4Search(mapping, form, request, response);
					} else {
						classService.deleteClassandManager(classService
								.getClassmodel(deleteX[i]));
						msg = "del";
					}
				}
			} else {
				classmodel = new Classmodel();
				DynaActionForm classForm = (DynaActionForm) form;
				classmodel = (Classmodel) classForm.get("classmodel");
				if (studentService.getStudentbyClass(classmodel.getClassId())
						.size() > 0) {
					messages.add(ActionMessages.GLOBAL_MESSAGE,
							new ActionMessage("class.cannotbedelete",
									classmodel.getClassNo()));
					saveErrors(request, messages);
					return load4Search(mapping, form, request, response);
				} else {
					classService.deleteClassandManager(classmodel);
				}
			}
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"class.deleted"));
			saveErrors(request, messages);
			if(getrole!=null&&"2".equals(getrole)){
				return new RedirectingActionForward("/classAction.do?method=load4Search&getrole=2" + "&msg="+ msg);

			}else{
				return load4Search(mapping, form, request, response);
			}

		} catch (Exception e) {
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"class.notdeleted"));
			saveErrors(request, messages);
			return load4Search(mapping, form, request, response);
		}

	}

	public ActionForward binding4List(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		// 书院列表
		List collegeList = collegeService.getAllCollegeByfdxy();
		request.setAttribute("collegeList", collegeList);
		// 所有班级列表
		List classList = classService.getClassmodelbyschoolId(new String("0001"));
		request.setAttribute("classList", classList);
		// 所有已绑定的宿舍列表
		List bindeddormList = dormitoryService.getBindedDorm(request);
		request.setAttribute("bindeddormList", bindeddormList);
//		// 楼区域列表
//		List locationList = studentService.getDiction("6");
//		request.setAttribute("locationList", locationList);
//		// 所有楼列表
//		List buildingList = studentService.getDiction("7");
//		// List buildingList = dormitoryService.getDormmitoryList();
//		request.setAttribute("buildingList", buildingList);
		
		classService.initForm(request);//初始化楼区域列表,所有楼列表
		
		// 所有没有分配的宿舍列表
		List roomList = dormitoryService.getDormNoClass(request);
		request.setAttribute("roomList", roomList);
		return mapping.findForward("bindinglist");
	}

	public ActionForward classList(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		return null;
	}

	public ActionForward bindingDormList(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) {
		return null;
	}

	public ActionForward DormList(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		return null;
	}

	public ActionForward saveBinding(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {

		String mydormitory = request.getParameter("dormitorymodel.dormitory");
		String myclass = request.getParameter("classes");
		request.setAttribute("mydormitory", mydormitory);
		request.setAttribute("myclass", myclass);
		String binddormitorys = request.getParameter("binddormitorys");
		String unbinddormitorys = request.getParameter("unbinddormitorys");
		String[] temp = StringUtil.split(binddormitorys, ",");
		String[] untemp = StringUtil.split(unbinddormitorys, ",");
		String operator = "";
		if (request.getSession().getAttribute("accountPerson") != null) {
			operator = ((Account) request.getSession().getAttribute(
					"accountPerson")).getPerson().getId();
		}
		// Extract attributes and parameters we will need
		ActionMessages messages = new ActionMessages();
		try {
			if (dormitoryService.updateDormitory(temp, untemp)) {
				dormitoryService.updateBatchDorm(operator);
			}
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"classBinding.success"));
			saveErrors(request, messages);
		} catch (DormitoryHasStuException e) {
			String dormerrmesg = e.getMessage();
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"classBinding.studenthasindorm", dormerrmesg));
			saveErrors(request, messages);
		} catch (Exception e) {
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"classBinding.error"));
			saveErrors(request, messages);
			return binding4List(mapping, form, request, response);
		}
		return binding4List(mapping, form, request, response);
	}

	public ActionForward alert4List(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {

		// 性别
		List genderList = studentService.getDiction("1");
		request.setAttribute("genderList", genderList);
		// 民族
		List nationList = studentService.getnationList();
		request.setAttribute("nationList", nationList);
		// 生源地
		List provinceList = studentService.getfromProvinceList();
		request.setAttribute("provinceList", provinceList);
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
		List classList = classService.getClassmodelbyschoolId(new String("0001"));
		request.setAttribute("classList", classList);
		return mapping.findForward("alertlist");
	}

	public ActionForward alert4Search(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		DynaActionForm studentForm = (DynaActionForm) form;
		Studentmodel studentmodel = (Studentmodel) studentForm
				.get("studentmodel");
		Classmodel classmodel = (Classmodel)studentForm.get("classmodel");
		String studentNo = studentmodel.getStudentNo();
		String stuName = studentmodel.getStuName();
		String gender = studentmodel.getGender();
		String nation = studentmodel.getNation();
		String majorin = studentmodel.getMajorin();
		String nationility = studentmodel.getNationality();
		String province = studentmodel.getFromProvince();
		String classId = classmodel.getClassId();
		String collegeId = request.getParameter("collegeId");
		String page = request.getParameter("pager.offset");
		String[] args = { studentNo, stuName, gender, nation, province,
				majorin, nationility,collegeId,classId, page };
		List studentmodels = null;
		if (request.getParameter("export") == null
				|| "".equals(request.getParameter("export"))) {
			Integer stuCount = studentService.findStudentCount(args);
			
			request.setAttribute("listcount", stuCount);			
			
			studentmodels = studentService.findStudent(args);
			request.setAttribute("stuCount", stuCount);

			// 性别
			List genderList = studentService.getDiction("1");
			request.setAttribute("genderList", genderList);
			// 民族
			List nationList = studentService.getnationList();
			request.setAttribute("nationList", nationList);
			// 生源地
			List provinceList = studentService.getfromProvinceList();
			request.setAttribute("provinceList", provinceList);
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
			List classList = classService.getClassmodelbyschoolId(new String("0001"));
			request.setAttribute("classList", classList);
			
			request.setAttribute("myclassId", classId);

			request.setAttribute("studentmodels", studentmodels);

			return mapping.findForward("alertlist");
		} else {
			// =================================================================
			studentmodels = studentService.findStudentExport(args);
			// Create the Excel File
			String fileName = "class_alter.xls";
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
			columnNames.add(1, "姓名");
			columnNames.add(2, "性别");
			columnNames.add(3, "民族");
			columnNames.add(4, "国籍");
			columnNames.add(5, "生源地");
			columnNames.add(6, "专业");
			columnNames.add(7, "所属书院");
			columnNames.add(8, "班级");
			columnNames.add(9, "辅导员");

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

				// populate the spreadsheet with the cell
				HSSFCell ctitle = row.createCell((short) 0);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue(tableData.getStudentNo());

				ctitle = row.createCell((short) 1);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue(tableData.getStuName());

				ctitle = row.createCell((short) 2);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue(tableData.getGender());

				ctitle = row.createCell((short) 3);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue(tableData.getNation());

				ctitle = row.createCell((short) 4);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue(tableData.getNationality());

				ctitle = row.createCell((short) 5);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue(tableData.getFromProvince());

				ctitle = row.createCell((short) 6);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue(tableData.getMajorin());

				ctitle = row.createCell((short) 7);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue(tableData.getCollege());

				ctitle = row.createCell((short) 8);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue(tableData.getClassId());

				ctitle = row.createCell((short) 9);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue(tableData.getAssistant());

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

	public ActionForward saveAlert(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		HttpSession session = request.getSession(false);
		DynaActionForm studentForm = (DynaActionForm) form;
		Classmodel myclassmodel = (Classmodel)studentForm.get("classmodel");
		String myclassId = myclassmodel.getClassId();
		String[] deleteX = request.getParameterValues("deleteX");
		String classId = request.getParameter("classes");
		// Extract attributes and parameters we will need
		ActionMessages messages = new ActionMessages();
		try {
			if (deleteX != null) {
				for (int i = 0; i < deleteX.length; i++) {
					// update classId state and record history
					Studentmodel studentmodel = studentService
							.getStudent(deleteX[i]);
					Classmodel classmodel = null;
					if (!"".equals(classId)) {
						classmodel = classService.getClassmodel(classId);
					}
					String classId_o = "";
					if (studentmodel.getYxClass() != null) {
						classId_o = studentmodel.getYxClass().getClassId();
					}
					Account account = null;
					String operater = "";
					if (session.getAttribute("accountPerson") != null) {
						account = (Account) session
								.getAttribute("accountPerson");
						operater = account.getPerson().getPersonName();
					} else {
						messages.add(ActionMessages.GLOBAL_MESSAGE,
								new ActionMessage("classAlert.loginFirst"));
						saveErrors(request, messages);
						request.setAttribute("myclass", classId);
						request.setAttribute("myclassId", myclassId);
						return alert4Search(mapping, form, request, response);
					}

					String alertTime = DateUtil.getNow();
					if (classmodel != null) {
						studentmodel.setYxClass(classmodel);
						ClassAlertHis classalerthis = new ClassAlertHis();
						classalerthis.setStudentId(studentmodel.getStudentId());
						classalerthis.setClassIdO(classId_o);
						classalerthis.setClassIdN(studentmodel.getYxClass()
								.getClassId());
						classalerthis.setOperatorId(operater);
						classalerthis.setOperatorTime(alertTime);
						studentService.updateStudentWithHis(studentmodel,
								classalerthis);
					}else{
						studentmodel.setYxClass(null);
						ClassAlertHis classalerthis = new ClassAlertHis();
						classalerthis.setStudentId(studentmodel.getStudentId());
						classalerthis.setClassIdO(classId_o);
						classalerthis.setClassIdN("");
						classalerthis.setOperatorId(operater);
						classalerthis.setOperatorTime(alertTime);
						studentService.updateStudentWithHis(studentmodel,
								classalerthis);

					}
				}
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"classAlert.success"));
				saveErrors(request, messages);
			}
		} catch (Exception e) {
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"classAlert.error"));
			saveErrors(request, messages);
			request.setAttribute("myclass", classId);
			request.setAttribute("myclassId", myclassId);
			return alert4Search(mapping, form, request, response);
		}
		request.setAttribute("myclass", classId);
		request.setAttribute("myclassId", myclassId);
		return alert4Search(mapping, form, request, response);
	}

	public ActionForward load4AlertList(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		
		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院
			//-------------------------------------------------
			request.setAttribute("classList", classService.getClassmodelbyschoolId(new String("0002")));
			return mapping.findForward("alerthislist_hlxy");
		}else{
			//-------------------------------------------------复旦学院
			request.setAttribute("classList", classService.getClassmodelbyschoolId(new String("0001")));
			return mapping.findForward("alerthislist");
		}		
		// 班级列表
		

		
	}

	public ActionForward load4AlertSearch(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) {
		
		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);
		
		DynaActionForm studentForm = (DynaActionForm) form;
		Studentmodel studentmodel = (Studentmodel) studentForm
				.get("studentmodel");
		String studentNo = studentmodel.getStudentNo();
		String stuName = studentmodel.getStuName();
		String classes = request.getParameter("classes");
		String operatorTime1 = request.getParameter("operatorTime1");
		String operatorTime2 = request.getParameter("operatorTime2");
		operatorTime1 = operatorTime1.replaceAll("-", "");
		operatorTime2 = operatorTime2.replaceAll("-", "");
		String page = request.getParameter("pager.offset");

		String order = request.getParameter("horder");
		String odr = "asc";
		if (order != null && order.length() > 0 && order.equals("d"))
			odr = "desc";
		String orderby = request.getParameter("orderby");

		// 起始页
		String offset = request.getParameter("pager.offset");
		if (offset == null) {
			offset = "0";
		}

		String[] args = { studentNo, stuName, classes, operatorTime1,
				operatorTime2, page, orderby, odr };
		List classAlertHis = null;
		
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院
			//-------------------------------------------------
			
			String schoolId = "0002";
			if (request.getParameter("export") == null
					|| "".equals(request.getParameter("export"))) {
				classAlertHis = classService.getAlertHistory(args,schoolId);

				List resultList = new ArrayList();
				if (classAlertHis != null && classAlertHis.size() != 0) {
					// 起始页设置
					if (offset.equals("0"))
						resultList = classAlertHis;
					else if ((Integer.parseInt(offset)) < classAlertHis.size()
							|| (Integer.parseInt(offset)) == classAlertHis.size())
						resultList = classAlertHis.subList((Integer
								.parseInt(offset)), classAlertHis.size());

				}
				// Integer alertHisCount = classService.getAlertHistoryCount(args);
				request.setAttribute("classAlertHis", resultList);
				request.setAttribute("hisCount", new Integer(classAlertHis.size()));
				request.setAttribute("classList", classService.getClassmodelbyschoolId(new String("0002")));
				request.setAttribute("order", order);
				return mapping.findForward("alerthislist_hlxy");
			} else {
				// =================================================================
				classAlertHis = classService.getAlertHistoryExport(args,schoolId);
				// Create the Excel File
				String fileName = "class_alter_his.xls";
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
				columnNames.add(1, "姓名");
				columnNames.add(2, "原班级");
				columnNames.add(3, "原辅导员");

				columnNames.add(4, "新班级");
				columnNames.add(5, "新辅导员");

				columnNames.add(6, "操作员");
				columnNames.add(7, "操作时间");

				for (int i = 0; i < columnNames.size(); i++) {
					HSSFCell cname = row.createCell((short) i);
					cname.setCellStyle(cellHeadStyle);
					cname.setEncoding(HSSFCell.ENCODING_UTF_16);
					cname.setCellValue((String) columnNames.get(i));
				}

				// Populate the Row Data to the SpreadSheet
				int rowCount = classAlertHis.size();
				// goal houses the number of cells in the target spreadsheet
				int goal = rowCount * columnNames.size();

				// actual population of target spreadsheet
				int currentCell = 0;

				for (int i = 0; i < rowCount; i++) {
					ClassAlertHistory tableData = (ClassAlertHistory) classAlertHis
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
					ctitle.setCellValue(tableData.getStuName());

					ctitle = row.createCell((short) 2);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getClassO());

					ctitle = row.createCell((short) 3);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getAssistantO());

					ctitle = row.createCell((short) 4);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getClassN());

					ctitle = row.createCell((short) 5);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getAssistantN());

					ctitle = row.createCell((short) 6);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getOperator());

					ctitle = row.createCell((short) 7);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getOperatorTime());

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
			
		}else{
			//-------------------------------------------------复旦学院
			String schoolId = "0001";
			if (request.getParameter("export") == null
					|| "".equals(request.getParameter("export"))) {
				classAlertHis = classService.getAlertHistory(args,schoolId);

				List resultList = new ArrayList();
				if (classAlertHis != null && classAlertHis.size() != 0) {
					// 起始页设置
					if (offset.equals("0"))
						resultList = classAlertHis;
					else if ((Integer.parseInt(offset)) < classAlertHis.size()
							|| (Integer.parseInt(offset)) == classAlertHis.size())
						resultList = classAlertHis.subList((Integer
								.parseInt(offset)), classAlertHis.size());

				}
				// Integer alertHisCount = classService.getAlertHistoryCount(args);
				request.setAttribute("classAlertHis", resultList);
				request.setAttribute("hisCount", new Integer(classAlertHis.size()));
				request.setAttribute("classList", classService.getClassmodelbyschoolId(new String("0001")));
				request.setAttribute("order", order);
				return mapping.findForward("alerthislist");
			} else {
				// =================================================================
				classAlertHis = classService.getAlertHistoryExport(args,schoolId);
				// Create the Excel File
				String fileName = "class_alter_his.xls";
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
				columnNames.add(1, "姓名");
				columnNames.add(2, "原班级");
				columnNames.add(3, "原辅导员");
				columnNames.add(4, "原书院");
				columnNames.add(5, "新班级");
				columnNames.add(6, "新辅导员");
				columnNames.add(7, "新书院");
				columnNames.add(8, "操作员");
				columnNames.add(9, "操作时间");

				for (int i = 0; i < columnNames.size(); i++) {
					HSSFCell cname = row.createCell((short) i);
					cname.setCellStyle(cellHeadStyle);
					cname.setEncoding(HSSFCell.ENCODING_UTF_16);
					cname.setCellValue((String) columnNames.get(i));
				}

				// Populate the Row Data to the SpreadSheet
				int rowCount = classAlertHis.size();
				// goal houses the number of cells in the target spreadsheet
				int goal = rowCount * columnNames.size();

				// actual population of target spreadsheet
				int currentCell = 0;

				for (int i = 0; i < rowCount; i++) {
					ClassAlertHistory tableData = (ClassAlertHistory) classAlertHis
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
					ctitle.setCellValue(tableData.getStuName());

					ctitle = row.createCell((short) 2);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getClassO());

					ctitle = row.createCell((short) 3);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getAssistantO());

					ctitle = row.createCell((short) 4);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getCollegeO());

					ctitle = row.createCell((short) 5);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getClassN());

					ctitle = row.createCell((short) 6);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getAssistantN());

					ctitle = row.createCell((short) 7);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getCollegeN());

					ctitle = row.createCell((short) 8);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getOperator());

					ctitle = row.createCell((short) 9);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getOperatorTime());

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

	public ActionForward load4AlertView(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		return null;
	}

	public ActionForward load4ClassList(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		
		
		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院
			//-------------------------------------------------
			
//			// 区域列表
//			List locationList = studentService.getDiction("6");
//			request.setAttribute("locationList", locationList);
//			// 楼列表
//			List buildingList = studentService.getDiction("7");
//			request.setAttribute("buildingList", buildingList);
			classService.initForm(request);
			// 班级列表
			List classList = classService.getClassmodelbyschoolId(new String("0002"));
			request.setAttribute("classList", classList);
			// 辅导员列表
			List assistantList = managerService.getClassAssitant_hlxy();
			request.setAttribute("assistantList", assistantList);
			return mapping.findForward("classsearchlist_hlxy");
			
		}else{
			//-------------------------------------------------复旦学院
			
//			// 区域列表
//			List locationList = studentService.getDiction("6");
//			request.setAttribute("locationList", locationList);
//			// 楼列表
//			List buildingList = studentService.getDiction("7");
//			request.setAttribute("buildingList", buildingList);
			classService.initForm(request);
			// 学院列表
			List collegeList = collegeService.getAllCollegeByfdxy();
			request.setAttribute("collegeList", collegeList);
			// 班级列表
			List classList = classService.getClassmodelbyschoolId(new String("0001"));
			request.setAttribute("classList", classList);
			// 辅导员列表
			List assistantList = managerService.getClassAssitant();
			request.setAttribute("assistantList", assistantList);
			return mapping.findForward("classsearchlist");
			
		}


	}

	public ActionForward load4fdyClassList(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) {
//		// 区域列表
//		List locationList = studentService.getDiction("6");
//		request.setAttribute("locationList", locationList);
//		// 楼列表
//		List buildingList = studentService.getDiction("7");
//		request.setAttribute("buildingList", buildingList);
		dormitoryService.initForm_fdy(request);
		
		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院
			//-------------------------------------------------
			return mapping.findForward("fdyclasssearchlist_hlxy");
		}else{
			//-------------------------------------------------复旦学院
			return mapping.findForward("fdyclasssearchlist");
		}
		
	}

	public ActionForward load4fdyClassSearch(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) {
		
		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院
			//-------------------------------------------------
			HttpSession session = request.getSession(false);
			// Extract attributes and parameters we will need
			DynaActionForm classForm = (DynaActionForm) form;
			
			Classmodel classmodel = (Classmodel) classForm.get("classmodel");

			String classId = classmodel.getClassId();
			
			String area = classForm.get("area").toString();
			String location = classForm.get("location").toString();
			String dormitory = classForm.get("dormitory").toString();
			String roomnumber = classForm.get("roomnumber").toString();
			String direction = classForm.get("direction").toString();			
			String page = request.getParameter("pager.offset");
			String[] args = { location, dormitory, roomnumber, page,area,direction,classId };
			ActionMessages messages = new ActionMessages();
			Account account = null;
			if (session.getAttribute("accountPerson") != null) {
				account = (Account) session.getAttribute("accountPerson");
				String managerNo = account.getPerson().getPersonCode();
				List managerList = managerService.getManagerByNo(managerNo);
				List classsearchmodels = null;
				if (managerList.size() > 0) {
					Managermodel Managermodel = (Managermodel) managerList.get(0);
					List classlist = managerService.findManagerclass_hlxy(Managermodel.getManagerId());
					if (classlist!=null&&classlist.size()>0) {
						if (request.getParameter("export") == null
								|| "".equals(request.getParameter("export"))) {
							Integer classCount = classService
									.getfdyClassSearchCount_hlxy(args, classlist);
							
							request.setAttribute("listcount", classCount);
							
							request.setAttribute("mydormitory", dormitory);
							// 总行数
							request.setAttribute("classCount", classCount);
							// 结果
							classsearchmodels = classService.findfdyClassSearch_hlxy(
									args, classlist);
							request.setAttribute("classsearchmodels",
									classsearchmodels);
//							// 区域列表
//							List locationList = studentService.getDiction("6");
//							request.setAttribute("locationList", locationList);
//							// 楼列表
//							List buildingList = studentService.getDiction("7");
//							request.setAttribute("buildingList", buildingList);
							dormitoryService.initForm_fdy(request);
							
						} else {
							// =================================================================
							classsearchmodels = classService
									.findfdyClassSearchExport_hlxy(args, classlist);
							// Create the Excel File
							String fileName = "class_dormitory_fdy_Info.xls";
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

//							columnNames.add(0, "书院");
							columnNames.add(0, "班级");
							columnNames.add(1, "辅导员");
							columnNames.add(2, "校区");
							columnNames.add(3, "区域");
							columnNames.add(4, "楼号");
							columnNames.add(5, "宿舍号");
							columnNames.add(6, "朝向");
							columnNames.add(7, "入住学生");
							columnNames.add(8, "床位数");
							columnNames.add(9, "宿舍电话");

							for (int i = 0; i < columnNames.size(); i++) {
								HSSFCell cname = row.createCell((short) i);
								cname.setCellStyle(cellHeadStyle);
								cname.setEncoding(HSSFCell.ENCODING_UTF_16);
								cname.setCellValue((String) columnNames.get(i));
							}

							// Populate the Row Data to the SpreadSheet
							int rowCount = classsearchmodels.size();
							// goal houses the number of cells in the target
							// spreadsheet
							int goal = rowCount * columnNames.size();

							// actual population of target spreadsheet
							int currentCell = 0;

							for (int i = 0; i < rowCount; i++) {
								ClassWithDormitory tableData = (ClassWithDormitory) classsearchmodels
										.get(i);
								// create row in spreadsheet
								row = sheet1.createRow((short) (i + 1));

								// populate the spreadsheet with the cell
								HSSFCell ctitle = row.createCell((short) 0);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getClassNo());


								ctitle = row.createCell((short) 1);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getAssistantName());
								
								ctitle = row.createCell((short) 2);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getArea());

								ctitle = row.createCell((short) 3);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getLocation());

								ctitle = row.createCell((short) 4);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getDormitory());

								ctitle = row.createCell((short) 5);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getRoomNumber());

								ctitle = row.createCell((short) 6);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getDirection());
								
								ctitle = row.createCell((short) 7);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getGender());

								ctitle = row.createCell((short) 8);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getAccomodation());

								ctitle = row.createCell((short) 9);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getTelphone());

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
					} else {
						messages.add(ActionMessages.GLOBAL_MESSAGE,
								new ActionMessage("classAlert.loginFirstornotass"));
						saveErrors(request, messages);
						return load4fdyClassList(mapping, form, request, response);
					}
				} else {
					messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
							"classAlert.loginFirstornotass"));
					saveErrors(request, messages);
					return load4fdyClassList(mapping, form, request, response);
				}
			} else {
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"classAlert.loginFirstornotass"));
				saveErrors(request, messages);
				return load4fdyClassList(mapping, form, request, response);
			}
			return mapping.findForward("fdyclasssearchlist_hlxy");
		}else{
			//-------------------------------------------------复旦学院
			HttpSession session = request.getSession(false);
			// Extract attributes and parameters we will need
			DynaActionForm classForm = (DynaActionForm) form;
			String location = classForm.get("location").toString();
			String dormitory = classForm.get("dormitory").toString();
			String roomnumber = classForm.get("roomnumber").toString();
			String direction = classForm.get("direction").toString();
			String page = request.getParameter("pager.offset");
			String[] args = { location, dormitory, roomnumber, page,direction };
			ActionMessages messages = new ActionMessages();
			Account account = null;
			if (session.getAttribute("accountPerson") != null) {
				account = (Account) session.getAttribute("accountPerson");
				String managerNo = account.getPerson().getPersonCode();
				List managerList = managerService.getManagerByNo(managerNo);
				List classsearchmodels = null;
				if (managerList.size() > 0) {
					Managermodel Managermodel = (Managermodel) managerList.get(0);
					String managerclass = managerService
							.findManagerclass(Managermodel.getManagerId());
					if (!"".equals(managerclass)) {
						if (request.getParameter("export") == null
								|| "".equals(request.getParameter("export"))) {
							Integer classCount = classService
									.getfdyClassSearchCount(args, managerclass);
							
							request.setAttribute("listcount", classCount);
							
							request.setAttribute("mydormitory", dormitory);
							// 总行数
							request.setAttribute("classCount", classCount);
							// 结果
							classsearchmodels = classService.findfdyClassSearch(
									args, managerclass);
							request.setAttribute("classsearchmodels",
									classsearchmodels);
//							// 区域列表
//							List locationList = studentService.getDiction("6");
//							request.setAttribute("locationList", locationList);
//							// 楼列表
//							List buildingList = studentService.getDiction("7");
//							request.setAttribute("buildingList", buildingList);
							dormitoryService.initForm_fdy(request);
							
						} else {
							// =================================================================
							classsearchmodels = classService
									.findfdyClassSearchExport(args, managerclass);
							// Create the Excel File
							String fileName = "class_dormitory_fdy_Info.xls";
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

							columnNames.add(0, "书院");
							columnNames.add(1, "班级");
							columnNames.add(2, "辅导员");
							columnNames.add(3, "校区");
							columnNames.add(4, "楼号");
							columnNames.add(5, "宿舍号");
							columnNames.add(6, "朝向");							
							columnNames.add(7, "入住学生");
							columnNames.add(8, "床位数");
							columnNames.add(9, "宿舍电话");

							for (int i = 0; i < columnNames.size(); i++) {
								HSSFCell cname = row.createCell((short) i);
								cname.setCellStyle(cellHeadStyle);
								cname.setEncoding(HSSFCell.ENCODING_UTF_16);
								cname.setCellValue((String) columnNames.get(i));
							}

							// Populate the Row Data to the SpreadSheet
							int rowCount = classsearchmodels.size();
							// goal houses the number of cells in the target
							// spreadsheet
							int goal = rowCount * columnNames.size();

							// actual population of target spreadsheet
							int currentCell = 0;

							for (int i = 0; i < rowCount; i++) {
								ClassWithDormitory tableData = (ClassWithDormitory) classsearchmodels
										.get(i);
								// create row in spreadsheet
								row = sheet1.createRow((short) (i + 1));

								// populate the spreadsheet with the cell
								HSSFCell ctitle = row.createCell((short) 0);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getCollegeName());

								ctitle = row.createCell((short) 1);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getClassNo());

								ctitle = row.createCell((short) 2);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getAssistantName());

								ctitle = row.createCell((short) 3);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getLocation());

								ctitle = row.createCell((short) 4);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getDormitory());

								ctitle = row.createCell((short) 5);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getRoomNumber());

								ctitle = row.createCell((short) 6);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getDirection());
								
								ctitle = row.createCell((short) 7);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getGender());

								ctitle = row.createCell((short) 8);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getAccomodation());

								ctitle = row.createCell((short) 9);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getTelphone());

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
					} else {
						messages.add(ActionMessages.GLOBAL_MESSAGE,
								new ActionMessage("classAlert.loginFirstornotass"));
						saveErrors(request, messages);
						return load4fdyClassList(mapping, form, request, response);
					}
				} else {
					messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
							"classAlert.loginFirstornotass"));
					saveErrors(request, messages);
					return load4fdyClassList(mapping, form, request, response);
				}
			} else {
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"classAlert.loginFirstornotass"));
				saveErrors(request, messages);
				return load4fdyClassList(mapping, form, request, response);
			}
			return mapping.findForward("fdyclasssearchlist");
		}
		

	}

	public ActionForward load4ClassSearch(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) {
		DynaActionForm classForm = (DynaActionForm) form;
		Classmodel classmodel = (Classmodel) classForm.get("classmodel");

		String classId = classmodel.getClassId();
		String college = classForm.get("college").toString();
		
		String area = classForm.get("area").toString();
		
		String location = classForm.get("location").toString();
		String assistant = classForm.get("assistant").toString();
		String dormitory = classForm.get("dormitory").toString();
		String roomnumber = classForm.get("roomnumber").toString();
		String direction = classForm.get("direction").toString();
		String page = request.getParameter("pager.offset");
		String[] args = { classId, college, assistant, location, dormitory,
				roomnumber, page,area,direction };
		List classsearchmodels = null;
		
		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院
			//-------------------------------------------------
			
			String schoolId="0002";			
			if (request.getParameter("export") == null
					|| "".equals(request.getParameter("export"))) {

				Integer classCount = classService.getClassSearchCount(args,schoolId);
				
				request.setAttribute("listcount", classCount);
				
				request.setAttribute("myclass", classId);
				request.setAttribute("mydormitory", dormitory);
				// 总行数
				request.setAttribute("classCount", classCount);
				// 结果
				classsearchmodels = classService.findClassSearch(args,schoolId);
				request.setAttribute("classsearchmodels", classsearchmodels);

				classService.initForm(request);
				// 学院列表
				List collegeList = collegeService.getAllCollegeByfdxy();
				request.setAttribute("collegeList", collegeList);
				// 班级列表
				List classList = classService.getClassmodelbyschoolId(new String("0002"));
				request.setAttribute("classList", classList);
				// 辅导员列表
				List assistantList = managerService.getClassAssitant_hlxy();
				request.setAttribute("assistantList", assistantList);
				return mapping.findForward("classsearchlist_hlxy");
			} else {
				// =================================================================
				classsearchmodels = classService.findClassSearchExport(args,schoolId);
				// Create the Excel File
				String fileName = "class_dormitoryInfo.xls";
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
				columnNames.add(2, "校区");
				columnNames.add(3, "区域");
				columnNames.add(4, "楼号");
				columnNames.add(5, "宿舍号");
				columnNames.add(6, "入住性别");	
				columnNames.add(7, "朝向");				
				columnNames.add(8, "床位数");
				columnNames.add(9, "宿舍电话");

				for (int i = 0; i < columnNames.size(); i++) {
					HSSFCell cname = row.createCell((short) i);
					cname.setCellStyle(cellHeadStyle);
					cname.setEncoding(HSSFCell.ENCODING_UTF_16);
					cname.setCellValue((String) columnNames.get(i));
				}

				// Populate the Row Data to the SpreadSheet
				int rowCount = classsearchmodels.size();
				// goal houses the number of cells in the target spreadsheet
				int goal = rowCount * columnNames.size();

				// actual population of target spreadsheet
				int currentCell = 0;

				for (int i = 0; i < rowCount; i++) {
					ClassWithDormitory tableData = (ClassWithDormitory) classsearchmodels
							.get(i);
					// create row in spreadsheet
					row = sheet1.createRow((short) (i + 1));

					// populate the spreadsheet with the cell
					HSSFCell ctitle = row.createCell((short) 0);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getClassNo());

					ctitle = row.createCell((short) 1);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getAssistantName());

					ctitle = row.createCell((short) 2);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getArea());
					
					ctitle = row.createCell((short) 3);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getLocation());

					ctitle = row.createCell((short) 4);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getDormitory());

					ctitle = row.createCell((short) 5);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getRoomNumber());
					
					ctitle = row.createCell((short) 6);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getGender());

					ctitle = row.createCell((short) 7);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getDirection());
					
					ctitle = row.createCell((short) 8);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getAccomodation());

					ctitle = row.createCell((short) 9);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getTelphone());

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
			
		}else{
			//-------------------------------------------------复旦学院
			String schoolId="0001";			
			if (request.getParameter("export") == null
					|| "".equals(request.getParameter("export"))) {

				Integer classCount = classService.getClassSearchCount(args,schoolId);
				
				request.setAttribute("listcount", classCount);
				
				request.setAttribute("myclass", classId);
				request.setAttribute("mydormitory", dormitory);
				// 总行数
				request.setAttribute("classCount", classCount);
				// 结果
				classsearchmodels = classService.findClassSearch(args,schoolId);
				request.setAttribute("classsearchmodels", classsearchmodels);

				classService.initForm(request);
				// 学院列表
				List collegeList = collegeService.getAllCollegeByfdxy();
				request.setAttribute("collegeList", collegeList);
				// 班级列表
				List classList = classService.getClassmodelbyschoolId(new String("0001"));
				request.setAttribute("classList", classList);
				// 辅导员列表
				List assistantList = managerService.getClassAssitant();
				request.setAttribute("assistantList", assistantList);
				return mapping.findForward("classsearchlist");
			} else {
				// =================================================================
				classsearchmodels = classService.findClassSearchExport(args,schoolId);
				// Create the Excel File
				String fileName = "class_dormitoryInfo.xls";
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
				columnNames.add(3, "校区");
				columnNames.add(4, "楼号");
				columnNames.add(5, "宿舍号");
				columnNames.add(6, "朝向");				
				columnNames.add(7, "入住学生");
				columnNames.add(8, "床位数");
				columnNames.add(9, "宿舍电话");

				for (int i = 0; i < columnNames.size(); i++) {
					HSSFCell cname = row.createCell((short) i);
					cname.setCellStyle(cellHeadStyle);
					cname.setEncoding(HSSFCell.ENCODING_UTF_16);
					cname.setCellValue((String) columnNames.get(i));
				}

				// Populate the Row Data to the SpreadSheet
				int rowCount = classsearchmodels.size();
				// goal houses the number of cells in the target spreadsheet
				int goal = rowCount * columnNames.size();

				// actual population of target spreadsheet
				int currentCell = 0;

				for (int i = 0; i < rowCount; i++) {
					ClassWithDormitory tableData = (ClassWithDormitory) classsearchmodels
							.get(i);
					// create row in spreadsheet
					row = sheet1.createRow((short) (i + 1));

					// populate the spreadsheet with the cell
					HSSFCell ctitle = row.createCell((short) 0);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getCollegeName());

					ctitle = row.createCell((short) 1);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getClassNo());

					ctitle = row.createCell((short) 2);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getAssistantName());

					ctitle = row.createCell((short) 3);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getLocation());

					ctitle = row.createCell((short) 4);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getDormitory());

					ctitle = row.createCell((short) 5);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getRoomNumber());

					ctitle = row.createCell((short) 6);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getDirection());
					
					ctitle = row.createCell((short) 7);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getGender());

					ctitle = row.createCell((short) 8);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getAccomodation());

					ctitle = row.createCell((short) 9);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getTelphone());

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

	public ActionForward load4ClassView(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		return null;
	}

	public ActionForward load4CSSList(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		// List statisticList = classService.classResultStatistic();
		// request.setAttribute("statisticList", statisticList);
		
		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院
			//-------------------------------------------------
			return mapping.findForward("classstatisticlist_hlxy");
		}else{
			//-------------------------------------------------复旦学院
			return mapping.findForward("classstatisticlist");
		}		

	}
	
	public ActionForward gztempclassStat(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) {
				
			String schoolId = "0002";
			List examTypeList = classService.examTypeList();
			request.setAttribute("examTypeList", examTypeList);
			List classStatististic = classService.tempexamTypeStatistic(schoolId);
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
			request.setAttribute("classStatististic", classStatististic);
			
			List majorList = classService.genderList();
			request.setAttribute("majorList", majorList);
			List majorStatistic = classService.tempgenderStatistic(schoolId);
			List gendercollegeclassList = classService.getCollegeClassList(schoolId);
			String gendercollegeId = "";
			String gendercollegename = "";
			for (int i = 0; i < gendercollegeclassList.size(); i++) {
				HashMap temp = (HashMap) gendercollegeclassList.get(i);
				if (gendercollegename.equals(temp.get("collegeName").toString())
						|| i == 0) {
					gendercollegeId = temp.get("collegeId").toString();
					gendercollegename = temp.get("collegeName").toString();
				}
				if (i == gendercollegeclassList.size() - 1) {
					HashMap genderaddmap = new HashMap();
					genderaddmap.put("collegeId", gendercollegeId);
					genderaddmap.put("collegeName", gendercollegename);
					genderaddmap.put("classNo", "smallCount");
					gendercollegeclassList.add(i + 1, genderaddmap);
					break;
				}
				if (!gendercollegename.equals(temp.get("collegeName").toString())
						&& i > 0) {
					HashMap genderaddmap = new HashMap();
					genderaddmap.put("collegeId", gendercollegeId);
					genderaddmap.put("collegeName", gendercollegename);
					genderaddmap.put("classNo", "smallCount");
					gendercollegeclassList.add(i, genderaddmap);
					gendercollegename = temp.get("collegeName").toString();
				}
			}
			// 总计
			HashMap genderaddmap = new HashMap();
			genderaddmap.put("collegeId", "allCount");
			genderaddmap.put("collegeName", "allCount");
			genderaddmap.put("classNo", "--");
			gendercollegeclassList.add(gendercollegeclassList.size(), genderaddmap);
			request.setAttribute("gendercollegeclassList", gendercollegeclassList);
			request.setAttribute("majorinStatistic", majorStatistic);
			
			return mapping.findForward("gztempclassstat");
		

	}

	public ActionForward classStatististic(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) {
		
		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院
			//-------------------------------------------------
			String schoolId = "0002";
			List examTypeList = classService.examTypeList();
			request.setAttribute("examTypeList", examTypeList);
			List classStatististic = classService.examTypeStatistic(schoolId);
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
			request.setAttribute("classStatististic", classStatististic);
			return mapping.findForward("classStatististic_hlxy");
		}else{
			//-------------------------------------------------复旦学院
			
			String schoolId = "0001";
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

			List classStatististic = classService.classResultStatistic(schoolId);
			List classStatististicWithAborad = classService.classResultStatisticWithAbroad(schoolId);
			request.setAttribute("collegeclassList", collegeclassList);
			request.setAttribute("classStatististic", classStatististic);
			request.setAttribute("classStatististicWithAborad", classStatististicWithAborad);
			return mapping.findForward("classStatististic");			
			
		}

	}

	public ActionForward classCheckInStatististic(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) {

		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院
			//-------------------------------------------------
			String schoolId = "0002";
			List examTypeList = classService.examTypeCheckInList();
			request.setAttribute("examTypeList", examTypeList);
			List classStatististic = classService.examTypeCheckedinStatistic(schoolId);
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
			request.setAttribute("classStatististic", classStatististic);
			return mapping.findForward("classStatististic_hlxy");			
		}else{
			//-------------------------------------------------复旦学院
			String schoolId = "0001";
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
			
			List classStatististic = classService.classCheckInResultStatistic(schoolId);
			List classStatististicWithAborad = classService.classCheckInResultStatisticWithAbroad(schoolId);
			request.setAttribute("collegeclassList", collegeclassList);
			request.setAttribute("classStatististic", classStatististic);
			request.setAttribute("classStatististicWithAborad", classStatististicWithAborad);
			return mapping.findForward("classStatististic");			
		}		

	}

	public ActionForward nationStatistic(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) {
		
		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院
			//-------------------------------------------------
			String schoolId="0002";
			List nationList = classService.nationList();
			request.setAttribute("nationList", nationList);
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
			List nationStatistic = classService.nationResultStatistic(schoolId);
			request.setAttribute("collegeclassList", collegeclassList);
			request.setAttribute("nationStatistic", nationStatistic);
			return mapping.findForward("nationStatistic_hlxy");
		}else{
			//-------------------------------------------------复旦学院
			String schoolId="0001";
			List nationList = classService.nationList();
			request.setAttribute("nationList", nationList);
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
			List nationStatistic = classService.nationResultStatistic(schoolId);
			request.setAttribute("collegeclassList", collegeclassList);
			request.setAttribute("nationStatistic", nationStatistic);
			return mapping.findForward("nationStatistic");
		}		

	}

	public ActionForward nationCheckInStatistic(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) {
		
		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院
			//-------------------------------------------------
			String schoolId = "0002";
			List nationList = classService.nationCheckInList();
			request.setAttribute("nationList", nationList);
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
			List nationStatistic = classService.nationCheckInResultStatistic(schoolId);
			request.setAttribute("collegeclassList", collegeclassList);
			request.setAttribute("nationStatistic", nationStatistic);
			return mapping.findForward("nationStatistic_hlxy");
		}else{
			//-------------------------------------------------复旦学院
			String schoolId = "0001";
			List nationList = classService.nationCheckInList();
			request.setAttribute("nationList", nationList);
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
			List nationStatistic = classService.nationCheckInResultStatistic(schoolId);
			request.setAttribute("collegeclassList", collegeclassList);
			request.setAttribute("nationStatistic", nationStatistic);
			return mapping.findForward("nationStatistic");
		}		

	}
		
	public ActionForward majorinStatistic(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) {

		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院
			//-------------------------------------------------性别统计
			String schoolId = "0002";
			List majorList = classService.genderList();
			request.setAttribute("majorList", majorList);
			List majorStatistic = classService.genderResultStatistic(schoolId);
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
			request.setAttribute("majorinStatistic", majorStatistic);
			return mapping.findForward("majorinStatistic_hlxy");			
		}else{
			//-------------------------------------------------复旦学院
			String schoolId = "0001";
			List majorList = classService.majorinList();
			request.setAttribute("majorList", majorList);
			List majorStatistic = classService.majorinResultStatistic(schoolId);
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
			request.setAttribute("majorinStatistic", majorStatistic);
			return mapping.findForward("majorinStatistic");			
		}

	}

	public ActionForward majorinCheckInStatistic(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) {

		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院
			//-------------------------------------------------性别统计
			String schoolId = "0002";
			List majorList = classService.genderCheckInList();
			request.setAttribute("majorList", majorList);
			List majorStatistic = classService.genderCheckInResultStatistic(schoolId);
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
			request.setAttribute("majorinStatistic", majorStatistic);
			return mapping.findForward("majorinStatistic_hlxy");			
		}else{
			//-------------------------------------------------复旦学院
			String schoolId = "0001";
			List majorList = classService.majorinCheckInList();
			request.setAttribute("majorList", majorList);
			List majorStatistic = classService.majorinCheckInResultStatistic(schoolId);
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
			request.setAttribute("majorinStatistic", majorStatistic);
			return mapping.findForward("majorinStatistic");			
		}

	}

	public ActionForward nativeplaceStatistic(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) {
		
		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院
			//-------------------------------------------------
			String schoolId = "0002";
			List provinceList = classService.provinceList();
			request.setAttribute("provinceList", provinceList);
			List nativeplaceStatistic = classService.nativeplaceResultStatistic(schoolId);
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
			request.setAttribute("nativeplaceStatistic", nativeplaceStatistic);
			return mapping.findForward("nativeplaceStatistic_hlxy");			
		}else{
			//-------------------------------------------------复旦学院
			String schoolId = "0001";
			List provinceList = classService.provinceList();
			request.setAttribute("provinceList", provinceList);
			List nativeplaceStatistic = classService.nativeplaceResultStatistic(schoolId);
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
			request.setAttribute("nativeplaceStatistic", nativeplaceStatistic);
			return mapping.findForward("nativeplaceStatistic");			
		}		

	}

	public ActionForward nativeplaceCheckInStatistic(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) {

		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院
			//-------------------------------------------------
			String schoolId = "0002";
			List provinceList = classService.provinceList();
			request.setAttribute("provinceList", provinceList);
			List nativeplaceStatistic = classService
					.nativeplaceCheckInResultStatistic(schoolId);
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
			request.setAttribute("nativeplaceStatistic", nativeplaceStatistic);
			return mapping.findForward("nativeplaceStatistic_hlxy");			
		}else{
			//-------------------------------------------------复旦学院
			String schoolId = "0001";
			List provinceList = classService.provinceList();
			request.setAttribute("provinceList", provinceList);
			List nativeplaceStatistic = classService
					.nativeplaceCheckInResultStatistic(schoolId);
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
			request.setAttribute("nativeplaceStatistic", nativeplaceStatistic);
			return mapping.findForward("nativeplaceStatistic");			
		}		

	}

	public ActionForward nationalityStatistic(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) {

		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院
			//-------------------------------------------------
			String schoolId = "0002";
			List nationalityList = classService.nationalityList();
			request.setAttribute("nationalityList", nationalityList);
			List nationalityStatistic = classService.nationalityResultStatistic(schoolId);
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
			request.setAttribute("nationalityStatistic", nationalityStatistic);
			return mapping.findForward("nationalityStatistic_hlxy");			
		}else{
			//-------------------------------------------------复旦学院
			String schoolId = "0001";
			List nationalityList = classService.nationalityList();
			request.setAttribute("nationalityList", nationalityList);
			List nationalityStatistic = classService.nationalityResultStatistic(schoolId);
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
			request.setAttribute("nationalityStatistic", nationalityStatistic);
			return mapping.findForward("nationalityStatistic");			
		}

	}

	public ActionForward nationalityCheckInStatistic(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) {

		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院
			//-------------------------------------------------
			String schoolId = "0002";
			List nationalityList = classService.nationalityCheckInList();
			request.setAttribute("nationalityList", nationalityList);
			List nationalityStatistic = classService
					.nationalityCheckInResultStatistic(schoolId);
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
			request.setAttribute("nationalityStatistic", nationalityStatistic);
			return mapping.findForward("nationalityStatistic_hlxy");
		}else{
			//-------------------------------------------------复旦学院
			String schoolId = "0001";
			List nationalityList = classService.nationalityCheckInList();
			request.setAttribute("nationalityList", nationalityList);
			List nationalityStatistic = classService
					.nationalityCheckInResultStatistic(schoolId);
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
			request.setAttribute("nationalityStatistic", nationalityStatistic);
			return mapping.findForward("nationalityStatistic");
		}

	}

	public ActionForward daleiStatistic(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		
		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院
			//-------------------------------------------------
			String schoolId = "0002";
			List collegeList = collegeService.getAllCollegeByfdxy();
			Collegemodel colmap = new Collegemodel();
			colmap.setCollegeId("daleiCount");
			colmap.setCollegeName("daleiCount");
			colmap.setCollegeNo("");
			collegeList.add(collegeList.size(),colmap);
			request.setAttribute("collegeList", collegeList);
			List daleiList = studentService.getDiction("14");
			request.setAttribute("daleiList", daleiList);
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
			request.setAttribute("zhuanyeResultStatistic", classService
					.zhuanyeResultStatistic());
			return mapping.findForward("daleiStatistic_hlxy");		
		}else{
			//-------------------------------------------------复旦学院
			String schoolId = "0001";
			List collegeList = collegeService.getAllCollegeByfdxy();
			Collegemodel colmap = new Collegemodel();
			colmap.setCollegeId("daleiCount");
			colmap.setCollegeName("daleiCount");
			colmap.setCollegeNo("");
			collegeList.add(collegeList.size(),colmap);
			request.setAttribute("collegeList", collegeList);
			List daleiList = studentService.getDiction("14");
			request.setAttribute("daleiList", daleiList);
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
			request.setAttribute("zhuanyeResultStatistic", classService
					.zhuanyeResultStatistic());
			return mapping.findForward("daleiStatistic");			
		}		

	}
	
	public ActionForward daleiCheckInStatistic(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {

		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院
			//-------------------------------------------------
			String schoolId = "0002";
			List collegeList = collegeService.getAllCollegeByfdxy();
			Collegemodel colmap = new Collegemodel();
			colmap.setCollegeId("daleiCount");
			colmap.setCollegeName("daleiCount");
			colmap.setCollegeNo("");
			collegeList.add(collegeList.size(),colmap);
			request.setAttribute("collegeList", collegeList);
			List daleiList = studentService.getDiction("14");
			request.setAttribute("daleiList", daleiList);
			List daleiResultStatistic = classService.daleiCheckInResultStatistic(schoolId);
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
			request.setAttribute("zhuanyeResultStatistic", classService
					.zhuanyeCheckInResultStatistic());
			return mapping.findForward("daleiStatistic_hlxy");			
		}else{
			//-------------------------------------------------复旦学院
			String schoolId = "0001";
			List collegeList = collegeService.getAllCollegeByfdxy();
			Collegemodel colmap = new Collegemodel();
			colmap.setCollegeId("daleiCount");
			colmap.setCollegeName("daleiCount");
			colmap.setCollegeNo("");
			collegeList.add(collegeList.size(),colmap);
			request.setAttribute("collegeList", collegeList);
			List daleiList = studentService.getDiction("14");
			request.setAttribute("daleiList", daleiList);
			List daleiResultStatistic = classService.daleiCheckInResultStatistic(schoolId);
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
			request.setAttribute("zhuanyeResultStatistic", classService
					.zhuanyeCheckInResultStatistic());
			return mapping.findForward("daleiStatistic");			
		}

	}
	
	//菜单开放时间设置
	public ActionForward menutimelist(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) {
		
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
		String sqlstring=" select new Map(a.id as id,b.name as menuName,a.beginDate as beginDate,a.beginTime as beginTime,a.endDate as endDate,a.endTime as endTime,a.updateTime as updateTime) from MenuTime a,Menu b where b.id=a.menuId and a.schoolId='0001' ";
		
		if(request.getParameter("hmenuName")!=null&&request.getParameter("hmenuName").length()!=0){
			 sqlstring=sqlstring+" and b.name like '%"+request.getParameter("hmenuName")+"%'";
			 request.setAttribute("menuName",request.getParameter("hmenuName"));
		}
		
		List menutimeList=classService.find(sqlstring);
		
		if(menutimeList!=null&&menutimeList.size()>0){
		    request.setAttribute("checkinlist",menutimeList);
		    request.setAttribute("listcount",new Integer(menutimeList.size()));
		}
		return mapping.findForward("menutimelist");	
	}
	
	public ActionForward updatemenutime(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		
		Account manager=(Account)session.getAttribute("accountPerson");	            
        String managerNo=manager.getPerson().getPersonCode();	//获取登录者的学工号
        String msg="";
		try {
			List menutimeList=classService.find(" select a from MenuTime a where a.id='"+request.getParameter("updateid")+"'");
	        
			if(menutimeList!=null&&menutimeList.size()>0){
				MenuTime menuTime=(MenuTime)menutimeList.get(0);
				String mtid=menuTime.getId();
				if(request.getParameter("beginDate"+mtid)!=null&&request.getParameter("beginDate"+mtid).length()>8)
				    menuTime.setBeginDate(new Date(Integer.parseInt(request.getParameter("beginDate"+mtid).substring(0,4))-1900,Integer.parseInt(request.getParameter("beginDate"+mtid).substring(5,7))-1,Integer.parseInt(request.getParameter("beginDate"+mtid).substring(8))));
				menuTime.setBeginTime(new Time(Integer.parseInt(request.getParameter("beginTime"+mtid).substring(0,2)),Integer.parseInt(request.getParameter("beginTime"+mtid).substring(3,5)),0));
				if(request.getParameter("endDate"+mtid)!=null&&request.getParameter("endDate"+mtid).length()>8)
				    menuTime.setEndDate(new Date(Integer.parseInt(request.getParameter("endDate"+mtid).substring(0,4))-1900,Integer.parseInt(request.getParameter("endDate"+mtid).substring(5,7))-1,Integer.parseInt(request.getParameter("endDate"+mtid).substring(8))));
				menuTime.setEndTime(new Time(Integer.parseInt(request.getParameter("endTime"+mtid).substring(0,2)),Integer.parseInt(request.getParameter("endTime"+mtid).substring(3,5)),0));
	       	    menuTime.setUpdator(managerNo);
				menuTime.setUpdateTime(new Timestamp(System.currentTimeMillis()));		     
						     
 		     // 数据库验证
		
			 if(classService==null)
				 System.out.println("service is null");
			 classService.updateMenuTime(menuTime);			 
			 msg="0";
			 request.setAttribute("msg",msg);
			 
			}
			return mapping.findForward("mtsuccess");
		} catch (Exception e) {
			e.printStackTrace();			
			return mapping.findForward("faile");
		}

	}

}
