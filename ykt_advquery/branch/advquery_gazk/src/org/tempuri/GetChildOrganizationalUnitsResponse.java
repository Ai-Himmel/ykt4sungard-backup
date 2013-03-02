
package org.tempuri;

import javax.xml.bind.JAXBElement;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElementRef;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlType;
import org.datacontract.schemas._2004._07.telerik_web.ArrayOfRadTreeNodeData;


/**
 * <p>Java class for anonymous complex type.
 * 
 * <p>The following schema fragment specifies the expected content contained within this class.
 * 
 * <pre>
 * &lt;complexType>
 *   &lt;complexContent>
 *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *       &lt;sequence>
 *         &lt;element name="GetChildOrganizationalUnitsResult" type="{http://schemas.datacontract.org/2004/07/Telerik.Web.UI}ArrayOfRadTreeNodeData" minOccurs="0"/>
 *       &lt;/sequence>
 *     &lt;/restriction>
 *   &lt;/complexContent>
 * &lt;/complexType>
 * </pre>
 * 
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "", propOrder = {
    "getChildOrganizationalUnitsResult"
})
@XmlRootElement(name = "GetChildOrganizationalUnitsResponse")
public class GetChildOrganizationalUnitsResponse {

    @XmlElementRef(name = "GetChildOrganizationalUnitsResult", namespace = "http://tempuri.org/", type = JAXBElement.class)
    protected JAXBElement<ArrayOfRadTreeNodeData> getChildOrganizationalUnitsResult;

    /**
     * Gets the value of the getChildOrganizationalUnitsResult property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link ArrayOfRadTreeNodeData }{@code >}
     *     
     */
    public JAXBElement<ArrayOfRadTreeNodeData> getGetChildOrganizationalUnitsResult() {
        return getChildOrganizationalUnitsResult;
    }

    /**
     * Sets the value of the getChildOrganizationalUnitsResult property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link ArrayOfRadTreeNodeData }{@code >}
     *     
     */
    public void setGetChildOrganizationalUnitsResult(JAXBElement<ArrayOfRadTreeNodeData> value) {
        this.getChildOrganizationalUnitsResult = ((JAXBElement<ArrayOfRadTreeNodeData> ) value);
    }

}
