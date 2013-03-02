package org.king.yangong.dormitorymanage.web.action;

import java.io.IOException;
import java.io.OutputStream;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.Date;
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
import org.king.checkinmanage.service.CheckinmanageService;
import org.king.classmanage.domain.Department;
import org.king.classmanage.domain.Dictionary;
import org.king.classmanage.domain.GzStuTemp;
import org.king.classmanage.domain.Studentmodel;
import org.king.classmanage.service.ClassService;
import org.king.classmanage.service.StudentService;
import org.king.dictionary.service.DictionaryService;
import org.king.dormitorymanage.domain.DormDept;
import org.king.dormitorymanage.domain.Dormitorymodel;
import org.king.framework.web.action.BaseAction;
import org.king.security.domain.Account;
import org.king.utils.DateUtil;
import org.king.quarters.domain.TabSsDept;
import org.king.rcvmanage.service.RcvmanageService;
import org.king.yangong.Constance;
import org.king.yangong.checkinmanage.service.YgCheckinmanageService;
import org.king.yangong.dormitorymanage.domain.GraduateType;
import org.king.yangong.dormitorymanage.domain.YxGraduate;
import org.king.yangong.dormitorymanage.domain.YxGzdormapply;
import org.king.yangong.dormitorymanage.service.DormAppService;
import org.king.yangong.dormitorymanage.service.YxGraduateService;

public class DormAppAction extends BaseAction{
	private YxGraduateService yxGraduateService;
	private ClassService classService;
	private StudentService studentService;
	private YgCheckinmanageService ygCheckinmanageService;
	DormAppService dormAppService;
	DictionaryService dictionaryService;
	
	private CheckinmanageService checkinmanageservice;
	
	public void setCheckinmanageService(CheckinmanageService checkinmanageservice) {
		this.checkinmanageservice = checkinmanageservice;
	}
	
	public void setClassService(ClassService classService) {
		this.classService = classService;
	}
	
	private RcvmanageService rcvmanageservice;
	
	public void setRcvmanageService(RcvmanageService rcvmanageservice) {
		this.rcvmanageservice = rcvmanageservice;
	}
	public void setDormAppService(DormAppService dormAppService) {
		this.dormAppService = dormAppService;
	}

	public void setDictionaryService(DictionaryService dictionaryService) {
		this.dictionaryService = dictionaryService;
	}
	/*
	 * 列出本人住宿申请登记信息
	 */
	public ActionForward loadGraduateByID(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		String timespan="";
		timespan=rcvmanageservice.checkTimeUp("0906001");
		if(!timespan.equals("")){
			request.setAttribute("timespan",timespan);
			return mapping.findForward("timeup");
		}

		String operator = "";
		if (request.getSession().getAttribute("accountPerson") != null) {
			operator = ((Account) request.getSession().getAttribute(
					"accountPerson")).getPerson().getPersonCode();
		}
		List li = dormAppService.getGraduate(operator); 

        String sqlstring="select new Map(s.id as id,s.graduateNo as studentNo,s.graduateName as stuName,s.sex as gender," +
		"s.curCollege as curCollege,s.speciality as majorin,s.graduateType as graduateType,s.dormitoryId as dormitoryId) " +
		"from YxGraduate s where s.graduateNo='"+operator+"' and s.enrollYear='"+DateUtil.getNow("yyyy")+"' ";		            	            
        List stuinfoList=checkinmanageservice.find(sqlstring);	
        if(stuinfoList!=null&&stuinfoList.size()!=0){
			if (((Map)stuinfoList.get(0)).get("graduateType") != null) {
				List cap_list = checkinmanageservice.find("select a.graduateType from GraduateType a where a.id='"
						+ (String)(((Map)stuinfoList.get(0)).get("graduateType")) + "' and a.ifdeleted = '1'");
				if (cap_list.size() > 0) {
					String Cap = cap_list.get(0).toString();
					((Map)stuinfoList.get(0)).put("graduateType", Cap);
				}
			}
			request.setAttribute("graduateType", ((Map)stuinfoList.get(0)).get("graduateType"));
        }

        //院系
        List collegeList = yxGraduateService.getCollegeListFromGraduateTable();
		if(collegeList!=null&&collegeList.size()>0)
			request.setAttribute("collegeList",collegeList);
        //专业
		List majorList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=28 order by di.id.dictValue");
		if(majorList!=null&&majorList.size()>0)
			request.setAttribute("majorinlist",majorList);
		
        request.setAttribute("stuinfoList",stuinfoList);
        
        if(li!=null&&li.size()>0){
			for(int i=0;i<li.size();i++){
				String s = (String)((Map)li.get(i)).get("distriction");
				if("北区".equals(s)){
					((Map)li.get(i)).put("distriction", "邯郸校区-北区");
				}
			}
    		request.setAttribute("graduateList", li);
        }
		return mapping.findForward("dormAppList4graduate");
	}
	
	/*
	 * 列出当年研究生住宿申请登记信息
	 */
	public ActionForward loadGraduateList(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		DynaActionForm graduateSearchForm = (DynaActionForm) form;
		String page = null;
		String operator = "";
		if (request.getSession().getAttribute("accountPerson") != null) {
			operator = ((Account) request.getSession().getAttribute(
					"accountPerson")).getPerson().getPersonCode();
		}
		if(request.getParameter("pager.offset")==null){
			page = "0";
		}else{
			page = request.getParameter("pager.offset");
		}
		dormAppService.initForm(request);
		request.getAttribute("messages");
		List TypeList = yxGraduateService.getTypeList();
		request.setAttribute("graduateTypeList", TypeList);
		
		List studentTypeList = dictionaryService.getDictionaryList(Constance.studentTypeKey);
		request.setAttribute("studentTypeList", studentTypeList);
		
		List matriculateTypeList = dictionaryService.getDictionaryList(Constance.matriculateTypeKey);
		request.setAttribute("matriculateTypeList", matriculateTypeList);
		
		List collegeList = yxGraduateService.getCollegeListFromGraduateTable();
		request.setAttribute("curCollegeList", collegeList);
		
 		List specialityList = dictionaryService.getDictionaryList(Constance.specialityKey);
 		request.setAttribute("specialityList", specialityList);
		List districtionList = yxGraduateService.getTabssdeptList(operator);
		for(int i=0;i<districtionList.size();i++){
			String s = ((TabSsDept)districtionList.get(i)).getName();
			if(s.equals("北区")){					
				((TabSsDept)districtionList.get(i)).setName("邯郸校区-北区");
			}
		}
		request.setAttribute("districtionList", districtionList);
		String[][] colandclsList=getColandCls();
		if(colandclsList!=null&&colandclsList.length>0){
			 request.setAttribute("classlist",colandclsList);
		}
		if (request.getParameter("export") == null
				|| "".equals(request.getParameter("export"))) {
			List li = dormAppService.getGraduateList(graduateSearchForm,page,operator);
			if(li!=null&&li.size()>0){
				String show = "";
				if("北区".equals(((Map)li.get(0)).get("distriction"))){
					show = "邯郸校区-北区";
				}else if("江湾".equals(((Map)li.get(0)).get("distriction"))){
					show = "江湾校区";
				}else if("张江".equals(((Map)li.get(0)).get("distriction"))){
					show = "张江校区";
				}else if("西苑".equals(((Map)li.get(0)).get("distriction"))){
					show = "枫林校区-西苑";
				}else{
					show = (String)((Map)li.get(0)).get("distriction");
				}
				request.setAttribute("show", show);
			}
			
			for(int i=0;i<li.size();i++){
				String s = (String)((Map)li.get(i)).get("distriction");
				if("北区".equals(s)){
					((Map)li.get(i)).put("distriction", "邯郸校区-北区");
				}
			}
			Integer count = dormAppService.getGraduateListCount(graduateSearchForm,operator);
			request.setAttribute("graduateList", li);	
			request.setAttribute("graduateCount", count);
			return mapping.findForward("dormAppList");
		}else{
			List yxgraduates = dormAppService.getGraduateListExport(graduateSearchForm,page,operator);
			String fileName = "graduate_domitoryApp_Info.xls";
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
			columnNames.add(3, "学生类别");
			columnNames.add(4, "培养方式");
			columnNames.add(5, "录取院系");
			columnNames.add(6, "录取专业");
			columnNames.add(7, "住宿年限");
			columnNames.add(8, "研究生住宿管理类别");
			columnNames.add(9, "住宿区域");
			columnNames.add(10, "是否需要住宿");
			columnNames.add(11, "备注");
			columnNames.add(12, "更新时间");


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
				Map tableData = (Map) yxgraduates
						.get(i);
				// create row in spreadsheet
				row = sheet1.createRow((short) (i + 1));

				// populate the spreadsheet with the cell
				HSSFCell ctitle = row.createCell((short) 0);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("graduateNo"));
				
				ctitle = row.createCell((short) 1);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("graduateName"));

				ctitle = row.createCell((short) 2);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				if("1".equals(tableData.get("sex"))){
					ctitle.setCellValue("男");
				}else{
					ctitle.setCellValue("女");
				}

				ctitle = row.createCell((short) 3);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("studentType"));
		
				ctitle = row.createCell((short) 4);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("matriculateType"));

				ctitle = row.createCell((short) 5);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("curCollege"));

				ctitle = row.createCell((short) 6);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("speciality"));

				ctitle = row.createCell((short) 7);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue(tableData.get("lengthofschool").toString());

				ctitle = row.createCell((short) 8);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("graduateType"));
				
				ctitle = row.createCell((short) 9);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("distriction"));
				
				ctitle = row.createCell((short) 10);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				if("1".equals(tableData.get("residentNeed"))){
					ctitle.setCellValue("是");
				}else{
					ctitle.setCellValue("否");
				}

				ctitle = row.createCell((short) 11);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("memo"));
				
				ctitle = row.createCell((short) 12);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("registerTime"));
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
		}
	}
	
	public ActionForward memoView(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		DynaActionForm graduateSearchForm = (DynaActionForm) form;
		String gid = (String)request.getParameter("gid");
		YxGraduate g = (YxGraduate)dormAppService.getGEntity(gid);
		graduateSearchForm.set("memo", g.getMemo());
		request.setAttribute("gid",gid);
		return mapping.findForward("memoView");
	}
	public ActionForward memoView4hl(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		DynaActionForm graduateSearchForm = (DynaActionForm) form;
		String gid = (String)request.getParameter("gid");
		YxGzdormapply g = (YxGzdormapply)dormAppService.gethlEntity(gid);
		graduateSearchForm.set("memo", g.getMemo());
		request.setAttribute("gid",gid);
		return mapping.findForward("memoView4hl");
	}
	/*
	 * 列出当年研究生住宿申请登记信息
	 */
	public ActionForward dormAppFilter(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		DynaActionForm graduateSearchForm = (DynaActionForm) form;
		String page = null;
		if(request.getParameter("pager.offset")==null){
			page = "0";
		}else{
			page = request.getParameter("pager.offset");
		}
		List studentTypeList = dictionaryService.getDictionaryList(Constance.studentTypeKey);
		List matriculateTypeList = dictionaryService.getDictionaryList(Constance.matriculateTypeKey);
		List collegeList = yxGraduateService.getCollegeListFromGraduateTable();
		List specialityList = dictionaryService.getDictionaryList(Constance.specialityKey);
		String[][] colandclsList=getColandCls();
		if(colandclsList!=null&&colandclsList.length>0){
			 request.setAttribute("classlist",colandclsList);
		}
		List li = dormAppService.getGraduateList(graduateSearchForm,page);
		request.setAttribute("graduateList", li);
		request.setAttribute("studentTypeList", studentTypeList);
		request.setAttribute("matriculateTypeList", matriculateTypeList);
		request.setAttribute("curCollegeList", collegeList);
		request.setAttribute("specialityList", specialityList);
		request.setAttribute("graduateCount", new Integer(li.size()));
		return mapping.findForward("dormAppList");
	}

	/*
	 * 修改研究生住宿申请登记信息
	 */
	public ActionForward updateGraduateInfo(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		//HttpSession session = request.getSession();
		String operator = "";
		if (request.getSession().getAttribute("accountPerson") != null) {
			operator = ((Account) request.getSession().getAttribute(
					"accountPerson")).getPerson().getPersonCode();
		}
		ActionMessages messages = new ActionMessages();
		List li = yxGraduateService.getGraduateListByDorm(operator);
		if(li!=null&&li.size()>0){
			messages.add(ActionMessages.GLOBAL_MESSAGE,
					new ActionMessage("graduateDormApp.cannotchange"));
			saveErrors(request, messages);
			return mapping.findForward("updateGraduateSuccess");
		}else{
			String[] itemlist = request.getParameterValues("itemlist");
			String[] itemList = request.getParameterValues("itemList");
			dormAppService.updateGraduateInfo(itemlist,itemList);
			messages.add(ActionMessages.GLOBAL_MESSAGE,
					new ActionMessage("graduateDormApp.appSuccess"));
			saveErrors(request, messages);
			
			return mapping.findForward("updateGraduateSuccess");
		}
	}
	
	/*
	 * 标记参与宿舍自动分配的高职生
	 */
	public ActionForward updateGzDormAppModify(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		ActionMessages messages = new ActionMessages();
//		HttpSession session = request.getSession();
		String operator = "";
		if (request.getSession().getAttribute("accountPerson") != null) {
			operator = ((Account) request.getSession().getAttribute(
					"accountPerson")).getPerson().getPersonCode();
		}
		List li = yxGraduateService.getGzListByDorm(operator);
		if(li!=null&&li.size()>0){
			messages.add(ActionMessages.GLOBAL_MESSAGE,
					new ActionMessage("graduateDormApp.cannotchange"));
			saveErrors(request, messages);
			return mapping.findForward("updateGzSuccess");
		}else{
			String[] itemlist = request.getParameterValues("itemlist");
			String[] itemList = request.getParameterValues("itemList");
			dormAppService.updateGZStudentInfo(itemlist,itemList);
			messages.add(ActionMessages.GLOBAL_MESSAGE,
					new ActionMessage("updateGraduateInfo.success"));
			saveErrors(request, messages);
			return mapping.findForward("updateGzSuccess");
		}
	}
	/*
	 * 修改本人住宿申请登记信息
	 */
	public ActionForward updateGraduateInfo4graduate(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		ActionMessages messages = new ActionMessages();
		String itemlist = request.getParameter("itemlist");
		String tag = request.getParameter("tag");
		String memo = request.getParameter("memo");
		dormAppService.updateGraduateInfo(itemlist,tag,memo);

			messages.add(ActionMessages.GLOBAL_MESSAGE,
					new ActionMessage("updateGraduateInfo.success"));
			saveErrors(request, messages);

		return mapping.findForward("updateGraduateSuccess4graduate");
	}
	
	/*
	 * 统计各院系床位绑定结果（院系、性别、应绑定人数、已绑定人数）
	 */
	public ActionForward deptDormBundTJ(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		
		DynaActionForm deptBundSearchForm = (DynaActionForm) form;
		List liBunding = dormAppService.list4DeptBundingTJ(deptBundSearchForm);
		List liBunded = dormAppService.list4DeptBundedTJ(deptBundSearchForm);
		for(int i=0;i<liBunding.size();i++){
			Map map = (Map)liBunding.get(i);
			for(int j=0;j<liBunded.size();j++){ 
				if(((String)map.get("deptCode")).equals((String)(((Map)liBunded.get(j)).get("deptCode")))
						&&((String)map.get("gender")).equals((String)(((Map)liBunded.get(j)).get("sex")))){
					map.put("bundedNum", (((Map)liBunded.get(j)).get("bundedNum")));
					break;
				}else{
					map.put("bundedNum", "0");
				}
			}
		}
		List liBundingTotal = dormAppService.list4DeptBundingTotalTJ(deptBundSearchForm);
		List liBundedTotal = dormAppService.list4DeptBundedTotalTJ(deptBundSearchForm);
		((Map)liBundingTotal.get(0)).put("bundedNum", ((Map)liBundedTotal.get(0)).get("bundedNum"));
		request.setAttribute("list4TJ", liBunding);
		request.setAttribute("list4TotalTJ", liBundingTotal);
		request.setAttribute("liBundsize", new Integer(liBunding.size()).toString());
		return mapping.findForward("deptDormBundTJSucc");
	}
	
	/*
	 * 显示某院系绑定到哪些房间（院系、房间号、性别、绑定床位数）
	 */
	public ActionForward deptDormBundingTJ(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		
		String deptId = request.getParameter("deptId");
		List liBunded = dormAppService.listDormBundByDept(deptId);
		Department dormDept = (Department)dormAppService.getEntity(deptId);
		request.setAttribute("list4TJ", liBunded);
		request.setAttribute("yx", dormDept);
		return mapping.findForward("deptDormBundingTJSucc");
	}
	
	/*
	 * 统计楼号床位绑定结果（楼号、可绑定人数、已绑定人数）
	 */
	public ActionForward buildDormBundTJ(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {

		DynaActionForm buildBundSearchForm = (DynaActionForm) form;
		List liBund = dormAppService.list4BuildBundingTJ(buildBundSearchForm);
		List liBundTotal = dormAppService.list4BuildBundingTotalTJ(buildBundSearchForm);
		request.setAttribute("list4TJ", liBund);
		request.setAttribute("list4TotalTJ", liBundTotal);
		request.setAttribute("liBundsize", new Integer(liBund.size()).toString());
		return mapping.findForward("buildDormBundTJSucc");
	}
	
	/*
	 * 显示某栋楼的房间绑定到哪些院系（楼号、房间号、性别、院系、绑定床位数）
	 */
	public ActionForward buildDormBundingTJ(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		
		String areaCode = request.getParameter("areaCode");
		String locationCode = request.getParameter("locationCode");
		String dormitoryId = request.getParameter("dormitoryId");
		List area = dormAppService.getDictionaryModel(17,areaCode);
		List location = dormAppService.getDictionaryModel(20,locationCode);
		List dormitory = dormAppService.getDictionaryModel(21,dormitoryId);
		//dormAppService.getDictionaryModel(17,areaCode);
		List liBunded = dormAppService.listDormBundByDormitory(areaCode,locationCode,dormitoryId);
		request.setAttribute("list4TJ", liBunded);
		request.setAttribute("dormitory", (String)(((Map)dormitory.get(0)).get("dictCaption")));
		request.setAttribute("area", (String)(((Map)area.get(0)).get("dictCaption")));
		request.setAttribute("location", (String)(((Map)location.get(0)).get("dictCaption")));
		return mapping.findForward("buildDormBundingTJSucc");
	}

	public void setYxGraduateService(YxGraduateService yxGraduateService) {
		this.yxGraduateService = yxGraduateService;
	}
	
	public String[][] getColandCls(){
		
		   List rList=new ArrayList();			   
		   String sqlstring = "";	
		   String[][] result;
		   
		   try {
				 if(ygCheckinmanageService==null)
					 System.out.println("service is null");		     
		     		     
		     rList=yxGraduateService.getMajorListFromGraduateTable();
		     if(rList!=null&&rList.size()>0){
		    	 result=new String[rList.size()][3];
		         for(int i=0;i<rList.size();i++){
		             result[i][0] =(String)(((Map)rList.get(i)).get("majorCode"));
		             result[i][1] = (String)(((Map)rList.get(i)).get("majorName"));
		             result[i][2] = (String)(((Map)rList.get(i)).get("collegeCode"));

		         } 		        
		         return result;
		     }
		     else
		    	 return null;

		   }catch (Exception e){
		     e.printStackTrace();
		     return null;
		   }

		 }

	public void setYgCheckinmanageService(
			YgCheckinmanageService ygCheckinmanageService) {
		this.ygCheckinmanageService = ygCheckinmanageService;
	}
	
	/*
	 * 列出护理学院宿舍申请登记信息列表
	 */
	public ActionForward loadGzList(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		DynaActionForm graduateSearchForm = (DynaActionForm) form;
		String page = null;
		if(request.getParameter("pager.offset")==null){
			page = "0";
		}else{
			page = request.getParameter("pager.offset");
		}
		List qxLi = dictionaryService.getDictionaryList("23");
		List sexLi = dictionaryService.getDictionaryList("1");
		List classLi = classService.getClassbyCollegeId("0002");
		if (request.getParameter("export") == null
				|| "".equals(request.getParameter("export"))) {
			List li = dormAppService.getGzList(graduateSearchForm,page);
			
			Integer count = dormAppService.getGzListCount(graduateSearchForm);
			request.setAttribute("graduateList", li);
			request.setAttribute("qxLi", qxLi);
			request.setAttribute("sexLi", sexLi);
			request.setAttribute("classLi", classLi);
	
			request.setAttribute("graduateCount", count);
			if(graduateSearchForm.getString("specialitySearch")==null||
					graduateSearchForm.getString("specialitySearch").equals("")){
				graduateSearchForm.set("specialitySearch", "1");
			}
			return mapping.findForward("gzdormAppList");
		}else{
			// =================================================================
			List yxgraduates = dormAppService.getGzListExport(graduateSearchForm,page);
			// Create the Excel File
			String fileName = "gz_dormApp_Info.xls";
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
			columnNames.add(3, "住址所在区县");
			columnNames.add(4, "详细住址");
			columnNames.add(5, "联系电话");
			columnNames.add(6, "是否申请住宿");
			columnNames.add(7, "备注");
			columnNames.add(8, "申请时间");



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
				HashMap tableData = (HashMap) yxgraduates
						.get(i);
				// create row in spreadsheet
				row = sheet1.createRow((short) (i + 1));

				// populate the spreadsheet with the cell
				HSSFCell ctitle = row.createCell((short) 0);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("studentNo"));
				
				ctitle = row.createCell((short) 1);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("stuName"));

				ctitle = row.createCell((short) 2);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				if("1".equals((String)tableData.get("gender"))){
					ctitle.setCellValue("男");
				}else{
					ctitle.setCellValue("女");
				}

				ctitle = row.createCell((short) 3);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("district"));
				
				ctitle = row.createCell((short) 4);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("curAddress"));
		
				ctitle = row.createCell((short) 5);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("curTelephone"));
				
				ctitle = row.createCell((short) 6);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				if(((String)tableData.get("ifNeedDorm")).equals("1")){
					ctitle.setCellValue("是");
				}else {
					ctitle.setCellValue("否");
				}

				ctitle = row.createCell((short) 7);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("memo"));
		
				ctitle = row.createCell((short) 8);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue(((Date)tableData.get("updateTime")).toString().substring(0,16));
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
	/*
	 * 列出护理学院宿舍申请登记信息列表(只列出申请了宿舍的记录)
	 */
	public ActionForward loadGzList4Need(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		DynaActionForm graduateSearchForm = (DynaActionForm) form;
		String page = null;
		if(request.getParameter("pager.offset")==null){
			page = "0";
		}else{
			page = request.getParameter("pager.offset");
		}
		List qxLi = dictionaryService.getDictionaryList("23");
		List sexLi = dictionaryService.getDictionaryList("1");
		List classLi = classService.getClassbyCollegeId("0002");
		if (request.getParameter("export") == null
				|| "".equals(request.getParameter("export"))) {
			List li = dormAppService.getGzList4NeedDorm(graduateSearchForm,page);
			

			Integer count = dormAppService.getGzList4NeedDormCount(graduateSearchForm);
			request.setAttribute("graduateList", li);
			request.setAttribute("qxLi", qxLi);
			request.setAttribute("sexLi", sexLi);
			request.setAttribute("classLi", classLi);
			request.setAttribute("graduateCount", count);
		}else {
			// =================================================================
			List yxgraduates = dormAppService.getGzList4NeedDormExport(graduateSearchForm);
			// Create the Excel File
			String fileName = "gz_resident_Info.xls";
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
			columnNames.add(3, "目前详细住址");
			columnNames.add(4, "是否申请住宿");
			columnNames.add(5, "是否参与住宿自动分配");



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
				HashMap tableData = (HashMap) yxgraduates
						.get(i);
				// create row in spreadsheet
				row = sheet1.createRow((short) (i + 1));

				// populate the spreadsheet with the cell
				HSSFCell ctitle = row.createCell((short) 0);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("stuNo"));
				
				ctitle = row.createCell((short) 1);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("stuName"));

				ctitle = row.createCell((short) 2);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				if("1".equals((String)tableData.get("gender"))){
					ctitle.setCellValue("男");
				}else{
					ctitle.setCellValue("女");
				}


				ctitle = row.createCell((short) 3);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("curAddress"));
		
				ctitle = row.createCell((short) 4);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				if(((String)tableData.get("ifNeedDorm")).equals("1")){
					ctitle.setCellValue("是");
				}else {
					ctitle.setCellValue("否");
				}

				ctitle = row.createCell((short) 5);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				if(((String)tableData.get("ifGiveDorm")).equals("1")){				
					ctitle.setCellValue("是");
				}else {
					ctitle.setCellValue("否");
				}


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


		if(graduateSearchForm.getString("specialitySearch")==null||graduateSearchForm.getString("specialitySearch").equals("")){
			graduateSearchForm.set("specialitySearch", "1");
		}
		return mapping.findForward("gzdormAppList4sx");
	}
	/*
	 * 显示护理学院宿舍申请登记信息
	 */
	public ActionForward loadGzDormAppInfo(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		
		DynaActionForm dormAppBillForm = (DynaActionForm) form;
		String itemList = request.getParameter("itemList");
		YxGzdormapply gzdormapply = null;
		if(itemList!=null&&!itemList.equals("")){
			gzdormapply = (YxGzdormapply)dormAppService.getGzdormapply(itemList);
			if(gzdormapply.getIfGiveDorm()!=null&&gzdormapply.getIfGiveDorm().equals("0")){
				List tmpli = studentService.find("select a from Studentmodel a where a.enrollYear = '"+DateUtil.getNow("yyyy")+"' and a.majorin ='623' and a.dormId is not null");
				if(tmpli==null||tmpli.size()==0){
					dormAppBillForm.set("id", gzdormapply.getId());
					dormAppBillForm.set("enterenceNo", gzdormapply.getEnrollNo());
					dormAppBillForm.set("studentNo", gzdormapply.getStudentNo());
					dormAppBillForm.set("district", gzdormapply.getDistrict());
					dormAppBillForm.set("curAddress", gzdormapply.getCurAddress());
					dormAppBillForm.set("curTelephone", gzdormapply.getCurTelephone());
					dormAppBillForm.set("ifNeedDorm", gzdormapply.getIfNeedDorm());
					dormAppBillForm.set("memo", gzdormapply.getMemo());
					List li = studentService.find("select new Map(a.stuName as stuName,a.gender as gender,b.classNo as className) from Studentmodel a,Classmodel b where a.enterenceNo = '"+gzdormapply.getEnrollNo()+"' " +
						               " and a.yxClass.classId = b.classId ");
		
					if(li!=null&&li.size()>0){
						Map map = (Map)li.get(0);
						String s = (String)map.get("gender");
						String g = (String)map.get("className");
						if(s.equals("1")){
							map.put("gender", "男");
						}else{
							map.put("gender", "女");
						}
						if(g==null){
							map.put("className", "");					
						}
						request.setAttribute("gzStu", (Map)li.get(0));
					}
					request.setAttribute("ifNeedDorm", gzdormapply.getIfNeedDorm());
				}else{
					request.setAttribute("msg", "已完成自动分配，不能修改");		
					return mapping.findForward("gzdormAppList");
				}
			}else{
				request.setAttribute("msg", "已经标记参与自动分配，不能改为不申请住宿!");
				return mapping.findForward("gzdormappcannomodify");
			}
		}else{
			dormAppBillForm.set("id", "");
			dormAppBillForm.set("enterenceNo", "");
			dormAppBillForm.set("studentNo","");
			dormAppBillForm.set("district", "");
			dormAppBillForm.set("curAddress", "");
			dormAppBillForm.set("curTelephone", "");
			dormAppBillForm.set("ifNeedDorm", "");
			dormAppBillForm.set("memo", "");
			request.setAttribute("ifNeedDorm", "");
		}
		request.setAttribute("gzdormapply", gzdormapply);
		
		dormAppService.initForm(request);
		
		return mapping.findForward("gzdormappInfo");
	}
	public ActionForward addGzDormAppInfo(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		
		DynaActionForm dormAppBillForm = (DynaActionForm) form;
		String itemList = "";
		YxGzdormapply gzdormapply = null;
		List tmpli = studentService.find("select a from Studentmodel a where a.enrollYear = '"+DateUtil.getNow("yyyy")+"' and a.majorin ='623' and a.dormId is not null");
		if(tmpli==null||tmpli.size()==0){
			if(itemList!=null&&!itemList.equals("")){
				gzdormapply = (YxGzdormapply)dormAppService.getGzdormapply(itemList);
				dormAppBillForm.set("id", gzdormapply.getId());
				dormAppBillForm.set("enterenceNo", gzdormapply.getEnrollNo());
				dormAppBillForm.set("studentNo", gzdormapply.getStudentNo());
				dormAppBillForm.set("district", gzdormapply.getDistrict());
				dormAppBillForm.set("curAddress", gzdormapply.getCurAddress());
				dormAppBillForm.set("curTelephone", gzdormapply.getCurTelephone());
				dormAppBillForm.set("ifNeedDorm", gzdormapply.getIfNeedDorm());
				dormAppBillForm.set("memo", gzdormapply.getMemo());
				List li = studentService.find("select new Map(a.stuName as stuName,a.gender as gender,b.classNo as className) from Studentmodel a,Classmodel b where a.enterenceNo = '"+gzdormapply.getEnrollNo()+"' " +
					               " and a.yxClass.classId = b.classId ");
				if(li!=null&&li.size()>0){
					Map map = (Map)li.get(0);
					String s = (String)map.get("gender");
					String g = (String)map.get("className");
					if(s.equals("1")){
						map.put("gender", "男");
					}else{
						map.put("gender", "女");
					}
					if(g==null){
						map.put("className", "");					
					}
					request.setAttribute("gzStu", (Map)li.get(0));
				}
				request.setAttribute("ifNeedDorm", gzdormapply.getIfNeedDorm());
			}else{
				dormAppBillForm.set("id", "");
				dormAppBillForm.set("enterenceNo", "");
				dormAppBillForm.set("studentNo","");
				dormAppBillForm.set("district", "");
				dormAppBillForm.set("curAddress", "");
				dormAppBillForm.set("curTelephone", "");
				dormAppBillForm.set("ifNeedDorm", "");
				dormAppBillForm.set("memo", "");
				request.setAttribute("ifNeedDorm", "");
			}
			request.setAttribute("gzdormapply", gzdormapply);
			
			dormAppService.initForm(request);
			return mapping.findForward("gzdormappInfo");
		}else{
			request.setAttribute("msg", "自动分配宿舍已经完成，不能再登记住宿");		
			return mapping.findForward("gzdormAppList");
		}

	}
	public ActionForward loadGzDormAppInfo4s(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		
		DynaActionForm dormAppBillForm = (DynaActionForm) form;
		YxGzdormapply gzdormapply = null;
		String itemList = request.getParameter("itemList");
		List li = dictionaryService.getDictionaryList("23");
		request.setAttribute("li", li);
		if(itemList!=null&&!itemList.equals("")){
			gzdormapply = (YxGzdormapply)dormAppService.getGzdormapply(itemList);
			dormAppBillForm.set("id", gzdormapply.getId());
			dormAppBillForm.set("enterenceNo", gzdormapply.getEnrollNo());
			dormAppBillForm.set("studentNo", gzdormapply.getStudentNo());
			dormAppBillForm.set("district", gzdormapply.getDistrict());
			dormAppBillForm.set("curAddress", gzdormapply.getCurAddress());
			dormAppBillForm.set("curTelephone", gzdormapply.getCurTelephone());
			dormAppBillForm.set("ifNeedDorm", gzdormapply.getIfNeedDorm());
			dormAppBillForm.set("memo", gzdormapply.getMemo());
			List sli = studentService.find("select new Map(a.stuName as stuName,a.studentNo as stuNo,a.gender as gender,b.classNo as className) from Studentmodel a,Classmodel b where a.studentNo = '"+gzdormapply.getStudentNo()+"' " +
            			" and a.yxClass.classId = b.classId ");
				if(sli!=null&&sli.size()>0){
				Map map = (Map)sli.get(0);
				String s = (String)map.get("gender");
				String g = (String)map.get("className");
				if(s.equals("1")){
					map.put("gender", "男");
				}else{
					map.put("gender", "女");
				}
				if(g==null){
					map.put("className", "");					
				}
				request.setAttribute("gzStu", (Map)sli.get(0));
				}
			request.setAttribute("ifNeedDorm", gzdormapply.getIfNeedDorm());
		}else{
			dormAppBillForm.set("id", "");
			dormAppBillForm.set("enterenceNo", "");
			dormAppBillForm.set("studentNo","");
			dormAppBillForm.set("district", "");
			dormAppBillForm.set("curAddress", "");
			dormAppBillForm.set("curTelephone", "");
			dormAppBillForm.set("ifNeedDorm", "");
			dormAppBillForm.set("memo", "");
			request.setAttribute("ifNeedDorm", "");
		}
		request.setAttribute("gzdormapply", gzdormapply);
		dormAppService.initForm(request);
		return mapping.findForward("gzdormappInfo4s");
	}
	
	/*
	 * 删除护理学院宿舍申请登记信息
	 */
	public ActionForward deleteGzDormAppInfo(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		String tag = request.getParameter("tag");
		String[] itemList = request.getParameterValues("itemList");
		dormAppService.deleteGzDormAppInfo(itemList,request);
		if(tag.equals("0")){
			request.setAttribute("msg", "删除成功!");			
			return mapping.findForward("gzdormappDeleteSuccess");
		}else{
			request.setAttribute("msg", "删除成功!");
			return mapping.findForward("gotoWelcome");
		}
	}
	
	/*
	 * 显示个人宿舍申请信息
	 */
	public ActionForward load4SingleDormApp4Gz(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		ActionMessages messages = new ActionMessages();
		String timespan="";
		timespan=rcvmanageservice.checkTimeUp("080688");
		if(!timespan.equals("")){
			request.setAttribute("timespan",timespan);
			return mapping.findForward("timeup");
		}
		DynaActionForm dormAppBillForm = (DynaActionForm) form;
		String stuNo = "";
		String enterenceNo = "";
		if (request.getSession().getAttribute("accountPerson") != null) {
			stuNo = ((Account) request.getSession().getAttribute(
					"accountPerson")).getPerson().getPersonCode();
		}
		List stuli = studentService.find("select a.enterenceNo from Studentmodel a where a.studentNo = '"+stuNo+"' ");
		if(stuli!=null&&stuli.size()>0&&stuli.get(0)!=null){
			enterenceNo = stuli.get(0).toString();
		}
		List li = dormAppService.getGzdormapplyByStuNo(enterenceNo);
		if(li!=null&&li.size()!=0){
			request.setAttribute("graduateList", li);
			dormAppService.initForm(request);
			return mapping.findForward("haveDormappinfo");
		}else{
			li = studentService.getStudentTempInfoByEnterenceNo(enterenceNo);
			GzStuTemp st = null;
			if(li!=null&&li.size()!=0){
				st = (GzStuTemp)li.get(0);
				dormAppBillForm.set("enterenceNo", enterenceNo);			
				dormAppBillForm.set("district", st.getDistrict());
				dormAppBillForm.set("curAddress", st.getFamilyAddress());
				dormAppBillForm.set("curTelephone", st.getTelephone());			
				List sli = studentService.find("select new Map(a.stuName as stuName,a.studentNo as stuNo,a.gender as gender,b.classNo as className) from Studentmodel a,Classmodel b where a.enterenceNo = '"+enterenceNo+"' " +
	            " and a.yxClass.classId = b.classId ");
					if(sli!=null&&sli.size()>0){
					Map map = (Map)sli.get(0);
					String s = (String)map.get("gender");
					String g = (String)map.get("className");
					if(s.equals("1")){
						map.put("gender", "男");
					}else{
						map.put("gender", "女");
					}
					if(g==null){
						map.put("className", "");					
					}
					request.setAttribute("gzStu", (Map)sli.get(0));
					}
			}else{
				messages.add(ActionMessages.GLOBAL_MESSAGE,
						new ActionMessage("studentsearch.nothisenterence"));
				saveErrors(request, messages);
			}		
			
			dormAppService.initForm(request);
			
			request.setAttribute("GzStuTemp", st);
			return mapping.findForward("nothaveDormappinfo");
		}		
	}
	/*
	 * 保存护理学院宿舍申请登记信息
	 */
	public ActionForward saveGzdormappInfo(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		DynaActionForm dormAppBillForm = (DynaActionForm) form;
		ActionMessages messages = new ActionMessages();
		YxGzdormapply yg = new YxGzdormapply();
		String operator = "";
		if (request.getSession().getAttribute("accountPerson") != null) {
			operator = ((Account) request.getSession().getAttribute(
					"accountPerson")).getPerson().getId();
		}
		String item = request.getParameter("item");
		String id = request.getParameter("id");
		
		dormAppService.initForm(request);

		if(id!=null&&!id.equals("")){
			yg.setId(dormAppBillForm.getString("id"));
			yg.setEnrollNo(dormAppBillForm.getString("enterenceNo"));
			yg.setStudentNo(dormAppBillForm.getString("studentNo"));
			yg.setDistrict(dormAppBillForm.getString("district"));
			yg.setCurAddress(dormAppBillForm.getString("curAddress"));
			yg.setCurTelephone(dormAppBillForm.getString("curTelephone"));
			if(item==null){
				yg.setIfNeedDorm("0");
			}else{
				yg.setIfNeedDorm("1");
			}
			yg.setIfGiveDorm("0");
			yg.setMemo(dormAppBillForm.getString("memo"));
			yg.setUpdator(operator);
			yg.setUpdateTime(new Date());
			
			dormAppService.updateGzdormappInfo(yg);
		}else{
			List li = dormAppService.getGzdormapplyByEnterenceNo(dormAppBillForm.getString("enterenceNo"));
			List sli = dormAppService.getGzdormapplyByStudentNo(dormAppBillForm.getString("studentNo"));
			if((li==null||li.size()==0)&&(sli==null||sli.size()==0)){
				yg.setEnrollNo(dormAppBillForm.getString("enterenceNo"));
				yg.setStudentNo(dormAppBillForm.getString("studentNo"));
				yg.setDistrict(dormAppBillForm.getString("district"));
				yg.setCurAddress(dormAppBillForm.getString("curAddress"));
				yg.setCurTelephone(dormAppBillForm.getString("curTelephone"));
				if(item==null){
					yg.setIfNeedDorm("0");
				}else{
					yg.setIfNeedDorm("1");
				}
				yg.setIfGiveDorm("0");
				yg.setMemo(dormAppBillForm.getString("memo"));
				yg.setUpdator(operator);
				yg.setUpdateTime(new Date());
				dormAppService.saveGzdormappInfo(yg);
			}else{
				messages.add(ActionMessages.GLOBAL_MESSAGE,
						new ActionMessage("studentsearch.hadrequested"));
				saveErrors(request, messages);
				return mapping.findForward("gzdormappInfo");
			}
		}
		request.setAttribute("msg", "添加或修改成功!");
		return mapping.findForward("updateSuccess");
	}
	public ActionForward saveMemo(ActionMapping mapping,ActionForm form,
			HttpServletRequest request,HttpServletResponse response){
		String operator = "";
		if (request.getSession().getAttribute("accountPerson") != null) {
			operator = ((Account) request.getSession().getAttribute(
					"accountPerson")).getPerson().getPersonCode();
		}
		ActionMessages messages = new ActionMessages();
		List li = yxGraduateService.getGraduateListByDorm(operator);
		if(li!=null&&li.size()>0){
			messages.add(ActionMessages.GLOBAL_MESSAGE,
					new ActionMessage("graduateDormApp.cannotchange"));
			saveErrors(request, messages);
			return mapping.findForward("updateGraduateSuccess");
		}else{
			String gid = (String)request.getParameter("gid");
			String tag = (String)request.getParameter("tag");
			String memo = (String)request.getParameter("memo");
			dormAppService.updateGraduateInfo(gid,tag,memo);
			return mapping.findForward("");
		}
	}
	public ActionForward saveGzdormappSingleInfo(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {

		ActionMessages messages = new ActionMessages();
		DynaActionForm dormAppBillForm = (DynaActionForm) form;
		List stuLi =  dormAppService.getStudentModel(dormAppBillForm.getString("enterenceNo"));
		
		YxGzdormapply yg = new YxGzdormapply();
		yg.setIfGiveDorm("0");
		if(stuLi!=null&&stuLi.size()!=0){
			yg.setStudentNo(((Studentmodel)stuLi.get(0)).getStudentNo());
		}else{
			List li = dictionaryService.getDictionaryList("23");
			request.setAttribute("li", li);
			messages.add(ActionMessages.GLOBAL_MESSAGE,
					new ActionMessage("studentsearch.nothisstudent"));
			saveErrors(request, messages);
			return mapping.findForward("gzdormappInfo4s");
		}
		String operator = "";
		if (request.getSession().getAttribute("accountPerson") != null) {
			operator = ((Account) request.getSession().getAttribute(
					"accountPerson")).getPerson().getId();
		}
		String item = request.getParameter("item");
		String id = request.getParameter("id");

		if(id!=null&&!id.equals("")){
			yg.setId(dormAppBillForm.getString("id"));
			yg.setEnrollNo(dormAppBillForm.getString("enterenceNo"));
			yg.setDistrict(dormAppBillForm.getString("district"));
			yg.setCurAddress(dormAppBillForm.getString("curAddress"));
			yg.setCurTelephone(dormAppBillForm.getString("curTelephone"));
			if(item==null){
				yg.setIfNeedDorm("0");
			}else{
				yg.setIfNeedDorm("1");
			}
			yg.setMemo(dormAppBillForm.getString("memo"));
			yg.setUpdator(operator);
			yg.setUpdateTime(new Date());			
			dormAppService.updateGzdormappInfo(yg);
		}else{
			List li = dormAppService.getGzdormapplyByEnterenceNo(dormAppBillForm.getString("enterenceNo"));
			if(li==null||li.size()==0){
				yg.setEnrollNo(dormAppBillForm.getString("enterenceNo"));
				yg.setDistrict(dormAppBillForm.getString("district"));
				yg.setCurAddress(dormAppBillForm.getString("curAddress"));
				yg.setCurTelephone(dormAppBillForm.getString("curTelephone"));
				if(item==null){
					yg.setIfNeedDorm("0");
				}else{
					yg.setIfNeedDorm("1");
				}
				yg.setIfGiveDorm("0");
				yg.setMemo(dormAppBillForm.getString("memo"));
				yg.setUpdator(operator);
				yg.setUpdateTime(new Date());
				dormAppService.saveGzdormappInfo(yg);
			}else{
				messages.add(ActionMessages.GLOBAL_MESSAGE,
						new ActionMessage("studentsearch.hadrequested"));
				saveErrors(request, messages);
				return mapping.findForward("gzdormappInfo");
			}
		}
		request.setAttribute("msg", "添加或修改成功!");
		return mapping.findForward("haveDormappinfo");
	}
	public ActionForward getStudentInfoByStudentNo(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		
		DynaActionForm dormAppBillForm = (DynaActionForm) form;
		ActionMessages messages = new ActionMessages();
		String studentNo = request.getParameter("studentNo");
		List li = studentService.getStudentTempInfoByStudentNo(studentNo);
		GzStuTemp st = null;
		if(li!=null&&li.size()!=0){
			st = (GzStuTemp)li.get(0);
			dormAppBillForm.set("enterenceNo", st.getEnterenceNo());			
			dormAppBillForm.set("district", st.getDistrict());
			dormAppBillForm.set("curAddress", st.getFamilyAddress());
			dormAppBillForm.set("curTelephone", st.getTelephone());			
			List sli = studentService.find("select new Map(a.stuName as stuName,a.gender as gender,b.classNo as className) from Studentmodel a,Classmodel b where a.studentNo = '"+studentNo+"' " +
            " and a.yxClass.classId = b.classId ");
if(sli!=null&&sli.size()>0){
Map map = (Map)sli.get(0);
String s = (String)map.get("gender");
String g = (String)map.get("className");
if(s.equals("1")){
	map.put("gender", "男");
}else{
	map.put("gender", "女");
}
if(g==null){
	map.put("className", "");					
}
request.setAttribute("gzStu", (Map)sli.get(0));
}
		}else{
			messages.add(ActionMessages.GLOBAL_MESSAGE,
					new ActionMessage("studentsearch.nothisstudent"));
			saveErrors(request, messages);
		}
		request.setAttribute("GzStuTemp", st);
		
		dormAppService.initForm(request);
		
		return mapping.findForward("gzdormappInfo");
	}
	
	public ActionForward getStudentInfoByEnterenceNo(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		
		DynaActionForm dormAppBillForm = (DynaActionForm) form;
		ActionMessages messages = new ActionMessages();
		String enterenceNo = request.getParameter("enterenceNo");
		List li = studentService.getStudentTempInfoByEnterenceNo(enterenceNo);
		GzStuTemp st = null;
		if(li!=null&&li.size()!=0){
			st = (GzStuTemp)li.get(0);
//			dormAppBillForm.set("studentNo", st.getStudentNo());			
			dormAppBillForm.set("district", st.getDistrict());
			dormAppBillForm.set("curAddress", st.getFamilyAddress());
			dormAppBillForm.set("curTelephone", st.getTelephone());			
			List sli = studentService.find("select new Map(a.studentNo as studentNo,a.stuName as stuName,a.gender as gender,b.classNo as className) from Studentmodel a,Classmodel b where a.enterenceNo = '"+enterenceNo+"' " +
            " and a.yxClass.classId = b.classId ");
				if(sli!=null&&sli.size()>0){
				Map map = (Map)sli.get(0);
				String s = (String)map.get("gender");
				String g = (String)map.get("className");
				String studentNo = (String)map.get("studentNo");	
				dormAppBillForm.set("studentNo", studentNo);
				if(s.equals("1")){
					map.put("gender", "男");
				}else{
					map.put("gender", "女");
				}
				if(g==null){
					map.put("className", "");					
				}
				request.setAttribute("gzStu", (Map)sli.get(0));
				}
		}else{
			messages.add(ActionMessages.GLOBAL_MESSAGE,
					new ActionMessage("studentsearch.nothisenterence"));
			saveErrors(request, messages);
		}		
		
		dormAppService.initForm(request);
		
		request.setAttribute("GzStuTemp", st);
		if(request.getParameter("tag")==null){
			return mapping.findForward("gzdormappInfo");
		}else{
			return mapping.findForward("gzdormappInfo4s");
		}
	}

	public void setStudentService(StudentService studentService) {
		this.studentService = studentService;
	}
}
