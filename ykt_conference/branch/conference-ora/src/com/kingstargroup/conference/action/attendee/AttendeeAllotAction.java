package com.kingstargroup.conference.action.attendee;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

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
 * 
 * @author hjw
 * 
 */
public class AttendeeAllotAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		String username = GetterUtil.get((String) request.getSession()
				.getAttribute("username"), "");
		// ִ�в���
		String cmd = request.getParameter("cmd");
		// ������
		int confid = ParamUtil.getInteger(request, "confid");
		if (confid == 0) {
			request.setAttribute("result", ConferenceUtil
					.getAllConference(username));
			return mapping.findForward("attendeeconflist");
		}
		String oneattend = request.getParameter("oneattend");
		if (!"1".equals(oneattend)) {
			custList = new ArrayList();
			oneattend = "1";
		}
		request.setAttribute("oneattend", oneattend);
		if ("send".equals(cmd)) {
			TConference conf = ConferenceUtil.getConfById(new Integer(confid));
			String beginDate = conf.getConBegindate();
			String signTime = conf.getConSigntime();
			String nowDate = DateUtilExtend.getNowDate2();
			String nowTime = DateUtilExtend.getNowTime2();

			if ((AttendeeUtil.getAttendeeListByConfId(confid).size() == 0)
					|| (AttendeeUtil.getDevListByConfId(confid).size() == 0)) {
				request.setAttribute("tipinfo", "��Ϊ����["
						+ GetDictionary.getConfNameById(confid)
						+ "]������Ա���豸��Ȼ�����·����������");
				return mapping.findForward("error");
			}

			// �·��������豸�����ڿ���ǰ��Сʱ����ִ�У���������
			if ((DateUtilExtend.diffDate(beginDate, nowDate) != 0)
					|| (DateUtilExtend.timeDiff2(nowTime, signTime) > 30)) {
				request.setAttribute("tipinfo", "���ڸû��鿪ʼǩ��ǰ��Сʱ�·�������");
				return mapping.findForward("error");
			}

			// �·���Ա����
			if (AttendeeUtil.addMesListByConfId(confid)) {
				request.setAttribute("tipinfo", GetDictionary
						.getConfNameById(confid)
						+ "���·���Ա�����ɹ���");
				return mapping.findForward("succeed");
			} else {
				request.setAttribute("tipinfo", GetDictionary
						.getConfNameById(confid)
						+ "���·���Ա����ʧ�ܣ��������·���");
				return mapping.findForward("error");
			}

		} else if ("allot".equals(cmd)) {
//			String devlist = AttendeeUtil.getUsedDevList(confid);
//			if (!devlist.equals("")) {
//				request.setAttribute("tipinfo", devlist
//						+ "���豸�ڴ�ʱ��λ�ʹ�ã���ѡ���������豸��");
//				return mapping.findForward("error");
//			}
			String[] deviceIds = request.getParameterValues("devdestlist");
			if (AttendeeUtil.attendeeAllot(confid, deviceIds, custList)) {
				request.setAttribute("tipinfo", GetDictionary
						.getConfNameById(confid)
						+ "��������Ա���豸�ɹ���");
				return mapping.findForward("succeed");
			} else {
				request.setAttribute("tipinfo", GetDictionary
						.getConfNameById(confid)
						+ "��������Ա���豸ʧ�ܣ������·��䣡");
				return mapping.findForward("error");
			}
		} else if ("stage2".equals(cmd)) {
			String bindCust = ParamUtil.getString(request, "bindCust");
			String custno = ParamUtil.getString(request, "custno");
			String custname = ParamUtil.getString(request, "custname");
			String duty = ParamUtil.getString(request, "duty");
			String dept = ParamUtil.getString(request, "dept");
			if (("".equals(custno)) && ("".equals(custname))
					&& ("".equals(duty)) && ("-".equals(dept))) {
				request.setAttribute("tipinfo", "����ָ����ѯ������");
				return mapping.findForward("error");
			}
			if (AAUtils.isAjaxRequest(request)) {
				List result = AttendeeUtil.getCustList(custno, custname, duty,dept,confid,custList);
				request.setAttribute("result", result);
				AAUtils.addZonesToRefresh(request, "hanquerylist");
				return mapping.findForward("attendee.allot_stage2");
			}
			saveCustList(bindCust);
			saveCustToList(request, confid);
			return mapping.findForward("attendee.allot_stage2");
		} else if ("stage3".equals(cmd)) {
			String bindCust = ParamUtil.getString(request, "bindCust");
			saveCustList(bindCust);
			saveCustToList(request, confid);
			return mapping.findForward("attendee.allot_stage3");
		} else if ("stage4".equals(cmd)) {
			return mapping.findForward("attendee.allot_stage4");
		} else if ("stage1".equals(cmd)) {
			REM_CUSTIDS = ParamUtil.getString(request, "bindCust");
			if (AAUtils.isAjaxRequest(request)) {
				int groupid = ParamUtil.getInteger(request, "groupsrclist");
				// �ع��÷�������ʾʱ������ʾ�Ѿ����������Ա����				
				request.setAttribute("refreshlist", AttendeeUtil
						.getCustListByGroupIdExcept(confid, groupid, REM_CUSTIDS));
				AAUtils.addZonesToRefresh(request, "countriesList");
				return mapping.findForward("attendee.allot_stage1");
			}
			request.setAttribute("attendedList", AttendeeUtil.getFirstAttendedList(confid));
			return mapping.findForward("attendee.allot_stage1");
		}
		return null;
	}

	private String REM_CUSTIDS = "";
	private List custList = null;

	private List saveCustList(String bindCust) {
		if (null != bindCust && !"".equals(bindCust)) {
			custList.clear();
			String custId ="";
			String[] temp = bindCust.split(",");
				for (int i = 0; i < temp.length; i++) {
					if (i % 4 == 0) {
						// dormitoryId
						custId = temp[i];
						if ("".equals(custId)) {
							i = i + 3;
							continue;
						}
						Map custMap = new HashMap();
						custMap.put("custId", temp[i]);
						custMap.put("delegray", temp[i+2]);
						custMap.put("custType", temp[i+3]);
						custList.add(custMap);
						i = i + 3;
					}
				}
		}
		
		
		return custList;
	}

	private void saveCustToList(HttpServletRequest request, int confid) {
		// ȡ���Ѿ����������Ա�����б���ʾ��ҳ���ұ�
		request.setAttribute("attendedList", AttendeeUtil.getAllAttendedList(
				confid, custList));
	}
}
