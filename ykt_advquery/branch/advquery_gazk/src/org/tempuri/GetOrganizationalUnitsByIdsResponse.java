
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
 *         &lt;element name="GetOrganizationalUnitsByIdsResult" type="{http://schemas.datacontract.org/2004/07/SAFF.Organization}ArrayOfOrganizationalUnit" minOccurs="0"/>
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
    "getOrganizationalUnitsByIdsResult"
})
@XmlRootElement(name = "GetOrganizationalUnitsByIdsResponse")
public class GetOrganizationalUnitsByIdsResponse {

    @XmlElementRef(name = "GetOrganizationalUnitsByIdsResult", namespace = "http://tempuri.org/", type = JAXBElement.class)
    protected JAXBElement<ArrayOfOrganizationalUnit> getOrganizationalUnitsByIdsResult;

    /**
     * Gets the value of the getOrganizationalUnitsByIdsResult property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link ArrayOfOrganizationalUnit }{@code >}
     *     
     */
    public JAXBElement<ArrayOfOrganizationalUnit> getGetOrganizationalUnitsByIdsResult() {
        return getOrganizationalUnitsByIdsResult;
    }

    /**
     * Sets the value of the getOrganizationalUnitsByIdsResult property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link ArrayOfOrganizationalUnit }{@code >}
     *     
     */
    public void setGetOrganizationalUnitsByIdsResult(JAXBElement<ArrayOfOrganizationalUnit> value) {
        this.getOrganizationalUnitsByIdsResult = ((JAXBElement<ArrayOfOrganizationalUnit> ) value);
    }

}
