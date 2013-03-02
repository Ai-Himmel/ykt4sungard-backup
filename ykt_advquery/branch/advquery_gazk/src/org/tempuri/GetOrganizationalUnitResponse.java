
package org.tempuri;

import javax.xml.bind.JAXBElement;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElementRef;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlType;
import org.datacontract.schemas._2004._07.saff.OrganizationalUnit;


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
 *         &lt;element name="GetOrganizationalUnitResult" type="{http://schemas.datacontract.org/2004/07/SAFF.Organization}OrganizationalUnit" minOccurs="0"/>
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
    "getOrganizationalUnitResult"
})
@XmlRootElement(name = "GetOrganizationalUnitResponse")
public class GetOrganizationalUnitResponse {

    @XmlElementRef(name = "GetOrganizationalUnitResult", namespace = "http://tempuri.org/", type = JAXBElement.class)
    protected JAXBElement<OrganizationalUnit> getOrganizationalUnitResult;

    /**
     * Gets the value of the getOrganizationalUnitResult property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link OrganizationalUnit }{@code >}
     *     
     */
    public JAXBElement<OrganizationalUnit> getGetOrganizationalUnitResult() {
        return getOrganizationalUnitResult;
    }

    /**
     * Sets the value of the getOrganizationalUnitResult property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link OrganizationalUnit }{@code >}
     *     
     */
    public void setGetOrganizationalUnitResult(JAXBElement<OrganizationalUnit> value) {
        this.getOrganizationalUnitResult = ((JAXBElement<OrganizationalUnit> ) value);
    }

}
