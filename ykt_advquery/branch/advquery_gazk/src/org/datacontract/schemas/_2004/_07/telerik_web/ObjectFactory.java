
package org.datacontract.schemas._2004._07.telerik_web;

import javax.xml.bind.JAXBElement;
import javax.xml.bind.annotation.XmlElementDecl;
import javax.xml.bind.annotation.XmlRegistry;
import javax.xml.namespace.QName;
import com.microsoft.schemas._2003._10.serialization.arrays.ArrayOfKeyValueOfstringanyType;


/**
 * This object contains factory methods for each 
 * Java content interface and Java element interface 
 * generated in the org.datacontract.schemas._2004._07.telerik_web package. 
 * <p>An ObjectFactory allows you to programatically 
 * construct new instances of the Java representation 
 * for XML content. The Java representation of XML 
 * content can consist of schema derived interfaces 
 * and classes representing the binding of schema 
 * type definitions, element declarations and model 
 * groups.  Factory methods for each of these are 
 * provided in this class.
 * 
 */
@XmlRegistry
public class ObjectFactory {

    private final static QName _RadTreeNodeData_QNAME = new QName("http://schemas.datacontract.org/2004/07/Telerik.Web.UI", "RadTreeNodeData");
    private final static QName _TreeNodeExpandMode_QNAME = new QName("http://schemas.datacontract.org/2004/07/Telerik.Web.UI", "TreeNodeExpandMode");
    private final static QName _ArrayOfRadTreeNodeData_QNAME = new QName("http://schemas.datacontract.org/2004/07/Telerik.Web.UI", "ArrayOfRadTreeNodeData");
    private final static QName _ControlItemData_QNAME = new QName("http://schemas.datacontract.org/2004/07/Telerik.Web.UI", "ControlItemData");
    private final static QName _ControlItemDataText_QNAME = new QName("http://schemas.datacontract.org/2004/07/Telerik.Web.UI", "Text");
    private final static QName _ControlItemDataValue_QNAME = new QName("http://schemas.datacontract.org/2004/07/Telerik.Web.UI", "Value");
    private final static QName _ControlItemDataAttributes_QNAME = new QName("http://schemas.datacontract.org/2004/07/Telerik.Web.UI", "Attributes");
    private final static QName _RadTreeNodeDataExpandedImageUrl_QNAME = new QName("http://schemas.datacontract.org/2004/07/Telerik.Web.UI", "ExpandedImageUrl");
    private final static QName _RadTreeNodeDataHoveredCssClass_QNAME = new QName("http://schemas.datacontract.org/2004/07/Telerik.Web.UI", "HoveredCssClass");
    private final static QName _RadTreeNodeDataNavigateUrl_QNAME = new QName("http://schemas.datacontract.org/2004/07/Telerik.Web.UI", "NavigateUrl");
    private final static QName _RadTreeNodeDataContentCssClass_QNAME = new QName("http://schemas.datacontract.org/2004/07/Telerik.Web.UI", "ContentCssClass");
    private final static QName _RadTreeNodeDataCssClass_QNAME = new QName("http://schemas.datacontract.org/2004/07/Telerik.Web.UI", "CssClass");
    private final static QName _RadTreeNodeDataSelectedCssClass_QNAME = new QName("http://schemas.datacontract.org/2004/07/Telerik.Web.UI", "SelectedCssClass");
    private final static QName _RadTreeNodeDataDisabledCssClass_QNAME = new QName("http://schemas.datacontract.org/2004/07/Telerik.Web.UI", "DisabledCssClass");
    private final static QName _RadTreeNodeDataContextMenuID_QNAME = new QName("http://schemas.datacontract.org/2004/07/Telerik.Web.UI", "ContextMenuID");
    private final static QName _RadTreeNodeDataImageUrl_QNAME = new QName("http://schemas.datacontract.org/2004/07/Telerik.Web.UI", "ImageUrl");
    private final static QName _RadTreeNodeDataHoveredImageUrl_QNAME = new QName("http://schemas.datacontract.org/2004/07/Telerik.Web.UI", "HoveredImageUrl");
    private final static QName _RadTreeNodeDataDisabledImageUrl_QNAME = new QName("http://schemas.datacontract.org/2004/07/Telerik.Web.UI", "DisabledImageUrl");

    /**
     * Create a new ObjectFactory that can be used to create new instances of schema derived classes for package: org.datacontract.schemas._2004._07.telerik_web
     * 
     */
    public ObjectFactory() {
    }

    /**
     * Create an instance of {@link ControlItemData }
     * 
     */
    public ControlItemData createControlItemData() {
        return new ControlItemData();
    }

    /**
     * Create an instance of {@link ArrayOfRadTreeNodeData }
     * 
     */
    public ArrayOfRadTreeNodeData createArrayOfRadTreeNodeData() {
        return new ArrayOfRadTreeNodeData();
    }

    /**
     * Create an instance of {@link RadTreeNodeData }
     * 
     */
    public RadTreeNodeData createRadTreeNodeData() {
        return new RadTreeNodeData();
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link RadTreeNodeData }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://schemas.datacontract.org/2004/07/Telerik.Web.UI", name = "RadTreeNodeData")
    public JAXBElement<RadTreeNodeData> createRadTreeNodeData(RadTreeNodeData value) {
        return new JAXBElement<RadTreeNodeData>(_RadTreeNodeData_QNAME, RadTreeNodeData.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link TreeNodeExpandMode }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://schemas.datacontract.org/2004/07/Telerik.Web.UI", name = "TreeNodeExpandMode")
    public JAXBElement<TreeNodeExpandMode> createTreeNodeExpandMode(TreeNodeExpandMode value) {
        return new JAXBElement<TreeNodeExpandMode>(_TreeNodeExpandMode_QNAME, TreeNodeExpandMode.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link ArrayOfRadTreeNodeData }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://schemas.datacontract.org/2004/07/Telerik.Web.UI", name = "ArrayOfRadTreeNodeData")
    public JAXBElement<ArrayOfRadTreeNodeData> createArrayOfRadTreeNodeData(ArrayOfRadTreeNodeData value) {
        return new JAXBElement<ArrayOfRadTreeNodeData>(_ArrayOfRadTreeNodeData_QNAME, ArrayOfRadTreeNodeData.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link ControlItemData }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://schemas.datacontract.org/2004/07/Telerik.Web.UI", name = "ControlItemData")
    public JAXBElement<ControlItemData> createControlItemData(ControlItemData value) {
        return new JAXBElement<ControlItemData>(_ControlItemData_QNAME, ControlItemData.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link String }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://schemas.datacontract.org/2004/07/Telerik.Web.UI", name = "Text", scope = ControlItemData.class)
    public JAXBElement<String> createControlItemDataText(String value) {
        return new JAXBElement<String>(_ControlItemDataText_QNAME, String.class, ControlItemData.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link String }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://schemas.datacontract.org/2004/07/Telerik.Web.UI", name = "Value", scope = ControlItemData.class)
    public JAXBElement<String> createControlItemDataValue(String value) {
        return new JAXBElement<String>(_ControlItemDataValue_QNAME, String.class, ControlItemData.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link ArrayOfKeyValueOfstringanyType }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://schemas.datacontract.org/2004/07/Telerik.Web.UI", name = "Attributes", scope = ControlItemData.class)
    public JAXBElement<ArrayOfKeyValueOfstringanyType> createControlItemDataAttributes(ArrayOfKeyValueOfstringanyType value) {
        return new JAXBElement<ArrayOfKeyValueOfstringanyType>(_ControlItemDataAttributes_QNAME, ArrayOfKeyValueOfstringanyType.class, ControlItemData.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link String }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://schemas.datacontract.org/2004/07/Telerik.Web.UI", name = "ExpandedImageUrl", scope = RadTreeNodeData.class)
    public JAXBElement<String> createRadTreeNodeDataExpandedImageUrl(String value) {
        return new JAXBElement<String>(_RadTreeNodeDataExpandedImageUrl_QNAME, String.class, RadTreeNodeData.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link String }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://schemas.datacontract.org/2004/07/Telerik.Web.UI", name = "HoveredCssClass", scope = RadTreeNodeData.class)
    public JAXBElement<String> createRadTreeNodeDataHoveredCssClass(String value) {
        return new JAXBElement<String>(_RadTreeNodeDataHoveredCssClass_QNAME, String.class, RadTreeNodeData.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link String }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://schemas.datacontract.org/2004/07/Telerik.Web.UI", name = "NavigateUrl", scope = RadTreeNodeData.class)
    public JAXBElement<String> createRadTreeNodeDataNavigateUrl(String value) {
        return new JAXBElement<String>(_RadTreeNodeDataNavigateUrl_QNAME, String.class, RadTreeNodeData.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link String }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://schemas.datacontract.org/2004/07/Telerik.Web.UI", name = "ContentCssClass", scope = RadTreeNodeData.class)
    public JAXBElement<String> createRadTreeNodeDataContentCssClass(String value) {
        return new JAXBElement<String>(_RadTreeNodeDataContentCssClass_QNAME, String.class, RadTreeNodeData.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link String }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://schemas.datacontract.org/2004/07/Telerik.Web.UI", name = "CssClass", scope = RadTreeNodeData.class)
    public JAXBElement<String> createRadTreeNodeDataCssClass(String value) {
        return new JAXBElement<String>(_RadTreeNodeDataCssClass_QNAME, String.class, RadTreeNodeData.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link String }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://schemas.datacontract.org/2004/07/Telerik.Web.UI", name = "SelectedCssClass", scope = RadTreeNodeData.class)
    public JAXBElement<String> createRadTreeNodeDataSelectedCssClass(String value) {
        return new JAXBElement<String>(_RadTreeNodeDataSelectedCssClass_QNAME, String.class, RadTreeNodeData.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link String }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://schemas.datacontract.org/2004/07/Telerik.Web.UI", name = "DisabledCssClass", scope = RadTreeNodeData.class)
    public JAXBElement<String> createRadTreeNodeDataDisabledCssClass(String value) {
        return new JAXBElement<String>(_RadTreeNodeDataDisabledCssClass_QNAME, String.class, RadTreeNodeData.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link String }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://schemas.datacontract.org/2004/07/Telerik.Web.UI", name = "ContextMenuID", scope = RadTreeNodeData.class)
    public JAXBElement<String> createRadTreeNodeDataContextMenuID(String value) {
        return new JAXBElement<String>(_RadTreeNodeDataContextMenuID_QNAME, String.class, RadTreeNodeData.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link String }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://schemas.datacontract.org/2004/07/Telerik.Web.UI", name = "ImageUrl", scope = RadTreeNodeData.class)
    public JAXBElement<String> createRadTreeNodeDataImageUrl(String value) {
        return new JAXBElement<String>(_RadTreeNodeDataImageUrl_QNAME, String.class, RadTreeNodeData.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link String }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://schemas.datacontract.org/2004/07/Telerik.Web.UI", name = "HoveredImageUrl", scope = RadTreeNodeData.class)
    public JAXBElement<String> createRadTreeNodeDataHoveredImageUrl(String value) {
        return new JAXBElement<String>(_RadTreeNodeDataHoveredImageUrl_QNAME, String.class, RadTreeNodeData.class, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link String }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://schemas.datacontract.org/2004/07/Telerik.Web.UI", name = "DisabledImageUrl", scope = RadTreeNodeData.class)
    public JAXBElement<String> createRadTreeNodeDataDisabledImageUrl(String value) {
        return new JAXBElement<String>(_RadTreeNodeDataDisabledImageUrl_QNAME, String.class, RadTreeNodeData.class, value);
    }

}
