/**
 * 
 */
package org.king.checkinmanage.service.impl;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

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
import org.king.checkinmanage.service.CheckinmanageService;
import org.king.classmanage.dao.StudentmodelDAO;
import org.king.classmanage.domain.Classmodel;
import org.king.classmanage.domain.Studentmodel;
import org.king.framework.exception.BusinessException;
import org.king.framework.service.impl.BaseService;
import org.king.framework.util.MyUtils;
import org.king.rcvmanage.domain.Stuarriveinfo;
import org.king.security.dao.AccountDAO;
import org.king.security.dao.RoleDAO;
import org.king.security.domain.Account;
import org.king.security.domain.Person;
import org.king.security.domain.Role;
import org.king.utils.DateUtil;

/**
 * @author jackey
 *
 */
public class CheckinmanageServiceImpl extends BaseService implements CheckinmanageService{
	
    private StucheckininfoDAO stucheckininfoDAO;
    private StuarchivesinfoDAO stuarchivesinfoDAO;
    private StuhealthinfoDAO stuhealthinfoDAO;
    private NoticemodelDAO noticemodelDAO;
    private UploadfileDAO uploadfileDAO;
    private CheckinSubminDAO checkinsubminDAO;
    private StuFeeInfoDAO stufeeinfoDAO;
    private StuCardfeeSubmitDAO stucardfeesubmitDAO;
    private StuCardfeeInfoDAO stucardfeeinfoDAO;
    private StudentmodelDAO studentmodelDAO;
	
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
	public void setStudentmodelDAO(StudentmodelDAO studentmodelDAO) {
		this.studentmodelDAO = studentmodelDAO;
	}
	
    private AccountDAO accountDAO;	
	public void setAccountDAO(AccountDAO accountDAO) {
		this.accountDAO = accountDAO;
	}
	
	private RoleDAO roleDAO;	
	public void setRoleDAO(RoleDAO roleDAO) {
		this.roleDAO = roleDAO;
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
	
    //导入录取通知书号
	public String updateEnrollNo(String[][] twoNos,String stuNos,String isgz){
		String notfindstu="";
		
		List studentList=find(" select a from Studentmodel a where a.studentNo in ("+stuNos+")");
		
		if(studentList!=null&&studentList.size()>0){
			String[][] eNos=new String[studentList.size()][5];
			String eNostring="";
			for(int j=0;j<studentList.size();j++){
				Studentmodel stu=(Studentmodel)studentList.get(j);
				boolean hasfind=false;
				
				for(int k=0;k<twoNos.length;k++){
					if(twoNos[k][0].equals(stu.getStudentNo())){
						stu.setEnterenceNo(twoNos[k][1]);
						
						if((isgz!=null&&isgz.equals("1"))||(stu.getMajorin()!=null&&stu.getMajorin().trim().equals("623"))){						    
							eNos[j][4]="1";
							List gzstuclass=find(" select c from GzStuTemp s,Classmodel c where s.classId=c.classId and s.enterenceNo='"+twoNos[k][1]+"' ");
							if(gzstuclass!=null&&gzstuclass.size()>0){
							    stu.setYxClass((Classmodel)gzstuclass.get(0));//更新高职生班号	
							}						    
						}
						else
							eNos[j][4]="0";
						
						studentmodelDAO.update(stu);
						
						List checkinli=find(" select a from Stucheckininfo a where a.studentNo='"+stu.getStudentNo()+"'");
						if(checkinli!=null&&checkinli.size()>0){
							Stucheckininfo sck=(Stucheckininfo)checkinli.get(0);
							sck.setEnrollNo(twoNos[k][1]);
							stucheckininfoDAO.update(sck);
						}
						List archiveli=find(" select a from Stuarchivesinfo a where a.studentNo='"+stu.getStudentNo()+"'");
						if(archiveli!=null&&archiveli.size()>0){
							Stuarchivesinfo sak=(Stuarchivesinfo)archiveli.get(0);
							sak.setEnrollNo(twoNos[k][1]);
							stuarchivesinfoDAO.update(sak);
						}
						List healthli=find(" select a from Stuhealthinfo a where a.studentNo='"+stu.getStudentNo()+"'");
						if(healthli!=null&&healthli.size()>0){
							Stuhealthinfo shk=(Stuhealthinfo)healthli.get(0);
							shk.setEnrollNo(twoNos[k][1]);
							stuhealthinfoDAO.update(shk);
						}						
						
						hasfind=true;
						
						eNos[j][0]=twoNos[k][1];//录取通知书号
						eNos[j][1]="666666";//本地登录密码默认为666666
						eNos[j][2]=stu.getStudentNo();//学号
						eNos[j][3]=stu.getStuName();//姓名
						
						String idcardno="";
						if(stu.getIdCard()!=null)
							idcardno=stu.getIdCard().trim();
						if(idcardno!=null&&idcardno.length()>0){//构造身份证后6位本地密码明文
							if(idcardno.length()>5)
								eNos[j][1]=idcardno.substring(idcardno.length()-6,idcardno.length());
							else
								eNos[j][1]=idcardno;
							
							char[] tempeNo=new char[eNos[j][1].length()];
							for(int l=0;l<eNos[j][1].length();l++){
								char curchar=eNos[j][1].charAt(l);
								if(curchar<'0'||curchar>'9'){
									curchar='0';
								}
								tempeNo[l]=curchar;
							}
							eNos[j][1]=new String(tempeNo);
						}
						
						eNos[j][1]=MyUtils.toMD5(eNos[j][1]);//加密
						
						eNostring=eNostring+"'"+eNos[j][0]+"'"+",";
						
						break;
					}
				}
				if(!hasfind){
					notfindstu=notfindstu+stu.getStudentNo()+",";
					eNos[j][0]="";
					eNos[j][1]="";
					eNos[j][2]="";
					eNos[j][3]="";
					eNos[j][4]="";
				}
			}
			
			if(eNostring.length()>0){
				eNostring=eNostring.substring(0,eNostring.length()-1);
			}
			
			if(eNostring.length()>0){
				List accountList=find("select a.name from Account a where a.name in ("+eNostring+")");
				String hasin="";
				if(accountList!=null&&accountList.size()>0){
					for(int i=0;i<accountList.size();i++){
						hasin=hasin+(String)accountList.get(i)+",";
					}
				}
				String bkrole=getRoleidByName("新生");
				String gzrole=getRoleidByName("护理学院新生");
				for(int i=0;i<eNos.length;i++){
					if(eNos[i][0].length()>0&&hasin.indexOf(eNos[i][0])==-1){//当前无此记录
						Person psn=new Person();						
						psn.setPersonCode(eNos[i][2]);
						psn.setPersonName(eNos[i][3]);
						psn.setPersonType("1");
						psn.setCreatedate(DateUtil.getNow().substring(0,8));
						psn.setLastdate(DateUtil.getNow().substring(0,8));
						
						Account act=new Account();
						act.setPerson(psn);
						act.setName(eNos[i][0]);
						act.setPassword(eNos[i][1]);
						
						accountDAO.save(act);
						
                        //加新生角色权限
						List roleList = new ArrayList();
						String roleid =null;
						if(eNos[i][4].equals("1"))
							roleid=gzrole;
						else
							roleid=bkrole;
						if(roleid!=null&&roleid.length()>0)
							roleList.add(roleid);						
						String[] roleArr =  new String[roleList.size()];
						if(roleList!=null&&roleList.size()>0){
						  roleList.toArray(roleArr);
						  try{
							grantAccountRoles(act.getId(),roleArr);
						  }catch(Exception e){
							e.printStackTrace();
						  }
						}
					}
					else if(eNos[i][0].length()>0){
						Account act=accountDAO.findAccountByName(eNos[i][0]);
						act.getPerson().setPersonCode(eNos[i][2]);
						act.getPerson().setPersonName(eNos[i][3]);
						act.setPassword(eNos[i][1]);
						accountDAO.update(act);
						
                        //更新新生角色权限
						List roleList = new ArrayList();
						String roleid =null;
						if(eNos[i][4].equals("1"))
							roleid=gzrole;
						else
							roleid=bkrole;
						if(roleid!=null&&roleid.length()>0)
							roleList.add(roleid);						
						String[] roleArr =  new String[roleList.size()];
						if(roleList!=null&&roleList.size()>0){
						  roleList.toArray(roleArr);
						  try{
							grantAccountRoles(act.getId(),roleArr);
						  }catch(Exception e){
							e.printStackTrace();
						  }
						}
					}
				}
			}
			
			
		}
		
		if(studentList!=null&&studentList.size()>0){
			for(int i=0;i<twoNos.length;i++){
				int j=0;				
				for(j=0;j<studentList.size();j++){
					Studentmodel stu=(Studentmodel)studentList.get(j);
					if(twoNos[i][0].equals(stu.getStudentNo()))
						break;
				}
				if(j>studentList.size()-1&&twoNos[i][0].length()>0){
					notfindstu=notfindstu+twoNos[i][0]+",";
				}
			}
		}
		
		if(notfindstu.length()>0)
			notfindstu=notfindstu.substring(0,notfindstu.length()-1);
		
		return notfindstu;
	}
	
	public String getRoleidByName(String roleName) {
		String roleId = "";
		List list = find("select a.id from Role a where a.name='" + roleName
						+ "'");
		if (list.size() > 0) {
			roleId = list.get(0).toString();
		}
		return roleId;
	}
	
	public void grantAccountRoles(String accountId, String[] currentRole) throws BusinessException {
		Account account = accountDAO.get(accountId);
		Set currentAccountRole = new HashSet();
		if(currentRole!=null) {
			for(int i=0;i<currentRole.length;i++){
				currentAccountRole.add((Role)roleDAO.get(currentRole[i]));
			}
		}
		account.setRoles(currentAccountRole);
		accountDAO.update(account);
	}
}
