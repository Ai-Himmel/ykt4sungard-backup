package org.king.yangong.dormitorymanage.web.action;

import java.io.IOException;
import java.io.OutputStream;
import java.io.UnsupportedEncodingException;
import java.sql.Date;
import java.sql.Time;
import java.sql.Timestamp;
import java.util.ArrayList;
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
import org.king.classmanage.domain.MenuTime;
import org.king.classmanage.service.ClassService;
import org.king.dormitorymanage.exception.DormitoryNotEnoughException;
import org.king.dormitorymanage.exception.StudentAlreadyInDormException;
import org.king.dormitorymanage.web.help.DormitoryWithAllInfo;
import org.king.framework.web.action.BaseAction;
import org.king.rcvmanage.service.RcvmanageService;
import org.king.security.domain.Account;
import org.king.utils.DateUtil;
import org.king.yangong.dormitorymanage.domain.YxGraduate;
import org.king.yangong.dormitorymanage.service.DormTypeManageService;
import org.king.yangong.dormitorymanage.service.YxGraduateService;
import org.king.quarters.domain.TabSsDept;

public class YxGraduateAction extends BaseAction {
	
	private YxGraduateService yxGraduateService;

	public void setYxGraduateService(YxGraduateService yxGraduateService) {
		this.yxGraduateService = yxGraduateService;
	}
	
	private DormTypeManageService dormTypeManageService;

	public void setDormTypeManageService(DormTypeManageService dormTypeManageService) {
		this.dormTypeManageService = dormTypeManageService;
	}
	
	private ClassService classService;
	
	public void setClassService(ClassService classService) {
		this.classService = classService;
	}

	public ActionForward load4Search(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		// ѧ�����
		List studentTypeList = yxGraduateService.getStudentTypeList();
		request.setAttribute("studentTypeList", studentTypeList);
		// ������ʽ
		List styleList = yxGraduateService.getStyleList();
		request.setAttribute("styleList", styleList);
		// ¼ȡԺϵ
		List collegeList = yxGraduateService.getCollegeListFromGraduateTable();
		request.setAttribute("collegeList", collegeList);
		// רҵ
		List specialityList = yxGraduateService.getSpecialityList();
		request.setAttribute("specialityList", specialityList);
		// �о�������
		List TypeList = yxGraduateService.getTypeList();
		request.setAttribute("TypeList", TypeList);
		return mapping.findForward("load4Search");
	}

	public ActionForward load4List(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession();
		ActionMessages messages = new ActionMessages();
		DynaActionForm graduateForm = (DynaActionForm) form;
		YxGraduate yxgraduate = (YxGraduate) graduateForm.get("YxGraduate");
		String startfrom = graduateForm.getString("startfrom");
		String page = request.getParameter("pager.offset");
		String lengthofschool =graduateForm.getString("lengthofschool");
		String graduateNoSearch1 = graduateForm.getString("graduateNoSearch1");
		String graduateNoSearch2 = graduateForm.getString("graduateNoSearch2");
		
		String[] args = { startfrom, page,graduateNoSearch1,graduateNoSearch2,lengthofschool,"" };
		// ѧ�����
		Account account = null;
		if (session.getAttribute("accountPerson") != null) {
			List studentTypeList = yxGraduateService.getStudentTypeList();
			request.setAttribute("studentTypeList", studentTypeList);
			// ������ʽ
			List styleList = yxGraduateService.getStyleList();
			request.setAttribute("styleList", styleList);
			// ¼ȡԺϵ
			List collegeList = yxGraduateService.getCollegeListFromGraduateTable();
			request.setAttribute("collegeList", collegeList);
			// רҵ
			List specialityList = yxGraduateService.getSpecialityList();
			request.setAttribute("specialityList", specialityList);
			// �о�������
			List TypeList = yxGraduateService.getTypeList();
			request.setAttribute("TypeList", TypeList);
			account = (Account) session.getAttribute("accountPerson");
			String stuemp_no = account.getPerson().getPersonCode();
			args[5] = stuemp_no;
			List yxgraduates = yxGraduateService.getGraduatesList(yxgraduate, args);
			Integer yxgraduatesCount = yxGraduateService.getGraduatesListCount(yxgraduate, args);
			request.setAttribute("yxgraduates", yxgraduates);
			request.setAttribute("graduateCount", yxgraduatesCount);
		} else {
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"classAlert.loginFirstornotass"));
			saveErrors(request, messages);
			return mapping.findForward("load4ResidentSearch");
		}
		return mapping.findForward("load4Search");
	}

	public ActionForward update(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		DynaActionForm graduateForm = (DynaActionForm) form;
		String newGraduateType = graduateForm.getString("newGraduateType");
		String newlengthofschool = graduateForm.getString("newlengthofschool");

		String[] args = { newGraduateType, newlengthofschool };
		String[] deleteX = request.getParameterValues("deleteX");
		ActionMessages messages = new ActionMessages();
		// ѧ�����
		try {
			yxGraduateService.updateGraduates(deleteX, args);
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
			"graduate.updatesuccess"));
	       saveErrors(request, messages);
		} catch (Exception e) {
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"graduate.updatefailue"));
			saveErrors(request, messages);
		}

		return mapping.findForward("updateSucc");
//		return load4List(mapping, form, request, response);
	}

	public ActionForward load4ResidentSearch(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		HttpSession session = request.getSession();
		ActionMessages messages = new ActionMessages();

		Account account = null;
		if (session.getAttribute("accountPerson") != null) {
			// ѧ�����
			List studentTypeList = yxGraduateService.getStudentTypeList();
			request.setAttribute("studentTypeList", studentTypeList);
			// ������ʽ
			List styleList = yxGraduateService.getStyleList();
			request.setAttribute("styleList", styleList);
			// ¼ȡԺϵ
			List collegeList = yxGraduateService
					.getCollegeListFromGraduateTable();
			request.setAttribute("collegeList", collegeList);
			// רҵ
			List specialityList = yxGraduateService.getSpecialityList();
			request.setAttribute("specialityList", specialityList);
			// �о�������
			List TypeList = yxGraduateService.getTypeList();
			request.setAttribute("TypeList", TypeList);

			// �Ƿ������ס��
			List requestavailableList = yxGraduateService
					.getRequestavailableList();
			request.setAttribute("requestavailableList", requestavailableList);
			account = (Account) session.getAttribute("accountPerson");
			String stuemp_no = account.getPerson().getPersonCode();
			List districtionList = yxGraduateService
					.getTabssdeptList(stuemp_no);
			for(int i=0;i<districtionList.size();i++){
				String s = ((TabSsDept)districtionList.get(i)).getName();
				if(s.equals("����")){					
					((TabSsDept)districtionList.get(i)).setName("����У��-����");
				}
			}
			request.setAttribute("districtionList", districtionList);
		} else {
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"classAlert.loginFirstornotass"));
			saveErrors(request, messages);
			return mapping.findForward("load4ResidentSearch");
		}
		return mapping.findForward("load4ResidentSearch");
	}

	public ActionForward load4ResidentList(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		HttpSession session = request.getSession();
		ActionMessages messages = new ActionMessages();
		DynaActionForm graduateForm = (DynaActionForm) form;

		YxGraduate yxgraduate = (YxGraduate) graduateForm.get("YxGraduate");
		String startfrom = graduateForm.getString("startfrom");
		String graduateNoSearch1 = graduateForm.getString("graduateNoSearch1");
		String graduateNoSearch2 = graduateForm.getString("graduateNoSearch2");
		String lengthofschool1 = graduateForm.getString("lengthofschool1");		
		String page = "";
		if(request.getParameter("pager.offset")==null){
			page = "0";
		}else{
			page = request.getParameter("pager.offset");
		}
		String[] args = { startfrom, page, "0",graduateNoSearch1,graduateNoSearch2,lengthofschool1 };

		Account account = null;
		if (session.getAttribute("accountPerson") != null) {
			// ѧ�����
			List studentTypeList = yxGraduateService.getStudentTypeList();
			request.setAttribute("studentTypeList", studentTypeList);
			// ������ʽ
			List styleList = yxGraduateService.getStyleList();
			request.setAttribute("styleList", styleList);
			// ¼ȡԺϵ
			List collegeList = yxGraduateService
					.getCollegeListFromGraduateTable();
			request.setAttribute("collegeList", collegeList);
			// רҵ
			List specialityList = yxGraduateService.getSpecialityList();
			request.setAttribute("specialityList", specialityList);
			// �о�������
			List TypeList = yxGraduateService.getTypeList();
			request.setAttribute("TypeList", TypeList);
			
			if (request.getParameter("export") == null
					|| "".equals(request.getParameter("export"))) {

			List requestavailableList = yxGraduateService
					.getRequestavailableList();
			request.setAttribute("requestavailableList", requestavailableList);

			account = (Account) session.getAttribute("accountPerson");
			String stuemp_no = account.getPerson().getPersonCode();
			List districtionList = yxGraduateService
					.getTabssdeptList(stuemp_no);
			for(int i=0;i<districtionList.size();i++){
				String s = ((TabSsDept)districtionList.get(i)).getName();
				if(s.equals("����")){					
					((TabSsDept)districtionList.get(i)).setName("����У��-����");
				}
			}
			request.setAttribute("districtionList", districtionList);
			args[2] = stuemp_no;
			List yxgraduates = yxGraduateService.getGraduateResidentsList(
					yxgraduate, args);
			for(int i=0;i<yxgraduates.size();i++){
				String s = ((YxGraduate)yxgraduates.get(i)).getDistriction();
				if("����".equals(s)){
					((YxGraduate)yxgraduates.get(i)).setDistriction("����У��-����");
				}
			}
			String noticemsg = "";
			List tmpList=classService.find(" select a from YxGraduate a " +
					"where (a.distriction is null or a.distriction='') and a.requestAvailable='1' and a.enrollYear='"+DateUtil.getNow("yyyy")+"'");
			if(tmpList!=null&&tmpList.size()>0){
				noticemsg += ((YxGraduate)tmpList.get(0)).getGraduateName();
				for(int k=1;k<tmpList.size();k++){
					noticemsg += ","+((YxGraduate)tmpList.get(k)).getGraduateName();
				}
				request.setAttribute("noticemsg", noticemsg);
			}
			
			Integer yxgraduatesCount = yxGraduateService.getGraduateResidentsListCount(yxgraduate, args);
			request.setAttribute("yxgraduates", yxgraduates);
			request.setAttribute("graduateCount", yxgraduatesCount);
			} else {
				account = (Account) session.getAttribute("accountPerson");
				String stuemp_no = account.getPerson().getPersonCode();
				args[2] = stuemp_no;
				// =================================================================
				List yxgraduates = yxGraduateService.getGraduateResidentsExport(yxgraduate,args);
				// Create the Excel File
				String fileName = "graduate_resident_Info.xls";
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
				columnNames.add(1, "����");
				columnNames.add(2, "�Ա�");
				columnNames.add(3, "ѧ�����");
				columnNames.add(4, "������ʽ");
				columnNames.add(5, "¼ȡԺϵ");
				columnNames.add(6, "¼ȡרҵ");
				columnNames.add(7, "ѧ��");
				columnNames.add(8, "�о���ס�޹������");
				columnNames.add(9, "ס������");
				columnNames.add(10, "�Ƿ������ס��");


				for (int i = 0; i < columnNames.size(); i++) {
					HSSFCell cname = row.createCell((short) i);
					cname.setCellStyle(cellHeadStyle);
					cname.setEncoding(HSSFCell.ENCODING_UTF_16);
					cname.setCellValue((String) columnNames.get(i));
				}

				// Populate the Row Data to the SpreadSheet
				int rowCount = yxgraduates.size();
				// goal houses the number of cells in the target spreadsheet
				int goal = rowCount * columnNames.size();

				// actual population of target spreadsheet
				int currentCell = 0;

				for (int i = 0; i < rowCount; i++) {
					YxGraduate tableData = (YxGraduate) yxgraduates
							.get(i);
					// create row in spreadsheet
					row = sheet1.createRow((short) (i + 1));

					// populate the spreadsheet with the cell
					HSSFCell ctitle = row.createCell((short) 0);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getGraduateNo());
					
					ctitle = row.createCell((short) 1);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getGraduateName());

					ctitle = row.createCell((short) 2);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getSex());

					ctitle = row.createCell((short) 3);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getStudentType());
			
					ctitle = row.createCell((short) 4);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getMatriculateType());

					ctitle = row.createCell((short) 5);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getCurCollege());

					ctitle = row.createCell((short) 6);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getSpeciality());

					ctitle = row.createCell((short) 7);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getLengthofschool());

					ctitle = row.createCell((short) 8);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getGraduateType());

					ctitle = row.createCell((short) 9);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getDistriction());

					ctitle = row.createCell((short) 10);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue(tableData.getRequestAvailable());


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

		} else {
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"classAlert.loginFirstornotass"));
			saveErrors(request, messages);
			return mapping.findForward("load4ResidentSearch");
		}

		return mapping.findForward("load4ResidentSearch");
	}

	public ActionForward residentUpdate(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		DynaActionForm graduateForm = (DynaActionForm) form;
		String newdistriction = graduateForm.getString("newdistriction");
		String newrequestavailable = graduateForm
				.getString("newrequestavailable");

		String[] args = { newdistriction, newrequestavailable };
		String[] deleteX = request.getParameterValues("deleteX");
		ActionMessages messages = new ActionMessages();
		// ѧ�����
		try {
			yxGraduateService.updateGraduateResidents(deleteX, args,request);
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
				"graduate.updatessuccess"));
			saveErrors(request, messages);
		} catch (Exception e) {
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"graduate.updatesfailue"));
			saveErrors(request, messages);
		}

		return mapping.findForward("residentUpdateSucc");
//		return load4ResidentList(mapping, form, request, response);
	}

	public ActionForward dormDistributionStatistic(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) {
		HttpSession session = request.getSession();
		ActionMessages messages = new ActionMessages();
		Account account = null;
		if (session.getAttribute("accountPerson") != null) {
			account = (Account) session.getAttribute("accountPerson");
			String stuemp_no = account.getPerson().getPersonCode();
			List collegeList = yxGraduateService
					.getCollegeListFromGraduateTableLimit(stuemp_no);
			request.setAttribute("collegeList", collegeList);
			
			List dormList=dormTypeManageService
					.getDormListFromGraduateTableLimit(stuemp_no);
			request.setAttribute("dormList", dormList);
			
			//List CollegeStudentCount = yxGraduateService
			//		.getCollegeStudentCount(stuemp_no);
			//request.setAttribute("CollegeStudentCount", CollegeStudentCount);

			//List CollegeDormitoryStatistic = yxGraduateService
			//		.getCollegeDormitoryStatistic(stuemp_no);
			//request.setAttribute("CollegeDormitoryStatistic",
			//		CollegeDormitoryStatistic);
			
			List CollegeStudentCount=dormTypeManageService.getDormStatbyCollege(stuemp_no);
			request.setAttribute("CollegeStudentCount", CollegeStudentCount);

			List CollegeDormitoryStatistic = dormTypeManageService.getDormStatbyDorm(stuemp_no);
			request.setAttribute("DormitoryStatistic",
					CollegeDormitoryStatistic);

		} else {
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"classAlert.loginFirstornotass"));
			saveErrors(request, messages);
			return mapping.findForward("dormDistributionStatistic");
		}

		return mapping.findForward("dormDistributionStatistic");
	}

	public ActionForward dormDistribution(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) {
		ActionMessages messages = new ActionMessages();
		try {
			HttpSession session = request.getSession();
			Account account = null;
			if (session.getAttribute("accountPerson") != null) {
				account = (Account) session.getAttribute("accountPerson");
				String stuemp_no = account.getPerson().getPersonCode();
				yxGraduateService.saveDormDistribution(stuemp_no);
				// ѧ���ְ�
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"dormDistribution.rss", yxGraduateService
								.getGraduateCount(stuemp_no)));
				saveErrors(request, messages);
			} else {
				messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"classAlert.loginFirstornotass"));
				saveErrors(request, messages);
				return dormDistributionStatistic(mapping, form, request,
						response);
			}

		} catch (StudentAlreadyInDormException e) {
			// e.printStackTrace();
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"dormDistribution.studentalreadyindorm"));
			saveErrors(request, messages);
			return dormDistributionStatistic(mapping, form, request, response);
		} catch (DormitoryNotEnoughException e) {
			// e.printStackTrace();
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"dormDistribution.dormitorynotenough"));
			saveErrors(request, messages);
			return dormDistributionStatistic(mapping, form, request, response);
		} catch (Exception e) {
			// e.printStackTrace();
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"dormDistribution.error"));
			saveErrors(request, messages);
			e.printStackTrace();
			return dormDistributionStatistic(mapping, form, request, response);

		}
		return mapping.findForward("dormDistributionSuccess");

	}
	
//	�˵�����ʱ������
	public ActionForward menutimelist(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) {
		
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
		String sqlstring=" select new Map(a.id as id,b.name as menuName,a.beginDate as beginDate,a.beginTime as beginTime,a.endDate as endDate,a.endTime as endTime,a.updateTime as updateTime) from MenuTime a,Menu b where b.id=a.menuId and a.schoolId='0003' ";
		
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
	
	public ActionForward load4SXTJ(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) {
		
		HttpSession session = request.getSession(true);

		Account account = (Account) session.getAttribute("accountPerson");
		String stuemp_no = account.getPerson().getPersonCode();
		
		List sxlist = yxGraduateService.getSxList(stuemp_no);
			
		List canreqlist = yxGraduateService.getCanreqList(stuemp_no);
		
		request.setAttribute("sxlist", sxlist);
		request.setAttribute("canreqlist", canreqlist);
		return mapping.findForward("sxTJ");	
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
        String managerNo=manager.getPerson().getPersonCode();	//��ȡ��¼�ߵ�ѧ����
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
						     
 		     // ���ݿ���֤
		
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
