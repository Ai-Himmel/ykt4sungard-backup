package com.kingstargroup.advquery.hibernate.util;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.apache.poi.hssf.usermodel.HSSFRow;
import org.apache.poi.hssf.usermodel.HSSFSheet;
import org.apache.struts.util.LabelValueBean;

import com.kingstargroup.advquery.hibernate.dao.LunchDAO;
import com.kingstargroup.advquery.lunch.TCifCosumerLunch;


public class LunchUtil extends BasicUtil {
	
	
	public static boolean  delePerson(String[] cutId){
		try{
		LunchDAO dao = LunchDAO.getInstance();
		for(int i=0;i<cutId.length;i++){
			TCifCosumerLunch lun = dao.finLunch(Integer.valueOf(cutId[i]));
			dao.delePerson(lun);
		}
		return true;  
		} catch (Exception e){
			return false;
		}finally{
			closeSession();
		}
	}  

    public static List getLunchtotal(String beginDate, String endDate, String tradedept,String lunchtype) {
        LunchDAO dao = LunchDAO.getInstance();
        List result = new ArrayList();
        try {
        	int all =0;
            List lunchtotal = dao.getLunchTotal(beginDate, endDate, tradedept,lunchtype);
            for (int i = 0; i < lunchtotal.size(); i++) {
                Object[] objects = (Object[]) lunchtotal.get(i);
                all=all+Integer.parseInt(objects[6].toString());
                HashMap lunMap = new HashMap();
                lunMap.put("deptname", objects[0]);
                lunMap.put("stuempno", objects[1]);
                lunMap.put("cutname", objects[2]);
                lunMap.put("typename", objects[3]);
                lunMap.put("total", objects[6]);
                lunMap.put("lunchtype", getTypename(objects[5]));
                result.add(lunMap);
            }
            HashMap lunMap = new HashMap();
            lunMap.put("deptname", "�ϼ�");
            lunMap.put("stuempno", "");
            lunMap.put("cutname", "");
            lunMap.put("typename", "");
            lunMap.put("total",new Integer(all));
            lunMap.put("lunchtype", "");
            result.add(lunMap);
            return result;
        } catch (Exception he) {
            he.printStackTrace();
            return null;
        } finally {
            closeSession();
        }
    }
    
    private static String  getTypename(Object typeid){
    	
    	if(typeid==null){
    		return "��Ա�����δ�Ǽ�";
    	}
    	if(typeid.toString().equals("1")){
    		return "ѧУ";
    	}
    	if(typeid.toString().equals("2")){
    		return "����";
    	}
    	if(typeid.toString().equals("3")){
    		return "�ʲ���˾";
    	}
    	return "";
    }

    public static List getLunchPerson(String stuempno, String tradedept,String lunchtype) {
        LunchDAO dao = LunchDAO.getInstance();
        List result = new ArrayList();
        try {
            List lunchPerson = dao.getLunchPerson(stuempno, tradedept,lunchtype);
            for (int i = 0; i < lunchPerson.size(); i++) {
                Object[] objects = (Object[]) lunchPerson.get(i);
                HashMap lunMap = new HashMap();
               
                lunMap.put("cut_name", objects[0]);
                lunMap.put("phy_ID", objects[1]);
                lunMap.put("stuemp_no", objects[2]);
                lunMap.put("state", objects[3]);
                lunMap.put("dept_name", objects[4]);
                lunMap.put("cut_id", objects[5]);
                lunMap.put("lunch_type", getTypename(objects[6]));
                result.add(lunMap);
            }
            return result;
        } catch (Exception he) {
            he.printStackTrace();
            return null;
        } finally {
            closeSession();
        }

    }

    public static List getLunch(String stuempno, String beginDate, String endDate, String tradedept,String lunchtype ) {
        //TODO
        LunchDAO dao = LunchDAO.getInstance();
        List result = new ArrayList();
        try {
            List account = dao.getLunch(stuempno, beginDate, endDate, tradedept,lunchtype);
            for (int i = 0; i < account.size(); i++) {
                Object[] objects = (Object[]) account.get(i);
                HashMap accMap = new HashMap();
                accMap.put("tx_date", objects[0]);
                accMap.put("tx_time", objects[1]);
                accMap.put("card_no", objects[2]);
                accMap.put("cut_name", objects[3]);
                accMap.put("device_id", objects[4]);
                accMap.put("COL_TIMESTAMP", objects[5]);
                accMap.put("stuemp_no", objects[6]);
                accMap.put("dept_name", objects[7]);
                accMap.put("lunch_type", getTypename(objects[8]));
                result.add(accMap);
            }
            return result;
        } catch (Exception he) {
            he.printStackTrace();
            return null;
        } finally {
            closeSession();
        }
    }
    
   /* public static  List  getLunchType(){
    	Map   tempMap = new HashMap();
    	String typeid="1";
    	String typename="ѧУ";
    	List  list = new ArrayList();
   
    	list.add(new LabelValueBean(typeid,typename));
    	typeid="2";
    	typename="����";
    	
    	list.add(new LabelValueBean(typeid,typename));
    	
    	typeid="3";
    	typename="�ʲ���˾";
    	list.add(new LabelValueBean(typeid,typename));
    	
    	list.add(tempMap);
    	return list;
    }*/
     

    public static String implunchfile(HSSFSheet sheet) {
        LunchDAO dao = new LunchDAO();
        String result = "";
        try {
            int rowCount = sheet.getPhysicalNumberOfRows();
            if (rowCount > 0) {
                int savenum = 0;
                int delnum = 0;
                for (int i = 1; i < rowCount; i++) {
                    HSSFRow row = sheet.getRow(i);
                    try {
                        String stuempNo = "";//ѧ����
                        String name = "";//����
                        String state = "";//״̬
                        String lunchtype="";
                        stuempNo = row.getCell((short) 0).getStringCellValue().trim();
                        name = row.getCell((short) 1).getStringCellValue().trim();
                        state = row.getCell((short) 2).getStringCellValue().trim();
                        lunchtype = row.getCell((short) 3).getStringCellValue().trim();
                        
                        Map tempMap = CustomerUtil.findCustomer(stuempNo, name);
                        if (tempMap.isEmpty() || !name.equals(tempMap.get("cutName"))) {
                            result = result + "��" + i + "��ѧ���ź�������Ӧ����Ϣ������,����ע��<br> ";
                            return result;
                        }
                        if(!lunchtype.equals("1")&&!lunchtype.equals("2")&&!lunchtype.equals("3")){
                     	   result = result + "��" + i + "��,�Ͳ�������ݴ���<br> ";
                     	   return result;
                     	   
                        }
                        //�����ظ�����
                        TCifCosumerLunch lun = dao.finLunch((Integer) tempMap.get("cutId"));
                        if (state.equals("1")) {//����
                            if (lun == null) {
                                if (dao.saveLunch(tempMap,lunchtype)) {
                                    savenum++;
                                }
                            } else {
                            	lun.setState(Integer.valueOf("1"));
                            	lun.setLunchType(Integer.valueOf(lunchtype));
                            	if(dao.updateLunch(lun)){
                            		savenum++;
                            	}
                            }
                        } else if (state.equals("3")) {//ɾ��
                            if (lun != null) {
                                if (dao.delLunch(lun)) ;
                                delnum++;
                            }
                        }
                    } catch (NumberFormatException ne) {
                        result = result + "��" + i + "���������ݷ��ı����ͣ��޸��ı����ͺ��ٵ��롣<br> ";
                    } catch (NullPointerException n) {
                        result = result + "��" + i + "���п����ݣ��������ٵ��롣<br>";
                    }
                }
                result = result + " �ɹ�����" + savenum + "�С�<br>";
                result = result + "�ɹ�ɾ��" + delnum + "�С�<br>";
            } else {
                result = result + "û���ҵ���Ч�ļ�¼��<br>";
            }
        } catch (Exception e) {
            result = result + "Excel�ļ�����쳣���޷����롣<br>";
        }finally{
        	 closeSession();
        }
        return result;
    }
}