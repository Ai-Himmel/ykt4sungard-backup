/* ============================================================
 * 版权：    king 版权所有 (c) 2006
 * 文件：    org.king.security.service.impl.AclImpl.java
 * 创建日期： 2006-4-19 23:02:06
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 * 2006-4-19 23:02:06      ljf        创建文件，实现基本功能
 * ============================================================
 */

/**
 * 
 */
package org.king.security.service.impl;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.king.framework.util.KingConfig;
import org.king.framework.util.MyUtils;
import org.king.framework.util.XMLUtils;
import org.king.security.domain.Account;
import org.king.security.domain.Menu;
import org.king.security.domain.ProtectedResource;
import org.king.security.domain.Resource;
import org.king.security.domain.Role;
import org.king.security.service.Acl;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

/**
 * <p>
 * AclImpl.java
 * </p>
 * <p>
 * {功能说明}
 * </p>
 * 
 * <p>
 * <a href="AclImpl.java.html"><i>查看源代码</i></a>
 * </p>
 * 
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-4-19
 * 
 * 
 */
public class AclImpl implements Acl {

	private static Log log = LogFactory.getLog(AclImpl.class);

	private static Map protectedResourcesMap;

	private static Collection protectedResources = new ArrayList();

	private static String fileName;

	private KingConfig kingConfig;

	public void setKingConfig(KingConfig kingConfig) {
		this.kingConfig = kingConfig;
	}

	/**
	 * init file path
	 */
	private void initFilePath() {
		fileName = kingConfig.getSecurityConfigPath();
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.security.service.Acl#isProtectedResource(java.lang.String)
	 */
	public boolean isProtectedResource(String url) {
		if (fileName == null) {
			init();
		}

		if (MyUtils.isBlank(url)) {
			return false;
		}

		return protectedResourcesMap.containsKey(url);

	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.security.service.Acl#getProtectedResources()
	 */
	public Collection getProtectedResources() {
		if (fileName == null) {
			init();
		}

		return protectedResources;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.security.service.Acl#setProtectedResourcesMap(java.util.Map)
	 */
	public void setProtectedResourcesMap(Map map) {
		init();
		protectedResourcesMap = map;
		protectedResources = (Collection) map.get("protectedResources");
		XMLUtils.write(protectedResources, fileName);

	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.security.service.Acl#hasRight(java.lang.String,
	 *      java.lang.String)
	 */
public boolean hasRight(String url, Account account) {
//		log.info("hasRight: " + url + account);

		if (fileName == null) {
			init();
		}

		if (MyUtils.isBlank(url) || MyUtils.isBlank(account)) {
			return false;
		}

		Set roles = account.getRoles();
		
		if(roles!=null){
			   for(Iterator iterator =roles.iterator();iterator.hasNext(); ){
				   Role role = (Role)iterator.next();
				   Set resources = role.getResources();
				   if(resources!=null){
					   for(Iterator iteratorRes =resources.iterator();iteratorRes.hasNext(); ){
						   Resource resource = (Resource)iteratorRes.next();
						   if(url.equals(resource.getUrl())){
							   return true;
						   }
					   }
				   }
				   
			   }
				
			}

			return false;

	}
	private void init() {
		initFilePath();

		int i;
		File xmlFile = new File(fileName);
		Document doc = null;
		String box = null;
		String url = null;
		String desc = null;
		String property;
		String value;

		try {
			DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();

			// validate xml file by parser
			// that is: use a dtd file to validate the xml file
			dbf.setValidating(true);

			DocumentBuilder db = dbf.newDocumentBuilder();
			doc = db.parse(xmlFile);

			Element root = doc.getDocumentElement();
			NodeList nodes = root.getChildNodes();

			for (i = 0; i < nodes.getLength(); i++) {
				Node node = nodes.item(i);

				if (node.getNodeName().equals("#text")) {
					continue;
				}

				if (node.getNodeName().equals(
						ProtectedResource.PROPERTY_PROTECTED_RESOURCE)) {
					ProtectedResource pr = parseNode(node);
					protectedResources.add(pr);
				}
			}
		} catch (ParserConfigurationException e) {
			log.error("parse acl-config.xml: " + e);
		} catch (IOException e) {
			log.error("parse  acl-config.xml: " + e);
		} catch (SAXException e) {
			log.error("parse acl-config.xml: " + e);
		}
	}

	/**
	 * Read uri and desc from a protected-resource node
	 * 
	 * @param protectedResourceNode
	 *            node of protected resource in xml file
	 * @return ProtectedResources
	 */
	private ProtectedResource parseNode(final Node protectedResourceNode) {
		String property;
		String value;
		NodeList nodes = protectedResourceNode.getChildNodes();
		String code = null;
		String url = null;
		String name = null;

		for (int i = 0; i < nodes.getLength(); i++) {
			Node node = nodes.item(i);

			if (node.getNodeName().equals("#text")) {
				continue;
			}

			property = node.getNodeName();
			value = node.getFirstChild().getNodeValue();

			if (property.equals(ProtectedResource.PROPERTY_URL)) {
				url = value;
			} else if (property.equals(ProtectedResource.PROPERTY_NAME)) {
				name = value;
			} else if (property.equals(ProtectedResource.PROPERTY_CODE)) {
				code = value;
			}
		}

		return new ProtectedResource(code, name, url);
	}

}
