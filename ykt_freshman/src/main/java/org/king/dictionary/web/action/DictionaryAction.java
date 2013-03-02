/**
 * 
 */
package org.king.dictionary.web.action;

import org.king.framework.web.action.BaseAction;

/**
 * @author jackey
 *
 */

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.sql.Timestamp;
import java.sql.Time;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.HashMap;
import java.util.Map;
import java.sql.Date;
import java.sql.Clob;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.poi.hssf.usermodel.HSSFCell;
import org.apache.poi.hssf.usermodel.HSSFRow;
import org.apache.poi.hssf.usermodel.HSSFSheet;
import org.apache.poi.hssf.usermodel.HSSFWorkbook;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionMessage;
import org.apache.struts.action.ActionMessages;
import org.apache.struts.validator.DynaValidatorForm;
import org.king.checkinmanage.domain.Noticemodel;
import org.king.checkinmanage.domain.Stucheckininfo;
import org.king.checkinmanage.domain.Stuhealthinfo;
import org.king.checkinmanage.service.CheckinmanageService;
import org.king.classmanage.domain.Dictionary;
import org.king.classmanage.domain.DictionaryId;
import org.king.dictionary.service.DictionaryService;
import org.king.framework.web.action.BaseAction;
import org.king.rcvmanage.domain.Stuarriveinfo;
import org.king.utils.DateUtil;


public class DictionaryAction  extends BaseAction{
	
    private CheckinmanageService checkinmanageservice;
	
	public void setCheckinmanageService(CheckinmanageService checkinmanageservice) {
		this.checkinmanageservice = checkinmanageservice;
	}
	private DictionaryService dictionaryService;
	public void setDictionaryService(DictionaryService dictionaryService){
		this.dictionaryService=dictionaryService;
	}
	
	public ActionForward saveArea(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		DynaValidatorForm aform = (DynaValidatorForm) form;
		Dictionary dictionary = (Dictionary)aform.get("dictionary");
		DictionaryId dictionaryId = (DictionaryId)aform.get("dictionaryId");
		String msg="";
		try {			
			 boolean flag=dictionaryService.check4Add(dictionaryId);
			 if(flag){
				 dictionary.setId(dictionaryId);
			     dictionaryService.save(dictionary);
			     msg="0";
			 }
			 else
				 msg="2";
			 
			 request.setAttribute("msg",msg);
			 return mapping.findForward("areasavesuccess");
		} catch (Exception e) {
			e.printStackTrace();
			request.setAttribute("msg","1");
			return mapping.findForward("faile");
		}

	}
				
	public ActionForward updateArea(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

        String dictvalue=request.getParameter("dictvalue");
        String dictcaption=request.getParameter("dictCaption"+dictvalue);
        
		try {
			Dictionary dictionary=findbyId(dictvalue,"17");
 		    if(dictionary!=null){
 		    	dictionary.setDictCaption(dictcaption);
 		    	dictionaryService.update(dictionary);
			    request.setAttribute("msg","0");
 		    }
			 return mapping.findForward("areasavesuccess");
		} catch (Exception e) {
			e.printStackTrace();
			request.setAttribute("msg","1");
			return mapping.findForward("faile");
		}

	}	
	
	public ActionForward saveLocation(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		DynaValidatorForm aform = (DynaValidatorForm) form;
		Dictionary dictionary = (Dictionary)aform.get("dictionary");
		DictionaryId dictionaryId = (DictionaryId)aform.get("dictionaryId");
		String msg="";
		try {			
			 boolean flag=dictionaryService.check4Add(dictionaryId);
			 if(flag){
				 dictionary.setId(dictionaryId);
			     dictionaryService.save(dictionary);
			     msg="0";
			 }
			 else
				 msg="2";
			 
			 request.setAttribute("msg",msg);
			 return mapping.findForward("locationsavesuccess");
		} catch (Exception e) {
			e.printStackTrace();
			request.setAttribute("msg","1");
			return mapping.findForward("faile");
		}

	}
				
	public ActionForward updateLocation(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

        String dictvalue=request.getParameter("dictvalue");
        String dictcaption=request.getParameter("dictCaption"+dictvalue);
        String dictsort=request.getParameter("dictSort"+dictvalue);
        
		try {
			Dictionary dictionary=findbyId(dictvalue,"20");
 		    if(dictionary!=null){
 		    	dictionary.setDictCaption(dictcaption);
 		    	dictionary.setDictSort(Double.valueOf(dictsort));
 		    	dictionaryService.update(dictionary);
			    request.setAttribute("msg","0");
 		    }
			 return mapping.findForward("locationsavesuccess");
		} catch (Exception e) {
			e.printStackTrace();
			request.setAttribute("msg","1");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward saveLevel(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		DynaValidatorForm aform = (DynaValidatorForm) form;
		Dictionary dictionary = (Dictionary)aform.get("dictionary");
		DictionaryId dictionaryId = (DictionaryId)aform.get("dictionaryId");
		String msg="";
		try {			
			 boolean flag=dictionaryService.check4Add(dictionaryId);
			 if(flag){
				 dictionary.setId(dictionaryId);
			     dictionaryService.save(dictionary);
			     msg="0";
			 }
			 else
				 msg="2";
			 
			 request.setAttribute("msg",msg);
			 return mapping.findForward("cengsavesuccess");
		} catch (Exception e) {
			e.printStackTrace();
			request.setAttribute("msg","1");
			return mapping.findForward("faile");
		}

	}
				
	public ActionForward updateLevel(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

        String dictvalue=request.getParameter("dictvalue");
        String dictcaption=request.getParameter("dictCaption"+dictvalue);
        String dictsort=request.getParameter("dictSort"+dictvalue);
        
		try {
			Dictionary dictionary=findbyId(dictvalue,"22");
 		    if(dictionary!=null){
 		    	dictionary.setDictCaption(dictcaption);
 		    	dictionary.setDictSort(Double.valueOf(dictsort));
 		    	dictionaryService.update(dictionary);
			    request.setAttribute("msg","0");
 		    }
			 return mapping.findForward("cengsavesuccess");
		} catch (Exception e) {
			e.printStackTrace();
			request.setAttribute("msg","1");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward saveDormitory(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		DynaValidatorForm aform = (DynaValidatorForm) form;
		Dictionary dictionary = (Dictionary)aform.get("dictionary");
		DictionaryId dictionaryId = (DictionaryId)aform.get("dictionaryId");
		String msg="";
		try {			
			 boolean flag=dictionaryService.check4Add(dictionaryId);
			 if(flag){
				 
				 dictionary.setId(dictionaryId);
				 String fudans="2,7,8";//¸´µ©Ñ§Ôº¾ÉÂ¥ºÅ×Öµä¶ÔÓ¦µÄÇøÓò´úÂë
				 if(fudans.indexOf(dictionary.getDictParent())!=-1)
				     dictionary.setDictParent1("fudan");
				 
			     dictionaryService.save(dictionary);
				 
			     
			     if(fudans.indexOf(dictionary.getDictParent())!=-1){
			         //Í¬²½¸´µ©Ñ§Ôº¾ÉÂ¥ºÅ×Öµä
			         DictionaryId fddictionaryId=new DictionaryId();
			         fddictionaryId.setDictNo(new Integer(7));
			         fddictionaryId.setDictValue(dictionaryId.getDictValue());
			         Dictionary fddictionary=new Dictionary();
			         fddictionary.setId(fddictionaryId);
			         fddictionary.setDictCaption(dictionary.getDictCaption());
			         fddictionary.setDictName("Â¥ºÅ");
			         fddictionary.setDictParent(dictionary.getDictParent());			         
			         dictionaryService.save(fddictionary);
			     }
			     msg="0";
			 }
			 else
				 msg="2";
			 
			 request.setAttribute("msg",msg);
			 return mapping.findForward("dormitorysavesuccess");
		} catch (Exception e) {
			e.printStackTrace();
			request.setAttribute("msg","1");
			return mapping.findForward("faile");
		}

	}
				
	public ActionForward updateDormitory(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

        String dictvalue=request.getParameter("dictvalue");
        String dictcaption=request.getParameter("dictCaption"+dictvalue);
        String dictsort=request.getParameter("dictSort"+dictvalue);
        
		try {
			Dictionary dictionary=findbyId(dictvalue,"21");
 		    if(dictionary!=null){
 		    	dictionary.setDictCaption(dictcaption);
 		    	dictionary.setDictSort(Double.valueOf(dictsort));
 		    	dictionaryService.update(dictionary);
 		    	
 		    	String fudans="2,7,8";//¸´µ©Ñ§Ôº¾ÉÂ¥ºÅ×Öµä¶ÔÓ¦µÄÇøÓò´úÂë
 		    	if(fudans.indexOf(dictionary.getDictParent())!=-1){
			        //Í¬²½¸´µ©Ñ§Ôº¾ÉÂ¥ºÅ×Öµä 		    		 
 		    		Dictionary fddictionary=findbyId(dictvalue,"7");
			        fddictionary.setDictCaption(dictcaption);
			        dictionaryService.update(fddictionary);
			     }
			    request.setAttribute("msg","0");
 		    }
			 return mapping.findForward("dormitorysavesuccess");
		} catch (Exception e) {
			e.printStackTrace();
			request.setAttribute("msg","1");
			return mapping.findForward("faile");
		}

	}
		
	public  Dictionary findbyId(String dictvalue,String dictno)
	throws Exception {
	
       try {
	      Dictionary dictionary=dictionaryService.findbyId(dictvalue,dictno);	 			 
	      return dictionary;
	      
      } catch (Exception e) {
	    e.printStackTrace();
      }
      return null;

      }
	
	public ActionForward findareaList(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
				
		try {
			 
			 String sqlstring="select new Map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) from Dictionary a where a.id.dictNo=17 order by a.id.dictValue";
			 
			 List dictList=dictionaryService.find(sqlstring);
			 
			 if(dictList!=null&&dictList.size()!=0){
				 request.setAttribute("dictlist",dictList);
				 request.setAttribute("listcount",new Integer(dictList.size()));				 		 
			 }
			 return mapping.findForward("arealist");	
			
		} catch (Exception e) {
			e.printStackTrace();
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward findcengList(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
				
		try {
			 
			 String sqlstring="select new Map(a.id.dictValue as dictValue,a.dictCaption as dictCaption,a.dictSort as dictSort) from Dictionary a where a.id.dictNo=22 order by a.dictSort";
			 
			 List dictList=dictionaryService.find(sqlstring);
			 
			 if(dictList!=null&&dictList.size()!=0){
				 request.setAttribute("dictlist",dictList);
				 request.setAttribute("listcount",new Integer(dictList.size()));				 		 
			 }
			 return mapping.findForward("cenglist");	
			
		} catch (Exception e) {
			e.printStackTrace();
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward findlocationList(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
				
		try {
			 
			 String sqlstring="select new Map(b.dictCaption as areaName,a.id.dictValue as dictValue,a.dictCaption as dictCaption,a.dictSort as dictSort) from Dictionary a,Dictionary b where b.id.dictNo=17 and b.id.dictValue=a.dictParent and a.id.dictNo=20 ";
			 
			 if(request.getParameter("search_area")!=null&&request.getParameter("search_area").length()>0)
				 sqlstring=sqlstring+" and b.id.dictValue='"+request.getParameter("search_area")+"'";
			 
			 sqlstring=sqlstring+" order by b.id.dictValue,a.dictSort";
			 
			 List dictList=dictionaryService.find(sqlstring);
			 
			 if(dictList!=null&&dictList.size()!=0){
				 request.setAttribute("dictlist",dictList);
				 request.setAttribute("listcount",new Integer(dictList.size()));				 		 
			 }
			 
			 sqlstring="select new Map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) from Dictionary a where a.id.dictNo=17 order by a.id.dictValue";
			 List areaList=dictionaryService.find(sqlstring);
			 if(areaList!=null&&areaList.size()>0)
				 request.setAttribute("arealist",areaList);
			 return mapping.findForward("locationlist");	
			
		} catch (Exception e) {
			e.printStackTrace();
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward finddormitoryList(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
				
		try {
			 
			 String sqlstring="select new Map(xq.dictCaption as areaName,b.dictCaption as locationName,a.id.dictValue as dictValue,a.dictCaption as dictCaption,a.dictSort as dictSort) from Dictionary a,Dictionary b,Dictionary xq where xq.id.dictNo=17 and xq.id.dictValue=b.dictParent and b.id.dictNo=20 and b.id.dictValue=a.dictParent and a.id.dictNo=21 ";
			 
			 if(request.getParameter("search_area")!=null&&request.getParameter("search_area").length()>0)
				 sqlstring=sqlstring+" and xq.id.dictValue='"+request.getParameter("search_area")+"'";
			 if(request.getParameter("search_location")!=null&&request.getParameter("search_location").length()>0)
				 sqlstring=sqlstring+" and b.id.dictValue='"+request.getParameter("search_location")+"'";
			 
			 sqlstring=sqlstring+" order by xq.id.dictValue,b.dictSort,a.dictSort";
			 
			 List dictList=dictionaryService.find(sqlstring);
			 
			 if(dictList!=null&&dictList.size()!=0){
				 request.setAttribute("dictlist",dictList);
				 request.setAttribute("listcount",new Integer(dictList.size()));				 		 
			 }
			 
			 sqlstring="select new Map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) from Dictionary a where a.id.dictNo=17 order by a.id.dictValue";
			 List areaList=dictionaryService.find(sqlstring);
			 if(areaList!=null&&areaList.size()>0)
				 request.setAttribute("arealist",areaList);
			 sqlstring="select new Map(a.id.dictValue as dictValue,a.dictCaption as dictCaption) from Dictionary a where a.id.dictNo=20 order by a.dictSort";
			 List locationList=dictionaryService.find(sqlstring);
			 if(locationList!=null&&locationList.size()>0)
				 request.setAttribute("locationlist",locationList);
			 
			 String[][] areaandlocList=getAreaandLoc();
			 if(areaandlocList!=null&&areaandlocList.length>0){
				 request.setAttribute("allist",areaandlocList);
			 }
			 
			 return mapping.findForward("dormitorylist");	
			
		} catch (Exception e) {
			e.printStackTrace();
			return mapping.findForward("faile");
		}

	}
	
	public String[][] getAreaandLoc(){
		
		   List rList=new ArrayList();			   
		   String sqlstring = "";	
		   String[][] result;
		   
		   try {
				
		     sqlstring="select new Map(b.id.dictValue as areaCode,a.id.dictValue as locationCode,a.dictCaption as locationName) from Dictionary a,Dictionary b where b.id.dictNo=17 and b.id.dictValue=a.dictParent and a.id.dictNo=20 order by b.id.dictValue,a.dictSort";
		     
		     rList=dictionaryService.find(sqlstring);
		     if(rList!=null&&rList.size()>0){
		    	 result=new String[rList.size()][3];
		         for(int i=0;i<rList.size();i++){
		             result[i][0] =(String)(((Map)rList.get(i)).get("locationCode"));
		             result[i][1] = (String)(((Map)rList.get(i)).get("locationName"));
		             result[i][2] = (String)(((Map)rList.get(i)).get("areaCode"));
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
			
}
