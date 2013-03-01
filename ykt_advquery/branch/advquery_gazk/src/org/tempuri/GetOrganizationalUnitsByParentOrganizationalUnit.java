
package org.tempuri;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlType;


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
 *         &lt;element name="parentOrganizationalUnitId" type="{http://schemas.microsoft.com/2003/10/Serialization/}guid" minOccurs="0"/>
 *         &lt;element name="recursive" type="{http://www.w3.org/2001/XMLSchema}boolean" minOccurs="0"/>
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
    "parentOrganizationalUnitId",
    "recursive"
})
@XmlRootElement(name = "GetOrganizationalUnitsByParentOrganizationalUnit")
public class GetOrganizationalUnitsByParentOrganizationalUnit {

    protected String parentOrganizationalUnitId;
    protected Boolean recursive;

    /**
     * Gets the value of the parentOrganizationalUnitId property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getParentOrganizationalUnitId() {
        return parentOrganizationalUnitId;
    }

    /**
     * Sets the value of the parentOrganizationalUnitId property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setParentOrganizationalUnitId(String value) {
        this.parentOrganizationalUnitId = value;
    }

    /**
     * Gets the value of the recursive property.
     * 
     * @return
     *     possible object is
     *     {@link Boolean }
     *     
     */
    public Boolean isRecursive() {
        return recursive;
    }

    /**
     * Sets the value of the recursive property.
     * 
     * @param value
     *     allowed object is
     *     {@link Boolean }
     *     
     */
    public void setRecursive(Boolean value) {
        this.recursive = value;
    }

}
