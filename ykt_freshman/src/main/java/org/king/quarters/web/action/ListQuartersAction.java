/* ============================================================
 * 版权：    king 版权所有 (c) 2007
 * 文件：    ListDeptAction.java
 * 创建日期： 2007-6-5 下午02:58:15
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 *  2007-6-5 下午02:58:15     王胜        创建文件，实现基本功能
 * ============================================================
 */
package org.king.quarters.web.action;

import java.io.ByteArrayInputStream;
import java.io.InputStream;
import java.io.OutputStream;
import java.sql.Date;
import java.sql.Time;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletResponse;

import org.apache.poi.hssf.usermodel.HSSFCell;
import org.apache.poi.hssf.usermodel.HSSFCellStyle;
import org.apache.poi.hssf.usermodel.HSSFFont;
import org.apache.poi.hssf.usermodel.HSSFRow;
import org.apache.poi.hssf.usermodel.HSSFSheet;
import org.apache.poi.hssf.usermodel.HSSFWorkbook;
import org.apache.poi.hssf.util.HSSFColor;
import org.king.common.service.IDirectoryService;
import org.king.dormitorymanage.domain.Dormitorymodel;
import org.king.quarters.domain.TabSsDept;
import org.king.quarters.service.IQuartersService;
import org.king.quarters.service.QuartersModel;

import com.opensymphony.webwork.ServletActionContext;
import com.opensymphony.xwork.ActionContext;
import com.opensymphony.xwork.ActionSupport;
import com.opensymphony.xwork.Preparable;

public class ListQuartersAction extends ActionSupport implements Preparable{

	private IQuartersService quartersService;
	private IDirectoryService directoryService;
	
	private List quarters = new ArrayList();
	private List locations;
	private List areas;
	private List dormitorys;
	private List sexs;
	private List levels;
	private List directions;
	private TabSsDept dept;
	private int pageNo = 1;
	private int pageSize = 100;
	private int count = 0;
	
	private QuartersModel model;
	
	private String type ="dofind";
	
	public List getQuarters() {
		return quarters;
	}
	
	public void prepare() throws Exception {
		areas = directoryService.getAreas();
		sexs = directoryService.getSexs();
		levels =directoryService.getLevels();
		directions = directoryService.getDirections();
		ActionContext context = ActionContext.getContext();
		String userId = (String)context.getSession().get("account");
	    dept  = quartersService.getManageDept(userId);
	}
	public String input(){
		//managers = quartersManagerService.getManagers();
		
		if (dept == null){
			  return "noRight";
			}
		return this.INPUT;
	}
	
	public String search() throws Exception{
		ActionContext context = ActionContext.getContext();
		String userId = (String)context.getSession().get("account");
				
		if (model != null && model.getArea() != null && ! model.getArea().trim().equals("")){
			locations = directoryService.getLocations(model.getArea());
		}
		if (model != null && model.getLocation() != null && !model.getLocation().trim().equals("")){
			dormitorys = directoryService.getDormitory(model.getLocation());
		}
		if(type.equals("doexl")){
			count = quartersService.getQuartersListAll(userId,quarters,model);
			
			HttpServletResponse response = ServletActionContext.getResponse();

			String	fileName="dormitory.xls";
				
			HSSFWorkbook wb = new HSSFWorkbook();
			            			
			HSSFSheet sheet1 = wb.createSheet("Sheet1");

			HSSFRow row = sheet1.createRow((short)0);
			
			List columnNames =new ArrayList();
			columnNames.add(0,"校区");
			columnNames.add(1,"区域");
			columnNames.add(2,"宿舍楼号");
			columnNames.add(3,"层号");
			columnNames.add(4,"单元号");
			columnNames.add(5,"房间号");
			columnNames.add(6,"总床位数");
			columnNames.add(7,"可分配给新生的床位数");
			columnNames.add(8,"入住性别");
			columnNames.add(9,"房间朝向");
			columnNames.add(10,"费用");
			columnNames.add(11,"电话");
			// System.out.println(columnNames.size());
			for (int i=0; i<columnNames.size(); i++)
			{
				 HSSFCell cname=row.createCell((short)i);
				 cname.setEncoding(HSSFCell.ENCODING_UTF_16);
				 cname.setCellValue((String)columnNames.get(i));
			}
			
			int rowCount =count;
			int currentCell = 0;
			
			for (int i=0; i<rowCount; i++)
			{
				Dormitorymodel dorm = (Dormitorymodel)quarters.get(i);
				
				row = sheet1.createRow((short)(i+1));
				
				HSSFCell ctitle=row.createCell((short)0);	
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue(dorm.getArea());
					
				ctitle=row.createCell((short)1);	
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue(dorm.getLocation());
					
				ctitle=row.createCell((short)2);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue(dorm.getDormitory());
					
				ctitle=row.createCell((short)3);	
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				String level=dorm.getLevel();
				if(level!=null){
				    int pos=level.indexOf("层");
				    if(pos!=-1)
					    level=level.substring(0,pos);
				}
				ctitle.setCellValue(level);
					
				ctitle=row.createCell((short)4);	
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue(dorm.getUnit());
					
				ctitle=row.createCell((short)5);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue(dorm.getRoomNumber());

                ctitle=row.createCell((short)6);	
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue(dorm.getAccomodation());
					
				ctitle=row.createCell((short)7);	
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue(dorm.getDistributeNum());
					
				ctitle=row.createCell((short)8);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue(dorm.getGender());
				
				ctitle=row.createCell((short)9);	
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue(dorm.getDirection());
					
				ctitle=row.createCell((short)10);	
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue(dorm.getFee());
				
				ctitle=row.createCell((short)11);	
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue(dorm.getTelphone());
														
				currentCell++;

			}						
			
			response.setContentType("application/x-msdownload");
			response.setHeader("Content-Disposition", "attachment;"
					+ " filename="
					+ new String(fileName.getBytes(), "ISO-8859-1"));

            OutputStream os = response.getOutputStream();
            wb.write(os);
            os.close();
            
		    return null;	
		}		    
		else{
			count = quartersService.getQuartersList(userId,quarters, pageNo, pageSize, model);
			
			return this.INPUT;
		}
	}
	public void setQuartersService(IQuartersService quartersService) {
		this.quartersService = quartersService;
	}
	//分页
	public int getPageNo() {
		return pageNo;
	}
	public void setPageNo(int pageNo) {
		this.pageNo = pageNo;
	}
	public int getPageSize() {
		return pageSize;
	}
	public void setPageSize(int pageSize) {
		this.pageSize = pageSize;
	}
	public int getCount() {
		return count;
	}
	public void setCount(int count) {
		this.count = count;
	}
	public void setDirectoryService(IDirectoryService directoryService) {
		this.directoryService = directoryService;
	}
	public List getLocations() {
		return locations;
	}
	public void setLocations(List locations) {
		this.locations = locations;
	}
	public List getSexs() {
		return sexs;
	}
	public void setSexs(List sexs) {
		this.sexs = sexs;
	}
	public List getAreas() {
		return areas;
	}
	public void setAreas(List areas) {
		this.areas = areas;
	}
	public List getDormitorys() {
		return dormitorys;
	}
	public void setDormitorys(List dormitorys) {
		this.dormitorys = dormitorys;
	}
	public List getDirections() {
		return directions;
	}
	public void setDirections(List directions) {
		this.directions = directions;
	}
	public List getLevels() {
		return levels;
	}
	public void setLevels(List levels) {
		this.levels = levels;
	}
	public TabSsDept getDept() {
		return dept;
	}
	public void setDept(TabSsDept dept) {
		this.dept = dept;
	}

	public QuartersModel getModel() {
		return model;
	}

	public void setModel(QuartersModel model) {
		this.model = model;
	}
	
	public String getType() {
		return type;
	}

	public void setType(String type) {
		this.type = type;
	}
	
}
