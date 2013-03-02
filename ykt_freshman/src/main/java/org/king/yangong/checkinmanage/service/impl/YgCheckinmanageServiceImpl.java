/**
 * 
 */
package org.king.yangong.checkinmanage.service.impl;

import java.util.List;

import org.king.checkinmanage.dao.CheckinSubminDAO;
import org.king.checkinmanage.dao.NoticemodelDAO;
import org.king.checkinmanage.dao.StuCardfeeInfoDAO;
import org.king.checkinmanage.dao.StuCardfeeSubmitDAO;
import org.king.checkinmanage.dao.StuFeeInfoDAO;
import org.king.checkinmanage.dao.StuarchivesinfoDAO;
import org.king.checkinmanage.dao.StucheckininfoDAO;
import org.king.checkinmanage.dao.StuhealthinfoDAO;
import org.king.checkinmanage.dao.UploadfileDAO;
import org.king.checkinmanage.domain.CheckinSubmin;
import org.king.checkinmanage.domain.Noticemodel;
import org.king.checkinmanage.domain.StuCardfeeInfo;
import org.king.checkinmanage.domain.StuCardfeeSubmit;
import org.king.checkinmanage.domain.StuFeeInfo;
import org.king.checkinmanage.domain.Stuarchivesinfo;
import org.king.checkinmanage.domain.Stucheckininfo;
import org.king.checkinmanage.domain.Stuhealthinfo;
import org.king.yangong.checkinmanage.service.YgCheckinmanageService;
import org.king.framework.service.impl.BaseService;
import org.king.rcvmanage.domain.Stuarriveinfo;

/**
 * @author jackey
 *
 */
public class YgCheckinmanageServiceImpl extends BaseService implements YgCheckinmanageService{
	
    private StucheckininfoDAO stucheckininfoDAO;
    private StuarchivesinfoDAO stuarchivesinfoDAO;
    private StuhealthinfoDAO stuhealthinfoDAO;
    private NoticemodelDAO noticemodelDAO;
    private UploadfileDAO uploadfileDAO;
    private CheckinSubminDAO checkinsubminDAO;
    private StuFeeInfoDAO stufeeinfoDAO;
    private StuCardfeeSubmitDAO stucardfeesubmitDAO;
    private StuCardfeeInfoDAO stucardfeeinfoDAO;
    
	
	public void setStucheckininfoDAO(StucheckininfoDAO stucheckininfoDAO) {
		this.stucheckininfoDAO = stucheckininfoDAO;
	}
	
	public void setStuarchivesinfoDAO(StuarchivesinfoDAO stuarchivesinfoDAO) {
		this.stuarchivesinfoDAO = stuarchivesinfoDAO;
	}
	
	public void setStuhealthinfoDAO(StuhealthinfoDAO stuhealthinfoDAO) {
		this.stuhealthinfoDAO = stuhealthinfoDAO;
	}
	
	public void setNoticemodelDAO(NoticemodelDAO noticemodelDAO) {
		this.noticemodelDAO = noticemodelDAO;
	}
	public void setUploadfileDAO(UploadfileDAO uploadfileDAO) {
		this.uploadfileDAO = uploadfileDAO;
	}
	public void setCheckinSubminDAO(CheckinSubminDAO checkinsubminDAO) {
		this.checkinsubminDAO = checkinsubminDAO;
	}
	public void setStuFeeInfoDAO(StuFeeInfoDAO stufeeinfoDAO) {
		this.stufeeinfoDAO = stufeeinfoDAO;
	}
	public void setStuCardfeeSubmitDAO(StuCardfeeSubmitDAO stucardfeesubmitDAO) {
		this.stucardfeesubmitDAO = stucardfeesubmitDAO;
	}
	public void setStuCardfeeInfoDAO(StuCardfeeInfoDAO stucardfeeinfoDAO) {
		this.stucardfeeinfoDAO = stucardfeeinfoDAO;
	}
	
	public void update(Stucheckininfo stucheckininfo){
		try{
			//System.out.println("serviceimpl");
			stucheckininfoDAO.update(stucheckininfo);
			//System.out.println("update ok");
		}catch(Exception e){
			e.printStackTrace();
			System.out.println("serviceimpl update error");
		}
	}
	
	public void update(Stuarchivesinfo stuarchivesinfo){
		try{
			//System.out.println("serviceimpl");
			stuarchivesinfoDAO.update(stuarchivesinfo);
			//System.out.println("update ok");
		}catch(Exception e){
			e.printStackTrace();
			System.out.println("serviceimpl update error");
		}
	}
	
	public void update(StuCardfeeInfo stucardfeeinfo){
		try{
			//System.out.println("serviceimpl");
			stucardfeeinfoDAO.update(stucardfeeinfo);
			//System.out.println("update ok");
		}catch(Exception e){
			e.printStackTrace();
			System.out.println("serviceimpl update error");
		}
	}
	
	public void save(StuCardfeeSubmit cardfeesubmit){
		try{
			//System.out.println("serviceimpl");
			stucardfeesubmitDAO.save(cardfeesubmit);
			//System.out.println("update ok");
		}catch(Exception e){
			e.printStackTrace();
			System.out.println("serviceimpl update error");
		}
	}
	
	public void update(StuCardfeeSubmit cardfeesubmit){
		try{
			//System.out.println("serviceimpl");
			stucardfeesubmitDAO.update(cardfeesubmit);
			//System.out.println("update ok");
		}catch(Exception e){
			e.printStackTrace();
			System.out.println("serviceimpl update error");
		}
	}
	
	public void update(Noticemodel notice){
		try{
			//System.out.println("serviceimpl");
			noticemodelDAO.update(notice);
			//System.out.println("update ok");
		}catch(Exception e){
			e.printStackTrace();
			System.out.println("serviceimpl update error");
		}
	}
	
	public void save(Stuhealthinfo stuhealthinfo){
		try{
			//System.out.println("serviceimpl");
			stuhealthinfoDAO.save(stuhealthinfo);
			//System.out.println("health update ok");
		}catch(Exception e){
			e.printStackTrace();
			System.out.println("health serviceimpl save error");
		}
	}
	
	public void update(Stuhealthinfo stuhealthinfo){
		try{
			//System.out.println("serviceimpl");
			stuhealthinfoDAO.update(stuhealthinfo);
			//System.out.println("health update ok");
		}catch(Exception e){
			e.printStackTrace();
			System.out.println("health serviceimpl update error");
		}
	}
	
	public void save(CheckinSubmin checkinsubmin){
		try{
			//System.out.println("serviceimpl");
			checkinsubminDAO.save(checkinsubmin);
			//System.out.println("checkinsubmin save ok");
		}catch(Exception e){
			e.printStackTrace();
			System.out.println("checkinsubmin serviceimpl save error");
		}
	}
	
	public void save(Stucheckininfo stucheckininfo){
		try{
			//System.out.println("serviceimpl");
			stucheckininfoDAO.save(stucheckininfo);
			//System.out.println("checkinsubmin save ok");
		}catch(Exception e){
			e.printStackTrace();
			System.out.println("checkinsubmin serviceimpl save error");
		}
	}
	
	public void save(Stuarchivesinfo stuarchivesinfo){
		try{
			//System.out.println("serviceimpl");
			stuarchivesinfoDAO.save(stuarchivesinfo);
			//System.out.println("checkinsubmin save ok");
		}catch(Exception e){
			e.printStackTrace();
			System.out.println("checkinsubmin serviceimpl save error");
		}
	}
	
	public void save(StuCardfeeInfo stuCardfeeInfo){
		try{
			//System.out.println("serviceimpl");
			stucardfeeinfoDAO.save(stuCardfeeInfo);
			//System.out.println("checkinsubmin save ok");
		}catch(Exception e){
			e.printStackTrace();
			System.out.println("checkinsubmin serviceimpl save error");
		}
	}
	
	public void save(Noticemodel notice){
		try{
			//System.out.println("serviceimpl");
			noticemodelDAO.save(notice);
			//System.out.println("notice save ok");
		}catch(Exception e){
			e.printStackTrace();
			System.out.println("notice serviceimpl save error");
		}
	}
	
	public void save(StuFeeInfo stufeeinfo){
		try{
			//System.out.println("serviceimpl");
			stufeeinfoDAO.save(stufeeinfo);
			//System.out.println("stufeeinfo save ok");
		}catch(Exception e){
			e.printStackTrace();
			System.out.println("stufeeinfo serviceimpl save error");
		}
	}
	
	public void update(StuFeeInfo stufeeinfo){
		try{
			//System.out.println("serviceimpl");
			stufeeinfoDAO.update(stufeeinfo);
			//System.out.println("stufeeinfo update ok");
		}catch(Exception e){
			e.printStackTrace();
			System.out.println("stufeeinfo serviceimpl update error");
		}
	}
	
	public void update(CheckinSubmin checkinsubmin){
		try{
			//System.out.println("serviceimpl");
			checkinsubminDAO.update(checkinsubmin);
			//System.out.println("checkinsubmin update ok");
		}catch(Exception e){
			e.printStackTrace();
			System.out.println("checkinsubmin serviceimpl update error");
		}
	}
	
	public void delete(Stuhealthinfo stuhealthinfo){
		try{
			//System.out.println("serviceimpl");
			stuhealthinfoDAO.delete(stuhealthinfo);
			//System.out.println("delete ok");
		}catch(Exception e){
			e.printStackTrace();
			System.out.println("serviceimpl delete error");
		}
	}
	
	public void delete(Noticemodel notice){
		try{
			//System.out.println("serviceimpl");
			noticemodelDAO.delete(notice);
			//System.out.println("delete ok");
		}catch(Exception e){
			e.printStackTrace();
			System.out.println("serviceimpl delete error");
		}
	}
	
	public void delete(StuFeeInfo stufeeinfo){
		try{
			//System.out.println("serviceimpl");
			stufeeinfoDAO.delete(stufeeinfo);
			//System.out.println("delete ok");
		}catch(Exception e){
			e.printStackTrace();
			System.out.println("serviceimpl delete error");
		}
	}
	
    public Noticemodel findbyId(String id){
    	
    	Noticemodel notice = null;
	    try{
	         notice = noticemodelDAO.findbyId(id);
	         return notice;
	    }catch(Exception e){
			e.printStackTrace();
			System.out.println("find by id error");
		}
		if(notice==null)
			System.out.println("notice is null");
		return notice;
   }
	
	//自己的方法
	public List find(String query){
		List result=null;
		try{
			result=stucheckininfoDAO.find(query);
			//System.out.println("find ok");
		}catch(Exception e){
			e.printStackTrace();
			System.out.println("find error");
		}
		if(result==null)
			System.out.println("findresult is null");
		return result;
	}
	
	public List getAllFee(){
		List result=null;
		try{
			result=stufeeinfoDAO.getAll();
			//System.out.println("get all ok");
		}catch(Exception e){
			e.printStackTrace();
			System.out.println("get all error");
		}
		if(result==null)
			System.out.println("findresult is null");
		return result;
	}

}
