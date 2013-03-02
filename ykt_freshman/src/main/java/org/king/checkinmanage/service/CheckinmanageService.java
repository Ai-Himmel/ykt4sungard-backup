/**
 * 
 */
package org.king.checkinmanage.service;

import java.util.List;

import org.king.checkinmanage.dao.StuCardfeeInfoDAO;
import org.king.checkinmanage.domain.CheckinSubmin;
import org.king.checkinmanage.domain.Noticemodel;
import org.king.checkinmanage.domain.StuCardfeeInfo;
import org.king.checkinmanage.domain.StuCardfeeSubmit;
import org.king.checkinmanage.domain.StuFeeInfo;
import org.king.checkinmanage.domain.Stuarchivesinfo;
import org.king.checkinmanage.domain.Stucheckininfo;
import org.king.checkinmanage.domain.Stuhealthinfo;
import org.king.framework.service.Service;

/**
 * @author jackey
 *
 */
public interface CheckinmanageService extends Service {

	public void update(Stucheckininfo stucheckininfo);
	
	public void update(Stuarchivesinfo stuarchivesinfo);
	
	public List find(String query);	
	
	public void save(Stuhealthinfo stuhealthinfo);
	
	public void update(Stuhealthinfo stuhealthinfo);
	
	public void delete(Stuhealthinfo stuhealthinfo);
	
	public void save(CheckinSubmin checkinsubmin);
	
	public void save(Stucheckininfo stucheckininfo);
	
	public void save(Stuarchivesinfo stuarchivesinfo);
	
	public void update(CheckinSubmin checkinsubmin);
	
	public void save(Noticemodel notice);
	
	public void update(Noticemodel notice);
	
	public void delete(Noticemodel notice);
	
	public Noticemodel findbyId(String id);
	
	public void save(StuFeeInfo stufeeinfo);
	
	public void update(StuFeeInfo stufeeinfo);
	
	public void delete(StuFeeInfo stufeeinfo);
	
	public List getAllFee();
	
	public void update(StuCardfeeInfo stucardfeeinfo);
	
	public void save(StuCardfeeSubmit cardfeesubmit);
	
	public void update(StuCardfeeSubmit cardfeesubmit);
	
	//导入录取通知书号
	public String updateEnrollNo(String[][] twoNos,String stuNos,String isgz);
}
