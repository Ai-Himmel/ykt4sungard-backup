package com.kingstargroup.conference.action.analyse;

import java.io.IOException;
import java.io.OutputStream;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.poi.hssf.usermodel.HSSFWorkbook;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.conference.common.ParamUtil;
import com.kingstargroup.conference.common.StringUtil;
import com.kingstargroup.conference.hibernate.form.TConference;
import com.kingstargroup.conference.util.AnalyseUtil;
import com.kingstargroup.conference.util.ExportUtil;

public class TotalAnalyseExportAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,HttpServletRequest request, HttpServletResponse response)throws IOException {
		response.setContentType("application/x-msdownload");
		response.setHeader("Content-Disposition","attachment; filename=\"report.xls\"");

		try {
			Integer conid = Integer.valueOf(ParamUtil.getString(request, "conId"));
			
			String webPath = request.getSession().getServletContext().getRealPath("/");
			Map beans = new HashMap();
			
			//���һ���������ݣ��������excelģ��
			TConference conference = null;
			List confList = AnalyseUtil.getConference(conid, "", "", "");
			if(confList!=null && confList.size()>0){
				conference = (TConference) confList.get(0);
			}
			beans.put("conference", conference);
			
			//���Ҽƻ���ϯ��Ա�б�
			List custList = AnalyseUtil.getTTAttendeeList(conid,"1");
			beans.put("custList", custList);
			
			//ͳ�������Լ�����
			List count = AnalyseUtil.getAtteCount(conid, "", "", "");
			calculateRate(beans,count);
			
			HSSFWorkbook workBook = ExportUtil.exportReport(webPath, beans);
			OutputStream out = response.getOutputStream();
			workBook.write(out);
			out.flush();
		} catch (Exception e) {
			e.printStackTrace();
		}
		return null;
	}
	
	private void calculateRate(Map beans,List count){
		Integer all = Integer.valueOf(0),present = Integer.valueOf(0),dayOff = Integer.valueOf(0),absent = Integer.valueOf(0),checkin = Integer.valueOf(0),nocard = Integer.valueOf(0),replace = Integer.valueOf(0),checkinLate = Integer.valueOf(0),nocardLate = Integer.valueOf(0), replaceLate = Integer.valueOf(0);
		if (count != null) {
			all = ((Integer) count.get(0));
			present = ((Integer) count.get(1));
			dayOff = ((Integer) count.get(2));
			absent = ((Integer) count.get(3));
			checkin = ((Integer) count.get(4));
			nocard = ((Integer) count.get(5));
			replace = ((Integer) count.get(6));
			checkinLate = ((Integer) count.get(7));
			nocardLate = ((Integer) count.get(8));
			replaceLate = ((Integer) count.get(9));
		}
		
		// �ƻ���ϯ
		beans.put("all", all);
		beans.put("allRate", all.intValue()==0?"0":"100%");
		// ʵ�ʳ�ϯ
		beans.put("present", present);
		beans.put("presentRate", all.intValue()==0?"0":StringUtil.getPercentage(present,all,2));
		// ���
		beans.put("dayOff", dayOff);
		beans.put("dayOffRate", all.intValue()==0?"0":StringUtil.getPercentage(dayOff,all,2));
		// ȱϯ
		beans.put("absent", absent);
		beans.put("absentRate", all.intValue()==0?"0":StringUtil.getPercentage(absent,all,2));
		// �ֿ�ǩ��
		beans.put("checkin", checkin);
		beans.put("checkinRate", all.intValue()==0?"0":StringUtil.getPercentage(checkin,all,2));
		// �޿�ǩ��
		beans.put("nocard", nocard);
		beans.put("nocardRate", all.intValue()==0?"0":StringUtil.getPercentage(nocard,all,2));
		// ����ǩ��
		beans.put("replace", replace);
		beans.put("replaceRate", all.intValue()==0?"0":StringUtil.getPercentage(replace,all,2));
		// �ֿ�ǩ�����ٵ���
		beans.put("checkinLate", checkinLate);
		beans.put("checkinLateRate", all.intValue()==0?"0":StringUtil.getPercentage(checkinLate,all,2));
		// �޿�ǩ�����ٵ���
		beans.put("nocardLate", nocardLate);
		beans.put("nocardLateRate", all.intValue()==0?"0":StringUtil.getPercentage(nocardLate,all,2));
		// ����ǩ�����ٵ���
		beans.put("replaceLate", replaceLate);
		beans.put("replaceLateRate", all.intValue()==0?"0":StringUtil.getPercentage(replaceLate,all,2));
	}
}
