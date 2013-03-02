/* ============================================================
 * 版权：    king 版权所有 (c) 2007
 * 文件：    QuartersServiceImpl.java
 * 创建日期： 2007-6-8 下午04:28:45
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 *  2007-6-8 下午04:28:45     王胜        创建文件，实现基本功能
 * ============================================================
 */
package org.king.quarters.service.impl;

import java.io.File;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import jxl.Cell;
import jxl.NumberCell;
import jxl.Sheet;
import jxl.Workbook;

import org.apache.commons.beanutils.BeanUtils;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;
import org.king.common.dao.AllDAO;
import org.king.common.service.IDirectoryService;
import org.king.dormitorymanage.domain.Dormitorymodel;
import org.king.quarters.domain.TabSsDept;
import org.king.quarters.service.IQuartersService;
import org.king.quarters.service.QuartersModel;
import org.king.security.domain.Account;
import org.springframework.orm.hibernate3.HibernateCallback;

public class QuartersServiceImpl implements IQuartersService {

	/* (non-Javadoc)
	 * @see org.king.quarters.service.IQuartersService#addOrUpdateQuarters(org.king.dormitorymanage.domain.Dormitorymodel)
	 */
	private AllDAO allDAO;
	private IDirectoryService directoryService;
	public void setAllDAO(AllDAO allDAO) {
		this.allDAO = allDAO;
	}

	public boolean addOrUpdateQuarters(Dormitorymodel quarters) {
		// TODO Auto-generated method stub
		if (quarters == null) return false;
		if(quarters.getCurDormDept() != null && quarters.getCurDormDept().trim().equals("")){
			quarters.setCurDormDept("");
		}
		if (quarters.getDistributeNum() <=0){
			quarters.setIfDistribute("0");
		}
		else {
			quarters.setIfDistribute("1");
		}
		quarters.setEmptyNum(quarters.getDistributeNum());
		//
		if (quarters.getDormitoryId() != null && !quarters.getDormitoryId().trim().equals("")){
			
			Dormitorymodel tempD = (Dormitorymodel)allDAO.getHibernateTemplate().load(Dormitorymodel.class,quarters.getDormitoryId().trim());
			try{
			String classId = tempD.getClassId();	
			BeanUtils.copyProperties(tempD,quarters);
			tempD.setClassId(classId);
			}catch(Throwable e){
				//nothing
			}
			allDAO.getHibernateTemplate().save(tempD);
		}
		else{
			allDAO.getHibernateTemplate().save(quarters);
		}
	
		List l = this.getExsitDormitorymodel(quarters);
		if (l != null && l.size() >1){
			throw new RuntimeException("该房间已经存在！");
		}
		return true;
	}

	/* (non-Javadoc)
	 * @see org.king.quarters.service.IQuartersService#getQuarters(java.lang.String)
	 */
	public Dormitorymodel getQuarters(String quartersId) {
		if (quartersId == null || quartersId.trim().equals("")) return null;
		Dormitorymodel m =(Dormitorymodel)allDAO.getHibernateTemplate().get(Dormitorymodel.class, quartersId);
		String deptId = m.getCurDormDept();
		if (deptId != null && ! deptId.trim().equals(""))  {
			TabSsDept dept = (TabSsDept)allDAO.getHibernateTemplate().get(TabSsDept.class, deptId);
			m.setMemo1(dept.getName());
		}
		return m;
	}

	/* (non-Javadoc)
	 * @see org.king.quarters.service.IQuartersService#getQuartersList(java.util.List, int, int, org.king.dormitorymanage.domain.Dormitorymodel)
	 */
	public int getQuartersList(String userId,List res, final int pageNo, final int pageSize,
			final QuartersModel conditions) {
		
		 final TabSsDept dept = this.getManageDept(userId);
			
	
		Object[] os = (Object[])allDAO.getHibernateTemplate().execute(new HibernateCallback(){
			public Object doInHibernate(Session session) throws HibernateException, SQLException {
				
				Map p = new HashMap();
				StringBuffer sb = new StringBuffer(" from Dormitorymodel d,Dictionary d2 where 1=1 and d.dormitory=d2.id.dictValue and d2.id.dictNo=21 ");
				if (dept != null && dept.getId() != null) {
					sb.append(" and (d.curDormDept=:deptId or d.curDormDept is null or d.curDormDept='' )");
					p.put("deptId",dept.getId());
				}
				if (conditions != null) {
					String temp = null;
					temp = conditions.getLocation();
					if (temp != null && !temp.trim().equals("")){
						sb.append(" and d.location=:location");
						p.put("location",temp);
					}
					temp = conditions.getArea();
					if (temp != null && !temp.trim().equals("")){
						sb.append(" and d.area=:area");
						p.put("area",temp);
					}
					temp = conditions.getLevel();
					if (temp != null && !temp.trim().equals("")){
						sb.append(" and d.level=:level");
						p.put("level",temp);
					}
					temp = conditions.getUnit();
					if (temp != null && !temp.trim().equals("")){
						sb.append(" and d.unit like :unit");
						p.put("unit","%"+temp+"%");
					}
					temp = conditions.getDormitory();
					if (temp != null && !temp.trim().equals("")){
						sb.append(" and d.dormitory =:dormitory");
						p.put("dormitory",temp);
					}
					temp = conditions.getDirection();
					if (temp != null && !temp.trim().equals("")){
						sb.append(" and d.direction =:direction");
						p.put("direction",temp);
					}
					temp = conditions.getGender();
					if (temp != null && !temp.trim().equals("")){
						sb.append(" and d.gender =:gender");
						p.put("gender",temp);
					}
					temp = conditions.getRoomNumber();
					if (temp != null && !temp.trim().equals("")){
						sb.append(" and d.roomNumber like:roomNumber");
						p.put("roomNumber","%"+temp+"%");
					}
					temp = conditions.getTelphone();
					if (temp != null && !temp.trim().equals("")){
						sb.append(" and d.telphone like :telphone");
						p.put("telphone","%"+temp+"%");
					}
					Double t2 = conditions.getFee();
					if (t2 != null && t2.intValue() != 0){
						sb.append(" and d.fee like :fee");
						p.put("fee","%"+t2+"%");
					}
					
				}
			    
				Query q = session.createQuery(" select d "+ sb.toString()+" order by d.area,d.location,d2.dictSort,d.level,d.unit,d.roomNumber");
				//
			    Iterator it = p.entrySet().iterator();
			    while (it.hasNext()){
					Map.Entry  e =(Map.Entry)it.next();
					Object key  = e.getKey();
					Object value = e.getValue();
				    q.setParameter(""+key,value);
						
				}
				q.setFirstResult((pageNo-1)*pageSize);
				q.setMaxResults(pageSize);
				List temp1  =  q.list();
				List temp = new ArrayList();
				if (temp1 != null){
					Dormitorymodel newDm = null;
					for (int i = 0; i <temp1.size(); i++){
						Dormitorymodel dm =(Dormitorymodel) temp1.get(i);
						newDm = new Dormitorymodel();
						try{
						 BeanUtils.copyProperties(newDm,dm);
						 //
						 String area = newDm.getArea();
						 if (area != null && !area.trim().equals("")){
							 newDm.setArea(directoryService.getAreaName(area.trim()));
						 }
						 //
						 String location = newDm.getLocation();
						 if (location != null && !location.trim().equals("")){
							 newDm.setLocation(directoryService.getLocationName(location.trim()));
						 }
						 //
						 String dormitory = newDm.getDormitory();
						 if (dormitory != null && !dormitory.trim().equals("")){
							 newDm.setDormitory(directoryService.getDormitoryName(dormitory.trim()));
						 }
						 //
						 String level = newDm.getLevel();
						 if (level != null && !level.trim().equals("")){
							 newDm.setLevel(directoryService.getLevelName(level.trim()));
						 }
						 //
						 String direction = newDm.getDirection();
						 if (direction != null && !direction.trim().equals("")){
							 newDm.setDirection(directoryService.getDirectionName(direction.trim()));
						 }
						 //
						 //
						 String sex = newDm.getGender();
						 if (sex != null && !sex.trim().equals("")){
							 newDm.setGender(directoryService.getSexName(sex.trim()));
						 }
						 temp.add(newDm);
						}catch(Throwable e){
							e.printStackTrace();
							continue;
						}
					}
				}
				//获取总记录数
				q = session.createQuery(" select count(*) " + sb.toString()); 
				//
				it = p.entrySet().iterator();
			    while (it.hasNext()){
					Map.Entry  e =(Map.Entry)it.next();
					Object key  = e.getKey();
					Object value = e.getValue();
					q.setParameter(""+key,value);
					
				}
				Number num = (Number)q.uniqueResult();
				//count = num.intValue();
				Object[] os = new Object[2];
				os[0] = temp;
				os[1] = num;
				return os;
			}
			
		});
		List t = (List)os[0];
		res.addAll(t);
		Number num = (Number)os[1];
		return num.intValue();
	}
	
	public int getQuartersListAll(String userId,List res,
			final QuartersModel conditions) {
		
		 final TabSsDept dept = this.getManageDept(userId);
			
	
		Object[] os = (Object[])allDAO.getHibernateTemplate().execute(new HibernateCallback(){
			public Object doInHibernate(Session session) throws HibernateException, SQLException {
				
				Map p = new HashMap();
				StringBuffer sb = new StringBuffer(" from Dormitorymodel d,Dictionary d2 where 1=1 and d.dormitory=d2.id.dictValue and d2.id.dictNo=21 ");
				if (dept != null && dept.getId() != null) {
					sb.append(" and (d.curDormDept=:deptId or d.curDormDept is null or d.curDormDept='' )");
					p.put("deptId",dept.getId());
				}
				if (conditions != null) {
					String temp = null;
					temp = conditions.getLocation();
					if (temp != null && !temp.trim().equals("")){
						sb.append(" and d.location=:location");
						p.put("location",temp);
					}
					temp = conditions.getArea();
					if (temp != null && !temp.trim().equals("")){
						sb.append(" and d.area=:area");
						p.put("area",temp);
					}
					temp = conditions.getLevel();
					if (temp != null && !temp.trim().equals("")){
						sb.append(" and d.level=:level");
						p.put("level",temp);
					}
					temp = conditions.getUnit();
					if (temp != null && !temp.trim().equals("")){
						sb.append(" and d.unit like :unit");
						p.put("unit","%"+temp+"%");
					}
					temp = conditions.getDormitory();
					if (temp != null && !temp.trim().equals("")){
						sb.append(" and d.dormitory =:dormitory");
						p.put("dormitory",temp);
					}
					temp = conditions.getDirection();
					if (temp != null && !temp.trim().equals("")){
						sb.append(" and d.direction =:direction");
						p.put("direction",temp);
					}
					temp = conditions.getGender();
					if (temp != null && !temp.trim().equals("")){
						sb.append(" and d.gender =:gender");
						p.put("gender",temp);
					}
					temp = conditions.getRoomNumber();
					if (temp != null && !temp.trim().equals("")){
						sb.append(" and d.roomNumber like:roomNumber");
						p.put("roomNumber","%"+temp+"%");
					}
					temp = conditions.getTelphone();
					if (temp != null && !temp.trim().equals("")){
						sb.append(" and d.telphone like :telphone");
						p.put("telphone","%"+temp+"%");
					}
					Double t2 = conditions.getFee();
					if (t2 != null && t2.intValue() != 0){
						sb.append(" and d.fee like :fee");
						p.put("fee","%"+t2+"%");
					}
					
				}
			    
				Query q = session.createQuery(" select d "+ sb.toString()+" order by d.area,d.location,d2.dictSort,d.level,d.unit,d.roomNumber");
				//
			    Iterator it = p.entrySet().iterator();
			    while (it.hasNext()){
					Map.Entry  e =(Map.Entry)it.next();
					Object key  = e.getKey();
					Object value = e.getValue();
				    q.setParameter(""+key,value);
						
				}
				
				List temp1  =  q.list();
				List temp = new ArrayList();
				if (temp1 != null){
					Dormitorymodel newDm = null;
					for (int i = 0; i <temp1.size(); i++){
						Dormitorymodel dm =(Dormitorymodel) temp1.get(i);
						newDm = new Dormitorymodel();
						try{
						 BeanUtils.copyProperties(newDm,dm);
						 //
						 String area = newDm.getArea();
						 if (area != null && !area.trim().equals("")){
							 newDm.setArea(directoryService.getAreaName(area.trim()));
						 }
						 //
						 String location = newDm.getLocation();
						 if (location != null && !location.trim().equals("")){
							 newDm.setLocation(directoryService.getLocationName(location.trim()));
						 }
						 //
						 String dormitory = newDm.getDormitory();
						 if (dormitory != null && !dormitory.trim().equals("")){
							 newDm.setDormitory(directoryService.getDormitoryName(dormitory.trim()));
						 }
						 //
						 String level = newDm.getLevel();
						 if (level != null && !level.trim().equals("")){
							 newDm.setLevel(directoryService.getLevelName(level.trim()));
						 }
						 //
						 String direction = newDm.getDirection();
						 if (direction != null && !direction.trim().equals("")){
							 newDm.setDirection(directoryService.getDirectionName(direction.trim()));
						 }
						 //
						 //
						 String sex = newDm.getGender();
						 if (sex != null && !sex.trim().equals("")){
							 newDm.setGender(directoryService.getSexName(sex.trim()));
						 }
						 temp.add(newDm);
						}catch(Throwable e){
							e.printStackTrace();
							continue;
						}
					}
				}
				//获取总记录数
				q = session.createQuery(" select count(*) " + sb.toString()); 
				//
				it = p.entrySet().iterator();
			    while (it.hasNext()){
					Map.Entry  e =(Map.Entry)it.next();
					Object key  = e.getKey();
					Object value = e.getValue();
					q.setParameter(""+key,value);
					
				}
				Number num = (Number)q.uniqueResult();
				//count = num.intValue();
				Object[] os = new Object[2];
				os[0] = temp;
				os[1] = num;
				return os;
			}
			
		});
		List t = (List)os[0];
		res.addAll(t);
		Number num = (Number)os[1];
		return num.intValue();
	}

	/* (non-Javadoc)
	 * @see org.king.quarters.service.IQuartersService#importQuarters(java.io.File)
	 */
	public int importQuarters(String userId,File excelFile) {
		// TODO Auto-generated method stub
		/*
		 * 0.成功
		 * 1.文件不存在 或 部门不存在
		 * 2.excel文件格式
		 * 3.格式不对
		 * 4.没有数据
		 * 
		 * */
		if (excelFile == null || !excelFile.exists()) return 1;
		TabSsDept dept = this.getManageDept(userId);
		if (dept == null || dept.getId() == null ||dept.getId().trim().equals("")) return 1;
		String rowInfo = "";
		try{
			Workbook workbook = Workbook.getWorkbook(excelFile);
			Sheet sheet = workbook.getSheet(0);
			
			//校区	区域	宿舍楼号	层号	单元号	房间号	总床位数	空床位数	入住性别	房间朝向	费用	电话
			int cs = sheet.getColumns();
			if (cs < 12) return 3;
			int rs = sheet.getRows();
			if (rs <= 1) return 4;
			Cell cell = null;
			NumberCell nc = null;
			Dormitorymodel model = null;
			List areas = directoryService.getAreas();
			List levels = directoryService.getLevels();
			List sexs = directoryService.getSexs();
			List ds = directoryService.getDirections();
			Map areaLocations = new HashMap();
			Map locationDormitorys = new HashMap();
			for (int i = 1; i < rs ; i++){
				
				 rowInfo = "第"+(i+1)+"行.";
				 
				 model = new Dormitorymodel();
				 model.setIfDistribute("1");
				 model.setCurDormDept(dept.getId());
				 //校区
				 cell = sheet.getCell(0, i);
				 
				
				 for (int j = 0 ; j < areas.size() ;j ++){
					 Map t = (Map)areas.get(j);
					 String name = (String)t.get("name");
					 if (cell.getContents() != null && cell.getContents().trim().equals(name)){
						 model.setArea((String)t.get("id"));
						 break;
					 }
					 
				 }
				 if (model.getArea() == null || model.getArea().trim().equals("")){
					 throw new RuntimeException("不存在的校区!");
				 }
				 //区域
				 cell = sheet.getCell(1, i);
				 List l = (List)areaLocations.get(model.getArea()); 
				 if (l == null)	{
					l =  directoryService.getLocations(model.getArea());
					areaLocations.put(model.getArea(),l);
				 }
				 
				 for (int j = 0 ; j < l.size() ;j ++){
					 Map t = (Map)l.get(j);
					 String name = (String)t.get("name");
					 if (cell.getContents() != null && cell.getContents().trim().equals(name)){
						 model.setLocation((String)t.get("id"));
						 break;
					 }
					
				 }
				 if(model.getLocation() == null || model.getLocation().trim().equals("")){
					 throw new RuntimeException("不存在的区域!");
				 }
				
				 //宿舍楼号
				 cell = sheet.getCell(2, i);
				 l = (List)locationDormitorys.get(model.getLocation());
				 if (l == null) {
					 l = directoryService.getDormitory(model.getLocation());
					 locationDormitorys.put(model.getLocation(),l);
				 }
				 for (int j = 0 ; j < l.size() ;j ++){
					 Map t = (Map)l.get(j);
					 String name = (String)t.get("name");
					 if (cell.getContents() != null && cell.getContents().trim().equals(name)){
						 model.setDormitory((String)t.get("id"));
						 break;
					 }
					 
				 }
				 if(model.getDormitory() == null || model.getDormitory().trim().equals("")){
					 throw new RuntimeException("不存在的宿舍楼号!");
				 }
				 //层号
				 cell = sheet.getCell(3, i);
				
				 for (int j = 0 ; j < levels.size() ;j ++){
					 Map t = (Map)levels.get(j);
					 String name = (String)t.get("name");
					 if (cell.getContents() != null && (cell.getContents().trim()+"层").equals(name)){
						 model.setLevel((String)t.get("id"));
						 break;
					 }
					 
				 }
				 if(model.getLevel() == null || model.getLevel().trim().equals("")){
					 throw new RuntimeException("不存在的层号!");
				 }
				 //单元号
				 cell = sheet.getCell(4, i);
				 model.setUnit(cell.getContents());
				 /*单元号可以为空*/
				 /*if(model.getUnit() == null || model.getUnit().trim().equals("")){
					 throw new RuntimeException("单元号不能为空!");
				 }*/
				 //房间号
				 cell = sheet.getCell(5, i);
				 model.setRoomNumber(cell.getContents());
				 if(model.getRoomNumber() == null || model.getRoomNumber().trim().equals("")){
					 throw new RuntimeException("房间号不能为空!");
				 }
				 //总床位数
				 cell = sheet.getCell(6, i);
				 nc = (NumberCell)cell;
				 model.setAccomodation((int)nc.getValue());
				 if(model.getAccomodation()==0){
					 throw new RuntimeException("总床位数不能为空!");
				 }
				 //空床位数
				 cell = sheet.getCell(7, i);
				 nc = (NumberCell)cell;
				 model.setEmptyNum((int)nc.getValue());
				 model.setDistributeNum((int)nc.getValue());
				 //入住性别
				 cell = sheet.getCell(8, i);
				 
				 for (int j = 0 ; j < sexs.size() ;j ++){
					 Map t = (Map)sexs.get(j);
					 String name = (String)t.get("name");
					 if (cell.getContents() != null && cell.getContents().trim().equals(name)){
						 model.setGender((String)t.get("id"));
						 break;
					 }
					 
				 }
				 if(model.getGender() == null || model.getGender().trim().equals("")){
					 throw new RuntimeException("入住性别不对!");
				 }
				 //房间朝向
				 cell = sheet.getCell(9, i);
				
				 for (int j = 0 ; j < ds.size() ;j ++){
					 Map t = (Map)ds.get(j);
					 String name = (String)t.get("name");
					 if (cell.getContents() != null && cell.getContents().trim().equals(name)){
						 model.setDirection((String)t.get("id"));
						 break;
					 }
					 
				 }
				
				 //费用
				 cell = sheet.getCell(10, i);
				 nc = (NumberCell)cell;
				 model.setFee(nc.getValue());
				 //电话
				 cell = sheet.getCell(11, i);
				 model.setTelphone(cell.getContents());
				 if (model.getAccomodation()<model.getDistributeNum()){
					 throw new RuntimeException("可分配床位数不能大于总床位数");
				 }
				 
				 if (model.getDistributeNum()<=0)model.setIfDistribute("0");
				 //
				 
				 Dormitorymodel exsitModel = null;
				 List ems = getExsitDormitorymodel(model);
				 if (ems != null && ems.size() > 1){
					 throw new RuntimeException("该房间已经被别的部门管理");
				 }
				 if (ems !=null && ems.size() ==1){
					 exsitModel = (Dormitorymodel)ems.get(0); 
				 }
				 if (exsitModel != null){
					 if (exsitModel.getCurDormDept() != null && exsitModel.getCurDormDept().trim().equals(dept.getId())){
						 exsitModel.setEmptyNum(model.getEmptyNum());
						 exsitModel.setDistributeNum(model.getEmptyNum());
						 exsitModel.setCurDormDept(dept.getId());
						 exsitModel.setIfDistribute(model.getIfDistribute());
						 exsitModel.setGender(model.getGender());
						 exsitModel.setDirection(model.getDirection());
						 exsitModel.setTelphone(model.getTelphone());
						 exsitModel.setFee(model.getFee());
						 //
						 allDAO.getHibernateTemplate().update(exsitModel);
					 }
					 else {
						 throw new RuntimeException("该房间已经被别的部门管理！");
					 }
				 }
				 else{
					 allDAO.getHibernateTemplate().save(model);
				 }
				 
				
			}
		
			workbook.close();
		}catch(Throwable e){
			e.printStackTrace();
			if (e instanceof RuntimeException){	
				String message = e.getMessage()+":"+rowInfo;
				throw new RuntimeException(message);
			}
			else {
				return 2;
			}
		}
		return 0;
	}
	private List getExsitDormitorymodel(Dormitorymodel con){
		String location = con.getLocation();
		String area = con.getArea();
		String dorm = con.getDormitory();
		String level = con.getLevel();
		String unit = con.getUnit();
		String roomNumber = con.getRoomNumber();
		List res = allDAO.getHibernateTemplate().findByNamedParam("from Dormitorymodel d where d.location=:location " +
				" and d.area=:area and d.dormitory=:dorm and d.level =:level " +
				" and d.unit =:unit and d.roomNumber =:roomNumber",
				new String[]{"location","area","dorm","level","unit","roomNumber"},new Object[]{location,area,dorm,level,unit,roomNumber});
		return res;
	}
	
	
	
	public static void main(String[] args){
		File f = new File("c:/test.xls");
		new QuartersServiceImpl().importQuarters(null,f);
	}

	public void setDirectoryService(IDirectoryService directoryService) {
		this.directoryService = directoryService;
	}

	public TabSsDept getManageDept(String userId) {
		try{
		Account acc =(Account)allDAO.getHibernateTemplate().get(Account.class, userId);
		String personCode = acc.getPerson().getPersonCode();
		List l = allDAO.getHibernateTemplate().findByNamedParam("select m.tabSsDept from TabSsManager m where m.stuNo =:stuNo and m.inOffice=:inOffice", 
				new String[]{"stuNo","inOffice"}, new Object[]{personCode,Boolean.TRUE});
		if (l != null && !l.isEmpty()){
			return (TabSsDept)l.get(0);
		}
		return null;
		}catch(Throwable e){
			e.printStackTrace();
			return null;
		}
	}

}
