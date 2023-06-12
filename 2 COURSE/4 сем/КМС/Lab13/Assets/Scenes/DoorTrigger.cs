using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DoorTrigger : MonoBehaviour
{
    public Light Point;

    void OnTriggerEnter(Collider col)
    {
        if (col.gameObject.name == "player")
        {
            Point.enabled = true;
        }
    }

    void OnTriggerExit(Collider col)
    {
        if (col.gameObject.name == "player")
        {
            Point.enabled = false;
        }
    }
}
