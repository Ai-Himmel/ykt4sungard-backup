package org.king.util;

import org.apache.commons.lang.StringUtils;
import org.apache.log4j.Logger;
import org.king.bean.ReceiveBean;
import org.king.bean.ReceiveItem;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import java.io.CharArrayReader;
import java.io.IOException;
import java.io.Reader;
import java.io.UnsupportedEncodingException;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * .
 * User: Yiming.You
 * Date: 2011-4-28
 */
public class Transformer {
    private static final Logger logger = Logger.getLogger(Transformer.class);

    /**
     * transform query result into map,key is the alias of the field in query string
     *
     * @param rs .
     * @return .
     * @throws SQLException .
     */
    public List<Map> transformToMap(ResultSet rs) throws SQLException {
        List<Map> result = new ArrayList<Map>();
        if (rs != null) {
            ResultSetMetaData metaData = rs.getMetaData();
            int columnCount = metaData.getColumnCount();
            while (rs.next()) {
                Map row = new HashMap();
                for (int i = 1; i <= columnCount; i++) {
                    String value = rs.getObject(i) == null ? "" : rs.getObject(i).toString();
                    row.put(metaData.getColumnName(i), value);
                }
                result.add(row);
            }
        }
        return result;
    }

    /**
     * transform query result into pojo,make sure there are set methods for the alias of the field in query string
     *
     * @param rs          .
     * @param entityClass .
     * @param <T>         .
     * @return .
     * @throws InvocationTargetException .
     * @throws NoSuchMethodException     .
     * @throws InstantiationException    .
     * @throws IllegalAccessException    .
     * @throws SQLException              .
     */
    public <T> List<T> transformToBean(ResultSet rs, final Class<T> entityClass) throws InvocationTargetException, NoSuchMethodException, InstantiationException, IllegalAccessException, SQLException {
        Map<String, Method> methods = getMethods(entityClass);
        List<T> result = new ArrayList<T>();
        if (rs != null) {
            ResultSetMetaData metaData = rs.getMetaData();
            int columnCount = metaData.getColumnCount();
            while (rs.next()) {
                T bean = getInstance(entityClass);
                for (int i = 1; i <= columnCount; i++) {
                    String columnName = metaData.getColumnName(i);
                    String value = rs.getObject(i) == null ? "" : rs.getObject(i).toString();
                    Method setMethod = methods.get("SET" + columnName.toUpperCase());
                    if (setMethod != null) {
                        Object[] args = new Object[]{value};
                        setMethod.invoke(bean, args);
                    } else {
                        logger.warn("can't find method:" + "SET" + columnName.toUpperCase());
                    }
                }
                result.add(bean);
            }
        }
        return result;
    }

    /**
     * get mapped methods,chang method name into upper case
     *
     * @param entityClass .
     * @return .
     */
    public Map<String, Method> getMethods(Class entityClass) {
        Map<String, Method> methods = new HashMap<String, Method>();
        Method[] array = entityClass.getMethods();
        for (int i = 0; i < array.length; i++) {
            Method method = array[i];
            String methodName = method.getName().toUpperCase();
            methods.put(methodName, method);
        }
        return methods;
    }

    /**
     * use constructor without args to get instance
     *
     * @param entityClass .
     * @param <T>         .
     * @return
     * @throws NoSuchMethodException     .
     * @throws InvocationTargetException .
     * @throws IllegalAccessException    .
     * @throws InstantiationException    .
     */
    public <T> T getInstance(final Class<T> entityClass) throws NoSuchMethodException, InvocationTargetException, IllegalAccessException, InstantiationException {
        Class[] argsClass = new Class[0];
        Object[] args = new Object[0];
        Constructor<T> constructor = entityClass.getConstructor(argsClass);
        return constructor.newInstance(args);
    }

    public Document parse(String content) throws IOException, SAXException, ParserConfigurationException {
        DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
        factory.setIgnoringElementContentWhitespace(true);
        DocumentBuilder builder = factory.newDocumentBuilder();
        Reader reader = new CharArrayReader(content.toCharArray());
        Document document = builder.parse(new InputSource(reader));
        return document;
    }

    /**
     * parse the response of init request
     *
     * @param content .
     * @return .
     */
    public boolean parseInitResult(String content) {
        if (StringUtils.isBlank(content)) {
            throw new RuntimeException("init content can not be null");
        }
        boolean initialized = false;

        //init result include action,status,msg,ecard_ip,time,code node,but we are concerned about action and status node
        String action = NodeUtil.getNodeValue("action", content)[0];
        String status = NodeUtil.getNodeValue("status", content)[0];
        if ("会话初始化".equals(action) && "成功".equals(status)) {
            initialized = true;
            logger.info("succeed to init session");
        } else {
            logger.error(content);
        }
        return initialized;
    }

    /**
     * parse the response of destroy request
     *
     * @param content .
     * @return .
     */
    public boolean parseDestroyResult(String content) {
        if (StringUtils.isBlank(content)) {
            throw new RuntimeException("destroy content can not be null");
        }
        boolean destroyed = false;

        //destroy result include action,status,msg,ecard_ip,time,code node,but we are concerned about action and status node
        String action = NodeUtil.getNodeValue("action", content)[0];
        String status = NodeUtil.getNodeValue("status", content)[0];
        if ("会话销毁".equals(action) && "成功".equals(status)) {
            destroyed = true;
            logger.info("succeed to destroy session");
        } else {
            logger.error(content);
        }
        return destroyed;
    }

    /**
     * parse the response of check request
     *
     * @param content .
     * @return .
     * @throws ParserConfigurationException .
     * @throws IOException                  .
     * @throws SAXException                 .
     */
    public ReceiveBean parseCheckResult(String content) throws ParserConfigurationException, IOException, SAXException {
        if (StringUtils.isBlank(content)) {
            throw new RuntimeException("check content can not be null");
        }
        ReceiveBean receiveBean = new ReceiveBean();
        Document document = parse(content);
        Element root = document.getDocumentElement();

        NodeList nodes = root.getChildNodes();
        Node dataNode = null;
        //parse action,status,msg node,and find data node if they exist
        for (int i = 0; i < nodes.getLength(); i++) {
            Node node = nodes.item(i);
            if (Node.TEXT_NODE == node.getNodeType()) {
                //find a text node
            } else {
                String nodeName = node.getNodeName();
                if ("action".equalsIgnoreCase(nodeName)) {
                    receiveBean.setAction(NodeUtil.getNodeText(node));
                } else if ("status".equalsIgnoreCase(nodeName)) {
                    receiveBean.setStatus(NodeUtil.getNodeText(node));
                } else if ("msg".equalsIgnoreCase(nodeName)) {
                    receiveBean.setMsg(NodeUtil.getNodeText(node));
                } else if ("data".equalsIgnoreCase(nodeName)) {
                    dataNode = node;
                } else if ("time".equalsIgnoreCase(nodeName)) {
                    receiveBean.setTime(NodeUtil.getNodeText(node));
                } else if ("code".equalsIgnoreCase(nodeName)) {
                    receiveBean.setCode(NodeUtil.getNodeText(node));
                } else {
                    //find an unexpected node
                    logger.warn("find an unexpected node:" + nodeName);
                }
            }
        }
        if ("对帐请求".equals(receiveBean.getAction()) && "成功".equals(receiveBean.getStatus())) {
            receiveBean.setData(parseDataNode(dataNode));
        } else {
            logger.error(content);
        }

        return receiveBean;
    }

    private List<ReceiveItem> parseDataNode(Node dataNode) {
        List<ReceiveItem> items = new ArrayList<ReceiveItem>();
        //parse data node,find check record list
        if (dataNode != null) {
            NodeList checkNodes = dataNode.getChildNodes();
            for (int i = 0; i < checkNodes.getLength(); i++) {
                Node node = checkNodes.item(i);
                if (Node.TEXT_NODE == node.getNodeType()) {
                    //find a text node
                } else {
                    String nodeName = node.getNodeName();
                    if ("check".equals(nodeName)) {
                        ReceiveItem item = parseCheckNode(node);
                        //check item if it's necessary
                        if (StringUtils.isNotBlank(item.getEcardId())) {
                            items.add(item);
                        } else {
                            logger.warn("find a check result without ecard_id:[" + item.getEcardId() + "," + item.getCheckResult() + "]");
                        }
                    } else {
                        //find an unexpected node
                        logger.warn("find an unexpected node:" + nodeName);
                    }
                }
            }
        }
        return items;
    }

    private ReceiveItem parseCheckNode(Node checkNode) {
        NodeList nodes = checkNode.getChildNodes();
        ReceiveItem item = new ReceiveItem();
        for (int i = 0; i < nodes.getLength(); i++) {
            Node node = nodes.item(i);
            if (Node.TEXT_NODE == node.getNodeType()) {
                //find a text node
            } else {
                String nodeName = node.getNodeName();
                if ("ecard_id".equals(nodeName)) {
                    item.setEcardId(NodeUtil.getNodeText(node));
                } else if ("check_result".equals(nodeName)) {
                    item.setCheckResult(NodeUtil.getNodeText(node));
                } else {
                    //find an unexpected node
                    logger.warn("find an unexpected node:" + nodeName);
                }
            }
        }
        updateItemStatus(item);
        return item;
    }

    private void updateItemStatus(ReceiveItem item) {
        String checkResult = item.getCheckResult();

        if ("数据不完整!".equals(checkResult)) {
            item.setStatus("4");
        } else if ("对帐补充值成功!".equals(checkResult)) {
            item.setStatus("5");
        } else if ("对帐补充值失败!".equals(checkResult)) {
            item.setStatus("6");
        } else if ("对帐成功!无错误!".equals(checkResult)) {
            item.setStatus("7");
        } else {
            logger.warn("can not get status from the unexpected check_result:[" + item.getEcardId() + "," + item.getCheckResult() + "]");
        }
    }
}
