package com.kingstargroup.conference.action.attendee;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.ajaxanywhere.AAUtils;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.conference.common.DateUtilExtend;
import com.kingstargroup.conference.common.GetterUtil;
import com.kingstargroup.conference.common.ParamUtil;
import com.kingstargroup.conference.hibernate.form.TConference;
import com.kingstargroup.conference.util.AttendeeUtil;
import com.kingstargroup.conference.util.ConferenceUtil;
import com.kingstargroup.conference.util.GetDictionary;

/**
 * 人员分配相关内容
 * @author hjw
 *
 */
public class AttendeeAllotAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		String username = GetterUtil.get((String) request.getSession().getAttribute("username"), "");
		//执行步骤
		String cmd = request.getParameter("cmd");
		//会议编号
		int confid = ParamUtil.getInteger(request,"confid");
		if (confid==0){
			request.setAttribute("result",ConferenceUtil.getAllConference(username));			
			return mapping.findForward("attendeeconflist");
		}
		if ("send".equals(cmd)){
			TConference conf = ConferenceUtil.getConfById(new Integer(confid));
			String beginDate = conf.getConBegindate();
			String signTime = conf.getConSigntime();
			String nowDate = DateUtilExtend.getNowDate2();
			String nowTime = DateUtilExtend.getNowTime2();
			
			if ((AttendeeUtil.getAttendeeListByConfId(confid).size()==0)
					||(AttendeeUtil.getDevListByConfId(confid).size()==0)){
				request.setAttribute("tipinfo","请为会议["+
						GetDictionary.getConfNameById(confid)+"]分配人员及设备，然后再下发与会名单！");
				return mapping.findForward("error");
			}
			
			//下发名单到设备必须在开会前半小时才能执行，否则不能下
			if ((DateUtilExtend.diffDate(beginDate,nowDate)!=0)
					||(DateUtilExtend.timeDiff2(nowTime,signTime)>30)){
				request.setAttribute("tipinfo","请在该会议开始签到前半小时下发名单！");
				return mapping.findForward("error");
			}
			
			//下发人员名单
			if (AttendeeUtil.addMesListByConfId(confid)){
				request.setAttribute("tipinfo",GetDictionary.getConfNameById(confid)+"：下发人员名单成功！");
				return mapping.findForward("succeed");
			}else{
				request.setAttribute("tipinfo",GetDictionary.getConfNameById(confid)+"：下发人员名单失败，请重新下发！");
				return mapping.findForward("error");
			}
			
		}else if ("allot".equals(cmd)){
			String devlist = AttendeeUtil.getUsedDevList(confid);
			if (!devlist.equals("")){
				request.setAttribute("tipinfo",devlist+"：设备在此时间段会使用，请选择其它的设备！");
				return mapping.findForward("error");
			}

			//从分组中得到的人员列表
			String custIdsGroup = ParamUtil.getString(request,"groupliststring");
			//从查询中得到的人员列表
			String custIdsQuery = ParamUtil.getString(request,"queryliststring");
			//设备列表
			String deviceIds = ParamUtil.getString(request,"devliststring");
			//人员类型
			String custtype = ParamUtil.getString(request,"custtype");
			//代表团名称
			String delegray = ParamUtil.getString(request,"delegray");
			//人员类型
			String custtype2 = ParamUtil.getString(request,"custtype2");
			//代表团名称
			String delegray2 = ParamUtil.getString(request,"delegray2");
			if (AttendeeUtil.attendeeAllot(confid,custIdsGroup,custIdsQuery,deviceIds,custtype,delegray,custtype2,delegray2)){
				request.setAttribute("tipinfo",GetDictionary.getConfNameById(confid)+"：分配人员及设备成功！");
				return mapping.findForward("succeed");
			}else{
				request.setAttribute("tipinfo",GetDictionary.getConfNameById(confid)+"：分配人员及设备失败，请重新分配！");
				return mapping.findForward("error");
			}
		}else if("stage2".equals(cmd)){
			String custno = ParamUtil.getString(request,"custno");
			String custname = ParamUtil.getString(request,"custname");
			String duty = ParamUtil.getString(request,"duty");
			String dept = ParamUtil.getString(request,"dept");
			if (("".equals(custno)) && ("".equals(custname)) && ("".equals(duty))
					&& ("-".equals(dept))) {
				request.setAttribute("tipinfo","请先指定查询条件！");
				return mapping.findForward("error");
			}			
			if (AAUtils.isAjaxRequest(request)){
				List result = AttendeeUtil.getCustList(custno,custname,duty,dept);
				request.setAttribute("result", result);
				AAUtils.addZonesToRefresh(request,"hanquerylist");
				return mapping.findForward("attendee.allot_stage2");
			}
			return mapping.findForward("attendee.allot_stage2");
		}else if("stage3".equals(cmd)){
			//从分组中得到的人员列表
			String custIdsGroup = ParamUtil.getString(request,"groupliststring");
			//从查询中得到的人员列表
			String custIdsQuery = ParamUtil.getString(request,"queryliststring");
			List attendeelist = AttendeeUtil.getAttendeeAllotList(custIdsGroup,custIdsQuery);
			request.setAttribute("attendeelist",attendeelist);
			return mapping.findForward("attendee.allot_stage3");
		}else if ("stage4".equals(cmd)){
			return mapping.findForward("attendee.allot_stage4");
		}else if("stage1".equals(cmd)){
			if (AAUtils.isAjaxRequest(request)){
				int groupid = ParamUtil.getInteger(request,"groupsrclist");
				request.setAttribute("refreshlist",AttendeeUtil.getCustListByGroupId(groupid));
		        AAUtils.addZonesToRefresh(request, "countriesList");
		    }
			return mapping.findForward("attendee.allot_stage1");
		}
		return null;
	}
}
