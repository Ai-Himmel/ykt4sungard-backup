package org.king.business.service;

import java.util.List;
import java.util.Map;

import org.apache.poi.hssf.usermodel.HSSFSheet;
import org.king.business.domain.BmStudent;
import org.king.business.domain.BmStuBm;
import org.king.business.domain.BmTest;
import org.king.business.domain.StuTestUpdate;

public interface StudentService {

	public BmStudent getDetail(String id);
	public List getList(Map m);
	public List getList(Map m,String startpage);
	public Integer getStudentCount(Map m);
	public List getnewaddList(Map m);
		
	public String saveStuBmbyImport(HSSFSheet sheet,String testId,String userId) throws Exception;
	public String updateStuBmbyImport(HSSFSheet sheet,String testId,String userId) throws Exception;
	public String deleteStuBmbyImport(HSSFSheet sheet,String testId,String userId) throws Exception;
	
	public String updateStuGrades(HSSFSheet sheet,String testId,String userId) throws Exception;
		
	public boolean save(BmStudent bmStudent);
	public boolean update(BmStudent bmStudent);
	public boolean delete(BmStudent bmStudent);
	
	public String saveStuBm(BmStudent bmStudent,BmTest bmTest,String userId) throws Exception;
	
	public boolean check4Save(BmStudent bmStudent);
	public boolean check4Update(BmStudent bmStudent);
	
	public boolean check4UpdateStuBm(String id);
	
	public BmStuBm getStuBmDetail(String id);
	public List getStuBm4Update(String id);
		
	public String saveBm(BmStuBm bmStuBm);
	public boolean updateBm(BmStuBm bmStuBm);
	public boolean deleteBm(BmStuBm bmStuBm);	

	public boolean check4SaveBm(String stuNo,String testId,String stubmId);
	public String check4DeleteBm(String id);
	public String check4Bm(String id,String stuNo);
	public String check4NotBm(String id);
	public String check4NotBmDue(String id);
	
	public List getBMTongji();
	public List getBMTongjiTotal();
	
	public List getStuBmList(String stuNo,boolean ifBm);
	public boolean updateStuBm(BmStuBm bmStuBm);
		
	public List find(String sqlstring);
	public List getStuPhoto(String cutId);
	
	public List gethistoryList(Map m);
	public List gethistoryList(Map m,String startpage);
	public Integer gethistoryCount(Map m);
	public boolean deleteHistory(BmStuBm bmStuBm);	
	
	public List getPhotoList(Map m);
	
	public boolean isFee(String stuNo,String testId);
	
	public boolean save(StuTestUpdate  stuTestupdate);
	
	public  List  getfeeTestList(Map m,String startpage);
	
	public  Integer getfeeTestCount(Map m);
	
	public boolean updateBmStuBm(BmStuBm bmStuBm);
		
}
