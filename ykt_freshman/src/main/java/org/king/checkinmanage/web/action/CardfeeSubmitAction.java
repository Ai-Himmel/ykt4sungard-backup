/**
 * 
 */
package org.king.checkinmanage.web.action;

import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionMessages;
import org.apache.struts.validator.DynaValidatorForm;
import org.king.checkinmanage.domain.CheckinSubmin;
import org.king.checkinmanage.domain.StuCardfeeSubmit;
import org.king.checkinmanage.domain.Stuhealthinfo;
import org.king.checkinmanage.service.CheckinmanageService;
import org.king.framework.web.action.BaseAction;
import org.king.utils.DateUtil;
public class CardfeeSubmitAction extends BaseAction{
	
    private CheckinmanageService checkinmanageservice;
	
	public void setCheckinmanageService(CheckinmanageService checkinmanageservice) {
		this.checkinmanageservice = checkinmanageservice;
	}
	
	public ActionForward cardfeesubmitlist(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		
		List stucheckininfoList=new ArrayList();
		List stucheckintotalList=new ArrayList();
		
		try {
			 if(checkinmanageservice==null)
				 System.out.println("service is null");
			 
            //�༶������Ϣ�ύ���ѯ
			 String sqlstring="select new Map(cs.id as id,cs.classNo as classNo,cs.ifSubmitted as ifSubmitted) from StuCardfeeSubmit cs";
			 
			 List checkinsubminList=checkinmanageservice.find(sqlstring);	 
			 			
			 //Ӧ��������
			 List sl1=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo) as shouldcheckinNum) from StuCardfeeInfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' group by c.classNo");
			 List sl1total=checkinmanageservice.find("select new Map(count(ci.studentNo) as shouldcheckinNumtotal) from StuCardfeeInfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"'");
			
			 if(sl1!=null&&sl1.size()>0){
				 //ʵ�ʱ�������
				 List sl2=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo) as exactcheckinNum) from StuCardfeeInfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ecardPayed='1' group by c.classNo");
				 List sl2total=checkinmanageservice.find("select new Map(count(ci.studentNo) as exactcheckinNumtotal) from StuCardfeeInfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ecardPayed='1'");
				 //δ��������
				 List sl3=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo)as notcheckinNum) from StuCardfeeInfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ecardPayed='0' group by c.classNo");
				 List sl3total=checkinmanageservice.find("select new Map(count(ci.studentNo)as notcheckinNumtotal) from StuCardfeeInfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ecardPayed='0'");
                 				 
				 for(int i=0;i<sl1.size();i++){
	 
					 Map m=(Map)sl1.get(i);
					 String cno=(String)m.get("classNo");
					 
					 if(sl2!=null&&sl2.size()>0){
						 int j=0;
						 for(j=0;j<sl2.size();j++){
					         Map m2=(Map)sl2.get(j);
					         if(((String)m2.get("classNo")).equals(cno)){
					             m.put("exactcheckinNum",m2.get("exactcheckinNum"));//�ϲ���һ��Map������
					             break;
					         }
						 }
						 if(j==sl2.size()||j>sl2.size()){
							 m.put("exactcheckinNum",null);
						 }
					 }
					 else
						 m.put("exactcheckinNum",null);
					 					 
					 if(sl3!=null&&sl3.size()>0){
						 int j=0;
						 for(j=0;j<sl3.size();j++){
					         Map m3=(Map)sl3.get(j);
					         if(((String)m3.get("classNo")).equals(cno)){
					             m.put("notcheckinNum",m3.get("notcheckinNum"));//�ϲ���һ��Map������
					             break;
					         }
						 }
						 if(j==sl3.size()||j>sl3.size()){
							 m.put("notcheckinNum",null);
						 }
					 }
					 else
						 m.put("notcheckinNum",null);					 
					 
					 
					 //�༶�����ύ״̬
					 if(checkinsubminList!=null&&checkinsubminList.size()>0){
						 int j=0;
						 for(j=0;j<checkinsubminList.size();j++){
							 Map mcs=(Map)checkinsubminList.get(j);
							 if(((String)mcs.get("classNo")).equals(cno)){
								 m.put("ifSubmitted",(String)mcs.get("ifSubmitted"));
								 m.put("csid",(String)mcs.get("id"));
								 break;
							 }
						 }
						 if(j==checkinsubminList.size()||j>checkinsubminList.size()){
							 m.put("ifSubmitted",null);//�����޸ð���ύ��¼,��˵���ð౨����Ϣδ�ύ
							 m.put("csid",null);
						 }
					 }
					 else{
						 m.put("ifSubmitted",null);//��Ϊ��,���а༶��δ�ύ������Ϣ	
						 m.put("csid",null);
					 }
					 			 
					 stucheckininfoList.add(m);
			 
			     }
				 
                 //������
				 for(int k=0;k<sl1total.size();k++){
					 Map t=(Map)sl1total.get(k);
					 
					 if(sl2total!=null&&sl2total.size()>k&&sl2total.get(k)!=null){
					     Map t2=(Map)sl2total.get(k);
					     t.put("exactcheckinNumtotal",t2.get("exactcheckinNumtotal"));//�ϲ���һ��Map������
					 }
					 else
						 t.put("exactcheckinNumtotal",null);
					 
					 if(sl3total!=null&&sl3total.size()>k&&sl3total.get(k)!=null){
					     Map t3=(Map)sl3total.get(k);
					     t.put("notcheckinNumtotal",t3.get("notcheckinNumtotal"));
					 }
					 else
						 t.put("notcheckinNumtotal",null);					 
					 
					 stucheckintotalList.add(t);
				 }
				 
			 }
		 
			 
			 if(stucheckininfoList!=null&&stucheckininfoList.size()!=0){
				 request.setAttribute("tjlist",stucheckininfoList);
				 request.setAttribute("tjlisttotal",stucheckintotalList);
				 //System.out.println("tongji list success");
				 //System.out.println(stucheckininfoList.size());
				 return mapping.findForward("cardfeesubmit");
			 }
			 else
				 return mapping.findForward("cardfeesubmit"); 

			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}
		
	}
		
	public ActionForward ecardfeesubmit(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		DynaValidatorForm aform = (DynaValidatorForm) form;	        
		StuCardfeeSubmit checkinsubmin = (StuCardfeeSubmit)aform.get("cardfeesubmit");
        
		try {
			checkinsubmin.setClassNo(request.getParameter("updateclassNo"));			
			checkinsubmin.setIfSubmitted("1");
			checkinsubmin.setId(request.getParameter("updateid"));
 		     // ���ݿ���֤
		
			 if(checkinmanageservice==null)
				 System.out.println("service is null");
			 if(checkinsubmin.getId()!=null&&checkinsubmin.getId().length()!=0&&!checkinsubmin.getId().equals("null"))
			     checkinmanageservice.update(checkinsubmin);
			 else
				 checkinmanageservice.save(checkinsubmin);				 
			 
			 return mapping.findForward("success");
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("update error");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward ecardfeebackto(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		DynaValidatorForm aform = (DynaValidatorForm) form;	        
		StuCardfeeSubmit checkinsubmin = (StuCardfeeSubmit)aform.get("cardfeesubmit");
        
		try {			
			checkinsubmin.setClassNo(request.getParameter("updateclassNo"));
			checkinsubmin.setIfSubmitted("0");
 		    checkinsubmin.setId(request.getParameter("updateid"));
			
			 if(checkinmanageservice==null)
				 System.out.println("service is null");
			 if(checkinsubmin.getId()!=null&&checkinsubmin.getId().length()!=0&&!checkinsubmin.getId().equals("null"))
			     checkinmanageservice.update(checkinsubmin);
			 System.out.println("update success");
			 return mapping.findForward("success");
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("update error");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward cardfeesubmitlistview(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		
		List stucheckininfoList=new ArrayList();
		List stucheckintotalList=new ArrayList();
		
		try {
			 if(checkinmanageservice==null)
				 System.out.println("service is null");
			 
            //�༶������Ϣ�ύ���ѯ
			 String sqlstring="select new Map(cs.id as id,cs.classNo as classNo,cs.ifSubmitted as ifSubmitted) from StuCardfeeSubmit cs";
			 
			 List checkinsubminList=checkinmanageservice.find(sqlstring);	 
			 			
			 //Ӧ��������
			 List sl1=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo) as shouldcheckinNum) from StuCardfeeInfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' group by c.classNo");
			 List sl1total=checkinmanageservice.find("select new Map(count(ci.studentNo) as shouldcheckinNumtotal) from StuCardfeeInfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"'");
			
			 if(sl1!=null&&sl1.size()>0){
				 //ʵ�ʱ�������
				 List sl2=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo) as exactcheckinNum) from StuCardfeeInfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ecardPayed='1' group by c.classNo");
				 List sl2total=checkinmanageservice.find("select new Map(count(ci.studentNo) as exactcheckinNumtotal) from StuCardfeeInfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ecardPayed='1'");
				 //δ��������
				 List sl3=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo)as notcheckinNum) from StuCardfeeInfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ecardPayed='0' group by c.classNo");
				 List sl3total=checkinmanageservice.find("select new Map(count(ci.studentNo)as notcheckinNumtotal) from StuCardfeeInfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ecardPayed='0'");
                 				 
				 for(int i=0;i<sl1.size();i++){
	 
					 Map m=(Map)sl1.get(i);
					 String cno=(String)m.get("classNo");
					 
					 if(sl2!=null&&sl2.size()>0){
						 int j=0;
						 for(j=0;j<sl2.size();j++){
					         Map m2=(Map)sl2.get(j);
					         if(((String)m2.get("classNo")).equals(cno)){
					             m.put("exactcheckinNum",m2.get("exactcheckinNum"));//�ϲ���һ��Map������
					             break;
					         }
						 }
						 if(j==sl2.size()||j>sl2.size()){
							 m.put("exactcheckinNum",null);
						 }
					 }
					 else
						 m.put("exactcheckinNum",null);
					 					 
					 if(sl3!=null&&sl3.size()>0){
						 int j=0;
						 for(j=0;j<sl3.size();j++){
					         Map m3=(Map)sl3.get(j);
					         if(((String)m3.get("classNo")).equals(cno)){
					             m.put("notcheckinNum",m3.get("notcheckinNum"));//�ϲ���һ��Map������
					             break;
					         }
						 }
						 if(j==sl3.size()||j>sl3.size()){
							 m.put("notcheckinNum",null);
						 }
					 }
					 else
						 m.put("notcheckinNum",null);					 
					 
					 
					 //�༶�����ύ״̬
					 if(checkinsubminList!=null&&checkinsubminList.size()>0){
						 int j=0;
						 for(j=0;j<checkinsubminList.size();j++){
							 Map mcs=(Map)checkinsubminList.get(j);
							 if(((String)mcs.get("classNo")).equals(cno)){
								 m.put("ifSubmitted",(String)mcs.get("ifSubmitted"));
								 m.put("csid",(String)mcs.get("id"));
								 break;
							 }
						 }
						 if(j==checkinsubminList.size()||j>checkinsubminList.size()){
							 m.put("ifSubmitted",null);//�����޸ð���ύ��¼,��˵���ð౨����Ϣδ�ύ
							 m.put("csid",null);
						 }
					 }
					 else{
						 m.put("ifSubmitted",null);//��Ϊ��,���а༶��δ�ύ������Ϣ	
						 m.put("csid",null);
					 }
					 			 
					 stucheckininfoList.add(m);
			 
			     }
				 
                 //������
				 for(int k=0;k<sl1total.size();k++){
					 Map t=(Map)sl1total.get(k);
					 
					 if(sl2total!=null&&sl2total.size()>k&&sl2total.get(k)!=null){
					     Map t2=(Map)sl2total.get(k);
					     t.put("exactcheckinNumtotal",t2.get("exactcheckinNumtotal"));//�ϲ���һ��Map������
					 }
					 else
						 t.put("exactcheckinNumtotal",null);
					 
					 if(sl3total!=null&&sl3total.size()>k&&sl3total.get(k)!=null){
					     Map t3=(Map)sl3total.get(k);
					     t.put("notcheckinNumtotal",t3.get("notcheckinNumtotal"));
					 }
					 else
						 t.put("notcheckinNumtotal",null);					 
					 
					 stucheckintotalList.add(t);
				 }
				 
			 }
		 
			 
			 if(stucheckininfoList!=null&&stucheckininfoList.size()!=0){
				 request.setAttribute("tjlist",stucheckininfoList);
				 request.setAttribute("tjlisttotal",stucheckintotalList);
				 //System.out.println("tongji list success");
				 //System.out.println(stucheckininfoList.size());
				 return mapping.findForward("cardfeesubmitlist");
			 }
			 else
				 return mapping.findForward("cardfeesubmitlist"); 

			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}
		
	}

}
