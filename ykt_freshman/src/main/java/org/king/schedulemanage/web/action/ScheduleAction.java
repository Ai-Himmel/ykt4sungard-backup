package org.king.schedulemanage.web.action;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.beanutils.BeanUtils;
import org.apache.commons.lang.StringUtils;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionMessage;
import org.apache.struts.action.ActionMessages;
import org.apache.struts.action.DynaActionForm;
import org.apache.struts.action.RedirectingActionForward;
import org.king.classmanage.domain.Classmanager;
import org.king.classmanage.domain.Classmodel;
import org.king.classmanage.domain.Collegemanager;
import org.king.classmanage.domain.Collegemodel;
import org.king.classmanage.domain.Dictionary;
import org.king.classmanage.domain.DictionaryId;
import org.king.classmanage.domain.Managermodel;
import org.king.classmanage.domain.Studentmodel;
import org.king.classmanage.service.ClassService;
import org.king.classmanage.service.CollegeService;
import org.king.classmanage.service.ManagerService;
import org.king.classmanage.service.StudentService;
import org.king.framework.web.action.BaseAction;
import org.king.schedulemanage.domain.Classschedulemodel;
import org.king.schedulemanage.domain.Collegeschedulemodel;
import org.king.schedulemanage.service.ScheduleService;
import org.king.security.domain.Account;

public class ScheduleAction extends BaseAction {
	private ScheduleService scheduleService;

	private CollegeService collegeService;

	private ClassService classService;

	private StudentService studentService;

	private ManagerService managerService;

	public void setScheduleService(ScheduleService scheduleService) {
		this.scheduleService = scheduleService;
	}

	public void setCollegeService(CollegeService collegeService) {
		this.collegeService = collegeService;
	}

	public void setClassService(ClassService classService) {
		this.classService = classService;
	}

	public void setStudentService(StudentService studentService) {
		this.studentService = studentService;
	}

	public void setManagerService(ManagerService managerService) {
		this.managerService = managerService;
	}

	public ActionForward init(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		return mapping.findForward("self");
	}

	public ActionForward init4Date(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		List freshDate = scheduleService.getScheduleDates();

		if (freshDate.size() != 0) {
			request.setAttribute("freshDate", freshDate);
		}
		return mapping.findForward("init4Date");
	}

	// 添加时间
	public ActionForward addDate(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		String newDictValue = "1";
		List dates = studentService.getDiction("13");
		String dateName = request.getParameter("freshDate");

		if (dates.size() != 0) {
			for (int i = 0; i < dates.size(); i++) {
				String temp = ((Dictionary) dates.get(i)).getId()
						.getDictValue();
				String caption = ((Dictionary) dates.get(i)).getDictCaption();
				if (caption.equals(dateName)) {
					request.setAttribute("msg", "添加失败：日期不能重复!");
					return mapping.findForward("addDate");
				}

				if (Integer.valueOf(newDictValue).intValue() <= Integer
						.valueOf(temp).intValue()) {
					newDictValue = String.valueOf(Integer.valueOf(temp)
							.intValue() + 1);
				}
			}
		}

		Dictionary dict = new Dictionary();
		DictionaryId dictId = new DictionaryId();
		dictId.setDictNo(Integer.valueOf("13"));
		dictId.setDictValue(newDictValue);
		dict.setId(dictId);
		dict.setDictCaption(dateName);
		dict.setDictName("迎新周日期");
		scheduleService.saveDict(dict);
		request.setAttribute("msg", "添加成功!");
		return mapping.findForward("addDate");
	}

	public ActionForward deleteDate(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		String dateId = request.getParameter("dateId");
		if (dateId != null && "" != dateId) {
			if (scheduleService.getCollegeScheduleCountByDate(dateId) != 0) {
				request.setAttribute("msg", "删除失败：该日期内已有日程安排，请先删除这些日程！");
			} else {
				Dictionary dict = new Dictionary();
				DictionaryId dictId = new DictionaryId();
				dictId.setDictNo(Integer.valueOf("13"));
				dictId.setDictValue(dateId);
				dict.setId(dictId);
				scheduleService.deleteDict(dict);
				request.setAttribute("msg", "删除成功！");	
			}
		}
	
		return mapping.findForward("addDate");
	}

	// 保存或更新书院日程安排
	public ActionForward save(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		String Cdate = null;
		int CfTime, CtTime;
		DynaActionForm collegeScheduleForm = (DynaActionForm) form;
		Collegeschedulemodel collegeSchedule = (Collegeschedulemodel) collegeScheduleForm
				.get("schedulemanage");
		String collegeId = "notAppear";
		if (collegeSchedule.getCollegeId() != ""
				&& collegeSchedule.getCollegeId() != null) {
			collegeId = collegeSchedule.getCollegeId();
		}
		String fromDate = collegeSchedule.getFromdate();
		String fromTime = collegeSchedule.getFromtime();
		String toTime = collegeSchedule.getTotime();
		String toDate = fromDate;
		if (Integer.parseInt(String.valueOf(fromTime.charAt(4))) < 5) {
			fromTime = fromTime.substring(0, 2) + fromTime.substring(3, 4)
					+ "0";
		} else {
			fromTime = fromTime.substring(0, 2) + fromTime.substring(3, 4)
					+ "5";
		}
		if (Integer.parseInt(String.valueOf(toTime.charAt(4))) < 5) {
			toTime = toTime.substring(0, 2) + toTime.substring(3, 4) + "0";
		} else {
			toTime = toTime.substring(0, 2) + toTime.substring(3, 4) + "5";
		}
		// 时间段校验
		List schedules = scheduleService.getAllCollegeSchedule();
		Collegeschedulemodel collegeschedulemodelForUpdate = null;
		if (schedules.size() != 0) {
			for (int i = 0; i < schedules.size(); i++) {
				if (collegeSchedule.getScheduleId() != null
						&& collegeSchedule.getScheduleId().equals(
								((Collegeschedulemodel) schedules.get(i))
										.getScheduleId())) {
					collegeschedulemodelForUpdate = (Collegeschedulemodel) schedules
							.get(i);
					continue;
				}
				Cdate = ((Collegeschedulemodel) schedules.get(i)).getFromdate();
				CfTime = Integer
						.valueOf(
								((Collegeschedulemodel) schedules.get(i))
										.getFromtime()).intValue();
				CtTime = Integer.valueOf(
						((Collegeschedulemodel) schedules.get(i)).getTotime())
						.intValue();
				String CcollegeId = ((Collegeschedulemodel) schedules.get(i))
						.getCollegeId();
				if ((collegeId.equals("ALL")
						|| collegeId.equalsIgnoreCase(CcollegeId) || CcollegeId
						.equalsIgnoreCase("ALL"))
						&& Cdate.equalsIgnoreCase(fromDate)) {
					if ((Integer.valueOf(fromTime).intValue() > CfTime && Integer
							.valueOf(fromTime).intValue() < CtTime)
							|| (Integer.valueOf(toTime).intValue() > CfTime && Integer
									.valueOf(toTime).intValue() < CtTime)
							|| (Integer.valueOf(fromTime).intValue() <= CfTime && Integer
									.valueOf(toTime).intValue() >= CtTime)) {
						String msg = "与书院日程安排:"
								+ buildString((Collegeschedulemodel) schedules
										.get(i)) + "发生时间冲突，请检查。";
						request.setAttribute("msg", msg);
						return mapping.findForward("scheduleExist");
					}
				}
			}
		}

		// 检查与班级日程的冲突
		List classScheduleList;

		if (collegeId.equalsIgnoreCase("ALL")) {
			classScheduleList = scheduleService.getCScheduleByDate(fromDate);
		} else
			classScheduleList = scheduleService.getCScheduleByCollegeIdAndDate(
					collegeId, fromDate);
		for (int i = 0; i < classScheduleList.size(); i++) {
			Classschedulemodel classSchedulemodel = (Classschedulemodel) ((Map) classScheduleList
					.get(i)).get("cSchedulemodel");
			int cft = Integer.valueOf(classSchedulemodel.getFromtime())
					.intValue();
			int ctt = Integer.valueOf(classSchedulemodel.getTitime())
					.intValue();

			if ((Integer.valueOf(fromTime).intValue() > cft && Integer.valueOf(
					fromTime).intValue() < ctt)
					|| (Integer.valueOf(toTime).intValue() > cft && Integer
							.valueOf(toTime).intValue() < ctt)
					|| (Integer.valueOf(fromTime).intValue() <= cft && Integer
							.valueOf(toTime).intValue() >= ctt)) {

				if (StringUtils.isNotBlank(collegeSchedule.getScheduleId())
						&& classSchedulemodel.getCollegeSchedule() != null
						&& classSchedulemodel.getCollegeSchedule()
								.getScheduleId().equals(
										collegeSchedule.getScheduleId())) {
					if (Integer.valueOf(fromTime).intValue() <= cft
							&& Integer.valueOf(toTime).intValue() >= ctt)
						continue;
				}
				String msg = "与班级日程安排:" + buildString(classSchedulemodel)
						+ "发生时间冲突，请检查。";
				request.setAttribute("msg", msg);
				return mapping.findForward("scheduleExist");
			}
		}

		collegeSchedule.setFromdate(fromDate);
		collegeSchedule.setFromtime(fromTime);
		collegeSchedule.setTodate(toDate);
		collegeSchedule.setTotime(toTime);
		collegeSchedule.setCollegeId(collegeId);
		String message = null;
		if (collegeschedulemodelForUpdate == null) {
			scheduleService.save(collegeSchedule);
			message = "add";
			
		} else {
			if(!collegeschedulemodelForUpdate.getPositon().equals(collegeSchedule.getPositon())){
				String position = collegeSchedule.getPositon();
				//有所改动
				List cList = scheduleService.getClassSplitSchedulesInSameCollegeByCollegeschedule(collegeSchedule,"ALL",null);
				if(cList!=null){
					for(int i=0;i<cList.size();i++){
						Classschedulemodel csmodel = (Classschedulemodel)cList.get(i);
						csmodel.setPositon(position);
						scheduleService.updateClaSchedule(csmodel);
					}
				}				
			}
			BeanUtils.copyProperties(collegeschedulemodelForUpdate,
					collegeSchedule);
			scheduleService.update(collegeschedulemodelForUpdate);
			message = "add";
		}
		return new RedirectingActionForward(
				"/scheduleAction.do?method=load4List" + "&dateId=" + fromDate+"&message=" + message);

	}

	// 删除书院日程安排
	public ActionForward delete(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		DynaActionForm collegeScheduleForm = (DynaActionForm) form;
		Collegeschedulemodel collegeSchedule = (Collegeschedulemodel) collegeScheduleForm
				.get("schedulemanage");
		String scheduleId = collegeSchedule.getScheduleId();
		collegeSchedule = scheduleService.getCollegeScheduleById(scheduleId);
		if (collegeSchedule != null) {
			List list = scheduleService
					.getClassSplitSchedulesInSameCollegeByCollegeschedule(
							collegeSchedule,"ALL",null);
			if (list.size() == 0) {
				String message = null;
				scheduleService.delete(collegeSchedule);
				message = "del";
				return new ActionForward("/scheduleAction.do?method=load4List"
						+ "&dateId=" + collegeSchedule.getFromdate()+ "&message=" + message);
			} else {

				request.setAttribute("msg", "班级日程安排："
						+ buildString((Classschedulemodel) list.get(0))
						+ "依赖于此日程安排，请先删除班级日程安排");
				return mapping.findForward("scheduleExist");
			}
		}

		request.setAttribute("msg", "不存在这个书院安排");
		return mapping.findForward("scheduleExist");
	}

	private String buildString(Classschedulemodel classschedulemodel) {
		String fromtime = classschedulemodel.getFromtime();
		String totime = classschedulemodel.getTitime();
		StringBuffer s = new StringBuffer("［");
		s.append(fromtime.substring(0, 2)).append(":").append(
				fromtime.substring(2));
		s.append("--");
		s.append(totime.substring(0, 2)).append(":")
				.append(totime.substring(2));
		Classmodel classmodel = classService.getClassmodel(classschedulemodel.getClassId());
		Collegemodel collegemodel = new Collegemodel(); 
		if(classmodel!=null){
			collegemodel = collegeService.getCollege(classmodel.getYxCollege().getCollegeId());
		}
		String collegename = "";
		if(collegemodel!=null){
			collegename = collegemodel.getCollegeName();
		}
		if(collegename!=null&&!"".equals(collegename)){
			s.append("］［").append(collegename).append("］");
		}else{
			s.append("］［").append("全体").append("］");			
		}
		s.append("［");
		String classId = classschedulemodel.getClassId();
		if (classId.equalsIgnoreCase("all"))
			s.append("各");
		else
			s.append(classService.getClassmodel(classId).getClassNo());

		s.append("班］［").append(classschedulemodel.getPositon()).append("］［")
				.append(classschedulemodel.getMission()).append("］");

		String remark = classschedulemodel.getRemark();
		if (StringUtils.isNotBlank(remark)) {
			s.append("［").append(remark).append("］");
		}

		return s.toString();
	}

	private String buildString(Collegeschedulemodel collegeschedulemodel) {
		String fromtime = collegeschedulemodel.getFromtime();
		String totime = collegeschedulemodel.getTotime();
		StringBuffer s = new StringBuffer("［");
		s.append(fromtime.substring(0, 2)).append(":").append(
				fromtime.substring(2));
		s.append("--");
		s.append(totime.substring(0, 2)).append(":")
				.append(totime.substring(2));
		s.append("］［");

		String collegeId = collegeschedulemodel.getCollegeId();

		if (collegeId.equalsIgnoreCase("ALL")) {
			s.append("全体书院");
		} else
			s.append(collegeService.getCollege(
					collegeschedulemodel.getCollegeId()).getCollegeName());

		s.append("］［").append(collegeschedulemodel.getPositon()).append("］［")
				.append(collegeschedulemodel.getObject()).append("］［").append(
						collegeschedulemodel.getMission()).append("］");
		String remark = collegeschedulemodel.getRemark();
		if (StringUtils.isNotBlank(remark)) {
			s.append("［").append(remark).append("］");
		}

		return s.toString();
	}

	// 保存或更新班级日程安排
	public ActionForward classSave(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		DynaActionForm classScheduleForm = (DynaActionForm) form;
		Classschedulemodel classSchedule = (Classschedulemodel) classScheduleForm
				.get("classSchedulemanage");

		String classId = classSchedule.getClassId();

		String fromDate = classSchedule.getFromdate();

		String fromTime = classSchedule.getFromtime();
		String toTime = classSchedule.getTitime();
		String toDate = fromDate;
		if (Integer.parseInt(String.valueOf(fromTime.charAt(4))) < 5) {
			fromTime = fromTime.substring(0, 2) + fromTime.substring(3, 4)
					+ "0";
		} else {
			fromTime = fromTime.substring(0, 2) + fromTime.substring(3, 4)
					+ "5";
		}
		if (Integer.parseInt(String.valueOf(toTime.charAt(4))) < 5) {
			toTime = toTime.substring(0, 2) + toTime.substring(3, 4) + "0";
		} else {
			toTime = toTime.substring(0, 2) + toTime.substring(3, 4) + "5";
		}

		String collegeId = request.getParameter("collegeId");

		List classSchedules = scheduleService
				.getClassScheduleExcludeSplitsByCollegeIdAndDate(collegeId,classId,
						fromDate, classSchedule.getScheduleId());
//		List collegeSchedules = scheduleService
//				.getCollegeScheduleByCollegeIdAndDate(collegeId, fromDate);

		// 与班级的时间段校验
		for (int i = 0; i < classSchedules.size(); i++) {
			Classschedulemodel classSchedulemodel = (Classschedulemodel) (classSchedules
					.get(i));

			int classFromTime = Integer.valueOf(
					classSchedulemodel.getFromtime()).intValue();
			int classToTime = Integer.valueOf(classSchedulemodel.getTitime())
					.intValue();

			if ((Integer.valueOf(fromTime).intValue() > classFromTime && Integer
					.valueOf(fromTime).intValue() < classToTime)
					|| (Integer.valueOf(toTime).intValue() > classFromTime && Integer
							.valueOf(toTime).intValue() < classToTime)
					|| (Integer.valueOf(fromTime).intValue() <= classFromTime && Integer
							.valueOf(toTime).intValue() >= classToTime)) {

				String msg = "与班级日程安排:" + buildString(classSchedulemodel)
						+ "发生时间冲突，请检查。";
				request.setAttribute("msg", msg);
				return mapping.findForward("scheduleExist");
			}
		}

		// 与学院的时间段校验
//		if (collegeSchedules.size() != 0) {
//			Collegeschedulemodel collegeSchedulemodel;
//			for (int j = 0; j < collegeSchedules.size(); j++) {
//				collegeSchedulemodel = (Collegeschedulemodel) collegeSchedules
//						.get(j);
//				int collegeFromTime = Integer.valueOf(
//						collegeSchedulemodel.getFromtime()).intValue();
//				int collegeToTime = Integer.valueOf(
//						collegeSchedulemodel.getTotime()).intValue();
//
//				if ((Integer.valueOf(fromTime).intValue() > collegeFromTime && Integer
//						.valueOf(fromTime).intValue() < collegeToTime)
//						|| (Integer.valueOf(toTime).intValue() > collegeFromTime && Integer
//								.valueOf(toTime).intValue() < collegeToTime)
//						|| (Integer.valueOf(fromTime).intValue() <= collegeFromTime && Integer
//								.valueOf(toTime).intValue() >= collegeToTime)) {
//
//					String msg = "与书院日程安排:" + buildString(collegeSchedulemodel)
//							+ "发生时间冲突，请检查。";
//					request.setAttribute("msg", msg);
//					return mapping.findForward("scheduleExist");
//				}
//
//			}
//		}

		classSchedule.setFromdate(fromDate);
		classSchedule.setFromtime(fromTime);
		classSchedule.setTodate(toDate);
		classSchedule.setTitime(toTime);
		classSchedule.setClassId(classId);
		classSchedule.setCollegeId(collegeId);
		String msg = null;
		ActionMessages messages = new ActionMessages();

		if (StringUtils.isBlank(classSchedule.getScheduleId())) {
			scheduleService.saveClaSchedule(classSchedule);
			msg = "add";
			request.setAttribute("msg", msg);
		} else {
			scheduleService.updateClaSchedule(classSchedule);
			msg = "add";
			request.setAttribute("msg", msg);	
		}

		String setup = request.getParameter("setup");
		if (setup != null && setup.equals("true")) {
			return new RedirectingActionForward(
					"/scheduleAction.do?method=load4ViewClass" + "&classId="
							+ classId + "&collegeId=" + collegeId
							+ "&msg=" + msg
							+ "&setup=true");
		} else
			return new RedirectingActionForward(
					"/scheduleAction.do?method=load4classList" + "&dateId="
							+ fromDate + "&collegeId=" + collegeId);

	}

	// 保存或更新分拆的班级日程安排
	public ActionForward classSplitSave(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		DynaActionForm classScheduleForm = (DynaActionForm) form;
		Classschedulemodel classSchedule = (Classschedulemodel) classScheduleForm
				.get("classSchedulemanage");

		Collegeschedulemodel collegeschedule = (Collegeschedulemodel) classScheduleForm
				.get("schedulemanage");
		String newcollegeId = collegeschedule.getCollegeId();
		classSchedule.setCollegeId(collegeschedule.getCollegeId());
		collegeschedule = scheduleService
				.getCollegeScheduleById(collegeschedule.getScheduleId());

		classSchedule.setCollegeSchedule(collegeschedule);

		classSchedule.setFromdate(collegeschedule.getFromdate());
		classSchedule.setTodate(collegeschedule.getFromdate());

		String fromTime = classSchedule.getFromtime();
		String toTime = classSchedule.getTitime();

		if (Integer.parseInt(String.valueOf(fromTime.charAt(4))) < 5) {
			fromTime = fromTime.substring(0, 2) + fromTime.substring(3, 4)
					+ "0";
		} else {
			fromTime = fromTime.substring(0, 2) + fromTime.substring(3, 4)
					+ "5";
		}
		if (Integer.parseInt(String.valueOf(toTime.charAt(4))) < 5) {
			toTime = toTime.substring(0, 2) + toTime.substring(3, 4) + "0";
		} else {
			toTime = toTime.substring(0, 2) + toTime.substring(3, 4) + "5";
		}

		classSchedule.setFromtime(fromTime);
		classSchedule.setTitime(toTime);

		// 与班级的时间段校验

		List schedules = scheduleService
				.getClassSplitSchedulesInSameCollegeByCollegeschedule(
						collegeschedule,newcollegeId, classSchedule.getScheduleId());

		String classId = classSchedule.getClassId();
		if (schedules.size() != 0) {
			for (int i = 0; i < schedules.size(); i++) {
				Classschedulemodel classSchedulemodel = (Classschedulemodel) schedules
						.get(i);

				int classFromTime = Integer.valueOf(
						classSchedulemodel.getFromtime()).intValue();
				int classToTime = Integer.valueOf(
						classSchedulemodel.getTitime()).intValue();
				if (classSchedulemodel.getClassId().equals(classId)
						|| classId.equalsIgnoreCase("all")
						|| classSchedulemodel.getClassId().equalsIgnoreCase(
								"all")) {
					if ((Integer.valueOf(fromTime).intValue() > classFromTime && Integer
							.valueOf(fromTime).intValue() < classToTime)
							|| (Integer.valueOf(toTime).intValue() > classFromTime && Integer
									.valueOf(toTime).intValue() < classToTime)
							|| (Integer.valueOf(fromTime).intValue() <= classFromTime && Integer
									.valueOf(toTime).intValue() >= classToTime)) {
						
						String msg = "与班级日程安排:"
								+ buildString(classSchedulemodel)
								+ "发生时间冲突，请检查。";
						request.setAttribute("msg", msg);
						return mapping.findForward("scheduleExist");
					}
				}
			}
		}
		String msg = null;
		if (StringUtils.isBlank(classSchedule.getScheduleId())){
			scheduleService.saveClaSchedule(classSchedule);
			msg = "add";
		}else{
			scheduleService.updateClaSchedule(classSchedule);
			msg = "add";
		}
		return new RedirectingActionForward(
				"/scheduleAction.do?method=load4classList" + "&dateId="
						+ classSchedule.getFromdate()+ "&msg="
						+ msg + "&collegeId="
						+ classSchedule.getCollegeId());

	}

	// 点击删除按钮删除班级日程安排
	public ActionForward classDelete(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		DynaActionForm classScheduleForm = (DynaActionForm) form;
		Classschedulemodel classSchedule = (Classschedulemodel) classScheduleForm
				.get("classSchedulemanage");
		String scheduleId = classSchedule.getScheduleId();

		classSchedule = scheduleService.getClassScheduleById(scheduleId);
		String msg = null;
		if (scheduleId != "" && scheduleId != null) {
			scheduleService.deleteClaSchedule(classSchedule);
			msg = "del";
		}
		String setup = request.getParameter("setup");
		if (setup != null && setup.equals("true")) {
			return new RedirectingActionForward(
					"/scheduleAction.do?method=load4ViewClass" + "&classId="
							+ classSchedule.getClassId() + "&collegeId="
							+ classSchedule.getCollegeId() +"&msg="
							+ msg + "&setup=true");
		} else
			return new RedirectingActionForward(
					"/scheduleAction.do?method=load4classList" + "&dateId="
							+ classSchedule.getFromdate() + "&collegeId="
							+ classSchedule.getCollegeId());
	}

	// 初始化书院日程安排
	/**
	 * Description: 书院日程安排
	 * 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 * @return Modify History: 2006-5-31 jackey update
	 */
	public ActionForward load4List(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		String dateId = request.getParameter("dateId");
		List collegeList = collegeService.getAllCollegeByfdxy();
		List scheduledateList = scheduleService.getScheduleDates();

		if (dateId == null) {
			dateId = ((Dictionary) scheduledateList.get(0)).getId()
					.getDictValue();
		}
		if (request.getParameter("message") != null&&"add".equals(request.getParameter("message"))) {
			request.setAttribute("msg", "添加或修改成功");
		}
		if (request.getParameter("message") != null&&"del".equals(request.getParameter("message"))) {
			request.setAttribute("msg", "删除成功");
		}		
		request.setAttribute("dateId", dateId);

		List scheduleList = scheduleService.getCollegeScheduleyDate(dateId);

		request.setAttribute("collegeList", collegeList);
		request
				.setAttribute("collegeCount", String
						.valueOf(collegeList.size()));
		request.setAttribute("scheduleList", scheduleList);
		request.setAttribute("scheduledateList", scheduledateList);
		return mapping.findForward("setupSchedule");
	}

	// 初始化班级日程安排
	public ActionForward load4classList(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {

		String dateId = request.getParameter("dateId");

		DynaActionForm college = (DynaActionForm) form;
		String collegeId = college.getString("scheduleCollegeId");
		if (collegeId == null || collegeId.length() == 0) {
			collegeId = request.getParameter("collegeId");
		}
		if (request.getParameter("msg") != null&&"add".equals(request.getParameter("msg"))) {
			request.setAttribute("msg", "修改成功");
		}
		List date = null;
		List colleges = scheduleService.getAllCollegeByfdxy();
		if (colleges.size() != 0) {
			request.setAttribute("colleges", colleges);
			List classSchedules = null, schedules = null;

			if (collegeId == null || collegeId.length() == 0) {
				collegeId = ((Collegemodel) colleges.get(0)).getCollegeId();
			}
			date = scheduleService.getScheduleDates();

			if (dateId == null) {
				dateId = ((Dictionary) date.get(0)).getId().getDictValue();
			}

			request.setAttribute("dateId", dateId);

			request.setAttribute("scheduledateList", date);
			// 根据书院id获取该书院及所有班级日程安排
			schedules = scheduleService.getCollegeScheduleByCollegeIdAndDate(
					collegeId, dateId);

			classSchedules = scheduleService
					.getSplittedCScheduleByCollegeIdAndDate(collegeId, dateId);
			for (int i = 0; i < schedules.size(); i++) {
				Collegeschedulemodel collegeschedulemodel = (Collegeschedulemodel) schedules
						.get(i);
				for (int j = 0; j < classSchedules.size(); j++) {
					Classschedulemodel classschedulemodel = (Classschedulemodel) ((Map) classSchedules
							.get(j)).get("cSchedulemodel");
					Collegeschedulemodel collegeschedule = classschedulemodel
							.getCollegeSchedule();
					if (collegeschedule != null
							&& collegeschedule.getScheduleId().equals(
									collegeschedulemodel.getScheduleId())) {
						schedules.remove(i);
						i--;
						break;
					}
				}
			}

			// Collegeschedulemodel collegeSchedulemodel = new
			// Collegeschedulemodel();
			// Classschedulemodel classschedulemodel = new Classschedulemodel();
			// String cdate, cft, ctt, cldate, clft, cltt;
			// int size = schedules.size(), i = 0;
			//
			// if (schedules.size() != 0) {
			// while (i < size) {
			// collegeSchedulemodel = (Collegeschedulemodel) schedules
			// .get(i);
			//
			// cdate = collegeSchedulemodel.getFromdate();
			// cft = collegeSchedulemodel.getFromtime();
			// ctt = collegeSchedulemodel.getTotime();
			// // 若书院日程已被拆完，则丢弃该书院日程
			// if (Integer.valueOf(collegeSchedulemodel.getFromtime())
			// .intValue() >= Integer.valueOf(
			// collegeSchedulemodel.getTotime()).intValue()) {
			// i++;
			// break;
			// }
			//
			// boolean split = false;
			// for (int j = 0; j < classSchedules.size(); j++) {
			// classschedulemodel = (Classschedulemodel) ((Map) classSchedules
			// .get(j)).get("cSchedulemodel");
			// cldate = classschedulemodel.getFromdate();
			// clft = classschedulemodel.getFromtime();
			// cltt = classschedulemodel.getTitime();
			// if (cdate.equals(cldate)
			// && Integer.valueOf(cft).intValue() <= Integer
			// .valueOf(clft).intValue()
			// && Integer.valueOf(ctt).intValue() >= Integer
			// .valueOf(cltt).intValue()) {
			// if (!clft.equals(cft)) {
			// Collegeschedulemodel temp = new Collegeschedulemodel();
			// temp.setCollegeId(collegeSchedulemodel
			// .getCollegeId());
			// temp.setFromdate(collegeSchedulemodel
			// .getFromdate());
			// temp.setFromtime(collegeSchedulemodel
			// .getFromtime());
			// temp.setMission(collegeSchedulemodel
			// .getMission());
			// temp
			// .setObject(collegeSchedulemodel
			// .getObject());
			// temp.setPositon(collegeSchedulemodel
			// .getPositon());
			// temp
			// .setRemark(collegeSchedulemodel
			// .getRemark());
			// temp.setScheduleId(collegeSchedulemodel
			// .getScheduleId());
			// temp.setTotime(clft);
			// schedules.add(temp);
			// }
			// if (!cltt.equals(ctt)) {
			// Collegeschedulemodel temp2 = new Collegeschedulemodel();
			// temp2.setFromtime(cltt);
			// temp2.setTotime(ctt);
			// temp2.setCollegeId(collegeSchedulemodel
			// .getCollegeId());
			// temp2.setFromdate(collegeSchedulemodel
			// .getFromdate());
			// temp2.setMission(collegeSchedulemodel
			// .getMission());
			// temp2.setObject(collegeSchedulemodel
			// .getObject());
			// temp2.setPositon(collegeSchedulemodel
			// .getPositon());
			// temp2.setRemark(collegeSchedulemodel
			// .getRemark());
			// temp2.setScheduleId(collegeSchedulemodel
			// .getScheduleId());
			// schedules.add(temp2);
			// }
			// schedules.remove(i);
			// split = true;
			// break;
			// }
			// }
			// size = schedules.size();
			// if (!split) {
			// i++;
			// }
			// }
			// }
			college.set("scheduleCollegeId", collegeId);
			request.setAttribute("scheduleCollegeId", collegeId);
			request.setAttribute("collegeSchedule", schedules);

			if (classSchedules != null) {
				request.setAttribute("classSchedules", classSchedules);
			}

		}
		return mapping.findForward("setupClassSchedule");
	}

	// 点击书院日程安排的信息
	public ActionForward cRevise(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		DynaActionForm scheduleForm = (DynaActionForm) form;
		List date = studentService.getDiction("13");
		request.setAttribute("dateList", date);
		String scheduleId = request.getParameter("scheduleId");
		request.setAttribute("scheduleId", scheduleId);
		Collegeschedulemodel collegeSchedule = scheduleService
				.getCollegeScheduleById(scheduleId);
		scheduleForm.set("schedulemanage", collegeSchedule);
		if (collegeService.getAllCollegeByfdxy() != null) {
			List colleges = collegeService.getAllCollegeByfdxy();
			request.setAttribute("colleges", colleges);
		}
		if (request.getParameter("popedem") != null) {
			request.setAttribute("popedem", "false");
		}
		return mapping.findForward("passRevise");
	}

	// 点击班级日程安排的信息
	public ActionForward cScheduleRevise(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		DynaActionForm scheduleForm = (DynaActionForm) form;
		List classes = null;
		List date = scheduleService.getScheduleDates();
		request.setAttribute("dateList", date);
		String scheduleId = request.getParameter("scheduleId");

		String collegeId = request.getParameter("collegeId");
		request.setAttribute("scheduleId", scheduleId);
		Classschedulemodel classSchedule = scheduleService
				.getClassScheduleById(scheduleId);
		scheduleForm.set("classSchedulemanage", classSchedule);
		classes = classService.getClassbyCollegeId(collegeId);
		if (classes != null) {
			request.setAttribute("collegeId", collegeId);
			request.setAttribute("classes", classes);
			request.setAttribute("classScheduleId", scheduleId);
		}
		if (request.getParameter("popedem") != null) {
			request.setAttribute("popedem", "false");
		}
		return mapping.findForward("cScheduleRevise");
	}

	public ActionForward editSplitCollegeSchedule(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		DynaActionForm scheduleForm = (DynaActionForm) form;
		List classes = null;

		String scheduleId = request.getParameter("scheduleId");

		if (StringUtils.isNotBlank(scheduleId)) {
			Classschedulemodel classschedulemodel = scheduleService
					.getClassScheduleById(scheduleId);

			Collegeschedulemodel collegeschedulemodel = classschedulemodel
					.getCollegeSchedule();

			String fromtime = collegeschedulemodel.getFromtime();
			String totime = collegeschedulemodel.getTotime();
			scheduleForm.set("schedulemanage", collegeschedulemodel);
			scheduleForm.set("classSchedulemanage", classschedulemodel);
			String newcollegeId = request.getParameter("collegeId");
			classes = classService.getClassbyCollegeId(newcollegeId);
			if (classes != null) {
				request.setAttribute("classes", classes);
			}

			List date = scheduleService.getScheduleDates();

			String dateId = collegeschedulemodel.getFromdate();
			for (int i = 0; i < date.size(); i++) {
				Dictionary dictionary = (Dictionary) date.get(i);

				if (dictionary.getId().getDictValue().equals(dateId)) {
					request.setAttribute("date", dictionary.getDictCaption());
					break;
				}
			}

			request.setAttribute("fromtime", fromtime.substring(0, 2) + ":"
					+ fromtime.substring(2));
			request.setAttribute("totime", totime.substring(0, 2) + ":"
					+ totime.substring(2));

			List list = scheduleService
					.getClassSplitSchedulesInSameCollegeByCollegeschedule(
							collegeschedulemodel,newcollegeId, null);

			List classSchedules = new ArrayList();
			for (int i = 0; i < list.size(); i++) {
				Classschedulemodel classschedule = (Classschedulemodel) list
						.get(i);
				String classId = classschedule.getClassId();
				String classNo;
				if (classId.equalsIgnoreCase("all")) {
					classNo = "各";
				} else
					classNo = classService.getClassmodel(
							classschedule.getClassId()).getClassNo();
				Map map = new HashMap();
				map.put("classNo", classNo);
				map.put("classschedule", classschedule);
				classSchedules.add(map);
			}
			request.setAttribute("classSchedules", classSchedules);
			return mapping.findForward("splitCollegeSchedule");
		}

		request.setAttribute("msg", "书院日程参数不能为空");
		return mapping.findForward("scheduleExist");
	}

	public ActionForward splitCollegeSchedule(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		DynaActionForm scheduleForm = (DynaActionForm) form;
		List classes = null;

		String scheduleId = request.getParameter("scheduleId");

		if (StringUtils.isNotBlank(scheduleId)) {
			Collegeschedulemodel collegeschedulemodel = scheduleService
					.getCollegeScheduleById(scheduleId);

			Classschedulemodel classschedulemodel = (Classschedulemodel) scheduleForm
					.get("classSchedulemanage");

			String fromtime, totime;

			fromtime = collegeschedulemodel.getFromtime();
			totime = collegeschedulemodel.getTotime();
			scheduleForm.set("schedulemanage", collegeschedulemodel);
			classschedulemodel.setFromtime(fromtime);
			classschedulemodel.setTitime(totime);
			classschedulemodel.setPositon(collegeschedulemodel.getPositon());
			classschedulemodel.setMission(collegeschedulemodel.getMission());
			String newcollegeId = request.getParameter("collegeId");
			classes = classService.getClassbyCollegeId(newcollegeId);
			if (classes != null) {
				request.setAttribute("classes", classes);
			}

			List date = scheduleService.getScheduleDates();

			String dateId = collegeschedulemodel.getFromdate();
			for (int i = 0; i < date.size(); i++) {
				Dictionary dictionary = (Dictionary) date.get(i);

				if (dictionary.getId().getDictValue().equals(dateId)) {
					request.setAttribute("date", dictionary.getDictCaption());
					break;
				}
			}

			request.setAttribute("fromtime", fromtime.substring(0, 2) + ":"
					+ fromtime.substring(2));
			request.setAttribute("totime", totime.substring(0, 2) + ":"
					+ totime.substring(2));

			List list = scheduleService
					.getClassSplitSchedulesInSameCollegeByCollegeschedule(
							collegeschedulemodel,newcollegeId, null);

			List classSchedules = new ArrayList();
			for (int i = 0; i < list.size(); i++) {
				Classschedulemodel classschedule = (Classschedulemodel) list
						.get(i);
				String classId = classschedule.getClassId();
				String classNo;
				if (classId.equalsIgnoreCase("all")) {
					classNo = "各";
				} else
					classNo = classService.getClassmodel(
							classschedule.getClassId()).getClassNo();
				Map map = new HashMap();
				map.put("classNo", classNo);
				map.put("classschedule", classschedule);
				classSchedules.add(map);
			}
			
//			for (int i = 0; i < list.size(); i++) {
//				Classschedulemodel classschedule = (Classschedulemodel) list
//						.get(i);
//				String classId = classschedule.getClassId();
//				if (classId.equalsIgnoreCase("all")) {
//					classschedule.setClassId("all");
//				} else
//					classschedule.setClassId(classService.getClassmodel(
//							classschedule.getClassId()).getClassNo());
//			}
			request.setAttribute("classSchedules", classSchedules);
			return mapping.findForward("splitCollegeSchedule");
		}

		request.setAttribute("msg", "书院日程参数不能为空");
		return mapping.findForward("scheduleExist");
	}

	// 点击书院日程安排的添加
	public ActionForward addCollegeSchedule(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		if (collegeService.getAllCollegeByfdxy() != null) {
			DynaActionForm actionForm = (DynaActionForm) form;
			Collegeschedulemodel collegeschedulemodel = new Collegeschedulemodel();
			collegeschedulemodel.setFromdate(request.getParameter("dateId"));
			actionForm.set("schedulemanage", collegeschedulemodel);
			List colleges = collegeService.getAllCollegeByfdxy();
			request.setAttribute("colleges", colleges);
			request
					.setAttribute("dateList", scheduleService
							.getScheduleDates());

		}
		return mapping.findForward("addCollegeSchedule");
	}

	// 点击班级日程安排的添加
	public ActionForward addClassSchedule(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {

		String collegeId = request.getParameter("collegeId");

		if (collegeId != null && collegeId.length() > 0) {
			DynaActionForm scheduleForm = (DynaActionForm) form;

			Classschedulemodel classschedulemodel = new Classschedulemodel();
			classschedulemodel.setCollegeId(collegeId);
			classschedulemodel.setFromdate(request.getParameter("dateId"));

			scheduleForm.set("classSchedulemanage", classschedulemodel);

			List classes = classService.getClassbyCollegeId(collegeId);
			if (classes.size() == 0) {
				request.setAttribute("msg", "错误：该书院尚未建立班级！请先建立班级。");
				return mapping.findForward("scheduleExist");
			}
			request.setAttribute("classes", classes);
			request.setAttribute("dateList", studentService.getDiction("13"));
			request.setAttribute("collegeId", collegeId);
			return mapping.findForward("addClassSchedule");
		} else {
			request.setAttribute("msg", "错误：书院参数不能为空");
			return mapping.findForward("scheduleExist");
		}

	}

	public ActionForward addSingleClassSchedule(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {

		String collegeId = request.getParameter("collegeId");
		String classId = request.getParameter("classId");
		if (collegeId != null && collegeId.length() > 0) {
			DynaActionForm scheduleForm = (DynaActionForm) form;

			Classschedulemodel classschedulemodel = new Classschedulemodel();
			classschedulemodel.setCollegeId(collegeId);

			classschedulemodel.setClassId(classId);
			scheduleForm.set("classSchedulemanage", classschedulemodel);

			request.setAttribute("classNo", classService.getClassmodel(classId)
					.getClassNo());
			request
					.setAttribute("dateList", scheduleService
							.getScheduleDates());
			request.setAttribute("collegeId", collegeId);
			request.setAttribute("setup", request.getParameter("setup"));
			return mapping.findForward("addSingleClassSchedule");
		} else {
			request.setAttribute("msg", "错误：书院参数不能为空");
			return mapping.findForward("scheduleExist");
		}

	}

	public ActionForward editSingleClassSchedule(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		String scheduleId = request.getParameter("scheduleId");
		if (scheduleId != null && scheduleId.length() > 0) {
			DynaActionForm scheduleForm = (DynaActionForm) form;

			Classschedulemodel classschedulemodel = scheduleService
					.getClassScheduleById(scheduleId);
			scheduleForm.set("classSchedulemanage", classschedulemodel);

			request.setAttribute("classNo", classService.getClassmodel(
					classschedulemodel.getClassId()).getClassNo());
			request
					.setAttribute("dateList", scheduleService
							.getScheduleDates());
			request
					.setAttribute("collegeId", classschedulemodel
							.getCollegeId());
			request.setAttribute("setup", request.getParameter("setup"));
			return mapping.findForward("addSingleClassSchedule");
		} else {
			request.setAttribute("msg", "错误：scheduleId参数不能为空");
			return mapping.findForward("scheduleExist");
		}
	}

	public ActionForward load4ViewAll(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		request.setAttribute("view", Boolean.TRUE);
		List collegeList = collegeService.getAllCollegeByfdxy();
		List scheduleList = scheduleService.getAllCollegeSchedule();
		List scheduledateList = scheduleService.getScheduleDates();
		request.setAttribute("collegeList", collegeList);
		request
				.setAttribute("collegeCount", String
						.valueOf(collegeList.size()));
		request.setAttribute("scheduleList", scheduleList);
		request.setAttribute("scheduledateList", scheduledateList);
		return mapping.findForward("initSchedule");
	}

	public ActionForward load4ViewAll2(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		List collegeList = collegeService.getAllCollegeByfdxy();
		List scheduledateList = scheduleService.getScheduleDates();
		Map schedulesMap = new HashMap();
		for (int i = 0; i < scheduledateList.size(); i++) {
			Dictionary date = (Dictionary) scheduledateList.get(i);
			schedulesMap.put(date, scheduleService.getCollegeScheduleyDate(date
					.getId().getDictValue()));
		}

		if (collegeList.size() > 0) {
			request.setAttribute("collegeList", collegeList);
			request.setAttribute("collegeCount",
					new Integer(collegeList.size()));
			request.setAttribute("schedulesMap", schedulesMap);
			request.setAttribute("scheduledateList", scheduledateList);
		}
		return mapping.findForward("viewAll");
	}

	public ActionForward load4ViewCollege(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		request.setAttribute("view", Boolean.TRUE);
		DynaActionForm college = (DynaActionForm) form;
		String collegeId = null;
		List date = null;
		List colleges = scheduleService.getAllCollegeByfdxy();
		if (colleges.size() > 0) {
			request.setAttribute("colleges", colleges);

			if (request.getParameter("collegeId") != null) {
				collegeId = request.getParameter("collegeId");
			}
			// 初始化时获取第一个书院id
			else {
				collegeId = ((Collegemodel) colleges.get(0)).getCollegeId();
			}

			request.setAttribute("collegeName", collegeService.getCollege(
					collegeId).getCollegeName());

			date = scheduleService.getScheduleDates();
			request.setAttribute("scheduledateList", date);
			// 根据书院id获取该书院及所有班级日程安排

			Map schedulesMap = new HashMap();
			Map classSchedulesMap = new HashMap();
			for (int i = 0; i < date.size(); i++) {
				Dictionary d = (Dictionary) date.get(i);

				List collegeSchedules = scheduleService
						.getCollegeScheduleByCollegeIdAndDate(collegeId, d
								.getId().getDictValue());
				schedulesMap.put(d, collegeSchedules);

				for (int j = 0; j < collegeSchedules.size(); j++) {
					Collegeschedulemodel collegeschedule1 = (Collegeschedulemodel) collegeSchedules
							.get(j);
					Collegeschedulemodel collegeschedule = scheduleService.getCollegeScheduleById(collegeschedule1.getScheduleId());
					List classSchedules = scheduleService
							.getClassSplitSchedulesInSameCollegeByCollegeschedule(
									collegeschedule,collegeId, null);
					if (classSchedules.size() > 0) {
						for (int m = 0; m < classSchedules.size(); m++) {
							Classschedulemodel classschedulemodel = (Classschedulemodel) classSchedules
									.get(m);
							if("all".equals(classschedulemodel.getClassId())){
								classschedulemodel.setClassId("各班");
							}else{
								classschedulemodel.setClassId(classService
										.getClassmodel(
												classschedulemodel.getClassId())
										.getClassNo());
							}
							
							
						}

						classSchedulesMap.put(collegeschedule, classSchedules);
					}
				}

			}

			college.set("scheduleCollegeId", collegeId);
			request.setAttribute("scheduleCollegeId", collegeId);
			request.setAttribute("collegeSchedule", schedulesMap);
			request.setAttribute("classSchedules", classSchedulesMap);

		}
		return mapping.findForward("load4classList");
	}

	private void addCollegeToList(List collegeList, Collegemodel collegemodel) {
		for (int j = 0; j < collegeList.size(); j++) {
			if (((Collegemodel) collegeList.get(j)).getCollegeId().equals(
					collegemodel.getCollegeId()))
				return;
		}

		collegeList.add(collegemodel);
	}

	public ActionForward load4ViewClass(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		DynaActionForm actionForm = (DynaActionForm) form;
		Account role = null;

		boolean isSupper = true;

		List classSchedules = null, collegeSchedules = null;

		if (request.getSession().getAttribute("accountPerson") != null) {
			role = (Account) request.getSession().getAttribute("accountPerson");
		}
		if (request.getParameter("msg") != null&&"add".equals(request.getParameter("msg"))) {
			request.setAttribute("msg", "添加或修改成功");
		}
		if (request.getParameter("msg") != null&&"del".equals(request.getParameter("msg"))) {
			request.setAttribute("msg", "删除成功");
		}
		List classesList = null;
		List collegeList = null;

		List list = managerService.getManagerByNo(role.getName());
		if (list.size() > 0) {
			Managermodel managermodel = (Managermodel) list.get(0);
			if (managermodel != null) {
				if (managerService.inRole(managermodel.getManagerId(), "11")) {
					isSupper = false;
					List collegeManagerList = managerService
							.getCollegeAssistantByManagerId(managermodel
									.getManagerId());
					// xuegongzuzhang
					if (collegeManagerList.size() > 0) {

						collegeList = new ArrayList();
						classesList = classService.getClassmodel();
						for (int i = 0; i < collegeManagerList.size(); i++) {
							Collegemanager collegemanager = (Collegemanager) collegeManagerList
									.get(i);
							Collegemodel collegemodel = collegeService
									.getCollege(collegemanager.getId()
											.getCollegeId());
							if (collegemodel != null)
								addCollegeToList(collegeList, collegemodel);
						}
					}

				}

				// fudaoyuan
				if (managerService.inRole(managermodel.getManagerId(), "22")
						|| managerService.inRole(managermodel.getManagerId(),
								"21")) {
					isSupper = false;
					List cList = managerService
							.getClassAssistantByManagerId(managermodel
									.getManagerId());
					if (cList.size() > 0) {
						collegeList = new ArrayList();
						classesList = new ArrayList();
						for (int i = 0; i < cList.size(); i++) {
							Classmanager classmanager = (Classmanager) (cList
									.get(i));
							String classId = classmanager.getId().getClassId();
							Collegemodel collegemodel = classService
									.getCollegeByClassId(classId);
							if (collegemodel != null) {

								classesList.add(classService
										.getClassmodel(classId));
								addCollegeToList(collegeList, collegemodel);

							}
						}
					}

				}
			}
		}
		// xuesheng
		if (collegeList == null) {			
			String personCode = role.getPerson().getPersonCode();
			Studentmodel studentmodel = studentService.getStudent(personCode);
			if (studentmodel != null) {
				isSupper = false;
				Classmodel classmodel = studentmodel.getYxClass();

				String collegeId = classmodel.getYxCollege().getCollegeId();
				Collegemodel collegemodel = collegeService
						.getCollege(collegeId);
				collegeList = new ArrayList();
				classesList = new ArrayList();
				collegeList.add(collegemodel);
				classesList.add(classmodel);
			}
		}

		// super
		if (isSupper) {
			classesList = classService.getClassmodelbyschoolId("0001");
			collegeList = collegeService.getAllCollegeByfdxy();
		}
		request.setAttribute("collegeList", collegeList);
		request.setAttribute("classList", classesList);

		List scheduledateList = scheduleService.getScheduleDates();
		request.setAttribute("scheduledateList", scheduledateList);

		String classId = request.getParameter("classId");
		if (StringUtils.isBlank(classId))
			classId = ((Classschedulemodel) actionForm
					.get("classSchedulemanage")).getClassId();
		else {
			((Classschedulemodel) actionForm.get("classSchedulemanage"))
					.setClassId(classId);
		}

		if (classId == null || classId.equals("")) {
			if(collegeList!= null){
			if (collegeList.size() == 1) {
				((Classschedulemodel) actionForm.get("classSchedulemanage"))
						.setCollegeId(((Collegemodel) collegeList.get(0))
								.getCollegeId());
			}
			if (classesList.size() == 1)
				classId = ((Classmodel) classesList.get(0)).getClassId();
			}

		}

		if (classId != null && !classId.equals("")) {
			Classmodel classmodel = (Classmodel) classService
					.getClassmodel(classId);

			String collegeId = classmodel.getYxCollege().getCollegeId();

			((Classschedulemodel) actionForm.get("classSchedulemanage"))
					.setCollegeId(collegeId);

			classSchedules = scheduleService.getClassScheduleByClassId(classId,
					collegeId);
//			collegeSchedules = scheduleService
//					.getCollegeScheduleByCollegeId(collegeId);

//			for (int i = 0; i < collegeSchedules.size(); i++) {
//				Collegeschedulemodel collegeschedulemodel = (Collegeschedulemodel) collegeSchedules
//						.get(i);
//				for (int j = 0; j < classSchedules.size(); j++) {
//					Classschedulemodel classschedulemodel = (Classschedulemodel) ((Map) classSchedules
//							.get(j)).get("cSchedulemodel");
//					Collegeschedulemodel collegeschedule = classschedulemodel
//							.getCollegeSchedule();
//					if (collegeschedule != null
//							&& collegeschedule.getScheduleId().equals(
//									collegeschedulemodel.getScheduleId())) {
//						collegeSchedules.remove(i);
//						i--;
//						break;
//					}
//				}
//			}
			actionForm.set("scheduleCollegeId", collegeId);
			request.setAttribute("scheduleCollegeId", collegeId);
			request.setAttribute("collegeSchedule", collegeSchedules);

			request.setAttribute("collegeName", collegeService.getCollege(
					collegeId).getCollegeName());
			request.setAttribute("className", classService.getClassmodel(
					classId).getClassNo());

			if (classSchedules.size() != 0) {
				request.setAttribute("classSchedules", classSchedules);
			}

			request.setAttribute("classId", classId);
		}

		request.setAttribute("setup", request.getParameter("setup"));

		return mapping.findForward("load4ViewClass");

	}

}