package org.king.dormitorymanage.web.action;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

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
import org.king.classmanage.domain.Managermodel;
import org.king.classmanage.service.ClassService;
import org.king.classmanage.service.CollegeService;
import org.king.classmanage.service.ManagerService;
import org.king.classmanage.service.StudentService;
import org.king.dormitorymanage.domain.Dormitorymodel;
import org.king.dormitorymanage.exception.AccomodationNotEnoughException;
import org.king.dormitorymanage.exception.AccomodationNotRightException;
import org.king.dormitorymanage.exception.DormitoryHasStuException;
import org.king.dormitorymanage.exception.DormitoryHasnotbindedException;
import org.king.dormitorymanage.exception.DormitoryNotExistException;
import org.king.dormitorymanage.exception.GenderNotExistException;
import org.king.dormitorymanage.exception.GenderNotMatchException;
import org.king.dormitorymanage.exception.LocationNotExistException;
import org.king.dormitorymanage.exception.StudentAlreadyInDormException;
import org.king.dormitorymanage.service.DormitoryService;
import org.king.dormitorymanage.web.help.DormitoryHisWithAllInfo;
import org.king.dormitorymanage.web.help.DormitoryStatistic;
import org.king.dormitorymanage.web.help.DormitoryWithAllInfo;
import org.king.framework.web.action.BaseAction;
import org.king.rcvmanage.service.RcvmanageService;
import org.king.security.domain.Account;
import org.king.upload.web.form.UpLoadForm;
import org.king.utils.StringUtil;

public class DormitoryAction extends BaseAction {
	private DormitoryService dormitoryService;

	private StudentService studentService;

	private CollegeService collegeService;

	private ClassService classService;

	private ManagerService managerService;

	public void setDormitoryService(DormitoryService dormitoryService) {
		this.dormitoryService = dormitoryService;
	}

	public void setStudentService(StudentService studentService) {
		this.studentService = studentService;
	}
	
    private RcvmanageService rcvmanageservice;
	
	public void setRcvmanageService(RcvmanageService rcvmanageservice) {
		this.rcvmanageservice = rcvmanageservice;
	}

	public ActionForward init4Maintain(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
//		// 楼列表
//		List dormitoryList = studentService.getDiction("7");
//		request.setAttribute("dormitoryList", dormitoryList);
//		// 楼区域列表
//		List locationList = studentService.getDiction("6");
//		request.setAttribute("locationList", locationList);
		// 性别
		List genderList = studentService.getDiction("1");
		request.setAttribute("genderList", genderList);
		
		dormitoryService.initForm(request);
		
		return mapping.findForward("init4Maintain");
	}

	public ActionForward init4Upload(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		return mapping.findForward("init4Upload");
	}

	public ActionForward init4Search(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		DynaActionForm adjustForm = (DynaActionForm)form; 
		String operator = "";
		HttpSession session = request.getSession();
		if(session!=null){
			Account account = (Account)session.getAttribute("accountPerson");
			if(account!=null){
				operator = account.getPerson().getPersonCode();
			}
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
		// 专业
		List majorinList = studentService.getmajorList();
		request.setAttribute("majorinList", majorinList);
		// 书院列表
		List collegeList = collegeService.getAllCollegeByfdxy();
		request.setAttribute("collegeList", collegeList);


//		// 楼区域列表
//		List locationList = studentService.getDiction("6");
//		request.setAttribute("locationList", locationList);
//		// 楼列表
//		List dormitoryList = studentService.getDiction("7");
//		request.setAttribute("dormitoryList", dormitoryList);
		
		dormitoryService.initForm(request);
		List areali = (List)request.getAttribute("areaList");
//		if(areali!=null&&areali.size()>0){
//			adjustForm.set("area",((Map)areali.get(0)).get("dictValue"));
//		}
		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院
			//-------------------------------------------------
			// 辅导员列表
			List assistantList = managerService.getClassAssitant_hlxy();
			request.setAttribute("assistantList", assistantList);
			// 班级列表
			List classList = classService.getClassmodelbyschoolId(new String("0002"));
			request.setAttribute("classList", classList);
			return mapping.findForward("init4Search_hlxy");
		}else if(getrole!=null&&!getrole.equals("")&&getrole.equals("3")){
			if(areali!=null&&areali.size()>0){
				adjustForm.set("area",((Map)areali.get(0)).get("dictValue"));
				request.setAttribute("area", ((Map)areali.get(0)).get("dictValue"));
				List localli = (List)request.getAttribute("locationList");
				if(localli!=null&&localli.size()>0){
					for(int i=0;i<localli.size();i++){
						if(((Map)localli.get(i)).get("dictParent").equals(((Map)areali.get(0)).get("dictValue"))){
							adjustForm.set("location",((Map)localli.get(i)).get("dictValue"));
							request.setAttribute("location", ((Map)localli.get(i)).get("dictValue"));
							break;
						}
					}
				}
			}
			//-------------------------------------------------研工
			return mapping.findForward("init4Search_yg");
		}else {
			//-------------------------------------------------复旦学院
			// 辅导员列表
			List assistantList = managerService.getClassAssitant();
			request.setAttribute("assistantList", assistantList);
			// 班级列表
			List classList = classService.getClassmodelbyschoolId(new String("0001"));
			request.setAttribute("classList", classList);
			return mapping.findForward("init4Search");
		}
		


	}
	public ActionForward singleSearch(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		
		String timespan="";
		timespan=rcvmanageservice.checkTimeUp("0906036");
		if(!timespan.equals("")){
			request.setAttribute("timespan",timespan);
			return mapping.findForward("timeup");
		}
		
		String operator = "";
		if (request.getSession().getAttribute("accountPerson") != null) {
			operator = ((Account) request.getSession().getAttribute(
					"accountPerson")).getPerson().getPersonCode();
		}
		
		List li = dormitoryService.getSingleDormInfo(operator);
		if(li!=null&&li.size()!=0){
			request.setAttribute("singleInfoList", li);
		}	
		return mapping.findForward("singleSearch");
	}
	public ActionForward init4FeeSearch(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
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
		// 书院列表
		List collegeList = collegeService.getAllCollegeByfdxy();
		request.setAttribute("collegeList", collegeList);
		// 班级列表
		List classList = classService.getClassmodelbyschoolId(new String("0001"));
		request.setAttribute("classList", classList);
		// 辅导员列表
		List assistantList = managerService.getClassAssitant();
		request.setAttribute("assistantList", assistantList);
//		// 楼区域列表
//		List locationList = studentService.getDiction("6");
//		request.setAttribute("locationList", locationList);
//		// 楼列表
//		List dormitoryList = studentService.getDiction("7");
//		request.setAttribute("dormitoryList", dormitoryList);
		
		dormitoryService.initForm(request);
		
		return mapping.findForward("init4FeeSearch");

	}

	public ActionForward init4fdySearch(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {

//		// 楼区域列表
//		List locationList = studentService.getDiction("6");
//		request.setAttribute("locationList", locationList);
//		// 楼列表
//		List dormitoryList = studentService.getDiction("7");
//		request.setAttribute("dormitoryList", dormitoryList);
		dormitoryService.initForm_fdy(request);
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
		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院
			//-------------------------------------------------
			return mapping.findForward("init4fdySearch_hlxy");
		}else{
			//-------------------------------------------------复旦学院
			return mapping.findForward("init4fdySearch");
		}



	}

	public ActionForward searchDetail(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		String operator = "";
		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);
		HttpSession session = request.getSession();
		if(session!=null){
			Account account = (Account)session.getAttribute("accountPerson");
			if(account!=null){
				operator = account.getPerson().getPersonCode();
			}
		}
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院
			//-------------------------------------------------
			// 处理查询信息
			// 获取查询关键字
			String schoolId = "0002";
			DynaActionForm dormForm = (DynaActionForm) form;
			String dormitory = dormForm.get("dorm").toString();
			String roomNumber = dormForm.get("roomNumber").toString();
			String collegeId = dormForm.get("collegeId").toString();
			String classId = dormForm.get("classId").toString();
			String managerId = dormForm.get("managerId").toString();
			String studentNo = dormForm.get("studentNo").toString();
			String stuName = dormForm.get("stuName").toString();
			String gender = dormForm.get("gender").toString();
			
			String district = dormForm.get("district").toString();	
			String enterenceNo = dormForm.get("enterenceNo").toString();
			
			String majorin = dormForm.get("majorin").toString();
			String nation = dormForm.get("nation").toString();
			String fromProvince = dormForm.get("fromProvince").toString();
			String location = dormForm.get("location").toString();
			
			String area = "";
			if(dormForm.get("area")!=null){
			area = dormForm.get("area").toString();
			}
			String offSet = request.getParameter("pager.offset");
			request.setAttribute("myclass", classId);
			request.setAttribute("mydormitory", dormitory);
			String[] args = { dormitory, roomNumber, collegeId, classId, managerId,
					studentNo, stuName, gender,majorin, nation, fromProvince, location,
					offSet,area,district,enterenceNo };
			List dormitorys = null;
			Integer dormitoryCount;
			if (request.getParameter("export") == null
					|| "".equals(request.getParameter("export"))) {
//				// 楼区域列表
//				List locationList = studentService.getDiction("6");
//				request.setAttribute("locationList", locationList);
//				// 楼列表
//				List dormitoryList = studentService.getDiction("7");
//				request.setAttribute("dormitoryList", dormitoryList);
				
				dormitoryService.initForm(request);
				
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
				// 书院列表
				List collegeList = collegeService.getAllCollegeByfdxy();
				request.setAttribute("collegeList", collegeList);
				// 班级列表
				List classList = classService.getClassmodelbyschoolId(new String("0002"));
				request.setAttribute("classList", classList);
				// 辅导员列表
				List assistantList = managerService.getClassAssitant_hlxy();
				request.setAttribute("assistantList", assistantList);

				dormitorys = dormitoryService.findDormitorys(args,schoolId);
				dormitoryCount = dormitoryService.getDormitoryCount(args,schoolId);
				request.setAttribute("dormitorys", dormitorys);
				request.setAttribute("dormitoryCount", dormitoryCount);

				return mapping.findForward("init4Search_hlxy");
			} else {
				// =================================================================
				dormitorys = dormitoryService.findDormitorysExport(args,schoolId);
				// Create the Excel File
				String fileName = "student_dormitory_Info.xls";
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
				columnNames.add(0, "校区");
				columnNames.add(1, "区域");
				columnNames.add(2, "楼号");
				columnNames.add(3, "宿舍号");
				columnNames.add(4, "班级");
				columnNames.add(5, "辅导员");
				columnNames.add(6, "学号");
				columnNames.add(7, "录取通知书号");				
				columnNames.add(8, "姓名");
				columnNames.add(9, "性别");
				columnNames.add(10, "专业");
//				columnNames.add(10, "生源地");
				columnNames.add(11, "上海区县");

				for (int i = 0; i < columnNames.size(); i++) {
					HSSFCell cname = row.createCell((short) i);
					cname.setCellStyle(cellHeadStyle);
					cname.setEncoding(HSSFCell.ENCODING_UTF_16);
					cname.setCellValue((String) columnNames.get(i));
				}

				// Populate the Row Data to the SpreadSheet
				int rowCount = dormitorys.size();
				// goal houses the number of cells in the target spreadsheet
				int goal = rowCount * columnNames.size();

				// actual population of target spreadsheet
				int currentCell = 0;

				for (int i = 0; i < rowCount; i++) {
					DormitoryWithAllInfo tableData = (DormitoryWithAllInfo) dormitorys
							.get(i);
					// create row in spreadsheet
					row = sheet1.createRow((short) (i + 1));

					// populate the spreadsheet with the cell
					HSSFCell ctitle = row.createCell((short) 0);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getArea());
					
					ctitle = row.createCell((short) 1);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getLocation());

					ctitle = row.createCell((short) 2);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getDormitory());

					ctitle = row.createCell((short) 3);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getRoomNumber());

					ctitle = row.createCell((short) 4);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getClassNo());

					ctitle = row.createCell((short) 5);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getManagerName());

					ctitle = row.createCell((short) 6);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getStudentNo());
					
					ctitle = row.createCell((short) 7);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getBirthday());

					ctitle = row.createCell((short) 8);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getStuName());

					ctitle = row.createCell((short) 9);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getGender());

					ctitle = row.createCell((short) 10);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getMajorin());

//					ctitle = row.createCell((short) 10);
//					ctitle.setCellStyle(cellDataStyle);
//					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
//					ctitle.setCellValue(tableData.getFromProvince());

					ctitle = row.createCell((short) 11);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getNation());

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
		}else if(getrole!=null&&!"".equals(getrole)&&getrole.equals("3")){ //研工部
			//-------------------------------------------------
			// 处理查询信息
			// 获取查询关键字
			String schoolId = "0003";
			DynaActionForm dormForm = (DynaActionForm) form;
		    String area = dormForm.get("area").toString();
			String location = dormForm.get("location").toString();
			String dormitory = dormForm.get("dorm").toString();
			String unit = dormForm.get("unit").toString();
			String roomNumber = dormForm.get("roomNumber").toString();
			String dormfee = dormForm.get("dormfee").toString();
			String studentNo = dormForm.get("studentNo").toString();
			String stuName = dormForm.get("stuName").toString();
			String gender = dormForm.get("gender").toString();

			String offSet = request.getParameter("pager.offset");
			request.setAttribute("mydormitory", dormitory);
			String[] args = {area,location,dormitory,unit,roomNumber,dormfee,studentNo, stuName, gender,offSet,operator};
			List dormitorys = null;
			Integer dormitoryCount;
			if (request.getParameter("export") == null
					|| "".equals(request.getParameter("export"))) {			
				dormitoryService.initForm(request);				
				// 性别
				List genderList = studentService.getDiction("1");
				request.setAttribute("genderList", genderList);

				dormitorys = dormitoryService.findDormitorys4yg(args,schoolId);
				dormitoryCount = dormitoryService.getDormitoryCount4yg(args,schoolId);
				request.setAttribute("dormitorys", dormitorys);
				request.setAttribute("dormitoryCount", dormitoryCount);

				return mapping.findForward("init4Search_yg");
			} else {
				// =================================================================
				dormitorys = dormitoryService.findDormitorysExport4yg(args,schoolId);
				// Create the Excel File
				String fileName = "student_dormitory_Info.xls";
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
				columnNames.add(0, "校区");
				columnNames.add(1, "区域");
				columnNames.add(2, "楼号");
				columnNames.add(3, "单元号");
				columnNames.add(4, "宿舍号");
				columnNames.add(5, "住宿费");
				columnNames.add(6, "学号");
				columnNames.add(7, "姓名");
				columnNames.add(8, "性别");
				columnNames.add(9, "出生日期");

				for (int i = 0; i < columnNames.size(); i++) {
					HSSFCell cname = row.createCell((short) i);
					cname.setCellStyle(cellHeadStyle);
					cname.setEncoding(HSSFCell.ENCODING_UTF_16);
					cname.setCellValue((String) columnNames.get(i));
				}

				// Populate the Row Data to the SpreadSheet
				int rowCount = dormitorys.size();
				// goal houses the number of cells in the target spreadsheet
				int goal = rowCount * columnNames.size();

				// actual population of target spreadsheet
				int currentCell = 0;

				for (int i = 0; i < rowCount; i++) {
					DormitoryWithAllInfo tableData = (DormitoryWithAllInfo) dormitorys
							.get(i);
					// create row in spreadsheet
					row = sheet1.createRow((short) (i + 1));

					// populate the spreadsheet with the cell
					HSSFCell ctitle = row.createCell((short) 0);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getArea());

					ctitle = row.createCell((short) 1);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getLocation());

					ctitle = row.createCell((short) 2);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getDormitory());

					ctitle = row.createCell((short) 3);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getUnit());

					ctitle = row.createCell((short) 4);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getRoomNumber());

					ctitle = row.createCell((short) 5);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getFee());

					ctitle = row.createCell((short) 6);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getStudentNo());

					ctitle = row.createCell((short) 7);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getStuName());

					ctitle = row.createCell((short) 8);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getGender());
					
					ctitle = row.createCell((short) 9);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getBirthday());

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
			// 处理查询信息
			// 获取查询关键字
			String schoolId = "0001";
			DynaActionForm dormForm = (DynaActionForm) form;
			String dormitory = dormForm.get("dorm").toString();
			String roomNumber = dormForm.get("roomNumber").toString();
			String collegeId = dormForm.get("collegeId").toString();
			String classId = dormForm.get("classId").toString();
			String managerId = dormForm.get("managerId").toString();
			String studentNo = dormForm.get("studentNo").toString();
			String stuName = dormForm.get("stuName").toString();
			String gender = dormForm.get("gender").toString();
			String majorin = dormForm.get("majorin").toString();
			String nation = dormForm.get("nation").toString();
			String enterenceNo = dormForm.get("enterenceNo").toString();
			String fromProvince = dormForm.get("fromProvince").toString();
			String location = dormForm.get("location").toString();
			String area = "";
			if(dormForm.get("area")!=null){
			area = dormForm.get("area").toString();
			}
			String offSet = request.getParameter("pager.offset");
			request.setAttribute("myclass", classId);
			request.setAttribute("mydormitory", dormitory);
			String[] args = { dormitory, roomNumber, collegeId, classId, managerId,
					studentNo, stuName, gender,majorin, nation, fromProvince, location,
					offSet,area,"",enterenceNo};
			List dormitorys = null;
			Integer dormitoryCount;
			if (request.getParameter("export") == null
					|| "".equals(request.getParameter("export"))) {
//				// 楼区域列表
//				List locationList = studentService.getDiction("6");
//				request.setAttribute("locationList", locationList);
//				// 楼列表
//				List dormitoryList = studentService.getDiction("7");
//				request.setAttribute("dormitoryList", dormitoryList);
				
				dormitoryService.initForm(request);
				
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
				// 书院列表
				List collegeList = collegeService.getAllCollegeByfdxy();
				request.setAttribute("collegeList", collegeList);
				// 班级列表
				List classList = classService.getClassmodelbyschoolId(new String("0001"));
				request.setAttribute("classList", classList);
				// 辅导员列表
				List assistantList = managerService.getClassAssitant();
				request.setAttribute("assistantList", assistantList);

				dormitorys = dormitoryService.findDormitorys(args,schoolId);
				dormitoryCount = dormitoryService.getDormitoryCount(args,schoolId);
				request.setAttribute("dormitorys", dormitorys);
				request.setAttribute("dormitoryCount", dormitoryCount);

				return mapping.findForward("init4Search");
			} else {
				// =================================================================
				dormitorys = dormitoryService.findDormitorysExport(args,schoolId);
				// Create the Excel File
				String fileName = "student_dormitory_Info.xls";
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
//				columnNames.add(0, "校区");				
				columnNames.add(0, "校区");
				columnNames.add(1, "楼号");
				columnNames.add(2, "宿舍号");
				columnNames.add(3, "书院");
				columnNames.add(4, "班级");
				columnNames.add(5, "辅导员");
				columnNames.add(6, "学号");
				columnNames.add(7, "录取通知书号");				
				columnNames.add(8, "姓名");
				columnNames.add(9, "性别");
				columnNames.add(10, "专业");
				columnNames.add(11, "生源地");
				columnNames.add(12, "民族");

				for (int i = 0; i < columnNames.size(); i++) {
					HSSFCell cname = row.createCell((short) i);
					cname.setCellStyle(cellHeadStyle);
					cname.setEncoding(HSSFCell.ENCODING_UTF_16);
					cname.setCellValue((String) columnNames.get(i));
				}

				// Populate the Row Data to the SpreadSheet
				int rowCount = dormitorys.size();
				// goal houses the number of cells in the target spreadsheet
				int goal = rowCount * columnNames.size();

				// actual population of target spreadsheet
				int currentCell = 0;

				for (int i = 0; i < rowCount; i++) {
					DormitoryWithAllInfo tableData = (DormitoryWithAllInfo) dormitorys
							.get(i);
					// create row in spreadsheet
					row = sheet1.createRow((short) (i + 1));

					// populate the spreadsheet with the cell
					HSSFCell ctitle = row.createCell((short) 0);
					
//					ctitle.setCellStyle(cellDataStyle);
//					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
//					ctitle.setCellValue(tableData.getArea());
//					
//					ctitle = row.createCell((short) 1);					
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getLocation());

					ctitle = row.createCell((short) 1);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getDormitory());

					ctitle = row.createCell((short) 2);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getRoomNumber());

					ctitle = row.createCell((short) 3);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getCollegeName());

					ctitle = row.createCell((short) 4);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getClassNo());

					ctitle = row.createCell((short) 5);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getManagerName());

					ctitle = row.createCell((short) 6);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getStudentNo());

					ctitle = row.createCell((short) 7);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getBirthday());
					
					ctitle = row.createCell((short) 8);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getStuName());

					ctitle = row.createCell((short) 9);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getGender());

					ctitle = row.createCell((short) 10);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getMajorin());

					ctitle = row.createCell((short) 11);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getFromProvince());

					ctitle = row.createCell((short) 12);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getNation());

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
	
	public ActionForward searchFeeDetail(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {

		// 处理查询信息
		// 获取查询关键字
		String schoolId ="0001";
		DynaActionForm dormForm = (DynaActionForm) form;
		String dormitory = dormForm.get("dorm").toString();
		String roomNumber = dormForm.get("roomNumber").toString();
		String collegeId = dormForm.get("collegeId").toString();
		String classId = dormForm.get("classId").toString();
		String managerId = dormForm.get("managerId").toString();
		String studentNo = dormForm.get("studentNo").toString();
		String stuName = dormForm.get("stuName").toString();
		String gender = dormForm.get("gender").toString();
		String majorin = dormForm.get("majorin").toString();
		String nation = dormForm.get("nation").toString();
		String fromProvince = dormForm.get("fromProvince").toString();
		String location = dormForm.get("location").toString();
		String offSet = request.getParameter("pager.offset");
		String area = dormForm.get("area").toString();
		
		request.setAttribute("myclass", classId);
		request.setAttribute("mydormitory", dormitory);
		String[] args = { dormitory, roomNumber, collegeId, classId, managerId,
				studentNo, stuName, gender, majorin, nation, fromProvince, location,
				offSet,area };
		List dormitorys = null;
		Integer dormitoryCount;
		if (request.getParameter("export") == null
				|| "".equals(request.getParameter("export"))) {
//			// 楼区域列表
//			List locationList = studentService.getDiction("6");
//			request.setAttribute("locationList", locationList);
//			// 楼列表
//			List dormitoryList = studentService.getDiction("7");
//			request.setAttribute("dormitoryList", dormitoryList);
			
			dormitoryService.initForm(request);
			
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
			// 书院列表
			List collegeList = collegeService.getAllCollegeByfdxy();
			request.setAttribute("collegeList", collegeList);
			// 班级列表
			List classList = classService.getClassmodelbyschoolId(new String("0001"));
			request.setAttribute("classList", classList);
			// 辅导员列表
			List assistantList = managerService.getClassAssitant();
			request.setAttribute("assistantList", assistantList);

			dormitorys = dormitoryService.findDormitorys(args,schoolId);
			dormitoryCount = dormitoryService.getDormitoryCount(args,schoolId);
			request.setAttribute("dormitorys", dormitorys);
			request.setAttribute("dormitoryCount", dormitoryCount);

			return mapping.findForward("init4FeeSearch");
		} else {
			// =================================================================
			dormitorys = dormitoryService.findDormitorysExport(args,schoolId);
			// Create the Excel File
			String fileName = "student_dormitory_Info.xls";
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
			columnNames.add(0, "校区");
			columnNames.add(1, "楼号");
			columnNames.add(2, "宿舍号");
			columnNames.add(3, "住宿费");
			columnNames.add(4, "学号");
			columnNames.add(5, "姓名");
			columnNames.add(6, "性别");
			columnNames.add(7, "专业");
			columnNames.add(8, "生源地");
			columnNames.add(9, "民族");
			columnNames.add(10, "书院");
			columnNames.add(11, "班级");
			columnNames.add(12, "辅导员");
			

			for (int i = 0; i < columnNames.size(); i++) {
				HSSFCell cname = row.createCell((short) i);
				cname.setCellStyle(cellHeadStyle);
				cname.setEncoding(HSSFCell.ENCODING_UTF_16);
				cname.setCellValue((String) columnNames.get(i));
			}

			// Populate the Row Data to the SpreadSheet
			int rowCount = dormitorys.size();
			// goal houses the number of cells in the target spreadsheet
			int goal = rowCount * columnNames.size();

			// actual population of target spreadsheet
			int currentCell = 0;

			for (int i = 0; i < rowCount; i++) {
				DormitoryWithAllInfo tableData = (DormitoryWithAllInfo) dormitorys
						.get(i);
				// create row in spreadsheet
				row = sheet1.createRow((short) (i + 1));

				// populate the spreadsheet with the cell
				HSSFCell ctitle = row.createCell((short) 0);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue(tableData.getLocation());

				ctitle = row.createCell((short) 1);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue(tableData.getDormitory());

				ctitle = row.createCell((short) 2);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue(tableData.getRoomNumber());
				
				ctitle = row.createCell((short) 3);
				ctitle.setCellStyle(cellDataStyle);				
				ctitle.setCellValue(tableData.getFee());
				
				ctitle = row.createCell((short) 4);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue(tableData.getStudentNo());

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
				ctitle.setCellValue(tableData.getMajorin());

				ctitle = row.createCell((short) 8);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue(tableData.getFromProvince());

				ctitle = row.createCell((short) 9);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue(tableData.getNation());

				ctitle = row.createCell((short) 10);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue(tableData.getCollegeName());

				ctitle = row.createCell((short) 11);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue(tableData.getClassNo());

				ctitle = row.createCell((short) 12);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue(tableData.getManagerName());

				

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

	public ActionForward searchfdyDetail(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		
		
		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院
			//-------------------------------------------------
			HttpSession session = request.getSession(false);
			ActionMessages messages = new ActionMessages();
			DynaActionForm dormForm = (DynaActionForm) form;
			String dormitory = dormForm.get("dorm").toString();
			String roomNumber = dormForm.get("roomNumber").toString();
			String studentNo = dormForm.get("studentNo").toString();
			String stuName = dormForm.get("stuName").toString();
			String gender = dormForm.get("gender").toString();
			String majorin = dormForm.get("majorin").toString();
			String nation = dormForm.get("nation").toString();
			String enterenceNo = dormForm.get("enterenceNo").toString();
			String fromProvince = dormForm.get("fromProvince").toString();
			String location = dormForm.get("location").toString();
			String area = dormForm.get("area").toString();
			String orderby = request.getParameter("orderby");
			String sort = request.getParameter("sort");
			String offSet = request.getParameter("pager.offset");
			
			String classId = dormForm.get("classId").toString();	
			String district = dormForm.get("district").toString();	
			
			request.setAttribute("mydormitory", dormitory);
			String[] args = { dormitory, roomNumber, studentNo, stuName,gender, majorin,
					nation, fromProvince, location, offSet, orderby, sort,area,classId,district,enterenceNo };
			Account account = null;
			if (session.getAttribute("accountPerson") != null) {
				account = (Account) session.getAttribute("accountPerson");
				String managerNo = account.getPerson().getPersonCode();
				List managerList = managerService.getManagerByNo(managerNo);
				if (managerList.size() > 0) {
					Managermodel Managermodel = (Managermodel) managerList.get(0);
					List classlist = managerService
							.findManagerclass_hlxy(Managermodel.getManagerId());
					if (classlist!=null&&classlist.size()>0) {

						List dormitorys = null;
						Integer dormitoryCount;
						if (request.getParameter("export") == null
								|| "".equals(request.getParameter("export"))) {
							dormitorys = dormitoryService.findfdyDormitorys_hlxy(args,
									classlist);
							dormitoryCount = dormitoryService.getfdyDormitoryCount_hlxy(
									args, classlist);
							request.setAttribute("dormitorys", dormitorys);
							request.setAttribute("dormitoryCount", dormitoryCount);
//							// 楼区域列表
//							List locationList = studentService.getDiction("6");
//							request.setAttribute("locationList", locationList);
//							// 楼列表
//							List dormitoryList = studentService.getDiction("7");
//							request.setAttribute("dormitoryList", dormitoryList);
							
							dormitoryService.initForm_fdy(request);
							
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
							request.setAttribute("sort", sort);
						} else {
							// =================================================================
							dormitorys = dormitoryService.findfdyDormitorysExport_hlxy(
									args, classlist);
							// Create the Excel File
							String fileName = "student_dormitory_fdy_Info.xls";
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
							columnNames.add(0, "校区");
							columnNames.add(1, "区域");
							columnNames.add(2, "楼号");
							columnNames.add(3, "宿舍号");
							columnNames.add(4, "班级");
							columnNames.add(5, "辅导员");
							columnNames.add(6, "学号");
							columnNames.add(7, "通知书号");							
							columnNames.add(8, "姓名");
							columnNames.add(9, "性别");
							columnNames.add(10, "上海区县");

							for (int i = 0; i < columnNames.size(); i++) {
								HSSFCell cname = row.createCell((short) i);
								cname.setCellStyle(cellHeadStyle);
								cname.setEncoding(HSSFCell.ENCODING_UTF_16);
								cname.setCellValue((String) columnNames.get(i));
							}

							// Populate the Row Data to the SpreadSheet
							int rowCount = dormitorys.size();
							// goal houses the number of cells in the target
							// spreadsheet
							int goal = rowCount * columnNames.size();

							// actual population of target spreadsheet
							int currentCell = 0;

							for (int i = 0; i < rowCount; i++) {
								DormitoryWithAllInfo tableData = (DormitoryWithAllInfo) dormitorys
										.get(i);
								// create row in spreadsheet
								row = sheet1.createRow((short) (i + 1));

								// populate the spreadsheet with the cell
								HSSFCell ctitle = row.createCell((short) 0);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getArea());

								ctitle = row.createCell((short) 1);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getLocation());
								
								ctitle = row.createCell((short) 2);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getDormitory());

								ctitle = row.createCell((short) 3);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getRoomNumber());

								ctitle = row.createCell((short) 4);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getClassNo());

								ctitle = row.createCell((short) 5);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getManagerName());

								ctitle = row.createCell((short) 6);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getStudentNo());

								ctitle = row.createCell((short) 7);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getBirthday());
								
								ctitle = row.createCell((short) 8);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getStuName());

								ctitle = row.createCell((short) 9);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getGender());

								ctitle = row.createCell((short) 10);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getNation());

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
								new ActionMessage(
										"dormitorySearch.loginFirstornotass"));
						saveErrors(request, messages);
						return init4fdySearch(mapping, form, request, response);
					}
				} else {
					messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
							"dormitorySearch.loginFirstornotass"));
					saveErrors(request, messages);
					return init4fdySearch(mapping, form, request, response);
				}
			} else {
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"dormitorySearch.loginFirstornotass"));
				saveErrors(request, messages);
				return init4fdySearch(mapping, form, request, response);
			}

			return mapping.findForward("init4fdySearch_hlxy");
		}else{
			//-------------------------------------------------复旦学院
			HttpSession session = request.getSession(false);
			ActionMessages messages = new ActionMessages();
			DynaActionForm dormForm = (DynaActionForm) form;
			String dormitory = dormForm.get("dorm").toString();
			String roomNumber = dormForm.get("roomNumber").toString();
			String studentNo = dormForm.get("studentNo").toString();
			String stuName = dormForm.get("stuName").toString();
			String gender = dormForm.get("gender").toString();
			String majorin = dormForm.get("majorin").toString();
			String nation = dormForm.get("nation").toString();
			String enterenceNo = dormForm.get("enterenceNo").toString();
			String fromProvince = dormForm.get("fromProvince").toString();
			String location = dormForm.get("location").toString();
			String orderby = request.getParameter("orderby");
			String sort = request.getParameter("sort");
			String offSet = request.getParameter("pager.offset");
			request.setAttribute("mydormitory", dormitory);
			String[] args = { dormitory, roomNumber, studentNo, stuName,gender, majorin,
					nation, fromProvince, location, offSet, orderby, sort,enterenceNo  };
			Account account = null;
			if (session.getAttribute("accountPerson") != null) {
				account = (Account) session.getAttribute("accountPerson");
				String managerNo = account.getPerson().getPersonCode();
				List managerList = managerService.getManagerByNo(managerNo);
				if (managerList.size() > 0) {
					Managermodel Managermodel = (Managermodel) managerList.get(0);
					String managerclass = managerService
							.findManagerclass(Managermodel.getManagerId());
					if (!"".equals(managerclass)) {

						List dormitorys = null;
						Integer dormitoryCount;
						if (request.getParameter("export") == null
								|| "".equals(request.getParameter("export"))) {
							dormitorys = dormitoryService.findfdyDormitorys(args,
									managerclass);
							dormitoryCount = dormitoryService.getfdyDormitoryCount(
									args, managerclass);
							request.setAttribute("dormitorys", dormitorys);
							request.setAttribute("dormitoryCount", dormitoryCount);
//							// 楼区域列表
//							List locationList = studentService.getDiction("6");
//							request.setAttribute("locationList", locationList);
//							// 楼列表
//							List dormitoryList = studentService.getDiction("7");
//							request.setAttribute("dormitoryList", dormitoryList);
							
							dormitoryService.initForm_fdy(request);
							
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
							request.setAttribute("sort", sort);
						} else {
							// =================================================================
							dormitorys = dormitoryService.findfdyDormitorysExport(
									args, managerclass);
							// Create the Excel File
							String fileName = "student_dormitory_fdy_Info.xls";
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
							columnNames.add(0, "校区");
							columnNames.add(1, "楼号");
							columnNames.add(2, "宿舍号");
							columnNames.add(3, "书院");
							columnNames.add(4, "班级");
							columnNames.add(5, "辅导员");
							columnNames.add(6, "学号");
							columnNames.add(7, "通知书号");
							columnNames.add(8, "姓名");
							columnNames.add(9, "性别");
							columnNames.add(10, "专业");
							columnNames.add(11, "生源地");
							columnNames.add(12, "民族");

							for (int i = 0; i < columnNames.size(); i++) {
								HSSFCell cname = row.createCell((short) i);
								cname.setCellStyle(cellHeadStyle);
								cname.setEncoding(HSSFCell.ENCODING_UTF_16);
								cname.setCellValue((String) columnNames.get(i));
							}

							// Populate the Row Data to the SpreadSheet
							int rowCount = dormitorys.size();
							// goal houses the number of cells in the target
							// spreadsheet
							int goal = rowCount * columnNames.size();

							// actual population of target spreadsheet
							int currentCell = 0;

							for (int i = 0; i < rowCount; i++) {
								DormitoryWithAllInfo tableData = (DormitoryWithAllInfo) dormitorys
										.get(i);
								// create row in spreadsheet
								row = sheet1.createRow((short) (i + 1));

								// populate the spreadsheet with the cell
								HSSFCell ctitle = row.createCell((short) 0);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getLocation());

								ctitle = row.createCell((short) 1);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getDormitory());

								ctitle = row.createCell((short) 2);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getRoomNumber());

								ctitle = row.createCell((short) 3);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getCollegeName());

								ctitle = row.createCell((short) 4);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getClassNo());

								ctitle = row.createCell((short) 5);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getManagerName());

								ctitle = row.createCell((short) 6);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getStudentNo());

								ctitle = row.createCell((short) 7);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getBirthday());
								
								ctitle = row.createCell((short) 8);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getStuName());

								ctitle = row.createCell((short) 9);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getGender());

								ctitle = row.createCell((short) 10);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getMajorin());

								ctitle = row.createCell((short) 11);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getFromProvince());

								ctitle = row.createCell((short) 12);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue(tableData.getNation());

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
								new ActionMessage(
										"dormitorySearch.loginFirstornotass"));
						saveErrors(request, messages);
						return init4fdySearch(mapping, form, request, response);
					}
				} else {
					messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
							"dormitorySearch.loginFirstornotass"));
					saveErrors(request, messages);
					return init4fdySearch(mapping, form, request, response);
				}
			} else {
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"dormitorySearch.loginFirstornotass"));
				saveErrors(request, messages);
				return init4fdySearch(mapping, form, request, response);
			}

			return mapping.findForward("init4fdySearch");			
		}
		

	}

	public ActionForward init4Adjust(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
//		// 楼区域列表
//		List locationList = studentService.getDiction("6");
//		request.setAttribute("locationList", locationList);
//		// 楼列表
//		List dormitoryList = studentService.getDiction("7");
//		request.setAttribute("dormitoryList", dormitoryList);
		DynaActionForm adjustForm = (DynaActionForm)form; 
		dormitoryService.initForm(request);	
		List areali = (List)request.getAttribute("areaList");
		if(areali!=null&&areali.size()>0){
			adjustForm.set("area",((Map)areali.get(0)).get("dictValue"));
		}
		// 性别
		List genderList = studentService.getDiction("1");
		request.setAttribute("genderList", genderList);
		
		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院
			//-------------------------------------------------
			request.setAttribute("dormmo", null);
			return mapping.findForward("init4Adjust_hlxy");
		}else if(getrole!=null&&!"".equals(getrole)&&getrole.equals("3")){
			//-------------------------------------------------研工部
			if(areali!=null&&areali.size()>0){
				adjustForm.set("area",((Map)areali.get(0)).get("dictValue"));
				request.setAttribute("area", ((Map)areali.get(0)).get("dictValue"));
				List localli = (List)request.getAttribute("locationList");
				if(localli!=null&&localli.size()>0){
					for(int i=0;i<localli.size();i++){
						if(((Map)localli.get(i)).get("dictParent").equals(((Map)areali.get(0)).get("dictValue"))){
							adjustForm.set("location",((Map)localli.get(i)).get("dictValue"));
							request.setAttribute("location", ((Map)localli.get(i)).get("dictValue"));
							List dormli = (List)request.getAttribute("buildingList");
							for(int j=0;j<dormli.size();j++){
								if(((Map)dormli.get(i)).get("dictParent").equals(((Map)localli.get(0)).get("dictValue"))){
									adjustForm.set("dormitory",((Map)dormli.get(i)).get("dictValue"));
									request.setAttribute("dormitory", ((Map)dormli.get(i)).get("dictValue"));
									break;
								}
							}
							break;
						}
					}
				}
			}
			request.setAttribute("dormmo", null);
			return mapping.findForward("init4Adjust_yg");
		}else{
			//-------------------------------------------------复旦学院
			request.setAttribute("dormmo", null);
			return mapping.findForward("init4Adjust");
		}		
	}
	public ActionForward init4SearchAdjust(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
				DynaActionForm dormForm = (DynaActionForm) form;
				String getrole = request.getParameter("getrole");
				String operator = "";
				if (request.getSession().getAttribute("accountPerson") != null) {
					operator = ((Account) request.getSession().getAttribute(
							"accountPerson")).getPerson().getPersonCode();
				}
				String areaA = "";
				String areaB = "";
				String unitA = "";
				String unitB = "";
				if(dormForm.get("areaA")!=null){
					areaA = dormForm.get("areaA").toString();
				}
				if(dormForm.get("areaB")!=null){
					areaB = dormForm.get("areaB").toString();
				}
				if(dormForm.get("unitA")!=null){
					unitA = dormForm.get("unitA").toString();
				}
				if(dormForm.get("unitB")!=null){
					unitB = dormForm.get("unitB").toString();
				}
				
				String locationA = dormForm.get("locationA").toString();
				String dormitoryA = dormForm.get("dormitoryA").toString();
				String roomNumberA = dormForm.get("roomNumberA").toString();
				String locationB = dormForm.get("locationB").toString();
				String dormitoryB = dormForm.get("dormitoryB").toString();
				String roomNumberB = dormForm.getString("roomNumberB");
				List bindStudentListA = null;
				List bindStudentListB = null;
				String mydormitoryIdA = "";
				String mydormitoryIdB = "";
				
				String[] argsA = { locationA, dormitoryA, roomNumberA,areaA,unitA,getrole,operator };
				String[] argsB = { locationB, dormitoryB, roomNumberB,areaB,unitB,getrole,operator };
				
//				String[] argsA = { locationA, dormitoryA, roomNumberA,areaA,getrole };
//				String[] argsB = { locationB, dormitoryB, roomNumberB,areaB,getrole };

//				// 楼区域列表
//				List locationList = studentService.getDiction("6");
//				request.setAttribute("locationList", locationList);
//				// 楼列表
//				List dormitoryList = studentService.getDiction("7");
//				request.setAttribute("dormitoryList", dormitoryList);
				
				 dormitoryService.initForm(request);
				 
					List arealiA = (List)request.getAttribute("areaList");
					if(arealiA!=null&&arealiA.size()>0){
						dormForm.set("areaA",((Map)arealiA.get(0)).get("dictValue"));
					}
					List arealiB = (List)request.getAttribute("areaList");
					if(arealiB!=null&&arealiB.size()>0){
						dormForm.set("areaB",((Map)arealiB.get(0)).get("dictValue"));
					}
				// 性别
				List genderList = studentService.getDiction("1");
				request.setAttribute("genderList", genderList);
				


				request.setAttribute("getrole", getrole);
				if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院
					//-------------------------------------------------
					String schoolId="0002";
					if (!"".equals(locationA) || !"".equals(dormitoryA)
							|| !"".equals(roomNumberA)) {
						bindStudentListA = dormitoryService.findDormPeoples(argsA,schoolId,request);
						Dormitorymodel dormmo = dormitoryService.getDormitory(areaA,locationA,
								dormitoryA, roomNumberA);
						if (dormmo != null) {
							mydormitoryIdA = dormmo.getDormitoryId();
						}
					}
					if (!"".equals(locationB) || !"".equals(dormitoryB)
							|| !"".equals(roomNumberB)) {
						bindStudentListB = dormitoryService.findDormPeoples(argsB,schoolId,request);
						Dormitorymodel dormmo = dormitoryService.getDormitory(areaB,locationB,
								dormitoryB, roomNumberB);
						if (dormmo != null) {
							mydormitoryIdB = dormmo.getDormitoryId();
						}
					}
					request.setAttribute("bindStudentListA", bindStudentListA);
					request.setAttribute("bindStudentListB", bindStudentListB);
					request.setAttribute("mydormitoryA", dormitoryA);
					request.setAttribute("mydormitoryB", dormitoryB);
					request.setAttribute("mydormitoryIdA", mydormitoryIdA);
					request.setAttribute("mydormitoryIdB", mydormitoryIdB);
					return mapping.findForward("twoDormAdjustList_hlxy");
				}else if(getrole!=null&&!"".equals(getrole)&&getrole.equals("3")){	//研工部
					//-------------------------------------------------
					if(arealiA!=null&&arealiA.size()>0){
						dormForm.set("areaA",((Map)arealiA.get(0)).get("dictValue"));
						request.setAttribute("areaA", ((Map)arealiA.get(0)).get("dictValue"));
						List localliA = (List)request.getAttribute("locationList");
						if(localliA!=null&&localliA.size()>0){
							for(int i=0;i<localliA.size();i++){
								if(((Map)localliA.get(i)).get("dictParent").equals(((Map)arealiA.get(0)).get("dictValue"))){
									dormForm.set("locationA",((Map)localliA.get(i)).get("dictValue"));
									request.setAttribute("locationA", ((Map)localliA.get(i)).get("dictValue"));
									List dormliA = (List)request.getAttribute("buildingList");
									for(int j=0;j<dormliA.size();j++){
										if(((Map)dormliA.get(i)).get("dictParent").equals(((Map)localliA.get(0)).get("dictValue"))){
											dormForm.set("dormitoryA",((Map)dormliA.get(i)).get("dictValue"));
											request.setAttribute("dormitoryA", ((Map)dormliA.get(i)).get("dictValue"));
											break;
										}
									}
									break;
								}
							}
						}
					}
					if(arealiB!=null&&arealiB.size()>0){
						dormForm.set("areaB",((Map)arealiB.get(0)).get("dictValue"));
						request.setAttribute("areaB", ((Map)arealiB.get(0)).get("dictValue"));
						List localliB = (List)request.getAttribute("locationList");
						if(localliB!=null&&localliB.size()>0){
							for(int i=0;i<localliB.size();i++){
								if(((Map)localliB.get(i)).get("dictParent").equals(((Map)arealiA.get(0)).get("dictValue"))){
									dormForm.set("locationB",((Map)localliB.get(i)).get("dictValue"));
									request.setAttribute("locationB", ((Map)localliB.get(i)).get("dictValue"));
									List dormliB = (List)request.getAttribute("buildingList");
									for(int j=0;j<dormliB.size();j++){
										if(((Map)dormliB.get(i)).get("dictParent").equals(((Map)localliB.get(0)).get("dictValue"))){
											dormForm.set("dormitoryB",((Map)dormliB.get(i)).get("dictValue"));
											request.setAttribute("dormitoryB", ((Map)dormliB.get(i)).get("dictValue"));
											break;
										}
									}
									break;
								}
							}
						}
					}
					String schoolId="0003";
					if (!"".equals(locationA) || !"".equals(dormitoryA)
							|| !"".equals(roomNumberA)||!"".equals(areaA)) {
						bindStudentListA = dormitoryService.findDormPeoples(argsA,schoolId,request);
						Dormitorymodel dormmo = dormitoryService.getDormitory(areaA,locationA,
								dormitoryA,unitA,roomNumberA,operator);
						if (dormmo != null) {
							mydormitoryIdA = dormmo.getDormitoryId();
						}
					}
					if (!"".equals(locationB) || !"".equals(dormitoryB)
							|| !"".equals(roomNumberB)||!"".equals(areaB)) {
						bindStudentListB = dormitoryService.findDormPeoples(argsB,schoolId,request);
						Dormitorymodel dormmo = dormitoryService.getDormitory(areaB,locationB,
								dormitoryB,unitB,roomNumberB,operator);
						if (dormmo != null) {
							mydormitoryIdB = dormmo.getDormitoryId();
						}
					}	
					request.setAttribute("bindStudentListA", bindStudentListA);
					request.setAttribute("bindStudentListB", bindStudentListB);
					request.setAttribute("mydormitoryA", dormitoryA);
					request.setAttribute("mydormitoryB", dormitoryB);
					request.setAttribute("mydormitoryIdA", mydormitoryIdA);
					request.setAttribute("mydormitoryIdB", mydormitoryIdB);
					return mapping.findForward("twoDormAdjustList_yg");
				}else{
					//-------------------------------------------------复旦学院
					String schoolId="0001";
					if (!"".equals(locationA) || !"".equals(dormitoryA)
							|| !"".equals(roomNumberA)) {
						bindStudentListA = dormitoryService.findDormPeoples(argsA,schoolId,request);
						Dormitorymodel dormmo = dormitoryService.getDormitory(areaA,locationA,
								dormitoryA, roomNumberA);
						if (dormmo != null) {
							mydormitoryIdA = dormmo.getDormitoryId();
						}
					}
					if (!"".equals(locationB) || !"".equals(dormitoryB)
							|| !"".equals(roomNumberB)) {
						bindStudentListB = dormitoryService.findDormPeoples(argsB,schoolId,request);
						Dormitorymodel dormmo = dormitoryService.getDormitory(areaB,locationB,
								dormitoryB, roomNumberB);
						if (dormmo != null) {
							mydormitoryIdB = dormmo.getDormitoryId();
						}
					}
					request.setAttribute("bindStudentListA", bindStudentListA);
					request.setAttribute("bindStudentListB", bindStudentListB);
					request.setAttribute("mydormitoryA", dormitoryA);
					request.setAttribute("mydormitoryB", dormitoryB);
					request.setAttribute("mydormitoryIdA", mydormitoryIdA);
					request.setAttribute("mydormitoryIdB", mydormitoryIdB);
					return mapping.findForward("twoDormAdjustList");
				}


			}
	public ActionForward init4AdjustHis(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		DynaActionForm adjustForm = (DynaActionForm)form; 
		dormitoryService.initForm(request);
		List areali = (List)request.getAttribute("areaList");
//		if(areali!=null&&areali.size()>0){
//			adjustForm.set("area",((Map)areali.get(0)).get("dictValue"));
//		}
		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院
			//-------------------------------------------------
			return mapping.findForward("init4AdjustHis_hlxy");
		}else if(getrole!=null&&!"".equals(getrole)&&getrole.equals("3")){
			//-------------------------------------------------研工部			
			if(areali!=null&&areali.size()>0){
				adjustForm.set("area",((Map)areali.get(0)).get("dictValue"));
				request.setAttribute("area", ((Map)areali.get(0)).get("dictValue"));
				List localli = (List)request.getAttribute("locationList");
				if(localli!=null&&localli.size()>0){
					for(int i=0;i<localli.size();i++){
						if(((Map)localli.get(i)).get("dictParent").equals(((Map)areali.get(0)).get("dictValue"))){
							adjustForm.set("location",((Map)localli.get(i)).get("dictValue"));
							request.setAttribute("location", ((Map)localli.get(i)).get("dictValue"));
						}
					}
				}
			}
			return mapping.findForward("init4AdjustHis_yg");
		}else{
			//-------------------------------------------------复旦学院
			return mapping.findForward("init4AdjustHis");
		}
		
	}

	public ActionForward init4Add(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		// 楼列表
		List dormitoryList = studentService.getDiction("7");
		request.setAttribute("dormitoryList", dormitoryList);
		// 楼区域列表
		List locationList = studentService.getDiction("6");
		// 性别
		List genderList = studentService.getDiction("1");
		request.setAttribute("genderList", genderList);
		request.setAttribute("locationList", locationList);
		return mapping.findForward("init4Add");
	}

	public ActionForward save(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		DynaActionForm dormForm = (DynaActionForm) form;
		// Extract attributes and parameters we will need
		ActionMessages messages = new ActionMessages();
		if (dormForm.get("dormitory") != null) {
			Dormitorymodel dorm = (Dormitorymodel) dormForm.get("dormitory");
			String location = dorm.getLocation();
			String dormitory = dorm.getDormitory();
			String roomNumber = dorm.getRoomNumber();
			if (dormitoryService.getDormbylocdormandnum(location, dormitory,
					roomNumber) > 0) {
				// 宿舍号重复
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"dormitory.thesameroomnumber", roomNumber));
				saveErrors(request, messages);
				request.setAttribute("mydormitory", dormitory);
				return init4Add(mapping, form, request, response);
			} else {
				try {
					dormitoryService.addDorm(dorm);
					messages.add(ActionMessages.GLOBAL_MESSAGE,
							new ActionMessage("dormitory.roomadded"));
					saveErrors(request, messages);
				} catch (Exception e) {
					messages.add(ActionMessages.GLOBAL_MESSAGE,
							new ActionMessage("dormitory.roomnotadded"));
					saveErrors(request, messages);
					request.setAttribute("mydormitory", dormitory);
					return init4Add(mapping, form, request, response);
				}
			}
		}
		// dormForm.reset(mapping, request);
		removeAttribute(mapping, request);
		// return searchAll(mapping, form, request, response);
		return mapping.findForward("dormitorylistgoto");
	}

	public ActionForward searchAll(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		DynaActionForm dormForm = (DynaActionForm) form;
		Dormitorymodel dorm = (Dormitorymodel) dormForm.get("dormitory");
		String location = dorm.getLocation();
		String dormitory = dorm.getDormitory();
		String roomNumber = dorm.getRoomNumber();
		String gender = dorm.getGender();
		String page = request.getParameter("pager.offset");
		String[] args = { location, dormitory, roomNumber, gender, page };
		request.setAttribute("dorms", dormitoryService.findDormInfo(args));
		request.setAttribute("dormsCount", dormitoryService
				.getDormInfoCount(args));
		request.setAttribute("mydormitory", dormitory);
//		// 楼列表
//		List dormitoryList = studentService.getDiction("7");
//		request.setAttribute("dormitoryList", dormitoryList);
//		// 楼区域列表
//		List locationList = studentService.getDiction("6");
//		request.setAttribute("locationList", locationList);
		dormitoryService.initForm(request);
		// 性别
		List genderList = studentService.getDiction("1");
		request.setAttribute("genderList", genderList);
		return mapping.findForward("searchSuccess");
	}

	public ActionForward revise(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		// 楼列表
		List dormitoryList = studentService.getDiction("7");
		request.setAttribute("dormitoryList", dormitoryList);
		// 楼区域列表
		List locationList = studentService.getDiction("6");
		// 性别
		List genderList = studentService.getDiction("1");
		request.setAttribute("genderList", genderList);
		request.setAttribute("locationList", locationList);
		String id = request.getParameter("dormitoryId");
		DynaActionForm dormForm = (DynaActionForm) form;
		Dormitorymodel dormitorymodel = dormitoryService.getDormByDormId(id);
		dormForm.set("dormitory", dormitorymodel);
		request.setAttribute("mydormitory", dormitorymodel.getDormitory());
		return mapping.findForward("revise");
	}

	public ActionForward submitRevise(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		DynaActionForm dormForm = (DynaActionForm) form;
		// Extract attributes and parameters we will need
		ActionMessages messages = new ActionMessages();
		Dormitorymodel dorm = (Dormitorymodel) dormForm.get("dormitory");
		// String location = dorm.getLocation();
		String dormitory = dorm.getDormitory();
		// String roomNumber = dorm.getRoomNumber();

		try {
			dormitoryService.updateDormitory(dorm);
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"dormitory.roommodified"));
			saveErrors(request, messages);
		} catch (AccomodationNotRightException e) {
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"dormitory.accomodationnotright"));
			saveErrors(request, messages);
			request.setAttribute("mydormitory", dormitory);
			return init4Add(mapping, form, request, response);
		} catch (Exception e) {
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"dormitory.roomnotmodified"));
			saveErrors(request, messages);
			request.setAttribute("mydormitory", dormitory);
			return init4Add(mapping, form, request, response);
		}
		// dormForm.reset(mapping, request);
		removeAttribute(mapping, request);
		return mapping.findForward("dormitorylistgoto");// searchAll(mapping,
		// form, request,
		// response);
	}

	public ActionForward delete(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		String[] deleteX = request.getParameterValues("deleteX");
		// Extract attributes and parameters we will need
		ActionMessages messages = new ActionMessages();
		try {
			dormitoryService.deleteDorm(deleteX);
		} catch (DormitoryHasStuException e) {
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"dormitory.dormhasstu", e.getMessage()));
			saveErrors(request, messages);
			return searchAll(mapping, form, request, response);
		} catch (Exception e) {
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"dormitory.notdeleted"));
			saveErrors(request, messages);
			return searchAll(mapping, form, request, response);
		}
		return searchAll(mapping, form, request, response);
	}

	public ActionForward searchAdjust(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		DynaActionForm dormForm = (DynaActionForm) form;
		String getrole = request.getParameter("getrole");
		String operator = "";
		if (request.getSession().getAttribute("accountPerson") != null) {
			operator = ((Account) request.getSession().getAttribute(
					"accountPerson")).getPerson().getPersonCode();
		}
		String areaA = "";
		String areaB = "";
		String unitA = "";
		String unitB = "";
		if(dormForm.get("areaA")!=null){
			areaA = dormForm.get("areaA").toString();
		}
		if(dormForm.get("areaB")!=null){
			areaB = dormForm.get("areaB").toString();
		}
		if(dormForm.get("unitA")!=null){
			unitA = dormForm.get("unitA").toString();
		}
		if(dormForm.get("unitB")!=null){
			unitB = dormForm.get("unitB").toString();
		}
		
		String locationA = dormForm.get("locationA").toString();
		String dormitoryA = dormForm.get("dormitoryA").toString();
		String roomNumberA = dormForm.get("roomNumberA").toString();
		String locationB = dormForm.get("locationB").toString();
		String dormitoryB = dormForm.get("dormitoryB").toString();
		String roomNumberB = dormForm.getString("roomNumberB");
		List bindStudentListA = null;
		List bindStudentListB = null;
		String mydormitoryIdA = "";
		String mydormitoryIdB = "";
		
		String[] argsA = { locationA, dormitoryA, roomNumberA,areaA,unitA,getrole,operator };
		String[] argsB = { locationB, dormitoryB, roomNumberB,areaB,unitB,getrole,operator };
		
//		String[] argsA = { locationA, dormitoryA, roomNumberA,areaA,getrole };
//		String[] argsB = { locationB, dormitoryB, roomNumberB,areaB,getrole };

//		// 楼区域列表
//		List locationList = studentService.getDiction("6");
//		request.setAttribute("locationList", locationList);
//		// 楼列表
//		List dormitoryList = studentService.getDiction("7");
//		request.setAttribute("dormitoryList", dormitoryList);
		
		 dormitoryService.initForm(request);
		 
			List arealiA = (List)request.getAttribute("areaList");
			if(arealiA!=null&&arealiA.size()>0){
				dormForm.set("areaA",((Map)arealiA.get(0)).get("dictValue"));
			}
			List arealiB = (List)request.getAttribute("areaList");
			if(arealiB!=null&&arealiB.size()>0){
				dormForm.set("areaB",((Map)arealiB.get(0)).get("dictValue"));
			}
		// 性别
		List genderList = studentService.getDiction("1");
		request.setAttribute("genderList", genderList);
		


		request.setAttribute("getrole", getrole);
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院
			//-------------------------------------------------
			String schoolId="0002";
			if (!"".equals(locationA) || !"".equals(dormitoryA)
					|| !"".equals(roomNumberA)) {
				bindStudentListA = dormitoryService.findDormPeoples(argsA,schoolId,request);
				Dormitorymodel dormmo = dormitoryService.getDormitory(areaA,locationA,
						dormitoryA, roomNumberA,operator);
				if (dormmo != null) {
					mydormitoryIdA = dormmo.getDormitoryId();
				}
			}
			if (!"".equals(locationB) || !"".equals(dormitoryB)
					|| !"".equals(roomNumberB)) {
				bindStudentListB = dormitoryService.findDormPeoples(argsB,schoolId,request);
				Dormitorymodel dormmo = dormitoryService.getDormitory(areaB,locationB,
						dormitoryB, roomNumberB,operator);
				if (dormmo != null) {
					mydormitoryIdB = dormmo.getDormitoryId();
				}
			}
			request.setAttribute("bindStudentListA", bindStudentListA);
			request.setAttribute("bindStudentListB", bindStudentListB);
			request.setAttribute("mydormitoryA", dormitoryA);
			request.setAttribute("mydormitoryB", dormitoryB);
			request.setAttribute("mydormitoryIdA", mydormitoryIdA);
			request.setAttribute("mydormitoryIdB", mydormitoryIdB);
			return mapping.findForward("twoDormAdjustList_hlxy");
		}else if(getrole!=null&&!"".equals(getrole)&&getrole.equals("3")){	//研工部
			//-------------------------------------------------

			String schoolId="0003";
			if (!"".equals(locationA) || !"".equals(dormitoryA)
					|| !"".equals(roomNumberA)||!"".equals(areaA)) {
				bindStudentListA = dormitoryService.findDormPeoples(argsA,schoolId,request);
				Dormitorymodel dormmo = dormitoryService.getDormitory(areaA,locationA,
						dormitoryA,unitA,roomNumberA,operator);
				if (dormmo != null) {
					mydormitoryIdA = dormmo.getDormitoryId();
				}
			}
			if (!"".equals(locationB) || !"".equals(dormitoryB)
					|| !"".equals(roomNumberB)||!"".equals(areaB)) {
				bindStudentListB = dormitoryService.findDormPeoples(argsB,schoolId,request);
				Dormitorymodel dormmo = dormitoryService.getDormitory(areaB,locationB,
						dormitoryB,unitB,roomNumberB,operator);
				if (dormmo != null) {
					mydormitoryIdB = dormmo.getDormitoryId();
				}
			}	
			request.setAttribute("bindStudentListA", bindStudentListA);
			request.setAttribute("bindStudentListB", bindStudentListB);
			request.setAttribute("mydormitoryA", dormitoryA);
			request.setAttribute("mydormitoryB", dormitoryB);
			request.setAttribute("mydormitoryIdA", mydormitoryIdA);
			request.setAttribute("mydormitoryIdB", mydormitoryIdB);
			return mapping.findForward("twoDormAdjustList_yg");
		}else{
			//-------------------------------------------------复旦学院
			String schoolId="0001";
			if (!"".equals(locationA) || !"".equals(dormitoryA)
					|| !"".equals(roomNumberA)) {
				bindStudentListA = dormitoryService.findDormPeoples(argsA,schoolId,request);
				Dormitorymodel dormmo = dormitoryService.getDormitory(areaA,locationA,
						dormitoryA, roomNumberA,operator);
				if (dormmo != null) {
					mydormitoryIdA = dormmo.getDormitoryId();
				}
			}
			if (!"".equals(locationB) || !"".equals(dormitoryB)
					|| !"".equals(roomNumberB)) {
				bindStudentListB = dormitoryService.findDormPeoples(argsB,schoolId,request);
				Dormitorymodel dormmo = dormitoryService.getDormitory(areaB,locationB,
						dormitoryB, roomNumberB,operator);
				if (dormmo != null) {
					mydormitoryIdB = dormmo.getDormitoryId();
				}
			}
			request.setAttribute("bindStudentListA", bindStudentListA);
			request.setAttribute("bindStudentListB", bindStudentListB);
			request.setAttribute("mydormitoryA", dormitoryA);
			request.setAttribute("mydormitoryB", dormitoryB);
			request.setAttribute("mydormitoryIdA", mydormitoryIdA);
			request.setAttribute("mydormitoryIdB", mydormitoryIdB);
			return mapping.findForward("twoDormAdjustList");
		}


	}

	public ActionForward searchfdyAdjust(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		
		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院
			//-------------------------------------------------
			HttpSession session = request.getSession(false);
			
			String timespan="";
			timespan=rcvmanageservice.checkTimeUp("080210");
			if(!timespan.equals("")){
				request.setAttribute("timespan",timespan);
				return mapping.findForward("timeup");
			}
			
			DynaActionForm dormForm = (DynaActionForm) form;
			String areaA = dormForm.get("areaA").toString();
			String locationA = dormForm.get("locationA").toString();
			String dormitoryA = dormForm.get("dormitoryA").toString();
			String roomNumberA = dormForm.get("roomNumberA").toString();
			String areaB = dormForm.get("areaB").toString();
			String locationB = dormForm.get("locationB").toString();
			String dormitoryB = dormForm.get("dormitoryB").toString();
			String roomNumberB = dormForm.get("roomNumberB").toString();
			List bindStudentListA = null;
			List bindStudentListB = null;
			String mydormitoryIdA = "";
			String mydormitoryIdB = "";
//			// 楼区域列表
//			List locationList = studentService.getDiction("6");
//			request.setAttribute("locationList", locationList);
//			// 楼列表
//			List dormitoryList = studentService.getDiction("7");
//			request.setAttribute("dormitoryList", dormitoryList);
			dormitoryService.initForm_fdy(request);
			// 性别
			List genderList = studentService.getDiction("1");
			request.setAttribute("genderList", genderList);
			String[] argsA = { locationA, dormitoryA, roomNumberA,areaA };
			ActionMessages messages = new ActionMessages();
			Account account = null;
			if (session.getAttribute("accountPerson") != null) {
				account = (Account) session.getAttribute("accountPerson");
				String managerNo = account.getPerson().getPersonCode();
				List managerList = managerService.getManagerByNo(managerNo);
				if (managerList.size() > 0) {
					Managermodel Managermodel = (Managermodel) managerList.get(0);
					List classlist = managerService
							.findManagerclass_hlxy(Managermodel.getManagerId());
					if (classlist!=null&&classlist.size()>0) {
						if (!"".equals(areaA) || !"".equals(locationA) || !"".equals(dormitoryA)
								|| !"".equals(roomNumberA)) {
							List dormmo = dormitoryService
									.getfdyDormitory_hlxy(areaA,locationA, dormitoryA,
											roomNumberA, classlist);
							if (dormmo != null&&dormmo.size()>0) {
								HashMap map = (HashMap)dormmo.get(0);
								mydormitoryIdA = (String)map.get("dormitoryId");
							} else {
								messages.add(ActionMessages.GLOBAL_MESSAGE,
										new ActionMessage(
												"dormAlert.RoomNotExistorNoright"));
								saveErrors(request, messages);
								return mapping.findForward("twoDormfdyAdjustList_hlxy");
							}
							bindStudentListA = dormitoryService
									.findfdyDormPeoples_hlxy(argsA,"0002",request);
						}
						String[] argsB = { locationB, dormitoryB, roomNumberB,areaB };
						if (!"".equals(locationB) || !"".equals(dormitoryB)
								|| !"".equals(roomNumberB)) {
							List dormmo = dormitoryService
									.getfdyDormitory_hlxy(areaB,locationB, dormitoryB,
											roomNumberB, classlist);
							if (dormmo != null&&dormmo.size()>0) {
								HashMap map = (HashMap)dormmo.get(0);								
								mydormitoryIdB = (String)map.get("dormitoryId");
							} else {
								messages.add(ActionMessages.GLOBAL_MESSAGE,
										new ActionMessage(
												"dormAlert.RoomNotExistorNoright"));
								saveErrors(request, messages);
								return mapping.findForward("twoDormfdyAdjustList_hlxy");
							}
							bindStudentListB = dormitoryService
									.findfdyDormPeoples_hlxy(argsB,"0002",request);
						}
					} else {
						messages.add(ActionMessages.GLOBAL_MESSAGE,
								new ActionMessage("dormAlert.loginFirstornotass"));
						saveErrors(request, messages);
						return mapping.findForward("twoDormfdyAdjustList_hlxy");
					}
				} else {
					messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
							"dormAlert.loginFirstornotass"));
					saveErrors(request, messages);
					return mapping.findForward("twoDormfdyAdjustList_hlxy");
				}
			} else {
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"dormAlert.loginFirstornotass"));
				saveErrors(request, messages);
				return mapping.findForward("twoDormfdyAdjustList_hlxy");
			}
			request.setAttribute("bindStudentListA", bindStudentListA);
			request.setAttribute("bindStudentListB", bindStudentListB);
			request.setAttribute("mydormitoryA", dormitoryA);
			request.setAttribute("mydormitoryB", dormitoryB);
			request.setAttribute("mydormitoryIdA", mydormitoryIdA);
			request.setAttribute("mydormitoryIdB", mydormitoryIdB);
			return mapping.findForward("twoDormfdyAdjustList_hlxy");
		}else{
			//-------------------------------------------------复旦学院
			HttpSession session = request.getSession(false);
			
			String timespan="";
			timespan=rcvmanageservice.checkTimeUp("2016");
			if(!timespan.equals("")){
				request.setAttribute("timespan",timespan);
				return mapping.findForward("timeup");
			} 
			
			DynaActionForm dormForm = (DynaActionForm) form;
			String locationA = dormForm.get("locationA").toString();
			String dormitoryA = dormForm.get("dormitoryA").toString();
			String roomNumberA = dormForm.get("roomNumberA").toString();
			String locationB = dormForm.get("locationB").toString();
			String dormitoryB = dormForm.get("dormitoryB").toString();
			String roomNumberB = dormForm.get("roomNumberB").toString();
			List bindStudentListA = null;
			List bindStudentListB = null;
			String mydormitoryIdA = "";
			String mydormitoryIdB = "";
//			// 楼区域列表
//			List locationList = studentService.getDiction("6");
//			request.setAttribute("locationList", locationList);
//			// 楼列表
//			List dormitoryList = studentService.getDiction("7");
//			request.setAttribute("dormitoryList", dormitoryList);
			
			dormitoryService.initForm_fdy(request);
			
			// 性别
			List genderList = studentService.getDiction("1");
			request.setAttribute("genderList", genderList);
			String[] argsA = { locationA, dormitoryA, roomNumberA };
			ActionMessages messages = new ActionMessages();
			Account account = null;
			if (session.getAttribute("accountPerson") != null) {
				account = (Account) session.getAttribute("accountPerson");
				String managerNo = account.getPerson().getPersonCode();
				List managerList = managerService.getManagerByNo(managerNo);
				if (managerList.size() > 0) {
					Managermodel Managermodel = (Managermodel) managerList.get(0);
					String managerclass = managerService
							.findManagerclass(Managermodel.getManagerId());
					if (!"".equals(managerclass)) {
						if (!"".equals(locationA) || !"".equals(dormitoryA)
								|| !"".equals(roomNumberA)) {
							Dormitorymodel dormmo = dormitoryService
									.getfdyDormitory(locationA, dormitoryA,
											roomNumberA, managerclass);
							if (dormmo != null) {
								mydormitoryIdA = dormmo.getDormitoryId();
							} else {
								messages.add(ActionMessages.GLOBAL_MESSAGE,
										new ActionMessage(
												"dormAlert.RoomNotExistorNoright"));
								saveErrors(request, messages);
								return mapping.findForward("twoDormfdyAdjustList");
							}
							bindStudentListA = dormitoryService
									.findDormPeoples(argsA,"0001",request);
						}
						String[] argsB = { locationB, dormitoryB, roomNumberB };
						if (!"".equals(locationB) || !"".equals(dormitoryB)
								|| !"".equals(roomNumberB)) {
							Dormitorymodel dormmo = dormitoryService
									.getfdyDormitory(locationB, dormitoryB,
											roomNumberB, managerclass);
							if (dormmo != null) {
								mydormitoryIdB = dormmo.getDormitoryId();
							} else {
								messages.add(ActionMessages.GLOBAL_MESSAGE,
										new ActionMessage(
												"dormAlert.RoomNotExistorNoright"));
								saveErrors(request, messages);
								return mapping.findForward("twoDormfdyAdjustList");
							}
							bindStudentListB = dormitoryService
									.findDormPeoples(argsB,"0001",request);
						}
					} else {
						messages.add(ActionMessages.GLOBAL_MESSAGE,
								new ActionMessage("dormAlert.loginFirstornotass"));
						saveErrors(request, messages);
						return mapping.findForward("twoDormfdyAdjustList");
					}
				} else {
					messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
							"dormAlert.loginFirstornotass"));
					saveErrors(request, messages);
					return mapping.findForward("twoDormfdyAdjustList");
				}
			} else {
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"dormAlert.loginFirstornotass"));
				saveErrors(request, messages);
				return mapping.findForward("twoDormfdyAdjustList");
			}
			request.setAttribute("bindStudentListA", bindStudentListA);
			request.setAttribute("bindStudentListB", bindStudentListB);
			request.setAttribute("mydormitoryA", dormitoryA);
			request.setAttribute("mydormitoryB", dormitoryB);
			request.setAttribute("mydormitoryIdA", mydormitoryIdA);
			request.setAttribute("mydormitoryIdB", mydormitoryIdB);
			return mapping.findForward("twoDormfdyAdjustList");
		}

	}

	public ActionForward saveAlert(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {

		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);	
		
		// Extract attributes and parameters we will need
		ActionMessages messages = new ActionMessages();
		String operator = "";
		if (request.getSession().getAttribute("accountPerson") != null) {
			operator = ((Account) request.getSession().getAttribute(
					"accountPerson")).getPerson().getId();
		}

		String bindStudentsA = request.getParameter("bindStudentsA");
		String bindStudentsB = request.getParameter("bindStudentsB");
		String[] tempA = StringUtil.split(bindStudentsA, ",");
		String[] tempB = StringUtil.split(bindStudentsB, ",");
		try {
			dormitoryService.updateTwoDormitory(tempA, tempB, operator,getrole);
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"saveAlert.alertsuccess"));
			saveErrors(request, messages);
		} catch (AccomodationNotEnoughException e) {
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"saveAlert.accomodationnotenough"));
			saveErrors(request, messages);
			searchAdjust(mapping, form, request, response);
		} catch (GenderNotMatchException e) {
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"saveAlert.gendernotmatch"));
			saveErrors(request, messages);
			searchAdjust(mapping, form, request, response);
		} catch (Exception e) {
			e.printStackTrace();
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"saveAlert.savenotsuccess"));
			saveErrors(request, messages);
			searchAdjust(mapping, form, request, response);
		}

		return searchAdjust(mapping, form, request, response);
	}

	public ActionForward savefdyAlert(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {

		
		// Extract attributes and parameters we will need
		ActionMessages messages = new ActionMessages();
		String getrole = request.getParameter("getrole");
		String operator = "";
		if (request.getSession().getAttribute("accountPerson") != null) {
			operator = ((Account) request.getSession().getAttribute(
					"accountPerson")).getPerson().getId();
		}

		String bindStudentsA = request.getParameter("bindStudentsA");
		String bindStudentsB = request.getParameter("bindStudentsB");
		String[] tempA = StringUtil.split(bindStudentsA, ",");
		String[] tempB = StringUtil.split(bindStudentsB, ",");
		try {
			dormitoryService.updateTwoDormitory(tempA, tempB, operator,getrole);
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"saveAlert.alertsuccess"));
			saveErrors(request, messages);
		} catch (AccomodationNotEnoughException e) {
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"saveAlert.accomodationnotenough"));
			saveErrors(request, messages);
			searchfdyAdjust(mapping, form, request, response);
		} catch (GenderNotMatchException e) {
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"saveAlert.gendernotmatch"));
			saveErrors(request, messages);
			searchfdyAdjust(mapping, form, request, response);
		} catch (Exception e) {
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"saveAlert.savenotsuccess"));
			saveErrors(request, messages);
			searchfdyAdjust(mapping, form, request, response);
		}

		return searchfdyAdjust(mapping, form, request, response);
	}

	public ActionForward searchPeopleAdjust(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		DynaActionForm dormForm = (DynaActionForm) form;
		// Extract attributes and parameters we will need
		ActionMessages messages = new ActionMessages();
		String stuNo = dormForm.get("stuNo").toString();
		String stuName = dormForm.get("stuName").toString();
		String gender = dormForm.get("gender").toString();
		String operator = "";
		if (request.getSession().getAttribute("accountPerson") != null) {
			operator = ((Account) request.getSession().getAttribute(
					"accountPerson")).getPerson().getPersonCode();
		}
		String area = "";
		String unit = "";
		if(dormForm.get("area")!=null&&!"".equals(dormForm.get("area"))){
		area = dormForm.get("area").toString();
		}
		if(dormForm.get("unit")!=null&&!"".equals(dormForm.get("unit"))){
			unit = dormForm.get("unit").toString();
		}
		String location = "";
		String dormitory = "";
		String roomNumber = "";
		if(dormForm.get("location")!=null&&!"".equals(dormForm.get("location"))){
			location = dormForm.get("location").toString();
		}
		if(dormForm.get("dormitory")!=null&&!"".equals(dormForm.get("dormitory"))){		
			dormitory = dormForm.get("dormitory").toString();
		}
		if(dormForm.get("roomNumber")!=null&&!"".equals(dormForm.get("roomNumber"))){		
			roomNumber = dormForm.get("roomNumber").toString();
		}
		
		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院
			//-------------------------------------------------
			
			String[] args = { stuNo, stuName, gender };
			String schoolId = "0002";
			request.setAttribute("unbindStudentList", dormitoryService
					.findAdjustPeoples(args,schoolId));
			// 处理要调整到的宿舍
			List bindStudentList = null;
			String mydormitoryId = "";
			String[] argsNew = { location, dormitory, roomNumber,area };
			if (!"".equals(location) && !"".equals(dormitory)
					&& !"".equals(roomNumber)&& !"".equals(area)) {
				Dormitorymodel dormmo = dormitoryService.getDormitory(area,location,
						dormitory, roomNumber,operator);
				request.setAttribute("dormmo", dormmo);
				if (dormmo != null) {
					mydormitoryId = dormmo.getDormitoryId();
				} else {
					messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
							"dormAlert.targetRoomNotExist"));
					saveErrors(request, messages);
					init4Adjust(mapping, form, request, response);
				}
				bindStudentList = dormitoryService.findDormPeoples(argsNew,schoolId,request);

			}

			request.setAttribute("mydormitoryId", mydormitoryId);
			request.setAttribute("bindStudentList", bindStudentList);
			request.setAttribute("mydormitory", dormitory);
//			// 楼区域列表
//			List locationList = studentService.getDiction("6");
//			request.setAttribute("locationList", locationList);
//			// 楼列表
//			List dormitoryList = studentService.getDiction("7");
//			request.setAttribute("dormitoryList", dormitoryList);
			
			dormitoryService.initForm(request);
			
			
			
			// 性别
			List genderList = studentService.getDiction("1");
			request.setAttribute("genderList", genderList);
			return mapping.findForward("init4Adjust_hlxy");
		}else if(getrole!=null&&!"".equals(getrole)&&getrole.equals("3")){
			//-------------------------------------------------研工部
			String[] args = { stuNo, stuName, gender, getrole,operator };
			String schoolId = "0003";
			request.setAttribute("unbindStudentList", dormitoryService
					.findAdjustPeoples(args,schoolId));
			// 处理要调整到的宿舍
			List bindStudentList = null;
			String mydormitoryId = "";
			String[] argsNew = { location, dormitory, roomNumber,area,unit,getrole,operator};
			if (!"".equals(area) &&!"".equals(location) && !"".equals(dormitory)
					&& !"".equals(roomNumber)&&!"".equals(unit)) {
				Dormitorymodel dormmo = dormitoryService.getDormitory(area,location,
						dormitory,unit,roomNumber,operator);
				
				request.setAttribute("dormmo", dormmo);
				if (dormmo != null) {
					mydormitoryId = dormmo.getDormitoryId();
				} else {
					messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
							"dormAlert.targetRoomNotExist"));
					saveErrors(request, messages);
					init4Adjust(mapping, form, request, response);
				}
				bindStudentList = dormitoryService.findDormPeoples(argsNew,schoolId,request);
			}

			request.setAttribute("mydormitoryId", mydormitoryId);
			request.setAttribute("bindStudentList", bindStudentList);
			request.setAttribute("mydormitory", dormitory);
//			// 楼区域列表
//			List locationList = studentService.getDiction("6");
//			request.setAttribute("locationList", locationList);
//			// 楼列表
//			List dormitoryList = studentService.getDiction("7");
//			request.setAttribute("dormitoryList", dormitoryList);
			
			dormitoryService.initForm(request);

			
			
			// 性别
			List genderList = studentService.getDiction("1");

			request.setAttribute("genderList", genderList);
			return mapping.findForward("searchAdjust_yg");	
		}else{
			//-------------------------------------------------复旦学院
			String[] args = { stuNo, stuName, gender };
			String schoolId = "0001";
			List li = dormitoryService.findAdjustPeoples(args,schoolId);
			request.setAttribute("unbindStudentList", li);
			
			// 处理要调整到的宿舍
			List bindStudentList = null;
			String mydormitoryId = "";
			String[] argsNew = { location, dormitory, roomNumber,area };
			if (!"".equals(location) && !"".equals(dormitory)
					&& !"".equals(roomNumber)) {
				Dormitorymodel dormmo = dormitoryService.getDormitory(area,location,
						dormitory, roomNumber,operator);
				request.setAttribute("dormmo", dormmo);
				if (dormmo != null) {
					mydormitoryId = dormmo.getDormitoryId();
				} else {
					messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
							"dormAlert.targetRoomNotExist"));
					saveErrors(request, messages);
					init4Adjust(mapping, form, request, response);
				}
				bindStudentList = dormitoryService.findDormPeoples(argsNew,schoolId,request);

			}

			request.setAttribute("mydormitoryId", mydormitoryId);
			request.setAttribute("bindStudentList", bindStudentList);
			request.setAttribute("mydormitory", dormitory);
//			// 楼区域列表
//			List locationList = studentService.getDiction("6");
//			request.setAttribute("locationList", locationList);
//			// 楼列表
//			List dormitoryList = studentService.getDiction("7");
//			request.setAttribute("dormitoryList", dormitoryList);
			
			dormitoryService.initForm(request);
			
			
			
			// 性别
			List genderList = studentService.getDiction("1");
			request.setAttribute("genderList", genderList);
			return mapping.findForward("searchAdjust");		
		}
		
		

		
	}

	public ActionForward savePeopleAlert(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		
		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);		
		
		// Extract attributes and parameters we will need
		ActionMessages messages = new ActionMessages();
		String operator = "";
		if (request.getSession().getAttribute("accountPerson") != null) {
			operator = ((Account) request.getSession().getAttribute(
					"accountPerson")).getPerson().getId();
		}
		// String Location = request.getParameter("location");
		// String Dormitory = request.getParameter("dormitory");
		// String Room = request.getParameter("room");
		String bindStudents = request.getParameter("bindStudents");
		String unbindStudents = request.getParameter("unbindStudents");
		String[] temp = StringUtil.split(bindStudents, ",");
		String[] untemp = StringUtil.split(unbindStudents, ",");
		try {
			dormitoryService.updateDormitoryPeople(temp, untemp, operator,getrole);
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"saveAlert.alertsuccess"));
			saveErrors(request, messages);
		} catch (AccomodationNotEnoughException e) {
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"saveAlert.accomodationnotenough"));
			saveErrors(request, messages);
			searchPeopleAdjust(mapping, form, request, response);
		} catch (DormitoryHasnotbindedException e) {
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"saveAlert.dormitoryhasnotbinded"));
			saveErrors(request, messages);
			searchPeopleAdjust(mapping, form, request, response);
		} catch (GenderNotMatchException e) {
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"saveAlert.gendernotmatch"));
			saveErrors(request, messages);
			searchPeopleAdjust(mapping, form, request, response);
		} catch (Exception e) {
			e.printStackTrace();
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"saveAlert.savenotsuccess"));
			saveErrors(request, messages);
			searchPeopleAdjust(mapping, form, request, response);
		}

		return searchPeopleAdjust(mapping, form, request, response);
	}

	public ActionForward alertHisSearch(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		
		dormitoryService.initForm(request);
		
		String area = request.getParameter("area");		
		String location = request.getParameter("location");	
		String unit = request.getParameter("unit");	
		String stuNo = request.getParameter("stuNo");
		String roomNo = request.getParameter("roomNumber");
		String dormNo = request.getParameter("dormitory");
		
		String startTime = request.getParameter("startDate");
		String endTime = request.getParameter("endDate");
		String page = request.getParameter("pager.offset");

		// 起始页
		String offset = request.getParameter("pager.offset");
		if (offset == null) {
			offset = "0";
		}
		String order = request.getParameter("horder");
		String odr = "asc";
		if (order != null && order.length() > 0 && order.equals("d"))
			odr = "desc";
		String orderby = request.getParameter("horderby");

		String args[] = { stuNo, roomNo, dormNo, startTime, endTime, location,
				page, orderby, odr,area,unit };
		List his = null;
		

		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院
			//-------------------------------------------------
			String schoolId = "0002";
			if (request.getParameter("export") == null
					|| "".equals(request.getParameter("export"))) {
				request.setAttribute("mydormitory", dormNo);
				his = dormitoryService.searchAlertHis(args,request,schoolId);
				List resultList = new ArrayList();
				if (his != null && his.size() != 0) {
					// 起始页设置
					if (offset.equals("0"))
						resultList = his;
					else if ((Integer.parseInt(offset)) < his.size()
							|| (Integer.parseInt(offset)) == his.size())
						resultList = his.subList((Integer.parseInt(offset)), his
								.size());

				}
				// Integer hisCount = dormitoryService.getHisCount(args);
				request.setAttribute("alertHis", resultList);
				request.setAttribute("hisCount", new Integer(his.size()));
				request.setAttribute("order", order);
				return mapping.findForward("init4AdjustHis_hlxy");
			} else {
				// =================================================================
				his = dormitoryService.searchAlertHisExport(args,request,schoolId);
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
				columnNames.add(1, "姓名");
				columnNames.add(2, "原校区");
				columnNames.add(3, "原区域");
				columnNames.add(4, "原楼号");
				columnNames.add(5, "原宿舍号");
				columnNames.add(6, "原班级");
				columnNames.add(7, "新校区");
				columnNames.add(8, "新区域");
				columnNames.add(9, "新楼号");
				columnNames.add(10, "新宿舍号");
				columnNames.add(11, "新班级");
				columnNames.add(12, "操作员");
				columnNames.add(13, "操作时间");

				for (int i = 0; i < columnNames.size(); i++) {
					HSSFCell cname = row.createCell((short) i);
					cname.setCellStyle(cellHeadStyle);
					cname.setEncoding(HSSFCell.ENCODING_UTF_16);
					cname.setCellValue((String) columnNames.get(i));
				}

				// Populate the Row Data to the SpreadSheet
				int rowCount = his.size();
				// goal houses the number of cells in the target spreadsheet
				int goal = rowCount * columnNames.size();

				// actual population of target spreadsheet
				int currentCell = 0;

				for (int i = 0; i < rowCount; i++) {
					DormitoryHisWithAllInfo tableData = (DormitoryHisWithAllInfo) his
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
					ctitle.setCellValue(tableData.getOarea());

					ctitle = row.createCell((short) 3);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getOlocation());

					ctitle = row.createCell((short) 4);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getOdorm());

					ctitle = row.createCell((short) 5);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getOroom());

					ctitle = row.createCell((short) 6);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getOclassNo());

					ctitle = row.createCell((short) 7);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getNarea());
					
					ctitle = row.createCell((short) 8);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getNlocation());

					ctitle = row.createCell((short) 9);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getNdorm());

					ctitle = row.createCell((short) 10);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getNroom());

					ctitle = row.createCell((short) 11);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getNclassNo());

					ctitle = row.createCell((short) 12);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getOpId());

					ctitle = row.createCell((short) 13);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getChangeTime());

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
		}else if(getrole!=null&&!"".equals(getrole)&&getrole.equals("3")){//研工部
			//-------------------------------------------------
			String schoolId = "0003";
			if (request.getParameter("export") == null
					|| "".equals(request.getParameter("export"))) {
				request.setAttribute("mydormitory", dormNo);
				his = dormitoryService.searchAlertHis(args,request,schoolId);
				
				List resultList = new ArrayList();
				if (his != null && his.size() != 0) {
					// 起始页设置
					if (offset.equals("0"))
						resultList = his;
					else if ((Integer.parseInt(offset)) < his.size()
							|| (Integer.parseInt(offset)) == his.size())
						resultList = his.subList((Integer.parseInt(offset)), his
								.size());

				}
				// Integer hisCount = dormitoryService.getHisCount(args);
				request.setAttribute("alertHis", resultList);
				request.setAttribute("hisCount", new Integer(his.size()));
				request.setAttribute("order", order);
				return mapping.findForward("init4AdjustHis_yg");
			} else{
				// =================================================================
				his = dormitoryService.searchAlertHisExport(args,request,schoolId);
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
				columnNames.add(1, "姓名");
				columnNames.add(2, "原校区");
				columnNames.add(3, "原区域");
				columnNames.add(4, "原楼号");
				columnNames.add(5, "原单元");
				columnNames.add(6, "原宿舍号");

				columnNames.add(7, "新校区");
				columnNames.add(8, "新区域");
				columnNames.add(9, "新楼号");
				columnNames.add(10, "新单元");
				columnNames.add(11, "新宿舍号");

				columnNames.add(12, "操作员");
				columnNames.add(13, "操作时间");

				for (int i = 0; i < columnNames.size(); i++) {
					HSSFCell cname = row.createCell((short) i);
					cname.setCellStyle(cellHeadStyle);
					cname.setEncoding(HSSFCell.ENCODING_UTF_16);
					cname.setCellValue((String) columnNames.get(i));
				}

				// Populate the Row Data to the SpreadSheet
				int rowCount = his.size();
				// goal houses the number of cells in the target spreadsheet
				int goal = rowCount * columnNames.size();

				// actual population of target spreadsheet
				int currentCell = 0;

				for (int i = 0; i < rowCount; i++) {
					DormitoryHisWithAllInfo tableData = (DormitoryHisWithAllInfo) his
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
					ctitle.setCellValue(tableData.getOarea());

					ctitle = row.createCell((short) 3);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getOlocation());

					ctitle = row.createCell((short) 4);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getOdorm());

					ctitle = row.createCell((short) 5);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getOunit());
					
					ctitle = row.createCell((short) 6);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getOroom());



					ctitle = row.createCell((short) 7);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getNarea());
					
					ctitle = row.createCell((short) 8);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getNlocation());

					ctitle = row.createCell((short) 9);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getNdorm());

					ctitle = row.createCell((short) 11);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getNunit());
					
					ctitle = row.createCell((short) 10);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getNroom());



					ctitle = row.createCell((short) 12);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getOpId());

					ctitle = row.createCell((short) 13);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getChangeTime());

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
				request.setAttribute("mydormitory", dormNo);
				his = dormitoryService.searchAlertHis(args,request,schoolId);
				List resultList = new ArrayList();
				if (his != null && his.size() != 0) {
					// 起始页设置
					if (offset.equals("0"))
						resultList = his;
					else if ((Integer.parseInt(offset)) < his.size()
							|| (Integer.parseInt(offset)) == his.size())
						resultList = his.subList((Integer.parseInt(offset)), his
								.size());

				}
				// Integer hisCount = dormitoryService.getHisCount(args);
				request.setAttribute("alertHis", resultList);
				request.setAttribute("hisCount", new Integer(his.size()));
				request.setAttribute("order", order);
				return mapping.findForward("searchHisOver");
			} else {
				// =================================================================
				his = dormitoryService.searchAlertHisExport(args,request,schoolId);
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
				columnNames.add(1, "姓名");
				columnNames.add(2, "原校区");
				columnNames.add(3, "原楼号");
				columnNames.add(4, "原宿舍号");
				columnNames.add(5, "原班级");
				columnNames.add(6, "新校区");
				columnNames.add(7, "新楼号");
				columnNames.add(8, "新宿舍号");
				columnNames.add(9, "新班级");
				columnNames.add(10, "操作员");
				columnNames.add(11, "操作时间");

				for (int i = 0; i < columnNames.size(); i++) {
					HSSFCell cname = row.createCell((short) i);
					cname.setCellStyle(cellHeadStyle);
					cname.setEncoding(HSSFCell.ENCODING_UTF_16);
					cname.setCellValue((String) columnNames.get(i));
				}

				// Populate the Row Data to the SpreadSheet
				int rowCount = his.size();
				// goal houses the number of cells in the target spreadsheet
				int goal = rowCount * columnNames.size();

				// actual population of target spreadsheet
				int currentCell = 0;

				for (int i = 0; i < rowCount; i++) {
					DormitoryHisWithAllInfo tableData = (DormitoryHisWithAllInfo) his
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
					ctitle.setCellValue(tableData.getOlocation());

					ctitle = row.createCell((short) 3);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getOdorm());

					ctitle = row.createCell((short) 4);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getOroom());

					ctitle = row.createCell((short) 5);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getOclassNo());

					ctitle = row.createCell((short) 6);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getNlocation());

					ctitle = row.createCell((short) 7);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getNdorm());

					ctitle = row.createCell((short) 8);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getNroom());

					ctitle = row.createCell((short) 9);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getNclassNo());

					ctitle = row.createCell((short) 10);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getOpId());

					ctitle = row.createCell((short) 11);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getChangeTime());

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

	public ActionForward showDormStat(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		List dormStat = dormitoryService.getDormStat(request);
		List notcheckindormStat=dormitoryService.getNotcheckinDormStat(request);
		if(notcheckindormStat!=null&&notcheckindormStat.size()>0){
			DormitoryStatistic ds=(DormitoryStatistic)notcheckindormStat.get(notcheckindormStat.size()-1);
			request.setAttribute("notcheckindormSum",new Integer(ds.getStudentInCount()));
		}
		Integer dormStatCount = dormitoryService.getDormStatCount(request);
		request.setAttribute("dormStat", dormStat);
		request.setAttribute("notcheckindormStat", notcheckindormStat);
		request.setAttribute("dormStatCount", dormStatCount);
		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院
			//-------------------------------------------------
			return mapping.findForward("dormStat_hlxy");
		}else if(getrole!=null&&!"".equals(getrole)&&getrole.equals("3")){ //研工
			return mapping.findForward("dormStat_yg");
		}else{
			//-------------------------------------------------复旦学院
			return mapping.findForward("dormStat");
		}
	}

	public ActionForward showRoomStat(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		List roomStat = null;
		String area = request.getParameter("Area");
		String dorm = request.getParameter("Dorm");
		String location = request.getParameter("Location");
		String cw = request.getParameter("cw");
		String yzrs = request.getParameter("yzrs");
		String kxcw = request.getParameter("kxcw");
		request.setAttribute("cw", cw);
		request.setAttribute("yzrs", yzrs);
		request.setAttribute("kxcw", kxcw);
		request.setAttribute("area", area);
		request.setAttribute("dorm", dorm);
		request.setAttribute("location", location);		
		
		String getrole = request.getParameter("getrole");
		request.setAttribute("getrole", getrole);		
		if(getrole!=null&&!"".equals(getrole)&&getrole.equals("2")){//护理学院
			//-------------------------------------------------
			roomStat = dormitoryService.getDormStat(dorm, location,area,request);
			Integer roomStatCount = dormitoryService.getDormStatCount(dorm,
					location,area,request);
			request.setAttribute("roomStat", roomStat);
			request.setAttribute("roomStatCount", roomStatCount);
			
			String dormInfo="";
			dormInfo=dormitoryService.getDormInfo(dorm, location,area);
			request.setAttribute("dormInfo",dormInfo);
			return mapping.findForward("roomStat_hlxy");
		}else if(getrole!=null&&!"".equals(getrole)&&getrole.equals("3")){ //研工
			roomStat = dormitoryService.getDormStatyg(dorm, location,area,request);
			Integer roomStatCount = dormitoryService.getDormStatCountyg(dorm,
					location,area,request);
			request.setAttribute("roomStat", roomStat);
			request.setAttribute("roomStatCount", roomStatCount);
			
			String dormInfo="";
			dormInfo=dormitoryService.getDormInfo(dorm, location,area);
			request.setAttribute("dormInfo",dormInfo);
			return mapping.findForward("roomStat_yg");
		}else{
			//-------------------------------------------------复旦学院
			roomStat = dormitoryService.getDormStat(dorm, location,request);
			Integer roomStatCount = dormitoryService.getDormStatCount(dorm,
					location,request);
			request.setAttribute("roomStat", roomStat);
			request.setAttribute("roomStatCount", roomStatCount);
			
			String dormInfo="";
			dormInfo=dormitoryService.getDormInfo(dorm, location);
			request.setAttribute("dormInfo",dormInfo);
			return mapping.findForward("roomStat");
		}		

	}
	
	public ActionForward showNotCheckinRoomStat(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		List roomStat = null;
		List notcheckinroomStat=null;
		String area = request.getParameter("Area");
		String dorm = request.getParameter("Dorm");
		String location = request.getParameter("Location");
		
		request.setAttribute("area", area);
		request.setAttribute("dorm", dorm);
		request.setAttribute("location", location);		
				
			//-------------------------------------------------复旦学院
			//roomStat = dormitoryService.getDormStat(dorm, location,request);
			notcheckinroomStat=dormitoryService.getNotCheckinDormStat(dorm, location,request);
			//Integer roomStatCount = dormitoryService.getDormStatCount(dorm,
			//		location,request);
			//request.setAttribute("roomStat", roomStat);
			//request.setAttribute("roomStatCount", roomStatCount);
			request.setAttribute("notcheckinroomStat", notcheckinroomStat);
			int totalNum=0;
			int inNum=0;
			int nonNum=0;
			int notcheckinNum=0;
			if(notcheckinroomStat!=null&&notcheckinroomStat.size()>0){
				for(int i=0;i<notcheckinroomStat.size();i++){
					Map notcheckinroom=(Map)notcheckinroomStat.get(i);
					totalNum=totalNum+((Integer)notcheckinroom.get("totalNum")).intValue();
					inNum=inNum+((Integer)notcheckinroom.get("allotNum")).intValue();
					nonNum=nonNum+((Integer)notcheckinroom.get("nonNum")).intValue();
					notcheckinNum=notcheckinNum+((Integer)notcheckinroom.get("notcheckinNum")).intValue();
				}
			}
			request.setAttribute("cw", String.valueOf(totalNum));
			request.setAttribute("yzrs", String.valueOf(inNum));
			request.setAttribute("kxcw", String.valueOf(nonNum));
			request.setAttribute("wbdcw", String.valueOf(notcheckinNum));
			
			String dormInfo="";
			dormInfo=dormitoryService.getDormInfo(dorm, location);
			request.setAttribute("dormInfo",dormInfo);
			return mapping.findForward("notcheckinroomStat");
				

	}

	public void setCollegeService(CollegeService collegeService) {
		this.collegeService = collegeService;
	}

	public void setClassService(ClassService classService) {
		this.classService = classService;
	}

	public void setManagerService(ManagerService managerService) {
		this.managerService = managerService;
	}

	public ActionForward importDormitoryFile(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) {
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
			try {
				InputStream is;
				is = file.getInputStream(); // 把文件读入
				List dormList = reloadSpreadsheetModel(is);
				if (dormList == null) {
					messages.add(ActionMessages.GLOBAL_MESSAGE,
							new ActionMessage("dormitory.empty"));
				} else if (dormList.size() > 0) {
					dormitoryService.addConvertDorm(dormList);
					messages.add(ActionMessages.GLOBAL_MESSAGE,
							new ActionMessage("dormitory.importsuccess"));
				}

			} catch (StudentAlreadyInDormException e) {
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"student.alreadyindorm"));
			} catch (LocationNotExistException e) {
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"dormitory.locationnotexist"));

			} catch (DormitoryNotExistException e) {
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"dormitory.dormitorynotexist"));
			} catch (GenderNotExistException e) {
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"dormitory.gendernotexist"));
			} catch (FileNotFoundException e) {
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"dormitory.fileError"));
			} catch (IOException e) {
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"dormitory.ioError"));
			} catch (Exception e) {
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"dormitory.ioError"));
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
			if (colCount < 7) {
				return null;
			}
			for (int i = 1; i < rowCount; i++) {

				HSSFRow row = sheet.getRow(i);

				ArrayList list = new ArrayList();
				list.add(row.getCell((short) 0).getStringCellValue());
				list.add(row.getCell((short) 1).getStringCellValue());
				list.add(String.valueOf(row.getCell((short) 2)
						.getNumericCellValue()));
				list.add(row.getCell((short) 3).getStringCellValue());
				list.add(String.valueOf(row.getCell((short) 4)
						.getNumericCellValue()));
				list.add(String.valueOf(row.getCell((short) 5)
						.getNumericCellValue()));
				if (row.getCell((short) 6) != null) {
					list.add(String.valueOf(row.getCell((short) 6)
							.getNumericCellValue()));
				} else {
					list.add("");
				}

				result.add(list);
			}

			return result;

		} catch (Exception e) {
			System.out.println("A POI error has occured.");
			e.printStackTrace();
			return null;
		}
	}

	/**
	 * 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward loadAllDormitory(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {

		return mapping.findForward("listAllDorm");
	}

	public ActionForward loadAllMajorin(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {

		return mapping.findForward("listAllMajorin");
	}

	/**
	 * 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward getXMLMenuTree(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		String menuTree = dormitoryService.getXmlMenuTree();

		request.setAttribute("menuTree", menuTree);

		return mapping.findForward("success");
	}

	public ActionForward getMajorinXMLMenuTree(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		String menuTree = dormitoryService.getMajorinXmlMenuTree();

		request.setAttribute("menuTree", menuTree);

		return mapping.findForward("success");
	}

}
