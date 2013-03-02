package com.kingstargroup.conference.action.sign;

import java.util.HashMap;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.conference.common.ParamUtil;
import com.kingstargroup.conference.util.AnalyseUtil;
import com.kingstargroup.conference.util.SignUtil;

/**
 * ���
 * 
 * @author hjw
 * 
 */
public class SignPreviewAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm from,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (null == request.getParameter("confid")) {
			request.setAttribute("tipinfo", "û��ҪԤ���Ļ��飡");
			return mapping.findForward("error");
		}
		int confid = ParamUtil.getInteger(request, "confid");
		String selectType = ParamUtil.getString(request, "selecttype");
		String attendeesign = ParamUtil.getString(request, "attendeesign");
		// String pos = ParamUtil.getString(request,"id");
		String attendeetime = ParamUtil.getString(request, "attendtime");
		String timeout = ParamUtil.getString(request, "timeout");

		if ("totle".equals(selectType)) {
			if ("prev".equals(attendeesign)) {
				if ("".equals(timeout)) {
					request.setAttribute("timeout", "9900");
				} else {
					request.setAttribute("timeout", timeout);
				}
				request.setAttribute("conference", SignUtil
						.getConfInfoById(confid));
				// ��Ӧ������
				request.setAttribute("totleattendee", new Integer(SignUtil
						.getConfTotleAttendeeByCofid(confid)));
				// ʵ������
				request.setAttribute("signednum", new Integer(SignUtil
						.getSignedNumByCofid(confid)));
				// �������
				List leaveList = SignUtil.getLeaveNumByConfid(confid);
				if (leaveList != null) {
					request.setAttribute("leavenum", new Integer(leaveList
							.size()));
					request.setAttribute("leavelist", leaveList);
				} else {
					request.setAttribute("leavenum", new Integer("0"));
					request.setAttribute("leavelist", leaveList);
				}

				// ���ǩ������
				List replaceList = SignUtil.getReplaceNumByConfid(confid);
				if (replaceList != null) {
					request.setAttribute("replacenum", new Integer(replaceList
							.size()));
					request.setAttribute("replacelist", replaceList);
				} else {
					request.setAttribute("replacenum", new Integer("0"));
					request.setAttribute("replacelist", replaceList);
				}
				// ����ǩ������
				List signList = SignUtil.getSignedNumByConfid(confid);
				if (signList != null) {
					request.setAttribute("csignednum", new Integer(signList
							.size()));
					request.setAttribute("csignedlist", signList);
				} else {
					request.setAttribute("csignednum", new Integer("0"));
					request.setAttribute("csignedlist", signList);
				}

				// δ������
				List unsignedList = SignUtil.getUnSignNumByConfid(confid);
				if (unsignedList != null) {
					request.setAttribute("unsignnum", new Integer(unsignedList
							.size()));
					request.setAttribute("unsignlist", unsignedList);
				} else {
					request.setAttribute("unsignnum", new Integer("0"));
					request.setAttribute("unsignlist", unsignedList);
				}
				//������ͳ��Ӧ��������ʵ��������δ���������������
				List deptList = SignUtil.getDeptListByConfid(confid);
				request.setAttribute("deptList", deptList);

				// HttpSession session = request.getSession();
				request.setAttribute("confid", new Integer(confid));
				if (attendeetime != null && !"".equals(attendeetime)) {
					List attList = AnalyseUtil.getPicAttendeeListTest(String
							.valueOf(confid), attendeetime, "0");
					if (attList != null && attList.size() > 0) {
						HashMap iter = (HashMap) attList.get(0);
						String attendTime = (String) iter.get("attendTime");
						request.setAttribute("attendtime", attendTime);

					} else {
						attList = AnalyseUtil.getPicAttendeeListTest(String
								.valueOf(confid), "", "0");
						if (attList != null && attList.size() > 0) {
							HashMap iter = (HashMap) attList.get(0);
							String attendTime = (String) iter.get("attendTime");
							request.setAttribute("attendtime", attendTime);
						}
					}
				} else {
					List attList = AnalyseUtil.getPicAttendeeListTest(String
							.valueOf(confid), "", "0");
					if (attList != null && attList.size() > 0) {
						HashMap iter = (HashMap) attList.get(0);
						String attendTime = (String) iter.get("attendTime");
						request.setAttribute("attendtime", attendTime);
					}
				}
				return mapping.findForward("preview");

			} else if ("prevtest".equals(attendeesign)) {
				if (attendeetime != null && !"".equals(attendeetime)) {
					List attList = AnalyseUtil.getPicAttendeeListTest(String
							.valueOf(confid), attendeetime, "0");
					if (attList != null && attList.size() > 0) {
						response.getWriter().write("1");
					} else {
						response.getWriter().write("0");
					}
				} else {
					List attList = AnalyseUtil.getPicAttendeeListTest(String
							.valueOf(confid), "", "0");
					if (attList != null && attList.size() > 0) {
						response.getWriter().write("1");
					} else {
						response.getWriter().write("0");
					}
				}
				return null;

			} else if ("prev1".equals(attendeesign)) {

				if ("".equals(timeout)) {
					request.setAttribute("timeout", "9900");
				} else {
					request.setAttribute("timeout", timeout);
				}
				request.setAttribute("conference", SignUtil
						.getConfInfoById(confid));
				// ��Ӧ������
				request.setAttribute("totleattendee", new Integer(SignUtil
						.getConfTotleAttendeeByCofid(confid)));
				// ʵ������
				request.setAttribute("signednum", new Integer(SignUtil
						.getSignedNumByCofid(confid)));
				// �������
				List leaveList = SignUtil.getLeaveNumByConfid(confid);
				if (leaveList != null) {
					request.setAttribute("leavenum", new Integer(leaveList
							.size()));
					request.setAttribute("leavelist", leaveList);
				} else {
					request.setAttribute("leavenum", new Integer("0"));
					request.setAttribute("leavelist", leaveList);
				}
				// ���ǩ������
				List replaceList = SignUtil.getReplaceNumByConfid(confid);
				if (replaceList != null) {
					request.setAttribute("replacenum", new Integer(replaceList
							.size()));
					request.setAttribute("replacelist", replaceList);
				} else {
					request.setAttribute("replacenum", new Integer("0"));
					request.setAttribute("replacelist", replaceList);
				}
				// ����ǩ������
				List signList = SignUtil.getSignedNumByConfid(confid);
				if (signList != null) {
					request.setAttribute("csignednum", new Integer(signList
							.size()));
					request.setAttribute("csignedlist", signList);
				} else {
					request.setAttribute("csignednum", new Integer("0"));
					request.setAttribute("csignedlist", signList);
				}
				// δ������
				List unsignedList = SignUtil.getUnSignNumByConfidCount(confid);
				if (unsignedList != null) {
					request.setAttribute("unsignnum", new Integer(unsignedList
							.size()));
					request.setAttribute("unsignlist", unsignedList);
				} else {
					request.setAttribute("unsignnum", new Integer("0"));
					request.setAttribute("unsignlist", unsignedList);
				}

				// HttpSession session = request.getSession();
				request.setAttribute("confid", new Integer(confid));
				if (attendeetime != null && !"".equals(attendeetime)) {
					List attList = AnalyseUtil.getPicAttendeeListTest(String
							.valueOf(confid), attendeetime, "0");
					if (attList != null && attList.size() > 0) {
						HashMap iter = (HashMap) attList.get(0);
						String attendTime = (String) iter.get("attendTime");
						request.setAttribute("attendtime", attendTime);

					} else {
						attList = AnalyseUtil.getPicAttendeeListTest(String
								.valueOf(confid), "", "0");
						if (attList != null && attList.size() > 0) {
							HashMap iter = (HashMap) attList.get(0);
							String attendTime = (String) iter.get("attendTime");
							request.setAttribute("attendtime", attendTime);
						}
					}
				} else {
					List attList = AnalyseUtil.getPicAttendeeListTest(String
							.valueOf(confid), "", "0");
					if (attList != null && attList.size() > 0) {
						HashMap iter = (HashMap) attList.get(0);
						String attendTime = (String) iter.get("attendTime");
						request.setAttribute("attendtime", attendTime);
					}
				}
				return mapping.findForward("preview1");

			} else if ("justprev1".equals(attendeesign)) {

				if ("".equals(timeout)) {
					request.setAttribute("timeout", "9900");
				} else {
					request.setAttribute("timeout", timeout);
				}
				request.setAttribute("conference", SignUtil
						.getConfInfoById(confid));
				// ��Ӧ������
				request.setAttribute("totleattendee", new Integer(SignUtil
						.getConfTotleAttendeeByCofid(confid)));
				// ʵ������
				request.setAttribute("signednum", new Integer(SignUtil
						.getSignedNumByCofid(confid)));

				// �������
				List leaveList = SignUtil.getLeaveNumByConfid(confid);
				if (leaveList != null) {
					request.setAttribute("leavenum", new Integer(leaveList
							.size()));
					request.setAttribute("leavelist", leaveList);
				} else {
					request.setAttribute("leavenum", new Integer("0"));
					request.setAttribute("leavelist", leaveList);
				}
				// ���ǩ������
				List replaceList = SignUtil.getReplaceNumByConfid(confid);
				if (replaceList != null) {
					request.setAttribute("replacenum", new Integer(replaceList
							.size()));
					request.setAttribute("replacelist", replaceList);
				} else {
					request.setAttribute("replacenum", new Integer("0"));
					request.setAttribute("replacelist", replaceList);
				}
				// ����ǩ������
				List signList = SignUtil.getSignedNumByConfid(confid);
				if (signList != null) {
					request.setAttribute("csignednum", new Integer(signList
							.size()));
					request.setAttribute("csignedlist", signList);
				} else {
					request.setAttribute("csignednum", new Integer("0"));
					request.setAttribute("csignedlist", signList);
				}
				// δ������
				List unsignedList = SignUtil.getUnSignNumByConfidCount(confid);
				if (unsignedList != null) {
					request.setAttribute("unsignnum", new Integer(unsignedList
							.size()));
					request.setAttribute("unsignlist", unsignedList);
				} else {
					request.setAttribute("unsignnum", new Integer("0"));
					request.setAttribute("unsignlist", unsignedList);
				}

				// HttpSession session = request.getSession();
				request.setAttribute("confid", new Integer(confid));
				if (attendeetime != null && !"".equals(attendeetime)) {
					List attList = AnalyseUtil.getPicAttendeeListTest(String
							.valueOf(confid), attendeetime, "0");
					if (attList != null && attList.size() > 0) {
						HashMap iter = (HashMap) attList.get(0);
						String attendTime = (String) iter.get("attendTime");
						request.setAttribute("attendtime", attendTime);

					} else {
						attList = AnalyseUtil.getPicAttendeeListTest(String
								.valueOf(confid), "", "0");
						if (attList != null && attList.size() > 0) {
							HashMap iter = (HashMap) attList.get(0);
							String attendTime = (String) iter.get("attendTime");
							request.setAttribute("attendtime", attendTime);
						}
					}
				} else {
					List attList = AnalyseUtil.getPicAttendeeListTest(String
							.valueOf(confid), "", "0");
					if (attList != null && attList.size() > 0) {
						HashMap iter = (HashMap) attList.get(0);
						String attendTime = (String) iter.get("attendTime");
						request.setAttribute("attendtime", attendTime);
					}
				}
				return mapping.findForward("justpreview1");

			} else if ("prev1test".equals(attendeesign)) {
				if (attendeetime != null && !"".equals(attendeetime)) {
					List attList = AnalyseUtil.getPicAttendeeListTest(String
							.valueOf(confid), attendeetime, "0");
					if (attList != null && attList.size() > 0) {
						response.getWriter().write("1");
					} else {
						response.getWriter().write("0");
					}
				} else {
					List attList = AnalyseUtil.getPicAttendeeListTest(String
							.valueOf(confid), "", "0");
					if (attList != null && attList.size() > 0) {
						response.getWriter().write("1");
					} else {
						response.getWriter().write("0");
					}
				}
				return null;

			} else if ("prev2".equals(attendeesign)) {
				if ("".equals(timeout)) {
					request.setAttribute("timeout", "9900");
				} else {
					request.setAttribute("timeout", timeout);
				}
				request.setAttribute("conference", SignUtil
						.getConfInfoById(confid));
				// ��Ӧ������
				request.setAttribute("totleattendee", new Integer(SignUtil
						.getConfTotleAttendeeByCofid(confid)));
				// ʵ������
				request.setAttribute("signednum", new Integer(SignUtil
						.getSignedNumByCofid(confid)));
				// �������
				List leaveList = SignUtil.getLeaveNumByConfid(confid);
				if (leaveList != null) {
					request.setAttribute("leavenum", new Integer(leaveList
							.size()));
				} else {
					request.setAttribute("leavenum", new Integer("0"));
				}
				List unsignedList = SignUtil.getUnSignNumByConfidCount(confid);
				// δ������
				if (unsignedList != null) {
					request.setAttribute("unsignnum", new Integer(unsignedList
							.size()));
				} else {
					request.setAttribute("unsignnum", new Integer("0"));
				}

				// HttpSession session = request.getSession();
				request.setAttribute("confid", new Integer(confid));
				// List attList =
				// AnalyseUtil.getPicAttendeeList(String.valueOf(confid),
				// attendeetime, "0");
				List attList = AnalyseUtil.getPicAttendeeList(String
						.valueOf(confid), "", "0");
				if (attList != null && attList.size() > 0) {
					HashMap iter = (HashMap) attList.get(0);
					String stuempNo = (String) iter.get("stuempNo");
					String cutName = (String) iter.get("cutName");
					String deptName = (String) iter.get("deptName");
					String dutyName = (String) iter.get("dutyName");
					String attendTime = (String) iter.get("attendTime");
					request.setAttribute("stuempNo", stuempNo);
					request.setAttribute("cutName", cutName);
					request.setAttribute("deptName", deptName);
					request.setAttribute("dutyName", dutyName);
					request.setAttribute("attendtime", attendTime);
					request.setAttribute("attList", attList);

				}

				return mapping.findForward("preview2");
			} else if ("justprev2".equals(attendeesign)) {
				if ("".equals(timeout)) {
					request.setAttribute("timeout", "9900");
				} else {
					request.setAttribute("timeout", timeout);
				}
				request.setAttribute("conference", SignUtil
						.getConfInfoById(confid));
				// ��Ӧ������
				request.setAttribute("totleattendee", new Integer(SignUtil
						.getConfTotleAttendeeByCofid(confid)));
				// ʵ������
				request.setAttribute("signednum", new Integer(SignUtil
						.getSignedNumByCofid(confid)));
				// �������
				List leaveList = SignUtil.getLeaveNumByConfid(confid);
				if(leaveList!=null){
					request.setAttribute("leavenum", new Integer(leaveList.size()));
				}else{
					request.setAttribute("leavenum", new Integer("0"));
				}
				
				List unsignedList = SignUtil.getUnSignNumByConfidCount(confid);
				// δ������
				if(unsignedList!=null){
				request.setAttribute("unsignnum", new Integer(unsignedList
						.size()));
				}else{
					request.setAttribute("unsignnum", new Integer("0"));
				}

				// HttpSession session = request.getSession();
				request.setAttribute("confid", new Integer(confid));
				List attList = AnalyseUtil.getPicAttendeeList(String
						.valueOf(confid), "", "0");
				if (attList != null && attList.size() > 0) {
					HashMap iter = (HashMap) attList.get(0);
					String stuempNo = (String) iter.get("stuempNo");
					String cutName = (String) iter.get("cutName");
					String deptName = (String) iter.get("deptName");
					String dutyName = (String) iter.get("dutyName");
					String attendTime = (String) iter.get("attendTime");
					request.setAttribute("stuempNo", stuempNo);
					request.setAttribute("cutName", cutName);
					request.setAttribute("deptName", deptName);
					request.setAttribute("dutyName", dutyName);
					request.setAttribute("attendtime", attendTime);
					request.setAttribute("attList", attList);

				}

				return mapping.findForward("justpreview2");
			} else if ("prev2test".equals(attendeesign)) {
				if (attendeetime != null && !"".equals(attendeetime)) {
					List attList = AnalyseUtil.getPicAttendeeListTest(String
							.valueOf(confid), attendeetime, "0");
					if (attList != null && attList.size() > 0) {
						response.getWriter().write("1");
					} else {
						response.getWriter().write("0");
					}
				} else {
					List attList = AnalyseUtil.getPicAttendeeListTest(String
							.valueOf(confid), "", "0");
					if (attList != null && attList.size() > 0) {
						response.getWriter().write("1");
					} else {
						response.getWriter().write("0");
					}
				}
				return null;

			} else if ("sign".equals(attendeesign)) {
				String deptName = ParamUtil.getString(request, "deptName");
				request.setAttribute("resultinfo", SignUtil
						.getSignedNumByConfid(confid,deptName));
				request.setAttribute("pretip", "ǩ�����Ԥ��--��ǩ����Ա�б�");
				return mapping.findForward("previewinfo");
			} else if ("unsign".equals(attendeesign)) {
				String deptName = ParamUtil.getString(request, "deptName");
				request.setAttribute("resultinfo", SignUtil
						.getUnSignNumByConfid(confid,deptName));
				request.setAttribute("pretip", "ǩ�����Ԥ��--δǩ����Ա�б�");
				request.setAttribute("ec_f_deptName", "	Ժ���칫��");
				return mapping.findForward("previewinfo");
			} else if ("leave".equals(attendeesign)) {
				String deptName = ParamUtil.getString(request, "deptName");
				request.setAttribute("resultinfo", SignUtil
						.getLeaveNumByConfid(confid,deptName));
				request.setAttribute("pretip", "ǩ�����Ԥ��--�����Ա�б�");
				return mapping.findForward("previewinfo");
			} else if ("replace".equals(attendeesign)) {
				request.setAttribute("resultinfo", SignUtil
						.getReplaceNumByConfid(confid));
				request.setAttribute("pretip", "ǩ�����Ԥ��--���ǩ����Ա�б�");
				return mapping.findForward("previewinfo");
			} else if("attendee".equals(attendeesign)){
				String deptName = ParamUtil.getString(request, "deptName");
				request.setAttribute("resultinfo", SignUtil
						.getAttendeeByConfid(confid,deptName));
				request.setAttribute("pretip", "ǩ�����Ԥ��--Ӧ����Ա�б�");
				return mapping.findForward("previewinfo");
			} else if("prevbasic".equals(attendeesign)){
				//������ϢԤ��
				if ("".equals(timeout)) {
					request.setAttribute("timeout", "9900");
				} else {
					request.setAttribute("timeout", timeout);
				}
				request.setAttribute("conference", SignUtil
						.getConfInfoById(confid));
				// ��Ӧ������
				request.setAttribute("totleattendee", new Integer(SignUtil
						.getConfTotleAttendeeByCofid(confid)));
				// ʵ������
				request.setAttribute("signednum", new Integer(SignUtil
						.getSignedNumByCofid(confid)));
				List unsignedList = SignUtil.getUnSignNumByConfidCount(confid);
				// δ������
				if(unsignedList!=null){
				request.setAttribute("unsignnum", new Integer(unsignedList
						.size()));
				}else{
					request.setAttribute("unsignnum", new Integer("0"));
				}

				// HttpSession session = request.getSession();
				request.setAttribute("confid", new Integer(confid));
				List attList = AnalyseUtil.getPicAttendeeList(String
						.valueOf(confid), "", "0");
				if (attList != null && attList.size() > 0) {
					HashMap iter = (HashMap) attList.get(0);
					String attendTime = (String) iter.get("attendTime");
					request.setAttribute("attendtime", attendTime);
				}

				return mapping.findForward("prevbasic");
			} else if("prevbasictest".equals(attendeesign)){
				//������Ϣ��֤
				if (attendeetime != null && !"".equals(attendeetime)) {
					List attList = AnalyseUtil.getPicAttendeeListTest(String
							.valueOf(confid), attendeetime, "0");
					if (attList != null && attList.size() > 0) {
						response.getWriter().write("1");
					} else {
						response.getWriter().write("0");
					}
				} else {
					List attList = AnalyseUtil.getPicAttendeeListTest(String
							.valueOf(confid), "", "0");
					if (attList != null && attList.size() > 0) {
						response.getWriter().write("1");
					} else {
						response.getWriter().write("0");
					}
				}
				return null;
				
			}

		} else if ("delegraytest".equals(attendeesign)) {
			if (attendeetime != null && !"".equals(attendeetime)) {
				List attList = AnalyseUtil.getPicAttendeeListTest(String
						.valueOf(confid), attendeetime, "0");
				if (attList != null && attList.size() > 0) {
					response.getWriter().write("1");
				} else {
					response.getWriter().write("0");
				}
			} else {
				List attList = AnalyseUtil.getPicAttendeeListTest(String
						.valueOf(confid), "", "0");
				if (attList != null && attList.size() > 0) {
					response.getWriter().write("1");
				} else {
					response.getWriter().write("0");
				}
			}
			return null;

		} else if ("justdelegray".equals(selectType)) {
			String id = request.getParameter("id");
			if ("".equals(timeout)) {
				request.setAttribute("timeout", "9900");
			} else {
				request.setAttribute("timeout", timeout);
			}
			// HttpSession session = request.getSession();
			request.setAttribute("confid", new Integer(confid));
			if (attendeetime != null && !"".equals(attendeetime)) {
				List attList = AnalyseUtil.getPicAttendeeListTest(String
						.valueOf(confid), attendeetime, "0");
				if (attList != null && attList.size() > 0) {
					HashMap iter = (HashMap) attList.get(0);
					String attendTime = (String) iter.get("attendTime");
					request.setAttribute("attendtime", attendTime);

				} else {
					attList = AnalyseUtil.getPicAttendeeListTest(String
							.valueOf(confid), "", "0");
					if (attList != null && attList.size() > 0) {
						HashMap iter = (HashMap) attList.get(0);
						String attendTime = (String) iter.get("attendTime");
						request.setAttribute("attendtime", attendTime);
					}
				}
			} else {
				List attList = AnalyseUtil.getPicAttendeeListTest(String
						.valueOf(confid), "", "0");
				if (attList != null && attList.size() > 0) {
					HashMap iter = (HashMap) attList.get(0);
					String attendTime = (String) iter.get("attendTime");
					request.setAttribute("attendtime", attendTime);
				}
			}
			if (null == id || "".equals(id)) {
				request.setAttribute("conference", SignUtil
						.getConfInfoById(confid));
				request.setAttribute("delegraylist", SignUtil
						.getDelegrayListByConfid(confid));
				request.setAttribute("pretip", "ǩ�����Ԥ��--�����ų�ϯ���ͳ��");
				request.setAttribute("confid", new Integer(confid));
				return mapping.findForward("justdelegray");
			} else {
				request.setAttribute("delegraylist", SignUtil
						.getCustListByConfidandDlgt(confid, id));
				request.setAttribute("pretip", "ǩ�����Ԥ��--�����ų�ϯ�����ϸ");
				request.setAttribute("confid", new Integer(confid));
				return mapping.findForward("justdelegraydetail");
			}

		} else if ("delegray".equals(selectType)) {
			String id = request.getParameter("id");
			if ("".equals(timeout)) {
				request.setAttribute("timeout", "9900");
			} else {
				request.setAttribute("timeout", timeout);
			}
			// HttpSession session = request.getSession();
			request.setAttribute("confid", new Integer(confid));
			if (attendeetime != null && !"".equals(attendeetime)) {
				List attList = AnalyseUtil.getPicAttendeeListTest(String
						.valueOf(confid), attendeetime, "0");
				if (attList != null && attList.size() > 0) {
					HashMap iter = (HashMap) attList.get(0);
					String attendTime = (String) iter.get("attendTime");
					request.setAttribute("attendtime", attendTime);

				} else {
					attList = AnalyseUtil.getPicAttendeeListTest(String
							.valueOf(confid), "", "0");
					if (attList != null && attList.size() > 0) {
						HashMap iter = (HashMap) attList.get(0);
						String attendTime = (String) iter.get("attendTime");
						request.setAttribute("attendtime", attendTime);
					}
				}
			} else {
				List attList = AnalyseUtil.getPicAttendeeListTest(String
						.valueOf(confid), "", "0");
				if (attList != null && attList.size() > 0) {
					HashMap iter = (HashMap) attList.get(0);
					String attendTime = (String) iter.get("attendTime");
					request.setAttribute("attendtime", attendTime);
				}
			}
			if (null == id || "".equals(id)) {
				request.setAttribute("conference", SignUtil
						.getConfInfoById(confid));
				request.setAttribute("delegraylist1", SignUtil
						.getDelegrayListByConfidspit(confid, 1));
				request.setAttribute("delegraylist2", SignUtil
						.getDelegrayListByConfidspit(confid, 2));
				request.setAttribute("pretip", "ǩ�����Ԥ��--�����ų�ϯ���ͳ��");
				request.setAttribute("confid", new Integer(confid));
				return mapping.findForward("delegray");
			} else {
				request.setAttribute("delegraylist", SignUtil
						.getCustListByConfidandDlgt(confid, id));
				request.setAttribute("pretip", "ǩ�����Ԥ��--�����ų�ϯ�����ϸ");
				request.setAttribute("confid", new Integer(confid));
				return mapping.findForward("delegraydetail");
			}

		}
		return null;
	}
}
