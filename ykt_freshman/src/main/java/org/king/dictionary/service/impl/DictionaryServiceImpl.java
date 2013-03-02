package org.king.dictionary.service.impl;

import java.sql.Types;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.Locale;
import java.util.Map;

import org.king.classmanage.domain.Department;
import org.king.classmanage.domain.Dictionary;
import org.king.classmanage.domain.DictionaryId;
import org.king.dictionary.service.DictionaryService;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;

import com.ibm.icu.text.CollationKey;
import com.ibm.icu.text.Collator;

public class DictionaryServiceImpl implements DictionaryService {

	private BaseDAO baseDAO;
	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}
	public List getDictionaryList(String flag) {
		List li = new ArrayList();
		MyQuery mq = new MyQuery();
		StringBuffer hqlStrBuf = 
			new StringBuffer("select new Map(a.id as id,a.id.dictValue as dictValue,a.dictCaption as dictCaption) "
				           + " from Dictionary a ");
		StringBuffer whereStrBuf =
			new StringBuffer(" where 1=1 and a.id.dictNo = ? ");
		if("23".equals(flag)){
			whereStrBuf.append(" order by a.id.dictValue ");
		}
		mq.addPara( new Integer(flag), Types.INTEGER);
		hqlStrBuf.append(whereStrBuf);
		mq.setQueryString(hqlStrBuf.toString());
		li = baseDAO.findEntity(mq);
		
		if(!"23".equals(flag)){
			Comparator comp2 = new Comparator() {
				public int compare(Object o1, Object o2) {
					Map m1 = (Map) o1;
					Map m2 = (Map) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String stuName1 = (String) m1.get("dictCaption");
					String stuName2 = (String) m2.get("dictCaption");
					CollationKey c1 = col.getCollationKey(stuName1);
					CollationKey c2 = col.getCollationKey(stuName2);
					return c1.compareTo(c2);
				}
			};
			Collections.sort(li, comp2);		
		}
		return li;
	}
	
	public boolean check4Add(DictionaryId dictionaryId){
		List dictli=find("select a from Dictionary a where a.id.dictNo="+dictionaryId.getDictNo()+" and a.id.dictValue='"+dictionaryId.getDictValue()+"'");
		if(dictli!=null&&dictli.size()>0)
			return false;
		else
			return true;
			
	}
	
	public Dictionary findbyId(String dictvalue,String dictno){
		List dictli=find("select a from Dictionary a where a.id.dictNo="+dictno+" and a.id.dictValue='"+dictvalue+"'");
		if(dictli!=null&&dictli.size()>0){
			Dictionary dictionary=(Dictionary)dictli.get(0);
			return dictionary;
		}else
			return null;
	}
	public void save(Dictionary dictionary){
		baseDAO.saveEntity(dictionary);
	}
	public void update(Dictionary dictionary){
		baseDAO.updateEntity(dictionary);
	}
	
	public List find(String query){
		List result=null;
		try{
			result=baseDAO.findEntity(query);
		}catch(Exception e){
			e.printStackTrace();
		}
		if(result==null)
			System.out.println("findresult is null");
		return result;
	}
}