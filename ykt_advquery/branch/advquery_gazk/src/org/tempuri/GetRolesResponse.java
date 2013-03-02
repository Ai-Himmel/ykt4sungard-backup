
package org.tempuri;

import javax.xml.bind.JAXBElement;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElementRef;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlType;
import org.datacontract.schemas._2004._07.saff.ArrayOfRole;


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
 *         &lt;element name="GetRolesResult" type="{http://schemas.datacontract.org/2004/07/SAFF.Organization}ArrayOfRole" minOccurs="0"/>
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
    "getRolesResult"
})
@XmlRootElement(name = "GetRolesResponse")
public class GetRolesResponse {

    @XmlElementRef(name = "GetRolesResult", namespace = "http://tempuri.org/", type = JAXBElement.class)
    protected JAXBElement<ArrayOfRole> getRolesResult;

    /**
     * Gets the value of the getRolesResult property.
     * 
     * @return
     *     possible object is
     *     {@link JAXBElement }{@code <}{@link ArrayOfRole }{@code >}
     *     
     */
    public JAXBElement<ArrayOfRole> getGetRolesResult() {
        return getRolesResult;
    }

    /**
     * Sets the value of the getRolesResult property.
     * 
     * @param value
     *     allowed object is
     *     {@link JAXBElement }{@code <}{@link ArrayOfRole }{@code >}
     *     
     */
    public void setGetRolesResult(JAXBElement<ArrayOfRole> value) {
        this.getRolesResult = ((JAXBElement<ArrayOfRole> ) value);
    }

}
