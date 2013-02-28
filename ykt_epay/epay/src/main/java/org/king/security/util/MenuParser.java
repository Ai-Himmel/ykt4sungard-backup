package org.king.security.util;

import org.apache.commons.lang.StringUtils;
import org.dom4j.Document;
import org.dom4j.Element;
import org.dom4j.io.SAXReader;
import org.king.security.domain.Menu;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.core.io.Resource;
import org.springframework.core.io.support.PathMatchingResourcePatternResolver;

import java.io.File;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;

/**
 * 菜单配置文件解析器
 *
 * @author Chen Junping
 */
public class MenuParser {
    private static Logger logger = LoggerFactory.getLogger(MenuParser.class);

    private static Menu menu = null;      //菜单对象

    private static String menuFile = "menu.xml";

    private static Set<String> urls = new HashSet<String>();
    			
    private static Set<String> acctypeurls = new HashSet<String>();

    public MenuParser(String menuFile) {
        this.menuFile = menuFile;
    }

    public static Menu getMenu() {
        return menu;
    }

    public static void setMenu(Menu menu) {
        MenuParser.menu = menu;
    }

    public static Set<String> getUrls() {
        return urls;
    }
    
    public static Set<String> getAcctypeurls() {
        return acctypeurls;
    }
    //菜单项初始化

    public static void init() {
        parseMenu();
    }

    //重新加载菜单项

    public static void reloadMenu() {
        parseMenu(true);
    }

    /**
     * 解析菜单
     *
     * @return .
     */
    public static Menu parseMenu() {

        return parseMenu(false);
    }

    public static Menu parseMenu(boolean isReload) {
        if (menu == null || isReload) {
            Menu menu = new Menu();
            urls.clear();
            try {
                PathMatchingResourcePatternResolver resolver = new PathMatchingResourcePatternResolver();

                Resource resource = resolver.getResource(menuFile);

                File file = resource.getFile();
                logger.info("the menu file path is " + file.getAbsolutePath());

                SAXReader reader = new SAXReader();
                Document doc = reader.read(file);
                Element root = doc.getRootElement();
                Element systemElement = (Element) root.elements().get(0);
                menu = parseMenuItem(systemElement, null);
            } catch (Exception e) {
                logger.info("error", e);
            }
            setMenu(menu);
        }
        return getMenu();
    }

    /**
     * 解析菜单明细项
     *
     * @param element        .
     * @param parentMenuItem .
     * @return .
     */
    private static Menu parseMenuItem(Element element, Menu parentMenuItem) {
        Menu item = new Menu();

        try {
            item.setCode(StringUtils.defaultString(element.attributeValue("code"), ""));
            item.setId(StringUtils.defaultString(element.attributeValue("id"), ""));
            item.setPid(StringUtils.defaultString(element.attributeValue("pid"), ""));
            item.setName(StringUtils.defaultString(element.attributeValue("name"), ""));
            item.setUrl(StringUtils.defaultString(element.attributeValue("url"), ""));
            item.setTitle(StringUtils.defaultString(element.attributeValue("title"), ""));
            item.setTarget(StringUtils.defaultString(element.attributeValue("target"), ""));
            item.setSortFlag(Integer.parseInt(StringUtils.defaultString(element.attributeValue("sortFlag"), "0")));
            item.setIcon(StringUtils.defaultString(element.attributeValue("icon"), ""));
            urls.add(item.getUrl());
            acctypeurls.add(item.getCode()+item.getUrl());
            Element child;
            Iterator iterator = element.elementIterator("menuitem");
            List<Menu> items = new ArrayList<Menu>();

            if (iterator != null && iterator.hasNext()) {
                for (; iterator.hasNext();) {
                    child = (Element) iterator.next();
                    Menu tmp = parseMenuItem(child, item);
                    items.add(tmp);
                }
            }
            item.setChildren(items);
        } catch (Exception e) {
            logger.info("error", e);
        }
        return item;
    }

    public static void main(String[] args) {
        init();
        Menu menu = getMenu();

    }
}
