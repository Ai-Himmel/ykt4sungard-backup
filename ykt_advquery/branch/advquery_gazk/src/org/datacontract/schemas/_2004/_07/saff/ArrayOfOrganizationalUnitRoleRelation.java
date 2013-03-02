
package org.datacontract.schemas._2004._07.saff;

import java.util.ArrayList;
import java.util.List;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlType;


/**
 * <p>Java class for ArrayOfOrganizationalUnit_Role_Relation complex type.
 * 
 * <p>The following schema fragment specifies the expected content contained within this class.
 * 
 * <pre>
 * &lt;complexType name="ArrayOfOrganizationalUnit_Role_Relation">
 *   &lt;complexContent>
 *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *       &lt;sequence>
 *         &lt;element name="OrganizationalUnit_Role_Relation" type="{http://schemas.datacontract.org/2004/07/SAFF.Organization}OrganizationalUnit_Role_Relation" maxOccurs="unbounded" minOccurs="0"/>
 *       &lt;/sequence>
 *     &lt;/restriction>
 *   &lt;/complexContent>
 * &lt;/complexType>
 * </pre>
 * 
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "ArrayOfOrganizationalUnit_Role_Relation", propOrder = {
    "organizationalUnitRoleRelation"
})
public class ArrayOfOrganizationalUnitRoleRelation {

    @XmlElement(name = "OrganizationalUnit_Role_Relation", required = true, nillable = true)
    protected List<OrganizationalUnitRoleRelation> organizationalUnitRoleRelation;

    /**
     * Gets the value of the organizationalUnitRoleRelation property.
     * 
     * <p>
     * This accessor method returns a reference to the live list,
     * not a snapshot. Therefore any modification you make to the
     * returned list will be present inside the JAXB object.
     * This is why there is not a <CODE>set</CODE> method for the organizationalUnitRoleRelation property.
     * 
     * <p>
     * For example, to add a new item, do as follows:
     * <pre>
     *    getOrganizationalUnitRoleRelation().add(newItem);
     * </pre>
     * 
     * 
     * <p>
     * Objects of the following type(s) are allowed in the list
     * {@link OrganizationalUnitRoleRelation }
     * 
     * 
     */
    public List<OrganizationalUnitRoleRelation> getOrganizationalUnitRoleRelation() {
        if (organizationalUnitRoleRelation == null) {
            organizationalUnitRoleRelation = new ArrayList<OrganizationalUnitRoleRelation>();
        }
        return this.organizationalUnitRoleRelation;
    }

}
