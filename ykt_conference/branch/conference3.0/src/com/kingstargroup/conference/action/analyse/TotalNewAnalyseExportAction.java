package com.kingstargroup.conference.action.analyse;

import java.io.IOException;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.lang.StringUtils;
import org.apache.poi.hssf.usermodel.HSSFWorkbook;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.conference.common.GetterUtil;
import com.kingstargroup.conference.common.ParamUtil;
import com.kingstargroup.conference.common.StringUtil;
import com.kingstargroup.conference.hibernate.form.DeptCustForm;
import com.kingstargroup.conference.hibernate.form.TConference;
import com.kingstargroup.conference.util.ConferenceUtil;
import com.kingstargroup.conference.util.ExportUtil;

public class TotalNewAnalyseExportAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,HttpServletRequest request, HttpServletResponse response)throws IOException {
		response.setContentType("application/x-msdownload");
		response.setHeader("Content-Disposition","attachment; filename=\"attendee.xls\"");

		String custno = ParamUtil.getString(request, "custno");
		String custname = ParamUtil.getString(request, "custname");
		String deptCode = ParamUtil.getString(request, "dept");
		String type = ParamUtil.getString(request,"type");
		String begindate = ParamUtil.getString(request, "begindate");
		String enddate = ParamUtil.getString(request, "enddate");
		String username = GetterUtil.get((String) request.getSession().getAttribute("username"), "");
		
		try {
			List result1 = ConferenceUtil.getConfList1(custno,custname,deptCode,type,begindate,enddate,username);
			List result2 = ConferenceUtil.getConfList2(custno,custname,deptCode,type,begindate,enddate,username);
			List result3 = ConferenceUtil.getConfList3(custno,custname,deptCode,type,begindate,enddate,username);
			List result4 = ConferenceUtil.getConfList4(custno,custname,deptCode,type,begindate,enddate,username);
			
			List confList = ConferenceUtil.getConfList5(custno,custname,deptCode,type,begindate,enddate,username);
			List deptCustList = ConferenceUtil.getConfList6(custno,custname,deptCode,type,begindate,enddate,username);

			if (null == result1){
				return null;
			}
			Map data = new HashMap();
			combineRow(data,result1,result2,result3,result4);
			processDeptcust(data,deptCustList,confList);
			List confCheckRate = new ArrayList();
			List confLateRate = new ArrayList();
			processSingleConferenceRate(data,confList,confCheckRate,confLateRate);
			
			HSSFWorkbook workBook = ExportUtil.exportAttendeeDirect(confList, deptCustList, confCheckRate, confLateRate);
			OutputStream out = response.getOutputStream();
			workBook.write(out);
			out.flush();
		} catch (Exception e) {
			e.printStackTrace();
		}
		return null;
	}
	
	private void combineRow(Map data, List result1,List result2,List result3,List result4) {
		if (result1 != null) {
			for (int i = 0; i < result1.size(); i++) {
				HashMap rs1 = (HashMap) result1.get(i);
				String conId = rs1.get("conId").toString();
				String custId = rs1.get("custId").toString();
				String classdeptNo = rs1.get("classdeptNo").toString();
				String stuempNo = rs1.get("stuempNo").toString();
				String attendSign = rs1.get("attendSign").toString();
				// 处理学工号和会议打卡标志
				data.put(classdeptNo + "." + custId, stuempNo);
				data.put(conId + "." + classdeptNo + "." + custId, attendSign);
			}
		}
		if(result2!=null){
			for(int j=0;j<result2.size();j++){
				HashMap rs2 = (HashMap)result2.get(j);
				String custId = rs2.get("custId").toString();
				String allcount = rs2.get("allcount").toString();
				String shouldcount = rs2.get("shouldcount").toString();
				String rate = StringUtil.getPercentage(Integer.valueOf(shouldcount),Integer.valueOf(allcount),2);
				//处理应出席人数，实际出席人数，个人出勤率
				data.put(custId+".allcount", allcount);
				data.put(custId+".shouldcount", shouldcount);
				data.put(custId+".rate", rate);
			}
		}
		if(result3!=null){
			for(int j=0;j<result3.size();j++){
				HashMap rs3 = (HashMap)result3.get(j);
				String classdeptNo = rs3.get("classdeptNo").toString();
				String conId = rs3.get("conId").toString();
				String allcount = rs3.get("allcount").toString();
				String shouldcount = rs3.get("shouldcount").toString();
				String rate = StringUtil.getPercentage(Integer.valueOf(shouldcount),Integer.valueOf(allcount),2);
				//处理部门会议出勤率
				data.put(conId+".count"+classdeptNo, rate);
			}
		}
		
		if(result4!=null){
			for(int j=0;j<result4.size();j++){
				HashMap rs4 = (HashMap)result4.get(j);
				String conId = rs4.get("conId").toString();
				String allcount = rs4.get("allcount").toString();
				String shouldcount = rs4.get("shouldcount").toString();
				String latecount = rs4.get("latecount").toString();
				String rateA = StringUtil.getPercentage(Integer.valueOf(shouldcount),Integer.valueOf(allcount),2);
				String rateB = StringUtil.getPercentage(Integer.valueOf(latecount),Integer.valueOf(allcount),2);
				//处理单次会议出勤率以及迟到率
				data.put(conId+".A", rateA);
				data.put(conId+".B", rateB);
			}
		}
	}
	
	private void processDeptcust(Map data,List deptCustList,List confList){
		if(deptCustList==null){
			return;
		}
		for(int i=0;i<deptCustList.size();i++){
			DeptCustForm dc = (DeptCustForm)deptCustList.get(i);
			String classdeptNo = dc.getDeptCode();
			if(dc.getCustId()==null){
				//部门统计行，处理部门会议出勤率
				List confSignList = new ArrayList();
				for(int j=0;j<confList.size();j++){
					TConference conference = (TConference)confList.get(j);
					String conId = String.valueOf(conference.getConId());
					confSignList.add(data.get(conId+"."+classdeptNo));
				}
				dc.setConfSignList(confSignList);
			} else {
				//个人统计行，处理学工号和会议打卡标志
				List confSignList = new ArrayList();
				String custId = String.valueOf(dc.getCustId());
				for(int j=0;j<confList.size();j++){
					TConference conference = (TConference)confList.get(j);
					String conId = String.valueOf(conference.getConId());
					String attendSign = (String) data.get(conId + "." + classdeptNo + "." + custId);
					if(StringUtils.isNotBlank(attendSign)){
						if("00".equals(attendSign)){
							attendSign = "×";
						} else {
							attendSign = "√";
						}
					} else {
						attendSign = "";
					}
					confSignList.add(attendSign);
				}
				String stuempNo = (String) data.get(classdeptNo + "." + custId);
				dc.setStuempNo(stuempNo);
				dc.setConfSignList(confSignList);
				
				//处理应出席人数，实际出席人数，个人出勤率
				String allcount = (String) data.get(custId+".allcount");
				String shouldcount = (String) data.get(custId+".shouldcount");
				String rate = (String) data.get(custId+".rate");
				dc.setPlan(Integer.valueOf(allcount));
				dc.setPresent(Integer.valueOf(shouldcount));
				dc.setCheckRate(rate);
			}
		}
	}
	
	private void processSingleConferenceRate(Map data,List confList,List confCheckRate,List confLateRate){
		for(int j=0;j<confList.size();j++){
			TConference conference = (TConference)confList.get(j);
			String conId = String.valueOf(conference.getConId());
			//处理单次会议出勤率以及迟到率
			String rateA = (String) data.get(conId+".A");
			String rateB = (String) data.get(conId+".B");
			confCheckRate.add(rateA);
			confLateRate.add(rateB);
		}
	}
}
