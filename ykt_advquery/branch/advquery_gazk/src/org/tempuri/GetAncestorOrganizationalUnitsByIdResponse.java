
package org.tempuri;

import javax.xml.bind.JAXBElement;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElementRef;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlType;
import org.datacontract.schemas._2004._07.saff.ArrayOfOrganizationalUnit;


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
 *         &lt;element name="GetAncestorOrganizationalUnitsByIdResult" type="{http://schemas.datacontract.org/2004/07/SAFF.Organization}ArrayOfOrganizationalUnit" minOccurs="0"/>
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
    "getAncestorOrganizationalUnitsByIdResult"
})
@XmlRootElement(name = "GetAncestorOrganizationalUnitsByIdResponse")
public class GetAncestorOrganizationalUnitsByIdResponse {

    @XmlElementRef(name = "GetAncestorOrganizationalUnitsByIdResult", namespace = "http://tempuri.org/", type = JAXBElement.class)
    protected JAXBElement<ArrayOfOrganizationalUnit> getAncestorOrganizationalUnitsByIdResult;

    /**
     * Gets the value of the getAncestorOrganizationalUnitsByIdResult property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link ArrayOfOrganizationalUnit }{@code >}
     *     
     */
    public JAXBElement<ArrayOfOrganizationalUnit> getGetAncestorOrganizationalUnitsByIdResult() {
        return getAncestorOrganizationalUnitsByIdResult;
    }

    /**
     * Sets the value of the getAncestorOrganizationalUnitsByIdResult property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link ArrayOfOrganizationalUnit }{@code >}
     *     
     */
    public void setGetAncestorOrganizationalUnitsByIdResult(JAXBElement<ArrayOfOrganizationalUnit> value) {
        this.getAncestorOrganizationalUnitsByIdResult = ((JAXBElement<ArrayOfOrganizationalUnit> ) value);
    }

}
