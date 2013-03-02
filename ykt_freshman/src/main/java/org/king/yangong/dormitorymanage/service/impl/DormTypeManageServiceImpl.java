package org.king.yangong.dormitorymanage.service.impl;

import java.sql.Types;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.utils.DateUtil;
import org.king.yangong.dormitorymanage.domain.GraduateType;
import org.king.yangong.dormitorymanage.service.DormTypeManageService;
import org.king.yangong.dormitorymanage.web.help.CollegeWithStuCount;

public class DormTypeManageServiceImpl implements DormTypeManageService {

	private BaseDAO baseDAO;
	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}
	
	public List getDormTypeList(String type) {
		
		List li = new ArrayList();
		StringBuffer hqlStrBuf = 
			new StringBuffer("select new map(a.id as id,a.graduateType as graduateType,b.personName as updator,a.updateTime as updateTime) "
				+ " from GraduateType a,Person b");
		StringBuffer whereStrBuf = 
			new StringBuffer(" where 1=1 and a.ifdeleted='1' and a.updator = b.id ");
		MyQuery mq = new MyQuery();
		if(type != null && !type.equals("")){
			whereStrBuf.append(" and a.graduateType like ?");
			mq.addPara("%" + type + "%", Types.VARCHAR);
		}
		whereStrBuf.append(" order by a.updateTime desc");
		hqlStrBuf.append(whereStrBuf);
		mq.setQueryString(hqlStrBuf.toString());
		li = baseDAO.findEntity(mq);
		
		return li;
	}

	public Object getDormTypeInfo(String itemList) {
		return baseDAO.getEntity(GraduateType.class, itemList);
	}

	public void saveDormTypeInfo(GraduateType graduateType) {
		baseDAO.saveEntity(graduateType);
		
	}

	public void updateDormTypeInfo(GraduateType graduateType) {
		// TODO Auto-generated method stub
		baseDAO.updateEntity(graduateType);
	}

	public void deleteDormTypeInfo(String[] itemLists) {
		// TODO Auto-generated method stub
		for(int i=0 ; i<itemLists.length ; i++){
			GraduateType graduateType=(GraduateType)baseDAO.getEntity(GraduateType.class, itemLists[i]);
			graduateType.setIfdeleted("0");
			baseDAO.updateEntity(graduateType);
		}
	}
	
	//宿舍分配统计
	public List getDormStatbyCollege(String stuemp_no) {
		List list_stu = baseDAO
				.findEntity("select new Map"
						+ "(a.curCollege as curCollege,count(a.graduateNo) as colStuNum) "
						+ "from YxGraduate a ,TabSsManager b where a.distriction=b.tabSsDept.id "
						+ "and b.stuNo='"
						+ stuemp_no
						+ "' and a.enrollYear='"
						+ DateUtil.getNow("yyyy")
						+ "' "
						+ "and a.requestAvailable='1' and a.residentNeed='1' "
						+ "group by a.curCollege ");
		
		List list_dorm = baseDAO
		      .findEntity("select new map(a.classId as curCollege,sum(a.distributeNum) as colDormNum) "
				+ " from ClassDorm a,TabSsManager b,Dormitorymodel c where a.dormId=c.dormitoryId and c.curDormDept=b.tabSsDept.id "
				+ "and b.stuNo='"
				+ stuemp_no
				+ "' and a.curYear='"
				+ DateUtil.getNow("yyyy")
				+ "' " + "group by a.classId");
		
		List mmaleshouldbindList = baseDAO
		       .findEntity("select new Map"
						+ "(a.curCollege as curCollege,count(a.graduateNo) as mmaleshouldbindNum) "
						+ "from YxGraduate a ,TabSsManager b where a.distriction=b.tabSsDept.id "
						+ "and b.stuNo='"
						+ stuemp_no
						+ "' and a.enrollYear='"
						+ DateUtil.getNow("yyyy")
						+ "' "
						+ "and a.requestAvailable='1' and a.residentNeed='1' and a.sex='1' and a.studentType='M' "
						+ "group by a.curCollege,a.studentType ");
		List mfemaleshouldbindList =baseDAO
		      .findEntity("select new Map"
						+ "(a.curCollege as curCollege,count(a.graduateNo) as mfemaleshouldbindNum) "
						+ "from YxGraduate a ,TabSsManager b where a.distriction=b.tabSsDept.id "
						+ "and b.stuNo='"
						+ stuemp_no
						+ "' and a.enrollYear='"
						+ DateUtil.getNow("yyyy")
						+ "' "
						+ "and a.requestAvailable='1' and a.residentNeed='1' and a.sex='2' and a.studentType='M' "
						+ "group by a.curCollege,a.studentType ");

		List dmaleshouldbindList = baseDAO
		       .findEntity("select new Map"
						+ "(a.curCollege as curCollege,count(a.graduateNo) as dmaleshouldbindNum) "
						+ "from YxGraduate a ,TabSsManager b where a.distriction=b.tabSsDept.id "
						+ "and b.stuNo='"
						+ stuemp_no
						+ "' and a.enrollYear='"
						+ DateUtil.getNow("yyyy")
						+ "' "
						+ "and a.requestAvailable='1' and a.residentNeed='1' and a.sex='1' and a.studentType='D' "
						+ "group by a.curCollege,a.studentType ");
		List dfemaleshouldbindList = baseDAO
		      .findEntity("select new Map"
						+ "(a.curCollege as curCollege,count(a.graduateNo) as dfemaleshouldbindNum) "
						+ "from YxGraduate a ,TabSsManager b where a.distriction=b.tabSsDept.id "
						+ "and b.stuNo='"
						+ stuemp_no
						+ "' and a.enrollYear='"
						+ DateUtil.getNow("yyyy")
						+ "' "
						+ "and a.requestAvailable='1' and a.residentNeed='1' and a.sex='2' and a.studentType='D' "
						+ "group by a.curCollege,a.studentType ");
		
		List mmaleexactbindList = baseDAO
	       .findEntity("select new map(a.classId as curCollege,sum(a.distributeNum) as mmaleexactbindNum) "
				+ "from ClassDorm a ,TabSsManager b,Dormitorymodel c where a.dormId=c.dormitoryId and c.curDormDept=b.tabSsDept.id "
				+ "and b.stuNo='"
				+ stuemp_no
				+ "' and a.curYear='"
				+ DateUtil.getNow("yyyy")
				+ "' "
				+ "and a.studentType='M' and a.sex='1' "
				+ " group by a.classId");
       List mfemaleexactbindList = baseDAO
           .findEntity("select new map(a.classId as curCollege,sum(a.distributeNum) as mfemaleexactbindNum) "
				+ "from ClassDorm a ,TabSsManager b,Dormitorymodel c where a.dormId=c.dormitoryId and c.curDormDept=b.tabSsDept.id "
				+ "and b.stuNo='"
				+ stuemp_no
				+ "' and a.curYear='"
				+ DateUtil.getNow("yyyy")
				+ "' "
				+ "and a.studentType='M' and a.sex='2' "
				+ " group by a.classId");

       List dmaleexactbindList = baseDAO
          .findEntity("select new map(a.classId as curCollege,sum(a.distributeNum) as dmaleexactbindNum) "
				+ "from ClassDorm a ,TabSsManager b,Dormitorymodel c where a.dormId=c.dormitoryId and c.curDormDept=b.tabSsDept.id "
				+ "and b.stuNo='"
				+ stuemp_no
				+ "' and a.curYear='"
				+ DateUtil.getNow("yyyy")
				+ "' "
				+ "and a.studentType='D' and a.sex='1' "
				+ " group by a.classId");
       List dfemaleexactbindList = baseDAO
          .findEntity("select new map(a.classId as curCollege,sum(a.distributeNum) as dfemaleexactbindNum) "
				+ "from ClassDorm a ,TabSsManager b,Dormitorymodel c where a.dormId=c.dormitoryId and c.curDormDept=b.tabSsDept.id "
				+ "and b.stuNo='"
				+ stuemp_no
				+ "' and a.curYear='"
				+ DateUtil.getNow("yyyy")
				+ "' "
				+ "and a.studentType='D' and a.sex='2' "
				+ " group by a.classId");
		
		
		int MMalesbtotal = 0;
		int MFemalesbtotal = 0;
		int DMalesbtotal = 0;
		int DFemalesbtotal = 0;
		int stuallSum = 0;
		
		int MMaleexbtotal = 0;
		int MFemaleexbtotal = 0;
		int DMaleexbtotal = 0;
		int DFemaleexbtotal = 0;
		int dormallSum = 0;
		
		for (int i = 0; i < list_stu.size(); i++) {
			Map collegeWithStuCount = (Map) list_stu
					.get(i);
			
			boolean hasremove=false;
			
			hasremove=false;
			for (int j = 0; j < mmaleshouldbindList.size(); j++) {				
				Map male = (Map) mmaleshouldbindList
						.get(j);
				String majorinmale = (String)male.get("curCollege");
				if (majorinmale.equals(collegeWithStuCount.get("curCollege"))) {
					collegeWithStuCount.put("mmaleshouldbindNum",male.get("mmaleshouldbindNum"));
					mmaleshouldbindList.remove(j);
					hasremove=true;
					break;
				}
			}
			if(!hasremove){
				collegeWithStuCount.put("mmaleshouldbindNum",new Integer(0));
			}
			
			hasremove=false;
			for (int k = 0; k < mfemaleshouldbindList.size(); k++) {
				hasremove=false;
				Map female = (Map) mfemaleshouldbindList
						.get(k);
				String majorinfemale = (String)female.get("curCollege");
				if (majorinfemale.equals(collegeWithStuCount.get("curCollege"))) {
					collegeWithStuCount.put("mfemaleshouldbindNum",female.get("mfemaleshouldbindNum"));
					mfemaleshouldbindList.remove(k);
					hasremove=true;
					break;
				}
			}
			if(!hasremove){
				collegeWithStuCount.put("mfemaleshouldbindNum",new Integer(0));
			}
						
			hasremove=false;
			for (int j = 0; j < dmaleshouldbindList.size(); j++) {
				Map male = (Map) dmaleshouldbindList
						.get(j);
				String majorinmale = (String)male.get("curCollege");
				if (majorinmale.equals(collegeWithStuCount.get("curCollege"))) {
					collegeWithStuCount.put("dmaleshouldbindNum",male.get("dmaleshouldbindNum"));
					dmaleshouldbindList.remove(j);
					hasremove=true;
					break;
				}
			}
			if(!hasremove){
				collegeWithStuCount.put("dmaleshouldbindNum",new Integer(0));
			}
			
			hasremove=false;
			for (int k = 0; k < dfemaleshouldbindList.size(); k++) {
				Map female = (Map) dfemaleshouldbindList
						.get(k);
				String majorinfemale = (String)female.get("curCollege");
				if (majorinfemale.equals(collegeWithStuCount.get("curCollege"))) {
					collegeWithStuCount.put("dfemaleshouldbindNum",female.get("dfemaleshouldbindNum"));
					dfemaleshouldbindList.remove(k);
					hasremove=true;
					break;
				}

			}
			if(!hasremove){
				collegeWithStuCount.put("dfemaleshouldbindNum",new Integer(0));
			}
			
			hasremove=false;
			for (int j = 0; j < mmaleexactbindList.size(); j++) {
				Map male = (Map) mmaleexactbindList
						.get(j);
				String majorinmale = (String)male.get("curCollege");
				if (majorinmale.equals(collegeWithStuCount.get("curCollege"))) {
					collegeWithStuCount.put("mmaleexactbindNum",male.get("mmaleexactbindNum"));
					mmaleexactbindList.remove(j);
					hasremove=true;
					break;
				}
			}
			if(!hasremove){
				collegeWithStuCount.put("mmaleexactbindNum",new Integer(0));
			}
			
			hasremove=false;
			for (int k = 0; k < mfemaleexactbindList.size(); k++) {
				Map female = (Map) mfemaleexactbindList
						.get(k);
				String majorinfemale = (String)female.get("curCollege");
				if (majorinfemale.equals(collegeWithStuCount.get("curCollege"))) {
					collegeWithStuCount.put("mfemaleexactbindNum",female.get("mfemaleexactbindNum"));
					mfemaleexactbindList.remove(k);
					hasremove=true;
					break;
				}
			}
			if(!hasremove){
				collegeWithStuCount.put("mfemaleexactbindNum",new Integer(0));
			}
				
			hasremove=false;
			for (int j = 0; j < dmaleexactbindList.size(); j++) {
				Map male = (Map) dmaleexactbindList
						.get(j);
				String majorinmale = (String)male.get("curCollege");
				if (majorinmale.equals(collegeWithStuCount.get("curCollege"))) {
					collegeWithStuCount.put("dmaleexactbindNum",male.get("dmaleexactbindNum"));
					dmaleexactbindList.remove(j);
					hasremove=true;
					break;
				}
			}
			if(!hasremove){
				collegeWithStuCount.put("dmaleexactbindNum",new Integer(0));
			}
			
			hasremove=false;
			for (int k = 0; k < dfemaleexactbindList.size(); k++) {
				Map female = (Map) dfemaleexactbindList
						.get(k);
				String majorinfemale = (String)female.get("curCollege");
				if (majorinfemale.equals(collegeWithStuCount.get("curCollege"))) {
					collegeWithStuCount.put("dfemaleexactbindNum",female.get("dfemaleexactbindNum"));
					dfemaleexactbindList.remove(k);
					hasremove=true;
					break;
				}

			}
			if(!hasremove){
				collegeWithStuCount.put("dfemaleexactbindNum",new Integer(0));
			}
			
			
			hasremove=false;
			for(int l=0;l<list_dorm.size();l++){
				Map dorm=(Map)list_dorm.get(l);
				String curCollege=(String)dorm.get("curCollege");
				if (curCollege.equals(collegeWithStuCount.get("curCollege"))) {
					collegeWithStuCount.put("colDormNum",dorm.get("colDormNum"));
					list_dorm.remove(l);
					hasremove=true;
					break;
				}
			}
			if(!hasremove){
				collegeWithStuCount.put("colDormNum",new Integer(0));
			}
			

			MMalesbtotal += ((Integer)collegeWithStuCount.get("mmaleshouldbindNum")).intValue();
			MFemalesbtotal += ((Integer)collegeWithStuCount.get("mfemaleshouldbindNum")).intValue();
			DMalesbtotal += ((Integer)collegeWithStuCount.get("dmaleshouldbindNum")).intValue();
			DFemalesbtotal += ((Integer)collegeWithStuCount.get("dfemaleshouldbindNum")).intValue();
			stuallSum += ((Integer)collegeWithStuCount.get("colStuNum")).intValue();
			
			
			MMaleexbtotal += ((Integer)collegeWithStuCount.get("mmaleexactbindNum")).intValue();
			MFemaleexbtotal += ((Integer)collegeWithStuCount.get("mfemaleexactbindNum")).intValue();
			DMaleexbtotal += ((Integer)collegeWithStuCount.get("dmaleexactbindNum")).intValue();
			DFemaleexbtotal += ((Integer)collegeWithStuCount.get("dfemaleexactbindNum")).intValue();
			dormallSum += ((Integer)collegeWithStuCount.get("colDormNum")).intValue();
								
		}
				
		Map addstu = new HashMap();
		addstu.put("stuallSum",new Integer(stuallSum));
		addstu.put("dormallSum",new Integer(dormallSum));
		addstu.put("MMalesbtotal",new Integer(MMalesbtotal));
		addstu.put("MFemalesbtotal",new Integer(MFemalesbtotal));
		addstu.put("DMalesbtotal",new Integer(DMalesbtotal));
		addstu.put("DFemalesbtotal",new Integer(DFemalesbtotal));
						
		addstu.put("MMaleexbtotal",new Integer(MMaleexbtotal));
		addstu.put("MFemaleexbtotal",new Integer(MFemaleexbtotal));
		addstu.put("DMaleexbtotal",new Integer(DMaleexbtotal));
		addstu.put("DFemaleexbtotal",new Integer(DFemaleexbtotal));
		
		list_stu.add(addstu);
		
		return list_stu;
	}
	
	public List getDormListFromGraduateTableLimit(String stuemp_no) {
		List ret = null;
		List dormList=new ArrayList();
		ret = baseDAO
				.findEntity(" select new Map(a.area as area,a.location as location,a.dormitory as dormitory) from Dormitorymodel a,TabSsManager c,Dictionary d1,Dictionary d2 "
						+ "where a.curDormDept=c.tabSsDept.id and a.location=d1.id.dictValue and d1.id.dictNo=20 and a.dormitory=d2.id.dictValue and d2.id.dictNo=21 and a.distributeNum>0 "
						+ "and c.stuNo='"
						+ stuemp_no
						+ "' order by a.area,d1.dictSort,d2.dictSort");
		if (ret != null && ret.size() > 0) {
			Map dorm1=(Map)ret.get(0);
			dormList.add(dorm1);
			for(int i=1;i<ret.size();i++){
				
				Map dorm2=(Map)ret.get(i);
				if(dorm2.equals(dorm1))
					dorm1=dorm2;
				else{
					dormList.add(dorm2);
					dorm1=dorm2;
				}
			}
						
			ChangeAreaValue(dormList);
			ChangeLocationValue(dormList);
			ChangeDormitoryValue(dormList);
		}
		
		return dormList;
	}
	
	public List getDormStatbyDorm(String stuemp_no){
		
		List managerdeptList=baseDAO.findEntity("select a.tabSsDept.id from TabSsManager a where a.stuNo='"+stuemp_no+"' and a.inOffice=1 ");
		
	    String curDept="";
	        
	    if(managerdeptList!=null&&managerdeptList.size()>0)
	        curDept=(String)managerdeptList.get(0);
	    
	    //可绑和未绑
		List totaldorm =  baseDAO
        .findEntity("select new Map(a.area as area,a.location as location,a.dormitory as dormitory,sum(a.distributeNum) as totaltotalNum,sum(a.emptyNum) as lefttotalNum) "
				+ "from Dormitorymodel a,TabSsManager c "
				+ "where a.curDormDept=c.tabSsDept.id "
				+ "and c.stuNo='"
				+ stuemp_no
				+ "' group by a.dormitory,a.location,a.area ");
		
		List maledorm =  baseDAO
        .findEntity("select new Map(a.area as area,a.location as location,a.dormitory as dormitory,sum(a.distributeNum) as totalmaleNum,sum(a.emptyNum) as leftmaleNum) "
				+ "from Dormitorymodel a,TabSsManager c "
				+ "where a.curDormDept=c.tabSsDept.id "
				+ "and c.stuNo='"
				+ stuemp_no
				+ "' and a.gender='1' group by a.dormitory,a.location,a.area ");
		
		List femaledorm =  baseDAO
        .findEntity("select new Map(a.area as area,a.location as location,a.dormitory as dormitory,sum(a.distributeNum) as totalfemaleNum,sum(a.emptyNum) as leftfemaleNum) "
				+ "from Dormitorymodel a,TabSsManager c "
				+ "where a.curDormDept=c.tabSsDept.id "
				+ "and c.stuNo='"
				+ stuemp_no
				+ "' and a.gender='2' group by a.dormitory,a.location,a.area ");
		
		int totaltotaltotal=0;
		int totalmaletotal=0;
		int totalfemaletotal=0;
		
		int lefttotaltotal=0;
		int leftmaletotal=0;
		int leftfemaletotal=0;
				
		for (int i = 0; i < totaldorm.size(); i++) {
			Map collegeWithStuCount = (Map) totaldorm
					.get(i);
			
			boolean hasremove=false;
			
			hasremove=false;
			for (int j = 0; j < maledorm.size(); j++) {				
				Map male = (Map) maledorm
						.get(j);
				String area = (String)male.get("area");
				String location = (String)male.get("location");
				String dormitory = (String)male.get("dormitory");
				if (area.equals(collegeWithStuCount.get("area"))&&location.equals(collegeWithStuCount.get("location"))&&dormitory.equals(collegeWithStuCount.get("dormitory"))) {
					collegeWithStuCount.put("totalmaleNum",male.get("totalmaleNum"));
					collegeWithStuCount.put("leftmaleNum",male.get("leftmaleNum"));
					maledorm.remove(j);
					hasremove=true;
					break;
				}
			}
			if(!hasremove){
				collegeWithStuCount.put("totalmaleNum",new Integer(0));
				collegeWithStuCount.put("leftmaleNum",new Integer(0));
			}
			
			hasremove=false;
			for (int j = 0; j < femaledorm.size(); j++) {				
				Map female = (Map) femaledorm
						.get(j);
				String area = (String)female.get("area");
				String location = (String)female.get("location");
				String dormitory = (String)female.get("dormitory");
				if (area.equals(collegeWithStuCount.get("area"))&&location.equals(collegeWithStuCount.get("location"))&&dormitory.equals(collegeWithStuCount.get("dormitory"))) {
					collegeWithStuCount.put("totalfemaleNum",female.get("totalfemaleNum"));
					collegeWithStuCount.put("leftfemaleNum",female.get("leftfemaleNum"));
					femaledorm.remove(j);
					hasremove=true;
					break;
				}
			}
			if(!hasremove){
				collegeWithStuCount.put("totalfemaleNum",new Integer(0));
				collegeWithStuCount.put("leftfemaleNum",new Integer(0));
			}
		
			totaltotaltotal += ((Integer)collegeWithStuCount.get("totaltotalNum")).intValue();
			totalmaletotal += ((Integer)collegeWithStuCount.get("totalmaleNum")).intValue();
			totalfemaletotal += ((Integer)collegeWithStuCount.get("totalfemaleNum")).intValue();
			lefttotaltotal += ((Integer)collegeWithStuCount.get("lefttotalNum")).intValue();
			leftmaletotal+=((Integer)collegeWithStuCount.get("leftmaleNum")).intValue();
			leftfemaletotal+=((Integer)collegeWithStuCount.get("leftfemaleNum")).intValue();
		}			
		
		//已绑定
		List entitys =  baseDAO
        .findEntity("select new Map(a.area as area,a.location as location,a.dormitory as dormitory,sum(b.distributeNum) as distributeNum) "
				+ "from Dormitorymodel a,ClassDorm b,TabSsManager c "
				+ "where a.dormitoryId=b.dormId and a.curDormDept=c.tabSsDept.id "
				+ "and c.stuNo='"
				+ stuemp_no
				+ "' and b.curYear='"
				+ DateUtil.getNow("yyyy") + "' group by a.dormitory,a.location,a.area ");
				
		List mmaleList=baseDAO
        .findEntity("select new Map(a.area as area,a.location as location,a.dormitory as dormitory,sum(b.distributeNum) as mmaleNum) "
				+ "from Dormitorymodel a,ClassDorm b,TabSsManager c "
				+ "where a.dormitoryId=b.dormId and a.curDormDept=c.tabSsDept.id "
				+ "and c.stuNo='"
				+ stuemp_no
				+ "' and b.curYear='"
				+ DateUtil.getNow("yyyy") + "' and b.sex='1' and b.studentType='M' group by a.dormitory,a.location,a.area ");
		
		List mfemaleList=baseDAO
        .findEntity("select new Map(a.area as area,a.location as location,a.dormitory as dormitory,sum(b.distributeNum) as mfemaleNum) "
				+ "from Dormitorymodel a,ClassDorm b,TabSsManager c "
				+ "where a.dormitoryId=b.dormId and a.curDormDept=c.tabSsDept.id "
				+ "and c.stuNo='"
				+ stuemp_no
				+ "' and b.curYear='"
				+ DateUtil.getNow("yyyy") + "' and b.sex='2' and b.studentType='M' group by a.dormitory,a.location,a.area ");
		
		List dmaleList=baseDAO
        .findEntity("select new Map(a.area as area,a.location as location,a.dormitory as dormitory,sum(b.distributeNum) as dmaleNum) "
				+ "from Dormitorymodel a,ClassDorm b,TabSsManager c "
				+ "where a.dormitoryId=b.dormId and a.curDormDept=c.tabSsDept.id "
				+ "and c.stuNo='"
				+ stuemp_no
				+ "' and b.curYear='"
				+ DateUtil.getNow("yyyy") + "' and b.sex='1' and b.studentType='D' group by a.dormitory,a.location,a.area ");
		
		List dfemaleList=baseDAO
        .findEntity("select new Map(a.area as area,a.location as location,a.dormitory as dormitory,sum(b.distributeNum) as dfemaleNum) "
				+ "from Dormitorymodel a,ClassDorm b,TabSsManager c "
				+ "where a.dormitoryId=b.dormId and a.curDormDept=c.tabSsDept.id "
				+ "and c.stuNo='"
				+ stuemp_no
				+ "' and b.curYear='"
				+ DateUtil.getNow("yyyy") + "' and b.sex='2' and b.studentType='D' group by a.dormitory,a.location,a.area ");

		int mmaletotal=0;
		int mfemaletotal=0;
		int dmaletotal=0;
		int dfemaletotal=0;
		int dormtotal=0;
		
		for (int i = 0; i < entitys.size(); i++) {
			Map collegeWithStuCount = (Map) entitys
					.get(i);
			
			boolean hasremove=false;
			
			hasremove=false;
			for (int j = 0; j < mmaleList.size(); j++) {				
				Map male = (Map) mmaleList
						.get(j);
				String area = (String)male.get("area");
				String location = (String)male.get("location");
				String dormitory = (String)male.get("dormitory");
				if (area.equals(collegeWithStuCount.get("area"))&&location.equals(collegeWithStuCount.get("location"))&&dormitory.equals(collegeWithStuCount.get("dormitory"))) {
					collegeWithStuCount.put("mmaleNum",male.get("mmaleNum"));
					mmaleList.remove(j);
					hasremove=true;
					break;
				}
			}
			if(!hasremove){
				collegeWithStuCount.put("mmaleNum",new Integer(0));
			}
			
			hasremove=false;
			for (int j = 0; j < mfemaleList.size(); j++) {				
				Map female = (Map) mfemaleList
						.get(j);
				String area = (String)female.get("area");
				String location = (String)female.get("location");
				String dormitory = (String)female.get("dormitory");
				if (area.equals(collegeWithStuCount.get("area"))&&location.equals(collegeWithStuCount.get("location"))&&dormitory.equals(collegeWithStuCount.get("dormitory"))) {
					collegeWithStuCount.put("mfemaleNum",female.get("mfemaleNum"));
					mfemaleList.remove(j);
					hasremove=true;
					break;
				}
			}
			if(!hasremove){
				collegeWithStuCount.put("mfemaleNum",new Integer(0));
			}
			
			hasremove=false;
			for (int j = 0; j < dmaleList.size(); j++) {				
				Map male = (Map)dmaleList
						.get(j);
				String area = (String)male.get("area");
				String location = (String)male.get("location");
				String dormitory = (String)male.get("dormitory");
				if (area.equals(collegeWithStuCount.get("area"))&&location.equals(collegeWithStuCount.get("location"))&&dormitory.equals(collegeWithStuCount.get("dormitory"))) {
					collegeWithStuCount.put("dmaleNum",male.get("dmaleNum"));
					dmaleList.remove(j);
					hasremove=true;
					break;
				}
			}
			if(!hasremove){
				collegeWithStuCount.put("dmaleNum",new Integer(0));
			}
			
			hasremove=false;
			for (int j = 0; j < dfemaleList.size(); j++) {				
				Map female = (Map) dfemaleList
						.get(j);
				String area = (String)female.get("area");
				String location = (String)female.get("location");
				String dormitory = (String)female.get("dormitory");
				if (area.equals(collegeWithStuCount.get("area"))&&location.equals(collegeWithStuCount.get("location"))&&dormitory.equals(collegeWithStuCount.get("dormitory"))) {
					collegeWithStuCount.put("dfemaleNum",female.get("dfemaleNum"));
					dfemaleList.remove(j);
					hasremove=true;
					break;
				}
			}
			if(!hasremove){
				collegeWithStuCount.put("dfemaleNum",new Integer(0));
			}
			
			mmaletotal += ((Integer)collegeWithStuCount.get("mmaleNum")).intValue();
			mfemaletotal += ((Integer)collegeWithStuCount.get("mfemaleNum")).intValue();
			dmaletotal += ((Integer)collegeWithStuCount.get("dmaleNum")).intValue();
			dfemaletotal += ((Integer)collegeWithStuCount.get("dfemaleNum")).intValue();
			dormtotal+=((Integer)collegeWithStuCount.get("distributeNum")).intValue();
		}
		
		
						
		if (totaldorm != null && totaldorm.size() > 0) {
			
			for(int i=0;i<totaldorm.size();i++){
				Map collegeWithStuCount = (Map) totaldorm.get(i);
				
				boolean hasremove=false;
				
				if(entitys!=null&&entitys.size()>0){
					for (int j = 0; j < entitys.size(); j++) {				
						Map ent = (Map) entitys
								.get(j);
						String area = (String)ent.get("area");
						String location = (String)ent.get("location");
						String dormitory = (String)ent.get("dormitory");
						if (area.equals(collegeWithStuCount.get("area"))&&location.equals(collegeWithStuCount.get("location"))&&dormitory.equals(collegeWithStuCount.get("dormitory"))) {
							collegeWithStuCount.put("mmaleNum",ent.get("mmaleNum"));
							collegeWithStuCount.put("mfemaleNum",ent.get("mfemaleNum"));
							collegeWithStuCount.put("dmaleNum",ent.get("dmaleNum"));
							collegeWithStuCount.put("dfemaleNum",ent.get("dfemaleNum"));
							collegeWithStuCount.put("distributeNum",ent.get("distributeNum"));
							entitys.remove(j);
							hasremove=true;
							break;
						}
					}
				}
				if(!hasremove){
					collegeWithStuCount.put("mmaleNum",new Integer(0));
					collegeWithStuCount.put("mfemaleNum",new Integer(0));
					collegeWithStuCount.put("dmaleNum",new Integer(0));
					collegeWithStuCount.put("dfemaleNum",new Integer(0));
					collegeWithStuCount.put("distributeNum",new Integer(0));
				}
			}
									
			ChangeAreaValue(totaldorm);
			ChangeLocationValue(totaldorm);
			ChangeDormitoryValue(totaldorm);
		}		
		
		Map addstu = new HashMap();
		addstu.put("totaltotaltotal",new Integer(totaltotaltotal));
		addstu.put("totalmaletotal",new Integer(totalmaletotal));
		addstu.put("totalfemaletotal",new Integer(totalfemaletotal));
		addstu.put("lefttotaltotal",new Integer(lefttotaltotal));
		addstu.put("leftmaletotal",new Integer(leftmaletotal));
		addstu.put("leftfemaletotal",new Integer(leftfemaletotal));
		addstu.put("dormtotal",new Integer(dormtotal));
		addstu.put("mmaletotal",new Integer(mmaletotal));
		addstu.put("mfemaletotal",new Integer(mfemaletotal));
		addstu.put("dmaletotal",new Integer(dmaletotal));
		addstu.put("dfemaletotal",new Integer(dfemaletotal));
		
		totaldorm.add(addstu);

       return totaldorm;
	}
	
	public List getAreaList() {
		List dictList = baseDAO
				.findEntity("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=17 order by di.id.dictValue");
		return dictList;
	}

	public List getLocationList() {
		List dictList = baseDAO
				.findEntity("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=20 order by di.id.dictValue");
		return dictList;
	}

	public List getDormitoryList() {
		List dictList = baseDAO
				.findEntity("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=21 order by di.id.dictValue");
		return dictList;
	}
	
	public void ChangeAreaValue(List list) {
		List dictList = getAreaList();
		for (int j = 0; j < list.size(); j++) {
			Map n = (Map) list.get(j);
			if (n.get("area") != null) {
				String mj = ((String) n.get("area")).trim();
				for (int k = 0; k < dictList.size(); k++) {
					Map n1 = (Map) dictList.get(k);
					String mj1 = ((String) n1.get("dictValue")).trim();
					if (mj.equals(mj1)) {
						n.put("areaName", ((String) n1.get("dictCaption"))
								.trim());
					}
				}
			} else
				n.put("areaName", "");
		}

	}

	public void ChangeLocationValue(List list) {
		List dictList = getLocationList();
		for (int j = 0; j < list.size(); j++) {
			Map n = (Map) list.get(j);
			if (n.get("location") != null) {
				String mj = ((String) n.get("location")).trim();
				for (int k = 0; k < dictList.size(); k++) {
					Map n1 = (Map) dictList.get(k);
					String mj1 = ((String) n1.get("dictValue")).trim();
					if (mj.equals(mj1)) {
						n.put("locationName", ((String) n1.get("dictCaption"))
								.trim());
					}
				}
			} else
				n.put("locationName", "");
		}

	}

	public void ChangeDormitoryValue(List list) {
		List dictList = getDormitoryList();
		for (int j = 0; j < list.size(); j++) {
			Map n = (Map) list.get(j);
			if (n.get("dormitory") != null) {
				String mj = ((String) n.get("dormitory")).trim();
				for (int k = 0; k < dictList.size(); k++) {
					Map n1 = (Map) dictList.get(k);
					String mj1 = ((String) n1.get("dictValue")).trim();
					if (mj.equals(mj1)) {
						n.put("dormitoryName", ((String) n1.get("dictCaption"))
								.trim());
					}
				}
			} else
				n.put("dormitoryName", "");
		}

	}

	public List findGraduateByGT(String gt) {
		String hqlStr = "selsct a from YxGraduate a where a.graduateType='"+gt+"'";
		List li = baseDAO.findEntity(hqlStr);
		return li;
	}
}
