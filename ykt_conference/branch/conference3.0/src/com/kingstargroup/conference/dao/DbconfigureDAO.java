/**
 * 
 */
package com.kingstargroup.conference.dao;

import java.util.Iterator;
import java.util.List;

import org.apache.log4j.Logger;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;

import com.kingstargroup.conference.common.SimpleEncoding;
import com.kingstargroup.conference.hibernate.form.TDictionary;


/**
 * @author jackey
 *
 */
public class DbconfigureDAO extends BasicDAO {
	private static DbconfigureDAO _instance;

	Logger errlog = Logger.getLogger("Errlog");
	Logger bizlog=Logger.getLogger("Businesslog");

	public static DbconfigureDAO getInstance() {
		if (_instance == null) {
			_instance = new DbconfigureDAO();
		}
		return _instance;
	}

	public String getDbconfigure(){
		Session s = getSession();
		String ret ="";
		try {			
			String temp = "from TPifDictionary a where a.id.dictNo=83";
			Query qt = s.createQuery(temp);
			String ip ="";
			String port ="";
			String dbname = "";
			String username ="";
			String pwd ="";
			List list = qt.list();
			Iterator iter = list.iterator();
			while(iter.hasNext()){
				TDictionary dic = (TDictionary)iter.next();
				if("ip".equals(dic.getId().getDictval())){
					ip=dic.getDictcaption();
				}else if("port".equals(dic.getId().getDictval())){
					port=dic.getDictcaption();
				}else if("dbname".equals(dic.getId().getDictval())){
					dbname=dic.getDictcaption();
				}else if("username".equals(dic.getId().getDictval())){
					username=dic.getDictcaption();
				}else if("pwd".equals(dic.getId().getDictval())){
					pwd=dic.getDictcaption();
				}
			}
			if("".equals(ip)||"".equals(port)||"".equals(dbname)||"".equals(username)||"".equals(pwd)){
				return ret;
			}else{
				String tempstr=ip+"&"+port+"&"+dbname+"&"+username+"&"+pwd;
				ret = SimpleEncoding.byte2hex(SimpleEncoding.encode(tempstr.getBytes(),"kingstar".getBytes()));
			}
			
		} catch (HibernateException ex) {
			ex.printStackTrace();
			errlog.error(ex);
		}catch (Exception e) {
			e.printStackTrace();
			errlog.error(e);
		}
		return ret;
	}


}
