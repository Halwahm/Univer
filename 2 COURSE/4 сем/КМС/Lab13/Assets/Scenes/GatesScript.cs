using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GatesScript : MonoBehaviour
{
    public Transform LeftDoor;
    public Transform RightDoor; 
    public GameObject FlyingCube;
    private bool _isOpen;

    private void OnTriggerEnter(Collider other)
   {
       if (other.name == "player")
       {
           OpenGate();
       }
   }

    private void OnTriggerExit(Collider other)
    {
        if (other.name == "player")
        {
            CloseGate();
        }
    }

    private void OnTriggerStay(Collider other)
    {
        if (other.name == "robot")
        {
            FlyingCube.transform.Rotate(0, 5f, 0);
            FlyingCube.transform.RotateAround(Vector3.zero, Vector3.up, 200f * Time.deltaTime);
        }
    }


    private void OpenGate()
    {
        if (!_isOpen)
        {
            LeftDoor.Rotate(Vector3.up, 80f);
            RightDoor.Rotate(Vector3.up, -80f);
            _isOpen = true;
        }
    }

    private void CloseGate()
    {
        if (_isOpen)
        {
            LeftDoor.Rotate(Vector3.up, -80f);
            RightDoor.Rotate(Vector3.up, 80f);
            _isOpen = false;
        }
    }
}
