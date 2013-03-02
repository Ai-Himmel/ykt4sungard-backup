/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: ManagerAction.java
 * Description: TODO
 * Modify History（或Change Log）:  
 * 操作类型（创建、修改等）   操作日期       操作者             操作内容简述
 * 创建  				 2006-4-28     何林青             
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
import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

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
import org.king.checkinmanage.domain.Stuarchivesinfo;
import org.king.classmanage.domain.Managermanagerrole;
import org.king.classmanage.domain.ManagermanagerroleId;
import org.king.classmanage.domain.Managermodel;
import org.king.classmanage.exception.ManagerInClassException;
import org.king.classmanage.exception.ManagerInCollegeException;
import org.king.classmanage.exception.ManagerInSchoolException;
import org.king.classmanage.service.ManagerService;
import org.king.classmanage.service.StudentService;
import org.king.classmanage.web.help.ManagerWithType;
import org.king.framework.web.action.BaseAction;
import org.king.security.domain.Account;
import org.king.security.domain.Person;
import org.king.security.domain.Role;
import org.king.security.service.AccountService;
import org.king.security.service.SecurityService;
import org.king.security.util.LdapFromSunDS;

public class ManagerAction extends BaseAction {
	private ManagerService managerService;

	private StudentService studentService;
	
	private AccountService accountService;
	
	private SecurityService securityService;
	

	/**
	 * @param securityService The securityService to set.
	 */
	public void setSecurityService(SecurityService securityService) {
		this.securityService = securityService;
	}

	/**
	 * @param accountService The accountService to set.
	 */
	public void setAccountService(AccountService accountService) {
		this.accountService = accountService;
	}

	public void setManagerService(ManagerService managerservice) {
		this.managerService = managerservice;
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
		
		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);
		
		// 性别
		List genderList = studentService.getDiction("1");
		request.setAttribute("genderList", genderList);
		managerService.initForm(request);
		
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院
			return mapping.findForward("list_hlxy");
		}else{
			return mapping.findForward("list");
		}
	
	}

	public ActionForward load4NameSearch(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) {
	
		
		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);
		
		DynaActionForm managerForm = (DynaActionForm) form;
		Managermodel managermodel = (Managermodel) managerForm
				.get("managermodel");
		String managerNo = managermodel.getManagerNo();
		LdapFromSunDS ldap = new LdapFromSunDS();
		HashMap managerInfo = ldap.getPersonInfo(request, managerNo);
		// Extract attributes and parameters we will need
		ActionMessages messages = new ActionMessages();
		String userName = "";
		String gender = "";
		String org = "";
		String type = "";
		if (null != managerInfo.get("userName")) {
			userName = managerInfo.get("userName").toString().trim();
			managermodel.setManagerName(userName);
			if (null != managerInfo.get("userSex")) {
				gender = (String) managerInfo.get("userSex");
				if (managerInfo.get("userSex").equals("男")) {
					gender = "1";
				} else if (managerInfo.get("userSex").equals("女")) {
					gender = "2";
				}				
			}
			
			if (null != managerInfo.get("userOrg")) {
				org = (String) managerInfo.get("userOrg");
			}
			if (null != managerInfo.get("userType")) {
				type = (String) managerInfo.get("userType");
			}
			managermodel.setGender(gender);
			managermodel.setManagerOrg(org);
			managermodel.setManagerType(type);
			managerForm.set("managermodel", managermodel);
		} else {
			managermodel.setManagerName("");
			managermodel.setGender("");
			managermodel.setManagerOrg("");
			managermodel.setManagerType("");
			managerForm.set("managermodel", managermodel);
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"manager.managernotexist"));
			saveErrors(request, messages);
		}
		if (managermodel.getManagerId() != null&&!"".equals(managermodel.getManagerId())) {
			return load4Edit(mapping, form, request, response);
		} else {
			return load4Add(mapping, form, request, response);
		}

	}

	public ActionForward load4Search(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		
		

		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);
		
		if (request.getParameter("msg") != null&&"add".equals(request.getParameter("msg"))) {
			request.setAttribute("msg", "添加或修改成功");
		}	
		
		DynaActionForm managerForm = (DynaActionForm) form;
		Managermodel managermodel = (Managermodel) managerForm
				.get("managermodel");
		String managerNo = managermodel.getManagerNo();
		String managerName = managermodel.getManagerName();
		String gender = managermodel.getGender();
		
		String school = managermodel.getSchoolId();//新增属性
		
		String leader = managerForm.get("leader").toString();
		String assistant = managerForm.get("assistant").toString();
		String tutor = managerForm.get("tutor").toString();
		String teacher = managerForm.get("teacher").toString();
		String page = request.getParameter("pager.offset");
		String available = managerForm.get("available1").toString();
		String[] args = { managerNo, managerName, gender, leader, assistant,
				tutor, teacher, page,school,available };
		List managermodels = null;		
		
		
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院
			//-------------------------------------------------
			String schoolId="0002";
			if (request.getParameter("export") == null
					|| "".equals(request.getParameter("export"))) {
				managermodels = managerService.findManager(args,schoolId);
				Integer managerCount = managerService.findManagerCount(args,schoolId);
				
				request.setAttribute("listcount", managerCount);
				
				request.setAttribute("managerCount", managerCount);
				request.setAttribute("managermodels", managermodels);
				// 性别
				request.setAttribute("genderList", studentService.getDiction("1"));
				managerService.initForm(request);
				return mapping.findForward("list_hlxy");
			} else {
				// =================================================================
				managermodels = managerService.findManagerExport(args,schoolId);
				// Create the Excel File
				String fileName = "managerInfo.xls";
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
				columnNames.add(0, "学/工号");
				columnNames.add(1, "姓名");
				columnNames.add(2, "性别");
//				columnNames.add(3, "所属院系");
				columnNames.add(3, "单位");
				columnNames.add(4, "人员类别");
				columnNames.add(5, "联系方式");
				columnNames.add(6, "职务");
				columnNames.add(7, "是否在任");

				for (int i = 0; i < columnNames.size(); i++) {
					HSSFCell cname = row.createCell((short) i);
					cname.setCellStyle(cellHeadStyle);
					cname.setEncoding(HSSFCell.ENCODING_UTF_16);
					cname.setCellValue((String) columnNames.get(i));
				}

				// Populate the Row Data to the SpreadSheet
				int rowCount = managermodels.size();
				// goal houses the number of cells in the target spreadsheet
				int goal = rowCount * columnNames.size();

				// actual population of target spreadsheet
				int currentCell = 0;

				for (int i = 0; i < rowCount; i++) {
					ManagerWithType tableData = (ManagerWithType) managermodels
							.get(i);
					// create row in spreadsheet
					row = sheet1.createRow((short) (i + 1));

					// populate the spreadsheet with the cell
					HSSFCell ctitle = row.createCell((short) 0);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);

					ctitle.setCellValue(tableData.getManagerNo() == null ? ""
							: tableData.getManagerNo().trim());

					ctitle = row.createCell((short) 1);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getManagerName() == null ? ""
							: tableData.getManagerName().trim());

					ctitle = row.createCell((short) 2);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getGender() == null ? ""
							: tableData.getGender().trim());
					
//					ctitle = row.createCell((short) 3);
//					ctitle.setCellStyle(cellDataStyle);
//					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
//					ctitle.setCellValue(tableData.getSchoolId() == null ? ""
//							: tableData.getSchoolId().trim());
					
					ctitle = row.createCell((short) 3);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getManagerOrg() == null ? ""
							: tableData.getManagerOrg().trim());

					ctitle = row.createCell((short) 4);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getManagerType() == null ? ""
							: tableData.getManagerType().trim());

					ctitle = row.createCell((short) 5);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getContact() == null ? ""
							: tableData.getContact().trim());

					ctitle = row.createCell((short) 6);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getRoleName() == null ? ""
							: tableData.getRoleName().trim());
					
					ctitle = row.createCell((short) 7);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					if(tableData.getAvailable() != null&&tableData.getAvailable().equals("1")){
						ctitle.setCellValue("是");
					}else if(tableData.getAvailable() != null&&tableData.getAvailable().equals("0")){
						ctitle.setCellValue("否");
					}else{
						ctitle.setCellValue("");						
					}
					// System.out.println(columnData);
					currentCell++;

				}
				OutputStream os;
				try {
					response.setContentType("application/x-msdownload");
					response
							.setHeader("Content-Disposition", "attachment;"
									+ " filename="
									+ new String(fileName.getBytes(), "GBK"));
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
			//-----------------------------------------------------------复旦学院
			String schoolId = "0001";
			if (request.getParameter("export") == null
					|| "".equals(request.getParameter("export"))) {
				managermodels = managerService.findManager(args,schoolId);
				Integer managerCount = managerService.findManagerCount(args,schoolId);
				
				request.setAttribute("listcount", managerCount);
				
				request.setAttribute("managerCount", managerCount);
				request.setAttribute("managermodels", managermodels);
				// 性别
				request.setAttribute("genderList", studentService.getDiction("1"));
				managerService.initForm(request);
				return mapping.findForward("list");
			} else {
				// =================================================================
				managermodels = managerService.findManagerExport(args,schoolId);
				// Create the Excel File
				String fileName = "managerInfo.xls";
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
				columnNames.add(0, "学/工号");
				columnNames.add(1, "姓名");
				columnNames.add(2, "性别");
//				columnNames.add(3, "所属院系");
				columnNames.add(3, "单位");
				columnNames.add(4, "人员类别");
				columnNames.add(5, "联系方式");
				columnNames.add(6, "职务");
				columnNames.add(7, "是否在任");				

				for (int i = 0; i < columnNames.size(); i++) {
					HSSFCell cname = row.createCell((short) i);
					cname.setCellStyle(cellHeadStyle);
					cname.setEncoding(HSSFCell.ENCODING_UTF_16);
					cname.setCellValue((String) columnNames.get(i));
				}

				// Populate the Row Data to the SpreadSheet
				int rowCount = managermodels.size();
				// goal houses the number of cells in the target spreadsheet
				int goal = rowCount * columnNames.size();

				// actual population of target spreadsheet
				int currentCell = 0;

				for (int i = 0; i < rowCount; i++) {
					ManagerWithType tableData = (ManagerWithType) managermodels
							.get(i);
					// create row in spreadsheet
					row = sheet1.createRow((short) (i + 1));

					// populate the spreadsheet with the cell
					HSSFCell ctitle = row.createCell((short) 0);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);

					ctitle.setCellValue(tableData.getManagerNo() == null ? ""
							: tableData.getManagerNo().trim());

					ctitle = row.createCell((short) 1);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getManagerName() == null ? ""
							: tableData.getManagerName().trim());

					ctitle = row.createCell((short) 2);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getGender() == null ? ""
							: tableData.getGender().trim());
					
//					ctitle = row.createCell((short) 3);
//					ctitle.setCellStyle(cellDataStyle);
//					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
//					ctitle.setCellValue(tableData.getSchoolId() == null ? ""
//							: tableData.getSchoolId().trim());
					
					ctitle = row.createCell((short) 3);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getManagerOrg() == null ? ""
							: tableData.getManagerOrg().trim());

					ctitle = row.createCell((short) 4);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getManagerType() == null ? ""
							: tableData.getManagerType().trim());

					ctitle = row.createCell((short) 5);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getContact() == null ? ""
							: tableData.getContact().trim());

					ctitle = row.createCell((short) 6);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getRoleName() == null ? ""
							: tableData.getRoleName().trim());
					
					ctitle = row.createCell((short) 7);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					if(tableData.getAvailable() != null&&tableData.getAvailable().equals("1")){
						ctitle.setCellValue("是");
					}else if(tableData.getAvailable() != null&&tableData.getAvailable().equals("0")){
						ctitle.setCellValue("否");
					}else{
						ctitle.setCellValue("");						
					}

					// System.out.println(columnData);
					currentCell++;

				}
				OutputStream os;
				try {
					response.setContentType("application/x-msdownload");
					response
							.setHeader("Content-Disposition", "attachment;"
									+ " filename="
									+ new String(fileName.getBytes(), "GBK"));
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
		
		DynaActionForm managerForm = (DynaActionForm) form;
		String managerId = request.getParameter("managerId");
		if (null != managerId) {
			Managermodel managermodel = managerService.getManager(managerId);
			if (null == managermodel) {
				load4List(mapping, form, request, response);
			}
			
			managerForm.set("managermodel", managermodel);
			List roleList = managerService.findManagerRole(managerId);
			for (int i = 0; i < roleList.size(); i++) {
				Managermanagerrole managermanagerrole = (Managermanagerrole) roleList
						.get(i);
				if ("01".equals(managermanagerrole.getId().getRoleId())) {
					managerForm.set("teacher", managermanagerrole.getId()
							.getRoleId());
				} else if ("11".equals(managermanagerrole.getId().getRoleId())) {
					managerForm.set("leader", managermanagerrole.getId()
							.getRoleId());
				} else if ("21".equals(managermanagerrole.getId().getRoleId())) {
					managerForm.set("assistant", managermanagerrole.getId()
							.getRoleId());
				} else if ("22".equals(managermanagerrole.getId().getRoleId())) {
					managerForm.set("tutor", managermanagerrole.getId()
							.getRoleId());
				}
			}

		}
		// 性别
		List genderList = studentService.getDiction("1");
		List typeList = studentService.getDepartment();
		managerService.initForm(request);
		request.setAttribute("genderList", genderList);
		request.setAttribute("typeList", typeList);
		request.setAttribute("actionFlag", "Modify");
		
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院
			//-------------------------------------------------
			return mapping.findForward("edit_hlxy");
		}else{
			//-------------------------------------------------复旦学院
			return mapping.findForward("edit");
		}
		
		
	}
	
	public ActionForward load4selfEdit(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
						
		HttpSession session = request.getSession(false);

	      if (session == null) {
		      session = request.getSession(true);
	      }
	      
	    DynaActionForm managerForm = (DynaActionForm) form;
       		
		Account manageract=(Account)session.getAttribute("accountPerson");        
        String managerNo=manageract.getPerson().getPersonCode();	//获取登录人的工号
        
        String managerId =null;
        List mgli=managerService.getManagerByNo(managerNo);
        if(mgli!=null&&mgli.size()>0){
        	Managermodel managerm=(Managermodel)mgli.get(0);
        	managerId=managerm.getManagerId();
        }
        	
		if (null != managerId) {
			Managermodel managermodel = managerService.getManager(managerId);
			if (null == managermodel) {
				request.setAttribute("msg","notManager");
				mapping.findForward("edit");
			}
						
			if(managermodel.getAvailable()!=null){
				request.setAttribute("manageravail",managermodel.getAvailable());
			}
			
			managerForm.set("managermodel", managermodel);
			List roleList = managerService.findManagerRole(managerId);
			for (int i = 0; i < roleList.size(); i++) {
				Managermanagerrole managermanagerrole = (Managermanagerrole) roleList
						.get(i);
				if ("01".equals(managermanagerrole.getId().getRoleId())) {
					managerForm.set("teacher", managermanagerrole.getId()
							.getRoleId());
					request.setAttribute("managerrole","01");
				} else if ("11".equals(managermanagerrole.getId().getRoleId())) {
					managerForm.set("leader", managermanagerrole.getId()
							.getRoleId());
					request.setAttribute("managerrole","11");
				} else if ("21".equals(managermanagerrole.getId().getRoleId())) {
					managerForm.set("assistant", managermanagerrole.getId()
							.getRoleId());
					request.setAttribute("managerrole","21");
				} else if ("22".equals(managermanagerrole.getId().getRoleId())) {
					managerForm.set("tutor", managermanagerrole.getId()
							.getRoleId());
					request.setAttribute("managerrole","22");
				}
			}

		}
		else{
			request.setAttribute("optresult","notManager");
		}
//		性别
		List genderList = studentService.getDiction("1");
		List typeList = studentService.getDepartment();
		managerService.initForm(request);
		request.setAttribute("genderList", genderList);
		request.setAttribute("typeList", typeList);
		return mapping.findForward("selfedit");
				
	}
	
	public ActionForward selfsave(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		
		DynaActionForm managerForm = (DynaActionForm) form;
		Managermodel managermodel = (Managermodel) managerForm
				.get("managermodel");
		try{			
		    managerService.updateManager(managermodel);
		    request.setAttribute("msg","0");
		}catch(Exception e){
			e.printStackTrace();
			request.setAttribute("msg","1");
		}
		return load4selfEdit(mapping,form,request,response);
	}

	public ActionForward load4Add(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		// 性别
		List genderList = studentService.getDiction("1");
		List typeList = studentService.getDepartment();
		managerService.initForm(request);
		request.setAttribute("genderList", genderList);
		request.setAttribute("typeList", typeList);
		request.setAttribute("actionFlag", "Add");
	
		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);		
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院
			//-------------------------------------------------
			return mapping.findForward("edit_hlxy");
		}else{
			//-------------------------------------------------复旦学院
			return mapping.findForward("add");
		}
		

	}

//	public ActionForward load4View(ActionMapping mapping, ActionForm form,
//			HttpServletRequest request, HttpServletResponse response) {
//		DynaActionForm managerForm = (DynaActionForm) form;
//		String managerId = request.getParameter("managerId");
//		if (null != managerId) {
//			Managermodel managermodel = managerService.getManager(managerId);
//			if (null == managermodel) {
//				load4List(mapping, form, request, response);
//			}
//			managerForm.set("managermodel", managermodel);
//		}
//		// 性别
//		request.setAttribute("genderList", studentService.getDiction("1"));
//		return mapping.findForward("edit");
//	}

	public ActionForward save(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		
		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);
		DynaActionForm managerForm = (DynaActionForm) form;
		Managermodel managermodel = (Managermodel) managerForm
				.get("managermodel");
		// Extract attributes and parameters we will need
		ActionMessages messages = new ActionMessages();
		String msg = null;
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院
			//-------------------------------------------------
			if ("".equals(managermodel.getManagerId())) {
				// 添加
				List list = new ArrayList();
				String leader = "";
				String assistant = managerForm.get("assistant").toString();
				String tutor = managerForm.get("tutor").toString();
				String teacher = managerForm.get("teacher").toString();
				if (!"".equals(leader)) {
					Managermanagerrole managermanagerrole = new Managermanagerrole();
					ManagermanagerroleId managermanagerroleId = new ManagermanagerroleId();
					managermanagerroleId.setManagerId("1");
					managermanagerroleId.setRoleId(leader);
					managermanagerrole.setId(managermanagerroleId);
					list.add(managermanagerrole);
				}
				if (!"".equals(assistant)) {
					Managermanagerrole managermanagerrole = new Managermanagerrole();
					ManagermanagerroleId managermanagerroleId = new ManagermanagerroleId();
					managermanagerroleId.setManagerId("1");
					managermanagerroleId.setRoleId(assistant);
					managermanagerrole.setId(managermanagerroleId);
					list.add(managermanagerrole);
				}
				if (!"".equals(tutor)) {
					Managermanagerrole managermanagerrole = new Managermanagerrole();
					ManagermanagerroleId managermanagerroleId = new ManagermanagerroleId();
					managermanagerroleId.setManagerId("1");
					managermanagerroleId.setRoleId(tutor);
					managermanagerrole.setId(managermanagerroleId);
					list.add(managermanagerrole);
				}
				if (!"".equals(teacher)) {
					Managermanagerrole managermanagerrole = new Managermanagerrole();
					ManagermanagerroleId managermanagerroleId = new ManagermanagerroleId();
					managermanagerroleId.setManagerId("1");
					managermanagerroleId.setRoleId(teacher);
					managermanagerrole.setId(managermanagerroleId);
					list.add(managermanagerrole);
				}

				try {
					if (managerService.getManagerByNo(managermodel.getManagerNo())
							.size() != 0) {
						
						// 编号重复
						messages.add(ActionMessages.GLOBAL_MESSAGE,
								new ActionMessage("manager.thesamemanagerno",
										managermodel.getManagerName().trim()));
						saveErrors(request, messages);
						request.setAttribute("actionFlag", "Add");
						return load4Add(mapping, form, request, response);
					} else {
						managerService.saveManagerandRole_hlxy(managermodel, list);
						
						//保存用户
						Account account = null;
						Set existRoles = null;
						account = accountService.findAccountByName(managermodel.getManagerNo());
						if (account == null || account.getId() == null){
							 account = new Account();
						}
						else{
							existRoles = account.getRoles();
						}
						Person person = new Person();
						person.setPersonCode(managermodel.getManagerNo());
						person.setPersonName(managermodel.getManagerName());
						person.setPersonType("2");
						person.setSex(managermodel.getGender());
						
						account.setName(managermodel.getManagerNo());
						account.setEnabled("0");
						account.setPerson(person);
						if (account != null && account.getId() != null){
							accountService.updateAccount(account);
						}
						else{
							accountService.saveAccount(account);
						}
						
						
						List roleList = new ArrayList();
						if (existRoles != null){
							Iterator it = existRoles.iterator();
							while (it.hasNext()){
								Role r = (Role)it.next();
								roleList.add(r.getId());
							}
							
						}
						String roleid ="";
						//授权
						if (!"".equals(leader)) {
							//学工组组长
							roleid = managerService.getRoleidByName("护理学院学工组组长");
							if(!"".equals(roleid)){
								roleList.add(roleid);
							}
						}
						if (!"".equals(assistant)) {
							//辅导员
							roleid = managerService.getRoleidByName("护理学院辅导员");
							if(!"".equals(roleid)){
								roleList.add(roleid);
							}
						}
						if (!"".equals(tutor)) {
							roleid = managerService.getRoleidByName("护理学院导师");
							if(!"".equals(roleid)){
								roleList.add(roleid);
							}
						}
						if (!"".equals(teacher)) {
							roleid = managerService.getRoleidByName("护理学院教务员");
							if(!"".equals(roleid)){
								roleList.add(roleid);
							}
						}
						
						String[] roleArr =  new String[roleList.size()];
						roleList.toArray(roleArr);
						securityService.grantAccountRoles(account.getId(),roleArr);
						messages.add(ActionMessages.GLOBAL_MESSAGE,
								new ActionMessage("manager.added", managermodel
										.getManagerName().trim()));
						saveErrors(request, messages);
						request.setAttribute("actionFlag", "Add");
						msg = "add";
					}
				} catch (Exception e) {
					e.printStackTrace();
					messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
							"manager.notsaved", managermodel.getManagerName()));
					saveErrors(request, messages);
					request.setAttribute("actionFlag", "Add");
					return load4Add(mapping, form, request, response);
				}
			} else {
				// 修改
				List list = new ArrayList();
				String leader = managerForm.get("leader").toString();
				String assistant = managerForm.get("assistant").toString();
				String tutor = managerForm.get("tutor").toString();
				String teacher = managerForm.get("teacher").toString();
				String roleStr = "";
				List roleList = new ArrayList();
				String roleid;
//				授权
				if (!"".equals(leader)) {
					//学工组组长
					roleid = managerService.getRoleidByName("护理学院学工组组长");
					if(!"".equals(roleid)){
						roleList.add(roleid);
					}
				}
				if (!"".equals(assistant)) {
					//辅导员
					roleid = managerService.getRoleidByName("护理学院辅导员");
					if(!"".equals(roleid)){
						roleList.add(roleid);
					}
				}
				if (!"".equals(tutor)) {
					roleid = managerService.getRoleidByName("护理学院导师");
					if(!"".equals(roleid)){
						roleList.add(roleid);
					}
				}
				if (!"".equals(teacher)) {
					roleid = managerService.getRoleidByName("护理学院教务员");
					if(!"".equals(roleid)){
						roleList.add(roleid);
					}
				}
				if (!"".equals(leader)) {
					Managermanagerrole managermanagerrole = new Managermanagerrole();
					ManagermanagerroleId managermanagerroleId = new ManagermanagerroleId();
					managermanagerroleId.setManagerId(managermodel.getManagerId());
					managermanagerroleId.setRoleId(leader);
					managermanagerrole.setId(managermanagerroleId);
					list.add(managermanagerrole);
					roleStr += "11,";
					
				}
				if (!"".equals(assistant)) {
					Managermanagerrole managermanagerrole = new Managermanagerrole();
					ManagermanagerroleId managermanagerroleId = new ManagermanagerroleId();
					managermanagerroleId.setManagerId(managermodel.getManagerId());
					managermanagerroleId.setRoleId(assistant);
					managermanagerrole.setId(managermanagerroleId);
					list.add(managermanagerrole);
					roleStr += "21,";
					
				}
				if (!"".equals(tutor)) {
					Managermanagerrole managermanagerrole = new Managermanagerrole();
					ManagermanagerroleId managermanagerroleId = new ManagermanagerroleId();
					managermanagerroleId.setManagerId(managermodel.getManagerId());
					managermanagerroleId.setRoleId(tutor);
					managermanagerrole.setId(managermanagerroleId);
					list.add(managermanagerrole);
					roleStr += "22,";
					
				}
				if (!"".equals(teacher)) {
					Managermanagerrole managermanagerrole = new Managermanagerrole();
					ManagermanagerroleId managermanagerroleId = new ManagermanagerroleId();
					managermanagerroleId.setManagerId(managermodel.getManagerId());
					managermanagerroleId.setRoleId(teacher);
					managermanagerrole.setId(managermanagerroleId);
					list.add(managermanagerrole);
					roleStr += "01,";
					
				}
				try {
//					managerService.getManager(managermodel.getManagerId());
					managermodel.setSchoolId("0002");
					managerService
							.updateManagerandRole(managermodel, list, roleStr);
					Account account = accountService.findAccountByName(managermodel.getManagerNo());
					
					Set existRoles = account.getRoles();
					Iterator it = existRoles.iterator();
					while (it.hasNext()){
						Role r = (Role)it.next();
						roleList.add(r.getId());
					}
					String[] roleArr =  new String[roleList.size()];
					roleList.toArray(roleArr);
					securityService.grantAccountRoles(account.getId(),roleArr);
//					List roleList = new ArrayList();
//					String roleid ="";
//					//授权
//					if (!"".equals(leader)) {
//						//主要负责人
//						roleid = managerService.getRoleidByName("学工组组长");
//						if(!"".equals(roleid)){
//							roleList.add(roleid);
//						}
//					}
//					if (!"".equals(assistant)) {
//						//辅导员
//						roleid = managerService.getRoleidByName("辅导员");
//						if(!"".equals(roleid)){
//							roleList.add(roleid);
//						}
//					}
//					if (!"".equals(tutor)) {
//						roleid = managerService.getRoleidByName("导师");
//						if(!"".equals(roleid)){
//							roleList.add(roleid);
//						}
//					}
//					if (!"".equals(teacher)) {
//						roleid = managerService.getRoleidByName("教务员");
//						if(!"".equals(roleid)){
//							roleList.add(roleid);
//						}
//					}
//					String[] roleArr =  new String[roleList.size()];
//					roleList.toArray(roleArr);
//					securityService.grantAccountRoles(managerService.getAccountidByNo(managermodel.getManagerNo()),roleArr);
					
					messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
							"manager.updated", managermodel.getManagerName()));
					saveErrors(request, messages);
					msg = "add";

				} catch (ManagerInClassException e) {
					e.printStackTrace();
					messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
							"manager.hadinclass", managermodel.getManagerName().trim()));
					saveErrors(request, messages);
					return load4Edit(mapping, form, request, response);
				} catch (ManagerInCollegeException e) {
					e.printStackTrace();
					messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
							"manager.hadincollege", managermodel.getManagerName().trim()));
					saveErrors(request, messages);
					return load4Edit(mapping, form, request, response);
				} catch (ManagerInSchoolException e) {
					e.printStackTrace();
					messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
							"manager.hadinschool", managermodel.getManagerName().trim()));
					saveErrors(request, messages);
					return load4Edit(mapping, form, request, response);
				} catch (Exception e) {
					e.printStackTrace();
					messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
							"manager.notupdated", managermodel.getManagerName().trim()));
					saveErrors(request, messages);
					request.setAttribute("actionFlag", "Modify");
					return load4Edit(mapping, form, request, response);
				}
			}
			removeAttribute(mapping, request);		
			return new RedirectingActionForward("/managerAction.do?method=load4Search&getrole=2" + "&msg="+ msg);
		}else{
			//-------------------------------------------------复旦学院

			if ("".equals(managermodel.getManagerId())) {
				// 添加
				List list = new ArrayList();
				String leader = managerForm.get("leader").toString();
				String assistant = managerForm.get("assistant").toString();
				String tutor = managerForm.get("tutor").toString();
				String teacher = managerForm.get("teacher").toString();
				if (!"".equals(leader)) {
					Managermanagerrole managermanagerrole = new Managermanagerrole();
					ManagermanagerroleId managermanagerroleId = new ManagermanagerroleId();
					managermanagerroleId.setManagerId("1");
					managermanagerroleId.setRoleId(leader);
					managermanagerrole.setId(managermanagerroleId);
					list.add(managermanagerrole);
				}
				if (!"".equals(assistant)) {
					Managermanagerrole managermanagerrole = new Managermanagerrole();
					ManagermanagerroleId managermanagerroleId = new ManagermanagerroleId();
					managermanagerroleId.setManagerId("1");
					managermanagerroleId.setRoleId(assistant);
					managermanagerrole.setId(managermanagerroleId);
					list.add(managermanagerrole);
				}
				if (!"".equals(tutor)) {
					Managermanagerrole managermanagerrole = new Managermanagerrole();
					ManagermanagerroleId managermanagerroleId = new ManagermanagerroleId();
					managermanagerroleId.setManagerId("1");
					managermanagerroleId.setRoleId(tutor);
					managermanagerrole.setId(managermanagerroleId);
					list.add(managermanagerrole);
				}
				if (!"".equals(teacher)) {
					Managermanagerrole managermanagerrole = new Managermanagerrole();
					ManagermanagerroleId managermanagerroleId = new ManagermanagerroleId();
					managermanagerroleId.setManagerId("1");
					managermanagerroleId.setRoleId(teacher);
					managermanagerrole.setId(managermanagerroleId);
					list.add(managermanagerrole);
				}
				
				
				try {
					if (managerService.getManagerByNo(managermodel.getManagerNo())
							.size() != 0) {
						
						// 编号重复
						messages.add(ActionMessages.GLOBAL_MESSAGE,
								new ActionMessage("manager.thesamemanagerno",
										managermodel.getManagerName().trim()));
						saveErrors(request, messages);
						request.setAttribute("actionFlag", "Add");
						return load4Add(mapping, form, request, response);
					} else {
						managerService.saveManagerandRole(managermodel, list);
						
						//保存用户
						Account account = null;
						Set existRoles = null;
						account = accountService.findAccountByName(managermodel.getManagerNo());
						if (account == null || account.getId() == null){
							 account = new Account();
						}
						else{
							existRoles = account.getRoles();
						}
						Person person = new Person();
						person.setPersonCode(managermodel.getManagerNo());
						person.setPersonName(managermodel.getManagerName());
						person.setPersonType("2");
						person.setSex(managermodel.getGender());
						
						account.setName(managermodel.getManagerNo());
						account.setEnabled("0");
						account.setPerson(person);
						if (account != null && account.getId() != null){
							accountService.updateAccount(account);
						}
						else{
							accountService.saveAccount(account);
						}
						
						
						List roleList = new ArrayList();
						if (existRoles != null){
							Iterator it = existRoles.iterator();
							while (it.hasNext()){
								Role r = (Role)it.next();
								roleList.add(r.getId());
							}
							
						}
						String roleid ="";
						//授权
						if (!"".equals(leader)) {
							//学工组组长
							roleid = managerService.getRoleidByName("学工组组长");
							if(!"".equals(roleid)){
								roleList.add(roleid);
							}
						}
						if (!"".equals(assistant)) {
							//辅导员
							roleid = managerService.getRoleidByName("辅导员");
							if(!"".equals(roleid)){
								roleList.add(roleid);
							}
						}
						if (!"".equals(tutor)) {
							roleid = managerService.getRoleidByName("导师");
							if(!"".equals(roleid)){
								roleList.add(roleid);
							}
						}
						if (!"".equals(teacher)) {
							roleid = managerService.getRoleidByName("教务员");
							if(!"".equals(roleid)){
								roleList.add(roleid);
							}
						}
						
						String[] roleArr =  new String[roleList.size()];
						roleList.toArray(roleArr);
						securityService.grantAccountRoles(account.getId(),roleArr);
						messages.add(ActionMessages.GLOBAL_MESSAGE,
								new ActionMessage("manager.added", managermodel
										.getManagerName().trim()));
						saveErrors(request, messages);
						request.setAttribute("actionFlag", "Add");
						msg = "add";
					}
				} catch (Exception e) {
					e.printStackTrace();
					messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
							"manager.notsaved", managermodel.getManagerName()));
					saveErrors(request, messages);
					request.setAttribute("actionFlag", "Add");
					return load4Add(mapping, form, request, response);
				}
			} else {
				// 修改
				List list = new ArrayList();
				String leader = managerForm.get("leader").toString();
				String assistant = managerForm.get("assistant").toString();
				String tutor = managerForm.get("tutor").toString();
				String teacher = managerForm.get("teacher").toString();
				String roleStr = "";
				if (!"".equals(leader)) {
					Managermanagerrole managermanagerrole = new Managermanagerrole();
					ManagermanagerroleId managermanagerroleId = new ManagermanagerroleId();
					managermanagerroleId.setManagerId(managermodel.getManagerId());
					managermanagerroleId.setRoleId(leader);
					managermanagerrole.setId(managermanagerroleId);
					list.add(managermanagerrole);
					roleStr += "11,";
				}
				if (!"".equals(assistant)) {
					Managermanagerrole managermanagerrole = new Managermanagerrole();
					ManagermanagerroleId managermanagerroleId = new ManagermanagerroleId();
					managermanagerroleId.setManagerId(managermodel.getManagerId());
					managermanagerroleId.setRoleId(assistant);
					managermanagerrole.setId(managermanagerroleId);
					list.add(managermanagerrole);
					roleStr += "21,";
				}
				if (!"".equals(tutor)) {
					Managermanagerrole managermanagerrole = new Managermanagerrole();
					ManagermanagerroleId managermanagerroleId = new ManagermanagerroleId();
					managermanagerroleId.setManagerId(managermodel.getManagerId());
					managermanagerroleId.setRoleId(tutor);
					managermanagerrole.setId(managermanagerroleId);
					list.add(managermanagerrole);
					roleStr += "22,";
				}
				if (!"".equals(teacher)) {
					Managermanagerrole managermanagerrole = new Managermanagerrole();
					ManagermanagerroleId managermanagerroleId = new ManagermanagerroleId();
					managermanagerroleId.setManagerId(managermodel.getManagerId());
					managermanagerroleId.setRoleId(teacher);
					managermanagerrole.setId(managermanagerroleId);
					list.add(managermanagerrole);
					roleStr += "01,";
				}
				try {
					managermodel.setSchoolId("0001");
					managerService
							.updateManagerandRole(managermodel, list, roleStr);
					Account account = accountService.findAccountByName(managermodel.getManagerNo());
					
					Set existRoles = account.getRoles();
					List roleList = new ArrayList();
					if (existRoles != null){
						Iterator it = existRoles.iterator();
						while (it.hasNext()){
							Role r = (Role)it.next();
							roleList.add(r.getId());
						}
						
					}
					String roleid ="";
					//授权
					if (!"".equals(leader)) {
						//学工组组长
						roleid = managerService.getRoleidByName("学工组组长");
						if(!"".equals(roleid)){
							roleList.add(roleid);
						}
					}
					if (!"".equals(assistant)) {
						//辅导员
						roleid = managerService.getRoleidByName("辅导员");
						if(!"".equals(roleid)){
							roleList.add(roleid);
						}
					}
					if (!"".equals(tutor)) {
						roleid = managerService.getRoleidByName("导师");
						if(!"".equals(roleid)){
							roleList.add(roleid);
						}
					}
					if (!"".equals(teacher)) {
						roleid = managerService.getRoleidByName("教务员");
						if(!"".equals(roleid)){
							roleList.add(roleid);
						}
					}
					
					String[] roleArr =  new String[roleList.size()];
					roleList.toArray(roleArr);
					securityService.grantAccountRoles(account.getId(),roleArr);
//					List roleList = new ArrayList();
//					String roleid ="";
//					//授权
//					if (!"".equals(leader)) {
//						//主要负责人
//						roleid = managerService.getRoleidByName("学工组组长");
//						if(!"".equals(roleid)){
//							roleList.add(roleid);
//						}
//					}
//					if (!"".equals(assistant)) {
//						//辅导员
//						roleid = managerService.getRoleidByName("辅导员");
//						if(!"".equals(roleid)){
//							roleList.add(roleid);
//						}
//					}
//					if (!"".equals(tutor)) {
//						roleid = managerService.getRoleidByName("导师");
//						if(!"".equals(roleid)){
//							roleList.add(roleid);
//						}
//					}
//					if (!"".equals(teacher)) {
//						roleid = managerService.getRoleidByName("教务员");
//						if(!"".equals(roleid)){
//							roleList.add(roleid);
//						}
//					}
//					String[] roleArr =  new String[roleList.size()];
//					roleList.toArray(roleArr);
//					securityService.grantAccountRoles(managerService.getAccountidByNo(managermodel.getManagerNo()),roleArr);
					
					messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
							"manager.updated", managermodel.getManagerName()));
					msg = "add";
					saveErrors(request, messages);

				} catch (ManagerInClassException e) {
					messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
							"manager.hadinclass", managermodel.getManagerName().trim()));
					saveErrors(request, messages);
					return load4Edit(mapping, form, request, response);
				} catch (ManagerInCollegeException e) {
					messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
							"manager.hadincollege", managermodel.getManagerName().trim()));
					saveErrors(request, messages);
					return load4Edit(mapping, form, request, response);
				} catch (ManagerInSchoolException e) {
					messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
							"manager.hadinschool", managermodel.getManagerName().trim()));
					saveErrors(request, messages);
					return load4Edit(mapping, form, request, response);
				} catch (Exception e) {
					messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
							"manager.notupdated", managermodel.getManagerName().trim()));
					saveErrors(request, messages);
					request.setAttribute("actionFlag", "Modify");
					return load4Edit(mapping, form, request, response);
				}
			}
			removeAttribute(mapping, request);
			return new RedirectingActionForward("/managerAction.do?method=load4Search" + "&msg="+ msg);
		}		
		

	}

	public ActionForward delete(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		String[] deleteX = request.getParameterValues("deleteX");
		// Extract attributes and parameters we will need
		ActionMessages messages = new ActionMessages();
		if (deleteX != null) {
//			for (int i = 0; i < deleteX.length; i++) {
//				try {
//					managerService.deleteManagerandRole(deleteX[i]);
//				} catch (ManagerInClassException e) {
//					messages.add(ActionMessages.GLOBAL_MESSAGE,
//							new ActionMessage("manager.hasinclass",
//									managerService.getManager(deleteX[i])
//											.getManagerName()));
//					saveErrors(request, messages);
//					return load4Search(mapping, form, request, response);
//				} catch (ManagerInCollegeException e) {
//					messages.add(ActionMessages.GLOBAL_MESSAGE,
//							new ActionMessage("manager.hasincollege",
//									managerService.getManager(deleteX[i])
//											.getManagerName().trim()));
//					saveErrors(request, messages);
//					return load4Search(mapping, form, request, response);
//				} catch (ManagerInSchoolException e) {
//					messages.add(ActionMessages.GLOBAL_MESSAGE,
//							new ActionMessage("manager.hasinschool",
//									managerService.getManager(deleteX[i])
//											.getManagerName().trim()));
//					saveErrors(request, messages);
//					return load4Search(mapping, form, request, response);
//				} catch (Exception e) {
//					messages.add(ActionMessages.GLOBAL_MESSAGE,
//							new ActionMessage("manager.notdeleted",
//									managerService.getManager(deleteX[i])
//											.getManagerName().trim()));
//					saveErrors(request, messages);
//					return load4Search(mapping, form, request, response);
//				}
//			}
			managerService.modifyManager_Available(deleteX);//修改管理员是否在任
		}
		messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
				"manager.successdeleted"));
		saveErrors(request, messages);
		
		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院
			//-------------------------------------------------
		}else{
			//-------------------------------------------------复旦学院
		}
		
		return load4Search(mapping, form, request, response);
	}
	
	public ActionForward changeOnSeatState(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		
		boolean flag=false;
		
		String[] ids=request.getParameterValues("cbgroup");
		
		String ifonseat="1";
		if(request.getParameter("ifonseat")!=null&&request.getParameter("ifonseat").length()>0){
			ifonseat=request.getParameter("ifonseat");
		}
		for(int i=0;i<ids.length;i++){
		            
		    try {
			 
		     Managermodel manager=managerService.findManager(ids[i]);
 		     // 数据库验证
		
			 manager.setAvailable(ifonseat);
			 managerService.updateManager(manager);
			 
			 request.setAttribute("updatemsg","0");
			 flag=true;
			 
		    } catch (Exception e) {
			e.printStackTrace();			
			flag=false;
			request.setAttribute("updatemsg","1");
			return load4Search(mapping, form, request, response);
			
		    }
		}
		if(flag)
			return load4Search(mapping, form, request, response);
		else{
			request.setAttribute("updatemsg","1");
			return load4Search(mapping, form, request, response);
		}
				
	}

}
