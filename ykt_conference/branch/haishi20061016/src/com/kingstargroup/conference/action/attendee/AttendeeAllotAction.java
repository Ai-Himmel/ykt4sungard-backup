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
 * ��Ա�����������
 * @author hjw
 *
 */
public class AttendeeAllotAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		String username = GetterUtil.get((String) request.getSession().getAttribute("username"), "");
		//ִ�в���
		String cmd = request.getParameter("cmd");
		//������
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
				request.setAttribute("tipinfo","��Ϊ����["+
						GetDictionary.getConfNameById(confid)+"]������Ա���豸��Ȼ�����·����������");
				return mapping.findForward("error");
			}
			
			//�·��������豸�����ڿ���ǰ��Сʱ����ִ�У���������
			if ((DateUtilExtend.diffDate(beginDate,nowDate)!=0)
					||(DateUtilExtend.timeDiff2(nowTime,signTime)>30)){
				request.setAttribute("tipinfo","���ڸû��鿪ʼǩ��ǰ��Сʱ�·�������");
				return mapping.findForward("error");
			}
			
			//�·���Ա����
			if (AttendeeUtil.addMesListByConfId(confid)){
				request.setAttribute("tipinfo",GetDictionary.getConfNameById(confid)+"���·���Ա�����ɹ���");
				return mapping.findForward("succeed");
			}else{
				request.setAttribute("tipinfo",GetDictionary.getConfNameById(confid)+"���·���Ա����ʧ�ܣ��������·���");
				return mapping.findForward("error");
			}
			
		}else if ("allot".equals(cmd)){
			String devlist = AttendeeUtil.getUsedDevList(confid);
			if (!devlist.equals("")){
				request.setAttribute("tipinfo",devlist+"���豸�ڴ�ʱ��λ�ʹ�ã���ѡ���������豸��");
				return mapping.findForward("error");
			}

			//�ӷ����еõ�����Ա�б�
			String custIdsGroup = ParamUtil.getString(request,"groupliststring");
			//�Ӳ�ѯ�еõ�����Ա�б�
			String custIdsQuery = ParamUtil.getString(request,"queryliststring");
			//�豸�б�
			String deviceIds = ParamUtil.getString(request,"devliststring");
			//��Ա����
			String custtype = ParamUtil.getString(request,"custtype");
			//����������
			String delegray = ParamUtil.getString(request,"delegray");
			//��Ա����
			String custtype2 = ParamUtil.getString(request,"custtype2");
			//����������
			String delegray2 = ParamUtil.getString(request,"delegray2");
			if (AttendeeUtil.attendeeAllot(confid,custIdsGroup,custIdsQuery,deviceIds,custtype,delegray,custtype2,delegray2)){
				request.setAttribute("tipinfo",GetDictionary.getConfNameById(confid)+"��������Ա���豸�ɹ���");
				return mapping.findForward("succeed");
			}else{
				request.setAttribute("tipinfo",GetDictionary.getConfNameById(confid)+"��������Ա���豸ʧ�ܣ������·��䣡");
				return mapping.findForward("error");
			}
		}else if("stage2".equals(cmd)){
			String custno = ParamUtil.getString(request,"custno");
			String custname = ParamUtil.getString(request,"custname");
			String duty = ParamUtil.getString(request,"duty");
			String dept = ParamUtil.getString(request,"dept");
			if (("".equals(custno)) && ("".equals(custname)) && ("".equals(duty))
					&& ("-".equals(dept))) {
				request.setAttribute("tipinfo","����ָ����ѯ������");
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
			//�ӷ����еõ�����Ա�б�
			String custIdsGroup = ParamUtil.getString(request,"groupliststring");
			//�Ӳ�ѯ�еõ�����Ա�б�
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
