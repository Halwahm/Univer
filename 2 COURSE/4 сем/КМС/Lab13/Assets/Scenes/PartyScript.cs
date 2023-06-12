using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PartyScript : MonoBehaviour
{
    public GameObject Cylinder;
    public Light PointLight1;
    public Light PointLight2;
    public Light PointLight3;

    private void OnTriggerStay(Collider col)
    {
        if (Random.Range(0, 2) < 1)
        {
            PointLight1.intensity = Random.Range(0f, 10f);
            PointLight1.enabled = true;
        }
        else
        {
            PointLight1.enabled = false;
        }

        if (Random.Range(0, 2) < 1)
        {
            PointLight2.intensity = Random.Range(0f, 10f);
            PointLight2.enabled = true;
        }
        else
        {
            PointLight2.enabled = false;
        }

        if (Random.Range(0, 2) < 1)
        {
            PointLight3.intensity = Random.Range(0f, 10f);
            PointLight3.enabled = true;
        }
        else
        {
            PointLight3.enabled = false;
        }

        Cylinder.transform.Rotate(100 * Time.deltaTime, 0, 0);
    }
}
