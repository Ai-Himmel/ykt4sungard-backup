package com.kingstargroup.conference.action.sign;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.fileupload.DiskFileUpload;
import org.apache.commons.fileupload.FileItem;
import org.apache.commons.fileupload.FileUpload;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.conference.common.ParamUtil;
import com.kingstargroup.conference.hibernate.form.TConference;
import com.kingstargroup.conference.util.AttendeeUtil;
import com.kingstargroup.conference.util.ConferenceUtil;
import com.kingstargroup.conference.util.GetDictionary;
import com.kingstargroup.conference.util.SignUtil;

public class uploadListAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		/**
		 * 直接输入物理卡号的处理方式
		 */
		// String physicalno = ParamUtil.getString(request,"physicalno");
		// if(!"".equals(physicalno)){
		// List attendeelist = AttendeeUtil.getAttendeeList(physicalno);
		// request.setAttribute("result", attendeelist);
		// request.setAttribute("physicalno", physicalno);
		// }
		/**
		 * 上传文件的处理方式
		 */
		String cmd = ParamUtil.getString(request, "cmd");
		int confid = ParamUtil.getInteger(request, "confid");
		
		if("upload".equals(cmd)){
			if(confid == 0){
				request.setAttribute("tipinfo", "签到失败:没有匹配的会议，请检查用户权限或上传文本格式！");
				return mapping.findForward("error");
			}
			String custIdString =request.getParameter("custIdString");	
			HashMap timemap = (HashMap) request.getSession().getAttribute("timemap");
			if (custIdString.lastIndexOf(",") == -1) {
				request.setAttribute("tipinfo", "上传失败:请查询已签到的与会人员！");
				return mapping.findForward("error");
			}
			String[] custid = custIdString.split(",");
			
			for (int i = 0; i < custid.length; i++) {
				if (SignUtil
						.getSignedOrNot(confid, Integer.parseInt(custid[i]))) {
					request.setAttribute("tipinfo", "该与会人员 " + custid[i]
							+ " 已经上传！");
					return mapping.findForward("error");
				}
			}
			String custs = "";
			if (SignUtil.uploadSign(confid, custid, timemap)) {
				/*for (int i = 0; i < custid.length; i++) {
					custs += GetDictionary.getCustNameById(Integer
							.parseInt(custid[i]))
							+ " ";
				}*/
				request.setAttribute("tipinfo",  "签到上传成功！");
				return mapping.findForward("succeed");
			} else {
				request.setAttribute("tipinfo", "签到失败，请检查原因！");
				return mapping.findForward("error");
			}
		}
          else {
			String physicalno = "";
			int   con_id =0;
			HashMap timemap = new HashMap();
			boolean isMultipart = FileUpload.isMultipartContent(request);
			if (isMultipart) {
				DiskFileUpload upload = new DiskFileUpload();

				// parse this request by the handler
				// this gives us a list of items from the request
				List items = upload.parseRequest(request);

				Iterator itr = items.iterator();

				while (itr.hasNext()) {
					FileItem item = (FileItem) itr.next();
					// check if the current item is a form field or an uploaded
					// file
					if (!item.isFormField()) {
						// the item must be an uploaded file save it to disk.
						// Note
						// that there
						// seems to be a bug in item.getName() as it returns the
						// full path on
						// the client's machine for the uploaded file name,
						// instead
						// of the file
						// name only. To overcome that, I have used a workaround
						// using
						// fullFile.getName().
						InputStream is = item.getInputStream();
						try {

							InputStreamReader isr = new InputStreamReader(is);
							BufferedReader br = new BufferedReader(isr);
							String Line = br.readLine();
							while (Line != null) {
								String[] record = Line.split(",");
								con_id = Integer.parseInt(record[3]);
								if (record.length == 1) {
									physicalno += record[0] + "\r\n";
								}
								if (record.length >= 2) {
									if(physicalno.indexOf(record[0])==-1){
										physicalno += record[0] + "\r\n";
										timemap.put(record[0], record[1]);
									}									
								}
								Line = br.readLine();
							}
							// physicalno = analysisFile(is);
							break;

						} catch (IOException e) {

							e.printStackTrace();
						} catch (Exception e) {
							e.printStackTrace();
						}

					}
				}
			}
			if (!"".equals(physicalno)) {
				String custIdString ="";
				List attendeelist = AttendeeUtil.getAttendeeList(physicalno,con_id ,
						timemap);
				HashMap confMap = new HashMap();
				
				if(attendeelist != null && attendeelist.size()>0){
					for(int i=0;i<attendeelist.size();i++){
						confMap =(HashMap)attendeelist.get(i);
						custIdString = custIdString+confMap.get("cutId")+",";
					}
				}
				HashMap newmap = AttendeeUtil.gettiemMap(physicalno, timemap);
				TConference conference = ConferenceUtil.getConfById(new Integer(con_id));
				request.setAttribute("conference", conference);
				request.setAttribute("result", attendeelist);
				request.setAttribute("physicalno", physicalno);
				request.setAttribute("custIdString", custIdString);
				request.getSession().setAttribute("timemap", newmap);
			}
			return mapping.findForward("sign.upload.list");

		}
	}

	public String analysisFile(InputStream is) throws IOException {
		InputStreamReader isr = new InputStreamReader(is);
		BufferedReader br = new BufferedReader(isr);
		String physicalno = "";
		String signtime = "";
		String Line = br.readLine();
		while (Line != null) {
			String[] record = Line.split(",");
			if (record.length == 1) {
				physicalno += record[0] + "\r\n";
			}
			if (record.length == 2) {
				physicalno += record[0] + "\r\n";
				signtime += record[1] + "\r\n";
			}
			Line = br.readLine();
		}
		return physicalno;
	}
}
