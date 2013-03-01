
package org.datacontract.schemas._2004._07.saff;

import java.util.ArrayList;
import java.util.List;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlType;


/**
 * <p>Java class for ArrayOfOrganizationalUnit complex type.
 * 
 * <p>The following schema fragment specifies the expected content contained within this class.
 * 
 * <pre>
 * &lt;complexType name="ArrayOfOrganizationalUnit">
 *   &lt;complexContent>
 *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *       &lt;sequence>
 *         &lt;element name="OrganizationalUnit" type="{http://schemas.datacontract.org/2004/07/SAFF.Organization}OrganizationalUnit" maxOccurs="unbounded" minOccurs="0"/>
 *       &lt;/sequence>
 *     &lt;/restriction>
 *   &lt;/complexContent>
 * &lt;/complexType>
 * </pre>
 * 
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "ArrayOfOrganizationalUnit", propOrder = {
    "organizationalUnit"
})
public class ArrayOfOrganizationalUnit {

    @XmlElement(name = "OrganizationalUnit", required = true, nillable = true)
    protected List<OrganizationalUnit> organizationalUnit;

    /**
     * Gets the value of the organizationalUnit property.
     * 
     * <p>
     * This accessor method returns a reference to the live list,
     * not a snapshot. Therefore any modification you make to the
     * returned list will be present inside the JAXB object.
     * This is why there is not a <CODE>set</CODE> method for the organizationalUnit property.
     * 
     * <p>
     * For example, to add a new item, do as follows:
     * <pre>
     *    getOrganizationalUnit().add(newItem);
     * </pre>
     * 
     * 
     * <p>
     * Objects of the following type(s) are allowed in the list
     * {@link OrganizationalUnit }
     * 
     * 
     */
    public List<OrganizationalUnit> getOrganizationalUnit() {
        if (organizationalUnit == null) {
            organizationalUnit = new ArrayList<OrganizationalUnit>();
        }
        return this.organizationalUnit;
    }

}
