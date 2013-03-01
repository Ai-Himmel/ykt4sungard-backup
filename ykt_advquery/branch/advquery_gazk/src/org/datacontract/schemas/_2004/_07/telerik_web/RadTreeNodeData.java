
package org.datacontract.schemas._2004._07.telerik_web;

import javax.xml.bind.JAXBElement;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlElementRef;
import javax.xml.bind.annotation.XmlType;


/**
 * <p>Java class for RadTreeNodeData complex type.
 * 
 * <p>The following schema fragment specifies the expected content contained within this class.
 * 
 * <pre>
 * &lt;complexType name="RadTreeNodeData">
 *   &lt;complexContent>
 *     &lt;extension base="{http://schemas.datacontract.org/2004/07/Telerik.Web.UI}ControlItemData">
 *       &lt;sequence>
 *         &lt;element name="ContentCssClass" type="{http://www.w3.org/2001/XMLSchema}string" minOccurs="0"/>
 *         &lt;element name="ContextMenuID" type="{http://www.w3.org/2001/XMLSchema}string" minOccurs="0"/>
 *         &lt;element name="CssClass" type="{http://www.w3.org/2001/XMLSchema}string" minOccurs="0"/>
 *         &lt;element name="DisabledCssClass" type="{http://www.w3.org/2001/XMLSchema}string" minOccurs="0"/>
 *         &lt;element name="DisabledImageUrl" type="{http://www.w3.org/2001/XMLSchema}string" minOccurs="0"/>
 *         &lt;element name="ExpandMode" type="{http://schemas.datacontract.org/2004/07/Telerik.Web.UI}TreeNodeExpandMode" minOccurs="0"/>
 *         &lt;element name="ExpandedImageUrl" type="{http://www.w3.org/2001/XMLSchema}string" minOccurs="0"/>
 *         &lt;element name="HoveredCssClass" type="{http://www.w3.org/2001/XMLSchema}string" minOccurs="0"/>
 *         &lt;element name="HoveredImageUrl" type="{http://www.w3.org/2001/XMLSchema}string" minOccurs="0"/>
 *         &lt;element name="ImageUrl" type="{http://www.w3.org/2001/XMLSchema}string" minOccurs="0"/>
 *         &lt;element name="NavigateUrl" type="{http://www.w3.org/2001/XMLSchema}string" minOccurs="0"/>
 *         &lt;element name="PostBack" type="{http://www.w3.org/2001/XMLSchema}boolean" minOccurs="0"/>
 *         &lt;element name="SelectedCssClass" type="{http://www.w3.org/2001/XMLSchema}string" minOccurs="0"/>
 *       &lt;/sequence>
 *     &lt;/extension>
 *   &lt;/complexContent>
 * &lt;/complexType>
 * </pre>
 * 
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "RadTreeNodeData", propOrder = {
    "contentCssClass",
    "contextMenuID",
    "cssClass",
    "disabledCssClass",
    "disabledImageUrl",
    "expandMode",
    "expandedImageUrl",
    "hoveredCssClass",
    "hoveredImageUrl",
    "imageUrl",
    "navigateUrl",
    "postBack",
    "selectedCssClass"
})
public class RadTreeNodeData
    extends ControlItemData
{

    @XmlElementRef(name = "ContentCssClass", namespace = "http://schemas.datacontract.org/2004/07/Telerik.Web.UI", type = JAXBElement.class)
    protected JAXBElement<String> contentCssClass;
    @XmlElementRef(name = "ContextMenuID", namespace = "http://schemas.datacontract.org/2004/07/Telerik.Web.UI", type = JAXBElement.class)
    protected JAXBElement<String> contextMenuID;
    @XmlElementRef(name = "CssClass", namespace = "http://schemas.datacontract.org/2004/07/Telerik.Web.UI", type = JAXBElement.class)
    protected JAXBElement<String> cssClass;
    @XmlElementRef(name = "DisabledCssClass", namespace = "http://schemas.datacontract.org/2004/07/Telerik.Web.UI", type = JAXBElement.class)
    protected JAXBElement<String> disabledCssClass;
    @XmlElementRef(name = "DisabledImageUrl", namespace = "http://schemas.datacontract.org/2004/07/Telerik.Web.UI", type = JAXBElement.class)
    protected JAXBElement<String> disabledImageUrl;
    @XmlElement(name = "ExpandMode")
    protected TreeNodeExpandMode expandMode;
    @XmlElementRef(name = "ExpandedImageUrl", namespace = "http://schemas.datacontract.org/2004/07/Telerik.Web.UI", type = JAXBElement.class)
    protected JAXBElement<String> expandedImageUrl;
    @XmlElementRef(name = "HoveredCssClass", namespace = "http://schemas.datacontract.org/2004/07/Telerik.Web.UI", type = JAXBElement.class)
    protected JAXBElement<String> hoveredCssClass;
    @XmlElementRef(name = "HoveredImageUrl", namespace = "http://schemas.datacontract.org/2004/07/Telerik.Web.UI", type = JAXBElement.class)
    protected JAXBElement<String> hoveredImageUrl;
    @XmlElementRef(name = "ImageUrl", namespace = "http://schemas.datacontract.org/2004/07/Telerik.Web.UI", type = JAXBElement.class)
    protected JAXBElement<String> imageUrl;
    @XmlElementRef(name = "NavigateUrl", namespace = "http://schemas.datacontract.org/2004/07/Telerik.Web.UI", type = JAXBElement.class)
    protected JAXBElement<String> navigateUrl;
    @XmlElement(name = "PostBack")
    protected Boolean postBack;
    @XmlElementRef(name = "SelectedCssClass", namespace = "http://schemas.datacontract.org/2004/07/Telerik.Web.UI", type = JAXBElement.class)
    protected JAXBElement<String> selectedCssClass;

    /**
     * Gets the value of the contentCssClass property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public JAXBElement<String> getContentCssClass() {
        return contentCssClass;
    }

    /**
     * Sets the value of the contentCssClass property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public void setContentCssClass(JAXBElement<String> value) {
        this.contentCssClass = ((JAXBElement<String> ) value);
    }

    /**
     * Gets the value of the contextMenuID property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public JAXBElement<String> getContextMenuID() {
        return contextMenuID;
    }

    /**
     * Sets the value of the contextMenuID property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public void setContextMenuID(JAXBElement<String> value) {
        this.contextMenuID = ((JAXBElement<String> ) value);
    }

    /**
     * Gets the value of the cssClass property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public JAXBElement<String> getCssClass() {
        return cssClass;
    }

    /**
     * Sets the value of the cssClass property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public void setCssClass(JAXBElement<String> value) {
        this.cssClass = ((JAXBElement<String> ) value);
    }

    /**
     * Gets the value of the disabledCssClass property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public JAXBElement<String> getDisabledCssClass() {
        return disabledCssClass;
    }

    /**
     * Sets the value of the disabledCssClass property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public void setDisabledCssClass(JAXBElement<String> value) {
        this.disabledCssClass = ((JAXBElement<String> ) value);
    }

    /**
     * Gets the value of the disabledImageUrl property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public JAXBElement<String> getDisabledImageUrl() {
        return disabledImageUrl;
    }

    /**
     * Sets the value of the disabledImageUrl property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public void setDisabledImageUrl(JAXBElement<String> value) {
        this.disabledImageUrl = ((JAXBElement<String> ) value);
    }

    /**
     * Gets the value of the expandMode property.
     * 
     * @return
     *     possible object is
     *     {@link TreeNodeExpandMode }
     *     
     */
    public TreeNodeExpandMode getExpandMode() {
        return expandMode;
    }

    /**
     * Sets the value of the expandMode property.
     * 
     * @param value
     *     allowed object is
     *     {@link TreeNodeExpandMode }
     *     
     */
    public void setExpandMode(TreeNodeExpandMode value) {
        this.expandMode = value;
    }

    /**
     * Gets the value of the expandedImageUrl property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public JAXBElement<String> getExpandedImageUrl() {
        return expandedImageUrl;
    }

    /**
     * Sets the value of the expandedImageUrl property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public void setExpandedImageUrl(JAXBElement<String> value) {
        this.expandedImageUrl = ((JAXBElement<String> ) value);
    }

    /**
     * Gets the value of the hoveredCssClass property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public JAXBElement<String> getHoveredCssClass() {
        return hoveredCssClass;
    }

    /**
     * Sets the value of the hoveredCssClass property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public void setHoveredCssClass(JAXBElement<String> value) {
        this.hoveredCssClass = ((JAXBElement<String> ) value);
    }

    /**
     * Gets the value of the hoveredImageUrl property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public JAXBElement<String> getHoveredImageUrl() {
        return hoveredImageUrl;
    }

    /**
     * Sets the value of the hoveredImageUrl property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public void setHoveredImageUrl(JAXBElement<String> value) {
        this.hoveredImageUrl = ((JAXBElement<String> ) value);
    }

    /**
     * Gets the value of the imageUrl property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public JAXBElement<String> getImageUrl() {
        return imageUrl;
    }

    /**
     * Sets the value of the imageUrl property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public void setImageUrl(JAXBElement<String> value) {
        this.imageUrl = ((JAXBElement<String> ) value);
    }

    /**
     * Gets the value of the navigateUrl property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public JAXBElement<String> getNavigateUrl() {
        return navigateUrl;
    }

    /**
     * Sets the value of the navigateUrl property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public void setNavigateUrl(JAXBElement<String> value) {
        this.navigateUrl = ((JAXBElement<String> ) value);
    }

    /**
     * Gets the value of the postBack property.
     * 
     * @return
     *     possible object is
     *     {@link Boolean }
     *     
     */
    public Boolean isPostBack() {
        return postBack;
    }

    /**
     * Sets the value of the postBack property.
     * 
     * @param value
     *     allowed object is
     *     {@link Boolean }
     *     
     */
    public void setPostBack(Boolean value) {
        this.postBack = value;
    }

    /**
     * Gets the value of the selectedCssClass property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public JAXBElement<String> getSelectedCssClass() {
        return selectedCssClass;
    }

    /**
     * Sets the value of the selectedCssClass property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link String }{@code >}
     *     
     */
    public void setSelectedCssClass(JAXBElement<String> value) {
        this.selectedCssClass = ((JAXBElement<String> ) value);
    }

}
